// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

struct FCharacterSheetData;

#pragma endregion Forward Declarations

// ============================================================================
// Race Bonus Orchestrator
// ============================================================================
#pragma region Race Bonus Orchestrator

/**
 * Orquestrador de Bônus Raciais para criação de personagem.
 * Coordena busca de dados, validação, cálculo e aplicação de bônus raciais.
 *
 * Responsabilidades:
 * - Buscar dados de raça e sub-raça (via Loader)
 * - Validar sub-raça (via Validator)
 * - Calcular bônus raciais (via Helpers)
 * - Aplicar bônus raciais (via motor puro)
 * - Fazer logging (responsabilidade do orquestrador)
 */
class MYPROJECT2_API FRaceBonusOrchestrator
{
public:
    /**
     * Processa bônus raciais de forma completa.
     * Coordena todas as operações: busca, validação, cálculo e aplicação.
     *
     * @param Data Estrutura genérica com dados de raça e referências de Final Scores
     */
    static void ProcessRacialBonuses(FCharacterSheetData& Data);
};

#pragma endregion Race Bonus Orchestrator
