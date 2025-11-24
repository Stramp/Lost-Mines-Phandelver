// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Validador de Point Buy para criação de personagem.
 * Responsável por validar alocação de Point Buy e calcular pontos restantes.
 */
class MYPROJECT2_API FPointBuyValidator
{
public:
    /**
     * Valida Point Buy system.
     * Calcula pontos gastos e valida ability scores estão dentro do range válido [8, 15].
     *
     * @param Asset Character Sheet Data Asset
     */
    static void ValidatePointBuy(UCharacterSheetDataAsset *Asset);
};
