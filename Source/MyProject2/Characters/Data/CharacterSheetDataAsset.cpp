// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAsset.h"

// Project includes - Data modules
#include "Characters/Data/GetOptions/CharacterSheetDataAssetGetOptions.h"
#include "Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"
#include "Characters/Data/Initializers/CharacterSheetDataAssetInitializers.h"
#include "Characters/Data/Loaders/CharacterSheetDataAssetLoaders.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetCorrectionApplier.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#if WITH_EDITOR
#include "Editor.h"
#include "PropertyEditorModule.h"
#endif

#pragma endregion Includes

// ============================================================================
// Constructor
// ============================================================================
#pragma region Constructor

UCharacterSheetDataAsset::UCharacterSheetDataAsset()
{
#if WITH_EDITOR
    FCharacterSheetDataAssetInitializers::InitializeAllPropertyHandlers(this);
#endif
}

#pragma endregion Constructor

// ============================================================================
// Editor-Only Implementation
// ============================================================================
#if WITH_EDITOR

// ============================================================================
// Property Change Handling
// ============================================================================

// ============================================================================
// Property Change Handling
// ============================================================================
#pragma region Property Change Handling

void UCharacterSheetDataAsset::PostLoad()
{
    Super::PostLoad();

    if (PropertyHandlers.Num() == 0)
    {
        FCharacterSheetDataAssetInitializers::InitializeAllPropertyHandlers(this);
    }

#if WITH_EDITOR
    // Delega toda a lógica de inicialização para Initializers (Template Method Pattern)
    FCharacterSheetDataAssetInitializers::InitializeBootProtocol(this);
#endif
}

/**
 * Processa mudanças de propriedades no editor.
 * Responsabilidade única: separar e chamar handler apropriado.
 */
void UCharacterSheetDataAsset::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // IMPORTANTE: Verifica bIsValidatingProperties ANTES de qualquer processamento
    // Isso evita que handlers bloqueiem mudanças de propriedades
    if (bIsValidatingProperties || !PropertyChangedEvent.Property)
    {
        return;
    }

    const FName PropertyName = PropertyChangedEvent.Property->GetFName();

    if (FCharacterSheetDataAssetHelpers::IsCalculatedProperty(PropertyName))
    {
        return;
    }

    // Responsabilidade única: separar e chamar handler apropriado
    EnsurePropertyHandlersInitialized();

    // Tenta encontrar handler para propriedade direta
    FName HandlerPropertyName = PropertyName;

    // Detecta propriedades aninhadas que precisam de handler específico
    FCharacterSheetDataAssetHelpers::DetectNestedMulticlassProperty(PropertyChangedEvent, HandlerPropertyName);

    // Chama handler se encontrado
    // IMPORTANTE: Handler é chamado DEPOIS que a propriedade já foi alterada
    // O handler não deve bloquear a mudança, apenas reagir a ela
    if (PropertyHandlerFunction *HandlerPtr = PropertyHandlers.Find(HandlerPropertyName))
    {
        (*HandlerPtr)(this, HandlerPropertyName);
    }
}

#pragma endregion Property Change Handling

// ============================================================================
// Property Handlers Initialization
// ============================================================================
#pragma region Property Handlers Initialization

void UCharacterSheetDataAsset::EnsurePropertyHandlersInitialized()
{
    if (PropertyHandlers.Num() == 0)
    {
        FCharacterSheetDataAssetInitializers::InitializeAllPropertyHandlers(this);
    }
}

void UCharacterSheetDataAsset::InitializePropertyHandlers()
{
    FCharacterSheetDataAssetInitializers::InitializeAllPropertyHandlers(this);
}

#pragma endregion Property Handlers Initialization

// ============================================================================
// GetOptions Functions (Editor Dropdowns)
// ============================================================================
#pragma region GetOptions Functions

/**
 * Wrapper functions for editor dropdown options.
 * Lógica real está em FCharacterSheetDataAssetGetOptions.
 */

TArray<FName> UCharacterSheetDataAsset::GetRaceNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetRaceNames(RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubraceNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetSubraceNames(RaceDataTable, SelectedRace);
}

TArray<FName> UCharacterSheetDataAsset::GetBackgroundNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetBackgroundNames(BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetAbilityScoreNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableFeatNames() const
{
    const TMap<FName, int32> AbilityScores = FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(
        FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence, FinalWisdom, FinalCharisma);

    return FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(FeatDataTable, AbilityScores);
}

TArray<FName> UCharacterSheetDataAsset::GetSkillNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetSkillNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableLanguageNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
        SelectedRace, SelectedSubrace, SelectedBackground, SelectedLanguages, RaceDataTable, BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableChoiceNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAvailableChoiceNames(ClassFeaturesDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetListClassAvaible() const
{
    return FCharacterSheetDataAssetGetOptions::GetListClassAvaible(ClassDataTable, FinalStrength, FinalDexterity,
                                                                   FinalConstitution, FinalIntelligence, FinalWisdom,
                                                                   FinalCharisma);
}

#pragma endregion GetOptions Functions

// ============================================================================
// Validation Helpers
// ============================================================================
#pragma region Validation Helpers

void UCharacterSheetDataAsset::SetValidatingProperties(bool bValidating) { bIsValidatingProperties = bValidating; }

bool UCharacterSheetDataAsset::IsValidatingProperties() const { return bIsValidatingProperties; }

#pragma endregion Validation Helpers

#endif // WITH_EDITOR
