// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FeatureDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Feature Choice Struct
// ============================================================================
#pragma region Feature Choice Struct

/**
 * Struct para armazenar uma escolha disponível em uma feature do tipo "Choice" ou "SubclassSelection".
 * Usado dentro de FFeatureDataRow para definir opções que o jogador pode escolher.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FFeatureChoice
{
    GENERATED_BODY()

    /** ID único da escolha (ex: "FC_Archery", "FC_Champion") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature Choice")
    FName ID;

    /** Nome da escolha exibido ao jogador (ex: "Archery", "Champion") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature Choice")
    FName Name;

    FFeatureChoice() : ID(NAME_None), Name(NAME_None) {}

    FFeatureChoice(const FName& InID, const FName& InName) : ID(InID), Name(InName) {}
};

#pragma endregion Feature Choice Struct

// ============================================================================
// Feature Data Struct
// ============================================================================
#pragma region Feature Data Struct

/**
 * Struct principal para dados de features de classe D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para uma feature: nome, descrição, tipo, nível e escolhas.
 *
 * Tipos de features suportadas:
 * - "Automatic": Feature aplicada automaticamente (ex: Second Wind, Action Surge)
 * - "Choice": Jogador escolhe entre opções (ex: Fighting Style)
 * - "SubclassSelection": Jogador escolhe subclasse (ex: Martial Archetype)
 * - "ASI": Ability Score Improvement
 * - "FeatSelection": Jogador pode escolher um Feat ao invés de ASI
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FFeatureDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da feature (ex: "Second Wind", "Fighting Style", "Action Surge") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    FName Name;

    /** ID único da feature (ex: "FC_SecondWind", "FC_FightingStyle", "FC_ActionSurge") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    FName FC_ID;

    /** Descrição textual da feature (localizável, para exibição na UI) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    FText Description;

    /** Nível em que a feature é desbloqueada */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    int32 LevelUnlocked = 1;

    /**
     * Tipo da feature: "Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection"
     *
     * Valores possíveis:
     * - "Automatic": Feature aplicada automaticamente (ex: Second Wind, Action Surge)
     * - "Choice": Jogador escolhe entre opções (ex: Fighting Style)
     * - "SubclassSelection": Jogador escolhe subclasse (ex: Martial Archetype)
     * - "ASI": Ability Score Improvement
     * - "FeatSelection": Jogador pode escolher um Feat ao invés de ASI
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    FName FeatureType;

    /**
     * Dados estruturados opcionais da feature.
     * Permite armazenar informações programáticas além da descrição.
     * Exemplo: {"UsesPerRest": "1", "Type": "BonusAction"} para Second Wind
     * Exemplo: {"AttacksAtLevel5": "2", "AttacksAtLevel11": "3"} para Extra Attack
     * Exemplo: {"Source": "FeatDataTable", "AlternativeTo": "FC_ASI"} para FeatSelection
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    TMap<FName, FString> FeatureData;

    /**
     * Escolhas disponíveis para features do tipo "Choice" ou "SubclassSelection".
     * Array vazio para features do tipo "Automatic" ou "ASI".
     * Para "FeatSelection", este array fica vazio (feats vêm do FeatDataTable).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
    TArray<FFeatureChoice> AvailableChoices;

    /**
     * Indica se a feature permite que o jogador escolha múltiplas opções.
     *
     * Comportamento:
     * - false (padrão): Jogador escolhe apenas 1 opção (ex: Fighting Style, Subclass Selection)
     * - true: Jogador pode escolher múltiplas opções (ex: Manobras, Metamagic)
     *
     * Apenas relevante quando FeatureType é "Choice" ou "SubclassSelection" e há escolhas disponíveis.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature",
              meta = (EditCondition = "FeatureType == \"Choice\" || FeatureType == \"SubclassSelection\"",
                      EditConditionHides))
    bool bAllowMultipleChoices = false;

    FFeatureDataRow()
        : Name(NAME_None)
        , FC_ID(NAME_None)
        , Description(FText::GetEmpty())
        , LevelUnlocked(1)
        , FeatureType(NAME_None)
        , bAllowMultipleChoices(false)
    {
    }

    FFeatureDataRow(const FName& InName, const FName& InFC_ID, const FText& InDescription, int32 InLevelUnlocked,
                    const FName& InFeatureType)
        : Name(InName)
        , FC_ID(InFC_ID)
        , Description(InDescription)
        , LevelUnlocked(InLevelUnlocked)
        , FeatureType(InFeatureType)
        , bAllowMultipleChoices(false)
    {
    }
};

#pragma endregion Feature Data Struct
