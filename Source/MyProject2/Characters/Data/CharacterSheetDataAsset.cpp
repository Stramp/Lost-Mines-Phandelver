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

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

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
// Local Helpers
// ============================================================================
#pragma region Local Helpers

namespace
{
    /**
     * Detecta se a propriedade mudada é uma propriedade aninhada dentro do array Multiclass.
     * Extraído de PostEditChangeProperty para manter função focada.
     *
     * @param PropertyChangedEvent Evento de mudança de propriedade
     * @param HandlerPropertyName [OUT] Nome da propriedade do handler (pode ser diferente de PropertyName)
     * @return true se é propriedade aninhada que precisa de handler específico, false caso contrário
     */
    bool DetectNestedMulticlassProperty(const FPropertyChangedEvent &PropertyChangedEvent, FName &HandlerPropertyName)
    {
        if (!PropertyChangedEvent.MemberProperty || !PropertyChangedEvent.Property)
        {
            return false;
        }

        const FName MemberPropertyName = PropertyChangedEvent.MemberProperty->GetFName();
        const FName PropertyName = PropertyChangedEvent.Property->GetFName();

        // Propriedades aninhadas em Multiclass array
        // Verifica se MemberProperty é Multiclass OU se Property é LevelInClass/Name/Progression diretamente
        if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, Multiclass) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name) ||
            PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression))
        {
            // LevelInClass dentro de ClassData dentro de Multiclass
            if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass))
            {
                HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass);
                return true;
            }
            // Name dentro de ClassData dentro de Multiclass
            else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name))
            {
                HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name);
                return true;
            }
            // Progression dentro de ClassData dentro de Multiclass
            else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression))
            {
                HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression);
                return true;
            }
        }

        return false;
    }
} // namespace

#pragma endregion Local Helpers

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
    DetectNestedMulticlassProperty(PropertyChangedEvent, HandlerPropertyName);

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
    // Por enquanto retorna vazio - será implementado quando a mecânica de preencher AvailableChoices estiver pronta
    return {};
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
