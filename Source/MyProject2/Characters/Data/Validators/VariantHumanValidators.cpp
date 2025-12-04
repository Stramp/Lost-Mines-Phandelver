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
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

// ============================================================================
// Variant Human Validation
// ============================================================================
#pragma region Variant Human Validation

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset || !Asset->GetIsVariantHuman())
    {
        return Result;
    }

    // Valida todas as áreas de Variant Human
    FValidationResult AbilityScoreResult = ValidateVariantHumanAbilityScoreChoices(Asset);
    FValidationResult FeatResult = ValidateVariantHumanFeat(Asset);
    FValidationResult SkillResult = ValidateVariantHumanSkill(Asset);

    // Agrega correções
    Result.Corrections.Append(AbilityScoreResult.Corrections);
    Result.Corrections.Append(FeatResult.Corrections);
    Result.Corrections.Append(SkillResult.Corrections);

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;

    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Valida usando função pura (apenas valida, não aplica)
    TArray<FName> ValidAbilityNames = DataTableHelpers::ExtractNames(CharacterSheetHelpers::GetAbilityScoreNames());
    TArray<int32> InvalidIndices;
    bool bHasDuplicates = false;
    bool bExceedsMax = false;
    bool bIsValid = ValidationHelpers::ValidateAbilityScoreChoicesPure(
        Asset->CustomAbilityScoreChoices, ValidAbilityNames, 2, InvalidIndices, bHasDuplicates, bExceedsMax);

    if (!bIsValid)
    {
        // Adiciona correção para remover elementos inválidos
        if (InvalidIndices.Num() > 0)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::RemoveInvalid,
                GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices), InvalidIndices,
                TEXT("CharacterSheetDataAsset: CustomAbilityScoreChoices contém elementos "
                     "inválidos. Removendo."));
            Result.AddCorrection(Correction);
        }

        // Adiciona correção para limpar array se excede máximo
        if (bExceedsMax)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::ClearArray,
                GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices), -1, 2,
                TEXT("CharacterSheetDataAsset: CustomAbilityScoreChoices excede máximo (2). "
                     "Ajustando."));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanFeat(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    if (Asset->FeatDataTable)
    {
        TArray<FName> AvailableFeats = Asset->GetAvailableFeatNames();
        bool bIsValid = ValidationHelpers::ValidateFeatSelectionPure(Asset->SelectedFeat, AvailableFeats);

        if (!bIsValid)
        {
            // Adiciona correção para resetar feat
            FValidationCorrection Correction(EValidationCorrectionType::ResetToNone,
                                             GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat), -1, 0,
                                             TEXT("CharacterSheetDataAsset: SelectedFeat não está disponível. "
                                                  "Resetando."));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanSkill(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Usa ProficiencyDataTable do Asset se disponível (Data-Driven), caso contrário usa fallback hardcoded
    TArray<FName> ValidSkills = DataTableHelpers::ExtractNames(Asset->GetSkillNames());
    bool bIsValid = ValidationHelpers::ValidateSkillSelectionPure(Asset->SelectedSkill, ValidSkills);

    if (!bIsValid)
    {
        // Adiciona correção para resetar skill
        FValidationCorrection Correction(EValidationCorrectionType::ResetToNone,
                                         GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill), -1, 0,
                                         TEXT("CharacterSheetDataAsset: SelectedSkill não é válido. Resetando."));
        Result.AddCorrection(Correction);
    }

    return Result;
}

#pragma endregion Variant Human Validation
