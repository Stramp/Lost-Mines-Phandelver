// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

#pragma endregion Includes

// ============================================================================
// Level Calculation Helpers
// ============================================================================
#pragma region Level Calculation Helpers

int32 CharacterSheetHelpers::CalculateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels)
{
    int32 TotalLevel = 0;

    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        if (Entry.Level > 0)
        {
            TotalLevel += Entry.Level;
        }
    }

    return TotalLevel;
}

#pragma endregion Level Calculation Helpers
