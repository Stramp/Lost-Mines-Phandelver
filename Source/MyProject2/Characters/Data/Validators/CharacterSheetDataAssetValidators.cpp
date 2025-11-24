// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetValidators.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/ValidationHelpers.h"
#include "Logging/LogMacros.h"

void FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset || !Asset->GetIsVariantHuman())
    {
        return;
    }

    ValidateVariantHumanAbilityScoreChoices(Asset);
    ValidateVariantHumanFeat(Asset);
    ValidateVariantHumanSkill(Asset);
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Usa ValidationHelpers para validar escolhas de ability scores
    TArray<FName> ValidAbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    ValidationHelpers::ValidateAbilityScoreChoices(Asset->CustomAbilityScoreChoices, ValidAbilityNames, 2);
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanFeat(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Usa ValidationHelpers para validar seleção de feat
    if (Asset->FeatDataTable)
    {
        TArray<FName> AvailableFeats = Asset->GetAvailableFeatNames();
        if (!ValidationHelpers::ValidateFeatSelection(Asset->SelectedFeat, AvailableFeats))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedFeat não está disponível. Resetando."));
        }
    }
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanSkill(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Usa ValidationHelpers para validar seleção de skill
    TArray<FName> ValidSkills = Asset->GetSkillNames();
    if (!ValidationHelpers::ValidateSkillSelection(Asset->SelectedSkill, ValidSkills))
    {
        UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedSkill não é válido. Resetando."));
    }
}

void FCharacterSheetDataAssetValidators::ValidateLanguageChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Se não há escolhas disponíveis, limpa SelectedLanguages
    if (!Asset->GetHasLanguageChoices() || Asset->MaxLanguageChoices == 0)
    {
        Asset->SelectedLanguages.Empty();
        return;
    }

    // Valida quantidade de escolhas (não pode exceder MaxLanguageChoices)
    TArray<FName> ValidLanguages = CharacterSheetHelpers::GetAvailableLanguageNames();
    ValidationHelpers::ValidateAbilityScoreChoices(Asset->SelectedLanguages, ValidLanguages, Asset->MaxLanguageChoices);
}
