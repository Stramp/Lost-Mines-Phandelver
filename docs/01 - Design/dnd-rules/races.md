---
title: "Races and Subraces"
category: design
subcategory: dnd-rules
tags: [races, subraces, racial-bonuses, dnd-5e]
last_updated: 2024-12-27
difficulty: beginner
related: [character-creation.md, ability-scores.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Design](../design/index.md) > [Regras D&D 5e](dnd-rules/index.md) > Races

# Race and Subrace - D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Estrutura e regras de raças e sub-raças no D&D 5e.
>

</details>

## 🏗️ Structure

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Estrutura Hierárquica</b></summary>

> ```
> Race
> ├── Base Race (e.g., "Elf")
> │   ├── Ability Score Improvements
> │   ├── Base Traits
> │   └── Subraces: ["High Elf", "Wood Elf", "Drow"]
> └── Subrace (selected from parent race)
> ├── Additional Ability Score Improvements
> └── Additional Traits
> ```
>

</details>

## 📋 Selection Rules

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Regras de Seleção</b></summary>

> - **Must select Race first** - Raça deve ser selecionada primeiro
> - **Subrace dropdown filtered by selected Race** - Sub-raças filtradas pela raça
> - **Subrace can be "None"** - Se raça não tem sub-raças
> - **Final bonuses = Race bonuses + Subrace bonuses** - Bônus finais são somados
>

</details>

## 🧮 Ability Score Bonuses

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Fórmula de Bônus</b></summary>

> ```
> FinalAbilityScore = BASE_ABILITY_SCORE + RaceBonuses + SubraceBonuses + PointBuyAllocation
> ```
>

> **Ordem de Aplicação (conforme implementação):**
> 1. **BASE_ABILITY_SCORE:** Valor base fixo = 8 (reset inicial)
> 2. **RaceBonuses:** Bônus da raça base (ex: Elf +2 DEX) - incrementa após reset
> 3. **SubraceBonuses:** Bônus da sub-raça (ex: High Elf +1 INT) - incrementa após raça base
> 4. **PointBuyAllocation:** Alocação do Point Buy (0-7) - incrementa após bônus raciais
>
> **⚠️ IMPORTANTE:**
> - A implementação aplica bônus raciais **ANTES** do Point Buy (ordem: Reset → Race → Point Buy)
> - Matematicamente a ordem não importa (é comutativa), mas a implementação segue esta ordem
>
> **📖 Ver também:** [ability-scores.md](ability-scores.md) - Fórmula completa de cálculo
>
</details>
---

## 💡 Example: Elf

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌳 Exemplo Prático</b></summary>

> - **Race:** Elf → +2 DEX
> - **Subrace:** High Elf → +1 INT
> - **Total:** +2 DEX, +1 INT
>

</details>

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Ability Scores](ability-scores.md)** - Como os bônus são aplicados
> - **[Character Creation](character-creation.md)** - Ordem de criação
>

</details>