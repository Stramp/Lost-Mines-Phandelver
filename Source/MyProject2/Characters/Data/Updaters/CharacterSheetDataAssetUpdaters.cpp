// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetUpdaters.h"
#include "../CharacterSheetDataAsset.h"
#include "../Helpers/CharacterSheetDataAssetHelpers.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "../../../Utils/CalculationHelpers.h"
#include "../../../Data/Tables/RaceDataTable.h"
#include "../../../Data/Tables/ClassDataTable.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "UObject/UnrealType.h"
#endif

void FCharacterSheetDataAssetUpdaters::UpdateRacialBonuses(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Nota: bIsValidatingProperties deve ser gerenciado pelo caller (handler)
    // Esta função assume que a flag já está setada corretamente

    if (!Asset->RaceDataTable || Asset->SelectedRace == NAME_None)
    {
        // Resetar bônus raciais se não há raça selecionada
        for (auto &Pair : Asset->AbilityScores)
        {
            Pair.Value.RacialBonus = 0;
            Pair.Value.FinalScore = Pair.Value.BaseScore;
        }
        return;
    }

    // Resetar todos os bônus primeiro
    for (auto &Pair : Asset->AbilityScores)
    {
        Pair.Value.RacialBonus = 0;
    }

    // Busca dados da raça base no Data Table
    // Otimização: Assumindo que RowName = RaceName no JSON, podemos usar FindRow diretamente
    // Se não encontrar, faz busca O(n) como fallback
    FRaceDataRow *RaceRow =
        Asset->RaceDataTable->FindRow<FRaceDataRow>(Asset->SelectedRace, TEXT("UpdateRacialBonuses"));

    // Fallback: Se FindRow não encontrou, pode ser que RowName != RaceName, então busca manual
    if (!RaceRow)
    {
        TArray<FName> RowNames = Asset->RaceDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FRaceDataRow *Row = Asset->RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
            {
                if (Row->RaceName == Asset->SelectedRace)
                {
                    RaceRow = Row;
                    break;
                }
            }
        }
    }

    // Se a raça não foi encontrada no Data Table, resetar bônus para evitar estado inconsistente
    if (!RaceRow)
    {
        for (auto &Pair : Asset->AbilityScores)
        {
            Pair.Value.RacialBonus = 0;
            Pair.Value.FinalScore = Pair.Value.BaseScore;
        }
        return;
    }

    // Busca sub-raça se necessário
    FRaceDataRow *SubraceRow = nullptr;
    if (Asset->SelectedSubrace != NAME_None)
    {
        // Validar se a sub-raça pertence à raça selecionada
        bool bSubraceValid = RaceRow->SubraceNames.Contains(Asset->SelectedSubrace);

        if (!bSubraceValid)
        {
            UE_LOG(LogTemp, Warning, TEXT("Subrace '%s' não pertence à raça '%s'. Resetando sub-raça."),
                   *Asset->SelectedSubrace.ToString(), *Asset->SelectedRace.ToString());

            // Marca objeto como modificado antes de alterar propriedade
            Asset->Modify();
            Asset->SelectedSubrace = NAME_None;
            // Não chama PostEditChangeProperty aqui para evitar recursão
            // A flag bIsValidatingProperties já protege contra re-disparo de handlers
        }
        else
        {
            // Busca direta da sub-raça (otimização)
            SubraceRow =
                Asset->RaceDataTable->FindRow<FRaceDataRow>(Asset->SelectedSubrace, TEXT("UpdateRacialBonuses"));

            // Fallback: busca manual se FindRow não encontrou
            if (!SubraceRow)
            {
                TArray<FName> RowNames = Asset->RaceDataTable->GetRowNames();
                for (const FName &RowName : RowNames)
                {
                    if (FRaceDataRow *Row =
                            Asset->RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
                    {
                        if (Row->RaceName == Asset->SelectedSubrace)
                        {
                            SubraceRow = Row;
                            break;
                        }
                    }
                }
            }

            if (!SubraceRow)
            {
                UE_LOG(LogTemp, Warning, TEXT("Subrace '%s' not found in RaceDataTable"),
                       *Asset->SelectedSubrace.ToString());
            }
        }
    }

    // Usa CalculationHelpers para calcular bônus raciais (função pura)
    TMap<FName, int32> RacialBonuses;
    CalculationHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, Asset->CustomAbilityScoreChoices, RacialBonuses);

    // Aplica bônus calculados ao Asset
    for (const auto &BonusPair : RacialBonuses)
    {
        if (FAbilityScoreEntry *Entry = Asset->AbilityScores.Find(BonusPair.Key))
        {
            Entry->RacialBonus = BonusPair.Value;
        }
    }

    // Atualizar scores finais após aplicar bônus da raça e sub-raça
    for (auto &Pair : Asset->AbilityScores)
    {
        Pair.Value.FinalScore =
            CalculationHelpers::CalculateFinalAbilityScore(Pair.Value.BaseScore, Pair.Value.RacialBonus, 0);
    }
}

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

    // Usa CalculationHelpers para calcular features disponíveis (função pura)
    Asset->AvailableFeatures =
        CalculationHelpers::CalculateAvailableFeatures(Asset->ClassLevels, Asset->ClassDataTable);

    // TODO: Adicionar proficiências de raça, classe e background quando necessário
    // Por enquanto, apenas estrutura preparada
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
    if (Asset->bIsVariantHuman != bNewIsVariantHuman)
    {
        Asset->bIsVariantHuman = bNewIsVariantHuman;

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bIsVariantHuman
        if (GIsEditor && !Asset->bIsValidatingProperties)
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(
                    Asset->GetClass(), GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bIsVariantHuman)))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Reseta escolhas se não for Variant Human
    if (!Asset->bIsVariantHuman)
    {
        FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(Asset);
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

    if (Asset->bCanShowSheet != bNewCanShowSheet)
    {
        Asset->bCanShowSheet = bNewCanShowSheet;

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        if (GIsEditor && !Asset->bIsValidatingProperties)
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(
                    Asset->GetClass(), GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bCanShowSheet)))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }
}
