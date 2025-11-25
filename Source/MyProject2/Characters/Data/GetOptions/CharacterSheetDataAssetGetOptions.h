// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;
class UCharacterSheetDataAsset;

/**
 * GetOptions functions for CharacterSheetDataAsset dropdowns.
 * Contains the logic for populating dropdown options in the editor.
 *
 * Note: The actual GetOptions functions must remain in UCharacterSheetDataAsset
 * class because Unreal Engine's GetOptions meta requires them to be in the same class.
 * These functions provide the implementation logic that can be reused and tested.
 */
class MYPROJECT2_API FCharacterSheetDataAssetGetOptions
{
public:
    /**
     * Returns all race names from RaceDataTable.
     */
    static TArray<FName> GetRaceNames(UDataTable *RaceDataTable);

    /**
     * Returns all available subraces for the selected race.
     */
    static TArray<FName> GetSubraceNames(UDataTable *RaceDataTable, FName SelectedRace);

    /**
     * Returns all background names from BackgroundDataTable.
     */
    static TArray<FName> GetBackgroundNames(UDataTable *BackgroundDataTable);

    /**
     * Returns all ability score names (Strength, Dexterity, etc.).
     */
    static TArray<FName> GetAbilityScoreNames();

    /**
     * Returns all available feats for Variant Human.
     * Uses level 1 and current ability scores.
     */
    static TArray<FName> GetAvailableFeatNames(UDataTable *FeatDataTable, const TMap<FName, int32> &AbilityScores);

    /**
     * Returns all skill names from D&D 5e.
     * TODO: Move to SkillDataTable when implemented.
     */
    static TArray<FName> GetSkillNames();

    /**
     * Returns all available language names from D&D 5e.
     * TODO: Move to LanguageDataTable when implemented.
     */
    static TArray<FName> GetAvailableLanguageNames();

    /**
     * Returns available languages for choice, filtered (excluding already known automatic languages and already
     * selected languages). Uses current character state (race, subrace, background) to filter out languages the
     * character already speaks. Also filters out languages already chosen in the SelectedLanguages array to prevent
     * duplicates.
     *
     * @param RaceName Selected race name (can be NAME_None)
     * @param SubraceName Selected subrace name (can be NAME_None)
     * @param BackgroundName Selected background name (can be NAME_None)
     * @param SelectedLanguages Array of languages already selected by the player
     * @param RaceDataTable Race Data Table (can be nullptr)
     * @param BackgroundDataTable Background Data Table (can be nullptr)
     * @return Array with available languages for choice (excluding already known and already selected)
     */
    static TArray<FName> GetAvailableLanguageNamesForChoice(FName RaceName, FName SubraceName, FName BackgroundName,
                                                            const TArray<FName> &SelectedLanguages,
                                                            UDataTable *RaceDataTable, UDataTable *BackgroundDataTable);

    /**
     * Returns all class names from ClassDataTable with availability prefix.
     * Uses MulticlassingMotor to check prerequisites and adds prefix for unavailable classes.
     */
    static TArray<FName> GetClassNames(const UCharacterSheetDataAsset *Asset);

    /**
     * Returns all available subclasses for the selected class.
     */
    static TArray<FName> GetSubclassNames(UDataTable *ClassDataTable, FName ClassName);

    /**
     * Returns available options for a specific choice.
     * Used for dynamic dropdowns in class features (e.g., Fighting Style, Maneuvers).
     */
    static TArray<FName> GetChoiceOptions(const UCharacterSheetDataAsset *Asset, FName ChoiceID, FName ClassName,
                                          int32 ClassLevel);
};
