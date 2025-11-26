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
// Boot Protocol - Complete Validation
// ============================================================================
#pragma region Boot Protocol

FValidationResult FCharacterSheetDataAssetValidators::ValidateAll(UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Valida todas as áreas e coleta correções
    FValidationResult VariantHumanResult = ValidateVariantHumanChoices(Asset);
    FValidationResult LanguageResult = ValidateLanguageChoices(Asset);
    FValidationResult MulticlassNameLevelResult = ValidateMulticlassNameLevelConsistency(Asset);
    FValidationResult MulticlassProgressionResult = ValidateMulticlassProgression(Asset);

    // Agrega todas as correções
    Result.Corrections.Append(VariantHumanResult.Corrections);
    Result.Corrections.Append(LanguageResult.Corrections);
    Result.Corrections.Append(MulticlassNameLevelResult.Corrections);
    Result.Corrections.Append(MulticlassProgressionResult.Corrections);

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;

    return Result;
}

#pragma endregion Boot Protocol

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

    // Valida usando ValidationHelpers (que aplica, mas precisamos apenas validar)
    // Para manter compatibilidade, ValidationHelpers já aplica, então não precisamos retornar correção
    // TODO: Refatorar ValidationHelpers para separar validação de aplicação
    TArray<FName> ValidAbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<FName> ChoicesCopy = Asset->CustomAbilityScoreChoices;
    bool bIsValid = ValidationHelpers::ValidateAbilityScoreChoices(ChoicesCopy, ValidAbilityNames, 2);

    if (!bIsValid)
    {
        // Se não é válido, precisa de correção (mas ValidationHelpers já aplica)
        // Por enquanto, apenas logamos
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: CustomAbilityScoreChoices precisa de correção (ValidationHelpers já "
                    "aplica)"));
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
        FName SelectedFeatCopy = Asset->SelectedFeat;
        bool bIsValid = ValidationHelpers::ValidateFeatSelection(SelectedFeatCopy, AvailableFeats);

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

    TArray<FName> ValidSkills = Asset->GetSkillNames();
    FName SelectedSkillCopy = Asset->SelectedSkill;
    bool bIsValid = ValidationHelpers::ValidateSkillSelection(SelectedSkillCopy, ValidSkills);

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

// ============================================================================
// Language Choices Validation
// ============================================================================
#pragma region Language Choices Validation

FValidationResult FCharacterSheetDataAssetValidators::ValidateLanguageChoices(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Se não há escolhas disponíveis, precisa limpar array
    if (!Asset->GetHasLanguageChoices() || Asset->MaxLanguageChoices == 0)
    {
        if (Asset->SelectedLanguages.Num() > 0)
        {
            FValidationCorrection Correction(EValidationCorrectionType::ClearArray,
                                             GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages), -1,
                                             0,
                                             TEXT("CharacterSheetDataAsset: Limpando SelectedLanguages (sem "
                                                  "escolhas disponíveis)"));
            Result.AddCorrection(Correction);
        }
        return Result;
    }

    // Valida quantidade (ValidationHelpers já aplica, mas verificamos se precisa de mais correções)
    TArray<FName> ValidLanguages = CharacterSheetHelpers::GetAvailableLanguageNames();
    TArray<FName> LanguagesCopy = Asset->SelectedLanguages;
    bool bIsValid =
        ValidationHelpers::ValidateAbilityScoreChoices(LanguagesCopy, ValidLanguages, Asset->MaxLanguageChoices);

    if (!bIsValid)
    {
        // ValidationHelpers já aplica, mas logamos
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: SelectedLanguages precisa de correção (ValidationHelpers já aplica)"));
    }

    return Result;
}

#pragma endregion Language Choices Validation

// ============================================================================
// Multiclass Validation
// ============================================================================
#pragma region Multiclass Validation

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassNameLevelConsistency(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Regra: Se não há classe, nível deve ser 0
        if (ClassName == NAME_None && LevelInClass != 0)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::AdjustValue, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass), i,
                0,
                FString::Printf(TEXT("Multiclass[%d] - Inconsistência: Name é NAME_None, LevelInClass deve ser 0"), i));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Nota: Esta função é const, então não pode atualizar bCanEditProgression diretamente.
    // A flag será atualizada pelos Handlers ou CorrectionApplier após aplicar correções.
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Valida se pode processar Progression (usa helper puro)
        if (!FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass))
        {
            // Se não pode processar e há itens, precisa limpar
            if (Entry.ClassData.Progression.Num() > 0)
            {
                FValidationCorrection Correction(
                    EValidationCorrectionType::ClearArray, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression),
                    i, 0,
                    FString::Printf(TEXT("Multiclass[%d] - Progression deve estar vazio: Name é NAME_None ou "
                                         "LevelInClass é 0"),
                                    i));
                Result.AddCorrection(Correction);
            }
        }
    }

    return Result;
}

#pragma endregion Multiclass Validation
