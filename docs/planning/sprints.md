---
title: "Sprints - Planejamento de Iterações"
category: planning
tags: [sprints, agile, scrum, iterations]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Sprints

# Sprints - Planejamento de Iterações

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este documento contém o **planejamento de sprints** para desenvolvimento incremental do projeto.
>
> **Duração do Sprint:** 1 semana (recomendado para features pequenas/médias)
>
> **Objetivo:** Entregar valor incremental a cada sprint, permitindo feedback contínuo e ajustes.
>
> **Estrutura:**
>
> - **Sprint Planning** - Selecionar tarefas do backlog
> - **Desenvolvimento** - Implementar tarefas
> - **Sprint Review** - Revisar entregas
> - **Sprint Retrospective** - Melhorias contínuas

</details>

---

## 📅 Sprint Atual

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Sprint 1 - Estrutura de Dados Base (Checkmate Inicial)</b></summary>

> **Duração:** 2 semanas (2024-12-27 a 2025-01-10)
>
> **Sprint Goal:** Estabelecer estrutura de dados runtime sólida e alinhada com `planos5.md` (Data-Oriented Design + ECS) para suportar todas as funcionalidades futuras.
>
> **Valor de Negócio:** Criar base arquitetural sólida que evita refatorações massivas futuras. "Checkmate" na estrutura inicial de dados.
>
> **Contexto:** Projeto considerado "novo" - focar em estrutura base antes de funcionalidades complexas.

### 📋 Tarefas do Sprint

<details open>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 DATA-001: Criar Estruturas de Dados Runtime Base</summary>

> **User Story:** Como desenvolvedor, eu quero estruturas de dados leves e bem definidas para runtime (inventário, equipamento, magias, condições) para suportar todas as funcionalidades futuras sem refatorações massivas.
>
> **Prioridade:** 🔴 Must Have
>
> **Estimativa:** 8 horas
>
> **Status:** 📋 Planejado
>
> **Tarefas Puras:**
>
> 1. **DATA-001-01:** Criar `FInventoryItem` struct (ItemID + Quantity) em `Data/Structures/FInventoryItem.h` - **1 hora** 🧪 TDD
> 2. **DATA-001-02:** Criar `FEquipmentSlot` struct (ItemID + SlotType) em `Data/Structures/FEquipmentSlot.h` - **1 hora** 🧪 TDD
> 3. **DATA-001-03:** Criar `FSpellSlot` struct (Level + Used/Available) em `Data/Structures/FSpellSlot.h` - **1 hora** 🧪 TDD
> 4. **DATA-001-04:** Criar `FSpellKnown` struct (SpellID + Prepared) em `Data/Structures/FSpellKnown.h` - **1 hora** 🧪 TDD
> 5. **DATA-001-05:** Criar `FConditionInstance` struct (ConditionID + Duration + Source) em `Data/Structures/FConditionInstance.h` - **1 hora** 🧪 TDD
> 6. **DATA-001-06:** Criar `FActiveEffect` struct (EffectID + Duration + Source) em `Data/Structures/FActiveEffect.h` - **1 hora** 🧪 TDD
> 7. **DATA-001-07:** Criar testes TDD para todas as structs (validação de serialização, SaveGame) - **2 horas** 🧪 TDD
>
> **Critérios de Aceite:**
>
> - ✅ Todas as structs criadas com `UPROPERTY(SaveGame)`
> - ✅ Structs seguem padrão "ID + Payload" (apenas IDs, não dados completos)
> - ✅ Testes TDD passam para todas as structs
> - ✅ Documentação inline completa
> - ✅ Alinhado com `planos5.md` (serialização diferencial)
>
> **📖 Referência:** [ANALISE_ESTRUTURA_DADOS.md](../../technical/reviews/ANALISE_ESTRUTURA_DADOS.md)

</details>

<details open>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 DATA-002: Criar Componentes Layer 4 Base</summary>

