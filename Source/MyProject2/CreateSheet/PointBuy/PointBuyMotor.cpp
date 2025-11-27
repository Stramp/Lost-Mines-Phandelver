// Copyright Epic Games, Inc. All Rights Reserved.

#include "PointBuyMotor.h"
#include "Data/Structures/FCharacterSheetData.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"
// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

FPointBuyResult FPointBuyMotor::ApplyPointBuy(FCharacterSheetData &Data)
{
    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLogContext Context(TEXT("PointBuy"), TEXT("ApplyPointBuy"));
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
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
    const int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS;
    FString FeedbackMessage;
    bool bWasAdjusted = false;

    // Calcula custo total dos scores base (8 + PointBuy) usando helper puro
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    int32 PointsRemaining = MaxPoints - TotalCost;

    // Se excedeu 27 pontos, ajusta automaticamente
    if (PointsRemaining < 0)
    {
        FeedbackMessage = CharacterSheetHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
        bWasAdjusted = true;

        // Recalcula após ajuste usando helper (elimina duplicação)
        BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
        TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
        PointsRemaining = MaxPoints - TotalCost;

        FLogContext Context(TEXT("PointBuy"), TEXT("ApplyPointBuy"));
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("Alocação ajustada automaticamente. %s"), *FeedbackMessage), true);
    }
    else if (PointsRemaining == 0)
    {
        FeedbackMessage = FString::Printf(TEXT("Todos os pontos foram alocados (%d/%d)"),
                                          DnDConstants::MAX_POINT_BUY_POINTS, DnDConstants::MAX_POINT_BUY_POINTS);
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
