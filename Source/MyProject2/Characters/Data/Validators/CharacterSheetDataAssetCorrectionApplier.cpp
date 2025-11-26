// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetCorrectionApplier.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

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
            FCharacterSheetDataAssetHelpers::ApplyResetToNone(Asset, Correction);
            break;

        case EValidationCorrectionType::ClearArray:
            FCharacterSheetDataAssetHelpers::ApplyClearArray(Asset, Correction);
            break;

        case EValidationCorrectionType::AdjustValue:
            FCharacterSheetDataAssetHelpers::ApplyAdjustValue(Asset, Correction);
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
