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

// Engine includes
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"

#pragma endregion Includes

// ============================================================================
// Local Helpers
// ============================================================================
#pragma region Local Helpers

namespace
{
    /**
     * Aplica correção ResetToNone para propriedade específica.
     */
    void ApplyResetToNone(UCharacterSheetDataAsset *Asset, const FValidationCorrection &Correction)
    {
        const FName PropertyName = Correction.PropertyName;

        if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat))
        {
            Asset->SelectedFeat = NAME_None;
        }
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill))
        {
            Asset->SelectedSkill = NAME_None;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: ResetToNone não implementado para %s"),
                   *PropertyName.ToString());
        }
    }

    /**
     * Aplica correção ClearArray para propriedade específica.
     */
    void ApplyClearArray(UCharacterSheetDataAsset *Asset, const FValidationCorrection &Correction)
    {
        const FName PropertyName = Correction.PropertyName;
        const int32 ArrayIndex = Correction.ArrayIndex;

        if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages))
        {
            Asset->SelectedLanguages.Empty();
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
                UE_LOG(LogTemp, Warning,
                       TEXT("CorrectionApplier: Progression limpo para Multiclass[%d] (bCanEditProgression = %s)"),
                       ArrayIndex, bCanEdit ? TEXT("true") : TEXT("false"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: ClearArray não implementado para %s"),
                   *PropertyName.ToString());
        }
    }

    /**
     * Aplica correção AdjustValue para propriedade específica.
     */
    void ApplyAdjustValue(UCharacterSheetDataAsset *Asset, const FValidationCorrection &Correction)
    {
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
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: AdjustValue não implementado para %s"),
                   *PropertyName.ToString());
        }
    }
} // namespace

#pragma endregion Local Helpers

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
            // TODO: Implementar quando necessário
            UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: RemoveInvalid não implementado ainda"));
            break;

        default:
            break;
        }

        // Log da mensagem se disponível
        if (!Correction.LogMessage.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("%s"), *Correction.LogMessage);
        }
    }
}

#pragma endregion Apply Corrections
