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
#include "GameFramework/CharacterMovementComponent.h"
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

    // Configuração de rotação seguindo padrão Lyra para third person
    // Câmera rotaciona livremente ao redor do personagem
    // Personagem rotaciona apenas quando se move, na direção do movimento (que é baseado na câmera)
    bUseControllerRotationYaw = false;

    // Personagem se orienta na direção do movimento automaticamente
    // (o movimento já usa a direção da câmera, então o personagem rotaciona na direção da câmera quando se move)
    if (UCharacterMovementComponent *MovementComp = GetCharacterMovement())
    {
        MovementComp->bOrientRotationToMovement = true;
    }
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
    FVector2D MovementVector = Value.Get<FVector2D>();
    FLoggingSystem::LogInfo(FLogContext(TEXT("MyCharacter"), TEXT("Move")),
                            FString::Printf(TEXT("Move - Input: X=%.2f Y=%.2f"), MovementVector.X, MovementVector.Y));
    // Obtém o Vector2D do input (X = Left/Right, Y = Forward/Backward)

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

    // Combina as direções em um único vetor de movimento
    FVector MovementDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);

    // Aplica movimento em uma única chamada
    AddMovementInput(MovementDirection, 1.0f);
}

void AMyCharacter::Look(const FInputActionValue &Value)
{
    // Obtém o Vector2D do input (X = Yaw, Y = Pitch)
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Log para debug
    FLoggingSystem::LogInfo(FLogContext(TEXT("MyCharacter"), TEXT("Look")),
                            FString::Printf(TEXT("Look - Input: X=%.2f Y=%.2f"), LookAxisVector.X, LookAxisVector.Y));

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

    // Aplica rotação Yaw (horizontal) - rotaciona apenas a câmera
    // (personagem não rotaciona automaticamente, apenas quando se move)
    AddControllerYawInput(LookAxisVector.X);

    // Aplica rotação Pitch (vertical) - rotaciona apenas a câmera
    AddControllerPitchInput(LookAxisVector.Y);
}

#pragma endregion Input Handlers
