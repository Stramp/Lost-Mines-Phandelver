// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

struct FPointBuyApplicationResult;

#pragma endregion Forward Declarations

// ============================================================================
// Point Buy Formatter
// ============================================================================
#pragma region Point Buy Formatter

/**
 * Formatador de mensagens de feedback para Point Buy.
 * Responsável por construir mensagens de feedback a partir de dados puros.
 *
 * Função pura: recebe dados, retorna string formatada, não modifica nada.
 */
class MYPROJECT2_API FPointBuyFormatter
{
public:
    /**
     * Formata mensagem de feedback baseada no resultado da aplicação de Point Buy.
     *
     * @param Result Resultado da aplicação de Point Buy
     * @param MaxPoints Pontos máximos permitidos
     * @return Mensagem de feedback formatada
     */
    static FString FormatFeedback(const FPointBuyApplicationResult& Result, int32 MaxPoints);
};

#pragma endregion Point Buy Formatter
