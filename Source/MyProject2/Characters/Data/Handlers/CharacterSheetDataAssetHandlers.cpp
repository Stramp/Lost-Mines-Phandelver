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

// Project includes - Updaters
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/ValidationGuard.h"

// Project includes - CreateSheet
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "CreateSheet/Multiclass/MulticlassMotor.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"

#pragma endregion Includes

// ============================================================================
// Local Helpers
// ============================================================================
#pragma region Local Helpers

namespace
{
    /**
     * Loga que PostEditChangeProperty chamou o handler para uma propriedade específica.
     * Helper local para evitar duplicação de código de log.
     *
     * @param PropertyName Nome da propriedade que mudou
     */
    void LogPropertyChange(FName PropertyName)
    {
        UE_LOG(LogTemp, Warning, TEXT("PostEditChangeProperty me chamou: %s mudou"), *PropertyName.ToString());
    }

    /**
     * Valida se Asset é válido e retorna false se não for.
     * Helper local para evitar duplicação de validação null.
     *
     * @param Asset Asset a validar
     * @return true se Asset é válido, false caso contrário
     */
    bool ValidateAsset(UCharacterSheetDataAsset *Asset) { return Asset != nullptr; }

    /**
     * Reseta sub-raça quando raça principal muda.
     * Extraído de HandleRaceChange para manter função focada.
     *
     * @param Asset Asset do personagem
     * @param PropertyName Nome da propriedade que mudou
     */
    void ResetSubraceIfRaceChanged(UCharacterSheetDataAsset *Asset, FName PropertyName)
    {
        if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
        {
            if (Asset->SelectedSubrace != NAME_None)
            {
                Asset->Modify();
                Asset->SelectedSubrace = NAME_None;
            }
        }
    }

    /**
     * Loga informações sobre status dos Data Tables.
     * Extraído de HandleDataTableChange para manter função focada.
     *
     * @param Asset Asset do personagem
     */
    void LogDataTableStatus(UCharacterSheetDataAsset *Asset)
    {
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

    /**
     * Obtém nome da classe formatado para log (ou "Unknown" se vazio).
     * Helper local para evitar duplicação de lógica de formatação.
     *
     * @param ClassName Nome da classe original
     * @return Nome formatado para exibição
     */
    FString GetFormattedClassName(const FString &ClassName)
    {
        return ClassName.IsEmpty() ? TEXT("Unknown") : ClassName;
    }

    /**
     * Reseta classe com tag de requerimento para NAME_None.
     * Extraído de HandleMulticlassClassNameChange para manter função focada.
     *
     * @param Entry Entrada de multiclasse a verificar
     * @param Index Índice da entrada no array
     * @return true se resetou a classe, false caso contrário
     */
    bool ResetClassWithRequirementTag(FMulticlassEntry &Entry, int32 Index)
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

} // namespace

#pragma endregion Local Helpers

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
    LogPropertyChange(PropertyName);

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Resetar sub-raça se raça mudou
    ResetSubraceIfRaceChanged(Asset, PropertyName);

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
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyStrength));

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Motor de Point Buy: aplica alocação nos Final Scores
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(Asset);

    // Valida Point Buy system (calcula PointsRemaining)
    FPointBuyValidator::ValidatePointBuy(Asset);

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
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground));

    if (!ValidateAsset(Asset))
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
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages));

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de idiomas
    FCharacterSheetDataAssetValidators::ValidateLanguageChoices(Asset);

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
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices));

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de Variant Human
    FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(Asset);

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
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable));

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
    FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(Asset);

    // Log informativo sobre status dos Data Tables
    LogDataTableStatus(Asset);
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
    if (!ValidateAsset(Asset))
    {
        return;
    }

    // Marca objeto como modificado
    Asset->Modify();

    // Processa mudanças de nível para todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        int32 LevelInClass = Entry.ClassData.LevelInClass;

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

        if (ClassName != NAME_None && LevelInClass > 0 && Asset->ClassDataTable)
        {
            FMulticlassMotor::ProcessLevelChange(ClassName, LevelInClass, Asset->ClassDataTable);
        }
    }
}

/**
 * Processa mudanças em ClassData.Name dentro do array Multiclass.
 * Reseta o campo para NAME_None se a classe selecionada tiver tag de requerimento (começa com "[").
 */
void FCharacterSheetDataAssetHandlers::HandleMulticlassClassNameChange(UCharacterSheetDataAsset *Asset)
{
    LogPropertyChange(GET_MEMBER_NAME_CHECKED(FMulticlassClassData, Name));

    if (!ValidateAsset(Asset))
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Verifica todas as entradas de multiclasse e reseta se tiver tag de requerimento
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        if (ResetClassWithRequirementTag(Entry, i))
        {
            Asset->Modify(); // Marca objeto como modificado apenas se resetou
        }
    }
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

#pragma endregion Wrapper Functions
