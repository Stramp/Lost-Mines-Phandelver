# 💪 AbilityScoreDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Criar/Editar Atributos</b></summary>

> **Arquivo:** `Content/Data/JSON/AbilityScoreDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome do atributo (ex: "Strength", "Dexterity")
> - `ID` - ID único (ex: "ABL_Strength", "ABL_Dexterity")
> - `Abbreviation` - Abreviação (ex: "STR", "DEX")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Strength",
> "ID": "ABL_Strength",
> "Abbreviation": "STR",
> "Description": "Strength measures bodily power."
> }
> ```
>
> **⚠️ Importante:** Não modifique os IDs dos atributos padrão (STR, DEX, CON, INT, WIS, CHA) - eles são usados como referência em outras tabelas.

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../suporte/ability-score-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
