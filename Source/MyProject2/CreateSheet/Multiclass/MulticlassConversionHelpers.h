// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// Forward declarations
class UDataTable;
struct FProficienciesEntry;
struct FMulticlassProficienciesEntry;
struct FFeatureDataRow;
struct FMulticlassClassFeature;
struct FDataTableRowHandle;

/**
 * Helpers de conversão para multiclasse.
 * Funções auxiliares para converter estruturas de dados e resolver IDs/handles para nomes legíveis.
 */
class MYPROJECT2_API FMulticlassConversionHelpers
{
public:
    /**
     * Resolve array de handles de proficiências para nomes legíveis.
     * Helper puro e testável para resolução de handles de proficiências (estrutura flat).
     *
     * @param ProficiencyHandles Array de handles de proficiências (FDataTableRowHandle[])
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes legíveis (ex: ["Simple Weapons"]) ou IDs originais se não encontrado
     */
    static TArray<FName> ResolveProficiencyHandlesToNames(const TArray<FDataTableRowHandle> &ProficiencyHandles,
                                                          const UDataTable *ProficiencyDataTable);

    /**
     * Resolve array de IDs de proficiências para nomes legíveis (legado - mantido para compatibilidade).
     * Helper puro e testável para resolução de IDs de proficiências.
     *
     * @param ProficiencyIDs Array de IDs de proficiências (ex: ["PW_Simple_Weapons"])
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes legíveis (ex: ["Simple Weapons"]) ou IDs originais se não encontrado
     */
    static TArray<FName> ResolveProficiencyIDsToNames(const TArray<FName> &ProficiencyIDs,
                                                      const UDataTable *ProficiencyDataTable);

    /**
     * Converte FProficienciesEntry (tabela) para FMulticlassProficienciesEntry (Data Asset) retornando nomes legíveis.
     * Resolve IDs de proficiências (ex: "PW_Simple_Weapons") para nomes legíveis (ex: "Simple Weapons").
     * Helper puro e testável para conversão de estruturas de proficiências.
     *
     * @param SourceEntry Entry da tabela
     * @param ProficiencyDataTable Data Table de proficiências para resolver IDs (pode ser nullptr)
     * @return Entry convertida para Data Asset com nomes legíveis
     */
    static FMulticlassProficienciesEntry ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry,
                                                                   const UDataTable *ProficiencyDataTable);

    /**
     * Converte FFeatureDataRow (tabela) para FMulticlassClassFeature (Data Asset).
     * Helper puro e testável para conversão de features.
     *
     * @param FeatureRow Row da feature da tabela
     * @param LevelUnlocked Nível em que a feature é desbloqueada
     * @return Feature convertida para Data Asset
     */
    static FMulticlassClassFeature ConvertFeatureRowToMulticlassFeature(const FFeatureDataRow &FeatureRow,
                                                                        int32 LevelUnlocked);

    /**
     * Constrói string formatada com lista de features.
     * Helper puro e testável para formatação de arrays de features.
     *
     * @param Features Array de nomes de features
     * @return String formatada (ex: "Feature1, Feature2" ou "Nenhum")
     */
    static FString BuildFeaturesString(const TArray<FName> &Features);
};
