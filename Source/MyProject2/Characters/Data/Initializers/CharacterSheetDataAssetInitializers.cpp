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

// Project includes - Loaders
#include "Characters/Data/Loaders/CharacterSheetDataAssetLoaders.h"

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"
#include "Characters/Data/Helpers/ValidationGuard.h"

// Project includes - Correction Applier
#include "Characters/Data/Validators/CharacterSheetDataAssetCorrectionApplier.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

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
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassFeaturesDataTable),
                                FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassProficienciesDataTable),
                                FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
}

#pragma endregion Data Table Handlers Initialization

// ============================================================================
// Multiclass Handlers Initialization
// ============================================================================
#pragma region Multiclass Handlers Initialization

void FCharacterSheetDataAssetInitializers::InitializeMulticlassHandlers(UCharacterSheetDataAsset *Asset)
{
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass),
                                FCharacterSheetDataAssetHandlers::HandleLevelInClassWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name),
                                FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression),
                                FCharacterSheetDataAssetHandlers::HandleProgressionWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Proficiencies),
                                FCharacterSheetDataAssetHandlers::HandleProficienciesWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassSkills, available),
                                FCharacterSheetDataAssetHandlers::HandleAvailableSkillWrapper);
    Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(FMulticlassSkills, Selected),
                                FCharacterSheetDataAssetHandlers::HandleSelectedSkillsWrapper);
}

#pragma endregion Multiclass Handlers Initialization

// ============================================================================
// Boot Protocol Initialization
// ============================================================================
#pragma region Boot Protocol Initialization

void FCharacterSheetDataAssetInitializers::InitializeBootProtocol(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // FASE 1: Preparar condições (ajustar LevelInClass ANTES de carregar)
    FCharacterSheetDataAssetUpdaters::AdjustLevelInClassForClassName(Asset);

    // FASE 2: Carregar dados (com condições corretas)
    FCharacterSheetDataAssetLoaders::LoadAllMulticlassData(Asset);

    // FASE 3: Validar estado
    FValidationResult BootValidationResult = FCharacterSheetDataAssetValidators::ValidateAll(Asset);

    // FASE 4: Corrigir se necessário (com Guard Pattern)
    if (BootValidationResult.bNeedsCorrection)
    {
        // Detecta se LevelInClass foi alterado (função pura, testável)
        bool bLevelInClassWasAdjusted =
            FCharacterSheetDataAssetHelpers::DetectLevelInClassCorrections(BootValidationResult);

        // Protege contra PostEditChangeProperty durante correções
        FValidationGuard Guard(Asset);
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, BootValidationResult);

        // FASE 5: Recarregar se correção alterou condições críticas (Strategy Pattern)
        if (bLevelInClassWasAdjusted)
        {
            FCharacterSheetDataAssetLoaders::ReloadMulticlassDataIfNeeded(Asset, true);
        }

        // Valida novamente após correções (defesa em profundidade)
        FValidationResult PostCorrectionResult = FCharacterSheetDataAssetValidators::ValidateAll(Asset);
        if (PostCorrectionResult.bNeedsCorrection)
        {
            FLogContext Context(TEXT("CharacterSheet"), TEXT("InitializeBootProtocol"));
            FLoggingSystem::LogWarning(Context,
                                       TEXT("Ainda há problemas após aplicar correções. Verifique manualmente."), true);
        }
    }

    // FASE 6: Finalizar (atualizar flags usando Updater)
    FCharacterSheetDataAssetUpdaters::UpdateMulticlassFlags(Asset);
}

#pragma endregion Boot Protocol Initialization
