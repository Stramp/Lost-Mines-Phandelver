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
// Point Buy Result Struct
// ============================================================================
#pragma region Point Buy Result Struct

/**
 * Resultado da aplicação de Point Buy pelo motor.
 * Contém feedback sobre validação e ajustes automáticos realizados.
 */
struct MYPROJECT2_API FPointBuyResult
{
    /** Se o resultado é válido (sem erros críticos) */
    bool bIsValid = true;

    /** Se o motor teve que ajustar a alocação automaticamente (excedeu MAX_POINT_BUY_POINTS) */
    bool bWasAutoAdjusted = false;

    /** Alocação final (pode ser diferente da original se foi ajustada) */
    TMap<FName, int32> FinalAllocation;

    /** Pontos restantes após alocação (pode ser negativo se excedeu) */
    int32 PointsRemaining = 0;

    /** Mensagem de feedback para o caller ajustar a UI */
    FString FeedbackMessage;

    /** Construtor padrão */
    FPointBuyResult() : bIsValid(true), bWasAutoAdjusted(false), PointsRemaining(0) {}

    /** Construtor com valores */
    FPointBuyResult(bool bValid, bool bAdjusted, const TMap<FName, int32> &Allocation, int32 Remaining,
                    const FString &Message)
        : bIsValid(bValid), bWasAutoAdjusted(bAdjusted), FinalAllocation(Allocation), PointsRemaining(Remaining),
          FeedbackMessage(Message)
    {
    }
};

#pragma endregion Point Buy Result Struct
