// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Data/Structures/FPointBuyResult.h"

#pragma endregion Includes

// ============================================================================
// Forward Declarations
// ============================================================================
#pragma region Forward Declarations

struct FCharacterSheetData;

#pragma endregion Forward Declarations

// ============================================================================
// Point Buy Orchestrator
// ============================================================================
#pragma region Point Buy Orchestrator

/**
 * Orquestrador de Point Buy para criação de personagem.
 * Coordena validação, ajuste, aplicação e formatação de feedback.
 *
 * Responsabilidades:
 * - Validar alocação de Point Buy
 * - Ajustar alocação se necessário
 * - Aplicar alocação (via motor puro)
 * - Formatar feedback para o caller
 * - Fazer logging (responsabilidade do orquestrador)
 */
class MYPROJECT2_API FPointBuyOrchestrator
{
public:
    /**
     * Processa alocação de Point Buy de forma completa.
     * Coordena todas as operações: validação, ajuste, aplicação e formatação.
     *
     * @param Data Estrutura genérica com dados de Point Buy e referências de Final Scores
     * @return Resultado com feedback sobre validação e ajustes realizados
     */
    static FPointBuyResult ProcessPointBuy(FCharacterSheetData& Data);
};

#pragma endregion Point Buy Orchestrator
