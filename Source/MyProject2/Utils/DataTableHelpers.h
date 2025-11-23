// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
struct FRaceDataRow;
struct FClassDataRow;
struct FFeatDataRow;

/**
 * Funções helper para busca de rows em Data Tables com fallback manual.
 * Centraliza lógica de busca que pode falhar com FindRow direto.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace DataTableHelpers
{
    // ============================================================================
    // Race Data Table Helpers
    // ============================================================================

    /**
     * Busca row de raça no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param RaceName Nome da raça para buscar
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindRaceRow(FName RaceName, UDataTable *RaceDataTable);

    /**
     * Busca row de sub-raça no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param SubraceName Nome da sub-raça para buscar
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindSubraceRow(FName SubraceName, UDataTable *RaceDataTable);

    // ============================================================================
    // Class Data Table Helpers
    // ============================================================================

    /**
     * Busca row de classe no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param ClassName Nome da classe para buscar
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FClassDataRow *FindClassRow(FName ClassName, UDataTable *ClassDataTable);

    // ============================================================================
    // Feat Data Table Helpers
    // ============================================================================

    /**
     * Busca row de feat no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param FeatName Nome do feat para buscar
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FFeatDataRow *FindFeatRow(FName FeatName, UDataTable *FeatDataTable);
} // namespace DataTableHelpers
