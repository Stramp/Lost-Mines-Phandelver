// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProficiencyDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Proficiency Data Struct
// ============================================================================
#pragma region Proficiency Data Struct

/**
 * Struct principal para dados de proficiências D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para uma proficiência: nome, ID, tipo e descrição.
 *
 * Tipos de proficiências suportadas:
 * - "Weapon": Proficiências com armas (ex: Simple Weapons, Martial Weapons)
 * - "Armor": Proficiências com armaduras (ex: Light Armor, Medium Armor, Heavy Armor)
 * - "Shield": Proficiências com escudos
 * - "Tool": Proficiências com ferramentas (ex: Thieves' Tools, Herbalism Kit)
 * - "Skill": Proficiências com skills (ex: Acrobatics, Athletics)
 * - "SavingThrow": Proficiências com saving throws (ex: Strength, Dexterity)
 * - "Language": Proficiências com idiomas (ex: Common, Elvish)
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProficiencyDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da proficiência (ex: "Simple Weapons", "Thieves' Tools", "Acrobatics") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
    FName Name;

    /** ID único da proficiência (ex: "PW_Simple_Weapons", "PT_Thieves_Tools", "PSK_Acrobatics") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
    FName ProficiencyID;

    /**
     * Tipo da proficiência.
     * Valores possíveis: "Weapon", "Armor", "Shield", "Tool", "Skill", "SavingThrow", "Language"
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
    FName Type;

    /** Descrição textual da proficiência (localizável, para exibição na UI) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
    FText Description;

    /**
     * Dados estruturados opcionais da proficiência.
     * Permite armazenar informações programáticas além da descrição.
     *
     * Exemplos de uso:
     * - Weapons: {"Damage": "1d4", "DamageType": "Bludgeoning", "Properties": "Light,Finesse"}
     * - Armor: {"AC": "15", "MaxDexBonus": "2", "StealthDisadvantage": "true"}
     * - Tools: {"UsesPerRest": "1", "ActionType": "Action"}
     * - Skills: {"AbilityModifier": "DEX"} (para skills que usam modificador específico)
     *
     * Vazio para proficiências passivas (Languages, SavingThrows básicos).
     * Preparado para migração futura para GAS (Gameplay Ability System).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
    TMap<FName, FString> ProficiencyData;

    FProficiencyDataRow()
        : Name(NAME_None)
        , ProficiencyID(NAME_None)
        , Type(NAME_None)
        , Description(FText::GetEmpty())
        , ProficiencyData()  // Inicializa vazio (backward compatible)
    {
    }

    FProficiencyDataRow(const FName& InName, const FName& InProficiencyID, const FName& InType,
                        const FText& InDescription)
        : Name(InName)
        , ProficiencyID(InProficiencyID)
        , Type(InType)
        , Description(InDescription)
        , ProficiencyData()  // Inicializa vazio (backward compatible)
    {
    }
};

#pragma endregion Proficiency Data Struct
