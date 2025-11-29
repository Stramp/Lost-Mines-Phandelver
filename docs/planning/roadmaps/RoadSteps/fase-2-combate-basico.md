---
title: "Fase 2: Combate Básico com GAS"
category: planning
tags: [roadmap, phase, combat, gas, planned]
last_updated: 2024-12-27
difficulty: advanced
related: [../../roadmap.md, ../../architecture/arquitetura-decisoes-criticas.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../../index.md) > [Planejamento](../index.md) > [Roadmap](../roadmap.md) > Fase 2

# Fase 2: Combate Básico com GAS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔴 Resumo Executivo</b></summary>

> **Status:** 📋 **Planejado** - **BLOQUEADO por Fase 0**
>
> **Objetivo:** Implementar sistema de combate básico usando GAS desde o início
>
> **Prioridade:** 🔴 **Alta** - Base para gameplay
>
> **Duração Estimada:** 2-3 semanas (80-120 horas)
>
> **⚠️ CRÍTICO:** Esta fase depende de Fase 0 (DEC-001, DEC-010) e Fase 1.5 (Spellcasting, ASI).

</details>

---

## 📋 Componentes Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Sistema de Combate</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>1. GAS AttributeSet (C++)</b></summary>
>
> > **Status:** ✅ Base já implementada em Fase 0 (DEC-001)
> >
> > **O que adicionar:**
> >
> > - Health, MaxHealth (já em DEC-001)
> > - Meta-Attributes para processamento de dano:
> >   - `Damage` (temporary) - Dano recebido
> >   - `Healing` (temporary) - Cura recebida
> > - `PostGameplayEffectExecute` para lógica de dano:
> >   - Aplicar dano a Health
> >   - Aplicar cura a Health
> >   - Verificar morte (Health <= 0)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>2. GAS Ability System Component</b></summary>
>
> > **Status:** ✅ Base já implementada em Fase 0 (DEC-010)
> >
> > **O que adicionar:**
> >
> > - ASC no PlayerState (Player) - ✅ Já configurado
> > - ASC no Character (AI) - ✅ Já configurado
> > - InitAbilityActorInfo configurado - ✅ Já configurado
> > - Preparação para Gameplay Effects e Abilities
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>3. CombatComponent</b></summary>
>
> > **O que implementar:**
> >
> > - `UCombatComponent` (herda de `UActorComponent`)
> > - Calcular AC (10 + Dex Mod + Armor):
> >   - `CalculateArmorClass()` - Calcula AC baseado em armadura e Dex Mod
> > - Calcular dano de ataque (weapon dice + ability modifier):
> >   - `CalculateAttackRoll()` - Calcula rolagem de ataque (d20 + ability mod + proficiency)
> >   - `CalculateDamage()` - Calcula dano (weapon dice + ability modifier)
> > - Aplicar dano via Gameplay Effects:
> >   - `ApplyDamage(float DamageAmount, EDamageType DamageType)`
> >   - `ApplyHealing(float HealingAmount)`
> > - Sistema de ações básico:
> >   - `Attack(AActor* Target)` - Ataque básico
> >   - `Dodge()` - Ação de esquiva
> >   - `Dash()` - Ação de dash
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>4. Gameplay Effects Básicos</b></summary>
>
> > **O que implementar:**
> >
> > - **GE_Damage (Instant):**
> >   - Aplicar dano a Health
> >   - Suporta diferentes tipos de dano (Fire, Cold, Slashing, etc.)
> >   - Modificadores baseados em resistências/vulnerabilidades
> >
> > - **GE_Heal (Instant):**
> >   - Aplicar cura a Health
> >   - Não pode exceder MaxHealth
> >
> > - **GE_Death (Infinite):**
> >   - Estado de morte
> >   - Aplicado quando Health <= 0
> >   - Remove todas as abilities ativas
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;"><b>5. CombatHelpers (em `Utils/`) - 🧪 TDD</b></summary>
>
> > **O que implementar (TDD obrigatório):**
> >
> > - `CalculateArmorClass(int32 DexterityModifier, int32 ArmorBonus, int32 ShieldBonus)` - Calcula AC
> > - `CalculateAttackRoll(int32 AbilityModifier, int32 ProficiencyBonus, bool bHasAdvantage, bool bHasDisadvantage)` - Calcula rolagem de ataque
> > - `CalculateDamage(int32 WeaponDiceCount, int32 WeaponDiceSides, int32 AbilityModifier)` - Calcula dano
> > - `RollD20(bool bHasAdvantage, bool bHasDisadvantage)` - Rola d20 (usa DiceRolls module)
> >
> > **Testes:**
> >
> > - 30-40 testes automatizados (TDD)
> > - Cobertura completa de todas as funções
>
> </details>

</details>

---

## 🔗 Dependências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 Bloqueios Críticos</b></summary>

> **Fase 2 está BLOQUEADA por:**
>
> - 🔴 **Fase 0 (DEC-001, DEC-010)** - **BLOQUEADOR CRÍTICO**
>   - Precisa de GAS Attributes (DEC-001)
>   - Precisa de ASC base (DEC-010)
>   - Precisa de Gameplay Tags (DEC-008)
>
> - 📋 **Fase 1 (Sistema de Fichas)** - Para ability scores e modifiers (já em GAS após Fase 0)
>
> - 📋 **Fase 1.5 (Melhorias D&D 5e)** - Para spellcasting e ASI
>   - Spellcasting (1.5.1) - Para magias em combate
>   - ASI (1.5.2) - Para ability score improvements
>
> **Fase 2 bloqueia:**
>
> - 📋 **Fase 3** - Teste de Combate Inicial

</details>

---

## 🎯 Entregas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ O Que Será Entregue</b></summary>

> - ✅ Sistema de combate funcional com GAS
> > - Health/MaxHealth via AttributeSet
> > - Aplicação de dano via Gameplay Effects
> > - Sistema de morte básico
> > - Ações básicas (Attack, Dodge, Dash)
> > - Cálculo de AC, Attack Roll, Damage
> > - CombatHelpers com testes (TDD)
> > - Integração com ability scores (GAS Attributes)
> > - Suporte a diferentes tipos de dano
> > - Sistema de resistências/vulnerabilidades básico

</details>

---

## 📊 Estimativas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Duração Estimada</b></summary>

> **Duração Total:** 2-3 semanas (80-120 horas)
>
> **Breakdown:**
>
> - CombatComponent: 1 semana (40 horas)
> - Gameplay Effects: 3-5 dias (24-40 horas)
> - CombatHelpers + Testes: 2-3 dias (16-24 horas)
> - Integração e testes: 2-3 dias (16-24 horas)
>
> **Total:** 2-3 semanas (96-128 horas)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Roadmap Completo](../roadmap.md)** - Visão geral de todas as fases
> - **[Fase 0: Decisões Arquiteturais](./fase-0-decisoes-arquiteturais.md)** - Bloqueador crítico
> - **[Fase 1.5: Melhorias D&D 5e](./fase-1.5-melhorias-dnd.md)** - Pré-requisito
> - **[Decisões Arquiteturais](../../architecture/arquitetura-decisoes-criticas.md)** - DEC-001, DEC-010

</details>

---

**Última atualização:** 2024-12-27
**Status:** 📋 Planejado (bloqueado por Fase 0)
