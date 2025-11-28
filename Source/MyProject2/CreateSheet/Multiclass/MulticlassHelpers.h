// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"

#pragma endregion Includes

/**
 * @deprecated Este arquivo foi dividido em 3 arquivos especializados:
 * - MulticlassValidationHelpers.h/cpp - Validações
 * - MulticlassDataLoadingHelpers.h/cpp - Carregamento de dados
 * - MulticlassConversionHelpers.h/cpp - Conversões
 *
 * Use os novos arquivos especializados ao invés deste.
 * Este arquivo é mantido apenas para compatibilidade temporária.
 */

// Forward declarations para compatibilidade
class UDataTable;
struct FClassDataRow;
struct FMulticlassClassFeature;

/**
 * @deprecated Use FMulticlassValidationHelpers, FMulticlassDataLoadingHelpers ou FMulticlassConversionHelpers
 */
class MYPROJECT2_API FMulticlassHelpers
{
public:
    // Este arquivo está vazio - todas as funções foram movidas para os novos arquivos especializados
};
