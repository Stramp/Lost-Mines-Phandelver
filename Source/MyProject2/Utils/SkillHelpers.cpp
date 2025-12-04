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
// Skill Helpers
// ============================================================================
#pragma region Skill Helpers

TArray<FNameWithID> CharacterSheetHelpers::GetSkillNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    // Sempre retorna Name + ID juntos (ID é a referência exata na Data Table)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllSkillNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os 18 nomes de skills padrão D&D 5e
    // Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
    // History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
    // Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
    // No fallback, usamos Name como ID temporário (já que não temos Data Table)
    return TArray<FNameWithID>{FNameWithID(TEXT("Acrobatics"), TEXT("Acrobatics")),
                               FNameWithID(TEXT("Animal Handling"), TEXT("Animal Handling")),
                               FNameWithID(TEXT("Arcana"), TEXT("Arcana")),
                               FNameWithID(TEXT("Athletics"), TEXT("Athletics")),
                               FNameWithID(TEXT("Deception"), TEXT("Deception")),
                               FNameWithID(TEXT("History"), TEXT("History")),
                               FNameWithID(TEXT("Insight"), TEXT("Insight")),
                               FNameWithID(TEXT("Intimidation"), TEXT("Intimidation")),
                               FNameWithID(TEXT("Investigation"), TEXT("Investigation")),
                               FNameWithID(TEXT("Medicine"), TEXT("Medicine")),
                               FNameWithID(TEXT("Nature"), TEXT("Nature")),
                               FNameWithID(TEXT("Perception"), TEXT("Perception")),
                               FNameWithID(TEXT("Performance"), TEXT("Performance")),
                               FNameWithID(TEXT("Persuasion"), TEXT("Persuasion")),
                               FNameWithID(TEXT("Religion"), TEXT("Religion")),
                               FNameWithID(TEXT("Sleight of Hand"), TEXT("Sleight of Hand")),
                               FNameWithID(TEXT("Stealth"), TEXT("Stealth")),
                               FNameWithID(TEXT("Survival"), TEXT("Survival"))};
}

TArray<FNameWithID> CharacterSheetHelpers::GetAvailableLanguageNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    // Sempre retorna Name + ID juntos (ID é a referência exata na Data Table)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllLanguageNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os idiomas padrão D&D 5e
    // No fallback, usamos Name como ID temporário (já que não temos Data Table)
    return TArray<FNameWithID>{
        FNameWithID(TEXT("Common"), TEXT("Common")),     FNameWithID(TEXT("Dwarvish"), TEXT("Dwarvish")),
        FNameWithID(TEXT("Elvish"), TEXT("Elvish")),     FNameWithID(TEXT("Giant"), TEXT("Giant")),
        FNameWithID(TEXT("Gnomish"), TEXT("Gnomish")),   FNameWithID(TEXT("Goblin"), TEXT("Goblin")),
        FNameWithID(TEXT("Halfling"), TEXT("Halfling")), FNameWithID(TEXT("Orc"), TEXT("Orc")),
        FNameWithID(TEXT("Abyssal"), TEXT("Abyssal")),   FNameWithID(TEXT("Celestial"), TEXT("Celestial")),
        FNameWithID(TEXT("Draconic"), TEXT("Draconic")), FNameWithID(TEXT("Deep Speech"), TEXT("Deep Speech")),
        FNameWithID(TEXT("Infernal"), TEXT("Infernal")), FNameWithID(TEXT("Primordial"), TEXT("Primordial")),
        FNameWithID(TEXT("Sylvan"), TEXT("Sylvan")),     FNameWithID(TEXT("Undercommon"), TEXT("Undercommon"))};
}

#pragma endregion Skill Helpers
