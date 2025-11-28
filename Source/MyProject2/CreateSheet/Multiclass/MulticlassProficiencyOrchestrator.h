// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Data/Structures/MulticlassTypes.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

class UDataTable;

#pragma endregion Forward Declarations

// ============================================================================
// Multiclass Proficiency Orchestrator
// ============================================================================
#pragma region Multiclass Proficiency Orchestrator

/**
 * Orquestrador de proficiências de multiclasse.
 * Coordena validação, busca de dados, resolução de handles, conversão e aplicação.
 *
 * Responsabilidades:
 * - Validar parâmetros de entrada (via Validator)
 * - Buscar dados da classe (via Loader)
 * - Resolver handles de proficiências (via Resolver)
 * - Converter dados para estrutura de multiclasse (via Converter)
 * - Aplicar proficiências (via motor puro)
 * - Fazer logging (responsabilidade do orquestrador)
 */
class MYPROJECT2_API FMulticlassProficiencyOrchestrator
{
public:
    /**
     * Carrega proficiências de uma classe para multiclasse de forma completa.
     * Coordena todas as operações: validação, busca, resolução, conversão e aplicação.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (deve ser 1 para carregar proficiências)
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param ProficiencyDataTable Data Table de proficiências para resolver IDs (pode ser nullptr)
     * @param OutProficiencies [OUT] Array de proficiências carregadas com nomes legíveis
     * @return true se proficiências foram carregadas com sucesso, false caso contrário
     */
    static bool Load(FName ClassName, int32 LevelInClass, const UDataTable* ClassDataTable,
                    const UDataTable* ProficiencyDataTable, TArray<FMulticlassProficienciesEntry>& OutProficiencies);
};

#pragma endregion Multiclass Proficiency Orchestrator
