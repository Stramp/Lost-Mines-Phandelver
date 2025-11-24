// Copyright Epic Games, Inc. All Rights Reserved.

#include "PointBuyMotor.h"
#include "../Core/CharacterSheetData.h"
#include "../../Utils/CalculationHelpers.h"
#include "../../Utils/CharacterSheetHelpers.h"
#include "Logging/LogMacros.h"

FPointBuyResult FPointBuyMotor::ApplyPointBuy(FCharacterSheetData &Data)
{
    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        UE_LOG(LogTemp, Error, TEXT("PointBuyMotor: Referências de Final Scores inválidas"));
        return FPointBuyResult();
    }

    // Motor converte propriedades diretas para TMap<FName, int32> antes de passar para helpers
    // Isso mantém os helpers recebendo dados puros e o motor encapsulando a transformação
    TMap<FName, int32> PointBuyMap;
    PointBuyMap.Add(TEXT("Strength"), Data.PointBuyStrength);
    PointBuyMap.Add(TEXT("Dexterity"), Data.PointBuyDexterity);
    PointBuyMap.Add(TEXT("Constitution"), Data.PointBuyConstitution);
    PointBuyMap.Add(TEXT("Intelligence"), Data.PointBuyIntelligence);
    PointBuyMap.Add(TEXT("Wisdom"), Data.PointBuyWisdom);
    PointBuyMap.Add(TEXT("Charisma"), Data.PointBuyCharisma);

    // Valida e ajusta se necessário (máximo 27 pontos)
    const int32 MaxPoints = 27;
    FString FeedbackMessage;
    bool bWasAdjusted = false;

    // Calcula custo total dos scores base (8 + PointBuy)
    TMap<FName, int32> BaseScores;
    BaseScores.Add(TEXT("Strength"), 8 + PointBuyMap.FindRef(TEXT("Strength")));
    BaseScores.Add(TEXT("Dexterity"), 8 + PointBuyMap.FindRef(TEXT("Dexterity")));
    BaseScores.Add(TEXT("Constitution"), 8 + PointBuyMap.FindRef(TEXT("Constitution")));
    BaseScores.Add(TEXT("Intelligence"), 8 + PointBuyMap.FindRef(TEXT("Intelligence")));
    BaseScores.Add(TEXT("Wisdom"), 8 + PointBuyMap.FindRef(TEXT("Wisdom")));
    BaseScores.Add(TEXT("Charisma"), 8 + PointBuyMap.FindRef(TEXT("Charisma")));

    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    int32 PointsRemaining = MaxPoints - TotalCost;

    // Se excedeu 27 pontos, ajusta automaticamente
    if (PointsRemaining < 0)
    {
        FeedbackMessage = AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
        bWasAdjusted = true;

        // Recalcula após ajuste
        BaseScores.Empty();
        BaseScores.Add(TEXT("Strength"), 8 + PointBuyMap.FindRef(TEXT("Strength")));
        BaseScores.Add(TEXT("Dexterity"), 8 + PointBuyMap.FindRef(TEXT("Dexterity")));
        BaseScores.Add(TEXT("Constitution"), 8 + PointBuyMap.FindRef(TEXT("Constitution")));
        BaseScores.Add(TEXT("Intelligence"), 8 + PointBuyMap.FindRef(TEXT("Intelligence")));
        BaseScores.Add(TEXT("Wisdom"), 8 + PointBuyMap.FindRef(TEXT("Wisdom")));
        BaseScores.Add(TEXT("Charisma"), 8 + PointBuyMap.FindRef(TEXT("Charisma")));

        TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
        PointsRemaining = MaxPoints - TotalCost;

        UE_LOG(LogTemp, Warning, TEXT("PointBuyMotor: Alocação ajustada automaticamente. %s"), *FeedbackMessage);
    }
    else if (PointsRemaining == 0)
    {
        FeedbackMessage = TEXT("Todos os pontos foram alocados (27/27)");
    }
    else
    {
        FeedbackMessage = FString::Printf(TEXT("Pontos restantes: %d"), PointsRemaining);
    }

    // Aplica Point Buy nos Final Scores (motor independente, não conhece bônus racial)
    CalculationHelpers::IncrementFinalScoresWithPointBuy(PointBuyMap, *Data.FinalStrength, *Data.FinalDexterity,
                                                         *Data.FinalConstitution, *Data.FinalIntelligence,
                                                         *Data.FinalWisdom, *Data.FinalCharisma);

    // Retorna resultado com feedback
    return FPointBuyResult(bWasAdjusted, PointBuyMap, PointsRemaining, FeedbackMessage);
}

FString FPointBuyMotor::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Ordem de redução: do final da fila (Charisma -> Wisdom -> Intelligence -> Constitution -> Dexterity -> Strength)
    TArray<FName> ReductionOrder = {TEXT("Charisma"),     TEXT("Wisdom"),    TEXT("Intelligence"),
                                    TEXT("Constitution"), TEXT("Dexterity"), TEXT("Strength")};

    // Calcula custo atual
    TMap<FName, int32> BaseScores;
    for (const auto &Pair : PointBuyMap)
    {
        BaseScores.Add(Pair.Key, 8 + Pair.Value);
    }
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);

    // Reduz até chegar a 27 pontos
    int32 PointsToReduce = TotalCost - MaxPoints;
    int32 CurrentIndex = 0;

    while (PointsToReduce > 0 && CurrentIndex < ReductionOrder.Num())
    {
        FName CurrentAttribute = ReductionOrder[CurrentIndex];
        int32 *CurrentAllocation = PointBuyMap.Find(CurrentAttribute);

        if (CurrentAllocation && *CurrentAllocation > 0)
        {
            // Calcula custo atual deste atributo
            int32 CurrentBaseScore = 8 + *CurrentAllocation;
            int32 CurrentCost = CharacterSheetHelpers::CalculatePointBuyCost(CurrentBaseScore);

            // Reduz 1 ponto
            (*CurrentAllocation)--;
            int32 NewBaseScore = 8 + *CurrentAllocation;
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
