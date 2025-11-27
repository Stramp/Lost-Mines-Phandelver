// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "FSkills.generated.h"

#pragma endregion Includes

// ============================================================================
// Skills Struct
// ============================================================================
#pragma region Skills Struct

/**
 * Struct para armazenar informações de skills disponíveis.
 * Usado dentro de FProficienciesEntry para definir escolhas de skills.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FSkills
{
    GENERATED_BODY()

    /** Lista de skills disponíveis para escolha */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    TArray<FName> available;

    /** Quantidade de skills que podem ser escolhidos */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 qtdAvailable;
};

#pragma endregion Skills Struct
