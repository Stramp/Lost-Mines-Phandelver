// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionType.h"
#include "InputActionManagerComponent.generated.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

class UInputAction;

#pragma endregion Forward Declarations

// ============================================================================
// Input Action Manager Component
// ============================================================================
#pragma region Input Action Manager Component

/**
 * Componente gerenciador de Input Actions.
 * Segue padrão Component-Based Architecture.
 *
 * Responsabilidades:
 * - Armazenar Input Actions de forma escalável (TMap)
 * - Fornecer acesso type-safe via enum
 * - Preparado para TDD (helpers testáveis)
 * - Data-Driven (configurável no editor)
 *
 * Benefícios:
 * - Modular: Pode ser usado em qualquer Actor
 * - Escalável: Fácil adicionar novas Input Actions (apenas adicionar ao enum)
 * - Testável: Componente isolado pode ser testado independentemente
 * - Type-Safe: Enum previne erros de string
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UInputActionManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    /**
     * Construtor padrão.
     */
    UInputActionManagerComponent();

    /**
     * Obtém Input Action por tipo.
     * Helper testável e type-safe.
     *
     * @param ActionType Tipo da Input Action
     * @return Ponteiro para Input Action, ou nullptr se não encontrada
     */
    UFUNCTION(BlueprintCallable, Category = "Input")
    UInputAction *GetInputAction(EInputActionType ActionType) const;

    /**
     * Registra uma Input Action.
     * Útil para configuração dinâmica ou testes.
     *
     * @param ActionType Tipo da Input Action
     * @param InputAction Ponteiro para Input Action
     */
    UFUNCTION(BlueprintCallable, Category = "Input")
    void RegisterInputAction(EInputActionType ActionType, UInputAction *InputAction);

    /**
     * Verifica se uma Input Action está registrada.
     *
     * @param ActionType Tipo da Input Action
     * @return true se a Input Action está registrada, false caso contrário
     */
    UFUNCTION(BlueprintCallable, Category = "Input")
    bool HasInputAction(EInputActionType ActionType) const;

protected:
    /**
     * Mapa de Input Actions indexado por tipo.
     * Data-Driven: Configurável no editor via Blueprint.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TMap<EInputActionType, UInputAction *> InputActions;
};

#pragma endregion Input Action Manager Component
