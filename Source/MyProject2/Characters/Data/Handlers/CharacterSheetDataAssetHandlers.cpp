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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(PropertyName);

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

    // Proficiências de raça mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(
        GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyStrength));

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

    // Features podem depender de ability scores
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(
        GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground));

    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Escolhas de idiomas podem mudar quando background muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);

    // Proficiências de background mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(
        GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages));

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
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(
        GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices));

    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

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
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

#pragma endregion Variant Human Handlers

// ============================================================================
// Data Table Handlers
// ============================================================================
#pragma region Data Table Handlers

/**
 * Processa mudanças em Data Tables (RaceDataTable, BackgroundDataTable, FeatDataTable, ClassDataTable).
 * Atualiza visibilidade da ficha e loga status dos Data Tables.
 */
void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset)
{
    FCharacterSheetDataAssetHelpers::LogPropertyChange(
        GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable));

    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida se todas as Data Tables obrigatórias estão cadastradas (exibe popup se faltando)
    FCharacterSheetDataAssetValidators::ValidateDataTables(Asset);

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name));

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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Progression));

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
    FCharacterSheetDataAssetHelpers::LogPropertyChange(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Proficiencies));

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
    HandleDataTableChange(Asset);
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

#pragma endregion Wrapper Functions
