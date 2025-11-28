// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

// Forward declarations
struct FClassDataRow;
struct FMulticlassRequirement;
struct FMulticlassRequirementGroup;

// Include MulticlassHelpers para FAttributeInfo (sem dependência circular: Helpers não inclui Validators)
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"
// Include FMulticlassRequirement para nova estrutura normalizada
#include "Data/Structures/FMulticlassRequirement.h"

/**
 * Validators para requisitos de multiclasse baseados em atributos.
 * Responsável por validar se personagem atende requisitos de atributos para multiclasse.
 * Segue padrão de organização modular do projeto.
 *
 * NOTA: Helpers puros (CreateAttributeMap, ParseAttributeRequirement, ValidateOrRequirement)
 * foram movidos para FMulticlassHelpers para seguir Clean Code (helpers em arquivos de helpers).
 */
class MYPROJECT2_API FMulticlassValidators
{
public:
    /**
     * Número de atributos esperados (STR, DEX, CON, INT, WIS, CHA).
     * Usa DnDConstants::NUM_ABILITY_SCORES para consistência.
     * Mantido aqui para compatibilidade com código existente.
     */
    static constexpr int32 NUM_ATTRIBUTES = 6; // DnDConstants::NUM_ABILITY_SCORES

    /**
     * Valida todos os requisitos de multiclasse de uma classe.
     * Requisitos são validados com lógica AND (todos devem ser satisfeitos).
     * Cada requisito pode ser OR (ex: "STR/13|DEX/13").
     * Usa helpers de FMulticlassHelpers para parsing e validação OR.
     *
     * @param MulticlassRequirements Array de strings de requisitos (formato AND)
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos (de FMulticlassHelpers)
     * @param OutMissingTag Tag formatada com o primeiro requisito faltante
     * @return true se todos os requisitos foram satisfeitos, false caso contrário
     */
    static bool ValidateMulticlassRequirements(const TArray<FString> &MulticlassRequirements,
                                               const TArray<int32> &Attributes,
                                               const TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> &AttributeMap,
                                               FString &OutMissingTag);

    /**
     * Processa uma classe e adiciona ao resultado com ou sem tag de requisito faltante.
     * Tenta usar nova estrutura normalizada primeiro, com fallback para formato antigo.
     *
     * @param ClassRow Linha da Data Table com dados da classe
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos (de FMulticlassHelpers)
     * @param OutResult Array onde a classe será adicionada (com ou sem tag)
     * @param AbilityScoreDataTable Data Table de Ability Scores (opcional, necessário para nova estrutura)
     */
    static void ProcessClassWithRequirements(const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
                                             const TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> &AttributeMap,
                                             TArray<FName> &OutResult,
                                             const UDataTable *AbilityScoreDataTable = nullptr);

    /**
     * Valida um requisito individual de atributo.
     * Nova função usando estrutura normalizada (FMulticlassRequirement).
     *
     * @param Requirement Requisito individual a validar
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AbilityScoreDataTable Data Table de Ability Scores para mapear AbilityID → índice
     * @param OutMissingTag [OUT] Tag formatada com requisito faltante (ex: "[STR +2]")
     * @return true se requisito foi satisfeito, false caso contrário
     */
    static bool ValidateRequirement(const FMulticlassRequirement &Requirement, const TArray<int32> &Attributes,
                                    const UDataTable *AbilityScoreDataTable, FString &OutMissingTag);

    /**
     * Valida um grupo de requisitos (com operador OR ou AND).
     * Nova função usando estrutura normalizada (FMulticlassRequirementGroup).
     *
     * @param Group Grupo de requisitos a validar
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AbilityScoreDataTable Data Table de Ability Scores para mapear AbilityID → índice
     * @param OutMissingTag [OUT] Tag formatada com requisito faltante
     * @return true se grupo foi satisfeito, false caso contrário
     */
    static bool ValidateRequirementGroup(const FMulticlassRequirementGroup &Group, const TArray<int32> &Attributes,
                                         const UDataTable *AbilityScoreDataTable, FString &OutMissingTag);

    /**
     * Valida todos os grupos de requisitos de multiclasse (lógica AND entre grupos).
     * Nova função usando estrutura normalizada (TArray<FMulticlassRequirementGroup>).
     *
     * @param RequirementGroups Array de grupos de requisitos
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AbilityScoreDataTable Data Table de Ability Scores para mapear AbilityID → índice
     * @param OutMissingTag [OUT] Tag formatada com primeiro requisito faltante
     * @return true se todos os grupos foram satisfeitos, false caso contrário
     */
    static bool ValidateMulticlassRequirementGroups(const TArray<FMulticlassRequirementGroup> &RequirementGroups,
                                                    const TArray<int32> &Attributes,
                                                    const UDataTable *AbilityScoreDataTable, FString &OutMissingTag);
};
