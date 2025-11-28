// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassValidationHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/AbilityScoreDataTable.h"

// Project includes - Structures
#include "Data/Structures/MulticlassTypes.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DnDConstants.h"

// Engine includes
#include "Engine/DataTable.h"

#pragma endregion Includes

// ============================================================================
// Progression Validation
// ============================================================================
#pragma region Progression Validation

bool FMulticlassValidationHelpers::CanProcessProgression(FName ClassName, int32 LevelInClass)
{
    // Progression só pode ser processada se há classe válida e nível > 0
    return ClassName != NAME_None && LevelInClass > 0;
}

#pragma endregion Progression Validation

// ============================================================================
// Proficiencies Validation
// ============================================================================
#pragma region Proficiencies Validation

bool FMulticlassValidationHelpers::ValidateLoadProficienciesInputs(FName ClassName, int32 LevelInClass,
                                                                   const UDataTable *ClassDataTable)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    if (!ClassDataTable)
    {
        return false;
    }

    // Proficiências são ganhas apenas no nível 1
    if (LevelInClass != 1)
    {
        return false;
    }

    return true;
}

#pragma endregion Proficiencies Validation

// ============================================================================
// Process Level Change Validation
// ============================================================================
#pragma region Process Level Change Validation

bool FMulticlassValidationHelpers::ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass,
                                                                      const UDataTable *ClassDataTable)
{
    if (ClassName == NAME_None)
    {
        return false;
    }

    if (!ClassDataTable)
    {
        return false;
    }

    if (LevelInClass < DnDConstants::MIN_LEVEL || LevelInClass > DnDConstants::MAX_LEVEL)
    {
        return false;
    }

    return true;
}

const FClassDataRow *FMulticlassValidationHelpers::FindAndValidateClassRow(FName ClassName,
                                                                            const UDataTable *ClassDataTable)
{
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        return nullptr;
    }

    return ClassRow;
}

#pragma endregion Process Level Change Validation

// ============================================================================
// Feature Validation
// ============================================================================
#pragma region Feature Validation

bool FMulticlassValidationHelpers::FeatureHasAvailableChoices(const FMulticlassClassFeature &Feature)
{
    // Apenas features do tipo "Choice" ou "SubclassSelection" podem ter escolhas disponíveis
    if (Feature.FeatureType != TEXT("Choice") && Feature.FeatureType != TEXT("SubclassSelection"))
    {
        return false;
    }

    // Verifica se feature tem escolhas disponíveis (flag já calculada na conversão)
    // Esta função é mantida para compatibilidade e validações futuras
    // A flag bHasAvailableChoices é calculada em ConvertFeatureRowToMulticlassFeature usando dados da tabela
    return Feature.bHasAvailableChoices;
}

#pragma endregion Feature Validation

// ============================================================================
// Attribute Helpers
// ============================================================================
#pragma region Attribute Helpers

TMap<FString, FMulticlassValidationHelpers::FAttributeInfo> FMulticlassValidationHelpers::CreateAttributeMap()
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

bool FMulticlassValidationHelpers::ParseAttributeRequirement(const FString &RequirementString, FString &OutAttribute,
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

bool FMulticlassValidationHelpers::ValidateOrRequirement(const FString &OrRequirementString,
                                                          const TArray<int32> &Attributes,
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

bool FMulticlassValidationHelpers::MapAbilityIDToIndex(FName AbilityID, const UDataTable *AbilityScoreDataTable,
                                                        int32 &OutIndex)
{
    OutIndex = -1;

    if (AbilityID == NAME_None || !AbilityScoreDataTable)
    {
        return false;
    }

    // Busca row pelo AbilityID na tabela
    TArray<FName> RowNames = AbilityScoreDataTable->GetRowNames();
    for (const FName &RowName : RowNames)
    {
        if (const FAbilityScoreDataRow *Row =
                AbilityScoreDataTable->FindRow<FAbilityScoreDataRow>(RowName, TEXT("MapAbilityIDToIndex")))
        {
            if (Row->ID == AbilityID)
            {
                // Mapeia AbilityID para índice usando Abbreviation
                FString Abbr = Row->Abbreviation.ToString().ToUpper();
                TMap<FString, FAttributeInfo> AttributeMap = CreateAttributeMap();
                const FAttributeInfo *AttrInfo = AttributeMap.Find(Abbr);
                if (AttrInfo)
                {
                    OutIndex = AttrInfo->Index;
                    return true;
                }
            }
        }
    }

    return false;
}

#pragma endregion Attribute Helpers
