// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHandlers.h"
#include "../CharacterSheetDataAsset.h"
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"

void FCharacterSheetDataAssetHandlers::HandleRaceChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Resetar sub-raça se raça mudou
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
    {
        Asset->SelectedSubrace = NAME_None;
    }

    // Atualiza flag Variant Human e reseta escolhas se necessário
    Asset->UpdateVariantHumanFlag();

    // Bônus raciais mudam quando raça/sub-raça muda
    Asset->UpdateRacialBonuses();

    // Proficiências de raça mudam
    Asset->UpdateCalculatedFields();

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleAbilityScoresChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Valida Point Buy system
    Asset->ValidatePointBuy();

    // Recalcula bônus raciais (depende de base scores)
    Asset->UpdateRacialBonuses();

    // Features podem depender de ability scores
    Asset->UpdateCalculatedFields();

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleClassLevelsChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Valida nível total (máximo 20)
    Asset->ValidateTotalLevel();

    // Features de classe mudam com níveis
    Asset->UpdateCalculatedFields();

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Apenas proficiências de background mudam
    Asset->UpdateCalculatedFields();

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Valida escolhas de Variant Human
    Asset->ValidateVariantHumanChoices();

    // Recalcula bônus raciais (Custom ASI afeta bônus)
    Asset->UpdateRacialBonuses();

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se todos os Data Tables foram selecionados
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->ClassDataTable != nullptr &&
                                  Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

    if (bAllDataTablesSelected)
    {
        UE_LOG(LogTemp, Log, TEXT("CharacterSheetDataAsset: Todos os Data Tables foram selecionados!"));

        // Quando todos os Data Tables estão prontos, atualiza tudo
        Asset->bIsValidatingProperties = true;
        Asset->ValidateAndUpdate(); // Orquestrador completo quando necessário
        Asset->bIsValidatingProperties = false;
    }
    else
    {
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: Ainda faltam Data Tables. Race: %s, Class: %s, Background: %s, Feat: %s"),
               Asset->RaceDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->ClassDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->BackgroundDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->FeatDataTable ? TEXT("OK") : TEXT("FALTANDO"));
    }
}
