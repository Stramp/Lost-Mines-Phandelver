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
     * Fórmula D&D 5e: floor((Score - ABILITY_MODIFIER_BASE) / ABILITY_MODIFIER_DIVISOR)
     *
     * @param Score Ability score (MIN_ABILITY_SCORE - MAX_ABILITY_SCORE)
     * @return Modificador calculado (pode ser negativo)
     */
    int32 CalculateAbilityModifier(int32 Score);

    /**
     * Reseta Final Scores para valor base (BASE_ABILITY_SCORE).
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
     * Fórmula D&D 5e: PROFICIENCY_BONUS_BASE + floor((TotalLevel - MIN_LEVEL) / PROFICIENCY_BONUS_DIVISOR)
     *
     * @param TotalLevel Nível total do personagem (MIN_LEVEL - MAX_LEVEL)
     * @return Bônus de proficiência
     */
    int32 CalculateProficiencyBonus(int32 TotalLevel);

    /**
     * Coleta proficiências de skills de Background.
     * Background fornece proficiências automáticas via SkillProficiencyHandles.
     *
     * @param BackgroundName Nome do background selecionado (pode ser NAME_None)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com IDs de proficiências de skills do background (sem duplicatas)
     */
    TArray<FName> CollectProficienciesFromBackground(FName BackgroundName, UDataTable *BackgroundDataTable);

    /**
     * Coleta proficiências de skills de Background e Variant Human.
     * Função orquestradora que combina proficiências de Background e adiciona skill do Variant Human.
     *
     * @param RaceName Nome da raça selecionada (não usado atualmente, mas mantido para compatibilidade futura)
     * @param SubraceName Nome da sub-raça selecionada (deve ser "Variant Human" para adicionar skill)
     * @param BackgroundName Nome do background selecionado
     * @param SelectedSkill Skill escolhido pelo Variant Human (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (não usado atualmente)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com IDs de proficiências de skills (sem duplicatas)
     */
    TArray<FName> CollectProficienciesFromBackgroundAndVariantHuman(FName RaceName, FName SubraceName,
                                                                    FName BackgroundName, FName SelectedSkill,
                                                                    UDataTable *RaceDataTable,
                                                                    UDataTable *BackgroundDataTable);

    // ============================================================================
    // Language Calculations
    // ============================================================================

    /**
     * Coleta idiomas automáticos da raça base.
     *
     * @param RaceName Nome da raça selecionada (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Array com IDs de idiomas automáticos da raça
     */
    TArray<FName> CollectLanguagesFromRace(FName RaceName, UDataTable *RaceDataTable);

    /**
     * Coleta idiomas automáticos da sub-raça.
     *
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Array com IDs de idiomas automáticos da sub-raça
     */
    TArray<FName> CollectLanguagesFromSubrace(FName SubraceName, UDataTable *RaceDataTable);

    /**
     * Coleta idiomas automáticos do background.
     *
     * @param BackgroundName Nome do background selecionado (pode ser NAME_None)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com IDs de idiomas automáticos do background
     */
    TArray<FName> CollectLanguagesFromBackground(FName BackgroundName, UDataTable *BackgroundDataTable);

    /**
     * Coleta idiomas de todas as fontes (raça + sub-raça + background + escolhas do jogador).
     * Função orquestradora que combina idiomas de múltiplas fontes.
     *
     * @param RaceName Nome da raça selecionada
     * @param SubraceName Nome da sub-raça selecionada (pode ser NAME_None)
     * @param BackgroundName Nome do background selecionado
     * @param SelectedLanguages Array com idiomas escolhidos pelo jogador (quando há escolhas)
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Array com nomes de idiomas coletados de todas as fontes (sem duplicatas)
     */
    TArray<FName> CollectLanguagesFromAllSources(FName RaceName, FName SubraceName, FName BackgroundName,
                                                 const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                 UDataTable *BackgroundDataTable);

    // ============================================================================
    // Hit Points Calculations
    // ============================================================================

    /**
     * Calcula HP ganho em um nível específico de uma classe.
     * Fórmula D&D 5e:
     * - Level MIN_LEVEL: HitDie + CON modifier
     * - Level 2+: ceil(HitDie/HP_AVERAGE_DIVISOR) + CON modifier (média do dado, arredondado para cima)
     *
     * @param HitDie Dado de vida da classe (MIN_HIT_DIE - MAX_HIT_DIE)
     * @param Level Nível na classe (MIN_LEVEL - MAX_LEVEL)
     * @param ConstitutionModifier Modificador de Constitution
     * @return HP ganho neste nível
     */
    int32 CalculateHPGainForLevel(int32 HitDie, int32 Level, int32 ConstitutionModifier);

    /**
     * Calcula HP total máximo do personagem baseado em todas as classes e seus níveis.
     * Soma HP de cada nível de cada classe.
     * Fórmula: Soma de CalculateHPGainForLevel para cada nível de cada classe.
     *
     * @param ClassIDs Array com IDs das classes (ordem deve corresponder a LevelsInClass)
     *                 Ex: ["CLASS_Fighter", "CLASS_Wizard"]
     * @param LevelsInClass Array com níveis em cada classe (ordem deve corresponder a ClassIDs)
     * @param ConstitutionModifier Modificador de Constitution (mesmo para todas as classes)
     * @param ClassDataTable Data Table de classes para buscar HitDie (pode ser nullptr)
     * @return HP máximo total do personagem
     */
    int32 CalculateMaxHP(const TArray<FName> &ClassIDs, const TArray<int32> &LevelsInClass, int32 ConstitutionModifier,
                         UDataTable *ClassDataTable);

    // ============================================================================
    // Armor Class (AC) Calculations
    // ============================================================================

    /**
     * Calcula Armor Class (AC) baseado em DEX modifier e armadura.
     * Fórmula D&D 5e:
     * - Sem armadura: 10 + DEX modifier
     * - Light Armor: ACValue + DEX modifier (sem limite)
     * - Medium Armor: ACValue + min(DEX modifier, +2)
     * - Heavy Armor: ACValue (sem DEX modifier)
     * - Shield: +2 AC (adiciona ao AC calculado)
     *
     * @param DexterityModifier Modificador de Dexterity
     * @param ArmorACValue AC base da armadura (0 se sem armadura)
     * @param ArmorType Tipo de armadura: "Light", "Medium", "Heavy", "Shield", ou NAME_None (sem armadura)
     * @param bHasShield Se personagem está usando escudo (adiciona +2 AC)
     * @return AC calculado
     */
    int32 CalculateAC(int32 DexterityModifier, int32 ArmorACValue = 0, FName ArmorType = NAME_None,
                      bool bHasShield = false);
} // namespace CalculationHelpers
