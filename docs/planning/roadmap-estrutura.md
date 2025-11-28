---
title: "Estrutura Hierárquica de Roadmaps"
category: planning
tags: [roadmap, structure, organization]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Estrutura de Roadmaps

# Estrutura Hierárquica de Roadmaps

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral da Estrutura</b></summary>

> Esta estrutura organiza o roadmap em **níveis hierárquicos** que vão desde a visão estratégica até tarefas puras e acionáveis.
>
> **Níveis:**
>
> 1. **Roadmap Principal** - Visão estratégica e fases principais
> 2. **Roadmaps Específicos** - Por categoria (Técnico, Funcional, etc.)
> 3. **Tarefas Puras** - Ações concretas e acionáveis
>
> **Benefícios:**
>
> - ✅ Caminho claro e navegável
> - ✅ Tarefas acionáveis em cada nível
> - ✅ Priorização clara
> - ✅ Estimativas realistas
> - ✅ Dependências explícitas

</details>

---

## 📐 Hierarquia de Roadmaps

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Nível 1: Roadmap Principal</b></summary>

> **Arquivo:** [roadmap.md](roadmap.md)
>
> **Objetivo:** Visão estratégica do projeto, fases principais e marcos importantes.
>
> **Conteúdo:**
>
> - Visão geral do projeto
> - Fases principais (1, 1.5, 2, 3, etc.)
> - Status geral de cada fase
> - Dependências entre fases
> - Marcos e entregas principais
> - Links para roadmaps específicos
>
> **Público:** Todos os stakeholders, visão de alto nível

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Nível 2: Roadmaps Específicos</b></summary>

> **Roadmaps por Categoria:**
>
> 1. **[roadmap-tecnico.md](roadmap-tecnico.md)** - Tarefas técnicas (bugs, correções, melhorias)
> 2. **[roadmap-funcional.md](roadmap-funcional.md)** - Features funcionais por categoria
> 3. **[roadmap-testes.md](roadmap-testes.md)** - Testes e validações
> 4. **[roadmap-integracao.md](roadmap-integracao.md)** - Integrações e dependências
>
> **Objetivo:** Detalhar tarefas específicas por categoria, com estimativas e prioridades.
>
> **Conteúdo:**
>
> - Tarefas agrupadas por categoria
> - Prioridades (Alta, Média, Baixa)
> - Estimativas de tempo
> - Dependências entre tarefas
> - Status de cada tarefa
> - Links para tarefas puras (nível 3)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Nível 3: Tarefas Puras</b></summary>

> **Objetivo:** Tarefas acionáveis, específicas e testáveis.
>
> **Características de Tarefa Pura:**
>
> - ✅ **Específica:** Uma única ação clara
> - ✅ **Mensurável:** Critério de conclusão definido
> - ✅ **Acionável:** Pode ser executada diretamente
> - ✅ **Testável:** Pode ser validada/testada
> - ✅ **Estimável:** Tempo estimado realista
>
> **Exemplo de Tarefa Pura:**
>
> - ❌ **Ruim:** "Implementar sistema de spellcasting"
> - ✅ **Bom:** "Criar função `CalculateSpellSaveDC()` em `SpellcastingHelpers.cpp` com testes TDD (2-3 horas)"
>
> **Organização:**
>
> - Tarefas puras estão dentro dos roadmaps específicos
> - Cada tarefa tem: descrição, estimativa, prioridade, dependências, critério de conclusão

</details>

---

## 🔗 Navegação entre Níveis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Fluxo de Navegação</b></summary>

> **Do Roadmap Principal para Específicos:**
>
> 1. Roadmap Principal mostra fases e status geral
> 2. Cada fase tem link para roadmap específico relevante
> 3. Roadmap específico detalha tarefas daquela fase
>
> **Do Roadmap Específico para Tarefas Puras:**
>
> 1. Roadmap específico agrupa tarefas por categoria
> 2. Cada categoria lista tarefas puras
> 3. Cada tarefa pura tem descrição completa e critério de conclusão
>
> **Exemplo de Fluxo:**
>
> ```
> Roadmap Principal
>   └─> Fase 1.5: Melhorias D&D 5e
>       └─> Roadmap Técnico
>           └─> Categoria: Spellcasting
>               └─> Tarefa Pura: Criar CalculateSpellSaveDC()
> ```

</details>

---

## 📊 Estrutura de Arquivos

```
docs/planning/
├── roadmap.md                    # Nível 1: Roadmap Principal
├── roadmap-estrutura.md          # Este arquivo (documentação da estrutura)
├── roadmap-tecnico.md            # Nível 2: Roadmap Técnico
├── roadmap-funcional.md          # Nível 2: Roadmap Funcional
├── roadmap-testes.md             # Nível 2: Roadmap de Testes
├── roadmap-integracao.md         # Nível 2: Roadmap de Integração
└── roadmap-tecnico-*.md          # Roadmaps técnicos específicos (já existentes)
    ├── roadmap-tecnico-itens-iniciais.md
    └── roadmap-tecnico-inventario-boilerplate.md
```

---

## ✅ Checklist de Tarefa Pura

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Validação de Tarefa Pura</b></summary>

> Antes de considerar uma tarefa "pura", verificar:
>
> - [ ] **Específica:** Ação única e clara?
> - [ ] **Mensurável:** Critério de conclusão definido?
> - [ ] **Acionável:** Pode ser executada diretamente?
> - [ ] **Testável:** Pode ser validada/testada?
> - [ ] **Estimável:** Tempo estimado realista?
> - [ ] **Sem ambiguidade:** Não há múltiplas interpretações?
> - [ ] **Tamanho adequado:** Pode ser completada em 1-2 dias (idealmente)?
>
> **Se todas as respostas forem SIM, a tarefa é "pura".**

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
