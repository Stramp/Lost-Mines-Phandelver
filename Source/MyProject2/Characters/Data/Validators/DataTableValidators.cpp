// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// Data Tables Validation
// ============================================================================
#pragma region Data Tables Validation

FValidationResult FCharacterSheetDataAssetValidators::ValidateDataTables(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateDataTables"));

    // Tabelas obrigatórias (sempre necessárias)
    TArray<FString> MissingTables;

    if (!Asset->RaceDataTable)
    {
        MissingTables.Add(TEXT("RaceDataTable"));
    }

    if (!Asset->BackgroundDataTable)
    {
        MissingTables.Add(TEXT("BackgroundDataTable"));
    }

    if (!Asset->ClassDataTable)
    {
        MissingTables.Add(TEXT("ClassDataTable"));
    }

    // FeatDataTable é obrigatória (todas as 6 tabelas são obrigatórias)
    if (!Asset->FeatDataTable)
    {
        MissingTables.Add(TEXT("FeatDataTable"));
    }

    // ClassFeaturesDataTable e ProficiencyDataTable são obrigatórias
    if (!Asset->ClassFeaturesDataTable)
    {
        MissingTables.Add(TEXT("ClassFeaturesDataTable"));
    }

    if (!Asset->ProficiencyDataTable)
    {
        MissingTables.Add(TEXT("ProficiencyDataTable"));
    }

    // Validação de tipo de Data Tables (sem alterar lógica de visibilidade)
    // Verifica se cada Data Table atribuída tem o RowStruct correto
    // NOTA: Esta validação é apenas informativa - não bloqueia lógica de visibilidade
    if (Asset->RaceDataTable && !DataTableHelpers::IsRaceDataTable(const_cast<UDataTable *>(Asset->RaceDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("RaceDataTable tem tipo incorreto. Esperado: FRaceDataRow. Por favor, atribua uma "
                                 "Data Table do tipo correto.")),
            0.5f);
    }

    if (Asset->ClassDataTable && !DataTableHelpers::IsClassDataTable(const_cast<UDataTable *>(Asset->ClassDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("ClassDataTable tem tipo incorreto. Esperado: FClassDataRow. Por favor, atribua uma "
                                 "Data Table do tipo correto.")),
            0.5f);
    }

    if (Asset->BackgroundDataTable &&
        !DataTableHelpers::IsBackgroundDataTable(const_cast<UDataTable *>(Asset->BackgroundDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("BackgroundDataTable tem tipo incorreto. Esperado: FBackgroundDataRow. Por favor, "
                                 "atribua uma Data Table do tipo correto.")),
            0.5f);
    }

    if (Asset->FeatDataTable && !DataTableHelpers::IsFeatDataTable(const_cast<UDataTable *>(Asset->FeatDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("FeatDataTable tem tipo incorreto. Esperado: FFeatDataRow. Por favor, atribua uma "
                                 "Data Table do tipo correto.")),
            0.5f);
    }

    if (Asset->ClassFeaturesDataTable &&
        !DataTableHelpers::IsFeatureDataTable(const_cast<UDataTable *>(Asset->ClassFeaturesDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("ClassFeaturesDataTable tem tipo incorreto. Esperado: FFeatureDataRow. Por favor, "
                                 "atribua uma Data Table do tipo correto.")),
            0.5f);
    }

    if (Asset->ProficiencyDataTable &&
        !DataTableHelpers::IsProficiencyDataTable(const_cast<UDataTable *>(Asset->ProficiencyDataTable)))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(
            Context,
            FString::Printf(TEXT("ProficiencyDataTable tem tipo incorreto. Esperado: FProficiencyDataRow. Por favor, "
                                 "atribua uma Data Table do tipo correto.")),
            0.5f);
    }

    // Nota: A verificação de visibilidade (UpdateSheetVisibility) já fornece feedback visual forte
    // quando tabelas estão faltando (esconde todas as props). Não é necessário popup adicional.
    // Esta validação não retorna correções (não há como corrigir automaticamente)
    return Result;
}

#pragma endregion Data Tables Validation
