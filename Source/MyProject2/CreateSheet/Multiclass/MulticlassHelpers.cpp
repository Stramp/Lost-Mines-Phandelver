// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - CreateSheet
#include "CreateSheet/Multiclass/MulticlassMotor.h"
#include "Data/Structures/MulticlassTypes.h"
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Project includes - Data Tables
#include "Data/Tables/ClassDataTable.h"
#include "Data/Tables/ProficiencyDataTable.h"
#include "Data/Tables/FeatureDataTable.h"
#include "Data/Tables/SkillDataTable.h"

// Project includes - Structures
#include "Data/Structures/FProficienciesEntry.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Project includes - Utils
#include "Utils/DataTableHelpers.h"
#include "Utils/DataTableRowHandleHelpers.h"
#include "Utils/DnDConstants.h"

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

    if (!ClassDataTable || Attributes.Num() < FMulticlassHelpers::NUM_ATTRIBUTES)
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

    const TMap<FString, FMulticlassHelpers::FAttributeInfo> AttributeMap = FMulticlassHelpers::CreateAttributeMap();
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

// ============================================================================
// Progression Validation
// ============================================================================
#pragma region Progression Validation

bool FMulticlassHelpers::CanProcessProgression(FName ClassName, int32 LevelInClass)
{
    // Progression só pode ser processada se há classe válida e nível > 0
    return ClassName != NAME_None && LevelInClass > 0;
}

#pragma endregion Progression Validation

// ============================================================================
// Proficiencies Conversion
// ============================================================================
#pragma region Proficiencies Conversion

TArray<FName>
FMulticlassHelpers::ResolveProficiencyHandlesToNames(const TArray<FDataTableRowHandle> &ProficiencyHandles,
                                                     const UDataTable *ProficiencyDataTable)
{
    TArray<FName> ResolvedNames;
    if (!ProficiencyDataTable || ProficiencyHandles.Num() == 0)
    {
        return ResolvedNames;
    }

    FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyHandlesToNames"));
    UDataTable *NonConstTable = const_cast<UDataTable *>(ProficiencyDataTable);
    FString TableName = ProficiencyDataTable->GetName();
    int32 UnresolvedCount = 0;

    ResolvedNames.Reserve(ProficiencyHandles.Num());

    for (const FDataTableRowHandle &Handle : ProficiencyHandles)
    {
        if (Handle.RowName == NAME_None)
        {
            continue;
        }

        // Resolve handle para obter ProficiencyRow
        const FProficiencyDataRow *ProficiencyRow =
            DataTableRowHandleHelpers::ResolveHandle<FProficiencyDataRow>(Handle);

        if (!ProficiencyRow && Handle.DataTable.Get() != nullptr)
        {
            // Fallback: tenta buscar pelo RowName diretamente
            ProficiencyRow = DataTableHelpers::FindProficiencyRowByID(Handle.RowName, NonConstTable);
        }

        if (ProficiencyRow && ProficiencyRow->Name != NAME_None)
        {
            // Usa nome legível se encontrado
            ResolvedNames.Add(ProficiencyRow->Name);
        }
        else
        {
            // Fallback: usa ID original se não encontrado na tabela
            ResolvedNames.Add(Handle.RowName);
            UnresolvedCount++;

            // Loga erro de Data Table
            FLoggingSystem::LogDataTableError(
                Context, TableName, Handle.RowName.ToString(), TEXT("ProficiencyHandle"),
                FString::Printf(TEXT("Proficiência '%s' não encontrada na tabela. Verifique se o handle está correto."),
                                *Handle.RowName.ToString()));
        }
    }

    // Loga resumo se houver IDs não resolvidos (sistema ajusta automaticamente - sem popup)
    if (UnresolvedCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d proficiência(s) não foram resolvidas para nomes legíveis."), UnresolvedCount),
            false);
    }

    return ResolvedNames;
}

