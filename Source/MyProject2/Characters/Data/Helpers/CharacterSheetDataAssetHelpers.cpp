// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHelpers.h"
#include "Characters/Data/CharacterSheetDataAsset.h"

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

TMap<FName, int32> FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(int32 FinalStrength, int32 FinalDexterity,
                                                                           int32 FinalConstitution,
                                                                           int32 FinalIntelligence, int32 FinalWisdom,
                                                                           int32 FinalCharisma)
{
    TMap<FName, int32> AbilityScores;
    AbilityScores.Add(TEXT("Strength"), FinalStrength);
    AbilityScores.Add(TEXT("Dexterity"), FinalDexterity);
    AbilityScores.Add(TEXT("Constitution"), FinalConstitution);
    AbilityScores.Add(TEXT("Intelligence"), FinalIntelligence);
    AbilityScores.Add(TEXT("Wisdom"), FinalWisdom);
    AbilityScores.Add(TEXT("Charisma"), FinalCharisma);
    return AbilityScores;
}
