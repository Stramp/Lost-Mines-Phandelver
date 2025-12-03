// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Misc/AutomationTest.h"
#include "Utils/FormattingHelpers.h"

#pragma endregion Includes

// ============================================================================
// FormattingHelpers Tests
// ============================================================================
#pragma region FormattingHelpers Tests

BEGIN_DEFINE_SPEC(FormattingHelpersSpec, "MyProject2.Utils.FormattingHelpers",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

END_DEFINE_SPEC(FormattingHelpersSpec)

void FormattingHelpersSpec::Define()
{
    Describe("FormatRaceDisplay",
             [this]()
             {
                 It("should format race name only when SubraceName is NAME_None",
                    [this]()
                    {
                        // Act
                        FString Result = FormattingHelpers::FormatRaceDisplay(TEXT("Elf"), NAME_None);

                        // Assert
                        TestTrue("Should return only race name", Result == TEXT("Elf"));
                    });

                 It("should format race with subrace when SubraceName is provided",
                    [this]()
                    {
                        // Act
                        FString Result = FormattingHelpers::FormatRaceDisplay(TEXT("Elf"), TEXT("High Elf"));

                        // Assert
                        TestTrue("Should return race with subrace", Result == TEXT("Elf (High Elf)"));
                    });

                 It("should return 'None (High Elf)' string when RaceName is NAME_None but SubraceName is provided",
                    [this]()
                    {
                        // Act
                        FString Result = FormattingHelpers::FormatRaceDisplay(NAME_None, TEXT("High Elf"));

                        // Assert
                        // A função retorna RaceName.ToString() + " (" + SubraceName.ToString() + ")"
                        // NAME_None.ToString() = "None", então resultado: "None (High Elf)"
                        TestTrue("Should return 'None (High Elf)' string", Result == TEXT("None (High Elf)"));
                    });

                 It("should format race only when SubraceName is NAME_None even if provided",
                    [this]()
                    {
                        // Act
                        FString Result = FormattingHelpers::FormatRaceDisplay(TEXT("Human"), NAME_None);

                        // Assert
                        TestTrue("Should return only race name", Result == TEXT("Human"));
                    });
             });

    Describe("FormatProficienciesList",
             [this]()
             {
                 It("should format array with multiple proficiencies",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> Proficiencies;
                        Proficiencies.Add(TEXT("Athletics"));
                        Proficiencies.Add(TEXT("Acrobatics"));
                        Proficiencies.Add(TEXT("Stealth"));

                        // Act
                        FString Result = FormattingHelpers::FormatProficienciesList(Proficiencies);

                        // Assert
                        TestTrue("Should contain all proficiencies", Result.Contains(TEXT("Athletics")));
                        TestTrue("Should contain all proficiencies", Result.Contains(TEXT("Acrobatics")));
                        TestTrue("Should contain all proficiencies", Result.Contains(TEXT("Stealth")));
                    });

                 It("should return empty string for empty array",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> EmptyProficiencies;

                        // Act
                        FString Result = FormattingHelpers::FormatProficienciesList(EmptyProficiencies);

                        // Assert
                        TestTrue("Should return empty string", Result.IsEmpty());
                    });

                 It("should format single proficiency without commas",
                    [this]()
                    {
                        // Arrange
                        TArray<FName> Proficiencies;
                        Proficiencies.Add(TEXT("Athletics"));

                        // Act
                        FString Result = FormattingHelpers::FormatProficienciesList(Proficiencies);

                        // Assert
                        TestTrue("Should return single proficiency", Result == TEXT("Athletics"));
                    });
             });

    Describe("FormatAbilityScores",
             [this]()
             {
                 It("should format complete ability scores map",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 15);
                        AbilityScores.Add(TEXT("Dexterity"), 14);
                        AbilityScores.Add(TEXT("Constitution"), 13);

                        // Act
                        FString Result = FormattingHelpers::FormatAbilityScores(AbilityScores);

                        // Assert
                        TestTrue("Should contain Strength", Result.Contains(TEXT("Strength")));
                        TestTrue("Should contain Dexterity", Result.Contains(TEXT("Dexterity")));
                        TestTrue("Should contain Constitution", Result.Contains(TEXT("Constitution")));
                    });

                 It("should return 'FALTANDO!' for all abilities when map is empty",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> EmptyScores;

                        // Act
                        FString Result = FormattingHelpers::FormatAbilityScores(EmptyScores);

                        // Assert
                        // A função itera sobre GetAbilityScoreNames() e marca todos como "FALTANDO!" quando não estão
                        // no map
                        TestTrue("Should contain 'FALTANDO!' for missing abilities",
                                 Result.Contains(TEXT("FALTANDO!")));
                        TestTrue("Should not be empty", !Result.IsEmpty());
                    });

                 It("should format ability scores with values",
                    [this]()
                    {
                        // Arrange
                        TMap<FName, int32> AbilityScores;
                        AbilityScores.Add(TEXT("Strength"), 15);

                        // Act
                        FString Result = FormattingHelpers::FormatAbilityScores(AbilityScores);

                        // Assert
                        TestTrue("Should contain ability name", Result.Contains(TEXT("Strength")));
                        TestTrue("Should contain ability value", Result.Contains(TEXT("15")));
                    });
             });
}

#pragma endregion FormattingHelpers Tests
