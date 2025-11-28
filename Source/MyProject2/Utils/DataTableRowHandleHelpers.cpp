// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/DataTableRowHandleHelpers.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// DataTableRowHandleHelpers Implementation
// ============================================================================
#pragma region DataTableRowHandleHelpers Implementation

FDataTableRowHandle DataTableRowHandleHelpers::CreateHandle(UDataTable* DataTable, const FName& RowName)
{
    FDataTableRowHandle Handle;
    if (DataTable && RowName != NAME_None)
    {
        // Verifica se a row existe antes de criar o handle
        if (DataTable->FindRow<FTableRowBase>(RowName, TEXT("CreateHandle")))
        {
            Handle.DataTable = DataTable;
            Handle.RowName = RowName;
        }
    }
    return Handle;
}

bool DataTableRowHandleHelpers::IsHandleValid(const FDataTableRowHandle& Handle)
{
    if (Handle.IsNull() || !Handle.DataTable)
    {
        return false;
    }
    // Verifica se a row ainda existe na tabela
    return Handle.DataTable->FindRow<FTableRowBase>(Handle.RowName, TEXT("IsHandleValid")) != nullptr;
}

#pragma endregion DataTableRowHandleHelpers Implementation
