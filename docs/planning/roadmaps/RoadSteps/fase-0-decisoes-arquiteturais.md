---
title: "Fase 0: Decisões Arquiteturais"
category: planning
tags: [roadmap, phase, architecture, critical, next]
last_updated: 2024-12-27
difficulty: advanced
related: [../../roadmap.md, ../../architecture/arquitetura-decisoes-criticas.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../../index.md) > [Planejamento](../index.md) > [Roadmap](../roadmap.md) > Fase 0

# Fase 0: Decisões Arquiteturais (PRÓXIMA IMPLEMENTAÇÃO)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Resumo Executivo</b></summary>

> **Status:** 🔴 **PRÓXIMA IMPLEMENTAÇÃO** - Decisões tomadas, **IMPLEMENTAÇÃO AGORA**
>
> **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2 (Combate)
>
> **Duração Estimada:** 1-2 semanas (foco em DEC-001 e DEC-010)
>
> **Objetivo:** Implementar base arquitetural sólida ANTES de continuar Fase 1
>
> **⚠️ CRÍTICO:** Segundo [Review: Metodologia Ágil Solo Dev](../../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md), DEC-001 e DEC-010 devem ser implementados **AGORA** para evitar refatoração massiva futura.
>
> **Justificativa:**
>
> > "Implementar DEC-001 e DEC-010 AGORA antes de continuar Fase 1. Evita refatoração massiva futura e desbloqueia Fase 2."

</details>

---

