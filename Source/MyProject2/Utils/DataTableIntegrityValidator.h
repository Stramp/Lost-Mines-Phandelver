// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DataTableIntegrityValidator.generated.h"

// Forward declarations
class UCharacterSheetDataAsset;

#pragma endregion Includes

// ============================================================================
// Validation Result
// ============================================================================
#pragma region Validation Result

/**
 * Resultado da validação de integridade referencial.
 *
 * Contém:
 * - Status de validação (válido ou inválido)
 * - Lista de erros encontrados
 * - Lista de avisos encontrados
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FDataTableValidationResult
{
    GENERATED_BODY()

    /** true se validação passou, false caso contrário */
    UPROPERTY(BlueprintReadOnly, Category = "Validation")
    bool bIsValid = true;

    /** Lista de erros encontrados (referências quebradas, IDs inválidos) */
    UPROPERTY(BlueprintReadOnly, Category = "Validation")
    TArray<FString> Errors;

    /** Lista de avisos encontrados (referências suspeitas, mas não críticas) */
    UPROPERTY(BlueprintReadOnly, Category = "Validation")
    TArray<FString> Warnings;

    FDataTableValidationResult()
        : bIsValid(true)
    {
    }

    /**
     * Adiciona um erro à lista.
     *
     * @param Error Mensagem de erro
     */
    void AddError(const FString& Error)
    {
        Errors.Add(Error);
        bIsValid = false;
    }

    /**
     * Adiciona um aviso à lista.
     *
     * @param Warning Mensagem de aviso
     */
    void AddWarning(const FString& Warning)
    {
        Warnings.Add(Warning);
    }
};

#pragma endregion Validation Result

// ============================================================================
// Data Table Integrity Validator
// ============================================================================
#pragma region Data Table Integrity Validator

/**
 * Valida integridade referencial entre Data Tables.
 *
 * Responsabilidade:
 * - Verificar todas as referências FDataTableRowHandle são válidas
 * - Verificar se todos os IDs referenciados existem
 * - Detectar referências circulares problemáticas
 * - Validar estrutura de dados (Name, ID, TypeTags)
 *
 * Princípio: Validação no Editor antes de Runtime
 * - Detecta problemas precocemente
 * - Evita crashes em runtime
 * - Alinhado com planos5.md (Fase 4: Validação e Integridade)
 */
class MYPROJECT2_API FDataTableIntegrityValidator
{
public:
    /**
     * Valida todas as Data Tables configuradas no CharacterSheetDataAsset.
     *
     * @param Asset Asset contendo todas as Data Tables
     * @return Resultado da validação
     */
    static FDataTableValidationResult ValidateAllDataTables(UCharacterSheetDataAsset* Asset);

    /**
     * Valida uma Data Table específica.
     * Verifica:
     * - Estrutura básica (Name, ID presentes)
     * - Referências FDataTableRowHandle válidas
     * - IDs únicos
     *
     * @param DataTable Data Table a validar
     * @return Resultado da validação
     */
    static FDataTableValidationResult ValidateDataTable(UDataTable* DataTable);

    /**
     * Valida uma referência FDataTableRowHandle.
     * Verifica se:
     * - Handle não é nulo
     * - DataTable existe
     * - RowName existe na DataTable
     *
     * @param Handle Handle a validar
     * @param Context Contexto para mensagens de erro (ex: "RaceDataTable.TraitHandles[0]")
     * @return Resultado da validação
     */
    static FDataTableValidationResult ValidateHandle(const FDataTableRowHandle& Handle, const FString& Context);

private:
    /**
     * Valida estrutura básica de uma row (Name, ID presentes).
     *
     * @param DataTable Data Table a validar
     * @param Result Resultado da validação (modificado)
     */
    static void ValidateBasicStructure(UDataTable* DataTable, FDataTableValidationResult& Result);

    /**
     * Valida referências FDataTableRowHandle em uma Data Table.
     *
     * @param DataTable Data Table a validar
     * @param Result Resultado da validação (modificado)
     */
    static void ValidateHandles(UDataTable* DataTable, FDataTableValidationResult& Result);

    /**
     * Valida IDs únicos em uma Data Table.
     *
     * @param DataTable Data Table a validar
     * @param Result Resultado da validação (modificado)
     */
    static void ValidateUniqueIDs(UDataTable* DataTable, FDataTableValidationResult& Result);
};

#pragma endregion Data Table Integrity Validator
