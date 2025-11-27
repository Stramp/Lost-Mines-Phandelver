// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Data/Tables/FeatDataTable.h"

#pragma endregion Includes

// ============================================================================
// Feat Data Helpers
// ============================================================================
#pragma region Feat Data Helpers

TArray<FName> FFeatDataRow::GetPrerequisites() const
{
    TArray<FName> PrerequisitesArray;

    // Procura por "Prerequisites" no FeatureData
    if (const FString *PrerequisitesStr = FeatureData.Find(TEXT("Prerequisites")))
    {
        if (PrerequisitesStr->IsEmpty())
        {
            return PrerequisitesArray; // Vazio
        }

        // Se contém vírgula, é array de strings separadas por vírgula
        if (PrerequisitesStr->Contains(TEXT(",")))
        {
            TArray<FString> PrerequisitesStrings;
            PrerequisitesStr->ParseIntoArray(PrerequisitesStrings, TEXT(","), true);

            for (const FString &PrereqStr : PrerequisitesStrings)
            {
                FString Trimmed = PrereqStr.TrimStartAndEnd();
                if (!Trimmed.IsEmpty())
                {
                    PrerequisitesArray.Add(FName(*Trimmed));
                }
            }
        }
        else
        {
            // String única
            FString Trimmed = PrerequisitesStr->TrimStartAndEnd();
            if (!Trimmed.IsEmpty())
            {
                PrerequisitesArray.Add(FName(*Trimmed));
            }
        }
    }

    return PrerequisitesArray;
}

#pragma endregion Feat Data Helpers
