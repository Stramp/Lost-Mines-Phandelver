// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

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

// ============================================================================
// Multiclass Validation
// ============================================================================
#pragma region Multiclass Validation

/**
 * Valida e corrige consistência entre Name e LevelInClass em entradas de multiclasse.
 * Regra: Se Name == NAME_None, LevelInClass deve ser 0.
 */
void FCharacterSheetDataAssetValidators::ValidateMulticlassNameLevelConsistency(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        int32 &LevelInClass = Entry.ClassData.LevelInClass;

        // Regra: Se não há classe, nível deve ser 0
        if (ClassName == NAME_None && LevelInClass != 0)
        {
            LevelInClass = 0;
            UE_LOG(LogTemp, Warning,
                   TEXT("Multiclass[%d] - Inconsistência corrigida: Name é NAME_None, LevelInClass ajustado para 0"),
                   i);
        }
    }
}

/**
 * Valida e limpa array Progression se inválido em entradas de multiclasse.
 * Limpa Progression se Name == NAME_None ou LevelInClass == 0.
 */
void FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Valida se pode processar Progression (usa helper puro)
        if (!FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass))
        {
            // Se não pode processar, limpa o array
            if (Entry.ClassData.Progression.Num() > 0)
            {
                Entry.ClassData.Progression.Empty();
                UE_LOG(LogTemp, Warning,
                       TEXT("Multiclass[%d] - Progression limpo: Name é NAME_None ou LevelInClass é 0"), i);
            }
        }
    }
}

#pragma endregion Multiclass Validation
