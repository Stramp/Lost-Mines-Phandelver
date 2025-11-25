// Copyright Epic Games, Inc. All Rights Reserved.

#include "MulticlassingMotor.h"
#include "MulticlassingResult.h"
#include "Data/Tables/ClassDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/CalculationHelpers.h"
#include "Math/UnrealMathUtility.h"

// FClassLevelEntry ainda é usado pelo motor de Multiclassing (mantido para compatibilidade)
// FMultClass é a nova struct simples para o Data Asset

FMulticlassingResult FMulticlassingMotor::CalculateMulticlassing(const TArray<FClassLevelEntry> &ClassLevels,
                                                                 UDataTable *ClassDataTable)
{
    FMulticlassingResult Result;

    // 1. Calcula TotalLevel (reutiliza helper existente)
    Result.TotalLevel = CharacterSheetHelpers::CalculateTotalLevel(ClassLevels);

    // 2. Calcula ProficiencyBonus (reutiliza helper existente)
    // Fórmula D&D 5e: 1 + floor((TotalLevel - 1) / 4)
    Result.ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(Result.TotalLevel);

    // 3. Coleta features disponíveis
    Result.AvailableFeatures = CollectAvailableFeatures(ClassLevels, ClassDataTable);

    // 4. Coleta informações de spellcasting (para SpellSystem)
    Result.SpellcastingInfo = CollectSpellcastingInfo(ClassLevels, ClassDataTable);

    return Result;
}

TArray<FClassFeature> FMulticlassingMotor::CollectAvailableFeatures(const TArray<FClassLevelEntry> &ClassLevels,
                                                                    UDataTable *ClassDataTable)
{
    TArray<FClassFeature> AllFeatures;

    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        // Coleta features desta classe até o nível atual
        TArray<FClassFeature> ClassFeatures = GetFeaturesForClassLevel(Entry.ClassName, Entry.Level, ClassDataTable);

        // Resolve escolhas do jogador (filtra features baseado em subclass, etc.)
        ResolveFeatureChoices(ClassFeatures, ClassLevels, ClassDataTable);

        AllFeatures.Append(ClassFeatures);
    }

    return AllFeatures;
}

TArray<FClassFeature> FMulticlassingMotor::GetFeaturesForClassLevel(FName ClassName, int32 ClassLevel,
                                                                    UDataTable *ClassDataTable)
{
    TArray<FClassFeature> Features;

    FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return Features;
    }

    // Filtra features até o nível atual
    for (const FClassFeature &Feature : ClassRow->Features)
    {
        if (Feature.LevelUnlocked <= ClassLevel)
        {
            Features.Add(Feature);
        }
    }

    return Features;
}

void FMulticlassingMotor::ResolveFeatureChoices(TArray<FClassFeature> &Features,
                                                const TArray<FClassLevelEntry> &ClassLevels, UDataTable *ClassDataTable)
{
    // TODO: Implementar lógica de resolução de escolhas
    // - Filtrar features baseado em subclass escolhida
    // - Filtrar features baseado em outras escolhas (fighting style, etc.)
    // - Remover features que dependem de escolhas não feitas
}

TArray<FClassSpellcastingInfo> FMulticlassingMotor::CollectSpellcastingInfo(const TArray<FClassLevelEntry> &ClassLevels,
                                                                            UDataTable *ClassDataTable)
{
    TArray<FClassSpellcastingInfo> InfoArray;

    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(Entry.ClassName, ClassDataTable);
        if (!ClassRow || !ClassRow->SpellcastingInfo.bHasSpellcasting)
        {
            continue;
        }

        FClassSpellcastingInfo Info;
        Info.ClassName = Entry.ClassName;
        Info.ClassLevel = Entry.Level;
        Info.bHasSpellcasting = true;
        Info.SpellcastingAbility = ClassRow->SpellcastingInfo.SpellcastingAbility;
        Info.SpellSlotsPerLevel = ClassRow->SpellcastingInfo.SpellSlotsPerLevel;

        InfoArray.Add(Info);
    }

    return InfoArray;
}

