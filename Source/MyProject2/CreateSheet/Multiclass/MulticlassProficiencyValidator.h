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

class UDataTable;

#pragma endregion Forward Declarations

// ============================================================================
// Multiclass Proficiency Validator
// ============================================================================
#pragma region Multiclass Proficiency Validator

/**
 * Validador de proficiências de multiclasse.
 * Responsável por validar parâmetros de entrada para carregamento de proficiências.
 *
 * Função pura: recebe dados, retorna resultado, não modifica nada.
 */
class MYPROJECT2_API FMulticlassProficiencyValidator
{
public:
    /**
     * Valida parâmetros de entrada para carregamento de proficiências.
     * Proficiências são ganhas apenas no nível 1.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (deve ser 1)
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    static bool ValidateInputs(FName ClassName, int32 LevelInClass, const UDataTable* ClassDataTable);
};

#pragma endregion Multiclass Proficiency Validator
