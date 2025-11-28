// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/PointBuyHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Calculate Points Remaining
// ============================================================================
#pragma region Calculate Points Remaining

int32 PointBuyHelpers::CalculatePointsRemaining(const TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Converte PointBuyMap para BaseScores para calcular custo
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);

    // Calcula custo total usando helper existente
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);

    // Retorna pontos restantes (pode ser negativo se excedeu)
    return MaxPoints - TotalCost;
}

#pragma endregion Calculate Points Remaining

// ============================================================================
// Adjust Point Buy Allocation
// ============================================================================
#pragma region Adjust Point Buy Allocation

FString PointBuyHelpers::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints,
                                                   UDataTable *AbilityScoreDataTable)
{
    // Calcula custo atual
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 CurrentCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);

    // Se não excedeu, não precisa ajustar
    if (CurrentCost <= MaxPoints)
    {
        return FString::Printf(TEXT("Alocação válida (%d/%d pontos)"), CurrentCost, MaxPoints);
    }

    // Obtém ordem de ability scores (Data-Driven)
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames(AbilityScoreDataTable);

    // Ordem de redução: do final da fila (último ability score primeiro)
    // Isso mantém atributos mais importantes (Strength, Dexterity) intactos quando possível
    TArray<FName> ReductionOrder;
    ReductionOrder.Reserve(AbilityNames.Num());
    for (int32 i = AbilityNames.Num() - 1; i >= 0; --i)
    {
        ReductionOrder.Add(AbilityNames[i]);
    }

    int32 ExcessPoints = CurrentCost - MaxPoints;
    int32 PointsReduced = 0;

    // Reduz valores do final da fila até que o custo seja <= MaxPoints
    for (FName &AbilityName : ReductionOrder)
    {
        if (ExcessPoints <= 0)
        {
            break;
        }

        int32 *CurrentValue = PointBuyMap.Find(AbilityName);
        if (!CurrentValue || *CurrentValue <= 0)
        {
            continue;
        }

        // Calcula quanto reduzir deste atributo
        int32 OldBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentValue;
        int32 OldCost = CharacterSheetHelpers::CalculatePointBuyCost(OldBaseScore);

        // Reduz 1 ponto de Point Buy
        (*CurrentValue)--;
        if (*CurrentValue < 0)
        {
            *CurrentValue = 0;
        }

        int32 NewBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentValue;
        int32 NewCost = CharacterSheetHelpers::CalculatePointBuyCost(NewBaseScore);
        int32 CostReduction = OldCost - NewCost;

        ExcessPoints -= CostReduction;
        PointsReduced += CostReduction;

        // Recalcula custo total para verificar se já está dentro do limite
        BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
        CurrentCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
        ExcessPoints = CurrentCost - MaxPoints;
    }

    // Prepara mensagem de feedback
    if (PointsReduced > 0)
    {
        return FString::Printf(TEXT("Alocação ajustada: %d pontos removidos. Custo final: %d/%d"), PointsReduced,
                               CurrentCost, MaxPoints);
    }

    return FString::Printf(TEXT("Alocação ajustada. Custo final: %d/%d"), CurrentCost, MaxPoints);
}

#pragma endregion Adjust Point Buy Allocation
