# 🏋️ SkillDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/SkillDataTable.h`
>
> **Struct:** `FSkillDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome da skill (ex: "Acrobatics", "Athletics", "Stealth") |
> | `ID` | `FName` | ID único (ex: "PSK_Acrobatics", "PSK_Athletics") |
> | `AbilityID` | `FName` | ID do Ability Score associado (ex: "ABL_Dexterity", "ABL_Strength") |
> | `Description` | `FText` | Descrição da skill (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Acrobatics</b></summary>

> ```json
> {
>   "Name": "Acrobatics",
>   "ID": "PSK_Acrobatics",
>   "AbilityID": "ABL_Dexterity",
>   "Description": "Your Dexterity (Acrobatics) check covers your attempt to stay on your feet in a tricky situation.",
>   "TypeTags": ["Skill.Physical", "Skill.Dexterity"]
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [💪 AbilityScoreDataTable](./ability-score-datatable.md) - Ability Scores associados
- [📋 ProficiencyDataTable](./proficiency-datatable.md) - Proficiências de skills

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
