// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Structures/FPointBuyResult.h"

// Forward declaration
struct FCharacterSheetData;

/**
 * Motor de Point Buy para criação de personagem.
 * Responsável APENAS por aplicar alocação de Point Buy nos Final Scores.
 *
 * Motor puro: apenas aplica, sem validação, logging, conversão ou formatação.
 * Motor independente: não conhece bônus raciais, apenas aplica Point Buy.
 *
 * Responsabilidades:
 * - Aplicar alocação de Point Buy nos Final Scores (ÚNICA responsabilidade)
 *
 * Para validação, ajuste, conversão e formatação, use FPointBuyOrchestrator.
 */
class MYPROJECT2_API FPointBuyMotor
{
public:
    /**
     * Aplica alocação de Point Buy nos Final Scores.
     * Motor puro: apenas aplica, assume que dados são válidos e já convertidos.
     *
     * @param PointBuyAllocation Alocação de Point Buy já convertida (TMap<FName, int32>)
     * @param FinalStrength [OUT] Referência para Final Strength (será modificado)
     * @param FinalDexterity [OUT] Referência para Final Dexterity (será modificado)
     * @param FinalConstitution [OUT] Referência para Final Constitution (será modificado)
     * @param FinalIntelligence [OUT] Referência para Final Intelligence (será modificado)
     * @param FinalWisdom [OUT] Referência para Final Wisdom (será modificado)
     * @param FinalCharisma [OUT] Referência para Final Charisma (será modificado)
     */
    static void ApplyPointBuy(const TMap<FName, int32>& PointBuyAllocation, int32& FinalStrength,
                              int32& FinalDexterity, int32& FinalConstitution, int32& FinalIntelligence,
                              int32& FinalWisdom, int32& FinalCharisma);
};
