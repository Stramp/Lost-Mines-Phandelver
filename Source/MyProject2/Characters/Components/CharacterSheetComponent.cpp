// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetComponent.h"
#include "../Data/CharacterSheetDataAsset.h"
#include "CharacterDataComponent.h"
#include "../../Utils/ComponentHelpers.h"
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

    // Salva referência ao Data Asset
    SourceDataAsset = DataAsset;

    UE_LOG(LogTemp, Log, TEXT("CharacterSheetComponent: Dados inicializados do Data Asset '%s'"),
           *DataAsset->GetName());
}
