// Copyright Epic Games, Inc. All Rights Reserved.

#include "PointBuyMotor.h"
#include "CreateSheet/Core/CharacterSheetData.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
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
        FeedbackMessage = CharacterSheetHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
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
