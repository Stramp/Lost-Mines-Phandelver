// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ClassDataTable.generated.h"

USTRUCT(BlueprintType)
struct MYPROJECT2_API FSkills
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<FName> available;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 qtdAvailable;
};

/**
 * Struct para armazenar proficiências de classe seguindo a estrutura do DJ_Class.json.
 * Cada elemento do array FProficiencies contém um objeto com armas, armaduras, savingThrows ou FSkills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProficienciesEntry
{
    GENERATED_BODY()

    /** Lista de armas (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> armas;

    /** Lista de armaduras (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> armaduras;

    /** Lista de saving throws (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> savingThrows;

    /** Informações de skills (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    FSkills FSkills;

    FProficienciesEntry() {}
};

/**
 * Struct para armazenar uma entrada de progressão por nível.
 * Segue a estrutura do DJ_Class.json.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProgressEntry
{
    GENERATED_BODY()

    /** Nível da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    int32 Level = 1;

    /** Lista de features desbloqueadas neste nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TArray<FName> Features;

    FProgressEntry() : Level(1) {}
};

/**
 * Struct principal para dados de classe seguindo a estrutura do DJ_Class.json.
 * Renomeado de FClass para FClassData para evitar conflito com UClass do engine.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassData
{
    GENERATED_BODY()

    /** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName Name;

    /** Nível máximo da classe (padrão: 20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 Level = 20;

    /** Proficiências da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FProficienciesEntry> FProficiencies;

    /** Progressão de features por nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FProgressEntry> FProgress;

    FClassData() : Name(NAME_None), Level(20) {}
};

/**
 * Struct principal para dados de classe D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Agora segue a estrutura do DJ_Class.json.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Estrutura principal da classe seguindo DJ_Class.json */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FClassData FClass;
};
