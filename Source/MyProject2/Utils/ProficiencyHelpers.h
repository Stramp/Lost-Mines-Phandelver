// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Data/Tables/ProficiencyDataTable.h"

#pragma endregion Includes

// ============================================================================
// ProficiencyHelpers Namespace
// ============================================================================
#pragma region ProficiencyHelpers Namespace

/**
 * Funções helper para ler e processar ProficiencyData de proficiências.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace ProficiencyHelpers
{
    /**
     * Obtém valor de ProficiencyData como FString.
     * Retorna string vazia se chave não existe.
     *
     * @param ProficiencyRow Row da proficiência
     * @param Key Chave a buscar (ex: "Damage", "AC")
     * @return Valor da chave ou string vazia se não existe
     */
    FString GetProficiencyDataValue(const FProficiencyDataRow& ProficiencyRow, const FName& Key);

    /**
     * Verifica se ProficiencyData não está vazio.
     *
     * @param ProficiencyRow Row da proficiência
     * @return true se ProficiencyData tem pelo menos uma entrada, false caso contrário
     */
    bool HasProficiencyData(const FProficiencyDataRow& ProficiencyRow);

    /**
     * Obtém valor de ProficiencyData como int32.
     * Retorna DefaultValue se chave não existe ou valor não é numérico.
     *
     * @param ProficiencyRow Row da proficiência
     * @param Key Chave a buscar (ex: "AC", "MaxDexBonus")
     * @param DefaultValue Valor padrão se chave não existe ou inválida
     * @return Valor convertido para int32 ou DefaultValue
     */
    int32 GetProficiencyDataAsInt(const FProficiencyDataRow& ProficiencyRow, const FName& Key, int32 DefaultValue = -1);

    /**
     * Obtém valor de ProficiencyData como float.
     * Retorna DefaultValue se chave não existe ou valor não é numérico.
     *
     * @param ProficiencyRow Row da proficiência
     * @param Key Chave a buscar
     * @param DefaultValue Valor padrão se chave não existe ou inválida
     * @return Valor convertido para float ou DefaultValue
     */
    float GetProficiencyDataAsFloat(const FProficiencyDataRow& ProficiencyRow, const FName& Key, float DefaultValue = 0.0f);

    /**
     * Obtém valor de ProficiencyData como bool.
     * Retorna DefaultValue se chave não existe.
     * Valores válidos: "true", "True", "1" → true | "false", "False", "0" → false
     *
     * @param ProficiencyRow Row da proficiência
     * @param Key Chave a buscar (ex: "StealthDisadvantage")
     * @param DefaultValue Valor padrão se chave não existe
     * @return Valor convertido para bool ou DefaultValue
     */
    bool GetProficiencyDataAsBool(const FProficiencyDataRow& ProficiencyRow, const FName& Key, bool DefaultValue = false);
}

#pragma endregion ProficiencyHelpers Namespace
