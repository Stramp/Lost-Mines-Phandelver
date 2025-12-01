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
    CharacterLevel = 1;
    CharacterRace = NAME_None;
    CharacterClass = NAME_None;
    SaveTimestamp = FDateTime::Now();
    SaveVersion = 1; // Versão inicial do save system
}

#pragma endregion Constructor
