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
// Local Helpers - Attribute Validation
// ============================================================================
#pragma region Local Helpers - Attribute Validation

namespace
{
    /** Número de atributos esperados (STR, DEX, CON, INT, WIS, CHA) */
    constexpr int32 NUM_ATTRIBUTES = 6;

    /** Informação sobre um atributo (índice no array e nome completo) */
    struct FAttributeInfo
    {
        int32 Index;
        FString FullName;
    };

    /**
     * Cria o mapa de atributos com suas abreviações e índices.
     * @return Mapa de abreviação (ex: "STR") para FAttributeInfo
     */
    TMap<FString, FAttributeInfo> CreateAttributeMap()
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

    /**
     * Parseia um requisito de atributo no formato "STR/13".
     * @param RequirementString String no formato "ATTR/VALUE" (ex: "STR/13")
     * @param OutAttribute Abreviação do atributo (ex: "STR")
     * @param OutRequiredValue Valor requerido (ex: 13)
     * @return true se o parse foi bem-sucedido, false caso contrário
     */
    bool ParseAttributeRequirement(const FString &RequirementString, FString &OutAttribute, int32 &OutRequiredValue)
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

    /**
     * Valida se um requisito OR é satisfeito pelos atributos do personagem.
     * Um requisito OR tem formato "STR/13|DEX/13" (STR 13 OU DEX 13).
     * @param OrRequirementString String com requisitos OR separados por "|"
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutMissingTag Tag formatada com requisito faltante (ex: "[STR +2]")
     * @return true se pelo menos um requisito do OR foi satisfeito, false caso contrário
     */
    bool ValidateOrRequirement(const FString &OrRequirementString, const TArray<int32> &Attributes,
                               const TMap<FString, FAttributeInfo> &AttributeMap, FString &OutMissingTag)
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

    /**
     * Valida todos os requisitos de multiclasse de uma classe.
     * Requisitos são validados com lógica AND (todos devem ser satisfeitos).
     * Cada requisito pode ser OR (ex: "STR/13|DEX/13").
     * @param MulticlassRequirements Array de strings de requisitos (formato AND)
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutMissingTag Tag formatada com o primeiro requisito faltante
     * @return true se todos os requisitos foram satisfeitos, false caso contrário
     */
    bool ValidateMulticlassRequirements(const TArray<FString> &MulticlassRequirements, const TArray<int32> &Attributes,
                                        const TMap<FString, FAttributeInfo> &AttributeMap, FString &OutMissingTag)
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

    /**
     * Processa uma classe e adiciona ao resultado com ou sem tag de requisito faltante.
     * @param ClassRow Linha da Data Table com dados da classe
     * @param Attributes Array de atributos na ordem [STR, DEX, CON, INT, WIS, CHA]
     * @param AttributeMap Mapa de abreviações para informações de atributos
     * @param OutResult Array onde a classe será adicionada (com ou sem tag)
     */
    void ProcessClassWithRequirements(const FClassDataRow *ClassRow, const TArray<int32> &Attributes,
                                      const TMap<FString, FAttributeInfo> &AttributeMap, TArray<FName> &OutResult)
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
} // namespace

#pragma endregion Local Helpers - Attribute Validation

// ============================================================================
// Get Available Class With Tag Requirements
// ============================================================================
#pragma region Get Available Class With Tag Requirements

TArray<FName> FMulticlassHelpers::GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
                                                                       const TArray<int32> &Attributes)
{
    TArray<FName> Result;

    if (!ClassDataTable || Attributes.Num() < NUM_ATTRIBUTES)
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

    const TMap<FString, FAttributeInfo> AttributeMap = CreateAttributeMap();
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);

    // Agora itera pelos rows com segurança (já sabemos que o tipo está correto)
    for (const FName &RowName : RowNames)
    {
        const FClassDataRow *Row =
            NonConstTable->FindRow<FClassDataRow>(RowName, TEXT("GetAvailableClassWithTagRequirements"));

        if (Row)
        {
            ProcessClassWithRequirements(Row, Attributes, AttributeMap, Result);
        }
    }

    return Result;
}

#pragma endregion Get Available Class With Tag Requirements

// ============================================================================
// Progression Array Helpers
// ============================================================================
#pragma region Progression Array Helpers

bool FMulticlassHelpers::AdjustProgressionArraySize(FMulticlassEntry &Entry)
{
    if (Entry.LevelInClass < 1 || Entry.LevelInClass > 20)
    {
        return false;
    }

    TArray<FProgressEntry> &Progression = Entry.ClassData.FClass.Progression;
    const int32 TargetSize = Entry.LevelInClass;

    // Redimensiona array para o tamanho desejado
    Progression.SetNum(TargetSize);

    // Garante que cada elemento tenha o Level correto (1-based)
    for (int32 i = 0; i < Progression.Num(); ++i)
    {
        Progression[i].Level = i + 1;
    }

    return true;
}

int32 FMulticlassHelpers::AdjustAllMulticlassProgressionArrays(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return 0;
    }

    int32 AdjustedCount = 0;

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        if (AdjustProgressionArraySize(Entry))
        {
            AdjustedCount++;

            // Processa mudança de nível se classe estiver selecionada
            const FName ClassName = Entry.ClassData.FClass.Name;
            const int32 LevelInClass = Entry.LevelInClass;

            if (ClassName != NAME_None && Asset->ClassDataTable)
            {
                FMulticlassMotor::ProcessLevelChange(ClassName, LevelInClass, Asset->ClassDataTable);
            }
        }
    }

    return AdjustedCount;
}

#pragma endregion Progression Array Helpers
