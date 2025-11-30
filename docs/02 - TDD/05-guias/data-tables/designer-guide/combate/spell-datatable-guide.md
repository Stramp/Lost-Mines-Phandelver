# 🔮 SpellDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Criar/Editar Magias</b></summary>

> **Arquivo:** `Content/Data/JSON/SpellDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome da magia (ex: "Fireball", "Mage Hand")
> - `ID` - ID único (ex: "SPL_Fireball", "SPL_MageHand")
> - `SpellLevel` - Nível (0 = Cantrip, 1-9 = Spell Level)
> - `Description` - Descrição textual
> - `SpellData` - Map de dados estruturados (Range, Components, etc.)
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Fireball",
> "ID": "SPL_Fireball",
> "SpellLevel": 3,
> "Description": "A bright streak flashes from your pointing finger.",
> "SpellData": {
> "Range": "150 feet",
> "Components": "V, S, M",
> "Duration": "Instantaneous"
> }
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../combate/spell-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
