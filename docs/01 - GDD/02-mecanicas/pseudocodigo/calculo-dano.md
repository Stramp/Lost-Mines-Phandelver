# Pseudocódigo - Cálculo e Aplicação de Dano

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💥 Cálculo de Dano</b></summary>

> Pseudocódigo para cálculo de dano de armas, incluindo críticos, resistências e vulnerabilidades, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo - Cálculo de Dano

```
FUNCTION CalculateDamage(Attacker, Target, Weapon, IsCritical)
    // Calcular dano base da arma
    weaponDie = GetWeaponDie(Weapon)
    weaponRoll = RollDice(weaponDie)

    IF IsCritical THEN
        // Crítico: rola dados novamente (dobra)
        weaponRoll = weaponRoll + RollDice(weaponDie)
    END IF

    // Adicionar modificador de atributo
    IF Weapon.Type == MELEE THEN
        abilityModifier = GetStrengthModifier(Attacker)
    ELSE IF Weapon.Type == RANGED THEN
        abilityModifier = GetDexterityModifier(Attacker)
    END IF

    baseDamage = weaponRoll + abilityModifier

    // Aplicar tipo de dano
    damageType = GetWeaponDamageType(Weapon)

    // Verificar resistências e vulnerabilidades
    IF Target.HasResistance(damageType) THEN
        baseDamage = FLOOR(baseDamage / 2)  // Reduzido pela metade
    ELSE IF Target.HasVulnerability(damageType) THEN
        baseDamage = baseDamage * 2  // Dobrado
    END IF

    // Aplicar dano ao alvo
    ApplyDamage(Target, baseDamage, damageType)

    RETURN baseDamage
END FUNCTION
```

---

## Pseudocódigo - Aplicação de Dano

```
FUNCTION ApplyDamage(Target, DamageAmount, DamageType)
    currentHP = Target.GetCurrentHP()
    newHP = currentHP - DamageAmount

    IF newHP <= 0 THEN
        newHP = 0
        Target.SetState(UNCONSCIOUS)
        // Verificar morte (se aplicável)
        IF Target.FailsDeathSavingThrows() THEN
            Target.SetState(DEAD)
        END IF
    END IF

    Target.SetCurrentHP(newHP)

    // Feedback visual/sonoro
    ShowDamageNumber(Target, DamageAmount, DamageType)
    PlayDamageSound(DamageType)
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Dano Melee:** Weapon Die + STR modifier
- **Dano Ranged:** Weapon Die + DEX modifier
- **Crítico:** Natural 20 = dobra todos os dados de dano
- **Resistência:** Dano reduzido pela metade (arredondado para baixo)
- **Vulnerabilidade:** Dano dobrado
- **HP <= 0:** Criatura fica inconsciente (Unconscious)

---

## 📖 Referências

- **GDD:** [Sistema de Combate - Dano](../02-mecanicas/sistema-combate.md#-cálculo-de-dano)
- **D&D 5e:** Player's Handbook - Damage and Healing

---

**Navegação:** [← Voltar ao Índice](index.md)
