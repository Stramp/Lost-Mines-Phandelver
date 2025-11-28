// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Data/Structures/FSkills.h"
#include "FProficienciesEntry.generated.h"

#pragma endregion Includes

// ============================================================================
// Proficiencies Struct
// ============================================================================
#pragma region Proficiencies Struct

/**
 * Struct para armazenar proficiências de classe seguindo a estrutura do ClassDataTable.json.
 * Cada elemento do array FProficiencies contém um objeto com armas, armaduras, SavingThrowIDs ou FSkills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProficienciesEntry
{
    GENERATED_BODY()

    /** Lista de armas (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> armas;

    /** Lista de armaduras (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> armaduras;

    /** Lista de IDs de saving throws (pode estar vazia) - ex: "ABL_Strength", "ABL_Constitution" */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    TArray<FName> SavingThrowIDs;

    /** Informações de skills (pode estar vazia) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proficiencies")
    FSkills FSkills;

    FProficienciesEntry() {}
};

#pragma endregion Proficiencies Struct
