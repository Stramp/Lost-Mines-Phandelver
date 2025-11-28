// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "ConditionDataTable.generated.h"

// ============================================================================
// Condition Data Row
// ============================================================================
#pragma region Condition Data Row

/**
 * Struct para dados de Condition (condições D&D 5e).
 * Tabela de referência (Master Data) usada por Spell, Trait, Item.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FConditionDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da condição (ex: "Blinded", "Poisoned", "Charmed") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
    FName Name;

    /** ID único da condição (ex: "CON_Blinded", "CON_Poisoned", "CON_Charmed") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
    FName ID;

    /** Descrição da condição (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
    FText Description;

    /** Gameplay Tags para categorização (ex: Condition.Blinded, Condition.Poisoned) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
    FGameplayTagContainer TypeTags;

    FConditionDataRow()
        : Name(NAME_None)
        , ID(NAME_None)
    {
    }
};

#pragma endregion Condition Data Row
