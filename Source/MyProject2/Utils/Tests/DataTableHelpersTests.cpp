// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/ItemDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// DataTableHelpers Tests
// ============================================================================
#pragma region DataTableHelpers Tests

BEGIN_DEFINE_SPEC(DataTableHelpersSpec, "MyProject2.Utils.DataTableHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

UDataTable *TestFeatDataTable;
FFeatDataRow *TestFeatRow;

END_DEFINE_SPEC(DataTableHelpersSpec)

void DataTableHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar Data Table de teste
            TestFeatDataTable = NewObject<UDataTable>();
            TestFeatDataTable->RowStruct = FFeatDataRow::StaticStruct();

            // Criar feat de teste
            TestFeatRow = new FFeatDataRow();
            TestFeatRow->Name = TEXT("Alert");
            TestFeatRow->ID = TEXT("Feat_Alert");
            TestFeatRow->Description = FText::FromString(TEXT("Test feat"));

            // Adicionar à tabela
            TestFeatDataTable->AddRow(TEXT("Feat_Alert"), *TestFeatRow);
        });

    AfterEach(
        [this]()
        {
            // Cleanup
            if (TestFeatDataTable)
            {
                TestFeatDataTable->ConditionalBeginDestroy();
            }
            if (TestFeatRow)
            {
                delete TestFeatRow;
            }
        });

    Describe(
        "FindFeatRow",
        [this]()
        {
            It("deve retornar nullptr quando FeatDataTable é nullptr",
               [this]()
               {
                   AddInfo(TEXT("Testando busca de feat com Data Table nulo"));

                   // Act
                   FFeatDataRow *Result = DataTableHelpers::FindFeatRow(TEXT("Feat_Alert"), nullptr);

                   // Assert
                   TestNull("FindFeatRow deve retornar nullptr quando Data Table é nulo", Result);
                   AddInfo(TEXT("✅ Teste passou: FindFeatRow retornou nullptr corretamente"));
               });

            It("deve retornar nullptr quando FeatName é NAME_None",
               [this]()
               {
                   AddInfo(TEXT("Testando busca de feat com nome NAME_None"));

                   // Act
                   FFeatDataRow *Result = DataTableHelpers::FindFeatRow(NAME_None, TestFeatDataTable);

                   // Assert
                   TestNull("FindFeatRow deve retornar nullptr quando FeatName é NAME_None", Result);
                   AddInfo(TEXT("✅ Teste passou: FindFeatRow retornou nullptr corretamente"));
               });

            It("deve retornar row quando FeatName corresponde ao FC_ID",
               [this]()
               {
                   AddInfo(TEXT("Testando busca de feat por FC_ID: Feat_Alert"));

                   // Act
                   FFeatDataRow *Result = DataTableHelpers::FindFeatRow(TEXT("Feat_Alert"), TestFeatDataTable);

                   // Assert
                   TestNotNull("FindFeatRow deve retornar row quando FC_ID corresponde", Result);
                   if (Result)
                   {
                       TestEqual("ID deve corresponder", Result->ID.ToString(), FString(TEXT("Feat_Alert")));
                       AddInfo(TEXT("✅ Teste passou: FindFeatRow encontrou row corretamente por FC_ID"));
                   }
               });

            It("deve retornar row quando FeatName corresponde ao Name",
               [this]()
               {
                   AddInfo(TEXT("Testando busca de feat por Name: Alert"));

                   // Act
                   FFeatDataRow *Result = DataTableHelpers::FindFeatRow(TEXT("Alert"), TestFeatDataTable);

                   // Assert
                   TestNotNull("FindFeatRow deve retornar row quando Name corresponde", Result);
                   if (Result)
                   {
                       TestEqual("Name deve corresponder", Result->Name.ToString(), FString(TEXT("Alert")));
                       AddInfo(TEXT("✅ Teste passou: FindFeatRow encontrou row corretamente por Name"));
                   }
               });

            It("deve retornar nullptr quando FeatName não existe na tabela",
               [this]()
               {
                   AddInfo(TEXT("Testando busca de feat inexistente: Feat_NonExistent"));

                   // Act
                   FFeatDataRow *Result = DataTableHelpers::FindFeatRow(TEXT("Feat_NonExistent"), TestFeatDataTable);

                   // Assert
                   TestNull("FindFeatRow deve retornar nullptr quando feat não existe na tabela", Result);
                   AddInfo(TEXT("✅ Teste passou: FindFeatRow retornou nullptr corretamente para feat inexistente"));
               });
        });

    Describe("FindRaceRow",
             [this]()
             {
                 It("should return nullptr when RaceDataTable is nullptr",
                    [this]()
                    {
                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(TEXT("Human"), nullptr);

                        // Assert
                        TestNull("Should return nullptr when table is null", Result);
                    });

                 It("should return nullptr when RaceName is NAME_None",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestRaceDataTable = NewObject<UDataTable>();
                        TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(NAME_None, TestRaceDataTable);

                        // Assert
                        TestNull("Should return nullptr when RaceName is NAME_None", Result);

                        // Cleanup
                        TestRaceDataTable->ConditionalBeginDestroy();
                    });

                 It("should return row when RaceName exists",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestRaceDataTable = NewObject<UDataTable>();
                        TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        FRaceDataRow *TestRaceRow = new FRaceDataRow();
                        TestRaceRow->Name = TEXT("Human");
                        TestRaceDataTable->AddRow(TEXT("Human"), *TestRaceRow);

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(TEXT("Human"), TestRaceDataTable);

                        // Assert
                        TestNotNull("Should return row when RaceName exists", Result);
                        if (Result)
                        {
                            TestTrue("Name should match", Result->Name == TEXT("Human"));
                        }

                        // Cleanup
                        delete TestRaceRow;
                        TestRaceDataTable->ConditionalBeginDestroy();
                    });

                 It("should return nullptr when RaceName does not exist",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestRaceDataTable = NewObject<UDataTable>();
                        TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

                        // Act
                        FRaceDataRow *Result =
                            DataTableHelpers::FindRaceRow(TEXT("NonExistentRace"), TestRaceDataTable);

                        // Assert
                        TestNull("Should return nullptr when RaceName does not exist", Result);

                        // Cleanup
                        TestRaceDataTable->ConditionalBeginDestroy();
                    });
             });

    Describe("FindClassRow",
             [this]()
             {
                 It("should return nullptr when ClassDataTable is nullptr",
                    [this]()
                    {
                        // Act
                        FClassDataRow *Result = DataTableHelpers::FindClassRow(TEXT("Fighter"), nullptr);

                        // Assert
                        TestNull("Should return nullptr when table is null", Result);
                    });

                 It("should return nullptr when ClassName is NAME_None",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestClassDataTable = NewObject<UDataTable>();
                        TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                        // Act
                        FClassDataRow *Result = DataTableHelpers::FindClassRow(NAME_None, TestClassDataTable);

                        // Assert
                        TestNull("Should return nullptr when ClassName is NAME_None", Result);

                        // Cleanup
                        TestClassDataTable->ConditionalBeginDestroy();
                    });

                 It("should return row when ClassName exists",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestClassDataTable = NewObject<UDataTable>();
                        TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                        FClassDataRow *TestClassRow = new FClassDataRow();
                        TestClassRow->FClass.Name = TEXT("Fighter");
                        TestClassDataTable->AddRow(TEXT("Fighter"), *TestClassRow);

                        // Act
                        FClassDataRow *Result = DataTableHelpers::FindClassRow(TEXT("Fighter"), TestClassDataTable);

                        // Assert
                        TestNotNull("Should return row when ClassName exists", Result);
                        if (Result)
                        {
                            TestTrue("ClassName should match", Result->FClass.Name == TEXT("Fighter"));
                        }

                        // Cleanup
                        delete TestClassRow;
                        TestClassDataTable->ConditionalBeginDestroy();
                    });

                 It("should return nullptr when ClassName does not exist",
                    [this]()
                    {
                        // Arrange
                        UDataTable *TestClassDataTable = NewObject<UDataTable>();
                        TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                        // Act
                        FClassDataRow *Result =
                            DataTableHelpers::FindClassRow(TEXT("NonExistentClass"), TestClassDataTable);

                        // Assert
                        TestNull("Should return nullptr when ClassName does not exist", Result);

                        // Cleanup
                        TestClassDataTable->ConditionalBeginDestroy();
                    });
             });

    Describe("GetAllSkillNames",
             [this]()
             {
                 It("deve retornar array vazio quando ProficiencyDataTable é nullptr",
                    [this]()
                    {
                        AddInfo(TEXT("Testando GetAllSkillNames com Data Table nulo"));

                        // Act
                        TArray<FName> Result = DataTableHelpers::GetAllSkillNames(nullptr);

                        // Assert
                        TestEqual("GetAllSkillNames deve retornar array vazio quando Data Table é nulo", Result.Num(),
                                  0);
                        AddInfo(TEXT("✅ Teste passou: GetAllSkillNames retornou array vazio corretamente"));
                    });

                 It("deve retornar array vazio quando Data Table não tem skills",
                    [this]()
                    {
                        AddInfo(TEXT("Testando GetAllSkillNames com Data Table sem skills"));

                        // Arrange
                        UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                        TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                        // Adicionar apenas uma proficiência que não é Skill
                        FProficiencyDataRow *TestRow = new FProficiencyDataRow();
                        TestRow->Name = TEXT("Simple Weapons");
                        TestRow->ID = TEXT("PW_Simple_Weapons");
                        TestRow->Type = TEXT("Weapon");
                        TestProficiencyDataTable->AddRow(TEXT("PW_Simple_Weapons"), *TestRow);

                        // Act
                        TArray<FName> Result = DataTableHelpers::GetAllSkillNames(TestProficiencyDataTable);

                        // Assert
                        TestEqual("GetAllSkillNames deve retornar array vazio quando não há skills", Result.Num(), 0);
                        AddInfo(TEXT("✅ Teste passou: GetAllSkillNames retornou array vazio quando não há skills"));

                        // Cleanup
                        delete TestRow;
                        TestProficiencyDataTable->ConditionalBeginDestroy();
                    });

                 It("deve retornar todas as skills quando Data Table tem skills",
                    [this]()
                    {
                        AddInfo(TEXT("Testando GetAllSkillNames com Data Table contendo skills"));

                        // Arrange
                        UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                        TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                        // Adicionar 3 skills de teste
                        FProficiencyDataRow *Skill1 = new FProficiencyDataRow();
                        Skill1->Name = TEXT("Acrobatics");
                        Skill1->ID = TEXT("PSK_Acrobatics");
                        Skill1->Type = TEXT("Skill");
                        TestProficiencyDataTable->AddRow(TEXT("PSK_Acrobatics"), *Skill1);

                        FProficiencyDataRow *Skill2 = new FProficiencyDataRow();
                        Skill2->Name = TEXT("Athletics");
                        Skill2->ID = TEXT("PSK_Athletics");
                        Skill2->Type = TEXT("Skill");
                        TestProficiencyDataTable->AddRow(TEXT("PSK_Athletics"), *Skill2);

                        FProficiencyDataRow *Skill3 = new FProficiencyDataRow();
                        Skill3->Name = TEXT("Stealth");
                        Skill3->ID = TEXT("PSK_Stealth");
                        Skill3->Type = TEXT("Skill");
                        TestProficiencyDataTable->AddRow(TEXT("PSK_Stealth"), *Skill3);

                        // Adicionar uma proficiência que não é Skill (para garantir que filtra corretamente)
                        FProficiencyDataRow *Weapon = new FProficiencyDataRow();
                        Weapon->Name = TEXT("Simple Weapons");
                        Weapon->ID = TEXT("PW_Simple_Weapons");
                        Weapon->Type = TEXT("Weapon");
                        TestProficiencyDataTable->AddRow(TEXT("PW_Simple_Weapons"), *Weapon);

                        // Act
                        TArray<FName> Result = DataTableHelpers::GetAllSkillNames(TestProficiencyDataTable);

                        // Assert
                        TestEqual("GetAllSkillNames deve retornar 3 skills", Result.Num(), 3);
                        TestTrue("Result deve conter Acrobatics", Result.Contains(TEXT("Acrobatics")));
                        TestTrue("Result deve conter Athletics", Result.Contains(TEXT("Athletics")));
                        TestTrue("Result deve conter Stealth", Result.Contains(TEXT("Stealth")));
                        TestFalse("Result não deve conter Simple Weapons (não é Skill)",
                                  Result.Contains(TEXT("Simple Weapons")));
                        AddInfo(TEXT("✅ Teste passou: GetAllSkillNames retornou todas as skills corretamente"));

                        // Cleanup
                        delete Skill1;
                        delete Skill2;
                        delete Skill3;
                        delete Weapon;
                        TestProficiencyDataTable->ConditionalBeginDestroy();
                    });
             });

    Describe(
        "GetAllLanguageNames",
        [this]()
        {
            It("deve retornar array vazio quando ProficiencyDataTable é nullptr",
               [this]()
               {
                   AddInfo(TEXT("Testando GetAllLanguageNames com Data Table nulo"));

                   // Act
                   TArray<FName> Result = DataTableHelpers::GetAllLanguageNames(nullptr);

                   // Assert
                   TestEqual("GetAllLanguageNames deve retornar array vazio quando Data Table é nulo", Result.Num(), 0);
                   AddInfo(TEXT("✅ Teste passou: GetAllLanguageNames retornou array vazio corretamente"));
               });

            It("deve retornar array vazio quando Data Table não tem languages",
               [this]()
               {
                   AddInfo(TEXT("Testando GetAllLanguageNames com Data Table sem languages"));

                   // Arrange
                   UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                   TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                   // Adicionar apenas uma proficiência que não é Language
                   FProficiencyDataRow *TestRow = new FProficiencyDataRow();
                   TestRow->Name = TEXT("Simple Weapons");
                   TestRow->ID = TEXT("PW_Simple_Weapons");
                   TestRow->Type = TEXT("Weapon");
                   TestProficiencyDataTable->AddRow(TEXT("PW_Simple_Weapons"), *TestRow);

                   // Act
                   TArray<FName> Result = DataTableHelpers::GetAllLanguageNames(TestProficiencyDataTable);

                   // Assert
                   TestEqual("GetAllLanguageNames deve retornar array vazio quando não há languages", Result.Num(), 0);
                   AddInfo(TEXT("✅ Teste passou: GetAllLanguageNames retornou array vazio quando não há languages"));

                   // Cleanup
                   delete TestRow;
                   TestProficiencyDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar todos os languages quando Data Table tem languages",
               [this]()
               {
                   AddInfo(TEXT("Testando GetAllLanguageNames com Data Table contendo languages"));

                   // Arrange
                   UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                   TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                   // Adicionar 3 languages de teste
                   FProficiencyDataRow *Lang1 = new FProficiencyDataRow();
                   Lang1->Name = TEXT("Common");
                   Lang1->ID = TEXT("PL_Common");
                   Lang1->Type = TEXT("Language");
                   TestProficiencyDataTable->AddRow(TEXT("PL_Common"), *Lang1);

                   FProficiencyDataRow *Lang2 = new FProficiencyDataRow();
                   Lang2->Name = TEXT("Elvish");
                   Lang2->ID = TEXT("PL_Elvish");
                   Lang2->Type = TEXT("Language");
                   TestProficiencyDataTable->AddRow(TEXT("PL_Elvish"), *Lang2);

                   FProficiencyDataRow *Lang3 = new FProficiencyDataRow();
                   Lang3->Name = TEXT("Draconic");
                   Lang3->ID = TEXT("PL_Draconic");
                   Lang3->Type = TEXT("Language");
                   TestProficiencyDataTable->AddRow(TEXT("PL_Draconic"), *Lang3);

                   // Adicionar uma proficiência que não é Language (para garantir que filtra corretamente)
                   FProficiencyDataRow *Weapon = new FProficiencyDataRow();
                   Weapon->Name = TEXT("Simple Weapons");
                   Weapon->ID = TEXT("PW_Simple_Weapons");
                   Weapon->Type = TEXT("Weapon");
                   TestProficiencyDataTable->AddRow(TEXT("PW_Simple_Weapons"), *Weapon);

                   // Act
                   TArray<FName> Result = DataTableHelpers::GetAllLanguageNames(TestProficiencyDataTable);

                   // Assert
                   TestEqual("GetAllLanguageNames deve retornar 3 languages", Result.Num(), 3);
                   TestTrue("Result deve conter Common", Result.Contains(TEXT("Common")));
                   TestTrue("Result deve conter Elvish", Result.Contains(TEXT("Elvish")));
                   TestTrue("Result deve conter Draconic", Result.Contains(TEXT("Draconic")));
                   TestFalse("Result não deve conter Simple Weapons (não é Language)",
                             Result.Contains(TEXT("Simple Weapons")));
                   AddInfo(TEXT("✅ Teste passou: GetAllLanguageNames retornou todos os languages corretamente"));

                   // Cleanup
                   delete Lang1;
                   delete Lang2;
                   delete Lang3;
                   delete Weapon;
                   TestProficiencyDataTable->ConditionalBeginDestroy();
               });
        });

    // ============================================================================
    // Data Table Type Validation Tests
    // ============================================================================
    Describe(
        "Data Table Type Validation",
        [this]()
        {
            It("deve retornar true quando RaceDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestRaceDataTable = NewObject<UDataTable>();
                   TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsRaceDataTable(TestRaceDataTable);

                   // Assert
                   TestTrue("IsRaceDataTable deve retornar true para RaceDataTable correto", Result);

                   // Cleanup
                   TestRaceDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar false quando DataTable não é RaceDataTable",
               [this]()
               {
                   // Arrange
                   UDataTable *TestClassDataTable = NewObject<UDataTable>();
                   TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsRaceDataTable(TestClassDataTable);

                   // Assert
                   TestFalse("IsRaceDataTable deve retornar false para ClassDataTable", Result);

                   // Cleanup
                   TestClassDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar false quando DataTable é nullptr",
               [this]()
               {
                   // Act
                   bool Result = DataTableHelpers::IsRaceDataTable(nullptr);

                   // Assert
                   TestFalse("IsRaceDataTable deve retornar false para nullptr", Result);
               });

            It("deve retornar true quando ClassDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestClassDataTable = NewObject<UDataTable>();
                   TestClassDataTable->RowStruct = FClassDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsClassDataTable(TestClassDataTable);

                   // Assert
                   TestTrue("IsClassDataTable deve retornar true para ClassDataTable correto", Result);

                   // Cleanup
                   TestClassDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar false quando DataTable não é ClassDataTable",
               [this]()
               {
                   // Arrange
                   UDataTable *TestRaceDataTable = NewObject<UDataTable>();
                   TestRaceDataTable->RowStruct = FRaceDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsClassDataTable(TestRaceDataTable);

                   // Assert
                   TestFalse("IsClassDataTable deve retornar false para RaceDataTable", Result);

                   // Cleanup
                   TestRaceDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar true quando BackgroundDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestBackgroundDataTable = NewObject<UDataTable>();
                   TestBackgroundDataTable->RowStruct = FBackgroundDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsBackgroundDataTable(TestBackgroundDataTable);

                   // Assert
                   TestTrue("IsBackgroundDataTable deve retornar true para BackgroundDataTable correto", Result);

                   // Cleanup
                   TestBackgroundDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar true quando FeatDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestFeatDataTable = NewObject<UDataTable>();
                   TestFeatDataTable->RowStruct = FFeatDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsFeatDataTable(TestFeatDataTable);

                   // Assert
                   TestTrue("IsFeatDataTable deve retornar true para FeatDataTable correto", Result);

                   // Cleanup
                   TestFeatDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar true quando FeatureDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestFeatureDataTable = NewObject<UDataTable>();
                   TestFeatureDataTable->RowStruct = FFeatureDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsFeatureDataTable(TestFeatureDataTable);

                   // Assert
                   TestTrue("IsFeatureDataTable deve retornar true para FeatureDataTable correto", Result);

                   // Cleanup
                   TestFeatureDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar true quando ProficiencyDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                   TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsProficiencyDataTable(TestProficiencyDataTable);

                   // Assert
                   TestTrue("IsProficiencyDataTable deve retornar true para ProficiencyDataTable correto", Result);

                   // Cleanup
                   TestProficiencyDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar true quando ItemDataTable tem RowStruct correto",
               [this]()
               {
                   // Arrange
                   UDataTable *TestItemDataTable = NewObject<UDataTable>();
                   TestItemDataTable->RowStruct = FItemDataRow::StaticStruct();

                   // Act
                   bool Result = DataTableHelpers::IsItemDataTable(TestItemDataTable);

                   // Assert
                   TestTrue("IsItemDataTable deve retornar true para ItemDataTable correto", Result);

                   // Cleanup
                   TestItemDataTable->ConditionalBeginDestroy();
               });

            It("deve retornar false quando DataTable não tem RowStruct configurado",
               [this]()
               {
                   // Arrange
                   UDataTable *TestDataTable = NewObject<UDataTable>();
                   // Não configura RowStruct

                   // Act
                   bool Result = DataTableHelpers::IsRaceDataTable(TestDataTable);

                   // Assert
                   TestFalse("IsRaceDataTable deve retornar false quando RowStruct não está configurado", Result);

                   // Cleanup
                   TestDataTable->ConditionalBeginDestroy();
               });
        });
}

#pragma endregion DataTableHelpers Tests
