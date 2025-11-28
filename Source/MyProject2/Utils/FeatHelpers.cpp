// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/DnDConstants.h"

// Project includes - Data Tables
#include "Data/Tables/FeatDataTable.h"

#pragma endregion Includes

// ============================================================================
// Feat Data Table Helpers
// ============================================================================
#pragma region Feat Data Table Helpers

bool CharacterSheetHelpers::CanTakeFeatAtLevel(int32 TotalLevel)
{
    // Em D&D 5e, feats podem ser escolhidos nos níveis 4, 8, 12, 16, 19 (ou ao invés de ASI)
    for (int32 i = 0; i < DnDConstants::NUM_FEAT_LEVELS; ++i)
    {
        if (DnDConstants::FEAT_LEVELS[i] == TotalLevel)
        {
            return true;
        }
    }
    return false;
}

bool CharacterSheetHelpers::ValidateAbilityScorePrerequisite(const FName &Prerequisite,
                                                             const TMap<FName, int32> &AbilityScores)
{
    if (Prerequisite == NAME_None)
    {
        return true; // Pré-requisito vazio é considerado válido
    }

    // Converte FName para FString para parsing
    FString PrerequisiteStr = Prerequisite.ToString();

    // Usa helper global para obter lista de ability scores válidos
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();

    // Tenta parsear formato "AbilityName Score"
    for (const FName &AbilityName : AbilityNames)
    {
        FString AbilityNameStr = AbilityName.ToString();
        if (PrerequisiteStr.StartsWith(AbilityNameStr))
        {
            // Remove o nome do ability e espaços
            FString ScoreStr = PrerequisiteStr.RightChop(AbilityNameStr.Len()).TrimStart();

            // Tenta converter para número
            int32 RequiredScore = 0;
            if (LexTryParseString(RequiredScore, *ScoreStr))
            {
                // Pré-requisito foi parseado com sucesso: ability name encontrado e score parseado
                // Se o ability não está no map, retorna false (dados faltando ou não inicializados)
                if (const int32 *CurrentScore = AbilityScores.Find(AbilityName))
                {
                    return *CurrentScore >= RequiredScore;
                }
                else
                {
                    // Ability score não encontrado no map - pré-requisito não pode ser atendido
                    return false;
                }
            }
        }
    }

    // Se não for um pré-requisito de ability score reconhecido,
    // assume que é outro tipo (proficiência, etc.) e retorna true
    // TODO: Implementar validação de outros tipos de pré-requisitos quando necessário
    return true;
}

bool CharacterSheetHelpers::MeetsFeatPrerequisites(const FFeatDataRow *Row, const TMap<FName, int32> &AbilityScores)
{
    if (!Row)
    {
        return false;
    }

    // Extrai pré-requisitos de FeatureData usando helper
    TArray<FName> Prerequisites = Row->GetPrerequisites();

    // Se não há pré-requisitos, o feat está disponível
    if (Prerequisites.Num() == 0)
    {
        return true;
    }

    // Valida cada pré-requisito
    // Todos os pré-requisitos devem ser atendidos (AND lógico)
    for (const FName &Prerequisite : Prerequisites)
    {
        if (!ValidateAbilityScorePrerequisite(Prerequisite, AbilityScores))
        {
            return false; // Se qualquer pré-requisito falhar, o feat não está disponível
        }
    }

    return true; // Todos os pré-requisitos foram atendidos
}

TArray<FName> CharacterSheetHelpers::GetAvailableFeats(int32 TotalLevel, const TMap<FName, int32> &AbilityScores,
                                                       UDataTable *FeatDataTable)
{
    if (!FeatDataTable || TotalLevel < DnDConstants::MIN_LEVEL)
    {
        return TArray<FName>();
    }

    if (!CharacterSheetHelpers::CanTakeFeatAtLevel(TotalLevel))
    {
        return TArray<FName>();
    }

    TSet<FName> AvailableFeatsSet;
    TArray<FName> RowNames = FeatDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatDataRow *Row = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("GetAvailableFeats")))
        {
            // Usa FC_ID como identificador principal, fallback para Name
            FName FeatIdentifier = Row->ID != NAME_None ? Row->ID : Row->Name;
            if (FeatIdentifier == NAME_None)
            {
                continue;
            }

            if (CharacterSheetHelpers::MeetsFeatPrerequisites(Row, AbilityScores))
            {
                AvailableFeatsSet.Add(FeatIdentifier);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para feats)
    return AvailableFeatsSet.Array();
}

TArray<FName> CharacterSheetHelpers::GetAvailableFeatsForVariantHuman(const TMap<FName, int32> &AbilityScores,
                                                                      UDataTable *FeatDataTable)
{
    if (!FeatDataTable)
    {
        return TArray<FName>();
    }

    // Variant Human pode escolher feat no nível 1 (bypassa verificação de nível)
    // Ainda valida pré-requisitos de ability scores
    // IMPORTANTE: Retorna Name (não FC_ID) para exibição legível no dropdown
    TSet<FName> AvailableFeatsSet;
    TArray<FName> RowNames = FeatDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatDataRow *Row = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("GetAvailableFeatsForVariantHuman")))
        {
            // Retorna Name para exibição legível no dropdown (ex: "Magic Initiate" ao invés de "Feat_MagicInitiate")
            if (Row->Name == NAME_None)
            {
                continue;
            }

            // Valida apenas pré-requisitos de ability scores (sem verificação de nível)
            if (CharacterSheetHelpers::MeetsFeatPrerequisites(Row, AbilityScores))
            {
                AvailableFeatsSet.Add(Row->Name);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para feats)
    return AvailableFeatsSet.Array();
}

#pragma endregion Feat Data Table Helpers

