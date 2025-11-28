// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

class UDataTable;

#pragma endregion Forward Declarations

// ============================================================================
// Point Buy Helpers
// ============================================================================
#pragma region Point Buy Helpers

/**
 * Funções helper específicas para Point Buy system.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais, exceto modificação de parâmetros de saída)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace PointBuyHelpers
{
    /**
     * Calcula pontos restantes de uma alocação de Point Buy.
     * Helper puro para evitar duplicação de código.
     *
     * @param PointBuyMap Alocação de Point Buy
     * @param MaxPoints Pontos máximos permitidos (padrão: DnDConstants::MAX_POINT_BUY_POINTS)
     * @return Pontos restantes (pode ser negativo se excedeu)
     */
    int32 CalculatePointsRemaining(const TMap<FName, int32> &PointBuyMap,
                                   int32 MaxPoints = DnDConstants::MAX_POINT_BUY_POINTS);

    /**
     * Ajusta alocação de Point Buy para não exceder pontos máximos.
     * Reduz do final da fila (ordem inversa de GetAbilityScoreNames).
     * Usa GetAbilityScoreNames() para manter Data-Driven (não hardcoded).
     *
     * Algoritmo de redução:
     * 1. Calcula custo total atual
     * 2. Se excede MaxPoints, reduz do final da fila (último ability score primeiro)
     * 3. Continua reduzindo até chegar a MaxPoints ou não conseguir mais reduzir
     *
     * @param PointBuyMap Alocação original (será modificada)
     * @param MaxPoints Pontos máximos permitidos (padrão: DnDConstants::MAX_POINT_BUY_POINTS)
     * @param AbilityScoreDataTable Data Table de ability scores (pode ser nullptr para fallback hardcoded)
     * @return Mensagem de feedback sobre o ajuste
     */
    FString AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints,
                                     UDataTable *AbilityScoreDataTable = nullptr);
} // namespace PointBuyHelpers

#pragma endregion Point Buy Helpers
