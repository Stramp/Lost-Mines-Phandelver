// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetHelpers.h"
#include "../Data/Tables/RaceDataTable.h"
#include "../Data/Tables/ClassDataTable.h"
#include "../Data/Tables/BackgroundDataTable.h"
#include "../Data/Tables/FeatDataTable.h"
#include "../Characters/Data/CharacterSheetDataAsset.h"

// ============================================================================
// Race Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllRaceNames(UDataTable *RaceDataTable)
{
    TArray<FName> RaceNames;

    if (!RaceDataTable)
    {
        return RaceNames;
    }

    TArray<FName> RowNames = RaceDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("GetAllRaceNames")))
        {
            if (Row->RaceName != NAME_None && Row->SubraceNames.Num() > 0)
            {
                RaceNames.AddUnique(Row->RaceName);
            }
        }
    }

    return RaceNames;
}

TArray<FName> CharacterSheetHelpers::GetAvailableSubraces(FName RaceName, UDataTable *RaceDataTable)
{
    TArray<FName> SubraceNames;

    if (!RaceDataTable || RaceName == NAME_None)
    {
        return SubraceNames;
    }

    TArray<FName> RowNames = RaceDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FRaceDataRow *Row = RaceDataTable->FindRow<FRaceDataRow>(RowName, TEXT("GetAvailableSubraces")))
        {
            if (Row->RaceName == RaceName)
            {
                SubraceNames = Row->SubraceNames;
                break;
            }
        }
    }

    return SubraceNames;
}

// ============================================================================
// Class Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllClassNames(UDataTable *ClassDataTable)
{
    TArray<FName> ClassNames;

    if (!ClassDataTable)
    {
        return ClassNames;
    }

    TArray<FName> RowNames = ClassDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("GetAllClassNames")))
        {
            if (Row->ClassName != NAME_None)
            {
                ClassNames.AddUnique(Row->ClassName);
            }
        }
    }

    return ClassNames;
}

TArray<FName> CharacterSheetHelpers::GetAvailableSubclasses(FName ClassName, UDataTable *ClassDataTable)
{
    TArray<FName> SubclassNames;

    if (!ClassDataTable || ClassName == NAME_None)
    {
        return SubclassNames;
    }

    TArray<FName> RowNames = ClassDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("GetAvailableSubclasses")))
        {
            if (Row->ClassName == ClassName)
            {
                SubclassNames = Row->SubclassNames;
                break;
            }
        }
    }

    return SubclassNames;
}

bool CharacterSheetHelpers::CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable *ClassDataTable)
{
    if (!ClassDataTable || ClassName == NAME_None || ClassLevel < 1)
    {
        return false;
    }

    // Em D&D 5e, subclasses são escolhidas no nível 3
    const int32 SubclassSelectionLevel = 3;

    if (ClassLevel < SubclassSelectionLevel)
    {
        return false;
    }

    // Verifica se a classe tem subclasses disponíveis
    TArray<FName> Subclasses = GetAvailableSubclasses(ClassName, ClassDataTable);
    return Subclasses.Num() > 0;
}

TArray<FClassFeature> CharacterSheetHelpers::GetFeaturesAtLevel(FName ClassName, int32 Level,
                                                                UDataTable *ClassDataTable)
{
    TArray<FClassFeature> Features;

    if (!ClassDataTable || ClassName == NAME_None || Level < 1)
    {
        return Features;
    }

    TArray<FName> RowNames = ClassDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FClassDataRow *Row = ClassDataTable->FindRow<FClassDataRow>(RowName, TEXT("GetFeaturesAtLevel")))
        {
            if (Row->ClassName == ClassName)
            {
                for (const FClassFeature &Feature : Row->Features)
                {
                    // Features persistem uma vez desbloqueadas (comportamento D&D 5e)
                    // Retorna todas as features desbloqueadas até o nível especificado
                    if (Feature.LevelUnlocked <= Level)
                    {
                        Features.Add(Feature);
                    }
                }
                break;
            }
        }
    }

    return Features;
}

// ============================================================================
// Background Data Table Helpers
// ============================================================================

TArray<FName> CharacterSheetHelpers::GetAllBackgroundNames(UDataTable *BackgroundDataTable)
{
    TArray<FName> BackgroundNames;

    if (!BackgroundDataTable)
    {
        return BackgroundNames;
    }

    TArray<FName> RowNames = BackgroundDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (FBackgroundDataRow *Row =
                BackgroundDataTable->FindRow<FBackgroundDataRow>(RowName, TEXT("GetAllBackgroundNames")))
        {
            if (Row->BackgroundName != NAME_None)
            {
                BackgroundNames.AddUnique(Row->BackgroundName);
            }
        }
    }

    return BackgroundNames;
}

// ============================================================================
// Feat Data Table Helpers
// ============================================================================

bool CharacterSheetHelpers::CanTakeFeatAtLevel(int32 TotalLevel)
{
    // Em D&D 5e, feats podem ser escolhidos nos níveis 4, 8, 12, 16, 19 (ou ao invés de ASI)
    TArray<int32> FeatLevels = {4, 8, 12, 16, 19};
    return FeatLevels.Contains(TotalLevel);
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
    TArray<FName> AvailableFeats;

    if (!FeatDataTable || TotalLevel < 1)
    {
        return AvailableFeats;
    }

    if (!CharacterSheetHelpers::CanTakeFeatAtLevel(TotalLevel))
    {
        return AvailableFeats;
    }

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
                AvailableFeats.AddUnique(Row->FeatName);
            }
        }
    }

    return AvailableFeats;
}

TArray<FName> CharacterSheetHelpers::GetAvailableFeatsForVariantHuman(const TMap<FName, int32> &AbilityScores,
                                                                      UDataTable *FeatDataTable)
{
    TArray<FName> AvailableFeats;

    if (!FeatDataTable)
    {
        return AvailableFeats;
    }

    // Variant Human pode escolher feat no nível 1 (bypassa verificação de nível)
    // Ainda valida pré-requisitos de ability scores
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
                AvailableFeats.AddUnique(Row->FeatName);
            }
        }
    }

    return AvailableFeats;
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
