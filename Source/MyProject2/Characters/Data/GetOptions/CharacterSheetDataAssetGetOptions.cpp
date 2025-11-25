// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetGetOptions.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "CreateSheet/Multiclassing/MulticlassingMotor.h"
#include "Engine/DataTable.h"

TArray<FName> FCharacterSheetDataAssetGetOptions::GetRaceNames(UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubraceNames(UDataTable *RaceDataTable, FName SelectedRace)
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, RaceDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetBackgroundNames(UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(BackgroundDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames()
{
    // Usa helper global para evitar duplicação
    return CharacterSheetHelpers::GetAbilityScoreNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(UDataTable *FeatDataTable,
                                                                        const TMap<FName, int32> &AbilityScores)
{
    if (!FeatDataTable)
    {
        return TArray<FName>();
    }

    // Para Variant Human, usa função específica que bypassa verificação de nível
    // Variant Human pode escolher feat no nível 1 (exceção especial de D&D 5e)
    return CharacterSheetHelpers::GetAvailableFeatsForVariantHuman(AbilityScores, FeatDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames()
{
    // Usa helper global para evitar duplicação
    // TODO: Futuramente, quando SkillDataTable for implementado, usar:
    // return CharacterSheetHelpers::GetAllSkillNames(SkillDataTable);
    return CharacterSheetHelpers::GetSkillNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNames()
{
    // TODO: Futuramente migrar para LanguageDataTable seguindo o princípio Data-Driven completo.
    // Por enquanto, hardcoded porque são constantes do sistema D&D 5e.
    return CharacterSheetHelpers::GetAvailableLanguageNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
    FName RaceName, FName SubraceName, FName BackgroundName, const TArray<FName> &SelectedLanguages,
    UDataTable *RaceDataTable, UDataTable *BackgroundDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguagesForChoice(RaceName, SubraceName, BackgroundName,
                                                                 SelectedLanguages, RaceDataTable, BackgroundDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetClassNames(const UCharacterSheetDataAsset *Asset)
{
    if (!Asset || !Asset->ClassDataTable)
    {
        return TArray<FName>();
    }

    // Obtém classes disponíveis do motor de multiclassing
    TArray<FClassOption> ClassOptions = FMulticlassingMotor::GetAvailableClasses(
        Asset->ClassDataTable, Asset->FinalStrength, Asset->FinalDexterity, Asset->FinalConstitution,
        Asset->FinalIntelligence, Asset->FinalWisdom, Asset->FinalCharisma);

    TArray<FName> FormattedClassNames;
    FormattedClassNames.Reserve(ClassOptions.Num());

    for (const FClassOption &Option : ClassOptions)
    {
        if (Option.RequirementMessage.IsEmpty())
        {
            // Classe disponível (RequirementMessage vazio): retorna nome normal
            FormattedClassNames.Add(Option.ClassName);
        }
        else
        {
            // Classe não disponível (RequirementMessage preenchido): adiciona prefixo com requisito específico
            FString FormattedName =
                FString::Printf(TEXT("[REQ %s] %s"), *Option.RequirementMessage, *Option.ClassName.ToString());
            FormattedClassNames.Add(FName(*FormattedName));
        }
    }

    return FormattedClassNames;
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubclassNames(UDataTable *ClassDataTable, FName ClassName)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubclasses(ClassName, ClassDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetChoiceOptions(const UCharacterSheetDataAsset *Asset,
                                                                   FName ChoiceID, FName ClassName, int32 ClassLevel)
{
    TArray<FName> Options;

    if (!Asset || !Asset->ClassDataTable)
    {
        return Options;
    }

    // Usa CharacterSheetHelpers para buscar opções
    Options = CharacterSheetHelpers::GetChoiceOptions(ChoiceID, ClassName, ClassLevel, Asset->ClassDataTable);

    return Options;
}
