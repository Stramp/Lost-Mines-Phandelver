// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/DnDConstants.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

#pragma endregion Includes

// ============================================================================
// Class Data Table Helpers
// ============================================================================
#pragma region Class Data Table Helpers

bool CharacterSheetHelpers::CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable)
{
    // Validação básica
    if (ClassName == NAME_None || ClassLevel < DnDConstants::MIN_LEVEL)
    {
        return false;
    }

    // Em D&D 5e, subclasses são escolhidas no nível 3
    // Nota: Verificação de subclasses disponíveis será implementada quando necessário
    // usando a nova estrutura FClassData.FProgress
    return ClassLevel >= DnDConstants::SUBCLASS_SELECTION_LEVEL;
}

#pragma endregion Class Data Table Helpers
