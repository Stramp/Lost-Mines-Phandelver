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
     * Handles changes to Data Tables (RaceDataTable, BackgroundDataTable, FeatDataTable, ClassDataTable).
     * Validates Data Table type and updates sheet visibility based on Data Tables selection.
     *
     * @param Asset Data Asset
     * @param PropertyName Name of the property that changed (to identify which Data Table was modified)
     */
    static void HandleDataTableChange(UCharacterSheetDataAsset *Asset, FName PropertyName);

    /**
     * Handles changes to LevelInClass in Multiclass array.
     * Ajusta o array Progression e processa features ganhas no nível correspondente.
     *
     * @param Asset Asset do personagem
     * @param bSkipGuard Se true, não cria FValidationGuard (útil quando chamado de outro handler que já tem Guard)
     */
    static void HandleLevelInClassChange(UCharacterSheetDataAsset *Asset, bool bSkipGuard = false);

    /**
     * Handles changes to ClassData.Name in Multiclass array.
     * Resets the field to NAME_None if the selected class has a requirement tag (starts with "[").
     */
    static void HandleMulticlassClassNameChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to ClassData.Progression in Multiclass array.
     * Valida e limpa Progression se Name == NAME_None ou LevelInClass == 0.
     */
    static void HandleProgressionChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to ClassData.Proficiencies in Multiclass array.
     * Atualiza qtdAvailable dinamicamente quando skills são escolhidas/removidas.
     */
    static void HandleProficienciesChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to FSkills.available (dropdown) in Multiclass array.
     * Quando uma skill é selecionada no dropdown, adiciona ao Selected e reseta available.
     */
    static void HandleAvailableSkillChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to FSkills.Selected (array) in Multiclass array.
     * Recalcula qtdAvailable quando skills são adicionadas/removidas do Selected.
     */
    static void HandleSelectedSkillsChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to FMulticlassClassFeature.AvailableChoiceToAdd (dropdown) in Multiclass array.
     * Quando uma escolha é selecionada no dropdown, adiciona ao SelectedChoices e reseta AvailableChoiceToAdd.
     * Usado para features do Tipo 3 (Escolhas Múltiplas) como Manobras e Metamagic.
     */
    static void HandleAvailableChoiceToAddChange(UCharacterSheetDataAsset *Asset);

    /**
     * Handles changes to FMulticlassClassFeature.SelectedChoices (array) in Multiclass array.
     * Valida escolhas quando são adicionadas/removidas do SelectedChoices.
     * Usado para features do Tipo 3 (Escolhas Múltiplas) como Manobras e Metamagic.
     */
    static void HandleSelectedChoicesChange(UCharacterSheetDataAsset *Asset);

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
    static void HandleLevelInClassWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleMulticlassClassNameWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleProgressionWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleProficienciesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleAvailableSkillWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleSelectedSkillsWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleAvailableChoiceToAddWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
    static void HandleSelectedChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName);
};
