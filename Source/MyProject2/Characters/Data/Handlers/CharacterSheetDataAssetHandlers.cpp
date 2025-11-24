// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHandlers.h"
#include "../CharacterSheetDataAsset.h"
#include "../Validators/CharacterSheetDataAssetValidators.h"
#include "../Updaters/CharacterSheetDataAssetUpdaters.h"
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
        if (Asset->SelectedSubrace != NAME_None)
        {
            Asset->Modify(); // Marca objeto como modificado
            Asset->SelectedSubrace = NAME_None;
            // Não chama PostEditChangeProperty aqui para evitar recursão
            // A flag bIsValidatingProperties já protege contra re-disparo de handlers
        }
    }

    // Atualiza flag Variant Human e reseta escolhas se necessário
    FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(Asset);

    // Atualiza flag de sub-raças disponíveis
    FCharacterSheetDataAssetUpdaters::UpdateSubraceFlag(Asset);

    // Bônus raciais mudam quando raça/sub-raça muda
    FCharacterSheetDataAssetUpdaters::UpdateRacialBonuses(Asset);

    // Escolhas de idiomas podem mudar quando raça/sub-raça muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);

    // Proficiências de raça mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Motor de Point Buy: aplica alocação nos Final Scores e valida
    FCharacterSheetDataAssetUpdaters::UpdatePointBuyAllocation(Asset);

    // Valida Point Buy system (calcula PointsRemaining)
    FCharacterSheetDataAssetValidators::ValidatePointBuy(Asset);

    // Features podem depender de ability scores
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

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
    FCharacterSheetDataAssetValidators::ValidateTotalLevel(Asset);

    // Features de classe mudam com níveis
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Escolhas de idiomas podem mudar quando background muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);

    // Proficiências de background mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Valida escolhas de idiomas
    FCharacterSheetDataAssetValidators::ValidateLanguageChoices(Asset);

    // Recalcula idiomas finais
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

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
    FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(Asset);

    // Recalcula bônus raciais (Custom ASI afeta bônus)
    FCharacterSheetDataAssetUpdaters::UpdateRacialBonuses(Asset);

    // Recalcula proficiências (SelectedSkill do Variant Human afeta proficiências)
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);

    Asset->bIsValidatingProperties = false;
}

void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->bIsValidatingProperties = true;

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
    FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(Asset);

    // Log informativo sobre status dos Data Tables
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->ClassDataTable != nullptr &&
                                  Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

    if (bAllDataTablesSelected)
    {
        UE_LOG(LogTemp, Log,
               TEXT("CharacterSheetDataAsset: Todos os Data Tables foram selecionados! Todas as categorias estão "
                    "visíveis."));
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

    Asset->bIsValidatingProperties = false;
}

// ============================================================================
// Wrapper Functions for Property Handler Map
// ============================================================================
// These wrapper functions are used as C-style function pointers in the
// PropertyHandlers map. They provide a consistent signature for all handlers.

void FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleRaceChange(Asset, PropertyName);
}

void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandlePointBuyAllocationChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleClassLevelsWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleClassLevelsChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper(UCharacterSheetDataAsset *Asset,
                                                                       FName PropertyName)
{
    HandleBackgroundChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper(UCharacterSheetDataAsset *Asset,
                                                                        FName PropertyName)
{
    HandleVariantHumanChoicesChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleLanguageChoicesChange(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleDataTableWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleDataTableChange(Asset);
}
