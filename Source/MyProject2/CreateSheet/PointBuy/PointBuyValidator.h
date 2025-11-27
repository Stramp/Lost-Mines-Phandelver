// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structures/FPointBuyValidationResult.h"

/**
 * Validador de Point Buy para criação de personagem.
 * Responsável por validar alocação de Point Buy e calcular pontos restantes.
 *
 * Validador puro: recebe dados, retorna resultado, não modifica nada.
 * Segue princípios de Clean Code: função sem efeitos colaterais, testável, reutilizável.
 */
class MYPROJECT2_API FPointBuyValidator
{
public:
    /**
     * Valida Point Buy system.
     * Calcula pontos gastos e valida ability scores estão dentro do range válido [8, 15].
     *
     * Função pura: recebe dados, retorna resultado, não modifica nada.
     *
     * @param PointBuyStrength Pontos alocados para Strength (0-7)
     * @param PointBuyDexterity Pontos alocados para Dexterity (0-7)
     * @param PointBuyConstitution Pontos alocados para Constitution (0-7)
     * @param PointBuyIntelligence Pontos alocados para Intelligence (0-7)
     * @param PointBuyWisdom Pontos alocados para Wisdom (0-7)
     * @param PointBuyCharisma Pontos alocados para Charisma (0-7)
     * @return Resultado da validação com pontos restantes e status de validação
     */
    static FPointBuyValidationResult ValidatePointBuy(int32 PointBuyStrength, int32 PointBuyDexterity,
                                                      int32 PointBuyConstitution, int32 PointBuyIntelligence,
                                                      int32 PointBuyWisdom, int32 PointBuyCharisma);
};
