// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ClassDataTable.generated.h"

/**
 * Struct para armazenar proficiências de classe.
 * Usado para armas, armaduras, saving throws e skills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassProficiency
{
	GENERATED_BODY()

	/** Tipo de proficiência (ex: "Weapon", "Armor", "SavingThrow", "Skill") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
	FName ProficiencyType;

	/** Nome da proficiência específica (ex: "Longsword", "Light Armor", "Strength", "Athletics") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiency")
	FName ProficiencyName;

	FClassProficiency()
		: ProficiencyType(NAME_None)
		, ProficiencyName(NAME_None)
	{
	}

	FClassProficiency(const FName& InProficiencyType, const FName& InProficiencyName)
		: ProficiencyType(InProficiencyType)
		, ProficiencyName(InProficiencyName)
	{
	}
};

/**
 * Struct para armazenar features de classe.
 * Combina descrição textual com dados estruturados para lógica programática.
 * Exemplos: Second Wind, Action Surge, Spellcasting.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassFeature
{
	GENERATED_BODY()

	/** Nome da feature (ex: "Second Wind", "Action Surge", "Spellcasting") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
	FName FeatureName;

	/** Descrição textual da feature (localizável, para exibição na UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
	FText Description;

	/** Nível em que a feature é desbloqueada */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
	int32 LevelUnlocked;

	/**
	 * Dados estruturados opcionais da feature.
	 * Permite armazenar informações programáticas além da descrição.
	 * Exemplo: {"UsesPerRest": "1", "Type": "BonusAction"} para Second Wind
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feature")
	TMap<FName, FString> FeatureData;

	FClassFeature()
		: FeatureName(NAME_None)
		, Description(FText::GetEmpty())
		, LevelUnlocked(1)
	{
	}

	FClassFeature(const FName& InFeatureName, const FText& InDescription, int32 InLevelUnlocked)
		: FeatureName(InFeatureName)
		, Description(InDescription)
		, LevelUnlocked(InLevelUnlocked)
	{
	}
};

/**
 * Struct para armazenar informações de spellcasting de uma classe.
 * Usado para classes que possuem spellcasting (Wizard, Cleric, etc.).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSpellcastingInfo
{
	GENERATED_BODY()

	/** Se a classe possui spellcasting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
	bool bHasSpellcasting;

	/** Nome do atributo usado para spellcasting (ex: "Intelligence", "Wisdom", "Charisma") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting", meta = (EditCondition = "bHasSpellcasting"))
	FName SpellcastingAbility;

	/**
	 * Número de spell slots por nível.
	 * Array indexado por nível (índice 0 = nível 1, índice 1 = nível 2, etc.).
	 * Cada elemento representa quantos spell slots daquele nível a classe ganha.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting", meta = (EditCondition = "bHasSpellcasting"))
	TArray<int32> SpellSlotsPerLevel;

	FSpellcastingInfo()
		: bHasSpellcasting(false)
		, SpellcastingAbility(NAME_None)
	{
	}
};

/**
 * Struct principal para dados de classe D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para uma classe: hit die, proficiências, equipamento, spellcasting, features.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassDataRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	FName ClassName;

	/** Descrição textual da classe (localizável) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	FText Description;

	/** Dado de vida da classe (4, 6, 8, 10 ou 12) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	int32 HitDie;

	/** Proficiências com armas */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FClassProficiency> WeaponProficiencies;

	/** Proficiências com armaduras */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FClassProficiency> ArmorProficiencies;

	/** Proficiências em saving throws */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FClassProficiency> SavingThrowProficiencies;

	/** Proficiências em skills (o jogador escolhe algumas delas) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FClassProficiency> SkillProficiencies;

	/** Equipamento inicial da classe (FNames de itens) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FName> StartingEquipment;

	/** Informações de spellcasting (se a classe possui spellcasting) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	FSpellcastingInfo SpellcastingInfo;

	/** Features da classe por nível */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
	TArray<FClassFeature> Features;
};
