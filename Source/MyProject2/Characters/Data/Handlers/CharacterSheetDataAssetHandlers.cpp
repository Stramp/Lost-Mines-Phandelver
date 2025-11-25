// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetHandlers.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"
#include "Characters/Data/Helpers/ValidationGuard.h"
#include "CreateSheet/PointBuy/PointBuyValidator.h"
#include "CreateSheet/Multiclassing/MulticlassingMotor.h"
#include "Logging/LogMacros.h"
#include "UObject/UnrealType.h"

void FCharacterSheetDataAssetHandlers::HandleRaceChange(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

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
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    Asset->RecalculateFinalScoresFromDataAsset();

    // Escolhas de idiomas podem mudar quando raça/sub-raça muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);

    // Proficiências de raça mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

void FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Motor de Point Buy: aplica alocação nos Final Scores
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    Asset->RecalculateFinalScoresFromDataAsset();

    // Valida Point Buy system (calcula PointsRemaining)
    FPointBuyValidator::ValidatePointBuy(Asset);

    // Features podem depender de ability scores
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleBackgroundChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Escolhas de idiomas podem mudar quando background muda
    FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(Asset);

    // Proficiências de background mudam
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleLanguageChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de idiomas
    FCharacterSheetDataAssetValidators::ValidateLanguageChoices(Asset);

    // Recalcula idiomas finais
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Valida escolhas de Variant Human
    FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(Asset);

    // Recalcula bônus raciais (Custom ASI afeta bônus)
    // Usa Core genérico via helper do Data Asset (aplica todos os motores)
    Asset->RecalculateFinalScoresFromDataAsset();

    // Recalcula proficiências (SelectedSkill do Variant Human afeta proficiências)
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(Asset);
}

void FCharacterSheetDataAssetHandlers::HandleDataTableChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // RAII Guard: gerencia bIsValidatingProperties automaticamente
    FValidationGuard Guard(Asset);

    // Atualiza visibilidade da ficha baseado na seleção de Data Tables
    FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(Asset);

    // Log informativo sobre status dos Data Tables
    bool bAllDataTablesSelected =
        Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

    if (bAllDataTablesSelected)
    {
        UE_LOG(LogTemp, Log,
               TEXT("CharacterSheetDataAsset: Todos os Data Tables foram selecionados! Todas as categorias estão "
                    "visíveis."));
    }
    else
    {
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: Ainda faltam Data Tables. Race: %s, Background: %s, Feat: %s"),
               Asset->RaceDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->BackgroundDataTable ? TEXT("OK") : TEXT("FALTANDO"),
               Asset->FeatDataTable ? TEXT("OK") : TEXT("FALTANDO"));
    }
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

void FCharacterSheetDataAssetHandlers::HandleMultClassChange(UCharacterSheetDataAsset *Asset)
{
    if (!Asset || Asset->IsValidatingProperties() || !Asset->ClassDataTable)
    {
        return;
    }

    FValidationGuard Guard(Asset);

    // Obtém classes disponíveis do motor
    TArray<FClassOption> ClassOptions = FMulticlassingMotor::GetAvailableClasses(
        Asset->ClassDataTable, Asset->FinalStrength, Asset->FinalDexterity, Asset->FinalConstitution,
        Asset->FinalIntelligence, Asset->FinalWisdom, Asset->FinalCharisma);

    // Cria mapa rápido para lookup (ClassName -> RequirementMessage)
    TMap<FName, FString> RequirementMap;
    for (const FClassOption &Option : ClassOptions)
    {
        RequirementMap.Add(Option.ClassName, Option.RequirementMessage);
    }

    // Valida cada entrada em MultClass
    bool bNeedsReset = false;
    for (FMultClass &ClassEntry : Asset->MultClass)
    {
        if (ClassEntry.ClassName == NAME_None)
        {
            continue; // Ignora entradas vazias
        }

        // Remove prefixo se existir (formato: "[REQ X Y] ClassName")
        FString ClassNameStr = ClassEntry.ClassName.ToString();
        if (ClassNameStr.StartsWith(TEXT("[")))
        {
            // Extrai nome real da classe (tudo após o último espaço)
            int32 LastSpaceIndex = ClassNameStr.Find(TEXT(" "), ESearchCase::CaseSensitive, ESearchDir::FromEnd);
            if (LastSpaceIndex != INDEX_NONE)
            {
                ClassNameStr = ClassNameStr.RightChop(LastSpaceIndex + 1);
                ClassEntry.ClassName = FName(*ClassNameStr);
            }
        }

        // Verifica se classe está disponível (RequirementMessage vazio = disponível)
        FString *RequirementMessage = RequirementMap.Find(ClassEntry.ClassName);
        if (!RequirementMessage || !RequirementMessage->IsEmpty())
        {
            // Classe não disponível (RequirementMessage preenchido): reseta para NAME_None
            ClassEntry.ClassName = NAME_None;
            bNeedsReset = true;
        }
    }

    if (bNeedsReset)
    {
        Asset->Modify(); // Marca como modificado no editor
    }
}

void FCharacterSheetDataAssetHandlers::HandleMultClassWrapper(UCharacterSheetDataAsset *Asset, FName PropertyName)
{
    HandleMultClassChange(Asset);
}
