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

    /** Lista de skills disponíveis para escolha - Preenchido automaticamente pelo motor */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<FName> available;

    /** Quantidade de skills que podem ser escolhidos - Calculado dinamicamente */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
    int32 qtdAvailable;

    /** Tamanho inicial de available quando proficiências foram carregadas - Usado para calcular qtdAvailable */
    UPROPERTY(meta = (Hidden))
    int32 InitialAvailableCount = 0;

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
    UPROPERTY(BlueprintReadOnly, Category = "Feature")
    FName FC_ID;

    /** Descrição da feature */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Feature")
    FText Description;

    /** Nível em que a feature é desbloqueada */
    UPROPERTY(BlueprintReadOnly, Category = "Feature")
    int32 LevelUnlocked = 1;

    /** Tipo da feature: "Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection" */
    UPROPERTY(BlueprintReadOnly, Category = "Feature")
    FName FeatureType;

    /** Dados adicionais da feature (chave-valor) */
    UPROPERTY(BlueprintReadOnly, Category = "Feature")
    TMap<FName, FString> FeatureData;

    /** Escolha selecionada (dropdown que lista os nomes das escolhas disponíveis) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature", meta = (GetOptions = "GetAvailableChoiceNames"))
    FName AvailableChoices;

    FMulticlassClassFeature() : LevelUnlocked(1), AvailableChoices(NAME_None) {}
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
