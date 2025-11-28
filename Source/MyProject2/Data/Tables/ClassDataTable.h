// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Data/Structures/FProgressEntry.h"
#include "ClassDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Data Table Row Struct
// ============================================================================
#pragma region Data Table Row Struct

/**
 * Struct principal para dados de classe D&D 5e usada em UDataTable.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Estrutura FLAT (sem aninhamento profundo) seguindo princípios do planos5.md.
 *
 * Migrado de estrutura aninhada (FClass) para estrutura flat para:
 * - Melhor compatibilidade com importador Unreal
 * - Consistência com outros JSONs do projeto
 * - Facilita migração futura para GAS
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassDataRow : public FTableRowBase
{
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

    /** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName ClassName;

    /**
     * Dado de vida da classe (Hit Die).
     * Valores possíveis: 6 (Wizard, Sorcerer), 8 (Bard, Cleric, etc), 10 (Fighter, Paladin, Ranger), 12 (Barbarian).
     * Usado para calcular HP máximo do personagem.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 HitDie = 6;

    /**
     * Requisitos de atributo para multiclasse nesta classe.
     * Formato: ["STR/13", "DEX/13"] para AND, ou ["STR/13|DEX/13"] para OR.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FString> MulticlassRequirements;

    /** Lista de handles para proficiências com armas */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FDataTableRowHandle> WeaponProficiencyHandles;

    /** Lista de handles para proficiências com armaduras */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FDataTableRowHandle> ArmorProficiencyHandles;

    /** Lista de handles para saving throws (Ability Scores) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FDataTableRowHandle> SavingThrowHandles;

    /** Lista de handles para skills disponíveis para escolha */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FDataTableRowHandle> AvailableSkillHandles;

    /** Quantidade de skills que podem ser escolhidos */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 SkillChoiceCount = 0;

    /** Progressão de features por nível (do nível 1 ao 20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FProgressEntry> Progression;

    /** Equipamentos iniciais da classe (FNames de itens) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FName> StartingEquipment;

    /** Ouro inicial alternativo (se jogador escolher ouro ao invés de equipamentos) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 StartingGold = 0;

    FClassDataRow()
        : Name(NAME_None), ID(NAME_None), ClassName(NAME_None), HitDie(6), SkillChoiceCount(0), StartingGold(0)
    {
    }
};

#pragma endregion Data Table Row Struct
