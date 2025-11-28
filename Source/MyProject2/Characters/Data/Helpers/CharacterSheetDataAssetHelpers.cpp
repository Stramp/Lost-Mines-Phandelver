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
#include "Utils/DataTableHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UnrealType.h"
#include "UObject/PropertyAccessUtil.h"

#if WITH_EDITOR
#include "PropertyEditorModule.h"
#include "Editor.h"
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
 * Atualiza campos Point Buy a partir de uma alocação final.
 * Usado quando o sistema Point Buy ajusta automaticamente valores inválidos.
 */
void FCharacterSheetDataAssetHelpers::UpdatePointBuyFromFinalAllocation(UCharacterSheetDataAsset *Asset,
                                                                        const TMap<FName, int32> &FinalAllocation)
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
        if (const int32 *FinalValue = FinalAllocation.Find(AbilityNames[Index]))
        {
            *PointBuyFields[Index] = *FinalValue;
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
    // Todas as 6 tabelas são obrigatórias: RaceDataTable, BackgroundDataTable, ClassDataTable,
    // FeatDataTable, ClassFeaturesDataTable, ProficiencyDataTable
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr &&
                                  Asset->ClassDataTable != nullptr && Asset->FeatDataTable != nullptr &&
                                  Asset->ClassFeaturesDataTable != nullptr && Asset->ProficiencyDataTable != nullptr;

    FLogContext Context(TEXT("CharacterSheet"), TEXT("LogDataTableStatus"));
    if (bAllDataTablesSelected)
    {
        FLoggingSystem::LogInfo(Context,
                                TEXT("Todos os Data Tables foram selecionados! Todas as categorias estão visíveis."));
    }
    else
    {
        // Aviso informativo - não requer ação imediata (sem popup)
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("Ainda faltam Data Tables. Race: %s, Background: %s, Class: %s, "
                                 "Feat: %s, ClassFeatures: %s, Proficiency: %s"),
                            Asset->RaceDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                            Asset->BackgroundDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                            Asset->ClassDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                            Asset->FeatDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                            Asset->ClassFeaturesDataTable ? TEXT("OK") : TEXT("FALTANDO"),
                            Asset->ProficiencyDataTable ? TEXT("OK") : TEXT("FALTANDO")),
            false);
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
        // Detecta mudanças em FMulticlassClassFeature.AvailableChoiceToAdd (dropdown - propriedade aninhada dentro de
        // Features)
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassFeature, AvailableChoiceToAdd))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassFeature, AvailableChoiceToAdd);
            return true;
        }
        // Detecta mudanças em FMulticlassClassFeature.SelectedChoices (array - propriedade aninhada dentro de Features)
        else if (PropertyName == GET_MEMBER_NAME_CHECKED(FMulticlassClassFeature, SelectedChoices))
        {
            HandlerPropertyName = GET_MEMBER_NAME_CHECKED(FMulticlassClassFeature, SelectedChoices);
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

// ============================================================================
// Data Table Type Validation Helpers
// ============================================================================
#pragma region Data Table Type Validation Helpers

bool FCharacterSheetDataAssetHelpers::ValidateDataTableType(UCharacterSheetDataAsset *Asset, UDataTable *DataTable,
                                                            const FName &PropertyName, const FString &ExpectedTypeName,
                                                            bool (*ValidationFunction)(UDataTable *))
{
    if (!DataTable)
    {
        // nullptr é válido (tabela não foi atribuída ainda)
        return true;
    }

    if (!ValidationFunction(DataTable))
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateDataTableType"));
        FString ErrorMessage =
            FString::Printf(TEXT("Data Table '%s' tem tipo incorreto. Esperado: %s. A tabela foi resetada para None."),
                            *PropertyName.ToString(), *ExpectedTypeName);
        FLoggingSystem::LogErrorWithThrottledPopup(Context, ErrorMessage, 0.5f);

        // Reset tabela para nullptr se tipo incorreto (validação restritiva)
        if (Asset)
        {
            Asset->Modify();
            // Usa reflexão para resetar a propriedade para nullptr
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), PropertyName))
            {
                if (FObjectProperty *ObjectProperty = CastField<FObjectProperty>(Property))
                {
                    void *PropertyValue = Property->ContainerPtrToValuePtr<void>(Asset);
                    ObjectProperty->SetObjectPropertyValue(PropertyValue, nullptr);

                    // Notifica editor sobre mudança
                    FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                    Asset->PostEditChangeProperty(PropertyChangedEvent);
                }
            }
        }

        return false;
    }

    return true;
}

