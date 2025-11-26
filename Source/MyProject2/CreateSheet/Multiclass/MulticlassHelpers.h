// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;

/**
 * Helpers para estrutura de dados de multiclasse.
 * Funções auxiliares para manipulação de arrays e estruturas de multiclasse.
 * Validação de atributos está em FMulticlassValidators.
 */
class MYPROJECT2_API FMulticlassHelpers
{
public:
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
};
