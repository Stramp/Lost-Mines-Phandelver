// Copyright Epic Games, Inc. All Rights Reserved.

#include "ValidationGuard.h"

#if WITH_EDITOR

#include "Characters/Data/CharacterSheetDataAsset.h"

FValidationGuard::FValidationGuard(UCharacterSheetDataAsset *InAsset) : Asset(InAsset)
{
    if (Asset)
    {
        Asset->SetValidatingProperties(true);
    }
}

FValidationGuard::~FValidationGuard()
{
    if (Asset)
    {
        Asset->SetValidatingProperties(false);
    }
}

#endif // WITH_EDITOR
