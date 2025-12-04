// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "FormattingHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// String Formatting
// ============================================================================
#pragma region String Formatting

FString FormattingHelpers::FormatRaceDisplay(FName RaceName, FName SubraceName)
{
    FString RaceDisplay = RaceName.ToString();
    if (SubraceName != NAME_None)
    {
        RaceDisplay += TEXT(" (") + SubraceName.ToString() + TEXT(")");
    }
    return RaceDisplay;
}

FString FormattingHelpers::FormatProficienciesList(const TArray<FName> &Proficiencies)
{
    FString ProficienciesList;
    for (int32 i = 0; i < Proficiencies.Num(); ++i)
    {
        ProficienciesList += Proficiencies[i].ToString();
        if (i < Proficiencies.Num() - 1)
        {
            ProficienciesList += TEXT(", ");
        }
    }
    return ProficienciesList;
}

FString FormattingHelpers::FormatAbilityScores(const TMap<FName, int32> &AbilityScores)
{
    FString FormattedScores;
    TArray<FNameWithID> AbilityOrderWithIDs = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<FName> AbilityOrder;
    for (const FNameWithID &AbilityWithID : AbilityOrderWithIDs)
    {
        AbilityOrder.Add(AbilityWithID.Name);
    }

    for (const FName &AbilityName : AbilityOrder)
    {
        if (AbilityScores.Contains(AbilityName))
        {
            FormattedScores += FString::Printf(TEXT("  %s: %d\n"), *AbilityName.ToString(), AbilityScores[AbilityName]);
        }
        else
        {
            FormattedScores += FString::Printf(TEXT("  %s: FALTANDO!\n"), *AbilityName.ToString());
        }
    }

    return FormattedScores;
}

#pragma endregion String Formatting
