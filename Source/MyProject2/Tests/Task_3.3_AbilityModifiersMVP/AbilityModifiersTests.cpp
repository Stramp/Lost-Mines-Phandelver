// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// Ability Modifiers Tests
// ============================================================================
#pragma region Ability Modifiers Tests

BEGIN_DEFINE_SPEC(AbilityModifiersSpec, "MyProject2.AbilityModifiers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(AbilityModifiersSpec)

void AbilityModifiersSpec::Define()
{
    // ============================================================================
    // CalculateAbilityModifier Tests
    // ============================================================================
    Describe("Issue-3.3/ CalculateAbilityModifier",
             [this]()
             {
                 It("deve calcular modificador correto para score 10 (modificador 0)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 10;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((10 - 10) / 2) = floor(0) = 0
                        TestEqual("Modificador para score 10 deve ser 0", Result, 0);
                    });

                 It("deve calcular modificador correto para score 15 (modificador +2)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 15;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((15 - 10) / 2) = floor(5/2) = floor(2.5) = 2
                        TestEqual("Modificador para score 15 deve ser +2", Result, 2);
                    });

                 It("deve calcular modificador correto para score 8 (modificador -1)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 8;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((8 - 10) / 2) = floor(-2/2) = floor(-1) = -1
                        TestEqual("Modificador para score 8 deve ser -1", Result, -1);
                    });

                 It("deve calcular modificador correto para score 20 (modificador +5)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 20;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((20 - 10) / 2) = floor(10/2) = floor(5) = 5
                        TestEqual("Modificador para score 20 deve ser +5", Result, 5);
                    });

                 It("deve calcular modificador correto para score 1 (modificador -5)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 1;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((1 - 10) / 2) = floor(-9/2) = floor(-4.5) = -5
                        TestEqual("Modificador para score 1 deve ser -5", Result, -5);
                    });

                 It("deve calcular modificador correto para score 30 (modificador +10)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 30;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((30 - 10) / 2) = floor(20/2) = floor(10) = 10
                        TestEqual("Modificador para score 30 deve ser +10", Result, 10);
                    });

                 It("deve calcular modificador correto para score 11 (modificador +0)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 11;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((11 - 10) / 2) = floor(1/2) = floor(0.5) = 0
                        TestEqual("Modificador para score 11 deve ser 0", Result, 0);
                    });

                 It("deve calcular modificador correto para score 12 (modificador +1)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 12;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((12 - 10) / 2) = floor(2/2) = floor(1) = 1
                        TestEqual("Modificador para score 12 deve ser +1", Result, 1);
                    });

                 It("deve calcular modificador correto para score 14 (modificador +2)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 14;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((14 - 10) / 2) = floor(4/2) = floor(2) = 2
                        TestEqual("Modificador para score 14 deve ser +2", Result, 2);
                    });

                 It("deve calcular modificador correto para score 13 (modificador +1)",
                    [this]()
                    {
                        // Arrange
                        int32 Score = 13;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);

                        // Assert
                        // Fórmula D&D 5e: floor((13 - 10) / 2) = floor(3/2) = floor(1.5) = 1
                        TestEqual("Modificador para score 13 deve ser +1", Result, 1);
                    });
             });
}

#pragma endregion Ability Modifiers Tests
