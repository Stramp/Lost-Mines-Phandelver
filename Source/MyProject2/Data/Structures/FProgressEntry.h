// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "FProgressEntry.generated.h"

#pragma endregion Includes

// ============================================================================
// Progress Struct
// ============================================================================
#pragma region Progress Struct

/**
 * Struct para armazenar uma entrada de progressão por nível.
 * Segue a estrutura do DJ_Class.json.
 * Define quais features são desbloqueadas em cada nível da classe.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProgressEntry
{
    GENERATED_BODY()

    /** Nível da classe (calculado automaticamente, não editável) */
    UPROPERTY(BlueprintReadOnly, Category = "Progress")
    int32 Level = 1;

    /** Lista de features desbloqueadas neste nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TArray<FName> Features;

    FProgressEntry() : Level(1) {}
};

#pragma endregion Progress Struct
