// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetHelpers.h"
#include "DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/TraitDataTable.h"
#include "Data/Tables/LanguageDataTable.h"
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
            // Coleta todos os nomes de sub-raças (agora via SubraceHandles)
            for (const FDataTableRowHandle &SubraceHandle : Row->SubraceHandles)
            {
                if (SubraceHandle.RowName != NAME_None)
                {
                    AllSubraceNamesSet.Add(SubraceHandle.RowName);
                }
            }

            // Coleta raça base (será filtrada depois se for sub-raça)
            if (Row->Name != NAME_None)
            {
                RaceNamesSet.Add(Row->Name);
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
        // Converte SubraceHandles para TArray<FName>
        TArray<FName> SubraceNames;
        for (const FDataTableRowHandle &SubraceHandle : RaceRow->SubraceHandles)
        {
            if (SubraceHandle.RowName != NAME_None)
            {
                SubraceNames.Add(SubraceHandle.RowName);
            }
        }
        return SubraceNames;
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
            // Usa ClassName da estrutura flat
            if (Row->ClassName != NAME_None)
            {
                ClassNamesSet.Add(Row->ClassName);
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
            if (Row->Name != NAME_None)
            {
                BackgroundNamesSet.Add(Row->Name);
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

// ============================================================================
// Ability Score Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAbilityScoreNames(UDataTable *AbilityScoreDataTable)
{
    // Se Data Table fornecido, busca do Data Table (Data-Driven)
    if (AbilityScoreDataTable)
    {
        TArray<FName> AbilityNames = DataTableHelpers::GetAllAbilityScoreNames(AbilityScoreDataTable);
        // Se encontrou ability scores no Data Table, retorna
        if (AbilityNames.Num() > 0)
        {
            return AbilityNames;
        }
    }

    // Fallback: retorna array estático com os 6 nomes de ability scores padrão D&D 5e
    // Ordem: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
    return TArray<FName>{TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                         TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
}

// ============================================================================
// Skill Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetSkillNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllSkillNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os 18 nomes de skills padrão D&D 5e
    // Ordem alfabética: Acrobatics, Animal Handling, Arcana, Athletics, Deception,
    // History, Insight, Intimidation, Investigation, Medicine, Nature, Perception,
    // Performance, Persuasion, Religion, Sleight of Hand, Stealth, Survival
    return TArray<FName>{TEXT("Acrobatics"),    TEXT("Animal Handling"), TEXT("Arcana"),   TEXT("Athletics"),
                         TEXT("Deception"),     TEXT("History"),         TEXT("Insight"),  TEXT("Intimidation"),
                         TEXT("Investigation"), TEXT("Medicine"),        TEXT("Nature"),   TEXT("Perception"),
                         TEXT("Performance"),   TEXT("Persuasion"),      TEXT("Religion"), TEXT("Sleight of Hand"),
                         TEXT("Stealth"),       TEXT("Survival")};
}

TArray<FName> CharacterSheetHelpers::GetAvailableLanguageNames(UDataTable *ProficiencyDataTable)
{
    // Se ProficiencyDataTable for fornecido, busca do Data Table (Data-Driven)
    if (ProficiencyDataTable)
    {
        return DataTableHelpers::GetAllLanguageNames(ProficiencyDataTable);
    }

    // Fallback: Retorna array hardcoded com os idiomas padrão D&D 5e
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
    // Agora usa TraitHandles que apontam para TraitDataTable
    if (SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            for (const FDataTableRowHandle &TraitHandle : SubraceRow->TraitHandles)
            {
                // Resolve handle para obter dados do trait
                if (const FTraitDataRow *TraitRow =
                        DataTableRowHandleHelpers::ResolveHandle<FTraitDataRow>(TraitHandle))
                {
                    // Verifica se é "Extra Language" pelo ID ou Name
                    if (TraitRow->ID == TEXT("TR_ExtraLanguage") || TraitRow->Name == TEXT("Extra Language"))
                    {
                        if (const FString *TypePtr = TraitRow->TraitData.Find(TEXT("Type")))
                        {
                            if (*TypePtr == TEXT("Language"))
                            {
                                if (const FString *CountPtr = TraitRow->TraitData.Find(TEXT("Count")))
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
    }

    // Verifica raça base se sub-raça não tiver escolha
    if (RaceName != NAME_None && OutCount == 0)
    {
        if (FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(RaceName, RaceDataTable))
        {
            for (const FDataTableRowHandle &TraitHandle : RaceRow->TraitHandles)
            {
                // Resolve handle para obter dados do trait
                if (const FTraitDataRow *TraitRow =
                        DataTableRowHandleHelpers::ResolveHandle<FTraitDataRow>(TraitHandle))
                {
                    // Verifica se é "Extra Language" pelo ID ou Name
                    if (TraitRow->ID == TEXT("TR_ExtraLanguage") || TraitRow->Name == TEXT("Extra Language"))
                    {
                        if (const FString *TypePtr = TraitRow->TraitData.Find(TEXT("Type")))
                        {
                            if (*TypePtr == TEXT("Language"))
                            {
                                if (const FString *CountPtr = TraitRow->TraitData.Find(TEXT("Count")))
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
            // Resolve LanguageHandles para obter ID
            for (const FDataTableRowHandle &LanguageHandle : RaceRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        AutomaticLanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    AutomaticLanguagesSet.Add(LanguageHandle.RowName);
                }
            }
        }
    }

    // Coleta idiomas automáticos da sub-raça
    if (RaceDataTable && SubraceName != NAME_None)
    {
        if (FRaceDataRow *SubraceRow = DataTableHelpers::FindSubraceRow(SubraceName, RaceDataTable))
        {
            // Resolve LanguageHandles para obter ID
            for (const FDataTableRowHandle &LanguageHandle : SubraceRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        AutomaticLanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    AutomaticLanguagesSet.Add(LanguageHandle.RowName);
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
            // Resolve LanguageHandles para obter ID
            for (const FDataTableRowHandle &LanguageHandle : BackgroundRow->LanguageHandles)
            {
                if (const FLanguageDataRow *LanguageRow =
                        DataTableRowHandleHelpers::ResolveHandle<FLanguageDataRow>(LanguageHandle))
                {
                    if (LanguageRow->ID != NAME_None)
                    {
                        AutomaticLanguagesSet.Add(LanguageRow->ID);
                    }
                }
                else if (LanguageHandle.RowName != NAME_None)
                {
                    // Fallback: usa RowName se resolução falhar
                    AutomaticLanguagesSet.Add(LanguageHandle.RowName);
                }
            }
        }
    }

    // Converte TSet para TArray (ordem não importa para idiomas)
    return AutomaticLanguagesSet.Array();
}

TArray<FName>
CharacterSheetHelpers::GetAvailableLanguagesForChoice(FName RaceName, FName SubraceName, FName BackgroundName,
                                                      const TArray<FName> &SelectedLanguages, UDataTable *RaceDataTable,
                                                      UDataTable *BackgroundDataTable, UDataTable *ProficiencyDataTable)
{
    // Obtém todos os idiomas disponíveis
    // Usa ProficiencyDataTable se fornecido (Data-Driven), caso contrário usa fallback hardcoded
    TArray<FName> AllLanguages = GetAvailableLanguageNames(ProficiencyDataTable);

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
    // Validação: scores devem estar entre MIN_POINT_BUY_SCORE e MAX_POINT_BUY_SCORE
    if (Score < DnDConstants::MIN_POINT_BUY_SCORE || Score > DnDConstants::MAX_POINT_BUY_SCORE)
    {
        return 0;
    }

    // Tabela oficial D&D 5e Point Buy
    if (Score == DnDConstants::MIN_POINT_BUY_SCORE)
    {
        return 0;
    }
    else if (Score >= (DnDConstants::MIN_POINT_BUY_SCORE + 1) && Score <= (DnDConstants::MAX_POINT_BUY_SCORE - 2))
    {
        // Scores 9-13: custo = (score - BASE_ABILITY_SCORE)
        return Score - DnDConstants::BASE_ABILITY_SCORE;
    }
    else if (Score == DnDConstants::INTERMEDIATE_POINT_BUY_SCORE)
    {
        return DnDConstants::POINT_BUY_COST_14;
    }
    else if (Score == DnDConstants::MAX_POINT_BUY_SCORE)
    {
        return DnDConstants::POINT_BUY_COST_15;
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

TMap<FName, int32> CharacterSheetHelpers::CreatePointBuyMapFromData(int32 PointBuyStrength, int32 PointBuyDexterity,
                                                                    int32 PointBuyConstitution,
                                                                    int32 PointBuyIntelligence, int32 PointBuyWisdom,
                                                                    int32 PointBuyCharisma)
{
    TMap<FName, int32> PointBuyMap;
    TArray<FName> AbilityNames = GetAbilityScoreNames();
    TArray<int32> Values = {PointBuyStrength,     PointBuyDexterity, PointBuyConstitution,
                            PointBuyIntelligence, PointBuyWisdom,    PointBuyCharisma};

    // Garante que temos exatamente NUM_ABILITY_SCORES atributos
    check(AbilityNames.Num() == DnDConstants::NUM_ABILITY_SCORES);
    check(Values.Num() == DnDConstants::NUM_ABILITY_SCORES);

    for (int32 i = 0; i < AbilityNames.Num() && i < Values.Num(); ++i)
    {
        PointBuyMap.Add(AbilityNames[i], Values[i]);
    }

    return PointBuyMap;
}

TMap<FName, int32> CharacterSheetHelpers::CreateBaseScoresFromPointBuy(const TMap<FName, int32> &PointBuyMap)
{
    TMap<FName, int32> BaseScores;
    TArray<FName> AbilityNames = GetAbilityScoreNames();

    for (const FName &AbilityName : AbilityNames)
    {
        BaseScores.Add(AbilityName, DnDConstants::BASE_ABILITY_SCORE + PointBuyMap.FindRef(AbilityName));
    }

    return BaseScores;
}

FString CharacterSheetHelpers::AdjustPointBuyAllocation(TMap<FName, int32> &PointBuyMap, int32 MaxPoints)
{
    // Calcula custo atual
    TMap<FName, int32> BaseScores = CreateBaseScoresFromPointBuy(PointBuyMap);
    int32 CurrentCost = CalculateTotalPointBuyCost(BaseScores);

    // Se não excedeu, não precisa ajustar
    if (CurrentCost <= MaxPoints)
    {
        return FString::Printf(TEXT("Alocação válida (%d/%d pontos)"), CurrentCost, MaxPoints);
    }

    // Ordem de redução: do final da fila (Charisma, Wisdom, Intelligence, Constitution, Dexterity, Strength)
    // Isso mantém atributos mais importantes (Strength, Dexterity) intactos quando possível
    TArray<FName> ReductionOrder = {TEXT("Charisma"),     TEXT("Wisdom"),    TEXT("Intelligence"),
                                    TEXT("Constitution"), TEXT("Dexterity"), TEXT("Strength")};

    int32 ExcessPoints = CurrentCost - MaxPoints;
    int32 PointsReduced = 0;

    // Reduz valores do final da fila até que o custo seja <= MaxPoints
    for (FName &AbilityName : ReductionOrder)
    {
        if (ExcessPoints <= 0)
        {
            break;
        }

        int32 *CurrentValue = PointBuyMap.Find(AbilityName);
        if (!CurrentValue || *CurrentValue <= 0)
        {
            continue;
        }

        // Calcula quanto reduzir deste atributo
        int32 OldBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentValue;
        int32 OldCost = CalculatePointBuyCost(OldBaseScore);

        // Reduz 1 ponto de Point Buy
        (*CurrentValue)--;
        if (*CurrentValue < 0)
        {
            *CurrentValue = 0;
        }

        int32 NewBaseScore = DnDConstants::BASE_ABILITY_SCORE + *CurrentValue;
        int32 NewCost = CalculatePointBuyCost(NewBaseScore);
        int32 CostReduction = OldCost - NewCost;

        ExcessPoints -= CostReduction;
        PointsReduced += CostReduction;

        // Recalcula custo total para verificar se já está dentro do limite
        BaseScores = CreateBaseScoresFromPointBuy(PointBuyMap);
        CurrentCost = CalculateTotalPointBuyCost(BaseScores);
        ExcessPoints = CurrentCost - MaxPoints;
    }

    // Prepara mensagem de feedback
    if (PointsReduced > 0)
    {
        return FString::Printf(TEXT("Alocação ajustada: %d pontos removidos. Custo final: %d/%d"), PointsReduced,
                               CurrentCost, MaxPoints);
    }

    return FString::Printf(TEXT("Alocação ajustada. Custo final: %d/%d"), CurrentCost, MaxPoints);
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
