// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAsset.h"
#include "Handlers/CharacterSheetDataAssetHandlers.h"
#include "Validators/CharacterSheetDataAssetValidators.h"
#include "Updaters/CharacterSheetDataAssetUpdaters.h"
#include "Containers/UnrealString.h"
#include "../../Utils/CharacterSheetHelpers.h"
#include "../../Data/Tables/RaceDataTable.h"
#include "../../Data/Tables/ClassDataTable.h"
#include "../../Data/Tables/BackgroundDataTable.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "PropertyEditorModule.h"
#endif

UCharacterSheetDataAsset::UCharacterSheetDataAsset()
{
    // Inicializa ability scores padrão (todos começam em 8)
    TArray<FName> AbilityNames = {TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                                  TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
    for (const FName &AbilityName : AbilityNames)
    {
        FAbilityScoreEntry Entry;
        Entry.BaseScore = 8;
        Entry.FinalScore = 8;
        AbilityScores.Add(AbilityName, Entry);
    }

    PointsRemaining = 27;
    TotalLevel = 0;

#if WITH_EDITOR
    InitializePropertyHandlers();
#endif
}

#if WITH_EDITOR
void UCharacterSheetDataAsset::PostLoad()
{
    Super::PostLoad();

    // Garantir que PropertyHandlers seja inicializado quando objeto é carregado do disco
    // (construtor não é chamado quando carregado do disco)
    if (PropertyHandlers.Num() == 0)
    {
        InitializePropertyHandlers();
    }
}

void UCharacterSheetDataAsset::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // Evita recursão infinita: se já estamos validando propriedades, não re-dispara validações
    if (bIsValidatingProperties)
    {
        return;
    }

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    FName PropertyName = PropertyChangedEvent.Property->GetFName();

    // Ignora mudanças em propriedades calculadas (não editadas diretamente)
    if (PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bIsVariantHuman) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bCanShowSheet))
    {
        return;
    }

    // Verificar se PropertyHandlers foi inicializado
    if (PropertyHandlers.Num() == 0)
    {
        InitializePropertyHandlers();
    }

    // Lookup handler no map usando ponteiros de função estáticos (mais seguro que std::function)
    if (PropertyHandlerFunction *HandlerPtr = PropertyHandlers.Find(PropertyName))
    {
        // Executar handler - ponteiros de função estáticos são seguros e não têm problemas de lifetime
        (*HandlerPtr)(this, PropertyName);
    }
}

// Funções wrapper estáticas para os handlers (necessárias porque ponteiros de função C-style
// não podem ser lambdas, apenas funções estáticas)
namespace
{
    void HandleSelectedRace(UCharacterSheetDataAsset *Asset, FName PropertyName)
    {
        FCharacterSheetDataAssetHandlers::HandleRaceChange(Asset, PropertyName);
    }

    void HandleSelectedSubrace(UCharacterSheetDataAsset *Asset, FName PropertyName)
    {
        FCharacterSheetDataAssetHandlers::HandleRaceChange(Asset, PropertyName);
    }

    void HandleAbilityScores(UCharacterSheetDataAsset *Asset, FName)
    {
        FCharacterSheetDataAssetHandlers::HandleAbilityScoresChange(Asset);
    }

    void HandleClassLevels(UCharacterSheetDataAsset *Asset, FName)
    {
        FCharacterSheetDataAssetHandlers::HandleClassLevelsChange(Asset);
    }

    void HandleSelectedBackground(UCharacterSheetDataAsset *Asset, FName)
    {
        FCharacterSheetDataAssetHandlers::HandleBackgroundChange(Asset);
    }

    void HandleVariantHumanChoices(UCharacterSheetDataAsset *Asset, FName)
    {
        FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesChange(Asset);
    }

    void HandleDataTable(UCharacterSheetDataAsset *Asset, FName)
    {
        FCharacterSheetDataAssetHandlers::HandleDataTableChange(Asset);
    }
} // namespace

