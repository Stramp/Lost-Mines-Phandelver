# ⚔️ ClassDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎭 Criar/Editar Classes</b></summary>

> **Arquivo:** `Content/Data/JSON/ClassDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome da classe (ex: "Fighter", "Wizard")
> - `ID` - ID único (ex: "CLASS_Fighter", "CLASS_Wizard")
> - `Description` - Descrição textual
> - `HitDie` - Dado de vida (6, 8, 10, 12)
> - `Proficiencies` - Array de proficiências
> - `Progression` - Array de progressão por nível
>
> **Exemplo simplificado:**
>
> ```json
> {
> "Name": "Fighter",
> "ID": "CLASS_Fighter",
> "Description": "A master of martial combat.",
> "HitDie": 10,
> "Proficiencies": [
> {
> "ProficiencyType": "Armor",
> "ProficiencyName": "All Armor"
> }
> ],
> "Progression": [
> {
> "Level": 1,
> "Features": ["Fighting Style", "Second Wind"]
> }
> ]
> }
> ```
>
> **💡 Dica:** A progressão é complexa. Consulte a documentação completa em [data-tables.md](../../data-tables.md#classdatatable).

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../personagem/class-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
