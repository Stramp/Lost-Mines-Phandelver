// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MulticlassProficiencyValidator.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Proficiency Validator
// ============================================================================
#pragma region Multiclass Proficiency Validator

bool FMulticlassProficiencyValidator::ValidateInputs(FName ClassName, int32 LevelInClass, const UDataTable* ClassDataTable)
{
    return FMulticlassValidationHelpers::ValidateLoadProficienciesInputs(ClassName, LevelInClass, ClassDataTable);
}

#pragma endregion Multiclass Proficiency Validator
