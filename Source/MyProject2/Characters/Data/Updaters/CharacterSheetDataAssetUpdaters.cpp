// Copyright Epic Games, Inc. All Rights Reserved.

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CharacterSheetDataAssetUpdaters.h"

// Project includes - Data Asset
#include "Characters/Data/CharacterSheetDataAsset.h"
#include "Data/Structures/MulticlassTypes.h"

// Project includes - CreateSheet
#include "CreateSheet/Core/CharacterSheetCore.h"
#include "Data/Structures/FCharacterSheetData.h"
#include "Data/Structures/FPointBuyResult.h"
#include "CreateSheet/Multiclass/MulticlassHelpers.h"

// Project includes - Helpers
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"

// Project includes - Utils
#include "Utils/CharacterSheetHelpers.h"
#include "Utils/CalculationHelpers.h"

// Project includes - Data Tables
#include "Data/Tables/RaceDataTable.h"
#include "Data/Tables/BackgroundDataTable.h"

// Project includes - Logging
#include "Logging/LoggingSystem.h"

// Engine includes
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

#if WITH_EDITOR
#include "Editor.h"
#include "UObject/UnrealType.h"
#endif

#pragma endregion Includes

// ============================================================================
// Calculated Fields Update
// ============================================================================
#pragma region Calculated Fields Update

/**
 * Atualiza campos calculados do Data Asset.
 *
 * Nota: Esta função foi mantida como stub para compatibilidade com handlers existentes.
 * Proficiencies e Languages foram removidos do Data Asset e são calculados diretamente
 * no CharacterDataComponent quando necessário.
 *
 * Campos calculados que ainda podem ser atualizados aqui:
 * - CharacterTotalLvl (calculado automaticamente pelos handlers)
 * - MaxHealth/CurrentHealth (calculado por RecalculateMaxHP)
 * - Final Ability Scores (calculado por RecalculateFinalScores)
 *
 * Esta função não faz nada atualmente porque todos os campos calculados são atualizados
 * por funções específicas (RecalculateFinalScores, RecalculateMaxHP, etc.).
 *
 * @param Asset Asset do personagem (pode ser nullptr)
 */
void FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Stub intencional: campos calculados são atualizados por funções específicas
    // Mantida para compatibilidade com handlers que chamam esta função
}

#pragma endregion Calculated Fields Update

// ============================================================================
// Language Choices Update
// ============================================================================
#pragma region Language Choices Update

/**
 * Atualiza detecção de escolhas de idiomas (bHasLanguageChoices, MaxLanguageChoices).
 * Detecta se raça/background/feat permite escolhas de idiomas.
 * NOTA: Não remove itens do array - isso é responsabilidade de Validators/CorrectionApplier.
 */
void FCharacterSheetDataAssetUpdaters::UpdateLanguageChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    Asset->SetHasLanguageChoices(false);
    Asset->MaxLanguageChoices = 0;

    int32 RaceLanguageCount = 0;
    int32 BackgroundLanguageCount = 0;

    // Verifica escolhas de idiomas da raça/sub-raça
    if (Asset->RaceDataTable)
    {
        CharacterSheetHelpers::HasLanguageChoiceFromRace(Asset->SelectedRace, Asset->SelectedSubrace,
                                                         Asset->RaceDataTable, RaceLanguageCount);
    }

    // Verifica escolhas de idiomas do background
    if (Asset->BackgroundDataTable)
    {
        CharacterSheetHelpers::HasLanguageChoiceFromBackground(Asset->SelectedBackground, Asset->BackgroundDataTable,
                                                               BackgroundLanguageCount);
    }

    // Soma total de escolhas disponíveis (raça + background)
    // NOTA: Futuramente, quando feats forem implementados, adicionar aqui também
    Asset->MaxLanguageChoices = RaceLanguageCount + BackgroundLanguageCount;
    bool bNewHasLanguageChoices = (Asset->MaxLanguageChoices > 0);

    // Atualiza flag bHasLanguageChoices e notifica editor se mudou
    if (Asset->GetHasLanguageChoices() != bNewHasLanguageChoices)
    {
        Asset->SetHasLanguageChoices(bNewHasLanguageChoices);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bHasLanguageChoices
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property =
                    FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bHasLanguageChoices"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // NOTA: Não remove itens do array aqui - isso é responsabilidade de Validators/CorrectionApplier.
    // Esta função apenas atualiza as flags e detecta disponibilidade de escolhas.
}

