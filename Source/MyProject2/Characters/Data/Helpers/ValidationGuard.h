// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#if WITH_EDITOR

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * RAII Guard para gerenciar automaticamente bIsValidatingProperties.
 * Garante que a flag seja resetada mesmo em caso de exceção ou early return.
 *
 * Uso:
 * {
 *     FValidationGuard Guard(Asset);
 *     // ... código que pode fazer early return ou lançar exceção ...
 * } // Guard automaticamente reseta bIsValidatingProperties no destrutor
 *
 * Nota: Só disponível no editor (WITH_EDITOR), pois bIsValidatingProperties só existe no editor.
 */
class MYPROJECT2_API FValidationGuard
{
public:
    /**
     * Construtor: seta bIsValidatingProperties = true.
     *
     * @param Asset Data Asset para gerenciar a flag
     */
    explicit FValidationGuard(UCharacterSheetDataAsset *Asset);

    /**
     * Destrutor: reseta bIsValidatingProperties = false.
     * Garante que a flag seja sempre resetada, mesmo em caso de exceção.
     */
    ~FValidationGuard();

    // Não permite cópia ou movimentação (evita problemas com múltiplos guards)
    FValidationGuard(const FValidationGuard &) = delete;
    FValidationGuard &operator=(const FValidationGuard &) = delete;
    FValidationGuard(FValidationGuard &&) = delete;
    FValidationGuard &operator=(FValidationGuard &&) = delete;

private:
    /** Ponteiro para o Asset (não possui, apenas referencia) */
    UCharacterSheetDataAsset *Asset;
};

#endif // WITH_EDITOR
