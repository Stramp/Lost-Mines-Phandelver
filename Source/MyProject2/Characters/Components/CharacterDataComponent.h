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

    /** Nome do personagem */
    UPROPERTY(BlueprintReadWrite, Category = "Character Data")
    FName CharacterName = NAME_None;

    /** Descrição do personagem (localizável) */
    UPROPERTY(BlueprintReadWrite, Category = "Character Data")
    FText CharacterDescription = FText::GetEmpty();

    /** Nível total do personagem */
    UPROPERTY(BlueprintReadOnly, Category = "Character Data")
    int32 CharacterTotalLvl = 0;

    /**
     * Faz log da ficha do personagem no console.
     */
    UFUNCTION(BlueprintCallable, Category = "Character Data")
    void LogCharacterSheet() const;
};
