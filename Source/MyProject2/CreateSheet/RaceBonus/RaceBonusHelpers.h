// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Containers/Array.h"

// Forward declarations
struct FRaceDataRow;

/**
 * Helpers para cálculo de bônus raciais.
 * Funções puras que calculam bônus sem modificar Asset diretamente.
 */
class MYPROJECT2_API FRaceBonusHelpers
{
public:
    /**
     * Calcula bônus raciais de ability scores.
     * Função pura que calcula bônus sem modificar Asset.
     *
     * @param RaceRow Row da raça base (pode ser nullptr)
     * @param SubraceRow Row da sub-raça (pode ser nullptr)
     * @param CustomChoices Array com escolhas customizadas (ex: Variant Human)
     * @param RacialBonuses [OUT] Map com bônus calculados (chave: FName do atributo, valor: bônus)
     */
    static void CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
                                       const TArray<FName> &CustomChoices, TMap<FName, int32> &RacialBonuses);

    /**
     * Incrementa Final Scores com bônus raciais.
     * Motor independente: apenas incrementa, não reseta, não conhece Point Buy.
     *
     * @param RacialBonuses Map com bônus raciais calculados
     * @param FinalStrength [IN/OUT] Score final de Strength
     * @param FinalDexterity [IN/OUT] Score final de Dexterity
     * @param FinalConstitution [IN/OUT] Score final de Constitution
     * @param FinalIntelligence [IN/OUT] Score final de Intelligence
     * @param FinalWisdom [IN/OUT] Score final de Wisdom
     * @param FinalCharisma [IN/OUT] Score final de Charisma
     */
    static void IncrementFinalScoresWithRacialBonuses(const TMap<FName, int32> &RacialBonuses, int32 &FinalStrength,
                                                      int32 &FinalDexterity, int32 &FinalConstitution,
                                                      int32 &FinalIntelligence, int32 &FinalWisdom,
                                                      int32 &FinalCharisma);
};
