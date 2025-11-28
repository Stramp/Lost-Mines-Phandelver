---
title: "Data Architecture"
category: technical
subcategory: data-architecture
tags: [data-architecture, database, normalization, data-oriented-design]
last_updated: 2024-12-27
difficulty: advanced
related: [../architecture.md, database-architecture.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > Data Architecture

# Data Architecture - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Esta seção contém documentação sobre **arquitetura de dados, organização de tabelas, banco de dados e estruturas de dados** para projetos de alta complexidade e escala.

</details>

---

## 📚 Documentos Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔬 Relatórios de Pesquisa</b></summary>

> **[high-performance-architectures-report.md](high-performance-architectures-report.md)** - Relatório completo sobre arquiteturas de alta performance:
>
> - Data-Oriented Design (DOD) vs OOP
> - Entity Component Systems (ECS)
> - Arquitetura de dados em Baldur's Gate 3 (Larian Studios)
> - Persistência e serialização de estado complexo
> - Arquiteturas de dados em escala planetária (Facebook TAO, Twitter/X)
> - Engenharia de banco de dados para atributos dinâmicos
> - Infraestrutura física e otimização de hardware
> - Governança, analytics e evolução de schema

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Estrutura de Dados Ideal</b></summary>

> **[ideal-data-structure-report.md](ideal-data-structure-report.md)** - Relatório completo sobre estrutura de dados ideal:
>
> - Análise completa dos JSONs existentes
> - Problemas críticos identificados
> - Estrutura ideal baseada em ECS + Data-Oriented Design
> - Tabelas de referência (Master Data)
> - Tabelas principais com IDs únicos
> - Padrão de nomenclatura de IDs
> - Checklist de migração completo
> - Comparação antes vs depois
> - Benefícios e prioridades de implementação

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗄️ Arquitetura de Banco de Dados</b></summary>

> **[database-architecture.md](database-architecture.md)** - Documentação completa da arquitetura de banco de dados implementada:
>
> - Padrão "ID + Tags + Payload"
> - FDataTableRowHandle: Referências type-safe
> - Gameplay Tags: Categorização flexível
> - Soft References: Lazy loading
> - Estrutura de Data Tables (Master Data e Principais)
> - Scripts de migração
> - Helpers e utilitários
> - Checklist de implementação

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Revisão Estrutural</b></summary>

> **[structural-review-report.md](../reviews/structural-review-report.md)** - Relatório completo de revisão estrutural:
>
> - Análise da estrutura atual (JSON, Data Tables, Documentação)
> - Problemas identificados (críticos, médios, baixos)
> - Sugestões de melhorias baseadas em referências AAA
> - Referências e justificativas (JSON Best Practices, DOD, ECS, BG3)
> - Plano de implementação priorizado (3 fases)
> - Comparação com padrões da indústria

</details>

---

## 🎯 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Rápidos</b></summary>

> - **[Relatório de Arquiteturas de Alta Performance](high-performance-architectures-report.md)** - Pesquisa completa sobre sistemas de dados complexos
> - **[Estrutura de Dados Ideal](ideal-data-structure-report.md)** - Análise e recomendações para o projeto
> - **[Revisão Estrutural Completa](../reviews/structural-review-report.md)** - Análise e melhorias sugeridas
> - **[Arquitetura Técnica](../architecture.md)** - Arquitetura completa do projeto
> - **[API Reference](../api.md)** - Referência de classes
> - **[Guias Práticos](../guides/)** - Guias passo a passo
> - **[Índice de Documentação Técnica](../index.md)** - Organização completa

</details>

---

## 📖 Resumo dos Conceitos Principais

### 🎯 Filosofia Fundamental: Composição sobre Herança

Para estruturas de dados perfeitas em Unreal Engine 5, siga:

- **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
- **Separação Static/Dynamic**: Definições em Data Tables (o que o item "é"), estado em componentes runtime (o que o item "tem" agora)
- **Padrão "Name + ID + Tags + Payload"**: Nome de exibição (Key Field) + Identificador único + metadados + dados específicos
- **Estrutura "Flat"**: JSONs planos e relacionais, não profundamente aninhados
- **Referências Type-Safe**: Uso de `FDataTableRowHandle` para referências entre tabelas

### Data-Oriented Design (DOD)

Organização de dados focada no layout físico na memória, priorizando cache hits e performance sobre modelagem orientada a objetos.

**Princípios:**
- **Array of Structures (AoS)** → **Structure of Arrays (SoA)**: Cada campo em seu próprio array contíguo
- **Cache-Friendly**: Dados organizados para maximizar cache hits da CPU
- **SIMD-Friendly**: Estrutura que permite processamento paralelo com instruções SIMD

### Entity Component System (ECS)

Padrão arquitetural que desacopla identidade (Entity), dados (Component) e lógica (System), permitindo composição dinâmica e escalabilidade.

**Estratégias de Armazenamento:**
- **Arquétipos (Archetypes)**: Agrupa entidades com mesma combinação de componentes - ideal para dados estáticos
- **Sparse Sets**: Arrays esparsos para flexibilidade dinâmica - ideal para estados efêmeros (buffs/debuffs)

### Normalização de Dados

Eliminação de redundância através de tabelas de referência (Master Data) e uso consistente de IDs únicos para todas as entidades.

### Serialização Binária

Uso de formatos binários (FlatBuffers, Protobuf) ao invés de JSON para persistência, reduzindo I/O e tamanho de arquivos.

**Serialização Diferencial**: Salvar apenas o "delta" (mudanças) em relação ao estado base, não o estado completo.

### Estrutura de Dados Ideal - ✅ IMPLEMENTADO

- **Tabelas de Referência (Master Data):** ✅ 9 tabelas implementadas (Traits, Languages, Skills, Spells, SpellSchools, DamageTypes, Conditions, Proficiencies, AbilityScores)
- **Tabelas Principais:** ✅ 6 tabelas implementadas (Races, Classes, Backgrounds, Feats, Features, Items)
- **Padrão Name + ID:** ✅ `Name` como Key Field (obrigatório pelo Unreal Engine), `ID` como identificador único interno
- **Referências Type-Safe:** ✅ Uso de `FDataTableRowHandle` para referências entre tabelas (nunca por string/Name)
- **Gameplay Tags:** ✅ Categorização flexível via `TypeTags` (FGameplayTagContainer) em todas as tabelas
- **Estrutura "Flat"**: ✅ JSONs relacionais planos, não aninhados profundamente

---

## 🎓 Aplicação no Projeto

Os relatórios desta seção fornecem a base teórica e prática para:

1. **Organização de Data Tables** - Estrutura normalizada e escalável
2. **Performance** - Otimizações baseadas em Data-Oriented Design
3. **Escalabilidade** - Preparação para projetos AAA (estilo Baldur's Gate 3)
4. **Manutenção** - Estrutura que facilita evolução e mudanças
5. **Integridade** - Validação automática de referências

---

---

## ✅ Status Atual da Implementação

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Estrutura Completa Implementada</b></summary>

> **Todas as 15 Data Tables seguem o padrão Name + ID + Tags + Payload:**
>
> ### ✅ Tabelas de Referência (Master Data) - 9 Tabelas
>
> 1. `AbilityScoreDataTable` - 6 atributos
> 2. `TraitDataTable` - Traits reutilizáveis
> 3. `LanguageDataTable` - Idiomas
> 4. `SkillDataTable` - Skills
> 5. `SpellDataTable` - Magias
> 6. `SpellSchoolDataTable` - Escolas de magia
> 7. `DamageTypeDataTable` - Tipos de dano
> 8. `ConditionDataTable` - Condições
> 9. `ProficiencyDataTable` - Proficiências
>
> ### ✅ Tabelas Principais - 6 Tabelas
>
> 1. `RaceDataTable` - Raças e sub-raças
> 2. `ClassDataTable` - Classes e progressão
> 3. `BackgroundDataTable` - Backgrounds
> 4. `FeatDataTable` - Feats
> 5. `FeatureDataTable` - Features de classe
> 6. `ItemDataTable` - Itens
>
> **Características Implementadas:**
>
> - ✅ Padrão **Name + ID** (Name como Key Field, ID como identificador único)
> - ✅ **FDataTableRowHandle** para referências type-safe entre tabelas
> - ✅ **Gameplay Tags** (`TypeTags`) para categorização flexível
> - ✅ **TSoftObjectPtr** para lazy loading de assets
> - ✅ **Normalização completa** (sem duplicação de dados)
> - ✅ **Estrutura "Flat"** (JSONs relacionais planos)
>
> **Documentação Completa:**
>
> - 📖 [Arquitetura de Banco de Dados](./database-architecture.md) - Implementação atual
> - 📖 [Estrutura de Dados Ideal](./ideal-data-structure-report.md) - Análise e recomendações
> - 📖 [Arquiteturas de Alta Performance](./high-performance-architectures-report.md) - Pesquisa e estudos
> - 📖 [Revisão Estrutural Completa](../reviews/structural-review-report.md) - Análise e melhorias sugeridas
> - 📖 [Revisão de Melhorias](data-architecture-review-improvements.md) - Melhorias identificadas e aplicadas
> - 📖 [Melhorias Aplicadas - planos5.md](planos5-improvements-summary.md) - Alinhamento com princípios
> - 📖 [Resumo da Revisão](REVIEW_SUMMARY.md) - Resumo executivo das melhorias

</details>

---

**Última atualização:** 2024-12-27 - Revisão completa aplicada, melhorias críticas corrigidas
