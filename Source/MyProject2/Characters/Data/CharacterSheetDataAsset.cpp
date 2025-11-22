// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAsset.h"
#include "../../Utils/CharacterSheetHelpers.h"
#include "../../Data/Tables/RaceDataTable.h"
#include "../../Data/Tables/ClassDataTable.h"
#include "../../Data/Tables/BackgroundDataTable.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "PropertyEditorModule.h"
#endif

UCharacterSheetDataAsset::UCharacterSheetDataAsset()
{
    // Inicializa ability scores padrão (todos começam em 8)
    TArray<FName> AbilityNames = {TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                                  TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
    for (const FName &AbilityName : AbilityNames)
    {
        FAbilityScoreEntry Entry;
        Entry.BaseScore = 8;
        Entry.FinalScore = 8;
        AbilityScores.Add(AbilityName, Entry);
    }

    PointsRemaining = 27;
    TotalLevel = 0;
}

#if WITH_EDITOR
void UCharacterSheetDataAsset::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Evita recursão infinita: se já estamos validando propriedades, não re-dispara validações
    if (bIsValidatingProperties)
    {
        return;
    }

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    FName PropertyName = PropertyChangedEvent.Property->GetFName();

    // Valida e atualiza quando propriedades relevantes mudam
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace))
    {
        // Resetar sub-raça se raça mudou
        if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace))
        {
            SelectedSubrace = NAME_None;
        }

        // ValidateAndUpdate() já chama UpdateRacialBonuses() e UpdateCalculatedFields()
        // Não precisa chamar separadamente para evitar redundância
        ValidateAndUpdate();
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, AbilityScores))
    {
        // ValidateAndUpdate() já chama ValidatePointBuy(), UpdateRacialBonuses() e UpdateCalculatedFields()
        // Não precisa chamar ValidatePointBuy() separadamente para evitar redundância
        ValidateAndUpdate();
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassLevels))
    {
        // ValidateAndUpdate() já chama ValidateTotalLevel() e UpdateCalculatedFields()
        // Não precisa chamar ValidateTotalLevel() separadamente para evitar redundância
        ValidateAndUpdate();
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground))
    {
        // ValidateAndUpdate() já chama UpdateCalculatedFields()
        ValidateAndUpdate();
    }
}

void UCharacterSheetDataAsset::ValidateAndUpdate()
{
    ValidatePointBuy();
    ValidateTotalLevel();
    UpdateRacialBonuses();
    UpdateCalculatedFields();
}

void UCharacterSheetDataAsset::ValidatePointBuy()
{
    // Calcula pontos gastos usando helper
    TMap<FName, int32> BaseScores;
    for (const auto &Pair : AbilityScores)
    {
        BaseScores.Add(Pair.Key, Pair.Value.BaseScore);
    }

    int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(BaseScores);
    PointsRemaining = 27 - TotalCost;

    // Validação D&D 5e Point Buy: exatamente 27 pontos devem ser gastos
    // PointsRemaining deve ser 0 para alocação válida
    // Não clampa silenciosamente - mantém o valor real para indicar estado inválido
    // Validação adicional: todos os scores devem estar entre 8 e 15
    bool bAllScoresValid = true;
    for (const auto &Pair : AbilityScores)
    {
        if (Pair.Value.BaseScore < 8 || Pair.Value.BaseScore > 15)
        {
            bAllScoresValid = false;
            break;
        }
    }

    // Se PointsRemaining != 0 ou scores inválidos, a alocação está incorreta
    // PointsRemaining negativo = pontos excedidos (mais de 27 gastos)
    // PointsRemaining positivo = pontos não gastos (menos de 27 gastos)
    // Não clampa para evitar mascarar estado inválido
}

void UCharacterSheetDataAsset::ValidateTotalLevel()
{
    // Calcula nível total usando helper
    TotalLevel = CharacterSheetHelpers::CalculateTotalLevel(ClassLevels);

    // Validação: nível total não pode exceder 20
    if (TotalLevel > 20)
    {
        TotalLevel = 20;

        // Seta flag para evitar recursão infinita ao modificar ClassLevels
        bIsValidatingProperties = true;

        // Ajusta níveis das classes para não exceder 20
        int32 RemainingLevels = 20;
        for (FClassLevelEntry &Entry : ClassLevels)
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

        // Limpa flag após modificar propriedades
        bIsValidatingProperties = false;
    }
}

