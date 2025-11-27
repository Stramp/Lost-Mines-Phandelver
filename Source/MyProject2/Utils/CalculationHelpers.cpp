// Copyright Epic Games, Inc. All Rights Reserved.

#include "CalculationHelpers.h"
#include "CharacterSheetHelpers.h"
#include "DataTableHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/DnDConstants.h"
#include "Logging/LogVerbosity.h"
#include "Math/UnrealMathUtility.h"

// ============================================================================
// Ability Score Calculations
// ============================================================================

int32 CalculationHelpers::CalculateAbilityModifier(int32 Score)
{
    // Fórmula D&D 5e: floor((Score - 10) / 2)
    return FMath::FloorToInt((Score - 10) / 2.0f);
}

void CalculationHelpers::ResetFinalScoresToBase(int32 &FinalStrength, int32 &FinalDexterity, int32 &FinalConstitution,
                                                int32 &FinalIntelligence, int32 &FinalWisdom, int32 &FinalCharisma)
{
    const int32 BaseScore = DnDConstants::BASE_ABILITY_SCORE;
    FinalStrength = BaseScore;
    FinalDexterity = BaseScore;
    FinalConstitution = BaseScore;
    FinalIntelligence = BaseScore;
    FinalWisdom = BaseScore;
    FinalCharisma = BaseScore;
}

void CalculationHelpers::IncrementFinalScoresWithPointBuy(const TMap<FName, int32> &PointBuyAllocation,
                                                          int32 &FinalStrength, int32 &FinalDexterity,
                                                          int32 &FinalConstitution, int32 &FinalIntelligence,
                                                          int32 &FinalWisdom, int32 &FinalCharisma)
{
    // Apenas incrementa (não reseta, não conhece bônus racial)
    FinalStrength += PointBuyAllocation.FindRef(TEXT("Strength"));
    FinalDexterity += PointBuyAllocation.FindRef(TEXT("Dexterity"));
    FinalConstitution += PointBuyAllocation.FindRef(TEXT("Constitution"));
    FinalIntelligence += PointBuyAllocation.FindRef(TEXT("Intelligence"));
    FinalWisdom += PointBuyAllocation.FindRef(TEXT("Wisdom"));
    FinalCharisma += PointBuyAllocation.FindRef(TEXT("Charisma"));
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

TArray<FName> CalculationHelpers::CalculateProficiencies(FName RaceName, FName SubraceName, FName BackgroundName,
                                                         FName SelectedSkill, UDataTable *RaceDataTable,
                                                         UDataTable *BackgroundDataTable)
{
    TSet<FName> ProficienciesSet;

    // Coleta proficiências de background
    if (BackgroundDataTable && BackgroundName != NAME_None)
    {
        if (FBackgroundDataRow *BackgroundRow =
                DataTableHelpers::FindBackgroundRow(BackgroundName, BackgroundDataTable))
        {
            // Adiciona proficiências de skills do background
            for (const FName &SkillProf : BackgroundRow->SkillProficiencies)
            {
                if (SkillProf != NAME_None)
                {
                    ProficienciesSet.Add(SkillProf);
                }
            }

            // NOTA: Idiomas não são proficiências, são calculados separadamente em CalculateLanguages()
            // Backgrounds não fornecem proficiências de idiomas, apenas escolhas de idiomas
        }
    }

    // Adiciona skill do Variant Human (se aplicável)
    // Variant Human permite escolher 1 skill proficiency no nível 1
    if (SubraceName == TEXT("Variant Human") && SelectedSkill != NAME_None)
    {
        ProficienciesSet.Add(SelectedSkill);
    }

    // NOTA: Proficiências de raça podem vir de Traits especiais (ex: Dwarf Stonecunning)
    // Se necessário no futuro, adicionar lógica aqui para extrair proficiências de Traits específicos da raça/sub-raça.

    // Converte TSet para TArray (ordem não importa para proficiências)
    return ProficienciesSet.Array();
}

TArray<FName> CalculationHelpers::CalculateLanguages(FName RaceName, FName SubraceName, FName BackgroundName,
                                                     const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                     UDataTable *BackgroundDataTable)
{
    TSet<FName> LanguagesSet;

    // Coleta idiomas automáticos da raça base
    if (RaceDataTable && RaceName != NAME_None)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            for (const FName &Language : RaceRow->Languages)
            {
                if (Language != NAME_None)
                {
                    LanguagesSet.Add(Language);
                }
            }
        }
    }

    // Coleta idiomas automáticos da sub-raça
    if (RaceDataTable && SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            for (const FName &Language : SubraceRow->Languages)
            {
                if (Language != NAME_None)
                {
                    LanguagesSet.Add(Language);
                }
            }
        }
    }

    // Coleta idiomas automáticos do background
    if (BackgroundDataTable && BackgroundName != NAME_None)
    {
        if (FBackgroundDataRow *BackgroundRow =
                DataTableHelpers::FindBackgroundRow(BackgroundName, BackgroundDataTable))
        {
            // Adiciona idiomas automáticos (não-escolhas)
            for (const FName &Language : BackgroundRow->Languages)
            {
                if (Language != NAME_None)
                {
                    LanguagesSet.Add(Language);
                }
            }
        }
    }

    // Adiciona idiomas escolhidos pelo jogador
    for (const FName &SelectedLanguage : SelectedLanguages)
    {
        if (SelectedLanguage != NAME_None)
        {
            LanguagesSet.Add(SelectedLanguage);
        }
    }

    // Converte TSet para TArray (ordem não importa para idiomas)
    return LanguagesSet.Array();
}

