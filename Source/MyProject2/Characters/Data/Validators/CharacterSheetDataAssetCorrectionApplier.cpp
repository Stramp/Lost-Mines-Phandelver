// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetCorrectionApplier.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Data Structures
#include "Data/Structures/MulticlassTypes.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"

#pragma endregion Includes

// ============================================================================
// Apply Corrections
// ============================================================================
#pragma region Apply Corrections

void FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(UCharacterSheetDataAsset *Asset,
                                                                 const FValidationResult &ValidationResult)
{
    if (!Asset || !ValidationResult.bNeedsCorrection)
    {
        return;
    }

    // Marca objeto como modificado antes de aplicar correções
    Asset->Modify();

    for (const FValidationCorrection &Correction : ValidationResult.Corrections)
    {
        switch (Correction.CorrectionType)
        {
        case EValidationCorrectionType::ResetToNone:
            ApplyResetToNone(Asset, Correction);
            break;

        case EValidationCorrectionType::ClearArray:
            ApplyClearArray(Asset, Correction);
            break;

        case EValidationCorrectionType::AdjustValue:
            ApplyAdjustValue(Asset, Correction);
            break;

        case EValidationCorrectionType::RemoveInvalid:
            ApplyRemoveInvalid(Asset, Correction);
            break;

        default:
            break;
        }

        // Log da mensagem se disponível (sem alert, apenas warning no log)
        if (!Correction.LogMessage.IsEmpty())
        {
            FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyCorrections"));
            FLoggingSystem::LogWarning(Context, Correction.LogMessage, false); // false = sem alert (popup)
        }
    }
}

#pragma endregion Apply Corrections

// ============================================================================
// Correction Application Helpers
// ============================================================================
#pragma region Correction Application Helpers

void FCharacterSheetDataAssetCorrectionApplier::ApplyResetToNone(UCharacterSheetDataAsset *Asset,
                                                                  const FValidationCorrection &Correction)
{
    if (!Asset)
    {
        return;
    }

    const FName PropertyName = Correction.PropertyName;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat))
    {
        Asset->SelectedFeat = NAME_None;
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill))
    {
        Asset->SelectedSkill = NAME_None;
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name))
    {
        // Name está dentro de Multiclass array
        const int32 ArrayIndex = Correction.ArrayIndex;
        if (ArrayIndex >= 0 && ArrayIndex < Asset->Multiclass.Num())
        {
            // Reseta Name e LevelInClass (quando Name é resetado, LevelInClass também deve ser 0)
            Asset->Multiclass[ArrayIndex].ClassData.Name = NAME_None;
            Asset->Multiclass[ArrayIndex].ClassData.LevelInClass = 0;
        }
    }
    else
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyResetToNone"));
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("ResetToNone não implementado para %s"), *PropertyName.ToString()), true);
    }
}

void FCharacterSheetDataAssetCorrectionApplier::ApplyClearArray(UCharacterSheetDataAsset *Asset,
                                                                const FValidationCorrection &Correction)
{
    if (!Asset)
    {
        return;
    }

    const FName PropertyName = Correction.PropertyName;
    const int32 ArrayIndex = Correction.ArrayIndex;
    const int32 NewValue = Correction.NewValue; // Para SetNum quando NewValue > 0

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages))
    {
        // Se NewValue > 0, reduz array para esse tamanho, senão limpa completamente
        if (NewValue > 0)
        {
            Asset->SelectedLanguages.SetNum(NewValue);
        }
        else
        {
            Asset->SelectedLanguages.Empty();
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices))
    {
        // Se NewValue > 0, reduz array para esse tamanho (máximo de 2 para Variant Human), senão limpa completamente
        if (NewValue > 0)
        {
            Asset->CustomAbilityScoreChoices.SetNum(NewValue);
            FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyClearArray"));
            FLoggingSystem::LogInfo(
                Context, FString::Printf(TEXT("CustomAbilityScoreChoices reduzido para %d itens (máximo para Variant Human)"),
                                         NewValue));
        }
        else
        {
            Asset->CustomAbilityScoreChoices.Empty();
            FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyClearArray"));
            FLoggingSystem::LogInfo(Context, TEXT("CustomAbilityScoreChoices limpo completamente"));
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression))
    {
        // Progression está dentro de Multiclass array
        if (ArrayIndex >= 0 && ArrayIndex < Asset->Multiclass.Num())
        {
            Asset->Multiclass[ArrayIndex].ClassData.Progression.Empty();
            // Atualiza flag após limpar
            const FName ClassName = Asset->Multiclass[ArrayIndex].ClassData.Name;
            const int32 LevelInClass = Asset->Multiclass[ArrayIndex].ClassData.LevelInClass;
            const bool bCanEdit = FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass);
            Asset->Multiclass[ArrayIndex].ClassData.bCanEditProgression = bCanEdit;
            Asset->Multiclass[ArrayIndex].ClassData.bCanEditProficiencies = bCanEdit;
            FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyClearArray"));
            FLoggingSystem::LogInfo(
                Context, FString::Printf(TEXT("Progression limpo para Multiclass[%d] (bCanEditProgression = %s)"),
                                         ArrayIndex, bCanEdit ? TEXT("true") : TEXT("false")));
        }
    }
    else
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyClearArray"));
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("ClearArray não implementado para %s"), *PropertyName.ToString()), true);
    }
}

