// Copyright Epic Games, Inc. All Rights Reserved.

#include "CalculationHelpers.h"
#include "CharacterSheetHelpers.h"
#include "DataTableHelpers.h"
#include "../Data/Tables/RaceDataTable.h"
#include "../Data/Tables/ClassDataTable.h"
#include "../Data/Tables/BackgroundDataTable.h"
#include "../Characters/Data/CharacterSheetDataAsset.h"
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

int32 CalculationHelpers::CalculateFinalAbilityScore(int32 RacialBonus, int32 PointBuyAllocation, int32 ASIBonus)
{
    // Base fixa = 8 (constante hardcoded)
    const int32 BaseScore = 8;
    return BaseScore + RacialBonus + PointBuyAllocation + ASIBonus;
}

void CalculationHelpers::ResetFinalScoresToBase(int32 &FinalStrength, int32 &FinalDexterity, int32 &FinalConstitution,
                                                int32 &FinalIntelligence, int32 &FinalWisdom, int32 &FinalCharisma)
{
    const int32 BaseScore = 8;
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
                                                         FName BackgroundName, FName SelectedSkill,
                                                         UDataTable *RaceDataTable, UDataTable *ClassDataTable,
                                                         UDataTable *BackgroundDataTable)
{
    TArray<FName> Proficiencies;

    // Coleta proficiências de todas as classes (multi-classing)
    if (ClassDataTable)
    {
        for (const FClassLevelEntry &ClassEntry : ClassLevels)
        {
            if (ClassEntry.ClassName == NAME_None)
            {
                continue;
            }

            // Busca row da classe
            if (FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassEntry.ClassName, ClassDataTable))
            {
                // Adiciona proficiências de armas
                for (const FClassProficiency &Prof : ClassRow->WeaponProficiencies)
                {
                    if (Prof.ProficiencyName != NAME_None)
                    {
                        Proficiencies.AddUnique(Prof.ProficiencyName);
                    }
                }

                // Adiciona proficiências de armaduras
                for (const FClassProficiency &Prof : ClassRow->ArmorProficiencies)
                {
                    if (Prof.ProficiencyName != NAME_None)
                    {
                        Proficiencies.AddUnique(Prof.ProficiencyName);
                    }
                }

                // Adiciona proficiências de saving throws
                for (const FClassProficiency &Prof : ClassRow->SavingThrowProficiencies)
                {
                    if (Prof.ProficiencyName != NAME_None)
                    {
                        Proficiencies.AddUnique(Prof.ProficiencyName);
                    }
                }

                // Adiciona proficiências de skills
                for (const FClassProficiency &Prof : ClassRow->SkillProficiencies)
                {
                    if (Prof.ProficiencyName != NAME_None)
                    {
                        Proficiencies.AddUnique(Prof.ProficiencyName);
                    }
                }
            }
        }
    }

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
                    Proficiencies.AddUnique(SkillProf);
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
        Proficiencies.AddUnique(SelectedSkill);
    }

    // NOTA: Proficiências de raça podem vir de Traits especiais (ex: Dwarf Stonecunning)
    // Por enquanto, não implementado. Se necessário no futuro, adicionar lógica aqui
    // para extrair proficiências de Traits específicos da raça/sub-raça.

    return Proficiencies;
}

TArray<FName> CalculationHelpers::CalculateLanguages(FName RaceName, FName SubraceName, FName BackgroundName,
                                                     const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                     UDataTable *BackgroundDataTable)
{
    TArray<FName> Languages;

    // Coleta idiomas automáticos da raça base
    if (RaceDataTable && RaceName != NAME_None)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            for (const FName &Language : RaceRow->Languages)
            {
                if (Language != NAME_None)
                {
                    Languages.AddUnique(Language);
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
                    Languages.AddUnique(Language);
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
                    Languages.AddUnique(Language);
                }
            }
        }
    }

    // Adiciona idiomas escolhidos pelo jogador
    for (const FName &SelectedLanguage : SelectedLanguages)
    {
        if (SelectedLanguage != NAME_None)
        {
            Languages.AddUnique(SelectedLanguage);
        }
    }

    return Languages;
}
