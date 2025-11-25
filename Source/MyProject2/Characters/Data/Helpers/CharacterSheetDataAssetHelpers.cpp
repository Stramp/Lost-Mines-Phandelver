// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHelpers.h"

#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/CharacterSheetHelpers.h"

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
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<int32> AbilityValues = {FinalStrength,     FinalDexterity, FinalConstitution,
                                   FinalIntelligence, FinalWisdom,    FinalCharisma};

    TMap<FName, int32> AbilityScores;
    AbilityScores.Reserve(AbilityNames.Num());

    for (int32 Index = 0; Index < AbilityNames.Num() && Index < AbilityValues.Num(); ++Index)
    {
        AbilityScores.Add(AbilityNames[Index], AbilityValues[Index]);
    }

    return AbilityScores;
}

void FCharacterSheetDataAssetHelpers::UpdatePointBuyFromAdjustedAllocation(UCharacterSheetDataAsset *Asset,
                                                                           const TMap<FName, int32> &AdjustedAllocation)
{
    if (!Asset)
    {
        return;
    }

    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    int32 *PointBuyFields[] = {&Asset->PointBuyStrength,     &Asset->PointBuyDexterity, &Asset->PointBuyConstitution,
                               &Asset->PointBuyIntelligence, &Asset->PointBuyWisdom,    &Asset->PointBuyCharisma};

    for (int32 Index = 0; Index < AbilityNames.Num() && Index < 6; ++Index)
    {
        if (const int32 *AdjustedValue = AdjustedAllocation.Find(AbilityNames[Index]))
        {
            *PointBuyFields[Index] = *AdjustedValue;
        }
    }
}
