# 🎒 ItemDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/ItemDataTable.h`
>
> **Struct:** `FItemDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome do item (ex: "Longsword", "Chain Mail", "15 gp") |
> | `ID` | `FName` | ID único (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail", "ITM_GOLD_15gp") |
> | `ItemType` | `FName` | Tipo: "Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold" |
> | `Weight` | `float` | Peso do item em libras (lbs) |
> | `Value` | `int32` | Valor do item em ouro (gp) |
> | `Description` | `FText` | Descrição do item (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Padrão de Nomenclatura de IDs</b></summary>

> - **ITM_WPN_*** = Item Weapon
> - **ITM_ARM_*** = Item Armor
> - **ITM_TOL_*** = Item Tool
> - **ITM_PCK_*** = Item Pack
> - **ITM_CNM_*** = Item Consumable
> - **ITM_OTH_*** = Item Other
> - **ITM_GOLD_*** = Item Gold (ouro)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Longsword</b></summary>

> ```json
> {
>   "Name": "Longsword",
>   "ID": "ITM_WPN_Longsword",
>   "ItemType": "Weapon",
>   "Weight": 3.0,
>   "Value": 15,
>   "Description": "A versatile melee weapon.",
>   "TypeTags": ["Item.Weapon.Martial", "Item.Weapon.Melee"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [📋 TDD - Equipamentos](../../04-regras-dnd/sistemas/equipment-system.md)
- [📋 TDD - Inventário](../../04-regras-dnd/sistemas/inventory-system.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