## 🔴 Ordem de Implementação (Críticos Primeiro)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Decisões Críticas (Implementar PRIMEIRO)</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>1. 🔴 DEC-001: GAS Attributes (migrar TMap → AttributeSet)</b></summary>
>
> > **Duração:** 1 semana (40 horas)
> >
> > **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2
> >
> > **Impacto:** Resolve problema de replicação, prepara para combate
> >
> > **O que implementar:**
> >
> > - Criar `UCharacterAttributeSet` com `FGameplayAttributeData` para Strength, Dexterity, etc.
> > - Meta-Attributes para modificadores (StrengthModifier, etc.)
> > - Health e MaxHealth em AttributeSet
> > - Migrar `CharacterDataComponent::AbilityScores` de `TMap<FName, int32>` para GAS Attributes
> > - Implementar `OnRep_*` functions para replicação
> > - Implementar `PreAttributeChange` e `PostGameplayEffectExecute`
> > - Atualizar todos os sistemas que usam Ability Scores
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-001](../../architecture/arquitetura-decisoes-criticas.md#dec-001)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>2. 🔴 DEC-010: GAS Completo (ASC, Tags, estrutura base)</b></summary>
>
> > **Duração:** 3-5 dias (24-40 horas)
> >
> > **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2
> >
> > **Dependências:** DEC-001
> >
> > **Impacto:** Estrutura base do GAS para combate
> >
> > **O que implementar:**
> >
> > - `UAbilitySystemComponent` no PlayerState (Player)
> > - `UAbilitySystemComponent` no Character (AI)
> > - `InitAbilityActorInfo` configurado
> > - Gameplay Tags configurados (DEC-008 integrado)
> > - Estrutura base para Gameplay Effects e Abilities (preparação para Fase 2)
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-010](../../architecture/arquitetura-decisoes-criticas.md#dec-010)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>3. 🔴 DEC-008: Gameplay Tags (sistema completo de notificações)</b></summary>
>
> > **Duração:** 2-3 dias (16-24 horas)
> >
> > **Prioridade:** 🔴 **Alta** - Necessário para GAS completo
> >
> > **Status Atual:** ⚠️ Parcial (helpers existem, sistema completo não)
> >
> > **O que implementar:**
> >
> > - Configurar Gameplay Tags no projeto
> > - Criar tags para notificações (ex: "Character.AbilityScore.Strength.Changed")
> > - Integrar tags com AttributeSet (OnRep dispara tags)
> > - Sistema de eventos baseado em tags
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-008](../../architecture/arquitetura-decisoes-criticas.md#dec-008)
>
> </details>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟡 Decisões Importantes (Depois dos Críticos)</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>4. 🟡 DEC-006: Dice Rolling (módulo DiceRolls/)</b></summary>
>
> > **Duração:** 2-3 dias (16-24 horas)
> >
> > **Prioridade:** 🟡 **Média** - Importante mas não bloqueia Fase 2
> >
> > **O que implementar:**
> >
> > - Namespace `DiceRolls` com funções:
> >   - `Roll(FString Expression)` - Parser "1d4" → RollDice(1, 4)
> >   - `Roll(int32 Count, int32 Sides)` - RollDice direto
> >   - `RollWithModifier(FString Expression, int32 Modifier)` - Com modificador
> >   - `SetSeed(int32 Seed)` - Para testes determinísticos
> > - Testes automatizados (TDD)
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-006](../../architecture/arquitetura-decisoes-criticas.md#dec-006)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>5. 🟡 DEC-002: Save/Load (USaveGame)</b></summary>
>
> > **Duração:** 2-3 dias (16-24 horas)
> >
> > **Prioridade:** 🟡 **Média** - Importante mas não bloqueia Fase 2
> >
> > **O que implementar:**
> >
> > - `UCharacterSaveGame` herdando de `USaveGame`
> > - `UPROPERTY(SaveGame)` para `FCharacterInstanceData`
> > - Salvar GAS Attributes
> > - Sistema de versionamento (migração de versões antigas)
> > - Funções `Save()` e `Load()`
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-002](../../architecture/arquitetura-decisoes-criticas.md#dec-002)
>
> </details>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟢 Decisões Secundárias (Pode Ser Depois)</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>6. 🟢 DEC-007: Tempo/Duração (sistema híbrido)</b></summary>
>
> > **Duração:** 1-2 dias (8-16 horas)
> >
> > **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> >
> > **O que implementar:**
> >
> > - `FDurationConverter::ConvertToRealTime()` - Converte turnos D&D para real-time
> > - Sistema híbrido: 1 turno D&D = 6 segundos real-time
> > - Preparação para GAS Effects (duração de efeitos)
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-007](../../architecture/arquitetura-decisoes-criticas.md#dec-007)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>7. 🟢 DEC-005: Networking (melhorias Server Authoritative)</b></summary>
>
> > **Duração:** 1-2 dias (8-16 horas)
> >
> > **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> >
> > **O que implementar:**
> >
> > - Melhorias em validação de RPCs (`WithValidation`)
> > - Garantir autoridade do servidor em todas as operações críticas
> > - Documentar padrões de networking
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-005](../../architecture/arquitetura-decisoes-criticas.md#dec-005)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>8. 🟢 DEC-009: Quests (estrutura base)</b></summary>
>
> > **Duração:** 1-2 dias (8-16 horas)
> >
> > **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> >
> > **O que implementar:**
> >
> > - `FQuestDataRow` (DataTable)
> > - `UQuestComponent` (componente replicável)
> > - Estrutura base para progresso de quests
> >
> > **📖 Detalhes Completos:** [arquitetura-decisoes-criticas.md#dec-009](../../architecture/arquitetura-decisoes-criticas.md#dec-009)
>
> </details>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Já Implementados</b></summary>

> - ✅ **DEC-003:** Bridge Component (melhorias)
> - ✅ **DEC-004:** Data Tables (carregamento completo)

</details>

---

## 📊 Duração e Estimativas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Estimativas de Tempo</b></summary>

> **Duração Total:** 1-2 semanas (foco em DEC-001 e DEC-010)
>
> **Duração Mínima (Críticos):** 1.5-2 semanas
>
> - DEC-001: 1 semana (40 horas)
> - DEC-010: 3-5 dias (24-40 horas)
> - DEC-008: 2-3 dias (16-24 horas)
> - **Total Críticos:** 1.5-2 semanas (80-104 horas)
>
> **Duração Completa (Todos):** 2-3 semanas
>
> - Críticos: 1.5-2 semanas
> - Importantes: 4-6 dias (32-48 horas)
> - Secundárias: 3-4 dias (24-32 horas)
> - **Total:** 2-3 semanas (136-184 horas)

</details>

---

## 🎯 Por que Esta Fase é Crítica

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Bloqueios e Dependências</b></summary>

> **Fase 0 bloqueia:**
>
> - 🔴 **Fase 2 (Combate)** - Precisa de GAS Attributes (DEC-001) e ASC (DEC-010)
> - 🔄 **Fase 1 (Fichas)** - Deve migrar para GAS Attributes após Fase 0
>
> **Por que implementar AGORA:**
>
> - Evita refatoração massiva na Fase 2
> - Alinha arquitetura desde o início
> - Prepara para combate (Fase 2)
> - [Review: Metodologia Ágil Solo Dev](../../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md) recomenda: **"Implementar AGORA antes de continuar Fase 1"**

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Roadmap Completo](../roadmap.md)** - Visão geral de todas as fases
> - **[Decisões Arquiteturais Críticas](../../architecture/arquitetura-decisoes-criticas.md)** - 🔴 **CRÍTICO** - Detalhes completos de cada decisão
> - **[Review: Metodologia Ágil Solo Dev](../../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md)** - 🔴 **CRÍTICO** - Justificativa para implementar AGORA

</details>

---

**Última atualização:** 2024-12-27
**Status:** 🔴 Próxima Implementação
