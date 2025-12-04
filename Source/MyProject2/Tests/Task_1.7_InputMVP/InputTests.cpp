// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Components/Input/InputActionManagerComponent.h"
#include "Characters/Components/Input/InputActionType.h"
#include "Characters/Helpers/MovementHelpers.h"
#include "InputAction.h"

#pragma endregion Includes

// ============================================================================
// Input Tests
// ============================================================================
#pragma region Input Tests

BEGIN_DEFINE_SPEC(InputSpec, "MyProject2.Input",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(InputSpec)

void InputSpec::Define()
{
    // ============================================================================
    // InputActionManagerComponent Tests
    // ============================================================================
    Describe(
        "Issue-1.7/ InputActionManagerComponent",
        [this]()
        {
            It("deve criar UInputActionManagerComponent sem crash",
               [this]()
               {
                   // Arrange & Act
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());

                   // Assert
                   TestNotNull("Component deve ser criado", Component);
                   TestTrue("UInputActionManagerComponent criado sem crash", Component != nullptr);
               });

            It("deve retornar nullptr quando GetInputAction para tipo não registrado",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());

                   // Act
                   UInputAction *Result = Component->GetInputAction(EInputActionType::Move);

                   // Assert
                   TestNull("GetInputAction deve retornar nullptr quando não registrado", Result);
               });

            It("deve retornar false quando HasInputAction para tipo não registrado",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());

                   // Act
                   bool bHasAction = Component->HasInputAction(EInputActionType::Move);

                   // Assert
                   TestFalse("HasInputAction deve retornar false quando não registrado", bHasAction);
               });

            It("deve registrar InputAction e retornar corretamente",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());
                   UInputAction *TestInputAction = NewObject<UInputAction>(GetTransientPackage());

                   // Act
                   Component->RegisterInputAction(EInputActionType::Move, TestInputAction);

                   // Assert
                   UInputAction *Result = Component->GetInputAction(EInputActionType::Move);
                   TestNotNull("GetInputAction deve retornar InputAction registrado", Result);
                   TestEqual("InputAction retornado deve ser o mesmo registrado", Result, TestInputAction);
                   TestTrue("HasInputAction deve retornar true após registro",
                            Component->HasInputAction(EInputActionType::Move));
               });

            It("deve registrar múltiplas InputActions",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());
                   UInputAction *MoveAction = NewObject<UInputAction>(GetTransientPackage());
                   UInputAction *LookAction = NewObject<UInputAction>(GetTransientPackage());

                   // Act
                   Component->RegisterInputAction(EInputActionType::Move, MoveAction);
                   Component->RegisterInputAction(EInputActionType::Look, LookAction);

                   // Assert
                   TestNotNull("Move Action deve estar registrada", Component->GetInputAction(EInputActionType::Move));
                   TestNotNull("Look Action deve estar registrada", Component->GetInputAction(EInputActionType::Look));
                   TestEqual("Move Action deve ser a correta", Component->GetInputAction(EInputActionType::Move),
                             MoveAction);
                   TestEqual("Look Action deve ser a correta", Component->GetInputAction(EInputActionType::Look),
                             LookAction);
               });

            It("deve ignorar RegisterInputAction com nullptr",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());

                   // Act
                   Component->RegisterInputAction(EInputActionType::Move, nullptr);

                   // Assert
                   // Não deve crashar e não deve registrar
                   TestNull("GetInputAction deve retornar nullptr após registrar nullptr",
                            Component->GetInputAction(EInputActionType::Move));
                   TestFalse("HasInputAction deve retornar false após registrar nullptr",
                             Component->HasInputAction(EInputActionType::Move));
               });

            It("deve sobrescrever InputAction existente",
               [this]()
               {
                   // Arrange
                   UInputActionManagerComponent *Component =
                       NewObject<UInputActionManagerComponent>(GetTransientPackage());
                   UInputAction *FirstAction = NewObject<UInputAction>(GetTransientPackage());
                   UInputAction *SecondAction = NewObject<UInputAction>(GetTransientPackage());

                   // Act
                   Component->RegisterInputAction(EInputActionType::Move, FirstAction);
                   Component->RegisterInputAction(EInputActionType::Move, SecondAction);

                   // Assert
                   UInputAction *Result = Component->GetInputAction(EInputActionType::Move);
                   TestNotNull("GetInputAction deve retornar InputAction após sobrescrever", Result);
                   TestEqual("InputAction retornado deve ser o segundo (sobrescrito)", Result, SecondAction);
               });
        });

    // ============================================================================
    // EInputActionType Enum Tests
    // ============================================================================
    Describe("Issue-1.7/ EInputActionType",
             [this]()
             {
                 It("deve ter valores de enum corretos",
                    [this]()
                    {
                        // Arrange & Act & Assert
                        // Valida que os valores do enum existem
                        EInputActionType MoveType = EInputActionType::Move;
                        EInputActionType LookType = EInputActionType::Look;
                        EInputActionType ToggleType = EInputActionType::ToggleRotationMode;

                        // Apenas valida que não crasha ao acessar
                        TestTrue("EInputActionType::Move deve existir", true);
                        TestTrue("EInputActionType::Look deve existir", true);
                        TestTrue("EInputActionType::ToggleRotationMode deve existir", true);

                        // Valida que são diferentes
                        TestNotEqual("Move e Look devem ser diferentes", MoveType, LookType);
                        TestNotEqual("Move e ToggleRotationMode devem ser diferentes", MoveType, ToggleType);
                        TestNotEqual("Look e ToggleRotationMode devem ser diferentes", LookType, ToggleType);
                    });
             });

    // ============================================================================
    // MovementHelpers Tests
    // ============================================================================
    Describe("Issue-1.7/ MovementHelpers",
             [this]()
             {
                 It("deve extrair rotação Yaw corretamente",
                    [this]()
                    {
                        // Arrange
                        FRotator TestRotation(45.0f, 90.0f, 30.0f); // Pitch=45, Yaw=90, Roll=30

                        // Act
                        FRotator Result = MovementHelpers::ExtractYawRotation(TestRotation);

                        // Assert
                        TestTrue("Yaw deve ser preservado", FMath::IsNearlyEqual(Result.Yaw, 90.0, 0.01));
                        TestTrue("Pitch deve ser 0", FMath::IsNearlyEqual(Result.Pitch, 0.0, 0.01));
                        TestTrue("Roll deve ser 0", FMath::IsNearlyEqual(Result.Roll, 0.0, 0.01));
                    });

                 It("deve calcular direção Forward corretamente",
                    [this]()
                    {
                        // Arrange
                        FRotator TestRotation(0.0f, 0.0f, 0.0f); // Olhando para frente (Yaw=0)

                        // Act
                        FVector Result = MovementHelpers::CalculateForwardDirection(TestRotation);

                        // Assert
                        // Forward deve ser aproximadamente (1, 0, 0) quando Yaw=0
                        TestTrue("Forward X deve ser aproximadamente 1.0", FMath::IsNearlyEqual(Result.X, 1.0f, 0.01f));
                        TestTrue("Forward Y deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.Y, 0.0f, 0.01f));
                        TestTrue("Forward Z deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.Z, 0.0f, 0.01f));
                    });

                 It("deve calcular direção Right corretamente",
                    [this]()
                    {
                        // Arrange
                        FRotator TestRotation(0.0f, 0.0f, 0.0f); // Olhando para frente (Yaw=0)

                        // Act
                        FVector Result = MovementHelpers::CalculateRightDirection(TestRotation);

                        // Assert
                        // Right deve ser aproximadamente (0, 1, 0) quando Yaw=0
                        TestTrue("Right X deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.X, 0.0f, 0.01f));
                        TestTrue("Right Y deve ser aproximadamente 1.0", FMath::IsNearlyEqual(Result.Y, 1.0f, 0.01f));
                        TestTrue("Right Z deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.Z, 0.0f, 0.01f));
                    });

                 It("deve calcular direção Forward com rotação Yaw=90",
                    [this]()
                    {
                        // Arrange
                        FRotator TestRotation(0.0f, 90.0f, 0.0f); // Olhando para direita (Yaw=90)

                        // Act
                        FVector Result = MovementHelpers::CalculateForwardDirection(TestRotation);

                        // Assert
                        // Forward deve ser aproximadamente (0, 1, 0) quando Yaw=90
                        TestTrue("Forward X deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.X, 0.0f, 0.01f));
                        TestTrue("Forward Y deve ser aproximadamente 1.0", FMath::IsNearlyEqual(Result.Y, 1.0f, 0.01f));
                        TestTrue("Forward Z deve ser aproximadamente 0.0", FMath::IsNearlyEqual(Result.Z, 0.0f, 0.01f));
                    });
             });
}

#pragma endregion Input Tests
