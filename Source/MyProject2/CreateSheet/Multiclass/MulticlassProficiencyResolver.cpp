// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "MulticlassProficiencyResolver.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassConversionHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/SkillDataTable.h"

// Project includes - Utils
#include "Utils/DataTableRowHandleHelpers.h"

#pragma endregion Includes

// ============================================================================
// Multiclass Proficiency Resolver
// ============================================================================
#pragma region Multiclass Proficiency Resolver

FClassProficiencyData FMulticlassProficiencyResolver::Resolve(const FClassDataRow* ClassRow, const UDataTable* ProficiencyDataTable)
{
    FClassProficiencyData Result;

    if (!ClassRow)
    {
        return Result;
    }

    // Resolve WeaponProficiencyHandles para nomes legíveis
    Result.WeaponNames = FMulticlassConversionHelpers::ResolveProficiencyHandlesToNames(ClassRow->WeaponProficiencyHandles, ProficiencyDataTable);

    // Resolve ArmorProficiencyHandles para nomes legíveis
    Result.ArmorNames = FMulticlassConversionHelpers::ResolveProficiencyHandlesToNames(ClassRow->ArmorProficiencyHandles, ProficiencyDataTable);

    // Resolve SavingThrowHandles para IDs (Ability Scores)
    Result.SavingThrowIDs.Empty();
    Result.SavingThrowIDs.Reserve(ClassRow->SavingThrowHandles.Num());
    for (const FDataTableRowHandle& Handle : ClassRow->SavingThrowHandles)
    {
        if (Handle.RowName != NAME_None)
        {
            Result.SavingThrowIDs.Add(Handle.RowName);
        }
    }

    // Resolve AvailableSkillHandles para IDs
    Result.AvailableSkillIDs.Empty();
    Result.AvailableSkillIDs.Reserve(ClassRow->AvailableSkillHandles.Num());
    for (const FDataTableRowHandle& SkillHandle : ClassRow->AvailableSkillHandles)
    {
        if (const FSkillDataRow* SkillRow = DataTableRowHandleHelpers::ResolveHandle<FSkillDataRow>(SkillHandle))
        {
            if (SkillRow->ID != NAME_None)
            {
                Result.AvailableSkillIDs.Add(SkillRow->ID);
            }
        }
        else if (SkillHandle.RowName != NAME_None)
        {
            Result.AvailableSkillIDs.Add(SkillHandle.RowName);
        }
    }

    // Copia quantidade de escolhas de skills
    Result.SkillChoiceCount = ClassRow->SkillChoiceCount;

    return Result;
}

#pragma endregion Multiclass Proficiency Resolver
