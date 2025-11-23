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

    // Resetar sub-raça se raça mudou
    // Seta flag antes de modificar para evitar re-disparar PostEditChangeProperty
    // e causar validação redundante
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
    {
        Asset->bIsValidatingProperties = true;
        Asset->SelectedSubrace = NAME_None;
        // Flag será limpa após ValidateAndUpdate() para proteger toda a operação
    }

    // ValidateAndUpdate() já chama UpdateRacialBonuses() e UpdateCalculatedFields()
    // Não precisa chamar separadamente para evitar redundância
    SafeValidateAndUpdate(Asset);

    // Limpa flag após validação completa
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
    {
        Asset->bIsValidatingProperties = false;
    }
}

void FCharacterSheetDataAssetHandlers::HandleAbilityScoresChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Seta flag para evitar recursão infinita ao modificar AbilityScores dentro de ValidateAndUpdate()
    Asset->bIsValidatingProperties = true;

    // ValidateAndUpdate() já chama ValidatePointBuy(), UpdateRacialBonuses() e UpdateCalculatedFields()
    // Não precisa chamar ValidatePointBuy() separadamente para evitar redundância
    SafeValidateAndUpdate(Asset);

    // Limpa flag após validação completa
    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleClassLevelsChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Seta flag para evitar recursão infinita ao modificar propriedades dentro de ValidateAndUpdate()
    Asset->bIsValidatingProperties = true;

    // ValidateAndUpdate() já chama ValidateTotalLevel() e UpdateCalculatedFields()
    // Não precisa chamar ValidateTotalLevel() separadamente para evitar redundância
    SafeValidateAndUpdate(Asset);

    // Limpa flag após validação completa
    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Seta flag para evitar recursão infinita ao modificar propriedades dentro de ValidateAndUpdate()
    Asset->bIsValidatingProperties = true;

    // ValidateAndUpdate() já chama UpdateCalculatedFields()
    SafeValidateAndUpdate(Asset);

    // Limpa flag após validação completa
    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Valida escolhas de Variant Human
    Asset->bIsValidatingProperties = true;
    SafeValidateAndUpdate(Asset);
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

        // TODO: Chamar update quando todos os Data Tables estiverem prontos
        // Asset->bIsValidatingProperties = true;
        // SafeValidateAndUpdate(Asset);
        // Asset->bIsValidatingProperties = false;
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

void FCharacterSheetDataAssetHandlers::SafeValidateAndUpdate(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->ValidateAndUpdate();
}
