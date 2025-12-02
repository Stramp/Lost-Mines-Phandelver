// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "InputActionType.generated.h"

#pragma endregion Includes

// ============================================================================
// Input Action Types Enum
// ============================================================================
#pragma region Input Action Types Enum

/**
 * Enum para identificar tipos de Input Actions.
 * Facilita adicionar novas Input Actions sem modificar múltiplos lugares.
 *
 * Segue padrão Data-Driven: novos tipos podem ser adicionados sem alterar código existente.
 */
UENUM(BlueprintType)
enum class EInputActionType : uint8
{
    Move,               // Movimento (W/A/S/D ou gamepad left stick)
    Look,               // Rotação/Look (Mouse ou gamepad right stick)
    ToggleRotationMode, // Alternar modo de rotação (hold para modo câmera)
                        // Adicione novas Input Actions aqui:
                        // Jump,
                        // Dash,
                        // Attack,
                        // Interact,
                        // Sprint,
                        // Crouch,
                        // Reload,
                        // Use
};

#pragma endregion Input Action Types Enum
