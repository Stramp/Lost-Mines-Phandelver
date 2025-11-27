// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
struct FRaceDataRow;

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
     * Reseta Final Scores para valor base (8).
     * Função pura que apenas reseta valores.
     *
     * @param FinalStrength [IN/OUT] Score final de Strength
     * @param FinalDexterity [IN/OUT] Score final de Dexterity
     * @param FinalConstitution [IN/OUT] Score final de Constitution
     * @param FinalIntelligence [IN/OUT] Score final de Intelligence
     * @param FinalWisdom [IN/OUT] Score final de Wisdom
     * @param FinalCharisma [IN/OUT] Score final de Charisma
     */
    void ResetFinalScoresToBase(int32 &FinalStrength, int32 &FinalDexterity, int32 &FinalConstitution,
                                int32 &FinalIntelligence, int32 &FinalWisdom, int32 &FinalCharisma);

    /**
     * Incrementa Final Scores com alocação de Point Buy.
     * Motor independente: apenas incrementa, não reseta, não conhece bônus racial.
     *
     * @param PointBuyAllocation Map com alocação de Point Buy (chave: FName do atributo, valor: 0-7)
     * @param FinalStrength [IN/OUT] Score final de Strength
     * @param FinalDexterity [IN/OUT] Score final de Dexterity
     * @param FinalConstitution [IN/OUT] Score final de Constitution
     * @param FinalIntelligence [IN/OUT] Score final de Intelligence
     * @param FinalWisdom [IN/OUT] Score final de Wisdom
     * @param FinalCharisma [IN/OUT] Score final de Charisma
     */
    void IncrementFinalScoresWithPointBuy(const TMap<FName, int32> &PointBuyAllocation, int32 &FinalStrength,
                                          int32 &FinalDexterity, int32 &FinalConstitution, int32 &FinalIntelligence,
                                          int32 &FinalWisdom, int32 &FinalCharisma);

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

    /**
     * Calcula proficiências do personagem (background + Variant Human skill).
     * Nota: Sem classes, proficiências vêm apenas de background e Variant Human.
     *
     * @param RaceName Nome da raça selecionada (para Variant Human)
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param BackgroundName Nome do background selecionado
     * @param SelectedSkill Skill escolhido para Variant Human (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com nomes de proficiências
     */
    TArray<FName> CalculateProficiencies(FName RaceName, FName SubraceName, FName BackgroundName, FName SelectedSkill,
                                         UDataTable *RaceDataTable, UDataTable *BackgroundDataTable);

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

    // ============================================================================
    // Hit Points Calculations
    // ============================================================================

    /**
     * Calcula HP ganho em um nível específico de uma classe.
     * Fórmula D&D 5e:
     * - Level 1: HitDie + CON modifier
     * - Level 2+: (HitDie/2 + 1) + CON modifier (média do dado, arredondado para cima)
     *
     * @param HitDie Dado de vida da classe (6, 8, 10 ou 12)
     * @param Level Nível na classe (1-20)
     * @param ConstitutionModifier Modificador de Constitution
     * @return HP ganho neste nível
     */
    int32 CalculateHPGainForLevel(int32 HitDie, int32 Level, int32 ConstitutionModifier);

    /**
     * Calcula HP total máximo do personagem baseado em todas as classes e seus níveis.
     * Soma HP de cada nível de cada classe.
     * Fórmula: Soma de CalculateHPGainForLevel para cada nível de cada classe.
     *
     * @param ClassNames Array com nomes das classes (ordem deve corresponder a LevelsInClass)
     * @param LevelsInClass Array com níveis em cada classe (ordem deve corresponder a ClassNames)
     * @param ConstitutionModifier Modificador de Constitution (mesmo para todas as classes)
     * @param ClassDataTable Data Table de classes para buscar HitDie (pode ser nullptr)
     * @return HP máximo total do personagem
     */
    int32 CalculateMaxHP(const TArray<FName> &ClassNames, const TArray<int32> &LevelsInClass,
                         int32 ConstitutionModifier, UDataTable *ClassDataTable);
} // namespace CalculationHelpers
