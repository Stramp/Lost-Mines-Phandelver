// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
struct FRaceDataRow;

/**
 * Estrutura genérica de dados para criação de ficha.
 * Usada pelo Core genérico para funcionar tanto no Data Asset quanto no Widget.
 *
 * Princípio: "Program to an interface, not an implementation" (Design Patterns)
 * O Core recebe dados puros, não objetos concretos, permitindo reutilização.
 *
 * Nota: Struct C++ normal (não USTRUCT) porque contém ponteiros e não precisa
 * ser exposta ao Blueprint. Usada apenas internamente para comunicação entre motores.
 */
struct MYPROJECT2_API FCharacterSheetData
{
    // ============================================================================
    // Point Buy Allocation (Input)
    // ============================================================================

    /** Pontos alocados para Strength (0-7) */
    int32 PointBuyStrength = 0;

    /** Pontos alocados para Dexterity (0-7) */
    int32 PointBuyDexterity = 0;

    /** Pontos alocados para Constitution (0-7) */
    int32 PointBuyConstitution = 0;

    /** Pontos alocados para Intelligence (0-7) */
    int32 PointBuyIntelligence = 0;

    /** Pontos alocados para Wisdom (0-7) */
    int32 PointBuyWisdom = 0;

    /** Pontos alocados para Charisma (0-7) */
    int32 PointBuyCharisma = 0;

    // ============================================================================
    // Race Data (Input)
    // ============================================================================

    /** Raça selecionada */
    FName SelectedRace = NAME_None;

    /** Sub-raça selecionada */
    FName SelectedSubrace = NAME_None;

    /** Escolhas customizadas de Ability Score (para Variant Human) */
    TArray<FName> CustomAbilityScoreChoices;

    /** Data Table de raças */
    UDataTable *RaceDataTable = nullptr;

    // ============================================================================
    // Final Scores (Output - referências para modificar diretamente)
    // ============================================================================

    /** Referência para Final Strength (será modificado pelo Core) */
    int32 *FinalStrength = nullptr;

    /** Referência para Final Dexterity (será modificado pelo Core) */
    int32 *FinalDexterity = nullptr;

    /** Referência para Final Constitution (será modificado pelo Core) */
    int32 *FinalConstitution = nullptr;

    /** Referência para Final Intelligence (será modificado pelo Core) */
    int32 *FinalIntelligence = nullptr;

    /** Referência para Final Wisdom (será modificado pelo Core) */
    int32 *FinalWisdom = nullptr;

    /** Referência para Final Charisma (será modificado pelo Core) */
    int32 *FinalCharisma = nullptr;

    // ============================================================================
    // Constructors
    // ============================================================================

    FCharacterSheetData() {}

    /**
     * Construtor completo para inicializar todos os dados.
     *
     * @param InPointBuyStrength Point Buy para Strength
     * @param InPointBuyDexterity Point Buy para Dexterity
     * @param InPointBuyConstitution Point Buy para Constitution
     * @param InPointBuyIntelligence Point Buy para Intelligence
     * @param InPointBuyWisdom Point Buy para Wisdom
     * @param InPointBuyCharisma Point Buy para Charisma
     * @param InSelectedRace Raça selecionada
     * @param InSelectedSubrace Sub-raça selecionada
     * @param InCustomAbilityScoreChoices Escolhas customizadas (Variant Human)
     * @param InRaceDataTable Data Table de raças
     * @param InFinalStrength Referência para Final Strength
     * @param InFinalDexterity Referência para Final Dexterity
     * @param InFinalConstitution Referência para Final Constitution
     * @param InFinalIntelligence Referência para Final Intelligence
     * @param InFinalWisdom Referência para Final Wisdom
     * @param InFinalCharisma Referência para Final Charisma
     */
    FCharacterSheetData(int32 InPointBuyStrength, int32 InPointBuyDexterity, int32 InPointBuyConstitution,
                        int32 InPointBuyIntelligence, int32 InPointBuyWisdom, int32 InPointBuyCharisma,
                        FName InSelectedRace, FName InSelectedSubrace, const TArray<FName> &InCustomAbilityScoreChoices,
                        UDataTable *InRaceDataTable, int32 *InFinalStrength, int32 *InFinalDexterity,
                        int32 *InFinalConstitution, int32 *InFinalIntelligence, int32 *InFinalWisdom,
                        int32 *InFinalCharisma)
        : PointBuyStrength(InPointBuyStrength), PointBuyDexterity(InPointBuyDexterity),
          PointBuyConstitution(InPointBuyConstitution), PointBuyIntelligence(InPointBuyIntelligence),
          PointBuyWisdom(InPointBuyWisdom), PointBuyCharisma(InPointBuyCharisma), SelectedRace(InSelectedRace),
          SelectedSubrace(InSelectedSubrace), CustomAbilityScoreChoices(InCustomAbilityScoreChoices),
          RaceDataTable(InRaceDataTable), FinalStrength(InFinalStrength), FinalDexterity(InFinalDexterity),
          FinalConstitution(InFinalConstitution), FinalIntelligence(InFinalIntelligence), FinalWisdom(InFinalWisdom),
          FinalCharisma(InFinalCharisma)
    {
    }
};