> **User Story:** Como desenvolvedor, eu quero componentes separados para inventário, equipamento, magias e condições para seguir princípios ECS e Single Responsibility.
>
> **Prioridade:** 🔴 Must Have
>
> **Estimativa:** 12 horas
>
> **Status:** 📋 Planejado
>
> **Tarefas Puras:**
>
> 1. **DATA-002-01:** Criar `UInventoryComponent` com `TArray<FInventoryItem>` - **3 horas** 🧪 TDD
> 2. **DATA-002-02:** Criar `UEquipmentComponent` com slots (armor, main hand, off hand, shield) - **3 horas** 🧪 TDD
> 3. **DATA-002-03:** Criar `USpellcastingComponent` com `TArray<FSpellSlot>` e `TArray<FSpellKnown>` - **3 horas** 🧪 TDD
> 4. **DATA-002-04:** Criar `UConditionComponent` com `TArray<FConditionInstance>` - **3 horas** 🧪 TDD
>
> **Critérios de Aceite:**
>
> - ✅ Todos os componentes herdam de `UActorComponent`
> - ✅ Propriedades replicáveis com `DOREPLIFETIME`
> - ✅ Testes TDD passam para cada componente
> - ✅ Componentes seguem Clean Code e Design Patterns
> - ✅ Documentação inline completa
>
> **📖 Referência:** [ANALISE_ESTRUTURA_DADOS.md](../../technical/reviews/ANALISE_ESTRUTURA_DADOS.md)

</details>

<details open>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 DATA-003: Adicionar Campos Calculados em CharacterDataComponent</summary>

> **User Story:** Como desenvolvedor, eu quero campos calculados (AC, Saving Throws, Skill Modifiers, Initiative, Speed, HP) em CharacterDataComponent para ter dados essenciais disponíveis em runtime.
>
> **Prioridade:** 🔴 Must Have
>
> **Estimativa:** 10 horas
>
> **Status:** 📋 Planejado
>
> **Tarefas Puras:**
>
> 1. **DATA-003-01:** Adicionar `AC` (Armor Class) calculado em `CharacterDataComponent.h` - **1.5 horas** 🧪 TDD
> 2. **DATA-003-02:** Adicionar `SavingThrows` calculados (TMap<FName, int32>) - **1.5 horas** 🧪 TDD
> 3. **DATA-003-03:** Adicionar `SkillModifiers` calculados (TMap<FName, int32>) - **1.5 horas** 🧪 TDD
> 4. **DATA-003-04:** Adicionar `Initiative` calculado - **1 hora** 🧪 TDD
> 5. **DATA-003-05:** Adicionar `Speed` atual (modificável por condições) - **1 hora** 🧪 TDD
> 6. **DATA-003-06:** Adicionar `InitialHP` e `MaxHP` calculados (Step 6) - **2 horas** 🧪 TDD
> 7. **DATA-003-07:** Criar updaters para todos os campos calculados - **1.5 horas**
>
> **Critérios de Aceite:**
>
> - ✅ Todos os campos adicionados com `UPROPERTY(Replicated)`
> - ✅ Funções de cálculo implementadas com testes TDD
> - ✅ Updaters criados e integrados
> - ✅ Testes E2E passam validando campos calculados
> - ✅ Suporta multiclasse (cálculos corretos)
>
> **📖 Referência:** [ANALISE_ESTRUTURA_DADOS.md](../../technical/reviews/ANALISE_ESTRUTURA_DADOS.md)

</details>

### 📊 Métricas do Sprint

> **Total Estimado:** 30 horas (2 semanas)
>
> **Progresso:**
>
> - **Tarefas Completadas:** 0/3 (0%)
> - **Horas Trabalhadas:** 0h / 30h (0%)
> - **Horas Restantes:** 30h
>
> **Velocity Esperada:** 30 horas (primeiro sprint - baseline para estrutura base)

### ✅ Definition of Done do Sprint

> - ✅ Todas as estruturas de dados runtime criadas (FInventoryItem, FEquipmentSlot, etc.)
> - ✅ Todos os componentes Layer 4 criados (UInventoryComponent, UEquipmentComponent, etc.)
> - ✅ Todos os campos calculados adicionados em CharacterDataComponent (AC, Saving Throws, etc.)
> - ✅ HP Inicial e MaxHP implementados (Step 6)
> - ✅ Testes TDD escritos e passando para todas as estruturas e componentes
> - ✅ Teste E2E passa validando estrutura completa
> - ✅ Código segue Clean Code e Design Patterns
> - ✅ Código revisado e sem warnings
> - ✅ Documentação inline completa
> - ✅ Alinhado com `planos5.md` (Data-Oriented Design + ECS)

### ⚠️ Riscos e Impedimentos

> **Riscos Identificados:**
>
> - ⚠️ **Médio:** Complexidade de integração entre componentes (mitigado com testes TDD)
> - ⚠️ **Médio:** Cálculos de AC/Saving Throws podem ter dependências não mapeadas (mitigado com análise prévia)
> - ⚠️ **Baixo:** Estrutura de dados pode precisar ajustes após testes (aceitável - é baseline)
>
> **Impedimentos:**
>
> - Nenhum no momento
>
> **Mitigações:**
>
> - Testes TDD garantem comportamento esperado
> - Análise prévia em `ANALISE_ESTRUTURA_DADOS.md`
> - Revisão de código após cada componente

