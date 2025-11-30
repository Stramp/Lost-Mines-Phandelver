# Estrutura de Relacionamento - Data Tables

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Diagrama de Relacionamento</b></summary>

> ```mermaid
> erDiagram
> RaceDataTable ||--o{ Subrace : contains
> ClassDataTable ||--o{ Subclass : contains
> CharacterSheetDataAsset }o--|| RaceDataTable : uses
> CharacterSheetDataAsset }o--|| ClassDataTable : uses
> CharacterSheetDataAsset }o--|| BackgroundDataTable : uses
> CharacterSheetDataAsset }o--|| FeatDataTable : uses
> ```
>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](index.md) | [→ Visão Geral](visao-geral.md)

**Última atualização:** 2024-12-27
