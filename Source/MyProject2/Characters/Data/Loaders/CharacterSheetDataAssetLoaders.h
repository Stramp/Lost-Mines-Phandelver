// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UCharacterSheetDataAsset;
class UDataTable;
struct FMulticlassProgressEntry;
struct FMulticlassProficienciesEntry;

/**
 * Loaders for CharacterSheetDataAsset.
 * Responsabilidade única: CARREGAR dados de Data Tables para o Data Asset.
 * NÃO valida, NÃO atualiza, apenas CARREGA.
 */
class MYPROJECT2_API FCharacterSheetDataAssetLoaders
{
public:
    // ============================================================================
    // Multiclass Data Loading
    // ============================================================================

    /**
     * Carrega informações básicas da classe (MulticlassRequirements) do Data Table.
     * Apenas carrega, não valida nem atualiza.
     *
     * @param Asset Data Asset do personagem
     * @param EntryIndex Índice da entrada no array Multiclass
     * @return true se carregou com sucesso, false caso contrário
     */
    static bool LoadClassBasicInfo(UCharacterSheetDataAsset *Asset, int32 EntryIndex);

    /**
     * Carrega proficiências da classe do Data Table.
     * Apenas carrega, não valida nem atualiza.
     *
     * @param Asset Data Asset do personagem
     * @param EntryIndex Índice da entrada no array Multiclass
     * @return true se carregou com sucesso, false caso contrário
     */
    static bool LoadClassProficiencies(UCharacterSheetDataAsset *Asset, int32 EntryIndex);

    /**
     * Carrega progressão da classe do Data Table.
     * Apenas carrega, não valida nem atualiza.
     *
     * @param Asset Data Asset do personagem
     * @param EntryIndex Índice da entrada no array Multiclass
     * @return true se carregou com sucesso, false caso contrário
     */
    static bool LoadClassProgression(UCharacterSheetDataAsset *Asset, int32 EntryIndex);

    /**
     * Loga features ganhas em um nível específico de uma classe.
     * Apenas loga informações, não carrega nem processa dados.
     *
     * @param Asset Data Asset do personagem
     * @param EntryIndex Índice da entrada no array Multiclass
     */
    static void LogLevelChangeFeatures(UCharacterSheetDataAsset *Asset, int32 EntryIndex);

    /**
     * Carrega todos os dados de multiclasse para todas as entradas.
     * Usado na inicialização (PostLoad) para garantir que dados estejam carregados quando asset é aberto.
     * Apenas carrega, não valida nem atualiza.
     *
     * @param Asset Data Asset do personagem
     */
    static void LoadAllMulticlassData(UCharacterSheetDataAsset *Asset);

    /**
     * Recarrega dados de multiclasse se correções críticas foram aplicadas.
     * Usado após ApplyCorrections quando LevelInClass foi alterado.
     * Apenas recarrega, não valida nem atualiza.
     *
     * @param Asset Data Asset do personagem
     * @param bLevelInClassWasAdjusted Se LevelInClass foi ajustado pelas correções
     */
    static void ReloadMulticlassDataIfNeeded(UCharacterSheetDataAsset *Asset, bool bLevelInClassWasAdjusted);
};
