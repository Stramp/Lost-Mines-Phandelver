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
            FCharacterSheetDataAssetHelpers::ApplyResetToNone(Asset, Correction);
            break;

        case EValidationCorrectionType::ClearArray:
            FCharacterSheetDataAssetHelpers::ApplyClearArray(Asset, Correction);
            break;

        case EValidationCorrectionType::AdjustValue:
            FCharacterSheetDataAssetHelpers::ApplyAdjustValue(Asset, Correction);
            break;

        case EValidationCorrectionType::RemoveInvalid:
            FCharacterSheetDataAssetHelpers::ApplyRemoveInvalid(Asset, Correction);
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
