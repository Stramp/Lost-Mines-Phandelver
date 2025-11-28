// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHandlers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/ValidationGuard.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetCorrectionApplier.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Loaders
#include "Characters/Data/Loaders/CharacterSheetDataAssetLoaders.h"

// Project includes - CreateSheet
// MulticlassHelpers foi dividido em 3 arquivos especializados (não usado diretamente aqui)

// Project includes - Utils
#include "Utils/FeatureChoiceHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Handlers
// ============================================================================
#pragma region Multiclass Handlers

/**
 * Processa mudanças em LevelInClass dentro do array Multiclass.
 * Ajusta o array Progression e processa features ganhas no nível correspondente.
 */
void FCharacterSheetDataAssetHandlers::HandleLevelInClassChange(UCharacterSheetDataAsset *Asset, bool bSkipGuard)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    // Se bSkipGuard é true, não cria Guard (útil quando chamado de outro handler que já tem Guard)
    FValidationGuard *GuardPtr = nullptr;
    FValidationGuard Guard(bSkipGuard ? nullptr : Asset);
    if (!bSkipGuard)
    {
        GuardPtr = &Guard;
    }

    // Protocolo de validação: valida todas as entradas antes de processar
    FValidationResult NameLevelResult =
        FCharacterSheetDataAssetValidators::ValidateMulticlassNameLevelConsistency(Asset);
    FValidationResult ProgressionResult = FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(Asset);

    // Aplica correções se necessário
    if (NameLevelResult.bNeedsCorrection || ProgressionResult.bNeedsCorrection)
    {
        FValidationResult CombinedResult;
        CombinedResult.Corrections.Append(NameLevelResult.Corrections);
        CombinedResult.Corrections.Append(ProgressionResult.Corrections);
        CombinedResult.bNeedsCorrection = true;
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, CombinedResult);
    }

    // Ajusta nível mínimo para classes válidas (delega para Updater)
    FCharacterSheetDataAssetUpdaters::AdjustMinimumLevelForValidClasses(Asset);

    // Atualiza flags para todas as entradas (apenas atualiza flags)
    FCharacterSheetDataAssetUpdaters::UpdateMulticlassFlags(Asset);

    // Processa mudanças de nível para todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        // Carrega progressão usando Loader (responsabilidade única: carregar)
        // O Loader já limpa o array se não pode processar Progression
        bool bLoaded = FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, i);
        if (!bLoaded)
        {
            // Se falhou ao carregar, ajusta array manualmente (fallback)
            FMulticlassEntry &Entry = Asset->Multiclass[i];
            FCharacterSheetDataAssetHelpers::AdjustProgressionFallback(&Entry.ClassData.Progression,
                                                                       Entry.ClassData.LevelInClass);
        }

        // Loga features ganhas no nível usando Loader (apenas log informativo)
        FCharacterSheetDataAssetLoaders::LogLevelChangeFeatures(Asset, i);
    }

    // Recalcula HP máximo quando níveis de classe mudam
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);
}

/**
 * Processa mudanças em ClassData.Name dentro do array Multiclass.
 * Reseta o campo para NAME_None se a classe selecionada tiver tag de requerimento (começa com "[").
 * Ajusta LevelInClass automaticamente: 1 se há classe, 0 se não há.
 */
void FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida classes com tags de requerimento e aplica correções (delega para Validator + CorrectionApplier)
    FValidationResult RequirementTagsResult =
        FCharacterSheetDataAssetValidators::ValidateMulticlassRequirementTags(Asset);
    if (RequirementTagsResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, RequirementTagsResult);
    }

    // Ajusta LevelInClass baseado na presença de ClassName (delega para Updater)
    FCharacterSheetDataAssetUpdaters::AdjustLevelInClassForClassName(Asset);

    // Atualiza flags para todas as entradas (apenas atualiza flags)
    FCharacterSheetDataAssetUpdaters::UpdateMulticlassFlags(Asset);

    // Carrega dados para todas as entradas usando Loaders (responsabilidade única: carregar)
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        // Carrega informações básicas da classe (MulticlassRequirements)
        FCharacterSheetDataAssetLoaders::LoadClassBasicInfo(Asset, i);

        // Carrega proficiências quando classe é escolhida e LevelInClass == 1
        FCharacterSheetDataAssetLoaders::LoadClassProficiencies(Asset, i);

        // Carrega progressão quando classe é escolhida (delega para Loader)
        FCharacterSheetDataAssetLoaders::LoadClassProgression(Asset, i);
    }

    // Valida consistência Name/LevelInClass e aplica correções
    FValidationResult NameLevelResult =
        FCharacterSheetDataAssetValidators::ValidateMulticlassNameLevelConsistency(Asset);
    FValidationResult ProgressionResult = FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(Asset);

    // Aplica correções se necessário
    if (NameLevelResult.bNeedsCorrection || ProgressionResult.bNeedsCorrection)
    {
        FValidationResult CombinedResult;
        CombinedResult.Corrections.Append(NameLevelResult.Corrections);
        CombinedResult.Corrections.Append(ProgressionResult.Corrections);
        CombinedResult.bNeedsCorrection = true;
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, CombinedResult);
    }

    // Chama HandleLevelInClassChange para processar mudanças de nível (ajustar Progression, etc.)
    // Passa bSkipGuard=true porque já estamos dentro de um Guard
    HandleLevelInClassChange(Asset, true);

    // Recalcula HP máximo quando classe é adicionada/removida
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);
}

/**
 * Processa mudanças em ClassData.Progression dentro do array Multiclass.
 * Delega validação para Validators (protocolo de validação).
 */
void FCharacterSheetDataAssetHandlers::HandleProgressionChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Protocolo de validação: valida e aplica correções
    FValidationResult ProgressionResult = FCharacterSheetDataAssetValidators::ValidateMulticlassProgression(Asset);
    if (ProgressionResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, ProgressionResult);
    }
    Asset->Modify(); // Marca objeto como modificado após validação
}

/**
 * Processa mudanças em ClassData.Proficiencies dentro do array Multiclass.
 * Delega atualização de qtdAvailable para Updater.
 */
void FCharacterSheetDataAssetHandlers::HandleProficienciesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Atualiza qtdAvailable dinamicamente (delega para Updater - responsabilidade única: atualizar)
    FCharacterSheetDataAssetUpdaters::UpdateMulticlassProficiencyChoices(Asset);

    // Valida escolhas de proficiências e aplica correções se necessário
    FValidationResult ProficienciesResult = FCharacterSheetDataAssetValidators::ValidateMulticlassProficiencies(Asset);
    if (ProficienciesResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, ProficienciesResult);
    }

    Asset->Modify(); // Marca objeto como modificado após atualização e validação
}

/**
 * Processa mudanças em FSkills.available (dropdown) dentro do array Multiclass.
 * Quando uma skill é selecionada no dropdown, adiciona ao Selected e reseta available.
 */
void FCharacterSheetDataAssetHandlers::HandleAvailableSkillChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    bool bAnyChange = false;

    // Itera por todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];

        for (FMulticlassProficienciesEntry &ProficiencyEntry : Entry.ClassData.Proficiencies)
        {
            FMulticlassSkills &Skills = ProficiencyEntry.FSkills;

            // Se available foi selecionado (não é NAME_None)
            if (Skills.available != NAME_None)
            {
                // Verifica se a skill está na lista InitialAvailable (validação)
                if (Skills.InitialAvailable.Contains(Skills.available))
                {
                    // Verifica se a skill já não foi escolhida (evita duplicatas)
                    if (!Skills.Selected.Contains(Skills.available))
                    {
                        // Adiciona ao Selected
                        Skills.Selected.Add(Skills.available);
                        bAnyChange = true;
                    }
                }

                // Sempre reseta available para permitir nova seleção (independente de validação)
                Skills.available = NAME_None;
            }
        }
    }

    // Atualiza qtdAvailable apenas se houve mudança (delega para Updater - responsabilidade única)
    if (bAnyChange)
    {
        FCharacterSheetDataAssetUpdaters::UpdateMulticlassProficiencyChoices(Asset);
    }

    Asset->Modify(); // Marca objeto como modificado
}

