---
title: "Data Tables - Índice"
category: technical
subcategory: data-tables
tags: [datatables, documentation, index]
last_updated: 2024-12-27
difficulty: beginner
related: [../data-architecture/index.md, ../../design/dnd-rules/index.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../index.md) > [Técnico](../technical/index.md) > Data Tables

# Data Tables - Documentação Técnica

> **Objetivo:** Índice centralizado da documentação técnica de todas as Data Tables do projeto.
>
> **Público-alvo:** Desenvolvedores e designers que precisam trabalhar com dados do jogo.

---

## 📋 Data Tables Disponíveis

### 🎯 Principais (Personagem)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Completa</b></summary>

> - **[RaceDataTable](race-datatable.md)** ✅ - Raças e sub-raças D&D 5e
> - **[ClassDataTable](class-datatable.md)** ✅ - Classes D&D 5e com multiclassing
> - **[BackgroundDataTable](background-datatable.md)** ⏳ - Backgrounds D&D 5e
> - **[FeatDataTable](feat-datatable.md)** ⏳ - Feats D&D 5e
> - **[FeatureDataTable](feature-datatable.md)** ⏳ - Features de classes/raças

</details>

### 🔧 Suporte (Sistemas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Sistemas de Suporte</b></summary>

> - **[ProficiencyDataTable](proficiency-datatable.md)** ⏳ - Proficiências (armas, armaduras, ferramentas)
> - **[SkillDataTable](skill-datatable.md)** ⏳ - Skills D&D 5e
> - **[AbilityScoreDataTable](abilityscore-datatable.md)** ⏳ - Ability Scores (STR, DEX, CON, etc.)
> - **[TraitDataTable](trait-datatable.md)** ⏳ - Traits especiais (Darkvision, Fey Ancestry, etc.)
> - **[LanguageDataTable](language-datatable.md)** ⏳ - Idiomas D&D 5e

</details>

### ⚔️ Magia e Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Magia e Combate</b></summary>

> - **[SpellDataTable](spell-datatable.md)** ⏳ - Spells D&D 5e
> - **[SpellSchoolDataTable](spellschool-datatable.md)** ⏳ - Escolas de magia
> - **[DamageTypeDataTable](damagetype-datatable.md)** ⏳ - Tipos de dano
> - **[ConditionDataTable](condition-datatable.md)** ⏳ - Condições (Poisoned, Stunned, etc.)
> - **[ItemDataTable](item-datatable.md)** ⏳ - Itens (armas, armaduras, consumíveis)

</details>

---

## 📊 Status de Documentação

| Data Table | Status | Documentação |
|------------|--------|--------------|
| RaceDataTable | ✅ Completo | [race-datatable.md](race-datatable.md) |
| ClassDataTable | ✅ Completo | [class-datatable.md](class-datatable.md) |
| BackgroundDataTable | ⏳ Pendente | - |
| FeatDataTable | ⏳ Pendente | - |
| FeatureDataTable | ⏳ Pendente | - |
| ProficiencyDataTable | ⏳ Pendente | - |
| SkillDataTable | ⏳ Pendente | - |
| AbilityScoreDataTable | ⏳ Pendente | - |
| TraitDataTable | ⏳ Pendente | - |
| LanguageDataTable | ⏳ Pendente | - |
| SpellDataTable | ⏳ Pendente | - |
| SpellSchoolDataTable | ⏳ Pendente | - |
| DamageTypeDataTable | ⏳ Pendente | - |
| ConditionDataTable | ⏳ Pendente | - |
| ItemDataTable | ⏳ Pendente | - |

**Progresso:** 2/15 (13%) ✅

---

## 🔗 Referências Rápidas

### Estrutura Comum

Todas as Data Tables seguem padrão comum:

- ✅ Campos de versionamento (`SchemaVersion`, `DataVersion`)
- ✅ Campos obrigatórios (`Name`, `ID`)
- ✅ Gameplay Tags (`TypeTags`)
- ✅ Referências type-safe (`FDataTableRowHandle`)

### Guias Relacionados

- **[JSON Schema Validation Guide](../guides/json-schema-validation-guide.md)** - Como validar schemas
- **[Schema Versioning Guide](../guides/schema-versioning-guide.md)** - Versionamento de schemas
- **[Data Architecture](../data-architecture/index.md)** - Arquitetura de dados do projeto

---

**Última atualização:** 2024-12-27
