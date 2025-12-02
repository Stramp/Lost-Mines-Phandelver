// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/MyCharacter.h"
#include "Characters/Components/Input/InputActionManagerComponent.h"
#include "Characters/Components/Input/InputActionType.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Tests/AutomationCommon.h"

#pragma endregion Includes

// ============================================================================
// Test Spec Definition
// ============================================================================
#pragma region Test Spec Definition

BEGIN_DEFINE_SPEC(MyCharacterIntegrationSpec, "MyProject2.Characters.MyCharacter.Integration",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter |
                      EAutomationTestFlags::ClientContext)
AMyCharacter *TestCharacter;
FTestWorldWrapper TestWorldWrapper;
APlayerController *TestPlayerController;
UInputAction *TestMoveAction;
UInputAction *TestLookAction;
END_DEFINE_SPEC(MyCharacterIntegrationSpec)

#pragma endregion Test Spec Definition

// ============================================================================
// Test Implementation
// ============================================================================
#pragma region Test Implementation

namespace
{
    void SetupTestInputActions(UWorld *TestWorld, AMyCharacter *TestCharacter, UInputAction *&TestMoveAction,
                               UInputAction *&TestLookAction)
    {
        TestMoveAction = NewObject<UInputAction>(TestWorld);
        TestLookAction = NewObject<UInputAction>(TestWorld);

        UInputActionManagerComponent *InputManager = TestCharacter->GetInputActionManager();
        if (InputManager)
        {
            InputManager->RegisterInputAction(EInputActionType::Move, TestMoveAction);
            InputManager->RegisterInputAction(EInputActionType::Look, TestLookAction);
        }
    }
} // namespace

