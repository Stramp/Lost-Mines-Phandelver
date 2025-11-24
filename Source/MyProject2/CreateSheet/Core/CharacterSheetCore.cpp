// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetCore.h"
#include "CreateSheet/PointBuy/PointBuyMotor.h"
#include "CreateSheet/PointBuy/PointBuyResult.h"
#include "CreateSheet/RaceBonus/RaceBonusMotor.h"
#include "Utils/CalculationHelpers.h"
#include "Logging/LogMacros.h"

void FCharacterSheetCore::RecalculateFinalScores(FCharacterSheetData &Data, FPointBuyResult *OutPointBuyResult)
{
    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterSheetCore: Referências de Final Scores inválidas"));
        return;
    }

    // Orquestrador: reseta para base (8) e aplica cada motor independente
    // Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation

    // 1. Reset para base (8)
    CalculationHelpers::ResetFinalScoresToBase(*Data.FinalStrength, *Data.FinalDexterity, *Data.FinalConstitution,
                                               *Data.FinalIntelligence, *Data.FinalWisdom, *Data.FinalCharisma);

    // 2. Aplica bônus raciais (motor independente)
    FRaceBonusMotor::ApplyRacialBonuses(Data);

    // 3. Aplica Point Buy (motor independente, não conhece bônus racial)
    // Retorna resultado com feedback para o caller ajustar a UI
    FPointBuyResult PointBuyResult = FPointBuyMotor::ApplyPointBuy(Data);
    if (OutPointBuyResult)
    {
        *OutPointBuyResult = PointBuyResult;
    }
}
