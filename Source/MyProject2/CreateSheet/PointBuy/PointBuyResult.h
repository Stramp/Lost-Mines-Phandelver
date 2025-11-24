// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"

/**
 * Resultado da aplicação de Point Buy pelo motor.
 * Contém feedback sobre validação e ajustes automáticos realizados.
 */
struct MYPROJECT2_API FPointBuyResult
{
    /** Se o motor teve que ajustar a alocação (excedeu 27 pontos) */
    bool bWasAdjusted = false;

    /** Alocação ajustada (pode ser diferente da original se foi ajustada) */
    TMap<FName, int32> AdjustedAllocation;

    /** Pontos restantes após alocação (pode ser negativo se excedeu) */
    int32 PointsRemaining = 0;

    /** Mensagem de feedback para o caller ajustar a UI */
    FString FeedbackMessage;

    /** Construtor padrão */
    FPointBuyResult() : bWasAdjusted(false), PointsRemaining(0) {}

    /** Construtor com valores */
    FPointBuyResult(bool bAdjusted, const TMap<FName, int32> &Allocation, int32 Remaining, const FString &Message)
        : bWasAdjusted(bAdjusted), AdjustedAllocation(Allocation), PointsRemaining(Remaining), FeedbackMessage(Message)
    {
    }
};
