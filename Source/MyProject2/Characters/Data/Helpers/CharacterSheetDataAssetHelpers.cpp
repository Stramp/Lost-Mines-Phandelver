// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHelpers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

// Engine includes
#include "Math/UnrealMathUtility.h"

#pragma endregion Includes

// ============================================================================
// Variant Human Helpers
// ============================================================================
#pragma region Variant Human Helpers

/**
 * Reseta todas as escolhas de Variant Human.
 * Limpa CustomAbilityScoreChoices, SelectedFeat e SelectedSkill.
 */
void FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->CustomAbilityScoreChoices.Empty();
    Asset->SelectedFeat = NAME_None;
    Asset->SelectedSkill = NAME_None;
}

#pragma endregion Variant Human Helpers

// ============================================================================
// Ability Scores Helpers
// ============================================================================
#pragma region Ability Scores Helpers

/**
 * Cria um mapa de ability scores a partir dos valores finais.
 * Usado para validação de feats e outras funcionalidades que precisam dos scores.
 */
TMap<FName, int32> FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(int32 FinalStrength, int32 FinalDexterity,
                                                                           int32 FinalConstitution,
                                                                           int32 FinalIntelligence, int32 FinalWisdom,
                                                                           int32 FinalCharisma)
{
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<int32> AbilityValues = {FinalStrength,     FinalDexterity, FinalConstitution,
                                   FinalIntelligence, FinalWisdom,    FinalCharisma};

    TMap<FName, int32> AbilityScores;
    AbilityScores.Reserve(AbilityNames.Num());

    for (int32 Index = 0; Index < AbilityNames.Num() && Index < AbilityValues.Num(); ++Index)
    {
        AbilityScores.Add(AbilityNames[Index], AbilityValues[Index]);
    }

    return AbilityScores;
}

#pragma endregion Ability Scores Helpers

// ============================================================================
// Point Buy Helpers
// ============================================================================
#pragma region Point Buy Helpers

/**
 * Atualiza campos Point Buy a partir de uma alocação ajustada.
 * Usado quando o sistema Point Buy ajusta automaticamente valores inválidos.
 */
void FCharacterSheetDataAssetHelpers::UpdatePointBuyFromAdjustedAllocation(UCharacterSheetDataAsset *Asset,
                                                                           const TMap<FName, int32> &AdjustedAllocation)
{
    if (!Asset)
    {
        return;
    }

    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    int32 *PointBuyFields[] = {&Asset->PointBuyStrength,     &Asset->PointBuyDexterity, &Asset->PointBuyConstitution,
                               &Asset->PointBuyIntelligence, &Asset->PointBuyWisdom,    &Asset->PointBuyCharisma};

    const int32 NumAbilityScores = AbilityNames.Num();
    const int32 NumPointBuyFields = sizeof(PointBuyFields) / sizeof(PointBuyFields[0]);
    const int32 MaxIndex = FMath::Min(NumAbilityScores, NumPointBuyFields);

    for (int32 Index = 0; Index < MaxIndex; ++Index)
    {
        if (const int32 *AdjustedValue = AdjustedAllocation.Find(AbilityNames[Index]))
        {
            *PointBuyFields[Index] = *AdjustedValue;
        }
    }
}

#pragma endregion Point Buy Helpers

// ============================================================================
// Property Validation Helpers
// ============================================================================
#pragma region Property Validation Helpers

bool FCharacterSheetDataAssetHelpers::IsCalculatedProperty(FName PropertyName)
{
    // Usa strings literais ao invés de GET_MEMBER_NAME_CHECKED para evitar necessidade de acesso a membros privados
    return PropertyName == FName(TEXT("bIsVariantHuman")) ||
           PropertyName == FName(TEXT("bHasLanguageChoices")) ||
           PropertyName == FName(TEXT("bHasSubraces")) ||
           PropertyName == FName(TEXT("bCanShowSheet"));
}

#pragma endregion Property Validation Helpers
