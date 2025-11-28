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
#include "CreateSheet/Multiclass/MulticlassDataLoadingHelpers.h"
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"
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
                                                    int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma,
                                                    const UDataTable *AbilityScoreDataTable)
{
    if (!ClassDataTable)
    {
        return {};
    }

    TArray<int32> CharacterAttributes = {FinalStrength,     FinalDexterity, FinalConstitution,
                                         FinalIntelligence, FinalWisdom,    FinalCharisma};

    return FMulticlassDataLoadingHelpers::GetAvailableClassWithTagRequirements(ClassDataTable, CharacterAttributes,
                                                                              AbilityScoreDataTable);
}

#pragma endregion Get Available Classes

// ============================================================================
// Load Class Proficiencies
// ============================================================================
#pragma region Load Class Proficiencies

void FMulticlassMotor::LoadClassProficiencies(const FMulticlassProficienciesEntry& Entry,
                                               TArray<FMulticlassProficienciesEntry>& OutProficiencies)
{
    // Motor puro: apenas adiciona entry ao array
    // Assume que entry já foi convertida (pré-condição)
    OutProficiencies.Add(Entry);
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
    if (!FMulticlassValidationHelpers::ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return false;
    }

    // Busca dados da classe na tabela (com logging de erro automático)
    const FClassDataRow *ClassRow =
        FMulticlassDataLoadingHelpers::FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassProgression"));
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
        if (!FMulticlassDataLoadingHelpers::ExtractLevelFeatures(ClassRow->Progression, Level, LevelEntry))
        {
            // Nível sem entrada na progressão é válido (alguns níveis não têm features)
            // Cria entrada vazia para manter consistência
            OutProgression.Add(ProgressEntry);
            continue;
        }

        // Carrega features detalhadas do ClassFeaturesDataTable (estrutura flat com FeatureHandles)
        TArray<FMulticlassClassFeature> Features;
        if (FMulticlassDataLoadingHelpers::LoadFeaturesForLevel(LevelEntry->FeatureHandles, FeatureDataTable, Level, Features))
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
