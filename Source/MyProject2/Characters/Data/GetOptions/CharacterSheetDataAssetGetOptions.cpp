// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetGetOptions.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/FeatureChoiceHelpers.h"

// Project includes - CreateSheet Motors
#include "CreateSheet/Multiclass/MulticlassMotor.h"

// Project includes - Data Tables
#include "Data/Tables/FeatureDataTable.h"

// Engine includes
#include "Engine/DataTable.h"
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Race and Background Options
// ============================================================================
#pragma region Race and Background Options

/**
 * Retorna todos os nomes de raças disponíveis no RaceDataTable.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetRaceNames(const UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllRaceNames(const_cast<UDataTable *>(RaceDataTable));
}

/**
 * Retorna todas as sub-raças disponíveis para a raça selecionada.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubraceNames(const UDataTable *RaceDataTable, FName SelectedRace)
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, const_cast<UDataTable *>(RaceDataTable));
}

/**
 * Retorna todos os nomes de backgrounds disponíveis no BackgroundDataTable.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetBackgroundNames(const UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(const_cast<UDataTable *>(BackgroundDataTable));
}

/**
 * Retorna todos os nomes de idiomas disponíveis (para dropdown de escolhas de idiomas).
 * Usa ProficiencyDataTable se fornecido (Data-Driven), caso contrário usa fallback hardcoded.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNames(const UDataTable *ProficiencyDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguageNames(const_cast<UDataTable *>(ProficiencyDataTable));
}

/**
 * Retorna idiomas disponíveis para escolha baseado em raça, sub-raça e background.
 * Exclui idiomas já selecionados.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
    FName RaceName, FName SubraceName, FName BackgroundName, const TArray<FName> &SelectedLanguages,
    const UDataTable *RaceDataTable, const UDataTable *BackgroundDataTable, const UDataTable *ProficiencyDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguagesForChoice(
        RaceName, SubraceName, BackgroundName, SelectedLanguages, const_cast<UDataTable *>(RaceDataTable),
        const_cast<UDataTable *>(BackgroundDataTable), const_cast<UDataTable *>(ProficiencyDataTable));
}

#pragma endregion Race and Background Options

// ============================================================================
// Point Buy Options
// ============================================================================
#pragma region Point Buy Options

/**
 * Retorna todos os nomes de ability scores (Strength, Dexterity, etc.).
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames()
{
    return CharacterSheetHelpers::GetAbilityScoreNames();
}

/**
 * Retorna todos os nomes de skills de D&D 5e.
 * Usa ProficiencyDataTable se fornecido (Data-Driven), caso contrário usa fallback hardcoded.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames(const UDataTable *ProficiencyDataTable)
{
    return CharacterSheetHelpers::GetSkillNames(const_cast<UDataTable *>(ProficiencyDataTable));
}

/**
 * Retorna todos os feats disponíveis para Variant Human baseado nos ability scores.
 * Filtra feats que têm requisitos de atributo atendidos.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(const UDataTable *FeatDataTable,
                                                                        const TMap<FName, int32> &AbilityScores)
{
    if (!FeatDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAvailableFeatsForVariantHuman(AbilityScores,
                                                                   const_cast<UDataTable *>(FeatDataTable));
}

#pragma endregion Point Buy Options

// ============================================================================
// Multiclass Options
// ============================================================================
#pragma region Multiclass Options

/**
 * Retorna todas as classes disponíveis com verificação de requisitos de atributo.
 * Atualmente retorna apenas nomes de classes do DataTable sem validação de requisitos.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetListClassAvaible(const UDataTable *ClassDataTable,
                                                                      int32 FinalStrength, int32 FinalDexterity,
                                                                      int32 FinalConstitution, int32 FinalIntelligence,
                                                                      int32 FinalWisdom, int32 FinalCharisma)
{
    // Solicita classes disponíveis ao motor de multiclasse
    return FMulticlassMotor::GetAvailableClasses(ClassDataTable, FinalStrength, FinalDexterity, FinalConstitution,
                                                 FinalIntelligence, FinalWisdom, FinalCharisma);
}

#pragma endregion Multiclass Options

// ============================================================================
// Feature Choice Options
// ============================================================================
#pragma region Feature Choice Options

/**
 * Retorna todos os nomes de escolhas disponíveis de todas as features no ClassFeaturesDataTable.
 * Coleta todas as AvailableChoices de todas as features na tabela.
 * Usado para dropdown em FMulticlassClassFeature.AvailableChoices.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableChoiceNames(const UDataTable *FeatureDataTable)
{
    TArray<FName> Result;
    TSet<FName> UniqueChoices; // Usa TSet para evitar duplicatas

    if (!FeatureDataTable)
    {
        return Result;
    }

    // Itera por todas as features na tabela
    TArray<FName> RowNames = FeatureDataTable->GetRowNames();

    for (const FName &RowName : RowNames)
    {
        if (const FFeatureDataRow *FeatureRow =
                FeatureDataTable->FindRow<FFeatureDataRow>(RowName, TEXT("GetAvailableChoiceNames")))
        {
            // Adiciona todos os nomes de escolhas disponíveis desta feature
            for (const FFeatureChoice &Choice : FeatureRow->AvailableChoices)
            {
                if (Choice.Name != NAME_None)
                {
                    UniqueChoices.Add(Choice.Name);
                }
            }
        }
    }

    // Converte TSet para TArray
    Result = UniqueChoices.Array();

    return Result;
}

/**
 * Retorna IDs de escolhas disponíveis filtrados por FC_ID de feature específica.
 * Apenas retorna IDs de escolhas da feature que corresponde ao FC_ID fornecido.
 * IDs são usados para referência da máquina (armazenados em AvailableChoices/SelectedChoices).
 * Usado para dropdown filtrado em FMulticlassClassFeature.AvailableChoices.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableChoiceIDsForFeature(const UDataTable *FeatureDataTable,
                                                                                   FName FeatureFC_ID)
{
    return FeatureChoiceHelpers::GetAvailableChoiceIDsForFeature(FeatureDataTable, FeatureFC_ID);
}

/**
 * Retorna nomes de escolhas disponíveis filtrados por FC_ID de feature específica.
 * Apenas retorna nomes de escolhas da feature que corresponde ao FC_ID fornecido.
 * Names são usados para exibição na UI (propriedades calculadas).
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableChoiceNamesForFeature(const UDataTable *FeatureDataTable,
                                                                                    FName FeatureFC_ID)
{
    return FeatureChoiceHelpers::GetAvailableChoiceNamesForFeature(FeatureDataTable, FeatureFC_ID);
}

#pragma endregion Feature Choice Options

// ============================================================================
// Skills Options
// ============================================================================
#pragma region Skills Options

/**
 * Retorna todos os nomes de skills de D&D 5e.
 * Usado para dropdown em FMulticlassSkills.available.
 * Nota: O handler filtrará baseado em InitialAvailable e Selected arrays.
 * Usa ProficiencyDataTable se fornecido (Data-Driven), caso contrário usa fallback hardcoded.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableSkills(const UDataTable *ProficiencyDataTable)
{
    return CharacterSheetHelpers::GetSkillNames(const_cast<UDataTable *>(ProficiencyDataTable));
}

#pragma endregion Skills Options
