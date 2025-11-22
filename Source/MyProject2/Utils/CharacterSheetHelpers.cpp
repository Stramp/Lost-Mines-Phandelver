// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetHelpers.h"
#include "../Data/Tables/RaceDataTable.h"
#include "../Data/Tables/ClassDataTable.h"
#include "../Data/Tables/BackgroundDataTable.h"
#include "../Data/Tables/FeatDataTable.h"

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
            if (Row->RaceName != NAME_None)
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
                    if (Feature.LevelUnlocked == Level)
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

namespace
{
    bool CanTakeFeatAtLevel(int32 TotalLevel)
    {
        // Em D&D 5e, feats podem ser escolhidos nos níveis 4, 8, 12, 16, 19 (ou ao invés de ASI)
        TArray<int32> FeatLevels = {4, 8, 12, 16, 19};
        return FeatLevels.Contains(TotalLevel);
    }

    bool MeetsFeatPrerequisites(const FFeatDataRow *Row, const TMap<FName, int32> &AbilityScores)
    {
        if (!Row)
        {
            return false;
        }

        // Validação básica: verifica se o pré-requisito está nos ability scores
        // Implementação simplificada - pode ser expandida para validação mais complexa
        for (const FName &Prerequisite : Row->Prerequisites)
        {
            if (Prerequisite != NAME_None)
            {
                // Por enquanto, apenas verifica se o pré-requisito não é um ability score requerido
                // Validação completa será implementada quando necessário
                return true;
            }
        }

        return true;
    }
} // namespace

TArray<FName> CharacterSheetHelpers::GetAvailableFeats(int32 TotalLevel, const TMap<FName, int32> &AbilityScores,
                                                       UDataTable *FeatDataTable)
{
    TArray<FName> AvailableFeats;

    if (!FeatDataTable || TotalLevel < 1)
    {
        return AvailableFeats;
    }

    if (!CanTakeFeatAtLevel(TotalLevel))
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

            if (MeetsFeatPrerequisites(Row, AbilityScores))
            {
                AvailableFeats.AddUnique(Row->FeatName);
            }
        }
    }

    return AvailableFeats;
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
