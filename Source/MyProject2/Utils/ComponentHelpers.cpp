// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "ComponentHelpers.h"

// Project includes - Characters
#include "Characters/Components/CharacterDataComponent.h"

// Engine includes
#include "GameFramework/Actor.h"

#pragma endregion Includes

// ============================================================================
// Component Helpers
// ============================================================================
#pragma region Component Helpers

UCharacterDataComponent *ComponentHelpers::FindCharacterDataComponent(AActor *Owner)
{
    if (!Owner)
    {
        return nullptr;
    }

    return Owner->FindComponentByClass<UCharacterDataComponent>();
}

#pragma endregion Component Helpers
