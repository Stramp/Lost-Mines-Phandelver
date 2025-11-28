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

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

#pragma endregion Includes

// ============================================================================
// Background Handlers
// ============================================================================
#pragma region Background Handlers

/**
 * Processa mudanças em SelectedBackground.
 * Atualiza escolhas de idiomas e campos calculados.
 */
void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Escolhas de idiomas podem mudar quando background muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);
}

#pragma endregion Background Handlers
