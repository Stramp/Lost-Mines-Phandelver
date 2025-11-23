// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "CharacterSheetDataAsset.generated.h"

// Forward declarations
class UDataTable;

/**
 * Struct para armazenar entrada de nível de classe (multi-classing).
 * Permite personagens terem níveis em múltiplas classes.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassLevelEntry
{
    GENERATED_BODY()

    /** Nome da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (GetOptions = "GetClassNames"))
    FName ClassName;

    /** Nível nesta classe (1-20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (ClampMin = "1", ClampMax = "20"))
    int32 Level = 1;

    /** Nome da subclasse escolhida (se aplicável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class",
              meta = (GetOptions = "GetSubclassNames", GetOptionsParam = "ClassName"))
    FName SubclassName;

    FClassLevelEntry() : ClassName(NAME_None), Level(1), SubclassName(NAME_None) {}

    FClassLevelEntry(const FName &InClassName, int32 InLevel)
        : ClassName(InClassName), Level(InLevel), SubclassName(NAME_None)
    {
    }
};

/**
 * Struct para armazenar ability score com base, bônus racial e score final.
 * Usado no sistema Point Buy.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreEntry
{
    GENERATED_BODY()

    /** Score base (8-15 para Point Buy) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability", meta = (ClampMin = "8", ClampMax = "15"))
    int32 BaseScore = 8;

    /** Bônus racial aplicado (calculado automaticamente) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 RacialBonus = 0;

    /** Score final (BaseScore + RacialBonus) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 FinalScore = 8;

    FAbilityScoreEntry() : BaseScore(8), RacialBonus(0), FinalScore(8) {}
};

/**
 * Data Asset para ficha de personagem D&D 5e.
 *
 * Camada 1 da arquitetura: Editor/Configuração
 *
 * Responsabilidade: Armazenar configuração estática do personagem editável no editor.
 * Contém interface completa para criação de fichas com validações em tempo real.
 *
 * Decisão de Design:
 * - EditDefaultsOnly: Editável apenas em defaults (não em instâncias)
 * - BlueprintReadOnly: Blueprints podem ler mas não modificar (dados autoritários)
 * - Não é replicável: Não precisa em runtime, apenas no editor
 * - Validações em PostEditChangeProperty: Validação em tempo real no editor
 *
 * Fluxo: CharacterSheetComponent lê este Data Asset e copia para CharacterDataComponent em runtime.
 */
UCLASS(BlueprintType)
class MYPROJECT2_API UCharacterSheetDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UCharacterSheetDataAsset();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;

    // ============================================================================
    // GetOptions Functions (para dropdowns no editor)
    // ============================================================================

    /** Retorna todos os nomes de raças disponíveis no RaceDataTable */
    UFUNCTION(CallInEditor)
    TArray<FName> GetRaceNames() const;

    /** Retorna todas as sub-raças disponíveis para a raça selecionada */
    UFUNCTION(CallInEditor)
    TArray<FName> GetSubraceNames() const;

    /** Retorna todos os nomes de backgrounds disponíveis no BackgroundDataTable */
    UFUNCTION(CallInEditor)
    TArray<FName> GetBackgroundNames() const;

    /** Retorna todos os nomes de classes disponíveis no ClassDataTable */
    UFUNCTION(CallInEditor)
    TArray<FName> GetClassNames() const;

    /** Retorna todas as subclasses disponíveis para uma classe específica */
    UFUNCTION(CallInEditor)
    TArray<FName> GetSubclassNames(FName ClassName) const;

    /** Retorna todos os nomes de ability scores (Strength, Dexterity, etc.) */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAbilityScoreNames() const;

    /** Retorna todos os feats disponíveis para Variant Human */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableFeatNames() const;

    /** Retorna todos os nomes de skills de D&D 5e */
    UFUNCTION(CallInEditor)
    TArray<FName> GetSkillNames() const;
