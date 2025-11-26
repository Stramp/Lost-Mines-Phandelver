// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Engine includes
#include "Misc/StringBuilder.h"

#pragma endregion Includes

// ============================================================================
// Attribute Map Creation
// ============================================================================
#pragma region Attribute Map Creation

TMap<FString, FMulticlassValidators::FAttributeInfo> FMulticlassValidators::CreateAttributeMap()
{
    TMap<FString, FAttributeInfo> AttributeMap;
    AttributeMap.Add(TEXT("STR"), {0, TEXT("STR")});
    AttributeMap.Add(TEXT("DEX"), {1, TEXT("DEX")});
    AttributeMap.Add(TEXT("CON"), {2, TEXT("CON")});
    AttributeMap.Add(TEXT("INT"), {3, TEXT("INT")});
    AttributeMap.Add(TEXT("WIS"), {4, TEXT("WIS")});
    AttributeMap.Add(TEXT("CHA"), {5, TEXT("CHA")});
    return AttributeMap;
}

#pragma endregion Attribute Map Creation

// ============================================================================
// Attribute Requirement Parsing
// ============================================================================
#pragma region Attribute Requirement Parsing

bool FMulticlassValidators::ParseAttributeRequirement(const FString &RequirementString, FString &OutAttribute,
                                                      int32 &OutRequiredValue)
{
    TArray<FString> Parts;
    RequirementString.TrimStartAndEnd().ParseIntoArray(Parts, TEXT("/"), true);

    if (Parts.Num() != 2)
    {
        return false;
    }

    OutAttribute = Parts[0].TrimStartAndEnd().ToUpper();
    return LexTryParseString(OutRequiredValue, *Parts[1]);
}

#pragma endregion Attribute Requirement Parsing

// ============================================================================
// OR Requirement Validation
// ============================================================================
#pragma region OR Requirement Validation

bool FMulticlassValidators::ValidateOrRequirement(const FString &OrRequirementString, const TArray<int32> &Attributes,
                                                  const TMap<FString, FAttributeInfo> &AttributeMap,
                                                  FString &OutMissingTag)
{
    TArray<FString> OrParts;
    OrRequirementString.ParseIntoArray(OrParts, TEXT("|"), true);

    for (const FString &OrPart : OrParts)
    {
        FString AttributeAbbr;
        int32 RequiredValue = 0;

        if (!ParseAttributeRequirement(OrPart, AttributeAbbr, RequiredValue))
        {
            continue;
        }

        const FAttributeInfo *AttrInfo = AttributeMap.Find(AttributeAbbr);
        if (!AttrInfo || !Attributes.IsValidIndex(AttrInfo->Index))
        {
            continue;
        }

        int32 CurrentValue = Attributes[AttrInfo->Index];
        if (CurrentValue >= RequiredValue)
        {
            return true; // OR satisfeito
        }

        // Guarda o requisito faltante para tag
        int32 Missing = RequiredValue - CurrentValue;
        OutMissingTag = FString::Printf(TEXT("[%s +%d]"), *AttrInfo->FullName, Missing);
    }

    return false; // Nenhum requisito do OR foi satisfeito
}

#pragma endregion OR Requirement Validation

// ============================================================================
// Multiclass Requirements Validation
// ============================================================================
#pragma region Multiclass Requirements Validation

bool FMulticlassValidators::ValidateMulticlassRequirements(const TArray<FString> &MulticlassRequirements,
                                                           const TArray<int32> &Attributes,
                                                           const TMap<FString, FAttributeInfo> &AttributeMap,
                                                           FString &OutMissingTag)
{
    for (const FString &RequirementStr : MulticlassRequirements)
    {
        FString OrMissingTag;
        if (!ValidateOrRequirement(RequirementStr, Attributes, AttributeMap, OrMissingTag))
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

void FMulticlassValidators::ProcessClassWithRequirements(const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
                                                         const TMap<FString, FAttributeInfo> &AttributeMap,
                                                         TArray<FName> &OutResult)
{
    if (!ClassRow || ClassRow->FClass.Name == NAME_None)
    {
        return;
    }

    FString ClassName = ClassRow->FClass.Name.ToString();

    // Se não há requisitos, classe está disponível
    if (ClassRow->FClass.MulticlassRequirements.Num() == 0)
    {
        OutResult.Add(FName(*ClassName));
        return;
    }

    // Valida requisitos (lógica AND entre elementos do array)
    FString MissingRequirementTag;
    bool bMeetsRequirements = ValidateMulticlassRequirements(ClassRow->FClass.MulticlassRequirements, Attributes,
                                                             AttributeMap, MissingRequirementTag);

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
