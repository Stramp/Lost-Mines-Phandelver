# Documentação Técnica (TDD)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v2.0 | 2024-12-27 | Refatoração completa: estrutura numerada, organização profunda |
| v1.0 | 2024-12-27 | Versão inicial |

---

# Documentação Técnica

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Esta seção contém toda a documentação relacionada à **arquitetura técnica, implementação e desenvolvimento** do projeto MyProject2.
>

> Explore os documentos abaixo organizados por categoria para entender a arquitetura, API, estrutura de dados e guias práticos.
>
</details>
---

## 📋 Seções Principais

- **[1. Arquitetura](01-arquitetura/index.md)** - Princípios e camadas arquiteturais
- **[2. API Reference](02-api/index.md)** - Classes, funções e componentes
- **[3. Dados](03-dados/index.md)** - Arquitetura de dados e Data Tables
- **[4. Regras D&D Algorítmicas](04-regras-dnd/index.md)** - Algoritmos técnicos D&D 5e
- **[5. Guias Práticos](05-guias/index.md)** - Guias passo a passo
- **[8. Pseudocódigo Técnico](08-pseudocodigo/index.md)** - Especificações de implementação

---

## Navegação Rápida

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Arquitetura</b></summary>

> **[1. Arquitetura Técnica](01-arquitetura/index.md)** - Documentação completa da arquitetura do projeto

    | Característica | Descrição |
    |----------------|-----------|
    | **Princípios** | Data-Driven, Modularidade, Editor-Friendly, Multiplayer-Ready |
    | **Design** | Data-Oriented Design e ECS (Composição sobre Herança) |
    | **Camadas** | Arquitetura em 4 Camadas (Data Assets → Bridge → Runtime → Features) |
    | **Motores** | Motores Desacoplados em `CreateSheet/` |
    | **GAS** | Preparação para migração futura ao Gameplay Ability System |

    [Ver arquitetura completa](01-arquitetura/principios/architecture.md)


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 API Reference</b></summary>

> **[2. Referência de API](02-api/index.md)** - Referência completa de todas as classes e funções

    | Componente | Descrição |
    |------------|-----------|
    | `CharacterDataComponent` | Componente de dados replicáveis em runtime |
    | `CharacterSheetComponent` | Componente bridge que aplica regras |
    | `CharacterSheetDataAsset` | Data Asset de configuração no editor |
    | `CreateSheet/` | Motores de criação (PointBuy, Multiclass, RaceBonus) |
    | `Helpers/` | Funções utilitárias reutilizáveis |

    [Ver API completa](02-api/componentes/api.md)


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Arquitetura de Dados</b></summary>

> **[3. Arquitetura de Dados](03-dados/index.md)** - Documentação sobre organização de dados

    | Documento | Descrição |
    |-----------|-----------|
    | **High Performance** | Relatório sobre DOD, ECS, Baldur's Gate 3 |
    | **Estrutura Ideal** | Padrão "ID + Tags + Payload" para projetos AAA |
    | **Database** | Arquitetura de banco de dados implementada |
    | **JSON Schema** | Validação e versionamento de schemas |

    [Ver arquitetura de dados](03-dados/arquitetura/implementacao/index.md)


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Regras D&D Algorítmicas</b></summary>

> **[4. Regras D&D Algorítmicas](04-regras-dnd/index.md)** - Algoritmos técnicos de implementação

    | Categoria | Algoritmos Disponíveis |
    |------------|----------------------|
    | **Criação** | Character Creation, Point Buy, Multiclass |
    | **Combate** | AC Calculation, Damage Calculation, Attack Roll |
    | **Progressão** | Level Up, Spellcasting |
    | **Sistemas** | Rest, Conditions |

    [Ver todos os algoritmos](04-regras-dnd/index.md)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Guias Práticos</b></summary>

> **[5. Guias Práticos](05-guias/index.md)** - Guias organizados por categoria

    | Categoria | Guias Disponíveis |
    |------------|-------------------|
    | **Setup** | Setup Completo, Data Tables Setup |
    | **Uso** | Getting Started, Workflows, Data Tables |
    | **Técnico** | Testes, TDD, Troubleshooting |

    [Ver todos os guias](05-guias/index.md)

---

## Documentos Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 architecture.md - Arquitetura completa do projeto</b></summary>

> **Princípios de Design:**
>

