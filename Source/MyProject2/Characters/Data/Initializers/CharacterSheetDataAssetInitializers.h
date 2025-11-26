// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UCharacterSheetDataAsset;

/**
 * Initializers para CharacterSheetDataAsset.
 * Responsável por inicializar o map de handlers de propriedades.
 * Segue padrão de organização modular do CharacterSheetDataAsset.
 */
class MYPROJECT2_API FCharacterSheetDataAssetInitializers
{
public:
    /**
     * Inicializa todos os handlers de propriedades no map.
     * Coordena chamadas para funções específicas por categoria.
     *
     * @param Asset Asset do personagem
     */
    static void InitializeAllPropertyHandlers(UCharacterSheetDataAsset *Asset);

private:
    // Funções auxiliares por categoria (privadas, chamadas apenas por InitializeAllPropertyHandlers)
    static void InitializeRaceHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializePointBuyHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializeBackgroundHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializeVariantHumanHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializeLanguageHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializeDataTableHandlers(UCharacterSheetDataAsset *Asset);
    static void InitializeMulticlassHandlers(UCharacterSheetDataAsset *Asset);
};
