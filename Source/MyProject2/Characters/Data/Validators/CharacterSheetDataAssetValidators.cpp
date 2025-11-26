// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/ValidationHelpers.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Variant Human Validation
// ============================================================================
#pragma region Variant Human Validation

/**
 * Valida todas as escolhas de Variant Human.
 * Orquestra validação de ability scores, feat e skill.
 */
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

/**
 * Valida escolhas de ability scores para Variant Human.
 * Deve ter exatamente 2 ability scores escolhidos.
 */
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

/**
 * Valida seleção de feat para Variant Human.
 * Verifica se o feat selecionado está disponível baseado nos ability scores.
 */
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

/**
 * Valida seleção de skill para Variant Human.
 * Verifica se o skill selecionado é válido.
 */
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

#pragma endregion Variant Human Validation

// ============================================================================
// Language Choices Validation
// ============================================================================
#pragma region Language Choices Validation

/**
 * Valida escolhas de idiomas.
 * Verifica quantidade máxima e limpa seleções se não há escolhas disponíveis.
 */
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

#pragma endregion Language Choices Validation
