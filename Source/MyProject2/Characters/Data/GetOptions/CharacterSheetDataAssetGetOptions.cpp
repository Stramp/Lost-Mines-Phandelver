// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetGetOptions.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"

// Project includes - CreateSheet Motors
#include "CreateSheet/Multiclass/MulticlassMotor.h"

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
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNames()
{
    return CharacterSheetHelpers::GetAvailableLanguageNames();
}

/**
 * Retorna idiomas disponíveis para escolha baseado em raça, sub-raça e background.
 * Exclui idiomas já selecionados.
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
    FName RaceName, FName SubraceName, FName BackgroundName, const TArray<FName> &SelectedLanguages,
    const UDataTable *RaceDataTable, const UDataTable *BackgroundDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguagesForChoice(
        RaceName, SubraceName, BackgroundName, SelectedLanguages, const_cast<UDataTable *>(RaceDataTable),
        const_cast<UDataTable *>(BackgroundDataTable));
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
 */
TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames()
{
    return CharacterSheetHelpers::GetSkillNames();
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
