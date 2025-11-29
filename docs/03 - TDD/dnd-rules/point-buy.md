---
title: "Point Buy System"
category: design
subcategory: dnd-rules
tags: [point-buy, ability-scores, dnd-5e, character-creation]
last_updated: 2024-12-27
difficulty: intermediate
related: [ability-scores.md, character-creation.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../index.md) > [Regras D&D 5e](dnd-rules/index.md) > Point Buy

# Point Buy System - D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Sistema de distribuição de pontos (Point Buy) para ability scores iniciais no D&D 5e.
>

</details>

## 💰 Cost Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Tabela de Custos</b></summary>

> | Ability Score | Cost |
> |---------------|------|
> | 8             | 0    |
> | 9             | 1    |
> | 10            | 2    |
> | 11            | 3    |
> | 12            | 4    |
> | 13            | 5    |
> | 14            | 7    |
> | 15            | 9    |
>

</details>

## 📜 Rules

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Regras do Sistema</b></summary>

> - **Starting points:** 27
> - **Base ability score:** 8 (BASE_ABILITY_SCORE - constante do sistema)
> - **Point Buy allocation range:** 0-7 (alocação adicional ao base)
> - **Resulting score range:** 8-15 (BASE_ABILITY_SCORE + PointBuyAllocation)
> - **Maximum score before racial bonuses:** 15
> - **All 6 abilities start at:** 8 (BASE_ABILITY_SCORE)
> - **Total cost must equal:** 27 (exatamente, não pode sobrar ou faltar)
>

> **⚠️ IMPORTANTE:** Point Buy é uma **alocação adicional** ao valor base (8), não um valor absoluto. O sistema calcula: `FinalScore = BASE_ABILITY_SCORE (8) + PointBuyAllocation (0-7)`.
>
</details>
---

## ✅ Validation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Validação</b></summary>

> ```pseudocode
> AvailablePoints = 27 - sum(cost for each ability)
> Valid if: AvailablePoints == 0 AND all scores >= 8 AND all scores <= 15
> ```
>

</details>

## 🧮 Calculation Function

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Função de Cálculo</b></summary>

> ```pseudocode
> function CalculateCost(score):
> if score == 8: return 0
> if score >= 9 && score <= 13: return score - 8
> if score == 14: return 7
> if score == 15: return 9
> ```
>

</details>

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Ability Scores](ability-scores.md)** - Como os scores são usados
> - **[Raças e Sub-raças](races.md)** - Bônus aplicados após Point Buy
>

</details>