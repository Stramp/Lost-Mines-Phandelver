// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAsset.h"
#include "Handlers/CharacterSheetDataAssetHandlers.h"
#include "Containers/UnrealString.h"
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

#if WITH_EDITOR
    InitializePropertyHandlers();
#endif
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

    // Ignora mudanças em bIsVariantHuman (é uma propriedade calculada, não editada diretamente)
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bIsVariantHuman))
    {
        return;
    }

    // Lookup handler in map and execute if found
    if (std::function<void()> *Handler = PropertyHandlers.Find(PropertyName))
    {
        (*Handler)();
    }
}

void UCharacterSheetDataAsset::InitializePropertyHandlers()
{
    // Race and Subrace handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace),
                         [this]()
                         {
                             FCharacterSheetDataAssetHandlers::HandleRaceChange(
                                 this, GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace));
                         });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace),
                         [this]()
                         {
                             FCharacterSheetDataAssetHandlers::HandleRaceChange(
                                 this, GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace));
                         });

    // Ability Scores handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, AbilityScores),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleAbilityScoresChange(this); });

    // Class Levels handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassLevels),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleClassLevelsChange(this); });

    // Background handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleBackgroundChange(this); });

    // Variant Human choices handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(this); });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(this); });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(this); });

    // Data Tables handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleDataTableChange(this); });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleDataTableChange(this); });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleDataTableChange(this); });
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable),
                         [this]() { FCharacterSheetDataAssetHandlers::HandleDataTableChange(this); });
}

void UCharacterSheetDataAsset::UpdateVariantHumanFlag()
{
    // Atualiza flag bIsVariantHuman e notifica editor se mudou
    // Variant Human é uma SUB-RAÇA, não uma raça
    bool bNewIsVariantHuman = (SelectedSubrace == TEXT("Variant Human"));
    if (bIsVariantHuman != bNewIsVariantHuman)
    {
        bIsVariantHuman = bNewIsVariantHuman;

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bIsVariantHuman
        if (GIsEditor && !bIsValidatingProperties)
        {
            Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(
                    GetClass(), GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bIsVariantHuman)))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Reseta escolhas se não for Variant Human
    if (!bIsVariantHuman)
    {
        ResetVariantHumanChoices();
    }
}

