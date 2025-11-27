// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "Data/Structures/MulticlassTypes.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/FeatureDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DnDConstants.h"

// Engine includes
#include "Engine/DataTable.h"
#include "UObject/StructOnScope.h"
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Get Available Class With Tag Requirements
// ============================================================================
#pragma region Get Available Class With Tag Requirements

TArray<FName> FMulticlassHelpers::GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                                       const TArray<int32> &Attributes)
{
    TArray<FName> Result;

    if (!ClassDataTable || Attributes.Num() < FMulticlassValidators::NUM_ATTRIBUTES)
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

    const TMap<FString, FMulticlassValidators::FAttributeInfo> AttributeMap =
        FMulticlassValidators::CreateAttributeMap();
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);

    // Agora itera pelos rows com segurança (já sabemos que o tipo está correto)
    for (const FName &RowName : RowNames)
    {
        const FClassDataRow *Row =
            NonConstTable->FindRow<FClassDataRow>(RowName, TEXT("GetAvailableClassWithTagRequirements"));

        if (Row)
        {
            FMulticlassValidators::ProcessClassWithRequirements(Row, Attributes, AttributeMap, Result);
        }
    }

    return Result;
}

#pragma endregion Get Available Class With Tag Requirements

// ============================================================================
// Progression Validation
// ============================================================================
#pragma region Progression Validation

bool FMulticlassHelpers::CanProcessProgression(FName ClassName, int32 LevelInClass)
{
    // Progression só pode ser processada se há classe válida e nível > 0
    return ClassName != NAME_None && LevelInClass > 0;
}

#pragma endregion Progression Validation

// ============================================================================
// Proficiencies Conversion
// ============================================================================
#pragma region Proficiencies Conversion

TArray<FName> FMulticlassHelpers::ResolveProficiencyIDsToNames(const TArray<FName> &ProficiencyIDs,
                                                               const UDataTable *ProficiencyDataTable)
{
    TArray<FName> ResolvedNames;
    ResolvedNames.Reserve(ProficiencyIDs.Num()); // Otimização: pre-aloca memória

    if (!ProficiencyDataTable)
    {
        // Se não há tabela, loga erro crítico e retorna IDs originais
        FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyIDsToNames"));
        FLoggingSystem::LogError(
            Context,
            TEXT("ProficiencyDataTable não está configurado. IDs não serão resolvidos para nomes legíveis."), true);
        return ProficiencyIDs;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(ProficiencyDataTable);
    FString TableName = ProficiencyDataTable->GetName();
    int32 UnresolvedCount = 0;

    for (const FName &ProficiencyID : ProficiencyIDs)
    {
        if (ProficiencyID == NAME_None)
        {
            continue;
        }

        // Busca proficiência na tabela pelo ID
        const FProficiencyDataRow *ProficiencyRow =
            DataTableHelpers::FindProficiencyRowByID(ProficiencyID, NonConstTable);

        if (ProficiencyRow && ProficiencyRow->Name != NAME_None)
        {
            // Usa nome legível se encontrado
            ResolvedNames.Add(ProficiencyRow->Name);
        }
        else
        {
            // Fallback: usa ID original se não encontrado na tabela
            ResolvedNames.Add(ProficiencyID);
            UnresolvedCount++;

            // Loga erro de Data Table
            FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyIDsToNames"));
            FLoggingSystem::LogDataTableError(
                Context, TableName, ProficiencyID.ToString(), TEXT("ProficiencyID"),
                FString::Printf(TEXT("Proficiência '%s' não encontrada na tabela. "
                                     "Verifique se o JSON tem 'ProficiencyID' ao invés de "
                                     "'p_id' e se o ID corresponde."),
                                *ProficiencyID.ToString()));
        }
    }

    // Loga resumo se houver IDs não resolvidos
    if (UnresolvedCount > 0)
    {
        FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyIDsToNames"));
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d proficiência(s) não foram resolvidas para nomes legíveis."), UnresolvedCount),
            true);
    }

    return ResolvedNames;
}

FMulticlassProficienciesEntry FMulticlassHelpers::ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry,
                                                                            const UDataTable *ProficiencyDataTable)
{
    FMulticlassProficienciesEntry Result;

    // Resolve IDs de armas para nomes legíveis
    Result.armas = FMulticlassHelpers::ResolveProficiencyIDsToNames(SourceEntry.armas, ProficiencyDataTable);

    // Resolve IDs de armaduras para nomes legíveis
    Result.armaduras = FMulticlassHelpers::ResolveProficiencyIDsToNames(SourceEntry.armaduras, ProficiencyDataTable);

    // Saving throws não precisam resolução (já são nomes de atributos)
    Result.savingThrows = SourceEntry.savingThrows;

    // Skills não precisam resolução (já são nomes de skills)
    Result.FSkills.available = SourceEntry.FSkills.available;
    Result.FSkills.qtdAvailable = SourceEntry.FSkills.qtdAvailable;

    // Armazena estado inicial para cálculo dinâmico de qtdAvailable
    Result.FSkills.InitialAvailableCount = SourceEntry.FSkills.available.Num();
    Result.FSkills.InitialQtdAvailable = SourceEntry.FSkills.qtdAvailable;

    return Result;
}


#pragma endregion Proficiencies Conversion

// ============================================================================
// Proficiencies Validation
// ============================================================================
#pragma region Proficiencies Validation

bool FMulticlassHelpers::ValidateLoadProficienciesInputs(FName ClassName, int32 LevelInClass,
                                                         const UDataTable *ClassDataTable)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    if (!ClassDataTable)
    {
        return false;
    }

    // Proficiências são ganhas apenas no nível 1
    if (LevelInClass != 1)
    {
        return false;
    }

    return true;
}