/**
 * Processa mudanças em FSkills.Selected (array) dentro do array Multiclass.
 * Recalcula qtdAvailable quando skills são adicionadas/removidas do Selected.
 */
void FCharacterSheetDataAssetHandlers::HandleSelectedSkillsChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Atualiza qtdAvailable dinamicamente (delega para Updater - responsabilidade única: atualizar)
    FCharacterSheetDataAssetUpdaters::UpdateMulticlassProficiencyChoices(Asset);

    // Valida escolhas de proficiências e aplica correções se necessário
    FValidationResult ProficienciesResult = FCharacterSheetDataAssetValidators::ValidateMulticlassProficiencies(Asset);
    if (ProficienciesResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, ProficienciesResult);
    }

    Asset->Modify(); // Marca objeto como modificado após atualização e validação
}

/**
 * Processa mudanças em FMulticlassClassFeature.AvailableChoiceToAdd (dropdown) dentro do array Multiclass.
 * Quando uma escolha é selecionada no dropdown, adiciona ao SelectedChoices e reseta AvailableChoiceToAdd.
 * Usado para features do Tipo 3 (Escolhas Múltiplas) como Manobras e Metamagic.
 *
 * Fluxo:
 * 1. Itera por todas as features de múltiplas escolhas usando helper reutilizável
 * 2. Valida escolha (válida, não duplicata, não excede limite)
 * 3. Adiciona ao SelectedChoices se válida
 * 4. Exibe feedback ao usuário se inválida
 * 5. Reseta AvailableChoiceToAdd para permitir nova seleção
 */
void FCharacterSheetDataAssetHandlers::HandleAvailableChoiceToAddChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    bool bAnyChange = false;
    FLogContext Context(TEXT("CharacterSheet"), TEXT("HandleAvailableChoiceToAddChange"));

    // Usa helper reutilizável para iterar por todas as features de múltiplas escolhas
    FCharacterSheetDataAssetHelpers::ForEachMultipleChoiceFeature(
        Asset,
        [Asset, &bAnyChange, &Context](FMulticlassClassFeature &Feature, const TArray<FName> &ValidChoices)
        {
            // Processa apenas se AvailableChoiceToAdd foi selecionado (não é NAME_None)
            if (Feature.AvailableChoiceToAdd == NAME_None)
            {
                return;
            }

            // Obtém limite máximo de escolhas (se houver)
            int32 MaxChoices = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);

            // Valida se pode adicionar escolha
            if (FCharacterSheetDataAssetHelpers::CanAddChoice(Feature.AvailableChoiceToAdd, ValidChoices,
                                                              Feature.SelectedChoices, MaxChoices))
            {
                // Adiciona ao SelectedChoices
                Feature.SelectedChoices.Add(Feature.AvailableChoiceToAdd);
                bAnyChange = true;
            }
            else
            {
                // Feedback ao usuário sobre por que escolha não foi adicionada
                // Converte ID para Name para melhor UX (usuário vê "Archery" ao invés de "FC_Archery")
                FName ChoiceDisplayName = FeatureChoiceHelpers::FindChoiceNameByID(
                    Asset->ClassFeaturesDataTable, Feature.ID, Feature.AvailableChoiceToAdd);
                FString ChoiceDisplayString = (ChoiceDisplayName != NAME_None)
                                                  ? ChoiceDisplayName.ToString()
                                                  : Feature.AvailableChoiceToAdd.ToString();

                FString Reason;
                if (!ValidChoices.Contains(Feature.AvailableChoiceToAdd))
                {
                    Reason = FString::Printf(TEXT("Escolha '%s' não é válida para feature '%s'"), *ChoiceDisplayString,
                                             *Feature.Name.ToString());
                }
                else if (Feature.SelectedChoices.Contains(Feature.AvailableChoiceToAdd))
                {
                    Reason = FString::Printf(TEXT("Escolha '%s' já foi selecionada para feature '%s'"),
                                             *ChoiceDisplayString, *Feature.Name.ToString());
                }
                else if (MaxChoices > 0 && Feature.SelectedChoices.Num() >= MaxChoices)
                {
                    Reason = FString::Printf(TEXT("Limite máximo de %d escolhas atingido para feature '%s'"),
                                             MaxChoices, *Feature.Name.ToString());
                }

                if (!Reason.IsEmpty())
                {
                    FLoggingSystem::LogWarningWithThrottledPopup(Context, Reason, 0.5f);
                }
            }

            // Sempre reseta AvailableChoiceToAdd para permitir nova seleção (independente de validação)
            Feature.AvailableChoiceToAdd = NAME_None;
        });

    // Marca objeto como modificado apenas se houve mudança
    if (bAnyChange)
    {
        Asset->Modify();
    }

    // Atualiza display names para exibição no editor
    FCharacterSheetDataAssetUpdaters::UpdateFeatureChoiceDisplayNames(Asset);
}

