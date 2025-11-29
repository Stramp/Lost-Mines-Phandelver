// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "LanguageDataTable.generated.h"

// ============================================================================
// Language Data Row
// ============================================================================
#pragma region Language Data Row

/**
 * Struct para dados de Language (idiomas D&D 5e).
 * Tabela de referência (Master Data) usada por Race, Background.
 * Herda de FTableRowBase para ser usada em UDataTable.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FLanguageDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do idioma (ex: "Common", "Elvish", "Dwarvish") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FName Name;

    /** ID único do idioma (ex: "PL_Common", "PL_Elvish", "PL_Dwarvish") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FName ID;

    /** Descrição do idioma (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FText Description;

    /** Gameplay Tags para categorização (ex: Language.Standard, Language.Exotic) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FGameplayTagContainer TypeTags;

    FLanguageDataRow() : Name(NAME_None), ID(NAME_None) {}
};

#pragma endregion Language Data Row
