// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

// Forward declarations
struct FClassDataRow;

// Include MulticlassHelpers para FAttributeInfo (sem dependência circular: Helpers não inclui Validators)
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

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
                                               const TMap<FString, FMulticlassHelpers::FAttributeInfo> &AttributeMap,
                                               FString &OutMissingTag);

    /**
     * Processa uma classe e adiciona ao resultado com ou sem tag de requisito faltante.
     * Usa FMulticlassHelpers::ValidateMulticlassRequirements para validação.
     *
     * @param ClassRow Linha da Data Table com dados da classe
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos (de FMulticlassHelpers)
     * @param OutResult Array onde a classe será adicionada (com ou sem tag)
     */
    static void ProcessClassWithRequirements(const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
                                             const TMap<FString, FMulticlassHelpers::FAttributeInfo> &AttributeMap,
                                             TArray<FName> &OutResult);
};
