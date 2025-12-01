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

    /**
     * Handler para movimento do personagem.
     * Converte input Vector2D em movimento relativo à rotação da câmera.
     *
     * @param Value Input Action Value contendo Vector2D (X = Left/Right, Y = Forward/Backward)
     */
    void Move(const FInputActionValue &Value);

    /**
     * Handler para rotação/look do personagem.
     * Rotaciona o personagem baseado na direção do mouse.
     *
     * @param Value Input Action Value contendo Vector2D (X = Yaw, Y = Pitch)
     */
    void Look(const FInputActionValue &Value);

    /**
     * Handler para quando pressionar a tecla de alternar modo de rotação (hold).
     * Ativa modo 2: Personagem sempre olha na direção da câmera.
     *
     * @param Value Input Action Value (não usado, mas necessário para assinatura)
     */
    void ToggleRotationMode(const FInputActionValue &Value);

    /**
     * Handler para quando soltar a tecla de alternar modo de rotação.
     * Volta para modo 1: Personagem rotaciona na direção do movimento.
     *
     * @param Value Input Action Value (não usado, mas necessário para assinatura)
     */
    void ReleaseRotationMode(const FInputActionValue &Value);

    /**
     * Atualiza o modo de rotação do personagem.
     *
     * @param bLookAtCamera Se true, personagem sempre olha na direção da câmera (modo 2)
     *                      Se false, personagem rotaciona na direção do movimento (modo 1)
     */
    void UpdateRotationMode(bool bLookAtCamera);

public:
    /**
     * Chamado para vincular funcionalidades ao input.
     * Configura os bindings das Input Actions.
     *
     * @param PlayerInputComponent Componente de input do jogador
     */
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};

#pragma endregion MyCharacter Class
