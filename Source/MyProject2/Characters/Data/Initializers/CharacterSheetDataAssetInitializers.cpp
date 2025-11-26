// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetInitializers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - Handlers
#include "Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h"

// Engine includes
#include "UObject/UnrealType.h"

#pragma endregion Includes

// ============================================================================
// Initialize All Property Handlers
// ============================================================================
#pragma region Initialize All Property Handlers

void FCharacterSheetDataAssetInitializers::InitializeAllPropertyHandlers(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    InitializeRaceHandlers(Asset);
    InitializePointBuyHandlers(Asset);
    InitializeBackgroundHandlers(Asset);
    InitializeVariantHumanHandlers(Asset);
    InitializeLanguageHandlers(Asset);
    InitializeDataTableHandlers(Asset);
    InitializeMulticlassHandlers(Asset);
}

#pragma endregion Initialize All Property Handlers

// ============================================================================
// Race Handlers Initialization
// ============================================================================
#pragma region Race Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeRaceHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace),
                                 FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace),
                                 FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper);
}

#pragma endregion Race Handlers Initialization

// ============================================================================
// Point Buy Handlers Initialization
// ============================================================================
#pragma region Point Buy Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializePointBuyHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyStrength),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyDexterity),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyConstitution),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyIntelligence),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyWisdom),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyCharisma),
                                 FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
}

#pragma endregion Point Buy Handlers Initialization

// ============================================================================
// Background Handlers Initialization
// ============================================================================
#pragma region Background Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeBackgroundHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground),
                                 FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper);
}

#pragma endregion Background Handlers Initialization

// ============================================================================
// Variant Human Handlers Initialization
// ============================================================================
#pragma region Variant Human Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeVariantHumanHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices),
                                 FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat),
                                 FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill),
                                 FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
}

#pragma endregion Variant Human Handlers Initialization

// ============================================================================
// Language Handlers Initialization
// ============================================================================
#pragma region Language Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeLanguageHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages),
                                 FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper);
}

#pragma endregion Language Handlers Initialization

// ============================================================================
// Data Table Handlers Initialization
// ============================================================================
#pragma region Data Table Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeDataTableHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable),
                                 FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable),
                                 FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable),
                                 FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable),
                                 FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
}

#pragma endregion Data Table Handlers Initialization

// ============================================================================
// Multiclass Handlers Initialization
// ============================================================================
#pragma region Multiclass Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeMulticlassHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassEntry, LevelInClass),
                                 FCharacterSheetDataAssetHandlers::HandleLevelInClassWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FClassData, Name),
                                 FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameWrapper);
}

#pragma endregion Multiclass Handlers Initialization
