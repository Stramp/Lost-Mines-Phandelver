---
title: "Multiclassing"
category: design
subcategory: dnd-rules
tags: [multiclassing, classes, dnd-5e, character-progression]
last_updated: 2024-12-27
difficulty: intermediate
related: [character-creation.md, level-up.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Design](../design/index.md) > [Regras D&D 5e](dnd-rules/index.md) > Multiclassing

# Multiclassing - D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Regras de multiclassing (multi-classing) no D&D 5e.
>

</details>

## 📊 Level Calculation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🧮 Cálculo de Nível Total</b></summary>

> ```
> TotalLevel = sum(levels in all classes)
> MaximumTotalLevel = 20
> ```
>

</details>

## ⚖️ Prerequisites

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Pré-requisitos por Classe</b></summary>

> Each class has ability score prerequisites. Must meet prerequisites for BOTH current class AND new class.
>

> **⚠️ IMPORTANTE:** Pré-requisitos são baseados nos **Final Ability Scores** (BASE_ABILITY_SCORE + Racial + PointBuy + ASI), não apenas no Point Buy.
>
> **Exemplo:**
> - Fighter requer STR 13 OU DEX 13
> - Personagem com STR 15 (BASE 8 + Racial +2 + PointBuy +5) → ✅ Pode multiclassar para Fighter
> - Personagem com STR 12 (BASE 8 + PointBuy +4, sem bônus racial) → ❌ Não pode multiclassar para Fighter
>
> | Class | Prerequisites |
> |-------|---------------|
> | Barbarian | Strength 13 |
> | Bard | Charisma 13 |
> | Cleric | Wisdom 13 |
> | Druid | Wisdom 13 |
> | Fighter | Strength 13 **OR** Dexterity 13 |
> | Monk | Dexterity 13 **AND** Wisdom 13 |
> | Paladin | Strength 13 **AND** Charisma 13 |
> | Ranger | Dexterity 13 **AND** Wisdom 13 |
> | Rogue | Dexterity 13 |
> | Sorcerer | Charisma 13 |
> | Warlock | Charisma 13 |
> | Wizard | Intelligence 13 |
>
</details>
---

## ✅ Validation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Validação de Multiclassing</b></summary>

> ```
> CanMulticlassTo(newClass) =
> MeetsPrerequisite(currentClass) AND MeetsPrerequisite(newClass)
> ```
>

</details>

## 🎯 Feature Calculation

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Cálculo de Features</b></summary>

> ```
> AvailableFeatures = []
> for each class in ClassLevels:
> classFeatures = GetClassFeatures(className)
> for feature in classFeatures:
> if feature.LevelUnlocked <= ClassLevels[className]:
> AvailableFeatures.add(feature)
> ```
>

</details>

## 🛡️ Proficiencies

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Proficiências ao Multiclassar</b></summary>

> When gaining first level in new class, you get **LIMITED proficiencies** (not all starting proficiencies):
>

</details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Armor and Weapon Proficiencies</summary>

    > | Class | Armor | Weapons | Shields |
    > |-------|-------|---------|---------|
    > | Barbarian | Light, Medium | Simple, Martial | No |
    > | Bard | Light | Simple, Hand Crossbow, Longsword, Rapier, Shortsword | No |
    > | Cleric | Light, Medium | Simple | Yes |
    > | Druid | Light, Medium (no metal) | Simple (clubs, daggers, darts, javelins, maces, quarterstaffs, scimitars, sickles, slings, spears) | Yes (no metal) |
    > | Fighter | Light, Medium, Heavy | Simple, Martial | Yes |
    > | Monk | None | Simple, Shortsword | No |
    > | Paladin | Light, Medium, Heavy | Simple, Martial | Yes |
    > | Ranger | Light, Medium | Simple, Martial | Yes |
    > | Rogue | Light | Simple, Hand Crossbow, Longsword, Rapier, Shortsword | No |
    > | Sorcerer | None | Simple (daggers, darts, slings, quarterstaffs, light crossbows) | No |
    > | Warlock | Light | Simple | No |
    > | Wizard | None | Simple (daggers, darts, slings, quarterstaffs, light crossbows) | No |

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Skill Proficiencies</summary>

    > - Gain proficiency in **ONE skill** from new class's skill list
    > - Exception: Rogue multiclass gains proficiency in ONE skill from Rogue list

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Tool Proficiencies</summary>

    > - Some classes grant tool proficiencies (check class description)

    </details>

    </details>

## 🔮 Spell Slots (if multiclassing spellcasters)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Cálculo de Spell Slots</b></summary>

> ### Caster Level Calculation
>

> Combine caster levels from different classes:
> - **Full Caster** (Bard, Cleric, Druid, Sorcerer, Wizard): Counts as 1 level
> - **Half Caster** (Paladin, Ranger): Counts as 0.5 level (rounded down)
> - **Warlock**: Separate (Pact Magic, does NOT combine)
>
> ```
> CasterLevel = FullCasterLevels + floor(HalfCasterLevels / 2)
> ```
>
</details>
    ### Full Casters
    - Bard, Cleric, Druid, Sorcerer, Wizard

    ### Half Casters
    - Paladin, Ranger

    ### Special Case: Warlock
    - Pact Magic slots are separate
    - Do NOT combine with other spell slots
    - Recover on short rest (not long rest)

    ### Example
    - Wizard 3 + Paladin 2
    - CasterLevel = 3 + floor(2/2) = 3 + 1 = 4
    - Use spell slot table for level 4 caster

    **📖 See [spellcasting.md](spellcasting.md) for full spell slot tables.**

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentos Relacionados</b></summary>

> - **[Spellcasting](spellcasting.md)** - Spell slots em multiclassing
> - **[Level Up](level-up.md)** - Features por nível
>

</details>