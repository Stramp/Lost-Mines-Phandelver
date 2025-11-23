// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class FText;

/**
 * Funções helper para formatação de dados de personagem D&D 5e.
 * Funções puras e reutilizáveis para formatação de strings e logs.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace FormattingHelpers
{
    // ============================================================================
    // String Formatting
    // ============================================================================

    /**
     * Formata display de raça com sub-raça (se houver).
     *
     * @param RaceName Nome da raça
     * @param SubraceName Nome da sub-raça (pode ser NAME_None)
     * @return String formatada (ex: "Elf" ou "Elf (High Elf)")
     */
    FString FormatRaceDisplay(FName RaceName, FName SubraceName);

    /**
     * Formata lista de proficiências como string separada por vírgulas.
     *
     * @param Proficiencies Array de nomes de proficiências
     * @return String formatada (ex: "Athletics, Acrobatics, Stealth")
     */
    FString FormatProficienciesList(const TArray<FName> &Proficiencies);

    /**
     * Formata ability scores para log/display.
     * Retorna string formatada com todos os ability scores em ordem padrão.
     *
     * @param AbilityScores Map com ability scores (chave: FName do atributo, valor: score)
     * @return String formatada com ability scores
     */
    FString FormatAbilityScores(const TMap<FName, int32> &AbilityScores);
} // namespace FormattingHelpers