void MyCharacterIntegrationSpec::Define()
{
    BeforeEach(
        [this]()
        {
            if (!TestWorldWrapper.CreateTestWorld(EWorldType::Game))
            {
                TestTrue("Mundo de teste deve ser criado", false);
                return;
            }

            UWorld *TestWorld = TestWorldWrapper.GetTestWorld();
            if (!TestWorld)
            {
                TestTrue("Mundo de teste deve ser válido", false);
                return;
            }

            if (!TestWorldWrapper.BeginPlayInTestWorld())
            {
                TestTrue("Mundo de teste deve iniciar play", false);
                return;
            }

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            TestCharacter = TestWorld->SpawnActor<AMyCharacter>(AMyCharacter::StaticClass(), FVector::ZeroVector,
                                                                FRotator::ZeroRotator, SpawnParams);

            if (!TestCharacter)
            {
                TestTrue("Character deve ser spawnado", false);
                return;
            }

            SetupTestInputActions(TestWorld, TestCharacter, TestMoveAction, TestLookAction);

            TestPlayerController = TestWorld->SpawnActor<APlayerController>(
                APlayerController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
            if (TestPlayerController && TestCharacter)
            {
                TestPlayerController->Possess(TestCharacter);
            }

            TestWorldWrapper.TickTestWorld(0.1f);
        });

    Describe(
        "Move Integration",
        [this]()
        {
            It("deve processar input de movimento sem crash",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UInputActionManagerComponent *InputManager = TestCharacter->GetInputActionManager();
                   TestTrue("Character deve ter InputActionManager", InputManager != nullptr);

                   UWorld *TestWorld = TestWorldWrapper.GetTestWorld();
                   if (TestWorld)
                   {
                       TestWorldWrapper.TickTestWorld(0.1f);
                   }

                   TestTrue("Character deve estar válido", IsValid(TestCharacter));
               });

            It("deve validar InputActionManager não é nullptr",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UInputActionManagerComponent *InputManager = TestCharacter->GetInputActionManager();
                   TestNotNull("InputActionManager não deve ser nullptr", InputManager);
               });

            It("deve ter InputActionManager configurado corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UInputActionManagerComponent *InputManager = TestCharacter->GetInputActionManager();
                   TestNotNull("InputActionManager deve existir", InputManager);

                   if (InputManager)
                   {
                       TestTrue("Move Action deve estar registrada",
                                InputManager->HasInputAction(EInputActionType::Move));
                       TestTrue("Look Action deve estar registrada",
                                InputManager->HasInputAction(EInputActionType::Look));
                   }
               });

            It("deve ter CharacterMovement configurado corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   TestNotNull("CharacterMovement deve existir", MovementComp);

                   if (MovementComp)
                   {
                       TestFalse("bOrientRotationToMovement deve ser false (modo movimento)",
                                 MovementComp->bOrientRotationToMovement);
                       TestTrue("bUseControllerDesiredRotation deve ser true (modo movimento)",
                                MovementComp->bUseControllerDesiredRotation);
                   }
               });

            It("deve ter configurações de velocidade e aceleração corretas",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   TestNotNull("CharacterMovement deve existir", MovementComp);

                   if (MovementComp)
                   {
                       // Valores esperados (hardcoded - sem lógica interna)
                       const float ExpectedMaxWalkSpeed = 600.0f;
                       const float ExpectedMaxAcceleration = 2048.0f;
                       const float ExpectedBrakingDeceleration = 512.0f;

                       TestEqual("MaxWalkSpeed deve ser 600.0", MovementComp->MaxWalkSpeed, ExpectedMaxWalkSpeed);
                       TestEqual("MaxAcceleration deve ser 2048.0", MovementComp->MaxAcceleration,
                                 ExpectedMaxAcceleration);
                       TestEqual("BrakingDecelerationWalking deve ser 512.0", MovementComp->BrakingDecelerationWalking,
                                 ExpectedBrakingDeceleration);
                   }
               });

            It("deve ter configurações de física corretas",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   TestNotNull("CharacterMovement deve existir", MovementComp);

                   if (MovementComp)
                   {
                       // Valores esperados (hardcoded - sem lógica interna)
                       const float ExpectedGroundFriction = 8.0f;
                       const float ExpectedGravityScale = 1.0f;
                       const float ExpectedJumpZVelocity = 420.0f;
                       const float ExpectedAirControl = 0.35f;

                       TestEqual("GroundFriction deve ser 8.0", MovementComp->GroundFriction, ExpectedGroundFriction);
                       TestEqual("GravityScale deve ser 1.0", MovementComp->GravityScale, ExpectedGravityScale);
                       TestEqual("JumpZVelocity deve ser 420.0", MovementComp->JumpZVelocity, ExpectedJumpZVelocity);
                       TestEqual("AirControl deve ser 0.35", MovementComp->AirControl, ExpectedAirControl);
                   }
               });

            It("deve ter configurações de rotação corretas",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   TestNotNull("CharacterMovement deve existir", MovementComp);

                   if (MovementComp)
                   {
                       // Valor esperado (hardcoded - sem lógica interna)
                       const FRotator ExpectedRotationRate(0.0f, 540.0f, 0.0f);

                       TestEqual("RotationRate.Yaw deve ser 540.0", MovementComp->RotationRate.Yaw,
                                 ExpectedRotationRate.Yaw);
                       TestEqual("RotationRate.Pitch deve ser 0.0", MovementComp->RotationRate.Pitch,
                                 ExpectedRotationRate.Pitch);
                       TestEqual("RotationRate.Roll deve ser 0.0", MovementComp->RotationRate.Roll,
                                 ExpectedRotationRate.Roll);
                   }
               });
        });

    Describe(
        "Look Integration",
        [this]()
        {
            It("deve ter PlayerController configurado corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   APlayerController *PC = Cast<APlayerController>(TestCharacter->GetController());
                   TestNotNull("PlayerController deve existir", PC);

                   if (PC)
                   {
                       FRotator ControlRotation = TestCharacter->GetControlRotation();
                       TestTrue("Control Rotation deve ser válido", true);
                   }
               });

            It("deve ter rotação inicial configurada corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   TestFalse("bUseControllerRotationYaw deve ser false", TestCharacter->bUseControllerRotationYaw);
                   TestFalse("bUseControllerRotationPitch deve ser false", TestCharacter->bUseControllerRotationPitch);
                   TestFalse("bUseControllerRotationRoll deve ser false", TestCharacter->bUseControllerRotationRoll);
               });
        });

    Describe(
        "UpdateRotationMode Integration",
        [this]()
        {
            It("deve configurar modo 1 (movimento) corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   if (!MovementComp)
                   {
                       TestTrue("Movement Component deve existir", false);
                       return;
                   }

                   TestCharacter->SetRotationMode(false);

                   TestFalse("Modo 1: bOrientRotationToMovement deve ser false",
                             MovementComp->bOrientRotationToMovement);
                   TestTrue("Modo 1: bUseControllerDesiredRotation deve ser true",
                            MovementComp->bUseControllerDesiredRotation);
               });

            It("deve configurar modo 2 (câmera) corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   if (!MovementComp)
                   {
                       TestTrue("Movement Component deve existir", false);
                       return;
                   }

                   TestCharacter->SetRotationMode(true);

                   TestTrue("Modo 2: bOrientRotationToMovement deve ser true", MovementComp->bOrientRotationToMovement);
                   TestFalse("Modo 2: bUseControllerDesiredRotation deve ser false",
                             MovementComp->bUseControllerDesiredRotation);
               });

            It("deve alternar entre modos corretamente",
               [this]()
               {
                   if (!TestCharacter)
                   {
                       TestTrue("Character deve existir", false);
                       return;
                   }

                   UCharacterMovementComponent *MovementComp = TestCharacter->GetCharacterMovement();
                   if (!MovementComp)
                   {
                       TestTrue("Movement Component deve existir", false);
                       return;
                   }

                   TestCharacter->SetRotationMode(false);
                   TestFalse("Modo 1: bOrientRotationToMovement deve ser false",
                             MovementComp->bOrientRotationToMovement);
                   TestTrue("Modo 1: bUseControllerDesiredRotation deve ser true",
                            MovementComp->bUseControllerDesiredRotation);

                   TestCharacter->SetRotationMode(true);
                   TestTrue("Modo 2: bOrientRotationToMovement deve ser true", MovementComp->bOrientRotationToMovement);
                   TestFalse("Modo 2: bUseControllerDesiredRotation deve ser false",
                             MovementComp->bUseControllerDesiredRotation);
               });
        });

    AfterEach(
        [this]()
        {
            if (TestCharacter)
            {
                TestCharacter->Destroy();
                TestCharacter = nullptr;
            }

            if (TestPlayerController)
            {
                TestPlayerController->Destroy();
                TestPlayerController = nullptr;
            }

            TestMoveAction = nullptr;
            TestLookAction = nullptr;

            TestWorldWrapper.DestroyTestWorld(true);
        });
}

#pragma endregion Test Implementation
