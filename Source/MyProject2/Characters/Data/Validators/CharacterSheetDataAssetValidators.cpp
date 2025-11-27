// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/ValidationHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

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

// ============================================================================
// Variant Human Validation
// ============================================================================
#pragma region Variant Human Validation

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset || !Asset->GetIsVariantHuman())
    {
        return Result;
    }

    // Valida todas as áreas de Variant Human
    FValidationResult AbilityScoreResult = ValidateVariantHumanAbilityScoreChoices(Asset);
    FValidationResult FeatResult = ValidateVariantHumanFeat(Asset);
    FValidationResult SkillResult = ValidateVariantHumanSkill(Asset);

    // Agrega correções
    Result.Corrections.Append(AbilityScoreResult.Corrections);
    Result.Corrections.Append(FeatResult.Corrections);
    Result.Corrections.Append(SkillResult.Corrections);

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;

    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Valida usando função pura (apenas valida, não aplica)
    TArray<FName> ValidAbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    TArray<int32> InvalidIndices;
    bool bHasDuplicates = false;
    bool bExceedsMax = false;
    bool bIsValid = ValidationHelpers::ValidateAbilityScoreChoicesPure(
        Asset->CustomAbilityScoreChoices, ValidAbilityNames, 2, InvalidIndices, bHasDuplicates, bExceedsMax);

    if (!bIsValid)
    {
        // Adiciona correção para remover elementos inválidos
        if (InvalidIndices.Num() > 0)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::RemoveInvalid,
                GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices), InvalidIndices,
                TEXT("CharacterSheetDataAsset: CustomAbilityScoreChoices contém elementos "
                     "inválidos. Removendo."));
            Result.AddCorrection(Correction);
        }

        // Adiciona correção para limpar array se excede máximo
        if (bExceedsMax)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::ClearArray,
                GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices), -1, 2,
                TEXT("CharacterSheetDataAsset: CustomAbilityScoreChoices excede máximo (2). "
                     "Ajustando."));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanFeat(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    if (Asset->FeatDataTable)
    {
        TArray<FName> AvailableFeats = Asset->GetAvailableFeatNames();
        bool bIsValid = ValidationHelpers::ValidateFeatSelectionPure(Asset->SelectedFeat, AvailableFeats);

        if (!bIsValid)
        {
            // Adiciona correção para resetar feat
            FValidationCorrection Correction(EValidationCorrectionType::ResetToNone,
                                             GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat), -1, 0,
                                             TEXT("CharacterSheetDataAsset: SelectedFeat não está disponível. "
                                                  "Resetando."));
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult FCharacterSheetDataAssetValidators::ValidateVariantHumanSkill(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Usa ProficiencyDataTable do Asset se disponível (Data-Driven), caso contrário usa fallback hardcoded
    TArray<FName> ValidSkills = Asset->GetSkillNames();
    bool bIsValid = ValidationHelpers::ValidateSkillSelectionPure(Asset->SelectedSkill, ValidSkills);

    if (!bIsValid)
    {
        // Adiciona correção para resetar skill
        FValidationCorrection Correction(EValidationCorrectionType::ResetToNone,
                                         GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill), -1, 0,
                                         TEXT("CharacterSheetDataAsset: SelectedSkill não é válido. Resetando."));
        Result.AddCorrection(Correction);
    }

    return Result;
}

#pragma endregion Variant Human Validation

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
    TArray<FName> ValidLanguages = CharacterSheetHelpers::GetAvailableLanguageNames(Asset->ProficiencyDataTable);
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

// ============================================================================
// Multiclass Validation
// ============================================================================
#pragma region Multiclass Validation

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassNameLevelConsistency(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Regra: Se não há classe, nível deve ser 0
        // Se ambos são None/0, isso é estado correto, não corrigir
        if (ClassName == NAME_None && LevelInClass != 0)
        {
            FValidationCorrection Correction(
                EValidationCorrectionType::AdjustValue, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass), i,
                0,
                FString::Printf(TEXT("Multiclass[%d] - Inconsistência: Name é NAME_None, LevelInClass deve ser 0"), i));
            Result.AddCorrection(Correction);
        }

        // Regra: Se há classe válida (sem tag), nível mínimo é 1
        // Nota: A correção é aplicada silenciosamente via AdjustLevelInClassForClassName no Handler
        if (FCharacterSheetDataAssetHelpers::IsValidClassWithoutTag(ClassName) && LevelInClass == 0)
        {
            FValidationCorrection Correction(EValidationCorrectionType::AdjustValue,
                                             GET_MEMBER_NAME_CHECKED(FMulticlassClassData, LevelInClass), i, 1,
                                             FString()); // Sem mensagem de log - correção silenciosa
            Result.AddCorrection(Correction);
        }
    }

    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Nota: Esta função é const, então não pode atualizar bCanEditProgression diretamente.
    // A flag será atualizada pelos Handlers ou CorrectionApplier após aplicar correções.
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Se Name == NAME_None E LevelInClass == 0, isso é estado correto
        // Apenas limpa Progression sem gerar correção/alerta
        if (ClassName == NAME_None && LevelInClass == 0)
        {
            // Estado correto: apenas limpa Progression se necessário (sem alerta)
            // A limpeza será feita pelo Loader ou Handler
            continue;
        }

        // Valida se pode processar Progression (usa helper puro)
        if (!FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass))
        {
            // Se não pode processar e há itens, precisa limpar
            if (Entry.ClassData.Progression.Num() > 0)
            {
                FValidationCorrection Correction(
                    EValidationCorrectionType::ClearArray, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression),
                    i, 0,
                    FString::Printf(TEXT("Multiclass[%d] - Progression deve estar vazio: Name é NAME_None ou "
                                         "LevelInClass é 0"),
                                    i));
                Result.AddCorrection(Correction);
            }
        }
    }

    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassProficiencies(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateMulticlassProficiencies"));

    // Valida todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];

        for (const FMulticlassProficienciesEntry &ProficiencyEntry : Entry.ClassData.Proficiencies)
        {
            const FMulticlassSkills &Skills = ProficiencyEntry.FSkills;

            // Se não há estado inicial armazenado, pula validação (ainda não foi carregado)
            if (Skills.InitialAvailable.Num() == 0 && Skills.InitialQtdAvailable == 0)
            {
                continue;
            }

            // Calcula quantas skills foram escolhidas (tamanho do array Selected)
            const int32 SkillsChosen = Skills.Selected.Num();

            // Validação: não pode ter mais skills escolhidas do que o permitido
            if (SkillsChosen > Skills.InitialQtdAvailable)
            {
                // Gera correção para ajustar qtdAvailable (aplicada pelo CorrectionApplier no Handler)
                FValidationCorrection Correction(
                    EValidationCorrectionType::AdjustValue, GET_MEMBER_NAME_CHECKED(FMulticlassSkills, qtdAvailable), i,
                    Skills.InitialQtdAvailable,
                    FString::Printf(TEXT("Multiclass[%d] - Mais skills escolhidas (%d) do que o permitido (%d). "
                                         "Ajustando qtdAvailable para %d."),
                                    i, SkillsChosen, Skills.InitialQtdAvailable, Skills.InitialQtdAvailable));
                Result.AddCorrection(Correction);

                // Log de aviso (não crítico - sistema ajusta automaticamente)
                FLoggingSystem::LogWarning(
                    Context,
                    FString::Printf(TEXT("Multiclass[%d] - Mais skills escolhidas (%d) do que o permitido (%d)."), i,
                                    SkillsChosen, Skills.InitialQtdAvailable),
                    false);
            }
        }
    }

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;
    return Result;
}

