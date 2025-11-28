// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassConversionHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/SkillDataTable.h"

// Project includes - Structures
#include "Data/Structures/FProficienciesEntry.h"
#include "Data/Structures/MulticlassTypes.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Resolve Proficiency Handles To Names
// ============================================================================
#pragma region Resolve Proficiency Handles To Names

TArray<FName> FMulticlassConversionHelpers::ResolveProficiencyHandlesToNames(
    const TArray<FDataTableRowHandle> &ProficiencyHandles, const UDataTable *ProficiencyDataTable)
{
    TArray<FName> ResolvedNames;
    if (!ProficiencyDataTable || ProficiencyHandles.Num() == 0)
    {
        return ResolvedNames;
    }

    FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyHandlesToNames"));
    UDataTable *NonConstTable = const_cast<UDataTable *>(ProficiencyDataTable);
    FString TableName = ProficiencyDataTable->GetName();
    int32 UnresolvedCount = 0;

    ResolvedNames.Reserve(ProficiencyHandles.Num());

    for (const FDataTableRowHandle &Handle : ProficiencyHandles)
    {
        if (Handle.RowName == NAME_None)
        {
            continue;
        }

        // Resolve handle para obter ProficiencyRow
        const FProficiencyDataRow *ProficiencyRow =
            DataTableRowHandleHelpers::ResolveHandle<FProficiencyDataRow>(Handle);

        if (!ProficiencyRow && Handle.DataTable.Get() != nullptr)
        {
            // Fallback: tenta buscar pelo RowName diretamente
            ProficiencyRow = DataTableHelpers::FindProficiencyRowByID(Handle.RowName, NonConstTable);
        }

        if (ProficiencyRow && ProficiencyRow->Name != NAME_None)
        {
            // Usa nome legível se encontrado
            ResolvedNames.Add(ProficiencyRow->Name);
        }
        else
        {
            // Fallback: usa ID original se não encontrado na tabela
            ResolvedNames.Add(Handle.RowName);
            UnresolvedCount++;

            // Loga erro de Data Table
            FLoggingSystem::LogDataTableError(
                Context, TableName, Handle.RowName.ToString(), TEXT("ProficiencyHandle"),
                FString::Printf(TEXT("Proficiência '%s' não encontrada na tabela. Verifique se o handle está correto."),
                                *Handle.RowName.ToString()));
        }
    }

    // Loga resumo se houver IDs não resolvidos (sistema ajusta automaticamente - sem popup)
    if (UnresolvedCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d proficiência(s) não foram resolvidas para nomes legíveis."), UnresolvedCount),
            false);
    }

    return ResolvedNames;
}

#pragma endregion Resolve Proficiency Handles To Names

// ============================================================================
// Resolve Proficiency IDs To Names
// ============================================================================
#pragma region Resolve Proficiency IDs To Names

