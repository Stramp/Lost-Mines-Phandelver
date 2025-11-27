// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

// Project includes - CreateSheet
#include "Data/Structures/MulticlassTypes.h"

#include "CharacterSheetDataAsset.generated.h"

// ============================================================================
// Forward Declarations
// ============================================================================

class UDataTable;

// ============================================================================
// Multiclass Class Data Struct
// ============================================================================

/**
 * Struct principal para dados de classe em multiclasse seguindo a estrutura do DJ_Class.json.
 * Contém todas as informações de uma classe D&D 5e.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassClassData
{
    GENERATED_BODY()

    /** Nome da classe (ex: "Fighter", "Wizard", "Cleric", "Rogue") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (GetOptions = "GetListClassAvaible"))
    FName Name;

    /** Nível da classe (editável no editor) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress",
              meta = (ClampMin = "0", ClampMax = "20")) // MAX_LEVEL (definido em DnDConstants.h)
    int32 LevelInClass = 0;

    /**
     * Flag calculada: indica se Progression pode ser editado.
     * true se Name != NAME_None E LevelInClass > 0, false caso contrário.
     * Usado para desabilitar botão "+" do array Progression no editor.
     */
    UPROPERTY(meta = (Hidden))
    bool bCanEditProgression = false;

    /**
     * Flag calculada: indica se Proficiencies pode ser editado.
     * true se Name != NAME_None E LevelInClass > 0, false caso contrário.
     * Usado para desabilitar botão "+" do array Proficiencies no editor.
     */
    UPROPERTY(meta = (Hidden))
    bool bCanEditProficiencies = false;

    /**
     * Requisitos de atributo para multiclasse nesta classe.
     * Formato: ["STR/13", "DEX/13"] para AND, ou ["STR/13|DEX/13"] para OR.
     * Exemplos:
     * - Fighter: ["STR/13|DEX/13"] (STR 13 OU DEX 13)
     * - Monk: ["DEX/13", "WIS/13"] (DEX 13 E WIS 13)
     * - Wizard: ["INT/13"] (INT 13)
     *
     * Campo somente leitura: definido no JSON, não editável no editor.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Class", meta = (Hidden))
    TArray<FString> MulticlassRequirements;

    /** Proficiências da classe (armas, armaduras, saving throws, skills) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class",
              meta = (HideEditConditionToggle, EditCondition = "bCanEditProficiencies", EditConditionHides))
    TArray<FMulticlassProficienciesEntry> Proficiencies;

    /** Progressão de features por nível (do nível 1 ao 20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class",
              meta = (HideEditConditionToggle, EditCondition = "bCanEditProgression", EditConditionHides))
    TArray<FMulticlassProgressEntry> Progression;

    FMulticlassClassData() : Name(NAME_None) {}
};

// ============================================================================
// Multiclass Entry Struct
// ============================================================================

/**
 * Struct para armazenar informações de multiclasse.
 * Contém FMulticlassClassData (dados da classe) diretamente.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassEntry
{
    GENERATED_BODY()

    /** Dados da classe (estrutura completa e independente) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclass")
    FMulticlassClassData ClassData;

    FMulticlassEntry() {}
};

// ============================================================================
// Class Declaration
// ============================================================================

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

    // Friend class para permitir acesso a PropertyHandlers durante inicialização
    friend class FCharacterSheetDataAssetInitializers;

public:
    // ============================================================================
    // Constructor
    // ============================================================================

    UCharacterSheetDataAsset();

    // ============================================================================
    // Public Methods for Modules (replaces friend class access)
    // ============================================================================
#if WITH_EDITOR

    /**
     * Sets the validating properties flag.
     * Used by Handlers to prevent recursive property change events.
     *
     * @param bValidating True if currently validating properties
     */
    void SetValidatingProperties(bool bValidating);

    /**
     * Gets the validating properties flag.
     * Used by Handlers/Validators/Updaters to check if validation is in progress.
     *
     * @return True if currently validating properties
     */
    bool IsValidatingProperties() const;

    // ============================================================================
    // Flag Getters and Setters (for Validators/Updaters)
    // ============================================================================

    /** Gets bIsVariantHuman flag. Used by Validators/Updaters. */
    bool GetIsVariantHuman() const { return bIsVariantHuman; }

    /** Sets bIsVariantHuman flag. Used by Updaters. */
    void SetIsVariantHuman(bool bValue) { bIsVariantHuman = bValue; }

    /** Gets bHasLanguageChoices flag. Used by Validators/Updaters. */
    bool GetHasLanguageChoices() const { return bHasLanguageChoices; }

    /** Sets bHasLanguageChoices flag. Used by Updaters. */
    void SetHasLanguageChoices(bool bValue) { bHasLanguageChoices = bValue; }

    /** Gets bHasSubraces flag. Used by Updaters. */
    bool GetHasSubraces() const { return bHasSubraces; }

    /** Sets bHasSubraces flag. Used by Updaters. */
    void SetHasSubraces(bool bValue) { bHasSubraces = bValue; }

    /** Gets bCanShowSheet flag. Used by Updaters. */
    bool GetCanShowSheet() const { return bCanShowSheet; }

    /** Sets bCanShowSheet flag. Used by Updaters. */
    void SetCanShowSheet(bool bValue) { bCanShowSheet = bValue; }

    // ============================================================================
    // Helper Methods
    // ============================================================================

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

    /** Retorna todos os nomes de ability scores (Strength, Dexterity, etc.) */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAbilityScoreNames() const;

    /** Retorna todos os feats disponíveis para Variant Human */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableFeatNames() const;

    /** Retorna todos os nomes de skills de D&D 5e */
    UFUNCTION(CallInEditor)
    TArray<FName> GetSkillNames() const;

    /** Retorna todos os nomes de skills disponíveis para escolha em multiclasse */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableSkills() const;

    /** Retorna todos os nomes de idiomas disponíveis (para dropdown de escolhas de idiomas) */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableLanguageNames() const;

    /** Retorna os nomes das escolhas disponíveis (para dropdown de SelectedChoice em FMulticlassClassFeature) */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableChoiceNames() const;

    /** Retorna todas as classes disponíveis com verificação de requisitos de atributo */
    UFUNCTION(CallInEditor)
    TArray<FName> GetListClassAvaible() const;
