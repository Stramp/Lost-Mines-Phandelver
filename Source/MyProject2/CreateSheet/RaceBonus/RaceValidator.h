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

struct FRaceDataRow;

#pragma endregion Forward Declarations

// ============================================================================
// Race Validator
// ============================================================================
#pragma region Race Validator

/**
 * Validador de raça e sub-raça.
 * Responsável por validar se sub-raça pertence à raça selecionada.
 *
 * Função pura: recebe dados, retorna resultado, não modifica nada.
 */
class MYPROJECT2_API FRaceValidator
{
public:
    /**
     * Valida se sub-raça pertence à raça selecionada.
     *
     * @param RaceRow Row da raça (pode ser nullptr)
     * @param SelectedSubrace Nome da sub-raça selecionada
     * @return true se sub-raça é válida, false caso contrário
     */
    static bool ValidateSubrace(const FRaceDataRow* RaceRow, FName SelectedSubrace);
};

#pragma endregion Race Validator
