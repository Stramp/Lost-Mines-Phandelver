// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Updaters for CharacterSheetDataAsset.
 * Responsabilidade única: ATUALIZAR campos calculados e flags.
 * NÃO valida, NÃO carrega dados, apenas ATUALIZA.
 */
class MYPROJECT2_API FCharacterSheetDataAssetUpdaters
{
public:
    // ============================================================================
    // Flag Updates
    // ============================================================================

    /**
     * Atualiza flag Variant Human e notifica editor se mudou.
     * Reseta Variant Human choices se no longer Variant Human.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateVariantHumanFlag(UCharacterSheetDataAsset *Asset);

    /**
     * Atualiza flag de sub-raças disponíveis (bHasSubraces).
     * Detecta se a raça selecionada tem sub-raças disponíveis.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateSubraceFlag(UCharacterSheetDataAsset *Asset);

    /**
     * Atualiza visibilidade da ficha baseado na seleção de Data Tables.
     * Mostra todas as categorias quando todos os Data Tables são selecionados.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateSheetVisibility(UCharacterSheetDataAsset *Asset);

    /**
     * Atualiza detecção de escolhas de idiomas (bHasLanguageChoices, MaxLanguageChoices).
     * Detecta se race/background/feat permite language choices.
     * NOTA: Não remove itens do array - isso é responsabilidade de Validators/CorrectionApplier.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateLanguageChoices(UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Calculated Values Update
    // ============================================================================

    /**
     * Recalcula scores finais usando Core genérico (aplica todos os motores).
     * Atualiza PointsRemaining e ajusta alocação se necessário.
     *
     * @param Asset Asset do personagem
     */
    static void RecalculateFinalScores(UCharacterSheetDataAsset *Asset);

    /**
     * Aplica resultado da validação do Point Buy no Asset.
     * Atualiza PointsRemaining com o valor calculado pela validação.
     *
     * @param Asset Asset do personagem
     * @param PointsRemaining Pontos restantes calculados pela validação
     */
    static void ApplyPointBuyValidationResult(UCharacterSheetDataAsset *Asset, int32 PointsRemaining);

    /**
     * Recalcula HP máximo do personagem baseado em todas as classes e seus níveis.
     * Usa HitDie de cada classe e Constitution modifier.
     * Atualiza MaxHealth e CurrentHealth (se CurrentHealth > MaxHealth, ajusta para MaxHealth).
     *
     * @param Asset Asset do personagem
     */
    static void RecalculateMaxHP(UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Multiclass Flags Update
    // ============================================================================

    /**
     * Atualiza flags bCanEditProgression e bCanEditProficiencies para todas as entradas de multiclasse.
     * Apenas atualiza flags, não carrega nem valida dados.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateMulticlassFlags(UCharacterSheetDataAsset *Asset);

    /**
     * Atualiza qtdAvailable dinamicamente quando skills são escolhidas/removidas do available.
     * Apenas atualiza, não valida nem carrega dados.
     *
     * @param Asset Asset do personagem
     */
    static void UpdateMulticlassProficiencyChoices(UCharacterSheetDataAsset *Asset);

    /**
     * Ajusta LevelInClass baseado na presença de ClassName.
     * Se ClassName != NAME_None, LevelInClass = 1. Caso contrário, LevelInClass = 0.
     * Apenas atualiza, não valida nem carrega dados.
     *
     * @param Asset Asset do personagem
     */
    static void AdjustLevelInClassForClassName(UCharacterSheetDataAsset *Asset);

    /**
     * Ajusta nível mínimo para classes válidas (sem tag de requerimento).
     * Se tem classe válida e LevelInClass == 0, ajusta para 1.
     * Apenas atualiza, não valida nem carrega dados.
     *
     * @param Asset Asset do personagem
     */
    static void AdjustMinimumLevelForValidClasses(UCharacterSheetDataAsset *Asset);
};
