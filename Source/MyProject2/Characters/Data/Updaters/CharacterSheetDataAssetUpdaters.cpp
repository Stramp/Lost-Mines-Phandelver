// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetUpdaters.h"
#include "../CharacterSheetDataAsset.h"
#include "../Helpers/CharacterSheetDataAssetHelpers.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "../../../Utils/CalculationHelpers.h"
#include "../../../Data/Tables/RaceDataTable.h"
#include "../../../Data/Tables/ClassDataTable.h"
#include "../../../Data/Tables/BackgroundDataTable.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "UObject/UnrealType.h"
#endif

void FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Nota: bIsValidatingProperties deve ser gerenciado pelo caller (handler)
    // Esta função assume que a flag já está setada corretamente

    Asset->AvailableFeatures.Empty();
    Asset->Proficiencies.Empty();
    Asset->Languages.Empty();

    // Usa CalculationHelpers para calcular features disponíveis (função pura)
    Asset->AvailableFeatures =
        CalculationHelpers::CalculateAvailableFeatures(Asset->ClassLevels, Asset->ClassDataTable);

    // Usa CalculationHelpers para calcular proficiências (raça, classe, background e Variant Human skill)
    Asset->Proficiencies = CalculationHelpers::CalculateProficiencies(
        Asset->SelectedRace, Asset->SelectedSubrace, Asset->ClassLevels, Asset->SelectedBackground,
        Asset->SelectedSkill, Asset->RaceDataTable, Asset->ClassDataTable, Asset->BackgroundDataTable);

    // Usa CalculationHelpers para calcular idiomas finais (raça + background + escolhas do jogador)
    Asset->Languages = CalculationHelpers::CalculateLanguages(Asset->SelectedRace, Asset->SelectedSubrace,
                                                              Asset->SelectedBackground, Asset->SelectedLanguages,
                                                              Asset->RaceDataTable, Asset->BackgroundDataTable);
}

void FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->SetHasLanguageChoices(false);
    Asset->MaxLanguageChoices = 0;

    int32 RaceLanguageCount = 0;
    int32 BackgroundLanguageCount = 0;

    // Verifica escolhas de idiomas da raça/sub-raça
    if (Asset->RaceDataTable)
    {
        CharacterSheetHelpers::HasLanguageChoiceFromRace(Asset->SelectedRace, Asset->SelectedSubrace,
                                                         Asset->RaceDataTable, RaceLanguageCount);
    }

    // Verifica escolhas de idiomas do background
    if (Asset->BackgroundDataTable)
    {
        CharacterSheetHelpers::HasLanguageChoiceFromBackground(Asset->SelectedBackground, Asset->BackgroundDataTable,
                                                               BackgroundLanguageCount);
    }

    // Soma total de escolhas disponíveis (raça + background)
    // NOTA: Futuramente, quando feats forem implementados, adicionar aqui também
    Asset->MaxLanguageChoices = RaceLanguageCount + BackgroundLanguageCount;
    bool bNewHasLanguageChoices = (Asset->MaxLanguageChoices > 0);

    // Ajusta array SelectedLanguages se o máximo diminuiu
    // Remove itens extras do final quando MaxLanguageChoices < SelectedLanguages.Num()
    if (Asset->SelectedLanguages.Num() > Asset->MaxLanguageChoices)
    {
        Asset->Modify(); // Marca objeto como modificado

        int32 ItemsToRemove = Asset->SelectedLanguages.Num() - Asset->MaxLanguageChoices;
        Asset->SelectedLanguages.SetNum(Asset->MaxLanguageChoices);

        UE_LOG(LogTemp, Log, TEXT("UpdateLanguageChoices: Removidos %d idioma(s) do array (máximo permitido: %d)"),
               ItemsToRemove, Asset->MaxLanguageChoices);
    }

    // Atualiza flag bHasLanguageChoices e notifica editor se mudou
    if (Asset->GetHasLanguageChoices() != bNewHasLanguageChoices)
    {
        Asset->SetHasLanguageChoices(bNewHasLanguageChoices);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bHasLanguageChoices
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property =
                    FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bHasLanguageChoices"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Se não há mais escolhas disponíveis, limpa SelectedLanguages
    if (!Asset->GetHasLanguageChoices())
    {
        Asset->SelectedLanguages.Empty();
    }
}

void FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Atualiza flag bIsVariantHuman e notifica editor se mudou
    // Variant Human é uma SUB-RAÇA, não uma raça
    bool bNewIsVariantHuman = (Asset->SelectedSubrace == TEXT("Variant Human"));
    if (Asset->GetIsVariantHuman() != bNewIsVariantHuman)
    {
        Asset->SetIsVariantHuman(bNewIsVariantHuman);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bIsVariantHuman
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bIsVariantHuman"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Reseta escolhas se não for Variant Human
    if (!Asset->GetIsVariantHuman())
    {
        FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(Asset);
    }
}

void FCharacterSheetDataAssetUpdaters::UpdateSubraceFlag(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se a raça selecionada tem sub-raças disponíveis
    bool bNewHasSubraces = false;
    if (Asset->RaceDataTable && Asset->SelectedRace != NAME_None)
    {
        TArray<FName> AvailableSubraces =
            CharacterSheetHelpers::GetAvailableSubraces(Asset->SelectedRace, Asset->RaceDataTable);
        bNewHasSubraces = (AvailableSubraces.Num() > 0);
    }

    // Atualiza flag bHasSubraces e notifica editor se mudou
    if (Asset->GetHasSubraces() != bNewHasSubraces)
    {
        Asset->SetHasSubraces(bNewHasSubraces);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bHasSubraces
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bHasSubraces"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Se não há mais sub-raças disponíveis, reseta SelectedSubrace
    if (!Asset->GetHasSubraces() && Asset->SelectedSubrace != NAME_None)
    {
        Asset->Modify();
        Asset->SelectedSubrace = NAME_None;
    }
}

void FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se todos os Data Tables foram selecionados
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->ClassDataTable != nullptr &&
                                  Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

    // bCanShowSheet = false significa mostrar todas as categorias
    // bCanShowSheet = true significa mostrar apenas Data Tables
    bool bNewCanShowSheet = !bAllDataTablesSelected;

    if (Asset->GetCanShowSheet() != bNewCanShowSheet)
    {
        Asset->SetCanShowSheet(bNewCanShowSheet);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bCanShowSheet"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }
}
