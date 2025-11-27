// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataTableHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/FeatureDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

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

    // Otimização: Tenta FindRow direto primeiro (pode funcionar se RowName == ClassName)
    FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(ClassName, TEXT("FindClassRow"));

    if (Row)
    {
        return Row;
    }

    // Otimização: Tenta com prefixo "Class_" (padrão comum em DataTables)
    FName ClassRowName = FName(*FString::Printf(TEXT("Class_%s"), *ClassName.ToString()));
    Row = ClassDataTable->FindRow<FClassDataRow>(ClassRowName, TEXT("FindClassRow"));

    if (Row)
    {
        return Row;
    }

    // Fallback: busca manual O(n) se FindRow não encontrou (último recurso)
    TArray<FName> RowNames = ClassDataTable->GetRowNames();

    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *FoundRow = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("FindClassRow")))
        {
            // Usa FClass.Name da nova estrutura
            if (FoundRow->FClass.Name == ClassName)
            {
                Row = FoundRow;
                break;
            }
        }
    }

    if (!Row)
    {
        FLogContext ErrorContext(TEXT("DataTable"), TEXT("FindClassRow"));
        FString TableName = ClassDataTable ? ClassDataTable->GetName() : TEXT("Unknown");
        FLoggingSystem::LogDataTableError(ErrorContext, TableName, ClassName.ToString(), TEXT("Name"),
                                          FString::Printf(TEXT("Classe '%s' não encontrada na tabela após todas as "
                                                               "tentativas (direto, Class_ prefixo, busca manual)."),
                                                          *ClassName.ToString()));
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
    // Procura por FC_ID primeiro, depois por Name
    if (!Row)
    {
        TArray<FName> RowNames = FeatDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FFeatDataRow *FoundRow = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("FindFeatRow")))
            {
                // Verifica FC_ID primeiro (identificador principal), depois Name
                if (FoundRow->FC_ID == FeatName || FoundRow->Name == FeatName)
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

// ============================================================================
// Proficiency Data Table Helpers
// ============================================================================

FProficiencyDataRow *DataTableHelpers::FindProficiencyRowByID(FName ProficiencyID, UDataTable *ProficiencyDataTable)
{
    if (!ProficiencyDataTable || ProficiencyID == NAME_None)
    {
        return nullptr;
    }

    // Busca manual O(n) comparando ProficiencyID de cada row
    // (não podemos usar FindRow direto porque RowName pode ser diferente de ProficiencyID)
    TArray<FName> RowNames = ProficiencyDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FProficiencyDataRow *FoundRow =
                ProficiencyDataTable->FindRow<FProficiencyDataRow>(RowName, TEXT("FindProficiencyRowByID")))
        {
            if (FoundRow->ProficiencyID == ProficiencyID)
            {
                return FoundRow;
            }
        }
    }

    return nullptr;
}

// ============================================================================
// Feature Data Table Helpers
// ============================================================================

FFeatureDataRow *DataTableHelpers::FindFeatureRowByID(FName FeatureID, UDataTable *FeatureDataTable)
{
    if (!FeatureDataTable || FeatureID == NAME_None)
    {
        return nullptr;
    }

    // Busca manual O(n) comparando FC_ID de cada row
    // (não podemos usar FindRow direto porque RowName pode ser diferente de FC_ID)
    TArray<FName> RowNames = FeatureDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatureDataRow *FoundRow = FeatureDataTable->FindRow<FFeatureDataRow>(RowName, TEXT("FindFeatureRowByID")))
        {
            if (FoundRow->FC_ID == FeatureID)
            {
                return FoundRow;
            }
        }
    }

    return nullptr;
}
