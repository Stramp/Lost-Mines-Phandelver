// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BackgroundDataTable.generated.h"

/**
 * Struct para representar escolhas de idiomas.
 * Usado quando background/raça/feat permite escolher idiomas (ex: "One language of your choice").
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FLanguageChoices
{
    GENERATED_BODY()

    /** Quantidade de idiomas que podem ser escolhidos (1, 2, 3, etc.) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language Choices")
    int32 Count = 0;

    FLanguageChoices() : Count(0) {}

    FLanguageChoices(int32 InCount) : Count(InCount) {}
};

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

    /** Idiomas automáticos que o background fornece (nomes reais de idiomas) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    TArray<FName> Languages;

    /** Escolhas de idiomas que o background permite (ex: "One language of your choice" = Count: 1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FLanguageChoices LanguageChoices;

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
