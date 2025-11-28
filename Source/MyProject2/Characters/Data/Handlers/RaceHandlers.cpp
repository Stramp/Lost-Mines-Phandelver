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
// Race Handlers
// ============================================================================
#pragma region Race Handlers

/**
 * Processa mudanças em SelectedRace ou SelectedSubrace.
 * Reseta sub-raça se raça mudou, atualiza flags e recalcula scores.
 */
void FCharacterSheetDataAssetHandlers::HandleRaceChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Resetar sub-raça se raça mudou
    FCharacterSheetDataAssetHelpers::ResetSubraceIfRaceChanged(Asset, PropertyName);

    // Atualiza flag Variant Human e reseta escolhas se necessário
    FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(Asset);

    // Atualiza flag de sub-raças disponíveis
    FCharacterSheetDataAssetUpdaters::UpdateSubraceFlag(Asset);

    // Bônus raciais mudam quando raça/sub-raça muda
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // HP muda quando Constitution muda (via RecalculateFinalScores)
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);

    // Escolhas de idiomas podem mudar quando raça/sub-raça muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);
}

#pragma endregion Race Handlers
