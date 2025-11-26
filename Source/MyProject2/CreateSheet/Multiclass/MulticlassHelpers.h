// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UDataTable;

// Forward declarations
class UCharacterSheetDataAsset;
struct FMulticlassEntry;

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
     * Ajusta o tamanho do array Progression para corresponder ao LevelInClass.
     * Garante que cada elemento tenha o Level correto (1, 2, 3, etc.).
     *
     * @param Entry Entrada de multiclasse a ajustar
     * @return true se ajustou o array, false caso contrário
     */
    static bool AdjustProgressionArraySize(FMulticlassEntry &Entry);

    /**
     * Ajusta o array Progression para todas as entradas de multiclasse.
     * Itera sobre todas as entradas e ajusta cada uma.
     * Chama o motor de multiclasse para processar cada mudança de nível.
     *
     * @param Asset Asset do personagem
     * @return Número de entradas ajustadas
     */
    static int32 AdjustAllMulticlassProgressionArrays(UCharacterSheetDataAsset *Asset);
};