TMap<FName, int32> FMulticlassingMotor::GetClassLevelsInfo(const TArray<FClassLevelEntry> &ClassLevels)
{
    TMap<FName, int32> Info;
    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        Info.Add(Entry.ClassName, Entry.Level);
    }
    return Info;
}

TArray<FClassOption> FMulticlassingMotor::GetAvailableClasses(UDataTable *ClassDataTable, int32 FinalStrength,
                                                              int32 FinalDexterity, int32 FinalConstitution,
                                                              int32 FinalIntelligence, int32 FinalWisdom,
                                                              int32 FinalCharisma)
{
    TArray<FClassOption> Options;

    if (!ClassDataTable)
    {
        return Options;
    }

    // Obtém todas as classes do Data Table
    TArray<FName> AllClassNames = CharacterSheetHelpers::GetAllClassNames(ClassDataTable);

    // Para cada classe, verifica se atende aos requisitos de multiclassing D&D 5e
    for (const FName &ClassName : AllClassNames)
    {
        FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, ClassDataTable);
        if (!ClassRow)
        {
            continue;
        }

        // TODO: Quando MulticlassingPrerequisites for adicionado ao ClassDataTable,
        // usar ClassRow->MulticlassingPrerequisites para validar
        // Por enquanto, implementa regras D&D 5e conhecidas

        FString RequirementMessage = TEXT("");

        // Regras D&D 5e para requisitos de multiclassing
        // Cada classe precisa de 13+ no atributo principal
        FString ClassNameStr = ClassName.ToString().ToLower();

        if (ClassNameStr.Contains(TEXT("fighter")))
        {
            // Fighter precisa de STR 13 OU DEX 13
            if (FinalStrength < 13 && FinalDexterity < 13)
            {
                // Ambos abaixo: mostra ambos
                RequirementMessage = TEXT("STR 13 ou DEX 13");
            }
            // Se pelo menos um está OK, RequirementMessage fica vazio (disponível)
        }
        else if (ClassNameStr.Contains(TEXT("wizard")))
        {
            if (FinalIntelligence < 13)
            {
                RequirementMessage = TEXT("INT 13");
            }
        }
        else if (ClassNameStr.Contains(TEXT("cleric")) || ClassNameStr.Contains(TEXT("druid")) ||
                 ClassNameStr.Contains(TEXT("ranger")))
        {
            if (FinalWisdom < 13)
            {
                RequirementMessage = TEXT("WIS 13");
            }
        }
        else if (ClassNameStr.Contains(TEXT("rogue")))
        {
            if (FinalDexterity < 13)
            {
                RequirementMessage = TEXT("DEX 13");
            }
        }
        else if (ClassNameStr.Contains(TEXT("barbarian")))
        {
            if (FinalStrength < 13)
            {
                RequirementMessage = TEXT("STR 13");
            }
        }
        else if (ClassNameStr.Contains(TEXT("bard")) || ClassNameStr.Contains(TEXT("paladin")) ||
                 ClassNameStr.Contains(TEXT("sorcerer")) || ClassNameStr.Contains(TEXT("warlock")))
        {
            if (FinalCharisma < 13)
            {
                RequirementMessage = TEXT("CHA 13");
            }
        }
        else if (ClassNameStr.Contains(TEXT("monk")))
        {
            // Monk precisa de DEX 13 E WIS 13
            if (FinalDexterity < 13 && FinalWisdom < 13)
            {
                RequirementMessage = TEXT("DEX 13 e WIS 13");
            }
            else if (FinalDexterity < 13)
            {
                RequirementMessage = TEXT("DEX 13");
            }
            else if (FinalWisdom < 13)
            {
                RequirementMessage = TEXT("WIS 13");
            }
            // Se ambos estão OK, RequirementMessage fica vazio (disponível)
        }
        // Se não reconhecer a classe, assume disponível (RequirementMessage fica vazio)

        Options.Add(FClassOption(ClassName, RequirementMessage));
    }

    return Options;
}
