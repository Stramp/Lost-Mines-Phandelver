// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetHelpers.h"
#include "DataTableHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/FeatDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/DnDConstants.h"

// ============================================================================
// Race Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllRaceNames(UDataTable *RaceDataTable)
{
    if (!RaceDataTable)
    {
        return TArray<FName>();
    }

    // Otimização: itera uma única vez coletando tudo
    // Evita O(n²) de FindRow dentro de loops
    TSet<FName> AllSubraceNamesSet;
    TSet<FName> RaceNamesSet;
    TArray<FName> RowNames = RaceDataTable->GetRowNames();

    // Primeira passagem: coleta sub-raças e raças base em uma única iteração
    for (const FName &RowName : RowNames)
    {
        if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("GetAllRaceNames")))
        {
            // Coleta todos os nomes de sub-raças
            for (const FName &SubraceName : Row->SubraceNames)
            {
                if (SubraceName != NAME_None)
                {
                    AllSubraceNamesSet.Add(SubraceName);
                }
            }

            // Coleta raça base (será filtrada depois se for sub-raça)
            if (Row->RaceName != NAME_None)
            {
                RaceNamesSet.Add(Row->RaceName);
            }
        }
    }

    // Remove raças que são sub-raças (não devem aparecer no dropdown)
    for (const FName &SubraceName : AllSubraceNamesSet)
    {
        RaceNamesSet.Remove(SubraceName);
    }

    // Converte TSet para TArray (ordem não importa para nomes de raças)
    return RaceNamesSet.Array();
}

TArray<FName> CharacterSheetHelpers::GetAvailableSubraces(FName RaceName, UDataTable *RaceDataTable)
{
    if (!RaceDataTable || RaceName == NAME_None)
    {
        return TArray<FName>();
    }

    // Usa DataTableHelpers para buscar row de raça (otimização: remove loop O(n²))
    if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
    {
        return RaceRow->SubraceNames;
    }

    return TArray<FName>();
}

// ============================================================================
// Class Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllClassNames(UDataTable *ClassDataTable)
{
    if (!ClassDataTable)
    {
        return TArray<FName>();
    }

    TSet<FName> ClassNamesSet;
    TArray<FName> RowNames = ClassDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("GetAllClassNames")))
        {
            // Usa FClass.Name da nova estrutura
            if (Row->FClass.Name != NAME_None)
            {
                ClassNamesSet.Add(Row->FClass.Name);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para nomes de classes)
    return ClassNamesSet.Array();
}

bool CharacterSheetHelpers::CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable)
{
    // Validação básica
    if (ClassName == NAME_None || ClassLevel < DnDConstants::MIN_LEVEL)
    {
        return false;
    }

    // Em D&D 5e, subclasses são escolhidas no nível 3
    // Nota: Verificação de subclasses disponíveis será implementada quando necessário
    // usando a nova estrutura FClassData.FProgress
    return ClassLevel >= DnDConstants::SUBCLASS_SELECTION_LEVEL;
}

// ============================================================================
// Background Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllBackgroundNames(UDataTable *BackgroundDataTable)
{
    if (!BackgroundDataTable)
    {
        return TArray<FName>();
    }

    TSet<FName> BackgroundNamesSet;
    TArray<FName> RowNames = BackgroundDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FBackgroundDataRow *Row =
                BackgroundDataTable->FindRow<FBackgroundDataRow>(RowName, TEXT("GetAllBackgroundNames")))
        {
            if (Row->BackgroundName != NAME_None)
            {
                BackgroundNamesSet.Add(Row->BackgroundName);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para nomes de backgrounds)
    return BackgroundNamesSet.Array();
}

// ============================================================================
// Feat Data Table Helpers
// ============================================================================

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

    // Se não há pré-requisitos, o feat está disponível
    if (Row->Prerequisites.Num() == 0)
    {
        return true;
    }

    // Valida cada pré-requisito
    // Todos os pré-requisitos devem ser atendidos (AND lógico)
    for (const FName &Prerequisite : Row->Prerequisites)
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
    if (!FeatDataTable || TotalLevel < 1)
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
            if (Row->FeatName == NAME_None)
            {
                continue;
            }

            if (CharacterSheetHelpers::MeetsFeatPrerequisites(Row, AbilityScores))
            {
                AvailableFeatsSet.Add(Row->FeatName);
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
    TSet<FName> AvailableFeatsSet;
    TArray<FName> RowNames = FeatDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FFeatDataRow *Row = FeatDataTable->FindRow<FFeatDataRow>(RowName, TEXT("GetAvailableFeatsForVariantHuman")))
        {
            if (Row->FeatName == NAME_None)
            {
                continue;
            }

            // Valida apenas pré-requisitos de ability scores (sem verificação de nível)
            if (CharacterSheetHelpers::MeetsFeatPrerequisites(Row, AbilityScores))
            {
                AvailableFeatsSet.Add(Row->FeatName);
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para feats)
    return AvailableFeatsSet.Array();
}

