# 🗣️ LanguageDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/LanguageDataTable.h`
>
> **Struct:** `FLanguageDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome do idioma (ex: "Common", "Elvish", "Dwarvish") |
> | `ID` | `FName` | ID único (ex: "PL_Common", "PL_Elvish", "PL_Dwarvish") |
> | `Description` | `FText` | Descrição do idioma (localizável) |
> | `Script` | `FName` | Script usado pelo idioma (ex: "Common", "Elvish") |
> | `Type` | `FName` | Tipo: "Standard", "Exotic" |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Common</b></summary>

> ```json
> {
>   "Name": "Common",
>   "ID": "PL_Common",
>   "Description": "The most widely spoken language in the world.",
>   "Script": "Common",
>   "Type": "Standard",
>   "TypeTags": ["Language.Standard"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [👤 RaceDataTable](../personagem/race-datatable.md) - Idiomas raciais
- [📜 BackgroundDataTable](../personagem/background-datatable.md) - Idiomas de background

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
