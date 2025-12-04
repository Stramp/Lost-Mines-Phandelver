// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Data/Tables/FeatDataTable.h"

#pragma endregion Includes

// ============================================================================
// FeatDataTable Tests
// ============================================================================
#pragma region FeatDataTable Tests

BEGIN_DEFINE_SPEC(FeatDataTableSpec, "MyProject2.Data.Tables.FeatDataTable",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

FFeatDataRow TestRow;

END_DEFINE_SPEC(FeatDataTableSpec)

void FeatDataTableSpec::Define()
{
    BeforeEach(
        [this]()
        {
            // Arrange: Reset row para cada teste
            TestRow = FFeatDataRow();
        });

    Describe(
        "GetPrerequisites",
        [this]()
        {
            It("should return empty array when FeatureData has no Prerequisites key",
               [this]()
               {
                   // Arrange: FeatureData vazio
                   TestRow.FeatureData.Empty();

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should return empty array", Prerequisites.Num(), 0);
               });

            It("should return empty array when Prerequisites is empty string",
               [this]()
               {
                   // Arrange: Prerequisites como string vazia
                   TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT(""));

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should return empty array", Prerequisites.Num(), 0);
               });

            It("should return array with one item when Prerequisites is single string",
               [this]()
               {
                   // Arrange: Prerequisites como string única
                   TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13"));

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should have one prerequisite", Prerequisites.Num(), 1);
                   TestEqual("Prerequisite should be Strength 13", Prerequisites[0], FName(TEXT("Strength 13")));
               });

            It("should return array with multiple items when Prerequisites has comma-separated values",
               [this]()
               {
                   // Arrange: Prerequisites como múltiplas strings separadas por vírgula
                   TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13, Dexterity 15"));

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should have two prerequisites", Prerequisites.Num(), 2);
                   TestEqual("First prerequisite should be Strength 13", Prerequisites[0], FName(TEXT("Strength 13")));
                   TestEqual("Second prerequisite should be Dexterity 15", Prerequisites[1],
                             FName(TEXT("Dexterity 15")));
               });

            It("should trim whitespace from prerequisites",
               [this]()
               {
                   // Arrange: Prerequisites com espaços extras
                   TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT("  Strength 13  ,  Dexterity 15  "));

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should have two prerequisites", Prerequisites.Num(), 2);
                   TestEqual("First prerequisite should be trimmed", Prerequisites[0], FName(TEXT("Strength 13")));
                   TestEqual("Second prerequisite should be trimmed", Prerequisites[1], FName(TEXT("Dexterity 15")));
               });

            It("should ignore empty strings in comma-separated values",
               [this]()
               {
                   // Arrange: Prerequisites com valores vazios
                   TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13,,Dexterity 15,"));

                   // Act
                   TArray<FName> Prerequisites = TestRow.GetPrerequisites();

                   // Assert
                   TestEqual("Should have two prerequisites (empty ones ignored)", Prerequisites.Num(), 2);
                   TestEqual("First prerequisite should be Strength 13", Prerequisites[0], FName(TEXT("Strength 13")));
                   TestEqual("Second prerequisite should be Dexterity 15", Prerequisites[1],
                             FName(TEXT("Dexterity 15")));
               });
        });
}

#pragma endregion FeatDataTable Tests