#pragma endregion Proficiencies Validation

// ============================================================================
// Process Level Change Helpers
// ============================================================================
#pragma region Process Level Change Helpers

FString FMulticlassHelpers::BuildFeaturesString(const TArray<FName> &Features)
{
    if (Features.Num() == 0)
    {
        return TEXT("Nenhum");
    }

    // Otimização: pre-aloca memória estimada (nome médio ~20 chars + separador)
    FString Result;
    Result.Reserve(Features.Num() * 25);

    for (int32 i = 0; i < Features.Num(); ++i)
    {
        if (i > 0)
        {
            Result += TEXT(", ");
        }
        Result += Features[i].ToString();
    }

    return Result;
}

bool FMulticlassHelpers::ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass,
                                                          const UDataTable *ClassDataTable)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    if (!ClassDataTable)
    {
        return false;
    }

    if (LevelInClass < DnDConstants::MIN_LEVEL || LevelInClass > DnDConstants::MAX_LEVEL)
    {
        return false;
    }

    return true;
}

const FClassDataRow *FMulticlassHelpers::FindAndValidateClassRow(FName ClassName, const UDataTable *ClassDataTable)
{
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        return nullptr;
    }

    return ClassRow;
}

bool FMulticlassHelpers::ExtractLevelFeatures(const TArray<FProgressEntry> &Progression, int32 LevelInClass,
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

#pragma endregion Process Level Change Helpers

// ============================================================================
// Feature Conversion Helpers
// ============================================================================
#pragma region Feature Conversion Helpers

FMulticlassClassFeature FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(const FFeatureDataRow &FeatureRow,
                                                                                  int32 LevelUnlocked)
{
    FMulticlassClassFeature Result;

    // Copia dados básicos
    Result.Name = FeatureRow.Name;
    Result.FC_ID = FeatureRow.FC_ID;
    Result.Description = FeatureRow.Description;
    Result.LevelUnlocked = LevelUnlocked; // Usa o nível passado como parâmetro
    Result.FeatureType = FeatureRow.FeatureType;
    Result.FeatureData = FeatureRow.FeatureData;

    // Popula AvailableChoices com nomes das escolhas disponíveis (se houver)
    // Para features do tipo "Choice" ou "SubclassSelection", preenche com nomes das escolhas
    if (FeatureRow.FeatureType == TEXT("Choice") || FeatureRow.FeatureType == TEXT("SubclassSelection"))
    {
        if (FeatureRow.AvailableChoices.Num() > 0)
        {
            // Usa o primeiro nome como padrão (jogador pode mudar no editor)
            Result.AvailableChoices = FeatureRow.AvailableChoices[0].Name;
        }
        else
        {
            Result.AvailableChoices = NAME_None;
        }
    }
    else
    {
        // Para features automáticas, AvailableChoices não é usado
        Result.AvailableChoices = NAME_None;
    }

    return Result;
}

bool FMulticlassHelpers::LoadFeaturesForLevel(const TArray<FName> &FeatureIDs, const UDataTable *FeatureDataTable,
                                               int32 LevelUnlocked, TArray<FMulticlassClassFeature> &OutFeatures)
{
    OutFeatures.Empty();

    if (!FeatureDataTable)
    {
        FLogContext Context(TEXT("Multiclass"), TEXT("LoadFeaturesForLevel"));
        FLoggingSystem::LogError(
            Context,
            TEXT("ClassFeaturesDataTable não está configurado. Features não serão carregadas."), true);
        return false;
    }

    if (FeatureIDs.Num() == 0)
    {
        // Nível sem features é válido (alguns níveis não têm features)
        return false;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(FeatureDataTable);
    FString TableName = FeatureDataTable->GetName();
    int32 LoadedCount = 0;
    int32 NotFoundCount = 0;

    for (const FName &FeatureID : FeatureIDs)
    {
        if (FeatureID == NAME_None)
        {
            continue;
        }

        // Busca feature na tabela pelo FC_ID
        const FFeatureDataRow *FeatureRow = DataTableHelpers::FindFeatureRowByID(FeatureID, NonConstTable);

        if (FeatureRow)
        {
            // Converte para FMulticlassClassFeature
            FMulticlassClassFeature ConvertedFeature =
                ConvertFeatureRowToMulticlassFeature(*FeatureRow, LevelUnlocked);
            OutFeatures.Add(ConvertedFeature);
            LoadedCount++;
        }
        else
        {
            // Feature não encontrada na tabela
            NotFoundCount++;

            FLogContext Context(TEXT("Multiclass"), TEXT("LoadFeaturesForLevel"));
            FLoggingSystem::LogDataTableError(
                Context, TableName, FeatureID.ToString(), TEXT("FC_ID"),
                FString::Printf(TEXT("Feature '%s' não encontrada na tabela. Verifique se o ID corresponde."),
                               *FeatureID.ToString()));
        }
    }

    // Log resumo se houver features não encontradas
    if (NotFoundCount > 0)
    {
        FLogContext Context(TEXT("Multiclass"), TEXT("LoadFeaturesForLevel"));
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d feature(s) não foram encontradas na tabela."), NotFoundCount), true);
    }

    return LoadedCount > 0;
}

const FClassDataRow *FMulticlassHelpers::FindClassRowWithErrorLogging(FName ClassName, const UDataTable *ClassDataTable,
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

bool FMulticlassHelpers::LoadClassBasicInfo(FName ClassName, const UDataTable *ClassDataTable,
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

    // Copia MulticlassRequirements da tabela
    OutMulticlassRequirements = ClassRow->FClass.MulticlassRequirements;

    return true;
}

#pragma endregion Feature Conversion Helpers
