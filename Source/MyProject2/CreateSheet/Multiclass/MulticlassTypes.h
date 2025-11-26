// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MulticlassTypes.generated.h"

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
