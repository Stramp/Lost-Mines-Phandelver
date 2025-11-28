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

// Project includes - CreateSheet
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "Data/Structures/FPointBuyValidationResult.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Handlers
// ============================================================================
#pragma region Point Buy Handlers

/**
 * Processa mudanças em Point Buy allocation (qualquer ability score).
 * Valida Point Buy system e atualiza Final Scores.
 */
void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Motor de Point Buy: aplica alocação nos Final Scores
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // HP muda quando Constitution muda (via RecalculateFinalScores)
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);

    // Valida Point Buy system (calcula PointsRemaining)
    FPointBuyValidationResult ValidationResult = FPointBuyValidator::ValidatePointBuy(
        Asset->PointBuyStrength, Asset->PointBuyDexterity, Asset->PointBuyConstitution, Asset->PointBuyIntelligence,
        Asset->PointBuyWisdom, Asset->PointBuyCharisma);

    // Aplica resultado da validação no Asset (delega para Updater)
    FCharacterSheetDataAssetUpdaters::ApplyPointBuyValidationResult(Asset, ValidationResult.PointsRemaining);

    // Log de aviso se scores estão fora do range válido (não crítico - sistema ajusta automaticamente)
    if (!ValidationResult.bAllScoresValid && !ValidationResult.LogMessage.IsEmpty())
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("HandlePointBuyAllocationChange"));
        FLoggingSystem::LogWarning(Context, ValidationResult.LogMessage, false);
    }
}

#pragma endregion Point Buy Handlers
