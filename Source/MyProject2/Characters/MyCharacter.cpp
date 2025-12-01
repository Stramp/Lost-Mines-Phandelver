// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Characters/MyCharacter.h"

// Project includes - Helpers
#include "Characters/Helpers/MovementHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#pragma endregion Includes

// ============================================================================
// Construction
// ============================================================================
#pragma region Construction

AMyCharacter::AMyCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;
}

#pragma endregion Construction

// ============================================================================
// Lifecycle
// ============================================================================
#pragma region Lifecycle

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Configura o Input Mapping Context
    APlayerController *PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem && IMC)
        {
            Subsystem->AddMappingContext(IMC, 0);
        }
    }
}

#pragma endregion Lifecycle

// ============================================================================
// Input Setup
// ============================================================================
#pragma region Input Setup

void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        // Bind Move Action
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
        }

        // Bind Look Action
        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
        }
    }
}

#pragma endregion Input Setup

// ============================================================================
// Input Handlers
// ============================================================================
#pragma region Input Handlers

void AMyCharacter::Move(const FInputActionValue &Value)
{
    // Obtém o Vector2D do input (X = Left/Right, Y = Forward/Backward)
    FVector2D MovementVector = Value.Get<FVector2D>();

    // Se o movimento for muito pequeno, ignora (evita drift)
    if (MovementVector.IsNearlyZero())
    {
        return;
    }

    // Obtém a rotação do controle (câmera)
    FRotator ControlRotation = GetControlRotation();

    // Calcula direções Forward e Right baseadas na rotação da câmera
    FVector ForwardDirection = MovementHelpers::CalculateForwardDirection(ControlRotation);
    FVector RightDirection = MovementHelpers::CalculateRightDirection(ControlRotation);

    // Aplica movimento Forward/Backward (Y do input)
    AddMovementInput(ForwardDirection, MovementVector.Y);

    // Aplica movimento Left/Right (X do input)
    AddMovementInput(RightDirection, MovementVector.X);

    // Log para debug (pode ser removido em produção)
    FLoggingSystem::LogInfo(
        FLogContext(TEXT("MyCharacter"), TEXT("Move")),
        FString::Printf(TEXT("Move - Input: X=%.2f Y=%.2f | Forward: (%.2f, %.2f, %.2f) | Right: (%.2f, %.2f, %.2f)"),
                        MovementVector.X, MovementVector.Y, ForwardDirection.X, ForwardDirection.Y, ForwardDirection.Z,
                        RightDirection.X, RightDirection.Y, RightDirection.Z));
}

void AMyCharacter::Look(const FInputActionValue &Value)
{
    // Obtém o Vector2D do input (X = Yaw, Y = Pitch)
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Se o input for muito pequeno, ignora (evita drift)
    if (LookAxisVector.IsNearlyZero())
    {
        return;
    }

    // Obtém o controller
    APlayerController *PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController)
    {
        return;
    }

    // Aplica rotação Yaw (horizontal) - rotaciona o personagem
    AddControllerYawInput(LookAxisVector.X);

    // Aplica rotação Pitch (vertical) - rotaciona a câmera
    AddControllerPitchInput(LookAxisVector.Y);

    // Log para debug (pode ser removido em produção)
    FLoggingSystem::LogInfo(FLogContext(TEXT("MyCharacter"), TEXT("Look")),
                            FString::Printf(TEXT("Look - Input: X=%.2f Y=%.2f"), LookAxisVector.X, LookAxisVector.Y));
}

#pragma endregion Input Handlers
