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

    /** ID único da skill (ex: "PSK_Acrobatics", "PSK_Athletics") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FName SkillID;

    /** Nome da skill (ex: "Acrobatics", "Athletics") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
    FText SkillName;

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
        : SkillID(NAME_None), AbilityID(NAME_None)
    {
    }
};

#pragma endregion Skill Data Row
