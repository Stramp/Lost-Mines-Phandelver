// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
struct FCharacterSheetData;

/**
 * Motor de Bônus Raciais para criação de personagem.
 * Responsável por calcular e aplicar bônus raciais nos Final Scores.
 *
 * Motor independente: não conhece Point Buy, apenas aplica bônus raciais.
 * Genérico: recebe FCharacterSheetData (dados puros), não objetos concretos.
 */
class MYPROJECT2_API FRaceBonusMotor
{
public:
    /**
     * Aplica bônus raciais nos Final Scores.
     * Calcula bônus de raça base, sub-raça e Variant Human, e aplica nos Final Scores.
     *
     * @param Data Estrutura genérica com dados de raça e referências de Final Scores
     */
    static void ApplyRacialBonuses(FCharacterSheetData &Data);
};
