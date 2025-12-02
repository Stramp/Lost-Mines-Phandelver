// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"

#pragma endregion Includes

// ============================================================================
// MovementHelpers Namespace
// ============================================================================
#pragma region MovementHelpers Namespace

/**
 * Helpers para cálculos de movimento de personagens.
 *
 * Funções puras e testáveis para:
 * - Calcular direções de movimento baseadas em rotação
 * - Converter rotação em direções Forward/Right
 */
namespace MovementHelpers
{
    FRotator ExtractYawRotation(const FRotator &ControlRotation);

    FVector CalculateForwardDirection(const FRotator &ControlRotation);

    FVector CalculateRightDirection(const FRotator &ControlRotation);
} // namespace MovementHelpers

#pragma endregion MovementHelpers Namespace
