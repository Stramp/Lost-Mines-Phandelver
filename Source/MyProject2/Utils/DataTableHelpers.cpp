// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataTableHelpers.h"
#include "Data/Tables/AbilityScoreDataTable.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/ItemDataTable.h"

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
                if (FoundRow->Name == RaceName)
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
                if (FoundRow->Name == SubraceName)
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
            // Usa ClassName da estrutura flat
            if (FoundRow->ClassName == ClassName)
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
    // Procura por ID primeiro, depois por Name
    if (!Row)
    {
        TArray<FName> RowNames = FeatDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FFeatDataRow *FoundRow = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("FindFeatRow")))
            {
                // Verifica ID primeiro (identificador principal), depois Name
                if (FoundRow->ID == FeatName || FoundRow->Name == FeatName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

FName DataTableHelpers::ConvertFeatNameToFCID(FName FeatName, UDataTable *FeatDataTable)
{
    if (!FeatDataTable || FeatName == NAME_None)
    {
        return NAME_None;
    }

    // Busca feat pelo Name
    if (FFeatDataRow *Row = DataTableHelpers::FindFeatRow(FeatName, FeatDataTable))
    {
        // Retorna ID se disponível, senão retorna Name (fallback)
        return Row->ID != NAME_None ? Row->ID : Row->Name;
    }

    return NAME_None;
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
                if (FoundRow->Name == BackgroundName)
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
            if (FoundRow->ID == ProficiencyID)
            {
                return FoundRow;
            }
        }
    }

    return nullptr;
}

// ============================================================================
// Proficiency Data Table Helpers - GetProficiencyNamesByType (Generic Helper)
// ============================================================================

TArray<FName> DataTableHelpers::GetProficiencyNamesByType(UDataTable *ProficiencyDataTable, FName ProficiencyType)
{
    TArray<FName> ProficiencyNames;

    if (!ProficiencyDataTable || ProficiencyType == NAME_None)
    {
        return ProficiencyNames; // Retorna array vazio
    }

    // Itera sobre todas as rows do Data Table
    TArray<FName> RowNames = ProficiencyDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FProficiencyDataRow *Row =
                ProficiencyDataTable->FindRow<FProficiencyDataRow>(RowName, TEXT("GetProficiencyNamesByType")))
        {
            // Filtra apenas proficiências do tipo especificado
            if (Row->Type == ProficiencyType && Row->Name != NAME_None)
            {
                ProficiencyNames.Add(Row->Name);
            }
        }
    }

    return ProficiencyNames;
}

// ============================================================================
// Proficiency Data Table Helpers - GetAllSkillNames (Wrapper)
// ============================================================================

TArray<FName> DataTableHelpers::GetAllSkillNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Skill"));
}

// ============================================================================
// Proficiency Data Table Helpers - GetAllLanguageNames (Wrapper)
// ============================================================================

TArray<FName> DataTableHelpers::GetAllLanguageNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Language"));
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

    // Busca manual O(n) comparando ID de cada row
    // (não podemos usar FindRow direto porque RowName pode ser diferente de ID)
    TArray<FName> RowNames = FeatureDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatureDataRow *FoundRow = FeatureDataTable->FindRow<FFeatureDataRow>(RowName, TEXT("FindFeatureRowByID")))
        {
                if (FoundRow->ID == FeatureID)
            {
                return FoundRow;
            }
        }
    }

    return nullptr;
}

// ============================================================================
// Data Table Type Validation Helpers
// ============================================================================

bool DataTableHelpers::ValidateDataTableRowStruct(UDataTable *DataTable, const UScriptStruct *ExpectedStruct)
{
    if (!DataTable || !ExpectedStruct)
    {
        return false;
    }

    const UScriptStruct *RowStruct = DataTable->GetRowStruct();
    if (!RowStruct)
    {
        return false;
    }

    // Compara o nome do struct para verificar se corresponde ao esperado
    const FName RowStructName = RowStruct->GetFName();
    const FName ExpectedStructName = ExpectedStruct->GetFName();

    return RowStructName == ExpectedStructName;
}

bool DataTableHelpers::IsRaceDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FRaceDataRow::StaticStruct());
}

bool DataTableHelpers::IsClassDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FClassDataRow::StaticStruct());
}

bool DataTableHelpers::IsBackgroundDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FBackgroundDataRow::StaticStruct());
}

bool DataTableHelpers::IsFeatDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FFeatDataRow::StaticStruct());
}

bool DataTableHelpers::IsFeatureDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FFeatureDataRow::StaticStruct());
}

bool DataTableHelpers::IsProficiencyDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FProficiencyDataRow::StaticStruct());
}

bool DataTableHelpers::IsItemDataTable(UDataTable *DataTable)
{
    return ValidateDataTableRowStruct(DataTable, FItemDataRow::StaticStruct());
}
