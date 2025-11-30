# 🏷️ TraitDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/TraitDataTable.h`
>
> **Struct:** `FTraitDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome do trait (ex: "Darkvision", "Fey Ancestry", "Trance") |
> | `ID` | `FName` | ID único (ex: "TR_Darkvision", "TR_FeyAncestry", "TR_Trance") |
> | `Description` | `FText` | Descrição textual do trait (localizável) |
> | `TraitData` | `TMap<FName, FString>` | Dados estruturados (ex: Range para Darkvision) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
> | `SpellReference` | `FDataTableRowHandle` | Referência a uma magia (se aplicável) |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Darkvision</b></summary>

> ```json
> {
>   "Name": "Darkvision",
>   "ID": "TR_Darkvision",
>   "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
>   "TraitData": {
>     "Range": "60"
>   },
>   "TypeTags": ["Trait.Vision.Darkvision", "Trait.Racial"],
>   "SpellReference": {}
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
> - [👤 RaceDataTable](../personagem/race-datatable.md) - Traits raciais
> - [🔮 SpellDataTable](../combate/spell-datatable.md) - Referências a magias

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
