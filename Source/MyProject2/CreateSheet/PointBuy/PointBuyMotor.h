// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structures/FPointBuyResult.h"

// Forward declaration
struct FCharacterSheetData;

/**
 * Motor de Point Buy para criação de personagem.
 * Responsável por aplicar alocação de Point Buy nos Final Scores.
 *
 * Motor independente: não conhece bônus raciais, apenas aplica Point Buy.
 * Genérico: recebe FCharacterSheetData (dados puros), não objetos concretos.
 *
 * Responsabilidades:
 * - Conhecer regras de Point Buy (máximo 27 pontos)
 * - Validar dados recebidos
 * - Ajustar automaticamente se exceder (reduzir do final da fila)
 * - Retornar feedback para o caller ajustar a UI
 */
class MYPROJECT2_API FPointBuyMotor
{
public:
    /**
     * Aplica alocação de Point Buy nos Final Scores.
     * Valida se não excede 27 pontos e ajusta automaticamente se necessário.
     * Retorna feedback para o caller ajustar a UI.
     *
     * @param Data Estrutura genérica com dados de Point Buy e referências de Final Scores
     * @return Resultado com feedback sobre validação e ajustes realizados
     */
    static FPointBuyResult ApplyPointBuy(FCharacterSheetData &Data);
};
