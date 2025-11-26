// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSheetDataAssetValidationResult.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Validators for CharacterSheetDataAsset.
 * Responsabilidade única: VALIDAR e retornar correções necessárias.
 * NÃO aplica correções diretamente - isso é responsabilidade do CorrectionApplier.
 */
class MYPROJECT2_API FCharacterSheetDataAssetValidators
{
public:
    // ============================================================================
    // Boot Protocol - Complete Validation
    // ============================================================================

    /**
     * Protocolo de validação completo para boot (PostLoad).
     * Valida todas as áreas e retorna todas as correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com todas as correções necessárias
     */
    static FValidationResult ValidateAll(UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Variant Human Validation
    // ============================================================================

    /**
     * Valida todas as escolhas de Variant Human.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateVariantHumanChoices(const UCharacterSheetDataAsset *Asset);

    /**
     * Valida escolhas de ability scores para Variant Human.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateVariantHumanAbilityScoreChoices(const UCharacterSheetDataAsset *Asset);

    /**
     * Valida seleção de feat para Variant Human.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateVariantHumanFeat(const UCharacterSheetDataAsset *Asset);

    /**
     * Valida seleção de skill para Variant Human.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateVariantHumanSkill(const UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Language Choices Validation
    // ============================================================================

    /**
     * Valida escolhas de idiomas.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateLanguageChoices(const UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Multiclass Validation
    // ============================================================================

    /**
     * Valida consistência entre Name e LevelInClass em entradas de multiclasse.
     * Regra: Se Name == NAME_None, LevelInClass deve ser 0.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateMulticlassNameLevelConsistency(const UCharacterSheetDataAsset *Asset);

    /**
     * Valida array Progression em entradas de multiclasse.
     * Regra: Progression deve estar vazio se Name == NAME_None ou LevelInClass == 0.
     * Retorna correções necessárias.
     *
     * @param Asset Data Asset a validar
     * @return Resultado com correções necessárias
     */
    static FValidationResult ValidateMulticlassProgression(const UCharacterSheetDataAsset *Asset);
};
