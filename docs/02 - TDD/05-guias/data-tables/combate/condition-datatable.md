# ⚠️ ConditionDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/ConditionDataTable.h`
>
> **Struct:** `FConditionDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome da condição (ex: "Blinded", "Poisoned", "Charmed") |
> | `ID` | `FName` | ID único (ex: "CON_Blinded", "CON_Poisoned", "CON_Charmed") |
> | `Description` | `FText` | Descrição da condição (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Blinded</b></summary>

> ```json
> {
>   "Name": "Blinded",
>   "ID": "CON_Blinded",
>   "Description": "A blinded creature can't see and automatically fails any ability check that requires sight.",
>   "TypeTags": ["Condition.Blinded", "Condition.Debuff"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [🔮 SpellDataTable](./spell-datatable.md) - Magias que causam condições
- [📋 TDD - Condições](../../04-regras-dnd/sistemas/conditions-algorithm.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
