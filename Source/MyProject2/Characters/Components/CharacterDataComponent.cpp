// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterDataComponent.h"
#include "Net/UnrealNetwork.h"

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
    DOREPLIFETIME(UCharacterDataComponent, AbilityScores);
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

    // Validação 1: Ability Scores devem ter os 6 atributos
    TArray<FName> RequiredAbilities = {TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                                       TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};

    for (const FName &AbilityName : RequiredAbilities)
    {
        if (!AbilityScores.Contains(AbilityName))
        {
            UE_LOG(LogTemp, Error, TEXT("CharacterDataComponent: Ability Score '%s' está faltando!"),
                   *AbilityName.ToString());
            bIsValid = false;
        }
        else
        {
            int32 Score = AbilityScores[AbilityName];
            if (Score < 1 || Score > 30)
            {
                UE_LOG(LogTemp, Error,
                       TEXT("CharacterDataComponent: Ability Score '%s' tem valor inválido: %d (deve ser 1-30)"),
                       *AbilityName.ToString(), Score);
                bIsValid = false;
            }
        }
    }

    // Validação 2: Raça deve estar selecionada
    if (SelectedRace == NAME_None)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterDataComponent: Raça não foi selecionada!"));
        bIsValid = false;
    }

    // Validação 3: Background deve estar selecionado
    if (SelectedBackground == NAME_None)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterDataComponent: Background não foi selecionado!"));
        bIsValid = false;
    }

    // Validação 4: Nível total deve ser válido (1-20)
    if (CharacterTotalLvl < 1 || CharacterTotalLvl > 20)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterDataComponent: Nível total inválido: %d (deve ser 1-20)"),
               CharacterTotalLvl);
        bIsValid = false;
    }

    // Validação 5: Nome não deve estar vazio
    if (CharacterName == NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("CharacterDataComponent: Nome do personagem não foi definido!"));
        // Não é erro crítico, apenas warning
    }

    return bIsValid;
}

void UCharacterDataComponent::LogCharacterSheet() const
{
    UE_LOG(LogTemp, Warning, TEXT("=== Character Sheet ==="));
    UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *CharacterName.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *CharacterDescription.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Level Total: %d"), CharacterTotalLvl);

    // Race & Background
    FString RaceDisplay = SelectedRace.ToString();
    if (SelectedSubrace != NAME_None)
    {
        RaceDisplay += TEXT(" (") + SelectedSubrace.ToString() + TEXT(")");
    }
    UE_LOG(LogTemp, Warning, TEXT("Race: %s"), *RaceDisplay);
    UE_LOG(LogTemp, Warning, TEXT("Background: %s"), *SelectedBackground.ToString());

    // Ability Scores
    UE_LOG(LogTemp, Warning, TEXT("--- Ability Scores ---"));
    TArray<FName> AbilityOrder = {TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                                  TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
    for (const FName &AbilityName : AbilityOrder)
    {
        if (AbilityScores.Contains(AbilityName))
        {
            UE_LOG(LogTemp, Warning, TEXT("  %s: %d"), *AbilityName.ToString(), AbilityScores[AbilityName]);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("  %s: FALTANDO!"), *AbilityName.ToString());
        }
    }

    // Proficiencies
    if (Proficiencies.Num() > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("--- Proficiencies (%d) ---"), Proficiencies.Num());
        FString ProficienciesList;
        for (int32 i = 0; i < Proficiencies.Num(); ++i)
        {
            ProficienciesList += Proficiencies[i].ToString();
            if (i < Proficiencies.Num() - 1)
            {
                ProficienciesList += TEXT(", ");
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("  %s"), *ProficienciesList);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("--- Proficiencies: Nenhuma ---"));
    }

    // Validação de integridade
    UE_LOG(LogTemp, Warning, TEXT("--- Data Integrity ---"));
    bool bIsValid = ValidateDataIntegrity();
    if (bIsValid)
    {
        UE_LOG(LogTemp, Warning, TEXT("  ✅ Todos os dados estão válidos e organizados corretamente"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("  ❌ Dados inválidos ou incompletos! Verifique os erros acima."));
    }

    UE_LOG(LogTemp, Warning, TEXT("======================"));
}
