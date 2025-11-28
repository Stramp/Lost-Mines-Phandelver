---
title: "Level Up System"
category: design
subcategory: dnd-rules
tags: [level-up, features, character-progression, dnd-5e]
last_updated: 2024-12-27
difficulty: intermediate
related: [multiclassing.md, character-creation.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Design](../design/index.md) > [Regras D&D 5e](dnd-rules/index.md) > Level Up

# Level Up System - D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Sistema de level up e features no D&D 5e.
>

</details>

## 📈 Level Progression

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⬆️ Progressão de Níveis</b></summary>

> - **Level 1:** Class features at level 1
> - **Levels 2-20:** Features unlock at specific levels per class
> - **ASI at:** 4, 8, 12, 16, 19 (some classes get extra)
>

</details>

## 🎯 Feature Unlocking

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔓 Desbloqueio de Features</b></summary>

> ```
> function GetFeaturesAtLevel(className, level):
> features = []
> classData = GetClassData(className)
> for feature in classData.Features:
> if feature.LevelUnlocked <= level:
> features.add(feature)
> return features
> ```
>

</details>

## ❤️ Hit Points

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💚 Cálculo de HP</b></summary>

> ```
> Level1HP = HitDie + Constitution Modifier
> Level2PlusHP = (HitDie / 2) + 1 + Constitution Modifier (ou rolagem)
> MaxHP = sum of all level HP gains
> ```
>

> **Exemplo (Fighter, CON +2):**
> - **Level 1:** 10 (d10) + 2 = 12 HP
> - **Level 2:** 6 (d10/2 + 1) + 2 = 8 HP adicional → Total: 20 HP
> - **Level 3:** 6 + 2 = 8 HP adicional → Total: 28 HP
>
> **⚠️ IMPORTANTE:** Constitution Modifier é calculado a partir do Final Constitution Score (BASE_ABILITY_SCORE + PointBuy + Racial + ASI).
>
</details>
---

## 📊 Proficiency Bonus

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Bônus de Proficiência</b></summary>

> | Total Level | Proficiency Bonus |
> |-------------|-------------------|
> | 1-4         | +2                |
> | 5-8         | +3                |
> | 9-12        | +4                |
> | 13-16       | +5                |
> | 17-20       | +6                |
>

> **Fórmula:**
> ```
> ProficiencyBonus = 2 + floor((TotalLevel - 1) / 4)
> ```
>
> **⚠️ IMPORTANTE:** Proficiency Bonus é baseado no **Total Level** (soma de todos os níveis de classes), não no nível de uma classe específica.
>
> **Exemplo (Fighter 3 / Rogue 2):**
> - Total Level = 5
> - Proficiency Bonus = +3 (níveis 5-8)
>
> **📖 Ver também:** [multiclassing.md](multiclassing.md) - Cálculo de Total Level
>
</details>
---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Ability Scores](ability-scores.md)** - ASI durante level up
> - **[Multiclassing](multiclassing.md)** - Level up em múltiplas classes
>

</details>