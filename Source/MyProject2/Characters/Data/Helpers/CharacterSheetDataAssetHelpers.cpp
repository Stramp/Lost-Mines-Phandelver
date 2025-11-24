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
