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
     * Handles changes to PointBuyAllocation.
     * Validates Point Buy system and updates Final Scores.
     */
    static void HandlePointBuyAllocationChange(UCharacterSheetDataAsset *Asset);

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
     * Handles changes to SelectedLanguages.
     * Validates language choices and updates calculated languages.
     */
    static void HandleLanguageChoicesChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to Data Tables (RaceDataTable, BackgroundDataTable, FeatDataTable).
     * Updates sheet visibility based on Data Tables selection and logs status.
     */
    static void HandleDataTableChange(UCharacterSheetDataAsset *Asset);

    // ============================================================================
    // Wrapper Functions for Property Handler Map (C-style function pointers)
    // ============================================================================
    // These wrapper functions are used as function pointers in the PropertyHandlers map.
    // They provide a consistent signature (UCharacterSheetDataAsset*, FName) for all handlers.

    static void HandleSelectedRaceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleSelectedSubraceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandlePointBuyAllocationWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleSelectedBackgroundWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleVariantHumanChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleLanguageChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleDataTableWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
};
