// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Data/Structures/FProficienciesEntry.h"
#include "Data/Structures/FProgressEntry.h"
#include "ClassDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Class Data Struct
// ============================================================================
#pragma region Class Data Struct

/**
 * Struct principal para dados de classe seguindo a estrutura do ClassDataTable.json.
 * Renomeado de FClass para FClassData para evitar conflito com UClass do engine.
 * Contém todas as informações de uma classe D&D 5e.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassData
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (GetOptions = "GetListClassAvaible"))
    FName Name;

    /**
     * Dado de vida da classe (Hit Die).
     * Valores possíveis: 6 (Wizard, Sorcerer), 8 (Bard, Cleric, etc), 10 (Fighter, Paladin, Ranger), 12 (Barbarian).
     * Usado para calcular HP máximo do personagem.
     * Campo somente leitura: definido no JSON, não editável no editor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Class", meta = (Hidden))
    int32 HitDie = 6;

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

    /** Equipamentos iniciais da classe (FNames de itens) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FName> StartingEquipment;

    /** Ouro inicial alternativo (se jogador escolher ouro ao invés de equipamentos) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 StartingGold = 0;

    FClassData() : Name(NAME_None), StartingGold(0) {}
};

#pragma endregion Class Data Struct

// ============================================================================
// Data Table Row Struct
// ============================================================================
#pragma region Data Table Row Struct

/**
 * Struct principal para dados de classe D&D 5e usada em UDataTable.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Agora segue a estrutura do ClassDataTable.json.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassDataRow : public FTableRowBase
{
    // Falso positivo do lint: GENERATED_BODY() é uma macro do Unreal que expande durante compilação
    GENERATED_BODY()

    /** Nome da classe (ex: "Class_Fighter", "Class_Wizard", "Class_Cleric") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName Name;

    /** ID único da classe (ex: "CLASS_Fighter", "CLASS_Wizard", "CLASS_Cleric") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName ID;

    /** Gameplay Tags para categorização (ex: Class.Fighter, Class.Martial, Class.Spellcaster) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FGameplayTagContainer TypeTags;

    /** Estrutura principal da classe seguindo ClassDataTable.json */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FClassData FClass;

    FClassDataRow()
        : Name(NAME_None), ID(NAME_None)
    {
    }
};

#pragma endregion Data Table Row Struct
