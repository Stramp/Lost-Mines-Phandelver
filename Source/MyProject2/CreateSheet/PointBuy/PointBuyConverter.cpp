// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyConverter.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

#pragma endregion Includes

// ============================================================================
// Point Buy Converter
// ============================================================================
#pragma region Point Buy Converter

TMap<FName, int32> FPointBuyConverter::ConvertFromData(const FCharacterSheetData& Data)
{
    return CharacterSheetHelpers::CreatePointBuyMapFromData(
        Data.PointBuyStrength, Data.PointBuyDexterity, Data.PointBuyConstitution, Data.PointBuyIntelligence,
        Data.PointBuyWisdom, Data.PointBuyCharisma);
}

#pragma endregion Point Buy Converter
