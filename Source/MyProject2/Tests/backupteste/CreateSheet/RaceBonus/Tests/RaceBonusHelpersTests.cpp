// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/RaceBonus/RaceBonusHelpers.h"
#include "Data/Tables/RaceDataTable.h"

#pragma endregion Includes

// ============================================================================
// RaceBonusHelpers Tests
// ============================================================================
#pragma region RaceBonusHelpers Tests

BEGIN_DEFINE_SPEC(RaceBonusHelpersSpec, "MyProject2.CreateSheet.RaceBonusHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(RaceBonusHelpersSpec)

void RaceBonusHelpersSpec::Define()
{
    Describe("CalculateRacialBonuses",
             [this]()
             {
                 It("deve calcular bônus de raça base apenas (Dwarf +2 CON)", [this]()
                    {
                        // Arrange: Raça base com bônus
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Dwarf");
                        RaceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, nullptr, TArray<FName>(), RacialBonuses);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Deve ter bônus de Constitution", RacialBonuses.FindRef(TEXT("Constitution")), 2);
                        TestEqual("Deve ter apenas 1 bônus", RacialBonuses.Num(), 1);
                    });

                 It("deve calcular bônus de sub-raça apenas (Hill Dwarf +1 WIS)", [this]()
                    {
                        // Arrange: Sub-raça com bônus
                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("Hill Dwarf");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Wisdom"), 1));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(nullptr, SubraceRow, TArray<FName>(), RacialBonuses);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Deve ter bônus de Wisdom", RacialBonuses.FindRef(TEXT("Wisdom")), 1);
                        TestEqual("Deve ter apenas 1 bônus", RacialBonuses.Num(), 1);
                    });

                 It("deve combinar bônus de raça base e sub-raça (Dwarf +2 CON, Hill Dwarf +1 WIS)", [this]()
                    {
                        // Arrange: Raça base + sub-raça
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Dwarf");
                        RaceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));

                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("Hill Dwarf");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Wisdom"), 1));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, TArray<FName>(), RacialBonuses);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Deve ter bônus de Constitution", RacialBonuses.FindRef(TEXT("Constitution")), 2);
                        TestEqual("Deve ter bônus de Wisdom", RacialBonuses.FindRef(TEXT("Wisdom")), 1);
                        TestEqual("Deve ter 2 bônus", RacialBonuses.Num(), 2);
                    });

                 It("deve acumular bônus quando raça e sub-raça têm mesmo atributo", [this]()
                    {
                        // Arrange: Raça e sub-raça com mesmo atributo
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Elf");
                        RaceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 2));

                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("High Elf");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 1));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, TArray<FName>(), RacialBonuses);

                        // Assert: Valores hardcoded conhecidos (2 + 1 = 3)
                        TestEqual("Deve acumular bônus de Dexterity", RacialBonuses.FindRef(TEXT("Dexterity")), 3);
                        TestEqual("Deve ter apenas 1 bônus", RacialBonuses.Num(), 1);
                    });

                 It("deve calcular Variant Human com 2 escolhas customizadas (+1 cada)", [this]()
                    {
                        // Arrange: Variant Human (sub-raça com ABL_Custom)
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Human");

                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("Variant Human");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Custom"), 1));

                        TArray<FName> CustomChoices;
                        CustomChoices.Add(TEXT("Strength"));
                        CustomChoices.Add(TEXT("Dexterity"));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, CustomChoices, RacialBonuses);

                        // Assert: Valores hardcoded conhecidos (2 escolhas = +1 cada)
                        TestEqual("Deve ter bônus de Strength", RacialBonuses.FindRef(TEXT("Strength")), 1);
                        TestEqual("Deve ter bônus de Dexterity", RacialBonuses.FindRef(TEXT("Dexterity")), 1);
                        TestEqual("Deve ter 2 bônus", RacialBonuses.Num(), 2);
                    });

                 It("deve calcular Variant Human com 1 escolha customizada (+2)", [this]()
                    {
                        // Arrange: Variant Human com apenas 1 escolha
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Human");

                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("Variant Human");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Custom"), 1));

                        TArray<FName> CustomChoices;
                        CustomChoices.Add(TEXT("Strength"));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, CustomChoices, RacialBonuses);

                        // Assert: Valores hardcoded conhecidos (1 escolha = +2)
                        TestEqual("Deve ter bônus de Strength", RacialBonuses.FindRef(TEXT("Strength")), 2);
                        TestEqual("Deve ter apenas 1 bônus", RacialBonuses.Num(), 1);
                    });

                 It("deve retornar mapa vazio quando RaceRow e SubraceRow são nullptr", [this]()
                    {
                        // Arrange: Sem raça
                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(nullptr, nullptr, TArray<FName>(), RacialBonuses);

                        // Assert
                        TestEqual("Deve estar vazio", RacialBonuses.Num(), 0);
                    });

                 It("deve ignorar entradas ABL_Custom na raça base", [this]()
                    {
                        // Arrange: Raça base com ABL_Custom (deve ser ignorado)
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Human");
                        RaceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Custom"), 1));

                        TMap<FName, int32> RacialBonuses;

                        // Act
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, nullptr, TArray<FName>(), RacialBonuses);

                        // Assert: ABL_Custom deve ser ignorado na raça base
                        TestEqual("Deve estar vazio (ABL_Custom ignorado)", RacialBonuses.Num(), 0);
                    });
             });

    Describe("IncrementFinalScoresWithRacialBonuses",
             [this]()
             {
                 It("deve incrementar Final Scores com bônus raciais corretamente", [this]()
                    {
                        // Arrange: Final Scores iniciais e bônus
                        int32 FinalStrength = 8;
                        int32 FinalDexterity = 8;
                        int32 FinalConstitution = 8;
                        int32 FinalIntelligence = 8;
                        int32 FinalWisdom = 8;
                        int32 FinalCharisma = 8;

                        TMap<FName, int32> RacialBonuses;
                        RacialBonuses.Add(TEXT("Strength"), 2);
                        RacialBonuses.Add(TEXT("Constitution"), 1);

                        // Act
                        FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(
                            RacialBonuses, FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence,
                            FinalWisdom, FinalCharisma);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Final Strength deve ser 10 (8 + 2)", FinalStrength, 10);
                        TestEqual("Final Constitution deve ser 9 (8 + 1)", FinalConstitution, 9);
                        TestEqual("Final Dexterity deve permanecer 8", FinalDexterity, 8);
                        TestEqual("Final Intelligence deve permanecer 8", FinalIntelligence, 8);
                        TestEqual("Final Wisdom deve permanecer 8", FinalWisdom, 8);
                        TestEqual("Final Charisma deve permanecer 8", FinalCharisma, 8);
                    });

                 It("deve incrementar todos os atributos quando há bônus para todos", [this]()
                    {
                        // Arrange: Todos os atributos com bônus
                        int32 FinalStrength = 10;
                        int32 FinalDexterity = 10;
                        int32 FinalConstitution = 10;
                        int32 FinalIntelligence = 10;
                        int32 FinalWisdom = 10;
                        int32 FinalCharisma = 10;

                        TMap<FName, int32> RacialBonuses;
                        RacialBonuses.Add(TEXT("Strength"), 1);
                        RacialBonuses.Add(TEXT("Dexterity"), 1);
                        RacialBonuses.Add(TEXT("Constitution"), 1);
                        RacialBonuses.Add(TEXT("Intelligence"), 1);
                        RacialBonuses.Add(TEXT("Wisdom"), 1);
                        RacialBonuses.Add(TEXT("Charisma"), 1);

                        // Act
                        FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(
                            RacialBonuses, FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence,
                            FinalWisdom, FinalCharisma);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Final Strength deve ser 11", FinalStrength, 11);
                        TestEqual("Final Dexterity deve ser 11", FinalDexterity, 11);
                        TestEqual("Final Constitution deve ser 11", FinalConstitution, 11);
                        TestEqual("Final Intelligence deve ser 11", FinalIntelligence, 11);
                        TestEqual("Final Wisdom deve ser 11", FinalWisdom, 11);
                        TestEqual("Final Charisma deve ser 11", FinalCharisma, 11);
                    });

                 It("deve não modificar Final Scores quando mapa está vazio", [this]()
                    {
                        // Arrange: Final Scores iniciais e mapa vazio
                        int32 FinalStrength = 15;
                        int32 FinalDexterity = 14;
                        int32 FinalConstitution = 13;
                        int32 FinalIntelligence = 12;
                        int32 FinalWisdom = 11;
                        int32 FinalCharisma = 10;

                        TMap<FName, int32> RacialBonuses; // Vazio

                        // Act
                        FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(
                            RacialBonuses, FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence,
                            FinalWisdom, FinalCharisma);

                        // Assert: Valores devem permanecer inalterados
                        TestEqual("Final Strength deve permanecer 15", FinalStrength, 15);
                        TestEqual("Final Dexterity deve permanecer 14", FinalDexterity, 14);
                        TestEqual("Final Constitution deve permanecer 13", FinalConstitution, 13);
                        TestEqual("Final Intelligence deve permanecer 12", FinalIntelligence, 12);
                        TestEqual("Final Wisdom deve permanecer 11", FinalWisdom, 11);
                        TestEqual("Final Charisma deve permanecer 10", FinalCharisma, 10);
                    });

                 It("deve acumular bônus quando raça e sub-raça têm mesmo atributo", [this]()
                    {
                        // Arrange: Raça e sub-raça com mesmo atributo (deve acumular)
                        FRaceDataRow *RaceRow = new FRaceDataRow();
                        RaceRow->Name = TEXT("Elf");
                        RaceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 2));

                        FRaceDataRow *SubraceRow = new FRaceDataRow();
                        SubraceRow->Name = TEXT("High Elf");
                        SubraceRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 1));

                        TMap<FName, int32> RacialBonuses;

                        // Act: Chama função real que deve acumular bônus
                        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, TArray<FName>(), RacialBonuses);

                        // Assert: Valores hardcoded conhecidos (2 + 1 = 3)
                        TestEqual("Bônus de Dexterity deve ser 3 (acumulado: 2 + 1)",
                                 RacialBonuses.FindRef(TEXT("Dexterity")), 3);
                        TestEqual("Deve ter apenas 1 bônus", RacialBonuses.Num(), 1);
                    });
             });
}

#pragma endregion RaceBonusHelpers Tests
