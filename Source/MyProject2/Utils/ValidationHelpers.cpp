// Copyright Epic Games, Inc. All Rights Reserved.

#include "ValidationHelpers.h"
#include "CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Logging/LogMacros.h"

// ============================================================================
// Point Buy Validation
// ============================================================================

bool ValidationHelpers::ValidatePointBuy(const TMap<FName, int32> &BaseScores, int32 &PointsRemaining, int32 MaxPoints)
{
    // Validação: todos os scores devem estar entre MIN_POINT_BUY_SCORE e MAX_POINT_BUY_SCORE
    bool bAllScoresValid = true;
    for (const auto &Pair : BaseScores)
    {
        if (Pair.Value < DnDConstants::MIN_POINT_BUY_SCORE || Pair.Value > DnDConstants::MAX_POINT_BUY_SCORE)
        {
            bAllScoresValid = false;
            break;
        }
    }

    // Calcula pontos gastos usando helper
    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    PointsRemaining = MaxPoints - TotalCost;

    // Retorna true se todos os scores estão no range válido
    return bAllScoresValid;
}

bool ValidationHelpers::ValidatePointBuyAllocation(const TMap<FName, int32> &BaseScores, int32 MaxPoints)
{
    // Valida range primeiro
    int32 PointsRemaining = 0;
    if (!ValidatePointBuy(BaseScores, PointsRemaining, MaxPoints))
    {
        return false;
    }

    // Valida que exatamente MaxPoints foram gastos
    return PointsRemaining == 0;
}

// ============================================================================
// Level Validation
// ============================================================================

bool ValidationHelpers::ValidateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels, int32 &TotalLevel,
                                           int32 MaxLevel)
{
    // Calcula nível total usando helper
    TotalLevel = CharacterSheetHelpers::CalculateTotalLevel(ClassLevels);

    // Valida se está dentro do range permitido
    return ValidateTotalLevelRange(TotalLevel, MaxLevel);
}

bool ValidationHelpers::ValidateTotalLevelRange(int32 Level, int32 MaxLevel)
{
    return Level >= DnDConstants::MIN_LEVEL && Level <= MaxLevel;
}

// ============================================================================
// Ability Score Validation
// ============================================================================

bool ValidationHelpers::ValidateAbilityScoreRange(int32 Score, int32 Min, int32 Max)
{
    return Score >= Min && Score <= Max;
}

bool ValidationHelpers::ValidateAbilityScoreChoicesPure(const TArray<FName> &Choices, const TArray<FName> &ValidNames,
                                                        int32 MaxChoices, TArray<int32> &OutInvalidIndices,
                                                        bool &OutHasDuplicates, bool &OutExceedsMax)
{
    OutInvalidIndices.Empty();
    OutHasDuplicates = false;
    OutExceedsMax = false;

    // Verifica se excede MaxChoices
    if (Choices.Num() > MaxChoices)
    {
        OutExceedsMax = true;
    }

    // Verifica duplicatas e elementos inválidos
    TSet<FName> SeenValidChoices;
    for (int32 i = 0; i < Choices.Num(); ++i)
    {
        const FName &Choice = Choices[i];

        // NAME_None é permitido temporariamente (usuário ainda está editando)
        if (Choice == NAME_None)
        {
            continue;
        }

        // Verifica se é válido
        if (!ValidNames.Contains(Choice))
        {
            OutInvalidIndices.Add(i);
        }

        // Verifica duplicatas (apenas para elementos válidos)
        if (SeenValidChoices.Contains(Choice))
        {
            OutHasDuplicates = true;
        }
        else
        {
            SeenValidChoices.Add(Choice);
        }
    }

    // Retorna true se válido (sem inválidos, sem duplicatas, quantidade <= MaxChoices)
    return OutInvalidIndices.Num() == 0 && !OutHasDuplicates && !OutExceedsMax;
}

// ============================================================================
// Selection Validation
// ============================================================================

bool ValidationHelpers::ValidateFeatSelectionPure(FName SelectedFeat, const TArray<FName> &AvailableFeats)
{
    // NAME_None é válido (nenhum feat selecionado)
    if (SelectedFeat == NAME_None)
    {
        return true;
    }

    // Verifica se está na lista de feats disponíveis
    return AvailableFeats.Contains(SelectedFeat);
}

bool ValidationHelpers::ValidateSkillSelectionPure(FName SelectedSkill, const TArray<FName> &ValidSkills)
{
    // NAME_None é válido (nenhuma skill selecionada)
    if (SelectedSkill == NAME_None)
    {
        return true;
    }

    // Verifica se está na lista de skills válidas
    return ValidSkills.Contains(SelectedSkill);
}
