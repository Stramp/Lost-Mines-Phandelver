// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Containers/Map.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Application Result Struct
// ============================================================================
#pragma region Point Buy Application Result Struct

/**
 * Resultado da aplicação de Point Buy pelo motor puro.
 * Contém apenas dados puros, sem mensagens formatadas.
 */
struct MYPROJECT2_API FPointBuyApplicationResult
{
    /** Se a aplicação foi bem-sucedida */
    bool bSuccess = true;

    /** Se a alocação foi ajustada automaticamente */
    bool bWasAutoAdjusted = false;

    /** Pontos restantes após alocação */
    int32 PointsRemaining = 0;

    /** Alocação aplicada */
    TMap<FName, int32> AppliedAllocation;

    /** Construtor padrão */
    FPointBuyApplicationResult()
        : bSuccess(true), bWasAutoAdjusted(false), PointsRemaining(0)
    {
    }

    /** Construtor com valores */
    FPointBuyApplicationResult(bool bInSuccess, bool bInWasAutoAdjusted, int32 InPointsRemaining,
                                const TMap<FName, int32>& InAppliedAllocation)
        : bSuccess(bInSuccess), bWasAutoAdjusted(bInWasAutoAdjusted), PointsRemaining(InPointsRemaining),
          AppliedAllocation(InAppliedAllocation)
    {
    }
};

#pragma endregion Point Buy Application Result Struct
