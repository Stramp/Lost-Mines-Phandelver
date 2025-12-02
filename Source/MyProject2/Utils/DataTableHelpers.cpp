// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "DataTableHelpers.h"

// Project includes - Data Tables
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

#pragma endregion Includes

// ============================================================================
// Ability Score Data Table Helpers
// ============================================================================
#pragma region Ability Score Data Table Helpers

FAbilityScoreDataRow *DataTableHelpers::FindAbilityScoreRow(FName AbilityName, UDataTable *AbilityScoreDataTable)
{
    if (!AbilityScoreDataTable || AbilityName == NAME_None)
    {
        return nullptr;
    }

    // Tenta FindRow direto primeiro (otimização)
    FAbilityScoreDataRow *Row =
        AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(AbilityName, TEXT("FindAbilityScoreRow"));

    // Fallback: busca manual O(n) se FindRow não encontrou
    // (pode acontecer se RowName != AbilityName no JSON)
    if (!Row)
    {
        TArray<FName> RowNames = AbilityScoreDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FAbilityScoreDataRow *FoundRow =
                    AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(RowName, TEXT("FindAbilityScoreRow")))
            {
                if (FoundRow->Name == AbilityName)
                {
                    Row = FoundRow;
                    break;
                }
            }
        }
    }

    return Row;
}

TArray<FName> DataTableHelpers::GetAllAbilityScoreNames(UDataTable *AbilityScoreDataTable)
{
    TArray<FName> AbilityNames;

    if (!AbilityScoreDataTable)
    {
        return AbilityNames;
    }

    TArray<FName> RowNames = AbilityScoreDataTable->GetRowNames();
    AbilityNames.Reserve(RowNames.Num()); // Otimização: pre-aloca memória
    for (const FName &RowName : RowNames)
    {
        if (FAbilityScoreDataRow *Row =
                AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(RowName, TEXT("GetAllAbilityScoreNames")))
        {
            if (Row->Name != NAME_None)
            {
                AbilityNames.Add(Row->Name);
            }
        }
    }

    return AbilityNames;
}

#pragma endregion Ability Score Data Table Helpers

// ============================================================================
// Race Data Table Helpers
// ============================================================================
#pragma region Race Data Table Helpers

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

#pragma endregion Race Data Table Helpers

// ============================================================================
// Class Data Table Helpers
// ============================================================================
#pragma region Class Data Table Helpers

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
            // Usa Name da estrutura flat
            if (FoundRow->Name == ClassName)
            {
                Row = FoundRow;
                break;
            }
        }
    }

    // Nota: Não logamos erro quando Row é nullptr porque isso é um comportamento esperado
    // quando a classe não existe na tabela. O log de erro só deve ocorrer em casos inesperados
    // ou quando há um problema real de configuração (não quando simplesmente não encontramos a classe).

    return Row;
}

#pragma endregion Class Data Table Helpers

// ============================================================================
// Feat Data Table Helpers
// ============================================================================
#pragma region Feat Data Table Helpers

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

#pragma endregion Feat Data Table Helpers

// ============================================================================
// Background Data Table Helpers
// ============================================================================
#pragma region Background Data Table Helpers

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

#pragma endregion Background Data Table Helpers

// ============================================================================
// Proficiency Data Table Helpers
// ============================================================================
#pragma region Proficiency Data Table Helpers

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

#pragma endregion Proficiency Data Table Helpers

// ============================================================================
// Proficiency Data Table Helpers - GetProficiencyNamesByType (Generic Helper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetProficiencyNamesByType

TArray<FName> DataTableHelpers::GetProficiencyNamesByType(UDataTable *ProficiencyDataTable, FName ProficiencyType)
{
    TArray<FName> ProficiencyNames;

    if (!ProficiencyDataTable || ProficiencyType == NAME_None)
    {
        return ProficiencyNames; // Retorna array vazio
    }

    // Itera sobre todas as rows do Data Table
    TArray<FName> RowNames = ProficiencyDataTable->GetRowNames();
    ProficiencyNames.Reserve(RowNames.Num()); // Otimização: pre-aloca memória
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

#pragma endregion Proficiency Data Table Helpers - GetProficiencyNamesByType

// ============================================================================
// Proficiency Data Table Helpers - GetAllSkillNames (Wrapper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetAllSkillNames

TArray<FName> DataTableHelpers::GetAllSkillNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Skill"));
}

#pragma endregion Proficiency Data Table Helpers - GetAllSkillNames

// ============================================================================
// Proficiency Data Table Helpers - GetAllLanguageNames (Wrapper)
// ============================================================================

// ============================================================================
// Proficiency Data Table Helpers - GetAllLanguageNames (Wrapper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetAllLanguageNames

TArray<FName> DataTableHelpers::GetAllLanguageNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Language"));
}

#pragma endregion Proficiency Data Table Helpers - GetAllLanguageNames

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

#pragma endregion Data Table Type Validation Helpers
