// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/ChoiceHelpers.h"

#pragma endregion Includes

// ============================================================================
// Choice Helpers
// ============================================================================
#pragma region Choice Helpers

TArray<FName> ChoiceHelpers::ParseOptionsString(const FString &OptionsString)
{
    TArray<FName> Options;

    if (OptionsString.IsEmpty())
    {
        return Options;
    }

    TArray<FString> OptionsStringArray;
    OptionsString.ParseIntoArray(OptionsStringArray, TEXT(","), true);

    for (const FString &OptionStr : OptionsStringArray)
    {
        FString TrimmedOption = OptionStr.TrimStartAndEnd();
        if (!TrimmedOption.IsEmpty())
        {
            Options.Add(FName(*TrimmedOption));
        }
    }

    return Options;
}

FString ChoiceHelpers::FormatOptionsString(const TArray<FName> &Options)
{
    FString OptionsString;

    for (int32 i = 0; i < Options.Num(); ++i)
    {
        if (i > 0)
        {
            OptionsString += TEXT(",");
        }
        OptionsString += Options[i].ToString();
    }

    return OptionsString;
}

#pragma endregion Choice Helpers
