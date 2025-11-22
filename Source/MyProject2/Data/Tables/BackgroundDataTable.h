// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BackgroundDataTable.generated.h"

/**
 * Struct principal para dados de background D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para um background: proficiências, idiomas, equipamento, feature.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FBackgroundDataRow : public FTableRowBase
{
	GENERATED_BODY()

	/** Nome do background (ex: "Acolyte", "Criminal", "Folk Hero", "Noble") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FName BackgroundName;

	/** Descrição textual do background (localizável) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FText Description;

	/** Proficiências em skills que o background fornece */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	TArray<FName> SkillProficiencies;

	/** Proficiências em idiomas que o background fornece */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	TArray<FName> LanguageProficiencies;

	/** Equipamento inicial do background (FNames de itens) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	TArray<FName> Equipment;

	/** Nome da feature especial do background (ex: "Shelter of the Faithful", "Criminal Contact") */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FName FeatureName;

	/** Descrição textual da feature do background (localizável) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FText FeatureDescription;
};
