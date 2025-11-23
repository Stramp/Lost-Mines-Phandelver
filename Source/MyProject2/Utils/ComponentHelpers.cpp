// Copyright Epic Games, Inc. All Rights Reserved.

#include "ComponentHelpers.h"
#include "../Characters/Components/CharacterDataComponent.h"
#include "GameFramework/Actor.h"

UCharacterDataComponent *ComponentHelpers::FindCharacterDataComponent(AActor *Owner)
{
    if (!Owner)
    {
        return nullptr;
    }

    return Owner->FindComponentByClass<UCharacterDataComponent>();
}
