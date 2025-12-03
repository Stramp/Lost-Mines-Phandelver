// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CalculationHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/SkillDataTable.h"
#include "Data/Tables/LanguageDataTable.h"

// Project includes - Characters
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Logging
#include "Logging/LogVerbosity.h"

// Engine includes
#include "Math/UnrealMathUtility.h"

#pragma endregion Includes

// ============================================================================
// Ability Score Calculations
// ============================================================================
#pragma region Ability Score Calculations

int32 CalculationHelpers::CalculateAbilityModifier(int32 Score)
{
    // Fórmula D&D 5e: floor((Score - ABILITY_MODIFIER_BASE) / ABILITY_MODIFIER_DIVISOR)
    return FMath::FloorToInt((Score - DnDConstants::ABILITY_MODIFIER_BASE) / DnDConstants::ABILITY_MODIFIER_DIVISOR);
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

#pragma endregion Ability Score Calculations

// ============================================================================
// Proficiency Calculations
// ============================================================================
#pragma region Proficiency Calculations

int32 CalculationHelpers::CalculateProficiencyBonus(int32 TotalLevel)
{
    // Fórmula D&D 5e: PROFICIENCY_BONUS_BASE + floor((TotalLevel - MIN_LEVEL) / PROFICIENCY_BONUS_DIVISOR)
    if (TotalLevel < DnDConstants::MIN_LEVEL)
    {
        return 0;
    }
    return DnDConstants::PROFICIENCY_BONUS_BASE +
           FMath::FloorToInt((TotalLevel - DnDConstants::MIN_LEVEL) / DnDConstants::PROFICIENCY_BONUS_DIVISOR);
}

#pragma endregion Proficiency Calculations

// ============================================================================
// Feature Calculations
// ============================================================================
#pragma region Feature Calculations

TArray<FName> CalculationHelpers::CollectProficienciesFromBackgroundAndVariantHuman(FName RaceName, FName SubraceName,
                                                                                    FName BackgroundName,
                                                                                    FName SelectedSkill,
                                                                                    UDataTable *RaceDataTable,
                                                                                    UDataTable *BackgroundDataTable)
{
    TSet<FName> ProficienciesSet;

    // Coleta proficiências de background
    if (BackgroundDataTable && BackgroundName != NAME_None)
    {
        if (FBackgroundDataRow *BackgroundRow =
                DataTableHelpers::FindBackgroundRow(BackgroundName, BackgroundDataTable))
        {
            // Adiciona proficiências de skills do background (agora via SkillProficiencyHandles)
            for (const FDataTableRowHandle &SkillProfHandle : BackgroundRow->SkillProficiencyHandles)
            {
                // Resolve handle para obter ID
                FName SkillProf = NAME_None;
                if (const FSkillDataRow *SkillRow =
                        DataTableRowHandleHelpers::ResolveHandle<FSkillDataRow>(SkillProfHandle))
                {
                    SkillProf = SkillRow->ID;
                }
                else if (SkillProfHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    SkillProf = SkillProfHandle.RowName;
                }

                if (SkillProf != NAME_None)
                {
                    ProficienciesSet.Add(SkillProf);
                }
            }

            // NOTA: Idiomas não são proficiências, são coletados separadamente em CollectLanguagesFromAllSources()
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

#pragma endregion Feature Calculations

// ============================================================================
// Language Calculations
// ============================================================================
#pragma region Language Calculations

TArray<FName> CalculationHelpers::CollectLanguagesFromAllSources(FName RaceName, FName SubraceName,
                                                                 FName BackgroundName,
                                                                 const TArray<FName> &SelectedLanguages,
                                                                 UDataTable *RaceDataTable,
                                                                 UDataTable *BackgroundDataTable)
{
    TSet<FName> LanguagesSet;

    // Coleta idiomas automáticos da raça base
    if (RaceDataTable && RaceName != NAME_None)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            // Resolve LanguageHandles para obter ID
            for (const FDataTableRowHandle &LanguageHandle : RaceRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        LanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    LanguagesSet.Add(LanguageHandle.RowName);
                }
            }
        }
    }

    // Coleta idiomas automáticos da sub-raça
    if (RaceDataTable && SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            // Resolve LanguageHandles para obter ID
            for (const FDataTableRowHandle &LanguageHandle : SubraceRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        LanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    LanguagesSet.Add(LanguageHandle.RowName);
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
            // Adiciona idiomas automáticos (não-escolhas) - agora via LanguageHandles
            for (const FDataTableRowHandle &LanguageHandle : BackgroundRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        LanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    LanguagesSet.Add(LanguageHandle.RowName);
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

#pragma endregion Language Calculations

// ============================================================================
// Hit Points Calculations
// ============================================================================
#pragma region Hit Points Calculations

int32 CalculationHelpers::CalculateHPGainForLevel(int32 HitDie, int32 Level, int32 ConstitutionModifier)
{
    if (Level < DnDConstants::MIN_LEVEL)
    {
        return 0;
    }

    int32 HPGain = 0;

    if (Level == DnDConstants::MIN_LEVEL)
    {
        // Level 1: HitDie + CON modifier
        HPGain = HitDie + ConstitutionModifier;
    }
    else
    {
        // Level 2+: (HitDie/HP_AVERAGE_DIVISOR + 1) + CON modifier (média do dado, arredondado para cima)
        // Fórmula: ceil(HitDie/HP_AVERAGE_DIVISOR) + CON modifier
        // Exemplo: HitDie 10 → ceil(10/2) = 5 + CON modifier
        HPGain = FMath::CeilToInt(HitDie / DnDConstants::HP_AVERAGE_DIVISOR) + ConstitutionModifier;
    }

    // HP nunca pode ser negativo (mínimo MIN_HP)
    return FMath::Max(DnDConstants::MIN_HP, HPGain);
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

        if (ClassName == NAME_None || LevelInClass < DnDConstants::MIN_LEVEL)
        {
            continue;
        }

        // Busca dados da classe para obter HitDie
        const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);
        if (!ClassRow)
        {
            continue;
        }

        const int32 HitDie = ClassRow->HitDie;
        if (HitDie <= 0)
        {
            // HitDie inválido, pula esta classe
            continue;
        }

        // Calcula HP para cada nível desta classe
        for (int32 Level = DnDConstants::MIN_LEVEL; Level <= LevelInClass; ++Level)
        {
            TotalHP += CalculateHPGainForLevel(HitDie, Level, ConstitutionModifier);
        }
    }

    // HP nunca pode ser negativo (mínimo MIN_HP)
    return FMath::Max(DnDConstants::MIN_HP, TotalHP);
}

#pragma endregion Hit Points Calculations

// ============================================================================
// Armor Class (AC) Calculations
// ============================================================================
#pragma region Armor Class Calculations

int32 CalculationHelpers::CalculateAC(int32 DexterityModifier, int32 ArmorACValue, FName ArmorType, bool bHasShield)
{
    int32 AC = 0;

    // Se não tem armadura, usa AC base (10 + DEX modifier)
    if (ArmorACValue == 0 || ArmorType == NAME_None)
    {
        AC = DnDConstants::BASE_AC + DexterityModifier;
    }
    else
    {
        // Calcula AC baseado no tipo de armadura
        if (ArmorType == TEXT("Light"))
        {
            // Light Armor: ACValue + DEX modifier (sem limite)
            AC = ArmorACValue + DexterityModifier;
        }
        else if (ArmorType == TEXT("Medium"))
        {
            // Medium Armor: ACValue + min(DEX modifier, +2)
            int32 LimitedDexModifier = FMath::Min(DexterityModifier, DnDConstants::MEDIUM_ARMOR_MAX_DEX);
            AC = ArmorACValue + LimitedDexModifier;
        }
        else if (ArmorType == TEXT("Heavy"))
        {
            // Heavy Armor: ACValue (sem DEX modifier)
            AC = ArmorACValue;
        }
        else
        {
            // Tipo de armadura desconhecido, usa AC base como fallback
            AC = DnDConstants::BASE_AC + DexterityModifier;
        }
    }

    // Adiciona bônus de escudo se aplicável
    if (bHasShield)
    {
        AC += DnDConstants::SHIELD_AC_BONUS;
    }

    return AC;
}

#pragma endregion Armor Class Calculations