// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "MulticlassTypes.generated.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Skills Struct
// ============================================================================
#pragma region Multiclass Skills Struct

/**
 * Struct para armazenar informações de skills disponíveis em multiclasse.
 * Usado dentro de FMulticlassProficienciesEntry para definir escolhas de skills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassSkills
{
    GENERATED_BODY()

    /** Skill selecionada no dropdown - Editável apenas quando qtdAvailable > 0 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills",
              meta = (GetOptions = "GetAvailableSkills", EditCondition = "qtdAvailable > 0"))
    FName available;

    /** Array de skills escolhidas - Preenchido quando available é selecionado */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<FName> Selected;

    /** Quantidade de skills que ainda podem ser escolhidos - Calculado dinamicamente */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
    int32 qtdAvailable;

    /** Lista inicial de skills disponíveis quando proficiências foram carregadas - Usado para popular dropdown */
    UPROPERTY(meta = (Hidden))
    TArray<FName> InitialAvailable;

    /** Quantidade inicial que pode ser escolhida - Usado para calcular qtdAvailable */
    UPROPERTY(meta = (Hidden))
    int32 InitialQtdAvailable = 0;
};

#pragma endregion Multiclass Skills Struct

// ============================================================================
// Multiclass Proficiencies Struct
// ============================================================================
#pragma region Multiclass Proficiencies Struct

