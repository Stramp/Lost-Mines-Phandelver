// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FeatDataTable.generated.h"

/**
 * Struct principal para dados de feats gerais D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Contém todas as informações necessárias para um feat: nome, descrição, pré-requisitos e benefícios.
 *
 * Feats são habilidades especiais que personagens podem adquirir ao invés de aumentar
 * Ability Scores. Exemplos: Alert, Magic Initiate, War Caster, Sharpshooter.
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FFeatDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do feat (ex: "Alert", "Magic Initiate", "War Caster", "Sharpshooter") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FName FeatName;

    /** Descrição textual do feat (localizável, para exibição na UI) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FText Description;

    /**
     * Pré-requisitos para adquirir o feat.
     * Array de strings descrevendo os requisitos (ex: "Strength 13", "Proficiency in Heavy Armor").
     * Pode ser array vazio se o feat não tiver pré-requisitos.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    TArray<FName> Prerequisites;

    /**
     * Benefícios estruturados do feat (dados programáticos).
     * Permite armazenar informações programáticas além da descrição textual.
     * Exemplo: {"InitiativeBonus": "5", "CannotBeSurprised": "true"} para Alert
     * Exemplo: {"SpellcastingAbility": "Intelligence", "Cantrips": "2", "FirstLevelSpells": "1"} para Magic Initiate
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    TMap<FName, FString> Benefits;

    FFeatDataRow() : FeatName(NAME_None), Description(FText::GetEmpty()) {}

    FFeatDataRow(const FName &InFeatName, const FText &InDescription) : FeatName(InFeatName), Description(InDescription)
    {
    }
};
