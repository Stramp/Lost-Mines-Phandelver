// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSheetData.h"

// Forward declaration
struct FPointBuyResult;

/**
 * Core genérico de criação de ficha - Orquestrador de motores.
 * Responsável por orquestrar todos os motores de criação de personagem.
 *
 * Genérico: funciona tanto no Data Asset quanto no Widget de criação.
 * Princípio: "Program to an interface, not an implementation" (Design Patterns)
 *
 * Orquestrador: reseta para base (8) e aplica cada motor independente sequencialmente.
 * Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation
 *
 * @see FCharacterSheetData - Estrutura genérica de dados
 */
class MYPROJECT2_API FCharacterSheetCore
{
public:
    /**
     * Recalcula Final Scores aplicando todos os motores sequencialmente.
     * Orquestrador: reseta para base (8) e aplica cada motor independente.
     * Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation
     *
     * Genérico: recebe FCharacterSheetData (dados puros), não objetos concretos.
     * Permite reutilização tanto no Data Asset quanto no Widget.
     *
     * @param Data Estrutura genérica com dados de entrada e referências de saída
     * @param OutPointBuyResult [OUT] Resultado do motor de Point Buy (feedback e ajustes)
     */
    static void RecalculateFinalScores(FCharacterSheetData &Data, FPointBuyResult *OutPointBuyResult = nullptr);
};
