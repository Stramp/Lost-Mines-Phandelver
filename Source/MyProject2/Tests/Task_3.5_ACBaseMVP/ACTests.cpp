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
// AC Tests
// ============================================================================
#pragma region AC Tests

BEGIN_DEFINE_SPEC(ACSpec, "MyProject2.AC", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(ACSpec)

void ACSpec::Define()
{
    // ============================================================================
    // CalculateAC Tests
    // ============================================================================
    Describe("Issue-3.5/ CalculateAC",
             [this]()
             {
                 It("deve calcular AC base sem armadura (10 + DEX modifier +2 = 12)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 12 (10 + 2)", Result, 12);
                    });

                 It("deve calcular AC base sem armadura com DEX modifier 0 (AC = 10)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 0;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 10 (10 + 0)", Result, 10);
                    });

                 It("deve calcular AC base sem armadura com DEX modifier negativo (AC = 8)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = -2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 8 (10 + (-2))", Result, 8);
                    });

                 It("deve calcular AC com armadura leve (ACValue 11 + DEX modifier +3 = 14)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 3;
                        int32 ArmorACValue = 11; // Leather Armor
                        FName ArmorType = TEXT("Light");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura leve deve ser 14 (11 + 3)", Result, 14);
                    });

                 It("deve calcular AC com armadura média limitando DEX modifier (ACValue 13 + min(DEX +4, +2) = 15)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 4; // +4, mas limitado a +2
                        int32 ArmorACValue = 13;     // Scale Mail
                        FName ArmorType = TEXT("Medium");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura média deve ser 15 (13 + min(4, 2) = 13 + 2)", Result, 15);
                    });

                 It("deve calcular AC com armadura média usando DEX modifier completo quando menor que +2",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 1; // +1, menor que limite +2
                        int32 ArmorACValue = 13;     // Scale Mail
                        FName ArmorType = TEXT("Medium");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura média deve ser 14 (13 + 1)", Result, 14);
                    });

                 It("deve calcular AC com armadura pesada sem DEX modifier (ACValue 16 = 16)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 3; // Ignorado para armaduras pesadas
                        int32 ArmorACValue = 16;     // Chain Mail
                        FName ArmorType = TEXT("Heavy");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura pesada deve ser 16 (sem DEX modifier)", Result, 16);
                    });

                 It("deve calcular AC com escudo adicionando +2 (AC base 12 + escudo = 14)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 2;
                        bool bHasShield = true;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, 0, NAME_None, bHasShield);

                        // Assert
                        TestEqual("AC com escudo deve ser 14 (10 + 2 + 2)", Result, 14);
                    });

                 It("deve calcular AC com armadura leve e escudo (ACValue 11 + DEX +3 + escudo +2 = 16)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 3;
                        int32 ArmorACValue = 11; // Leather Armor
                        FName ArmorType = TEXT("Light");
                        bool bHasShield = true;

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                        // Assert
                        TestEqual("AC com armadura leve e escudo deve ser 16 (11 + 3 + 2)", Result, 16);
                    });

                 It("deve calcular AC com armadura média e escudo (ACValue 13 + min(DEX +4, +2) + escudo +2 = 17)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 4; // Limitado a +2
                        int32 ArmorACValue = 13;     // Scale Mail
                        FName ArmorType = TEXT("Medium");
                        bool bHasShield = true;

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                        // Assert
                        TestEqual("AC com armadura média e escudo deve ser 17 (13 + 2 + 2)", Result, 17);
                    });

                 It("deve calcular AC com armadura pesada e escudo (ACValue 16 + escudo +2 = 18)",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 3; // Ignorado
                        int32 ArmorACValue = 16;     // Chain Mail
                        FName ArmorType = TEXT("Heavy");
                        bool bHasShield = true;

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType, bHasShield);

                        // Assert
                        TestEqual("AC com armadura pesada e escudo deve ser 18 (16 + 2)", Result, 18);
                    });

                 It("deve usar AC base como fallback para tipo de armadura desconhecido",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 2;
                        int32 ArmorACValue = 10;
                        FName ArmorType = TEXT("Unknown"); // Tipo desconhecido

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        // Deve usar AC base (10 + DEX modifier) como fallback
                        TestEqual("AC com tipo desconhecido deve usar AC base (10 + 2)", Result, 12);
                    });

                 It("deve usar AC base quando ArmorACValue é 0 mesmo com tipo definido",
                    [this]()
                    {
                        // Arrange
                        int32 DexterityModifier = 2;
                        int32 ArmorACValue = 0; // Zero significa sem armadura
                        FName ArmorType = TEXT("Light");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        // Deve usar AC base quando ArmorACValue é 0
                        TestEqual("AC com ArmorACValue 0 deve usar AC base (10 + 2)", Result, 12);
                    });
             });
}

#pragma endregion AC Tests