### 📝 Notas do Daily Scrum

> **2024-12-27 (Início do Sprint):**
>
> - Sprint iniciado
> - Tarefas selecionadas do backlog
> - Objetivo do sprint definido
>
> **Atualizar diariamente conforme trabalho progride...**

### 🎯 Status do Sprint

> **Status:** 📋 Planejado
>
> **Última Atualização:** 2024-12-27

</details>

---

## 📋 Próximos Sprints

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Sprint 2 - Starting Equipment</b></summary>

> **Duração:** 1 semana (2025-01-03 a 2025-01-10)
>
> **Objetivo:** Implementar sistema de equipamentos iniciais (classe e background) para completar Step 5.
>
> **Tarefas Planejadas:**
>
> 1. **FUNC-007:** Starting Equipment da Classe (6.5 horas) - 🔴 M
> 2. **FUNC-008:** Starting Equipment do Background (2.75 horas) - 🔴 M
>
> **Total Estimado:** 9.25 horas
>
> **Dependências:**
>
> - ✅ Sprint 1 completo
> - 📋 ItemDataTable básico criado
>
> **Status:** 📋 Planejado

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Sprint 3 - Validações e Testes</b></summary>

> **Duração:** 1 semana (2025-01-10 a 2025-01-17)
>
> **Objetivo:** Validar sistemas críticos com testes end-to-end completos.
>
> **Tarefas Planejadas:**
>
> 1. **TEC-003:** Validação Completa do Sistema de Multiclasse (4.5 horas) - 🟡 S
> 2. **TEC-004:** Validar Criação de Feat no Editor (3 horas) - 🟡 S
>
> **Total Estimado:** 7.5 horas
>
> **Dependências:**
>
> - ✅ Sprint 2 completo
>
> **Status:** 📋 Planejado

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Sprint 4 - Métodos Alternativos de Ability Scores</b></summary>

> **Duração:** 2 semanas (2025-01-17 a 2025-01-31)
>
> **Objetivo:** Implementar Standard Array e Roll 4d6 como alternativas ao Point Buy.
>
> **Tarefas Planejadas:**
>
> 1. **FUNC-001:** Standard Array (7.5 horas) - 🟡 S
> 2. **FUNC-002:** Roll 4d6 Drop Lowest (9.75 horas) - 🟡 S
>
> **Total Estimado:** 17.25 horas
>
> **Dependências:**
>
> - ✅ Sprint 3 completo
>
> **Status:** 📋 Planejado

</details>

---

## 📊 Velocity Tracking

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Histórico de Velocity</b></summary>

> **Velocity (Horas por Sprint):**
>
> | Sprint | Duração | Horas Estimadas | Horas Reais | Tarefas Completadas | Status | Observações |
> |--------|---------|-----------------|-------------|---------------------|--------|-------------|
> | Sprint 1 | 2 semanas | 30h | - | 0/3 | 📋 Planejado | Baseline - Estrutura Base |
> | Sprint 2 | 1 semana | 9.25h | - | - | 📋 Planejado | - |
> | Sprint 3 | 1 semana | 7.5h | - | - | 📋 Planejado | - |
> | Sprint 4 | 2 semanas | 17.25h | - | - | 📋 Planejado | - |
>
> **Média de Velocity:** Será calculada após completar 3+ sprints
>
> **Análise:**
>
> - **Sprint 1:** Baseline inicial - ajustar estimativas futuras baseado em resultados
> - **Próximos Sprints:** Velocity será calculada após Sprint 1 para melhorar estimativas
>
> **Nota:** Velocity será atualizada após cada sprint para melhorar estimativas futuras e planejamento.

</details>

---

## 🎯 Burndown Chart

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📉 Sprint 1 - Burndown</b></summary>

