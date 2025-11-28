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

    /** ID único do idioma (ex: "PL_Common", "PL_Elvish") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FName LanguageID;

    /** Nome do idioma (ex: "Common", "Elvish") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FText LanguageName;

    /** Descrição do idioma (localizável) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FText Description;

    /** Script usado pelo idioma (ex: "Common", "Elvish") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FName Script;

    /** Tipo do idioma (ex: "Standard", "Exotic") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FName Type;

    /** Gameplay Tags para categorização (ex: Language.Standard, Language.Exotic) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Language")
    FGameplayTagContainer TypeTags;

    FLanguageDataRow()
        : LanguageID(NAME_None), Script(NAME_None), Type(NAME_None)
    {
    }
};

#pragma endregion Language Data Row
