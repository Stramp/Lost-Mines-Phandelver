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
#include "CreateSheet/PointBuy/PointBuyValidationResult.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "CreateSheet/Multiclass/MulticlassMotor.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

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

    // Valida Point Buy system (calcula PointsRemaining)
    FPointBuyValidationResult ValidationResult = FPointBuyValidator::ValidatePointBuy(
        Asset->PointBuyStrength, Asset->PointBuyDexterity, Asset->PointBuyConstitution, Asset->PointBuyIntelligence,
        Asset->PointBuyWisdom, Asset->PointBuyCharisma);

    // Aplica resultado da validação no Asset
    Asset->PointsRemaining = ValidationResult.PointsRemaining;

    // Log de aviso se scores estão fora do range válido
    if (!ValidationResult.bAllScoresValid && !ValidationResult.LogMessage.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *ValidationResult.LogMessage);
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
void FCharacterSheetDataAssetHandlers::HandleLevelInClassChange(UCharacterSheetDataAsset *Asset)
{
    if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

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

    // Marca objeto como modificado
    Asset->Modify();

    // Processa mudanças de nível para todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Atualiza flags bCanEditProgression e bCanEditProficiencies (desabilita botão "+" no editor)
        Entry.ClassData.bCanEditProgression = FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass);
        Entry.ClassData.bCanEditProficiencies = FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass);

        // Valida se é permitido processar Progression (usa helper puro)
        if (!Entry.ClassData.bCanEditProgression)
        {
            // Se não pode processar, limpa o array e pula para próxima entrada
            Entry.ClassData.Progression.Empty();
            continue;
        }

        // Se LevelInClass mudou, ajusta o array Progression
        TArray<FMulticlassProgressEntry> &Progression = Entry.ClassData.Progression;
        if (LevelInClass >= 1 && LevelInClass <= 20)
        {
            Progression.SetNum(LevelInClass);
            // Garante que cada elemento tenha o Level correto (1-based)
            for (int32 j = 0; j < Progression.Num(); ++j)
            {
                Progression[j].Level = j + 1;
            }
        }
        else
        {
            // Se LevelInClass inválido, usa tamanho do array
            LevelInClass = Progression.Num();
        }

        // Processa features do nível apenas se há classe válida e nível válido
        if (Asset->ClassDataTable)
        {
            FMulticlassMotor::ProcessLevelChange(ClassName, LevelInClass, Asset->ClassDataTable);
        }
    }
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

    // Verifica todas as entradas de multiclasse e reseta se tiver tag de requerimento
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        if (FCharacterSheetDataAssetHelpers::ResetClassWithRequirementTag(Entry, i))
        {
            Asset->Modify(); // Marca objeto como modificado apenas se resetou
        }

        // Ajusta LevelInClass baseado na presença de classe
        const FName ClassName = Entry.ClassData.Name;
        if (ClassName != NAME_None)
        {
            // Se há classe, seta LevelInClass para 1
            Entry.ClassData.LevelInClass = 1;
        }
        else
        {
            // Se não há classe, seta LevelInClass para 0
            Entry.ClassData.LevelInClass = 0;
        }

        // Atualiza flags bCanEditProgression e bCanEditProficiencies (desabilita botão "+" no editor)
        Entry.ClassData.bCanEditProgression =
            FMulticlassHelpers::CanProcessProgression(Entry.ClassData.Name, Entry.ClassData.LevelInClass);
        Entry.ClassData.bCanEditProficiencies =
            FMulticlassHelpers::CanProcessProgression(Entry.ClassData.Name, Entry.ClassData.LevelInClass);

        // Carrega proficiências quando classe é escolhida e LevelInClass == 1
        // Usa LoadClassProficiencies para obter nomes legíveis (padrão)
        if (ClassName != NAME_None && Entry.ClassData.LevelInClass == 1)
        {
            TArray<FMulticlassProficienciesEntry> LoadedProficiencies;
            if (FMulticlassMotor::LoadClassProficiencies(ClassName, Entry.ClassData.LevelInClass, Asset->ClassDataTable,
                                                         Asset->ClassProficienciesDataTable, LoadedProficiencies))
            {
                // Preenche array de proficiências com resultado do motor
                Entry.ClassData.Proficiencies = LoadedProficiencies;
                UE_LOG(LogTemp, Warning,
                       TEXT("FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameChange - "
                            "Proficiências carregadas para classe '%s': %d entradas"),
                       *ClassName.ToString(), LoadedProficiencies.Num());
            }
            else
            {
                // Limpa proficiências se não foi possível carregar
                Entry.ClassData.Proficiencies.Empty();
                UE_LOG(LogTemp, Warning,
                       TEXT("FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameChange - "
                            "Falha ao carregar proficiências para classe '%s'"),
                       *ClassName.ToString());
            }
        }
        else
        {
            // Limpa proficiências se não há classe ou nível não é 1
            Entry.ClassData.Proficiencies.Empty();
        }
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
    HandleLevelInClassChange(Asset);
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
 * Atualiza qtdAvailable dinamicamente quando skills são escolhidas/removidas do available.
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

    // Atualiza qtdAvailable para todas as entradas de proficiências
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];

        for (FMulticlassProficienciesEntry &ProficiencyEntry : Entry.ClassData.Proficiencies)
        {
            FMulticlassSkills &Skills = ProficiencyEntry.FSkills;

            // Se não há estado inicial armazenado, inicializa com valores atuais
            if (Skills.InitialAvailableCount == 0 && Skills.InitialQtdAvailable == 0)
            {
                Skills.InitialAvailableCount = Skills.available.Num();
                Skills.InitialQtdAvailable = Skills.qtdAvailable;
            }

            // Calcula quantas skills foram escolhidas (removidas do available)
            const int32 CurrentAvailableCount = Skills.available.Num();
            const int32 SkillsChosen = Skills.InitialAvailableCount - CurrentAvailableCount;

            // Atualiza qtdAvailable: quantidade inicial menos skills já escolhidas
            // FMath::Max garante que qtdAvailable nunca será negativo
            Skills.qtdAvailable = FMath::Max(0, Skills.InitialQtdAvailable - SkillsChosen);

            // Validação: não pode ter mais skills escolhidas do que o permitido
            if (SkillsChosen > Skills.InitialQtdAvailable)
            {
                UE_LOG(LogTemp, Warning,
                       TEXT("FCharacterSheetDataAssetHandlers::HandleProficienciesChange - "
                            "Aviso: Mais skills escolhidas (%d) do que o permitido (%d) para entrada %d"),
                       SkillsChosen, Skills.InitialQtdAvailable, i);
            }
        }
    }

    Asset->Modify(); // Marca objeto como modificado após atualização
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
