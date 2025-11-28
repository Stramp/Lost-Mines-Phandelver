// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceValidator.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Race Validator
// ============================================================================
#pragma region Race Validator

bool FRaceValidator::ValidateSubrace(const FRaceDataRow* RaceRow, FName SelectedSubrace)
{
    if (!RaceRow || SelectedSubrace == NAME_None)
    {
        return false;
    }

    // Valida se a sub-raça pertence à raça selecionada (via SubraceHandles)
    for (const FDataTableRowHandle& SubraceHandle : RaceRow->SubraceHandles)
    {
        if (SubraceHandle.RowName == SelectedSubrace)
        {
            return true;
        }
    }

    return false;
}

#pragma endregion Race Validator
