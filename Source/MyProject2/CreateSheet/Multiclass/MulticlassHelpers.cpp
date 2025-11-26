// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Characters
#include "Characters/Data/CharacterSheetDataAsset.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"

// Engine includes
#include "Engine/DataTable.h"
#include "UObject/StructOnScope.h"
#include "Logging/LogMacros.h"

#pragma endregion Includes

// ============================================================================
// Get Available Class With Tag Requirements
// ============================================================================
#pragma region Get Available Class With Tag Requirements

TArray<FName> FMulticlassHelpers::GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                                       const TArray<int32> &Attributes)
{
    TArray<FName> Result;

    if (!ClassDataTable || Attributes.Num() < FMulticlassValidators::NUM_ATTRIBUTES)
    {
        return Result;
    }

    // Verifica o tipo do Row Structure do DataTable ANTES de tentar acessar rows
    // Isso evita erros "incorrect type" que aparecem quando FindRow é chamado
    const UScriptStruct *RowStruct = ClassDataTable->GetRowStruct();
    if (!RowStruct)
    {
        // DataTable não tem Row Structure configurado
        return Result;
    }

    // Compara o nome do struct para verificar se é FClassDataRow
    // Usa GetFName() para comparação segura
    const FName RowStructName = RowStruct->GetFName();
    const FName ExpectedStructName = FClassDataRow::StaticStruct()->GetFName();

    if (RowStructName != ExpectedStructName)
    {
        // DataTable não está configurado com FClassDataRow, retorna vazio silenciosamente
        return Result;
    }

    // Verifica se o DataTable tem rows
    const TArray<FName> RowNames = ClassDataTable->GetRowNames();
    if (RowNames.Num() == 0)
    {
        return Result;
    }

    const TMap<FString, FMulticlassValidators::FAttributeInfo> AttributeMap =
        FMulticlassValidators::CreateAttributeMap();
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);

    // Agora itera pelos rows com segurança (já sabemos que o tipo está correto)
    for (const FName &RowName : RowNames)
    {
        const FClassDataRow *Row =
            NonConstTable->FindRow<FClassDataRow>(RowName, TEXT("GetAvailableClassWithTagRequirements"));

        if (Row)
        {
            FMulticlassValidators::ProcessClassWithRequirements(Row, Attributes, AttributeMap, Result);
        }
    }

    return Result;
}

#pragma endregion Get Available Class With Tag Requirements
