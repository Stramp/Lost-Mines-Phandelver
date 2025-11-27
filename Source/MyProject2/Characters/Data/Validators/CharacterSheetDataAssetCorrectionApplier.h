// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSheetDataAssetValidationResult.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Aplicador de correções de validação.
 * Responsabilidade única: aplicar correções retornadas pelos Validators.
 * Separação clara: Validators validam e retornam, Applier aplica.
 */
class MYPROJECT2_API FCharacterSheetDataAssetCorrectionApplier
{
public:
    /**
     * Aplica todas as correções de um resultado de validação.
     * Modifica o Data Asset conforme as correções necessárias.
     *
     * @param Asset Data Asset a ser corrigido
     * @param ValidationResult Resultado da validação com correções
     */
    static void ApplyCorrections(UCharacterSheetDataAsset *Asset, const FValidationResult &ValidationResult);

    // ============================================================================
    // Correction Application Helpers
    // ============================================================================

    /**
     * Aplica correção ResetToNone para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyResetToNone(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);

    /**
     * Aplica correção ClearArray para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyClearArray(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);

    /**
     * Aplica correção AdjustValue para propriedade específica.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada
     */
    static void ApplyAdjustValue(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);

    /**
     * Aplica correção RemoveInvalid para propriedade específica.
     * Remove elementos inválidos de arrays baseado em índices fornecidos.
     * Helper puro e testável para aplicação de correções.
     *
     * @param Asset Asset do personagem
     * @param Correction Correção a ser aplicada (deve conter índices inválidos em ArrayIndex ou NewValue)
     */
    static void ApplyRemoveInvalid(UCharacterSheetDataAsset *Asset, const struct FValidationCorrection &Correction);
};