> - **Data-Driven**: Todas as regras vêm de Data Tables/Assets
>
> - **Modularidade**: Código organizado por domínio
>
> - **Editor-Friendly**: Funciona perfeitamente no editor
>
> - **Multiplayer-Ready**: Preparado para multiplayer desde o início
>
> **Arquitetura em 4 Camadas:**
>
> 1. **Data Assets** (Editor) - Configuração estática
>
> 2. **Bridge Components** (Server) - Aplicação de regras
>
> 3. **Runtime Components** (Replicável) - Dados em runtime
>
> 4. **Feature Components** (Específicos) - Features de classe
>
> **Motores Desacoplados:**
>
> - `PointBuyMotor` - Sistema de alocação de pontos
>
> - `MulticlassMotor` - Sistema de multiclassing
>
> - `RaceBonusMotor` - Aplicação de bônus de raça
>
> [Ver arquitetura completa](01-arquitetura/principios/architecture.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔌 api.md - Referência completa da API</b></summary>

> **Componentes Principais:**
>

> | Classe | Herda de | Responsabilidade |
> |--------|----------|------------------|
> | `UCharacterDataComponent` | `UActorComponent` | Dados replicáveis em runtime |
> | `UCharacterSheetComponent` | `UActorComponent` | Bridge de aplicação de regras |
> | `UCharacterSheetDataAsset` | `UDataAsset` | Configuração no editor |
>
> **Motores (CreateSheet/):**
>
> - `FPointBuyMotor` - Validação e cálculo de Point Buy
>
> - `FMulticlassMotor` - Validação e aplicação de multiclassing
>
> - `FRaceBonusMotor` - Aplicação de bônus de raça
>
> **Helpers e Utilitários:**
>
> - `ComponentHelpers` - Funções para buscar componentes
>
> - `CalculationHelpers` - Cálculos de modificadores e bônus
>
> - `ValidationHelpers` - Validações reutilizáveis
>
> [Ver API completa](02-api/componentes/api.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗄️ data-architecture/ - Organização de dados e estruturas</b></summary>

> **Documentos Disponíveis:**
>

> | Documento | Conteúdo |
> |-----------|----------|
> | **high-performance-architectures-report.md** | Pesquisa sobre DOD, ECS, Baldur's Gate 3 |
> | **ideal-data-structure-report.md** | Estrutura ideal baseada em padrões AAA |
> | **database-architecture.md** | Arquitetura implementada (ID + Tags + Payload) |
> | **json-schema.md** | Validação e versionamento de schemas |
>
> **Filosofia:**
>
> - **Composição sobre Herança**: Estruturas planas e relacionais
>
> - **Separação Static/Dynamic**: Dados estáticos separados de runtime
>
> - **Normalização**: Tabelas de referência e relacionamentos
>
> - **Performance**: Estruturas otimizadas para cache
>
> [Ver arquitetura de dados](03-dados/arquitetura/implementacao/index.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 guides/ - Guias passo a passo organizados por categoria</b></summary>

> **Setup e Configuração:**
>

> - [Setup Completo](guides/setup.md) - Configurar ambiente do zero
>
> - [Data Tables Setup](guides/data-tables-setup.md) - Criar e configurar Data Tables
>
> **Uso do Sistema:**
>
> - [Getting Started](guides/getting-started.md) - Criar primeiro personagem
>
> - [Workflows](guides/workflows.md) - Fluxos principais do sistema
>
> - [Data Tables](guides/data-tables.md) - Estrutura e uso dos Data Tables
>
> **Desenvolvimento Técnico:**
>
> - [Testes Automatizados](guides/testing.md) - Implementação e execução
>
> - [TDD Complete Guide](guides/tdd-complete-guide.md) - Test-Driven Development
>
> - [Troubleshooting](guides/troubleshooting.md) - Problemas comuns e soluções
>
> [Ver todos os guias](guides/index.md)
>
</details>
---

## Estrutura do Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📁 Organização de Arquivos</b></summary>

> ```
> Source/MyProject2/
> ├── Characters/          # Personagens e raças
> ├── Components/          # Componentes reutilizáveis
> │   ├── Data/           # Componentes de dados
> │   ├── Features/        # Componentes de features
> │   └── UI/             # Componentes de UI
> ├── Data/               # Data Assets e Data Tables
> ├── Gameplay/           # Mecânicas de gameplay
> │   └── CreateSheet/    # Motores de criação
> │       ├── PointBuy/   # Motor de Point Buy
> │       ├── Multiclass/ # Motor de Multiclassing
> │       └── RaceBonus/  # Motor de Bônus de Raça
> └── Utils/              # Utilitários e helpers
> ```
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Padrões de Código</b></summary>

> | Padrão | Aplicação |
> |--------|-----------|
> | **Data-Driven** | Todas as regras em Data Tables/Assets |
> | **Component-Based** | Separação de responsabilidades em componentes |
> | **Motor Pattern** | Lógica de negócio em motores desacoplados |
> | **Helper Pattern** | Funções reutilizáveis em `Utils/` ou `Helpers/` |
> | **Clean Code** | Funções pequenas, testáveis, DRY |
>

</details>

## Links Úteis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Navegação</b></summary>

> **Documentação Principal:**
>

> - [Home](../../README.md) - Visão geral do projeto
>
> - [Documentação](../index.md) - Índice completo
>
> - [ARCHITECTURE.md](../../ARCHITECTURE.md) - Resumo da arquitetura
>
> **Outras Seções:**
>
> - [Design](../design/) - Regras D&D 5e e GDD
>
> - [Planejamento](../planning/) - Roadmap e planos
>
> **Recursos:**
>
> - [Glossário](../GLOSSARY.md) - Conceitos e termos
>
> - [Mapa de Navegação](../NAVIGATION.md) - Navegação completa
>
</details>
---

**Última atualização:** 2024-12-27
