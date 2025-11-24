// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
class UCharacterSheetDataAsset;

/**
 * Updaters for CharacterSheetDataAsset.
 * Handles all update logic for calculated fields and racial bonuses.
 */
class MYPROJECT2_API FCharacterSheetDataAssetUpdaters
{
public:
    /**
     * Updates racial bonuses on ability scores.
     * Applies bonuses from base race and subrace (including Variant Human custom ASI).
     */
    static void UpdateRacialBonuses(UCharacterSheetDataAsset *Asset);

    /**
     * Updates calculated fields (AvailableFeatures, Proficiencies, etc.).
     * Collects features from all classes and levels.
     */
    static void UpdateCalculatedFields(UCharacterSheetDataAsset *Asset);

    /**
     * Updates Variant Human flag and notifies editor if changed.
     * Resets Variant Human choices if no longer Variant Human.
     */
    static void UpdateVariantHumanFlag(UCharacterSheetDataAsset *Asset);

    /**
     * Updates sheet visibility based on Data Tables selection.
     * Shows all categories when all Data Tables are selected, otherwise shows only Data Tables.
     */
    static void UpdateSheetVisibility(UCharacterSheetDataAsset *Asset);

    /**
     * Updates language choices detection (bHasLanguageChoices, MaxLanguageChoices).
     * Detects if race/background/feat allows language choices.
     */
    static void UpdateLanguageChoices(UCharacterSheetDataAsset *Asset);

    /**
     * Updates subrace flag (bHasSubraces).
     * Detects if selected race has available subraces.
     */
    static void UpdateSubraceFlag(UCharacterSheetDataAsset *Asset);

    /**
     * Recalcula Final Scores aplicando todos os motores sequencialmente.
     * Orquestrador: reseta para base (8) e aplica cada motor independente.
     * Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation
     *
     * @param Asset Character Sheet Data Asset
     */
    static void RecalculateFinalScores(UCharacterSheetDataAsset *Asset);

    /**
     * Updates Point Buy allocation and applies to Final Scores.
     * Motor independente: calcula alocação de Point Buy (0-7 por atributo) e aplica nos Final Scores.
     */
    static void UpdatePointBuyAllocation(UCharacterSheetDataAsset *Asset);
};
