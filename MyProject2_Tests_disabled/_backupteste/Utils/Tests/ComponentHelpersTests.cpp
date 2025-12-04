// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/ComponentHelpers.h"
#include "Characters/Components/CharacterDataComponent.h"
#include "GameFramework/Actor.h"

#pragma endregion Includes

// ============================================================================
// ComponentHelpers Tests
// ============================================================================
#pragma region ComponentHelpers Tests

BEGIN_DEFINE_SPEC(ComponentHelpersSpec, "MyProject2.Utils.ComponentHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

AActor *TestActor;
UCharacterDataComponent *TestComponent;

END_DEFINE_SPEC(ComponentHelpersSpec)

void ComponentHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Actor e Component para cada teste
            // Nota: FindComponentByClass funciona mesmo sem adicionar explicitamente
            // se o componente foi criado com o Owner correto
            TestActor = NewObject<AActor>();
            TestComponent = NewObject<UCharacterDataComponent>(TestActor);
        });

    AfterEach(
        [this]()
        {
            // Cleanup após cada teste
            if (TestActor)
            {
                TestActor->ConditionalBeginDestroy();
            }
        });

    Describe("FindCharacterDataComponent",
             [this]()
             {
                 It("should return component when owner has it",
                    [this]()
                    {
                        // Act
                        UCharacterDataComponent *Result = ComponentHelpers::FindCharacterDataComponent(TestActor);

                        // Assert
                        TestNotNull("Result should not be null", Result);
                        TestEqual("Result should be the same component", Result, TestComponent);
                    });

                 It("should return nullptr when owner is null",
                    [this]()
                    {
                        // Act
                        UCharacterDataComponent *Result = ComponentHelpers::FindCharacterDataComponent(nullptr);

                        // Assert
                        TestNull("Result should be null", Result);
                    });

                 It("should return nullptr when owner has no component",
                    [this]()
                    {
                        // Arrange: Criar Actor sem componente
                        AActor *ActorWithoutComponent = NewObject<AActor>();

                        // Act
                        UCharacterDataComponent *Result =
                            ComponentHelpers::FindCharacterDataComponent(ActorWithoutComponent);

                        // Assert
                        TestNull("Result should be null", Result);

                        // Cleanup
                        ActorWithoutComponent->ConditionalBeginDestroy();
                    });
             });
}

#pragma endregion ComponentHelpers Tests
