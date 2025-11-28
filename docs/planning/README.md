---
title: "Guia de Navegação - Planning"
category: planning
tags: [planning, guide, navigation]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Guia de Navegação

# Guia de Navegação - Planning

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este guia ajuda a **navegar** pela pasta `planning/` e entender **onde encontrar** informações específicas.
>
> **Estrutura da Pasta:**
>
> - **Roadmaps** - Visão estratégica e detalhada
> - **Metodologia Ágil** - Guias e processos ágeis
> - **Backlog e Sprints** - Planejamento de trabalho
> - **Planos Técnicos** - Implementações detalhadas

</details>

---

## 🗺️ Por Onde Começar?

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Dependendo do Seu Objetivo</b></summary>

> **Quero ver o panorama geral do projeto:**
>
> → **[roadmap.md](roadmap.md)** - Visão estratégica, fases principais, status geral
>
> **Quero ver o que preciso fazer agora:**
>
> → **[backlog.md](backlog.md)** - Lista priorizada (Must/Should/Could)
> → **[sprints.md](sprints.md)** - Sprint atual e próximos
>
> **Quero entender metodologias ágeis:**
>
> → **[agile-methodology.md](agile-methodology.md)** - Guia completo de Scrum/Kanban
>
> **Quero ver detalhes técnicos de uma tarefa:**
>
> → **[roadmap-tecnico.md](roadmap-tecnico.md)** - Bugs, correções, melhorias técnicas
>
> **Quero ver detalhes funcionais de uma feature:**
>
> → **[roadmap-funcional.md](roadmap-funcional.md)** - Features por categoria (Step 3-6)
>
> **Quero entender a estrutura hierárquica:**
>
> → **[roadmap-estrutura.md](roadmap-estrutura.md)** - Documentação da hierarquia

</details>

---

## 📐 Hierarquia de Documentos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Fluxo de Navegação</b></summary>

> **Nível 1: Visão Estratégica**
>
> - `roadmap.md` - Epics (Fases), status geral
>
> **Nível 2: Planejamento Ágil**
>
> - `backlog.md` - User Stories priorizadas (MoSCoW)
> - `sprints.md` - Planejamento de iterações
>
> **Nível 3: Detalhes Técnicos/Funcionais**
>
> - `roadmap-tecnico.md` - User Stories técnicas com Tasks
> - `roadmap-funcional.md` - User Stories funcionais com Tasks
>
> **Nível 4: Tarefas Puras**
>
> - Dentro dos roadmaps específicos
> - Cada tarefa tem: estimativa, prioridade, DoD, dependências
>
> **Fluxo Recomendado:**
>
> ```
> roadmap.md (Epic)
>   ↓
> backlog.md (User Story priorizada)
>   ↓
> sprints.md (Sprint atual)
>   ↓
> roadmap-tecnico.md ou roadmap-funcional.md (Tasks)
>   ↓
> Implementar
> ```

</details>

---

## 📚 Documentos por Categoria

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Categorias</b></summary>

> **Roadmaps:**
>
> - `roadmap.md` - Principal
> - `roadmap-tecnico.md` - Técnico
> - `roadmap-funcional.md` - Funcional
> - `roadmap-estrutura.md` - Estrutura hierárquica
>
> **Metodologia Ágil:**
>
> - `agile-methodology.md` - Guia completo
> - `backlog.md` - Backlog priorizado
> - `sprints.md` - Planejamento de sprints
>
> **Planos Técnicos:**
>
> - `roadmap-tecnico-itens-iniciais.md` - Itens iniciais
> - `roadmap-tecnico-inventario-boilerplate.md` - Inventário
>
> **Outros:**
>
> - `index.md` - Índice principal
> - `revisao-estrutural-integracao.md` - Revisão estrutural

</details>

---

## ✅ Checklist de Uso

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Como Usar</b></summary>

> **Para Planejar um Sprint:**
>
> 1. [ ] Revisar `backlog.md` (prioridades MoSCoW)
> 2. [ ] Selecionar tarefas Must Have primeiro
> 3. [ ] Verificar dependências em `roadmap-tecnico.md` ou `roadmap-funcional.md`
> 4. [ ] Adicionar ao `sprints.md`
> 5. [ ] Validar estimativas com velocity anterior
>
> **Para Implementar uma Tarefa:**
>
> 1. [ ] Ler User Story completa no roadmap específico
> 2. [ ] Verificar Definition of Done
> 3. [ ] Revisar dependências
> 4. [ ] Seguir TDD quando aplicável
> 5. [ ] Validar que DoD foi atendido
> 6. [ ] Atualizar status no backlog
>
> **Para Atualizar o Backlog:**
>
> 1. [ ] Mover tarefas completadas para "Done"
> 2. [ ] Reavaliar prioridades MoSCoW
> 3. [ ] Adicionar novas tarefas identificadas
> 4. [ ] Atualizar estimativas baseadas em velocity

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
