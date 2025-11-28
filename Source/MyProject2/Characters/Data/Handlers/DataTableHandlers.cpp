// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHandlers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/ValidationGuard.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableSchemaValidator.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Data Table Handlers
// ============================================================================
#pragma region Data Table Handlers

/**
 * Processa mudanças em Data Tables (RaceDataTable, BackgroundDataTable, FeatDataTable, ClassDataTable).
 * Valida tipo de Data Table e atualiza visibilidade da ficha.
 *
 * @param Asset Data Asset
 * @param PropertyName Nome da propriedade que mudou (para identificar qual Data Table foi modificada)
 */
void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida tipo de Data Table específica que foi alterada
    // Usa GET_MEMBER_NAME_CHECKED para comparar com PropertyName
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->RaceDataTable, PropertyName,
                                                               TEXT("FRaceDataRow"), DataTableHelpers::IsRaceDataTable);

        // Valida schema JSON (estrutura básica)
        if (Asset->RaceDataTable)
        {
            FDataTableSchemaValidationResult SchemaResult =
                FDataTableSchemaValidator::ValidateBasicStructure(Asset->RaceDataTable, TEXT("RaceDataTable"));
            if (!SchemaResult.bIsValid)
            {
                // Log erros de schema (não bloqueia, apenas avisa)
                for (const FString &Error : SchemaResult.Errors)
                {
                    UE_LOG(LogTemp, Warning, TEXT("RaceDataTable Schema Error: %s"), *Error);
                }
            }
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(
            Asset, Asset->ClassDataTable, PropertyName, TEXT("FClassDataRow"), DataTableHelpers::IsClassDataTable);

        // Valida schema JSON (estrutura básica)
        if (Asset->ClassDataTable)
        {
            FDataTableSchemaValidationResult SchemaResult =
                FDataTableSchemaValidator::ValidateBasicStructure(Asset->ClassDataTable, TEXT("ClassDataTable"));
            if (!SchemaResult.bIsValid)
            {
                // Log erros de schema (não bloqueia, apenas avisa)
                for (const FString &Error : SchemaResult.Errors)
                {
                    UE_LOG(LogTemp, Warning, TEXT("ClassDataTable Schema Error: %s"), *Error);
                }
            }
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->BackgroundDataTable, PropertyName,
                                                               TEXT("FBackgroundDataRow"),
                                                               DataTableHelpers::IsBackgroundDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->FeatDataTable, PropertyName,
                                                               TEXT("FFeatDataRow"), DataTableHelpers::IsFeatDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassFeaturesDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->ClassFeaturesDataTable, PropertyName,
                                                               TEXT("FFeatureDataRow"),
                                                               DataTableHelpers::IsFeatureDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ProficiencyDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->ProficiencyDataTable, PropertyName,
                                                               TEXT("FProficiencyDataRow"),
                                                               DataTableHelpers::IsProficiencyDataTable);
    }

    // Valida se todas as Data Tables obrigatórias estão cadastradas (exibe popup se faltando)
    // NOTA: Esta validação não verifica tipo, apenas se estão preenchidas (lógica de visibilidade)
    FCharacterSheetDataAssetValidators::ValidateDataTables(Asset);

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
    // NOTA: Esta lógica não deve ser alterada - apenas verifica se != nullptr
    FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(Asset);

    // Log informativo sobre status dos Data Tables
    FCharacterSheetDataAssetHelpers::LogDataTableStatus(Asset);
}

#pragma endregion Data Table Handlers
