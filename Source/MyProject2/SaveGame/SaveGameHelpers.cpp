// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "SaveGameHelpers.h"

// Project includes - SaveGame
#include "MyProject2SaveGame.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Kismet/GameplayStatics.h"

#pragma endregion Includes

// ============================================================================
// Save Operations
// ============================================================================
#pragma region Save Operations

bool USaveGameHelpers::SaveGameToSlot(UMyProject2SaveGame *SaveGameObject, const FString &SlotName, int32 UserIndex)
{
    // Validação de parâmetros
    if (!SaveGameObject)
    {
        FLogContext Context(TEXT("SaveGame"), TEXT("SaveGameToSlot"));
        FLoggingSystem::LogWarning(Context, TEXT("SaveGameObject é nullptr. Não é possível salvar."), false);
        return false;
    }

    // Usa valores padrão se não especificados
    FString FinalSlotName = SlotName.IsEmpty() ? UMyProject2SaveGame::DefaultSaveSlotName : SlotName;
    int32 FinalUserIndex = UserIndex == -1 ? UMyProject2SaveGame::DefaultUserIndex : UserIndex;

    // Atualiza timestamp antes de salvar
    SaveGameObject->SaveTimestamp = FDateTime::Now();

    // Salva usando GameplayStatics
    bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveGameObject, FinalSlotName, FinalUserIndex);

    // Log do resultado
    FLogContext Context(TEXT("SaveGame"), TEXT("SaveGameToSlot"));
    if (bSuccess)
    {
        FLoggingSystem::LogInfo(Context,
                                FString::Printf(TEXT("Save salvo com sucesso: Slot='%s', UserIndex=%d, Character='%s'"),
                                                *FinalSlotName, FinalUserIndex, *SaveGameObject->CharacterName));
    }
    else
    {
        FLoggingSystem::LogError(
            Context, FString::Printf(TEXT("Falha ao salvar: Slot='%s', UserIndex=%d"), *FinalSlotName, FinalUserIndex));
    }

    return bSuccess;
}

#pragma endregion Save Operations

// ============================================================================
// Load Operations
// ============================================================================
#pragma region Load Operations

UMyProject2SaveGame *USaveGameHelpers::LoadGameFromSlot(const FString &SlotName, int32 UserIndex)
{
    // Usa valores padrão se não especificados
    FString FinalSlotName = SlotName.IsEmpty() ? UMyProject2SaveGame::DefaultSaveSlotName : SlotName;
    int32 FinalUserIndex = UserIndex == -1 ? UMyProject2SaveGame::DefaultUserIndex : UserIndex;

    // Carrega usando GameplayStatics
    USaveGame *LoadedSave = UGameplayStatics::LoadGameFromSlot(FinalSlotName, FinalUserIndex);

    // Cast para nosso tipo específico
    UMyProject2SaveGame *MySaveGame = Cast<UMyProject2SaveGame>(LoadedSave);

    // Log do resultado
    FLogContext Context(TEXT("SaveGame"), TEXT("LoadGameFromSlot"));
    if (MySaveGame)
    {
        FLoggingSystem::LogInfo(
            Context, FString::Printf(TEXT("Save carregado com sucesso: Slot='%s', UserIndex=%d, Character='%s'"),
                                     *FinalSlotName, FinalUserIndex, *MySaveGame->CharacterName));
    }
    else
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("Falha ao carregar save ou save não existe: Slot='%s', UserIndex=%d"), *FinalSlotName,
                            FinalUserIndex),
            false);
    }

    return MySaveGame;
}

bool USaveGameHelpers::DoesSaveGameExist(const FString &SlotName, int32 UserIndex)
{
    // Usa valores padrão se não especificados
    FString FinalSlotName = SlotName.IsEmpty() ? UMyProject2SaveGame::DefaultSaveSlotName : SlotName;
    int32 FinalUserIndex = UserIndex == -1 ? UMyProject2SaveGame::DefaultUserIndex : UserIndex;

    // Verifica se save existe
    return UGameplayStatics::DoesSaveGameExist(FinalSlotName, FinalUserIndex);
}

bool USaveGameHelpers::DeleteGameInSlot(const FString &SlotName, int32 UserIndex)
{
    // Usa valores padrão se não especificados
    FString FinalSlotName = SlotName.IsEmpty() ? UMyProject2SaveGame::DefaultSaveSlotName : SlotName;
    int32 FinalUserIndex = UserIndex == -1 ? UMyProject2SaveGame::DefaultUserIndex : UserIndex;

    // Deleta save
    bool bSuccess = UGameplayStatics::DeleteGameInSlot(FinalSlotName, FinalUserIndex);

    // Log do resultado
    FLogContext Context(TEXT("SaveGame"), TEXT("DeleteGameInSlot"));
    if (bSuccess)
    {
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Save deletado com sucesso: Slot='%s', UserIndex=%d"),
                                                         *FinalSlotName, FinalUserIndex));
    }
    else
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("Falha ao deletar save ou save não existe: Slot='%s', UserIndex=%d"), *FinalSlotName,
                            FinalUserIndex),
            false);
    }

    return bSuccess;
}

#pragma endregion Load Operations
