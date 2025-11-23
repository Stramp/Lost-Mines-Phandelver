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
     * Initializes default ability scores.
     * Populates AbilityScores map with all 6 ability scores at specified base value.
     *
     * @param AbilityScores Map to populate with ability scores
     * @param DefaultValue Base value for all ability scores (padrão: 8)
     */
    static void InitializeDefaultAbilityScores(TMap<FName, FAbilityScoreEntry> &AbilityScores, int32 DefaultValue = 8);

    /**
     * Resets Variant Human choices when race changes.
     * Clears CustomAbilityScoreChoices, SelectedFeat, and SelectedSkill.
     */
    static void ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset);
};
