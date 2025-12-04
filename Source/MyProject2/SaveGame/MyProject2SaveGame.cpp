// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MyProject2SaveGame.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// Save Slot Configuration
// ============================================================================
#pragma region Save Slot Configuration

const FString UMyProject2SaveGame::DefaultSaveSlotName = TEXT("SaveSlot");
const int32 UMyProject2SaveGame::DefaultUserIndex = 0;

#pragma endregion Save Slot Configuration

// ============================================================================
// Constructor
// ============================================================================
#pragma region Constructor

UMyProject2SaveGame::UMyProject2SaveGame()
{
    // Inicializa valores padrão
    CharacterName = TEXT("");
    CharacterRace = NAME_None;
    CharacterClass = NAME_None;
    // Regra: Se character tem classe, ele tem nível. Se não tem classe, não tem nível.
    CharacterLevel = 0; // Inicializa como 0 (sem classe = sem nível)
    SaveTimestamp = FDateTime::Now();
    SaveVersion = 1; // Versão inicial do save system
}

#pragma endregion Constructor
