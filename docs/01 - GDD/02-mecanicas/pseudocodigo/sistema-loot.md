# Pseudocódigo - Sistema Completo de Roll de Loot

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Sistema de Roll de Loot</b></summary>

> Pseudocódigo completo para sistema de roll de loot, incluindo seleção de raridade, item específico e moedas, seguindo D&D 5e.

</details>

---

## Pseudocódigo - Roll de Loot Principal

```
FUNCTION RollLoot(Enemy, EnemyCR, EnemyType)
    lootTable = []

    // 1. Determinar raridade do item
    probabilities = CalculateLootRarityProbabilities(EnemyCR)
    rarityRoll = RandomFloat(0.0, 1.0)

    rarity = COMMON
    cumulative = 0.0

    cumulative = cumulative + probabilities.Common
    IF rarityRoll <= cumulative THEN
        rarity = COMMON
    ELSE
        cumulative = cumulative + probabilities.Uncommon
        IF rarityRoll <= cumulative THEN
            rarity = UNCOMMON
        ELSE
            cumulative = cumulative + probabilities.Rare
            IF rarityRoll <= cumulative THEN
                rarity = RARE
            ELSE
                cumulative = cumulative + probabilities.VeryRare
                IF rarityRoll <= cumulative THEN
                    rarity = VERY_RARE
                ELSE
                    rarity = LEGENDARY
                END IF
            END IF
        END IF
    END IF

    // 2. Selecionar item da tabela de loot específica do tipo de inimigo
    enemyLootTable = GetLootTableForEnemyType(EnemyType, rarity)

    IF enemyLootTable.IsEmpty() THEN
        // Fallback: usar tabela genérica
        enemyLootTable = GetGenericLootTable(rarity)
    END IF

    // 3. Roll do item específico (baseado em probabilidades da tabela)
    item = RollItemFromTable(enemyLootTable)

    // 4. Adicionar moedas (sempre presente)
    coinRoll = RandomFloat(0.0, 1.0)
    IF coinRoll <= GetCoinDropProbability(EnemyType) THEN
        coinAmount = RollCoinAmount(EnemyCR, EnemyType)
        lootTable.Add(Coin(coinAmount))
    END IF

    // 5. Adicionar item (se rolado)
    IF item != NULL THEN
        lootTable.Add(item)
    END IF

    RETURN lootTable
END FUNCTION
```

---

## Pseudocódigo - Roll de Item da Tabela

```
FUNCTION RollItemFromTable(LootTable)
    totalWeight = 0.0
    FOR EACH entry IN LootTable DO
        totalWeight = totalWeight + entry.Weight
    END FOR

    roll = RandomFloat(0.0, totalWeight)
    currentWeight = 0.0

    FOR EACH entry IN LootTable DO
        currentWeight = currentWeight + entry.Weight
        IF roll <= currentWeight THEN
            RETURN entry.Item
        END IF
    END FOR

    RETURN NULL
END FUNCTION
```

---

## Pseudocódigo - Roll de Moedas

```
FUNCTION RollCoinAmount(EnemyCR, EnemyType)
    // Moedas baseadas em CR e tipo
    baseAmount = GetBaseCoinAmount(EnemyCR)

    // Ajustar por tipo de inimigo
    IF EnemyType == HUMANOID THEN
        multiplier = 1.0  // Humanoides têm mais moedas
    ELSE IF EnemyType == UNDEAD THEN
        multiplier = 0.5  // Mortos-vivos têm menos moedas
    ELSE IF EnemyType == BOSS THEN
        multiplier = 5.0  // Bosses têm muito mais moedas
    ELSE
        multiplier = 0.8  // Outros tipos
    END IF

    finalAmount = baseAmount * multiplier

    // Adicionar variação aleatória (±20%)
    variation = RandomFloat(0.8, 1.2)
    finalAmount = finalAmount * variation

    RETURN ROUND(finalAmount)
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Raridade:** Determinada por roll baseado em probabilidades ajustadas por CR
- **Item Específico:** Selecionado da tabela de loot do tipo de inimigo
- **Moedas:** Sempre presentes (com probabilidade baseada no tipo)
- **Fallback:** Usa tabela genérica se tabela específica estiver vazia
- **Variação:** Moedas têm variação aleatória de ±20%

---

## 📖 Referências

- **GDD:** [Tabelas de Loot - Implementação](../05-economia/tabelas-loot.md#implementação-técnica)
- **D&D 5e:** Dungeon Master's Guide - Treasure

---

**Navegação:** [← Voltar ao Índice](index.md)
