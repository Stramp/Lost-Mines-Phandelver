// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyValidator.h"

// Project includes - Utils
#include "Utils/ValidationHelpers.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Validate Point Buy
// ============================================================================
#pragma region Validate Point Buy

FPointBuyValidationResult FPointBuyValidator::ValidatePointBuy(int32 PointBuyStrength, int32 PointBuyDexterity,
                                                               int32 PointBuyConstitution, int32 PointBuyIntelligence,
                                                               int32 PointBuyWisdom, int32 PointBuyCharisma)
{
    // Converte alocação de Point Buy (0-7) para score base (8-15) para validação
    TMap<FName, int32> BaseScores;
    BaseScores.Add(TEXT("Strength"), 8 + PointBuyStrength);
    BaseScores.Add(TEXT("Dexterity"), 8 + PointBuyDexterity);
    BaseScores.Add(TEXT("Constitution"), 8 + PointBuyConstitution);
    BaseScores.Add(TEXT("Intelligence"), 8 + PointBuyIntelligence);
    BaseScores.Add(TEXT("Wisdom"), 8 + PointBuyWisdom);
    BaseScores.Add(TEXT("Charisma"), 8 + PointBuyCharisma);

    // Usa ValidationHelpers para validar e calcular pontos restantes
    int32 PointsRemaining = 0;
    bool bAllScoresValid = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining, 27);

    // Determina se a alocação está completamente válida
    bool bIsValid = (PointsRemaining == 0 && bAllScoresValid);

    // Prepara mensagem de log se houver problema
    FString LogMessage;
    if (!bAllScoresValid)
    {
        LogMessage = TEXT("CharacterSheetDataAsset: Alguns ability scores estão fora do range válido [8, 15]");
    }

    // Se PointsRemaining != 0 ou scores inválidos, a alocação está incorreta
    // PointsRemaining negativo = pontos excedidos (mais de 27 gastos)
    // PointsRemaining positivo = pontos não gastos (menos de 27 gastos)
    // Não clampa para evitar mascarar estado inválido

    return FPointBuyValidationResult(PointsRemaining, bAllScoresValid, bIsValid, LogMessage);
}

#pragma endregion Validate Point Buy
