// Copyright Epic Games, Inc. All Rights Reserved.

#include "CalculationHelpers.h"
#include "CharacterSheetHelpers.h"
#include "../Data/Tables/RaceDataTable.h"
#include "../Data/Tables/ClassDataTable.h"
#include "../Characters/Data/CharacterSheetDataAsset.h"

// ============================================================================
// Ability Score Calculations
// ============================================================================

int32 CalculationHelpers::CalculateAbilityModifier(int32 Score)
{
    // Fórmula D&D 5e: floor((Score - 10) / 2)
    return FMath::FloorToInt((Score - 10) / 2.0f);
}

int32 CalculationHelpers::CalculateFinalAbilityScore(int32 BaseScore, int32 RacialBonus, int32 ASIBonus)
{
    return BaseScore + RacialBonus + ASIBonus;
}

void CalculationHelpers::CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
                                                const TArray<FName> &CustomChoices, TMap<FName, int32> &RacialBonuses)
{
    // Resetar bônus primeiro
    RacialBonuses.Empty();

    // Aplicar bônus da raça base
    if (RaceRow)
    {
        for (const FAbilityScoreImprovement &Improvement : RaceRow->AbilityScoreImprovements)
        {
            // Bônus normal para atributo específico
            // Nota: "Custom" é tratado apenas na sub-raça (Variant Human)
            if (Improvement.AbilityName != TEXT("Custom"))
            {
                int32 *BonusPtr = RacialBonuses.Find(Improvement.AbilityName);
                if (BonusPtr)
                {
                    *BonusPtr += Improvement.Bonus;
                }
                else
                {
                    RacialBonuses.Add(Improvement.AbilityName, Improvement.Bonus);
                }
            }
        }
    }

    // Aplicar bônus da sub-raça
    if (SubraceRow)
    {
        for (const FAbilityScoreImprovement &Improvement : SubraceRow->AbilityScoreImprovements)
        {
            // Tratar "Custom" para Variant Human (sub-raça)
            if (Improvement.AbilityName == TEXT("Custom"))
            {
                // Variant Human: aplicar +1 para cada atributo em CustomChoices
                for (const FName &CustomAbility : CustomChoices)
                {
                    if (CustomAbility != NAME_None)
                    {
                        int32 *BonusPtr = RacialBonuses.Find(CustomAbility);
                        if (BonusPtr)
                        {
                            *BonusPtr += 1; // Cada escolha dá +1
                        }
                        else
                        {
                            RacialBonuses.Add(CustomAbility, 1);
                        }
                    }
                }
            }
            else
            {
                // Bônus normal para atributo específico
                int32 *BonusPtr = RacialBonuses.Find(Improvement.AbilityName);
                if (BonusPtr)
                {
                    *BonusPtr += Improvement.Bonus;
                }
                else
                {
                    RacialBonuses.Add(Improvement.AbilityName, Improvement.Bonus);
                }
            }
        }
    }
}

// ============================================================================
// Proficiency Calculations
// ============================================================================

int32 CalculationHelpers::CalculateProficiencyBonus(int32 TotalLevel)
{
    // Fórmula D&D 5e: 1 + floor((TotalLevel - 1) / 4)
    if (TotalLevel < 1)
    {
        return 0;
    }
    return 1 + FMath::FloorToInt((TotalLevel - 1) / 4.0f);
}

// ============================================================================
// Feature Calculations
// ============================================================================

TArray<FName> CalculationHelpers::CalculateAvailableFeatures(const TArray<FClassLevelEntry> &ClassLevels,
                                                             UDataTable *ClassDataTable)
{
    TArray<FName> AvailableFeatures;

    if (!ClassDataTable)
    {
        return AvailableFeatures;
    }

    // Coleta features de todas as classes e níveis
    // GetFeaturesAtLevel() retorna todas as features desbloqueadas até o nível especificado
    for (const FClassLevelEntry &ClassEntry : ClassLevels)
    {
        if (ClassEntry.ClassName == NAME_None || ClassEntry.Level < 1)
        {
            continue;
        }

        // Busca todas as features desbloqueadas até o nível atual da classe
        TArray<FClassFeature> Features =
            CharacterSheetHelpers::GetFeaturesAtLevel(ClassEntry.ClassName, ClassEntry.Level, ClassDataTable);
        for (const FClassFeature &Feature : Features)
        {
            AvailableFeatures.AddUnique(Feature.FeatureName);
        }
    }

    return AvailableFeatures;
}

TArray<FName> CalculationHelpers::CalculateProficiencies(FName RaceName, FName SubraceName,
                                                         const TArray<FClassLevelEntry> &ClassLevels,
                                                         FName BackgroundName, UDataTable *RaceDataTable,
                                                         UDataTable *ClassDataTable, UDataTable *BackgroundDataTable)
{
    TArray<FName> Proficiencies;

    // TODO: Implementar coleta de proficiências de raça, classe e background
    // Por enquanto, retorna array vazio (placeholder para implementação futura)

    return Proficiencies;
}
