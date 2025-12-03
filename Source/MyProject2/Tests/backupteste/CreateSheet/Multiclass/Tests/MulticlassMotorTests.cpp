// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassProficiencyOrchestrator.h"
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/AbilityScoreDataTable.h"
#include "Data/Structures/MulticlassTypes.h"
#include "Data/Structures/FMulticlassRequirement.h"
#include "Data/Structures/FProgressEntry.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// MulticlassMotor Tests
// ============================================================================
#pragma region MulticlassMotor Tests

BEGIN_DEFINE_SPEC(MulticlassMotorSpec, "MyProject2.CreateSheet.MulticlassMotor",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable *TestClassDataTable;
UDataTable *TestFeatureDataTable;
UDataTable *TestProficiencyDataTable;
UDataTable *TestAbilityScoreDataTable;

END_DEFINE_SPEC(MulticlassMotorSpec)

void MulticlassMotorSpec::Define()
{
    BeforeEach([this]()
               {
                   // Arrange: Criar Data Tables mocks
                   TestClassDataTable = NewObject<UDataTable>();
                   TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                   TestFeatureDataTable = NewObject<UDataTable>();
                   TestFeatureDataTable->RowStruct = FFeatureDataRow::StaticStruct();

                   TestProficiencyDataTable = NewObject<UDataTable>();
                   TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                   TestAbilityScoreDataTable = NewObject<UDataTable>();
                   TestAbilityScoreDataTable->RowStruct = FAbilityScoreDataRow::StaticStruct();
               });

    Describe("GetAvailableClasses",
             [this]()
             {
                 It("deve retornar classes disponíveis quando atributos atendem requisitos", [this]()
                    {
                        // Arrange: Classe com requisito STR 13
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        FighterRow->Name = TEXT("Fighter");

                        FMulticlassRequirementGroup Group;
                        Group.Operator = TEXT("OR");
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Strength"), 13));
                        Group.Requirements.Add(FMulticlassRequirement(TEXT("ABL_Dexterity"), 13));
                        FighterRow->MulticlassRequirementGroups.Add(Group);
                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        // Adicionar Ability Scores ao Data Table
                        FAbilityScoreDataRow *StrRow = new FAbilityScoreDataRow();
                        StrRow->Name = TEXT("Strength");
                        StrRow->ID = TEXT("ABL_Strength");
                        StrRow->Abbreviation = TEXT("STR");
                        TestAbilityScoreDataTable->AddRow(TEXT("ABL_Strength"), *StrRow);

                        FAbilityScoreDataRow *DexRow = new FAbilityScoreDataRow();
                        DexRow->Name = TEXT("Dexterity");
                        DexRow->ID = TEXT("ABL_Dexterity");
                        DexRow->Abbreviation = TEXT("DEX");
                        TestAbilityScoreDataTable->AddRow(TEXT("ABL_Dexterity"), *DexRow);

                        // Atributos: STR = 15 (satisfaz), DEX = 12
                        int32 FinalStrength = 15;
                        int32 FinalDexterity = 12;
                        int32 FinalConstitution = 14;
                        int32 FinalIntelligence = 10;
                        int32 FinalWisdom = 11;
                        int32 FinalCharisma = 13;

                        // Act
                        TArray<FName> AvailableClasses = FMulticlassMotor::GetAvailableClasses(
                            TestClassDataTable, FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence,
                            FinalWisdom, FinalCharisma, TestAbilityScoreDataTable);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Deve ter pelo menos uma classe disponível", AvailableClasses.Num() > 0);
                        TestTrue("Fighter deve estar disponível (STR 15 >= 13)",
                                 AvailableClasses.Contains(TEXT("Fighter")));
                    });

                 It("deve retornar array vazio quando ClassDataTable é nullptr", [this]()
                    {
                        // Arrange: Sem Data Table
                        int32 FinalStrength = 15;
                        int32 FinalDexterity = 12;
                        int32 FinalConstitution = 14;
                        int32 FinalIntelligence = 10;
                        int32 FinalWisdom = 11;
                        int32 FinalCharisma = 13;

                        // Act
                        TArray<FName> AvailableClasses = FMulticlassMotor::GetAvailableClasses(
                            nullptr, FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence, FinalWisdom,
                            FinalCharisma, TestAbilityScoreDataTable);

                        // Assert
                        TestEqual("Deve retornar array vazio", AvailableClasses.Num(), 0);
                    });
             });

    Describe("LoadClassProficiencies",
             [this]()
             {
                 It("deve carregar proficiências de classe no nível 1", [this]()
                    {
                        // Arrange: Classe com proficiências
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        FighterRow->Name = TEXT("Fighter");

                        // Adicionar proficiência de arma
                        FDataTableRowHandle WeaponHandle;
                        WeaponHandle.DataTable = TestProficiencyDataTable;
                        WeaponHandle.RowName = TEXT("Simple Weapons");
                        FighterRow->WeaponProficiencyHandles.Add(WeaponHandle);

                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        // Adicionar proficiência ao Data Table
                        FProficiencyDataRow *WeaponProficiency = new FProficiencyDataRow();
                        WeaponProficiency->Name = TEXT("Simple Weapons");
                        WeaponProficiency->ID = TEXT("PW_Simple_Weapons");
                        TestProficiencyDataTable->AddRow(TEXT("Simple Weapons"), *WeaponProficiency);

                        TArray<FMulticlassProficienciesEntry> OutProficiencies;

                        // Act
                        bool bLoaded = FMulticlassProficiencyOrchestrator::Load(
                            TEXT("Fighter"), 1, TestClassDataTable, TestProficiencyDataTable, OutProficiencies);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Deve carregar proficiências", bLoaded);
                        TestTrue("Deve ter pelo menos uma entrada", OutProficiencies.Num() > 0);
                        if (OutProficiencies.Num() > 0)
                        {
                            TestTrue("Deve ter proficiência de arma",
                                     OutProficiencies[0].armas.Contains(TEXT("Simple Weapons")));
                        }
                    });

                 It("deve retornar false quando nível não é 1 (proficiências só no nível 1)", [this]()
                    {
                        // Arrange: Nível 2 (proficiências só no nível 1)
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        TArray<FMulticlassProficienciesEntry> OutProficiencies;

                        // Act
                        bool bLoaded = FMulticlassProficiencyOrchestrator::Load(
                            TEXT("Fighter"), 2, TestClassDataTable, TestProficiencyDataTable, OutProficiencies);

                        // Assert
                        TestFalse("Não deve carregar proficiências no nível 2", bLoaded);
                    });

                 It("deve retornar false quando ClassName é NAME_None", [this]()
                    {
                        // Arrange: Classe inválida
                        TArray<FMulticlassProficienciesEntry> OutProficiencies;

                        // Act
                        bool bLoaded = FMulticlassProficiencyOrchestrator::Load(
                            NAME_None, 1, TestClassDataTable, TestProficiencyDataTable, OutProficiencies);

                        // Assert
                        TestFalse("Não deve carregar proficiências com classe inválida", bLoaded);
                    });
             });

    Describe("LoadClassProgression - Features com/sem escolhas",
             [this]()
             {
                 It("deve retornar features com AvailableChoices NAME_None quando feature é Automatic", [this]()
                    {
                        // Arrange: Feature Automatic
                        FFeatureDataRow *SecondWindRow = new FFeatureDataRow();
                        SecondWindRow->Name = TEXT("Second Wind");
                        SecondWindRow->ID = TEXT("FC_SecondWind");
                        SecondWindRow->FeatureType = TEXT("Automatic");
                        SecondWindRow->LevelUnlocked = 1;
                        SecondWindRow->AvailableChoices.Empty();
                        TestFeatureDataTable->AddRow(TEXT("FC_SecondWind"), *SecondWindRow);

                        // Classe com progressão
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        FighterRow->Name = TEXT("Fighter");

                        FProgressEntry Level1Entry;
                        Level1Entry.Level = 1;
                        FDataTableRowHandle FeatureHandle;
                        FeatureHandle.DataTable = TestFeatureDataTable;
                        FeatureHandle.RowName = TEXT("FC_SecondWind");
                        Level1Entry.FeatureHandles.Add(FeatureHandle);
                        FighterRow->Progression.Add(Level1Entry);

                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        TArray<FMulticlassProgressEntry> Progression;

                        // Act
                        bool bLoaded = FMulticlassMotor::LoadClassProgression(
                            TEXT("Fighter"), 1, TestClassDataTable, TestFeatureDataTable, Progression);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Motor deve carregar progressão", bLoaded);
                        TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                        if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                        {
                            FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                            TestEqual("Feature Automatic deve ter AvailableChoices = NAME_None",
                                     FirstFeature.AvailableChoices, FName(NAME_None));
                            TestFalse("Feature Automatic não deve ter escolhas disponíveis",
                                     FMulticlassValidationHelpers::FeatureHasAvailableChoices(FirstFeature));
                        }
                    });

                 It("deve retornar features com AvailableChoices preenchido quando feature é Choice com escolhas",
                    [this]()
                    {
                        // Arrange: Feature Choice com escolhas
                        FFeatureDataRow *FightingStyleRow = new FFeatureDataRow();
                        FightingStyleRow->Name = TEXT("Fighting Style");
                        FightingStyleRow->ID = TEXT("FC_FightingStyle");
                        FightingStyleRow->FeatureType = TEXT("Choice");
                        FightingStyleRow->LevelUnlocked = 1;

                        FFeatureChoice Choice1;
                        Choice1.ID = TEXT("FC_Archery");
                        Choice1.Name = TEXT("Archery");
                        FightingStyleRow->AvailableChoices.Add(Choice1);

                        FFeatureChoice Choice2;
                        Choice2.ID = TEXT("FC_Defense");
                        Choice2.Name = TEXT("Defense");
                        FightingStyleRow->AvailableChoices.Add(Choice2);

                        TestFeatureDataTable->AddRow(TEXT("FC_FightingStyle"), *FightingStyleRow);

                        // Classe com progressão
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        FighterRow->Name = TEXT("Fighter");

                        FProgressEntry Level1Entry;
                        Level1Entry.Level = 1;
                        FDataTableRowHandle FeatureHandle;
                        FeatureHandle.DataTable = TestFeatureDataTable;
                        FeatureHandle.RowName = TEXT("FC_FightingStyle");
                        Level1Entry.FeatureHandles.Add(FeatureHandle);
                        FighterRow->Progression.Add(Level1Entry);

                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        TArray<FMulticlassProgressEntry> Progression;

                        // Act
                        bool bLoaded = FMulticlassMotor::LoadClassProgression(
                            TEXT("Fighter"), 1, TestClassDataTable, TestFeatureDataTable, Progression);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Motor deve carregar progressão", bLoaded);
                        TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                        if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                        {
                            FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                            TestNotEqual("Feature Choice deve ter AvailableChoices preenchido",
                                        FirstFeature.AvailableChoices, FName(NAME_None));
                            TestTrue("Feature Choice com escolhas deve retornar true",
                                    FMulticlassValidationHelpers::FeatureHasAvailableChoices(FirstFeature));
                        }
                    });

                 It("deve retornar features com AvailableChoices NAME_None quando feature é Choice mas sem escolhas na "
                    "tabela",
                    [this]()
                    {
                        // Arrange: Feature Choice sem escolhas
                        FFeatureDataRow *FightingStyleRow = new FFeatureDataRow();
                        FightingStyleRow->Name = TEXT("Fighting Style");
                        FightingStyleRow->ID = TEXT("FC_FightingStyle");
                        FightingStyleRow->FeatureType = TEXT("Choice");
                        FightingStyleRow->LevelUnlocked = 1;
                        FightingStyleRow->AvailableChoices.Empty(); // Sem escolhas
                        TestFeatureDataTable->AddRow(TEXT("FC_FightingStyle"), *FightingStyleRow);

                        // Classe com progressão
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        FighterRow->Name = TEXT("Fighter");

                        FProgressEntry Level1Entry;
                        Level1Entry.Level = 1;
                        FDataTableRowHandle FeatureHandle;
                        FeatureHandle.DataTable = TestFeatureDataTable;
                        FeatureHandle.RowName = TEXT("FC_FightingStyle");
                        Level1Entry.FeatureHandles.Add(FeatureHandle);
                        FighterRow->Progression.Add(Level1Entry);

                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        TArray<FMulticlassProgressEntry> Progression;

                        // Act
                        bool bLoaded = FMulticlassMotor::LoadClassProgression(
                            TEXT("Fighter"), 1, TestClassDataTable, TestFeatureDataTable, Progression);

                        // Assert: Valores hardcoded conhecidos
                        TestTrue("Motor deve carregar progressão", bLoaded);
                        TestTrue("Deve ter pelo menos 1 nível", Progression.Num() > 0);
                        if (Progression.Num() > 0 && Progression[0].Features.Num() > 0)
                        {
                            FMulticlassClassFeature FirstFeature = Progression[0].Features[0];
                            TestEqual("Feature Choice sem escolhas deve ter AvailableChoices = NAME_None",
                                     FirstFeature.AvailableChoices, FName(NAME_None));
                            TestFalse("Feature Choice sem escolhas não deve retornar true",
                                     FMulticlassValidationHelpers::FeatureHasAvailableChoices(FirstFeature));
                        }
                    });

                 It("deve retornar false quando ClassName é NAME_None", [this]()
                    {
                        // Arrange: Classe inválida
                        TArray<FMulticlassProgressEntry> Progression;

                        // Act
                        bool bLoaded = FMulticlassMotor::LoadClassProgression(
                            NAME_None, 1, TestClassDataTable, TestFeatureDataTable, Progression);

                        // Assert
                        TestFalse("Não deve carregar progressão com classe inválida", bLoaded);
                    });

                 It("deve retornar false quando LevelInClass é inválido (0 ou negativo)", [this]()
                    {
                        // Arrange: Nível inválido
                        FClassDataRow *FighterRow = new FClassDataRow();
                        FighterRow->Name = TEXT("Fighter");
                        FighterRow->ID = TEXT("CLASS_Fighter");
                        TestClassDataTable->AddRow(TEXT("Fighter"), *FighterRow);

                        TArray<FMulticlassProgressEntry> Progression;

                        // Act
                        bool bLoaded = FMulticlassMotor::LoadClassProgression(
                            TEXT("Fighter"), 0, TestClassDataTable, TestFeatureDataTable, Progression);

                        // Assert
                        TestFalse("Não deve carregar progressão com nível inválido", bLoaded);
                    });
             });
}

#pragma endregion MulticlassMotor Tests
