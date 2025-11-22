// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterSheetDataAsset.generated.h"

/**
 * Data Asset para ficha de personagem D&D 5e.
 *
 * Camada 1 da arquitetura: Editor/Configuração
 *
 * Responsabilidade: Armazenar configuração estática do personagem editável no editor.
 * Não contém lógica, apenas dados. Funciona apenas no editor para designers.
 *
 * Decisão de Design:
 * - EditDefaultsOnly: Editável apenas em defaults (não em instâncias)
 * - BlueprintReadOnly: Blueprints podem ler mas não modificar (dados autoritários)
 * - Não é replicável: Não precisa em runtime, apenas no editor
 *
 * Fluxo: CharacterSheetComponent lê este Data Asset e copia para CharacterDataComponent em runtime.
 */
UCLASS(BlueprintType)
class MYPROJECT2_API UCharacterSheetDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /** Nome do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Sheet")
    FName CharacterName = TEXT("Character Name");

    /** Descrição do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Sheet")
    FName CharacterDescription = TEXT("Character Description");

    /** Nível total do personagem */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Sheet")
    int16 CharacterTotalLvl = 0;
};