TArray<FName> FMulticlassConversionHelpers::ResolveProficiencyIDsToNames(const TArray<FName> &ProficiencyIDs,
                                                                          const UDataTable *ProficiencyDataTable)
{
    FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyIDsToNames"));
    TArray<FName> ResolvedNames;
    ResolvedNames.Reserve(ProficiencyIDs.Num()); // Otimização: pre-aloca memória

    if (!ProficiencyDataTable)
    {
        // Se não há tabela, loga erro crítico e retorna IDs originais
        FLoggingSystem::LogError(
            Context, TEXT("ProficiencyDataTable não está configurado. IDs não serão resolvidos para nomes legíveis."),
            true);
        return ProficiencyIDs;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(ProficiencyDataTable);
    FString TableName = ProficiencyDataTable->GetName();
    int32 UnresolvedCount = 0;

    for (const FName &ProficiencyID : ProficiencyIDs)
    {
        if (ProficiencyID == NAME_None)
        {
            continue;
        }

        // Busca proficiência na tabela pelo ID
        const FProficiencyDataRow *ProficiencyRow =
            DataTableHelpers::FindProficiencyRowByID(ProficiencyID, NonConstTable);

        if (ProficiencyRow && ProficiencyRow->Name != NAME_None)
        {
            // Usa nome legível se encontrado
            ResolvedNames.Add(ProficiencyRow->Name);
        }
        else
        {
            // Fallback: usa ID original se não encontrado na tabela
            ResolvedNames.Add(ProficiencyID);
            UnresolvedCount++;

            // Loga erro de Data Table
            FLoggingSystem::LogDataTableError(
                Context, TableName, ProficiencyID.ToString(), TEXT("ProficiencyID"),
                FString::Printf(TEXT("Proficiência '%s' não encontrada na tabela. "
                                     "Verifique se o JSON tem 'ProficiencyID' ao invés de "
                                     "'p_id' e se o ID corresponde."),
                                *ProficiencyID.ToString()));
        }
    }

    // Loga resumo se houver IDs não resolvidos (sistema ajusta automaticamente - sem popup)
    if (UnresolvedCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d proficiência(s) não foram resolvidas para nomes legíveis."), UnresolvedCount),
            false);
    }

    return ResolvedNames;
}

#pragma endregion Resolve Proficiency IDs To Names

// ============================================================================
// Convert Proficiencies Entry
// ============================================================================
#pragma region Convert Proficiencies Entry

FMulticlassProficienciesEntry FMulticlassConversionHelpers::ConvertProficienciesEntry(
    const FProficienciesEntry &SourceEntry, const UDataTable *ProficiencyDataTable)
{
    FMulticlassProficienciesEntry Result;

    // Resolve IDs de armas para nomes legíveis
    Result.armas = ResolveProficiencyIDsToNames(SourceEntry.armas, ProficiencyDataTable);

    // Resolve IDs de armaduras para nomes legíveis
    Result.armaduras = ResolveProficiencyIDsToNames(SourceEntry.armaduras, ProficiencyDataTable);

    // Saving throws agora são IDs (ex: "ABL_Strength", "ABL_Constitution")
    Result.SavingThrowIDs = SourceEntry.SavingThrowIDs;

    // Skills: converte FDataTableRowHandle (master data) para FName SkillID (runtime instance)
    // SourceEntry.FSkills.AvailableSkillHandles é TArray<FDataTableRowHandle>
    // Result.FSkills.InitialAvailable é TArray<FName> (SkillID)
    Result.FSkills.InitialAvailable.Empty();
    Result.FSkills.InitialAvailable.Reserve(SourceEntry.FSkills.AvailableSkillHandles.Num());

    // Resolve cada handle para obter SkillID
    for (const FDataTableRowHandle &SkillHandle : SourceEntry.FSkills.AvailableSkillHandles)
    {
        // Resolve handle para obter SkillID da FSkillDataRow
        if (const FSkillDataRow *SkillRow = DataTableRowHandleHelpers::ResolveHandle<FSkillDataRow>(SkillHandle))
        {
            if (SkillRow->ID != NAME_None)
            {
                Result.FSkills.InitialAvailable.Add(SkillRow->ID);
            }
        }
        else if (SkillHandle.RowName != NAME_None)
        {
            // Fallback: usa RowName se resolução falhar (assumindo que RowName = SkillID)
            Result.FSkills.InitialAvailable.Add(SkillHandle.RowName);
        }
    }

    Result.FSkills.available = NAME_None;                    // Dropdown inicia vazio
    Result.FSkills.Selected.Empty();                         // Array de escolhas inicia vazio
    Result.FSkills.qtdAvailable = SourceEntry.FSkills.Count; // Quantidade inicial disponível
    Result.FSkills.InitialQtdAvailable = SourceEntry.FSkills.Count;

    return Result;
}

#pragma endregion Convert Proficiencies Entry

// ============================================================================
// Convert Feature Row To Multiclass Feature
// ============================================================================
#pragma region Convert Feature Row To Multiclass Feature

