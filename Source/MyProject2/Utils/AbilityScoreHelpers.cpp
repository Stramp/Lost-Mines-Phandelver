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

TArray<FNameWithID> CharacterSheetHelpers::GetAbilityScoreNames(UDataTable *AbilityScoreDataTable)
{
    // Se Data Table fornecido, busca do Data Table (Data-Driven)
    // Sempre retorna Name + ID juntos (ID é a referência exata na Data Table)
    if (AbilityScoreDataTable)
    {
        TArray<FNameWithID> AbilityNamesWithIDs = DataTableHelpers::GetAllAbilityScoreNames(AbilityScoreDataTable);
        // Se encontrou ability scores no Data Table, retorna
        if (AbilityNamesWithIDs.Num() > 0)
        {
            return AbilityNamesWithIDs;
        }
    }

    // Fallback: retorna array estático com os 6 nomes de ability scores padrão D&D 5e
    // Ordem: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
    // No fallback, usamos Name como ID temporário (já que não temos Data Table)
    return TArray<FNameWithID>{FNameWithID(TEXT("Strength"), TEXT("Strength")),
                               FNameWithID(TEXT("Dexterity"), TEXT("Dexterity")),
                               FNameWithID(TEXT("Constitution"), TEXT("Constitution")),
                               FNameWithID(TEXT("Intelligence"), TEXT("Intelligence")),
                               FNameWithID(TEXT("Wisdom"), TEXT("Wisdom")),
                               FNameWithID(TEXT("Charisma"), TEXT("Charisma"))};
}

#pragma endregion Ability Score Helpers
