// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "PointBuyValidator.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/ValidationHelpers.h"
#include "Utils/DnDConstants.h"

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
    // Converte alocação de Point Buy (0-7) para score base (BASE_ABILITY_SCORE + PointBuy) para validação
    // Usa helpers puros para eliminar duplicação e magic numbers (DRY + Clean Code)
    TMap<FName, int32> PointBuyMap =
        CharacterSheetHelpers::CreatePointBuyMapFromData(PointBuyStrength, PointBuyDexterity, PointBuyConstitution,
                                                         PointBuyIntelligence, PointBuyWisdom, PointBuyCharisma);
    TMap<FName, int32> BaseScores = CharacterSheetHelpers::CreateBaseScoresFromPointBuy(PointBuyMap);

    // Usa ValidationHelpers para validar e calcular pontos restantes
    int32 PointsRemaining = 0;
    bool bAllScoresValid =
        ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining, DnDConstants::MAX_POINT_BUY_POINTS);

    // Determina se a alocação está completamente válida
    bool bIsValid = (PointsRemaining == 0 && bAllScoresValid);

    // Prepara mensagem de log se houver problema
    FString LogMessage;
    if (!bAllScoresValid)
    {
        LogMessage =
            FString::Printf(TEXT("CharacterSheetDataAsset: Alguns ability scores estão fora do range válido [%d, %d]"),
                            DnDConstants::MIN_POINT_BUY_SCORE, DnDConstants::MAX_POINT_BUY_SCORE);
    }

    // Se PointsRemaining != 0 ou scores inválidos, a alocação está incorreta
    // PointsRemaining negativo = pontos excedidos (mais de MAX_POINT_BUY_POINTS gastos)
    // PointsRemaining positivo = pontos não gastos (menos de MAX_POINT_BUY_POINTS gastos)
    // Não clampa para evitar mascarar estado inválido

    return FPointBuyValidationResult(PointsRemaining, bAllScoresValid, bIsValid, LogMessage);
}

#pragma endregion Validate Point Buy
