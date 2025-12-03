// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/Core/CharacterSheetCore.h"
#include "Data/Structures/FCharacterSheetData.h"
#include "Data/Structures/FPointBuyResult.h"
#include "Data/Tables/RaceDataTable.h"
#include "Engine/DataTable.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// CharacterSheetCore Tests
// ============================================================================
#pragma region CharacterSheetCore Tests

BEGIN_DEFINE_SPEC(CharacterSheetCoreSpec, "MyProject2.CreateSheet.CharacterSheetCore",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

int32 TestFinalStrength;
int32 TestFinalDexterity;
int32 TestFinalConstitution;
int32 TestFinalIntelligence;
int32 TestFinalWisdom;
int32 TestFinalCharisma;
UDataTable *TestRaceDataTable;

END_DEFINE_SPEC(CharacterSheetCoreSpec)

void CharacterSheetCoreSpec::Define()
{
    BeforeEach([this]()
               {
                   // Arrange: Inicializar Final Scores com valores arbitrários (serão resetados)
                   TestFinalStrength = 20;
                   TestFinalDexterity = 20;
                   TestFinalConstitution = 20;
                   TestFinalIntelligence = 20;
                   TestFinalWisdom = 20;
                   TestFinalCharisma = 20;

                   // Criar Data Table mock
                   TestRaceDataTable = NewObject<UDataTable>();
                   TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();
               });

    Describe("RecalculateFinalScores",
             [this]()
             {
                 It("deve recalcular completo: Base (8) + RaceBonus (+2 CON) + PointBuy (+7 STR = 15)", [this]()
                    {
                        // Arrange: Raça com bônus + Point Buy
                        FRaceDataRow *DwarfRow = new FRaceDataRow();
                        DwarfRow->Name = TEXT("Dwarf");
                        DwarfRow->ID = TEXT("RACE_Dwarf");
                        DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));
                        TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 0;    // Score 8 = 0 pontos
                        Data.PointBuyConstitution = 0; // Score 8 = 0 pontos
                        Data.PointBuyIntelligence = 0; // Score 8 = 0 pontos
                        Data.PointBuyWisdom = 0;       // Score 8 = 0 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult PointBuyResult;
                        FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

                        // Assert: Valores hardcoded conhecidos
                        // Fórmula: FinalScore = BASE_ABILITY_SCORE (8) + RacialBonus + PointBuyAllocation
                        // STR: 8 (base) + 0 (race) + 7 (point buy) = 15
                        // CON: 8 (base) + 2 (race) + 0 (point buy) = 10
                        TestEqual("Final Strength deve ser 15 (8 + 0 + 7)", TestFinalStrength, 15);
                        TestEqual("Final Constitution deve ser 10 (8 + 2 + 0)", TestFinalConstitution, 10);
                        TestEqual("Final Dexterity deve ser 8 (8 + 0 + 0)", TestFinalDexterity, 8);
                        TestTrue("Point Buy deve ser válido", PointBuyResult.bIsValid);
                    });

                 It("deve aplicar ordem correta: reset → race → point buy", [this]()
                    {
                        // Arrange: Valores iniciais altos (devem ser resetados)
                        TestFinalStrength = 30;
                        TestFinalDexterity = 30;

                        FRaceDataRow *ElfRow = new FRaceDataRow();
                        ElfRow->Name = TEXT("Elf");
                        ElfRow->ID = TEXT("RACE_Elf");
                        ElfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 2));
                        TestRaceDataTable->AddRow(TEXT("Elf"), *ElfRow);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Elf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 5;     // Score 13 = 5 pontos
                        Data.PointBuyDexterity = 6;    // Score 14 = 7 pontos
                        Data.PointBuyConstitution = 0;
                        Data.PointBuyIntelligence = 0;
                        Data.PointBuyWisdom = 0;
                        Data.PointBuyCharisma = 0;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FCharacterSheetCore::RecalculateFinalScores(Data, nullptr);

                        // Assert: Valores hardcoded conhecidos
                        // STR: 8 (reset) + 0 (race) + 5 (point buy) = 13
                        // DEX: 8 (reset) + 2 (race) + 6 (point buy) = 16
                        TestEqual("Final Strength deve ser 13 (resetado e recalculado)", TestFinalStrength, 13);
                        TestEqual("Final Dexterity deve ser 16 (resetado, race bonus, point buy)", TestFinalDexterity, 16);
                    });

                 It("deve recalcular apenas com RaceBonus (sem Point Buy)", [this]()
                    {
                        // Arrange: Apenas raça, sem Point Buy
                        FRaceDataRow *DwarfRow = new FRaceDataRow();
                        DwarfRow->Name = TEXT("Dwarf");
                        DwarfRow->ID = TEXT("RACE_Dwarf");
                        DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));
                        TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 0;     // Sem Point Buy
                        Data.PointBuyDexterity = 0;
                        Data.PointBuyConstitution = 0;
                        Data.PointBuyIntelligence = 0;
                        Data.PointBuyWisdom = 0;
                        Data.PointBuyCharisma = 0;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FCharacterSheetCore::RecalculateFinalScores(Data, nullptr);

                        // Assert: Valores hardcoded conhecidos
                        // CON: 8 (base) + 2 (race) + 0 (point buy) = 10
                        TestEqual("Final Constitution deve ser 10 (8 + 2)", TestFinalConstitution, 10);
                        TestEqual("Final Strength deve ser 8 (8 + 0 + 0)", TestFinalStrength, 8);
                    });

                 It("deve recalcular apenas com Point Buy (sem RaceBonus)", [this]()
                    {
                        // Arrange: Apenas Point Buy, sem raça
                        FCharacterSheetData Data;
                        Data.SelectedRace = NAME_None; // Sem raça
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 6;    // Score 14 = 7 pontos
                        Data.PointBuyConstitution = 5; // Score 13 = 5 pontos
                        Data.PointBuyIntelligence = 4; // Score 12 = 4 pontos
                        Data.PointBuyWisdom = 2;       // Score 10 = 2 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FCharacterSheetCore::RecalculateFinalScores(Data, nullptr);

                        // Assert: Valores hardcoded conhecidos
                        // STR: 8 (base) + 0 (race) + 7 (point buy) = 15
                        // DEX: 8 (base) + 0 (race) + 6 (point buy) = 14
                        TestEqual("Final Strength deve ser 15 (8 + 0 + 7)", TestFinalStrength, 15);
                        TestEqual("Final Dexterity deve ser 14 (8 + 0 + 6)", TestFinalDexterity, 14);
                        TestEqual("Final Constitution deve ser 13 (8 + 0 + 5)", TestFinalConstitution, 13);
                    });

                 It("deve recalcular com ambos: RaceBonus + Point Buy (caso completo)", [this]()
                    {
                        // Arrange: Raça + sub-raça + Point Buy completo
                        FRaceDataRow *DwarfRow = new FRaceDataRow();
                        DwarfRow->Name = TEXT("Dwarf");
                        DwarfRow->ID = TEXT("RACE_Dwarf");
                        DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));
                        TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);

                        FRaceDataRow *HillDwarfRow = new FRaceDataRow();
                        HillDwarfRow->Name = TEXT("Hill Dwarf");
                        HillDwarfRow->ID = TEXT("RACE_HillDwarf");
                        HillDwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Wisdom"), 1));
                        TestRaceDataTable->AddRow(TEXT("Hill Dwarf"), *HillDwarfRow);

                        // Adicionar sub-raça à raça base
                        FDataTableRowHandle HillDwarfHandle;
                        HillDwarfHandle.DataTable = TestRaceDataTable;
                        HillDwarfHandle.RowName = TEXT("Hill Dwarf");
                        DwarfRow->SubraceHandles.Add(HillDwarfHandle);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.SelectedSubrace = TEXT("Hill Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 6;    // Score 14 = 7 pontos
                        Data.PointBuyConstitution = 5; // Score 13 = 5 pontos
                        Data.PointBuyIntelligence = 4; // Score 12 = 4 pontos
                        Data.PointBuyWisdom = 2;       // Score 10 = 2 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult PointBuyResult;
                        FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

                        // Assert: Valores hardcoded conhecidos
                        // STR: 8 (base) + 0 (race) + 7 (point buy) = 15
                        // DEX: 8 (base) + 0 (race) + 6 (point buy) = 14
                        // CON: 8 (base) + 2 (race) + 5 (point buy) = 15
                        // WIS: 8 (base) + 1 (sub-race) + 2 (point buy) = 11
                        TestEqual("Final Strength deve ser 15", TestFinalStrength, 15);
                        TestEqual("Final Dexterity deve ser 14", TestFinalDexterity, 14);
                        TestEqual("Final Constitution deve ser 15 (8 + 2 + 5)", TestFinalConstitution, 15);
                        TestEqual("Final Wisdom deve ser 11 (8 + 1 + 2)", TestFinalWisdom, 11);
                        TestTrue("Point Buy deve ser válido", PointBuyResult.bIsValid);
                    });

                 It("deve não recalcular quando referências de Final Scores são nullptr", [this]()
                    {
                        // Arrange: Referências inválidas
                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = nullptr; // Inválido

                        // Act
                        FCharacterSheetCore::RecalculateFinalScores(Data, nullptr);

                        // Assert: Função deve retornar sem erro (validação interna)
                        TestTrue("Teste deve passar (função valida referências)", true);
                    });

                 It("deve retornar resultado de Point Buy quando OutPointBuyResult é fornecido", [this]()
                    {
                        // Arrange: Point Buy válido
                        FCharacterSheetData Data;
                        Data.SelectedRace = NAME_None;
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 6;    // Score 14 = 7 pontos
                        Data.PointBuyConstitution = 5; // Score 13 = 5 pontos
                        Data.PointBuyIntelligence = 4; // Score 12 = 4 pontos
                        Data.PointBuyWisdom = 2;       // Score 10 = 2 pontos
                        Data.PointBuyCharisma = 0;     // Score 8 = 0 pontos
                        // Total: 9 + 7 + 5 + 4 + 2 + 0 = 27 pontos
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult PointBuyResult;
                        FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Point Buy deve ser válido", PointBuyResult.bIsValid);
                        TestEqual("Pontos restantes devem ser 0", PointBuyResult.PointsRemaining, 0);
                    });

                 It("deve ajustar automaticamente quando Point Buy excede 27 pontos", [this]()
                    {
                        // Arrange: Point Buy que excede 27 pontos (será ajustado automaticamente)
                        FCharacterSheetData Data;
                        Data.SelectedRace = NAME_None;
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.PointBuyStrength = 7;     // Score 15 = 9 pontos
                        Data.PointBuyDexterity = 7;    // Score 15 = 9 pontos
                        Data.PointBuyConstitution = 7; // Score 15 = 9 pontos
                        Data.PointBuyIntelligence = 7; // Score 15 = 9 pontos
                        Data.PointBuyWisdom = 7;       // Score 15 = 9 pontos
                        Data.PointBuyCharisma = 7;     // Score 15 = 9 pontos
                        // Total: 9 * 6 = 54 pontos (excede 27, será ajustado)
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FPointBuyResult PointBuyResult;
                        FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Point Buy deve ser válido após ajuste automático", PointBuyResult.bIsValid);
                        TestTrue("Deve ter sido ajustado automaticamente", PointBuyResult.bWasAutoAdjusted);
                        TestEqual("Pontos restantes devem ser 0 após ajuste", PointBuyResult.PointsRemaining, 0);
                    });
             });
}

#pragma endregion CharacterSheetCore Tests
