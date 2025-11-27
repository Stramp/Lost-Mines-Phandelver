// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

// Forward declarations
struct FClassDataRow;

/**
 * Validators para requisitos de multiclasse baseados em atributos.
 * Responsável por validar se personagem atende requisitos de atributos para multiclasse.
 * Segue padrão de organização modular do projeto.
 */
class MYPROJECT2_API FMulticlassValidators
{
public:
    /**
     * Informação sobre um atributo (índice no array e nome completo).
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
     * @return Mapa de abreviação (ex: "STR") para FAttributeInfo
     */
    static TMap<FString, FAttributeInfo> CreateAttributeMap();

    /**
     * Parseia um requisito de atributo no formato "STR/13".
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
     * @param OrRequirementString String com requisitos OR separados por "|"
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutMissingTag Tag formatada com requisito faltante (ex: "[STR +2]")
     * @return true se pelo menos um requisito do OR foi satisfeito, false caso contrário
     */
    static bool ValidateOrRequirement(const FString &OrRequirementString, const TArray<int32> &Attributes,
                                      const TMap<FString, FAttributeInfo> &AttributeMap, FString &OutMissingTag);

    /**
     * Valida todos os requisitos de multiclasse de uma classe.
     * Requisitos são validados com lógica AND (todos devem ser satisfeitos).
     * Cada requisito pode ser OR (ex: "STR/13|DEX/13").
     * @param MulticlassRequirements Array de strings de requisitos (formato AND)
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutMissingTag Tag formatada com o primeiro requisito faltante
     * @return true se todos os requisitos foram satisfeitos, false caso contrário
     */
    static bool ValidateMulticlassRequirements(const TArray<FString> &MulticlassRequirements,
                                               const TArray<int32> &Attributes,
                                               const TMap<FString, FAttributeInfo> &AttributeMap,
                                               FString &OutMissingTag);

    /**
     * Processa uma classe e adiciona ao resultado com ou sem tag de requisito faltante.
     * @param ClassRow Linha da Data Table com dados da classe
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutResult Array onde a classe será adicionada (com ou sem tag)
     */
    static void ProcessClassWithRequirements(const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
                                             const TMap<FString, FAttributeInfo> &AttributeMap,
                                             TArray<FName> &OutResult);
};
