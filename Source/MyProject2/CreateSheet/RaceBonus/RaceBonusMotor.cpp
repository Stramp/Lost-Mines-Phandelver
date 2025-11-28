// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceBonusMotor.h"
#include "RaceBonusHelpers.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

void FRaceBonusMotor::ApplyRacialBonuses(FCharacterSheetData &Data)
{
    FLogContext Context(TEXT("RaceBonus"), TEXT("ApplyRacialBonuses"));

    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
        return;
    }

    // Calcula bônus raciais
    TMap<FName, int32> RacialBonuses;
    if (Data.RaceDataTable && Data.SelectedRace != NAME_None)
    {
        // Usa DataTableHelpers para buscar row de raça (remove código duplicado)
        FRaceDataRow *RaceRow = DataTableHelpers::FindRaceRow(Data.SelectedRace, Data.RaceDataTable);

        // Busca sub-raça se necessário
        FRaceDataRow *SubraceRow = nullptr;
        if (RaceRow && Data.SelectedSubrace != NAME_None)
        {
            // Validar se a sub-raça pertence à raça selecionada (agora via SubraceHandles)
            bool bSubraceValid = false;
            for (const FDataTableRowHandle &SubraceHandle : RaceRow->SubraceHandles)
            {
                if (SubraceHandle.RowName == Data.SelectedSubrace)
                {
                    bSubraceValid = true;
                    break;
                }
            }

            if (!bSubraceValid)
            {
                // Aviso: sub-raça inválida (sistema ajusta automaticamente - sem popup)
                FLoggingSystem::LogWarning(
                    Context,
                    FString::Printf(
                        TEXT("Sub-raça '%s' não pertence à raça '%s'. Bônus de sub-raça não será aplicado."),
                        *Data.SelectedSubrace.ToString(), *Data.SelectedRace.ToString()),
                    false);
            }
            else
            {
                // Usa DataTableHelpers para buscar row de sub-raça (remove código duplicado)
                SubraceRow = DataTableHelpers::FindSubraceRow(Data.SelectedSubrace, Data.RaceDataTable);

                if (!SubraceRow)
                {
                    // Aviso: sub-raça não encontrada (sistema ajusta automaticamente - sem popup)
                    FLoggingSystem::LogWarning(Context,
                                               FString::Printf(TEXT("Sub-raça '%s' não encontrada no RaceDataTable"),
                                                               *Data.SelectedSubrace.ToString()),
                                               false);
                }
            }
        }

        // Calcula bônus raciais usando RaceBonusHelpers (função pura)
        FRaceBonusHelpers::CalculateRacialBonuses(RaceRow, SubraceRow, Data.CustomAbilityScoreChoices, RacialBonuses);
    }

    // Incrementa com bônus raciais (motor independente)
    FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses(RacialBonuses, *Data.FinalStrength, *Data.FinalDexterity,
                                                             *Data.FinalConstitution, *Data.FinalIntelligence,
                                                             *Data.FinalWisdom, *Data.FinalCharisma);
}
