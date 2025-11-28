// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassDataLoadingHelpers.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassValidators.h"
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"
#include "CreateSheet/Multiclass/MulticlassConversionHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatureDataTable.h"

// Project includes - Structures
#include "Data/Structures/MulticlassTypes.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Get Available Class With Tag Requirements
// ============================================================================
#pragma region Get Available Class With Tag Requirements

TArray<FName> FMulticlassDataLoadingHelpers::GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                                                  const TArray<int32> &Attributes,
                                                                                  const UDataTable *AbilityScoreDataTable)
{
    TArray<FName> Result;

    if (!ClassDataTable || Attributes.Num() < FMulticlassValidationHelpers::NUM_ATTRIBUTES)
    {
        return Result;
    }

    // Verifica o tipo do Row Structure do DataTable ANTES de tentar acessar rows
    // Isso evita erros "incorrect type" que aparecem quando FindRow é chamado
    const UScriptStruct *RowStruct = ClassDataTable->GetRowStruct();
    if (!RowStruct)
    {
        // DataTable não tem Row Structure configurado
        return Result;
    }

    // Compara o nome do struct para verificar se é FClassDataRow
    // Usa GetFName() para comparação segura
    const FName RowStructName = RowStruct->GetFName();
    const FName ExpectedStructName = FClassDataRow::StaticStruct()->GetFName();

    if (RowStructName != ExpectedStructName)
    {
        // DataTable não está configurado com FClassDataRow, retorna vazio silenciosamente
        return Result;
    }

    // Verifica se o DataTable tem rows
    const TArray<FName> RowNames = ClassDataTable->GetRowNames();
    if (RowNames.Num() == 0)
    {
        return Result;
    }

    const TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> AttributeMap =
        FMulticlassValidationHelpers::CreateAttributeMap();
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);

    // Agora itera pelos rows com segurança (já sabemos que o tipo está correto)
    for (const FName &RowName : RowNames)
    {
        const FClassDataRow *Row =
            NonConstTable->FindRow<FClassDataRow>(RowName, TEXT("GetAvailableClassWithTagRequirements"));

        if (Row)
        {
            FMulticlassValidators::ProcessClassWithRequirements(Row, Attributes, AttributeMap, Result,
                                                                AbilityScoreDataTable);
        }
    }

    return Result;
}

#pragma endregion Get Available Class With Tag Requirements

// ============================================================================
// Find Class Row With Error Logging
// ============================================================================
#pragma region Find Class Row With Error Logging

const FClassDataRow *FMulticlassDataLoadingHelpers::FindClassRowWithErrorLogging(FName ClassName,
                                                                                  const UDataTable *ClassDataTable,
                                                                                  const FString &FunctionName)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return nullptr;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        FLogContext Context(TEXT("Multiclass"), FunctionName);
        FString TableName = ClassDataTable->GetName();
        FLoggingSystem::LogDataTableError(
            Context, TableName, ClassName.ToString(), TEXT("Name"),
            FString::Printf(TEXT("Classe '%s' não encontrada na tabela."), *ClassName.ToString()));
    }

    return ClassRow;
}

#pragma endregion Find Class Row With Error Logging

// ============================================================================
// Load Class Basic Info
// ============================================================================
#pragma region Load Class Basic Info

bool FMulticlassDataLoadingHelpers::LoadClassBasicInfo(FName ClassName, const UDataTable *ClassDataTable,
                                                        TArray<FString> &OutMulticlassRequirements)
{
    OutMulticlassRequirements.Empty();

    if (ClassName == NAME_None || !ClassDataTable)
    {
        return false;
    }

    // Busca dados da classe na tabela (com logging de erro automático)
    const FClassDataRow *ClassRow =
        FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassBasicInfo"));
    if (!ClassRow)
    {
        return false;
    }

    // Copia MulticlassRequirements da tabela (estrutura flat)
    OutMulticlassRequirements = ClassRow->MulticlassRequirements;

    return true;
}

#pragma endregion Load Class Basic Info

// ============================================================================
// Extract Level Features
// ============================================================================
#pragma region Extract Level Features

bool FMulticlassDataLoadingHelpers::ExtractLevelFeatures(const TArray<FProgressEntry> &Progression, int32 LevelInClass,
                                                         const FProgressEntry *&OutLevelEntry)
{
    if (LevelInClass > Progression.Num())
    {
        return false;
    }

    // Array é 0-based, nível é 1-based
    OutLevelEntry = &Progression[LevelInClass - 1];
    return true;
}

