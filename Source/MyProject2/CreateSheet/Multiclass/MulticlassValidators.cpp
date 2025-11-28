// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Engine includes
#include "Misc/StringBuilder.h"

#pragma endregion Includes

// NOTA: Helpers puros (CreateAttributeMap, ParseAttributeRequirement, ValidateOrRequirement)
// foram movidos para FMulticlassHelpers para seguir Clean Code (helpers em arquivos de helpers).

// ============================================================================
// Multiclass Requirements Validation
// ============================================================================
#pragma region Multiclass Requirements Validation

bool FMulticlassValidators::ValidateMulticlassRequirements(
    const TArray<FString> &MulticlassRequirements, const TArray<int32> &Attributes,
    const TMap<FString, FMulticlassHelpers::FAttributeInfo> &AttributeMap, FString &OutMissingTag)
{
    for (const FString &RequirementStr : MulticlassRequirements)
    {
        FString OrMissingTag;
        if (!FMulticlassHelpers::ValidateOrRequirement(RequirementStr, Attributes, AttributeMap, OrMissingTag))
        {
            OutMissingTag = OrMissingTag;
            return false; // AND falhou
        }
    }

    return true; // Todos os requisitos AND foram satisfeitos
}

#pragma endregion Multiclass Requirements Validation

// ============================================================================
// Class Processing With Requirements
// ============================================================================
#pragma region Class Processing With Requirements

void FMulticlassValidators::ProcessClassWithRequirements(
    const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
    const TMap<FString, FMulticlassHelpers::FAttributeInfo> &AttributeMap, TArray<FName> &OutResult)
{
    if (!ClassRow || ClassRow->ClassName == NAME_None)
    {
        return;
    }

    FString ClassName = ClassRow->ClassName.ToString();

    // Se não há requisitos, classe está disponível (estrutura flat)
    if (ClassRow->MulticlassRequirements.Num() == 0)
    {
        OutResult.Add(FName(*ClassName));
        return;
    }

    // Valida requisitos (lógica AND entre elementos do array) - estrutura flat
    FString MissingRequirementTag;
    bool bMeetsRequirements = ValidateMulticlassRequirements(ClassRow->MulticlassRequirements, Attributes, AttributeMap,
                                                             MissingRequirementTag);

    // Adiciona classe com ou sem tag
    if (bMeetsRequirements)
    {
        OutResult.Add(FName(*ClassName));
    }
    else
    {
        FString ClassWithTag = FString::Printf(TEXT("%s %s"), *MissingRequirementTag, *ClassName);
        OutResult.Add(FName(*ClassWithTag));
    }
}

#pragma endregion Class Processing With Requirements
