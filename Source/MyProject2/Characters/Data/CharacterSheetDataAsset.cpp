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

    if (bIsValidatingProperties || !PropertyChangedEvent.Property)
    {
        return;
    }

    const FName PropertyName = PropertyChangedEvent.Property->GetFName();

    if (IsCalculatedProperty(PropertyName))
    {
        return;
    }

    EnsurePropertyHandlersInitialized();

    if (PropertyHandlerFunction *HandlerPtr = PropertyHandlers.Find(PropertyName))
    {
        (*HandlerPtr)(this, PropertyName);
    }
}

bool UCharacterSheetDataAsset::IsCalculatedProperty(FName PropertyName) const
{
    return PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bIsVariantHuman) ||
           PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bHasLanguageChoices) ||
           PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bHasSubraces) ||
           PropertyName == GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bCanShowSheet);
}

void UCharacterSheetDataAsset::EnsurePropertyHandlersInitialized()
{
    if (PropertyHandlers.Num() == 0)
    {
        InitializePropertyHandlers();
    }
}

void UCharacterSheetDataAsset::InitializePropertyHandlers()
{
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedRace),
                         FCharacterSheetDataAssetHandlers::HandleSelectedRaceWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSubrace),
                         FCharacterSheetDataAssetHandlers::HandleSelectedSubraceWrapper);

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

    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedBackground),
                         FCharacterSheetDataAssetHandlers::HandleSelectedBackgroundWrapper);

    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, CustomAbilityScoreChoices),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedFeat),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);
    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedSkill),
                         FCharacterSheetDataAssetHandlers::HandleVariantHumanChoicesWrapper);

    PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, SelectedLanguages),
                         FCharacterSheetDataAssetHandlers::HandleLanguageChoicesWrapper);

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
    FCharacterSheetData Data(PointBuyStrength, PointBuyDexterity, PointBuyConstitution, PointBuyIntelligence,
                             PointBuyWisdom, PointBuyCharisma, SelectedRace, SelectedSubrace, CustomAbilityScoreChoices,
                             RaceDataTable, &FinalStrength, &FinalDexterity, &FinalConstitution, &FinalIntelligence,
                             &FinalWisdom, &FinalCharisma);

    FPointBuyResult PointBuyResult;
    FCharacterSheetCore::RecalculateFinalScores(Data, &PointBuyResult);

    PointsRemaining = PointBuyResult.PointsRemaining;

    if (PointBuyResult.bWasAdjusted)
    {
        Modify();
        FCharacterSheetDataAssetHelpers::UpdatePointBuyFromAdjustedAllocation(this, PointBuyResult.AdjustedAllocation);
        UE_LOG(LogTemp, Warning, TEXT("CharacterSheetDataAsset: %s"), *PointBuyResult.FeedbackMessage);
    }
}
#endif
