// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Characters/Helpers/MovementHelpers.h"
#include "Math/RotationMatrix.h"
#include "Math/Rotator.h"
#include "Math/Vector.h"

#pragma endregion Includes

// ============================================================================
// MovementHelpers Implementation
// ============================================================================
#pragma region MovementHelpers Implementation

FRotator MovementHelpers::ExtractYawRotation(const FRotator &ControlRotation)
{
    return FRotator(0.0f, ControlRotation.Yaw, 0.0f);
}

FVector MovementHelpers::CalculateForwardDirection(const FRotator &ControlRotation)
{
    return FRotationMatrix(ExtractYawRotation(ControlRotation)).GetUnitAxis(EAxis::X);
}

FVector MovementHelpers::CalculateRightDirection(const FRotator &ControlRotation)
{
    return FRotationMatrix(ExtractYawRotation(ControlRotation)).GetUnitAxis(EAxis::Y);
}

#pragma endregion MovementHelpers Implementation
