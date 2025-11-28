// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassMotor.h"

// Project includes - Core
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/FeatureDataTable.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "Data/Structures/MulticlassTypes.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Data/Tables/SkillDataTable.h"
#include "Utils/DnDConstants.h"

// Engine includes
#include "Engine/DataTable.h"
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Get Available Classes
// ============================================================================
#pragma region Get Available Classes

TArray<FName> FMulticlassMotor::GetAvailableClasses(const UDataTable *ClassDataTable, int32 FinalStrength,
                                                    int32 FinalDexterity, int32 FinalConstitution,
                                                    int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma)
{
    if (!ClassDataTable)
    {
        return {};
    }

    TArray<int32> CharacterAttributes = {FinalStrength,     FinalDexterity, FinalConstitution,
                                         FinalIntelligence, FinalWisdom,    FinalCharisma};

    return FMulticlassHelpers::GetAvailableClassWithTagRequirements(ClassDataTable, CharacterAttributes);
}

#pragma endregion Get Available Classes

// ============================================================================
// Load Class Proficiencies
// ============================================================================
#pragma region Load Class Proficiencies

bool FMulticlassMotor::LoadClassProficiencies(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable,
                                              const UDataTable *ProficiencyDataTable,
                                              TArray<FMulticlassProficienciesEntry> &OutProficiencies)
{
    // Limpa array de saída
    OutProficiencies.Empty();

    // Validação de entrada (guard clauses)
    if (!FMulticlassHelpers::ValidateLoadProficienciesInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return false;
    }

    // Busca dados da classe na tabela (com logging de erro automático)
    const FClassDataRow *ClassRow =
        FMulticlassHelpers::FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassProficiencies"));
    if (!ClassRow)
    {
        return false;
    }

    // Converte proficiências da estrutura flat (arrays de handles separados)
    FMulticlassProficienciesEntry ConvertedEntry;

    // Resolve WeaponProficiencyHandles para nomes legíveis
    ConvertedEntry.armas = FMulticlassHelpers::ResolveProficiencyHandlesToNames(
        ClassRow->WeaponProficiencyHandles, ProficiencyDataTable);

    // Resolve ArmorProficiencyHandles para nomes legíveis
    ConvertedEntry.armaduras = FMulticlassHelpers::ResolveProficiencyHandlesToNames(
        ClassRow->ArmorProficiencyHandles, ProficiencyDataTable);

    // Resolve SavingThrowHandles para IDs (Ability Scores)
    ConvertedEntry.SavingThrowIDs.Empty();
    ConvertedEntry.SavingThrowIDs.Reserve(ClassRow->SavingThrowHandles.Num());
    for (const FDataTableRowHandle &Handle : ClassRow->SavingThrowHandles)
    {
        if (Handle.RowName != NAME_None)
        {
            ConvertedEntry.SavingThrowIDs.Add(Handle.RowName);
        }
    }

    // Resolve AvailableSkillHandles para IDs
    ConvertedEntry.FSkills.InitialAvailable.Empty();
    ConvertedEntry.FSkills.InitialAvailable.Reserve(ClassRow->AvailableSkillHandles.Num());
    for (const FDataTableRowHandle &SkillHandle : ClassRow->AvailableSkillHandles)
    {
        if (const FSkillDataRow *SkillRow = DataTableRowHandleHelpers::ResolveHandle<FSkillDataRow>(SkillHandle))
        {
            if (SkillRow->ID != NAME_None)
            {
                ConvertedEntry.FSkills.InitialAvailable.Add(SkillRow->ID);
            }
        }
        else if (SkillHandle.RowName != NAME_None)
        {
            ConvertedEntry.FSkills.InitialAvailable.Add(SkillHandle.RowName);
        }
    }

    ConvertedEntry.FSkills.available = NAME_None;
    ConvertedEntry.FSkills.Selected.Empty();
    ConvertedEntry.FSkills.qtdAvailable = ClassRow->SkillChoiceCount;
    ConvertedEntry.FSkills.InitialQtdAvailable = ClassRow->SkillChoiceCount;

    OutProficiencies.Add(ConvertedEntry);

    // Log quando proficiências são carregadas (ponto chave)
    if (OutProficiencies.Num() > 0)
    {
        FLogContext Context(TEXT("Multiclass"), TEXT("LoadClassProficiencies"));
        FLoggingSystem::LogInfo(Context,
                                FString::Printf(TEXT("Classe '%s': %d proficiência(s) carregada(s) com sucesso."),
                                                *ClassName.ToString(), OutProficiencies.Num()));
    }

    return true;
}

#pragma endregion Load Class Proficiencies

// ============================================================================
// Load Class Progression
// ============================================================================
#pragma region Load Class Progression

bool FMulticlassMotor::LoadClassProgression(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable,
                                            const UDataTable *FeatureDataTable,
                                            TArray<FMulticlassProgressEntry> &OutProgression)
{
    // Limpa array de saída
    OutProgression.Empty();

    // Validação de entrada (guard clauses)
    if (!FMulticlassHelpers::ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return false;
    }

    // Busca dados da classe na tabela (com logging de erro automático)
    const FClassDataRow *ClassRow =
        FMulticlassHelpers::FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassProgression"));
    if (!ClassRow)
    {
        return false;
    }

    // Popula Progression para cada nível de 1 até LevelInClass
    for (int32 Level = DnDConstants::MIN_LEVEL; Level <= LevelInClass; ++Level)
    {
        FMulticlassProgressEntry ProgressEntry;
        ProgressEntry.Level = Level;

        // Extrai features do nível específico (estrutura flat)
        const FProgressEntry *LevelEntry = nullptr;
        if (!FMulticlassHelpers::ExtractLevelFeatures(ClassRow->Progression, Level, LevelEntry))
        {
            // Nível sem entrada na progressão é válido (alguns níveis não têm features)
            // Cria entrada vazia para manter consistência
            OutProgression.Add(ProgressEntry);
            continue;
        }

        // Carrega features detalhadas do ClassFeaturesDataTable (estrutura flat com FeatureHandles)
        TArray<FMulticlassClassFeature> Features;
        if (FMulticlassHelpers::LoadFeaturesForLevel(LevelEntry->FeatureHandles, FeatureDataTable, Level, Features))
        {
            ProgressEntry.Features = Features;
        }

        OutProgression.Add(ProgressEntry);
    }

    // Log quando progressão é carregada (ponto chave)
    if (OutProgression.Num() > 0)
    {
        FLogContext Context(TEXT("Multiclass"), TEXT("LoadClassProgression"));
        FLoggingSystem::LogInfo(
            Context, FString::Printf(TEXT("Classe '%s': %d nível(is) de progressão carregado(s) com sucesso."),
                                     *ClassName.ToString(), OutProgression.Num()));
    }

    return true;
}

#pragma endregion Load Class Progression
