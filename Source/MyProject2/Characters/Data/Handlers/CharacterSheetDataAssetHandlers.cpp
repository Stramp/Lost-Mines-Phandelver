// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetHandlers.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - Validators
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetCorrectionApplier.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidationResult.h"

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/ValidationGuard.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - CreateSheet
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "Data/Structures/FPointBuyValidationResult.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Loaders
#include "Characters/Data/Loaders/CharacterSheetDataAssetLoaders.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/FeatureChoiceHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"
#include "Math/UnrealMathUtility.h"

#pragma endregion Includes

// ============================================================================
// Race Handlers
// ============================================================================
#pragma region Race Handlers

/**
 * Processa mudanças em SelectedRace ou SelectedSubrace.
 * Reseta sub-raça se raça mudou, atualiza flags e recalcula scores.
 */
void FCharacterSheetDataAssetHandlers::HandleRaceChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Resetar sub-raça se raça mudou
    FCharacterSheetDataAssetHelpers::ResetSubraceIfRaceChanged(Asset, PropertyName);

    // Atualiza flag Variant Human e reseta escolhas se necessário
    FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(Asset);

    // Atualiza flag de sub-raças disponíveis
    FCharacterSheetDataAssetUpdaters::UpdateSubraceFlag(Asset);

    // Bônus raciais mudam quando raça/sub-raça muda
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // HP muda quando Constitution muda (via RecalculateFinalScores)
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);

    // Escolhas de idiomas podem mudar quando raça/sub-raça muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);
}

#pragma endregion Race Handlers

// ============================================================================
// Point Buy Handlers
// ============================================================================
#pragma region Point Buy Handlers

/**
 * Processa mudanças em Point Buy allocation (qualquer ability score).
 * Valida Point Buy system e atualiza Final Scores.
 */
void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Motor de Point Buy: aplica alocação nos Final Scores
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // HP muda quando Constitution muda (via RecalculateFinalScores)
    FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(Asset);

    // Valida Point Buy system (calcula PointsRemaining)
    FPointBuyValidationResult ValidationResult = FPointBuyValidator::ValidatePointBuy(
        Asset->PointBuyStrength, Asset->PointBuyDexterity, Asset->PointBuyConstitution, Asset->PointBuyIntelligence,
        Asset->PointBuyWisdom, Asset->PointBuyCharisma);

    // Aplica resultado da validação no Asset (delega para Updater)
    FCharacterSheetDataAssetUpdaters::ApplyPointBuyValidationResult(Asset, ValidationResult.PointsRemaining);

    // Log de aviso se scores estão fora do range válido (não crítico - sistema ajusta automaticamente)
    if (!ValidationResult.bAllScoresValid && !ValidationResult.LogMessage.IsEmpty())
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("HandlePointBuyAllocationChange"));
        FLoggingSystem::LogWarning(Context, ValidationResult.LogMessage, false);
    }
}

#pragma endregion Point Buy Handlers

// ============================================================================
// Background Handlers
// ============================================================================
#pragma region Background Handlers

/**
 * Processa mudanças em SelectedBackground.
 * Atualiza escolhas de idiomas e campos calculados.
 */
void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Escolhas de idiomas podem mudar quando background muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);
}

#pragma endregion Background Handlers

// ============================================================================
// Language Handlers
// ============================================================================
#pragma region Language Handlers

/**
 * Processa mudanças em SelectedLanguages.
 * Valida escolhas de idiomas e atualiza campos calculados.
 */
void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de idiomas e aplica correções
    FValidationResult LanguageResult = FCharacterSheetDataAssetValidators::ValidateLanguageChoices(Asset);
    if (LanguageResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, LanguageResult);
    }

    // Recalcula idiomas finais
}

#pragma endregion Language Handlers

// ============================================================================
// Variant Human Handlers
// ============================================================================
#pragma region Variant Human Handlers

/**
 * Processa mudanças em Variant Human choices (CustomAbilityScoreChoices, SelectedFeat, SelectedSkill).
 * Valida escolhas e recalcula bônus raciais e proficiências.
 */
void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Converte SelectedFeat de Name para FC_ID se necessário
    // Dropdown retorna Name (ex: "Magic Initiate"), mas código espera FC_ID (ex: "Feat_MagicInitiate")
    if (Asset->SelectedFeat != NAME_None && Asset->FeatDataTable)
    {
        FName FeatFC_ID = DataTableHelpers::ConvertFeatNameToFCID(Asset->SelectedFeat, Asset->FeatDataTable);
        if (FeatFC_ID != NAME_None && FeatFC_ID != Asset->SelectedFeat)
        {
            // Converte Name para FC_ID
            Asset->SelectedFeat = FeatFC_ID;
        }
    }

    // Valida escolhas de Variant Human e aplica correções
    FValidationResult VariantHumanResult = FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(Asset);
    if (VariantHumanResult.bNeedsCorrection)
    {
        FCharacterSheetDataAssetCorrectionApplier::ApplyCorrections(Asset, VariantHumanResult);
    }

    // Recalcula bônus raciais (Custom ASI afeta bônus)
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // Recalcula proficiências (SelectedSkill do Variant Human afeta proficiências)
}

