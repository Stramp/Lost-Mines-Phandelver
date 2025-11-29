---
title: "Roadmap Completo"
category: planning
tags: [roadmap, planning, phases, development]
last_updated: 2024-12-27
difficulty: intermediate
related: [../architecture/arquitetura-decisoes-criticas.md, ../../technical/architecture.md]
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Roadmap

# Roadmap Completo - MyProject2

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este documento contém o **roadmap completo** desde as decisões arquiteturais até o combate inicial funcionando.
>
> **Objetivo:** Transformar o sistema de fichas atual em um jogo completo, mantendo fidelidade às regras D&D 5ª edição.
>
> **Status Geral:**
>
> - ✅ **Fase 0.5:** Data Tables (Completo)
> - 🔴 **Fase 0:** Decisões Arquiteturais (**PRÓXIMA IMPLEMENTAÇÃO - BLOQUEIA TUDO**)
> - 🔄 **Fase 1:** Sistema de Fichas (70% completo) - **Pausado até Fase 0**
> - 📋 **Fase 1.5:** Melhorias D&D 5e (Planejado) - **BLOQUEADO por Fase 0 (DEC-001)**
> - 📋 **Fase 2:** Combate Básico com GAS (Planejado) - **BLOQUEADO por Fase 0**
> - 📋 **Fase 3:** Teste de Combate Inicial (Planejado)
>
> **📖 Referências:**
>
> - **[Decisões Arquiteturais Críticas](../architecture/arquitetura-decisoes-criticas.md)** - 🔴 **CRÍTICO** - Todas as decisões que precisam ser implementadas
>   - **[Status de Implementação](../architecture/arquitetura-decisoes-criticas.md#-status-de-implementação)** - Tabela completa de status
>   - **[Diagrama de Dependências](../architecture/arquitetura-decisoes-criticas.md#-diagrama-de-dependências)** - Visualização de dependências
> - **[Review: Metodologia Ágil Solo Dev](../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md)** - 🔴 **CRÍTICO** - Alinhamento com metodologias ágeis
> - **[Revisão Estrutural - Integração](../architecture/revisao-estrutural-integracao.md)** - Sistemas D&D 5e faltantes

</details>

---

## 📊 Legenda de Status

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔖 Status e Símbolos</b></summary>

> **Status:**
>
> - ✅ **Completo** - Implementado e testado
> - 🔄 **Em desenvolvimento** - Trabalho em andamento
> - 🔴 **Próxima** - Próxima implementação (bloqueia outras fases)
> - 📋 **Planejado** - Definido no roadmap, não iniciado
> - ⚠️ **Pendente** - Aguardando validação ou decisão
>
> **Prioridade:**
>
> - 🔴 **Alta** - Crítico para próxima fase
> - 🟡 **Média** - Importante mas não bloqueante
> - 🟢 **Baixa** - Melhorias e polish
>
> **Metodologia:**
>
> - 🧪 **TDD** - Test-Driven Development obrigatório (testes ANTES da implementação)
> - 📝 **Test-After** - Testes depois são aceitáveis (Getters/Setters, wrappers simples)

</details>

---

## ✅ Fase 0.5: Data Tables (CONCLUÍDA)

> **📖 [Ver detalhes completos →](./roadsteps/fase-0.5-data-tables.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Configuração e Validação de Data Tables</b></summary>

> **Status:** ✅ **Completo** - Todas as tabelas e structs prontas e testadas
>
> **Objetivo:** Garantir que todas as Data Tables estejam 100% configuradas, validadas e prontas.
>
> **✅ Conclusão:** 2024-12-27 - Todas as 15 tabelas validadas, structs C++ alinhadas, schemas JSON criados
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📊 Tabelas Validadas</b></summary>
>
> > **Tabelas de Referência (Master Data) - 9 Tabelas:**
> >
> > 1. ✅ AbilityScoreDataTable
> > 2. ✅ TraitDataTable
> > 3. ✅ LanguageDataTable
> > 4. ✅ SkillDataTable
> > 5. ✅ SpellDataTable (133 magias completas)
> > 6. ✅ SpellSchoolDataTable
> > 7. ✅ DamageTypeDataTable (incluindo tipos físicos)
> > 8. ✅ ConditionDataTable
> > 9. ✅ ProficiencyDataTable
> >
> > **Tabelas Principais - 6 Tabelas:**
> >
> > 1. ✅ RaceDataTable
> > 2. ✅ ClassDataTable
> > 3. ✅ BackgroundDataTable
> > 4. ✅ FeatDataTable
> > 5. ✅ FeatureDataTable (49 features)
> > 6. ✅ ItemDataTable
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🎯 Entregas</b></summary>
>
> > - ✅ **15 Data Tables** configuradas e validadas
> > - ✅ **15 Structs C++** alinhadas com JSON
> > - ✅ **15 Schemas JSON** criados para validação
> > - ✅ **Dados completos** (133 magias, 49 features, todos os itens iniciais)
> > - ✅ **Compilação bem-sucedida** de todas as structs
>
> </details>

</details>

---

## 🔴 Fase 0: Decisões Arquiteturais (PRÓXIMA IMPLEMENTAÇÃO)

> **📖 [Ver detalhes completos →](./roadsteps/fase-0-decisoes-arquiteturais.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Implementação Crítica - BLOQUEIA Fase 2</b></summary>

> **Status:** 🔴 **PRÓXIMA IMPLEMENTAÇÃO** - Decisões tomadas, **IMPLEMENTAÇÃO AGORA**
>
> **Objetivo:** Implementar base arquitetural sólida ANTES de continuar Fase 1
>
> **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2 (Combate)
>
> **⚠️ CRÍTICO:** Segundo [Review: Metodologia Ágil Solo Dev](../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md), DEC-001 e DEC-002 devem ser implementados **AGORA** para evitar refatoração massiva futura.
>
> **Justificativa:**
>
> > "Implementar DEC-001 e DEC-002 AGORA antes de continuar Fase 1. Evita refatoração massiva futura e desbloqueia Fase 2."
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔴 Ordem de Implementação (Críticos Primeiro)</b></summary>
>
> > **1. 🔴 DEC-001: GAS Attributes (migrar TMap → AttributeSet)**
> >
> > - **Duração:** 1 semana (40 horas)
> > - **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2
> > - **Impacto:** Resolve problema de replicação, prepara para combate
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-001](../architecture/arquitetura-decisoes-criticas.md#dec-001)
> >
> > **2. 🔴 DEC-002: GAS Completo (ASC, Tags, estrutura base)** ⭐
> >
> > - **Duração:** 3-5 dias (24-40 horas)
> > - **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2
> > - **Dependências:** DEC-001
> > - **Impacto:** Estrutura base do GAS para combate
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-007](../architecture/arquitetura-decisoes-criticas.md#dec-007)
> >
> > **3. 🔴 DEC-003: Gameplay Tags (sistema completo de notificações)**
> >
> > - **Duração:** 2-3 dias (16-24 horas)
> > - **Prioridade:** 🔴 **Alta** - Necessário para GAS completo
> > - **Status Atual:** ⚠️ Parcial (helpers existem, sistema completo não)
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-003](../architecture/arquitetura-decisoes-criticas.md#dec-003)
> >
> > **4. 🟡 DEC-004: Dice Rolling (módulo DiceRolls/)**
> >
> > - **Duração:** 2-3 dias (16-24 horas)
> > - **Prioridade:** 🟡 **Média** - Importante mas não bloqueia Fase 2
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-004](../architecture/arquitetura-decisoes-criticas.md#dec-004)
> >
> > **5. 🟡 DEC-007: Save/Load (USaveGame)**
> >
> > - **Duração:** 2-3 dias (16-24 horas)
> > - **Prioridade:** 🟡 **Média** - Importante mas não bloqueia Fase 2
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-007](../architecture/arquitetura-decisoes-criticas.md#dec-007)
> >
> > **6. 🟢 DEC-006: Tempo/Duração (sistema híbrido)**
> >
> > - **Duração:** 1-2 dias (8-16 horas)
> > - **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-006](../architecture/arquitetura-decisoes-criticas.md#dec-006)
> >
> > **7. 🟢 DEC-007: Networking (melhorias Server Authoritative)**
> >
> > - **Duração:** 1-2 dias (8-16 horas)
> > - **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-007](../architecture/arquitetura-decisoes-criticas.md#dec-007)
> >
> > **8. 🟢 DEC-008: Quests (estrutura base)**
> >
> > - **Duração:** 1-2 dias (8-16 horas)
> > - **Prioridade:** 🟢 **Baixa** - Pode ser feito depois
> > - **📖 Detalhes:** [arquitetura-decisoes-criticas.md#dec-008](../architecture/arquitetura-decisoes-criticas.md#dec-008)
> >
> > **✅ Já Implementados:**
> >
> > - ✅ **DEC-009:** Bridge Component (melhorias)
> > - ✅ **DEC-010:** Data Tables (carregamento completo)
>
> </details>
>
> **Duração Estimada Total:** 1-2 semanas (foco em DEC-001 e DEC-002)
>
> **Duração Mínima (Críticos):** 1.5-2 semanas (DEC-001 + DEC-002 + DEC-003)
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📚 Referência Completa</b></summary>
>
> > Para detalhes completos de cada decisão, justificativas e implementação recomendada, consulte:
> >
> > **[Decisões Arquiteturais Críticas](../architecture/arquitetura-decisoes-criticas.md)**
>
> </details>

</details>

---

## 🔄 Fase 1: Sistema de Fichas (70% COMPLETO)

> **📖 [Ver detalhes completos →](./roadsteps/fase-1-sistema-fichas.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Sistema de Criação de Personagens D&D 5e</b></summary>

> **Status:** 🔄 **Em desenvolvimento** - Core funcional, **PAUSADO até Fase 0**
>
> **Progresso:** ~70% completo
>
> **Objetivo:** Sistema completo de criação de personagens D&D 5e
>
> **⚠️ IMPORTANTE:** Fase 1 está pausada até completar Fase 0 (DEC-001 e DEC-002). Após Fase 0, Fase 1 será migrada para usar GAS Attributes.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>✅ O Que Foi Implementado</b></summary>
>
> > - ✅ **Motores Básicos** (RaceBonus, PointBuy, Multiclass)
> > - ✅ **Sistema de Validação** completo
> > - ✅ **Variant Human** (feat, skill, ability choices)
> > - ✅ **Multiclasse** (estrutura e validação)
> > - ✅ **Sistema de Dropdowns** (races, classes, backgrounds, etc.)
> > - ✅ **Cálculos Básicos** (modifiers, proficiency, HP)
> > - ✅ **275+ Testes Automatizados**
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📋 O Que Está Faltando</b></summary>
>
> > - 📋 **Itens Iniciais** e boilerplate de inventário
> > - ⚠️ **Validação e Testes** finais (testes end-to-end, correção de Proficiency Bonus)
> > - 📋 **Migração para GAS Attributes** (após Fase 0)
>
> </details>
>
> **Duração Estimada:** 1-2 semanas (restante, após Fase 0)

</details>

---

## 📋 Fase 1.5: Melhorias D&D 5e

> **📖 [Ver detalhes completos →](./roadsteps/fase-1.5-melhorias-dnd.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟡 Melhorias e Completude D&D 5e</b></summary>

> **Status:** 📋 **Planejado** - **BLOQUEADO por Fase 0 (DEC-001)**
>
> **Objetivo:** Completar sistemas D&D 5e documentados mas não implementados
>
> **Prioridade:** 🔴 **Alta** - Essencial para fidelidade às regras D&D 5e
>
> **Duração Estimada:** 3-4 semanas
>
> **Metodologia:** 🧪 **TDD obrigatório** para todas as funções helper/motor
>
> **⚠️ CRÍTICO - Dependência de DEC-001:**
>
> > **Fase 1.5.1 (Spellcasting)** precisa de **DEC-001 (GAS Attributes)** implementado:
> >
> > - SpellcastingHelpers precisa de Ability Modifiers em GAS Attributes
> > - Spell Save DC = `8 + ProficiencyBonus + SpellcastingAbilityModifier` (modifier vem de GAS)
> > - Spell Attack Modifier = `ProficiencyBonus + SpellcastingAbilityModifier` (modifier vem de GAS)
> >
> > **📖 Referência:** [Revisão Estrutural - Alinhamento com DEC-001](../architecture/revisao-estrutural-integracao.md#alinhamento-com-decisões-arquiteturais)
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔴 1.5.1 - Sistema de Spellcasting (1-2 semanas)</b></summary>
>
> > **Prioridade:** 🔴 Alta - Base para Fase 2 (Combate)
> >
> > **⚠️ BLOQUEADO por:** DEC-001 (GAS Attributes) - Spellcasting precisa de Ability Modifiers em GAS
> >
> > **Dependências:**
> >
> > - ✅ **DEC-001:** GAS Attributes (Ability Modifiers em GAS)
> > - ✅ **DEC-004:** Dice Rolling (parser de dados "1d4" para spells)
> >
> > **Entregas:**
> >
> > - 📋 SpellcastingHelpers (CalculateSpellSaveDC, CalculateSpellAttackModifier, etc.)
> >   - **Usa:** GAS Attributes para Ability Modifiers (DEC-001)
> > - 📋 SpellcastingConstants (DnDConstants.h)
> > - 📋 Testes automatizados (50-70 testes) - 🧪 TDD obrigatório
> > - 📋 Integração com CharacterSheetDataAsset
> >
> > **📖 Referência:** [Revisão Estrutural - Spellcasting](../architecture/revisao-estrutural-integracao.md#-1-sistema-de-spellcasting---não-implementado)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔴 1.5.2 - Sistema de ASI (1 semana)</b></summary>
>
> > **Prioridade:** 🔴 Alta - Essencial para progressão de personagem
> >
> > **⚠️ BLOQUEADO por:** DEC-001 (GAS Attributes) - ASI precisa atualizar GAS Attributes
> >
> > **Dependências:**
> >
> > - ✅ **DEC-001:** GAS Attributes (ASI atualiza Ability Scores em GAS)
> >
> > **Entregas:**
> >
> > - 📋 ASIHelpers (GetASILevelsForClass, CanTakeASIAtLevel, etc.)
> > - 📋 ASIStructs (FASIOption, FASIEntry)
> > - 📋 Testes automatizados (30-40 testes) - 🧪 TDD obrigatório
> > - 📋 Integração com CharacterSheetDataAsset
> > - 📋 Atualização de GAS Attributes quando ASI é aplicado
> >
> > **📖 Referência:** [Revisão Estrutural - ASI](../architecture/revisao-estrutural-integracao.md#-2-sistema-de-asi-ability-score-improvements---parcial)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🟡 1.5.3 - Level Up System Completo (1 semana)</b></summary>
>
> > **Prioridade:** 🟡 Média - Importante mas não bloqueante
> >
> > **Entregas:**
> >
> > - 📋 LevelUpMotor (ProcessLevelUp, GetAvailableChoicesAtLevel, etc.)
> > - 📋 LevelUpHelpers (CalculateHPGainForLevelUp, GetFeaturesUnlockedAtLevel)
> > - 📋 Testes automatizados (40-50 testes)
> > - 📋 Integração com CharacterSheetDataAsset
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🟡 1.5.4 - Correção de Testes Proficiency Bonus (2-4 horas)</b></summary>
>
> > **Prioridade:** 🟡 Média - Correção de testes existentes
> >
> > **Problema:** Testes esperam valores incorretos (base 1 ao invés de base 2)
> >
> > **Solução:** Corrigir valores esperados em CalculationHelpersTests.cpp
>
> </details>

</details>

---

## 📋 Fase 2: Combate Básico com GAS

> **📖 [Ver detalhes completos →](./roadsteps/fase-2-combate-basico.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Sistema de Combate Funcional</b></summary>

> **Status:** 📋 **Planejado** - **BLOQUEADO por Fase 0**
>
> **Objetivo:** Implementar sistema de combate básico usando GAS desde o início
>
> **Prioridade:** 🔴 **Alta** - Base para gameplay
>
> **Duração Estimada:** 2-3 semanas
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📋 Componentes Principais</b></summary>
>
> > - 📋 **GAS AttributeSet (C++)**
> >   - Health, MaxHealth (já em DEC-001)
> >   - Meta-Atributos para processamento de dano
> >   - PostGameplayEffectExecute para lógica de dano
> >
> > - 📋 **GAS Ability System Component**
> >   - ASC no PlayerState (Player)
> >   - ASC no Character (AI)
> >   - InitAbilityActorInfo configurado
> >
> > - 📋 **CombatComponent**
> >   - Calcular AC (10 + Dex Mod + Armor)
> >   - Calcular dano de ataque (weapon dice + ability modifier)
> >   - Aplicar dano via Gameplay Effects
> >   - Sistema de ações básico (Attack, Dodge, Dash)
> >
> > - 📋 **Gameplay Effects Básicos**
> >   - GE_Damage (Instant) - Aplicar dano
> >   - GE_Heal (Instant) - Curar
> >   - GE_Death (Infinite) - Estado de morte
> >
> > - 📋 **CombatHelpers** (em `Utils/`) - 🧪 TDD
> >   - CalculateArmorClass()
> >   - CalculateAttackRoll()
> >   - CalculateDamage()
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔗 Dependências</b></summary>
>
> > - ✅ Fase 0 (DEC-001, DEC-002) - **BLOQUEADOR CRÍTICO** - GAS Attributes e ASC base
> > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores e modifiers (já em GAS após Fase 0)
> > - ✅ Fase 1.5 (Melhorias D&D 5e) - Para spellcasting e ASI
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🎯 Entregas</b></summary>
>
> > - Sistema de combate funcional com GAS
> > - Health/MaxHealth via AttributeSet
> > - Aplicação de dano via Gameplay Effects
> > - Sistema de morte básico
>
> </details>

</details>

---

## 📋 Fase 3: Teste de Combate Inicial

> **📖 [Ver detalhes completos →](./roadsteps/fase-3-teste-combate.md)**

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟢 Validação de Combate</b></summary>

> **Status:** 📋 **Planejado** - Aguardando Fase 2
>
> **Objetivo:** Testar combate com personagens reais usando fichas reais
>
> **Prioridade:** 🟢 **Média** - Validação e ajustes
>
> **Duração Estimada:** 1-2 semanas
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📋 Entregas</b></summary>
>
> > - 📋 Criação de personagens de teste
> > - 📋 Combate básico funcionando
> > - 📋 Multiplayer básico (2+ jogadores)
> > - 📋 Validação de regras D&D 5e em combate
> > - 📋 Correções e ajustes baseados em testes
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔗 Dependências</b></summary>
>
> > - ✅ Fase 2 (Combate Básico) - Sistema de combate implementado
>
> </details>

</details>

---

## 🔴 Caminho Crítico para Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Ordem de Implementação Obrigatória</b></summary>

> **Caminho Crítico Identificado (baseado em [Checklist de Decisões](../architecture/arquitetura-decisoes-criticas.md#-checklist-de-decisões)):**
>
> ```text
> Fase 0.5: Data Tables ✅ (COMPLETO)
>   ↓
> 🔴 Fase 0: Decisões Arquiteturais (1-2 semanas) ← PRÓXIMA
>   ├── DEC-001: GAS Attributes (1 semana) 🔴 CRÍTICO ⭐ PRIMEIRO
>   │   └── BLOQUEIA: Fase 1.5, Fase 2, Save/Load, Multiplayer
>   ├── DEC-002: GAS Completo (3-5 dias) 🔴 CRÍTICO ⭐ SEGUNDO
>   │   └── Depende de: DEC-001
>   ├── DEC-003: Gameplay Tags (2-3 dias) 🔴 ALTA (terceiro)
>   │   └── Depende de: DEC-001, DEC-002
>   └── DEC-004: Dice Rolling (2-3 dias) 🟡 MÉDIA [paralelo]
>       └── Necessário para: Fase 1.5.1 (Spellcasting)
>   ↓
> 🔄 Fase 1: Completar 30% restante (1-2 semanas)
>   └── Migrar para GAS Attributes (após Fase 0)
>   ↓
> 📋 Fase 1.5: Melhorias D&D 5e (3-4 semanas) ⚠️ BLOQUEADO por DEC-001
>   ├── 1.5.1: Spellcasting → Precisa DEC-001 (Ability Modifiers)
>   ├── 1.5.2: ASI → Precisa DEC-001 (atualizar Attributes)
>   ├── 1.5.3: Level Up System
>   └── 1.5.4: Correção Testes
>   ↓
> 📋 Fase 2: Combate Básico com GAS (2-3 semanas)
>   └── Depende de: Fase 0 (DEC-001, DEC-002) + Fase 1.5
>   ↓
> 📋 Fase 3: Teste de Combate Inicial (1-2 semanas)
>   ↓
> 🎮 COMBATE FUNCIONANDO
> ```
>
> **Total Estimado:** 7-11 semanas (1.75-2.75 meses) até combate funcionando
>
> **Bloqueios Críticos (baseado em [Status de Implementação](../architecture/arquitetura-decisoes-criticas.md#-status-de-implementação)):**
>
> - 🔴 **Fase 0 (DEC-001)** → **BLOQUEIA Fase 1.5** (Spellcasting e ASI precisam de GAS Attributes)
> - 🔴 **Fase 0 (DEC-001, DEC-002)** → **BLOQUEIA Fase 2** (Combate precisa de GAS)
> - 🔄 **Fase 1 (30% restante)** → Bloqueia Fase 1.5 (completar sistema de fichas)
> - 📋 **Fase 1.5** → Bloqueia Fase 2 (Spellcasting necessário para combate)
>
> **Por que Fase 0 é crítica:**
>
> - Fase 2 precisa de GAS Attributes (DEC-001)
> - Fase 2 precisa de ASC base (DEC-002)
> - Se não implementar agora → refatoração massiva na Fase 2
> - [Review: Metodologia Ágil Solo Dev](../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md) recomenda: **"Implementar AGORA antes de continuar Fase 1"**

</details>

---

## 📊 Resumo Visual do Roadmap

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Fluxo Completo até Combate</b></summary>

> Diagrama de dependências e ordem de implementação:
>
> ```text
> Fase 0.5: Data Tables ✅ (COMPLETO)
>   ↓
> 🔴 Fase 0: Decisões Arquiteturais (PRÓXIMA - 1-2 semanas)
>   ├── DEC-001: GAS Attributes 🔴 (1 semana) ← CRÍTICO
>   ├── DEC-002: GAS Completo 🔴 (3-5 dias) ← CRÍTICO
>   ├── DEC-003: Gameplay Tags 🔴 (2-3 dias)
>   ├── DEC-004: Dice Rolling 🟡 (2-3 dias)
>   ├── DEC-007: Save/Load 🟡 (2-3 dias)
>   ├── DEC-009: Bridge Component ✅ (Implementado)
>   ├── DEC-010: Data Tables ✅ (Implementado)
>   ├── DEC-006: Tempo/Duração 🟢 (1-2 dias)
>   ├── DEC-007: Networking 🟢 (1-2 dias)
>   └── DEC-008: Quests 🟢 (1-2 dias)
>   ↓
> 🔄 Fase 1: Sistema de Fichas (70% → 100%) (1-2 semanas)
>   └── Migração para GAS Attributes (após Fase 0)
>   ↓
> 📋 Fase 1.5: Melhorias D&D 5e (3-4 semanas)
>   ├── 1.5.1: Spellcasting
>   ├── 1.5.2: ASI
>   ├── 1.5.3: Level Up System
>   └── 1.5.4: Correção Testes
>   ↓
> 📋 Fase 2: Combate Básico com GAS (2-3 semanas)
>   └── Depende de: Fase 0 + Fase 1.5
>   ↓
> 📋 Fase 3: Teste de Combate Inicial (1-2 semanas)
>   ↓
> 🎮 COMBATE FUNCIONANDO
> ```
>
> **Total Estimado:** 7-11 semanas (1.75-2.75 meses)
>
> **Status Atual:**
>
> - ✅ Fase 0.5 completa
> - 🔴 **Fase 0: PRÓXIMA IMPLEMENTAÇÃO** (DEC-001 e DEC-002 críticos)
> - 🔄 Fase 1: 70% completo (pausado até Fase 0)
> - 📋 Fases 1.5, 2, 3: Planejadas

</details>

---

## 🎯 Próximos Passos Imediatos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Ações Imediatas (Ordem Correta)</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔴 1. IMPLEMENTAR FASE 0 (DECISÕES ARQUITETURAIS) - PRIMEIRO</b></summary>
>
> > **Prioridade:** 🔴 **MÁXIMA** - Bloqueia Fase 2 (Combate)
> >
> > **Justificativa do Relatório:**
> >
> > > "Implementar DEC-001 e DEC-002 AGORA antes de continuar Fase 1. Evita refatoração massiva futura."
> >
> > **Ordem de Implementação:**
> >
> > 1. 🔴 **DEC-001:** GAS Attributes (migrar TMap → AttributeSet) - **1 semana**
> > 2. 🔴 **DEC-002:** GAS Completo (ASC, Tags, estrutura base) - **3-5 dias**
> > 3. 🔴 **DEC-003:** Gameplay Tags (sistema completo) - **2-3 dias**
> > 4. 🟡 **DEC-004:** Dice Rolling (módulo DiceRolls/) - **2-3 dias**
> > 5. 🟡 **DEC-007:** Save/Load (USaveGame) - **2-3 dias**
> > 6. 🟢 **Outras decisões** (DEC-007, DEC-006, DEC-008) - **1-2 dias cada**
> >
> > **Duração Total:** 1-2 semanas (foco em DEC-001 e DEC-002)
> >
> > **📖 Detalhes Completos:** [Decisões Arquiteturais Críticas](../architecture/arquitetura-decisoes-criticas.md)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>🔄 2. Finalizar Fase 1 (Sistema de Fichas) - DEPOIS</b></summary>
>
> > **Após completar Fase 0:**
> >
> > - 📋 Migrar Fase 1 para usar GAS Attributes (DEC-001, DEC-002)
> > - 📋 Implementar sistema de itens iniciais
> > - 📋 Criar boilerplate de inventário (estruturas modulares)
> > - ⚠️ Validar criação de feat no editor
> > - ⚠️ Corrigir testes de Proficiency Bonus
> > - ⚠️ Testes de integração end-to-end completos
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>📋 3. Iniciar Fase 1.5 (Melhorias D&D 5e) - DEPOIS</b></summary>
>
> > **Após completar Fase 1:**
> >
> > - 📋 1.5.1: Sistema de Spellcasting (1-2 semanas) - 🧪 TDD
> > - 📋 1.5.2: Sistema de ASI (1 semana) - 🧪 TDD
> > - 📋 1.5.3: Level Up System Completo (1 semana) - 🧪 TDD
> > - 📋 1.5.4: Correção de Testes Proficiency Bonus (2-4 horas)
>
> </details>

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Decisões Arquiteturais Críticas](../architecture/arquitetura-decisoes-criticas.md)** - 🔴 **CRÍTICO** - Todas as decisões que precisam ser implementadas
>   - **[Status de Implementação](../architecture/arquitetura-decisoes-criticas.md#-status-de-implementação)** - Tabela completa de status de cada decisão
>   - **[Checklist de Decisões](../architecture/arquitetura-decisoes-criticas.md#-checklist-de-decisões)** - Checklist detalhado com status real
>   - **[Diagrama de Dependências](../architecture/arquitetura-decisoes-criticas.md#-diagrama-de-dependências)** - Visualização de dependências entre decisões
> - **[Revisão Estrutural - Integração](../architecture/revisao-estrutural-integracao.md)** - Sistemas D&D 5e faltantes e alinhamento com DEC-001 e DEC-002
> - **[Review: Metodologia Ágil Solo Dev](../../technical/reviews/REVIEW-METODOLOGIA-AGIL-SOLO-DEV.md)** - 🔴 **CRÍTICO** - Alinhamento com metodologias ágeis
> - **[Validação de Data Tables](../validation/data-tables-validation.md)** - Checklist detalhado para validação

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 6.0 - Renumerado para refletir ordem de implementação
**Melhorias:**


- Numeração reorganizada: DEC-001 (1º) → DEC-002 (2º) → DEC-003 (3º) → etc.
- Ordem de implementação agora reflete a numeração
- Todas as referências atualizadas
- Alinhado com Status de Implementação e Diagrama de Dependências