/**
 * Processa mudanças em FMulticlassClassFeature.SelectedChoices (array) dentro do array Multiclass.
 * Valida escolhas quando são adicionadas/removidas do SelectedChoices.
 * Usado para features do Tipo 3 (Escolhas Múltiplas) como Manobras e Metamagic.
 *
 * Fluxo:
 * 1. Itera por todas as features de múltiplas escolhas usando helper reutilizável
 * 2. Remove escolhas inválidas e duplicatas usando helper otimizado
 * 3. Valida limite máximo (se houver) e remove escolhas excedentes
 * 4. Exibe feedback ao usuário se escolhas foram removidas
 */
void FCharacterSheetDataAssetHandlers::HandleSelectedChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    bool bAnyChange = false;
    FLogContext Context(TEXT("CharacterSheet"), TEXT("HandleSelectedChoicesChange"));

    // Usa helper reutilizável para iterar por todas as features de múltiplas escolhas
    FCharacterSheetDataAssetHelpers::ForEachMultipleChoiceFeature(
        Asset,
        [&bAnyChange, &Context](FMulticlassClassFeature &Feature, const TArray<FName> &ValidChoices)
        {
            // Remove escolhas inválidas e duplicatas usando helper otimizado
            bool bCleaned =
                FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(Feature.SelectedChoices, ValidChoices);

            if (bCleaned)
            {
                bAnyChange = true;
                FLoggingSystem::LogWarningWithThrottledPopup(
                    Context,
                    FString::Printf(TEXT("Escolhas inválidas ou duplicatas foram removidas de feature '%s'"),
                                    *Feature.Name.ToString()),
                    0.5f);
            }

            // Valida limite máximo de escolhas (se houver)
            int32 MaxChoices = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);
            if (MaxChoices > 0 && Feature.SelectedChoices.Num() > MaxChoices)
            {
                // Remove escolhas excedentes (mantém as primeiras)
                int32 ExcessCount = Feature.SelectedChoices.Num() - MaxChoices;
                Feature.SelectedChoices.SetNum(MaxChoices);
                bAnyChange = true;

                FLoggingSystem::LogWarningWithThrottledPopup(
                    Context,
                    FString::Printf(
                        TEXT("Limite máximo de %d escolhas para feature '%s' excedido. %d escolhas foram removidas."),
                        MaxChoices, *Feature.Name.ToString(), ExcessCount),
                    0.5f);
            }
        });

    // Marca objeto como modificado apenas se houve mudança
    if (bAnyChange)
    {
        Asset->Modify();
    }

    // Atualiza display names para exibição no editor
    FCharacterSheetDataAssetUpdaters::UpdateFeatureChoiceDisplayNames(Asset);
}

#pragma endregion Multiclass Handlers
