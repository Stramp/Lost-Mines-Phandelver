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

    /**
     * Protocolo de inicialização de boot (PostLoad).
     * Orquestra ordem fixa de operações usando Template Method Pattern.
     * Responsabilidade única: coordenar inicialização completa do Data Asset.
     *
     * Ordem de execução:
     * 1. Preparar condições (ajustar LevelInClass)
     * 2. Carregar dados (com condições corretas)
     * 3. Validar estado
     * 4. Corrigir se necessário (com Guard Pattern)
     * 5. Recarregar se correção alterou condições críticas
     * 6. Finalizar (atualizar flags)
     *
     * @param Asset Data Asset a inicializar
     */
    static void InitializeBootProtocol(UCharacterSheetDataAsset *Asset);

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
