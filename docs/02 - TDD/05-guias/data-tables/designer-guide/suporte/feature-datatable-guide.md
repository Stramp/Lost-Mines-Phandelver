# ⚙️ FeatureDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎁 Criar/Editar Features</b></summary>

> **Arquivo:** `Content/Data/JSON/FeatureDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome da feature (ex: "Second Wind", "Fighting Style")
> - `ID` - ID único (ex: "FC_SecondWind", "FC_FightingStyle")
> - `Description` - Descrição textual
> - `LevelUnlocked` - Nível em que é desbloqueada
> - `FeatureType` - Tipo ("Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection")
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Second Wind",
> "ID": "FC_SecondWind",
> "Description": "You have a limited well of stamina.",
> "LevelUnlocked": 1,
> "FeatureType": "Automatic",
> "FeatureData": {
> "UsesPerRest": "1"
> }
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../suporte/feature-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
