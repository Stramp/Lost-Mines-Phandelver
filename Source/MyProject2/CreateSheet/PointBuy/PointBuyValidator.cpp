// Copyright Epic Games, Inc. All Rights Reserved.

#include "PointBuyValidator.h"
#include "../../Characters/Data/CharacterSheetDataAsset.h"
#include "../../Utils/ValidationHelpers.h"
#include "Logging/LogMacros.h"

void FPointBuyValidator::ValidatePointBuy(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Converte alocação de Point Buy (0-7) para score base (8-15) para validação
    // Validador trabalha com propriedades diretas internamente
    TMap<FName, int32> BaseScores;
    BaseScores.Add(TEXT("Strength"), 8 + Asset->PointBuyStrength);
    BaseScores.Add(TEXT("Dexterity"), 8 + Asset->PointBuyDexterity);
    BaseScores.Add(TEXT("Constitution"), 8 + Asset->PointBuyConstitution);
    BaseScores.Add(TEXT("Intelligence"), 8 + Asset->PointBuyIntelligence);
    BaseScores.Add(TEXT("Wisdom"), 8 + Asset->PointBuyWisdom);
    BaseScores.Add(TEXT("Charisma"), 8 + Asset->PointBuyCharisma);

    // Usa ValidationHelpers para validar e calcular pontos restantes
    int32 PointsRemaining = 0;
    bool bAllScoresValid = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining, 27);
    Asset->PointsRemaining = PointsRemaining;

    // Log de aviso se scores estão fora do range válido
    if (!bAllScoresValid)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: Alguns ability scores estão fora do range válido [8, 15]"));
    }

    // Se PointsRemaining != 0 ou scores inválidos, a alocação está incorreta
    // PointsRemaining negativo = pontos excedidos (mais de 27 gastos)
    // PointsRemaining positivo = pontos não gastos (menos de 27 gastos)
    // Não clampa para evitar mascarar estado inválido
}
