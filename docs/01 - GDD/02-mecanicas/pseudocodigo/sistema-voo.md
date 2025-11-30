# Pseudocódigo - Sistema de Voo

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🦅 Sistema de Voo</b></summary>

> Pseudocódigo para sistema de voo, incluindo verificação de voo, movimento aéreo, cálculo de posição e queda, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo - Verificação de Voo

```
FUNCTION IsFlying(Creature)
    RETURN Creature.HasFlightSpeed() AND Creature.CurrentHP > 0
END FUNCTION
```

---

## Pseudocódigo - Movimento sobre Obstáculos

```
FUNCTION CanMoveOverObstacle(Creature, Obstacle)
    IF IsFlying(Creature) THEN
        // Criatura voadora pode passar sobre obstáculos terrestres
        IF Obstacle.Type == GROUND_OBSTACLE THEN
            RETURN TRUE
        ELSE IF Obstacle.Type == AERIAL_OBSTACLE THEN
            // Obstáculos aéreos (teto, estruturas altas) bloqueiam
            RETURN FALSE
        END IF
    ELSE
        // Criatura terrestre segue regras normais de colisão
        RETURN CheckNormalCollision(Creature, Obstacle)
    END IF
END FUNCTION
```

---

## Pseudocódigo - Cálculo de Posição Aérea

```
FUNCTION CalculateFlyingPosition(Creature)
    // Posição horizontal = posição da sombra
    horizontalPosition = Creature.ShadowPosition

    // Altura = baseada na velocidade de voo (quanto mais rápido, mais alto)
    flightSpeed = Creature.GetFlightSpeed()
    baseHeight = 2.0 // Altura base em metros
    heightMultiplier = flightSpeed / 12.0 // Normalizado para 12m/s
    verticalOffset = baseHeight * heightMultiplier

    // Tamanho do sprite = reduzido proporcionalmente à altura
    baseSize = Creature.BaseSpriteSize
    sizeMultiplier = 1.0 - (verticalOffset * 0.1) // Reduz 10% por metro de altura
    spriteSize = baseSize * MAX(sizeMultiplier, 0.5) // Mínimo 50% do tamanho original

    RETURN {
        position: horizontalPosition + Vector3(0, verticalOffset, 0),
        spriteSize: spriteSize,
        shadowPosition: horizontalPosition
    }
END FUNCTION
```

---

## Pseudocódigo - Queda de Criatura Voadora

```
FUNCTION HandleFlyingCreatureFall(Creature)
    // Criatura foi derrubada (0 HP ou efeito especial)
    fallHeight = Creature.CurrentFlyingHeight

    // Calcular dano de queda (D&D 5e: 1d6 por 3m, máximo 20d6)
    IF fallHeight <= 3.0 THEN
        fallDamage = 0
    ELSE
        damageDice = MIN(FLOOR(fallHeight / 3.0), 20) // Máximo 20d6
        fallDamage = RollDice(damageDice, 6)
    END IF

    // Aplicar dano
    ApplyDamage(Creature, fallDamage, BLUDGEONING)

    // Criatura para de voar
    Creature.SetFlyingState(FALSE)
    Creature.SetFlyingHeight(0.0)

    // Animação de queda
    PlayFallAnimation(Creature, fallHeight)
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Voo Ativo:** Requer Flight Speed > 0 e HP > 0
- **Obstáculos Terrestres:** Criaturas voadoras podem passar sobre
- **Obstáculos Aéreos:** Bloqueiam criaturas voadoras
- **Altura:** Baseada na velocidade de voo
- **Queda:** Dano de 1d6 por 3m (máximo 20d6 para 60m+)

---

## 📖 Referências

- **GDD:** [Física e Interação - Voo](../02-mecanicas/fisica-interacao.md#movimento-aéreo-voo)
- **D&D 5e:** Player's Handbook - Flying Movement

---

**Navegação:** [← Voltar ao Índice](index.md)
