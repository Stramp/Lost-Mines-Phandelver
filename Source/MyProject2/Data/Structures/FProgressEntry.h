// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FProgressEntry.generated.h"

#pragma endregion Includes

// ============================================================================
// Progress Struct
// ============================================================================
#pragma region Progress Struct

/**
 * Struct para armazenar uma entrada de progressão por nível.
 * Atualizado para estrutura FLAT usando FeatureHandles ao invés de FName[].
 * Define quais features são desbloqueadas em cada nível da classe.
 *
 * Migrado de FName[] para FDataTableRowHandle[] para:
 * - Type safety (referências validadas pelo editor)
 * - Consistência com outros JSONs do projeto
 * - Facilita migração futura para GAS
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FProgressEntry
{
    GENERATED_BODY()

    /** Nível da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    int32 Level = 1;

    /** Lista de handles para features desbloqueadas neste nível */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    TArray<FDataTableRowHandle> FeatureHandles;

    FProgressEntry() : Level(1) {}
};

#pragma endregion Progress Struct
