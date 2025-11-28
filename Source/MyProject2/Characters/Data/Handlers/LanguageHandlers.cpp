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

#pragma endregion Includes

// ============================================================================
// Language Handlers
// ============================================================================
#pragma region Language Handlers

/**
 * Processa mudanças em SelectedLanguages.
 * Valida escolhas de idiomas e atualiza campos calculados.
 */
void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de idiomas e aplica correções
    FValidationResult LanguageResult = FCharacterSheetDataAssetValidators::ValidateLanguageChoices(Asset);
    if (LanguageResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, LanguageResult);
    }

    // Recalcula idiomas finais
}

#pragma endregion Language Handlers