#pragma endregion Data Table Type Validation Helpers

// ============================================================================
// Multiple Choice Feature Helpers
// ============================================================================
#pragma region Multiple Choice Feature Helpers

void FCharacterSheetDataAssetHelpers::ForEachMultipleChoiceFeature(
    UCharacterSheetDataAsset *Asset,
    TFunctionRef<void(FMulticlassClassFeature &Feature, const TArray<FName> &ValidChoices)> Callback)
{
    if (!Asset)
    {
        return;
    }

    // Itera por todas as entradas de multiclasse
    for (FMulticlassEntry &Entry : Asset->Multiclass)
    {
        // Itera por todas as features em todas as progressões
        for (FMulticlassProgressEntry &ProgressEntry : Entry.ClassData.Progression)
        {
            for (FMulticlassClassFeature &Feature : ProgressEntry.Features)
            {
                // Processa apenas features do Tipo 3 (Escolhas Múltiplas)
                if (!Feature.bHasAvailableChoices || !Feature.bIsMultipleChoice)
                {
                    continue;
                }

                // Obtém lista de IDs de escolhas válidas para esta feature (filtradas por FC_ID)
                TArray<FName> ValidChoices = Asset->GetAvailableChoiceIDsForFeature(Feature.ID);

                // Executa callback
                Callback(Feature, ValidChoices);
            }
        }
    }
}

int32 FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(const FMulticlassClassFeature &Feature)
{
    // Busca MaxChoices em FeatureData
    if (Feature.FeatureData.Contains(TEXT("MaxChoices")))
    {
        const FString &MaxChoicesStr = Feature.FeatureData[TEXT("MaxChoices")];
        int32 MaxChoices = FCString::Atoi(*MaxChoicesStr);
        return MaxChoices > 0 ? MaxChoices : -1; // Retorna -1 se valor inválido
    }

    // Sem limite definido
    return -1;
}

bool FCharacterSheetDataAssetHelpers::CanAddChoice(FName Choice, const TArray<FName> &ValidChoices,
                                                   const TArray<FName> &SelectedChoices, int32 MaxChoices)
{
    // Verifica se escolha está na lista válida
    if (!ValidChoices.Contains(Choice))
    {
        return false;
    }

    // Verifica se escolha já não foi escolhida (evita duplicatas)
    if (SelectedChoices.Contains(Choice))
    {
        return false;
    }

    // Verifica se não excede limite (se houver)
    if (MaxChoices > 0 && SelectedChoices.Num() >= MaxChoices)
    {
        return false;
    }

    return true;
}

bool FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(TArray<FName> &SelectedChoices,
                                                                      const TArray<FName> &ValidChoices)
{
    bool bAnyChange = false;

    // Remove escolhas inválidas e duplicatas em um único loop otimizado
    TSet<FName> UniqueChoices;
    TArray<FName> CleanedChoices;
    CleanedChoices.Reserve(SelectedChoices.Num());

    for (const FName &Choice : SelectedChoices)
    {
        // Verifica se é válida e não é duplicata
        if (ValidChoices.Contains(Choice) && !UniqueChoices.Contains(Choice))
        {
            UniqueChoices.Add(Choice);
            CleanedChoices.Add(Choice);
        }
        else
        {
            bAnyChange = true; // Houve remoção
        }
    }

    // Atualiza array apenas se houve mudanças
    if (bAnyChange)
    {
        SelectedChoices = CleanedChoices;
    }

    return bAnyChange;
}

#pragma endregion Multiple Choice Feature Helpers
