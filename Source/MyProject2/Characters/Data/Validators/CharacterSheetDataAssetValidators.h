// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Validators for CharacterSheetDataAsset.
 * Handles all validation logic for character sheet data.
 */
class MYPROJECT2_API FCharacterSheetDataAssetValidators
{
public:
    /**
     * Validates Point Buy system.
     * Calculates points spent and validates ability scores are within valid range [8, 15].
     */
    static void ValidatePointBuy(UCharacterSheetDataAsset *Asset);

    /**
     * Validates total level.
     * Ensures total level doesn't exceed 20 and adjusts class levels if necessary.
     */
    static void ValidateTotalLevel(UCharacterSheetDataAsset *Asset);

    /**
     * Validates Variant Human choices.
     * Ensures CustomAbilityScoreChoices has exactly 2 elements,
     * SelectedFeat is available, and SelectedSkill is valid.
     */
    static void ValidateVariantHumanChoices(UCharacterSheetDataAsset *Asset);
};