FMulticlassClassFeature FMulticlassConversionHelpers::ConvertFeatureRowToMulticlassFeature(
    const FFeatureDataRow &FeatureRow, int32 LevelUnlocked)
{
    FMulticlassClassFeature Result;

    // Copia dados básicos
    Result.Name = FeatureRow.Name;
    Result.ID = FeatureRow.ID;
    Result.Description = FeatureRow.Description;
    Result.LevelUnlocked = LevelUnlocked; // Usa o nível passado como parâmetro
    Result.FeatureType = FeatureRow.FeatureType;
    Result.FeatureData = FeatureRow.FeatureData;

    // Calcula flags baseado em dados da tabela (fonte de verdade)
    const bool bIsChoiceType =
        (FeatureRow.FeatureType == TEXT("Choice") || FeatureRow.FeatureType == TEXT("SubclassSelection"));
    const int32 ChoicesCount = FeatureRow.AvailableChoices.Num();
    const bool bHasChoicesInTable = bIsChoiceType && (ChoicesCount > 0);

    // bIsMultipleChoice é determinado por bAllowMultipleChoices, não pela quantidade de opções
    // Tipo 2 (Escolha Única): bAllowMultipleChoices = false → usa AvailableChoices (dropdown)
    // Tipo 3 (Escolhas Múltiplas): bAllowMultipleChoices = true → usa SelectedChoices (array)
    const bool bIsMultiple = bHasChoicesInTable && FeatureRow.bAllowMultipleChoices;

    // Define flags calculadas
    Result.bHasAvailableChoices = bHasChoicesInTable;
    Result.bIsMultipleChoice = bIsMultiple;

    // Popula AvailableChoices ou SelectedChoices baseado no tipo
    if (bHasChoicesInTable)
    {
        if (bIsMultiple)
        {
            // Tipo 3: Escolhas Múltiplas - usa AvailableChoiceToAdd + SelectedChoices (array)
            Result.AvailableChoices = NAME_None;     // Não usado para múltiplas escolhas
            Result.AvailableChoiceToAdd = NAME_None; // Dropdown para adicionar ao array
            Result.SelectedChoices.Empty();          // Inicia vazio para jogador escolher
        }
        else
        {
            // Tipo 2: Escolha Única - usa AvailableChoices (dropdown)
            // Se houver apenas 1 opção, preenche automaticamente com ID; caso contrário, deixa vazio para jogador
            // escolher
            if (ChoicesCount == 1)
            {
                Result.AvailableChoices = FeatureRow.AvailableChoices[0].ID; // Armazena ID, não Name
            }
            else
            {
                Result.AvailableChoices = NAME_None; // Jogador escolhe no dropdown
            }
            Result.AvailableChoiceToAdd = NAME_None; // Não usado para escolha única
            Result.SelectedChoices.Empty();          // Não usado para escolha única
        }
    }
    else
    {
        // Tipo 1: Feature Automático - nenhuma escolha disponível
        Result.AvailableChoices = NAME_None;
        Result.AvailableChoiceToAdd = NAME_None;
        Result.SelectedChoices.Empty();
    }

    return Result;
}

#pragma endregion Convert Feature Row To Multiclass Feature

// ============================================================================
// Build Features String
// ============================================================================
#pragma region Build Features String

FString FMulticlassConversionHelpers::BuildFeaturesString(const TArray<FName> &Features)
{
    if (Features.Num() == 0)
    {
        return TEXT("Nenhum");
    }

    // Otimização: pre-aloca memória estimada (nome médio ~20 chars + separador)
    FString Result;
    Result.Reserve(Features.Num() * 25);

    for (int32 i = 0; i < Features.Num(); ++i)
    {
        if (i > 0)
        {
            Result += TEXT(", ");
        }
        Result += Features[i].ToString();
    }

    return Result;
}

#pragma endregion Build Features String
