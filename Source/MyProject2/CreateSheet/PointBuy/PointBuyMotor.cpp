// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyMotor.h"

// Project includes - Utils
#include "Utils/CalculationHelpers.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Motor
// ============================================================================
#pragma region Point Buy Motor

void FPointBuyMotor::ApplyPointBuy(const TMap<FName, int32>& PointBuyAllocation, int32& FinalStrength,
                                    int32& FinalDexterity, int32& FinalConstitution, int32& FinalIntelligence,
                                    int32& FinalWisdom, int32& FinalCharisma)
{
    // Motor puro: apenas aplica Point Buy nos Final Scores
    // Assume que dados são válidos e já convertidos (pré-condição)
    CalculationHelpers::IncrementFinalScoresWithPointBuy(PointBuyAllocation, FinalStrength, FinalDexterity,
                                                         FinalConstitution, FinalIntelligence, FinalWisdom,
                                                         FinalCharisma);
}

#pragma endregion Point Buy Motor
