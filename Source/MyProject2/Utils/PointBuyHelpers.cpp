// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/PointBuyHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Helpers
// ============================================================================
#pragma region Point Buy Helpers

int32 PointBuyHelpers::CalculatePointsRemaining(const TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Calcula custo total usando helpers puros (elimina duplicação)
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    return MaxPoints - TotalCost;
}

FString PointBuyHelpers::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints,
                                                  UDataTable *AbilityScoreDataTable)
{
    // Ordem de redução: do final da fila (inverte ordem de GetAbilityScoreNames)
    // Usa GetAbilityScoreNames() para manter Data-Driven (não hardcoded)
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames(AbilityScoreDataTable);
    TArray<FName> ReductionOrder;
    // Inverte ordem (do final para o início)
    for (int32 i = AbilityNames.Num() - 1; i >= 0; --i)
    {
        ReductionOrder.Add(AbilityNames[i]);
    }

    // Calcula custo atual usando helper puro (elimina duplicação e magic number)
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);

    // Reduz até chegar a MaxPoints pontos
    int32 PointsToReduce = TotalCost - MaxPoints;
    int32 CurrentIndex = 0;

    while (PointsToReduce > 0 && CurrentIndex < ReductionOrder.Num())
    {
        FName CurrentAttribute = ReductionOrder[CurrentIndex];
        int32 *CurrentAllocation = PointBuyMap.Find(CurrentAttribute);

        if (CurrentAllocation && *CurrentAllocation > 0)
        {
            // Calcula custo atual deste atributo
            int32 CurrentBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentAllocation;
            int32 CurrentCost = CharacterSheetHelpers::CalculatePointBuyCost(CurrentBaseScore);

            // Reduz 1 ponto
            (*CurrentAllocation)--;
            int32 NewBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentAllocation;
            int32 NewCost = CharacterSheetHelpers::CalculatePointBuyCost(NewBaseScore);

            // Atualiza pontos a reduzir
            PointsToReduce -= (CurrentCost - NewCost);

            // Se ainda precisa reduzir, continua no mesmo atributo
            if (PointsToReduce > 0)
            {
                continue;
            }
        }

        // Próximo atributo
        CurrentIndex++;
    }

    // Gera mensagem de feedback
    if (PointsToReduce <= 0)
    {
        return FString::Printf(TEXT("Alocação ajustada: reduzido do final da fila para não exceder %d pontos"),
                               MaxPoints);
    }
    else
    {
        return FString::Printf(TEXT("Alocação ajustada parcialmente: ainda excede %d pontos por %d"), MaxPoints,
                               PointsToReduce);
    }
}

#pragma endregion Point Buy Helpers
