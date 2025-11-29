---
title: "Metodologia Ágil - Guia de Uso"
category: planning
tags: [agile, scrum, kanban, methodology]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Metodologia Ágil

# Metodologia Ágil - Guia de Uso

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este documento explica como o projeto utiliza **metodologias ágeis** (Scrum/Kanban) para gerenciamento de desenvolvimento.
>
> **Conceitos Aplicados:**
>
> - **Epics** - Grandes funcionalidades (ex: "Sistema de Criação de Personagem")
> - **User Stories** - Funcionalidades do ponto de vista do usuário
> - **Sprints** - Iterações de 1-2 semanas
> - **Backlog** - Lista priorizada de trabalho
> - **Definition of Done** - Critérios de conclusão
> - **Velocity** - Velocidade de entrega
>
> **Benefícios:**
>
> - ✅ Flexibilidade para mudanças
> - ✅ Entrega incremental de valor
> - ✅ Feedback contínuo
> - ✅ Transparência e visibilidade

</details>

---

## 📐 Estrutura Ágil do Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Hierarquia: Epic → User Story → Task</b></summary>

> **Epic (Épico):**
>
> - Grande funcionalidade que pode levar múltiplos sprints
> - Exemplo: "Sistema Completo de Criação de Personagem D&D 5e"
> - Dividido em múltiplas User Stories
>
> **User Story (História de Usuário):**
>
> - Funcionalidade do ponto de vista do usuário
> - Formato: "Como [tipo de usuário], eu quero [ação] para [benefício]"
> - Exemplo: "Como jogador, eu quero escolher Standard Array para distribuir ability scores de forma balanceada"
> - Dividida em múltiplas Tasks
>
> **Task (Tarefa):**
>
> - Tarefa técnica específica e acionável
> - Exemplo: "Criar função `GetStandardArrayValues()` em `Utils/AbilityScoreHelpers.h/cpp`"
> - Tem estimativa, prioridade e critério de conclusão

</details>

---

## 🏃 Sprints e Iterações

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Estrutura de Sprints</b></summary>

> **Duração:** 1-2 semanas (recomendado: 1 semana para features pequenas, 2 semanas para features maiores)
>
> **Cerimônias:**
>
> - **Sprint Planning** - Planejar trabalho do sprint
> - **Daily Standup** - Acompanhamento diário (opcional para projeto solo)
> - **Sprint Review** - Revisar entregas
> - **Sprint Retrospective** - Melhorias contínuas
>
> **Backlog do Sprint:**
>
> - Tarefas selecionadas do backlog principal
> - Priorizadas por valor e dependências
> - Estimadas e testáveis

</details>

---

## 📊 Priorização MoSCoW

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Método MoSCoW</b></summary>

> **M - Must Have (Deve Ter):**
>
> - Crítico para o projeto
> - Bloqueia outras funcionalidades
> - Exemplo: Corrigir bugs críticos, HP inicial
>
> **S - Should Have (Deveria Ter):**
>
> - Importante mas não bloqueante
> - Melhora significativamente o produto
> - Exemplo: Standard Array, Starting Equipment
>
> **C - Could Have (Poderia Ter):**
>
> - Desejável mas não essencial
> - Pode ser adiado sem grande impacto
> - Exemplo: Personality Traits, Ideals
>
> **W - Won't Have (Não Terá):**
>
> - Não será implementado neste ciclo
> - Pode ser considerado no futuro
> - Exemplo: Features avançadas de Fase 5+

</details>

---

## ✅ Definition of Done (DoD)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✔️ Critérios de Conclusão</b></summary>

> Uma tarefa é considerada **"Done"** quando:
>
> - ✅ **Código implementado** seguindo Clean Code e Design Patterns
> - ✅ **Testes escritos** (TDD quando aplicável) e passando
> - ✅ **Documentação atualizada** (se necessário)
> - ✅ **Compila sem erros** ou warnings críticos
> - ✅ **Validação manual** realizada (quando aplicável)
> - ✅ **Code review** realizado (se em equipe)
> - ✅ **Integrado** com sistema existente
> - ✅ **Critério de conclusão específico** atendido
>
> **User Story é "Done" quando:**
>
> - ✅ Todas as tasks da story estão "Done"
> - ✅ Funcionalidade testada end-to-end
> - ✅ Aceita pelo "Product Owner" (você mesmo)

</details>

---

## 📈 Métricas e Velocity

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Tracking de Progresso</b></summary>

> **Velocity (Velocidade):**
>
> - Horas trabalhadas por sprint
> - Tarefas completadas por sprint
> - Usado para planejar próximos sprints
>
> **Burndown Chart:**
>
> - Visualização de progresso do sprint
> - Horas restantes vs. tempo decorrido
>
> **Métricas Importantes:**
>
> - **Throughput:** Tarefas completadas por semana
> - **Cycle Time:** Tempo médio para completar uma tarefa
> - **Lead Time:** Tempo desde planejamento até conclusão

</details>

---

## 🔗 Integração com Roadmaps

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Como Usar com Roadmaps</b></summary>

> **Roadmap Principal:**
>
> - Contém **Epics** (Fases)
> - Visão estratégica de longo prazo
>
> **Roadmaps Específicos:**
>
> - Contém **User Stories** agrupadas por categoria
> - Priorizadas com MoSCoW
>
> **Tarefas Puras:**
>
> - **Tasks** técnicas específicas
> - Estimadas e acionáveis
> - Selecionadas para sprints
>
> **Fluxo:**
>
> ```
> Epic (Fase) → User Story → Task → Sprint Backlog → Done
> ```

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> - **[Roadmap Principal](../roadmaps/roadmap.md)** - Epics e fases
> > - **[Roadmap Técnico](roadmap-tecnico.md)** - User Stories técnicas
> > - **[Roadmap Funcional](roadmap-funcional.md)** - User Stories funcionais
> > - **[Backlog](backlog.md)** - Lista priorizada de trabalho
> > - **[Sprints](sprints.md)** - Planejamento de sprints

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
