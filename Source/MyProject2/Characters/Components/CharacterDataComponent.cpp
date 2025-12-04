// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterDataComponent.h"

// Project includes - Utils
#include "Utils/ValidationHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/FormattingHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Net/UnrealNetwork.h"

#pragma endregion Includes

// ============================================================================
// Constructor
// ============================================================================
#pragma region Constructor

UCharacterDataComponent::UCharacterDataComponent() { PrimaryComponentTick.bCanEverTick = false; }

#pragma endregion Constructor

// ============================================================================
// Replication
// ============================================================================
#pragma region Replication

void UCharacterDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UCharacterDataComponent, CharacterName);
    DOREPLIFETIME(UCharacterDataComponent, CharacterDescription);
    DOREPLIFETIME(UCharacterDataComponent, CharacterTotalLvl);
    DOREPLIFETIME(UCharacterDataComponent, SelectedRace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedSubrace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedBackground);
    DOREPLIFETIME(UCharacterDataComponent, Proficiencies);
    DOREPLIFETIME(UCharacterDataComponent, AvailableFeatures);
    DOREPLIFETIME(UCharacterDataComponent, SelectedFeat);
    DOREPLIFETIME(UCharacterDataComponent, SelectedSkill);
    DOREPLIFETIME(UCharacterDataComponent, CustomAbilityScoreChoices);
    DOREPLIFETIME(UCharacterDataComponent, RaceTraits);
    DOREPLIFETIME(UCharacterDataComponent, Languages);
    // NOTA: AbilityScores (TMap) não pode ser replicado diretamente
    // Para replicação futura, usar TArray de structs ou implementar replicação customizada
}

#pragma endregion Replication

// ============================================================================
// Lifecycle
// ============================================================================
#pragma region Lifecycle

void UCharacterDataComponent::BeginPlay()
{
    Super::BeginPlay();
    // Seu código aqui
    LogCharacterSheet();
}

#pragma endregion Lifecycle

// ============================================================================
// Validation
// ============================================================================
#pragma region Validation

bool UCharacterDataComponent::ValidateDataIntegrity() const
{
    FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));

    bool bAbilityScoresValid = ValidateAbilityScoresIntegrity(Context);
    bool bBasicDataValid = ValidateBasicDataIntegrity(Context);
    bool bLevelValid = ValidateLevelIntegrity(Context);

    return bAbilityScoresValid && bBasicDataValid && bLevelValid;
}

bool UCharacterDataComponent::ValidateAbilityScoresIntegrity(const FLogContext &Context) const
{
    bool bIsValid = true;
    TArray<FNameWithID> RequiredAbilitiesWithIDs = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<FName> RequiredAbilities;
    for (const FNameWithID &AbilityWithID : RequiredAbilitiesWithIDs)
    {
        RequiredAbilities.Add(AbilityWithID.Name);
    }

    for (const FName &AbilityName : RequiredAbilities)
    {
        if (!AbilityScores.Contains(AbilityName))
        {
            // Usa throttle para evitar múltiplos popups quando há vários erros em loop
            FLoggingSystem::LogErrorWithThrottledPopup(
                Context, FString::Printf(TEXT("Ability Score '%s' está faltando!"), *AbilityName.ToString()), 0.5f);
            bIsValid = false;
        }
        else
        {
            int32 Score = AbilityScores[AbilityName];
            if (!ValidationHelpers::ValidateAbilityScoreRange(Score, DnDConstants::MIN_ABILITY_SCORE,
                                                              DnDConstants::MAX_ABILITY_SCORE))
            {
                // Usa throttle para evitar múltiplos popups quando há vários erros em loop
                FLoggingSystem::LogErrorWithThrottledPopup(
                    Context,
                    FString::Printf(TEXT("Ability Score '%s' tem valor inválido: %d (deve ser %d-%d)"),
                                    *AbilityName.ToString(), Score, DnDConstants::MIN_ABILITY_SCORE,
                                    DnDConstants::MAX_ABILITY_SCORE),
                    0.5f);
                bIsValid = false;
            }
        }
    }

    return bIsValid;
}

bool UCharacterDataComponent::ValidateBasicDataIntegrity(const FLogContext &Context) const
{
    bool bIsValid = true;

    // Raça deve estar selecionada
    if (SelectedRace == NAME_None)
    {
        FLoggingSystem::LogError(Context, TEXT("Raça não foi selecionada!"), true);
        bIsValid = false;
    }

    // Background deve estar selecionado
    if (SelectedBackground == NAME_None)
    {
        FLoggingSystem::LogError(Context, TEXT("Background não foi selecionado!"), true);
        bIsValid = false;
    }

    // Nome não deve estar vazio (não crítico - apenas warning sem popup)
    if (CharacterName == NAME_None)
    {
        FLoggingSystem::LogWarning(Context, TEXT("Nome do personagem não foi definido!"), false);
    }

    return bIsValid;
}

bool UCharacterDataComponent::ValidateLevelIntegrity(const FLogContext &Context) const
{
    if (!ValidationHelpers::ValidateTotalLevelRange(CharacterTotalLvl, DnDConstants::MAX_LEVEL))
    {
        FLoggingSystem::LogError(Context,
                                 FString::Printf(TEXT("Nível total inválido: %d (deve ser %d-%d)"), CharacterTotalLvl,
                                                 DnDConstants::MIN_LEVEL, DnDConstants::MAX_LEVEL),
                                 true);
        return false;
    }

    return true;
}

