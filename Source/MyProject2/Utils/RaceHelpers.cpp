// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

#pragma endregion Includes

// ============================================================================
// Race Data Table Helpers
// ============================================================================
#pragma region Race Data Table Helpers

TArray<FName> CharacterSheetHelpers::GetAllRaceNames(UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return TArray<FName>();
    }

    // Otimização: itera uma única vez coletando tudo
    // Evita O(n²) de FindRow dentro de loops
    TSet<FName> AllSubraceNamesSet;
    TSet<FName> RaceNamesSet;
    TArray<FName> RowNames = RaceDataTable->GetRowNames();

    // Primeira passagem: coleta sub-raças e raças base em uma única iteração
    for (const FName &RowName : RowNames)
    {
        if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("GetAllRaceNames")))
        {
            // Coleta todos os nomes de sub-raças (agora via SubraceHandles)
            for (const FDataTableRowHandle &SubraceHandle : Row->SubraceHandles)
            {
                if (SubraceHandle.RowName != NAME_None)
                {
                    AllSubraceNamesSet.Add(SubraceHandle.RowName);
                }
            }

            // Coleta raça base (será filtrada depois se for sub-raça)
            if (Row->Name != NAME_None)
            {
                RaceNamesSet.Add(Row->Name);
            }
        }
    }

    // Remove raças que são sub-raças (não devem aparecer no dropdown)
    for (const FName &SubraceName : AllSubraceNamesSet)
    {
        RaceNamesSet.Remove(SubraceName);
    }

    // Converte TSet para TArray (ordem não importa para nomes de raças)
    return RaceNamesSet.Array();
}

TArray<FName> CharacterSheetHelpers::GetAvailableSubraces(FName RaceName, UDataTable *RaceDataTable)
{
    if (!RaceDataTable || RaceName == NAME_None)
    {
        return TArray<FName>();
    }

    // Usa DataTableHelpers para buscar row de raça (otimização: remove loop O(n²))
    if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
    {
        // Converte SubraceHandles para TArray<FName>
        TArray<FName> SubraceNames;
        SubraceNames.Reserve(RaceRow->SubraceHandles.Num()); // Otimização: pre-aloca memória
        for (const FDataTableRowHandle &SubraceHandle : RaceRow->SubraceHandles)
        {
            if (SubraceHandle.RowName != NAME_None)
            {
                SubraceNames.Add(SubraceHandle.RowName);
            }
        }
        return SubraceNames;
    }

    return TArray<FName>();
}

#pragma endregion Race Data Table Helpers


