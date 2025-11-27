// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Forward declarations
class UCharacterSheetDataAsset;

/**
 * Tipos de correção que podem ser aplicadas.
 */
enum class EValidationCorrectionType : uint8
{
    None = 0,
    ResetToNone,  // Reseta propriedade para NAME_None
    ClearArray,   // Limpa array
    AdjustValue,  // Ajusta valor numérico
    RemoveInvalid // Remove itens inválidos de array
};

/**
 * Estrutura que representa uma correção necessária.
 * Validators retornam isso, Data Asset aplica.
 * Struct C++ normal (não USTRUCT) pois não precisa ser exposto ao Blueprint.
 */
struct FValidationCorrection
{
    /** Tipo de correção a ser aplicada */
    EValidationCorrectionType CorrectionType = EValidationCorrectionType::None;

    /** Nome da propriedade a ser corrigida */
    FName PropertyName = NAME_None;

    /** Índice do array (se aplicável, -1 se não) */
    int32 ArrayIndex = -1;

    /** Valor a ser ajustado (para AdjustValue) */
    int32 NewValue = 0;

    /** Índices múltiplos (para RemoveInvalid quando há múltiplos elementos a remover) */
    TArray<int32> InvalidIndices;

    /** Mensagem de log para a correção */
    FString LogMessage;

    FValidationCorrection() = default;

    FValidationCorrection(EValidationCorrectionType InType, FName InPropertyName, int32 InArrayIndex = -1,
                          int32 InNewValue = 0, const FString &InLogMessage = TEXT(""))
        : CorrectionType(InType), PropertyName(InPropertyName), ArrayIndex(InArrayIndex), NewValue(InNewValue),
          LogMessage(InLogMessage)
    {
    }

    FValidationCorrection(EValidationCorrectionType InType, FName InPropertyName, const TArray<int32> &InInvalidIndices,
                          const FString &InLogMessage = TEXT(""))
        : CorrectionType(InType), PropertyName(InPropertyName), ArrayIndex(-1), NewValue(0),
          InvalidIndices(InInvalidIndices), LogMessage(InLogMessage)
    {
    }
};

/**
 * Resultado de validação completo.
 * Contém todas as correções necessárias para o Data Asset aplicar.
 * Struct C++ normal (não USTRUCT) pois não precisa ser exposto ao Blueprint.
 */
struct FValidationResult
{
    /** Se há correções necessárias */
    bool bNeedsCorrection = false;

    /** Array de correções a serem aplicadas */
    TArray<FValidationCorrection> Corrections;

    FValidationResult() = default;

    /** Adiciona uma correção ao resultado */
    void AddCorrection(const FValidationCorrection &Correction)
    {
        Corrections.Add(Correction);
        bNeedsCorrection = true;
    }

    /** Limpa todas as correções */
    void Clear()
    {
        Corrections.Empty();
        bNeedsCorrection = false;
    }
};
