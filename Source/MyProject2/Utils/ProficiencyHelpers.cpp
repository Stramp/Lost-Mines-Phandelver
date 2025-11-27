// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/ProficiencyHelpers.h"

#pragma endregion Includes

// ============================================================================
// ProficiencyHelpers Implementation
// ============================================================================
#pragma region ProficiencyHelpers Implementation

namespace ProficiencyHelpers
{
    FString GetProficiencyDataValue(const FProficiencyDataRow& ProficiencyRow, const FName& Key)
    {
        if (const FString* Value = ProficiencyRow.ProficiencyData.Find(Key))
        {
            return *Value;
        }
        return FString();
    }

    bool HasProficiencyData(const FProficiencyDataRow& ProficiencyRow)
    {
        return ProficiencyRow.ProficiencyData.Num() > 0;
    }

    int32 GetProficiencyDataAsInt(const FProficiencyDataRow& ProficiencyRow, const FName& Key, int32 DefaultValue)
    {
        if (const FString* Value = ProficiencyRow.ProficiencyData.Find(Key))
        {
            // Valida se string é numérica antes de converter
            if (Value->IsNumeric())
            {
                return FCString::Atoi(**Value);
            }
        }
        return DefaultValue;
    }

    float GetProficiencyDataAsFloat(const FProficiencyDataRow& ProficiencyRow, const FName& Key, float DefaultValue)
    {
        if (const FString* Value = ProficiencyRow.ProficiencyData.Find(Key))
        {
            // Usa LexTryParseString que retorna true se conversão foi bem-sucedida
            float Result;
            if (LexTryParseString(Result, **Value))
            {
                return Result;
            }
        }
        return DefaultValue;
    }

    bool GetProficiencyDataAsBool(const FProficiencyDataRow& ProficiencyRow, const FName& Key, bool DefaultValue)
    {
        if (const FString* Value = ProficiencyRow.ProficiencyData.Find(Key))
        {
            FString LowerValue = Value->ToLower();
            // Retorna true para "true" ou "1"
            if (LowerValue == TEXT("true") || LowerValue == TEXT("1"))
            {
                return true;
            }
            // Retorna false para "false" ou "0"
            if (LowerValue == TEXT("false") || LowerValue == TEXT("0"))
            {
                return false;
            }
            // Para valores inválidos, retorna default
        }
        return DefaultValue;
    }
}

#pragma endregion ProficiencyHelpers Implementation
