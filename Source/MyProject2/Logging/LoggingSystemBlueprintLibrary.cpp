// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "LoggingSystemBlueprintLibrary.h"

// Project includes - Logging
#include "LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// Simplified Log Functions
// ============================================================================
#pragma region Simplified Log Functions

void ULoggingSystemBlueprintLibrary::LogDebug_Simple(const FString &Module, const FString &Message)
{
    FLogContext Context(Module, TEXT("Blueprint"));
    FLoggingSystem::LogDebug(Context, Message);
}

void ULoggingSystemBlueprintLibrary::LogInfo_Simple(const FString &Module, const FString &Message)
{
    FLogContext Context(Module, TEXT("Blueprint"));
    FLoggingSystem::LogInfo(Context, Message);
}

void ULoggingSystemBlueprintLibrary::LogWarning_Simple(const FString &Module, const FString &Message)
{
    FLogContext Context(Module, TEXT("Blueprint"));
    FLoggingSystem::LogWarning(Context, Message, true);
}

void ULoggingSystemBlueprintLibrary::LogError_Simple(const FString &Module, const FString &Message)
{
    FLogContext Context(Module, TEXT("Blueprint"));
    FLoggingSystem::LogError(Context, Message, true);
}

#pragma endregion Simplified Log Functions

// ============================================================================
// Complete Log Functions
// ============================================================================
#pragma region Complete Log Functions

void ULoggingSystemBlueprintLibrary::LogDebug_Complete(const FString &Module, const FString &Function,
                                                       const FString &Message, const FString &AssetName)
{
    FLogContext Context(Module, Function, AssetName);
    FLoggingSystem::LogDebug(Context, Message);
}

void ULoggingSystemBlueprintLibrary::LogInfo_Complete(const FString &Module, const FString &Function,
                                                      const FString &Message, const FString &AssetName)
{
    FLogContext Context(Module, Function, AssetName);
    FLoggingSystem::LogInfo(Context, Message);
}

void ULoggingSystemBlueprintLibrary::LogWarning_Complete(const FString &Module, const FString &Function,
                                                         const FString &Message, const FString &AssetName)
{
    FLogContext Context(Module, Function, AssetName);
    FLoggingSystem::LogWarning(Context, Message, true);
}

void ULoggingSystemBlueprintLibrary::LogError_Complete(const FString &Module, const FString &Function,
                                                       const FString &Message, const FString &AssetName)
{
    FLogContext Context(Module, Function, AssetName);
    FLoggingSystem::LogError(Context, Message, true);
}

#pragma endregion Complete Log Functions
