// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// CharacterSheetHelpers Tests
// ============================================================================
#pragma region CharacterSheetHelpers Tests

BEGIN_DEFINE_SPEC(CharacterSheetHelpersSpec, "MyProject2.Utils.CharacterSheetHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

FFeatDataRow *TestFeatRow;
TMap<FName, int32> TestAbilityScores;

END_DEFINE_SPEC(CharacterSheetHelpersSpec)

void CharacterSheetHelpersSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Criar feat de teste
            TestFeatRow = new FFeatDataRow();
            TestFeatRow->Name = TEXT("Test Feat");
            TestFeatRow->ID = TEXT("Feat_Test");

            // Criar ability scores de teste
            TestAbilityScores.Empty();
            TestAbilityScores.Add(TEXT("Strength"), 15);
            TestAbilityScores.Add(TEXT("Dexterity"), 13);
            TestAbilityScores.Add(TEXT("Constitution"), 14);
            TestAbilityScores.Add(TEXT("Intelligence"), 12);
            TestAbilityScores.Add(TEXT("Wisdom"), 10);
            TestAbilityScores.Add(TEXT("Charisma"), 8);
        });

    AfterEach(
        [this]()
        {
            // Cleanup
            if (TestFeatRow)
            {
                delete TestFeatRow;
            }
            TestAbilityScores.Empty();
        });

    Describe("MeetsFeatPrerequisites",
             [this]()
             {
                 It("should return false when Row is nullptr",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(nullptr, TestAbilityScores);

                        // Assert
                        TestFalse("Should return false when Row is nullptr", Result);
                    });

                 It("should return true when feat has no prerequisites",
                    [this]()
                    {
                        // Arrange: Feat sem pré-requisitos
                        TestFeatRow->FeatureData.Empty();

                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(TestFeatRow, TestAbilityScores);

                        // Assert
                        TestTrue("Should return true when no prerequisites", Result);
                    });

                 It("should return true when all prerequisites are met",
                    [this]()
                    {
                        // Arrange: Feat com pré-requisito atendido
                        TestFeatRow->FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13"));
                        // Strength = 15 >= 13 ✓

                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(TestFeatRow, TestAbilityScores);

                        // Assert
                        TestTrue("Should return true when prerequisites are met", Result);
                    });

                 It("should return false when prerequisite is not met",
                    [this]()
                    {
                        // Arrange: Feat com pré-requisito não atendido
                        TestFeatRow->FeatureData.Add(TEXT("Prerequisites"), TEXT("Charisma 15"));
                        // Charisma = 8 < 15 ✗

                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(TestFeatRow, TestAbilityScores);

                        // Assert
                        TestFalse("Should return false when prerequisite is not met", Result);
                    });

                 It("should return true when all multiple prerequisites are met",
                    [this]()
                    {
                        // Arrange: Feat com múltiplos pré-requisitos atendidos
                        TestFeatRow->FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13, Dexterity 12"));
                        // Strength = 15 >= 13 ✓, Dexterity = 13 >= 12 ✓

                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(TestFeatRow, TestAbilityScores);

                        // Assert
                        TestTrue("Should return true when all prerequisites are met", Result);
                    });

                 It("should return false when any prerequisite is not met",
                    [this]()
                    {
                        // Arrange: Feat com um pré-requisito não atendido
                        TestFeatRow->FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13, Charisma 15"));
                        // Strength = 15 >= 13 ✓, Charisma = 8 < 15 ✗

                        // Act
                        bool Result = CharacterSheetHelpers::MeetsFeatPrerequisites(TestFeatRow, TestAbilityScores);

                        // Assert
                        TestFalse("Should return false when any prerequisite is not met", Result);
                    });
             });

    Describe(
        "ValidateAbilityScorePrerequisite",
        [this]()
        {
            It("should return true when Prerequisite is NAME_None",
               [this]()
               {
                   // Act
                   bool Result = CharacterSheetHelpers::ValidateAbilityScorePrerequisite(NAME_None, TestAbilityScores);

                   // Assert
                   TestTrue("Should return true when Prerequisite is NAME_None", Result);
               });

            It("should return true when ability score meets requirement",
               [this]()
               {
                   // Act: Strength 13, temos Strength 15
                   bool Result =
                       CharacterSheetHelpers::ValidateAbilityScorePrerequisite(TEXT("Strength 13"), TestAbilityScores);

                   // Assert
                   TestTrue("Should return true when score meets requirement", Result);
               });

            It("should return false when ability score does not meet requirement",
               [this]()
               {
                   // Act: Charisma 15, temos Charisma 8
                   bool Result =
                       CharacterSheetHelpers::ValidateAbilityScorePrerequisite(TEXT("Charisma 15"), TestAbilityScores);

                   // Assert
                   TestFalse("Should return false when score does not meet requirement", Result);
               });

            It("should return false when ability score is not in map",
               [this]()
               {
                   // Arrange: Ability score não existe no map
                   TMap<FName, int32> EmptyScores;

                   // Act
                   bool Result =
                       CharacterSheetHelpers::ValidateAbilityScorePrerequisite(TEXT("Strength 13"), EmptyScores);

                   // Assert
                   TestFalse("Should return false when ability score is not in map", Result);
               });
        });

    Describe("GetAbilityScoreNames",
             [this]()
             {
                 It("should return array with 6 ability score names",
                    [this]()
                    {
                        // Act
                        TArray<FName> Result = CharacterSheetHelpers::GetAbilityScoreNames();

                        // Assert
                        TestEqual("Should have 6 ability scores", Result.Num(), 6);
                    });

                 It("should return correct ability score names in order",
                    [this]()
                    {
                        // Act
                        TArray<FName> Result = CharacterSheetHelpers::GetAbilityScoreNames();

                        // Assert
                        TestTrue("First should be Strength", Result[0] == TEXT("Strength"));
                        TestTrue("Second should be Dexterity", Result[1] == TEXT("Dexterity"));
                        TestTrue("Third should be Constitution", Result[2] == TEXT("Constitution"));
                        TestTrue("Fourth should be Intelligence", Result[3] == TEXT("Intelligence"));
                        TestTrue("Fifth should be Wisdom", Result[4] == TEXT("Wisdom"));
                        TestTrue("Sixth should be Charisma", Result[5] == TEXT("Charisma"));
                    });
             });

    Describe("CanTakeFeatAtLevel",
             [this]()
             {
                 It("should return true for level 4",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(4);

                        // Assert
                        TestTrue("Level 4 should allow feat", Result);
                    });

                 It("should return true for level 8",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(8);

                        // Assert
                        TestTrue("Level 8 should allow feat", Result);
                    });

                 It("should return true for level 12",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(12);

                        // Assert
                        TestTrue("Level 12 should allow feat", Result);
                    });

                 It("should return true for level 16",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(16);

                        // Assert
                        TestTrue("Level 16 should allow feat", Result);
                    });

                 It("should return true for level 19",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(19);

                        // Assert
                        TestTrue("Level 19 should allow feat", Result);
                    });

                 It("should return false for level 1",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(1);

                        // Assert
                        TestFalse("Level 1 should not allow feat", Result);
                    });

                 It("should return false for level 3",
                    [this]()
                    {
                        // Act
                        bool Result = CharacterSheetHelpers::CanTakeFeatAtLevel(3);

                        // Assert
                        TestFalse("Level 3 should not allow feat", Result);
                    });
             });

    Describe("CreatePointBuyMapFromData",
             [this]()
             {
                 It("should create map with all ability scores",
                    [this]()
                    {
                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreatePointBuyMapFromData(3, 2, 1, 0, 0, 0);

                        // Assert
                        TestEqual("Should have 6 abilities", Result.Num(), 6);
                        TestEqual("Strength should be 3", Result.FindRef(TEXT("Strength")), 3);
                        TestEqual("Dexterity should be 2", Result.FindRef(TEXT("Dexterity")), 2);
                        TestEqual("Constitution should be 1", Result.FindRef(TEXT("Constitution")), 1);
                    });

                 It("should create map with all zeros",
                    [this]()
                    {
                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreatePointBuyMapFromData(0, 0, 0, 0, 0, 0);

                        // Assert
                        TestEqual("Should have 6 abilities", Result.Num(), 6);
                        TestEqual("All values should be 0", Result.FindRef(TEXT("Strength")), 0);
                    });

                 It("should create map with maximum values",
                    [this]()
                    {
                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreatePointBuyMapFromData(7, 7, 7, 7, 7, 7);

                        // Assert
                        TestEqual("Should have 6 abilities", Result.Num(), 6);
                        TestEqual("All values should be 7", Result.FindRef(TEXT("Strength")), 7);
                    });
             });

    Describe("CreateBaseScoresFromPointBuy",
             [this]()
             {
                 It("should calculate base scores correctly",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 3);
                        PointBuyMap.Add(TEXT("Dexterity"), 2);

                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);

                        // Assert
                        // BASE_ABILITY_SCORE = 8, então 8 + 3 = 11, 8 + 2 = 10
                        TestEqual("Strength should be 11", Result.FindRef(TEXT("Strength")), 11);
                        TestEqual("Dexterity should be 10", Result.FindRef(TEXT("Dexterity")), 10);
                    });

                 It("should return empty map for empty PointBuyMap",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> EmptyMap;

                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(EmptyMap);

                        // Assert
                        TestEqual("Should return empty map", Result.Num(), 0);
                    });

                 It("should calculate base score for ability not in map as BASE_ABILITY_SCORE",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> PointBuyMap;
                        PointBuyMap.Add(TEXT("Strength"), 3);
                        // Dexterity não está no map

                        // Act
                        TMap<FName, int32> Result = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);

                        // Assert
                        // Apenas Strength deve estar no resultado
                        TestEqual("Should have only Strength", Result.Num(), 1);
                        TestEqual("Strength should be 11", Result.FindRef(TEXT("Strength")), 11);
                    });
             });

    Describe("GetSkillNames",
             [this]()
             {
                 It("deve retornar array hardcoded quando ProficiencyDataTable é nullptr",
                    [this]()
                    {
                        AddInfo(TEXT("Testando GetSkillNames com ProficiencyDataTable nullptr (fallback hardcoded)"));

                        // Act
                        TArray<FName> Result = CharacterSheetHelpers::GetSkillNames(nullptr);

                        // Assert
                        TestEqual("GetSkillNames deve retornar 18 skills hardcoded quando Data Table é nulo",
                                  Result.Num(), 18);
                        TestTrue("Result deve conter Acrobatics (hardcoded)", Result.Contains(TEXT("Acrobatics")));
                        TestTrue("Result deve conter Athletics (hardcoded)", Result.Contains(TEXT("Athletics")));
                        TestTrue("Result deve conter Stealth (hardcoded)", Result.Contains(TEXT("Stealth")));
                        AddInfo(TEXT("✅ Teste passou: GetSkillNames retornou array hardcoded corretamente"));
                    });

                 It("deve retornar skills do Data Table quando ProficiencyDataTable é fornecido",
                    [this]()
                    {
                        AddInfo(TEXT("Testando GetSkillNames com ProficiencyDataTable (Data-Driven)"));

                        // Arrange
                        UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                        TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                        // Adicionar 2 skills de teste
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

                        // Act
                        TArray<FName> Result = CharacterSheetHelpers::GetSkillNames(TestProficiencyDataTable);

                        // Assert
                        TestEqual("GetSkillNames deve retornar 2 skills do Data Table", Result.Num(), 2);
                        TestTrue("Result deve conter Acrobatics (do Data Table)", Result.Contains(TEXT("Acrobatics")));
                        TestTrue("Result deve conter Athletics (do Data Table)", Result.Contains(TEXT("Athletics")));
                        AddInfo(TEXT("✅ Teste passou: GetSkillNames retornou skills do Data Table corretamente"));

                        // Cleanup
                        delete Skill1;
                        delete Skill2;
                        TestProficiencyDataTable->ConditionalBeginDestroy();
                    });
             });

    Describe(
        "GetAvailableLanguageNames",
        [this]()
        {
            It("deve retornar array hardcoded quando ProficiencyDataTable é nullptr",
               [this]()
               {
                   AddInfo(TEXT(
                       "Testando GetAvailableLanguageNames com ProficiencyDataTable nullptr (fallback hardcoded)"));

                   // Act
                   TArray<FName> Result = CharacterSheetHelpers::GetAvailableLanguageNames(nullptr);

                   // Assert
                   TestEqual("GetAvailableLanguageNames deve retornar languages hardcoded quando Data Table é nulo",
                             Result.Num(), 16);
                   TestTrue("Result deve conter Common (hardcoded)", Result.Contains(TEXT("Common")));
                   TestTrue("Result deve conter Elvish (hardcoded)", Result.Contains(TEXT("Elvish")));
                   TestTrue("Result deve conter Draconic (hardcoded)", Result.Contains(TEXT("Draconic")));
                   AddInfo(TEXT("✅ Teste passou: GetAvailableLanguageNames retornou array hardcoded corretamente"));
               });

            It("deve retornar languages do Data Table quando ProficiencyDataTable é fornecido",
               [this]()
               {
                   AddInfo(TEXT("Testando GetAvailableLanguageNames com ProficiencyDataTable (Data-Driven)"));

                   // Arrange
                   UDataTable *TestProficiencyDataTable = NewObject<UDataTable>();
                   TestProficiencyDataTable->RowStruct = FProficiencyDataRow::StaticStruct();

                   // Adicionar 2 languages de teste
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

                   // Act
                   TArray<FName> Result = CharacterSheetHelpers::GetAvailableLanguageNames(TestProficiencyDataTable);

                   // Assert
                   TestEqual("GetAvailableLanguageNames deve retornar 2 languages do Data Table", Result.Num(), 2);
                   TestTrue("Result deve conter Common (do Data Table)", Result.Contains(TEXT("Common")));
                   TestTrue("Result deve conter Elvish (do Data Table)", Result.Contains(TEXT("Elvish")));
                   AddInfo(TEXT(
                       "✅ Teste passou: GetAvailableLanguageNames retornou languages do Data Table corretamente"));

                   // Cleanup
                   delete Lang1;
                   delete Lang2;
                   TestProficiencyDataTable->ConditionalBeginDestroy();
               });
        });
}

#pragma endregion CharacterSheetHelpers Tests
