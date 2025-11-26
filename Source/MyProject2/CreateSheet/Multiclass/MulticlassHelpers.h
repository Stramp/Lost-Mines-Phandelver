// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;

/**
 * Helpers para validação e aplicação de regras de multiclasse.
 * Funções auxiliares reutilizáveis para o motor de multiclasse.
 */
class MYPROJECT2_API FMulticlassHelpers
{
public:
    /**
     * Retorna todos os nomes de classes disponíveis no Data Table.
     * Retorna os nomes sem prefixo (ex: "Fighter", "Wizard", "Rogue").
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @return Array com nomes das classes (sem prefixo), ou array vazio se Data Table inválido
     */
    static TArray<FName> GetAllClassNames(const UDataTable *ClassDataTable);

    /**
     * Retorna classes disponíveis com tags de requisitos faltantes.
     * Classes que não atendem requisitos terão tag como "[INT +13]" indicando o requisito faltante.
     *
     * @param ClassDataTable Data Table de classes (pode ser nullptr)
     * @param Attributes Array de atributos na ordem: [STR, DEX, CON, INT, WIS, CHA]
     * @return Array de FName com nomes das classes (com tags se não disponíveis)
     */
    static TArray<FName> GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                              const TArray<int32> &Attributes);
};