void FCharacterSheetDataAssetCorrectionApplier::ApplyAdjustValue(UCharacterSheetDataAsset *Asset,
                                                                  const FValidationCorrection &Correction)
{
    if (!Asset)
    {
        return;
    }

    const FName PropertyName = Correction.PropertyName;
    const int32 ArrayIndex = Correction.ArrayIndex;
    const int32 NewValue = Correction.NewValue;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass))
    {
        // LevelInClass está dentro de Multiclass array
        if (ArrayIndex >= 0 && ArrayIndex < Asset->Multiclass.Num())
        {
            Asset->Multiclass[ArrayIndex].ClassData.LevelInClass = NewValue;
            // Atualiza flags bCanEditProgression e bCanEditProficiencies após ajustar LevelInClass
            const FName ClassName = Asset->Multiclass[ArrayIndex].ClassData.Name;
            const bool bCanEdit = FMulticlassHelpers::CanProcessProgression(ClassName, NewValue);
            Asset->Multiclass[ArrayIndex].ClassData.bCanEditProgression = bCanEdit;
            Asset->Multiclass[ArrayIndex].ClassData.bCanEditProficiencies = bCanEdit;
        }
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassSkills, qtdAvailable))
    {
        // qtdAvailable está dentro de FSkills dentro de Proficiencies array dentro de Multiclass array
        if (ArrayIndex >= 0 && ArrayIndex < Asset->Multiclass.Num())
        {
            // Ajusta qtdAvailable para todas as proficiências da entrada
            for (FMulticlassProficienciesEntry &ProficiencyEntry :
                 Asset->Multiclass[ArrayIndex].ClassData.Proficiencies)
            {
                ProficiencyEntry.FSkills.qtdAvailable = NewValue;
            }
        }
    }
    else
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyAdjustValue"));
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("AdjustValue não implementado para %s"), *PropertyName.ToString()), true);
    }
}

void FCharacterSheetDataAssetCorrectionApplier::ApplyRemoveInvalid(UCharacterSheetDataAsset *Asset,
                                                                   const FValidationCorrection &Correction)
{
    if (!Asset)
    {
        return;
    }

    const FName PropertyName = Correction.PropertyName;
    const TArray<int32> &InvalidIndices = Correction.InvalidIndices;

    if (InvalidIndices.Num() == 0)
    {
        return;
    }

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices))
    {
        // Remove elementos inválidos do array (em ordem reversa para manter índices válidos)
        TArray<int32> SortedIndices = InvalidIndices;
        SortedIndices.Sort([](const int32 &A, const int32 &B) { return A > B; }); // Ordem decrescente

        for (int32 Index : SortedIndices)
        {
            if (Index >= 0 && Index < Asset->CustomAbilityScoreChoices.Num())
            {
                Asset->CustomAbilityScoreChoices.RemoveAt(Index);
            }
        }

        FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyRemoveInvalid"));
        FLoggingSystem::LogInfo(Context,
                                FString::Printf(TEXT("Removidos %d elementos inválidos de CustomAbilityScoreChoices"),
                                                InvalidIndices.Num()));
    }
    else
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("ApplyRemoveInvalid"));
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("RemoveInvalid não implementado para %s"), *PropertyName.ToString()), true);
    }
}

#pragma endregion Correction Application Helpers
