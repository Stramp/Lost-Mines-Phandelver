// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHelpers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UnrealType.h"

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
    return PropertyName == FName(TEXT("bIsVariantHuman")) || PropertyName == FName(TEXT("bHasLanguageChoices")) ||
           PropertyName == FName(TEXT("bHasSubraces")) || PropertyName == FName(TEXT("bCanShowSheet"));
}

#pragma endregion Property Validation Helpers

// ============================================================================
// Handler Helpers
// ============================================================================
#pragma region Handler Helpers

void FCharacterSheetDataAssetHelpers::LogPropertyChange(FName PropertyName)
{
    UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty me chamou: %s mudou"), *PropertyName.ToString());
}

bool FCharacterSheetDataAssetHelpers::ValidateAsset(UCharacterSheetDataAsset *Asset) { return Asset != nullptr; }

void FCharacterSheetDataAssetHelpers::ResetSubraceIfRaceChanged(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!Asset)
    {
        return;
    }

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
    {
        if (Asset->SelectedSubrace != NAME_None)
        {
            Asset->Modify();
            Asset->SelectedSubrace = NAME_None;
        }
    }
}

void FCharacterSheetDataAssetHelpers::LogDataTableStatus(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    bool bAllDataTablesSelected =
        Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

    if (bAllDataTablesSelected)
    {
        UE_LOG(LogTemp, Log,
               TEXT("CharacterSheetDataAsset: Todos os Data Tables foram selecionados! Todas as categorias estão "
                    "visíveis."));
    }
    else
    {
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: Ainda faltam Data Tables. Race: %s, Background: %s, Feat: %s"),
               Asset->RaceDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->BackgroundDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->FeatDataTable ? TEXT("OK") : TEXT("FALTANDO"));
    }
}

FString FCharacterSheetDataAssetHelpers::GetFormattedClassName(const FString &ClassName)
{
    return ClassName.IsEmpty() ? TEXT("Unknown") : ClassName;
}

bool FCharacterSheetDataAssetHelpers::ResetClassWithRequirementTag(FMulticlassEntry &Entry, int32 Index)
{
    FString ClassName = Entry.ClassData.Name.ToString();

    if (ClassName.StartsWith(TEXT("[")))
    {
        Entry.ClassData.Name = NAME_None;
        UE_LOG(LogTemp, Warning, TEXT("Multiclass[%d] - Classe com tag de requerimento resetada: %s"), Index,
               *ClassName);
        return true;
    }

    return false;
}

#pragma endregion Handler Helpers

// ============================================================================
// Correction Application Helpers
// ============================================================================
#pragma region Correction Application Helpers

void FCharacterSheetDataAssetHelpers::ApplyResetToNone(UCharacterSheetDataAsset *Asset,
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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: ResetToNone não implementado para %s"),
               *PropertyName.ToString());
    }
}

void FCharacterSheetDataAssetHelpers::ApplyClearArray(UCharacterSheetDataAsset *Asset,
                                                      const FValidationCorrection &Correction)
{
    if (!Asset)
    {
        return;
    }

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

void FCharacterSheetDataAssetHelpers::ApplyAdjustValue(UCharacterSheetDataAsset *Asset,
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
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CorrectionApplier: AdjustValue não implementado para %s"),
               *PropertyName.ToString());
    }
}

#pragma endregion Correction Application Helpers
