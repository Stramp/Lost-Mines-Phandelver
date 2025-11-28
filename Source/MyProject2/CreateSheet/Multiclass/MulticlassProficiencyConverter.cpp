// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MulticlassProficiencyConverter.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Proficiency Converter
// ============================================================================
#pragma region Multiclass Proficiency Converter

FMulticlassProficienciesEntry FMulticlassProficiencyConverter::Convert(const FClassProficiencyData& ProficiencyData)
{
    FMulticlassProficienciesEntry Result;

    // Copia dados já resolvidos
    Result.armas = ProficiencyData.WeaponNames;
    Result.armaduras = ProficiencyData.ArmorNames;
    Result.SavingThrowIDs = ProficiencyData.SavingThrowIDs;

    // Configura skills
    Result.FSkills.InitialAvailable = ProficiencyData.AvailableSkillIDs;
    Result.FSkills.available = NAME_None;
    Result.FSkills.Selected.Empty();
    Result.FSkills.qtdAvailable = ProficiencyData.SkillChoiceCount;
    Result.FSkills.InitialQtdAvailable = ProficiencyData.SkillChoiceCount;

    return Result;
}

#pragma endregion Multiclass Proficiency Converter
