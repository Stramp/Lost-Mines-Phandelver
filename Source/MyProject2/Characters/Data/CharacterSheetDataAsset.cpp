// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSheetDataAsset.h"

#include "Characters/Data/GetOptions/CharacterSheetDataAssetGetOptions.h"
#include "Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h"
#include "Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h"
#include "Characters/Data/Updaters/CharacterSheetDataAssetUpdaters.h"
#include "Characters/Data/Validators/CharacterSheetDataAssetValidators.h"
#include "CreateSheet/Core/CharacterSheetCore.h"
#include "CreateSheet/Core/CharacterSheetData.h"
#include "CreateSheet/PointBuy/PointBuyResult.h"
#include "Data/Tables/BackgroundDataTable.h"
#include "Data/Tables/RaceDataTable.h"
#include "Utils/CharacterSheetHelpers.h"

#include "Containers/UnrealString.h"
#include "Logging/LogMacros.h"

#if WITH_EDITOR
#include "Editor.h"
#include "PropertyEditorModule.h"
#endif

UCharacterSheetDataAsset::UCharacterSheetDataAsset()
{
#if WITH_EDITOR
    InitializePropertyHandlers();
#endif
}

#if WITH_EDITOR
void UCharacterSheetDataAsset::PostLoad()
{
    Super::PostLoad();

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

    // Point Buy Allocation handlers (6 propriedades separadas)
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyStrength),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyDexterity),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyConstitution),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyIntelligence),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyWisdom),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, PointBuyCharisma),
                         FCharacterSheetDataAssetHandlers::HandlePointBuyAllocationWrapper);

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
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, BackgroundDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, FeatDataTable),
                         FCharacterSheetDataAssetHandlers::HandleDataTableWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, ClassDataTable),
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

TArray<FName> UCharacterSheetDataAsset::GetAbilityScoreNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAbilityScoreNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableFeatNames() const
{
    const TMap<FName, int32> AbilityScores = FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(
        FinalStrength, FinalDexterity, FinalConstitution, FinalIntelligence, FinalWisdom, FinalCharisma);

    return FCharacterSheetDataAssetGetOptions::GetAvailableFeatNames(FeatDataTable, AbilityScores);
}

TArray<FName> UCharacterSheetDataAsset::GetSkillNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetSkillNames();
}

TArray<FName> UCharacterSheetDataAsset::GetAvailableLanguageNames() const
{
    return FCharacterSheetDataAssetGetOptions::GetAvailableLanguageNamesForChoice(
        SelectedRace, SelectedSubrace, SelectedBackground, SelectedLanguages, RaceDataTable, BackgroundDataTable);
}

TArray<FName> UCharacterSheetDataAsset::GetClassNameOptions() const
{
    return FCharacterSheetDataAssetGetOptions::GetClassNameOptions(ClassDataTable, FinalStrength, FinalDexterity,
                                                                   FinalConstitution, FinalIntelligence, FinalWisdom,
                                                                   FinalCharisma);
}
void UCharacterSheetDataAsset::SetValidatingProperties(bool bValidating) { bIsValidatingProperties = bValidating; }

bool UCharacterSheetDataAsset::IsValidatingProperties() const { return bIsValidatingProperties; }

void UCharacterSheetDataAsset::RecalculateFinalScoresFromDataAsset()
{
    // Cria estrutura genérica a partir do Data Asset
    FCharacterSheetData Data(PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                             PointBuyWisdom, PointBuyCharisma, SelectedRace, SelectedSubrace, CustomAbilityScoreChoices,
                             RaceDataTable, &FinalStrength, &FinalDexterity, &FinalConstitution, &FinalIntelligence,
                             &FinalWisdom, &FinalCharisma);

    // Chama Core genérico (funciona tanto no Data Asset quanto no Widget)
    FPointBuyResult PointBuyResult;
    FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

    // Se o motor ajustou a alocação, atualiza propriedades do Data Asset
    if (PointBuyResult.bWasAdjusted)
    {
        Modify(); // Marca objeto como modificado no editor

        // Atualiza propriedades com valores ajustados
        PointBuyStrength = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Strength"));
        PointBuyDexterity = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Dexterity"));
        PointBuyConstitution = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Constitution"));
        PointBuyIntelligence = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Intelligence"));
        PointBuyWisdom = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Wisdom"));
        PointBuyCharisma = PointBuyResult.AdjustedAllocation.FindRef(TEXT("Charisma"));

        // Atualiza PointsRemaining
        PointsRemaining = PointBuyResult.PointsRemaining;

        // Log de feedback
        UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: %s"), *PointBuyResult.FeedbackMessage);
    }
    else
    {
        // Atualiza PointsRemaining mesmo se não foi ajustado
        PointsRemaining = PointBuyResult.PointsRemaining;
    }
}
#endif
