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

FAbilityScoreDataRow *DataTableHelpers::FindAbilityScoreRow(FName AbilityID, UDataTable *AbilityScoreDataTable)
{
    return FindRowByID<FAbilityScoreDataRow>(AbilityID, AbilityScoreDataTable, TEXT("FindAbilityScoreRow"));
}

TArray<FNameWithID> DataTableHelpers::GetAllAbilityScoreNames(UDataTable *AbilityScoreDataTable)
{
    TArray<FNameWithID> AbilityNamesWithIDs;

    if (!AbilityScoreDataTable)
    {
        return AbilityNamesWithIDs;
    }

    TArray<FName> RowNames = AbilityScoreDataTable->GetRowNames();
    AbilityNamesWithIDs.Reserve(RowNames.Num()); // Otimização: pre-aloca memória
    for (const FName &RowName : RowNames)
    {
        if (FAbilityScoreDataRow *Row =
                AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(RowName, TEXT("GetAllAbilityScoreNames")))
        {
            if (Row->Name != NAME_None && Row->ID != NAME_None)
            {
                AbilityNamesWithIDs.Add(FNameWithID(Row->Name, Row->ID));
            }
        }
    }

    return AbilityNamesWithIDs;
}

#pragma endregion Ability Score Data Table Helpers

// ============================================================================
// Race Data Table Helpers
// ============================================================================
#pragma region Race Data Table Helpers

FRaceDataRow *DataTableHelpers::FindRaceRow(FName RaceID, UDataTable *RaceDataTable)
{
    return FindRowByID<FRaceDataRow>(RaceID, RaceDataTable, TEXT("FindRaceRow"));
}

FRaceDataRow *DataTableHelpers::FindSubraceRow(FName SubraceID, UDataTable *RaceDataTable)
{
    return FindRowByID<FRaceDataRow>(SubraceID, RaceDataTable, TEXT("FindSubraceRow"));
}

#pragma endregion Race Data Table Helpers

// ============================================================================
// Class Data Table Helpers
// ============================================================================
#pragma region Class Data Table Helpers

FClassDataRow *DataTableHelpers::FindClassRow(FName ClassID, UDataTable *ClassDataTable)
{
    return FindRowByID<FClassDataRow>(ClassID, ClassDataTable, TEXT("FindClassRow"));
}

FName DataTableHelpers::FindClassIDByName(FName ClassName, UDataTable *ClassDataTable)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return NAME_None;
    }

    // Itera sobre todas as rows do Data Table
    TArray<FName> RowNames = ClassDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("FindClassIDByName")))
        {
            // Compara Name (não ID) para encontrar a classe
            if (Row->Name == ClassName)
            {
                return Row->ID; // Retorna ID correspondente
            }
        }
    }

    return NAME_None;
}

#pragma endregion Class Data Table Helpers

// ============================================================================
// Feat Data Table Helpers
// ============================================================================
#pragma region Feat Data Table Helpers

FFeatDataRow *DataTableHelpers::FindFeatRow(FName FeatID, UDataTable *FeatDataTable)
{
    return FindRowByID<FFeatDataRow>(FeatID, FeatDataTable, TEXT("FindFeatRow"));
}

FName DataTableHelpers::FindFeatIDByName(FName FeatName, UDataTable *FeatDataTable)
{
    if (!FeatDataTable || FeatName == NAME_None)
    {
        return NAME_None;
    }

    // Busca feat pelo Name (busca manual porque FindFeatRow agora busca por ID)
    TArray<FName> RowNames = FeatDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatDataRow *FoundRow = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("FindFeatIDByName")))
        {
            if (FoundRow->Name == FeatName)
            {
                // Retorna ID se disponível, senão retorna Name (fallback)
                return FoundRow->ID != NAME_None ? FoundRow->ID : FoundRow->Name;
            }
        }
    }

    return NAME_None;
}

#pragma endregion Feat Data Table Helpers

// ============================================================================
// Background Data Table Helpers
// ============================================================================
#pragma region Background Data Table Helpers

FBackgroundDataRow *DataTableHelpers::FindBackgroundRow(FName BackgroundID, UDataTable *BackgroundDataTable)
{
    return FindRowByID<FBackgroundDataRow>(BackgroundID, BackgroundDataTable, TEXT("FindBackgroundRow"));
}

#pragma endregion Background Data Table Helpers

// ============================================================================
// Proficiency Data Table Helpers
// ============================================================================
#pragma region Proficiency Data Table Helpers

FProficiencyDataRow *DataTableHelpers::FindProficiencyRowByID(FName ProficiencyID, UDataTable *ProficiencyDataTable)
{
    return FindRowByID<FProficiencyDataRow>(ProficiencyID, ProficiencyDataTable, TEXT("FindProficiencyRowByID"));
}