/**
 * Struct para armazenar proficiências de classe em multiclasse seguindo a estrutura do DJ_Class.json.
 * Cada elemento do array contém um objeto com armas, armaduras, savingThrows ou FMulticlassSkills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassProficienciesEntry
{
    GENERATED_BODY()

    /** Lista de armas (pode estar vazia) - Readonly: preenchido automaticamente pelo motor */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Proficiencies")
    TArray<FName> armas;

    /** Lista de armaduras (pode estar vazia) - Readonly: preenchido automaticamente pelo motor */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Proficiencies")
    TArray<FName> armaduras;

    /** Lista de saving throws (pode estar vazia) - Readonly: preenchido automaticamente pelo motor */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Proficiencies")
    TArray<FName> savingThrows;

    /** Informações de skills (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    FMulticlassSkills FSkills;

    FMulticlassProficienciesEntry() {}
};

#pragma endregion Multiclass Proficiencies Struct

// ============================================================================
// Multiclass Class Feature Choice Struct
// ============================================================================
#pragma region Multiclass Class Feature Choice Struct

/**
 * Struct para armazenar uma escolha disponível de feature.
 * Usado dentro de FMulticlassClassFeature para definir escolhas disponíveis.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassClassFeatureChoice
{
    GENERATED_BODY()

    /** ID único da escolha (ex: "FC_Archery", "FC_Champion") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature Choice")
    FName ID;

    /** Nome da escolha (ex: "Archery", "Champion") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature Choice")
    FName Name;

    FMulticlassClassFeatureChoice() {}
};

#pragma endregion Multiclass Class Feature Choice Struct

// ============================================================================
// Multiclass Class Feature Struct
// ============================================================================
#pragma region Multiclass Class Feature Struct

/**
 * Struct para armazenar uma feature de classe em multiclasse.
 * Segue a estrutura do DJ_FeaturesClass.json.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassClassFeature
{
    GENERATED_BODY()

    /** Nome da feature (ex: "Second Wind", "Fighting Style") */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feature")
    FName Name;

    /** ID único da feature (ex: "FC_SecondWind", "FC_FightingStyle") */
    UPROPERTY(BlueprintReadOnly, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices", EditConditionHides))
    FName FC_ID;

    /** Descrição da feature */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feature")
    FText Description;

    /** Nível em que a feature é desbloqueada */
    UPROPERTY(BlueprintReadOnly, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices", EditConditionHides))
    int32 LevelUnlocked = 1;

    /** Tipo da feature: "Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection" */
    UPROPERTY(BlueprintReadOnly, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices", EditConditionHides))
    FName FeatureType;

    /** Dados adicionais da feature (chave-valor) */
    UPROPERTY(BlueprintReadOnly, Category = "Feature",
              meta = (EditCondition = "FeatureData.Num() > 0", EditConditionHides))
    TMap<FName, FString> FeatureData;

    /**
     * Escolha única selecionada pelo jogador (dropdown que lista os IDs das escolhas disponíveis filtradas por FC_ID).
     * Usado para Tipo 2 (Escolha Única): jogador escolhe apenas 1 opção entre várias disponíveis.
     *
     * Comportamento:
     * - Preenchido automaticamente se houver exatamente 1 escolha disponível na tabela (armazena ID)
     * - Deixado como NAME_None se houver múltiplas opções (jogador escolhe no dropdown)
     * - Sempre NAME_None para features automáticas (Tipo 1) ou escolhas múltiplas (Tipo 3)
     *
     * O dropdown é filtrado automaticamente pela função GetAvailableChoiceIDsForFeature usando o FC_ID desta feature.
     * Armazena ID (referência da máquina), não Name. O Name é exibido em AvailableChoicesDisplayName.
     * Visível apenas quando bHasAvailableChoices é true E bIsMultipleChoice é false (Tipo 2).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature",
              meta = (GetOptions = "GetAvailableChoiceIDsForFeature", GetOptionsFunctionParams = "FC_ID",
                      EditCondition = "bHasAvailableChoices && !bIsMultipleChoice", EditConditionHides))
    FName AvailableChoices; // Armazena ID (referência da máquina)

    /**
     * Dropdown para adicionar escolhas ao array SelectedChoices (Tipo 3: Escolhas Múltiplas).
     * Lista escolhas disponíveis filtradas por FC_ID.
     * Usado para features que permitem escolher múltiplas opções (ex: Manobras, Metamagic).
     *
     * Comportamento:
     * - Quando uma escolha é selecionada aqui, ela deve ser adicionada ao array SelectedChoices
     * - Sempre NAME_None para features automáticas (Tipo 1) ou escolha única (Tipo 2)
     *
     * Visível apenas quando bHasAvailableChoices é true E bIsMultipleChoice é true (Tipo 3).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature",
              meta = (GetOptions = "GetAvailableChoiceIDsForFeature", GetOptionsFunctionParams = "FC_ID",
                      EditCondition = "bHasAvailableChoices && bIsMultipleChoice", EditConditionHides))
    FName AvailableChoiceToAdd; // Armazena ID (referência da máquina)

    /**
     * Array de escolhas selecionadas para Tipo 3 (Escolhas Múltiplas).
     * Armazena as escolhas que o jogador selecionou usando AvailableChoiceToAdd.
     * Usado para features que permitem escolher múltiplas opções (ex: Manobras, Metamagic).
     *
     * Visível apenas quando bHasAvailableChoices é true E bIsMultipleChoice é true (Tipo 3).
     * Sempre vazio para features automáticas (Tipo 1) ou escolha única (Tipo 2).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices && bIsMultipleChoice", EditConditionHides))
    TArray<FName> SelectedChoices;

    /**
     * Flag calculada: indica se feature tem escolhas disponíveis para o jogador.
     * true se FeatureType é "Choice" ou "SubclassSelection" E há escolhas na tabela (AvailableChoices.Num() > 0).
     * Usado para controlar visibilidade dos campos AvailableChoices e SelectedChoices no editor.
     */
    UPROPERTY(meta = (Hidden))
    bool bHasAvailableChoices = false;

    /**
     * Flag calculada: indica se feature permite múltiplas escolhas.
     * true se FeatureType é "Choice" ou "SubclassSelection" E bAllowMultipleChoices é true na tabela.
     * Usado para controlar se mostra AvailableChoices (escolha única) ou SelectedChoices (múltiplas escolhas).
     *
     * Tipo 2 (Escolha Única): bIsMultipleChoice = false → mostra AvailableChoices (dropdown)
     * Tipo 3 (Escolhas Múltiplas): bIsMultipleChoice = true → mostra AvailableChoiceToAdd + SelectedChoices (dropdown + array)
     */
    UPROPERTY(meta = (Hidden))
    bool bIsMultipleChoice = false;

#if WITH_EDITORONLY_DATA
    /**
     * Propriedade calculada: exibe o nome da escolha selecionada (baseado no ID armazenado em AvailableChoices).
     * Usado apenas para exibição no editor (UI).
     * Não editável - calculado automaticamente a partir de AvailableChoices (ID).
     */
    UPROPERTY(VisibleAnywhere, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices && !bIsMultipleChoice && AvailableChoices != NAME_None",
                      EditConditionHides))
    FName AvailableChoicesDisplayName; // Nome calculado para exibição

    /**
     * Propriedade calculada: exibe o nome da escolha no dropdown (baseado no ID armazenado em AvailableChoiceToAdd).
     * Usado apenas para exibição no editor (UI).
     * Não editável - calculado automaticamente a partir de AvailableChoiceToAdd (ID).
     */
    UPROPERTY(VisibleAnywhere, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices && bIsMultipleChoice && AvailableChoiceToAdd != NAME_None",
                      EditConditionHides))
    FName AvailableChoiceToAddDisplayName; // Nome calculado para exibição

    /**
     * Propriedade calculada: exibe os nomes das escolhas selecionadas (baseado nos IDs armazenados em SelectedChoices).
     * Usado apenas para exibição no editor (UI).
     * Não editável - calculado automaticamente a partir de SelectedChoices (IDs).
     */
    UPROPERTY(VisibleAnywhere, Category = "Feature",
              meta = (EditCondition = "bHasAvailableChoices && bIsMultipleChoice && SelectedChoices.Num() > 0",
                      EditConditionHides))
    TArray<FName> SelectedChoicesDisplayNames; // Nomes calculados para exibição
#endif

    FMulticlassClassFeature()
        : LevelUnlocked(1)
        , AvailableChoices(NAME_None)
        , AvailableChoiceToAdd(NAME_None)
        , bHasAvailableChoices(false)
        , bIsMultipleChoice(false)
#if WITH_EDITORONLY_DATA
        , AvailableChoicesDisplayName(NAME_None)
        , AvailableChoiceToAddDisplayName(NAME_None)
#endif
    {
    }
};

#pragma endregion Multiclass Class Feature Struct

// ============================================================================
// Multiclass Progress Struct
// ============================================================================
#pragma region Multiclass Progress Struct

/**
 * Struct para armazenar uma entrada de progressão por nível em multiclasse.
 * Segue a estrutura do DJ_Class.json.
 * Define quais features são desbloqueadas em cada nível da classe.
 */
USTRUCT(BlueprintType, meta = (DisplayName = "Nível"))
struct MYPROJECT2_API FMulticlassProgressEntry
{
    GENERATED_BODY()

    /** Nível da classe (calculado automaticamente, não editável) */
    UPROPERTY(BlueprintReadOnly, Category = "Progress")
    int32 Level = 1;

    /** Lista de features desbloqueadas neste nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TArray<FMulticlassClassFeature> Features;

    FMulticlassProgressEntry() : Level(1) {}
};

#pragma endregion Multiclass Progress Struct
