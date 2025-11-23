// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
struct FRaceDataRow;
struct FClassLevelEntry;
struct FClassFeature;

/**
 * Funções helper para cálculos de dados de personagem D&D 5e.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais, exceto modificação de parâmetros de saída)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace CalculationHelpers
{
    // ============================================================================
    // Ability Score Calculations
    // ============================================================================

    /**
     * Calcula o modificador de ability score (Ability Modifier).
     * Fórmula D&D 5e: floor((Score - 10) / 2)
     *
     * @param Score Ability score (1-30)
     * @return Modificador calculado (pode ser negativo)
     */
    int32 CalculateAbilityModifier(int32 Score);

    /**
     * Calcula o score final de ability score.
     *
     * @param BaseScore Score base (do Point Buy)
     * @param RacialBonus Bônus racial aplicado
     * @param ASIBonus Bônus de Ability Score Improvement (padrão: 0)
     * @return Score final (BaseScore + RacialBonus + ASIBonus)
     */
    int32 CalculateFinalAbilityScore(int32 BaseScore, int32 RacialBonus, int32 ASIBonus = 0);

    /**
     * Calcula bônus raciais de ability scores.
     * Função pura que calcula bônus sem modificar Asset.
     *
     * @param RaceRow Row da raça base (pode ser nullptr)
     * @param SubraceRow Row da sub-raça (pode ser nullptr)
     * @param CustomChoices Array com escolhas customizadas (ex: Variant Human)
     * @param RacialBonuses [OUT] Map com bônus calculados (chave: FName do atributo, valor: bônus)
     */
    void CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
                                const TArray<FName> &CustomChoices, TMap<FName, int32> &RacialBonuses);

    // ============================================================================
    // Proficiency Calculations
    // ============================================================================

    /**
     * Calcula o bônus de proficiência baseado no nível total.
     * Fórmula D&D 5e: 1 + floor((TotalLevel - 1) / 4)
     *
     * @param TotalLevel Nível total do personagem (1-20)
     * @return Bônus de proficiência
     */
    int32 CalculateProficiencyBonus(int32 TotalLevel);

    // ============================================================================
    // Feature Calculations
    // ============================================================================

    /**
     * Calcula features disponíveis baseado em níveis de classes.
     *
     * @param ClassLevels Array com entradas de nível por classe
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com nomes de features disponíveis
     */
    TArray<FName> CalculateAvailableFeatures(const TArray<FClassLevelEntry> &ClassLevels, UDataTable *ClassDataTable);

    /**
     * Calcula proficiências do personagem (raça + classe + background + Variant Human skill).
     *
     * @param RaceName Nome da raça selecionada
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param ClassLevels Array com entradas de nível por classe
     * @param BackgroundName Nome do background selecionado
     * @param SelectedSkill Skill escolhido para Variant Human (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com nomes de proficiências
     */
    TArray<FName> CalculateProficiencies(FName RaceName, FName SubraceName, const TArray<FClassLevelEntry> &ClassLevels,
                                         FName BackgroundName, FName SelectedSkill, UDataTable *RaceDataTable,
                                         UDataTable *ClassDataTable, UDataTable *BackgroundDataTable);

    // ============================================================================
    // Language Calculations
    // ============================================================================

    /**
     * Calcula idiomas finais do personagem (raça + background + escolhas do jogador + feats).
     *
     * @param RaceName Nome da raça selecionada
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param BackgroundName Nome do background selecionado
     * @param SelectedLanguages Array com idiomas escolhidos pelo jogador (quando há escolhas)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com nomes de idiomas que o personagem fala
     */
    TArray<FName> CalculateLanguages(FName RaceName, FName SubraceName, FName BackgroundName,
                                     const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                     UDataTable *BackgroundDataTable);
} // namespace CalculationHelpers
