// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassTypes.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

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

FMulticlassProficienciesEntry FMulticlassHelpers::ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry)
{
    FMulticlassProficienciesEntry Result;
    Result.armas = SourceEntry.armas;
    Result.armaduras = SourceEntry.armaduras;
    Result.savingThrows = SourceEntry.savingThrows;

    // Converte FSkills para FMulticlassSkills
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

    FString Result;
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

    if (LevelInClass < 1 || LevelInClass > 20)
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
