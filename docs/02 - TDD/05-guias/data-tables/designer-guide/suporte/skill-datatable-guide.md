# 🏋️ SkillDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Criar/Editar Skills</b></summary>

> **Arquivo:** `Content/Data/JSON/SkillDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome da skill (ex: "Acrobatics", "Athletics")
> - `ID` - ID único (ex: "PSK_Acrobatics", "PSK_Athletics")
> - `AbilityID` - ID do atributo associado (ex: "ABL_Dexterity", "ABL_Strength")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Acrobatics",
> "ID": "PSK_Acrobatics",
> "AbilityID": "ABL_Dexterity",
> "Description": "Your Dexterity (Acrobatics) check covers your attempt to stay on your feet."
> }
> ```
>
> **💡 Dica:** O `AbilityID` deve referenciar um ID válido de `AbilityScoreDataTable`.

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../suporte/skill-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
