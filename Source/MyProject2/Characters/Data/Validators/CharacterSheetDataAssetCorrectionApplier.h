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
};
