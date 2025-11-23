// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAssetValidators.h"
#include "../CharacterSheetDataAsset.h"
#include "../../../Utils/CharacterSheetHelpers.h"
#include "../../../Utils/ValidationHelpers.h"
#include "Logging/LogMacros.h"

void FCharacterSheetDataAssetValidators::ValidatePointBuy(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Extrai base scores para validação
    TMap<FName, int32> BaseScores;
    for (const auto &Pair : Asset->AbilityScores)
    {
        BaseScores.Add(Pair.Key, Pair.Value.BaseScore);
    }

    // Usa ValidationHelpers para validar e calcular pontos restantes
    int32 PointsRemaining = 0;
    bool bAllScoresValid = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining, 27);
    Asset->PointsRemaining = PointsRemaining;

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

    // Usa ValidationHelpers para calcular e validar nível total
    int32 TotalLevel = 0;
    bool bIsValid = ValidationHelpers::ValidateTotalLevel(Asset->ClassLevels, TotalLevel, 20);
    Asset->TotalLevel = TotalLevel;

    // Se nível total exceder 20, ajusta níveis das classes
    // Nota: Ajuste de níveis individuais deve ficar no validator acoplado (modifica Asset)
    if (!bIsValid && Asset->TotalLevel > 20)
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

    // Usa ValidationHelpers para validar escolhas de ability scores
    TArray<FName> ValidAbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    ValidationHelpers::ValidateAbilityScoreChoices(Asset->CustomAbilityScoreChoices, ValidAbilityNames, 2);
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanFeat(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Usa ValidationHelpers para validar seleção de feat
    if (Asset->FeatDataTable)
    {
        TArray<FName> AvailableFeats = Asset->GetAvailableFeatNames();
        if (!ValidationHelpers::ValidateFeatSelection(Asset->SelectedFeat, AvailableFeats))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedFeat não está disponível. Resetando."));
        }
    }
}

void FCharacterSheetDataAssetValidators::ValidateVariantHumanSkill(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Usa ValidationHelpers para validar seleção de skill
    TArray<FName> ValidSkills = Asset->GetSkillNames();
    if (!ValidationHelpers::ValidateSkillSelection(Asset->SelectedSkill, ValidSkills))
    {
        UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedSkill não é válido. Resetando."));
    }
}
