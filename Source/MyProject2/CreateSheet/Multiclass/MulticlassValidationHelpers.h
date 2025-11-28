// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#pragma endregion Includes

// Forward declarations
class UDataTable;
struct FClassDataRow;
struct FMulticlassClassFeature;

/**
 * Helpers de validação para multiclasse.
 * Funções auxiliares para validação de inputs, requisitos e estruturas.
 */
class MYPROJECT2_API FMulticlassValidationHelpers
{
public:
    // ============================================================================
    // Progression Validation
    // ============================================================================

    /**
     * Valida se é permitido processar Progression para uma entrada de multiclasse.
     * Regra: Progression só pode ser processada se há classe válida (Name != NAME_None) e nível > 0.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe
     * @return true se é válido processar Progression, false caso contrário
     */
    static bool CanProcessProgression(FName ClassName, int32 LevelInClass);

    /**
     * Valida parâmetros de entrada para carregamento de proficiências.
     * Proficiências são ganhas apenas no nível 1.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe (deve ser 1)
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    static bool ValidateLoadProficienciesInputs(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);

    /**
     * Valida parâmetros de entrada para ProcessLevelChange.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param LevelInClass Nível na classe
     * @param ClassDataTable Data Table de classes
     * @return true se parâmetros são válidos, false caso contrário
     */
    static bool ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);

    /**
     * Busca e valida dados da classe na tabela.
     * Função pura e testável, sem side effects.
     *
     * @param ClassName Nome da classe
     * @param ClassDataTable Data Table de classes
     * @return Row da classe encontrada, ou nullptr se não encontrada
     */
    static const FClassDataRow *FindAndValidateClassRow(FName ClassName, const UDataTable *ClassDataTable);

    /**
     * Verifica se uma feature tem escolhas disponíveis para o jogador.
     * Retorna true se FeatureType é "Choice" ou "SubclassSelection" E bHasAvailableChoices é true.
     * Helper puro e testável, sem side effects.
     *
     * @param Feature Feature a verificar
     * @return true se feature tem escolhas disponíveis, false caso contrário
     */
    static bool FeatureHasAvailableChoices(const FMulticlassClassFeature &Feature);

    // ============================================================================
    // Attribute Helpers (used for validation)
    // ============================================================================

    /**
     * Informação sobre um atributo (índice no array e nome completo).
     * Usado para mapear abreviações de atributos (ex: "STR") para índices e nomes completos.
     */
    struct FAttributeInfo
    {
        int32 Index;
        FString FullName;
    };

    /**
     * Número de atributos esperados (STR, DEX, CON, INT, WIS, CHA).
     * Usa DnDConstants::NUM_ABILITY_SCORES para consistência.
     */
    static constexpr int32 NUM_ATTRIBUTES = 6; // DnDConstants::NUM_ABILITY_SCORES

    /**
     * Cria o mapa de atributos com suas abreviações e índices.
     * Helper puro e reutilizável para criar mapa de atributos.
     *
     * @return Mapa de abreviação (ex: "STR") para FAttributeInfo
     */
    static TMap<FString, FAttributeInfo> CreateAttributeMap();

    /**
     * Parseia um requisito de atributo no formato "STR/13".
     * Helper puro e reutilizável para parsing de strings de requisitos.
     *
     * @param RequirementString String no formato "ATTR/VALUE" (ex: "STR/13")
     * @param OutAttribute Abreviação do atributo (ex: "STR")
     * @param OutRequiredValue Valor requerido (ex: 13)
     * @return true se o parse foi bem-sucedido, false caso contrário
     */
    static bool ParseAttributeRequirement(const FString &RequirementString, FString &OutAttribute,
                                          int32 &OutRequiredValue);

    /**
     * Valida se um requisito OR é satisfeito pelos atributos do personagem.
     * Um requisito OR tem formato "STR/13|DEX/13" (STR 13 OU DEX 13).
     * Helper puro e reutilizável para validação de requisitos OR.
     *
     * @param OrRequirementString String com requisitos OR separados por "|"
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutMissingTag Tag formatada com requisito faltante (ex: "[STR +2]")
     * @return true se pelo menos um requisito do OR foi satisfeito, false caso contrário
     */
    static bool ValidateOrRequirement(const FString &OrRequirementString, const TArray<int32> &Attributes,
                                      const TMap<FString, FAttributeInfo> &AttributeMap, FString &OutMissingTag);

    /**
     * Mapeia AbilityID (ex: "ABL_Strength") para índice no array de atributos [STR, DEX, CON, INT, WIS, CHA].
     * Helper puro e reutilizável para conversão de AbilityID para índice.
     * Usa AbilityScoreDataTable para buscar informações do atributo.
     *
     * @param AbilityID ID do atributo (ex: "ABL_Strength", "ABL_Dexterity")
     * @param AbilityScoreDataTable Data Table de Ability Scores (pode ser nullptr)
     * @param OutIndex [OUT] Índice no array de atributos (0-5) ou -1 se não encontrado
     * @return true se AbilityID foi encontrado e mapeado, false caso contrário
     */
    static bool MapAbilityIDToIndex(FName AbilityID, const UDataTable *AbilityScoreDataTable, int32 &OutIndex);
};
