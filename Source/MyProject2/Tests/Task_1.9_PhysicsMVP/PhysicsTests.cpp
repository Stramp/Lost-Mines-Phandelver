// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#pragma endregion Includes

// ============================================================================
// Physics Tests
// ============================================================================
#pragma region Physics Tests

BEGIN_DEFINE_SPEC(PhysicsSpec, "MyProject2.Physics",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(PhysicsSpec)

void PhysicsSpec::Define()
{
    // ============================================================================
    // MyCharacter Physics Configuration Tests
    // ============================================================================
    Describe(
        "Issue-1.9/ MyCharacter Physics Configuration",
        [this]()
        {
            It("deve criar AMyCharacter sem crash",
               [this]()
               {
                   // Arrange & Act
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());

                   // Assert
                   TestNotNull("Character deve ser criado", Character);
                   TestTrue("AMyCharacter criado sem crash", Character != nullptr);
               });

            It("deve ter CharacterMovementComponent configurado",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());

                   // Act
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Assert
                   TestNotNull("CharacterMovementComponent deve existir", MovementComp);
               });

            It("deve configurar MaxWalkSpeed como 600.0 cm/s",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("MaxWalkSpeed deve ser 600.0 cm/s",
                            FMath::IsNearlyEqual(MovementComp->MaxWalkSpeed, 600.0f, 0.01f));
               });

            It("deve configurar MaxAcceleration como 2048.0 cm/s²",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("MaxAcceleration deve ser 2048.0 cm/s²",
                            FMath::IsNearlyEqual(MovementComp->MaxAcceleration, 2048.0f, 0.01f));
               });

            It("deve configurar BrakingDecelerationWalking como 512.0 cm/s²",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("BrakingDecelerationWalking deve ser 512.0 cm/s²",
                            FMath::IsNearlyEqual(MovementComp->BrakingDecelerationWalking, 512.0f, 0.01f));
               });

            It("deve configurar GroundFriction como 8.0",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("GroundFriction deve ser 8.0",
                            FMath::IsNearlyEqual(MovementComp->GroundFriction, 8.0f, 0.01f));
               });

            It("deve configurar RotationRate.Yaw como 540.0 graus/s",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("RotationRate.Yaw deve ser 540.0 graus/s",
                            FMath::IsNearlyEqual(MovementComp->RotationRate.Yaw, 540.0, 0.01));
               });

            It("deve configurar RotationRate.Pitch como 0.0 graus/s",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("RotationRate.Pitch deve ser 0.0 graus/s",
                            FMath::IsNearlyEqual(MovementComp->RotationRate.Pitch, 0.0, 0.01));
               });

            It("deve configurar RotationRate.Roll como 0.0 graus/s",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("RotationRate.Roll deve ser 0.0 graus/s",
                            FMath::IsNearlyEqual(MovementComp->RotationRate.Roll, 0.0, 0.01));
               });

            It("deve configurar GravityScale como 1.0",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("GravityScale deve ser 1.0", FMath::IsNearlyEqual(MovementComp->GravityScale, 1.0f, 0.01f));
               });

            It("deve configurar bOrientRotationToMovement como false",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestFalse("bOrientRotationToMovement deve ser false", MovementComp->bOrientRotationToMovement);
               });

            It("deve configurar bUseControllerDesiredRotation como true",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("bUseControllerDesiredRotation deve ser true", MovementComp->bUseControllerDesiredRotation);
               });

            It("deve configurar JumpZVelocity como 420.0 cm/s",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("JumpZVelocity deve ser 420.0 cm/s",
                            FMath::IsNearlyEqual(MovementComp->JumpZVelocity, 420.0f, 0.01f));
               });

            It("deve configurar AirControl como 0.35",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("AirControl deve ser 0.35", FMath::IsNearlyEqual(MovementComp->AirControl, 0.35f, 0.01f));
               });

            It("deve configurar bCanWalkOffLedges como true",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestTrue("bCanWalkOffLedges deve ser true", MovementComp->bCanWalkOffLedges);
               });

            It("deve configurar bCanWalkOffLedgesWhenCrouching como false",
               [this]()
               {
                   // Arrange
                   AMyCharacter *Character = NewObject<AMyCharacter>(GetTransientPackage());
                   UCharacterMovementComponent *MovementComp = Character->GetCharacterMovement();

                   // Act & Assert
                   TestFalse("bCanWalkOffLedgesWhenCrouching deve ser false",
                             MovementComp->bCanWalkOffLedgesWhenCrouching);
               });
        });
}

#pragma endregion Physics Tests
