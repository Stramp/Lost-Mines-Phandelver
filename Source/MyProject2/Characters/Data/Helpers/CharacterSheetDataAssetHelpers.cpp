// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHelpers.h"
#include "../CharacterSheetDataAsset.h"
#include "../../../Utils/CharacterSheetHelpers.h"

void FCharacterSheetDataAssetHelpers::InitializeDefaultAbilityScores(TMap<FName, FAbilityScoreEntry> &AbilityScores,
                                                                     int32 DefaultValue)
{
    // Usa CharacterSheetHelpers para obter nomes de ability scores
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    for (const FName &AbilityName : AbilityNames)
    {
        FAbilityScoreEntry Entry;
        Entry.BaseScore = DefaultValue;
        AbilityScores.Add(AbilityName, Entry);
    }
}

void FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->CustomAbilityScoreChoices.Empty();
    Asset->SelectedFeat = NAME_None;
    Asset->SelectedSkill = NAME_None;
}
