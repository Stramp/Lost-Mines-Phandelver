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
#include "Utils/PointBuyHelpers.h"
#include "CreateSheet/PointBuy/PointBuyValidator.h"

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
        return FPointBuyResult(false, false, TMap<FName, int32>(), 0, TEXT("Erro: Referências inválidas"));
    }

    // Motor converte propriedades diretas para TMap<FName, int32> antes de passar para helpers
    // Isso mantém os helpers recebendo dados puros e o motor encapsulando a transformação
    // Usa helper puro para eliminar duplicação (DRY)
    TMap<FName, int32> PointBuyMap = CharacterSheetHelpers::CreatePointBuyMapFromData(
        Data.PointBuyStrength, Data.PointBuyDexterity, Data.PointBuyConstitution, Data.PointBuyIntelligence,
        Data.PointBuyWisdom, Data.PointBuyCharisma);

    // Valida usando PointBuyValidator (separação de responsabilidades - Clean Code)
    FPointBuyValidationResult ValidationResult =
        FPointBuyValidator::ValidatePointBuy(Data.PointBuyStrength, Data.PointBuyDexterity, Data.PointBuyConstitution,
                                             Data.PointBuyIntelligence, Data.PointBuyWisdom, Data.PointBuyCharisma);

    const int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS;
    FString FeedbackMessage;
    bool bWasAutoAdjusted = false;
    int32 PointsRemaining = ValidationResult.PointsRemaining;

    // Se excedeu MAX_POINT_BUY_POINTS, ajusta automaticamente (sistema ajusta - sem popup)
    if (PointsRemaining < 0)
    {
        FeedbackMessage = PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
        bWasAutoAdjusted = true;

        // Recalcula após ajuste (usa helper para evitar duplicação)
        PointsRemaining = PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, MaxPoints);

        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("Alocação ajustada automaticamente. %s"), *FeedbackMessage), false);
    }
    else if (PointsRemaining == 0)
    {
        FeedbackMessage = FString::Printf(TEXT("Todos os pontos foram alocados (%d/%d)"), MaxPoints, MaxPoints);
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
    return FPointBuyResult(true, bWasAutoAdjusted, PointBuyMap, PointsRemaining, FeedbackMessage);
}
