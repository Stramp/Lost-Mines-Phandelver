// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetValidators.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

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
        if (!FMulticlassValidationHelpers::CanProcessProgression(ClassName, LevelInClass))
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
        TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> AttributeMap = FMulticlassValidationHelpers::CreateAttributeMap();
        const FMulticlassValidationHelpers::FAttributeInfo *AttrInfo = AttributeMap.Find(AttributeAbbr);

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

