# 🎯 ProficiencyDataTable

> **Caminho:** `Source/MyProject2/Data/Tables/ProficiencyDataTable.h`
>
> **Struct:** `FProficiencyDataRow`

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Campos</b></summary>

> | Campo | Tipo | Descrição |
> |-------|------|-----------|
> | `Name` | `FName` | Nome da proficiência (ex: "Simple Weapons", "Thieves' Tools") |
> | `ID` | `FName` | ID único (ex: "PW_Simple_Weapons", "PT_Thieves_Tools") |
> | `Type` | `FName` | Tipo: "Weapon", "Armor", "Shield", "Tool", "Skill", "SavingThrow", "Language" |
> | `Description` | `FText` | Descrição textual (localizável) |
> | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
> | `ProficiencyData` | `TMap<FName, FString>` | Dados estruturados opcionais |

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Tipos de Proficiências</b></summary>

> - **"Weapon"**: Proficiências com armas (ex: Simple Weapons, Martial Weapons)
> - **"Armor"**: Proficiências com armaduras (ex: Light Armor, Medium Armor, Heavy Armor)
> - **"Shield"**: Proficiências com escudos
> - **"Tool"**: Proficiências com ferramentas (ex: Thieves' Tools, Herbalism Kit)
> - **"Skill"**: Proficiências com skills (ex: Acrobatics, Athletics)
> - **"SavingThrow"**: Proficiências com saving throws (ex: Strength, Dexterity)
> - **"Language"**: Proficiências com idiomas (ex: Common, Elvish)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplo de JSON - Simple Weapons</b></summary>

> ```json
> {
>   "Name": "Simple Weapons",
>   "ID": "PW_Simple_Weapons",
>   "Type": "Weapon",
>   "Description": "Proficiency with all simple weapons.",
>   "TypeTags": ["Proficiency.Weapon.Simple"],
>   "ProficiencyData": {}
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Data Tables - Índice](../../data-tables/index.md)
- [👤 RaceDataTable](../personagem/race-datatable.md) - Proficiências raciais
- [🎓 ClassDataTable](../personagem/class-datatable.md) - Proficiências de classe
- [📜 BackgroundDataTable](../personagem/background-datatable.md) - Proficiências de background

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables.md |
