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
struct FRaceDataRow;
struct FCharacterSheetData;

#pragma endregion Forward Declarations

// ============================================================================
// Race Data Loader
// ============================================================================
#pragma region Race Data Loader

/**
 * Carregador de dados de raça.
 * Responsável por buscar dados de raça e sub-raça do Data Table.
 *
 * Função pura: recebe dados, retorna dados carregados, não modifica nada.
 */
class MYPROJECT2_API FRaceDataLoader
{
public:
    /**
     * Estrutura para armazenar dados de raça carregados.
     */
    struct FRaceData
    {
        FRaceDataRow* RaceRow = nullptr;
        FRaceDataRow* SubraceRow = nullptr;
    };

    /**
     * Carrega dados de raça e sub-raça do Data Table.
     *
     * @param Data Estrutura genérica com dados de raça
     * @return Dados de raça carregados (RaceRow e SubraceRow)
     */
    static FRaceData Load(const FCharacterSheetData& Data);
};

#pragma endregion Race Data Loader
