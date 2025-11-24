// Copyright Epic Games, Inc. All Rights Reserved.

#include "RaceBonusMotor.h"
#include "RaceBonusHelpers.h"
#include "CreateSheet/Core/CharacterSheetData.h"
#include "Data/Tables/RaceDataTable.h"
#include "Utils/DataTableHelpers.h"
#include "Logging/LogMacros.h"

void FRaceBonusMotor::ApplyRacialBonuses(FCharacterSheetData &Data)
{
    // Valida referências de saída
    if (!Data.FinalStrength || !Data.FinalDexterity || !Data.FinalConstitution || !Data.FinalIntelligence ||
        !Data.FinalWisdom || !Data.FinalCharisma)
    {
        UE_LOG(LogTemp, Error, TEXT("RaceBonusMotor: Referências de Final Scores inválidas"));
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
            // Validar se a sub-raça pertence à raça selecionada
            bool bSubraceValid = RaceRow->SubraceNames.Contains(Data.SelectedSubrace);

            if (!bSubraceValid)
            {
                // Aviso: sub-raça inválida (validação deve ser feita pelo caller - Data Asset ou Widget)
                UE_LOG(LogTemp, Warning,
                       TEXT("RaceBonusMotor: Sub-raça '%s' não pertence à raça '%s'. Bônus de sub-raça não será "
                            "aplicado."),
                       *Data.SelectedSubrace.ToString(), *Data.SelectedRace.ToString());
            }
            else
            {
                // Usa DataTableHelpers para buscar row de sub-raça (remove código duplicado)
                SubraceRow = DataTableHelpers::FindSubraceRow(Data.SelectedSubrace, Data.RaceDataTable);

                if (!SubraceRow)
                {
                    UE_LOG(LogTemp, Warning, TEXT("RaceBonusMotor: Sub-raça '%s' não encontrada no RaceDataTable"),
                           *Data.SelectedSubrace.ToString());
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
