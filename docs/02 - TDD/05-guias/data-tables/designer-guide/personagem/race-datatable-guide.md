# 👥 RaceDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏃 Criar/Editar Raças</b></summary>

> **Arquivo:** `Content/Data/JSON/RaceDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome da raça (ex: "Human", "Elf")
> - `ID` - ID único (ex: "RACE_Human", "RACE_Elf")
> - `Description` - Descrição textual
> - `AbilityScoreImprovements` - Array de bônus de atributos
> - `Size` - Tamanho ("Small", "Medium", "Large")
> - `BaseSpeed` - Velocidade em pés (geralmente 30)
>
> **Exemplo completo:**
>
> ```json
> {
> "Name": "Dwarf",
> "ID": "RACE_Dwarf",
> "Description": "Bold and hardy dwarves are known as skilled warriors.",
> "AbilityScoreImprovements": [
> {
> "AbilityID": "ABL_Constitution",
> "Bonus": 2
> }
> ],
> "Size": "Medium",
> "BaseSpeed": 25,
> "TraitHandles": [],
> "SubraceHandles": [],
> "LanguageHandles": []
> }
> ```
>
> **💡 Dica:** Use `AbilityID` ao invés de `AbilityName`. Os IDs estão em `AbilityScoreDataTable`.

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../personagem/race-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
