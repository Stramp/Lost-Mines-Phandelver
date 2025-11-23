// Copyright Epic Games, Inc. All Rights Reserved.

#include "ValidationHelpers.h"
#include "CharacterSheetHelpers.h"
#include "../Characters/Data/CharacterSheetDataAsset.h"
#include "Logging/LogMacros.h"

// ============================================================================
// Point Buy Validation
// ============================================================================

bool ValidationHelpers::ValidatePointBuy(const TMap<FName, int32> &BaseScores, int32 &PointsRemaining, int32 MaxPoints)
{
    // Validação: todos os scores devem estar entre 8 e 15
    bool bAllScoresValid = true;
    for (const auto &Pair : BaseScores)
    {
        if (Pair.Value < 8 || Pair.Value > 15)
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

bool ValidationHelpers::ValidateTotalLevelRange(int32 Level, int32 MaxLevel) { return Level >= 1 && Level <= MaxLevel; }

// ============================================================================
// Ability Score Validation
// ============================================================================

bool ValidationHelpers::ValidateAbilityScoreRange(int32 Score, int32 Min, int32 Max)
{
    return Score >= Min && Score <= Max;
}

bool ValidationHelpers::ValidateAbilityScoreChoices(TArray<FName> &Choices, const TArray<FName> &ValidNames,
                                                    int32 MaxChoices)
{
    // Remove duplicatas
    TArray<FName> UniqueChoices;
    for (FName Choice : Choices)
    {
        if (Choice != NAME_None && !UniqueChoices.Contains(Choice))
        {
            UniqueChoices.Add(Choice);
        }
    }

    // Limita quantidade
    if (UniqueChoices.Num() > MaxChoices)
    {
        UniqueChoices.SetNum(MaxChoices);
    }

    // Valida que todos os nomes são válidos
    bool bAllValid = true;
    for (FName &Choice : UniqueChoices)
    {
        if (!ValidNames.Contains(Choice))
        {
            // Corrige valor inválido para primeiro válido (ou NAME_None se não houver)
            if (ValidNames.Num() > 0)
            {
                Choice = ValidNames[0];
            }
            else
            {
                Choice = NAME_None;
            }
            bAllValid = false;
        }
    }

    // Atualiza Choices com valores validados
    Choices = UniqueChoices;

    // Retorna true se válido (1 <= Choices.Num() <= MaxChoices e todos os nomes são válidos)
    return bAllValid && Choices.Num() >= 1 && Choices.Num() <= MaxChoices;
}

// ============================================================================
// Selection Validation
// ============================================================================

bool ValidationHelpers::ValidateFeatSelection(FName &SelectedFeat, const TArray<FName> &AvailableFeats)
{
    // NAME_None é válido (nenhum feat selecionado)
    if (SelectedFeat == NAME_None)
    {
        return true;
    }

    // Verifica se está na lista de feats disponíveis
    if (AvailableFeats.Contains(SelectedFeat))
    {
        return true;
    }

    // Reset se inválido
    SelectedFeat = NAME_None;
    return false;
}

bool ValidationHelpers::ValidateSkillSelection(FName &SelectedSkill, const TArray<FName> &ValidSkills)
{
    // NAME_None é válido (nenhuma skill selecionada)
    if (SelectedSkill == NAME_None)
    {
        return true;
    }

    // Verifica se está na lista de skills válidas
    if (ValidSkills.Contains(SelectedSkill))
    {
        return true;
    }

    // Reset se inválido
    SelectedSkill = NAME_None;
    return false;
}
