// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetComponent.h"
#include "../Data/CharacterSheetDataAsset.h"
#include "CharacterDataComponent.h"
#include "../../Utils/ComponentHelpers.h"
#include "../../Utils/DataTableHelpers.h"
#include "../../Data/Tables/RaceDataTable.h"
#include "GameFramework/Actor.h"

UCharacterSheetComponent::UCharacterSheetComponent() { PrimaryComponentTick.bCanEverTick = false; }

UCharacterDataComponent *UCharacterSheetComponent::FindOrGetCharacterDataComponent()
{
    if (!CharacterDataComponent)
    {
        CharacterDataComponent = ComponentHelpers::FindCharacterDataComponent(GetOwner());
    }
    return CharacterDataComponent;
}

void UCharacterSheetComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor *Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterSheetComponent: Owner não encontrado"));
        return;
    }

    if (!FindOrGetCharacterDataComponent())
    {
        FString OwnerName = Owner ? Owner->GetName() : TEXT("Desconhecido");
        UE_LOG(LogTemp, Error, TEXT("CharacterSheetComponent: CharacterDataComponent não encontrado no Actor %s"),
               *OwnerName);
        return;
    }

    // Se há um Data Asset atribuído, inicializa automaticamente
    if (SourceDataAsset)
    {
        InitializeFromDataAsset(SourceDataAsset);
    }
}

void UCharacterSheetComponent::InitializeFromDataAsset(UCharacterSheetDataAsset *DataAsset)
{
    // Guard clauses - validações iniciais
    if (!ensureMsgf(DataAsset, TEXT("CharacterSheetComponent: DataAsset é nullptr")))
    {
        return;
    }

    if (!FindOrGetCharacterDataComponent())
    {
        AActor *Owner = GetOwner();
        FString OwnerName = Owner ? Owner->GetName() : TEXT("Desconhecido");
        UE_LOG(LogTemp, Error, TEXT("CharacterSheetComponent: CharacterDataComponent não encontrado no Actor %s"),
               *OwnerName);
        return;
    }

    // Copia dados do Data Asset para o CharacterDataComponent
    CharacterDataComponent->CharacterName = DataAsset->CharacterName;
    CharacterDataComponent->CharacterDescription = DataAsset->CharacterDescription;
    CharacterDataComponent->CharacterTotalLvl = DataAsset->TotalLevel;
    CharacterDataComponent->SelectedRace = DataAsset->SelectedRace;
    CharacterDataComponent->SelectedSubrace = DataAsset->SelectedSubrace;
    CharacterDataComponent->SelectedBackground = DataAsset->SelectedBackground;
    CharacterDataComponent->Proficiencies = DataAsset->Proficiencies;
    CharacterDataComponent->AvailableFeatures = DataAsset->AvailableFeatures;

    // Copia Variant Human choices (se aplicável)
    CharacterDataComponent->SelectedFeat = DataAsset->SelectedFeat;
    CharacterDataComponent->SelectedSkill = DataAsset->SelectedSkill;
    CharacterDataComponent->CustomAbilityScoreChoices = DataAsset->CustomAbilityScoreChoices;

    // Copia idiomas calculados (automáticos + escolhidos)
    CharacterDataComponent->Languages = DataAsset->Languages;

    // Busca e copia traits da raça (raça base + sub-raça se houver)
    CharacterDataComponent->RaceTraits.Empty();
    if (DataAsset->RaceDataTable && DataAsset->SelectedRace != NAME_None)
    {
        // Busca traits da raça base
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(DataAsset->SelectedRace, DataAsset->RaceDataTable))
        {
            for (const FRaceTrait &Trait : RaceRow->Traits)
            {
                if (Trait.TraitName != NAME_None)
                {
                    CharacterDataComponent->RaceTraits.AddUnique(Trait.TraitName);
                }
            }
        }

        // Busca traits da sub-raça (se houver)
        if (DataAsset->SelectedSubrace != NAME_None)
        {
            if (FRaceDataRow *SubraceRow =
                    DataTableHelpers::FindSubraceRow(DataAsset->SelectedSubrace, DataAsset->RaceDataTable))
            {
                for (const FRaceTrait &Trait : SubraceRow->Traits)
                {
                    if (Trait.TraitName != NAME_None)
                    {
                        CharacterDataComponent->RaceTraits.AddUnique(Trait.TraitName);
                    }
                }
            }
        }
    }

    // Copia ability scores (valores finais dos campos dedicados)
    CharacterDataComponent->AbilityScores.Empty();
    CharacterDataComponent->AbilityScores.Add(TEXT("Strength"), DataAsset->FinalStrength);
    CharacterDataComponent->AbilityScores.Add(TEXT("Dexterity"), DataAsset->FinalDexterity);
    CharacterDataComponent->AbilityScores.Add(TEXT("Constitution"), DataAsset->FinalConstitution);
    CharacterDataComponent->AbilityScores.Add(TEXT("Intelligence"), DataAsset->FinalIntelligence);
    CharacterDataComponent->AbilityScores.Add(TEXT("Wisdom"), DataAsset->FinalWisdom);
    CharacterDataComponent->AbilityScores.Add(TEXT("Charisma"), DataAsset->FinalCharisma);

    // Salva referência ao Data Asset
    SourceDataAsset = DataAsset;

    UE_LOG(LogTemp, Log, TEXT("CharacterSheetComponent: Dados inicializados do Data Asset '%s'"),
           *DataAsset->GetName());
}