TArray<FName> FMulticlassHelpers::ResolveProficiencyIDsToNames(const TArray<FName> &ProficiencyIDs,
                                                               const UDataTable *ProficiencyDataTable)
{
    FLogContext Context(TEXT("Multiclass"), TEXT("ResolveProficiencyIDsToNames"));
    TArray<FName> ResolvedNames;
    ResolvedNames.Reserve(ProficiencyIDs.Num()); // Otimização: pre-aloca memória

    if (!ProficiencyDataTable)
    {
        // Se não há tabela, loga erro crítico e retorna IDs originais
        FLoggingSystem::LogError(
            Context, TEXT("ProficiencyDataTable não está configurado. IDs não serão resolvidos para nomes legíveis."),
            true);
        return ProficiencyIDs;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(ProficiencyDataTable);
    FString TableName = ProficiencyDataTable->GetName();
    int32 UnresolvedCount = 0;

    for (const FName &ProficiencyID : ProficiencyIDs)
    {
        if (ProficiencyID == NAME_None)
        {
            continue;
        }

        // Busca proficiência na tabela pelo ID
        const FProficiencyDataRow *ProficiencyRow =
            DataTableHelpers::FindProficiencyRowByID(ProficiencyID, NonConstTable);

        if (ProficiencyRow && ProficiencyRow->Name != NAME_None)
        {
            // Usa nome legível se encontrado
            ResolvedNames.Add(ProficiencyRow->Name);
        }
        else
        {
            // Fallback: usa ID original se não encontrado na tabela
            ResolvedNames.Add(ProficiencyID);
            UnresolvedCount++;

            // Loga erro de Data Table
            FLoggingSystem::LogDataTableError(
                Context, TableName, ProficiencyID.ToString(), TEXT("ProficiencyID"),
                FString::Printf(TEXT("Proficiência '%s' não encontrada na tabela. "
                                     "Verifique se o JSON tem 'ProficiencyID' ao invés de "
                                     "'p_id' e se o ID corresponde."),
                                *ProficiencyID.ToString()));
        }
    }

    // Loga resumo se houver IDs não resolvidos (sistema ajusta automaticamente - sem popup)
    if (UnresolvedCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context,
            FString::Printf(TEXT("%d proficiência(s) não foram resolvidas para nomes legíveis."), UnresolvedCount),
            false);
    }

    return ResolvedNames;
}

FMulticlassProficienciesEntry FMulticlassHelpers::ConvertProficienciesEntry(const FProficienciesEntry &SourceEntry,
                                                                            const UDataTable *ProficiencyDataTable)
{
    FMulticlassProficienciesEntry Result;

    // Resolve IDs de armas para nomes legíveis
    Result.armas = FMulticlassHelpers::ResolveProficiencyIDsToNames(SourceEntry.armas, ProficiencyDataTable);

    // Resolve IDs de armaduras para nomes legíveis
    Result.armaduras = FMulticlassHelpers::ResolveProficiencyIDsToNames(SourceEntry.armaduras, ProficiencyDataTable);

    // Saving throws agora são IDs (ex: "ABL_Strength", "ABL_Constitution")
    Result.SavingThrowIDs = SourceEntry.SavingThrowIDs;

    // Skills: converte FDataTableRowHandle (master data) para FName SkillID (runtime instance)
    // SourceEntry.FSkills.AvailableSkillHandles é TArray<FDataTableRowHandle>
    // Result.FSkills.InitialAvailable é TArray<FName> (SkillID)
    Result.FSkills.InitialAvailable.Empty();
    Result.FSkills.InitialAvailable.Reserve(SourceEntry.FSkills.AvailableSkillHandles.Num());

    // Resolve cada handle para obter SkillID
    for (const FDataTableRowHandle &SkillHandle : SourceEntry.FSkills.AvailableSkillHandles)
    {
        // Resolve handle para obter SkillID da FSkillDataRow
        if (const FSkillDataRow *SkillRow = DataTableRowHandleHelpers::ResolveHandle<FSkillDataRow>(SkillHandle))
        {
            if (SkillRow->ID != NAME_None)
            {
                Result.FSkills.InitialAvailable.Add(SkillRow->ID);
            }
        }
        else if (SkillHandle.RowName != NAME_None)
        {
            // Fallback: usa RowName se resolução falhar (assumindo que RowName = SkillID)
            Result.FSkills.InitialAvailable.Add(SkillHandle.RowName);
        }
    }

    Result.FSkills.available = NAME_None;                    // Dropdown inicia vazio
    Result.FSkills.Selected.Empty();                         // Array de escolhas inicia vazio
    Result.FSkills.qtdAvailable = SourceEntry.FSkills.Count; // Quantidade inicial disponível
    Result.FSkills.InitialQtdAvailable = SourceEntry.FSkills.Count;

    return Result;
}