#endif
    // ============================================================================
    // Data Tables
    // ============================================================================

    /** Referência ao Data Table de raças */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *RaceDataTable = nullptr;

    /** Referência ao Data Table de classes */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *ClassDataTable = nullptr;

    /** Referência ao Data Table de backgrounds */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *BackgroundDataTable = nullptr;

    /** Referência ao Data Table de feats */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *FeatDataTable = nullptr;

    // ============================================================================
    // Basic Info
    // ============================================================================

    /** Nome do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    FName CharacterName = TEXT("Character Name");

    /** Descrição do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    FText CharacterDescription = FText::GetEmpty();

    /** Nível total do personagem (soma de todos os níveis de classes, máximo 20) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic Info",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 TotalLevel = 0;

    // ============================================================================
    // Race & Background
    // ============================================================================

    /** Raça selecionada */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background",
              meta = (GetOptions = "GetRaceNames", EditCondition = "!bCanShowSheet", EditConditionHides))
    FName SelectedRace = NAME_None;

    /** Sub-raça selecionada (se aplicável) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background",
              meta = (GetOptions = "GetSubraceNames", EditCondition = "!bCanShowSheet", EditConditionHides))
    FName SelectedSubrace = NAME_None;

    /** Background selecionado */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background",
              meta = (GetOptions = "GetBackgroundNames", EditCondition = "!bCanShowSheet", EditConditionHides))
    FName SelectedBackground = NAME_None;

    // ============================================================================
    // Variant Human Choices (aparece apenas quando SelectedSubrace == "Variant Human")
    // ============================================================================

    /** Escolhas customizadas de atributos para Variant Human (2x +1 para distribuir) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variant Human",
              meta = (GetOptions = "GetAbilityScoreNames", EditCondition = "bIsVariantHuman && !bCanShowSheet",
                      EditConditionHides))
    TArray<FName> CustomAbilityScoreChoices;

    /** Feat escolhido para Variant Human */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variant Human",
              meta = (GetOptions = "GetAvailableFeatNames", EditCondition = "bIsVariantHuman && !bCanShowSheet",
                      EditConditionHides))
    FName SelectedFeat = NAME_None;

    /** Skill escolhido para Variant Human */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variant Human",
              meta = (GetOptions = "GetSkillNames", EditCondition = "bIsVariantHuman && !bCanShowSheet",
                      EditConditionHides))
    FName SelectedSkill = NAME_None;

    // ============================================================================
    // Ability Scores (Point Buy System)
    // ============================================================================

    /** Ability scores do personagem (chave: nome do atributo, valor: entrada com base/racial/final) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    TMap<FName, FAbilityScoreEntry> AbilityScores;

    /** Pontos restantes no sistema Point Buy (27 pontos totais) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Scores",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 PointsRemaining = 27;

    // ============================================================================
    // Classes (Multi-classing)
    // ============================================================================

    /** Níveis em cada classe (permite multi-classing) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Classes",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FClassLevelEntry> ClassLevels;

    // ============================================================================
    // Calculated (Read-only)
    // ============================================================================

    /** Features disponíveis baseadas nas classes e níveis */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Calculated",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FName> AvailableFeatures;

    /** Proficiências do personagem (raça + classe + background) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Calculated",
              meta = (EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FName> Proficiencies;

private:
#if WITH_EDITORONLY_DATA
    /** Flag calculada: true se SelectedSubrace == "Variant Human" (propriedade interna, não visível no editor) */
    UPROPERTY()
    bool bIsVariantHuman = false;

    /** Flag to control sheet display (true = only Data Tables, false = all categories) */
    UPROPERTY()
    bool bCanShowSheet = true;
#endif

#if WITH_EDITOR
    /** Flag para evitar recursão infinita ao modificar propriedades durante validação */
    bool bIsValidatingProperties = false;

    /** Valida e atualiza campos calculados */
    void ValidateAndUpdate();

    /** Valida Point Buy system */
    void ValidatePointBuy();

    /** Valida nível total */
    void ValidateTotalLevel();

    /** Atualiza bônus raciais nos ability scores */
    void UpdateRacialBonuses();

    /** Atualiza campos calculados usando helpers */
    void UpdateCalculatedFields();

    /** Valida escolhas de Variant Human */
    void ValidateVariantHumanChoices();

    /** Reseta escolhas de Variant Human quando raça muda */
    void ResetVariantHumanChoices();
#endif
};
