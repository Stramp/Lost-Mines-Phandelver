// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/FeatureChoiceHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/FeatureDataTable.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Feature Choice Helpers Implementation
// ============================================================================
#pragma region Feature Choice Helpers Implementation

// ============================================================================
// Internal Helpers
// ============================================================================
#pragma region Internal Helpers

// Removido: FindFeatureRowByID duplicado
// Agora usa DataTableHelpers::FindFeatureRowByID diretamente

#pragma endregion Internal Helpers

// ============================================================================
// Public Helpers
// ============================================================================
#pragma region Public Helpers

FName FeatureChoiceHelpers::FindChoiceIDByName(const UDataTable *FeatureDataTable, FName FeatureID, FName ChoiceName)
{
    if (ChoiceName == NAME_None)
    {
        return NAME_None;
    }

    // Usa DataTableHelpers::FindFeatureRowByID para buscar feature row
    const FFeatureDataRow *FeatureRow =
        DataTableHelpers::FindFeatureRowByID(FeatureID, const_cast<UDataTable *>(FeatureDataTable));
    if (!FeatureRow)
    {
        return NAME_None;
    }

    // Busca escolha pelo Name
    for (const FFeatureChoice &Choice : FeatureRow->AvailableChoices)
    {
        if (Choice.Name == ChoiceName)
        {
            return Choice.ID;
        }
    }

    return NAME_None;
}

FName FeatureChoiceHelpers::FindChoiceNameByID(const UDataTable *FeatureDataTable, FName FeatureID, FName ChoiceID)
{
    if (ChoiceID == NAME_None)
    {
        return NAME_None;
    }

    // Usa DataTableHelpers::FindFeatureRowByID para buscar feature row
    const FFeatureDataRow *FeatureRow =
        DataTableHelpers::FindFeatureRowByID(FeatureID, const_cast<UDataTable *>(FeatureDataTable));
    if (!FeatureRow)
    {
        return NAME_None;
    }

    // Busca escolha pelo ID
    for (const FFeatureChoice &Choice : FeatureRow->AvailableChoices)
    {
        if (Choice.ID == ChoiceID)
        {
            return Choice.Name;
        }
    }

    return NAME_None;
}

TArray<FName> FeatureChoiceHelpers::GetAvailableChoiceIDsForFeature(const UDataTable *FeatureDataTable, FName FeatureID)
{
    TArray<FName> Result;

    // Usa DataTableHelpers::FindFeatureRowByID para buscar feature row
    const FFeatureDataRow *FeatureRow =
        DataTableHelpers::FindFeatureRowByID(FeatureID, const_cast<UDataTable *>(FeatureDataTable));
    if (!FeatureRow)
    {
        return Result;
    }

    // Adiciona apenas os IDs de escolhas disponíveis desta feature específica
    for (const FFeatureChoice &Choice : FeatureRow->AvailableChoices)
    {
        if (Choice.ID != NAME_None)
        {
            Result.Add(Choice.ID);
        }
    }

    return Result;
}

TArray<FName> FeatureChoiceHelpers::GetAvailableChoiceNamesForFeature(const UDataTable *FeatureDataTable,
                                                                      FName FeatureID)
{
    TArray<FName> Result;

    // Usa DataTableHelpers::FindFeatureRowByID para buscar feature row
    const FFeatureDataRow *FeatureRow =
        DataTableHelpers::FindFeatureRowByID(FeatureID, const_cast<UDataTable *>(FeatureDataTable));
    if (!FeatureRow)
    {
        return Result;
    }

    // Adiciona apenas os nomes de escolhas disponíveis desta feature específica
    for (const FFeatureChoice &Choice : FeatureRow->AvailableChoices)
    {
        if (Choice.Name != NAME_None)
        {
            Result.Add(Choice.Name);
        }
    }

    return Result;
}

TArray<FName> FeatureChoiceHelpers::ConvertChoiceIDsToNames(const UDataTable *FeatureDataTable, FName FeatureID,
                                                            const TArray<FName> &ChoiceIDs)
{
    TArray<FName> Result;

    if (!FeatureDataTable || FeatureID == NAME_None)
    {
        return Result;
    }

    for (const FName &ChoiceID : ChoiceIDs)
    {
        FName ChoiceName = FindChoiceNameByID(FeatureDataTable, FeatureID, ChoiceID);
        if (ChoiceName != NAME_None)
        {
            Result.Add(ChoiceName);
        }
    }

    return Result;
}

TArray<FName> FeatureChoiceHelpers::ConvertChoiceNamesToIDs(const UDataTable *FeatureDataTable, FName FeatureID,
                                                            const TArray<FName> &ChoiceNames)
{
    TArray<FName> Result;

    if (!FeatureDataTable || FeatureID == NAME_None)
    {
        return Result;
    }

    for (const FName &ChoiceName : ChoiceNames)
    {
        FName ChoiceID = FindChoiceIDByName(FeatureDataTable, FeatureID, ChoiceName);
        if (ChoiceID != NAME_None)
        {
            Result.Add(ChoiceID);
        }
    }

    return Result;
}

FString FeatureChoiceHelpers::FormatChoiceIDForDisplay(FName ChoiceID)
{
    if (ChoiceID == NAME_None)
    {
        return TEXT("");
    }

    FString IDString = ChoiceID.ToString();

    // Remove prefixo "FC_" se presente
    if (IDString.StartsWith(TEXT("FC_")))
    {
        IDString.RemoveAt(0, 3); // Remove "FC_"
    }

    return IDString;
}

#pragma endregion Feature Choice Helpers Implementation
