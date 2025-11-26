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

    TArray<int32> CharacterAttributes = {
        FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence, FinalWisdom, FinalCharisma};

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
// Local Helpers
// ============================================================================
#pragma region Local Helpers

namespace
{
    /**
     * Constrói string formatada com lista de features.
     * Helper local para manter ProcessLevelChange focada.
     *
     * @param Features Array de nomes de features
     * @return String formatada (ex: "Feature1, Feature2" ou "Nenhum")
     */
    FString BuildFeaturesString(const TArray<FName> &Features)
    {
        if (Features.Num() == 0)
        {
            return TEXT("Nenhum");
        }

        FString Result;
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

    /**
     * Valida parâmetros de entrada para ProcessLevelChange.
     * Extraído para manter função principal focada.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    bool ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable)
    {
        if (ClassName == NAME_None)
        {
            return false;
        }

        if (!ClassDataTable)
        {
            return false;
        }

        if (LevelInClass < 1 || LevelInClass > 20)
        {
            return false;
        }

        return true;
    }

    /**
     * Busca e valida dados da classe na tabela.
     * Extraído para manter função principal focada.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes
     * @return Row da classe encontrada, ou nullptr se não encontrada
     */
    const FClassDataRow *FindAndValidateClassRow(FName ClassName, const UDataTable *ClassDataTable)
    {
        UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
        const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

        if (!ClassRow)
        {
            return nullptr;
        }

        return ClassRow;
    }

    /**
     * Extrai features do nível específico da progressão.
     * Extraído para manter função principal focada.
     *
     * @param Progression Array de progressão da classe
     * @param LevelInClass Nível desejado (1-based)
     * @param OutLevelEntry [OUT] Entry do nível encontrado
     * @return true se nível foi encontrado, false caso contrário
     */
    bool ExtractLevelFeatures(const TArray<FProgressEntry> &Progression, int32 LevelInClass,
                              const FProgressEntry *&OutLevelEntry)
    {
        if (LevelInClass > Progression.Num())
        {
            return false;
        }

        // Array é 0-based, nível é 1-based
        OutLevelEntry = &Progression[LevelInClass - 1];
        return true;
    }
} // namespace

#pragma endregion Local Helpers

// ============================================================================
// Process Level Change
// ============================================================================
#pragma region Process Level Change

void FMulticlassMotor::ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable)
{
    // Validação de entrada (guard clauses)
    if (!ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return;
    }

    // Busca dados da classe na tabela
    const FClassDataRow *ClassRow = FindAndValidateClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return;
    }

    // Extrai features do nível específico
    const FProgressEntry *LevelEntry = nullptr;
    if (!ExtractLevelFeatures(ClassRow->FClass.Progression, LevelInClass, LevelEntry))
    {
        return;
    }

    // Log apenas quando há features ganhas (ponto chave)
    if (LevelEntry->Features.Num() > 0)
    {
        FString FeaturesString = BuildFeaturesString(LevelEntry->Features);
        UE_LOG(LogTemp, Warning,
               TEXT("FMulticlassMotor::ProcessLevelChange - Classe = %s, Level = %d, Features = [%s]"),
               *ClassName.ToString(), LevelInClass, *FeaturesString);
    }
}

#pragma endregion Process Level Change
