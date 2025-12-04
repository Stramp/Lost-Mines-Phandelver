// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/PointBuyHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"
#include "Utils/DataTableHelpers.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Calculate Point Buy Cost
// ============================================================================
#pragma region Calculate Point Buy Cost

int32 PointBuyHelpers::CalculatePointBuyCost(int32 Score)
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

#pragma endregion Calculate Point Buy Cost

// ============================================================================
// Calculate Total Point Buy Cost
// ============================================================================
#pragma region Calculate Total Point Buy Cost

int32 PointBuyHelpers::CalculateTotalPointBuyCost(const TMap<FName, int32> &AbilityScores)
{
    int32 TotalCost = 0;

    for (const auto &Pair : AbilityScores)
    {
        TotalCost += CalculatePointBuyCost(Pair.Value);
    }

    return TotalCost;
}

#pragma endregion Calculate Total Point Buy Cost

// ============================================================================
// Calculate Points Remaining
// ============================================================================
#pragma region Calculate Points Remaining

int32 PointBuyHelpers::CalculatePointsRemaining(const TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Converte PointBuyMap para BaseScores para calcular custo
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);

    // Calcula custo total usando helper de PointBuyHelpers
    int32 TotalCost = CalculateTotalPointBuyCost(BaseScores);

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
    int32 CurrentCost = CalculateTotalPointBuyCost(BaseScores);

    // Se não excedeu, não precisa ajustar
    if (CurrentCost <= MaxPoints)
    {
        return FString::Printf(TEXT("Alocação válida (%d/%d pontos)"), CurrentCost, MaxPoints);
    }

    // Obtém ordem de ability scores (Data-Driven)
    TArray<FNameWithID> AbilityNamesWithIDs = CharacterSheetHelpers::GetAbilityScoreNames(AbilityScoreDataTable);
    TArray<FName> AbilityNames;
    for (const FNameWithID &AbilityWithID : AbilityNamesWithIDs)
    {
        AbilityNames.Add(AbilityWithID.Name);
    }

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
    const int32 MaxIterations = 100; // Proteção contra loop infinito
    int32 Iterations = 0;

    // Reduz valores do final da fila até que o custo seja <= MaxPoints
    // Continua reduzindo até que não haja mais excesso ou não seja possível reduzir mais
    while (ExcessPoints > 0 && Iterations < MaxIterations)
    {
        Iterations++;
        bool bReducedAny = false;

        // Tenta reduzir de cada atributo (do final para o início)
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
            int32 OldCost = CalculatePointBuyCost(OldBaseScore);

            // Reduz 1 ponto de Point Buy
            (*CurrentValue)--;
            if (*CurrentValue < 0)
            {
                *CurrentValue = 0;
            }

            int32 NewBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentValue;
            int32 NewCost = CalculatePointBuyCost(NewBaseScore);
            int32 CostReduction = OldCost - NewCost;

            if (CostReduction > 0)
            {
                ExcessPoints -= CostReduction;
                PointsReduced += CostReduction;
                bReducedAny = true;
            }

            // Recalcula custo total para verificar se já está dentro do limite
            BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
            CurrentCost = CalculateTotalPointBuyCost(BaseScores);
            ExcessPoints = CurrentCost - MaxPoints;
        }

        // Se não conseguiu reduzir nada nesta iteração, para o loop
        if (!bReducedAny)
        {
            break;
        }
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
