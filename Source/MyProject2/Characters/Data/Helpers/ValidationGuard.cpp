// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "ValidationGuard.h"

#if WITH_EDITOR

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

#pragma endregion Includes

// ============================================================================
// Constructor and Destructor
// ============================================================================
#pragma region Constructor and Destructor

/**
 * RAII Guard para gerenciar flag bIsValidatingProperties.
 * Automaticamente seta flag como true no construtor e false no destrutor.
 * Previne recursão infinita em PostEditChangeProperty.
 */
FValidationGuard::FValidationGuard(UCharacterSheetDataAsset *InAsset) : Asset(InAsset)
{
    if (Asset)
    {
        Asset->SetValidatingProperties(true);
    }
}

FValidationGuard::~FValidationGuard()
{
    if (Asset)
    {
        Asset->SetValidatingProperties(false);
    }
}

#pragma endregion Constructor and Destructor

#endif // WITH_EDITOR
