// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SpellDataTable.generated.h"

// Forward declarations
struct FSpellSchoolDataRow;
struct FDamageTypeDataRow;

// ============================================================================
// Spell Data Row
// ============================================================================
#pragma region Spell Data Row

/**
 * Struct para dados de Spell (magias D&D 5e).
 * Tabela de referência (Master Data) usada por Class, Trait.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSpellDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da magia (ex: "Fireball", "Mage Hand", "Magic Missile") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FName Name;

    /** ID único da magia (ex: "SPL_Fireball", "SPL_MageHand", "SPL_MagicMissile") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FName ID;

    /** Nível da magia (0 = Cantrip, 1-9 = Spell Level) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    int32 SpellLevel;

    /** Referência à escola da magia (ex: Evocation, Abjuration) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FDataTableRowHandle SchoolReference;

    /** Referência ao tipo de dano (se aplicável, ex: Fire, Cold) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FDataTableRowHandle DamageTypeReference;

    /** Descrição da magia (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FText Description;

    /** Gameplay Tags para categorização (ex: Spell.Damage, Spell.Healing, Spell.Buff) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    FGameplayTagContainer TypeTags;

    /** Dados estruturados da magia (Range, Components, Duration, etc.) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
    TMap<FName, FString> SpellData;

    FSpellDataRow()
        : Name(NAME_None)
        , ID(NAME_None)
        , SpellLevel(0)
    {
    }
};

#pragma endregion Spell Data Row
