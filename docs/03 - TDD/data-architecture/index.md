---
title: "Data Architecture"
category: technical
subcategory: data-architecture
tags: [data-architecture, database, normalization, data-oriented-design]
last_updated: 2024-12-27
difficulty: advanced
related: [../architecture.md, database-architecture.md]
---

# Arquitetura de Dados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Esta seção contém documentação sobre **arquitetura de dados, organização de tabelas, banco de dados e estruturas de dados** para projetos de alta complexidade e escala.
>

> Explore os documentos abaixo para entender como os dados são organizados, normalizados e otimizados no projeto MyProject2.
>
> **📖 Documentação Relacionada:**
>
> - **[Regras D&D 5e](../../03 - TDD/dnd-rules/index.md)** - Regras implementadas no sistema
>
> - **[GAS + D&D Adaptation](../../design/gas-dnd-adaptation.md)** - Como D&D 5e é adaptado para GAS
>
> - **[Arquitetura Técnica](../architecture.md)** - Arquitetura completa do projeto
>
</details>
---

## Documentos Principais


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔬 Relatórios de Pesquisa</b></summary>

> **[high-performance-architectures-report.md](high-performance-architectures-report.md)** - Relatório completo sobre arquiteturas de alta performance:
>
> - Data-Oriented Design (DOD) vs OOP
>
> - Entity Component Systems (ECS)
>
> - Arquitetura de dados em Baldur's Gate 3 (Larian Studios)
>
> - Persistência e serialização de estado complexo
>
> - Arquiteturas de dados em escala planetária (Facebook TAO, Twitter/X)
>
> - Engenharia de banco de dados para atributos dinâmicos
>
> - Infraestrutura física e otimização de hardware
>
> - Governança, analytics e evolução de schema
>
> [Ver relatório completo](high-performance-architectures-report.md)
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Estrutura de Dados Ideal</b></summary>

> **[ideal-data-structure-report.md](ideal-data-structure-report.md)** - Relatório completo sobre estrutura de dados ideal:
>
> - Análise completa dos JSONs existentes
>
> - Problemas críticos identificados
>
> - Estrutura ideal baseada em ECS + Data-Oriented Design
>
> - Tabelas de referência (Master Data)
>
> - Tabelas principais com IDs únicos
>
> - Padrão de nomenclatura de IDs
>
> - Checklist de migração completo
>
> - Comparação antes vs depois
>
> - Benefícios e prioridades de implementação
>
> [Ver relatório completo](ideal-data-structure-report.md)
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗄️ Arquitetura de Banco de Dados</b></summary>

> **[database-architecture.md](database-architecture.md)** - Documentação completa da arquitetura de banco de dados implementada:
>
> - Padrão "ID + Tags + Payload"
>
> - FDataTableRowHandle: Referências type-safe
>
> - Gameplay Tags: Categorização flexível
>
> - Soft References: Lazy loading
>
> - Estrutura de Data Tables (Master Data e Principais)
>
> - Scripts de migração
>
> - Helpers e utilitários
>
> - Checklist de implementação
>
> [Ver arquitetura completa](database-architecture.md)
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Carregamento Centralizado (Data Registry)</b></summary>

> **[data-registry-architecture.md](data-registry-architecture.md)** - Arquitetura de alto desempenho para carregamento centralizado:
>
> - UDataRegistrySubsystem: Solução nativa da Epic Games
>
> - Carregamento único na inicialização (Preload/CacheAll)
>
> - Acesso O(1) via Hash Maps (FindRow)
>
> - Dados estáticos vs dinâmicos (Padrão Flyweight)
>
> - Thread safety e imutabilidade
>
> - Gerenciamento de memória (Hard vs Soft References)
>
> - Integração futura com MassEntity (ECS)
>
> - Comparativo: Lyra vs Data Registry
>
> - Guia completo de implementação C++
>
> [Ver arquitetura completa](data-registry-architecture.md)
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Revisão Estrutural</b></summary>

> **[structural-review-report.md](../reviews/structural-review-report.md)** - Relatório completo de revisão estrutural:
>
> - Análise da estrutura atual (JSON, Data Tables, Documentação)
>
> - Problemas identificados (críticos, médios, baixos)
>
> - Sugestões de melhorias baseadas em referências AAA
>
> - Referências e justificativas (JSON Best Practices, DOD, ECS, BG3)
>
> - Plano de implementação priorizado (3 fases)
>
> - Comparação com padrões da indústria
>
> [Ver revisão estrutural](../reviews/structural-review-report.md)
>

</details>
---

## Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> **Documentação Principal:**
>

> - [Relatório de Arquiteturas de Alta Performance](high-performance-architectures-report.md) - Pesquisa completa sobre sistemas de dados complexos
>
> - [Estrutura de Dados Ideal](ideal-data-structure-report.md) - Análise e recomendações para o projeto
>
> - [Revisão Estrutural Completa](../reviews/structural-review-report.md) - Análise e melhorias sugeridas
>
> - [Arquitetura de Banco de Dados](database-architecture.md) - Padrão "ID + Tags + Payload"
>
> - [Carregamento Centralizado (Data Registry)](data-registry-architecture.md) - Arquitetura de alto desempenho
>
> - [JSON Schema](json-schema.md) - Validação e versionamento
>
> **Outras Seções:**
>
> - [Arquitetura Técnica](../architecture.md) - Arquitetura completa do projeto
>
> - [API Reference](../api.md) - Referência de classes
>
> - [Guias Práticos](../guides/) - Guias passo a passo
>
</details>
---

**Última atualização:** 2024-12-27
