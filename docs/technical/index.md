---
title: "Technical Documentation"
category: technical
tags: [technical, architecture, api, guides]
last_updated: 2024-12-27
---

# Documentação Técnica

!!! abstract "Visão Geral"
    Esta seção contém toda a documentação relacionada à **arquitetura técnica, implementação e desenvolvimento** do projeto MyProject2.

    Explore os documentos abaixo para entender a arquitetura, API, estrutura de dados e guias práticos de desenvolvimento.

---

## Documentos Principais

!!! tip "Explore a Documentação"
    Selecione uma categoria abaixo para começar:

=== "🏗️ Arquitetura"

    **Documentação completa da arquitetura do projeto**

    [:octicons-arrow-right-24: Ver arquitetura completa](architecture.md)

    - Princípios de Design (Data-Driven, Modularidade, Editor-Friendly, Multiplayer-Ready)
    - Data-Oriented Design e ECS
    - Arquitetura em 4 Camadas
    - Motores Desacoplados
    - Preparação para GAS

=== "📖 API Reference"

    **Referência completa de todas as classes e funções**

    [:octicons-arrow-right-24: Ver API completa](api.md)

    - CharacterDataComponent
    - CharacterSheetComponent
    - CharacterSheetDataAsset
    - CreateSheet - Motores
    - Helpers e Utilitários

=== "📊 Arquitetura de Dados"

    **Organização de dados, DOD, ECS e estruturas ideais**

    [:octicons-arrow-right-24: Ver arquitetura de dados](data-architecture/)

    - Relatório de Arquiteturas de Alta Performance
    - Estrutura de Dados Ideal (Padrão AAA)
    - Filosofia: Composição sobre Herança
    - Normalização e Tabelas de Referência

=== "📋 Guias Práticos"

    **Guias passo a passo para setup, uso e desenvolvimento**

    [:octicons-arrow-right-24: Ver todos os guias](guides/)

    - Setup e Configuração
    - Getting Started
    - Workflows
    - Testes e TDD
    - Troubleshooting

---

## Arquitetura Técnica

!!! note "Arquitetura Completa"
    **[architecture.md](architecture.md)** - Documentação completa da arquitetura:

    - **Princípios de Design**: Data-Driven, Modularidade, Editor-Friendly, Multiplayer-Ready
    - **Data-Oriented Design e ECS**: Composição sobre Herança, Separação Static/Dynamic
    - **Arquitetura em 4 Camadas**: Data Assets → Bridge Components → Runtime Components → Feature Components
    - **Motores Desacoplados**: CreateSheet/ com motores independentes
    - **Preparação para GAS**: Migração futura para Gameplay Ability System
    - **Regras de Implementação**: Padrões e convenções
    - **Estrutura de Arquivos**: Organização do código

---

## API Reference

!!! info "Referência de API"
    **[api.md](api.md)** - Referência completa da API:

    - **CharacterDataComponent**: Componente de dados replicáveis
    - **CharacterSheetComponent**: Componente bridge de aplicação de regras
    - **CharacterSheetDataAsset**: Data Asset de configuração
    - **CreateSheet - Motores**: PointBuy, Multiclass, RaceBonus
    - **Helpers e Utilitários**: Funções reutilizáveis

---

## Arquitetura de Dados

!!! tip "Organização de Dados"
    **[data-architecture/](data-architecture/)** - Documentação sobre organização de dados:

    - **Relatório de Arquiteturas de Alta Performance**: DOD, ECS, Baldur's Gate 3
    - **Estrutura de Dados Ideal**: Padrão "ID + Tags + Payload" para projetos AAA
    - **Filosofia**: Composição sobre Herança, Separação Static/Dynamic
    - **Estrutura "Flat"**: JSONs planos e relacionais
    - **Normalização**: Tabelas de referência e relacionamentos
    - **Serialização**: Serialização diferencial, formatos binários

    [:octicons-arrow-right-24: Ver arquitetura de dados completa](data-architecture/index.md)

---

## Guias Práticos

!!! success "Guias Passo a Passo"
    **[guides/](guides/)** - Guias organizados por categoria:

    **Setup e Configuração:**
    - [:material-tools: Setup Completo](guides/setup.md) - Configurar ambiente do zero
    - [:material-table: Data Tables Setup](guides/data-tables-setup.md) - Criar e configurar Data Tables

    **Uso:**
    - [:material-rocket-launch: Getting Started](guides/getting-started.md) - Criar primeiro personagem
    - [:material-workflow: Workflows](guides/workflows.md) - Fluxos principais do sistema
    - [:material-database: Data Tables](guides/data-tables.md) - Estrutura e uso

    **Técnico:**
    - [:material-test-tube: Testes Automatizados](guides/testing.md) - Implementação e execução
    - [:material-code-tags: TDD Complete Guide](guides/tdd-complete-guide.md) - Test-Driven Development
    - [:material-bug: Troubleshooting](guides/troubleshooting.md) - Problemas comuns

    [:octicons-arrow-right-24: Ver todos os guias](guides/index.md)

---

## Navegação Rápida

!!! question "Links Úteis"
    **Documentação Principal:**

    - [:material-home: Home](../../README.md) - Visão geral do projeto
    - [:material-book: Documentação](../index.md) - Índice completo
    - [:material-file-document: ARCHITECTURE.md](../../ARCHITECTURE.md) - Resumo da arquitetura

    **Outras Seções:**

    - [:material-palette: Design](../design/) - Regras D&D 5e e GDD
    - [:material-calendar: Planejamento](../planning/) - Roadmap e planos

    **Recursos:**

    - [:material-book-open-page-variant: Glossário](../GLOSSARY.md) - Conceitos e termos
    - [:material-map: Mapa de Navegação](../NAVIGATION.md) - Navegação completa
