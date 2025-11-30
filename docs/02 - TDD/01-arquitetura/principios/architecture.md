# Arquitetura do Projeto - MyProject2

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v3.0 | 2024-12-27 | Refatorado: convertido em overview, removido conteúdo duplicado e GDD |
| v2.0 | 2024-12-27 | Refatoração: removido frontmatter, atualizado para estrutura numerada |
| v1.0 | 2024-12-27 | Versão inicial |

---

## Visão Geral

Este documento fornece uma **visão geral** da arquitetura técnica do projeto, baseada em princípios de design que garantem código limpo, manutenível, escalável e preparado para multiplayer.

**📖 Para documentação detalhada, consulte as seções específicas abaixo.**

---

## 📋 Navegação da Documentação de Arquitetura

### 1. [Princípios de Design](../principios/index.md)

Os 5 princípios fundamentais que guiam a arquitetura:

- **[Data-Driven](../principios/data-driven.md)** - Implementação técnica de Data-Driven
- **[Modularidade](../principios/modularidade.md)** - Implementação técnica de Modularidade
- **[Editor-Friendly](../principios/editor-friendly.md)** - Implementação técnica de Editor-Friendly
- **[Multiplayer-Ready](../principios/multiplayer-ready.md)** - Implementação técnica de Multiplayer
- **[Separation of Concerns](../principios/separation-of-concerns.md)** - Implementação técnica de Separação de Responsabilidades

### 2. [Arquitetura em Camadas](../camadas/index.md)

Arquitetura em 4 camadas distintas:

- **[Camada 1: Data Assets](../camadas/layer-1-data-assets.md)** - Editor/Configuração
- **[Camada 2: Bridge Components](../camadas/layer-2-bridge-components.md)** - Aplicação de Regras
- **[Camada 3: Runtime Data Components](../camadas/layer-3-runtime-data.md)** - Dados Replicáveis
- **[Camada 4: Feature Components](../camadas/layer-4-feature-components.md)** - Lógica Específica

### 3. [Fluxo de Dados](../fluxo-dados.md)

Diagrama de fluxo de dados entre Editor, Servidor e Cliente.

### 4. [Arquitetura CreateSheet/](../createsheet.md)

Motores desacoplados para criação de personagem:

- **FCharacterSheetCore** - Orquestrador
- **FRaceBonusMotor** - Motor de Bônus Raciais
- **FPointBuyMotor** - Motor de Point Buy
- **FMulticlassMotor** - Motor de Multiclassing
- **FCharacterSheetData** - Estrutura Genérica

**📖 Para mais detalhes, veja [Arquitetura CreateSheet/](../createsheet.md)**

### 5. Data-Oriented Design e ECS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Princípios de Performance e Arquitetura</b></summary>

> O projeto segue princípios de **Data-Oriented Design (DOD)** e está preparado para evoluir para um padrão **Entity Component System (ECS)** quando necessário.
>
> **Filosofia Técnica:**
>
> - **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
> - **Separação Static/Dynamic**: Definições em Data Tables (o que o item "é"), estado em componentes runtime (o que o item "tem" agora)
> - **Padrão "ID + Tags + Payload"**: Identificador único + metadados + dados específicos
> - **Estrutura "Flat"**: JSONs planos e relacionais, não profundamente aninhados
>
> **Aplicação Técnica no Projeto:**
>
> - Data Tables contêm apenas definições estáticas (raça, classe, traits)
> - Componentes runtime contêm estado dinâmico (HP atual, buffs ativos, escolhas do jogador)
> - Referências por ID, nunca por string/Name
> - Estruturas JSON planas e relacionais
>
> **📖 Para detalhes completos sobre DOD, ECS e arquiteturas de alta performance, veja:**
>
> - [Relatório de Arquiteturas de Alta Performance](../../03-dados/arquitetura/relatorios/high-performance-architectures-report.md)
> - [Relatório de Estrutura de Dados Ideal](../../03-dados/arquitetura/relatorios/ideal-data-structure-report.md)
> - [Arquitetura de Carregamento Centralizado (Data Registry)](../../03-dados/arquitetura/implementacao/data-registry-architecture.md) - Carregamento único e acesso O(1)

</details>

### 6. [Preparação para GAS](../sistemas/gas-dnd-adaptation/index.md)

Arquitetura GAS - Preparação e Padrões:

- **[Visão Geral](../sistemas/gas-dnd-adaptation/index.md)** - Overview da preparação
- **[Localização do ASC](../sistemas/gas-dnd-adaptation/asc-location.md)** - Onde criar o ASC
- **[AttributeSet](../sistemas/gas-dnd-adaptation/attribute-set.md)** - Atributos em C++
- **[Gameplay Abilities](../sistemas/gas-dnd-adaptation/gameplay-abilities.md)** - Habilidades em Blueprint
- **[UI Reativa](../sistemas/gas-dnd-adaptation/ui-reativa.md)** - Event-Driven UI
- **[Gerenciamento de Habilidades](../sistemas/gas-dnd-adaptation/gerenciamento-habilidades.md)** - Handles
- **[Data Assets Concedendo Habilidades](../sistemas/gas-dnd-adaptation/data-assets-habilidades.md)** - Data-Driven
- **[Replication Modes](../sistemas/gas-dnd-adaptation/multiplayer.md)** - Multiplayer
- **[Migração do Projeto](../sistemas/gas-dnd-adaptation/migracao-projeto.md)** - Plano de migração
- **[Checklist de Implementação](../sistemas/gas-dnd-adaptation/checklist-implementacao.md)** - Checklist

### 7. [Regras de Implementação](../regras-implementacao.md)

Guia de regras e padrões técnicos para implementação.

### 8. [Checklist de Arquitetura](../checklist.md)

Checklist antes de criar novo código.

### 9. [Estrutura de Arquivos Recomendada](../estrutura-arquivos.md)

Organização de diretórios e arquivos, incluindo organização modular do CharacterSheetDataAsset.

### 10. [Sistema de Logging](../logging.md)

Sistema centralizado de logging com suporte a popups no editor e throttle.

### 11. [Referências](../referencias.md)

Documentação do projeto e links externos.

---

## 📚 Referências de Design (GDD)

Para entender **O QUÊ** e **PORQUÊ** (design), consulte:

- **[Pilares de Design](../../../01 - GDD/01-visao-geral/pilares-design.md)** - Porquê usar Data-Driven, Modularidade, etc.
- **[Sistemas de Personagem](../../../01 - GDD/02-mecanicas/sistemas-personagem.md)** - Design de sistemas de personagem
- **[Estrutura do Projeto](../../../01 - GDD/01-visao-geral/estrutura-projeto.md)** - Visão geral do projeto

**💡 Lembre-se:** Este documento (TDD) explica **COMO** implementar tecnicamente. O GDD explica **O QUÊ** e **PORQUÊ**.

---

**Navegação:** [← Voltar para Arquitetura](../index.md)

**Última atualização:** 2024-12-27