// ============================================================================
// Hit Points Calculations
// ============================================================================

int32 CalculationHelpers::CalculateHPGainForLevel(int32 HitDie, int32 Level, int32 ConstitutionModifier)
{
    if (Level < 1)
    {
        return 0;
    }

    int32 HPGain = 0;

    if (Level == 1)
    {
        // Level 1: HitDie + CON modifier
        HPGain = HitDie + ConstitutionModifier;
    }
    else
    {
        // Level 2+: (HitDie/2 + 1) + CON modifier (média do dado, arredondado para cima)
        // Fórmula: ceil(HitDie/2) + CON modifier
        // Exemplo: HitDie 10 → ceil(10/2) = 5 + CON modifier
        HPGain = FMath::CeilToInt(HitDie / 2.0f) + ConstitutionModifier;
    }

    // HP nunca pode ser negativo (mínimo 1)
    return FMath::Max(1, HPGain);
}

int32 CalculationHelpers::CalculateMaxHP(const TArray<FName> &ClassNames, const TArray<int32> &LevelsInClass,
                                         int32 ConstitutionModifier, UDataTable *ClassDataTable)
{
    if (!ClassDataTable || ClassNames.Num() != LevelsInClass.Num() || ClassNames.Num() == 0)
    {
        return 0;
    }

    int32 TotalHP = 0;
    UDataTable *NonConstTable = ClassDataTable;

    for (int32 i = 0; i < ClassNames.Num(); ++i)
    {
        const FName &ClassName = ClassNames[i];
        const int32 LevelInClass = LevelsInClass[i];

        if (ClassName == NAME_None || LevelInClass < 1)
        {
            continue;
        }

        // Busca dados da classe para obter HitDie
        const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);
        if (!ClassRow)
        {
            continue;
        }

        const int32 HitDie = ClassRow->FClass.HitDie;
        if (HitDie <= 0)
        {
            // HitDie inválido, pula esta classe
            continue;
        }

        // Calcula HP para cada nível desta classe
        for (int32 Level = 1; Level <= LevelInClass; ++Level)
        {
            TotalHP += CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);
        }
    }

    // HP nunca pode ser negativo (mínimo 1)
    return FMath::Max(1, TotalHP);
}
