// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterDataComponent.h"

UCharacterDataComponent::UCharacterDataComponent() { PrimaryComponentTick.bCanEverTick = false; }

void UCharacterDataComponent::BeginPlay()
{
    Super::BeginPlay();
    // Seu código aqui
    LogCharacterSheet();
}

void UCharacterDataComponent::LogCharacterSheet() const
{
    UE_LOG(LogTemp, Warning, TEXT("=== Character Sheet ==="));
    UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *CharacterName.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Description: %s"), *CharacterDescription.ToString());
    UE_LOG(LogTemp, Warning, TEXT("Level Total: %d"), CharacterTotalLvl);
    UE_LOG(LogTemp, Warning, TEXT("======================"));
}
