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
    if (UInputAction *const *FoundAction = InputActions.Find(ActionType))
    {
        return *FoundAction;
    }
    return nullptr;
}

void UInputActionManagerComponent::RegisterInputAction(EInputActionType ActionType, UInputAction *InputAction)
{
    if (!InputAction)
    {
        UE_LOG(LogTemp, Warning, TEXT("RegisterInputAction recebeu nullptr para ActionType %d"),
               static_cast<int32>(ActionType));
        return;
    }

    if (InputActions.Contains(ActionType))
    {
        UE_LOG(LogTemp, Warning, TEXT("RegisterInputAction sobrescrevendo InputAction existente para ActionType %d"),
               static_cast<int32>(ActionType));
    }

    InputActions.Add(ActionType, InputAction);
}

bool UInputActionManagerComponent::HasInputAction(EInputActionType ActionType) const
{
    return InputActions.Contains(ActionType) && InputActions[ActionType] != nullptr;
}

#pragma endregion Input Action Management
