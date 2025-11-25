// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Data/Tables/ClassDataTable.h"
#include "CharacterSheetDataAsset.generated.h"

// Forward declarations
class UDataTable;
class FCharacterSheetDataAssetHandlers;
class FCharacterSheetDataAssetValidators;
class FCharacterSheetDataAssetUpdaters;
class FCharacterSheetDataAssetHelpers;

/**
 * Struct para armazenar uma escolha disponível em uma classe.
 * Representa uma escolha específica (ex: Fighting Style, Subclass, ASI).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassChoice
{
    GENERATED_BODY()

    /** ID único da escolha (ex: "Fighter_FightingStyle_1") - INVISÍVEL no editor */
    UPROPERTY()
    FName ChoiceID;

    /** Nome da escolha exibido ao usuário (ex: "Fighting Style", "Arquetipos guerreiro") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice")
    FName ChoiceName;

    /**
     * Tipo da escolha: determina como a escolha é processada.
     * Valores possíveis:
     * - "Simple": Escolha simples (1 de N opções)
     * - "Multiple": Escolha múltipla (M de N opções)
     * - "SubclassSelection": Seleção de subclasse
     * - "ASI": Ability Score Improvement
     * - "Scalable": Escolha que escala com nível
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice")
    FName ChoiceType;

    /** Opções disponíveis para escolhas simples - VISÍVEL quando tem conteúdo */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice",
              meta = (EditCondition = "AvailableSingleChoices.Num() > 0", EditConditionHides))
    TArray<FName> AvailableSingleChoices;

    /** Opções disponíveis para escolhas múltiplas - INVISÍVEL quando vazio, VISÍVEL quando preenchido */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice",
              meta = (EditCondition = "AvailableMultChoice.Num() > 0", EditConditionHides))
    TArray<FName> AvailableMultChoice;

    /** Nível da classe quando a escolha foi desbloqueada */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Choice")
    int32 Level;

    FClassChoice() : ChoiceID(NAME_None), ChoiceName(NAME_None), ChoiceType(NAME_None), Level(1) {}
};

