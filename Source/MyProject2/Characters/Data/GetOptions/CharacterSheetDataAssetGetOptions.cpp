// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetGetOptions.h"

#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Tables/RaceDataTable.h"
#include "Utils/CharacterSheetHelpers.h"

#include "Engine/DataTable.h"
#include "Logging/LogMacros.h"

// ============================================================================
// Race and Background Section
// ============================================================================

TArray<FName> FCharacterSheetDataAssetGetOptions::GetRaceNames(const UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllRaceNames(const_cast<UDataTable *>(RaceDataTable));
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetSubraceNames(const UDataTable *RaceDataTable, FName SelectedRace)
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, const_cast<UDataTable *>(RaceDataTable));
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetBackgroundNames(const UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return {};
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(const_cast<UDataTable *>(BackgroundDataTable));
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNames()
{
    return CharacterSheetHelpers::GetAvailableLanguageNames();
}

TArray<FName> FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
    FName RaceName, FName SubraceName, FName BackgroundName, const TArray<FName> &SelectedLanguages,
    const UDataTable *RaceDataTable, const UDataTable *BackgroundDataTable)
{
    return CharacterSheetHelpers::GetAvailableLanguagesForChoice(
        RaceName, SubraceName, BackgroundName, SelectedLanguages, const_cast<UDataTable *>(RaceDataTable),
        const_cast<UDataTable *>(BackgroundDataTable));
}

// ============================================================================
// Point Buy Section
// ============================================================================

// --- Ability Scores ---
TArray<FName> FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames()
{
    return CharacterSheetHelpers::GetAbilityScoreNames();
}

// --- Skills ---
TArray<FName> FCharacterSheetDataAssetGetOptions::GetSkillNames() { return CharacterSheetHelpers::GetSkillNames(); }

// --- Feats ---
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

// ============================================================================
// Multiclass Section
// ============================================================================
TArray<FName> FCharacterSheetDataAssetGetOptions::GetListClassAvaible(const UDataTable *ClassDataTable,
                                                                      int32 FinalStrength, int32 FinalDexterity,
                                                                      int32 FinalConstitution, int32 FinalIntelligence,
                                                                      int32 FinalWisdom, int32 FinalCharisma)
{
    // ===== LOG: CALLER FAZENDO PRIMEIRA SOLICITAÇÃO PRO MOTOR =====
    UE_LOG(
        LogTemp, Warning,
        TEXT(
            "=== CALLER: CharacterSheetDataAssetGetOptions::GetListClassAvaible - PRIMEIRA SOLICITAÇÃO PRO MOTOR ==="));
    UE_LOG(LogTemp, Warning, TEXT("ClassDataTable: %s"), ClassDataTable ? *ClassDataTable->GetName() : TEXT("nullptr"));
    UE_LOG(LogTemp, Warning, TEXT("Atributos Finais:"));
    UE_LOG(LogTemp, Warning, TEXT("  STR: %d"), FinalStrength);
    UE_LOG(LogTemp, Warning, TEXT("  DEX: %d"), FinalDexterity);
    UE_LOG(LogTemp, Warning, TEXT("  CON: %d"), FinalConstitution);
    UE_LOG(LogTemp, Warning, TEXT("  INT: %d"), FinalIntelligence);
    UE_LOG(LogTemp, Warning, TEXT("  WIS: %d"), FinalWisdom);
    UE_LOG(LogTemp, Warning, TEXT("  CHA: %d"), FinalCharisma);
    UE_LOG(LogTemp, Warning, TEXT("================================================================"));
    // ===== FIM DO LOG =====

    if (!ClassDataTable)
    {
        return {};
    }

    // Retorna apenas nomes de classes do DataTable sem validação de requisitos
    return CharacterSheetHelpers::GetAllClassNames(const_cast<UDataTable *>(ClassDataTable));
}
