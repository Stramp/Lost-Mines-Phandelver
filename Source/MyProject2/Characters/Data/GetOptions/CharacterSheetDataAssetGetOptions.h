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
    static TArray<FName> GetRaceNames(const UDataTable *RaceDataTable);

    /**
     * Returns all available subraces for the selected race.
     */
    static TArray<FName> GetSubraceNames(const UDataTable *RaceDataTable, FName SelectedRace);

    /**
     * Returns all background names from BackgroundDataTable.
     */
    static TArray<FName> GetBackgroundNames(const UDataTable *BackgroundDataTable);

    /**
     * Returns all ability score names (Strength, Dexterity, etc.).
     */
    static TArray<FName> GetAbilityScoreNames();

    /**
     * Returns all available feats for Variant Human.
     * Uses level 1 and current ability scores.
     */
    static TArray<FName> GetAvailableFeatNames(const UDataTable *FeatDataTable,
                                               const TMap<FName, int32> &AbilityScores);

    /**
     * Returns all skill names from D&D 5e.
     * Uses ProficiencyDataTable if provided (Data-Driven), otherwise falls back to hardcoded list.
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes de skills
     */
    static TArray<FName> GetSkillNames(const UDataTable *ProficiencyDataTable = nullptr);

    /**
     * Returns all available language names from D&D 5e.
     * Uses ProficiencyDataTable if provided (Data-Driven), otherwise falls back to hardcoded list.
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes de languages
     */
    static TArray<FName> GetAvailableLanguageNames(const UDataTable *ProficiencyDataTable = nullptr);

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
     * @param ProficiencyDataTable Proficiency Data Table (can be nullptr for hardcoded fallback)
     * @return Array with available languages for choice (excluding already known and already selected)
     */
    static TArray<FName> GetAvailableLanguageNamesForChoice(FName RaceName, FName SubraceName, FName BackgroundName,
                                                            const TArray<FName> &SelectedLanguages,
                                                            const UDataTable *RaceDataTable,
                                                            const UDataTable *BackgroundDataTable,
                                                            const UDataTable *ProficiencyDataTable = nullptr);

    /**
     * Returns all available class names with attribute requirement verification.
     * Formats class names as "ClassName" if available, or "ClassName (STR 13)" if requirements not met.
     *
     * @param ClassDataTable Class Data Table (can be nullptr)
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @return Array of formatted class names with requirement messages
     */
    static TArray<FName> GetListClassAvaible(const UDataTable *ClassDataTable, int32 FinalStrength,
                                             int32 FinalDexterity, int32 FinalConstitution, int32 FinalIntelligence,
                                             int32 FinalWisdom, int32 FinalCharisma);

    /**
     * Returns all available choice names from ClassFeaturesDataTable.
     * Collects all AvailableChoices from all features in the table.
     * Used for dropdown in FMulticlassClassFeature.AvailableChoices.
     *
     * @param FeatureDataTable Feature Data Table (can be nullptr)
     * @return Array with all available choice names from all features
     */
    static TArray<FName> GetAvailableChoiceNames(const UDataTable *FeatureDataTable);

    /**
     * Returns available choice IDs filtered by specific feature ID.
     * Only returns choice IDs from the feature matching the provided ID.
     * IDs are used for machine reference (stored in AvailableChoices/SelectedChoices).
     *
     * @param FeatureDataTable Feature Data Table (can be nullptr)
     * @param FeatureID ID of the feature to filter choices (ex: "FC_FightingStyle")
     * @return Array with available choice IDs only from the specified feature
     */
    static TArray<FName> GetAvailableChoiceIDsForFeature(const UDataTable *FeatureDataTable, FName FeatureID);

    /**
     * Returns available choice names filtered by specific feature ID.
     * Only returns choice names from the feature matching the provided ID.
     * Names are used for UI display (calculated properties).
     *
     * @param FeatureDataTable Feature Data Table (can be nullptr)
     * @param FeatureID ID of the feature to filter choices (ex: "FC_FightingStyle")
     * @return Array with available choice names only from the specified feature
     */
    static TArray<FName> GetAvailableChoiceNamesForFeature(const UDataTable *FeatureDataTable, FName FeatureID);

    /**
     * Returns all available skill names from D&D 5e.
     * Used for dropdown in FMulticlassSkills.available.
     * Note: The handler will filter based on InitialAvailable and Selected arrays.
     * Uses ProficiencyDataTable if provided (Data-Driven), otherwise falls back to hardcoded list.
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array with all D&D 5e skill names
     */
    static TArray<FName> GetAvailableSkills(const UDataTable *ProficiencyDataTable = nullptr);
};
