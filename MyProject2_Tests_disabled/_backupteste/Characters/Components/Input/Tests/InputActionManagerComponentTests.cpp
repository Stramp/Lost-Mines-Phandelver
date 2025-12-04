// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Characters/Components/Input/InputActionManagerComponent.h"
#include "Characters/Components/Input/InputActionType.h"
#include "InputAction.h"

#pragma endregion Includes

// ============================================================================
// Test Spec Definition
// ============================================================================
#pragma region Test Spec Definition

BEGIN_DEFINE_SPEC(InputActionManagerComponentSpec, "MyProject2.Characters.Components.Input.InputActionManagerComponent",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
UInputActionManagerComponent *Component;
UInputAction *TestInputAction;
END_DEFINE_SPEC(InputActionManagerComponentSpec)

#pragma endregion Test Spec Definition

// ============================================================================
// Test Implementation
// ============================================================================
#pragma region Test Implementation

void InputActionManagerComponentSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar componente e Input Action de teste
            Component = NewObject<UInputActionManagerComponent>();
            TestInputAction = NewObject<UInputAction>();
        });

    Describe("GetInputAction",
             [this]()
             {
                 It("deve retornar nullptr quando Input Action não está registrada",
                    [this]()
                    {
                        // Arrange: Componente sem Input Actions registradas

                        // Act
                        UInputAction *Result = Component->GetInputAction(EInputActionType::Move);

                        // Assert
                        TestNull("Deve retornar nullptr quando não encontrada", Result);
                    });

                 It("deve retornar Input Action correta quando registrada",
                    [this]()
                    {
                        // Arrange: Registrar Input Action
                        Component->RegisterInputAction(EInputActionType::Move, TestInputAction);

                        // Act
                        UInputAction *Result = Component->GetInputAction(EInputActionType::Move);

                        // Assert
                        TestNotNull("Deve retornar Input Action quando encontrada", Result);
                        TestEqual("Deve retornar a mesma Input Action registrada", Result, TestInputAction);
                    });

                 It("deve retornar Input Action correta para diferentes tipos",
                    [this]()
                    {
                        // Arrange: Registrar múltiplas Input Actions
                        UInputAction *MoveAction = NewObject<UInputAction>();
                        UInputAction *LookAction = NewObject<UInputAction>();

                        Component->RegisterInputAction(EInputActionType::Move, MoveAction);
                        Component->RegisterInputAction(EInputActionType::Look, LookAction);

                        // Act
                        UInputAction *MoveResult = Component->GetInputAction(EInputActionType::Move);
                        UInputAction *LookResult = Component->GetInputAction(EInputActionType::Look);

                        // Assert
                        TestEqual("Move deve retornar MoveAction", MoveResult, MoveAction);
                        TestEqual("Look deve retornar LookAction", LookResult, LookAction);
                    });
             });

    Describe("RegisterInputAction",
             [this]()
             {
                 It("deve registrar Input Action corretamente",
                    [this]()
                    {
                        // Arrange: Componente vazio

                        // Act
                        Component->RegisterInputAction(EInputActionType::Move, TestInputAction);

                        // Assert
                        TestTrue("Deve ter Input Action registrada", Component->HasInputAction(EInputActionType::Move));
                        TestEqual("Deve retornar Input Action registrada",
                                  Component->GetInputAction(EInputActionType::Move), TestInputAction);
                    });

                 It("não deve registrar Input Action quando nullptr",
                    [this]()
                    {
                        // Arrange: Componente vazio

                        // Act
                        Component->RegisterInputAction(EInputActionType::Move, nullptr);

                        // Assert
                        TestFalse("Não deve ter Input Action registrada quando nullptr",
                                  Component->HasInputAction(EInputActionType::Move));
                    });

                 It("deve sobrescrever Input Action existente",
                    [this]()
                    {
                        // Arrange: Registrar Input Action inicial
                        UInputAction *FirstAction = NewObject<UInputAction>();
                        Component->RegisterInputAction(EInputActionType::Move, FirstAction);

                        // Act: Registrar nova Input Action para o mesmo tipo
                        Component->RegisterInputAction(EInputActionType::Move, TestInputAction);

                        // Assert
                        UInputAction *Result = Component->GetInputAction(EInputActionType::Move);
                        TestEqual("Deve retornar a nova Input Action", Result, TestInputAction);
                        TestNotEqual("Não deve retornar a Input Action antiga", Result, FirstAction);
                    });
             });

    Describe("HasInputAction",
             [this]()
             {
                 It("deve retornar false quando Input Action não está registrada",
                    [this]()
                    {
                        // Arrange: Componente sem Input Actions

                        // Act
                        bool Result = Component->HasInputAction(EInputActionType::Move);

                        // Assert
                        TestFalse("Deve retornar false quando não registrada", Result);
                    });

                 It("deve retornar true quando Input Action está registrada",
                    [this]()
                    {
                        // Arrange: Registrar Input Action
                        Component->RegisterInputAction(EInputActionType::Move, TestInputAction);

                        // Act
                        bool Result = Component->HasInputAction(EInputActionType::Move);

                        // Assert
                        TestTrue("Deve retornar true quando registrada", Result);
                    });
             });

    AfterEach(
        [this]()
        {
            // Cleanup
            Component = nullptr;
            TestInputAction = nullptr;
        });
}

#pragma endregion Test Implementation
