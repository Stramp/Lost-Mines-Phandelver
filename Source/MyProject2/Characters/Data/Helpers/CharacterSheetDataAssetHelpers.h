// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

// Forward declarations
class UCharacterSheetDataAsset;

/**
 * Helpers for CharacterSheetDataAsset.
 * Utility functions for resetting and managing character sheet data.
 */
class MYPROJECT2_API FCharacterSheetDataAssetHelpers
{
public:
    /**
     * Resets Variant Human choices when race changes.
     * Clears CustomAbilityScoreChoices, SelectedFeat, and SelectedSkill.
     */
    static void ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset);
};
