// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declaration
struct FCharacterSheetData;

/**
 * Motor de Bônus Raciais para criação de personagem.
 * Responsável APENAS por aplicar bônus raciais nos Final Scores.
 *
 * Motor puro: apenas aplica, sem validação, logging, busca de dados ou cálculo.
 * Motor independente: não conhece Point Buy, apenas aplica bônus raciais.
 *
 * Responsabilidades:
 * - Aplicar bônus raciais nos Final Scores (ÚNICA responsabilidade)
 *
 * Para busca de dados, validação, cálculo e logging, use FRaceBonusOrchestrator.
 */
class MYPROJECT2_API FRaceBonusMotor
{
public:
    /**
     * Aplica bônus raciais nos Final Scores.
     * Motor puro: apenas aplica, assume que bônus já foram calculados.
     *
     * @param RacialBonuses Map com bônus raciais já calculados (chave: FName do atributo, valor: bônus)
     * @param FinalStrength [OUT] Referência para Final Strength (será modificado)
     * @param FinalDexterity [OUT] Referência para Final Dexterity (será modificado)
     * @param FinalConstitution [OUT] Referência para Final Constitution (será modificado)
     * @param FinalIntelligence [OUT] Referência para Final Intelligence (será modificado)
     * @param FinalWisdom [OUT] Referência para Final Wisdom (será modificado)
     * @param FinalCharisma [OUT] Referência para Final Charisma (será modificado)
     */
    static void ApplyRacialBonuses(const TMap<FName, int32>& RacialBonuses, int32& FinalStrength,
                                    int32& FinalDexterity, int32& FinalConstitution, int32& FinalIntelligence,
                                    int32& FinalWisdom, int32& FinalCharisma);
};
