// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Data/Tables/FeatureDataTable.h"
#include "FeatDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Feat Data Struct
// ============================================================================
#pragma region Feat Data Struct

/**
 * Struct principal para dados de feats gerais D&D 5e.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Segue o padrão de FFeatureDataRow para consistência estrutural.
 * Contém todas as informações necessárias para um feat: nome, descrição, tipo, nível e dados estruturados.
 *
 * Feats são habilidades especiais que personagens podem adquirir ao invés de aumentar
 * Ability Scores. Exemplos: Alert, Magic Initiate, War Caster, Sharpshooter.
 *
 * Estrutura alinhada com FeatDataTable.json:
 * - Name: Nome do feat
 * - ID: ID único (ex: "Feat_Alert", "Feat_MagicInitiate")
 * - Description: Descrição textual
 * - LevelUnlocked: Nível mínimo (padrão: 4)
 * - FeatureType: "Feat"
 * - FeatureData: Dados estruturados (Prerequisites, Benefits, etc.)
 * - AvailableChoices: Escolhas disponíveis (geralmente vazio para feats)
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FFeatDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /** Nome do feat (ex: "Alert", "Magic Initiate", "War Caster", "Sharpshooter") - Key Field */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FName Name;

    /** ID único do feat (ex: "Feat_Alert", "Feat_MagicInitiate", "Feat_WarCaster") */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FName ID;

    /** Gameplay Tags para categorização (ex: Feat.Alert, Feat.Combat) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FGameplayTagContainer TypeTags;

    /** Descrição textual do feat (localizável, para exibição na UI) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FText Description;

    /** Nível em que o feat é desbloqueado (padrão: 4, nível mínimo para feats em D&D 5e) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    int32 LevelUnlocked = 4;

    /**
     * Tipo da feature: "Feat"
     * Mantido para consistência com FFeatureDataRow.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    FName FeatureType;

    /**
     * Dados estruturados do feat (dados programáticos).
     * Permite armazenar informações programáticas além da descrição textual.
     *
     * Estrutura esperada:
     * - "Prerequisites": String ou array de pré-requisitos (ex: "Strength 13" ou ["Strength 13", "Dexterity 15"])
     * - Benefícios específicos do feat (ex: "InitiativeBonus": "5", "CannotBeSurprised": "true")
     *
     * Exemplo para Alert:
     * {"InitiativeBonus": "5", "CannotBeSurprised": "true", "NoAdvantageFromHidden": "true"}
     *
     * Exemplo para Magic Initiate:
     * {"SpellcastingAbility": "Intelligence", "Cantrips": "2", "FirstLevelSpells": "1"}
     *
     * Exemplo para Defensive Duelist:
     * {"Prerequisites": "Dexterity 13", "ReactionACBonus": "proficiency", "RequiresFinesseWeapon": "true"}
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    TMap<FName, FString> FeatureData;

    /**
     * Escolhas disponíveis para feats que permitem escolhas (geralmente vazio).
     * Array vazio para a maioria dos feats.
     * Pode conter escolhas para feats especiais que permitem seleção.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Feat")
    TArray<FFeatureChoice> AvailableChoices;

    /**
     * Indica se o feat permite que o jogador escolha múltiplas opções.
     *
     * Comportamento:
     * - false (padrão): Jogador escolhe apenas 1 opção (ex: Elemental Adept escolhe 1 tipo de dano)
     * - true: Jogador pode escolher múltiplas opções (raro em feats D&D 5e)
     *
     * Apenas relevante quando há escolhas disponíveis em AvailableChoices.
     * Campo oculto no editor - configurado apenas via JSON/Data Table.
     */
    UPROPERTY(BlueprintReadWrite, Category = "Feat", meta = (Hidden))
    bool bAllowMultipleChoices = false;

    FFeatDataRow()
        : Name(NAME_None), ID(NAME_None), Description(FText::GetEmpty()), LevelUnlocked(4), FeatureType(NAME_None),
          bAllowMultipleChoices(false)
    {
    }

    FFeatDataRow(const FName &InName, const FName &InID, const FText &InDescription, int32 InLevelUnlocked = 4,
                 const FName &InFeatureType = TEXT("Feat"))
        : Name(InName), ID(InID), Description(InDescription), LevelUnlocked(InLevelUnlocked),
          FeatureType(InFeatureType), bAllowMultipleChoices(false)
    {
    }

    /**
     * Helper: Extrai pré-requisitos de FeatureData.
     * Prerequisites podem estar como string única ou array de strings separadas por vírgula.
     * Retorna array de FName para compatibilidade com código existente.
     */
    TArray<FName> GetPrerequisites() const;
};

#pragma endregion Feat Data Struct
