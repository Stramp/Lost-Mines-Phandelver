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
     * Validates Variant Human choices.
     * Orchestrates validation of ability scores, feat, and skill.
     */
    static void ValidateVariantHumanChoices(UCharacterSheetDataAsset *Asset);

    /**
     * Validates Variant Human ability score choices.
     * Ensures CustomAbilityScoreChoices has exactly 2 valid elements.
     */
    static void ValidateVariantHumanAbilityScoreChoices(UCharacterSheetDataAsset *Asset);

    /**
     * Validates Variant Human selected feat.
     * Ensures SelectedFeat is available and valid.
     */
    static void ValidateVariantHumanFeat(UCharacterSheetDataAsset *Asset);

    /**
     * Validates Variant Human selected skill.
     * Ensures SelectedSkill is valid.
     */
    static void ValidateVariantHumanSkill(UCharacterSheetDataAsset *Asset);

    /**
     * Validates language choices.
     * Ensures SelectedLanguages count doesn't exceed MaxLanguageChoices.
     */
    static void ValidateLanguageChoices(UCharacterSheetDataAsset *Asset);
};
