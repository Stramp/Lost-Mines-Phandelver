// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHelpers.h"
#include "../CharacterSheetDataAsset.h"

void FCharacterSheetDataAssetHelpers::InitializeDefaultAbilityScores(TMap<FName, FAbilityScoreEntry> &AbilityScores)
{
    // Inicializa ability scores padrão (todos começam em 8)
    TArray<FName> AbilityNames = {TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                                  TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
    for (const FName &AbilityName : AbilityNames)
    {
        FAbilityScoreEntry Entry;
        Entry.BaseScore = 8;
        Entry.FinalScore = 8;
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
