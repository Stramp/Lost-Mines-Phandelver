// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataTableHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"

// ============================================================================
// Race Data Table Helpers
// ============================================================================

FRaceDataRow *DataTableHelpers::FindRaceRow(FName RaceName, UDataTable *RaceDataTable)
{
    if (!RaceDataTable || RaceName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RaceName, TEXT("FindRaceRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    // (pode acontecer se RowName != RaceName no JSON)
    if (!Row)
    {
        TArray<FName> RowNames = RaceDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FRaceDataRow *FoundRow = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("FindRaceRow")))
            {
                if (FoundRow->RaceName == RaceName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

FRaceDataRow *DataTableHelpers::FindSubraceRow(FName SubraceName, UDataTable *RaceDataTable)
{
    if (!RaceDataTable || SubraceName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(SubraceName, TEXT("FindSubraceRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    if (!Row)
    {
        TArray<FName> RowNames = RaceDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FRaceDataRow *FoundRow = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("FindSubraceRow")))
            {
                if (FoundRow->RaceName == SubraceName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

// ============================================================================
// Class Data Table Helpers
// ============================================================================

FClassDataRow *DataTableHelpers::FindClassRow(FName ClassName, UDataTable *ClassDataTable)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(ClassName, TEXT("FindClassRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    if (!Row)
    {
        TArray<FName> RowNames = ClassDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FClassDataRow *FoundRow = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("FindClassRow")))
            {
                if (FoundRow->ClassName == ClassName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

// ============================================================================
// Feat Data Table Helpers
// ============================================================================

FFeatDataRow *DataTableHelpers::FindFeatRow(FName FeatName, UDataTable *FeatDataTable)
{
    if (!FeatDataTable || FeatName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FFeatDataRow *Row = FeatDataTable->FindRow<FFeatDataRow>(FeatName, TEXT("FindFeatRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    if (!Row)
    {
        TArray<FName> RowNames = FeatDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FFeatDataRow *FoundRow = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("FindFeatRow")))
            {
                if (FoundRow->FeatName == FeatName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

// ============================================================================
// Background Data Table Helpers
// ============================================================================

FBackgroundDataRow *DataTableHelpers::FindBackgroundRow(FName BackgroundName, UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable || BackgroundName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FBackgroundDataRow *Row =
        BackgroundDataTable->FindRow<FBackgroundDataRow>(BackgroundName, TEXT("FindBackgroundRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    if (!Row)
    {
        TArray<FName> RowNames = BackgroundDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FBackgroundDataRow *FoundRow =
                    BackgroundDataTable->FindRow<FBackgroundDataRow>(RowName, TEXT("FindBackgroundRow")))
            {
                if (FoundRow->BackgroundName == BackgroundName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}