#pragma endregion Proficiencies Conversion

// ============================================================================
// Proficiencies Validation
// ============================================================================
#pragma region Proficiencies Validation

bool FMulticlassHelpers::ValidateLoadProficienciesInputs(FName ClassName, int32 LevelInClass,
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
// Process Level Change Helpers
// ============================================================================
#pragma region Process Level Change Helpers

FString FMulticlassHelpers::BuildFeaturesString(const TArray<FName> &Features)
{
    if (Features.Num() == 0)
    {
        return TEXT("Nenhum");
    }

    // Otimização: pre-aloca memória estimada (nome médio ~20 chars + separador)
    FString Result;
    Result.Reserve(Features.Num() * 25);

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

bool FMulticlassHelpers::ValidateProcessLevelChangeInputs(FName ClassName, int32 LevelInClass,
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

const FClassDataRow *FMulticlassHelpers::FindAndValidateClassRow(FName ClassName, const UDataTable *ClassDataTable)
{
    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        return nullptr;
    }

    return ClassRow;
}

bool FMulticlassHelpers::ExtractLevelFeatures(const TArray<FProgressEntry> &Progression, int32 LevelInClass,
                                              const FProgressEntry *&OutLevelEntry)
{
    if (LevelInClass > Progression.Num())
    {
        return false;
    }

    // Array é 0-based, nível é 1-based
    OutLevelEntry = &Progression[LevelInClass - 1];
    return true;
}

#pragma endregion Process Level Change Helpers

// ============================================================================
// Feature Conversion Helpers
// ============================================================================
#pragma region Feature Conversion Helpers

FMulticlassClassFeature FMulticlassHelpers::ConvertFeatureRowToMulticlassFeature(const FFeatureDataRow &FeatureRow,
                                                                                 int32 LevelUnlocked)
{
    FMulticlassClassFeature Result;

    // Copia dados básicos
    Result.Name = FeatureRow.Name;
    Result.ID = FeatureRow.ID;
    Result.Description = FeatureRow.Description;
    Result.LevelUnlocked = LevelUnlocked; // Usa o nível passado como parâmetro
    Result.FeatureType = FeatureRow.FeatureType;
    Result.FeatureData = FeatureRow.FeatureData;

    // Calcula flags baseado em dados da tabela (fonte de verdade)
    const bool bIsChoiceType =
        (FeatureRow.FeatureType == TEXT("Choice") || FeatureRow.FeatureType == TEXT("SubclassSelection"));
    const int32 ChoicesCount = FeatureRow.AvailableChoices.Num();
    const bool bHasChoicesInTable = bIsChoiceType && (ChoicesCount > 0);

    // bIsMultipleChoice é determinado por bAllowMultipleChoices, não pela quantidade de opções
    // Tipo 2 (Escolha Única): bAllowMultipleChoices = false → usa AvailableChoices (dropdown)
    // Tipo 3 (Escolhas Múltiplas): bAllowMultipleChoices = true → usa SelectedChoices (array)
    const bool bIsMultiple = bHasChoicesInTable && FeatureRow.bAllowMultipleChoices;

    // Define flags calculadas
    Result.bHasAvailableChoices = bHasChoicesInTable;
    Result.bIsMultipleChoice = bIsMultiple;

    // Popula AvailableChoices ou SelectedChoices baseado no tipo
    if (bHasChoicesInTable)
    {
        if (bIsMultiple)
        {
            // Tipo 3: Escolhas Múltiplas - usa AvailableChoiceToAdd + SelectedChoices (array)
            Result.AvailableChoices = NAME_None;     // Não usado para múltiplas escolhas
            Result.AvailableChoiceToAdd = NAME_None; // Dropdown para adicionar ao array
            Result.SelectedChoices.Empty();          // Inicia vazio para jogador escolher
        }
        else
        {
            // Tipo 2: Escolha Única - usa AvailableChoices (dropdown)
            // Se houver apenas 1 opção, preenche automaticamente com ID; caso contrário, deixa vazio para jogador
            // escolher
            if (ChoicesCount == 1)
            {
                Result.AvailableChoices = FeatureRow.AvailableChoices[0].ID; // Armazena ID, não Name
            }
            else
            {
                Result.AvailableChoices = NAME_None; // Jogador escolhe no dropdown
            }
            Result.AvailableChoiceToAdd = NAME_None; // Não usado para escolha única
            Result.SelectedChoices.Empty();          // Não usado para escolha única
        }
    }
    else
    {
        // Tipo 1: Feature Automático - nenhuma escolha disponível
        Result.AvailableChoices = NAME_None;
        Result.AvailableChoiceToAdd = NAME_None;
        Result.SelectedChoices.Empty();
    }

    return Result;
}

bool FMulticlassHelpers::LoadFeaturesForLevel(const TArray<FDataTableRowHandle> &FeatureHandles,
                                              const UDataTable *FeatureDataTable, int32 LevelUnlocked,
                                              TArray<FMulticlassClassFeature> &OutFeatures)
{
    FLogContext Context(TEXT("Multiclass"), TEXT("LoadFeaturesForLevel"));
    OutFeatures.Empty();

    if (!FeatureDataTable)
    {
        FLoggingSystem::LogError(
            Context, TEXT("ClassFeaturesDataTable não está configurado. Features não serão carregadas."), true);
        return false;
    }

    if (FeatureHandles.Num() == 0)
    {
        // Nível sem features é válido (alguns níveis não têm features)
        return false;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(FeatureDataTable);
    FString TableName = FeatureDataTable->GetName();
    int32 LoadedCount = 0;
    int32 NotFoundCount = 0;

    for (const FDataTableRowHandle &FeatureHandle : FeatureHandles)
    {
        if (FeatureHandle.RowName == NAME_None)
        {
            continue;
        }

        // Resolve handle para obter FeatureRow
        const FFeatureDataRow *FeatureRow = DataTableRowHandleHelpers::ResolveHandle<FFeatureDataRow>(FeatureHandle);

        if (!FeatureRow && FeatureHandle.DataTable.Get() != nullptr)
        {
            // Fallback: tenta buscar pelo RowName diretamente
            FeatureRow = DataTableHelpers::FindFeatureRowByID(FeatureHandle.RowName, NonConstTable);
        }

        if (FeatureRow)
        {
            // Converte para FMulticlassClassFeature
            FMulticlassClassFeature ConvertedFeature = ConvertFeatureRowToMulticlassFeature(*FeatureRow, LevelUnlocked);
            OutFeatures.Add(ConvertedFeature);
            LoadedCount++;
        }
        else
        {
            // Feature não encontrada na tabela
            NotFoundCount++;

            FLoggingSystem::LogDataTableError(
                Context, TableName, FeatureHandle.RowName.ToString(), TEXT("FeatureHandle"),
                FString::Printf(TEXT("Feature '%s' não encontrada na tabela. Verifique se o handle está correto."),
                                *FeatureHandle.RowName.ToString()));
        }
    }

    // Log resumo se houver features não encontradas (sistema ajusta automaticamente - sem popup)
    if (NotFoundCount > 0)
    {
        FLoggingSystem::LogWarning(
            Context, FString::Printf(TEXT("%d feature(s) não foram encontradas na tabela."), NotFoundCount), false);
    }

    return LoadedCount > 0;
}

const FClassDataRow *FMulticlassHelpers::FindClassRowWithErrorLogging(FName ClassName, const UDataTable *ClassDataTable,
                                                                      const FString &FunctionName)
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return nullptr;
    }

    UDataTable *NonConstTable = const_cast<UDataTable *>(ClassDataTable);
    const FClassDataRow *ClassRow = DataTableHelpers::FindClassRow(ClassName, NonConstTable);

    if (!ClassRow)
    {
        FLogContext Context(TEXT("Multiclass"), FunctionName);
        FString TableName = ClassDataTable->GetName();
        FLoggingSystem::LogDataTableError(
            Context, TableName, ClassName.ToString(), TEXT("Name"),
            FString::Printf(TEXT("Classe '%s' não encontrada na tabela."), *ClassName.ToString()));
    }

    return ClassRow;
}

bool FMulticlassHelpers::LoadClassBasicInfo(FName ClassName, const UDataTable *ClassDataTable,
                                            TArray<FString> &OutMulticlassRequirements)
{
    OutMulticlassRequirements.Empty();

    if (ClassName == NAME_None || !ClassDataTable)
    {
        return false;
    }

    // Busca dados da classe na tabela (com logging de erro automático)
    const FClassDataRow *ClassRow = FindClassRowWithErrorLogging(ClassName, ClassDataTable, TEXT("LoadClassBasicInfo"));
    if (!ClassRow)
    {
        return false;
    }

    // Copia MulticlassRequirements da tabela (estrutura flat)
    OutMulticlassRequirements = ClassRow->MulticlassRequirements;

    return true;
}

#pragma endregion Load Class Basic Info

// ============================================================================
// Feature Has Available Choices Helper
// ============================================================================
#pragma region Feature Has Available Choices Helper

bool FMulticlassHelpers::FeatureHasAvailableChoices(const FMulticlassClassFeature &Feature)
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

#pragma endregion Feature Has Available Choices Helper

#pragma endregion Feature Conversion Helpers

// ============================================================================
// Logging Helpers
// ============================================================================
#pragma region Logging Helpers

void FMulticlassHelpers::LogLevelChangeFeatures(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable)
{
    // Validação de entrada (guard clauses)
    if (!ValidateProcessLevelChangeInputs(ClassName, LevelInClass, ClassDataTable))
    {
        return;
    }

    // Busca dados da classe na tabela
    const FClassDataRow *ClassRow = FindAndValidateClassRow(ClassName, ClassDataTable);
    if (!ClassRow)
    {
        return;
    }

    // Extrai features do nível específico (estrutura flat)
    const FProgressEntry *LevelEntry = nullptr;
    if (!ExtractLevelFeatures(ClassRow->Progression, LevelInClass, LevelEntry))
    {
        return;
    }

    // Log apenas quando há features ganhas (ponto chave)
    // Converte FeatureHandles para FName[] para logging
    TArray<FName> FeatureNames;
    for (const FDataTableRowHandle &Handle : LevelEntry->FeatureHandles)
    {
        if (Handle.RowName != NAME_None)
        {
            FeatureNames.Add(Handle.RowName);
        }
    }
    if (FeatureNames.Num() > 0)
    {
        FString FeaturesString = BuildFeaturesString(FeatureNames);
        FLogContext Context(TEXT("Multiclass"), TEXT("LogLevelChangeFeatures"));
        FLoggingSystem::LogInfo(Context, FString::Printf(TEXT("Classe '%s' nível %d: features ganhas = [%s]"),
                                                         *ClassName.ToString(), LevelInClass, *FeaturesString));
    }
}

#pragma endregion Logging Helpers

// ============================================================================
// Attribute Helpers (moved from MulticlassValidators for Clean Code compliance)
// ============================================================================
#pragma region Attribute Helpers

TMap<FString, FMulticlassHelpers::FAttributeInfo> FMulticlassHelpers::CreateAttributeMap()
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

bool FMulticlassHelpers::ParseAttributeRequirement(const FString &RequirementString, FString &OutAttribute,
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

bool FMulticlassHelpers::ValidateOrRequirement(const FString &OrRequirementString, const TArray<int32> &Attributes,
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

#pragma endregion Attribute Helpers
