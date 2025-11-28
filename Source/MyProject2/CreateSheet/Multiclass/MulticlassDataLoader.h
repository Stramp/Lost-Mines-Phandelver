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
struct FClassDataRow;

#pragma endregion Forward Declarations

// ============================================================================
// Multiclass Data Loader
// ============================================================================
#pragma region Multiclass Data Loader

/**
 * Carregador de dados de classe para multiclasse.
 * Responsável por buscar dados da classe do Data Table.
 *
 * Função pura: recebe dados, retorna dados carregados, não modifica nada.
 */
class MYPROJECT2_API FMulticlassDataLoader
{
public:
    /**
     * Carrega row de classe do Data Table.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Row da classe (pode ser nullptr se não encontrado)
     */
    static const FClassDataRow* LoadClassRow(FName ClassName, const UDataTable* ClassDataTable);
};

#pragma endregion Multiclass Data Loader