void UCharacterSheetDataAsset::ValidateAndUpdate()
{
    // Orquestrador completo: atualiza tudo (usado apenas quando necessário)
    UpdateVariantHumanFlag();
    ValidatePointBuy();
    ValidateTotalLevel();
    UpdateRacialBonuses();
    UpdateCalculatedFields();

    // Valida escolhas de Variant Human se aplicável
    if (bIsVariantHuman)
    {
        ValidateVariantHumanChoices();
    }
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
    // Otimização: Assumindo que RowName = RaceName no JSON, podemos usar FindRow diretamente
    // Se não encontrar, faz busca O(n) como fallback
    FRaceDataRow *RaceRow = RaceDataTable->FindRow<FRaceDataRow>(SelectedRace, TEXT("UpdateRacialBonuses"));

    // Fallback: Se FindRow não encontrou, pode ser que RowName != RaceName, então busca manual
    if (!RaceRow)
    {
        TArray<FName> RowNames = RaceDataTable->GetRowNames();
        for (const FName &RowName : RowNames)
        {
            if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
            {
                if (Row->RaceName == SelectedRace)
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
        for (auto &Pair : AbilityScores)
        {
            Pair.Value.RacialBonus = 0;
            Pair.Value.FinalScore = Pair.Value.BaseScore;
        }
        bIsValidatingProperties = false;
        return;
    }

    // Aplicar bônus da raça base
    for (const FAbilityScoreImprovement &Improvement : RaceRow->AbilityScoreImprovements)
    {
        // Bônus normal para atributo específico
        // Nota: "Custom" é tratado apenas na sub-raça (Variant Human)
        if (FAbilityScoreEntry *Entry = AbilityScores.Find(Improvement.AbilityName))
        {
            Entry->RacialBonus += Improvement.Bonus;
        }
    }

    // Se uma sub-raça foi selecionada, validar e aplicar bônus adicionais
    if (SelectedSubrace != NAME_None)
    {
        // Validar se a sub-raça pertence à raça selecionada
        bool bSubraceValid = RaceRow->SubraceNames.Contains(SelectedSubrace);

        if (!bSubraceValid)
        {
            UE_LOG(LogTemp, Warning, TEXT("Subrace '%s' não pertence à raça '%s'. Resetando sub-raça."),
                   *SelectedSubrace.ToString(), *SelectedRace.ToString());
            SelectedSubrace = NAME_None;
        }
        else
        {
            // Busca direta da sub-raça (otimização)
            FRaceDataRow *SubraceRow =
                RaceDataTable->FindRow<FRaceDataRow>(SelectedSubrace, TEXT("UpdateRacialBonuses"));

            // Fallback: busca manual se FindRow não encontrou
            if (!SubraceRow)
            {
                TArray<FName> RowNames = RaceDataTable->GetRowNames();
                for (const FName &RowName : RowNames)
                {
                    if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("UpdateRacialBonuses")))
                    {
                        if (Row->RaceName == SelectedSubrace)
                        {
                            SubraceRow = Row;
                            break;
                        }
                    }
                }
            }

            if (SubraceRow)
            {
                // Aplicar bônus adicionais da sub-raça (somando aos bônus da raça base)
                for (const FAbilityScoreImprovement &Improvement : SubraceRow->AbilityScoreImprovements)
                {
                    // Tratar "Custom" para Variant Human (sub-raça)
                    if (Improvement.AbilityName == TEXT("Custom") && SelectedSubrace == TEXT("Variant Human"))
                    {
                        // Variant Human: aplicar +1 para cada atributo em CustomAbilityScoreChoices
                        for (const FName &CustomAbility : CustomAbilityScoreChoices)
                        {
                            if (FAbilityScoreEntry *Entry = AbilityScores.Find(CustomAbility))
                            {
                                Entry->RacialBonus += 1; // Cada escolha dá +1
                            }
                        }
                    }
                    else if (FAbilityScoreEntry *Entry = AbilityScores.Find(Improvement.AbilityName))
                    {
                        // Bônus normal para atributo específico
                        Entry->RacialBonus += Improvement.Bonus;
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Subrace '%s' not found in RaceDataTable"), *SelectedSubrace.ToString());
            }
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
    // Seta flag para evitar recursão infinita ao modificar UPROPERTY fields
    bIsValidatingProperties = true;

    AvailableFeatures.Empty();
    Proficiencies.Empty();

    if (!ClassDataTable)
    {
        bIsValidatingProperties = false;
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

    // Limpa flag após modificar propriedades
    bIsValidatingProperties = false;
}

TArray<FName> UCharacterSheetDataAsset::GetRaceNames() const
{
    if (!RaceDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubraceNames() const
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetBackgroundNames() const
{
    if (!BackgroundDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetClassNames() const
{
    if (!ClassDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllClassNames(ClassDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubclassNames(FName ClassName) const
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubclasses(ClassName, ClassDataTable);
}

void UCharacterSheetDataAsset::ValidateVariantHumanChoices()
{
    if (!bIsVariantHuman)
    {
        return;
    }

    // Validar CustomAbilityScoreChoices: deve ter exatamente 2 elementos
    if (CustomAbilityScoreChoices.Num() != 2)
    {
        // Ajusta para ter exatamente 2 elementos
        CustomAbilityScoreChoices.SetNum(2);
        // Preenche com valores padrão se necessário
        if (CustomAbilityScoreChoices[0] == NAME_None)
        {
            CustomAbilityScoreChoices[0] = TEXT("Strength");
        }
        if (CustomAbilityScoreChoices[1] == NAME_None)
        {
            CustomAbilityScoreChoices[1] = TEXT("Dexterity");
        }
    }

    // Validar que os atributos escolhidos são válidos
    TArray<FName> ValidAbilityNames = GetAbilityScoreNames();
    for (FName &AbilityName : CustomAbilityScoreChoices)
    {
        if (!ValidAbilityNames.Contains(AbilityName))
        {
            AbilityName = TEXT("Strength"); // Valor padrão
        }
    }

    // Validar SelectedFeat (deve estar na lista de feats disponíveis)
    if (SelectedFeat != NAME_None && FeatDataTable)
    {
        TArray<FName> AvailableFeats = GetAvailableFeatNames();
        if (!AvailableFeats.Contains(SelectedFeat))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedFeat '%s' não está disponível. Resetando."),
                   *SelectedFeat.ToString());
            SelectedFeat = NAME_None;
        }
    }

    // Validar SelectedSkill (deve estar na lista de skills válidas)
    if (SelectedSkill != NAME_None)
    {
        TArray<FName> ValidSkills = GetSkillNames();
        if (!ValidSkills.Contains(SelectedSkill))
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: SelectedSkill '%s' não é válido. Resetando."),
                   *SelectedSkill.ToString());
            SelectedSkill = NAME_None;
        }
    }
}

void UCharacterSheetDataAsset::ResetVariantHumanChoices()
{
    CustomAbilityScoreChoices.Empty();
    SelectedFeat = NAME_None;
    SelectedSkill = NAME_None;
}

TArray<FName> UCharacterSheetDataAsset::GetAbilityScoreNames() const
{
    return TArray<FName>{TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                         TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableFeatNames() const
{
    if (!FeatDataTable)
    {
        return TArray<FName>();
    }

    // Para Variant Human, todos os feats estão disponíveis (sem pré-requisitos de nível)
    // Usa nível 1 e ability scores atuais
    TMap<FName, int32> CurrentAbilityScores;
    for (const auto &Pair : AbilityScores)
    {
        CurrentAbilityScores.Add(Pair.Key, Pair.Value.FinalScore);
    }

    return CharacterSheetHelpers::GetAvailableFeats(1, CurrentAbilityScores, FeatDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSkillNames() const
{
    // Lista completa de skills de D&D 5e
    return TArray<FName>{TEXT("Acrobatics"),    TEXT("Animal Handling"), TEXT("Arcana"),   TEXT("Athletics"),
                         TEXT("Deception"),     TEXT("History"),         TEXT("Insight"),  TEXT("Intimidation"),
                         TEXT("Investigation"), TEXT("Medicine"),        TEXT("Nature"),   TEXT("Perception"),
                         TEXT("Performance"),   TEXT("Persuasion"),      TEXT("Religion"), TEXT("Sleight of Hand"),
                         TEXT("Stealth"),       TEXT("Survival")};
}
#endif
