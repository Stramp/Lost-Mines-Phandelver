// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/PointBuyHelpers.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// Point Buy System Helpers
// ============================================================================
#pragma region Point Buy System Helpers

TMap<FName, int32> CharacterSheetHelpers::CreatePointBuyMapFromData(int32 PointBuyStrength, int32 PointBuyDexterity,
                                                                    int32 PointBuyConstitution,
                                                                    int32 PointBuyIntelligence, int32 PointBuyWisdom,
                                                                    int32 PointBuyCharisma)
{
    TMap<FName, int32> PointBuyMap;
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<int32> Values = {PointBuyStrength,     PointBuyDexterity, PointBuyConstitution,
                            PointBuyIntelligence, PointBuyWisdom,    PointBuyCharisma};

    // Garante que temos exatamente NUM_ABILITY_SCORES atributos
    check(AbilityNames.Num() == DnDConstants::NUM_ABILITY_SCORES);
    check(Values.Num() == DnDConstants::NUM_ABILITY_SCORES);

    for (int32 i = 0; i < AbilityNames.Num() && i < Values.Num(); ++i)
    {
        PointBuyMap.Add(AbilityNames[i], Values[i]);
    }

    return PointBuyMap;
}

TMap<FName, int32> CharacterSheetHelpers::CreateBaseScoresFromPointBuy(const TMap<FName, int32> &PointBuyMap)
{
    TMap<FName, int32> BaseScores;

    // Apenas cria entradas para ability scores presentes no map
    for (const auto &Pair : PointBuyMap)
    {
        BaseScores.Add(Pair.Key, DnDConstants::BASE_ABILITY_SCORE + Pair.Value);
    }

    return BaseScores;
}

#pragma endregion Point Buy System Helpers
