// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyFormatter.h"

// Project includes - Data Structures
#include "Data/Structures/FPointBuyApplicationResult.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Formatter
// ============================================================================
#pragma region Point Buy Formatter

FString FPointBuyFormatter::FormatFeedback(const FPointBuyApplicationResult& Result, int32 MaxPoints)
{
    if (Result.PointsRemaining == 0)
    {
        return FString::Printf(TEXT("Todos os pontos foram alocados (%d/%d)"), MaxPoints, MaxPoints);
    }
    else if (Result.bWasAutoAdjusted)
    {
        return FString::Printf(TEXT("Alocação ajustada automaticamente. Pontos restantes: %d"), Result.PointsRemaining);
    }
    else
    {
        return FString::Printf(TEXT("Pontos restantes: %d"), Result.PointsRemaining);
    }
}

#pragma endregion Point Buy Formatter