#pragma endregion Proficiency Data Table Helpers

// ============================================================================
// FNameWithID Helpers
// ============================================================================
#pragma region FNameWithID Helpers

TArray<FName> DataTableHelpers::ExtractNames(const TArray<FNameWithID> &NamesWithIDs)
{
    TArray<FName> Names;
    Names.Reserve(NamesWithIDs.Num()); // Otimização: pre-aloca memória
    for (const FNameWithID &NameWithID : NamesWithIDs)
    {
        Names.Add(NameWithID.Name);
    }
    return Names;
}

TArray<FNameWithID> DataTableHelpers::ConvertNamesToFNameWithID(const TArray<FName> &Names,
                                                                const TArray<FNameWithID> &AllNamesWithIDs)
{
    TArray<FNameWithID> NamesWithIDs;
    NamesWithIDs.Reserve(Names.Num()); // Otimização: pre-aloca memória

    // Cria mapa para busca O(1) ao invés de O(n) - otimização de O(n*m) para O(n+m)
    TMap<FName, FNameWithID> NameToFNameWithIDMap;
    NameToFNameWithIDMap.Reserve(AllNamesWithIDs.Num());
    for (const FNameWithID &NameWithID : AllNamesWithIDs)
    {
        NameToFNameWithIDMap.Add(NameWithID.Name, NameWithID);
    }

    // Busca cada Name no mapa O(1) ao invés de loop O(n)
    for (const FName &Name : Names)
    {
        if (const FNameWithID *FoundNameWithID = NameToFNameWithIDMap.Find(Name))
        {
            NamesWithIDs.Add(*FoundNameWithID);
        }
    }

    return NamesWithIDs;
}

#pragma endregion FNameWithID Helpers

// ============================================================================
// Proficiency Data Table Helpers - GetProficiencyNamesByType (Generic Helper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetProficiencyNamesByType

TArray<FNameWithID> DataTableHelpers::GetProficiencyNamesByType(UDataTable *ProficiencyDataTable, FName ProficiencyType)
{
    TArray<FNameWithID> ProficiencyNamesWithIDs;

    if (!ProficiencyDataTable || ProficiencyType == NAME_None)
    {
        return ProficiencyNamesWithIDs; // Retorna array vazio
    }

    // Itera sobre todas as rows do Data Table
    TArray<FName> RowNames = ProficiencyDataTable->GetRowNames();
    ProficiencyNamesWithIDs.Reserve(RowNames.Num()); // Otimização: pre-aloca memória
    for (const FName &RowName : RowNames)
    {
        if (FProficiencyDataRow *Row =
                ProficiencyDataTable->FindRow<FProficiencyDataRow>(RowName, TEXT("GetProficiencyNamesByType")))
        {
            // Filtra apenas proficiências do tipo especificado
            // Sempre retorna Name + ID juntos (ID é a referência exata na Data Table)
            if (Row->Type == ProficiencyType && Row->Name != NAME_None && Row->ID != NAME_None)
            {
                ProficiencyNamesWithIDs.Add(FNameWithID(Row->Name, Row->ID));
            }
        }
    }

    return ProficiencyNamesWithIDs;
}

#pragma endregion Proficiency Data Table Helpers - GetProficiencyNamesByType

// ============================================================================
// Proficiency Data Table Helpers - GetAllSkillNames (Wrapper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetAllSkillNames

TArray<FNameWithID> DataTableHelpers::GetAllSkillNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Skill"));
}

#pragma endregion Proficiency Data Table Helpers - GetAllSkillNames

// ============================================================================
// Proficiency Data Table Helpers - GetAllLanguageNames (Wrapper)
// ============================================================================
#pragma region Proficiency Data Table Helpers - GetAllLanguageNames

TArray<FNameWithID> DataTableHelpers::GetAllLanguageNames(UDataTable *ProficiencyDataTable)
{
    return GetProficiencyNamesByType(ProficiencyDataTable, TEXT("Language"));
}

#pragma endregion Proficiency Data Table Helpers - GetAllLanguageNames

// ============================================================================
// Feature Data Table Helpers
// ============================================================================

FFeatureDataRow *DataTableHelpers::FindFeatureRowByID(FName FeatureID, UDataTable *FeatureDataTable)
{
    return FindRowByID<FFeatureDataRow>(FeatureID, FeatureDataTable, TEXT("FindFeatureRowByID"));
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

// ============================================================================
// Item Data Table Helpers
// ============================================================================
#pragma region Item Data Table Helpers

FItemDataRow *DataTableHelpers::FindItemRow(FName ItemID, UDataTable *ItemDataTable)
{
    return FindRowByID<FItemDataRow>(ItemID, ItemDataTable, TEXT("FindItemRow"));
}

#pragma endregion Item Data Table Helpers
