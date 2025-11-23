// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"
#include "../CharacterSheetDataAssetTypes.h"

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
     * Initializes default ability scores (all start at 8).
     * Populates AbilityScores map with all 6 ability scores at base value 8.
     */
    static void InitializeDefaultAbilityScores(TMap<FName, FAbilityScoreEntry> &AbilityScores);

    /**
     * Resets Variant Human choices when race changes.
     * Clears CustomAbilityScoreChoices, SelectedFeat, and SelectedSkill.
     */
    static void ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset);
};
