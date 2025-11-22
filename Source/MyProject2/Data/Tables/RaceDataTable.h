// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RaceDataTable.generated.h"

/**
 * Struct para armazenar modificadores de Ability Score de raças.
 * Usado para representar bônus de atributos (ex: +2 Strength, +1 Dexterity).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreImprovement
{
	GENERATED_BODY()

	/** Nome do atributo que recebe o bônus (ex: "Strength", "Dexterity", "Constitution") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
	FName AbilityName;

	/** Valor do bônus a ser aplicado ao atributo (geralmente +1 ou +2) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
	int32 Bonus;

	FAbilityScoreImprovement()
		: AbilityName(NAME_None)
		, Bonus(0)
	{
	}

	FAbilityScoreImprovement(const FName& InAbilityName, int32 InBonus)
		: AbilityName(InAbilityName)
		, Bonus(InBonus)
	{
	}
};

/**
 * Struct para armazenar traits de raça.
 * Combina descrição textual (para UI/localização) com dados estruturados (para lógica).
 * Exemplos: Darkvision, Fey Ancestry, Stonecunning.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FRaceTrait
{
	GENERATED_BODY()

	/** Nome do trait (ex: "Darkvision", "Fey Ancestry", "Stonecunning") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FName TraitName;

	/** Descrição textual do trait (localizável, para exibição na UI) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FText Description;

	/**
	 * Dados estruturados opcionais do trait.
	 * Permite armazenar informações programáticas além da descrição.
	 * Exemplo: {"Range": "60", "Type": "Vision"} para Darkvision
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	TMap<FName, FString> TraitData;

	FRaceTrait()
		: TraitName(NAME_None)
		, Description(FText::GetEmpty())
	{
	}

	FRaceTrait(const FName& InTraitName, const FText& InDescription)
		: TraitName(InTraitName)
		, Description(InDescription)
	{
	}
};

/**
 * Struct principal para dados de raça D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para uma raça: atributos, tamanho, velocidade, traits, etc.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FRaceDataRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Nome da raça (ex: "Human", "Elf", "Dwarf", "Halfling") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FName RaceName;

	/** Descrição textual da raça (localizável) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FText Description;

	/** Lista de modificadores de Ability Score que a raça fornece */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FAbilityScoreImprovement> AbilityScoreImprovements;

	/** Tamanho da raça (ex: "Small", "Medium", "Large") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FName Size;

	/** Velocidade base da raça em pés */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	int32 BaseSpeed;

	/** Lista de traits especiais da raça (Darkvision, Fey Ancestry, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FRaceTrait> Traits;

	/** Nomes das sub-raças disponíveis para esta raça (ex: "High Elf", "Wood Elf" para Elf) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FName> SubraceNames;

	/** Idiomas que a raça conhece automaticamente */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FName> Languages;
};
