// Copyright Epic Games, Inc. All Rights Reserved.

#include "MulticlassingValidator.h"
#include "Data/Tables/ClassDataTable.h"
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Utils/DataTableHelpers.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Containers/UnrealString.h"

bool FMulticlassingValidator::ValidateMulticlassingPrerequisites(const TArray<FClassLevelEntry> &ClassLevels,
                                                                 UDataTable *ClassDataTable, int32 FinalStrength,
                                                                 int32 FinalDexterity, int32 FinalConstitution,
                                                                 int32 FinalIntelligence, int32 FinalWisdom,
                                                                 int32 FinalCharisma, FString &OutErrorMessage)
{
    if (ClassLevels.Num() <= 1)
    {
        // Sem multiclassing, não precisa validar
        return true;
    }

    if (!ClassDataTable)
    {
        OutErrorMessage = TEXT("ClassDataTable não está configurado");
        return false;
    }

    // TODO: Implementar validação de pré-requisitos D&D 5e
    // Cada classe tem pré-requisitos específicos (ex: Fighter precisa STR 13 ou DEX 13)
    // Precisa verificar se o personagem atende aos pré-requisitos de TODAS as classes

    // Por enquanto, retorna true (validação será implementada quando necessário)
    return true;
}

bool FMulticlassingValidator::ValidateChoices(const FClassLevelEntry &ClassEntry, UDataTable *ClassDataTable,
                                              FString &OutErrorMessage)
{
    if (!ClassDataTable)
    {
        OutErrorMessage = TEXT("ClassDataTable não está configurado");
        return false;
    }

    // TODO: Implementar validação de escolhas quando necessário
    // Por enquanto, Choices é apenas TArray<FName> (valores escolhidos)
    // Validação será implementada quando necessário baseado na ordem das features

    return true;
}
