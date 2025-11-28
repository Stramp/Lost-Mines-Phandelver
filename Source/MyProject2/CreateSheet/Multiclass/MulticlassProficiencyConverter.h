// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Data/Structures/MulticlassTypes.h"
#include "CreateSheet/Multiclass/FClassProficiencyData.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Proficiency Converter
// ============================================================================
#pragma region Multiclass Proficiency Converter

/**
 * Conversor de dados de proficiência para estrutura de multiclasse.
 * Responsável por converter FClassProficiencyData para FMulticlassProficienciesEntry.
 *
 * Função pura: recebe dados, retorna dados convertidos, não modifica nada.
 */
class MYPROJECT2_API FMulticlassProficiencyConverter
{
public:
    /**
     * Converte dados de proficiência já resolvidos para estrutura de multiclasse.
     *
     * @param ProficiencyData Dados de proficiência já resolvidos
     * @return Entry de proficiências convertida
     */
    static FMulticlassProficienciesEntry Convert(const FClassProficiencyData& ProficiencyData);
};

#pragma endregion Multiclass Proficiency Converter
