// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceBonusHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Calculate Racial Bonuses
// ============================================================================
#pragma region Calculate Racial Bonuses

void FRaceBonusHelpers::CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
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
            // Nota: "ABL_Custom" é tratado apenas na sub-raça (Variant Human)
            // Converte AbilityID (ex: "ABL_Strength") para nome de ability score (ex: "Strength")
            if (Improvement.AbilityID != TEXT("ABL_Custom"))
            {
                // Extrai nome do ability score do ID (remove prefixo "ABL_")
                FString AbilityIDStr = Improvement.AbilityID.ToString();
                FString AbilityNameStr = AbilityIDStr.Replace(TEXT("ABL_"), TEXT(""));
                FName AbilityName = FName(*AbilityNameStr);

                int32 *BonusPtr = RacialBonuses.Find(AbilityName);
                if (BonusPtr)
                {
                    *BonusPtr += Improvement.Bonus;
                }
                else
                {
                    RacialBonuses.Add(AbilityName, Improvement.Bonus);
                }
            }
        }
    }

    // Aplicar bônus da sub-raça
    if (SubraceRow)
    {
        // Verificar se há entrada "ABL_Custom" (Variant Human)
        bool bHasCustomEntry = false;
        for (const FAbilityScoreImprovement &CheckImprovement : SubraceRow->AbilityScoreImprovements)
        {
            if (CheckImprovement.AbilityID == TEXT("ABL_Custom"))
            {
                bHasCustomEntry = true;
                break; // Encontrou, não precisa continuar
            }
        }

        // Processa CustomChoices UMA VEZ se houver entrada "Custom"
        // Variant Human permite escolher 2 atributos para receber +1 cada
        if (bHasCustomEntry)
        {
            const int32 BonusPerItem = (CustomChoices.Num() == 1) ? 2 : 1;
            for (const FName &CustomAbility : CustomChoices)
            {
                if (CustomAbility != NAME_None)
                {
                    int32 *BonusPtr = RacialBonuses.Find(CustomAbility);
                    if (BonusPtr)
                    {
                        *BonusPtr += BonusPerItem; // Acumula se já existe
                    }
                    else
                    {
                        RacialBonuses.Add(CustomAbility, BonusPerItem); // Adiciona se não existe
                    }
                }
            }
        }

        // Processa melhorias normais (pula entradas "ABL_Custom" já processadas)
        for (const FAbilityScoreImprovement &Improvement : SubraceRow->AbilityScoreImprovements)
        {
            if (Improvement.AbilityID != TEXT("ABL_Custom"))
            {
                // Extrai nome do ability score do ID (remove prefixo "ABL_")
                FString AbilityIDStr = Improvement.AbilityID.ToString();
                FString AbilityNameStr = AbilityIDStr.Replace(TEXT("ABL_"), TEXT(""));
                FName AbilityName = FName(*AbilityNameStr);

                int32 *BonusPtr = RacialBonuses.Find(AbilityName);
                if (BonusPtr)
                {
                    *BonusPtr += Improvement.Bonus;
                }
                else
                {
                    RacialBonuses.Add(AbilityName, Improvement.Bonus);
                }
            }
        }
    }
}

#pragma endregion Calculate Racial Bonuses

// ============================================================================
// Increment Final Scores With Racial Bonuses
// ============================================================================
#pragma region Increment Final Scores With Racial Bonuses

void FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(const TMap<FName, int32> &RacialBonuses,
                                                              int32 &FinalStrength, int32 &FinalDexterity,
                                                              int32 &FinalConstitution, int32 &FinalIntelligence,
                                                              int32 &FinalWisdom, int32 &FinalCharisma)
{
    // Apenas incrementa (não reseta, não conhece Point Buy)
    FinalStrength += RacialBonuses.FindRef(TEXT("Strength"));
    FinalDexterity += RacialBonuses.FindRef(TEXT("Dexterity"));
    FinalConstitution += RacialBonuses.FindRef(TEXT("Constitution"));
    FinalIntelligence += RacialBonuses.FindRef(TEXT("Intelligence"));
    FinalWisdom += RacialBonuses.FindRef(TEXT("Wisdom"));
    FinalCharisma += RacialBonuses.FindRef(TEXT("Charisma"));
}

#pragma endregion Increment Final Scores With Racial Bonuses
