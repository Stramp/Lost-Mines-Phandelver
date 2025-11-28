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

int32 CharacterSheetHelpers::CalculatePointBuyCost(int32 Score)
{
    // Validação: scores devem estar entre MIN_POINT_BUY_SCORE e MAX_POINT_BUY_SCORE
    if (Score < DnDConstants::MIN_POINT_BUY_SCORE || Score > DnDConstants::MAX_POINT_BUY_SCORE)
    {
        return 0;
    }

    // Tabela oficial D&D 5e Point Buy
    if (Score == DnDConstants::MIN_POINT_BUY_SCORE)
    {
        return 0;
    }
    else if (Score >= (DnDConstants::MIN_POINT_BUY_SCORE + 1) && Score <= (DnDConstants::MAX_POINT_BUY_SCORE - 2))
    {
        // Scores 9-13: custo = (score - BASE_ABILITY_SCORE)
        return Score - DnDConstants::BASE_ABILITY_SCORE;
    }
    else if (Score == DnDConstants::INTERMEDIATE_POINT_BUY_SCORE)
    {
        return DnDConstants::POINT_BUY_COST_14;
    }
    else if (Score == DnDConstants::MAX_POINT_BUY_SCORE)
    {
        return DnDConstants::POINT_BUY_COST_15;
    }

    return 0;
}

int32 CharacterSheetHelpers::CalculateTotalPointBuyCost(const TMap<FName, int32> &AbilityScores)
{
    int32 TotalCost = 0;

    for (const auto &Pair : AbilityScores)
    {
        TotalCost += CalculatePointBuyCost(Pair.Value);
    }

    return TotalCost;
}

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
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();

    for (const FName &AbilityName : AbilityNames)
    {
        BaseScores.Add(AbilityName, DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(AbilityName));
    }

    return BaseScores;
}

FString CharacterSheetHelpers::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Delega para PointBuyHelpers::AdjustPointBuyAllocation
    return PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints, nullptr);
}

#pragma endregion Point Buy System Helpers
