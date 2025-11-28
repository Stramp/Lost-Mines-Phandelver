// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/Tables/FeatureDataTable.h"

#pragma endregion Includes

// ============================================================================
// Feature Choice Helpers
// ============================================================================
#pragma region Feature Choice Helpers

/**
 * Helpers para manipulação de FFeatureChoice (ID ↔ Name).
 * Funções reutilizáveis para converter entre ID (referência da máquina) e Name (exibição UI).
 */
namespace FeatureChoiceHelpers
{
    /**
     * Busca o ID de uma escolha a partir do Name em uma feature específica.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature que contém a escolha
     * @param ChoiceName Nome da escolha a buscar
     * @return ID da escolha se encontrado, NAME_None caso contrário
     */
    FName FindChoiceIDByName(const UDataTable *FeatureDataTable, FName FeatureID, FName ChoiceName);

    /**
     * Busca o Name de uma escolha a partir do ID em uma feature específica.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature que contém a escolha
     * @param ChoiceID ID da escolha a buscar
     * @return Name da escolha se encontrado, NAME_None caso contrário
     */
    FName FindChoiceNameByID(const UDataTable *FeatureDataTable, FName FeatureID, FName ChoiceID);

    /**
     * Retorna array de IDs de escolhas disponíveis filtrados por ID de feature específica.
     * Usado para dropdown que armazena ID (referência da máquina).
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature para filtrar escolhas
     * @return Array com IDs de escolhas apenas da feature especificada
     */
    TArray<FName> GetAvailableChoiceIDsForFeature(const UDataTable *FeatureDataTable, FName FeatureID);

    /**
     * Retorna array de Names de escolhas disponíveis filtrados por ID de feature específica.
     * Usado para exibição na UI (propriedades calculadas).
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature para filtrar escolhas
     * @return Array com Names de escolhas apenas da feature especificada
     */
    TArray<FName> GetAvailableChoiceNamesForFeature(const UDataTable *FeatureDataTable, FName FeatureID);

    /**
     * Converte array de IDs para array de Names.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature que contém as escolhas
     * @param ChoiceIDs Array de IDs a converter
     * @return Array de Names correspondentes aos IDs
     */
    TArray<FName> ConvertChoiceIDsToNames(const UDataTable *FeatureDataTable, FName FeatureID,
                                         const TArray<FName> &ChoiceIDs);

    /**
     * Converte array de Names para array de IDs.
     * Helper puro e testável, sem side effects.
     *
     * @param FeatureDataTable Data Table de features
     * @param FeatureID ID da feature que contém as escolhas
     * @param ChoiceNames Array de Names a converter
     * @return Array de IDs correspondentes aos Names
     */
    TArray<FName> ConvertChoiceNamesToIDs(const UDataTable *FeatureDataTable, FName FeatureID,
                                         const TArray<FName> &ChoiceNames);

    /**
     * Formata ID para exibição (remove prefixo "FC_" se presente).
     * Helper puro e testável, sem side effects.
     *
     * @param ChoiceID ID da escolha (ex: "FC_Archery")
     * @return Nome formatado para exibição (ex: "Archery")
     */
    FString FormatChoiceIDForDisplay(FName ChoiceID);
} // namespace FeatureChoiceHelpers

#pragma endregion Feature Choice Helpers
