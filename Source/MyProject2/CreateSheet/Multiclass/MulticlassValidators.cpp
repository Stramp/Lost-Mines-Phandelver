// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/AbilityScoreDataTable.h"
#include "Data/Structures/FMulticlassRequirement.h"

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
    const TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> &AttributeMap, FString &OutMissingTag)
{
    for (const FString &RequirementStr : MulticlassRequirements)
    {
        FString OrMissingTag;
        if (!FMulticlassValidationHelpers::ValidateOrRequirement(RequirementStr, Attributes, AttributeMap, OrMissingTag))
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
    const TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> &AttributeMap, TArray<FName> &OutResult,
    const UDataTable *AbilityScoreDataTable)
{
    if (!ClassRow || ClassRow->Name == NAME_None)
    {
        return;
    }

    FString ClassName = ClassRow->Name.ToString();

    // Tenta usar nova estrutura normalizada primeiro (se disponível e AbilityScoreDataTable fornecido)
    if (ClassRow->MulticlassRequirementGroups.Num() > 0 && AbilityScoreDataTable)
    {
        FString MissingRequirementTag;
        bool bMeetsRequirements = ValidateMulticlassRequirementGroups(ClassRow->MulticlassRequirementGroups, Attributes,
                                                                      AbilityScoreDataTable, MissingRequirementTag);

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
        return;
    }

    // Fallback para formato antigo (compatibilidade)
    if (ClassRow->MulticlassRequirements.Num() > 0)
    {
        // Valida requisitos (lógica AND entre elementos do array) - estrutura flat
        FString MissingRequirementTag;
        bool bMeetsRequirements = ValidateMulticlassRequirements(ClassRow->MulticlassRequirements, Attributes,
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
        return;
    }

    // Se não há requisitos, classe está disponível
    OutResult.Add(FName(*ClassName));
}

#pragma endregion Class Processing With Requirements

// ============================================================================
// New Normalized Structure Validation
// ============================================================================
#pragma region New Normalized Structure Validation

bool FMulticlassValidators::ValidateRequirement(const FMulticlassRequirement &Requirement,
                                                const TArray<int32> &Attributes,
                                                const UDataTable *AbilityScoreDataTable, FString &OutMissingTag)
{
    if (Requirement.AbilityID == NAME_None || !AbilityScoreDataTable)
    {
        return false;
    }

    // Mapeia AbilityID para índice
    int32 AttributeIndex = -1;
    if (!FMulticlassValidationHelpers::MapAbilityIDToIndex(Requirement.AbilityID, AbilityScoreDataTable, AttributeIndex))
    {
        OutMissingTag = FString::Printf(TEXT("[%s +?]"), *Requirement.AbilityID.ToString());
        return false;
    }

    // Valida se índice é válido
    if (!Attributes.IsValidIndex(AttributeIndex))
    {
        OutMissingTag = FString::Printf(TEXT("[%s +?]"), *Requirement.AbilityID.ToString());
        return false;
    }

    // Valida valor
    int32 CurrentValue = Attributes[AttributeIndex];
    if (CurrentValue >= Requirement.Value)
    {
        return true;
    }

    // Calcula valor faltante para tag
    int32 Missing = Requirement.Value - CurrentValue;

    // Busca abreviação do atributo para tag
    if (const FAbilityScoreDataRow *Row =
            AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(Requirement.AbilityID, TEXT("ValidateRequirement")))
    {
        FString Abbr = Row->Abbreviation.ToString().ToUpper();
        OutMissingTag = FString::Printf(TEXT("[%s +%d]"), *Abbr, Missing);
    }
    else
    {
        OutMissingTag = FString::Printf(TEXT("[%s +%d]"), *Requirement.AbilityID.ToString(), Missing);
    }

    return false;
}

bool FMulticlassValidators::ValidateRequirementGroup(const FMulticlassRequirementGroup &Group,
                                                     const TArray<int32> &Attributes,
                                                     const UDataTable *AbilityScoreDataTable, FString &OutMissingTag)
{
    if (Group.Requirements.Num() == 0)
    {
        return true; // Grupo vazio é sempre válido
    }

    bool bIsOR = Group.Operator.Equals(TEXT("OR"), ESearchCase::IgnoreCase);
    bool bIsAND = Group.Operator.Equals(TEXT("AND"), ESearchCase::IgnoreCase);

    if (!bIsOR && !bIsAND)
    {
        // Operador desconhecido, assume AND
        bIsAND = true;
    }

    if (bIsOR)
    {
        // OR: pelo menos um requisito deve ser satisfeito
        for (const FMulticlassRequirement &Req : Group.Requirements)
        {
            FString MissingTag;
            if (ValidateRequirement(Req, Attributes, AbilityScoreDataTable, MissingTag))
            {
                return true; // OR satisfeito
            }
            // Guarda primeiro requisito faltante para tag
            if (OutMissingTag.IsEmpty())
            {
                OutMissingTag = MissingTag;
            }
        }
        return false; // Nenhum requisito do OR foi satisfeito
    }
    else // AND
    {
        // AND: todos os requisitos devem ser satisfeitos
        for (const FMulticlassRequirement &Req : Group.Requirements)
        {
            FString MissingTag;
            if (!ValidateRequirement(Req, Attributes, AbilityScoreDataTable, MissingTag))
            {
                OutMissingTag = MissingTag;
                return false; // AND falhou
            }
        }
        return true; // Todos os requisitos do AND foram satisfeitos
    }
}

bool FMulticlassValidators::ValidateMulticlassRequirementGroups(
    const TArray<FMulticlassRequirementGroup> &RequirementGroups, const TArray<int32> &Attributes,
    const UDataTable *AbilityScoreDataTable, FString &OutMissingTag)
{
    // Grupos são combinados com lógica AND (todos os grupos devem ser satisfeitos)
    for (const FMulticlassRequirementGroup &Group : RequirementGroups)
    {
        FString MissingTag;
        if (!ValidateRequirementGroup(Group, Attributes, AbilityScoreDataTable, MissingTag))
        {
            OutMissingTag = MissingTag;
            return false; // Grupo falhou
        }
    }

    return true; // Todos os grupos foram satisfeitos
}

#pragma endregion New Normalized Structure Validation
