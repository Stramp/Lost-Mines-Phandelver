// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/Tables/ClassDataTable.h"
#include "MulticlassingResult.generated.h"

/**
 * Struct para opção de classe com informação de disponibilidade.
 * Usado para filtrar classes no dropdown baseado em requisitos de atributo.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassOption
{
    GENERATED_BODY()

    /** Nome da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Option")
    FName ClassName;

    /**
     * Mensagem de requisito de atributo.
     * - String vazia ("") = classe disponível
     * - String preenchida (ex: "DEX 13") = classe não disponível, mostra requisito
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class Option")
    FString RequirementMessage;

    FClassOption() : ClassName(NAME_None), RequirementMessage(TEXT("")) {}

    FClassOption(const FName &InClassName, const FString &InRequirementMessage)
        : ClassName(InClassName), RequirementMessage(InRequirementMessage)
    {
    }
};

/**
 * Struct para armazenar informações de spellcasting de uma classe.
 * Usado para interface com SpellSystem futuro (dados brutos).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FClassSpellcastingInfo
{
    GENERATED_BODY()

    /** Nome da classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
    FName ClassName;

    /** Nível nesta classe */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
    int32 ClassLevel;

    /** Se a classe possui spellcasting */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
    bool bHasSpellcasting;

    /** Atributo usado para spellcasting */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
    FName SpellcastingAbility;

    /** Spell slots por nível (array indexado por nível de spell) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spellcasting")
    TArray<int32> SpellSlotsPerLevel;

    FClassSpellcastingInfo()
        : ClassName(NAME_None), ClassLevel(0), bHasSpellcasting(false), SpellcastingAbility(NAME_None)
    {
    }
};

/**
 * Struct de resultado do motor de multiclassing.
 * Contém todos os dados calculados pelo MulticlassingMotor.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FMulticlassingResult
{
    GENERATED_BODY()

    /** Nível total do personagem (soma de todos os níveis de classe) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclassing")
    int32 TotalLevel = 0;

    /** Bônus de proficiência baseado no TotalLevel */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclassing")
    int32 ProficiencyBonus = 0;

    /** Features disponíveis no nível atual (com escolhas resolvidas) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclassing")
    TArray<FClassFeature> AvailableFeatures;

    /** Informações de spellcasting para SpellSystem (dados brutos) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiclassing")
    TArray<FClassSpellcastingInfo> SpellcastingInfo;

    FMulticlassingResult() : TotalLevel(0), ProficiencyBonus(0) {}
};
