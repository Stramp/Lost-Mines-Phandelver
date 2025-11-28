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
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

struct FCharacterSheetData;

#pragma endregion Forward Declarations

// ============================================================================
// Point Buy Converter
// ============================================================================
#pragma region Point Buy Converter

/**
 * Conversor de dados para Point Buy.
 * Responsável por converter dados de FCharacterSheetData para TMap<FName, int32>.
 *
 * Função pura: recebe dados, retorna dados convertidos, não modifica nada.
 */
class MYPROJECT2_API FPointBuyConverter
{
public:
    /**
     * Converte dados de FCharacterSheetData para TMap<FName, int32>.
     *
     * @param Data Estrutura genérica com dados de Point Buy
     * @return Map com valores de Point Buy (chave: FName do atributo, valor: pontos de Point Buy)
     */
    static TMap<FName, int32> ConvertFromData(const FCharacterSheetData& Data);
};

#pragma endregion Point Buy Converter
