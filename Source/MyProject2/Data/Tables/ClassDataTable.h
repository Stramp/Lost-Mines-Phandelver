// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ClassDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Skills Struct
// ============================================================================
#pragma region Skills Struct

/**
 * Struct para armazenar informações de skills disponíveis.
 * Usado dentro de FProficienciesEntry para definir escolhas de skills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSkills
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Lista de skills disponíveis para escolha */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<FName> available;

    /** Quantidade de skills que podem ser escolhidos */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 qtdAvailable;
};

#pragma endregion Skills Struct

// ============================================================================
// Proficiencies Struct
// ============================================================================
#pragma region Proficiencies Struct

/**
 * Struct para armazenar proficiências de classe seguindo a estrutura do DJ_Class.json.
 * Cada elemento do array FProficiencies contém um objeto com armas, armaduras, savingThrows ou FSkills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProficienciesEntry
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
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

#pragma endregion Proficiencies Struct

// ============================================================================
// Progress Struct
// ============================================================================
#pragma region Progress Struct

/**
 * Struct para armazenar uma entrada de progressão por nível.
 * Segue a estrutura do DJ_Class.json.
 * Define quais features são desbloqueadas em cada nível da classe.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProgressEntry
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Nível da classe (calculado automaticamente, não editável) */
    UPROPERTY(BlueprintReadOnly, Category = "Progress")
    int32 Level = 1;

    /** Lista de features desbloqueadas neste nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TArray<FName> Features;

    FProgressEntry() : Level(1) {}
};

#pragma endregion Progress Struct

// ============================================================================
// Class Data Struct
// ============================================================================
#pragma region Class Data Struct

/**
 * Struct principal para dados de classe seguindo a estrutura do DJ_Class.json.
 * Renomeado de FClass para FClassData para evitar conflito com UClass do engine.
 * Contém todas as informações de uma classe D&D 5e.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassData
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Class",
		meta = (GetOptions = "GetListClassAvaible") )
    FName Name;

    /**
     * Requisitos de atributo para multiclasse nesta classe.
     * Formato: ["STR/13", "DEX/13"] para AND, ou ["STR/13|DEX/13"] para OR.
     * Exemplos:
     * - Fighter: ["STR/13|DEX/13"] (STR 13 OU DEX 13)
     * - Monk: ["DEX/13", "WIS/13"] (DEX 13 E WIS 13)
     * - Wizard: ["INT/13"] (INT 13)
     *
     * Campo somente leitura: definido no JSON, não editável no editor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Class", meta = (Hidden))
    TArray<FString> MulticlassRequirements;

    /** Proficiências da classe (armas, armaduras, saving throws, skills) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FProficienciesEntry> Proficiencies;

    /** Progressão de features por nível (do nível 1 ao 20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FProgressEntry> Progression;

    FClassData() : Name(NAME_None) {}
};

#pragma endregion Class Data Struct

// ============================================================================
// Data Table Row Struct
// ============================================================================
#pragma region Data Table Row Struct

/**
 * Struct principal para dados de classe D&D 5e usada em UDataTable.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Agora segue a estrutura do DJ_Class.json.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassDataRow : public FTableRowBase
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Estrutura principal da classe seguindo DJ_Class.json */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FClassData FClass;
};

#pragma endregion Data Table Row Struct
