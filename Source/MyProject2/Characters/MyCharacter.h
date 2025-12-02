// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyCharacter.generated.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

class UInputMappingContext;
class UInputAction;
class UInputActionManagerComponent;

#pragma endregion Forward Declarations

// ============================================================================
// MyCharacter Class
// ============================================================================
#pragma region MyCharacter Class

/**
 * Character principal do jogo com movimento third person completo.
 *
 * Suporta:
 * - Movimento em todas as direções (Forward/Backward, Left/Right)
 * - Rotação baseada na direção do mouse (Look)
 * - Sistema preparado para transição Third Person -> Top Down
 */
UCLASS()
class MYPROJECT2_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    /**
     * Construtor padrão.
     */
    AMyCharacter();

protected:
    /**
     * Chamado quando o jogo inicia ou quando o actor é spawnado.
     * Configura o Input Mapping Context.
     */
    virtual void BeginPlay() override;

    /**
     * Input Mapping Context usado para mapear teclas para Input Actions.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext *IMC;

    /**
     * Componente gerenciador de Input Actions.
     * Modular e escalável - facilita adicionar novas Input Actions.
     * Configurável no editor via Blueprint (Data-Driven).
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
    UInputActionManagerComponent *InputActionManager;

    void Move(const FInputActionValue &Value);
    void Look(const FInputActionValue &Value);
    void ToggleRotationMode(const FInputActionValue &Value);
    void ReleaseRotationMode(const FInputActionValue &Value);

    void UpdateRotationMode(bool bLookAtCamera);

    void SetupInputMappingContext();
    void BindInputActions(UEnhancedInputComponent *EnhancedInputComponent);

public:
    UFUNCTION(BlueprintCallable, Category = "Character|Input")
    UInputActionManagerComponent *GetInputActionManager() const { return InputActionManager; }

    UFUNCTION(BlueprintCallable, Category = "Character|Rotation")
    void SetRotationMode(bool bLookAtCamera) { UpdateRotationMode(bLookAtCamera); }

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};

#pragma endregion MyCharacter Class
