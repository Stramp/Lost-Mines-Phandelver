---
title: "Fase 1: Sistema de Fichas"
category: planning
tags: [roadmap, phase, character-sheet, in-progress]
last_updated: 2024-12-27
difficulty: intermediate
related: [../../roadmap.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../../index.md) > [Planejamento](../index.md) > [Roadmap](../roadmap.md) > Fase 1

# Fase 1: Sistema de Fichas (70% COMPLETO)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Resumo Executivo</b></summary>

> **Status:** 🔄 **Em desenvolvimento** - Core funcional, **PAUSADO até Fase 0**
>
> **Progresso:** ~70% completo
>
> **Objetivo:** Sistema completo de criação de personagens D&D 5e
>
> **Duração Estimada:** 1-2 semanas (restante, após Fase 0)
>
> **⚠️ IMPORTANTE:** Fase 1 está pausada até completar Fase 0 (DEC-001 e DEC-010). Após Fase 0, Fase 1 será migrada para usar GAS Attributes.

</details>

---

## ✅ O Que Foi Implementado

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Funcionalidades Completas</b></summary>

> - ✅ **Motores Básicos:**
>   - `RaceBonusMotor` - Aplicação de bônus raciais
>   - `PointBuyMotor` - Sistema de Point Buy para ability scores
>   - `MulticlassMotor` - Sistema de multiclasse
>
> - ✅ **Sistema de Validação:**
>   - Validators completos para todas as regras D&D 5e
>   - Validação de multiclasse
>   - Validação de Point Buy
>
> - ✅ **Variant Human:**
>   - Escolha de feat
>   - Escolha de skill
>   - Escolha de ability score improvement
>
> - ✅ **Multiclasse:**
>   - Estrutura completa
>   - Validação de pré-requisitos
>   - Cálculo de proficiências
>
> - ✅ **Sistema de Dropdowns:**
>   - Races, Classes, Backgrounds
>   - Skills, Feats, Features
>   - Integração com Data Tables
>
> - ✅ **Cálculos Básicos:**
>   - Ability Modifiers
>   - Proficiency Bonus
>   - HP inicial
>
> - ✅ **Testes Automatizados:**
>   - 275+ testes automatizados
>   - Cobertura de motores, validators e helpers

</details>

---

## 📋 O Que Está Faltando

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Tarefas Pendentes</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>1. 📋 Itens Iniciais e Boilerplate de Inventário</b></summary>
>
> > **Prioridade:** 🔴 Alta
> >
> > **O que implementar:**
> >
> > - Sistema de itens iniciais (Starting Equipment)
> > - Estruturas base de inventário (FInventoryItem, FEquipmentSlot)
> > - Integração com ItemDataTable
> > - Validação de itens iniciais por classe/background
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>2. ⚠️ Validação e Testes Finais</b></summary>
>
> > **Prioridade:** 🔴 Alta
> >
> > **O que fazer:**
> >
> > - Testes end-to-end completos
> > - Correção de testes de Proficiency Bonus (valores esperados incorretos)
> > - Validação de criação de feat no editor
> > - Testes de integração com Data Tables
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>3. 📋 Migração para GAS Attributes</b></summary>
>
> > **Prioridade:** 🔴 **CRÍTICA** - Depende de Fase 0
> >
> > **O que fazer:**
> >
> > - Migrar `CharacterDataComponent::AbilityScores` de `TMap<FName, int32>` para GAS Attributes (DEC-001)
> > - Atualizar todos os sistemas que usam Ability Scores
> > - Integrar com `UCharacterAttributeSet`
> > - Atualizar testes para usar GAS Attributes
>
> </details>

</details>

---

## 🔗 Dependências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Bloqueios</b></summary>

> **Fase 1 está BLOQUEADA por:**
>
> - 🔴 **Fase 0 (DEC-001, DEC-010)** - Precisa migrar para GAS Attributes
> - ✅ **Fase 0.5** - Data Tables (completo)
>
> **Fase 1 bloqueia:**
>
> - 📋 **Fase 1.5** - Melhorias D&D 5e (aguarda conclusão de Fase 1)

</details>

---

## 📊 Estimativas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Duração Estimada</b></summary>

> **Duração Total:** 1-2 semanas (restante, após Fase 0)
>
> **Breakdown:**
>
> - Itens Iniciais: 2-3 dias (16-24 horas)
> - Validação e Testes: 2-3 dias (16-24 horas)
> - Migração para GAS: 3-5 dias (24-40 horas) - Depende de Fase 0
>
> **Total:** 1-2 semanas (56-88 horas)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Roadmap Completo](../roadmap.md)** - Visão geral de todas as fases
> - **[Fase 0: Decisões Arquiteturais](./fase-0-decisoes-arquiteturais.md)** - Bloqueador crítico
> - **[Decisões Arquiteturais](../../architecture/arquitetura-decisoes-criticas.md)** - DEC-001: GAS Attributes

</details>

---

**Última atualização:** 2024-12-27
**Status:** 🔄 Em desenvolvimento (pausado até Fase 0)
