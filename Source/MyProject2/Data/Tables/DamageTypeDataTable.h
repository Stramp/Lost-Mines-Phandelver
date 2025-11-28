// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "DamageTypeDataTable.generated.h"

// ============================================================================
// Damage Type Data Row
// ============================================================================
#pragma region Damage Type Data Row

/**
 * Struct para dados de Damage Type (tipos de dano D&D 5e).
 * Tabela de referência (Master Data) usada por Spell, Trait, Item.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FDamageTypeDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do tipo de dano (ex: "Fire", "Cold", "Lightning") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Type")
    FName Name;

    /** ID único do tipo de dano (ex: "DAM_Fire", "DAM_Cold", "DAM_Lightning") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Type")
    FName ID;

    /** Descrição do tipo de dano (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Type")
    FText Description;

    /** Gameplay Tags para categorização (ex: DamageType.Fire, DamageType.Cold) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Type")
    FGameplayTagContainer TypeTags;

    FDamageTypeDataRow()
        : Name(NAME_None)
        , ID(NAME_None)
    {
    }
};

#pragma endregion Damage Type Data Row
