// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Helpers para manipulação de escolhas (choices) e metadados.
 * Funções reutilizáveis para evitar duplicação de código.
 */
namespace ChoiceHelpers
{
    /**
     * Converte string separada por vírgulas em TArray<FName>.
     * Remove espaços em branco e valores vazios.
     *
     * @param OptionsString String com opções separadas por vírgulas (ex: "Archery,Defense,Dueling")
     * @return Array de FName com as opções parseadas
     */
    TArray<FName> ParseOptionsString(const FString &OptionsString);

    /**
     * Converte TArray<FName> em string separada por vírgulas.
     *
     * @param Options Array de opções
     * @return String formatada (ex: "Archery,Defense,Dueling")
     */
    FString FormatOptionsString(const TArray<FName> &Options);
} // namespace ChoiceHelpers

/**
 * Constantes para chaves de Metadata de escolhas.
 * Evita magic strings e facilita manutenção.
 */
namespace ChoiceMetadataKeys
{
    constexpr const TCHAR *AvailableOptions = TEXT("AvailableOptions");
    constexpr const TCHAR *ChoicesAllowed = TEXT("ChoicesAllowed");
    constexpr const TCHAR *DependsOn = TEXT("DependsOn");
    constexpr const TCHAR *RequiredValue = TEXT("RequiredValue");
} // namespace ChoiceMetadataKeys
