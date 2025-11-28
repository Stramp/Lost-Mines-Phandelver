// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
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
 * Contém todas as informações necessárias para um background: proficiências, idiomas, equipamento, trait.
 *
 * Estrutura atualizada para usar FDataTableRowHandle e Gameplay Tags.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FBackgroundDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do background (ex: "Acolyte", "Criminal", "Folk Hero", "Noble") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FName Name;

    /** ID único do background (ex: "BG_Acolyte", "BG_Criminal", "BG_FolkHero") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FName ID;

    /** Descrição textual do background (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FText Description;

    /** Gameplay Tags para categorização (ex: Background.Acolyte) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FGameplayTagContainer TypeTags;

    /** Lista de handles para proficiências em skills que o background fornece */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    TArray<FDataTableRowHandle> SkillProficiencyHandles;

    /** Lista de handles para idiomas automáticos que o background fornece */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    TArray<FDataTableRowHandle> LanguageHandles;

    /** Escolhas de idiomas que o background permite (ex: "One language of your choice" = Count: 1) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FLanguageChoices LanguageChoices;

    /** Equipamento inicial do background (FNames de itens) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    TArray<FName> Equipment;

    /** Handle para o trait especial do background (ex: "Shelter of the Faithful", "Criminal Contact") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FDataTableRowHandle TraitHandle;

    /** Descrição textual do trait do background (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
    FText TraitDescription;

    FBackgroundDataRow() : Name(NAME_None), ID(NAME_None) {}
};