#endif

    // ============================================================================
    // Data Tables
    // ============================================================================

    /** Referência ao Data Table de raças */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *RaceDataTable = nullptr;

    /** Referência ao Data Table de backgrounds */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *BackgroundDataTable = nullptr;

    /** Referência ao Data Table de feats */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *FeatDataTable = nullptr;

    /** Referência ao Data Table de classes */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *ClassDataTable = nullptr;

    /** Referência ao Data Table de features de classe */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *ClassFeaturesDataTable = nullptr;
    /** Referência ao Data Table de features de classe */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data Tables")
    UDataTable *ClassProficienciesDataTable = nullptr;

    // ============================================================================
    // Basic Info
    // ============================================================================
    /** Nome do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    FName CharacterName = TEXT("Character Name");

    /** Descrição do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    FText CharacterDescription = FText::GetEmpty();

    /** Nível total do personagem (soma de todos os níveis de classe) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 TotalLevel = 1;

    /** Bônus de proficiência baseado no TotalLevel */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 ProficiencyBonus = 2;

    /** HP máximo do personagem (calculado automaticamente baseado em HitDie + Constitution modifier) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 MaxHealth = 0;

    /** HP atual do personagem (inicialmente igual a MaxHealth, editável para simular dano) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Basic | Info",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0"))
    int32 CurrentHealth = 0;

    // ============================================================================
    // Final Attributes (8 + RacialBonus + PointBuyAllocation)
    // ============================================================================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalStrength = 8;

    /** Dexterity final - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalDexterity = 8;

    /** Constitution final - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalConstitution = 8;

    /** Intelligence final - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalIntelligence = 8;

    /** Wisdom final - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalWisdom = 8;

    /** Charisma final - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalCharisma = 8;

    // ============================================================================
    // Race & Background
    // ============================================================================
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetRaceNames", EditCondition = "!bCanShowSheet",
                      EditConditionHides))
    FName SelectedRace = NAME_None;

    /** Sub-raça selecionada (se aplicável) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetSubraceNames",
                      EditCondition = "bHasSubraces && !bCanShowSheet", EditConditionHides))
    FName SelectedSubrace = NAME_None;

    /** Background selecionado */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetBackgroundNames", EditCondition = "!bCanShowSheet",
                      EditConditionHides))
    FName SelectedBackground = NAME_None;

    // ============================================================================
    // Variant Human Choices
    // (aparece apenas quando SelectedSubrace == "Variant Human")
    // ============================================================================

    /** Escolhas customizadas de atributos para Variant Human (2x +1 para distribuir) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Variant Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetAbilityScoreNames",
                      EditCondition = "bIsVariantHuman && !bCanShowSheet", EditConditionHides))
    TArray<FName> CustomAbilityScoreChoices;

    /** Feat escolhido para Variant Human */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Variant Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetAvailableFeatNames",
                      EditCondition = "bIsVariantHuman && !bCanShowSheet", EditConditionHides))
    FName SelectedFeat = NAME_None;

    /** Skill escolhido para Variant Human */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Variant Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetSkillNames",
                      EditCondition = "bIsVariantHuman && !bCanShowSheet", EditConditionHides))
    FName SelectedSkill = NAME_None;

    // ============================================================================
    // Language Choices
    // (aparece quando há escolhas de idiomas disponíveis)
    // ============================================================================

    /** Idiomas escolhidos pelo jogador (quando raça/background/feat permite escolha) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background | Language Choices",
              meta = (HideEditConditionToggle, GetOptions = "GetAvailableLanguageNames",
                      EditCondition = "bHasLanguageChoices && !bCanShowSheet", EditConditionHides))
    TArray<FName> SelectedLanguages;

    /** Quantidade máxima de idiomas que podem ser escolhidos (calculado automaticamente) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Race & Background | Language Choices",
              meta = (HideEditConditionToggle, EditCondition = "bHasLanguageChoices && !bCanShowSheet",
                      EditConditionHides))
    int32 MaxLanguageChoices = 0;

    // ============================================================================
    // Ability Scores (Point Buy System)
    // ============================================================================
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 PointsRemaining = 27; // MAX_POINT_BUY_POINTS (definido em DnDConstants.h)

    /** Pontos alocados em Strength (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyStrength = 0;

    /** Pontos alocados em Dexterity (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyDexterity = 0;

    /** Pontos alocados em Constitution (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyConstitution = 0;

    /** Pontos alocados em Intelligence (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyIntelligence = 0;

    /** Pontos alocados em Wisdom (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyWisdom = 0;

    /** Pontos alocados em Charisma (0-7) */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides, ClampMin = "0",
                      ClampMax = "7"))
    int32 PointBuyCharisma = 0;

    // ============================================================================
    // Multiclass
    // ============================================================================
    // #region Multiclass
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MultClass",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FMulticlassEntry> Multiclass;
    // #endregion