#pragma endregion Language Choices Update

// ============================================================================
// Variant Human Flag Update
// ============================================================================
#pragma region Variant Human Flag Update

/**
 * Atualiza flag Variant Human e notifica editor se mudou.
 * Reseta escolhas de Variant Human se não for mais Variant Human.
 * Variant Human é uma SUB-RAÇA, não uma raça.
 */
void FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Atualiza flag bIsVariantHuman e notifica editor se mudou
    // Variant Human é uma SUB-RAÇA, não uma raça
    bool bNewIsVariantHuman = (Asset->SelectedSubrace == TEXT("Variant Human"));
    if (Asset->GetIsVariantHuman() != bNewIsVariantHuman)
    {
        Asset->SetIsVariantHuman(bNewIsVariantHuman);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bIsVariantHuman
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bIsVariantHuman"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Reseta escolhas se não for Variant Human
    if (!Asset->GetIsVariantHuman())
    {
        FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(Asset);
    }
}

#pragma endregion Variant Human Flag Update

// ============================================================================
// Subrace Flag Update
// ============================================================================
#pragma region Subrace Flag Update

/**
 * Atualiza flag de sub-raças disponíveis (bHasSubraces).
 * Detecta se a raça selecionada tem sub-raças disponíveis.
 * Reseta SelectedSubrace se não há mais sub-raças disponíveis.
 */
