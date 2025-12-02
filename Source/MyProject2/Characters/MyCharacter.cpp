// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Characters/MyCharacter.h"

// Project includes - Components
#include "Characters/Components/Input/InputActionManagerComponent.h"
#include "Characters/Components/Input/InputActionType.h"

// Project includes - Helpers
#include "Characters/Helpers/MovementHelpers.h"

// Engine includes
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"

#pragma endregion Includes

// ============================================================================
// Construction
// ============================================================================
#pragma region Construction

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    InputActionManager = CreateDefaultSubobject<UInputActionManagerComponent>(TEXT("InputActionManager"));

    // Configuração de rotação seguindo padrão Lyra para third person
    // Câmera rotaciona livremente; personagem rotaciona apenas quando se move
    bUseControllerRotationYaw = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;

    // ============================================================================
    // Physics and Movement Configuration
    // ============================================================================
    // Configuração básica de física e movimento para MVP
    // Valores podem ser ajustados no Editor via Blueprint se necessário
    if (UCharacterMovementComponent *MovementComp = GetCharacterMovement())
    {
        // Rotation Configuration
        MovementComp->bOrientRotationToMovement = false;
        MovementComp->bUseControllerDesiredRotation = true;

        // Movement Speed Configuration
        MovementComp->MaxWalkSpeed = 600.0f;               // Velocidade máxima de caminhada (cm/s)
        MovementComp->MaxAcceleration = 2048.0f;           // Aceleração máxima (cm/s²)
        MovementComp->BrakingDecelerationWalking = 512.0f; // Desaceleração ao parar (cm/s²)

        // Ground Friction
        MovementComp->GroundFriction = 8.0f; // Atrito no chão (padrão: 8.0)

        // Rotation Rate
        MovementComp->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // Taxa de rotação (graus/s) - Yaw apenas

        // Jump Configuration (preparação para futuro)
        MovementComp->JumpZVelocity = 420.0f; // Velocidade inicial do pulo (cm/s)
        MovementComp->AirControl = 0.35f;     // Controle no ar (0.0-1.0)

        // Physics Configuration
        MovementComp->GravityScale = 1.0f;                    // Escala de gravidade (padrão: 1.0)
        MovementComp->bCanWalkOffLedges = true;               // Permite caminhar de bordas
        MovementComp->bCanWalkOffLedgesWhenCrouching = false; // Não permite caminhar de bordas agachado
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
    SetupInputMappingContext();
}

void AMyCharacter::SetupInputMappingContext()
{
    APlayerController *PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController)
    {
        return;
    }

    UEnhancedInputLocalPlayerSubsystem *Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    if (!Subsystem)
    {
        return;
    }

    ensureMsgf(IMC, TEXT("Input Mapping Context não configurado em %s. Input não funcionará."), *GetName());
    if (IMC)
    {
        Subsystem->AddMappingContext(IMC, 0);
    }
}

#pragma endregion Lifecycle

// ============================================================================
// Input Setup
// ============================================================================
#pragma region Input Setup

namespace
{
    constexpr float INPUT_DEADZONE = 0.01f;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    ensureMsgf(InputActionManager, TEXT("InputActionManager não configurado em %s. Input não funcionará."), *GetName());
    if (!InputActionManager)
    {
        return;
    }

    UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    ensureMsgf(EnhancedInputComponent, TEXT("EnhancedInputComponent não encontrado em %s. Input não funcionará."),
               *GetName());
    if (!EnhancedInputComponent)
    {
        return;
    }

    BindInputActions(EnhancedInputComponent);
}

void AMyCharacter::BindInputActions(UEnhancedInputComponent *EnhancedInputComponent)
{
    check(InputActionManager);
    check(EnhancedInputComponent);

    if (UInputAction *MoveAction = InputActionManager->GetInputAction(EInputActionType::Move))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("MoveAction não encontrada em InputActionManager de %s"), *GetName());
    }

    if (UInputAction *LookAction = InputActionManager->GetInputAction(EInputActionType::Look))
    {
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("LookAction não encontrada em InputActionManager de %s"), *GetName());
    }

    if (UInputAction *ToggleAction = InputActionManager->GetInputAction(EInputActionType::ToggleRotationMode))
    {
        EnhancedInputComponent->BindAction(ToggleAction, ETriggerEvent::Triggered, this,
                                           &AMyCharacter::ToggleRotationMode);
        EnhancedInputComponent->BindAction(ToggleAction, ETriggerEvent::Completed, this,
                                           &AMyCharacter::ReleaseRotationMode);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ToggleRotationModeAction não encontrada em InputActionManager de %s"),
               *GetName());
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
    if (MovementVector.IsNearlyZero(INPUT_DEADZONE))
    {
        return;
    }

    FRotator ControlRotation = GetControlRotation();
    FVector ForwardDirection = MovementHelpers::CalculateForwardDirection(ControlRotation);
    FVector RightDirection = MovementHelpers::CalculateRightDirection(ControlRotation);
    FVector MovementDirection = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);

    AddMovementInput(MovementDirection, 1.0f);
}

void AMyCharacter::Look(const FInputActionValue &Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    if (LookAxisVector.IsNearlyZero(INPUT_DEADZONE))
    {
        return;
    }

    APlayerController *PlayerController = Cast<APlayerController>(GetController());
    if (!PlayerController)
    {
        return;
    }

    AddControllerYawInput(LookAxisVector.X);
    // Invertido para comportamento padrão de mouse em third person
    AddControllerPitchInput(-LookAxisVector.Y);
}

void AMyCharacter::ToggleRotationMode(const FInputActionValue &Value) { UpdateRotationMode(true); }

void AMyCharacter::ReleaseRotationMode(const FInputActionValue &Value) { UpdateRotationMode(false); }

void AMyCharacter::UpdateRotationMode(bool bLookAtCamera)
{
    if (UCharacterMovementComponent *MovementComp = GetCharacterMovement())
    {
        if (bLookAtCamera)
        {
            MovementComp->bUseControllerDesiredRotation = false;
            MovementComp->bOrientRotationToMovement = true;
        }
        else
        {
            MovementComp->bOrientRotationToMovement = false;
            MovementComp->bUseControllerDesiredRotation = true;
        }
    }
}

#pragma endregion Input Handlers
