// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/BackgroundDataTable.h"

#pragma endregion Includes

// ============================================================================
// Background Data Table Helpers
// ============================================================================
#pragma region Background Data Table Helpers

TArray<FName> CharacterSheetHelpers::GetAllBackgroundNames(UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return TArray<FName>();
    }

    TSet<FName> BackgroundNamesSet;
    TArray<FName> RowNames = BackgroundDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FBackgroundDataRow *Row =
                BackgroundDataTable->FindRow<FBackgroundDataRow>(RowName, TEXT("GetAllBackgroundNames")))
        {
            if (Row->Name != NAME_None)
            {
                BackgroundNamesSet.Add(Row->Name);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para nomes de backgrounds)
    return BackgroundNamesSet.Array();
}

#pragma endregion Background Data Table Helpers
