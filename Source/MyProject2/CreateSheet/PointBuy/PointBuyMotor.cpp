// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyMotor.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Utils
#include "Utils/CalculationHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

FPointBuyResult FPointBuyMotor::ApplyPointBuy(FCharacterSheetData &Data)
{
    FLogContext Context(TEXT("PointBuy"), TEXT("ApplyPointBuy"));

    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
        return FPointBuyResult();
    }

    // Motor converte propriedades diretas para TMap<FName, int32> antes de passar para helpers
    // Isso mantém os helpers recebendo dados puros e o motor encapsulando a transformação
    // Usa helper puro para eliminar duplicação (DRY)
    TMap<FName, int32> PointBuyMap = CharacterSheetHelpers::CreatePointBuyMapFromData(
        Data.PointBuyStrength, Data.PointBuyDexterity, Data.PointBuyConstitution, Data.PointBuyIntelligence,
        Data.PointBuyWisdom, Data.PointBuyCharisma);

    // Valida e ajusta se necessário (máximo MAX_POINT_BUY_POINTS)
    const int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS;
    FString FeedbackMessage;
    bool bWasAdjusted = false;

    // Calcula custo total dos scores base (BASE_ABILITY_SCORE + PointBuy) usando helper puro
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    int32 PointsRemaining = MaxPoints - TotalCost;

    // Se excedeu MAX_POINT_BUY_POINTS, ajusta automaticamente (sistema ajusta - sem popup)
    if (PointsRemaining < 0)
    {
        FeedbackMessage = CharacterSheetHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
        bWasAdjusted = true;

        // Recalcula após ajuste usando helper (elimina duplicação)
        BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);
        TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
        PointsRemaining = MaxPoints - TotalCost;

        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("Alocação ajustada automaticamente. %s"), *FeedbackMessage), false);
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
