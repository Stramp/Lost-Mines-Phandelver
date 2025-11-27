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
            TestFeatRow->FC_ID = TEXT("Feat_Alert");
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
                       TestEqual("FC_ID deve corresponder", Result->FC_ID.ToString(), FString(TEXT("Feat_Alert")));
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
                        TestRaceRow->RaceName = TEXT("Human");
                        TestRaceDataTable->AddRow(TEXT("Human"), *TestRaceRow);

                        // Act
                        FRaceDataRow *Result = DataTableHelpers::FindRaceRow(TEXT("Human"), TestRaceDataTable);

                        // Assert
                        TestNotNull("Should return row when RaceName exists", Result);
                        if (Result)
                        {
                            TestTrue("RaceName should match", Result->RaceName == TEXT("Human"));
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
}

#pragma endregion DataTableHelpers Tests
