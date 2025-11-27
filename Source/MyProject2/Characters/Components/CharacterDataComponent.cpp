// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterDataComponent.h"
#include "Net/UnrealNetwork.h"
#include "Utils/ValidationHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/FormattingHelpers.h"
#include "Utils/DnDConstants.h"
#include "Logging/LoggingSystem.h"

UCharacterDataComponent::UCharacterDataComponent() { PrimaryComponentTick.bCanEverTick = false; }

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

void UCharacterDataComponent::BeginPlay()
{
    Super::BeginPlay();
    // Seu código aqui
    LogCharacterSheet();
}

bool UCharacterDataComponent::ValidateDataIntegrity() const
{
    bool bIsValid = true;

    // Validação 1: Ability Scores devem ter os 6 atributos e valores válidos
    TArray<FName> RequiredAbilities = CharacterSheetHelpers::GetAbilityScoreNames();

    for (const FName &AbilityName : RequiredAbilities)
    {
        if (!AbilityScores.Contains(AbilityName))
        {
            FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
            FLoggingSystem::LogError(
                Context, FString::Printf(TEXT("Ability Score '%s' está faltando!"), *AbilityName.ToString()), true);
            bIsValid = false;
        }
        else
        {
            int32 Score = AbilityScores[AbilityName];
            if (!ValidationHelpers::ValidateAbilityScoreRange(Score, DnDConstants::MIN_ABILITY_SCORE,
                                                              DnDConstants::MAX_ABILITY_SCORE))
            {
                FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
                FLoggingSystem::LogError(
                    Context,
                    FString::Printf(TEXT("Ability Score '%s' tem valor inválido: %d (deve ser %d-%d)"),
                                    *AbilityName.ToString(), Score, DnDConstants::MIN_ABILITY_SCORE,
                                    DnDConstants::MAX_ABILITY_SCORE),
                    true);
                bIsValid = false;
            }
        }
    }

    // Validação 2: Raça deve estar selecionada
    if (SelectedRace == NAME_None)
    {
        FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
        FLoggingSystem::LogError(Context, TEXT("Raça não foi selecionada!"), true);
        bIsValid = false;
    }

    // Validação 3: Background deve estar selecionado
    if (SelectedBackground == NAME_None)
    {
        FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
        FLoggingSystem::LogError(Context, TEXT("Background não foi selecionado!"), true);
        bIsValid = false;
    }

    // Validação 4: Nível total deve ser válido (1-20)
    if (!ValidationHelpers::ValidateTotalLevelRange(CharacterTotalLvl, DnDConstants::MAX_LEVEL))
    {
        FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
        FLoggingSystem::LogError(Context,
                                 FString::Printf(TEXT("Nível total inválido: %d (deve ser %d-%d)"), CharacterTotalLvl,
                                                 DnDConstants::MIN_LEVEL, DnDConstants::MAX_LEVEL),
                                 true);
        bIsValid = false;
    }

    // Validação 5: Nome não deve estar vazio
    if (CharacterName == NAME_None)
    {
        FLogContext Context(TEXT("CharacterDataComponent"), TEXT("ValidateDataIntegrity"));
        FLoggingSystem::LogWarning(Context, TEXT("Nome do personagem não foi definido!"), true);
        // Não é erro crítico, apenas warning
    }

    return bIsValid;
}

void UCharacterDataComponent::LogCharacterSheet() const
{
    FLogContext Context(TEXT("CharacterDataComponent"), TEXT("LogCharacterSheet"));

    // Função de debug - usa LogInfo para logs informativos
    FLoggingSystem::LogInfo(Context, TEXT("=== Character Sheet ==="));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Name: %s"), *CharacterName.ToString()));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Description: %s"), *CharacterDescription.ToString()));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Level Total: %d"), CharacterTotalLvl));

    // Race & Background (usa FormattingHelpers)
    FString RaceDisplay = FormattingHelpers::FormatRaceDisplay(SelectedRace, SelectedSubrace);
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Race: %s"), *RaceDisplay));
    FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Background: %s"), *SelectedBackground.ToString()));

    // Variant Human Choices (se aplicável)
    if (SelectedSubrace == TEXT("Variant Human"))
    {
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

    // Race Traits
    if (RaceTraits.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("--- Race Traits (%d) ---"), RaceTraits.Num()));
        FString TraitsList = FormattingHelpers::FormatProficienciesList(RaceTraits);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *TraitsList));
    }

    // Ability Scores (usa FormattingHelpers)
    FLoggingSystem::LogInfo(Context, TEXT("--- Ability Scores ---"));
    TArray<FName> AbilityOrder = CharacterSheetHelpers::GetAbilityScoreNames();
    for (const FName &AbilityName : AbilityOrder)
    {
        if (AbilityScores.Contains(AbilityName))
        {
            FLoggingSystem::LogInfo(
                Context, FString::Printf(TEXT("  %s: %d"), *AbilityName.ToString(), AbilityScores[AbilityName]));
        }
        else
        {
            FLoggingSystem::LogError(Context, FString::Printf(TEXT("  %s: FALTANDO!"), *AbilityName.ToString()), true);
        }
    }

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

    // Available Features
    if (AvailableFeatures.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context,
                                FString::Printf(TEXT("--- Available Features (%d) ---"), AvailableFeatures.Num()));
        FString FeaturesList = FormattingHelpers::FormatProficienciesList(AvailableFeatures);
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("  %s"), *FeaturesList));
    }

    // Validação de integridade
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

    FLoggingSystem::LogInfo(Context, TEXT("======================"));
}
