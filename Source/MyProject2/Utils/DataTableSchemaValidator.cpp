// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "Utils/DataTableSchemaValidator.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Engine includes
#include "Engine/DataTable.h"
#include "UObject/StructOnScope.h"
#include "UObject/PropertyIterator.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

#pragma endregion Includes

// ============================================================================
// Validate Data Table Schema
// ============================================================================
#pragma region Validate Data Table Schema

FDataTableSchemaValidationResult FDataTableSchemaValidator::ValidateDataTableSchema(UDataTable *DataTable,
                                                                                    const FString &SchemaName,
                                                                                    bool bUsePythonValidation)
{
    FDataTableSchemaValidationResult Result;
    Result.SchemaName = SchemaName;

    if (!DataTable)
    {
        Result.AddError(FString::Printf(TEXT("DataTable '%s' é nullptr"), *SchemaName));
        return Result;
    }

    // Valida estrutura básica primeiro (sempre em C++)
    FDataTableSchemaValidationResult BasicResult = ValidateBasicStructure(DataTable, SchemaName);
    Result.bIsValid = BasicResult.bIsValid;
    Result.Errors.Append(BasicResult.Errors);
    Result.Warnings.Append(BasicResult.Warnings);

    // Valida padrões de nomenclatura
    FDataTableSchemaValidationResult PatternResult = ValidateNamingPatterns(DataTable, SchemaName);
    if (!PatternResult.bIsValid)
    {
        Result.bIsValid = false;
        Result.Errors.Append(PatternResult.Errors);
        Result.Warnings.Append(PatternResult.Warnings);
    }

    // Validação completa com Python (opcional)
    if (bUsePythonValidation)
    {
        // Tenta encontrar arquivo JSON correspondente
        FString JsonFilePath = FPaths::ProjectContentDir() / TEXT("Data/JSON") / (SchemaName + TEXT(".json"));
        if (FPaths::FileExists(JsonFilePath))
        {
            FDataTableSchemaValidationResult PythonResult = ValidateWithPythonScript(JsonFilePath, SchemaName);
            if (!PythonResult.bIsValid)
            {
                Result.bIsValid = false;
                Result.Errors.Append(PythonResult.Errors);
            }
            Result.Warnings.Append(PythonResult.Warnings);
        }
        else
        {
            Result.AddWarning(
                FString::Printf(TEXT("Arquivo JSON não encontrado para validação Python: %s"), *JsonFilePath));
        }
    }

    return Result;
}

FDataTableSchemaValidationResult FDataTableSchemaValidator::ValidateBasicStructure(UDataTable *DataTable,
                                                                                   const FString &SchemaName)
{
    FDataTableSchemaValidationResult Result;
    Result.SchemaName = SchemaName;

    if (!DataTable)
    {
        Result.AddError(FString::Printf(TEXT("DataTable '%s' é nullptr"), *SchemaName));
        return Result;
    }

    const UScriptStruct *RowStruct = DataTable->GetRowStruct();
    if (!RowStruct)
    {
        Result.AddError(FString::Printf(TEXT("DataTable '%s' não tem RowStruct configurado"), *SchemaName));
        return Result;
    }

    const TArray<FName> RowNames = DataTable->GetRowNames();
    if (RowNames.Num() == 0)
    {
        Result.AddWarning(FString::Printf(TEXT("DataTable '%s' está vazio"), *SchemaName));
        return Result;
    }

    // Valida cada row
    for (const FName &RowName : RowNames)
    {
        void *RowData = DataTable->FindRowUnchecked(RowName);
        if (RowData)
        {
            ValidateRequiredFields(RowName, RowStruct, RowData, SchemaName, Result);
        }
    }

    return Result;
}

