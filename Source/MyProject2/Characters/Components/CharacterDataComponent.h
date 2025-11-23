// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDataComponent.generated.h"

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
};