private:
#if WITH_EDITORONLY_DATA
    // ============================================================================
    // Editor-Only Flags (internal state, not visible in editor)
    // ============================================================================

    /** Flag calculada: true se SelectedSubrace == "Variant Human" */
    UPROPERTY()
    bool bIsVariantHuman = false;

    /** Flag calculada: true se há escolhas de idiomas disponíveis (raça/background/feat) */
    UPROPERTY()
    bool bHasLanguageChoices = false;

    /** Flag calculada: true se a raça selecionada tem sub-raças disponíveis */
    UPROPERTY()
    bool bHasSubraces = false;

    /** Flag to control sheet display (true = only Data Tables, false = all categories) */
    UPROPERTY()
    bool bCanShowSheet = true;
#endif

#if WITH_EDITOR
    // ============================================================================
    // Editor-Only Private Members
    // ============================================================================

    /** Flag para evitar recursão infinita ao modificar propriedades durante validação */
    bool bIsValidatingProperties = false;

    /** Tipo para ponteiros de função estáticos (mais seguro que std::function) */
    using PropertyHandlerFunction = void (*)(UCharacterSheetDataAsset *, FName);

    // ============================================================================
    // Editor-Only Protected Members
    // ============================================================================
protected:
    /** Map de nomes de propriedades para seus handlers (usando ponteiros de função estáticos) */
    TMap<FName, PropertyHandlerFunction> PropertyHandlers;

    // ============================================================================
    // Editor-Only Private Methods
    // ============================================================================
private:
    /** Inicializa o map de handlers (chamado no construtor e PostLoad) */
    void InitializePropertyHandlers();

    /** Called after object is loaded from disk - ensures PropertyHandlers is initialized */
    virtual void PostLoad() override;

    /** Ensures PropertyHandlers map is initialized */
    void EnsurePropertyHandlersInitialized();
#endif
};