void UCharacterSheetDataAsset::UpdateRacialBonuses()
{
    // Seta flag para evitar recursão infinita ao modificar AbilityScores
    bIsValidatingProperties = true;

    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        // Resetar bônus raciais se não há raça selecionada
        for (auto &Pair : AbilityScores)
        {
            Pair.Value.RacialBonus = 0;
            Pair.Value.FinalScore = Pair.Value.BaseScore;
        }
        bIsValidatingProperties = false;
        return;
    }

    // Resetar todos os bônus primeiro
    for (auto &Pair : AbilityScores)
    {
        Pair.Value.RacialBonus = 0;
    }

    // Busca dados da raça base no Data Table
    bool bRaceFound = false;
    TArray<FName> RowNames = RaceDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
        {
            if (Row->RaceName == SelectedRace)
            {
                bRaceFound = true;

                // Aplicar bônus da raça base
                for (const FAbilityScoreImprovement &Improvement : Row->AbilityScoreImprovements)
                {
                    if (FAbilityScoreEntry *Entry = AbilityScores.Find(Improvement.AbilityName))
                    {
                        Entry->RacialBonus += Improvement.Bonus;
                    }
                }

                break;
            }
        }
    }

    // Se a raça não foi encontrada no Data Table, resetar bônus para evitar estado inconsistente
    if (!bRaceFound)
    {
        for (auto &Pair : AbilityScores)
        {
            Pair.Value.RacialBonus = 0;
            Pair.Value.FinalScore = Pair.Value.BaseScore;
        }
        bIsValidatingProperties = false;
        return;
    }

    // Se uma sub-raça foi selecionada, aplicar bônus adicionais da sub-raça
    if (SelectedSubrace != NAME_None)
    {
        bool bSubraceFound = false;
        for (const FName &RowName : RowNames)
        {
            if (FRaceDataRow *SubraceRow = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
            {
                if (SubraceRow->RaceName == SelectedSubrace)
                {
                    bSubraceFound = true;

                    // Aplicar bônus adicionais da sub-raça (somando aos bônus da raça base)
                    for (const FAbilityScoreImprovement &Improvement : SubraceRow->AbilityScoreImprovements)
                    {
                        if (FAbilityScoreEntry *Entry = AbilityScores.Find(Improvement.AbilityName))
                        {
                            Entry->RacialBonus += Improvement.Bonus;
                        }
                    }

                    break;
                }
            }
        }

        // Se sub-raça não foi encontrada, apenas loga (não reseta bônus da raça base)
        if (!bSubraceFound)
        {
            UE_LOG(LogTemp, Warning, TEXT("Subrace '%s' not found in RaceDataTable"), *SelectedSubrace.ToString());
        }
    }

    // Atualizar scores finais após aplicar bônus da raça e sub-raça
    for (auto &Pair : AbilityScores)
    {
        Pair.Value.FinalScore = Pair.Value.BaseScore + Pair.Value.RacialBonus;
    }

    // Limpa flag após modificar propriedades
    bIsValidatingProperties = false;
}

void UCharacterSheetDataAsset::UpdateCalculatedFields()
{
    AvailableFeatures.Empty();
    Proficiencies.Empty();

    if (!ClassDataTable)
    {
        return;
    }

    // Coleta features de todas as classes e níveis
    // GetFeaturesAtLevel() agora retorna todas as features desbloqueadas até o nível especificado
    // (corrigido para usar <= em vez de ==), então chamamos apenas uma vez por classe
    for (const FClassLevelEntry &ClassEntry : ClassLevels)
    {
        if (ClassEntry.ClassName == NAME_None || ClassEntry.Level < 1)
        {
            continue;
        }

        // Busca todas as features desbloqueadas até o nível atual da classe
        TArray<FClassFeature> Features =
            CharacterSheetHelpers::GetFeaturesAtLevel(ClassEntry.ClassName, ClassEntry.Level, ClassDataTable);
        for (const FClassFeature &Feature : Features)
        {
            AvailableFeatures.AddUnique(Feature.FeatureName);
        }
    }

    // TODO: Adicionar proficiências de raça, classe e background quando necessário
    // Por enquanto, apenas estrutura preparada
}
#endif
