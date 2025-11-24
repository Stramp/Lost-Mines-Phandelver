// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetGetOptions.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "../../../Data/Tables/RaceDataTable.h"
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
