# 🔥 DamageTypeDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/DamageTypeDataTable.h`
>
> **Struct:** `FDamageTypeDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome do tipo de dano (ex: "Fire", "Cold", "Lightning") |
> | `ID` | `FName` | ID único (ex: "DAM_Fire", "DAM_Cold", "DAM_Lightning") |
> | `Description` | `FText` | Descrição do tipo de dano (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Fire</b></summary>

> ```json
> {
>   "Name": "Fire",
>   "ID": "DAM_Fire",
>   "Description": "Fire damage is dealt by flames, heat, and magical fire effects.",
>   "TypeTags": ["DamageType.Fire", "DamageType.Elemental"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [🔮 SpellDataTable](./spell-datatable.md) - Magias que causam este tipo de dano

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
