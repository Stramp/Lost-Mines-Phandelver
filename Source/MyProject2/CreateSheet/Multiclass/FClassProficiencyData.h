// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Containers/Array.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

struct FSkillDataRow;

#pragma endregion Forward Declarations

// ============================================================================
// Class Proficiency Data Struct
// ============================================================================
#pragma region Class Proficiency Data Struct

/**
 * Estrutura intermediária para dados de proficiência já resolvidos.
 * Usada para passar dados do Resolver para o Converter.
 */
struct MYPROJECT2_API FClassProficiencyData
{
    /** Nomes de armas já resolvidos */
    TArray<FName> WeaponNames;

    /** Nomes de armaduras já resolvidos */
    TArray<FName> ArmorNames;

    /** IDs de saving throws (Ability Scores) */
    TArray<FName> SavingThrowIDs;

    /** IDs de skills disponíveis */
    TArray<FName> AvailableSkillIDs;

    /** Quantidade de skills que podem ser escolhidas */
    int32 SkillChoiceCount = 0;

    FClassProficiencyData()
        : SkillChoiceCount(0)
    {
    }
};

#pragma endregion Class Proficiency Data Struct
