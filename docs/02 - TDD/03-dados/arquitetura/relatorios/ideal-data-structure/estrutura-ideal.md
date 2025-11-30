# Estrutura Ideal (Projeto Zerado)

## Arquitetura Baseada em ECS + Data-Oriented Design

**Princípios Fundamentais:**

1. **Data-Oriented Design (DOD)**: Organizar dados por layout de memória, não por hierarquia de classes
2. **Entity Component System (ECS)**: Desacoplar identidade de dados e comportamento
3. **Separação Static/Dynamic**: Definições em Data Tables, estado em componentes runtime
4. **Composição sobre Herança**: Usar composição de componentes ao invés de árvores de herança

**Para mais detalhes sobre DOD e ECS, veja [high-performance-architectures-report.md](../high-performance-architectures-report.md)**

---

## 📋 Estrutura de Tabelas

### Tabelas de Referência (Master Data) - Prioridade 1

- **[AbilityScoreDataTable](tabelas-referencia/ability-score-datatable.md)** - 6 atributos
- **[TraitDataTable](tabelas-referencia/trait-datatable.md)** - Traits reutilizáveis
- **[LanguageDataTable](tabelas-referencia/language-datatable.md)** - Idiomas
- **[SkillDataTable](tabelas-referencia/skill-datatable.md)** - 18 skills
- **[SpellDataTable](tabelas-referencia/spell-datatable.md)** - Todas as magias D&D 5e
- **[SpellSchoolDataTable](tabelas-referencia/spell-school-datatable.md)** - 8 escolas
- **[DamageTypeDataTable](tabelas-referencia/damage-type-datatable.md)** - 10 tipos de dano
- **[ConditionDataTable](tabelas-referencia/condition-datatable.md)** - 14 condições

### Tabelas Principais - Prioridade 2

- **[RaceDataTable](tabelas-principais/race-datatable.md)** - Raças e sub-raças
- **[ClassDataTable](tabelas-principais/class-datatable.md)** - Classes e progressão
- **[BackgroundDataTable](tabelas-principais/background-datatable.md)** - Backgrounds
- **[FeatDataTable](tabelas-principais/feat-datatable.md)** - Feats
- **[FeatureDataTable](tabelas-principais/feature-datatable.md)** - Features
- **[ProficiencyDataTable](tabelas-principais/proficiency-datatable.md)** - Proficiências
- **[ItemDataTable](tabelas-principais/item-datatable.md)** - Itens

---

## 🔗 Navegação

- [📚 Relatório - Índice](./index.md)
- [📊 Tabelas de Referência](tabelas-referencia/index.md)
- [📊 Tabelas Principais](tabelas-principais/index.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
