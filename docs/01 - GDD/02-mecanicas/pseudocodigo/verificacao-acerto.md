# Pseudocódigo - Verificação de Acerto

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Verificação de Acerto</b></summary>

> Pseudocódigo para verificação de acerto em ataques, incluindo críticos, vantagem/desvantagem e modificadores, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo

```
FUNCTION CheckAttackHit(Attacker, Target, Weapon)
    // Rolar d20
    d20Roll = RollD20()
    isCritical = (d20Roll == 20)
    isCriticalMiss = (d20Roll == 1)

    IF isCriticalMiss THEN
        RETURN MISS  // Sempre erra
    END IF

    IF isCritical THEN
        RETURN CRITICAL_HIT  // Sempre acerta, dano crítico
    END IF

    // Calcular modificadores de ataque
    proficiencyBonus = GetProficiencyBonus(Attacker)
    isProficient = IsProficientWithWeapon(Attacker, Weapon)

    IF Weapon.Type == MELEE THEN
        abilityModifier = GetStrengthModifier(Attacker)
    ELSE IF Weapon.Type == RANGED THEN
        abilityModifier = GetDexterityModifier(Attacker)
    END IF

    attackBonus = abilityModifier
    IF isProficient THEN
        attackBonus = attackBonus + proficiencyBonus
    END IF

    // Aplicar vantagem/desvantagem
    IF HasAdvantage(Attacker) THEN
        d20Roll2 = RollD20()
        d20Roll = MAX(d20Roll, d20Roll2)
    ELSE IF HasDisadvantage(Attacker) THEN
        d20Roll2 = RollD20()
        d20Roll = MIN(d20Roll, d20Roll2)
    END IF

    // Calcular roll total
    attackRoll = d20Roll + attackBonus

    // Obter AC do alvo
    targetAC = CalculateAC(Target)

    // Verificar se acertou
    IF attackRoll >= targetAC THEN
        RETURN HIT
    ELSE
        RETURN MISS
    END IF
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Natural 1:** Sempre erra (critical miss)
- **Natural 20:** Sempre acerta (critical hit)
- **Attack Roll:** d20 + Proficiency Bonus (se proficiente) + Ability Modifier
- **Vantagem:** Rola 2d20, usa o maior
- **Desvantagem:** Rola 2d20, usa o menor
- **Acerto:** Attack Roll >= Target AC

---

## 📖 Referências

- **GDD:** [Sistema de Combate - Ataques](../02-mecanicas/sistema-combate.md#-ataques-e-acertos)
- **D&D 5e:** Player's Handbook - Attack Rolls

---

**Navegação:** [← Voltar ao Índice](index.md)
