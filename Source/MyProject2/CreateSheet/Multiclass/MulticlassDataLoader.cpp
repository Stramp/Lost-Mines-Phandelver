// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MulticlassDataLoader.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassDataLoadingHelpers.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Data Loader
// ============================================================================
#pragma region Multiclass Data Loader

const FClassDataRow* FMulticlassDataLoader::LoadClassRow(FName ClassName, const UDataTable* ClassDataTable)
{
    return FMulticlassDataLoadingHelpers::FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassRow"));
}

#pragma endregion Multiclass Data Loader
