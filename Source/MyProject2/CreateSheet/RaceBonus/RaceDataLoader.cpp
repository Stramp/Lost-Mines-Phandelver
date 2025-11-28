// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceDataLoader.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// Race Data Loader
// ============================================================================
#pragma region Race Data Loader

FRaceDataLoader::FRaceData FRaceDataLoader::Load(const FCharacterSheetData& Data)
{
    FRaceData Result;

    if (Data.RaceDataTable && Data.SelectedRace != NAME_None)
    {
        // Busca row de raça
        Result.RaceRow = DataTableHelpers::FindRaceRow(Data.SelectedRace, Data.RaceDataTable);

        // Busca sub-raça se necessário
        if (Result.RaceRow && Data.SelectedSubrace != NAME_None)
        {
            Result.SubraceRow = DataTableHelpers::FindSubraceRow(Data.SelectedSubrace, Data.RaceDataTable);
        }
    }

    return Result;
}

#pragma endregion Race Data Loader
