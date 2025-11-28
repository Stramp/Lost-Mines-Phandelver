// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/GameplayTagHelpers.h"
#include "GameplayTagsManager.h"

#pragma endregion Includes

// ============================================================================
// GameplayTagHelpers Implementation
// ============================================================================
#pragma region GameplayTagHelpers Implementation

bool GameplayTagHelpers::HasTag(const FGameplayTagContainer& Container, const FGameplayTag& Tag)
{
    if (!Tag.IsValid())
    {
        return false;
    }
    return Container.HasTag(Tag);
}

bool GameplayTagHelpers::HasAnyTagInGroup(const FGameplayTagContainer& Container, const FGameplayTag& TagGroup)
{
    if (!TagGroup.IsValid())
    {
        return false;
    }
    // Verifica se container tem alguma tag que começa com o grupo (ex: Race.*)
    // Itera sobre todas as tags do container e verifica se alguma começa com o grupo
    for (const FGameplayTag& Tag : Container)
    {
        if (Tag.MatchesTag(TagGroup))
        {
            return true;
        }
    }
    return false;
}

FGameplayTag GameplayTagHelpers::NameToTag(const FName& TagName)
{
    if (TagName == NAME_None)
    {
        return FGameplayTag();
    }
    return FGameplayTag::RequestGameplayTag(TagName);
}

FName GameplayTagHelpers::TagToName(const FGameplayTag& Tag)
{
    if (!Tag.IsValid())
    {
        return NAME_None;
    }
    return Tag.GetTagName();
}

#pragma endregion GameplayTagHelpers Implementation