> **Horas Iniciais:** 30 horas
>
> **Progresso Diário:**
>
> | Data | Horas Trabalhadas | Horas Restantes | Tarefas Completadas | Observações |
> |------|------------------|-----------------|---------------------|------------|
> | 2024-12-27 | 0h | 30h | 0/3 | Sprint iniciado - Estrutura Base |
> | 2024-12-28 | - | - | - | Atualizar diariamente |
> | 2024-12-29 | - | - | - | Atualizar diariamente |
> | 2024-12-30 | - | - | - | Atualizar diariamente |
> | 2024-12-31 | - | - | - | Atualizar diariamente |
> | 2025-01-01 | - | - | - | Atualizar diariamente |
> | 2025-01-02 | - | - | - | Atualizar diariamente |
> | 2025-01-03 | - | - | - | Atualizar diariamente |
> | 2025-01-04 | - | - | - | Atualizar diariamente |
> | 2025-01-05 | - | - | - | Atualizar diariamente |
> | 2025-01-06 | - | - | - | Atualizar diariamente |
> | 2025-01-07 | - | - | - | Atualizar diariamente |
> | 2025-01-08 | - | - | - | Atualizar diariamente |
> | 2025-01-09 | - | - | - | Atualizar diariamente |
> | 2025-01-10 | - | - | - | Sprint Review |
>
> **Gráfico Visual (Atualizar diariamente):**
>
> ```text
> Horas Restantes
> 30.0 |●
> 25.0 | ●
> 20.0 |  ●
> 15.0 |   ●
> 10.0 |    ●
>  5.0 |     ●
>  0.0 |_______●
>       Seg Ter Qua Qui Sex Sáb Dom Seg Ter Qua Qui Sex Sáb Dom
> ```
>
> **Atualização:** Atualizar diariamente conforme trabalho progride.

</details>

---

## 🔄 Cerimônias Ágeis

### 📅 Sprint Planning

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Planejamento do Sprint</b></summary>

> **Quando:** Início de cada sprint
>
> **Duração:** 1-2 horas (para sprint de 1 semana)
>
> **Objetivo:** Selecionar tarefas do backlog para o sprint e definir Sprint Goal
>
> **Processo:**
>
> 1. Revisar backlog priorizado ([backlog.md](backlog.md))
> 2. Selecionar tarefas Must Have primeiro
> 3. Adicionar Should Have se houver capacidade
> 4. Validar dependências
> 5. Estimar esforço total
> 6. Confirmar que está dentro da capacidade (velocity)
> 7. Definir Sprint Goal claro e mensurável
>
> **Resultado:** Backlog da Sprint definido e compreendido por todos

</details>

### 📅 Sprint Review (Sprint 1)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Revisão do Sprint 1</b></summary>

> **Quando:** 2025-01-10 (final do Sprint 1)
>
> **Duração:** 1 hora
>
> **Objetivo:** Revisar entregas e validar Definition of Done
>
> **Checklist de Revisão:**
>
> - [ ] Todas as tarefas completadas revisadas
> - [ ] Definition of Done validada para cada tarefa
> - [ ] Funcionalidades demonstradas (se aplicável)
> - [ ] Velocity atualizada com horas reais
> - [ ] Tarefas completadas movidas para "Done"
> - [ ] Feedback coletado
> - [ ] Backlog atualizado com base no feedback
>
> **Resultado do Sprint 1:**
>
> - **Tarefas Completadas:** -/2 (preencher após review)
> - **Horas Reais:** -h (preencher após review)
> - **Velocity:** -h (preencher após review)
> - **Sprint Goal Atingido:** ✅/❌ (preencher após review)
>
> **Observações:** (preencher após review)

</details>

### 📅 Sprint Retrospective (Sprint 1)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Retrospectiva do Sprint 1</b></summary>

> **Quando:** 2025-01-10 (após Sprint Review)
>
> **Duração:** 1 hora
>
> **Objetivo:** Identificar melhorias contínuas
>
> **Perguntas para Reflexão:**
>
> 1. **O que funcionou bem?**
>    - (preencher após retrospectiva)
>
> 2. **O que pode ser melhorado?**
>    - (preencher após retrospectiva)
>
> 3. **Ações concretas para próximo sprint:**
>    - (preencher após retrospectiva)
>
> **Melhorias Identificadas:**
>
> - (preencher após retrospectiva)
>
> **Ações para Sprint 2:**
>
> - (preencher após retrospectiva)
>
> **Resultado:** Processos e documentação atualizados

</details>

---

## 🔗 Links Relacionados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Referências</b></summary>

> - **[Backlog](backlog.md)** - Lista priorizada de trabalho
> >
> > - **[Metodologia Ágil](agile-methodology.md)** - Guia de uso de metodologias ágeis
> > - **[Roadmap Técnico](roadmap-tecnico.md)** - Detalhes técnicos das tarefas
> > - **[Roadmap Funcional](roadmap-funcional.md)** - Detalhes funcionais das tarefas

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
