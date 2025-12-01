// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Characters/Components/Input/InputActionManagerComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

#pragma endregion Includes

// ============================================================================
// Constructor
// ============================================================================
#pragma region Constructor

UInputActionManagerComponent::UInputActionManagerComponent() { PrimaryComponentTick.bCanEverTick = false; }

#pragma endregion Constructor

// ============================================================================
// Input Action Management
// ============================================================================
#pragma region Input Action Management

UInputAction *UInputActionManagerComponent::GetInputAction(EInputActionType ActionType) const
{
    if (const UInputAction *const *FoundAction = InputActions.Find(ActionType))
    {
        return *FoundAction;
    }
    return nullptr;
}

void UInputActionManagerComponent::RegisterInputAction(EInputActionType ActionType, UInputAction *InputAction)
{
    if (InputAction)
    {
        InputActions.Add(ActionType, InputAction);
    }
}

bool UInputActionManagerComponent::HasInputAction(EInputActionType ActionType) const
{
    return InputActions.Contains(ActionType) && InputActions[ActionType] != nullptr;
}

#pragma endregion Input Action Management
