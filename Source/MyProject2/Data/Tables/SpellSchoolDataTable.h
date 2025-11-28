// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SpellSchoolDataTable.generated.h"

// ============================================================================
// Spell School Data Row
// ============================================================================
#pragma region Spell School Data Row

/**
 * Struct para dados de Spell School (escolas de magia D&D 5e).
 * Tabela de referência (Master Data) usada por Spell.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSpellSchoolDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da escola (ex: "Abjuration", "Evocation", "Necromancy") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell School")
    FName Name;

    /** ID único da escola (ex: "SCH_Abjuration", "SCH_Evocation", "SCH_Necromancy") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell School")
    FName ID;

    /** Descrição da escola (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell School")
    FText Description;

    /** Gameplay Tags para categorização (ex: SpellSchool.Abjuration, SpellSchool.Evocation) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell School")
    FGameplayTagContainer TypeTags;

    FSpellSchoolDataRow()
        : Name(NAME_None)
        , ID(NAME_None)
    {
    }
};

#pragma endregion Spell School Data Row
