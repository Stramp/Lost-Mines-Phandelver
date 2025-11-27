// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDataComponent.generated.h"

// Forward declarations
struct FLogContext;

/**
 * Componente de dados do personagem em runtime.
 *
 * Camada 3 da arquitetura: Runtime Data Components
 *
 * Responsabilidade: Armazenar dados replicáveis do personagem em runtime.
 * Todas as propriedades devem ser replicáveis para suportar multiplayer.
 *
 * Decisão de Design:
 * - BlueprintReadWrite/ReadOnly: Controla acesso de Blueprints
 * - CharacterTotalLvl é ReadOnly: Calculado automaticamente, não editável
 * - Preparado para migração futura para GAS Attributes
 *
 * Fluxo: Recebe dados do CharacterSheetComponent e replica para clientes via DOREPLIFETIME.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UCharacterDataComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    UCharacterDataComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const override;

    /** Nome do personagem */
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
    FName CharacterName = NAME_None;

    /** Descrição do personagem (localizável) */
    UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
    FText CharacterDescription = FText::GetEmpty();

    /** Nível total do personagem */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    int32 CharacterTotalLvl = 0;

    /** Raça selecionada */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    FName SelectedRace = NAME_None;

    /** Sub-raça selecionada */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    FName SelectedSubrace = NAME_None;

    /** Background selecionado */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    FName SelectedBackground = NAME_None;

    /** Proficiências do personagem (raça + classe + background) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    TArray<FName> Proficiencies;

    /** Features disponíveis do personagem (raça + classe) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    TArray<FName> AvailableFeatures;

    /** Variant Human: Feat escolhido (se aplicável) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    FName SelectedFeat = NAME_None;

    /** Variant Human: Skill escolhido (se aplicável) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    FName SelectedSkill = NAME_None;

    /** Variant Human: Escolhas customizadas de ability scores (se aplicável) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    TArray<FName> CustomAbilityScoreChoices;

    /** Traits da raça (ex: Darkvision, Fey Ancestry) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    TArray<FName> RaceTraits;

    /** Idiomas que o personagem fala (automáticos + escolhidos) */
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
    TArray<FName> Languages;

    /** Ability scores finais (chave: nome do atributo, valor: score final)
     * NOTA: TMap não pode ser replicado diretamente no Unreal Engine.
     * Para replicação futura, usar TArray de structs ou implementar replicação customizada.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Character Data")
    TMap<FName, int32> AbilityScores;

    /**
     * Valida integridade dos dados do personagem.
     * Verifica se todos os dados necessários estão presentes e consistentes.
     *
     * @return true se todos os dados estão válidos, false caso contrário
     */
    UFUNCTION(BlueprintCallable, Category = "Character Data")
    bool ValidateDataIntegrity() const;

    /**
     * Faz log da ficha do personagem no console.
     * Valida integridade dos dados antes de exibir.
     * Este log garante que a informação está totalmente organizada e bem disposta
     * nos componentes necessários para tudo funcionar bem.
     */
    UFUNCTION(BlueprintCallable, Category = "Character Data")
    void LogCharacterSheet() const;

private:
    // ============================================================================
    // Validation Helpers
    // ============================================================================

    /**
     * Valida integridade dos Ability Scores.
     * Verifica se todos os 6 atributos estão presentes e com valores válidos.
     *
     * @param Context Contexto de log para mensagens de erro
     * @return true se todos os ability scores são válidos, false caso contrário
     */
    bool ValidateAbilityScoresIntegrity(const FLogContext &Context) const;

    /**
     * Valida dados básicos do personagem (Raça, Background, Nome).
     *
     * @param Context Contexto de log para mensagens de erro
     * @return true se dados básicos são válidos, false caso contrário
     */
    bool ValidateBasicDataIntegrity(const FLogContext &Context) const;

    /**
     * Valida nível total do personagem.
     *
     * @param Context Contexto de log para mensagens de erro
     * @return true se nível é válido, false caso contrário
     */
    bool ValidateLevelIntegrity(const FLogContext &Context) const;

    // ============================================================================
    // Logging Helpers
    // ============================================================================

    /**
     * Faz log das informações básicas do personagem.
     *
     * @param Context Contexto de log
     */
    void LogBasicInfo(const FLogContext &Context) const;

    /**
     * Faz log das escolhas de Variant Human (se aplicável).
     *
     * @param Context Contexto de log
     */
    void LogVariantHumanChoices(const FLogContext &Context) const;

    /**
     * Faz log dos Ability Scores.
     *
     * @param Context Contexto de log
     */
    void LogAbilityScores(const FLogContext &Context) const;

    /**
     * Faz log de proficiências e idiomas.
     *
     * @param Context Contexto de log
     */
    void LogProficienciesAndLanguages(const FLogContext &Context) const;

    /**
     * Faz log das features disponíveis.
     *
     * @param Context Contexto de log
     */
    void LogAvailableFeatures(const FLogContext &Context) const;

    /**
     * Faz log do resultado da validação de integridade.
     *
     * @param Context Contexto de log
     */
    void LogDataIntegrityResult(const FLogContext &Context) const;
};
