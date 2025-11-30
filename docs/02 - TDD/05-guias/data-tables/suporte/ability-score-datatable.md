# 💪 AbilityScoreDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h`
>
> **Struct:** `FAbilityScoreDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome do atributo (ex: "Strength", "Dexterity", "Constitution") |
> | `ID` | `FName` | ID único (ex: "ABL_Strength", "ABL_Dexterity", "ABL_Constitution") |
> | `Abbreviation` | `FName` | Abreviação (ex: "STR", "DEX", "CON") |
> | `Description` | `FText` | Descrição do atributo (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Strength</b></summary>

> ```json
> {
>   "Name": "Strength",
>   "ID": "ABL_Strength",
>   "Abbreviation": "STR",
>   "Description": "Strength measures bodily power, athletic training, and the extent to which you can exert raw physical force.",
>   "TypeTags": ["Ability.Physical", "Ability.Strength"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [🏋️ SkillDataTable](./skill-datatable.md) - Skills associadas aos Ability Scores
- [👤 RaceDataTable](../personagem/race-datatable.md) - Bônus raciais de Ability Scores

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