void FCharacterSheetDataAssetUpdaters::UpdateSubraceFlag(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se a raça selecionada tem sub-raças disponíveis
    bool bNewHasSubraces = false;
    if (Asset->RaceDataTable && Asset->SelectedRace != NAME_None)
    {
        TArray<FName> AvailableSubraces =
            CharacterSheetHelpers::GetAvailableSubraces(Asset->SelectedRace, Asset->RaceDataTable);
        bNewHasSubraces = (AvailableSubraces.Num() > 0);
    }

    // Atualiza flag bHasSubraces e notifica editor se mudou
    if (Asset->GetHasSubraces() != bNewHasSubraces)
    {
        Asset->SetHasSubraces(bNewHasSubraces);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        // A verificação em PostEditChangeProperty evita recursão ao ignorar mudanças em bHasSubraces
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bHasSubraces"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }

    // Se não há mais sub-raças disponíveis, reseta SelectedSubrace
    if (!Asset->GetHasSubraces() && Asset->SelectedSubrace != NAME_None)
    {
        Asset->Modify();
        Asset->SelectedSubrace = NAME_None;
    }
}

#pragma endregion Subrace Flag Update

// ============================================================================
// Sheet Visibility Update
// ============================================================================
#pragma region Sheet Visibility Update

/**
 * Atualiza visibilidade da ficha baseado na seleção de Data Tables.
 * Mostra todas as categorias quando todos os Data Tables são selecionados.
 * Mostra apenas Data Tables quando algum está faltando.
 */
void FCharacterSheetDataAssetUpdaters::UpdateSheetVisibility(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Verifica se todos os Data Tables obrigatórios foram selecionados
    // Todas as 6 tabelas são obrigatórias: RaceDataTable, BackgroundDataTable, ClassDataTable,
    // FeatDataTable, ClassFeaturesDataTable, ClassProficienciesDataTable
    bool bAllDataTablesSelected = Asset->RaceDataTable != nullptr && Asset->BackgroundDataTable != nullptr &&
                                  Asset->ClassDataTable != nullptr && Asset->FeatDataTable != nullptr &&
                                  Asset->ClassFeaturesDataTable != nullptr &&
                                  Asset->ClassProficienciesDataTable != nullptr;

    // bCanShowSheet = false significa mostrar todas as categorias
    // bCanShowSheet = true significa mostrar apenas Data Tables
    bool bNewCanShowSheet = !bAllDataTablesSelected;

    if (Asset->GetCanShowSheet() != bNewCanShowSheet)
    {
        Asset->SetCanShowSheet(bNewCanShowSheet);

#if WITH_EDITOR
        // Notifica o editor sobre a mudança para atualizar EditCondition
        if (GIsEditor && !Asset->IsValidatingProperties())
        {
            Asset->Modify();
            if (FProperty *Property = FindFieldChecked<FProperty>(Asset->GetClass(), FName(TEXT("bCanShowSheet"))))
            {
                FPropertyChangedEvent PropertyChangedEvent(Property, EPropertyChangeType::ValueSet);
                Asset->PostEditChangeProperty(PropertyChangedEvent);
            }
        }
#endif
    }
}

#pragma endregion Sheet Visibility Update

// ============================================================================
// Final Scores Calculation
// ============================================================================
#pragma region Final Scores Calculation

/**
 * Recalcula scores finais usando Core genérico (aplica todos os motores).
 * Atualiza PointsRemaining e ajusta alocação se necessário.
 */
void FCharacterSheetDataAssetUpdaters::RecalculateFinalScores(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Cria estrutura de dados para o Core genérico
    FCharacterSheetData Data(
        Asset->PointBuyStrength, Asset->PointBuyDexterity, Asset->PointBuyConstitution, Asset->PointBuyIntelligence,
        Asset->PointBuyWisdom, Asset->PointBuyCharisma, Asset->SelectedRace, Asset->SelectedSubrace,
        Asset->CustomAbilityScoreChoices, Asset->RaceDataTable, &Asset->FinalStrength, &Asset->FinalDexterity,
        &Asset->FinalConstitution, &Asset->FinalIntelligence, &Asset->FinalWisdom, &Asset->FinalCharisma);

    // Recalcula scores finais usando Core genérico (aplica todos os motores)
    FPointBuyResult PointBuyResult;
    FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

    // Atualiza pontos restantes
    Asset->PointsRemaining = PointBuyResult.PointsRemaining;

    // Se houve ajuste automático, atualiza alocação e loga aviso (não crítico - sistema ajusta automaticamente)
    if (PointBuyResult.bWasAdjusted)
    {
        Asset->Modify();
        FCharacterSheetDataAssetHelpers::UpdatePointBuyFromAdjustedAllocation(Asset, PointBuyResult.AdjustedAllocation);
        FLogContext Context(TEXT("CharacterSheet"), TEXT("RecalculateFinalScores"));
        FLoggingSystem::LogWarning(Context, PointBuyResult.FeedbackMessage, false);
    }
}

/**
 * Aplica resultado da validação do Point Buy no Asset.
 * Atualiza PointsRemaining com o valor calculado pela validação.
 */
void FCharacterSheetDataAssetUpdaters::ApplyPointBuyValidationResult(UCharacterSheetDataAsset *Asset,
                                                                     int32 PointsRemaining)
{
    if (!Asset)
    {
        return;
    }

    Asset->PointsRemaining = PointsRemaining;
}

#pragma endregion Final Scores Calculation

// ============================================================================
// Max HP Calculation
// ============================================================================
#pragma region Max HP Calculation

/**
 * Recalcula HP máximo do personagem baseado em todas as classes e seus níveis.
 * Usa HitDie de cada classe e Constitution modifier.
 * Atualiza MaxHealth e CurrentHealth (se CurrentHealth > MaxHealth, ajusta para MaxHealth).
 */
void FCharacterSheetDataAssetUpdaters::RecalculateMaxHP(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    // Valida se há tabela de classes configurada
    if (!Asset->ClassDataTable)
    {
        Asset->MaxHealth = 0;
        Asset->CurrentHealth = 0;
        return;
    }

    // Coleta informações de todas as classes
    TArray<FName> ClassNames;
    TArray<int32> LevelsInClass;

    for (const FMulticlassEntry &Entry : Asset->Multiclass)
    {
        if (Entry.ClassData.Name != NAME_None && Entry.ClassData.LevelInClass > 0)
        {
            ClassNames.Add(Entry.ClassData.Name);
            LevelsInClass.Add(Entry.ClassData.LevelInClass);
        }
    }

    // Se não há classes, HP é 0
    if (ClassNames.Num() == 0)
    {
        Asset->MaxHealth = 0;
        Asset->CurrentHealth = 0;
        return;
    }

    // Calcula Constitution modifier
    const int32 ConstitutionModifier = CalculationHelpers::CalculateAbilityModifier(Asset->FinalConstitution);

    // Calcula HP máximo usando helper
    const int32 NewMaxHealth =
        CalculationHelpers::CalculateMaxHP(ClassNames, LevelsInClass, ConstitutionModifier, Asset->ClassDataTable);

    // Atualiza MaxHealth
    Asset->MaxHealth = NewMaxHealth;

    // Ajusta CurrentHealth se necessário (não pode ser maior que MaxHealth)
    if (Asset->CurrentHealth > Asset->MaxHealth)
    {
        Asset->CurrentHealth = Asset->MaxHealth;
    }
    // Se CurrentHealth é 0 e MaxHealth > 0, inicializa com MaxHealth
    else if (Asset->CurrentHealth == 0 && Asset->MaxHealth > 0)
    {
        Asset->CurrentHealth = Asset->MaxHealth;
    }
}

#pragma endregion Max HP Calculation

// ============================================================================
// Multiclass Flags Update
// ============================================================================
#pragma region Multiclass Flags Update

/**
 * Atualiza flags bCanEditProgression e bCanEditProficiencies para todas as entradas de multiclasse.
 * Apenas atualiza flags, não carrega nem valida dados.
 */
void FCharacterSheetDataAssetUpdaters::UpdateMulticlassFlags(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;
        const int32 LevelInClass = Entry.ClassData.LevelInClass;

        // Atualiza flags usando helper puro
        const bool bCanEdit = FMulticlassHelpers::CanProcessProgression(ClassName, LevelInClass);
        Entry.ClassData.bCanEditProgression = bCanEdit;
        Entry.ClassData.bCanEditProficiencies = bCanEdit;

        // Garante que Progression está vazio quando não pode processar
        if (!bCanEdit)
        {
            Entry.ClassData.Progression.Empty();
        }
    }
}

