// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
struct FClassLevelEntry;

/**
 * Funções helper para validação de dados de personagem D&D 5e.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais, exceto modificação de parâmetros de saída)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace ValidationHelpers
{
    // ============================================================================
    // Point Buy Validation
    // ============================================================================

    /**
     * Valida alocação de Point Buy e calcula pontos restantes.
     *
     * @param BaseScores Map com ability scores base (chave: FName do atributo, valor: score)
     * @param PointsRemaining [OUT] Pontos restantes após alocação (pode ser negativo se excedeu)
     * @param MaxPoints Pontos máximos disponíveis (padrão: 27 para D&D 5e)
     * @return true se todos os scores estão no range válido [8, 15], false caso contrário
     */
    bool ValidatePointBuy(const TMap<FName, int32> &BaseScores, int32 &PointsRemaining, int32 MaxPoints = 27);

    /**
     * Valida alocação completa de Point Buy (range + pontos).
     *
     * @param BaseScores Map com ability scores base
     * @param MaxPoints Pontos máximos disponíveis (padrão: 27)
     * @return true se válido (range correto E exatamente MaxPoints gastos), false caso contrário
     */
    bool ValidatePointBuyAllocation(const TMap<FName, int32> &BaseScores, int32 MaxPoints = 27);

    // ============================================================================
    // Level Validation
    // ============================================================================

    /**
     * Calcula nível total e valida se está dentro do range permitido.
     *
     * @param ClassLevels Array com entradas de nível por classe
     * @param TotalLevel [OUT] Nível total calculado
     * @param MaxLevel Nível máximo permitido (padrão: 20 para D&D 5e)
     * @return true se nível total <= MaxLevel, false caso contrário
     */
    bool ValidateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels, int32 &TotalLevel, int32 MaxLevel = 20);

    /**
     * Valida se um nível total está dentro do range permitido.
     *
     * @param Level Nível total a validar
     * @param MaxLevel Nível máximo permitido (padrão: 20)
     * @return true se 1 <= Level <= MaxLevel, false caso contrário
     */
    bool ValidateTotalLevelRange(int32 Level, int32 MaxLevel = 20);

    // ============================================================================
    // Ability Score Validation
    // ============================================================================

    /**
     * Valida se um ability score está dentro do range permitido.
     *
     * @param Score Ability score a validar
     * @param Min Valor mínimo permitido (padrão: 1)
     * @param Max Valor máximo permitido (padrão: 30)
     * @return true se Min <= Score <= Max, false caso contrário
     */
    bool ValidateAbilityScoreRange(int32 Score, int32 Min = 1, int32 Max = 30);

    /**
     * Valida escolhas de ability scores (ex: Variant Human).
     * Remove duplicatas, valida nomes e limita quantidade.
     *
     * @param Choices [IN/OUT] Array de escolhas (será modificado: duplicatas removidas, valores inválidos corrigidos)
     * @param ValidNames Array com nomes válidos de ability scores
     * @param MaxChoices Número máximo de escolhas permitidas (padrão: 2)
     * @return true se válido (1 <= Choices.Num() <= MaxChoices e todos os nomes são válidos), false caso contrário
     */
    bool ValidateAbilityScoreChoices(TArray<FName> &Choices, const TArray<FName> &ValidNames, int32 MaxChoices = 2);

    // ============================================================================
    // Selection Validation
    // ============================================================================

    /**
     * Valida se uma seleção de feat está disponível.
     *
     * @param SelectedFeat [IN/OUT] Feat selecionado (será resetado para NAME_None se inválido)
     * @param AvailableFeats Array com feats disponíveis
     * @return true se SelectedFeat está em AvailableFeats ou é NAME_None, false caso contrário
     */
    bool ValidateFeatSelection(FName &SelectedFeat, const TArray<FName> &AvailableFeats);

    /**
     * Valida se uma seleção de skill é válida.
     *
     * @param SelectedSkill [IN/OUT] Skill selecionado (será resetado para NAME_None se inválido)
     * @param ValidSkills Array com skills válidas
     * @return true se SelectedSkill está em ValidSkills ou é NAME_None, false caso contrário
     */
    bool ValidateSkillSelection(FName &SelectedSkill, const TArray<FName> &ValidSkills);
} // namespace ValidationHelpers
