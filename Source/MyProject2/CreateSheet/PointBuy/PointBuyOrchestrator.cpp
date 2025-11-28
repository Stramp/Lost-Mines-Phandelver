// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyOrchestrator.h"

// Project includes - CreateSheet
#include "CreateSheet/PointBuy/PointBuyMotor.h"
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "CreateSheet/PointBuy/PointBuyConverter.h"
#include "CreateSheet/PointBuy/PointBuyFormatter.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"
#include "Data/Structures/FPointBuyApplicationResult.h"

// Project includes - Utils
#include "Utils/PointBuyHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Orchestrator
// ============================================================================
#pragma region Point Buy Orchestrator

FPointBuyResult FPointBuyOrchestrator::ProcessPointBuy(FCharacterSheetData& Data)
{
    FLogContext Context(TEXT("PointBuyOrchestrator"), TEXT("ProcessPointBuy"));

    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
        return FPointBuyResult(false, false, TMap<FName, int32>(), 0, TEXT("Erro: Referências inválidas"));
    }

    // 1. Converte dados (Converter)
    TMap<FName, int32> PointBuyMap = FPointBuyConverter::ConvertFromData(Data);

    // 2. Valida (Validator)
    FPointBuyValidationResult ValidationResult = FPointBuyValidator::ValidatePointBuy(
        Data.PointBuyStrength, Data.PointBuyDexterity, Data.PointBuyConstitution, Data.PointBuyIntelligence,
        Data.PointBuyWisdom, Data.PointBuyCharisma);

    const int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS;
    int32 PointsRemaining = ValidationResult.PointsRemaining;
    bool bWasAutoAdjusted = false;

    // 3. Ajusta se necessário (Adjuster)
    if (PointsRemaining < 0)
    {
        FString AdjustMessage = PointBuyHelpers::AdjustPointBuyAllocation(PointBuyMap, MaxPoints);
        bWasAutoAdjusted = true;

        // Recalcula após ajuste
        PointsRemaining = PointBuyHelpers::CalculatePointsRemaining(PointBuyMap, MaxPoints);

        // Logging (responsabilidade do orquestrador)
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("Alocação ajustada automaticamente. %s"), *AdjustMessage), false);
    }

    // 4. Aplica (Motor puro)
    FPointBuyMotor::ApplyPointBuy(PointBuyMap, *Data.FinalStrength, *Data.FinalDexterity, *Data.FinalConstitution,
                                   *Data.FinalIntelligence, *Data.FinalWisdom, *Data.FinalCharisma);

    // 5. Formata feedback (Formatter)
    FPointBuyApplicationResult ApplicationResult(true, bWasAutoAdjusted, PointsRemaining, PointBuyMap);
    FString FeedbackMessage = FPointBuyFormatter::FormatFeedback(ApplicationResult, MaxPoints);

    // Retorna resultado com feedback
    return FPointBuyResult(true, bWasAutoAdjusted, PointBuyMap, PointsRemaining, FeedbackMessage);
}

#pragma endregion Point Buy Orchestrator
