// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "CreateSheet/Multiclass/FClassProficiencyData.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

class UDataTable;
struct FClassDataRow;

#pragma endregion Forward Declarations

// ============================================================================
// Multiclass Proficiency Resolver
// ============================================================================
#pragma region Multiclass Proficiency Resolver

/**
 * Resolvedor de handles de proficiências para nomes/IDs.
 * Responsável por resolver handles de proficiências para dados utilizáveis.
 *
 * Função pura: recebe dados, retorna dados resolvidos, não modifica nada.
 */
class MYPROJECT2_API FMulticlassProficiencyResolver
{
public:
    /**
     * Resolve handles de proficiências para dados utilizáveis.
     *
     * @param ClassRow Row da classe (pode ser nullptr)
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Dados de proficiência já resolvidos
     */
    static FClassProficiencyData Resolve(const FClassDataRow* ClassRow, const UDataTable* ProficiencyDataTable);
};

#pragma endregion Multiclass Proficiency Resolver
