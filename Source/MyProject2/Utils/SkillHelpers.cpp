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

TArray<FName> CharacterSheetHelpers::GetSkillNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllSkillNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os 18 nomes de skills padrão D&D 5e
    // Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
    // History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
    // Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
    return TArray<FName>{TEXT("Acrobatics"),    TEXT("Animal Handling"), TEXT("Arcana"),   TEXT("Athletics"),
                         TEXT("Deception"),     TEXT("History"),         TEXT("Insight"),  TEXT("Intimidation"),
                         TEXT("Investigation"), TEXT("Medicine"),        TEXT("Nature"),   TEXT("Perception"),
                         TEXT("Performance"),   TEXT("Persuasion"),      TEXT("Religion"), TEXT("Sleight of Hand"),
                         TEXT("Stealth"),       TEXT("Survival")};
}

TArray<FName> CharacterSheetHelpers::GetAvailableLanguageNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllLanguageNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os idiomas padrão D&D 5e
    return TArray<FName>{TEXT("Common"),   TEXT("Dwarvish"),   TEXT("Elvish"),   TEXT("Giant"),
                         TEXT("Gnomish"),  TEXT("Goblin"),     TEXT("Halfling"), TEXT("Orc"),
                         TEXT("Abyssal"),  TEXT("Celestial"),  TEXT("Draconic"), TEXT("Deep Speech"),
                         TEXT("Infernal"), TEXT("Primordial"), TEXT("Sylvan"),   TEXT("Undercommon")};
}

#pragma endregion Skill Helpers
