// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetGetOptions.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "../../../Data/Tables/RaceDataTable.h"
#include "../../../Data/Tables/ClassDataTable.h"
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

TArray<FName> FCharacterSheetDataAssetGetOptions::GetClassNames(UDataTable *ClassDataTable)
{
    if (!ClassDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllClassNames(ClassDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubclassNames(UDataTable *ClassDataTable, FName ClassName)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubclasses(ClassName, ClassDataTable);
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

    // Para Variant Human, todos os feats estão disponíveis (sem pré-requisitos de nível)
    // Usa nível 1 e ability scores atuais
    return CharacterSheetHelpers::GetAvailableFeats(1, AbilityScores, FeatDataTable);
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames()
{
    // Usa helper global para evitar duplicação
    // TODO: Futuramente, quando SkillDataTable for implementado, usar:
    // return CharacterSheetHelpers::GetAllSkillNames(SkillDataTable);
    return CharacterSheetHelpers::GetSkillNames();
}
