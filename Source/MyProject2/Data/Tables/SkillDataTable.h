// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillDataTable.generated.h"

// Forward declaration
struct FAbilityScoreDataRow;

// ============================================================================
// Skill Data Row
// ============================================================================
#pragma region Skill Data Row

/**
 * Struct para dados de Skill (habilidades D&D 5e).
 * Tabela de referência (Master Data) usada por Class, Background.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSkillDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome da skill (ex: "Acrobatics", "Athletics", "Stealth") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName Name;

    /** ID único da skill (ex: "PSK_Acrobatics", "PSK_Athletics", "PSK_Stealth") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName ID;

    /** ID do Ability Score associado (ex: "ABL_Dexterity", "ABL_Strength") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName AbilityID;

    /** Descrição da skill (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FText Description;

    /** Gameplay Tags para categorização (ex: Skill.Physical, Skill.Social, Skill.Knowledge) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FGameplayTagContainer TypeTags;

    FSkillDataRow()
        : Name(NAME_None)
        , ID(NAME_None)
        , AbilityID(NAME_None)
    {
    }
};

#pragma endregion Skill Data Row
