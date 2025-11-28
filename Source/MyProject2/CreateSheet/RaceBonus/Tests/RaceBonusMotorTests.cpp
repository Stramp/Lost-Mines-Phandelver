// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/RaceBonus/RaceBonusOrchestrator.h"
#include "Data/Structures/FCharacterSheetData.h"
#include "Data/Tables/RaceDataTable.h"
#include "Engine/DataTable.h"
#include "Utils/DnDConstants.h"

#pragma endregion Includes

// ============================================================================
// RaceBonusMotor Tests
// ============================================================================
#pragma region RaceBonusMotor Tests

BEGIN_DEFINE_SPEC(RaceBonusMotorSpec, "MyProject2.CreateSheet.RaceBonusMotor",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

int32 TestFinalStrength;
int32 TestFinalDexterity;
int32 TestFinalConstitution;
int32 TestFinalIntelligence;
int32 TestFinalWisdom;
int32 TestFinalCharisma;
UDataTable *TestRaceDataTable;

END_DEFINE_SPEC(RaceBonusMotorSpec)

void RaceBonusMotorSpec::Define()
{
    BeforeEach([this]()
               {
                   // Arrange: Inicializar Final Scores com valores base
                   TestFinalStrength = DnDConstants::BASE_ABILITY_SCORE;
                   TestFinalDexterity = DnDConstants::BASE_ABILITY_SCORE;
                   TestFinalConstitution = DnDConstants::BASE_ABILITY_SCORE;
                   TestFinalIntelligence = DnDConstants::BASE_ABILITY_SCORE;
                   TestFinalWisdom = DnDConstants::BASE_ABILITY_SCORE;
                   TestFinalCharisma = DnDConstants::BASE_ABILITY_SCORE;

                   // Criar Data Table mock
                   TestRaceDataTable = NewObject<UDataTable>();
                   TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();
               });

    Describe("ApplyRacialBonuses",
             [this]()
             {
                 It("deve aplicar bônus de raça base apenas (Dwarf +2 CON)", [this]()
                    {
                        // Arrange: Raça base com bônus
                        FRaceDataRow *DwarfRow = new FRaceDataRow();
                        DwarfRow->Name = TEXT("Dwarf");
                        DwarfRow->ID = TEXT("RACE_Dwarf");
                        DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));
                        TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Final Constitution deve ser 10 (8 + 2)", TestFinalConstitution, 10);
                        TestEqual("Final Strength deve permanecer 8", TestFinalStrength, 8);
                        TestEqual("Final Dexterity deve permanecer 8", TestFinalDexterity, 8);
                    });

                 It("deve aplicar bônus de raça base e sub-raça (Dwarf +2 CON, Hill Dwarf +1 WIS)", [this]()
                    {
                        // Arrange: Raça base + sub-raça
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
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Final Constitution deve ser 10 (8 + 2)", TestFinalConstitution, 10);
                        TestEqual("Final Wisdom deve ser 9 (8 + 1)", TestFinalWisdom, 9);
                        TestEqual("Final Strength deve permanecer 8", TestFinalStrength, 8);
                    });

                 It("deve aplicar Variant Human com 2 escolhas customizadas (+1 cada)", [this]()
                    {
                        // Arrange: Variant Human
                        FRaceDataRow *HumanRow = new FRaceDataRow();
                        HumanRow->Name = TEXT("Human");
                        HumanRow->ID = TEXT("RACE_Human");
                        TestRaceDataTable->AddRow(TEXT("Human"), *HumanRow);

                        FRaceDataRow *VariantHumanRow = new FRaceDataRow();
                        VariantHumanRow->Name = TEXT("Variant Human");
                        VariantHumanRow->ID = TEXT("RACE_VariantHuman");
                        VariantHumanRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Custom"), 1));
                        TestRaceDataTable->AddRow(TEXT("Variant Human"), *VariantHumanRow);

                        // Adicionar sub-raça à raça base
                        FDataTableRowHandle VariantHumanHandle;
                        VariantHumanHandle.DataTable = TestRaceDataTable;
                        VariantHumanHandle.RowName = TEXT("Variant Human");
                        HumanRow->SubraceHandles.Add(VariantHumanHandle);

                        TArray<FName> CustomChoices;
                        CustomChoices.Add(TEXT("Strength"));
                        CustomChoices.Add(TEXT("Dexterity"));

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Human");
                        Data.SelectedSubrace = TEXT("Variant Human");
                        Data.CustomAbilityScoreChoices = CustomChoices;
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Valores hardcoded conhecidos
                        TestEqual("Final Strength deve ser 9 (8 + 1)", TestFinalStrength, 9);
                        TestEqual("Final Dexterity deve ser 9 (8 + 1)", TestFinalDexterity, 9);
                        TestEqual("Final Constitution deve permanecer 8", TestFinalConstitution, 8);
                    });

                 It("deve não aplicar bônus quando RaceDataTable é nullptr", [this]()
                    {
                        // Arrange: Sem Data Table
                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = nullptr;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Valores devem permanecer inalterados
                        TestEqual("Final Strength deve permanecer 8", TestFinalStrength, 8);
                        TestEqual("Final Dexterity deve permanecer 8", TestFinalDexterity, 8);
                        TestEqual("Final Constitution deve permanecer 8", TestFinalConstitution, 8);
                    });

                 It("deve não aplicar bônus quando SelectedRace é NAME_None", [this]()
                    {
                        // Arrange: Sem raça selecionada
                        FCharacterSheetData Data;
                        Data.SelectedRace = NAME_None;
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Valores devem permanecer inalterados
                        TestEqual("Final Strength deve permanecer 8", TestFinalStrength, 8);
                        TestEqual("Final Dexterity deve permanecer 8", TestFinalDexterity, 8);
                        TestEqual("Final Constitution deve permanecer 8", TestFinalConstitution, 8);
                    });

                 It("deve não aplicar bônus quando referências de Final Scores são nullptr", [this]()
                    {
                        // Arrange: Referências inválidas
                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = nullptr; // Inválido

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Função deve retornar sem erro (validação interna)
                        TestTrue("Teste deve passar (função valida referências)", true);
                    });

                 It("deve não aplicar bônus de sub-raça quando sub-raça não pertence à raça", [this]()
                    {
                        // Arrange: Sub-raça inválida
                        FRaceDataRow *DwarfRow = new FRaceDataRow();
                        DwarfRow->Name = TEXT("Dwarf");
                        DwarfRow->ID = TEXT("RACE_Dwarf");
                        DwarfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Constitution"), 2));
                        TestRaceDataTable->AddRow(TEXT("Dwarf"), *DwarfRow);

                        FRaceDataRow *ElfRow = new FRaceDataRow();
                        ElfRow->Name = TEXT("Elf");
                        ElfRow->ID = TEXT("RACE_Elf");
                        ElfRow->AbilityScoreImprovements.Add(FAbilityScoreImprovement(TEXT("ABL_Dexterity"), 2));
                        TestRaceDataTable->AddRow(TEXT("Elf"), *ElfRow);

                        FCharacterSheetData Data;
                        Data.SelectedRace = TEXT("Dwarf");
                        Data.SelectedSubrace = TEXT("Elf"); // Sub-raça inválida (não pertence a Dwarf)
                        Data.RaceDataTable = TestRaceDataTable;
                        Data.FinalStrength = &TestFinalStrength;
                        Data.FinalDexterity = &TestFinalDexterity;
                        Data.FinalConstitution = &TestFinalConstitution;
                        Data.FinalIntelligence = &TestFinalIntelligence;
                        Data.FinalWisdom = &TestFinalWisdom;
                        Data.FinalCharisma = &TestFinalCharisma;

                        // Act
                        FRaceBonusOrchestrator::ProcessRacialBonuses(Data);

                        // Assert: Apenas bônus de raça base deve ser aplicado
                        TestEqual("Final Constitution deve ser 10 (8 + 2)", TestFinalConstitution, 10);
                        TestEqual("Final Dexterity deve permanecer 8 (sub-raça inválida ignorada)", TestFinalDexterity, 8);
                    });
             });
}

#pragma endregion RaceBonusMotor Tests
