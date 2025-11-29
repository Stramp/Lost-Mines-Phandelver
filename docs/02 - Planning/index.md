---
title: "Planning Documentation"
category: planning
tags: [planning, roadmap, phases, development]
last_updated: 2024-12-27
---

# Planejamento do Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Esta seção contém toda a documentação relacionada ao **planejamento e roadmap** do projeto:
>

> - Roadmap completo e detalhado
>
> - Fases de desenvolvimento com prazos
>
> - Status de cada item
>
> - Decisões de arquitetura que impactam o planejamento
>
> - Histórico de mudanças no plano
>
</details>
---

## Estrutura de Documentos

A documentação de planejamento está organizada nas seguintes categorias:

### 📊 Roadmaps (`roadmaps/`)
- `roadmap.md` - Roadmap principal consolidado
- `roadmap-estrutura.md` - Roadmap de estrutura
- `roadmap-funcional.md` - Roadmap funcional
- `roadmap-tecnico.md` - Roadmap técnico
- `roadmap-tecnico-inventario-boilerplate.md` - Inventário de boilerplate
- `roadmap-tecnico-itens-iniciais.md` - Itens técnicos iniciais

### 🏗️ Arquitetura (`architecture/`)
- `arquitetura-decisoes-criticas.md` - Decisões arquiteturais críticas (DEC-001, DEC-002, etc.)
- `revisao-estrutural-integracao.md` - Revisão estrutural e integração

### ✅ Validação (`validation/`)
- `data-tables-validation.md` - Validação de data tables

### 📋 Metodologia (`methodology/`)
- `agile-methodology.md` - Metodologia ágil do projeto

### 📝 Backlog (`backlog/`)
- `backlog.md` - Backlog do projeto

### 📅 Sprints (`sprints/`)
- `sprints.md` - Visão geral das sprints
- `sprint-1/` - Sprint 1 e seus documentos (DATA-000, DATA-001, etc.)
- `sprint-2/`, `sprint-3/`, `sprint-4/` - Sprints futuras

### 📜 Changelog (`changelog/`)
- `CHANGELOG.md` - Histórico de mudanças no planejamento

## Documentos Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Roadmap e Planejamento</b></summary>

> ### Roadmap do Projeto
>
> [**roadmap.md**](roadmaps/roadmap.md) - Roadmap principal (visão estratégica)
>
> **Roadmaps Específicos:**
>
> - [**data-tables-validation.md**](validation/data-tables-validation.md) - 🔴 **PRIORIDADE CRÍTICA** - Checklist de validação de cada tabela (Fase 0)
> - [**roadmap-tecnico.md**](roadmaps/roadmap-tecnico.md) - Bugs, correções e melhorias técnicas
> - [**roadmap-funcional.md**](roadmaps/roadmap-funcional.md) - Features por categoria (Step 3-6)
> - [**roadmap-estrutura.md**](roadmaps/roadmap-estrutura.md) - Estrutura hierárquica de roadmaps
>
> ### Metodologia Ágil
>
> [**agile-methodology.md**](methodology/agile-methodology.md) - Guia de uso de metodologias ágeis (Scrum/Kanban)
>
> [**backlog.md**](backlog/backlog.md) - Lista priorizada de trabalho (MoSCoW)
>
> [**sprints.md**](sprints.md) - Planejamento de sprints e iterações

</details>

    | Fase | Status | Descrição |
    |------|--------|-----------|
    | **Fase 1** | ✅ Completo | Sistema de Fichas Básico |
    | **Fase 1.5** | 🔄 Em Progresso | Melhorias e Completude D&D 5e |
    | **Fase 2** | 🔮 Planejado | Sistema de Itens e Inventário |
    | **Fase 3** | 🔮 Planejado | Sistema de Combate |
    | **Fase 4** | 🔮 Planejado | Sistema de Magias |
    | **Fase 5** | 🔮 Planejado | Migração para GAS |

    **Características:**

    - Todas as fases de desenvolvimento

    - Prazos estimados

    - Dependências entre fases

    - Status detalhado de cada item

    - Decisões técnicas que impactam o planejamento

    - Histórico de mudanças

    [Ver roadmap completo](roadmaps/roadmap.md)


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Revisão Estrutural</b></summary>


</details>
    ### Análise e Melhorias

    [**revisao-estrutural-integracao.md**](architecture/revisao-estrutural-integracao.md) - Revisão estrutural completa

    | Aspecto | Status |
    |---------|--------|
    | **Comparação com planos5.md** | ✅ Completo |
    | **Análise de regras D&D 5e** | ✅ Completo |
    | **Identificação de melhorias** | ✅ Completo |
    | **Integração no roadmap** | ✅ Completo (Fase 1.5 criada) |
    | **Status de sistemas** | ✅ Documentado |

    [Ver revisão estrutural](architecture/revisao-estrutural-integracao.md)


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Planos Técnicos</b></summary>


</details>
    ### Implementação Detalhada

    [**roadmap-tecnico-itens-iniciais.md**](roadmaps/roadmap-tecnico-itens-iniciais.md) - Plano técnico para itens iniciais

    | Etapa | Descrição |
    |-------|-----------|
    | **Análise** | Regras D&D 5e para itens iniciais |
    | **Arquitetura** | Padrões do projeto (Data-Driven, Component-Based) |
    | **Implementação** | Fase por fase com detalhes |
    | **Design** | Decisões de design documentadas |
    | **Testes** | Estratégia de testes completa |
    | **Estimativa** | Tempo estimado por fase |

    [Ver plano técnico](roadmaps/roadmap-tecnico-itens-iniciais.md)

