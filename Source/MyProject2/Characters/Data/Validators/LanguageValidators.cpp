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
#include "Utils/DataTableHelpers.h"

#pragma endregion Includes

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

    // Valida quantidade: não pode ter mais escolhas do que o máximo permitido
    if (Asset->SelectedLanguages.Num() > Asset->MaxLanguageChoices)
    {
        FValidationCorrection Correction(EValidationCorrectionType::ClearArray,
                                         GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages), -1,
                                         Asset->MaxLanguageChoices,
                                         FString::Printf(TEXT("CharacterSheetDataAsset: Reduzindo SelectedLanguages de "
                                                              "%d para %d (máximo permitido)"),
                                                         Asset->SelectedLanguages.Num(), Asset->MaxLanguageChoices));
        Result.AddCorrection(Correction);
    }

    // Valida nomes: todos devem ser válidos
    // Usa ProficiencyDataTable do Asset se disponível (Data-Driven), caso contrário usa fallback hardcoded
    TArray<FName> ValidLanguages =
        DataTableHelpers::ExtractNames(CharacterSheetHelpers::GetAvailableLanguageNames(Asset->ProficiencyDataTable));
    for (int32 i = 0; i < Asset->SelectedLanguages.Num(); ++i)
    {
        const FName &Language = Asset->SelectedLanguages[i];
        if (Language != NAME_None && !ValidLanguages.Contains(Language))
        {
            FValidationCorrection Correction(EValidationCorrectionType::ResetToNone,
                                             GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages), i, 0,
                                             FString::Printf(TEXT("CharacterSheetDataAsset: Idioma '%s' não é válido. "
                                                                  "Resetando."),
                                                             *Language.ToString()));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

#pragma endregion Language Choices Validation
