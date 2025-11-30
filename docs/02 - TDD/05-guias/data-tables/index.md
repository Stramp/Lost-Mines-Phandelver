# Data Tables - Índice

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Os Data Tables armazenam dados estruturados de D&D 5e (raças, classes, backgrounds, feats) em formato JSON, permitindo que designers modifiquem regras sem alterar código.
>
> **Filosofia de Estrutura:**
>
> - **Estrutura "Flat" (Plana)**: JSONs relacionais e planos, não profundamente aninhados
> - **Padrão "ID + Tags + Payload"**: Cada entrada tem um ID único, tags para categorização, e payload com dados específicos
> - **Separação Static/Dynamic**: Data Tables contêm apenas definições estáticas (o que o item "é"), não estado dinâmico (o que o item "tem" agora)
> - **Composição sobre Herança**: Use referências por ID ao invés de estruturas aninhadas complexas

</details>

---

## 📖 Documentação

- **[Visão Geral](visao-geral.md)** - Introdução e filosofia de estrutura
- **[Estrutura de Relacionamento](estrutura-relacionamento.md)** - Diagrama de relacionamento entre Data Tables
- **[Estrutura Comum](estrutura-comum.md)** - Padrões e estruturas compartilhadas

### 👤 Personagem

- **[RaceDataTable](personagem/race-datatable.md)** - Estrutura de raças
- **[ClassDataTable](personagem/class-datatable.md)** - Estrutura de classes
- **[BackgroundDataTable](personagem/background-datatable.md)** - Estrutura de backgrounds

### 🛠️ Suporte

- **[FeatDataTable](suporte/feat-datatable.md)** - Estrutura de feats
- **[FeatureDataTable](suporte/feature-datatable.md)** - Estrutura de features
- **[ProficiencyDataTable](suporte/proficiency-datatable.md)** - Estrutura de proficiências
- **[SkillDataTable](suporte/skill-datatable.md)** - Estrutura de skills
- **[LanguageDataTable](suporte/language-datatable.md)** - Estrutura de idiomas
- **[AbilityScoreDataTable](suporte/ability-score-datatable.md)** - Estrutura de atributos
- **[TraitDataTable](suporte/trait-datatable.md)** - Estrutura de traits
- **[ItemDataTable](suporte/item-datatable.md)** - Estrutura de itens

### ⚔️ Combate

- **[SpellDataTable](combate/spell-datatable.md)** - Estrutura de magias
- **[SpellSchoolDataTable](combate/spell-school-datatable.md)** - Estrutura de escolas de magia
- **[DamageTypeDataTable](combate/damage-type-datatable.md)** - Estrutura de tipos de dano
- **[ConditionDataTable](combate/condition-datatable.md)** - Estrutura de condições

### 🔧 Integração e Referência

- **[Integração com Sistema](integracao/integracao-sistema.md)** - Como criar/editar Data Tables no editor e validações aplicadas
- **[Exemplos de JSON](exemplos/exemplos-json.md)** - Exemplos completos de JSON válido
- **[Boas Práticas](boas-praticas.md)** - Recomendações e melhores práticas
- **[Troubleshooting](troubleshooting.md)** - Problemas comuns e soluções

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v2.0 | 2024-12-27 | Índice atualizado após subdivisão de data-tables.md |
| v1.0 | 2024-12-27 | Índice criado após divisão de data-tables.md |

**Navegação:** [← Voltar para Guias](../index.md) | [→ Visão Geral](visao-geral.md)

**Última atualização:** 2024-12-27
