# 🎒 ItemDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛍️ Criar/Editar Itens</b></summary>

> **Arquivo:** `Content/Data/JSON/ItemDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome do item (ex: "Longsword", "Chain Mail")
> - `ID` - ID único (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail")
> - `ItemType` - Tipo ("Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold")
> - `Weight` - Peso em libras (float)
> - `Value` - Valor em ouro (int32)
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Longsword",
> "ID": "ITM_WPN_Longsword",
> "ItemType": "Weapon",
> "Weight": 3.0,
> "Value": 15,
> "Description": "A versatile melee weapon."
> }
> ```
>
> **💡 Dica:** Use o padrão de nomenclatura de IDs:
> - `ITM_WPN_*` = Weapon
> - `ITM_ARM_*` = Armor
> - `ITM_TOL_*` = Tool
> - `ITM_GOLD_*` = Gold

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../suporte/item-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
