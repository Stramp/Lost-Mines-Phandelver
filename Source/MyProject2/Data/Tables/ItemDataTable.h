// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// ============================================================================
// Includes
// ============================================================================
#pragma region Includes

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

#pragma endregion Includes

// ============================================================================
// Item Data Row Struct
// ============================================================================
#pragma region Item Data Row Struct

/**
 * Struct principal para dados de itens D&D 5e usada em UDataTable.
 * Herda de FTableRowBase para ser usada em UDataTable.
 * Segue a estrutura do Item_All.json.
 *
 * Itens incluem: armas, armaduras, ferramentas, consumíveis, packs e outros equipamentos.
 * Também inclui itens especiais de ouro (ITM_GOLD_*).
 */
USTRUCT(BlueprintType)
struct MYPROJECT2_API FItemDataRow : public FTableRowBase
{
    GENERATED_BODY()

    /**
     * ID único do item (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail", "ITM_GOLD_15gp").
     * Usado como chave primária na Data Table e para referências em outras estruturas.
     * Padrão de nomenclatura:
     * - ITM_WPN_* = Item Weapon
     * - ITM_ARM_* = Item Armor
     * - ITM_TOL_* = Item Tool
     * - ITM_PCK_* = Item Pack
     * - ITM_CNM_* = Item Consumable
     * - ITM_OTH_* = Item Other
     * - ITM_GOLD_* = Item Gold (ouro)
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemID;

    /**
     * Nome do item (ex: "Longsword", "Chain Mail", "15 gp").
     * Nome legível para exibição na UI.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemName;

    /**
     * Tipo do item: "Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold".
     * Usado para categorização e filtragem de itens.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemType;

    /**
     * Peso do item em libras (lbs).
     * Usado para calcular peso total do inventário e validar Carrying Capacity.
     * Ouro tem peso 0.0.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float Weight = 0.0f;

    /**
     * Valor do item em ouro (gp).
     * Para itens de ouro (ITM_GOLD_*), este é o valor em gp.
     * Para outros itens, é o preço de compra/venda.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 Value = 0;

    /**
     * Descrição do item (localizável).
     * Descrição textual completa do item para exibição na UI.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Description;

    FItemDataRow() : ItemID(NAME_None), ItemName(NAME_None), ItemType(NAME_None), Weight(0.0f), Value(0) {}

    FItemDataRow(const FName &InItemID, const FName &InItemName, const FName &InItemType, float InWeight, int32 InValue,
                 const FText &InDescription)
        : ItemID(InItemID), ItemName(InItemName), ItemType(InItemType), Weight(InWeight), Value(InValue),
          Description(InDescription)
    {
    }
};

#pragma endregion Item Data Row Struct
