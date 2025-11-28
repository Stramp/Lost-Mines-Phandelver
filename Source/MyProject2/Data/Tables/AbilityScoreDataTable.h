// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "AbilityScoreDataTable.generated.h"

// ============================================================================
// Ability Score Data Row
// ============================================================================
#pragma region Ability Score Data Row

/**
 * Struct para dados de Ability Score (atributos D&D 5e).
 * Tabela de referência (Master Data) usada por todas as outras tabelas.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do atributo (ex: "Strength", "Dexterity") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
    FName Name;

    /** ID único do atributo (ex: "ABL_Strength", "ABL_Dexterity") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
    FName ID;

    /** Abreviação do atributo (ex: "STR", "DEX") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
    FName Abbreviation;

    /** Descrição do atributo (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
    FText Description;

    /** Gameplay Tags para categorização (ex: Ability.Physical, Ability.Mental) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Score")
    FGameplayTagContainer TypeTags;

    FAbilityScoreDataRow()
        : Name(NAME_None), ID(NAME_None), Abbreviation(NAME_None)
    {
    }
};

#pragma endregion Ability Score Data Row