#pragma endregion Validation

// ============================================================================
// Logging
// ============================================================================
#pragma region Logging

void UCharacterDataComponent::LogCharacterSheet() const
{
    FLogContext Context(TEXT("CharacterDataComponent"), TEXT("LogCharacterSheet"));

    FLoggingSystem::LogInfo(Context, TEXT("=== Character Sheet ==="));

    LogBasicInfo(Context);
    LogVariantHumanChoices(Context);
    LogAbilityScores(Context);
    LogProficienciesAndLanguages(Context);
    LogAvailableFeatures(Context);
    LogDataIntegrityResult(Context);

    FLoggingSystem::LogInfo(Context, TEXT("======================"));
}

void UCharacterDataComponent::LogBasicInfo(const FLogContext &Context) const
{
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Name: %s"), *CharacterName.ToString()));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Description: %s"), *CharacterDescription.ToString()));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Level Total: %d"), CharacterTotalLvl));

    // Race & Background (usa FormattingHelpers)
    FString RaceDisplay = FormattingHelpers::FormatRaceDisplay(SelectedRace, SelectedSubrace);
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Race: %s"), *RaceDisplay));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Background: %s"), *SelectedBackground.ToString()));

    // Race Traits
    if (RaceTraits.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("--- Race Traits (%d) ---"), RaceTraits.Num()));
        FString TraitsList = FormattingHelpers::FormatProficienciesList(RaceTraits);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *TraitsList));
    }
}

void UCharacterDataComponent::LogVariantHumanChoices(const FLogContext &Context) const
{
    if (SelectedSubrace != TEXT("Variant Human"))
    {
        return;
    }

    FLoggingSystem::LogInfo(Context, TEXT("--- Variant Human Choices ---"));

    // Custom Ability Score Choices
    if (CustomAbilityScoreChoices.Num() > 0)
    {
        FString ChoicesStr;
        for (int32 i = 0; i < CustomAbilityScoreChoices.Num(); ++i)
        {
            ChoicesStr += CustomAbilityScoreChoices[i].ToString();
            if (i < CustomAbilityScoreChoices.Num() - 1)
            {
                ChoicesStr += TEXT(", ");
            }
        }
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  Custom Ability Score Choices: %s"), *ChoicesStr));
    }

    // Selected Feat
    if (SelectedFeat != NAME_None)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  Selected Feat: %s"), *SelectedFeat.ToString()));
    }

    // Selected Skill
    if (SelectedSkill != NAME_None)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  Selected Skill: %s"), *SelectedSkill.ToString()));
    }
}

void UCharacterDataComponent::LogAbilityScores(const FLogContext &Context) const
{
    FLoggingSystem::LogInfo(Context, TEXT("--- Ability Scores ---"));
    TArray<FNameWithID> AbilityOrderWithIDs = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<FName> AbilityOrder;
    for (const FNameWithID &AbilityWithID : AbilityOrderWithIDs)
    {
        AbilityOrder.Add(AbilityWithID.Name);
    }
    for (const FName &AbilityName : AbilityOrder)
    {
        if (AbilityScores.Contains(AbilityName))
        {
            FLoggingSystem::LogInfo(
                Context, FString::Printf(TEXT("  %s: %d"), *AbilityName.ToString(), AbilityScores[AbilityName]));
        }
        else
        {
            // Usa throttle para evitar múltiplos popups quando há vários erros em loop
            FLoggingSystem::LogErrorWithThrottledPopup(
                Context, FString::Printf(TEXT("  %s: FALTANDO!"), *AbilityName.ToString()), 0.5f);
        }
    }
}

void UCharacterDataComponent::LogProficienciesAndLanguages(const FLogContext &Context) const
{
    // Proficiencies (usa FormattingHelpers)
    if (Proficiencies.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("--- Proficiencies (%d) ---"), Proficiencies.Num()));
        FString ProficienciesList = FormattingHelpers::FormatProficienciesList(Proficiencies);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *ProficienciesList));
    }
    else
    {
        FLoggingSystem::LogInfo(Context, TEXT("--- Proficiencies: Nenhuma ---"));
    }

    // Languages (usa FormattingHelpers)
    if (Languages.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("--- Languages (%d) ---"), Languages.Num()));
        FString LanguagesList = FormattingHelpers::FormatProficienciesList(Languages);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *LanguagesList));
    }
    else
    {
        FLoggingSystem::LogInfo(Context, TEXT("--- Languages: Nenhuma ---"));
    }
}

void UCharacterDataComponent::LogAvailableFeatures(const FLogContext &Context) const
{
    if (AvailableFeatures.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context,
                                FString::Printf(TEXT("--- Available Features (%d) ---"), AvailableFeatures.Num()));
        FString FeaturesList = FormattingHelpers::FormatProficienciesList(AvailableFeatures);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *FeaturesList));
    }
}

void UCharacterDataComponent::LogDataIntegrityResult(const FLogContext &Context) const
{
    FLoggingSystem::LogInfo(Context, TEXT("--- Data Integrity ---"));
    bool bIsValid = ValidateDataIntegrity();
    if (bIsValid)
    {
        FLoggingSystem::LogInfo(Context, TEXT("  ✅ Todos os dados estão válidos e organizados corretamente"));
    }
    else
    {
        FLoggingSystem::LogError(Context, TEXT("  ❌ Dados inválidos ou incompletos! Verifique os erros acima."), true);
    }
}

#pragma endregion Logging