FDataTableSchemaValidationResult FDataTableSchemaValidator::ValidateNamingPatterns(UDataTable *DataTable,
                                                                                   const FString &SchemaName)
{
    FDataTableSchemaValidationResult Result;
    Result.SchemaName = SchemaName;

    if (!DataTable)
    {
        return Result;
    }

    const FString ExpectedIDPrefix = GetExpectedIDPrefix(SchemaName);
    const FString ExpectedTypeTagsPrefix = GetExpectedTypeTagsPrefix(SchemaName);

    const UScriptStruct *RowStruct = DataTable->GetRowStruct();
    if (!RowStruct)
    {
        return Result;
    }

    const TArray<FName> RowNames = DataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        void *RowData = DataTable->FindRowUnchecked(RowName);
        if (!RowData)
        {
            continue;
        }

        // Valida ID (se campo existir)
        if (FProperty *IDProperty = RowStruct->FindPropertyByName(TEXT("ID")))
        {
            if (FNameProperty *NameProperty = CastField<FNameProperty>(IDProperty))
            {
                FName IDValue = NameProperty->GetPropertyValue_InContainer(RowData);
                if (!IDValue.IsNone() && !ValidateIDPattern(IDValue.ToString(), ExpectedIDPrefix))
                {
                    Result.AddError(FString::Printf(TEXT("Row '%s' tem ID '%s' que não segue padrão esperado '%s*'"),
                                                    *RowName.ToString(), *IDValue.ToString(), *ExpectedIDPrefix));
                }
            }
        }

        // Valida TypeTags (se campo existir)
        if (FProperty *TagsProperty = RowStruct->FindPropertyByName(TEXT("TypeTags")))
        {
            if (FArrayProperty *ArrayProperty = CastField<FArrayProperty>(TagsProperty))
            {
                // Validação simplificada - verifica se tags seguem padrão
                // Nota: Validação completa requer acesso a FGameplayTagContainer
                // Por enquanto, apenas valida se campo existe
            }
        }
    }

    return Result;
}

FDataTableSchemaValidationResult FDataTableSchemaValidator::ValidateWithPythonScript(const FString &JsonFilePath,
                                                                                     const FString &SchemaName)
{
    FDataTableSchemaValidationResult Result;
    Result.SchemaName = SchemaName;
    Result.SourceJsonPath = JsonFilePath;

#if WITH_EDITOR
    // Caminho do script Python
    FString ScriptPath = FPaths::ProjectDir() / TEXT("scripts/validate_json_schemas.py");
    if (!FPaths::FileExists(ScriptPath))
    {
        Result.AddWarning(FString::Printf(TEXT("Script Python não encontrado: %s"), *ScriptPath));
        return Result;
    }

    // Comando Python
    FString PythonCommand = FString::Printf(TEXT("python \"%s\" --file \"%s\""), *ScriptPath, *JsonFilePath);

    // Executa comando
    FString Output;
    FString Errors;
    int32 ReturnCode = 0;

    FPlatformProcess::ExecProcess(*PythonCommand, nullptr, &ReturnCode, &Output, &Errors);

    if (ReturnCode != 0)
    {
        Result.AddError(FString::Printf(TEXT("Validação Python falhou: %s"), *Errors));
    }
    else if (Output.Contains(TEXT("Invalido")) || Output.Contains(TEXT("ERRO")))
    {
        Result.AddError(FString::Printf(TEXT("Validação Python encontrou erros: %s"), *Output));
    }
    else
    {
        // Validação passou
        Result.bIsValid = true;
    }
#else
    Result.AddWarning(TEXT("Validação Python só está disponível no Editor"));
#endif

    return Result;
}

#pragma endregion Validate Data Table Schema

// ============================================================================
// Private Helpers
// ============================================================================
#pragma region Private Helpers

void FDataTableSchemaValidator::ValidateRequiredFields(const FName &RowName, const UScriptStruct *RowStruct,
                                                       const void *RowData, const FString &SchemaName,
                                                       FDataTableSchemaValidationResult &Result)
{
    // Valida Name (sempre presente, é a chave)
    if (RowName.IsNone())
    {
        Result.AddError(FString::Printf(TEXT("Row sem Name na DataTable '%s'"), *SchemaName));
    }

    // Valida ID (obrigatório)
    if (FProperty *IDProperty = RowStruct->FindPropertyByName(TEXT("ID")))
    {
        if (FNameProperty *NameProperty = CastField<FNameProperty>(IDProperty))
        {
            FName IDValue = NameProperty->GetPropertyValue_InContainer(RowData);
            if (IDValue.IsNone())
            {
                Result.AddError(
                    FString::Printf(TEXT("Row '%s' na DataTable '%s' não tem ID"), *RowName.ToString(), *SchemaName));
            }
        }
    }
    else
    {
        Result.AddWarning(
            FString::Printf(TEXT("Row '%s' na DataTable '%s' não tem campo ID"), *RowName.ToString(), *SchemaName));
    }

    // Valida TypeTags (obrigatório)
    if (FProperty *TagsProperty = RowStruct->FindPropertyByName(TEXT("TypeTags")))
    {
        // TypeTags é FGameplayTagContainer, validação simplificada
        // Verifica apenas se campo existe
    }
    else
    {
        Result.AddWarning(FString::Printf(TEXT("Row '%s' na DataTable '%s' não tem campo TypeTags"),
                                          *RowName.ToString(), *SchemaName));
    }
}

