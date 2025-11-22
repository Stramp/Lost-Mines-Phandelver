// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterSheetDataAsset.generated.h"

/**
 * Data Asset para ficha de personagem D&D 5e.
 * Armazena configuração estática do personagem (editável no editor).
 *
 * Este é o primeiro passo: apenas o nome do personagem.
 * Vamos adicionar mais propriedades gradualmente.
 */
UCLASS(BlueprintType)
class MYPROJECT2_API UCharacterSheetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Nome do personagem */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	FName CharacterName;
};