FValidationResult
FCharacterSheetDataAssetValidators::ValidateMulticlassRequirementTags(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    // Cria array de atributos finais na ordem [STR, DEX, CON, INT, WIS, CHA]
    TArray<int32> FinalAttributes = FCharacterSheetDataAssetHelpers::CreateAttributesArray(
        Asset->FinalStrength, Asset->FinalDexterity, Asset->FinalConstitution, Asset->FinalIntelligence,
        Asset->FinalWisdom, Asset->FinalCharisma);

    FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateMulticlassRequirementTags"));

    // Valida todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        const FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;

        // Se não tem tag de requerimento, pula
        if (!FCharacterSheetDataAssetHelpers::HasRequirementTag(ClassName))
        {
            continue;
        }

        // Extrai tag do nome
        FString ClassNameStr = ClassName.ToString();
        FString Tag;
        if (!FCharacterSheetDataAssetHelpers::ExtractRequirementTag(ClassNameStr, Tag))
        {
            // Se não conseguiu extrair tag, reseta
            FValidationCorrection Correction(
                EValidationCorrectionType::ResetToNone, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name), i, 0,
                FString::Printf(TEXT("Multiclass[%d] - Classe com tag de requerimento inválida. Resetando."), i));
            Result.AddCorrection(Correction);
            continue;
        }

        // Parseia tag para obter atributo e valor faltante
        FString AttributeAbbr;
        int32 MissingValue = 0;
        if (!FCharacterSheetDataAssetHelpers::ParseRequirementTag(Tag, AttributeAbbr, MissingValue))
        {
            // Se não conseguiu parsear, reseta
            FValidationCorrection Correction(
                EValidationCorrectionType::ResetToNone, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name), i, 0,
                FString::Printf(TEXT("Multiclass[%d] - Classe com tag de requerimento inválida. Resetando."), i));
            Result.AddCorrection(Correction);
            continue;
        }

        // Obtém nome completo do atributo
        FString FullAttributeName = FCharacterSheetDataAssetHelpers::GetFullAttributeName(AttributeAbbr);
        if (FullAttributeName.IsEmpty())
        {
            FullAttributeName = AttributeAbbr; // Fallback para abreviação se não encontrou
        }

        // Obtém valor atual do atributo
        TMap<FString, FMulticlassValidators::FAttributeInfo> AttributeMap = FMulticlassValidators::CreateAttributeMap();
        const FMulticlassValidators::FAttributeInfo *AttrInfo = AttributeMap.Find(AttributeAbbr);

        int32 RequiredValue = 0;
        if (AttrInfo && FinalAttributes.IsValidIndex(AttrInfo->Index))
        {
            int32 CurrentValue = FinalAttributes[AttrInfo->Index];
            // Calcula valor requerido: valor atual + valor faltante
            RequiredValue = CurrentValue + MissingValue;
        }
        else
        {
            // Fallback: usa apenas o valor faltante
            RequiredValue = MissingValue;
        }

        // Valida se personagem atende requisito
        bool bMeetsRequirement = false;
        if (AttrInfo && FinalAttributes.IsValidIndex(AttrInfo->Index))
        {
            int32 CurrentValue = FinalAttributes[AttrInfo->Index];
            bMeetsRequirement = CurrentValue >= RequiredValue;
        }

        // Se não atende requisito, reseta classe
        if (!bMeetsRequirement)
        {
            // Formata mensagem: "Você precisa ter mais de XX em [Nome do Atributo]"
            FString Message =
                FString::Printf(TEXT("Você precisa ter mais de %d em %s"), RequiredValue, *FullAttributeName);

            FValidationCorrection Correction(
                EValidationCorrectionType::ResetToNone, GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name), i, 0,
                FString::Printf(TEXT("Multiclass[%d] - Classe com tag de requerimento resetada: %s"), i, *Message));
            Result.AddCorrection(Correction);

            // Alerta popup crítico: jogador escolheu classe que não pode
            // Usa throttle para evitar múltiplos popups quando há vários erros em loop
            FLoggingSystem::LogWarningWithThrottledPopup(Context, Message, 0.5f);
        }
    }

    Result.bNeedsCorrection = Result.Corrections.Num() > 0;
    return Result;
}