#pragma endregion Variant Human Handlers

// ============================================================================
// Data Table Handlers
// ============================================================================
#pragma region Data Table Handlers


/**
 * Processa mudanças em Data Tables (RaceDataTable, BackgroundDataTable, FeatDataTable, ClassDataTable).
 * Valida tipo de Data Table e atualiza visibilidade da ficha.
 *
 * @param Asset Data Asset
 * @param PropertyName Nome da propriedade que mudou (para identificar qual Data Table foi modificada)
 */
void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida tipo de Data Table específica que foi alterada
    // Usa GET_MEMBER_NAME_CHECKED para comparar com PropertyName
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->RaceDataTable, PropertyName,
                                                                TEXT("FRaceDataRow"), DataTableHelpers::IsRaceDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->ClassDataTable, PropertyName,
                                                                TEXT("FClassDataRow"), DataTableHelpers::IsClassDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->BackgroundDataTable, PropertyName,
                                                                TEXT("FBackgroundDataRow"),
                                                                DataTableHelpers::IsBackgroundDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->FeatDataTable, PropertyName,
                                                                TEXT("FFeatDataRow"), DataTableHelpers::IsFeatDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassFeaturesDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->ClassFeaturesDataTable, PropertyName,
                                                                TEXT("FFeatureDataRow"),
                                                                DataTableHelpers::IsFeatureDataTable);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ProficiencyDataTable))
    {
        FCharacterSheetDataAssetHelpers::ValidateDataTableType(Asset, Asset->ProficiencyDataTable, PropertyName,
                                                                TEXT("FProficiencyDataRow"),
                                                                DataTableHelpers::IsProficiencyDataTable);
    }

    // Valida se todas as Data Tables obrigatórias estão cadastradas (exibe popup se faltando)
    // NOTA: Esta validação não verifica tipo, apenas se estão preenchidas (lógica de visibilidade)
    FCharacterSheetDataAssetValidators::ValidateDataTables(Asset);

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
    // NOTA: Esta lógica não deve ser alterada - apenas verifica se != nullptr
    FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(Asset);

    // Log informativo sobre status dos Data Tables
    FCharacterSheetDataAssetHelpers::LogDataTableStatus(Asset);
}

#pragma endregion Data Table Handlers

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
                    Asset->ClassFeaturesDataTable, Feature.FC_ID, Feature.AvailableChoiceToAdd);
                FString ChoiceDisplayString = (ChoiceDisplayName != NAME_None)
                                                 ? ChoiceDisplayName.ToString()
                                                 : Feature.AvailableChoiceToAdd.ToString();

                FString Reason;
                if (!ValidChoices.Contains(Feature.AvailableChoiceToAdd))
                {
                    Reason = FString::Printf(TEXT("Escolha '%s' não é válida para feature '%s'"),
                                             *ChoiceDisplayString, *Feature.Name.ToString());
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
            bool bCleaned = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(
                Feature.SelectedChoices, ValidChoices);

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
                    FString::Printf(TEXT("Limite máximo de %d escolhas para feature '%s' excedido. %d escolhas foram removidas."),
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

// ============================================================================
// Wrapper Functions for Property Handler Map
// ============================================================================
#pragma region Wrapper Functions

/**
 * Wrapper functions usadas como ponteiros de função C-style no map PropertyHandlers.
 * Fornecem assinatura consistente (UCharacterSheetDataAsset*, FName) para todos os handlers.
 * Organizadas na mesma ordem dos handlers principais para facilitar manutenção.
 */

// ============================================================================
// Race Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

// ============================================================================
// Point Buy Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandlePointBuyAllocationChange(Asset);
}

// ============================================================================
// Background Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandleBackgroundChange(Asset);
}

// ============================================================================
// Language Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleLanguageChoicesChange(Asset);
}

// ============================================================================
// Variant Human Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper(UCharacterSheetDataAsset *Asset,
                                                                        FName PropertyName)
{
    HandleVariantHumanChoicesChange(Asset);
}

// ============================================================================
// Data Table Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleDataTableWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleDataTableChange(Asset, PropertyName);
}

// ============================================================================
// Multiclass Wrappers
// ============================================================================

void FCharacterSheetDataAssetHandlers::HandleLevelInClassWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleLevelInClassChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameWrapper(UCharacterSheetDataAsset *Asset,
                                                                        FName PropertyName)
{
    HandleMulticlassClassNameChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleProgressionWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleProgressionChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleProficienciesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleProficienciesChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleAvailableSkillWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleAvailableSkillChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedSkillsWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleSelectedSkillsChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleAvailableChoiceToAddWrapper(UCharacterSheetDataAsset *Asset,
                                                                          FName PropertyName)
{
    HandleAvailableChoiceToAddChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleSelectedChoicesChange(Asset);
}

#pragma endregion Wrapper Functions
