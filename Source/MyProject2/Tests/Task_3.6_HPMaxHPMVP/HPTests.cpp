// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/CalculationHelpers.h"
#include "Utils/DnDConstants.h"
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/ClassDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// HP Tests
// ============================================================================
#pragma region HP Tests

BEGIN_DEFINE_SPEC(HPSpec, "MyProject2.HP", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
UDataTable *RealClassDataTable;
END_DEFINE_SPEC(HPSpec)

void HPSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Carrega ClassDataTable real do Content usando LoadObject
            RealClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DataTable/ClassDataTable"));
        });

    // ============================================================================
    // CalculateHPGainForLevel Tests
    // ============================================================================
    Describe("Issue-3.6/ CalculateHPGainForLevel",
             [this]()
             {
                 It("deve calcular HP nível 1 com HitDie 10 e CON modifier +2 (HP = 12)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 10; // Fighter, Paladin, Ranger
                        int32 Level = 1;
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 1 = HitDie + CON modifier = 10 + 2 = 12
                        TestEqual("HP nível 1 deve ser 12 (10 + 2)", Result, 12);
                    });

                 It("deve calcular HP nível 1 com HitDie 6 e CON modifier 0 (HP = 6)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 6; // Wizard, Sorcerer
                        int32 Level = 1;
                        int32 ConstitutionModifier = 0;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 1 = HitDie + CON modifier = 6 + 0 = 6
                        TestEqual("HP nível 1 deve ser 6 (6 + 0)", Result, 6);
                    });

                 It("deve calcular HP nível 1 com HitDie 12 e CON modifier -1 (HP mínimo = 1)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 12; // Barbarian
                        int32 Level = 1;
                        int32 ConstitutionModifier = -1;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 1 = HitDie + CON modifier = 12 + (-1) = 11
                        // Mas HP nunca pode ser menor que MIN_HP (1)
                        TestEqual("HP nível 1 com CON negativo deve respeitar mínimo de 1", Result, 11);
                    });

                 It("deve calcular HP nível 2 com HitDie 10 e CON modifier +2 (HP = 7)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 10; // Fighter, Paladin, Ranger
                        int32 Level = 2;
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 2+ = ceil(HitDie/2) + CON modifier = ceil(10/2) + 2 = 5 + 2 = 7
                        TestEqual("HP nível 2 deve ser 7 (ceil(10/2) + 2)", Result, 7);
                    });

                 It("deve calcular HP nível 3 com HitDie 8 e CON modifier +1 (HP = 5)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 8; // Bard, Cleric, Druid, Monk, Rogue, Warlock
                        int32 Level = 3;
                        int32 ConstitutionModifier = 1;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 2+ = ceil(HitDie/2) + CON modifier = ceil(8/2) + 1 = 4 + 1 = 5
                        TestEqual("HP nível 3 deve ser 5 (ceil(8/2) + 1)", Result, 5);
                    });

                 It("deve calcular HP nível 2 com HitDie 6 e CON modifier -2 (HP mínimo = 1)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 6; // Wizard, Sorcerer
                        int32 Level = 2;
                        int32 ConstitutionModifier = -2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 2+ = ceil(HitDie/2) + CON modifier = ceil(6/2) + (-2) = 3 + (-2) = 1
                        // HP nunca pode ser menor que MIN_HP (1)
                        TestEqual("HP nível 2 com CON negativo deve respeitar mínimo de 1", Result, 1);
                    });

                 It("deve calcular HP nível 5 com HitDie 12 e CON modifier +3 (HP = 9)",
                    [this]()
                    {
                        // Arrange
                        int32 HitDie = 12; // Barbarian
                        int32 Level = 5;
                        int32 ConstitutionModifier = 3;

                        // Act
                        int32 Result = CalculationHelpers::CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);

                        // Assert
                        // HP nível 2+ = ceil(HitDie/2) + CON modifier = ceil(12/2) + 3 = 6 + 3 = 9
                        TestEqual("HP nível 5 deve ser 9 (ceil(12/2) + 3)", Result, 9);
                    });
             });

    // ============================================================================
    // CalculateMaxHP Tests
    // ============================================================================
    Describe("Issue-3.6/ CalculateMaxHP",
             [this]()
             {
                 It("deve calcular MaxHP para Fighter nível 1 com CON modifier +2 usando dados da Data Table",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Busca Fighter na Data Table pelo ID
                        FClassDataRow *FighterRow =
                            DataTableHelpers::FindClassRow(TEXT("CLASS_Fighter"), RealClassDataTable);

                        if (!FighterRow)
                        {
                            AddInfo(TEXT("Fighter não encontrado na Data Table. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs = {FighterRow->ID};
                        TArray<int32> LevelsInClass = {1};
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        // Fighter HitDie = 10 (valor conhecido D&D 5e)
                        // HP nível 1 = HitDie + CON modifier = 10 + 2 = 12
                        TestEqual("MaxHP Fighter nível 1 deve ser 12 (10 + 2)", Result, 12);
                    });

                 It("deve calcular MaxHP para Wizard nível 1 com CON modifier 0 usando dados da Data Table",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Busca Wizard na Data Table pelo ID
                        FClassDataRow *WizardRow =
                            DataTableHelpers::FindClassRow(TEXT("CLASS_Wizard"), RealClassDataTable);

                        if (!WizardRow)
                        {
                            AddInfo(TEXT("Wizard não encontrado na Data Table. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs = {WizardRow->ID};
                        TArray<int32> LevelsInClass = {1};
                        int32 ConstitutionModifier = 0;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        // Wizard HitDie = 6 (valor conhecido D&D 5e)
                        // HP nível 1 = HitDie + CON modifier = 6 + 0 = 6
                        TestEqual("MaxHP Wizard nível 1 deve ser 6 (6 + 0)", Result, 6);
                    });

                 It("deve calcular MaxHP para Fighter nível 3 com CON modifier +2 usando dados da Data Table",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Busca Fighter na Data Table pelo ID
                        FClassDataRow *FighterRow =
                            DataTableHelpers::FindClassRow(TEXT("CLASS_Fighter"), RealClassDataTable);

                        if (!FighterRow)
                        {
                            AddInfo(TEXT("Fighter não encontrado na Data Table. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs = {FighterRow->ID};
                        TArray<int32> LevelsInClass = {3};
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        // Fighter HitDie = 10
                        // HP nível 1 = 10 + 2 = 12
                        // HP nível 2 = ceil(10/2) + 2 = 5 + 2 = 7
                        // HP nível 3 = ceil(10/2) + 2 = 5 + 2 = 7
                        // Total = 12 + 7 + 7 = 26
                        TestEqual("MaxHP Fighter nível 3 deve ser 26 (12 + 7 + 7)", Result, 26);
                    });

                 It("deve calcular MaxHP para multiclass Fighter 2 / Wizard 1 com CON modifier +1 usando dados da Data "
                    "Table",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        // Busca Fighter e Wizard na Data Table pelo ID
                        FClassDataRow *FighterRow =
                            DataTableHelpers::FindClassRow(TEXT("CLASS_Fighter"), RealClassDataTable);
                        FClassDataRow *WizardRow =
                            DataTableHelpers::FindClassRow(TEXT("CLASS_Wizard"), RealClassDataTable);

                        if (!FighterRow || !WizardRow)
                        {
                            AddInfo(TEXT("Fighter ou Wizard não encontrado na Data Table. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs = {FighterRow->ID, WizardRow->ID};
                        TArray<int32> LevelsInClass = {2, 1};
                        int32 ConstitutionModifier = 1;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        // Fighter HitDie = 10
                        // Fighter nível 1 = 10 + 1 = 11
                        // Fighter nível 2 = ceil(10/2) + 1 = 5 + 1 = 6
                        // Wizard HitDie = 6
                        // Wizard nível 1 = 6 + 1 = 7
                        // Total = 11 + 6 + 7 = 24
                        TestEqual("MaxHP Fighter 2 / Wizard 1 deve ser 24 (11 + 6 + 7)", Result, 24);
                    });

                 It("deve retornar 0 quando ClassDataTable é nullptr",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> ClassIDs = {TEXT("CLASS_Fighter")};
                        TArray<int32> LevelsInClass = {1};
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result =
                            CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier, nullptr);

                        // Assert
                        TestEqual("MaxHP deve ser 0 quando ClassDataTable é nullptr", Result, 0);
                    });

                 It("deve retornar 0 quando arrays têm tamanhos diferentes",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs = {TEXT("CLASS_Fighter"), TEXT("CLASS_Wizard")};
                        TArray<int32> LevelsInClass = {1}; // Tamanho diferente
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        TestEqual("MaxHP deve ser 0 quando arrays têm tamanhos diferentes", Result, 0);
                    });

                 It("deve retornar 0 quando ClassNames está vazio",
                    [this]()
                    {
                        // Arrange
                        if (!RealClassDataTable)
                        {
                            AddInfo(TEXT("ClassDataTable não foi carregado. Pulando teste."));
                            return;
                        }

                        TArray<FName> ClassIDs;
                        TArray<int32> LevelsInClass;
                        int32 ConstitutionModifier = 2;

                        // Act
                        int32 Result = CalculationHelpers::CalculateMaxHP(ClassIDs, LevelsInClass, ConstitutionModifier,
                                                                          RealClassDataTable);

                        // Assert
                        TestEqual("MaxHP deve ser 0 quando ClassIDs está vazio", Result, 0);
                    });
             });
}

#pragma endregion HP Tests