// ============================================================================
// Ability Score Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAbilityScoreNames()
{
    // Retorna array estático com os 6 nomes de ability scores padrão D&D 5e
    // Ordem: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
    return TArray<FName>{TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                         TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
}

// ============================================================================
// Skill Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetSkillNames()
{
    // Retorna array estático com os 18 nomes de skills padrão D&D 5e
    // Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
    // History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
    // Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
    //
    // TODO: Futuramente migrar para SkillDataTable seguindo o princípio Data-Driven completo.
    // Por enquanto, hardcoded porque são constantes do sistema D&D 5e (assim como Ability Scores).
    // Quando implementado SkillDataTable, criar função GetAllSkillNames(UDataTable* SkillDataTable)
    // similar a GetAllRaceNames() e GetAllClassNames().
    return TArray<FName>{TEXT("Acrobatics"),    TEXT("Animal Handling"), TEXT("Arcana"),   TEXT("Athletics"),
                         TEXT("Deception"),     TEXT("History"),         TEXT("Insight"),  TEXT("Intimidation"),
                         TEXT("Investigation"), TEXT("Medicine"),        TEXT("Nature"),   TEXT("Perception"),
                         TEXT("Performance"),   TEXT("Persuasion"),      TEXT("Religion"), TEXT("Sleight of Hand"),
                         TEXT("Stealth"),       TEXT("Survival")};
}

TArray<FName> CharacterSheetHelpers::GetAvailableLanguageNames()
{
    // TODO: Futuramente migrar para LanguageDataTable seguindo o princípio Data-Driven completo.
    // Por enquanto, hardcoded porque são constantes do sistema D&D 5e.
    // Quando implementado LanguageDataTable, criar função GetAllLanguageNames(UDataTable* LanguageDataTable)
    // similar a GetAllRaceNames() e GetAllClassNames().
    return TArray<FName>{TEXT("Common"),   TEXT("Dwarvish"),   TEXT("Elvish"),   TEXT("Giant"),
                         TEXT("Gnomish"),  TEXT("Goblin"),     TEXT("Halfling"), TEXT("Orc"),
                         TEXT("Abyssal"),  TEXT("Celestial"),  TEXT("Draconic"), TEXT("Deep Speech"),
                         TEXT("Infernal"), TEXT("Primordial"), TEXT("Sylvan"),   TEXT("Undercommon")};
}

bool CharacterSheetHelpers::HasLanguageChoiceFromRace(FName RaceName, FName SubraceName, UDataTable *RaceDataTable,
                                                      int32 &OutCount)
{
    OutCount = 0;

    if (!RaceDataTable)
    {
        return false;
    }

    // Verifica sub-raça primeiro (tem prioridade sobre raça base)
    if (SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            for (const FRaceTrait &Trait : SubraceRow->Traits)
            {
                if (Trait.TraitName == TEXT("Extra Language"))
                {
                    if (const FString *TypePtr = Trait.TraitData.Find(TEXT("Type")))
                    {
                        if (*TypePtr == TEXT("Language"))
                        {
                            if (const FString *CountPtr = Trait.TraitData.Find(TEXT("Count")))
                            {
                                OutCount = FCString::Atoi(**CountPtr);
                                return OutCount > 0;
                            }
                        }
                    }
                }
            }
        }
    }

    // Verifica raça base se sub-raça não tiver escolha
    if (RaceName != NAME_None && OutCount == 0)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            for (const FRaceTrait &Trait : RaceRow->Traits)
            {
                if (Trait.TraitName == TEXT("Extra Language"))
                {
                    if (const FString *TypePtr = Trait.TraitData.Find(TEXT("Type")))
                    {
                        if (*TypePtr == TEXT("Language"))
                        {
                            if (const FString *CountPtr = Trait.TraitData.Find(TEXT("Count")))
                            {
                                OutCount = FCString::Atoi(**CountPtr);
                                return OutCount > 0;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool CharacterSheetHelpers::HasLanguageChoiceFromBackground(FName BackgroundName, UDataTable *BackgroundDataTable,
                                                            int32 &OutCount)
{
    OutCount = 0;

    if (!BackgroundDataTable || BackgroundName == NAME_None)
    {
        return false;
    }

    if (FBackgroundDataRow *BackgroundRow = DataTableHelpers::FindBackgroundRow(BackgroundName, BackgroundDataTable))
    {
        OutCount = BackgroundRow->LanguageChoices.Count;
        return OutCount > 0;
    }

    return false;
}

TArray<FName> CharacterSheetHelpers::GetAutomaticLanguages(FName RaceName, FName SubraceName, FName BackgroundName,
                                                           UDataTable *RaceDataTable, UDataTable *BackgroundDataTable)
{
    TSet<FName> AutomaticLanguagesSet;

    // Coleta idiomas automáticos da raça base
    if (RaceDataTable && RaceName != NAME_None)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            for (const FName &Language : RaceRow->Languages)
            {
                if (Language != NAME_None)
                {
                    AutomaticLanguagesSet.Add(Language);
                }
            }
        }
    }

    // Coleta idiomas automáticos da sub-raça
    if (RaceDataTable && SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            for (const FName &Language : SubraceRow->Languages)
            {
                if (Language != NAME_None)
                {
                    AutomaticLanguagesSet.Add(Language);
                }
            }
        }
    }

    // Coleta idiomas automáticos do background (não-escolhas)
    if (BackgroundDataTable && BackgroundName != NAME_None)
    {
        if (FBackgroundDataRow *BackgroundRow =
                DataTableHelpers::FindBackgroundRow(BackgroundName, BackgroundDataTable))
        {
            for (const FName &Language : BackgroundRow->Languages)
            {
                if (Language != NAME_None)
                {
                    AutomaticLanguagesSet.Add(Language);
                }
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para idiomas)
    return AutomaticLanguagesSet.Array();
}

TArray<FName> CharacterSheetHelpers::GetAvailableLanguagesForChoice(FName RaceName, FName SubraceName,
                                                                    FName BackgroundName,
                                                                    const TArray<FName> &SelectedLanguages,
                                                                    UDataTable *RaceDataTable,
                                                                    UDataTable *BackgroundDataTable)
{
    // Obtém todos os idiomas disponíveis
    TArray<FName> AllLanguages = GetAvailableLanguageNames();

    // Calcula idiomas automáticos já conhecidos
    TArray<FName> AutomaticLanguages =
        GetAutomaticLanguages(RaceName, SubraceName, BackgroundName, RaceDataTable, BackgroundDataTable);

    // Converte para TSet para busca O(1) em vez de O(n)
    TSet<FName> AutomaticLanguagesSet(AutomaticLanguages);
    TSet<FName> SelectedLanguagesSet(SelectedLanguages);

    // Remove idiomas já conhecidos (automáticos + já escolhidos no array) do array completo
    TArray<FName> AvailableLanguages;
    AvailableLanguages.Reserve(AllLanguages.Num()); // Pre-aloca memória
    for (const FName &Language : AllLanguages)
    {
        // Exclui idiomas automáticos (busca O(1) com TSet)
        if (AutomaticLanguagesSet.Contains(Language))
        {
            continue;
        }

        // Exclui idiomas já escolhidos no array SelectedLanguages (busca O(1) com TSet)
        if (SelectedLanguagesSet.Contains(Language))
        {
            continue;
        }

        AvailableLanguages.Add(Language);
    }

    return AvailableLanguages;
}

// ============================================================================
// Point Buy System Helpers
// ============================================================================

int32 CharacterSheetHelpers::CalculatePointBuyCost(int32 Score)
{
    // Validação: scores devem estar entre 8 e 15
    if (Score < 8 || Score > 15)
    {
        return 0;
    }

    // Tabela oficial D&D 5e Point Buy
    if (Score == 8)
    {
        return 0;
    }
    else if (Score >= 9 && Score <= 13)
    {
        return Score - 8;
    }
    else if (Score == 14)
    {
        return 7;
    }
    else if (Score == 15)
    {
        return 9;
    }

    return 0;
}

int32 CharacterSheetHelpers::CalculateTotalPointBuyCost(const TMap<FName, int32> &AbilityScores)
{
    int32 TotalCost = 0;

    for (const auto &Pair : AbilityScores)
    {
        TotalCost += CalculatePointBuyCost(Pair.Value);
    }

    return TotalCost;
}

TMap<FName, int32> CharacterSheetHelpers::CreateBaseScoresFromPointBuy(const TMap<FName, int32> &PointBuyMap)
{
    TMap<FName, int32> BaseScores;
    BaseScores.Add(TEXT("Strength"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Strength")));
    BaseScores.Add(TEXT("Dexterity"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Dexterity")));
    BaseScores.Add(TEXT("Constitution"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Constitution")));
    BaseScores.Add(TEXT("Intelligence"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Intelligence")));
    BaseScores.Add(TEXT("Wisdom"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Wisdom")));
    BaseScores.Add(TEXT("Charisma"), DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(TEXT("Charisma")));
    return BaseScores;
}

FString CharacterSheetHelpers::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Ordem de redução: do final da fila (Charisma -> Wisdom -> Intelligence -> Constitution -> Dexterity -> Strength)
    TArray<FName> ReductionOrder = {TEXT("Charisma"),     TEXT("Wisdom"),    TEXT("Intelligence"),
                                    TEXT("Constitution"), TEXT("Dexterity"), TEXT("Strength")};

    // Calcula custo atual usando helper puro (elimina duplicação e magic number)
    TMap<FName, int32> BaseScores = CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 TotalCost = CalculateTotalPointBuyCost(BaseScores);

    // Reduz até chegar a MaxPoints pontos
    int32 PointsToReduce = TotalCost - MaxPoints;
    int32 CurrentIndex = 0;

    while (PointsToReduce > 0 && CurrentIndex < ReductionOrder.Num())
    {
        FName CurrentAttribute = ReductionOrder[CurrentIndex];
        int32 *CurrentAllocation = PointBuyMap.Find(CurrentAttribute);

        if (CurrentAllocation && *CurrentAllocation > 0)
        {
            // Calcula custo atual deste atributo
            int32 CurrentBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentAllocation;
            int32 CurrentCost = CalculatePointBuyCost(CurrentBaseScore);

            // Reduz 1 ponto
            (*CurrentAllocation)--;
            int32 NewBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentAllocation;
            int32 NewCost = CalculatePointBuyCost(NewBaseScore);

            // Atualiza pontos a reduzir
            PointsToReduce -= (CurrentCost - NewCost);

            // Se ainda precisa reduzir, continua no mesmo atributo
            if (PointsToReduce > 0)
            {
                continue;
            }
        }

        // Próximo atributo
        CurrentIndex++;
    }

    // Gera mensagem de feedback
    if (PointsToReduce <= 0)
    {
        return FString::Printf(TEXT("Alocação ajustada: reduzido do final da fila para não exceder %d pontos"),
                               MaxPoints);
    }
    else
    {
        return FString::Printf(TEXT("Alocação ajustada parcialmente: ainda excede %d pontos por %d"), MaxPoints,
                               PointsToReduce);
    }
}

// ============================================================================
// Level Calculation Helpers
// ============================================================================

int32 CharacterSheetHelpers::CalculateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels)
{
    int32 TotalLevel = 0;

    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        if (Entry.Level > 0)
        {
            TotalLevel += Entry.Level;
        }
    }

    return TotalLevel;
}

// ============================================================================
// Multiclassing Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetChoiceOptions(FName ChoiceID, FName ClassName, int32 ClassLevel,
                                                      UDataTable *ClassDataTable)
{
    TArray<FName> Options;

    if (!ClassDataTable || ChoiceID == NAME_None || ClassName == NAME_None)
    {
        return Options;
    }

    FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return Options;
    }

    return Options;
}

bool CharacterSheetHelpers::IsChoiceValid(FName ChoiceID, const TArray<FName> &SelectedValues,
                                          const TArray<FClassLevelEntry> &ClassLevels, UDataTable *ClassDataTable)
{
    if (ChoiceID == NAME_None || SelectedValues.Num() == 0 || !ClassDataTable)
    {
        return false;
    }

    // Busca a escolha no Data Table
    for (const FClassLevelEntry &Entry : ClassLevels)
    {
        FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(Entry.ClassName, ClassDataTable);
        if (!ClassRow)
        {
            continue;
        }
    }

    return false;
}
