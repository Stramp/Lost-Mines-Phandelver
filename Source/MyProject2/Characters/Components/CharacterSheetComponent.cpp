// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetComponent.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "CharacterDataComponent.h"
#include "Utils/ComponentHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Logging/LoggingSystem.h"
#include "GameFramework/Actor.h"

UCharacterSheetComponent::UCharacterSheetComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UCharacterSheetComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor *Owner = GetOwner();
    if (!Owner)
    {
        FLogContext Context(TEXT("CharacterSheetComponent"), TEXT("BeginPlay"));
        FLoggingSystem::LogError(Context, TEXT("Owner não encontrado"), true);
        return;
    }

    // Cache explícito do CharacterDataComponent no BeginPlay
    CharacterDataComponent = ComponentHelpers::FindCharacterDataComponent(Owner);
    if (!CharacterDataComponent)
    {
        FString OwnerName = Owner ? Owner->GetName() : TEXT("Desconhecido");
        FLogContext Context(TEXT("CharacterSheetComponent"), TEXT("BeginPlay"));
        FLoggingSystem::LogError(
            Context, FString::Printf(TEXT("CharacterDataComponent não encontrado no Actor %s"), *OwnerName), true);
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

    // Se componente não foi cacheado ainda (pode acontecer se chamado antes do BeginPlay), busca agora
    if (!CharacterDataComponent)
    {
        AActor *Owner = GetOwner();
        if (!Owner)
        {
            FLogContext Context(TEXT("CharacterSheetComponent"), TEXT("InitializeFromDataAsset"));
            FLoggingSystem::LogError(Context, TEXT("Owner não encontrado"), true);
            return;
        }

        CharacterDataComponent = ComponentHelpers::FindCharacterDataComponent(Owner);
        if (!CharacterDataComponent)
        {
            FString OwnerName = Owner ? Owner->GetName() : TEXT("Desconhecido");
            FLogContext Context(TEXT("CharacterSheetComponent"), TEXT("InitializeFromDataAsset"));
            FLoggingSystem::LogError(
                Context, FString::Printf(TEXT("CharacterDataComponent não encontrado no Actor %s"), *OwnerName), true);
            return;
        }
    }

    // Copia dados do Data Asset para o CharacterDataComponent
    CharacterDataComponent->CharacterName = DataAsset->CharacterName;
    CharacterDataComponent->CharacterDescription = DataAsset->CharacterDescription;
    // Nota: TotalLevel e AvailableFeatures não existem mais no Data Asset (removidos - serão calculados pelo motor de
    // multiclassing)
    CharacterDataComponent->CharacterTotalLvl = 0; // Sem classes, nível é 0
    CharacterDataComponent->SelectedRace = DataAsset->SelectedRace;
    CharacterDataComponent->SelectedSubrace = DataAsset->SelectedSubrace;
    CharacterDataComponent->SelectedBackground = DataAsset->SelectedBackground;
    CharacterDataComponent->AvailableFeatures.Empty(); // Sem classes, não há features

    // Copia Variant Human choices (se aplicável)
    CharacterDataComponent->SelectedFeat = DataAsset->SelectedFeat;
    CharacterDataComponent->SelectedSkill = DataAsset->SelectedSkill;
    CharacterDataComponent->CustomAbilityScoreChoices = DataAsset->CustomAbilityScoreChoices;

    // Nota: Proficiencies e Languages são calculados diretamente no CharacterDataComponent quando necessário
    // Não são mais armazenados no Data Asset

    // Busca e copia traits da raça (raça base + sub-raça se houver)
    CharacterDataComponent->RaceTraits.Empty();
    if (DataAsset->RaceDataTable && DataAsset->SelectedRace != NAME_None)
    {
        // Otimização: usa TSet para verificação O(1) antes de adicionar
        TSet<FName> TraitsSet;

        // Busca traits da raça base
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(DataAsset->SelectedRace, DataAsset->RaceDataTable))
        {
            for (const FRaceTrait &Trait : RaceRow->Traits)
            {
                if (Trait.TraitName != NAME_None && !TraitsSet.Contains(Trait.TraitName))
                {
                    TraitsSet.Add(Trait.TraitName);
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
                    if (Trait.TraitName != NAME_None && !TraitsSet.Contains(Trait.TraitName))
                    {
                        TraitsSet.Add(Trait.TraitName);
                    }
                }
            }
        }

        // Converte TSet para TArray
        CharacterDataComponent->RaceTraits = TraitsSet.Array();
    }

    // Copia ability scores (valores finais dos campos dedicados)
    // Usa helper GetAbilityScoreNames para eliminar duplicação (DRY)
    CharacterDataComponent->AbilityScores.Empty();
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<int32 *> AbilityValues = {&DataAsset->FinalStrength,     &DataAsset->FinalDexterity,
                                     &DataAsset->FinalConstitution, &DataAsset->FinalIntelligence,
                                     &DataAsset->FinalWisdom,       &DataAsset->FinalCharisma};

    // Garante que temos exatamente 6 atributos
    check(AbilityNames.Num() == 6);
    check(AbilityValues.Num() == 6);

    for (int32 i = 0; i < AbilityNames.Num() && i < AbilityValues.Num(); ++i)
    {
        CharacterDataComponent->AbilityScores.Add(AbilityNames[i], *AbilityValues[i]);
    }

    // Salva referência ao Data Asset
    SourceDataAsset = DataAsset;

    FLogContext Context(TEXT("CharacterSheetComponent"), TEXT("InitializeFromDataAsset"));
    FLoggingSystem::LogInfo(Context,
                            FString::Printf(TEXT("Dados inicializados do Data Asset '%s'"), *DataAsset->GetName()));
}
