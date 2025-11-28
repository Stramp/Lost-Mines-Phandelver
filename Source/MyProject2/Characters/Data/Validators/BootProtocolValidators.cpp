// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

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
    // NOTA: ValidateDataTables não retorna correções, apenas alerta (validação preventiva)
    FValidationResult DataTablesResult = ValidateDataTables(Asset);
    FValidationResult VariantHumanResult = ValidateVariantHumanChoices(Asset);
    FValidationResult LanguageResult = ValidateLanguageChoices(Asset);
    FValidationResult MulticlassNameLevelResult = ValidateMulticlassNameLevelConsistency(Asset);
    FValidationResult MulticlassProgressionResult = ValidateMulticlassProgression(Asset);
    FValidationResult MulticlassProficienciesResult = ValidateMulticlassProficiencies(Asset);
    FValidationResult MulticlassRequirementTagsResult = ValidateMulticlassRequirementTags(Asset);

    // Agrega todas as correções
    Result.Corrections.Append(DataTablesResult.Corrections);
    Result.Corrections.Append(VariantHumanResult.Corrections);
    Result.Corrections.Append(LanguageResult.Corrections);
    Result.Corrections.Append(MulticlassNameLevelResult.Corrections);
    Result.Corrections.Append(MulticlassProgressionResult.Corrections);
    Result.Corrections.Append(MulticlassProficienciesResult.Corrections);
    Result.Corrections.Append(MulticlassRequirementTagsResult.Corrections);

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;

    return Result;
}

#pragma endregion Boot Protocol
