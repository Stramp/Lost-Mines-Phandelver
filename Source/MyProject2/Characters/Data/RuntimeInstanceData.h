// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RuntimeInstanceData.generated.h"

#pragma endregion Includes

// ============================================================================
// Character Instance Data
// ============================================================================
#pragma region Character Instance Data

/**
 * Estrutura leve para dados de instância em runtime.
 *
 * Princípio: Serialização Diferencial (Baldur's Gate 3)
 * - Não salva definições completas (vêm de Data Tables)
 * - Salva apenas estado mutável (HP atual, escolhas do jogador)
 * - Apenas IDs de referência, não dados completos
 *
 * Uso: Save Games, Serialização de Estado
 *
 * Benefícios:
 * - Save games menores (apenas delta)
 * - Carregamento mais rápido
 * - Alinhado com planos5.md (serialização diferencial)
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FCharacterInstanceData
{
    GENERATED_BODY()

    // ============================================================================
    // Reference IDs (Definition Data vem de Data Tables)
    // ============================================================================

    /** ID da raça selecionada (referência para RaceDataTable) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    FName RaceID;

    /** ID da sub-raça selecionada (referência para RaceDataTable) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    FName SubraceID;

    /** ID da classe selecionada (referência para ClassDataTable) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    FName ClassID;

    /** ID do background selecionado (referência para BackgroundDataTable) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    FName BackgroundID;

    // ============================================================================
    // Mutable State (Runtime Data)
    // ============================================================================

    /** HP atual (não MaxHP que vem da definição) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    float CurrentHealth = 0.0f;

    /** Nível atual (não toda a progressão) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    int32 CurrentLevel = 1;

    /** Escolhas do jogador: Skills selecionados (não todos disponíveis) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TArray<FName> SelectedSkillIDs;

    /** Escolhas do jogador: Features ativas (não todas disponíveis) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TArray<FName> ActiveFeatureIDs;

    /** Escolhas do jogador: Feats selecionados */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TArray<FName> SelectedFeatIDs;

    /** Escolhas do jogador: Idiomas escolhidos (além dos automáticos) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TArray<FName> ChosenLanguageIDs;

    /** Variant Human: Escolhas customizadas de ability scores */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TArray<FName> CustomAbilityScoreChoices;

    /** Ability Scores finais (runtime state) */
    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Instance Data")
    TMap<FName, int32> FinalAbilityScores;

    FCharacterInstanceData()
        : RaceID(NAME_None)
        , SubraceID(NAME_None)
        , ClassID(NAME_None)
        , BackgroundID(NAME_None)
        , CurrentHealth(0.0f)
        , CurrentLevel(1)
    {
    }
};

#pragma endregion Character Instance Data
