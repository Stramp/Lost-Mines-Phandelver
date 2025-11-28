// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceBonusMotor.h"

// Project includes - CreateSheet
#include "CreateSheet/RaceBonus/RaceBonusHelpers.h"

#pragma endregion Includes

// ============================================================================
// Race Bonus Motor
// ============================================================================
#pragma region Race Bonus Motor

void FRaceBonusMotor::ApplyRacialBonuses(const TMap<FName, int32>& RacialBonuses, int32& FinalStrength,
                                         int32& FinalDexterity, int32& FinalConstitution, int32& FinalIntelligence,
                                         int32& FinalWisdom, int32& FinalCharisma)
{
    // Motor puro: apenas aplica bônus raciais nos Final Scores
    // Assume que bônus já foram calculados (pré-condição)
    FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(RacialBonuses, FinalStrength, FinalDexterity,
                                                             FinalConstitution, FinalIntelligence, FinalWisdom,
                                                             FinalCharisma);
}

#pragma endregion Race Bonus Motor
