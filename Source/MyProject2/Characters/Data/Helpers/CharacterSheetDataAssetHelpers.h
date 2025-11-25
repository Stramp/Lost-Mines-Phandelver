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

    /**
     * Creates a map of ability scores from final attribute values.
     * Used for feat validation and other ability score-based operations.
     *
     * @param FinalStrength Final Strength score
     * @param FinalDexterity Final Dexterity score
     * @param FinalConstitution Final Constitution score
     * @param FinalIntelligence Final Intelligence score
     * @param FinalWisdom Final Wisdom score
     * @param FinalCharisma Final Charisma score
     * @return Map of ability score names to their final values
     */
    static TMap<FName, int32> CreateAbilityScoresMap(int32 FinalStrength, int32 FinalDexterity, int32 FinalConstitution,
                                                     int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma);

    /**
     * Updates Point Buy allocation values from adjusted allocation map.
     * Uses GetAbilityScoreNames() to ensure data-driven approach.
     *
     * @param Asset Character Sheet Data Asset to update
     * @param AdjustedAllocation Map of ability score names to adjusted values
     */
    static void UpdatePointBuyFromAdjustedAllocation(UCharacterSheetDataAsset *Asset,
                                                     const TMap<FName, int32> &AdjustedAllocation);
};
