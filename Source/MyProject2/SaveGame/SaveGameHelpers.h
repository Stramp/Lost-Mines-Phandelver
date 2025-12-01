// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "SaveGameHelpers.generated.h"

#pragma endregion Includes

// Forward declarations
class UMyProject2SaveGame;

// ============================================================================
// SaveGame Helpers
// ============================================================================
#pragma region SaveGame Helpers

/**
 * Helper functions para SaveGame operations.
 *
 * Fornece funções estáticas para salvar e carregar dados do jogo.
 *
 * Princípios:
 * - Funções estáticas puras (sem estado)
 * - Validação de parâmetros
 * - Logging de operações
 * - Retorno de boolean para sucesso/falha
 */
UCLASS()
class MYPROJECT2_API USaveGameHelpers : public UObject
{
    GENERATED_BODY()

public:
    // ========================================================================
    // Save Operations
    // ========================================================================
#pragma region Save Operations

    /**
     * Salva dados do jogo em um slot.
     *
     * @param SaveGameObject Objeto SaveGame com dados a salvar
     * @param SlotName Nome do slot de save (opcional, usa DefaultSaveSlotName se vazio)
     * @param UserIndex Índice do usuário (opcional, usa DefaultUserIndex se -1)
     * @return true se salvamento foi bem-sucedido, false caso contrário
     */
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    static bool SaveGameToSlot(UMyProject2SaveGame *SaveGameObject, const FString &SlotName = TEXT(""),
                               int32 UserIndex = -1);

#pragma endregion Save Operations

    // ========================================================================
    // Load Operations
    // ========================================================================
#pragma region Load Operations

    /**
     * Carrega dados do jogo de um slot.
     *
     * @param SlotName Nome do slot de save (opcional, usa DefaultSaveSlotName se vazio)
     * @param UserIndex Índice do usuário (opcional, usa DefaultUserIndex se -1)
     * @return Ponteiro para objeto SaveGame carregado, nullptr se falhou
     */
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    static UMyProject2SaveGame *LoadGameFromSlot(const FString &SlotName = TEXT(""), int32 UserIndex = -1);

    /**
     * Verifica se existe um save no slot especificado.
     *
     * @param SlotName Nome do slot de save (opcional, usa DefaultSaveSlotName se vazio)
     * @param UserIndex Índice do usuário (opcional, usa DefaultUserIndex se -1)
     * @return true se save existe, false caso contrário
     */
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    static bool DoesSaveGameExist(const FString &SlotName = TEXT(""), int32 UserIndex = -1);

    /**
     * Deleta um save do slot especificado.
     *
     * @param SlotName Nome do slot de save (opcional, usa DefaultSaveSlotName se vazio)
     * @param UserIndex Índice do usuário (opcional, usa DefaultUserIndex se -1)
     * @return true se deleção foi bem-sucedida, false caso contrário
     */
    UFUNCTION(BlueprintCallable, Category = "Save Game")
    static bool DeleteGameInSlot(const FString &SlotName = TEXT(""), int32 UserIndex = -1);

#pragma endregion Load Operations
};

#pragma endregion SaveGame Helpers
