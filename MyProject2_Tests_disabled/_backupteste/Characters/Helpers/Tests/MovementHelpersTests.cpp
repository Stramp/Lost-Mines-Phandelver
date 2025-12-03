// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Helpers/MovementHelpers.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"

#pragma endregion Includes

// ============================================================================
// Test Spec Definition
// ============================================================================
#pragma region Test Spec Definition

BEGIN_DEFINE_SPEC(MovementHelpersSpec, "MyProject2.Characters.MovementHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
END_DEFINE_SPEC(MovementHelpersSpec)

#pragma endregion Test Spec Definition

// ============================================================================
// Test Implementation
// ============================================================================
#pragma region Test Implementation

void MovementHelpersSpec::Define()
{
    Describe("CalculateForwardDirection",
             [this]()
             {
                 It("deve calcular direção Forward correta para rotação Yaw 0° (direção +X)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 0.0f, 0.0f);
                        FVector ExpectedDirection(1.0f, 0.0f, 0.0f); // +X (frente no Unreal)

                        // Act
                        FVector Result = MovementHelpers::CalculateForwardDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Forward para Yaw 0° deve ser +X", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Forward para Yaw 0° deve ter Y = 0", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Forward para Yaw 0° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve calcular direção Forward correta para rotação Yaw 90° (direção +Y)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 90.0f, 0.0f);
                        FVector ExpectedDirection(0.0f, 1.0f, 0.0f); // +Y (direita no Unreal)

                        // Act
                        FVector Result = MovementHelpers::CalculateForwardDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Forward para Yaw 90° deve ter X = 0", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Forward para Yaw 90° deve ser +Y", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Forward para Yaw 90° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve calcular direção Forward correta para rotação Yaw 180° (direção -X)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 180.0f, 0.0f);
                        FVector ExpectedDirection(-1.0f, 0.0f, 0.0f); // -X (trás no Unreal)

                        // Act
                        FVector Result = MovementHelpers::CalculateForwardDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Forward para Yaw 180° deve ser -X", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Forward para Yaw 180° deve ter Y = 0", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Forward para Yaw 180° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve ignorar Pitch e Roll, usando apenas Yaw",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotationWithPitch(45.0f, 0.0f, 0.0f); // Pitch 45°, Yaw 0°
                        FRotator ControlRotationYawOnly(0.0f, 0.0f, 0.0f);    // Yaw 0° apenas
                        FVector ExpectedDirection(1.0f, 0.0f, 0.0f);          // +X (mesmo resultado)

                        // Act
                        FVector ResultWithPitch = MovementHelpers::CalculateForwardDirection(ControlRotationWithPitch);
                        FVector ResultYawOnly = MovementHelpers::CalculateForwardDirection(ControlRotationYawOnly);

                        // Assert
                        TestEqual("Direção com Pitch deve ser igual à direção sem Pitch (X)",
                                  static_cast<float>(ResultWithPitch.X), static_cast<float>(ResultYawOnly.X), 0.001f);
                        TestEqual("Direção com Pitch deve ser igual à direção sem Pitch (Y)",
                                  static_cast<float>(ResultWithPitch.Y), static_cast<float>(ResultYawOnly.Y), 0.001f);
                        TestEqual("Direção com Pitch deve ser igual à direção sem Pitch (Z)",
                                  static_cast<float>(ResultWithPitch.Z), static_cast<float>(ResultYawOnly.Z), 0.001f);
                    });
             });

    Describe("CalculateRightDirection",
             [this]()
             {
                 It("deve calcular direção Right correta para rotação Yaw 0° (direção +Y)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 0.0f, 0.0f);
                        FVector ExpectedDirection(0.0f, 1.0f, 0.0f); // +Y (direita no Unreal)

                        // Act
                        FVector Result = MovementHelpers::CalculateRightDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Right para Yaw 0° deve ter X = 0", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Right para Yaw 0° deve ser +Y", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Right para Yaw 0° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve calcular direção Right correta para rotação Yaw 90° (direção -X)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 90.0f, 0.0f);
                        FVector ExpectedDirection(-1.0f, 0.0f, 0.0f); // -X (esquerda no Unreal quando Yaw = 90°)

                        // Act
                        FVector Result = MovementHelpers::CalculateRightDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Right para Yaw 90° deve ser -X", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Right para Yaw 90° deve ter Y = 0", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Right para Yaw 90° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve calcular direção Right correta para rotação Yaw 180° (direção -Y)",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotation(0.0f, 180.0f, 0.0f);
                        FVector ExpectedDirection(0.0f, -1.0f, 0.0f); // -Y (esquerda no Unreal quando Yaw = 180°)

                        // Act
                        FVector Result = MovementHelpers::CalculateRightDirection(ControlRotation);

                        // Assert
                        TestEqual("Direção Right para Yaw 180° deve ter X = 0", static_cast<float>(Result.X),
                                  static_cast<float>(ExpectedDirection.X), 0.001f);
                        TestEqual("Direção Right para Yaw 180° deve ser -Y", static_cast<float>(Result.Y),
                                  static_cast<float>(ExpectedDirection.Y), 0.001f);
                        TestEqual("Direção Right para Yaw 180° deve ter Z = 0", static_cast<float>(Result.Z),
                                  static_cast<float>(ExpectedDirection.Z), 0.001f);
                    });

                 It("deve ignorar Pitch e Roll, usando apenas Yaw",
                    [this]()
                    {
                        // Arrange
                        FRotator ControlRotationWithPitch(45.0f, 0.0f, 0.0f); // Pitch 45°, Yaw 0°
                        FRotator ControlRotationYawOnly(0.0f, 0.0f, 0.0f);    // Yaw 0° apenas
                        FVector ExpectedDirection(0.0f, 1.0f, 0.0f);          // +Y (mesmo resultado)

                        // Act
                        FVector ResultWithPitch = MovementHelpers::CalculateRightDirection(ControlRotationWithPitch);
                        FVector ResultYawOnly = MovementHelpers::CalculateRightDirection(ControlRotationYawOnly);

                        // Assert
                        TestEqual("Direção Right com Pitch deve ser igual à direção sem Pitch (X)",
                                  static_cast<float>(ResultWithPitch.X), static_cast<float>(ResultYawOnly.X), 0.001f);
                        TestEqual("Direção Right com Pitch deve ser igual à direção sem Pitch (Y)",
                                  static_cast<float>(ResultWithPitch.Y), static_cast<float>(ResultYawOnly.Y), 0.001f);
                        TestEqual("Direção Right com Pitch deve ser igual à direção sem Pitch (Z)",
                                  static_cast<float>(ResultWithPitch.Z), static_cast<float>(ResultYawOnly.Z), 0.001f);
                    });
             });
}

#pragma endregion Test Implementation
