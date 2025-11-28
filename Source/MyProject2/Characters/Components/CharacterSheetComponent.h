// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "CharacterSheetComponent.generated.h"

class UCharacterSheetDataAsset;
class UCharacterDataComponent;

/**
 * Bridge Component - Camada 2
 * Faz ponte entre Data Asset e Runtime Component, aplica regras de raça e classe.
 *
 * Responsabilidade: Carregar dados do Data Asset para Runtime Component.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT2_API UCharacterSheetComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterSheetComponent();

    /**
     * Inicializa o componente a partir de um Data Asset.
     * Lê os dados do Data Asset e copia para o CharacterDataComponent.
     */
    UFUNCTION(BlueprintCallable, Category = "Character")
    void InitializeFromDataAsset(UCharacterSheetDataAsset *DataAsset);

    /**
     * Configura propriedades replicáveis para multiplayer.
     * Segue princípio "Multiplayer-Ready" da arquitetura.
     */
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual void BeginPlay() override;

private:
    /** Data Asset fonte (template) - Replicável para multiplayer */
    UPROPERTY(Replicated, EditAnywhere, Category = "Character Sheet")
    UCharacterSheetDataAsset *SourceDataAsset;

    /** Referência ao componente de dados em runtime */
    UPROPERTY()
    UCharacterDataComponent *CharacterDataComponent;
};
