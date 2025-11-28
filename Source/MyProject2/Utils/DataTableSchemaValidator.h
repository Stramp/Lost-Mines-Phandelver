// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataTableIntegrityValidator.h"
#include "DataTableSchemaValidator.generated.h"

#pragma endregion Includes

// ============================================================================
// JSON Schema Validation Result
// ============================================================================
#pragma region JSON Schema Validation Result

/**
 * Resultado da validação de Data Table contra JSON Schema.
 * Estende FDataTableValidationResult com informações específicas de schema.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FDataTableSchemaValidationResult : public FDataTableValidationResult
{
    GENERATED_BODY()

    /** Nome do schema usado para validação */
    UPROPERTY(BlueprintReadOnly, Category = "Schema Validation")
    FString SchemaName;

    /** Versão do schema (se disponível) */
    UPROPERTY(BlueprintReadOnly, Category = "Schema Validation")
    FString SchemaVersion;

    /** Caminho do arquivo JSON original (se disponível) */
    UPROPERTY(BlueprintReadOnly, Category = "Schema Validation")
    FString SourceJsonPath;

    FDataTableSchemaValidationResult() : FDataTableValidationResult() {}
};

#pragma endregion JSON Schema Validation Result

// ============================================================================
// Data Table Schema Validator
// ============================================================================
#pragma region Data Table Schema Validator

/**
 * Valida Data Tables contra JSON Schemas.
 *
 * Responsabilidade:
 * - Validar estrutura de dados (Name, ID, TypeTags obrigatórios)
 * - Validar tipos de dados (strings, números, arrays)
 * - Validar padrões (regex para IDs, TypeTags)
 * - Validar referências FDataTableRowHandle
 * - Chamar script Python para validação completa (opcional)
 *
 * Princípio: Validação no Editor antes de Runtime
 * - Detecta problemas estruturais precocemente
 * - Alinhado com padrão "Name + ID + Tags + Payload"
 * - Complementa DataTableIntegrityValidator (validação referencial)
 */
class MYPROJECT2_API FDataTableSchemaValidator
{
public:
    /**
     * Valida uma Data Table contra seu JSON Schema.
     * Valida estrutura básica em C++ e pode chamar script Python para validação completa.
     *
     * @param DataTable Data Table a validar
     * @param SchemaName Nome do schema (ex: "RaceDataTable", "ClassDataTable")
     * @param bUsePythonValidation Se true, chama script Python para validação completa (requer Python instalado)
     * @return Resultado da validação
     */
    static FDataTableSchemaValidationResult ValidateDataTableSchema(UDataTable *DataTable, const FString &SchemaName,
                                                                    bool bUsePythonValidation = false);

    /**
     * Valida estrutura básica de uma row (Name, ID, TypeTags obrigatórios).
     * Validação rápida em C++ sem dependência de Python.
     *
     * @param DataTable Data Table a validar
     * @param SchemaName Nome do schema para mensagens de erro
     * @return Resultado da validação
     */
    static FDataTableSchemaValidationResult ValidateBasicStructure(UDataTable *DataTable, const FString &SchemaName);

    /**
     * Valida padrões de nomenclatura (IDs, TypeTags).
     * Verifica se seguem padrões definidos nos schemas.
     *
     * @param DataTable Data Table a validar
     * @param SchemaName Nome do schema
     * @return Resultado da validação
     */
    static FDataTableSchemaValidationResult ValidateNamingPatterns(UDataTable *DataTable, const FString &SchemaName);

    /**
     * Chama script Python para validação completa contra JSON Schema.
     * Requer Python instalado e script validate_json_schemas.py disponível.
     *
     * @param JsonFilePath Caminho do arquivo JSON a validar
     * @param SchemaName Nome do schema
     * @return Resultado da validação
     */
    static FDataTableSchemaValidationResult ValidateWithPythonScript(const FString &JsonFilePath,
                                                                     const FString &SchemaName);

private:
    /**
     * Valida se uma row tem campos obrigatórios (Name, ID, TypeTags).
     *
     * @param RowName Nome da row
     * @param RowStruct Struct da row
     * @param RowData Dados da row
     * @param SchemaName Nome do schema
     * @param Result Resultado da validação (modificado)
     */
    static void ValidateRequiredFields(const FName &RowName, const UScriptStruct *RowStruct, const void *RowData,
                                       const FString &SchemaName, FDataTableSchemaValidationResult &Result);

    /**
     * Valida padrão de ID (ex: RACE_Elf, CLASS_Fighter).
     *
     * @param ID ID a validar
     * @param ExpectedPrefix Prefixo esperado (ex: "RACE_", "CLASS_")
     * @return true se válido, false caso contrário
     */
    static bool ValidateIDPattern(const FString &ID, const FString &ExpectedPrefix);

    /**
     * Valida padrão de TypeTags (ex: ["Race.Elf", "Race.Fey"]).
     *
     * @param TypeTags Array de tags a validar
     * @param ExpectedPrefix Prefixo esperado (ex: "Race.", "Class.")
     * @return true se válido, false caso contrário
     */
    static bool ValidateTypeTagsPattern(const TArray<FString> &TypeTags, const FString &ExpectedPrefix);

    /**
     * Mapeia nome de Data Table para prefixo esperado de ID.
     *
     * @param SchemaName Nome do schema
     * @return Prefixo esperado (ex: "RACE_", "CLASS_")
     */
    static FString GetExpectedIDPrefix(const FString &SchemaName);

    /**
     * Mapeia nome de Data Table para prefixo esperado de TypeTags.
     *
     * @param SchemaName Nome do schema
     * @return Prefixo esperado (ex: "Race.", "Class.")
     */
    static FString GetExpectedTypeTagsPrefix(const FString &SchemaName);
};

#pragma endregion Data Table Schema Validator
