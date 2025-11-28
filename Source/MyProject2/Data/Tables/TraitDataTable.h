// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "TraitDataTable.generated.h"

// ============================================================================
// Trait Data Row
// ============================================================================
#pragma region Trait Data Row

/**
 * Struct para dados de Trait (traços especiais de raças, classes, etc.).
 * Tabela de referência (Master Data) usada por Race, Class, Background.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FTraitDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** ID único do trait (ex: "TR_Darkvision", "TR_FeyAncestry") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    FName TraitID;

    /** Nome do trait (ex: "Darkvision", "Fey Ancestry") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    FText TraitName;

    /** Descrição textual do trait (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    FText Description;

    /** Dados estruturados do trait (regras específicas, ex: Range para Darkvision) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    TMap<FName, FString> TraitData;

    /** Gameplay Tags para categorização (ex: Trait.Vision.Darkvision, Trait.Racial.FeyAncestry) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    FGameplayTagContainer TypeTags;

    /** Referência a uma magia, se este trait concede uma (ex: Cantrip para High Elf) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
    FDataTableRowHandle SpellReference;

    FTraitDataRow()
        : TraitID(NAME_None)
    {
    }
};

#pragma endregion Trait Data Row
