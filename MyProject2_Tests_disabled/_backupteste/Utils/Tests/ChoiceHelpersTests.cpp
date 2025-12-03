// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/ChoiceHelpers.h"

#pragma endregion Includes

// ============================================================================
// ChoiceHelpers Tests
// ============================================================================
#pragma region ChoiceHelpers Tests

BEGIN_DEFINE_SPEC(ChoiceHelpersSpec, "MyProject2.Utils.ChoiceHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(ChoiceHelpersSpec)

void ChoiceHelpersSpec::Define()
{
    Describe("ParseOptionsString",
             [this]()
             {
                 It("should parse comma-separated string into array",
                    [this]()
                    {
                        // Arrange
                        FString OptionsString = TEXT("Archery,Defense,Dueling");

                        // Act
                        TArray<FName> Result = ChoiceHelpers::ParseOptionsString(OptionsString);

                        // Assert
                        TestTrue("Should have 3 options", Result.Num() == 3);
                        TestTrue("First should be Archery", Result[0] == TEXT("Archery"));
                        TestTrue("Second should be Defense", Result[1] == TEXT("Defense"));
                        TestTrue("Third should be Dueling", Result[2] == TEXT("Dueling"));
                    });

                 It("should trim whitespace from options",
                    [this]()
                    {
                        // Arrange
                        FString OptionsString = TEXT("  Archery  ,  Defense  ,  Dueling  ");

                        // Act
                        TArray<FName> Result = ChoiceHelpers::ParseOptionsString(OptionsString);

                        // Assert
                        TestEqual("Should have 3 options", Result.Num(), 3);
                        TestTrue("First should be trimmed", Result[0] == TEXT("Archery"));
                        TestTrue("Second should be trimmed", Result[1] == TEXT("Defense"));
                        TestTrue("Third should be trimmed", Result[2] == TEXT("Dueling"));
                    });

                 It("should return empty array for empty string",
                    [this]()
                    {
                        // Arrange
                        FString EmptyString = TEXT("");

                        // Act
                        TArray<FName> Result = ChoiceHelpers::ParseOptionsString(EmptyString);

                        // Assert
                        TestTrue("Should return empty array", Result.Num() == 0);
                    });

                 It("should ignore empty strings between commas",
                    [this]()
                    {
                        // Arrange
                        FString OptionsString = TEXT("Archery,,Defense,");

                        // Act
                        TArray<FName> Result = ChoiceHelpers::ParseOptionsString(OptionsString);

                        // Assert
                        TestTrue("Should have 2 options (empty ones ignored)", Result.Num() == 2);
                        TestTrue("First should be Archery", Result[0] == TEXT("Archery"));
                        TestTrue("Second should be Defense", Result[1] == TEXT("Defense"));
                    });
             });

    Describe("FormatOptionsString",
             [this]()
             {
                 It("should format array with multiple options",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> Options;
                        Options.Add(TEXT("Archery"));
                        Options.Add(TEXT("Defense"));
                        Options.Add(TEXT("Dueling"));

                        // Act
                        FString Result = ChoiceHelpers::FormatOptionsString(Options);

                        // Assert
                        TestTrue("Should contain Archery", Result.Contains(TEXT("Archery")));
                        TestTrue("Should contain Defense", Result.Contains(TEXT("Defense")));
                        TestTrue("Should contain Dueling", Result.Contains(TEXT("Dueling")));
                    });

                 It("should return empty string for empty array",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> EmptyOptions;

                        // Act
                        FString Result = ChoiceHelpers::FormatOptionsString(EmptyOptions);

                        // Assert
                        TestTrue("Should return empty string", Result.IsEmpty());
                    });

                 It("should format single option without commas",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> Options;
                        Options.Add(TEXT("Archery"));

                        // Act
                        FString Result = ChoiceHelpers::FormatOptionsString(Options);

                        // Assert
                        TestTrue("Should return single option", Result == TEXT("Archery"));
                    });
             });
}

#pragma endregion ChoiceHelpers Tests
