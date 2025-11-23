// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetValidators.h"
#include "../CharacterSheetDataAsset.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "Logging/LogMacros.h"

void FCharacterSheetDataAssetValidators::ValidatePointBuy(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Calcula pontos gastos usando helper
    TMap<FName, int32> BaseScores;
    for (const auto &Pair : Asset->AbilityScores)
    {
        BaseScores.Add(Pair.Key, Pair.Value.BaseScore);
    }

    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    Asset->PointsRemaining = 27 - TotalCost;

    // Validação D&D 5e Point Buy: exatamente 27 pontos devem ser gastos
    // PointsRemaining deve ser 0 para alocação válida
    // Não clampa silenciosamente - mantém o valor real para indicar estado inválido
    // Validação adicional: todos os scores devem estar entre 8 e 15
    bool bAllScoresValid = true;
    for (const auto &Pair : Asset->AbilityScores)
    {
        if (Pair.Value.BaseScore < 8 || Pair.Value.BaseScore > 15)
        {
            bAllScoresValid = false;
            break;
        }
    }

    // Log de aviso se scores estão fora do range válido
    if (!bAllScoresValid)
    {
        UE_LOG(LogTemp, Warning,
               TEXT("CharacterSheetDataAsset: Alguns ability scores estão fora do range válido [8, 15]"));
    }

    // Se PointsRemaining != 0 ou scores inválidos, a alocação está incorreta
    // PointsRemaining negativo = pontos excedidos (mais de 27 gastos)
    // PointsRemaining positivo = pontos não gastos (menos de 27 gastos)
    // Não clampa para evitar mascarar estado inválido
}

void FCharacterSheetDataAssetValidators::ValidateTotalLevel(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Calcula nível total usando helper
    Asset->TotalLevel = CharacterSheetHelpers::CalculateTotalLevel(Asset->ClassLevels);

    // Validação: nível total não pode exceder 20
    if (Asset->TotalLevel > 20)
    {
        Asset->TotalLevel = 20;

        // Nota: bIsValidatingProperties deve ser gerenciado pelo caller (handler)
        // Esta função assume que a flag já está setada corretamente

        // Ajusta níveis das classes para não exceder 20
        int32 RemainingLevels = 20;
        for (FClassLevelEntry &Entry : Asset->ClassLevels)
        {
            if (RemainingLevels <= 0)
            {
                Entry.Level = 0;
            }
            else if (Entry.Level > RemainingLevels)
            {
                Entry.Level = RemainingLevels;
            }
            RemainingLevels -= Entry.Level;
        }
    }
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset || !Asset->bIsVariantHuman)
    {
        return;
    }

    ValidateVariantHumanAbilityScoreChoices(Asset);
    ValidateVariantHumanFeat(Asset);
    ValidateVariantHumanSkill(Asset);
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanAbilityScoreChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Validar CustomAbilityScoreChoices: deve ser possivel adicionar até 2 atributos, dando +1 a cada atributo
    // escolhido. Se o numero de atributos escolhidos for somente 1, deve se adicionar +2 para o unico atributo
    // escolhido. Se escolher 2 atributos, deve se adicionar +1 para cada atributo escolhido.
    if (Asset->CustomAbilityScoreChoices.Num() > 2)
    {
        // Ajusta para ter no maximo 2 elementos
        Asset->CustomAbilityScoreChoices.SetNum(2);
    }

    // Validar que os atributos escolhidos são válidos
    TArray<FName> ValidAbilityNames = Asset->GetAbilityScoreNames();
    for (FName &AbilityName : Asset->CustomAbilityScoreChoices)
    {
        if (AbilityName != NAME_None && !ValidAbilityNames.Contains(AbilityName))
        {
            AbilityName = TEXT("Strength"); // Valor padrão se inválido
        }
    }
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanFeat(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Validar SelectedFeat (deve estar na lista de feats disponíveis)
    if (Asset->SelectedFeat != NAME_None && Asset->FeatDataTable)
    {
        TArray<FName> AvailableFeats = Asset->GetAvailableFeatNames();
        if (!AvailableFeats.Contains(Asset->SelectedFeat))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedFeat '%s' não está disponível. Resetando."),
                   *Asset->SelectedFeat.ToString());
            Asset->SelectedFeat = NAME_None;
        }
    }
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanSkill(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Validar SelectedSkill (deve estar na lista de skills válidas)
    if (Asset->SelectedSkill != NAME_None)
    {
        TArray<FName> ValidSkills = Asset->GetSkillNames();
        if (!ValidSkills.Contains(Asset->SelectedSkill))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedSkill '%s' não é válido. Resetando."),
                   *Asset->SelectedSkill.ToString());
            Asset->SelectedSkill = NAME_None;
        }
    }
}