#pragma endregion Multiclass Flags Update

// ============================================================================
// Multiclass Proficiency Choices Update
// ============================================================================
#pragma region Multiclass Proficiency Choices Update

/**
 * Atualiza qtdAvailable dinamicamente quando skills são adicionadas/removidas do Selected.
 * Apenas atualiza, não valida nem carrega dados.
 */
void FCharacterSheetDataAssetUpdaters::UpdateMulticlassProficiencyChoices(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];

        for (FMulticlassProficienciesEntry &ProficiencyEntry : Entry.ClassData.Proficiencies)
        {
            FMulticlassSkills &Skills = ProficiencyEntry.FSkills;

            // Calcula qtdAvailable: quantidade inicial menos skills já escolhidas (Selected.Num())
            // FMath::Max garante que qtdAvailable nunca será negativo
            Skills.qtdAvailable = FMath::Max(0, Skills.InitialQtdAvailable - Skills.Selected.Num());
        }
    }
}

#pragma endregion Multiclass Proficiency Choices Update

// ============================================================================
// Multiclass Level Adjustment
// ============================================================================
#pragma region Multiclass Level Adjustment

/**
 * Ajusta LevelInClass baseado na presença de ClassName.
 * Se ClassName != NAME_None, LevelInClass = 1. Caso contrário, LevelInClass = 0.
 * Apenas atualiza, não valida nem carrega dados.
 */
void FCharacterSheetDataAssetUpdaters::AdjustLevelInClassForClassName(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;

        // Ajusta LevelInClass baseado na presença de classe (lógica simples)
        Entry.ClassData.LevelInClass = (ClassName != NAME_None) ? 1 : 0;
    }
}

/**
 * Ajusta nível mínimo para classes válidas (sem tag de requerimento).
 * Se tem classe válida e LevelInClass == 0, ajusta para 1.
 * Apenas atualiza, não valida nem carrega dados.
 */
void FCharacterSheetDataAssetUpdaters::AdjustMinimumLevelForValidClasses(UCharacterSheetDataAsset *Asset)
{
    if (!Asset)
    {
        return;
    }

    for (int32 i = 0; i < Asset->Multiclass.Num(); ++i)
    {
        FMulticlassEntry &Entry = Asset->Multiclass[i];
        const FName ClassName = Entry.ClassData.Name;

        // Se tem classe válida (não é None e não tem tag), nível mínimo é 1
        if (FCharacterSheetDataAssetHelpers::IsValidClassWithoutTag(ClassName) && Entry.ClassData.LevelInClass == 0)
        {
            Entry.ClassData.LevelInClass = 1;
        }
    }
}

#pragma endregion Multiclass Level Adjustment
