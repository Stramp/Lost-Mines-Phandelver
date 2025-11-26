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
     * Updates calculated fields (Proficiencies, Languages, etc.).
     * Calculates proficiencies from background and Variant Human skill.
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
     * Recalcula scores finais usando Core genérico (aplica todos os motores).
     * Atualiza PointsRemaining e ajusta alocação se necessário.
     *
     * @param Asset Asset do personagem
     */
    static void RecalculateFinalScores(UCharacterSheetDataAsset *Asset);
};
