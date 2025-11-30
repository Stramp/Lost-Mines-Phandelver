# Pseudocódigo - Cálculo de Atributos Finais

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Cálculo de Atributos Finais</b></summary>

> Pseudocódigo para cálculo de atributos finais (base + racial + point buy + ASI) e modificadores, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo - Cálculo de Atributo Final

```
FUNCTION CalculateFinalAbilityScore(Character, AbilityType)
    // 1. Valor base fixo
    baseScore = 8

    // 2. Bônus racial
    race = Character.GetRace()
    racialBonus = GetRacialAbilityBonus(race, AbilityType)

    // 3. Alocação do Point Buy
    pointBuyAllocation = GetPointBuyAllocation(Character, AbilityType)

    // 4. ASI (Ability Score Improvements de level up)
    asiBonus = GetASIBonus(Character, AbilityType)

    // 5. Calcular score final
    finalScore = baseScore + racialBonus + pointBuyAllocation + asiBonus

    // Limite máximo: 20 (sem itens mágicos)
    finalScore = MIN(finalScore, 20)

    RETURN finalScore
END FUNCTION
```

---

## Pseudocódigo - Cálculo de Modificador

```
FUNCTION CalculateAbilityModifier(AbilityScore)
    // Fórmula D&D 5e: floor((Score - 10) / 2)
    modifier = FLOOR((AbilityScore - 10) / 2)
    RETURN modifier
END FUNCTION
```

---

## Pseudocódigo - Recalcular Stats Derivados

```
FUNCTION RecalculateDerivedStats(Character)
    // Recalcular todos os valores derivados após mudança de atributos

    FOR EACH ability IN [STR, DEX, CON, INT, WIS, CHA] DO
        finalScore = CalculateFinalAbilityScore(Character, ability)
        modifier = CalculateAbilityModifier(finalScore)
        Character.SetAbilityScore(ability, finalScore)
        Character.SetAbilityModifier(ability, modifier)
    END FOR

    // Recalcular HP máximo (se CON mudou)
    RecalculateMaxHP(Character)

    // Recalcular AC (se DEX mudou)
    RecalculateAC(Character)

    // Recalcular Spell Save DC (se spellcasting ability mudou)
    IF IsSpellcaster(Character) THEN
        spellcastingAbility = GetSpellcastingAbility(Character.GetPrimaryClass())
        proficiencyBonus = Character.GetProficiencyBonus()
        abilityModifier = Character.GetAbilityModifier(spellcastingAbility)
        spellSaveDC = 8 + proficiencyBonus + abilityModifier
        Character.SetSpellSaveDC(spellSaveDC)
    END IF
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Base Score:** 8 (valor inicial para todos os atributos)
- **Racial Bonus:** +2 em um atributo, +1 em outro (varia por raça)
- **Point Buy:** Alocação de 27 pontos (sistema Point Buy D&D 5e)
- **ASI:** +2 em um atributo OU +1 em dois atributos (níveis 4, 8, 12, 16, 19)
- **Limite Máximo:** 20 (sem itens mágicos)
- **Modificador:** floor((Score - 10) / 2)

---

## 📖 Referências

- **GDD:** [Sistemas de Personagem - Atributos](../02-mecanicas/sistemas-personagem.md#-atributos-ability-scores)
- **D&D 5e:** Player's Handbook - Ability Scores

---

**Navegação:** [← Voltar ao Índice](index.md)
