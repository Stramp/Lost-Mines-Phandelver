// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/DataTableIntegrityValidator.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/TraitDataTable.h"
#include "Data/Tables/LanguageDataTable.h"
#include "Data/Tables/SkillDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// DataTableIntegrityValidator Implementation
// ============================================================================
#pragma region DataTableIntegrityValidator Implementation

FDataTableValidationResult FDataTableIntegrityValidator::ValidateAllDataTables(UCharacterSheetDataAsset* Asset)
{
    FDataTableValidationResult Result;

    if (!Asset)
    {
        Result.AddError(TEXT("CharacterSheetDataAsset é nullptr"));
        return Result;
    }

    // Validar cada Data Table individualmente
    if (Asset->RaceDataTable)
    {
        FDataTableValidationResult RaceResult = ValidateDataTable(Asset->RaceDataTable);
        if (!RaceResult.bIsValid)
        {
            Result.Errors.Append(RaceResult.Errors);
            Result.Warnings.Append(RaceResult.Warnings);
        }
    }
    else
    {
        Result.AddWarning(TEXT("RaceDataTable não está configurado"));
    }

    if (Asset->ClassDataTable)
    {
        FDataTableValidationResult ClassResult = ValidateDataTable(Asset->ClassDataTable);
        if (!ClassResult.bIsValid)
        {
            Result.Errors.Append(ClassResult.Errors);
            Result.Warnings.Append(ClassResult.Warnings);
        }
    }
    else
    {
        Result.AddWarning(TEXT("ClassDataTable não está configurado"));
    }

    if (Asset->BackgroundDataTable)
    {
        FDataTableValidationResult BackgroundResult = ValidateDataTable(Asset->BackgroundDataTable);
        if (!BackgroundResult.bIsValid)
        {
            Result.Errors.Append(BackgroundResult.Errors);
            Result.Warnings.Append(BackgroundResult.Warnings);
        }
    }
    else
    {
        Result.AddWarning(TEXT("BackgroundDataTable não está configurado"));
    }

    // Validar referências entre Data Tables
    if (Asset->RaceDataTable && Asset->TraitDataTable)
    {
        // Validar TraitHandles em RaceDataTable
        const TMap<FName, uint8*>& RowMap = Asset->RaceDataTable->GetRowMap();
        for (const auto& Pair : RowMap)
        {
            if (const FRaceDataRow* RaceRow = reinterpret_cast<const FRaceDataRow*>(Pair.Value))
            {
                for (int32 i = 0; i < RaceRow->TraitHandles.Num(); ++i)
                {
                    FString Context = FString::Printf(TEXT("RaceDataTable[%s].TraitHandles[%d]"), *Pair.Key.ToString(), i);
                    FDataTableValidationResult HandleResult = ValidateHandle(RaceRow->TraitHandles[i], Context);
                    if (!HandleResult.bIsValid)
                    {
                        Result.Errors.Append(HandleResult.Errors);
                    }
                }
            }
        }
    }

    if (Asset->ClassDataTable && Asset->SkillDataTable)
    {
        // Validar AvailableSkillHandles em ClassDataTable
        const TMap<FName, uint8*>& RowMap = Asset->ClassDataTable->GetRowMap();
        for (const auto& Pair : RowMap)
        {
            if (const FClassDataRow* ClassRow = reinterpret_cast<const FClassDataRow*>(Pair.Value))
            {
                for (int32 i = 0; i < ClassRow->FClass.Skills.AvailableSkillHandles.Num(); ++i)
                {
                    FString Context = FString::Printf(TEXT("ClassDataTable[%s].AvailableSkillHandles[%d]"), *Pair.Key.ToString(), i);
                    FDataTableValidationResult HandleResult = ValidateHandle(ClassRow->FClass.Skills.AvailableSkillHandles[i], Context);
                    if (!HandleResult.bIsValid)
                    {
                        Result.Errors.Append(HandleResult.Errors);
                    }
                }
            }
        }
    }

    return Result;
}

FDataTableValidationResult FDataTableIntegrityValidator::ValidateDataTable(UDataTable* DataTable)
{
    FDataTableValidationResult Result;

    if (!DataTable)
    {
        Result.AddError(TEXT("DataTable é nullptr"));
        return Result;
    }

    // Validar estrutura básica
    ValidateBasicStructure(DataTable, Result);

    // Validar referências
    ValidateHandles(DataTable, Result);

    // Validar IDs únicos
    ValidateUniqueIDs(DataTable, Result);

    return Result;
}

FDataTableValidationResult FDataTableIntegrityValidator::ValidateHandle(const FDataTableRowHandle& Handle, const FString& Context)
{
    FDataTableValidationResult Result;

    if (Handle.IsNull())
    {
        Result.AddError(FString::Printf(TEXT("%s: Handle é nulo"), *Context));
        return Result;
    }

    if (!Handle.DataTable)
    {
        Result.AddError(FString::Printf(TEXT("%s: DataTable é nullptr"), *Context));
        return Result;
    }

    if (Handle.RowName == NAME_None)
    {
        Result.AddError(FString::Printf(TEXT("%s: RowName é NAME_None"), *Context));
        return Result;
    }

    // Verificar se a row existe
    if (!DataTableRowHandleHelpers::IsHandleValid(Handle))
    {
        Result.AddError(FString::Printf(TEXT("%s: Row '%s' não existe em DataTable '%s'"),
            *Context, *Handle.RowName.ToString(), *Handle.DataTable->GetName()));
    }

    return Result;
}

void FDataTableIntegrityValidator::ValidateBasicStructure(UDataTable* DataTable, FDataTableValidationResult& Result)
{
    if (!DataTable || !DataTable->RowStruct)
    {
        return;
    }

    const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

    for (const auto& Pair : RowMap)
    {
        // Verificar se Name está presente (Key Field obrigatório)
        if (Pair.Key == NAME_None)
        {
            Result.AddError(FString::Printf(TEXT("DataTable '%s': Row com Name NAME_None encontrado"), *DataTable->GetName()));
        }

        // Verificar se ID está presente (usando reflexão básica)
        // Nota: Validação completa de ID requer conhecimento do tipo específico da row
        // Esta é uma validação básica - validação completa deve ser feita por tipo específico
    }
}

void FDataTableIntegrityValidator::ValidateHandles(UDataTable* DataTable, FDataTableValidationResult& Result)
{
    // Validação de handles é feita por tipo específico
    // Esta função é um placeholder para validação genérica se necessário
    // Validação completa é feita em ValidateAllDataTables com conhecimento dos tipos específicos
}

void FDataTableIntegrityValidator::ValidateUniqueIDs(UDataTable* DataTable, FDataTableValidationResult& Result)
{
    if (!DataTable || !DataTable->RowStruct)
    {
        return;
    }

    // Validação de IDs únicos requer conhecimento do tipo específico da row
    // Esta função é um placeholder para validação genérica se necessário
    // Validação completa deve ser feita por tipo específico (ex: verificar FRaceDataRow.ID)
}

#pragma endregion DataTableIntegrityValidator Implementation