#pragma endregion Multiclass Validation

// ============================================================================
// Data Tables Validation
// ============================================================================
#pragma region Data Tables Validation

FValidationResult FCharacterSheetDataAssetValidators::ValidateDataTables(const UCharacterSheetDataAsset *Asset)
{
    FValidationResult Result;

    if (!Asset)
    {
        return Result;
    }

    FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateDataTables"));

    // Tabelas obrigatórias (sempre necessárias)
    TArray<FString> MissingTables;

    if (!Asset->RaceDataTable)
    {
        MissingTables.Add(TEXT("RaceDataTable"));
    }

    if (!Asset->BackgroundDataTable)
    {
        MissingTables.Add(TEXT("BackgroundDataTable"));
    }

    if (!Asset->ClassDataTable)
    {
        MissingTables.Add(TEXT("ClassDataTable"));
    }

    // FeatDataTable é obrigatória apenas se personagem é Variant Human
    if (Asset->GetIsVariantHuman() && !Asset->FeatDataTable)
    {
        MissingTables.Add(TEXT("FeatDataTable (obrigatória para Variant Human)"));
    }

    // ClassFeaturesDataTable e ClassProficienciesDataTable são obrigatórias
    if (!Asset->ClassFeaturesDataTable)
    {
        MissingTables.Add(TEXT("ClassFeaturesDataTable"));
    }

    if (!Asset->ClassProficienciesDataTable)
    {
        MissingTables.Add(TEXT("ClassProficienciesDataTable"));
    }

    // Nota: A verificação de visibilidade (UpdateSheetVisibility) já fornece feedback visual forte
    // quando tabelas estão faltando (esconde todas as props). Não é necessário popup adicional.
    // Esta validação não retorna correções (não há como corrigir automaticamente)
    return Result;
}

#pragma endregion Data Tables Validation