---

## Fases do Roadmap

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Fase 1: Sistema de Fichas Básico - Completo</b></summary>

> **Status:** ✅ **100% Completo**
>

> **Componentes Implementados:**
>
> - ✅ Sistema de criação de personagem
>
> - ✅ Point Buy System
>
> - ✅ Multiclassing
>
> - ✅ Raças e bônus
>
> - ✅ Validação completa
>
> - ✅ Data Tables configuradas
>
> **Documentação:**
>
> - [Arquitetura Técnica](../technical/architecture.md)
>
> - [API Reference](../technical/api.md)
>
> - [Guias Práticos](../technical/guides/)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Fase 1.5: Melhorias e Completude D&D 5e - Em Progresso</b></summary>

> **Status:** 🔄 **60% Completo**
>

> **Melhorias em Andamento:**
>
> - 🔄 Sistema de Level Up completo
>
> - 🔄 Features de classe por nível
>
> - 🔄 ASI (Ability Score Improvement)
>
> - 🔄 Feats opcionais
>
> - ✅ Testes automatizados (275+ testes)
>
> - ✅ Documentação completa
>
> **Próximos Passos:**
>
> - Implementar Level Up completo
>
> - Adicionar mais features de classe
>
> - Sistema de Feats
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Fase 2: Sistema de Itens e Inventário - Planejado</b></summary>

> **Status:** 🔮 **Planejado**
>

> **Componentes Planejados:**
>
> - Sistema de itens iniciais (equipamento)
>
> - Inventário básico
>
> - Gerenciamento de equipamento
>
> - Peso e capacidade
>
> **Documentação:**
>
> - [Plano Técnico: Itens Iniciais](roadmap-tecnico-itens-iniciais.md)
>
> - [Plano Técnico: Inventário](roadmap-tecnico-inventario-boilerplate.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Fase 3: Sistema de Combate - Planejado</b></summary>

> **Status:** 🔮 **Planejado**
>

> **Componentes Planejados:**
>
> - Sistema de turnos
>
> - Ataques e dano
>
> - Condições (buffs/debuffs)
>
> - HP e morte
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Fase 4: Sistema de Magias - Planejado</b></summary>

> **Status:** 🔮 **Planejado**
>

> **Componentes Planejados:**
>
> - Spellcasting completo
>
> - Slots de magia
>
> - Preparação de magias
>
> - Efeitos de magias
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Fase 5: Migração para GAS - Planejado</b></summary>

> **Status:** 🔮 **Planejado**
>

> **Componentes Planejados:**
>
> - Migração de dados para GAS Attributes
>
> - Migração de lógica para GAS Abilities
>
> - Sistema de Effects completo
>
> - Preparação para multiplayer
>
> **Documentação:**
>
> - [Adaptação D&D 5e + GAS](../design/gas-dnd-adaptation.md)
>
</details>
---

## 🚀 Início Rápido

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Guia de Navegação</b></summary>

> **[README.md](README.md)** - Guia completo de navegação pela pasta planning
>
> **Navegação rápida:**
>
> - 🗺️ **Visão Geral:** [roadmap.md](roadmaps/roadmap.md)
> - 📋 **O Que Fazer Agora:** [backlog.md](backlog/backlog.md) → [sprints.md](sprints.md)
> - 🔧 **Detalhes Técnicos:** [roadmap-tecnico.md](roadmaps/roadmap-tecnico.md)
> - ⚙️ **Detalhes Funcionais:** [roadmap-funcional.md](roadmaps/roadmap-funcional.md)
> - 📚 **Metodologia Ágil:** [agile-methodology.md](methodology/agile-methodology.md)
> - 📝 **Histórico:** [CHANGELOG.md](changelog/CHANGELOG.md)

</details>

---

## Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> **Documentação Principal:**
>

> - [Roadmap Completo](roadmaps/roadmap.md) - Planejamento detalhado (com Fase 1.5 integrada)
>
> - [Revisão Estrutural](architecture/revisao-estrutural-integracao.md) - Análise completa e melhorias identificadas
>
> - [Plano Técnico: Itens Iniciais](roadmaps/roadmap-tecnico-itens-iniciais.md) - Implementação detalhada
>
> - [Plano Técnico: Boilerplate de Inventário](roadmaps/roadmap-tecnico-inventario-boilerplate.md) - Estruturas modulares
>
> **Outras Seções:**
>
> - [GDD](../design/gdd.md) - Visão do jogo final
>
> - [Arquitetura Técnica](../technical/architecture.md) - Decisões técnicas
>
> - [Regras D&D 5e](../design/dnd-rules/) - Regras implementadas
>
> **Recursos:**
>
> - [README Principal](../../README.md) - Visão geral do projeto
>
> - [ARCHITECTURE.md](../../ARCHITECTURE.md) - Resumo da arquitetura
>
> - [Índice de Documentação](../index.md) - Organização completa
>
</details>
---

**Última atualização:** 2024-12-27
