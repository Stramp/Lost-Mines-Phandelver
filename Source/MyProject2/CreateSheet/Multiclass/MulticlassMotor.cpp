// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "CreateSheet/Core/CharacterSheetData.h"
#include "Data/Tables/ClassDataTable.h"
#include "Engine/DataTable.h"
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/DataTableHelpers.h"
#include "Logging/LogMacros.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

TArray<FName> FMulticlassMotor::GetAvailableClasses(const UDataTable *ClassDataTable, int32 FinalStrength,
                                                    int32 FinalDexterity, int32 FinalConstitution,
                                                    int32 FinalIntelligence, int32 FinalWisdom, int32 FinalCharisma)
{
    if (!ClassDataTable)
    {
        return {};
    }

    // TODO: Implementar validação de requisitos de atributo

    TArray<int32> charAttributes = {FinalStrength,     FinalDexterity, FinalConstitution,
                                    FinalIntelligence, FinalWisdom,    FinalCharisma};

    return FMulticlassHelpers::GetAvailableClassWithTagRequirements(ClassDataTable, charAttributes);

    // filtrar classes que atendem requisitos de atributo

    // devolver as classes filtradas no padrao de prefixo com req e atributo

    // Por enquanto retorna todas as classes do DataTable
    // Quando requisitos forem adicionados ao ClassDataTable, filtrar classes que atendem requisitos

    return {};
}

bool FMulticlassMotor::ValidateMulticlassRequirements(const FCharacterSheetData &Data, FName DesiredClassName)
{
    // TODO: Implementar validação de requisitos de atributo
    // Verificar requisitos da classe desejada no ClassDataTable
    // Comparar com atributos finais do personagem

    return true;
}

void FMulticlassMotor::ApplyMulticlassRules(FCharacterSheetData &Data)
{
    // TODO: Implementar aplicação de regras de multiclasse
    // - Proficiências de multiclasse (armaduras, armas, skills)
    // - Features de multiclasse
    // - Cálculo de nível total
}

// ============================================================================
// Local Helpers
// ============================================================================
#pragma region Local Helpers

namespace
{
    /**
     * Constrói string formatada com lista de features.
     * Helper local para manter ProcessLevelChange focada.
     *
     * @param Features Array de nomes de features
     * @return String formatada (ex: "Feature1, Feature2" ou "Nenhum")
     */
    FString BuildFeaturesString(const TArray<FName> &Features)
    {
        if (Features.Num() == 0)
        {
            return TEXT("Nenhum");
        }

        FString Result;
        for (int32 i = 0; i < Features.Num(); ++i)
        {
            if (i > 0)
            {
                Result += TEXT(", ");
            }
            Result += Features[i].ToString();
        }

        return Result;
    }
} // namespace

#pragma endregion Local Helpers

// ============================================================================
// Process Level Change
// ============================================================================
#pragma region Process Level Change

void FMulticlassMotor::ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable)
{
    // Validação de entrada (guard clauses - Clean Code)
    if (ClassName == NAME_None)
    {
        return;
    }

    if (!ClassDataTable)
    {
        return;
    }

    if (LevelInClass < 1 || LevelInClass > 20)
    {
        return;
    }

    // Busca dados da classe na tabela usando helper existente
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        return;
    }

    // Busca features do nível específico na progressão
    const TArray<FProgressEntry> &Progression = ClassRow->FClass.Progression;

    // Valida se o nível está dentro do range da progressão
    if (LevelInClass > Progression.Num())
    {
        return;
    }

    // Acessa o entry do nível (array é 0-based, nível é 1-based)
    const FProgressEntry &LevelEntry = Progression[LevelInClass - 1];

    // Monta string com features ganhas neste nível
    FString FeaturesString = BuildFeaturesString(LevelEntry.Features);

    // Log informativo
    FString ClassNameString = ClassName.ToString();
    UE_LOG(LogTemp, Warning,
           TEXT("FMulticlassMotor::ProcessLevelChange - Classe = %s, LevelInClass = %d, Features = [%s]"),
           *ClassNameString, LevelInClass, *FeaturesString);
}

#pragma endregion Process Level Change
