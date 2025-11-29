---
title: "Fase 1.5: Melhorias D&D 5e"
category: planning
tags: [roadmap, phase, dnd-improvements, planned]
last_updated: 2024-12-27
difficulty: intermediate
related: [../../roadmap.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../../index.md) > [Planejamento](../index.md) > [Roadmap](../roadmap.md) > Fase 1.5

# Fase 1.5: Melhorias D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Resumo Executivo</b></summary>

> **Status:** 📋 **Planejado** - Aguardando conclusão de Fase 1
>
> **Objetivo:** Completar sistemas D&D 5e documentados mas não implementados
>
> **Prioridade:** 🔴 **Alta** - Essencial para fidelidade às regras D&D 5e
>
> **Duração Estimada:** 3-4 semanas
>
> **Metodologia:** 🧪 **TDD obrigatório** para todas as funções helper/motor

</details>

---

## 🔴 1.5.1 - Sistema de Spellcasting

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Sistema de Spellcasting (1-2 semanas)</b></summary>

> **Prioridade:** 🔴 Alta - Base para Fase 2 (Combate)
>
> **Duração:** 1-2 semanas (40-80 horas)
>
> **Entregas:**
>
> - 📋 **SpellcastingHelpers** (em `Utils/`):
>   - `CalculateSpellSaveDC(int32 SpellcastingAbilityModifier, int32 ProficiencyBonus)`
>   - `CalculateSpellAttackModifier(int32 SpellcastingAbilityModifier, int32 ProficiencyBonus)`
>   - `CalculateSpellSlots(int32 ClassLevel, EClass SpellcastingClass)`
>   - `CalculateCantripsKnown(int32 ClassLevel, EClass SpellcastingClass)`
>   - `CalculateSpellsPrepared(int32 ClassLevel, int32 SpellcastingAbilityModifier, EClass SpellcastingClass)`
>
> - 📋 **SpellcastingConstants** (em `DnDConstants.h`):
>   - Tabelas de Spell Slots por nível
>   - Tabelas de Cantrips Known por nível
>   - Regras de preparação de magias
>
> - 📋 **Testes Automatizados:**
>   - 50-70 testes (TDD obrigatório)
>   - Cobertura completa de todas as funções
>
> - 📋 **Integração:**
>   - Integração com `CharacterSheetDataAsset`
>   - Integração com `SpellDataTable`
>   - Cálculo automático baseado em classe e nível
>
> **📖 Referência:** [roadmap-funcional.md](../../roadmap-funcional.md) - FUNC-003: Sistema de Spellcasting

</details>

---

## 🔴 1.5.2 - Sistema de ASI

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Sistema de ASI (1 semana)</b></summary>

> **Prioridade:** 🔴 Alta - Essencial para progressão de personagem
>
> **Duração:** 1 semana (40 horas)
>
> **Entregas:**
>
> - 📋 **ASIHelpers** (em `Utils/`):
>   - `GetASILevelsForClass(EClass Class)` - Retorna níveis que ganham ASI (4, 8, 12, 16, 19)
>   - `CanTakeASIAtLevel(int32 Level, EClass Class)` - Valida se pode tomar ASI
>   - `GetAvailableASIOptions()` - Retorna opções (ability score +2, ability score +1/+1, feat)
>   - `ValidateASISelection(FASIOption Selection)` - Valida seleção
>
> - 📋 **ASIStructs:**
>   - `FASIOption` - Opção de ASI (ability score improvement ou feat)
>   - `FASIEntry` - Entrada de ASI tomada (nível, opção escolhida)
>
> - 📋 **Testes Automatizados:**
>   - 30-40 testes (TDD obrigatório)
>   - Cobertura completa de todas as funções
>
> - 📋 **Integração:**
>   - Integração com `CharacterSheetDataAsset`
>   - Validação de ASI por classe e nível
>
> **📖 Referência:** [roadmap-funcional.md](../../roadmap-funcional.md) - FUNC-004: Sistema de ASI

