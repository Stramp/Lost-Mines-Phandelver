# Level Up System - D&D 5e

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Sistema de level up e features no D&D 5e.

</details>

---

## 📈 Level Progression

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⬆️ Progressão de Níveis</b></summary>

> - **Level 1:** Class features at level 1
> - **Levels 2-20:** Features unlock at specific levels per class
> - **ASI at:** 4, 8, 12, 16, 19 (some classes get extra)

</details>

---

## 🎯 Feature Unlocking

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔓 Desbloqueio de Features</b></summary>

> ```
> function GetFeaturesAtLevel(className, level):
>     features = []
>     classData = GetClassData(className)
>     for feature in classData.Features:
>         if feature.LevelUnlocked <= level:
>             features.add(feature)
>     return features
> ```

</details>

---

## ❤️ Hit Points

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💚 Cálculo de HP</b></summary>

> ```
> Level1HP = HitDie + CON modifier
> Level2PlusHP = HitDie/2 + 1 + CON modifier (or roll)
> MaxHP = sum of all level HP gains
> ```

</details>

---

## 📊 Proficiency Bonus

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Bônus de Proficiência</b></summary>

> | Level | Proficiency Bonus |
> |-------|-------------------|
> | 1-4   | +2                |
> | 5-8   | +3                |
> | 9-12  | +4                |
> | 13-16 | +5                |
> | 17-20 | +6                |
>
> ```
> ProficiencyBonus = ceil(TotalLevel / 4) + 1
> ```

</details>

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Ability Scores](ability-scores.md)** - ASI durante level up
> - **[Multiclassing](multiclassing.md)** - Level up em múltiplas classes

</details>
