# 🎓 SpellSchoolDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/SpellSchoolDataTable.h`
>
> **Struct:** `FSpellSchoolDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome da escola (ex: "Abjuration", "Evocation", "Necromancy") |
> | `ID` | `FName` | ID único (ex: "SCH_Abjuration", "SCH_Evocation") |
> | `Description` | `FText` | Descrição da escola (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Evocation</b></summary>

> ```json
> {
>   "Name": "Evocation",
>   "ID": "SCH_Evocation",
>   "Description": "Evocation spells manipulate magical energy to produce a desired effect.",
>   "TypeTags": ["SpellSchool.Evocation"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [🔮 SpellDataTable](./spell-datatable.md) - Magias que usam esta escola

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