</details>

---

## 🟡 1.5.3 - Level Up System Completo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟡 Level Up System Completo (1 semana)</b></summary>

> **Prioridade:** 🟡 Média - Importante mas não bloqueante
>
> **Duração:** 1 semana (40 horas)
>
> **Entregas:**
>
> - 📋 **LevelUpMotor** (em `CreateSheet/Core/`):
>   - `ProcessLevelUp(int32 NewLevel, EClass Class)` - Processa level up
>   - `GetAvailableChoicesAtLevel(int32 Level, EClass Class)` - Retorna escolhas disponíveis
>   - `ValidateLevelUp(int32 CurrentLevel, int32 NewLevel, EClass Class)` - Valida level up
>
> - 📋 **LevelUpHelpers** (em `Utils/`):
>   - `CalculateHPGainForLevelUp(int32 Level, EClass Class, int32 ConstitutionModifier)` - Calcula ganho de HP
>   - `GetFeaturesUnlockedAtLevel(int32 Level, EClass Class)` - Retorna features desbloqueadas
>   - `GetSpellSlotsGainedAtLevel(int32 Level, EClass Class)` - Retorna spell slots ganhos
>
> - 📋 **Testes Automatizados:**
>   - 40-50 testes (TDD obrigatório)
>   - Cobertura completa de todas as funções
>
> - 📋 **Integração:**
>   - Integração com `CharacterSheetDataAsset`
>   - Integração com `ClassDataTable` (features por nível)
>   - Integração com sistema de Spellcasting (1.5.1)
>   - Integração com sistema de ASI (1.5.2)
>
> **📖 Referência:** [roadmap-funcional.md](../../roadmap-funcional.md) - FUNC-005: Level Up System

</details>

---

## 🟡 1.5.4 - Correção de Testes Proficiency Bonus

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🟡 Correção de Testes Proficiency Bonus (2-4 horas)</b></summary>

> **Prioridade:** 🟡 Média - Correção de testes existentes
>
> **Duração:** 2-4 horas
>
> **Problema:**
>
> - Testes esperam valores incorretos (base 1 ao invés de base 2)
> - Proficiency Bonus em D&D 5e começa em +2 (nível 1-4)
> - Testes atuais esperam +1 para nível 1
>
> **Solução:**
>
> - Corrigir valores esperados em `CalculationHelpersTests.cpp`
> - Atualizar todos os testes de Proficiency Bonus
> - Validar que testes passam com valores corretos
>
> **Arquivos Afetados:**
>
> - `Source/MyProject2/CreateSheet/Tests/CalculationHelpersTests.cpp`

</details>

---

## 🔗 Dependências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Bloqueios</b></summary>

> **Fase 1.5 está BLOQUEADA por:**
>
> - 🔄 **Fase 1** - Sistema de Fichas (deve estar 100% completo)
> - ✅ **Fase 0.5** - Data Tables (completo)
>
> **Fase 1.5 bloqueia:**
>
> - 📋 **Fase 2** - Combate Básico (precisa de Spellcasting e ASI)

</details>

---

## 📊 Estimativas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Duração Total</b></summary>

> **Duração Total:** 3-4 semanas (120-160 horas)
>
> **Breakdown:**
>
> - 1.5.1: Spellcasting - 1-2 semanas (40-80 horas)
> - 1.5.2: ASI - 1 semana (40 horas)
> - 1.5.3: Level Up System - 1 semana (40 horas)
> - 1.5.4: Correção Testes - 2-4 horas
>
> **Total:** 3-4 semanas (122-164 horas)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Roadmap Completo](../roadmap.md)** - Visão geral de todas as fases
> - **[Fase 1: Sistema de Fichas](./fase-1-sistema-fichas.md)** - Pré-requisito
> - **[Roadmap Funcional](../../roadmap-funcional.md)** - Detalhes de funcionalidades

</details>

---

**Última atualização:** 2024-12-27
**Status:** 📋 Planejado (aguardando Fase 1)
