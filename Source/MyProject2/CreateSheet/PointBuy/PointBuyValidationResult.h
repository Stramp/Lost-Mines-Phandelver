// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Resultado da validação de Point Buy.
 * Validador puro: recebe dados, retorna resultado, não modifica nada.
 */
struct MYPROJECT2_API FPointBuyValidationResult
{
    /** Pontos restantes após validação (pode ser negativo se excedeu 27 pontos) */
    int32 PointsRemaining = 0;

    /** Se todos os scores estão dentro do range válido [8, 15] */
    bool bAllScoresValid = true;

    /** Se a alocação está correta (PointsRemaining == 0 e bAllScoresValid == true) */
    bool bIsValid = true;

    /** Mensagem de log (se houver problema) */
    FString LogMessage;

    FPointBuyValidationResult() : PointsRemaining(0), bAllScoresValid(true), bIsValid(true) {}

    FPointBuyValidationResult(int32 InPointsRemaining, bool bInAllScoresValid, bool bInIsValid,
                              const FString &InLogMessage = TEXT(""))
        : PointsRemaining(InPointsRemaining), bAllScoresValid(bInAllScoresValid), bIsValid(bInIsValid),
          LogMessage(InLogMessage)
    {
    }
};
