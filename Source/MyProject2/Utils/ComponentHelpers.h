// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AActor;
class UCharacterDataComponent;

/**
 * Funções helper para busca e manipulação de componentes.
 * Funções puras e reutilizáveis seguindo princípios de Clean Code.
 */
namespace ComponentHelpers
{
    /**
     * Busca o CharacterDataComponent no Actor especificado.
     * Função pura, sem efeitos colaterais, parametrizada e reutilizável.
     *
     * @param Owner Actor onde buscar o componente
     * @return CharacterDataComponent encontrado ou nullptr se não existir
     */
    UCharacterDataComponent *FindCharacterDataComponent(AActor *Owner);
} // namespace ComponentHelpers
