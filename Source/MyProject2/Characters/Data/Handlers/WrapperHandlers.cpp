// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHandlers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

#pragma endregion Includes

// ============================================================================
// Wrapper Functions for Property Handler Map
// ============================================================================
#pragma region Wrapper Functions

/**
 * Wrapper functions usadas como ponteiros de função C-style no map PropertyHandlers.
 * Fornecem assinatura consistente (UCharacterSheetDataAsset*, FName) para todos os handlers.
 * Organizadas na mesma ordem dos handlers principais para facilitar manutenção.
 */

// ============================================================================
// Race Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

// ============================================================================
// Point Buy Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandlePointBuyAllocationChange(Asset);
}

// ============================================================================
// Background Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandleBackgroundChange(Asset);
}

// ============================================================================
// Language Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleLanguageChoicesChange(Asset);
}

// ============================================================================
// Variant Human Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper(UCharacterSheetDataAsset *Asset,
                                                                        FName PropertyName)
{
    HandleVariantHumanChoicesChange(Asset);
}

// ============================================================================
// Data Table Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleDataTableWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleDataTableChange(Asset, PropertyName);
}

// ============================================================================
// Multiclass Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleLevelInClassWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleLevelInClassChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameWrapper(UCharacterSheetDataAsset *Asset,
                                                                        FName PropertyName)
{
    HandleMulticlassClassNameChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleProgressionWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleProgressionChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleProficienciesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleProficienciesChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleAvailableSkillWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleAvailableSkillChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedSkillsWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleSelectedSkillsChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleAvailableChoiceToAddWrapper(UCharacterSheetDataAsset *Asset,
                                                                         FName PropertyName)
{
    HandleAvailableChoiceToAddChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleSelectedChoicesChange(Asset);
}

#pragma endregion Wrapper Functions
