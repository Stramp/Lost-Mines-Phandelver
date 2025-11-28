// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

// Forward declarations
class UDataTable;
class UScriptStruct;
struct FRaceDataRow;
struct FClassDataRow;
struct FFeatDataRow;
struct FBackgroundDataRow;
struct FProficiencyDataRow;
struct FFeatureDataRow;
struct FItemDataRow;

/**
 * Funções helper para busca de rows em Data Tables com fallback manual.
 * Centraliza lógica de busca que pode falhar com FindRow direto.
 *
 * Todas as funções são:
 * - Puras (sem efeitos colaterais)
 * - Parametrizadas (sem dependência de estado interno)
 * - Testáveis isoladamente
 * - < 50 linhas cada
 */
namespace DataTableHelpers
{
    // ============================================================================
    // Race Data Table Helpers
    // ============================================================================

    /**
     * Busca row de raça no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param RaceName Nome da raça para buscar
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindRaceRow(FName RaceName, UDataTable *RaceDataTable);

    /**
     * Busca row de sub-raça no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param SubraceName Nome da sub-raça para buscar
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindSubraceRow(FName SubraceName, UDataTable *RaceDataTable);

    // ============================================================================
    // Class Data Table Helpers
    // ============================================================================

    /**
     * Busca row de classe no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param ClassName Nome da classe para buscar
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FClassDataRow *FindClassRow(FName ClassName, UDataTable *ClassDataTable);

    // ============================================================================
    // Feat Data Table Helpers
    // ============================================================================

    /**
     * Busca row de feat no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param FeatName Nome do feat para buscar
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FFeatDataRow *FindFeatRow(FName FeatName, UDataTable *FeatDataTable);

    /**
     * Converte Name de feat para ID.
     * Busca feat pelo Name e retorna seu ID.
     * Retorna NAME_None se feat não encontrado ou Data Table inválido.
     *
     * @param FeatName Name do feat (ex: "Magic Initiate")
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return ID do feat (ex: "Feat_MagicInitiate") ou NAME_None se não encontrado
     */
    FName ConvertFeatNameToFCID(FName FeatName, UDataTable *FeatDataTable);

    // ============================================================================
    // Background Data Table Helpers
    // ============================================================================

    /**
     * Busca row de background no Data Table.
     * Tenta FindRow direto primeiro, depois busca manual O(n) como fallback.
     *
     * @param BackgroundName Nome do background para buscar
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FBackgroundDataRow *FindBackgroundRow(FName BackgroundName, UDataTable *BackgroundDataTable);

    // ============================================================================
    // Proficiency Data Table Helpers
    // ============================================================================

    /**
     * Busca row de proficiência no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param ProficiencyID ID da proficiência para buscar (ex: "PW_Simple_Weapons")
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FProficiencyDataRow *FindProficiencyRowByID(FName ProficiencyID, UDataTable *ProficiencyDataTable);

    /**
     * Retorna todos os nomes de proficiências de um tipo específico no ProficiencyDataTable.
     * Função genérica que filtra proficiências por tipo (ex: "Skill", "Language", "Weapon", etc.).
     * Helper interno reutilizável para evitar duplicação de código (DRY).
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @param ProficiencyType Tipo de proficiência para filtrar (ex: "Skill", "Language")
     * @return Array com nomes de todas as proficiências do tipo especificado, ou array vazio se Data Table inválido ou
     * sem proficiências do tipo
     */
    TArray<FName> GetProficiencyNamesByType(UDataTable *ProficiencyDataTable, FName ProficiencyType);

    /**
     * Retorna todos os nomes de skills disponíveis no ProficiencyDataTable.
     * Filtra apenas proficiências do tipo "Skill".
     * Wrapper que chama GetProficiencyNamesByType com tipo "Skill".
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes de todas as skills, ou array vazio se Data Table inválido ou sem skills
     */
    TArray<FName> GetAllSkillNames(UDataTable *ProficiencyDataTable);

    /**
     * Retorna todos os nomes de languages disponíveis no ProficiencyDataTable.
     * Filtra apenas proficiências do tipo "Language".
     * Wrapper que chama GetProficiencyNamesByType com tipo "Language".
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com nomes de todos os languages, ou array vazio se Data Table inválido ou sem languages
     */
    TArray<FName> GetAllLanguageNames(UDataTable *ProficiencyDataTable);

    // ============================================================================
    // Feature Data Table Helpers
    // ============================================================================

    /**
     * Busca row de feature no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param FeatureID ID da feature para buscar (ex: "FC_SecondWind", "FC_FightingStyle")
     * @param FeatureDataTable Data Table de features (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FFeatureDataRow *FindFeatureRowByID(FName FeatureID, UDataTable *FeatureDataTable);

    // ============================================================================
    // Data Table Type Validation Helpers
    // ============================================================================

    /**
     * Valida se DataTable tem RowStruct do tipo esperado.
     * Compara o nome do RowStruct com o struct esperado.
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @param ExpectedStruct Struct esperado (ex: FRaceDataRow::StaticStruct())
     * @return true se RowStruct corresponde ao esperado, false caso contrário
     */
    bool ValidateDataTableRowStruct(UDataTable *DataTable, const UScriptStruct *ExpectedStruct);

    /**
     * Valida se DataTable é do tipo RaceDataTable (tem RowStruct FRaceDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é RaceDataTable, false caso contrário
     */
    bool IsRaceDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo ClassDataTable (tem RowStruct FClassDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é ClassDataTable, false caso contrário
     */
    bool IsClassDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo BackgroundDataTable (tem RowStruct FBackgroundDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é BackgroundDataTable, false caso contrário
     */
    bool IsBackgroundDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo FeatDataTable (tem RowStruct FFeatDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é FeatDataTable, false caso contrário
     */
    bool IsFeatDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo FeatureDataTable (tem RowStruct FFeatureDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é FeatureDataTable, false caso contrário
     */
    bool IsFeatureDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo ProficiencyDataTable (tem RowStruct FProficiencyDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é ProficiencyDataTable, false caso contrário
     */
    bool IsProficiencyDataTable(UDataTable *DataTable);

    /**
     * Valida se DataTable é do tipo ItemDataTable (tem RowStruct FItemDataRow).
     *
     * @param DataTable Data Table a validar (pode ser nullptr)
     * @return true se é ItemDataTable, false caso contrário
     */
    bool IsItemDataTable(UDataTable *DataTable);
} // namespace DataTableHelpers
