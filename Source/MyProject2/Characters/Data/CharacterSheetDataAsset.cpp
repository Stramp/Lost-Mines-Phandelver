// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAsset.h"
#include "Handlers/CharacterSheetDataAssetHandlers.h"
#include "Validators/CharacterSheetDataAssetValidators.h"
#include "Updaters/CharacterSheetDataAssetUpdaters.h"
#include "GetOptions/CharacterSheetDataAssetGetOptions.h"
#include "Helpers/CharacterSheetDataAssetHelpers.h"
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
    // Inicializa Point Buy allocation com 0 para todos os atributos (base = 8, sem pontos gastos)
    TArray<FName> AbilityNames = CharacterSheetHelpers::GetAbilityScoreNames();
    for (const FName &AbilityName : AbilityNames)
    {
        PointBuyAllocation.Add(AbilityName, 0);
    }

    // PointsRemaining e TotalLevel já têm valores padrão no header (= 27 e = 0)
    // Não precisam ser inicializados aqui

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
        PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bHasLanguageChoices) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bHasSubraces) ||
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

void UCharacterSheetDataAsset::InitializePropertyHandlers()
{
    // Race and Subrace handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace),
                         FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace),
                         FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper);

    // Point Buy Allocation handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyAllocation),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);

    // Class Levels handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassLevels),
                         FCharacterSheetDataAssetHandlers::HandleClassLevelsWrapper);

    // Background handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground),
                         FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper);

    // Variant Human choices handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);

    // Language choices handler
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages),
                         FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper);

    // Data Tables handlers
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
}

// ============================================================================
// GetOptions Functions (wrappers - lógica está em FCharacterSheetDataAssetGetOptions)
// ============================================================================
// Estas funções DEVEM ficar na classe porque Unreal Engine procura por elas
// quando vê GetOptions = "GetRaceNames" no meta do UPROPERTY.
// A lógica foi movida para FCharacterSheetDataAssetGetOptions para melhor organização.

TArray<FName> UCharacterSheetDataAsset::GetRaceNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetRaceNames(RaceDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubraceNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetSubraceNames(RaceDataTable, SelectedRace);
}

TArray<FName> UCharacterSheetDataAsset::GetBackgroundNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetBackgroundNames(BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetClassNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetClassNames(ClassDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetSubclassNames(FName ClassName) const
{
    return FCharacterSheetDataAssetGetOptions::GetSubclassNames(ClassDataTable, ClassName);
}

TArray<FName> UCharacterSheetDataAsset::GetAbilityScoreNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableFeatNames() const
{
    // Converte campos finais para formato esperado pelo módulo
    TMap<FName, int32> CurrentAbilityScores;
    CurrentAbilityScores.Add(TEXT("Strength"), FinalStrength);
    CurrentAbilityScores.Add(TEXT("Dexterity"), FinalDexterity);
    CurrentAbilityScores.Add(TEXT("Constitution"), FinalConstitution);
    CurrentAbilityScores.Add(TEXT("Intelligence"), FinalIntelligence);
    CurrentAbilityScores.Add(TEXT("Wisdom"), FinalWisdom);
    CurrentAbilityScores.Add(TEXT("Charisma"), FinalCharisma);

    return FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(FeatDataTable, CurrentAbilityScores);
}

TArray<FName> UCharacterSheetDataAsset::GetSkillNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetSkillNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableLanguageNames() const
{
    // Usa função filtrada que exclui idiomas já conhecidos automaticamente e já escolhidos no array
    // Segue padrão de GetAvailableFeatNames que filtra baseado em estado do personagem
    // Filtra também SelectedLanguages para evitar duplicatas entre elementos do array
    return FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
        SelectedRace, SelectedSubrace, SelectedBackground, SelectedLanguages, RaceDataTable, BackgroundDataTable);
}

void UCharacterSheetDataAsset::SetValidatingProperties(bool bValidating) { bIsValidatingProperties = bValidating; }

bool UCharacterSheetDataAsset::IsValidatingProperties() const { return bIsValidatingProperties; }
#endif
