// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Handlers for PostEditChangeProperty events in CharacterSheetDataAsset.
 * Each handler manages the validation and update logic for specific property changes.
 */
class MYPROJECT2_API FCharacterSheetDataAssetHandlers
{
public:
    /**
     * Handles changes to SelectedRace or SelectedSubrace.
     * Resets subrace if race changed, then validates and updates.
     */
    static void HandleRaceChange(UCharacterSheetDataAsset *Asset, FName PropertyName);

    /**
     * Handles changes to AbilityScores.
     * Validates Point Buy system and updates calculated fields.
     */
    static void HandleAbilityScoresChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to ClassLevels.
     * Validates total level and updates calculated fields.
     */
    static void HandleClassLevelsChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to SelectedBackground.
     * Updates calculated fields (proficiencies, etc.).
     */
    static void HandleBackgroundChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to Variant Human choices (CustomAbilityScoreChoices, SelectedFeat, SelectedSkill).
     * Validates Variant Human specific choices.
     */
    static void HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to Data Tables (RaceDataTable, ClassDataTable, BackgroundDataTable, FeatDataTable).
     * Validates if all Data Tables are selected and logs status.
     * When all Data Tables are ready, calls ValidateAndUpdate() to update everything.
     */
    static void HandleDataTableChange(UCharacterSheetDataAsset *Asset);
};
