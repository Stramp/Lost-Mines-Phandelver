// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPtr.h"
#include "RaceDataTable.generated.h"

// Forward declarations
class UTexture2D;

// ============================================================================
// Ability Score Improvement Struct
// ============================================================================
#pragma region Ability Score Improvement Struct

/**
 * Struct para armazenar modificadores de Ability Score de raças.
 * Usado para representar bônus de atributos (ex: +2 Strength, +1 Dexterity).
 * Agora usa AbilityID ao invés de AbilityName para referência tipada.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreImprovement
{
	GENERATED_BODY()

	/** ID do atributo que recebe o bônus (ex: "ABL_Strength", "ABL_Dexterity", "ABL_Constitution") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
	FName AbilityID;

	/** Valor do bônus a ser aplicado ao atributo (geralmente +1 ou +2) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
	int32 Bonus;

	FAbilityScoreImprovement()
		: AbilityID(NAME_None)
		, Bonus(0)
	{
	}

	FAbilityScoreImprovement(const FName& InAbilityID, int32 InBonus)
		: AbilityID(InAbilityID)
		, Bonus(InBonus)
	{
	}
};

#pragma endregion Ability Score Improvement Struct

// ============================================================================
// Race Data Row Struct
// ============================================================================
#pragma region Race Data Row Struct

/**
 * Struct principal para dados de raça D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para uma raça: atributos, tamanho, velocidade, traits, etc.
 *
 * Estrutura atualizada para usar FDataTableRowHandle e Gameplay Tags.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FRaceDataRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Nome da raça (ex: "Human", "Elf", "Dwarf", "Halfling") - Key Field */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FName Name;

	/** ID único da raça (ex: "RACE_Dwarf", "RACE_Elf", "RACE_Human") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FName ID;

	/** Descrição textual da raça (localizável) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FText Description;

	/** Gameplay Tags para categorização (ex: Race.Dwarf, Race.Elf, Race.Subrace.HighElf) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FGameplayTagContainer TypeTags;

	/** Lista de modificadores de Ability Score que a raça fornece */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FAbilityScoreImprovement> AbilityScoreImprovements;

	/** Tamanho da raça (ex: "Small", "Medium", "Large") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	FName Size;

	/** Velocidade base da raça em pés */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	int32 BaseSpeed;

	/** Lista de handles para traits especiais da raça (Darkvision, Fey Ancestry, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FDataTableRowHandle> TraitHandles;

	/** Lista de handles para sub-raças disponíveis para esta raça (ex: High Elf, Wood Elf para Elf) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FDataTableRowHandle> SubraceHandles;

	/** Lista de handles para idiomas que a raça conhece automaticamente */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TArray<FDataTableRowHandle> LanguageHandles;

	/** Referência suave para o ícone visual da raça */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Race")
	TSoftObjectPtr<UTexture2D> IconTexture;

	FRaceDataRow()
		: Name(NAME_None)
		, ID(NAME_None)
		, Size(NAME_None)
		, BaseSpeed(30)
	{
	}
};

#pragma endregion Race Data Row Struct
