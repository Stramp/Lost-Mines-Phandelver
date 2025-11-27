// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetLoaders.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Structures/MulticlassTypes.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Data Loading
// ============================================================================
#pragma region Multiclass Data Loading

bool FCharacterSheetDataAssetLoaders::LoadClassBasicInfo(UCharacterSheetDataAsset *Asset, int32 EntryIndex)
{
    if (!Asset || EntryIndex < 0 || EntryIndex >= Asset->Multiclass.Num())
    {
        return false;
    }

    FMulticlassEntry &Entry = Asset->Multiclass[EntryIndex];
    const FName ClassName = Entry.ClassData.Name;

    // Só carrega se há classe válida e tabela configurada
    if (ClassName == NAME_None || !Asset->ClassDataTable)
    {
        Entry.ClassData.MulticlassRequirements.Empty();
        return false;
    }

    // Carrega informações básicas usando helper
    TArray<FString> LoadedRequirements;
    if (FMulticlassHelpers::LoadClassBasicInfo(ClassName, Asset->ClassDataTable, LoadedRequirements))
    {
        Entry.ClassData.MulticlassRequirements = LoadedRequirements;
        return true;
    }

    Entry.ClassData.MulticlassRequirements.Empty();
    return false;
}

bool FCharacterSheetDataAssetLoaders::LoadClassProficiencies(UCharacterSheetDataAsset *Asset, int32 EntryIndex)
{
    if (!Asset || EntryIndex < 0 || EntryIndex >= Asset->Multiclass.Num())
    {
        return false;
    }

    FMulticlassEntry &Entry = Asset->Multiclass[EntryIndex];
    const FName ClassName = Entry.ClassData.Name;
    const int32 LevelInClass = Entry.ClassData.LevelInClass;

    // Só carrega se há classe válida, nível 1 e tabelas configuradas
    if (ClassName == NAME_None || LevelInClass != 1)
    {
        Entry.ClassData.Proficiencies.Empty();
        return false;
    }

    // ClassDataTable é obrigatória e já validada em ValidateDataTables (não precisa validar aqui)
    if (!Asset->ClassDataTable)
    {
        Entry.ClassData.Proficiencies.Empty();
        return false;
    }

    // ProficiencyDataTable é obrigatória para resolver IDs de proficiências
    if (!Asset->ProficiencyDataTable)
    {
        FLogContext Context(TEXT("CharacterSheet"), TEXT("LoadClassProficiencies"));
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(
                TEXT("Multiclass[%d] - ProficiencyDataTable não configurado no Data Asset. Configure a tabela "
                     "em 'Data Tables > Proficiency Data Table' para carregar proficiências."),
                EntryIndex),
            false);
        Entry.ClassData.Proficiencies.Empty();
        return false;
    }

    // Carrega proficiências usando motor
    TArray<FMulticlassProficienciesEntry> LoadedProficiencies;
    if (FMulticlassMotor::LoadClassProficiencies(ClassName, LevelInClass, Asset->ClassDataTable,
                                                 Asset->ProficiencyDataTable, LoadedProficiencies))
    {
        Entry.ClassData.Proficiencies = LoadedProficiencies;
        return true;
    }

    // Log de falha (motor não conseguiu carregar)
    FLogContext Context(TEXT("CharacterSheet"), TEXT("LoadClassProficiencies"));
    FLoggingSystem::LogWarning(Context,
                               FString::Printf(TEXT("Multiclass[%d] - Falha ao carregar proficiências para classe "
                                                    "'%s'. Verifique se a classe existe no ClassDataTable."),
                                               EntryIndex, *ClassName.ToString()),
                               false);
    Entry.ClassData.Proficiencies.Empty();
    return false;
}

bool FCharacterSheetDataAssetLoaders::LoadClassProgression(UCharacterSheetDataAsset *Asset, int32 EntryIndex)
{
    if (!Asset || EntryIndex < 0 || EntryIndex >= Asset->Multiclass.Num())
    {
        return false;
    }

    FMulticlassEntry &Entry = Asset->Multiclass[EntryIndex];
    const FName ClassName = Entry.ClassData.Name;
    const int32 LevelInClass = Entry.ClassData.LevelInClass;

    // Só carrega se pode processar Progression
    if (!FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass))
    {
        Entry.ClassData.Progression.Empty();
        return false;
    }

    // Carrega progressão usando motor
    if (Asset->ClassDataTable && Asset->ClassFeaturesDataTable)
    {
        TArray<FMulticlassProgressEntry> LoadedProgression;
        if (FMulticlassMotor::LoadClassProgression(ClassName, LevelInClass, Asset->ClassDataTable,
                                                   Asset->ClassFeaturesDataTable, LoadedProgression))
        {
            Entry.ClassData.Progression = LoadedProgression;
            return true;
        }
    }

    // Se falhou, retorna false (fallback será feito pelo Handler)
    return false;
}

void FCharacterSheetDataAssetLoaders::LogLevelChangeFeatures(UCharacterSheetDataAsset *Asset, int32 EntryIndex)
{
    if (!Asset || EntryIndex < 0 || EntryIndex >= Asset->Multiclass.Num())
    {
        return;
    }

    FMulticlassEntry &Entry = Asset->Multiclass[EntryIndex];
    const FName ClassName = Entry.ClassData.Name;
    const int32 LevelInClass = Entry.ClassData.LevelInClass;

    // Só loga se há classe válida e tabela configurada
    if (ClassName == NAME_None || !Asset->ClassDataTable)
    {
        return;
    }

    // Loga features ganhas no nível usando helper (apenas log informativo)
    FMulticlassHelpers::LogLevelChangeFeatures(ClassName, LevelInClass, Asset->ClassDataTable);
}

void FCharacterSheetDataAssetLoaders::LoadAllMulticlassData(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Carrega dados para todas as entradas de multiclasse
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        // Carrega informações básicas da classe (MulticlassRequirements)
        LoadClassBasicInfo(Asset, i);

        // Carrega proficiências se classe válida e nível 1
        LoadClassProficiencies(Asset, i);

        // Carrega progressão se classe válida e nível > 0
        LoadClassProgression(Asset, i);
    }
}

void FCharacterSheetDataAssetLoaders::ReloadMulticlassDataIfNeeded(UCharacterSheetDataAsset *Asset,
                                                                   bool bLevelInClassWasAdjusted)
{
    if (!Asset || !bLevelInClassWasAdjusted)
    {
        return;
    }

    // Recarrega apenas proficiências e progression (não BasicInfo, pois não depende de LevelInClass)
    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        LoadClassProficiencies(Asset, i);
        LoadClassProgression(Asset, i);
    }
}

#pragma endregion Multiclass Data Loading
