// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHelpers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Structures/MulticlassTypes.h"
#include "Data/Tables/ClassDataTable.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DnDConstants.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UnrealType.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#endif

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

TArray<int32> FCharacterSheetDataAssetHelpers::CreateAttributesArray(int32 FinalStrength, int32 FinalDexterity,
                                                                     int32 FinalConstitution, int32 FinalIntelligence,
                                                                     int32 FinalWisdom, int32 FinalCharisma)
{
    return {FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence, FinalWisdom, FinalCharisma};
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

    // Verifica se todos os Data Tables obrigatórios foram selecionados
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr &&
                                  Asset->ClassDataTable != nullptr && Asset->FeatDataTable != nullptr;

    if (bAllDataTablesSelected)
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("LogDataTableStatus"));
        FLoggingSystem::LogInfo(Context,
                                TEXT("Todos os Data Tables foram selecionados! Todas as categorias estão visíveis."));
    }
    else
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("LogDataTableStatus"));
        FLoggingSystem::LogWarning(Context,
                                   FString::Printf(TEXT("Ainda faltam Data Tables. Race: %s, Background: %s, Feat: %s"),
                                                   Asset->RaceDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                                                   Asset->BackgroundDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                                                   Asset->FeatDataTable ? TEXT("OK") : TEXT("FALTANDO")),
                                   true);
    }
}

FString FCharacterSheetDataAssetHelpers::GetFormattedClassName(const FString &ClassName)
{
    return ClassName.IsEmpty() ? TEXT("Unknown") : ClassName;
}

bool FCharacterSheetDataAssetHelpers::ExtractRequirementTag(const FString &ClassName, FString &OutTag)
{
    if (!ClassName.StartsWith(TEXT("[")))
    {
        return false;
    }

    // Encontra o fechamento da tag "]"
    int32 TagEndIndex = ClassName.Find(TEXT("]"));
    if (TagEndIndex == INDEX_NONE)
    {
        return false;
    }

    // Extrai tag incluindo os colchetes: "[INT +3]"
    OutTag = ClassName.Mid(0, TagEndIndex + 1);
    return true;
}

bool FCharacterSheetDataAssetHelpers::ParseRequirementTag(const FString &Tag, FString &OutAttributeAbbr,
                                                          int32 &OutMissingValue)
{
    // Remove colchetes: "[INT +3]" -> "INT +3"
    FString TagContent = Tag;
    TagContent.RemoveFromStart(TEXT("["));
    TagContent.RemoveFromEnd(TEXT("]"));

    // Parseia: "INT +3" -> "INT", 3
    TArray<FString> Parts;
    TagContent.ParseIntoArray(Parts, TEXT(" "), true);

    if (Parts.Num() < 2)
    {
        return false;
    }

    // Primeira parte é o atributo
    OutAttributeAbbr = Parts[0].ToUpper();

    // Segunda parte deve ser "+N" ou "N"
    FString ValueStr = Parts[1];
    ValueStr.RemoveFromStart(TEXT("+"));
    if (!LexTryParseString(OutMissingValue, *ValueStr))
    {
        return false;
    }

    return true;
}

FString FCharacterSheetDataAssetHelpers::GetFullAttributeName(const FString &AttributeAbbr)
{
    // Mapa de abreviações para nomes completos
    static const TMap<FString, FString> AttributeNameMap = {
        {TEXT("STR"), TEXT("Strength")},     {TEXT("DEX"), TEXT("Dexterity")}, {TEXT("CON"), TEXT("Constitution")},
        {TEXT("INT"), TEXT("Intelligence")}, {TEXT("WIS"), TEXT("Wisdom")},    {TEXT("CHA"), TEXT("Charisma")}};

    const FString *FullName = AttributeNameMap.Find(AttributeAbbr.ToUpper());
    return FullName ? *FullName : FString();
}

bool FCharacterSheetDataAssetHelpers::HasRequirementTag(FName ClassName)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    FString ClassNameStr = ClassName.ToString();
    return ClassNameStr.StartsWith(TEXT("["));
}

bool FCharacterSheetDataAssetHelpers::IsValidClassWithoutTag(FName ClassName)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    return !HasRequirementTag(ClassName);
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

void FCharacterSheetDataAssetHelpers::ApplyClearArray(UCharacterSheetDataAsset *Asset,
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

void FCharacterSheetDataAssetHelpers::ApplyRemoveInvalid(UCharacterSheetDataAsset *Asset,
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

// ============================================================================
// Multiclass Helpers
// ============================================================================
#pragma region Multiclass Helpers

void FCharacterSheetDataAssetHelpers::AdjustProgressionFallback(TArray<FMulticlassProgressEntry> *Progression,
                                                                int32 LevelInClass)
{
    if (!Progression || LevelInClass < DnDConstants::MIN_LEVEL || LevelInClass > DnDConstants::MAX_LEVEL)
    {
        return;
    }

    Progression->SetNum(LevelInClass);
    // Garante que cada elemento tenha o Level correto (1-based)
    for (int32 j = 0; j < Progression->Num(); ++j)
    {
        (*Progression)[j].Level = j + 1;
    }
}

#if WITH_EDITOR
bool FCharacterSheetDataAssetHelpers::DetectNestedMulticlassProperty(const FPropertyChangedEvent &PropertyChangedEvent,
                                                                     FName &HandlerPropertyName)
{
    if (!PropertyChangedEvent.MemberProperty || !PropertyChangedEvent.Property)
    {
        return false;
    }

    const FName MemberPropertyName = PropertyChangedEvent.MemberProperty->GetFName();
    const FName PropertyName = PropertyChangedEvent.Property->GetFName();

    // Propriedades aninhadas em Multiclass array
    // Verifica se MemberProperty é Multiclass OU se Property é LevelInClass/Name/Progression/Proficiencies
    // diretamente
    if (MemberPropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, Multiclass) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Proficiencies))
    {
        // LevelInClass dentro de ClassData dentro de Multiclass
        if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass);
            return true;
        }
        // Name dentro de ClassData dentro de Multiclass
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name);
            return true;
        }
        // Progression dentro de ClassData dentro de Multiclass
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression);
            return true;
        }
        // Proficiencies dentro de ClassData dentro de Multiclass
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Proficiencies))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Proficiencies);
            return true;
        }
        // Detecta mudanças em FSkills.available (dropdown - propriedade aninhada dentro de Proficiencies)
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassSkills, available))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassSkills, available);
            return true;
        }
        // Detecta mudanças em FSkills.Selected (array - propriedade aninhada dentro de Proficiencies)
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassSkills, Selected))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassSkills, Selected);
            return true;
        }
    }

    return false;
}
#endif // WITH_EDITOR

bool FCharacterSheetDataAssetHelpers::DetectLevelInClassCorrections(const FValidationResult &ValidationResult)
{
    for (const FValidationCorrection &Correction : ValidationResult.Corrections)
    {
        if (Correction.CorrectionType == EValidationCorrectionType::AdjustValue &&
            Correction.PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass))
        {
            return true;
        }
    }
    return false;
}

#pragma endregion Multiclass Helpers
