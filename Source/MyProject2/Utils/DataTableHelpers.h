// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableHelpers.generated.h"

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
struct FAbilityScoreDataRow;

// ============================================================================
// Name With ID Struct
// ============================================================================
#pragma region Name With ID Struct

/**
 * Struct para retornar Name + ID juntos.
 * Sempre que retornamos dados parciais (não o Row completo), incluímos o ID junto.
 * O ID é a referência exata do dado na Data Table.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FNameWithID
{
    GENERATED_BODY()

    /** Nome legível (ex: "Human", "Strength", "Athletics") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FName Name;

    /** ID único (ex: "RACE_Human", "ABL_Strength", "PW_Skill_Athletics") - Referência exata na Data Table */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FName ID;

    FNameWithID() : Name(NAME_None), ID(NAME_None) {}

    FNameWithID(const FName &InName, const FName &InID) : Name(InName), ID(InID) {}
};

#pragma endregion Name With ID Struct

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
    // Ability Score Data Table Helpers
    // ============================================================================

    /**
     * Busca row de ability score no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param AbilityID ID do ability score para buscar (ex: "ABL_Strength", "ABL_Dexterity")
     * @param AbilityScoreDataTable Data Table de ability scores (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FAbilityScoreDataRow *FindAbilityScoreRow(FName AbilityID, UDataTable *AbilityScoreDataTable);

    /**
     * Retorna todos os nomes de ability scores do Data Table com seus IDs.
     * Se Data Table não fornecido, retorna array vazio.
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * @param AbilityScoreDataTable Data Table de ability scores (pode ser nullptr)
     * @return Array com Name + ID de ability scores (do Data Table ou vazio)
     */
    TArray<FNameWithID> GetAllAbilityScoreNames(UDataTable *AbilityScoreDataTable);

    // ============================================================================
    // Race Data Table Helpers
    // ============================================================================

    /**
     * Busca row de raça no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param RaceID ID da raça para buscar (ex: "RACE_Human", "RACE_Elf")
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindRaceRow(FName RaceID, UDataTable *RaceDataTable);

    /**
     * Busca row de sub-raça no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param SubraceID ID da sub-raça para buscar
     * @param RaceDataTable Data Table de raças (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FRaceDataRow *FindSubraceRow(FName SubraceID, UDataTable *RaceDataTable);

    // ============================================================================
    // Class Data Table Helpers
    // ============================================================================

    /**
     * Busca row de classe no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param ClassID ID da classe para buscar (ex: "CLASS_Fighter", "CLASS_Wizard")
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FClassDataRow *FindClassRow(FName ClassID, UDataTable *ClassDataTable);

    // ============================================================================
    // Feat Data Table Helpers
    // ============================================================================

    /**
     * Busca row de feat no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param FeatID ID do feat para buscar (ex: "Feat_Alert", "Feat_MagicInitiate")
     * @param FeatDataTable Data Table de feats (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FFeatDataRow *FindFeatRow(FName FeatID, UDataTable *FeatDataTable);

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
     * Busca row de background no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param BackgroundID ID do background para buscar (ex: "BG_Acolyte", "BG_Criminal")
     * @param BackgroundDataTable Data Table de backgrounds (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FBackgroundDataRow *FindBackgroundRow(FName BackgroundID, UDataTable *BackgroundDataTable);

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
     * Retorna todos os nomes de proficiências de um tipo específico no ProficiencyDataTable com seus IDs.
     * Função genérica que filtra proficiências por tipo (ex: "Skill", "Language", "Weapon", etc.).
     * Helper interno reutilizável para evitar duplicação de código (DRY).
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @param ProficiencyType Tipo de proficiência para filtrar (ex: "Skill", "Language")
     * @return Array com Name + ID de todas as proficiências do tipo especificado, ou array vazio se Data Table inválido
     * ou sem proficiências do tipo
     */
    TArray<FNameWithID> GetProficiencyNamesByType(UDataTable *ProficiencyDataTable, FName ProficiencyType);

    /**
     * Retorna todos os nomes de skills disponíveis no ProficiencyDataTable com seus IDs.
     * Filtra apenas proficiências do tipo "Skill".
     * Wrapper que chama GetProficiencyNamesByType com tipo "Skill".
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com Name + ID de todas as skills, ou array vazio se Data Table inválido ou sem skills
     */
    TArray<FNameWithID> GetAllSkillNames(UDataTable *ProficiencyDataTable);

    /**
     * Retorna todos os nomes de languages disponíveis no ProficiencyDataTable com seus IDs.
     * Filtra apenas proficiências do tipo "Language".
     * Wrapper que chama GetProficiencyNamesByType com tipo "Language".
     * Sempre retorna Name + ID juntos (ID é a referência exata na Data Table).
     *
     * @param ProficiencyDataTable Data Table de proficiências (pode ser nullptr)
     * @return Array com Name + ID de todos os languages, ou array vazio se Data Table inválido ou sem languages
     */
    TArray<FNameWithID> GetAllLanguageNames(UDataTable *ProficiencyDataTable);

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

    // ============================================================================
    // Item Data Table Helpers
    // ============================================================================

    /**
     * Busca row de item no Data Table pelo ID.
     * Busca manual O(n) comparando ID de cada row.
     *
     * @param ItemID ID do item para buscar (ex: "ITM_ARM_LeatherArmor", "ITM_ARM_ChainMail")
     * @param ItemDataTable Data Table de itens (pode ser nullptr)
     * @return Row encontrado, ou nullptr se não encontrado ou Data Table inválido
     */
    FItemDataRow *FindItemRow(FName ItemID, UDataTable *ItemDataTable);
} // namespace DataTableHelpers
