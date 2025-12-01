// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyProject2SaveGame.generated.h"

#pragma endregion Includes

// ============================================================================
// MyProject2 SaveGame
// ============================================================================
#pragma region MyProject2 SaveGame

/**
 * Classe base para salvamento de dados do jogo.
 *
 * Herda de USaveGame e fornece estrutura básica para salvar/carregar
 * dados do personagem e do jogo.
 *
 * Princípios:
 * - UPROPERTY(SaveGame) para propriedades que devem ser salvas
 * - Estrutura simples para MVP (dados básicos do personagem)
 * - Preparado para expansão futura (inventário, quests, etc.)
 */
UCLASS(BlueprintType)
class MYPROJECT2_API UMyProject2SaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    // ========================================================================
    // Constructor
    // ========================================================================
#pragma region Constructor

    UMyProject2SaveGame();

#pragma endregion Constructor

    // ========================================================================
    // Save Slot Configuration
    // ========================================================================
#pragma region Save Slot Configuration

    /** Nome padrão do slot de save */
    static const FString DefaultSaveSlotName;

    /** Índice padrão do usuário para save */
    static const int32 DefaultUserIndex;

#pragma endregion Save Slot Configuration

    // ========================================================================
    // Character Data
    // ========================================================================
#pragma region Character Data

    /** Nome do personagem */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Character", SaveGame)
    FString CharacterName;

    /** Nível do personagem */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Character", SaveGame)
    int32 CharacterLevel;

    /** Raça do personagem */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Character", SaveGame)
    FName CharacterRace;

    /** Classe do personagem */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Character", SaveGame)
    FName CharacterClass;

#pragma endregion Character Data

    // ========================================================================
    // Game Data
    // ========================================================================
#pragma region Game Data

    /** Timestamp do save (quando foi salvo) */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Game", SaveGame)
    FDateTime SaveTimestamp;

    /** Versão do save (para compatibilidade futura) */
    UPROPERTY(VisibleAnywhere, Category = "Save Data|Game", SaveGame)
    int32 SaveVersion;

#pragma endregion Game Data
};

#pragma endregion MyProject2 SaveGame
