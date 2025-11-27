// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetCore.h"

// Project includes - CreateSheet
#include "CreateSheet/PointBuy/PointBuyMotor.h"
#include "CreateSheet/RaceBonus/RaceBonusMotor.h"

// Project includes - Data Structures
#include "Data/Structures/FPointBuyResult.h"

// Project includes - Utils
#include "Utils/CalculationHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

void FCharacterSheetCore::RecalculateFinalScores(FCharacterSheetData &Data, FPointBuyResult *OutPointBuyResult)
{
    FLogContext Context(TEXT("CharacterSheetCore"), TEXT("RecalculateFinalScores"));

    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
        return;
    }

    // Orquestrador: reseta para base (BASE_ABILITY_SCORE) e aplica cada motor independente
    // Fórmula: FinalScore = BASE_ABILITY_SCORE + RacialBonus + PointBuyAllocation

    // 1. Reset para base (BASE_ABILITY_SCORE)
    CalculationHelpers::ResetFinalScoresToBase(*Data.FinalStrength, *Data.FinalDexterity, *Data.FinalConstitution,
                                               *Data.FinalIntelligence, *Data.FinalWisdom, *Data.FinalCharisma);

    // 2. Aplica bônus raciais (motor independente)
    FRaceBonusMotor::ApplyRacialBonuses(Data);

    // 3. Aplica Point Buy (motor independente, não conhece bônus racial)
    // Retorna resultado com feedback para o caller ajustar a UI
    FPointBuyResult PointBuyResult = FPointBuyMotor::ApplyPointBuy(Data);
    if (OutPointBuyResult)
    {
        *OutPointBuyResult = PointBuyResult;
    }
}
