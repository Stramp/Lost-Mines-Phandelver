// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "RaceBonusOrchestrator.h"

// Project includes - CreateSheet
#include "CreateSheet/RaceBonus/RaceBonusMotor.h"
#include "CreateSheet/RaceBonus/RaceDataLoader.h"
#include "CreateSheet/RaceBonus/RaceValidator.h"
#include "CreateSheet/RaceBonus/RaceBonusHelpers.h"

// Project includes - Data Structures
#include "Data/Structures/FCharacterSheetData.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Race Bonus Orchestrator
// ============================================================================
#pragma region Race Bonus Orchestrator

void FRaceBonusOrchestrator::ProcessRacialBonuses(FCharacterSheetData& Data)
{
    FLogContext Context(TEXT("RaceBonusOrchestrator"), TEXT("ProcessRacialBonuses"));

    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        FLoggingSystem::LogError(Context, TEXT("Referências de Final Scores inválidas"), true);
        return;
    }

    // 1. Busca dados (Loader)
    FRaceDataLoader::FRaceData RaceData = FRaceDataLoader::Load(Data);

    // 2. Valida sub-raça (Validator)
    if (RaceData.RaceRow && Data.SelectedSubrace != NAME_None)
    {
        if (!FRaceValidator::ValidateSubrace(RaceData.RaceRow, Data.SelectedSubrace))
        {
            // Logging (responsabilidade do orquestrador)
            FLoggingSystem::LogWarning(
                Context,
                FString::Printf(
                    TEXT("Sub-raça '%s' não pertence à raça '%s'. Bônus de sub-raça não será aplicado."),
                    *Data.SelectedSubrace.ToString(), *Data.SelectedRace.ToString()),
                false);
            RaceData.SubraceRow = nullptr; // Remove sub-raça inválida
        }
        else if (!RaceData.SubraceRow)
        {
            // Logging (responsabilidade do orquestrador)
            FLoggingSystem::LogWarning(
                Context,
                FString::Printf(TEXT("Sub-raça '%s' não encontrada no RaceDataTable"), *Data.SelectedSubrace.ToString()),
                false);
        }
    }

    // 3. Calcula bônus raciais (Helpers)
    TMap<FName, int32> RacialBonuses;
    FRaceBonusHelpers::CalculateRacialBonuses(RaceData.RaceRow, RaceData.SubraceRow, Data.CustomAbilityScoreChoices,
                                               RacialBonuses);

    // 4. Aplica bônus raciais (Motor puro)
    FRaceBonusMotor::ApplyRacialBonuses(RacialBonuses, *Data.FinalStrength, *Data.FinalDexterity, *Data.FinalConstitution,
                                        *Data.FinalIntelligence, *Data.FinalWisdom, *Data.FinalCharisma);

    // Logging (responsabilidade do orquestrador)
    if (RacialBonuses.Num() > 0)
    {
        FLoggingSystem::LogInfo(Context, TEXT("Bônus raciais aplicados com sucesso"));
    }
}

#pragma endregion Race Bonus Orchestrator
