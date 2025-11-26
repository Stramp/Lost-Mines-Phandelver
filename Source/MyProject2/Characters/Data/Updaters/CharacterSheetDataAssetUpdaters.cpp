// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetUpdaters.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Core/CharacterSheetCore.h"
#include "CreateSheet/Core/CharacterSheetData.h"
#include "CreateSheet/PointBuy/PointBuyResult.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/CalculationHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"

// Engine includes
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "UObject/UnrealType.h"
#endif

#pragma endregion Includes

// ============================================================================
// Calculated Fields Update
// ============================================================================
#pragma region Calculated Fields Update

/**
 * Atualiza campos calculados (proficiências, idiomas, etc.).
 * Nota: Proficiencies e Languages foram removidos do Data Asset.
 * Eles são calculados diretamente no CharacterDataComponent quando necessário.
 */
void FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Nota: bIsValidatingProperties deve ser gerenciado pelo caller (handler)
    // Esta função assume que a flag já está setada corretamente
    // Nota: Proficiencies e Languages foram removidos do Data Asset
    // Eles são calculados diretamente no CharacterDataComponent quando necessário
}

#pragma endregion Calculated Fields Update

// ============================================================================
// Language Choices Update
// ============================================================================
#pragma region Language Choices Update

/**
 * Atualiza detecção de escolhas de idiomas (bHasLanguageChoices, MaxLanguageChoices).
 * Detecta se raça/background/feat permite escolhas de idiomas.
 * Ajusta SelectedLanguages se o máximo diminuiu.
 */
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

#pragma endregion Language Choices Update

// ============================================================================
// Variant Human Flag Update
// ============================================================================
#pragma region Variant Human Flag Update

/**
 * Atualiza flag Variant Human e notifica editor se mudou.
 * Reseta escolhas de Variant Human se não for mais Variant Human.
 * Variant Human é uma SUB-RAÇA, não uma raça.
 */
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

#pragma endregion Variant Human Flag Update

// ============================================================================
// Subrace Flag Update
// ============================================================================
#pragma region Subrace Flag Update

/**
 * Atualiza flag de sub-raças disponíveis (bHasSubraces).
 * Detecta se a raça selecionada tem sub-raças disponíveis.
 * Reseta SelectedSubrace se não há mais sub-raças disponíveis.
 */
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

#pragma endregion Subrace Flag Update

// ============================================================================
// Sheet Visibility Update
// ============================================================================
#pragma region Sheet Visibility Update

/**
 * Atualiza visibilidade da ficha baseado na seleção de Data Tables.
 * Mostra todas as categorias quando todos os Data Tables são selecionados.
 * Mostra apenas Data Tables quando algum está faltando.
 */
void FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se todos os Data Tables foram selecionados
    bool bAllDataTablesSelected =
        Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr && Asset->FeatDataTable != nullptr;

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

#pragma endregion Sheet Visibility Update

// ============================================================================
// Final Scores Calculation
// ============================================================================
#pragma region Final Scores Calculation

void FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Cria estrutura de dados para o Core genérico
    FCharacterSheetData Data(Asset->PointBuyStrength, Asset->PointBuyDexterity, Asset->PointBuyConstitution,
                             Asset->PointBuyIntelligence, Asset->PointBuyWisdom, Asset->PointBuyCharisma,
                             Asset->SelectedRace, Asset->SelectedSubrace, Asset->CustomAbilityScoreChoices,
                             Asset->RaceDataTable, &Asset->FinalStrength, &Asset->FinalDexterity,
                             &Asset->FinalConstitution, &Asset->FinalIntelligence, &Asset->FinalWisdom,
                             &Asset->FinalCharisma);

    // Recalcula scores finais usando Core genérico (aplica todos os motores)
    FPointBuyResult PointBuyResult;
    FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

    // Atualiza pontos restantes
    Asset->PointsRemaining = PointBuyResult.PointsRemaining;

    // Se houve ajuste automático, atualiza alocação e loga aviso
    if (PointBuyResult.bWasAdjusted)
    {
        Asset->Modify();
        FCharacterSheetDataAssetHelpers::UpdatePointBuyFromAdjustedAllocation(Asset, PointBuyResult.AdjustedAllocation);
        UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: %s"), *PointBuyResult.FeedbackMessage);
    }
}

#pragma endregion Final Scores Calculation