#pragma endregion Extract Level Features

// ============================================================================
// Load Features For Level
// ============================================================================
#pragma region Load Features For Level

bool FMulticlassDataLoadingHelpers::LoadFeaturesForLevel(const TArray<FDataTableRowHandle> &FeatureHandles,
                                                          const UDataTable *FeatureDataTable, int32 LevelUnlocked,
                                                          TArray<FMulticlassClassFeature> &OutFeatures)
{
    FLogContext Context(TEXT("Multiclass"), TEXT("LoadFeaturesForLevel"));
    OutFeatures.Empty();

    if (!FeatureDataTable)
    {
        FLoggingSystem::LogError(
            Context, TEXT("ClassFeaturesDataTable não está configurado. Features não serão carregadas."), true);
        return false;
    }

    if (FeatureHandles.Num() == 0)
    {
        // Nível sem features é válido (alguns níveis não têm features)
        return false;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(FeatureDataTable);
    FString TableName = FeatureDataTable->GetName();
    int32 LoadedCount = 0;
    int32 NotFoundCount = 0;

    for (const FDataTableRowHandle &FeatureHandle : FeatureHandles)
    {
        if (FeatureHandle.RowName == NAME_None)
        {
            continue;
        }

        // Resolve handle para obter FeatureRow
        const FFeatureDataRow *FeatureRow = DataTableRowHandleHelpers::ResolveHandle<FFeatureDataRow>(FeatureHandle);

        if (!FeatureRow && FeatureHandle.DataTable.Get() != nullptr)
        {
            // Fallback: tenta buscar pelo RowName diretamente
            FeatureRow = DataTableHelpers::FindFeatureRowByID(FeatureHandle.RowName, NonConstTable);
        }

        if (FeatureRow)
        {
            // Converte para FMulticlassClassFeature
            FMulticlassClassFeature ConvertedFeature =
                FMulticlassConversionHelpers::ConvertFeatureRowToMulticlassFeature(*FeatureRow, LevelUnlocked);
            OutFeatures.Add(ConvertedFeature);
            LoadedCount++;
        }
        else
        {
            // Feature não encontrada na tabela
            NotFoundCount++;

            FLoggingSystem::LogDataTableError(
                Context, TableName, FeatureHandle.RowName.ToString(), TEXT("FeatureHandle"),
                FString::Printf(TEXT("Feature '%s' não encontrada na tabela. Verifique se o handle está correto."),
                                *FeatureHandle.RowName.ToString()));
        }
    }

    // Log resumo se houver features não encontradas (sistema ajusta automaticamente - sem popup)
    if (NotFoundCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("%d feature(s) não foram encontradas na tabela."), NotFoundCount), false);
    }

    return LoadedCount > 0;
}

#pragma endregion Load Features For Level

// ============================================================================
// Log Level Change Features
// ============================================================================
#pragma region Log Level Change Features

void FMulticlassDataLoadingHelpers::LogLevelChangeFeatures(FName ClassName, int32 LevelInClass,
                                                            const UDataTable *ClassDataTable)
{
    // Validação de entrada (guard clauses)
    if (!FMulticlassValidationHelpers::ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return;
    }

    // Busca dados da classe na tabela
    const FClassDataRow *ClassRow =
        FMulticlassValidationHelpers::FindAndValidateClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return;
    }

    // Extrai features do nível específico (estrutura flat)
    const FProgressEntry *LevelEntry = nullptr;
    if (!ExtractLevelFeatures(ClassRow->Progression, LevelInClass, LevelEntry))
    {
        return;
    }

    // Log apenas quando há features ganhas (ponto chave)
    // Converte FeatureHandles para FName[] para logging
    TArray<FName> FeatureNames;
    for (const FDataTableRowHandle &Handle : LevelEntry->FeatureHandles)
    {
        if (Handle.RowName != NAME_None)
        {
            FeatureNames.Add(Handle.RowName);
        }
    }
    if (FeatureNames.Num() > 0)
    {
        FString FeaturesString = FMulticlassConversionHelpers::BuildFeaturesString(FeatureNames);
        FLogContext Context(TEXT("Multiclass"), TEXT("LogLevelChangeFeatures"));
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Classe '%s' nível %d: features ganhas = [%s]"),
                                                         *ClassName.ToString(), LevelInClass, *FeaturesString));
    }
}

#pragma endregion Log Level Change Features
