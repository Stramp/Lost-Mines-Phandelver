// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassMotor.h"

// Project includes - Core
#include "CreateSheet/Core/CharacterSheetData.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"
#include "CreateSheet/Multiclass/MulticlassTypes.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

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
// Validate Multiclass Requirements
// ============================================================================
#pragma region Validate Multiclass Requirements

bool FMulticlassMotor::ValidateMulticlassRequirements(const FCharacterSheetData &Data, FName DesiredClassName)
{
    // TODO: Implementar validação de requisitos de atributo
    return true;
}

#pragma endregion Validate Multiclass Requirements

// ============================================================================
// Apply Multiclass Rules
// ============================================================================
#pragma region Apply Multiclass Rules

void FMulticlassMotor::ApplyMulticlassRules(FCharacterSheetData &Data)
{
    // TODO: Implementar aplicação de regras de multiclasse
}

#pragma endregion Apply Multiclass Rules

// ============================================================================
// Process Level Change
// ============================================================================
#pragma region Process Level Change

void FMulticlassMotor::ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable)
{
    // Validação de entrada (guard clauses)
    if (!FMulticlassHelpers::ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return;
    }

    // Busca dados da classe na tabela
    const FClassDataRow *ClassRow = FMulticlassHelpers::FindAndValidateClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return;
    }

    // Extrai features do nível específico
    const FProgressEntry *LevelEntry = nullptr;
    if (!FMulticlassHelpers::ExtractLevelFeatures(ClassRow->FClass.Progression, LevelInClass, LevelEntry))
    {
        return;
    }

    // Log apenas quando há features ganhas (ponto chave)
    if (LevelEntry->Features.Num() > 0)
    {
        FString FeaturesString = FMulticlassHelpers::BuildFeaturesString(LevelEntry->Features);
        UE_LOG(LogTemp, Warning,
               TEXT("FMulticlassMotor::ProcessLevelChange - Classe = %s, Level = %d, Features = [%s]"),
               *ClassName.ToString(), LevelInClass, *FeaturesString);
    }
}

#pragma endregion Process Level Change

// ============================================================================
// Load Class Proficiencies
// ============================================================================
#pragma region Load Class Proficiencies

bool FMulticlassMotor::LoadClassProficiencies(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable,
                                              TArray<FMulticlassProficienciesEntry> &OutProficiencies)
{
    // Limpa array de saída
    OutProficiencies.Empty();

    // Validação de entrada (guard clauses)
    if (!FMulticlassHelpers::ValidateLoadProficienciesInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return false;
    }

    // Busca dados da classe na tabela
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);
    if (!ClassRow)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("FMulticlassMotor::LoadClassProficiencies - Classe '%s' não encontrada na tabela"),
               *ClassName.ToString());
        return false;
    }

    // Converte todas as proficiências da classe
    for (const FProficienciesEntry &SourceEntry : ClassRow->FClass.Proficiencies)
    {
        FMulticlassProficienciesEntry ConvertedEntry = FMulticlassHelpers::ConvertProficienciesEntry(SourceEntry);
        OutProficiencies.Add(ConvertedEntry);
    }

    // Log quando proficiências são carregadas (ponto chave)
    if (OutProficiencies.Num() > 0)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("FMulticlassMotor::LoadClassProficiencies - Classe = %s, Proficiências carregadas = %d"),
               *ClassName.ToString(), OutProficiencies.Num());
    }

    return true;
}

#pragma endregion Load Class Proficiencies
