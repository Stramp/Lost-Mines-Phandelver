// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetGetOptions.h"

#include "Characters/Data/CharacterSheetDataAsset.h"
#include "CreateSheet/Multiclassing/MulticlassingMotor.h"
#include "CreateSheet/Multiclassing/MulticlassingResult.h"
#include "Data/Tables/RaceDataTable.h"
#include "Utils/CharacterSheetHelpers.h"

#include "Engine/DataTable.h"

TArray<FName> FCharacterSheetDataAssetGetOptions::GetRaceNames(const UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubraceNames(const UDataTable *RaceDataTable, FName SelectedRace)
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, RaceDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetBackgroundNames(const UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(BackgroundDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames()
{
    return CharacterSheetHelpers::GetAbilityScoreNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(const UDataTable *FeatDataTable,
                                                                        const TMap<FName, int32> &AbilityScores)
{
    if (!FeatDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAvailableFeatsForVariantHuman(AbilityScores, FeatDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames() { return CharacterSheetHelpers::GetSkillNames(); }

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNames()
{
    return CharacterSheetHelpers::GetAvailableLanguageNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
    FName RaceName, FName SubraceName, FName BackgroundName, const TArray<FName> &SelectedLanguages,
    const UDataTable *RaceDataTable, const UDataTable *BackgroundDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguagesForChoice(RaceName, SubraceName, BackgroundName,
                                                                 SelectedLanguages, RaceDataTable, BackgroundDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetClassNameOptions(const UDataTable *ClassDataTable,
                                                                      int32 FinalStrength, int32 FinalDexterity,
                                                                      int32 FinalConstitution, int32 FinalIntelligence,
                                                                      int32 FinalWisdom, int32 FinalCharisma)
{
    if (!ClassDataTable)
    {
        return {};
    }

    TArray<FName> FormattedClassNames;
    TArray<FClassOption> AvailableClasses =
        FMulticlassingMotor::GetAvailableClasses(ClassDataTable, FinalStrength, FinalDexterity, FinalConstitution,
                                                 FinalIntelligence, FinalWisdom, FinalCharisma);

    FormattedClassNames.Reserve(AvailableClasses.Num());

    for (const FClassOption &ClassOption : AvailableClasses)
    {
        const FString FormattedClassName = FormatClassNameWithRequirement(ClassOption);
        FormattedClassNames.Add(FName(*FormattedClassName));
    }

    return FormattedClassNames;
}

FString FCharacterSheetDataAssetGetOptions::FormatClassNameWithRequirement(const FClassOption &ClassOption)
{
    if (ClassOption.RequirementMessage.IsEmpty())
    {
        return ClassOption.ClassName.ToString();
    }

    return FString::Printf(TEXT("%s (%s)"), *ClassOption.ClassName.ToString(), *ClassOption.RequirementMessage);
}
