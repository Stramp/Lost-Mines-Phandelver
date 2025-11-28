// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MulticlassProficiencyOrchestrator.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassProficiencyValidator.h"
#include "CreateSheet/Multiclass/MulticlassDataLoader.h"
#include "CreateSheet/Multiclass/MulticlassProficiencyResolver.h"
#include "CreateSheet/Multiclass/MulticlassProficiencyConverter.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Proficiency Orchestrator
// ============================================================================
#pragma region Multiclass Proficiency Orchestrator

bool FMulticlassProficiencyOrchestrator::Load(FName ClassName, int32 LevelInClass, const UDataTable* ClassDataTable,
                                               const UDataTable* ProficiencyDataTable,
                                               TArray<FMulticlassProficienciesEntry>& OutProficiencies)
{
    FLogContext Context(TEXT("MulticlassProficiencyOrchestrator"), TEXT("Load"));

    // Limpa array de saída
    OutProficiencies.Empty();

    // 1. Valida (Validator)
    if (!FMulticlassProficiencyValidator::ValidateInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return false;
    }

    // 2. Busca dados (Loader)
    const FClassDataRow* ClassRow = FMulticlassDataLoader::LoadClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return false;
    }

    // 3. Resolve handles (Resolver)
    FClassProficiencyData ProficiencyData = FMulticlassProficiencyResolver::Resolve(ClassRow, ProficiencyDataTable);

    // 4. Converte (Converter)
    FMulticlassProficienciesEntry Entry = FMulticlassProficiencyConverter::Convert(ProficiencyData);

    // 5. Aplica (Motor puro)
    FMulticlassMotor::LoadClassProficiencies(Entry, OutProficiencies);

    // 6. Logging (responsabilidade do orquestrador)
    if (OutProficiencies.Num() > 0)
    {
        FLoggingSystem::LogInfo(
            Context,
            FString::Printf(TEXT("Classe '%s': %d proficiência(s) carregada(s) com sucesso."), *ClassName.ToString(),
                           OutProficiencies.Num()));
    }

    return true;
}

#pragma endregion Multiclass Proficiency Orchestrator