/**
 * Struct para armazenar progresso de classe do personagem.
 * Representa uma classe e seu nível atual.
 * Usado no Data Asset para armazenar progresso simples de classes.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMultClass
{
    GENERATED_BODY()

    /** Nome da classe - dropdown mostra classes disponíveis com requisitos de atributo */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (GetOptions = "GetClassNameOptions"))
    FName ClassName;

    /** Nível nesta classe (1-20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class", meta = (ClampMin = "1", ClampMax = "20"))
    int32 Level = 1;

    /**
     * Escolhas feitas pelo jogador nesta classe.
     * Array de estruturas FClassChoice onde cada item representa uma escolha feita.
     * Exemplos: Fighting Style (Level 1), Subclass (Level 3), ASI (Level 4).
     * Auto-preenchido pelo handler baseado no nível da classe e features do DataTable.
     * EditCondition mostra apenas quando Level >= 1 (escolhas disponíveis).
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choices", meta = (EditCondition = "Level >= 1"))
    TArray<FClassChoice> Choices;

    FMultClass() : ClassName(NAME_None), Level(1) {}

    FMultClass(const FName &InClassName, int32 InLevel) : ClassName(InClassName), Level(InLevel) {}
};

/**
 * Struct para armazenar entrada de nível de classe (multi-classing).
 * Usado pelo motor de Multiclassing para cálculos internos.
 * NOTA: Para o Data Asset, use FMultClass (mais simples).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassLevelEntry
{
    GENERATED_BODY()

    /** Nome da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName ClassName;

    /** Nível nesta classe (1-20) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    int32 Level = 1;

    /** Nome da subclasse escolhida (se aplicável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    FName SubclassName;

    /** Escolhas feitas pelo jogador nesta classe (ex: Fighting Style, Maneuvers) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
    TArray<FName> Choices;

    FClassLevelEntry() : ClassName(NAME_None), Level(1), SubclassName(NAME_None) {}

    FClassLevelEntry(const FName &InClassName, int32 InLevel)
        : ClassName(InClassName), Level(InLevel), SubclassName(NAME_None)
    {
    }
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
    // ============================================================================
    // Public methods for modules (replaces friend class access)
    // ============================================================================

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

    /**
     * Gets bIsVariantHuman flag.
     * Used by Validators/Updaters.
     *
     * @return True if selected subrace is Variant Human
     */
    bool GetIsVariantHuman() const { return bIsVariantHuman; }

    /**
     * Sets bIsVariantHuman flag.
     * Used by Updaters.
     *
     * @param bValue New value
     */
    void SetIsVariantHuman(bool bValue) { bIsVariantHuman = bValue; }

    /**
     * Gets bHasLanguageChoices flag.
     * Used by Validators/Updaters.
     *
     * @return True if there are language choices available
     */
    bool GetHasLanguageChoices() const { return bHasLanguageChoices; }

    /**
     * Sets bHasLanguageChoices flag.
     * Used by Updaters.
     *
     * @param bValue New value
     */
    void SetHasLanguageChoices(bool bValue) { bHasLanguageChoices = bValue; }

    /**
     * Gets bHasSubraces flag.
     * Used by Updaters.
     *
     * @return True if selected race has subraces
     */
    bool GetHasSubraces() const { return bHasSubraces; }

    /**
     * Sets bHasSubraces flag.
     * Used by Updaters.
     *
     * @param bValue New value
     */
    void SetHasSubraces(bool bValue) { bHasSubraces = bValue; }

    /**
     * Gets bCanShowSheet flag.
     * Used by Updaters.
     *
     * @return True if sheet can be shown
     */
    bool GetCanShowSheet() const { return bCanShowSheet; }

    /**
     * Sets bCanShowSheet flag.
     * Used by Updaters.
     *
     * @param bValue New value
     */
    void SetCanShowSheet(bool bValue) { bCanShowSheet = bValue; }

    /**
     * Helper: Cria FCharacterSheetData a partir do Data Asset e chama Core genérico.
     * Bridge entre Data Asset específico e Core genérico.
     * Used by Handlers to recalculate final scores when properties change.
     */
    void RecalculateFinalScoresFromDataAsset();

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

    /** Retorna todos os nomes de idiomas disponíveis (para dropdown de escolhas de idiomas) */
    UFUNCTION(CallInEditor)
    TArray<FName> GetAvailableLanguageNames() const;

    /** Retorna todas as classes disponíveis com verificação de requisitos de atributo */
    UFUNCTION(CallInEditor)
    TArray<FName> GetClassNameOptions() const;
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

    /** Strength final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalStrength = 8;

    /** Dexterity final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalDexterity = 8;

    /** Constitution final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalConstitution = 8;

    /** Intelligence final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalIntelligence = 8;

    /** Wisdom final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalWisdom = 8;

    /** Charisma final (8 + RacialBonus + PointBuyAllocation) - Valor pronto para uso */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basic | Final Atribute",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 FinalCharisma = 8;

    // ============================================================================
    // Race & Background
    // ============================================================================

    /** Raça selecionada */
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
    // Variant Human Choices (aparece apenas quando SelectedSubrace == "Variant Human")
    // ============================================================================

    // Propriedades de Variant Human (agrupadas em subcategoria)

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
    // Language Choices (aparece quando há escolhas de idiomas disponíveis)
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

    // ============================================================================
    // Point Buy Allocation (0-7 pontos por atributo, total = 27 pontos)
    // ============================================================================
    /** Pontos restantes no sistema Point Buy (27 pontos totais) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Scores",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    int32 PointsRemaining = 27;
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
    // Classes | Progress
    // ============================================================================

    /** Progresso de classes do personagem (multiclassing) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Classes",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FMultClass> MultClass;

    // ============================================================================
    // Calculated (Read-only)
    // ============================================================================

    /** Proficiências do personagem (background + Variant Human skill) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Calculated",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FName> Proficiencies;

    /** Idiomas que o personagem fala (calculado automaticamente: raça + background + escolhas) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Calculated",
              meta = (HideEditConditionToggle, EditCondition = "!bCanShowSheet", EditConditionHides))
    TArray<FName> Languages;

private:
#if WITH_EDITORONLY_DATA
    /** Flag calculada: true se SelectedSubrace == "Variant Human" (propriedade interna, não visível no editor) */
    UPROPERTY()
    bool bIsVariantHuman = false;

    /** Flag calculada: true se há escolhas de idiomas disponíveis (raça/background/feat) (propriedade interna, não
     * visível no editor) */
    UPROPERTY()
    bool bHasLanguageChoices = false;

    /** Flag calculada: true se a raça selecionada tem sub-raças disponíveis (propriedade interna, não visível no
     * editor) */
    UPROPERTY()
    bool bHasSubraces = false;

    /** Flag to control sheet display (true = only Data Tables, false = all categories) */
    UPROPERTY()
    bool bCanShowSheet = true;
#endif

#if WITH_EDITOR
    /** Flag para evitar recursão infinita ao modificar propriedades durante validação */
    bool bIsValidatingProperties = false;

    /** Tipo para ponteiros de função estáticos (mais seguro que std::function) */
    using PropertyHandlerFunction = void (*)(UCharacterSheetDataAsset *, FName);

    /** Map de nomes de propriedades para seus handlers (usando ponteiros de função estáticos) */
    TMap<FName, PropertyHandlerFunction> PropertyHandlers;

    /** Inicializa o map de handlers (chamado no construtor e PostLoad) */
    void InitializePropertyHandlers();

    /** Called after object is loaded from disk - ensures PropertyHandlers is initialized */
    virtual void PostLoad() override;

    /** Checks if property is a calculated property that should be ignored */
    bool IsCalculatedProperty(FName PropertyName) const;

    /** Ensures PropertyHandlers map is initialized */
    void EnsurePropertyHandlersInitialized();
#endif
};
