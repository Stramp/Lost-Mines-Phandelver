# Pseudocódigo - Verificação de Alcance vs. Criatura Voadora

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🦅 Alcance vs. Criaturas Voadoras</b></summary>

> Pseudocódigo para verificação de alcance de ataques contra criaturas voadoras, incluindo regras especiais para armas com Reach.

</details>

---

## Pseudocódigo

```
FUNCTION CanAttackTarget(Attacker, Target, Weapon)
    // Verificar se alvo está voando
    isTargetFlying = IsFlying(Target)
    isAttackerFlying = IsFlying(Attacker)

    // Verificar tipo de arma
    IF Weapon.Type == MELEE THEN
        // Ataque corpo a corpo
        IF isTargetFlying AND NOT isAttackerFlying THEN
            // Alvo voando, atacante não voa
            IF Weapon.HasReach() AND Target.FlyingHeight < 3.0 THEN
                // Arma com alcance pode atingir criatura voadora baixa
                RETURN TRUE
            ELSE
                // Não pode atingir
                ShowMessage("Fora de Alcance - Criatura Voadora")
                RETURN FALSE
            END IF
        ELSE
            // Ambos voando ou ambos terrestres: verifica alcance normal
            distance = CalculateDistance(Attacker, Target)
            maxRange = Weapon.GetMeleeRange()
            RETURN distance <= maxRange
        END IF
    ELSE IF Weapon.Type == RANGED THEN
        // Ataque à distância funciona normalmente
        distance = CalculateDistance(Attacker, Target)
        maxRange = Weapon.GetRangedRange()
        RETURN distance <= maxRange
    END IF
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Ataque Melee vs. Voador:** Não pode atingir (a menos que atacante também voe)
- **Arma com Reach:** Pode atingir criatura voadora baixa (altura < 3m)
- **Ataque Ranged vs. Voador:** Funciona normalmente
- **Ambos Voadores:** Verifica alcance normal

---

## 📖 Referências

- **GDD:** [Sistema de Combate - Alcance](../02-mecanicas/sistema-combate.md#-alcance-e-movimento)
- **GDD:** [Física e Interação - Voo](../02-mecanicas/fisica-interacao.md#movimento-aéreo-voo)

---

**Navegação:** [← Voltar ao Índice](index.md)
