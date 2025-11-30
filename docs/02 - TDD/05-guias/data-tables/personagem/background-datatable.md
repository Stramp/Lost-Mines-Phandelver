# BackgroundDataTable

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 BackgroundDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/BackgroundDataTable.h`
>
> **Struct:** `FBackgroundDataRow`

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `BackgroundName` | `FName` | Nome do background (ex: "Acolyte", "Criminal", "Noble") |
> | `Description` | `FText` | Descrição textual do background |
> | `SkillProficiencies` | `TArray<FName>` | Skills em que o background fornece proficiência |
> | `LanguageProficiencies` | `TArray<FName>` | Idiomas em que o background fornece proficiência |
> | `Equipment` | `TArray<FName>` | Equipamento inicial (FNames de itens) |
> | `FeatureName` | `FName` | Nome da feature especial do background |
> | `FeatureDescription` | `FText` | Descrição da feature |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Acolyte</b></summary>

> ```json
> {
>   "Name": "Acolyte",
>   "BackgroundName": "Acolyte",
>   "Description": "You have spent your life in the service of a temple.",
>   "SkillProficiencies": ["Insight", "Religion"],
>   "LanguageProficiencies": ["Common", "One additional language"],
>   "Equipment": ["Holy Symbol", "Prayer Book", "Common Clothes", "15 Gold"],
>   "FeatureName": "Shelter of the Faithful",
>   "FeatureDescription": "You and your adventuring companions can receive free healing and care at a temple."
> }
> ```

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](../index.md) | [→ ClassDataTable](class-datatable.md)

**Última atualização:** 2024-12-27