bool FDataTableSchemaValidator::ValidateIDPattern(const FString &ID, const FString &ExpectedPrefix)
{
    if (ExpectedPrefix.IsEmpty())
    {
        return true; // Sem padrão definido, aceita qualquer ID
    }

    return ID.StartsWith(ExpectedPrefix);
}

bool FDataTableSchemaValidator::ValidateTypeTagsPattern(const TArray<FString> &TypeTags, const FString &ExpectedPrefix)
{
    if (ExpectedPrefix.IsEmpty())
    {
        return true; // Sem padrão definido, aceita qualquer tag
    }

    for (const FString &Tag : TypeTags)
    {
        if (!Tag.StartsWith(ExpectedPrefix))
        {
            return false;
        }
    }

    return true;
}

FString FDataTableSchemaValidator::GetExpectedIDPrefix(const FString &SchemaName)
{
    // Mapeia nome de schema para prefixo esperado de ID
    if (SchemaName.Contains(TEXT("Race")))
    {
        return TEXT("RACE_");
    }
    else if (SchemaName.Contains(TEXT("Class")))
    {
        return TEXT("CLASS_");
    }
    else if (SchemaName.Contains(TEXT("Background")))
    {
        return TEXT("BG_");
    }
    else if (SchemaName.Contains(TEXT("Feat")))
    {
        return TEXT("FEAT_");
    }
    else if (SchemaName.Contains(TEXT("Feature")))
    {
        return TEXT("FC_");
    }
    else if (SchemaName.Contains(TEXT("Proficiency")))
    {
        return TEXT("PW_"); // Weapon proficiency prefix (pode variar)
    }
    else if (SchemaName.Contains(TEXT("Item")))
    {
        return TEXT("ITM_");
    }
    else if (SchemaName.Contains(TEXT("Trait")))
    {
        return TEXT("TR_");
    }
    else if (SchemaName.Contains(TEXT("Language")))
    {
        return TEXT("PL_"); // Prefixo correto conforme documentação (PL = Proficiency Language)
    }
    else if (SchemaName.Contains(TEXT("Skill")))
    {
        return TEXT("PSK_");
    }
    else if (SchemaName.Contains(TEXT("Spell")))
    {
        return TEXT("SPL_");
    }
    else if (SchemaName.Contains(TEXT("AbilityScore")))
    {
        return TEXT("ABL_");
    }

    return TEXT(""); // Sem padrão definido
}

FString FDataTableSchemaValidator::GetExpectedTypeTagsPrefix(const FString &SchemaName)
{
    // Mapeia nome de schema para prefixo esperado de TypeTags
    if (SchemaName.Contains(TEXT("Race")))
    {
        return TEXT("Race.");
    }
    else if (SchemaName.Contains(TEXT("Class")))
    {
        return TEXT("Class.");
    }
    else if (SchemaName.Contains(TEXT("Background")))
    {
        return TEXT("Background.");
    }
    else if (SchemaName.Contains(TEXT("Feat")))
    {
        return TEXT("Feat.");
    }
    else if (SchemaName.Contains(TEXT("Feature")))
    {
        return TEXT("Feature.");
    }
    else if (SchemaName.Contains(TEXT("Proficiency")))
    {
        return TEXT("Proficiency.");
    }
    else if (SchemaName.Contains(TEXT("Item")))
    {
        return TEXT("Item.");
    }
    else if (SchemaName.Contains(TEXT("Trait")))
    {
        return TEXT("Trait.");
    }
    else if (SchemaName.Contains(TEXT("Language")))
    {
        return TEXT("Language.");
    }
    else if (SchemaName.Contains(TEXT("Skill")))
    {
        return TEXT("Skill.");
    }
    else if (SchemaName.Contains(TEXT("Spell")))
    {
        return TEXT("Spell.");
    }
    else if (SchemaName.Contains(TEXT("AbilityScore")))
    {
        return TEXT("Ability.");
    }

    return TEXT(""); // Sem padrão definido
}

#pragma endregion Private Helpers
