# ⭐ FeatDataTable - Guia para Designers

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💫 Criar/Editar Feats</b></summary>

> **Arquivo:** `Content/Data/JSON/FeatDataTable.json`
>
> **Campos obrigatórios:**
>
> - `Name` - Nome do feat (ex: "Alert", "Great Weapon Master")
> - `ID` - ID único (ex: "FEAT_Alert", "FEAT_GreatWeaponMaster")
> - `Description` - Descrição textual
> - `Prerequisites` - Array de pré-requisitos (pode ser vazio)
> - `Benefits` - Map de benefícios estruturados
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Alert",
> "ID": "FEAT_Alert",
> "Description": "Always on the lookout for danger.",
> "Prerequisites": [],
> "Benefits": {
> "InitiativeBonus": "5",
> "CannotBeSurprised": "true"
> }
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia para Designers - Índice](../index.md)
- [📖 Guia Rápido](../guia-rapido.md)
- [📊 Documentação Técnica Completa](../../suporte/feat-datatable.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de data-tables-designer-guide.md |
