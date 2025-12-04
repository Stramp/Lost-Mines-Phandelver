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
// Proficiency Bonus Tests
// ============================================================================
#pragma region Proficiency Bonus Tests

BEGIN_DEFINE_SPEC(ProficiencyBonusSpec, "MyProject2.ProficiencyBonus",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(ProficiencyBonusSpec)

void ProficiencyBonusSpec::Define()
{
    // ============================================================================
    // CalculateProficiencyBonus Tests
    // ============================================================================
    Describe("Issue-3.4/ CalculateProficiencyBonus",
             [this]()
             {
                 It("deve calcular bônus correto para nível 1 (bônus +2)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 1;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((1 - 1) / 4) = 2 + 0 = 2
                        TestEqual("Bônus de proficiência para nível 1 deve ser +2", Result, 2);
                    });

                 It("deve calcular bônus correto para nível 4 (bônus +2)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 4;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((4 - 1) / 4) = 2 + floor(3/4) = 2 + 0 = 2
                        TestEqual("Bônus de proficiência para nível 4 deve ser +2", Result, 2);
                    });

                 It("deve calcular bônus correto para nível 5 (bônus +3)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 5;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((5 - 1) / 4) = 2 + floor(4/4) = 2 + 1 = 3
                        TestEqual("Bônus de proficiência para nível 5 deve ser +3", Result, 3);
                    });

                 It("deve calcular bônus correto para nível 8 (bônus +3)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 8;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((8 - 1) / 4) = 2 + floor(7/4) = 2 + 1 = 3
                        TestEqual("Bônus de proficiência para nível 8 deve ser +3", Result, 3);
                    });

                 It("deve calcular bônus correto para nível 9 (bônus +4)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 9;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((9 - 1) / 4) = 2 + floor(8/4) = 2 + 2 = 4
                        TestEqual("Bônus de proficiência para nível 9 deve ser +4", Result, 4);
                    });

                 It("deve calcular bônus correto para nível 12 (bônus +4)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 12;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((12 - 1) / 4) = 2 + floor(11/4) = 2 + 2 = 4
                        TestEqual("Bônus de proficiência para nível 12 deve ser +4", Result, 4);
                    });

                 It("deve calcular bônus correto para nível 13 (bônus +5)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 13;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((13 - 1) / 4) = 2 + floor(12/4) = 2 + 3 = 5
                        TestEqual("Bônus de proficiência para nível 13 deve ser +5", Result, 5);
                    });

                 It("deve calcular bônus correto para nível 16 (bônus +5)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 16;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((16 - 1) / 4) = 2 + floor(15/4) = 2 + 3 = 5
                        TestEqual("Bônus de proficiência para nível 16 deve ser +5", Result, 5);
                    });

                 It("deve calcular bônus correto para nível 17 (bônus +6)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 17;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((17 - 1) / 4) = 2 + floor(16/4) = 2 + 4 = 6
                        TestEqual("Bônus de proficiência para nível 17 deve ser +6", Result, 6);
                    });

                 It("deve calcular bônus correto para nível 20 (bônus +6)",
                    [this]()
                    {
                        // Arrange
                        int32 Level = 20;

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(Level);

                        // Assert
                        // Fórmula D&D 5e: 2 + floor((20 - 1) / 4) = 2 + floor(19/4) = 2 + 4 = 6
                        TestEqual("Bônus de proficiência para nível 20 deve ser +6", Result, 6);
                    });
             });
}

#pragma endregion Proficiency Bonus Tests
