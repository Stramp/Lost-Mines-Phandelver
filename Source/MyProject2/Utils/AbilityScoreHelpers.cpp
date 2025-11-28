// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// Ability Score Helpers
// ============================================================================
#pragma region Ability Score Helpers

TArray<FName> CharacterSheetHelpers::GetAbilityScoreNames(UDataTable *AbilityScoreDataTable)
{
    // Se Data Table fornecido, busca do Data Table (Data-Driven)
    if (AbilityScoreDataTable)
    {
        TArray<FName> AbilityNames = DataTableHelpers::GetAllAbilityScoreNames(AbilityScoreDataTable);
        // Se encontrou ability scores no Data Table, retorna
        if (AbilityNames.Num() > 0)
        {
            return AbilityNames;
        }
    }

    // Fallback: retorna array estático com os 6 nomes de ability scores padrão D&D 5e
    // Ordem: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
    return TArray<FName>{TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                         TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
}

#pragma endregion Ability Score Helpers
