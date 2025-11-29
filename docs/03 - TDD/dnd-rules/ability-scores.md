---
title: "Ability Scores"
category: design
subcategory: dnd-rules
tags: [ability-scores, attributes, modifiers, dnd-5e]
last_updated: 2024-12-27
difficulty: beginner
related: [point-buy.md, character-creation.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../index.md) > [Regras D&D 5e](dnd-rules/index.md) > Ability Scores

# Ability Scores - D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Documentação algorítmica dos Ability Scores (Atributos) no D&D 5e.
>

</details>

## 📋 Ability Names

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Os 6 Atributos</b></summary>

> - **Strength (STR)** - Força
> - **Dexterity (DEX)** - Destreza
> - **Constitution (CON)** - Constituição
> - **Intelligence (INT)** - Inteligência
> - **Wisdom (WIS)** - Sabedoria
> - **Charisma (CHA)** - Carisma
>

</details>

## 🧮 Modifier Calculation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Fórmula do Modificador</b></summary>

> ```
> Modifier = floor((Score - 10) / 2)
> ```
>

> **Exemplos:**
> - Score 8 → Modifier = -1
> - Score 10 → Modifier = 0
> - Score 12 → Modifier = +1
> - Score 14 → Modifier = +2
> - Score 16 → Modifier = +3
> - Score 18 → Modifier = +4
> - Score 20 → Modifier = +5
>
</details>
---

## 📊 Score Ranges

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Faixas de Valores</b></summary>

> - **BASE_ABILITY_SCORE:** 8 (constante fixa do sistema)
> - **Point Buy Allocation:** 0-7 (alocação adicional ao base)
> - **Resulting Score (Point Buy):** 8-15 (BASE_ABILITY_SCORE + PointBuyAllocation)
> - **After Racial Bonuses:** 8-17 (tipicamente, máximo 17 com bônus +2)
> - **Maximum (with ASI):** 20 (limite máximo de D&D 5e)
>

> **⚠️ IMPORTANTE:**
> - Point Buy não pode resultar em score > 15 (antes de bônus raciais)
> - Bônus raciais são aplicados após Point Buy
> - ASI pode aumentar até 20 durante level up
>
</details>
---

## 🔢 Final Score Formula

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Cálculo do Score Final</b></summary>

> ```
> FinalScore = BASE_ABILITY_SCORE + RacialBonuses + PointBuyAllocation + ASI
> ```
>

> **Ordem de Aplicação (conforme implementação):**
> 1. **BASE_ABILITY_SCORE:** Valor base fixo = **8** (reset inicial)
> 2. **RacialBonuses:** Bônus da raça/sub-raça (incrementa após reset)
> 3. **PointBuyAllocation:** Alocação do Point Buy (0-7, incrementa após bônus raciais)
> 4. **ASI:** Ability Score Improvements (de level up, aplicado após Point Buy)
>
> **⚠️ IMPORTANTE:** Matematicamente a ordem não importa (é comutativa), mas a implementação segue esta ordem para consistência.
>
> **Exemplo:**
> - Reset: 8 (BASE_ABILITY_SCORE)
> - Racial: +2 (Dwarf Constitution) → 10
> - Point Buy: +7 (alocação para Strength) → 15
> - **Final Strength:** 8 + 0 (racial) + 7 (point buy) = 15
> - **Final Constitution:** 8 + 2 (racial) + 0 (point buy) = 10
>
> **📖 Ver também:** [gas-dnd-adaptation.md](../gas-dnd-adaptation.md) - Como funciona no sistema
>
</details>
---

## ⬆️ Ability Score Improvements (ASI)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Níveis de ASI</b></summary>

> **Classes recebem ASI nos níveis:** 4, 8, 12, 16, 19
>

> **Opções:**
> - +2 em um atributo **OU**
> - +1 em dois atributos
>
> **Exceções:**
> - **Fighter/Rogue** recebem ASI extra nos níveis: 6, 10, 14
>
</details>
---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Point Buy System](point-buy.md)** - Como distribuir pontos inicialmente
> - **[Raças e Sub-raças](races.md)** - Bônus raciais
> - **[Level Up](level-up.md)** - ASI durante progressão
>

</details>