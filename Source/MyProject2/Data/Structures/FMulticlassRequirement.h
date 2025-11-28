// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FMulticlassRequirement.generated.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Requirement Struct
// ============================================================================
#pragma region Multiclass Requirement Struct

/**
 * Requisito individual de atributo para multiclasse.
 * Estrutura normalizada substituindo formato string "STR/13".
 *
 * Exemplo:
 * {
 *   "AbilityID": "ABL_Strength",
 *   "Value": 13
 * }
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassRequirement
{
    GENERATED_BODY()

    /** ID do atributo requerido (ex: "ABL_Strength", "ABL_Dexterity") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclass Requirement")
    FName AbilityID;

    /** Valor mínimo requerido do atributo */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclass Requirement")
    int32 Value = 0;

    FMulticlassRequirement() : AbilityID(NAME_None), Value(0) {}

    FMulticlassRequirement(FName InAbilityID, int32 InValue) : AbilityID(InAbilityID), Value(InValue) {}
};

#pragma endregion Multiclass Requirement Struct

// ============================================================================
// Multiclass Requirement Group Struct
// ============================================================================
#pragma region Multiclass Requirement Group Struct

/**
 * Grupo de requisitos de atributo para multiclasse.
 * Permite lógica AND/OR entre requisitos.
 *
 * Exemplo (OR - qualquer um dos requisitos):
 * {
 *   "Operator": "OR",
 *   "Requirements": [
 *     {"AbilityID": "ABL_Strength", "Value": 13},
 *     {"AbilityID": "ABL_Dexterity", "Value": 13}
 *   ]
 * }
 *
 * Exemplo (AND - todos os requisitos):
 * {
 *   "Operator": "AND",
 *   "Requirements": [
 *     {"AbilityID": "ABL_Strength", "Value": 13},
 *     {"AbilityID": "ABL_Constitution", "Value": 13}
 *   ]
 * }
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassRequirementGroup
{
    GENERATED_BODY()

    /** Operador lógico: "OR" (qualquer um) ou "AND" (todos) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclass Requirement Group")
    FString Operator = TEXT("OR");

    /** Lista de requisitos individuais */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclass Requirement Group")
    TArray<FMulticlassRequirement> Requirements;

    FMulticlassRequirementGroup() : Operator(TEXT("OR")) {}

    FMulticlassRequirementGroup(const FString &InOperator, const TArray<FMulticlassRequirement> &InRequirements)
        : Operator(InOperator), Requirements(InRequirements)
    {
    }
};

#pragma endregion Multiclass Requirement Group Struct
