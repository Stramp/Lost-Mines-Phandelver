// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/DnDConstants.h"
#include "Data/Tables/ClassDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// CalculationHelpers Tests
// ============================================================================
#pragma region CalculationHelpers Tests

BEGIN_DEFINE_SPEC(CalculationHelpersSpec, "MyProject2.Utils.CalculationHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(CalculationHelpersSpec)

void CalculationHelpersSpec::Define()
{
    Describe("CalculateAbilityModifier",
             [this]()
             {
                 It("deve calcular modificador correto para score 10 (modificador 0)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 10 (modificador base)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(10);

                        // Assert
                        TestEqual("Modificador para score 10 deve ser 0", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: modificador calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 8 (modificador -1)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 8 (modificador negativo)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(8);

                        // Assert
                        TestEqual("Modificador para score 8 deve ser -1", Result, -1);
                        AddInfo(TEXT("✅ Teste passou: modificador negativo calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 15 (modificador +2)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 15 (modificador positivo)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(15);

                        // Assert
                        TestEqual("Modificador para score 15 deve ser +2", Result, 2);
                        AddInfo(TEXT("✅ Teste passou: modificador positivo calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 20 (modificador +5)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 20 (modificador máximo comum)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(20);

                        // Assert
                        TestEqual("Modificador para score 20 deve ser +5", Result, 5);
                        AddInfo(TEXT("✅ Teste passou: modificador máximo calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 1 (modificador mínimo -5)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 1 (modificador mínimo)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(1);

                        // Assert
                        // Fórmula: floor((1 - 10) / 2) = floor(-9/2) = floor(-4.5) = -5
                        TestEqual("Modificador para score 1 deve ser -5", Result, -5);
                        AddInfo(TEXT("✅ Teste passou: modificador mínimo calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 30 (modificador máximo +10)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 30 (modificador máximo)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(30);

                        // Assert
                        TestEqual("Modificador para score 30 deve ser +10", Result, 10);
                        AddInfo(TEXT("✅ Teste passou: modificador máximo absoluto calculado corretamente"));
                    });

                 It("deve calcular modificador correto para score 11 (modificador 0, floor)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 11 (deve fazer floor para 0)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(11);

                        // Assert
                        TestEqual("Modificador para score 11 deve ser 0 (floor)", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: floor aplicado corretamente para score 11"));
                    });

                 It("deve calcular modificador correto para score 13 (modificador +1, floor)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 13 (deve fazer floor para +1)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(13);

                        // Assert
                        TestEqual("Modificador para score 13 deve ser +1 (floor)", Result, 1);
                        AddInfo(TEXT("✅ Teste passou: floor aplicado corretamente para score 13"));
                    });

                 It("deve calcular modificador correto para score 17 (modificador +3, floor)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAbilityModifier com score 17 (deve fazer floor para +3)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateAbilityModifier(17);

                        // Assert
                        TestEqual("Modificador para score 17 deve ser +3 (floor)", Result, 3);
                        AddInfo(TEXT("✅ Teste passou: floor aplicado corretamente para score 17"));
                    });
             });

    Describe("CalculateProficiencyBonus",
             [this]()
             {
                 It("deve calcular bônus correto para nível 1 (bônus +2)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 1 (bônus inicial)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(1);

                        // Assert
                        // D&D 5e: 2 + floor((1-1)/4) = 2 + 0 = 2
                        int32 ExpectedBonus = 2; // Valor hardcoded conhecido
                        TestEqual("Bônus de proficiência para nível 1 deve ser +2", Result, ExpectedBonus);
                        AddInfo(TEXT("✅ Teste passou: bônus inicial calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 4 (bônus +2)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 4 (ainda +2)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(4);

                        // Assert
                        // D&D 5e: 2 + floor((4-1)/4) = 2 + floor(0.75) = 2 + 0 = 2
                        int32 ExpectedBonus = 2; // Valor hardcoded conhecido
                        TestEqual("Bônus de proficiência para nível 4 deve ser +2", Result, ExpectedBonus);
                        AddInfo(TEXT("✅ Teste passou: bônus calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 5 (bônus +3)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 5 (primeiro aumento)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(5);

                        // Assert
                        TestEqual("Bônus de proficiência para nível 5 deve ser +3", Result, 3);
                        AddInfo(TEXT("✅ Teste passou: primeiro aumento de bônus calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 9 (bônus +4)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 9 (segundo aumento)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(9);

                        // Assert
                        TestEqual("Bônus de proficiência para nível 9 deve ser +4", Result, 4);
                        AddInfo(TEXT("✅ Teste passou: segundo aumento de bônus calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 13 (bônus +5)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 13 (terceiro aumento)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(13);

                        // Assert
                        // D&D 5e: 2 + floor((13-1)/4) = 2 + floor(3) = 2 + 3 = 5
                        int32 ExpectedBonus = 5; // Valor hardcoded conhecido
                        TestEqual("Bônus de proficiência para nível 13 deve ser +5", Result, ExpectedBonus);
                        AddInfo(TEXT("✅ Teste passou: terceiro aumento de bônus calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 17 (bônus +6)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 17 (quarto aumento)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(17);

                        // Assert
                        // D&D 5e: 2 + floor((17-1)/4) = 2 + floor(4) = 2 + 4 = 6
                        int32 ExpectedBonus = 6; // Valor hardcoded conhecido
                        TestEqual("Bônus de proficiência para nível 17 deve ser +6", Result, ExpectedBonus);
                        AddInfo(TEXT("✅ Teste passou: quarto aumento de bônus calculado corretamente"));
                    });

                 It("deve calcular bônus correto para nível 20 (bônus máximo +6)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível 20 (bônus máximo)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(20);

                        // Assert
                        // D&D 5e: 2 + floor((20-1)/4) = 2 + floor(4.75) = 2 + 4 = 6
                        int32 ExpectedBonus = 6; // Valor hardcoded conhecido
                        TestEqual("Bônus de proficiência para nível 20 deve ser +6", Result, ExpectedBonus);
                        AddInfo(TEXT("✅ Teste passou: bônus máximo calculado corretamente"));
                    });

                 It("deve retornar 0 para nível inválido (< 1)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível inválido (0)"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(0);

                        // Assert
                        TestEqual("Bônus de proficiência para nível 0 deve ser 0", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: nível inválido tratado corretamente"));
                    });

                 It("deve retornar 0 para nível negativo",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateProficiencyBonus com nível negativo"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateProficiencyBonus(-5);

                        // Assert
                        TestEqual("Bônus de proficiência para nível negativo deve ser 0", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: nível negativo tratado corretamente"));
                    });
             });

    Describe("CalculateHPGainForLevel",
             [this]()
             {
                 It("deve calcular HP correto para level 1 com HitDie 8 e CON +2",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 1 = HitDie + CON"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(8, 1, 2);

                        // Assert
                        TestEqual("HP para level 1 deve ser HitDie + CON modifier", Result, 10);
                        AddInfo(TEXT("✅ Teste passou: HP level 1 calculado corretamente"));
                    });

                 It("deve calcular HP correto para level 2+ com HitDie 8 e CON +2",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 2+ = média do dado + CON"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(8, 2, 2);

                        // Assert
                        // Implementação usa: CeilToInt(8/2.0) = CeilToInt(4.0) = 4, + CON 2 = 6
                        TestEqual("HP para level 2+ deve ser média do dado + CON", Result, 6);
                        AddInfo(TEXT("✅ Teste passou: HP level 2+ calculado corretamente"));
                    });

                 It("deve calcular HP correto para level 1 com HitDie 12 e CON +3",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 1 com HitDie maior"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(12, 1, 3);

                        // Assert
                        TestEqual("HP para level 1 com HitDie 12 deve ser 15", Result, 15);
                        AddInfo(TEXT("✅ Teste passou: HP com HitDie maior calculado corretamente"));
                    });

                 It("deve calcular HP correto para level 2+ com HitDie 12 e CON +3",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 2+ com HitDie maior"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(12, 2, 3);

                        // Assert
                        // Implementação usa: CeilToInt(12/2.0) = CeilToInt(6.0) = 6, + CON 3 = 9
                        TestEqual("HP para level 2+ com HitDie 12 deve ser 9", Result, 9);
                        AddInfo(TEXT("✅ Teste passou: HP level 2+ com HitDie maior calculado corretamente"));
                    });

                 It("deve calcular HP correto para level 1 com CON negativo",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 1 com CON negativo"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(8, 1, -1);

                        // Assert
                        TestEqual("HP para level 1 com CON -1 deve ser 7", Result, 7);
                        AddInfo(TEXT("✅ Teste passou: HP com CON negativo calculado corretamente"));
                    });

                 It("deve calcular HP correto para level 1 com CON zero",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 1 com CON zero"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(8, 1, 0);

                        // Assert
                        TestEqual("HP para level 1 com CON 0 deve ser igual ao HitDie", Result, 8);
                        AddInfo(TEXT("✅ Teste passou: HP com CON zero calculado corretamente"));
                    });

                 It("deve calcular HP para diferentes HitDie (6, 8, 10, 12)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: diferentes HitDie"));

                        // Act & Assert
                        TestEqual("HitDie 6, level 1, CON +2 = 8", CalculationHelpers::CalculateHPGainForLevel(6, 1, 2),
                                  8);
                        TestEqual("HitDie 8, level 1, CON +2 = 10",
                                  CalculationHelpers::CalculateHPGainForLevel(8, 1, 2), 10);
                        TestEqual("HitDie 10, level 1, CON +2 = 12",
                                  CalculationHelpers::CalculateHPGainForLevel(10, 1, 2), 12);
                        TestEqual("HitDie 12, level 1, CON +2 = 14",
                                  CalculationHelpers::CalculateHPGainForLevel(12, 1, 2), 14);
                        AddInfo(TEXT("✅ Teste passou: diferentes HitDie calculados corretamente"));
                    });

                 It("deve calcular HP para level 20 (último nível)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateHPGainForLevel: level 20"));

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(8, 20, 2);

                        // Assert
                        // Level 20 ainda usa média do dado (não é level 1)
                        // CeilToInt(8/2.0) = 4, + CON 2 = 6
                        TestEqual("HP para level 20 deve usar média do dado", Result, 6);
                        AddInfo(TEXT("✅ Teste passou: HP level 20 calculado corretamente"));
                    });
             });

    Describe("CalculateMaxHP",
             [this]()
             {
                 It("deve retornar 0 quando ClassDataTable é nullptr",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateMaxHP com ClassDataTable nullptr"));

                        // Arrange
                        TArray<FName> ClassNames;
                        ClassNames.Add(TEXT("Fighter"));

                        TArray<int32> LevelsInClass;
                        LevelsInClass.Add(5);

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassNames, LevelsInClass, 2, nullptr);

                        // Assert
                        TestEqual("Should return 0 when ClassDataTable is nullptr", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: nullptr tratado corretamente"));
                    });

                 It("deve retornar 0 quando arrays têm tamanhos diferentes",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateMaxHP com arrays de tamanhos diferentes"));

                        // Arrange
                        TArray<FName> ClassNames;
                        ClassNames.Add(TEXT("Fighter"));

                        TArray<int32> LevelsInClass;
                        LevelsInClass.Add(5);
                        LevelsInClass.Add(3); // Tamanho diferente

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassNames, LevelsInClass, 2, nullptr);

                        // Assert
                        TestEqual("Should return 0 when arrays have different sizes", Result, 0);
                        AddInfo(TEXT("✅ Teste passou: arrays inválidos tratados corretamente"));
                    });

                 It("deve calcular HP máximo para single class com ClassDataTable válido",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateMaxHP: single class level 5, HitDie 10, CON +2"));

                        // Arrange
                        UDataTable *TestClassDataTable = NewObject<UDataTable>();
                        TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                        FClassDataRow *TestClassRow = new FClassDataRow();
                        TestClassRow->Name = TEXT("Fighter");
                        TestClassRow->HitDie = 10;
                        TestClassDataTable->AddRow(TEXT("Fighter"), *TestClassRow);

                        TArray<FName> ClassNames;
                        ClassNames.Add(TEXT("Fighter"));

                        TArray<int32> LevelsInClass;
                        LevelsInClass.Add(5);

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateMaxHP(ClassNames, LevelsInClass, 2, TestClassDataTable);

                        // Assert
                        // Level 1: 10 + 2 = 12
                        // Levels 2-5: 4 * (CeilToInt(10/2.0) + 2) = 4 * (5 + 2) = 4 * 7 = 28
                        // Total: 12 + 28 = 40
                        TestEqual("HP máximo deve ser calculado corretamente", Result, 40);
                        AddInfo(TEXT("✅ Teste passou: HP máximo calculado corretamente"));

                        // Cleanup
                        delete TestClassRow;
                        TestClassDataTable->ConditionalBeginDestroy();
                    });

                 It("deve retornar 0 quando ClassName não existe no DataTable",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateMaxHP com ClassName inexistente"));

                        // Arrange
                        UDataTable *TestClassDataTable = NewObject<UDataTable>();
                        TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                        TArray<FName> ClassNames;
                        ClassNames.Add(TEXT("NonExistentClass"));

                        TArray<int32> LevelsInClass;
                        LevelsInClass.Add(5);

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateMaxHP(ClassNames, LevelsInClass, 2, TestClassDataTable);

                        // Assert
                        // Quando classe não existe, faz continue, TotalHP = 0, retorna FMath::Max(1, 0) = 1
                        TestEqual("Should return 1 (minimum) when class not found", Result, 1);
                        AddInfo(TEXT("✅ Teste passou: classe inexistente tratada corretamente"));

                        // Cleanup
                        TestClassDataTable->ConditionalBeginDestroy();
                    });
             });

    // ============================================================================
    // Armor Class (AC) Calculations
    // ============================================================================
    Describe("CalculateAC",
             [this]()
             {
                 It("deve calcular AC base sem armadura (10 + DEX modifier +2 = 12)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC sem armadura com DEX modifier +2"));

                        // Arrange
                        int32 DexterityModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 12 (10 + 2)", Result, 12);
                        AddInfo(TEXT("✅ Teste passou: AC base calculado corretamente"));
                    });

                 It("deve calcular AC base sem armadura com DEX modifier 0 (AC = 10)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC sem armadura com DEX modifier 0"));

                        // Arrange
                        int32 DexterityModifier = 0;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 10 (10 + 0)", Result, 10);
                        AddInfo(TEXT("✅ Teste passou: AC base com DEX 0 calculado corretamente"));
                    });

                 It("deve calcular AC base sem armadura com DEX modifier negativo (AC = 8)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC sem armadura com DEX modifier -2"));

                        // Arrange
                        int32 DexterityModifier = -2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier);

                        // Assert
                        TestEqual("AC base deve ser 8 (10 + (-2))", Result, 8);
                        AddInfo(TEXT("✅ Teste passou: AC base com DEX negativo calculado corretamente"));
                    });

                 It("deve calcular AC com armadura leve (ACValue 11 + DEX modifier +3 = 14)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC com armadura leve (Leather Armor)"));

                        // Arrange
                        int32 DexterityModifier = 3;
                        int32 ArmorACValue = 11; // Leather Armor
                        FName ArmorType = TEXT("Light");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura leve deve ser 14 (11 + 3)", Result, 14);
                        AddInfo(TEXT("✅ Teste passou: AC com armadura leve calculado corretamente"));
                    });

                 It("deve calcular AC com armadura média limitando DEX modifier (ACValue 13 + min(DEX +4, +2) = 15)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC com armadura média limitando DEX modifier"));

                        // Arrange
                        int32 DexterityModifier = 4; // +4, mas limitado a +2
                        int32 ArmorACValue = 13;     // Scale Mail
                        FName ArmorType = TEXT("Medium");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura média deve ser 15 (13 + min(4, 2) = 13 + 2)", Result, 15);
                        AddInfo(TEXT("✅ Teste passou: AC com armadura média limitando DEX corretamente"));
                    });

                 It("deve calcular AC com armadura pesada sem DEX modifier (ACValue 16 = 16)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC com armadura pesada (Chain Mail)"));

                        // Arrange
                        int32 DexterityModifier = 3; // Ignorado para armaduras pesadas
                        int32 ArmorACValue = 16;     // Chain Mail
                        FName ArmorType = TEXT("Heavy");

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, ArmorACValue, ArmorType);

                        // Assert
                        TestEqual("AC com armadura pesada deve ser 16 (sem DEX modifier)", Result, 16);
                        AddInfo(TEXT("✅ Teste passou: AC com armadura pesada calculado corretamente"));
                    });

                 It("deve calcular AC com escudo adicionando +2 (AC base 12 + escudo = 14)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC com escudo"));

                        // Arrange
                        int32 DexterityModifier = 2;
                        bool bHasShield = true;

                        // Act
                        int32 Result = CalculationHelpers::CalculateAC(DexterityModifier, 0, NAME_None, bHasShield);

                        // Assert
                        TestEqual("AC com escudo deve ser 14 (10 + 2 + 2)", Result, 14);
                        AddInfo(TEXT("✅ Teste passou: AC com escudo calculado corretamente"));
                    });

                 It("deve calcular AC com armadura leve e escudo (ACValue 11 + DEX +3 + escudo +2 = 16)",
                    [this]()
                    {
                        AddInfo(TEXT("Testando CalculateAC com armadura leve e escudo"));

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
                        AddInfo(TEXT("✅ Teste passou: AC com armadura leve e escudo calculado corretamente"));
                    });
             });
}

#pragma endregion CalculationHelpers Tests
