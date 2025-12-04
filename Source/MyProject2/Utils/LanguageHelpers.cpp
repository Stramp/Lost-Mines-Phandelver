// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetHelpers.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/TraitDataTable.h"
#include "Data/Tables/LanguageDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"

#pragma endregion Includes

// ============================================================================
// Language Helpers
// ============================================================================
#pragma region Language Helpers

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
    TArray<FNameWithID> AllLanguagesWithIDs = GetAvailableLanguageNames(ProficiencyDataTable);
    TArray<FName> AllLanguages;
    for (const FNameWithID &LanguageWithID : AllLanguagesWithIDs)
    {
        AllLanguages.Add(LanguageWithID.Name);
    }

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

#pragma endregion Language Helpers
