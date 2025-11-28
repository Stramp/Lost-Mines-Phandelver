// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

// Forward declarations
class UDataTable;

/**
 * Funções helper para manipulação de Gameplay Tags.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 */
namespace GameplayTagHelpers
{
    /**
     * Verifica se um GameplayTagContainer contém uma tag específica.
     *
     * @param Container Container de tags a verificar
     * @param Tag Tag a procurar (ex: "Race.Elf")
     * @return true se contém a tag, false caso contrário
     */
    bool HasTag(const FGameplayTagContainer& Container, const FGameplayTag& Tag);

    /**
     * Verifica se um GameplayTagContainer contém qualquer tag de um grupo.
     *
     * @param Container Container de tags a verificar
     * @param TagGroup Tag pai (ex: "Race" verifica Race.*)
     * @return true se contém alguma tag do grupo, false caso contrário
     */
    bool HasAnyTagInGroup(const FGameplayTagContainer& Container, const FGameplayTag& TagGroup);

    /**
     * Converte FName para FGameplayTag.
     *
     * @param TagName Nome da tag (ex: "Race.Elf")
     * @return GameplayTag correspondente, ou Tag inválida se não encontrada
     */
    FGameplayTag NameToTag(const FName& TagName);

    /**
     * Converte FGameplayTag para FName.
     *
     * @param Tag GameplayTag a converter
     * @return Nome da tag, ou NAME_None se inválida
     */
    FName TagToName(const FGameplayTag& Tag);
} // namespace GameplayTagHelpers