void UCharacterSheetDataAsset::InitializePropertyHandlers()
{
    // Race and Subrace handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace), HandleSelectedRace);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace), HandleSelectedSubrace);

    // Ability Scores handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, AbilityScores), HandleAbilityScores);

    // Class Levels handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassLevels), HandleClassLevels);

    // Background handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground),
                         HandleSelectedBackground);

    // Variant Human choices handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices),
                         HandleVariantHumanChoices);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat), HandleVariantHumanChoices);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill), HandleVariantHumanChoices);

    // Data Tables handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable), HandleDataTable);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable), HandleDataTable);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable), HandleDataTable);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable), HandleDataTable);
}

void UCharacterSheetDataAsset::ValidateAndUpdate()
{
    // Orquestrador completo: atualiza tudo (usado apenas quando necessário)
    // Gerencia bIsValidatingProperties para proteger contra recursão
    bool bWasValidating = bIsValidatingProperties;
    if (!bWasValidating)
    {
        bIsValidatingProperties = true;
    }

    FCharacterSheetDataAssetUpdaters::UpdateVariantHumanFlag(this);
    FCharacterSheetDataAssetValidators::ValidatePointBuy(this);
    FCharacterSheetDataAssetValidators::ValidateTotalLevel(this);
    FCharacterSheetDataAssetUpdaters::UpdateRacialBonuses(this);
    FCharacterSheetDataAssetUpdaters::UpdateCalculatedFields(this);

    // Valida escolhas de Variant Human se aplicável
    if (bIsVariantHuman)
    {
        FCharacterSheetDataAssetValidators::ValidateVariantHumanChoices(this);
    }

    // Restaura flag apenas se não estava setada antes
    if (!bWasValidating)
    {
        bIsValidatingProperties = false;
    }
}

TArray<FName> UCharacterSheetDataAsset::GetRaceNames() const
{
    if (!RaceDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubraceNames() const
{
    if (!RaceDataTable || SelectedRace == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubraces(SelectedRace, RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetBackgroundNames() const
{
    if (!BackgroundDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllBackgroundNames(BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetClassNames() const
{
    if (!ClassDataTable)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAllClassNames(ClassDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubclassNames(FName ClassName) const
{
    if (!ClassDataTable || ClassName == NAME_None)
    {
        return TArray<FName>();
    }

    return CharacterSheetHelpers::GetAvailableSubclasses(ClassName, ClassDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetAbilityScoreNames() const
{
    return TArray<FName>{TEXT("Strength"),     TEXT("Dexterity"), TEXT("Constitution"),
                         TEXT("Intelligence"), TEXT("Wisdom"),    TEXT("Charisma")};
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableFeatNames() const
{
    if (!FeatDataTable)
    {
        return TArray<FName>();
    }

    // Para Variant Human, todos os feats estão disponíveis (sem pré-requisitos de nível)
    // Usa nível 1 e ability scores atuais
    TMap<FName, int32> CurrentAbilityScores;
    for (const auto &Pair : AbilityScores)
    {
        CurrentAbilityScores.Add(Pair.Key, Pair.Value.FinalScore);
    }

    return CharacterSheetHelpers::GetAvailableFeats(1, CurrentAbilityScores, FeatDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSkillNames() const
{
    // Lista completa de skills de D&D 5e
    return TArray<FName>{TEXT("Acrobatics"),    TEXT("Animal Handling"), TEXT("Arcana"),   TEXT("Athletics"),
                         TEXT("Deception"),     TEXT("History"),         TEXT("Insight"),  TEXT("Intimidation"),
                         TEXT("Investigation"), TEXT("Medicine"),        TEXT("Nature"),   TEXT("Perception"),
                         TEXT("Performance"),   TEXT("Persuasion"),      TEXT("Religion"), TEXT("Sleight of Hand"),
                         TEXT("Stealth"),       TEXT("Survival")};
}
#endif
