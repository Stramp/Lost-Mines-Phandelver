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
#include "Characters/Data/Validators/CharacterSheetDataAssetCorrectionApplier.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// Variant Human Handlers
// ============================================================================
#pragma region Variant Human Handlers

/**
 * Processa mudanças em Variant Human choices (CustomAbilityScoreChoices, SelectedFeat, SelectedSkill).
 * Valida escolhas e recalcula bônus raciais e proficiências.
 */
void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Converte SelectedFeat de Name para FC_ID se necessário
    // Dropdown retorna Name (ex: "Magic Initiate"), mas código espera ID (ex: "Feat_MagicInitiate")
    if (Asset->SelectedFeat != NAME_None && Asset->FeatDataTable)
    {
        FName FeatID = DataTableHelpers::FindFeatIDByName(Asset->SelectedFeat, Asset->FeatDataTable);
        if (FeatID != NAME_None && FeatID != Asset->SelectedFeat)
        {
            // Converte Name para ID
            Asset->SelectedFeat = FeatID;
        }
    }

    // Valida escolhas de Variant Human e aplica correções
    FValidationResult VariantHumanResult = FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(Asset);
    if (VariantHumanResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, VariantHumanResult);
    }

    // Recalcula bônus raciais (Custom ASI afeta bônus)
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // Recalcula proficiências (SelectedSkill do Variant Human afeta proficiências)
}

#pragma endregion Variant Human Handlers
