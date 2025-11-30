# Pseudocódigo - Sistema de Fontes e Drenos

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💰 Sistema de Fontes e Drenos</b></summary>

> Pseudocódigo para cálculo de fontes de ouro, drenos e balanceamento econômico, seguindo D&D 5e.

</details>

---

## Pseudocódigo - Cálculo de Fontes de Ouro por Sessão

```
FUNCTION CalculateGoldSourcesPerSession(ChapterNumber, QuestType, DungeonType, Encounters)
    totalSources = 0.0

    // 1. Recompensa de Quest Principal
    IF QuestType == MAIN_QUEST THEN
        questReward = GetMainQuestReward(ChapterNumber)
        // Capítulo 1: 50-100 GP, Capítulo 2: 100-200 GP, etc.
        totalSources = totalSources + questReward
    END IF

    // 2. Recompensa de Quest Secundária
    IF QuestType == SIDE_QUEST THEN
        sideQuestReward = RandomFloat(10.0, 50.0) // 10-50 GP
        totalSources = totalSources + sideQuestReward
    END IF

    // 3. Tesouro de Masmorra
    IF DungeonType != NULL THEN
        dungeonTreasure = GetDungeonTreasure(DungeonType)
        // Cragmaw Hideout: 100-200 GP, Redbrand Hideout: 150-300 GP, etc.
        totalSources = totalSources + dungeonTreasure
    END IF

    // 4. Loot de Inimigos
    FOR EACH encounter IN Encounters DO
        FOR EACH enemy IN encounter.Enemies DO
            enemyLoot = CalculateEnemyLoot(enemy)
            totalSources = totalSources + enemyLoot
        END FOR
    END FOR

    // 5. Venda de Itens (estimativa baseada em loot)
    itemsSold = EstimateItemsSold(Encounters)
    saleValue = CalculateSaleValue(itemsSold) // 50% do valor de compra
    totalSources = totalSources + saleValue

    RETURN totalSources
END FUNCTION

FUNCTION CalculateEnemyLoot(Enemy)
    enemyType = Enemy.GetType()
    enemyCR = Enemy.GetChallengeRating()

    // Moedas baseadas em tipo e CR
    coinAmount = RollCoinAmount(enemyCR, enemyType)

    // Itens (baseado em sistema de loot)
    lootTable = RollLoot(Enemy, enemyCR, enemyType)
    itemValue = CalculateItemValue(lootTable)

    RETURN coinAmount + itemValue
END FUNCTION
```

---

## Pseudocódigo - Cálculo de Drenos de Ouro por Sessão

```
FUNCTION CalculateGoldSinksPerSession(PlayerLevel, RestCount, ServicesUsed, EquipmentPurchased)
    totalSinks = 0.0

    // 1. Compra de Equipamento
    IF EquipmentPurchased != NULL THEN
        equipmentCost = GetEquipmentCost(PlayerLevel, EquipmentPurchased)
        // Nível 1: ~75 GP, Nível 3: ~150 GP, Nível 5: ~350 GP
        totalSinks = totalSinks + equipmentCost
    END IF

    // 2. Reparo de Equipamentos
    repairCost = CalculateRepairCost(EquipmentPurchased)
    // 10% do valor do item
    totalSinks = totalSinks + repairCost

    // 3. Custos de Descanso
    FOR i = 1 TO RestCount DO
        restCost = RandomFloat(0.5, 2.0) // 0.5-2 GP por long rest
        totalSinks = totalSinks + restCost
    END FOR

    // 4. Serviços (cura, identificação, etc.)
    FOR EACH service IN ServicesUsed DO
        serviceCost = GetServiceCost(service)
        totalSinks = totalSinks + serviceCost
    END FOR

    // 5. Consumíveis (poções, etc.)
    consumablesCost = EstimateConsumablesCost(PlayerLevel)
    // ~125 GP por sessão (2-3 poções)
    totalSinks = totalSinks + consumablesCost

    RETURN totalSinks
END FUNCTION

FUNCTION CalculateRepairCost(Equipment)
    totalRepairCost = 0.0

    FOR EACH item IN Equipment DO
        IF item.NeedsRepair() THEN
            itemValue = GetItemValue(item)
            repairCost = itemValue * 0.10 // 10% do valor
            totalRepairCost = totalRepairCost + repairCost
        END IF
    END FOR

    RETURN totalRepairCost
END FUNCTION
```

---

## Pseudocódigo - Sistema de Balanceamento Econômico

```
FUNCTION ValidateEconomicBalance(PlayerLevel, SessionNumber)
    // Calcular fontes e drenos
    sources = CalculateGoldSourcesPerSession(...)
    sinks = CalculateGoldSinksPerSession(...)
    netBalance = sources - sinks

    // Validação de equilíbrio
    IF netBalance < 0 THEN
        WARNING "Dreno maior que fonte - jogador pode ficar sem recursos"
        // Sugerir ajustes: reduzir custos ou aumentar fontes
    ELSE IF netBalance > 200 THEN
        WARNING "Fonte muito maior que dreno - economia pode ficar inflacionada"
        // Sugerir ajustes: aumentar custos ou reduzir fontes
    END IF

    // Calcular saldo acumulado por nível
    accumulatedGold = CalculateAccumulatedGold(PlayerLevel)
    expectedGold = GetExpectedGoldForLevel(PlayerLevel)

    IF accumulatedGold < expectedGold * 0.8 THEN
        WARNING "Jogador abaixo do ouro esperado para o nível"
    ELSE IF accumulatedGold > expectedGold * 1.2 THEN
        WARNING "Jogador acima do ouro esperado para o nível"
    END IF

    RETURN {
        netBalance: netBalance,
        accumulatedGold: accumulatedGold,
        expectedGold: expectedGold,
        isBalanced: (netBalance >= -50 AND netBalance <= 200)
    }
END FUNCTION

FUNCTION CalculateAccumulatedGold(PlayerLevel)
    totalGold = 0.0

    FOR level = 1 TO PlayerLevel DO
        sourcesPerLevel = GetAverageSourcesPerLevel(level)
        sinksPerLevel = GetAverageSinksPerLevel(level)
        levelBalance = sourcesPerLevel - sinksPerLevel
        totalGold = totalGold + levelBalance
    END FOR

    RETURN totalGold
END FUNCTION

FUNCTION GetExpectedGoldForLevel(PlayerLevel)
    // Valores esperados baseados em D&D 5e
    expectedGoldTable = {
        1: 200,   // Starting gold + primeira sessão
        2: 500,   // Acumulado até nível 2
        3: 750,   // Acumulado até nível 3
        4: 1050,  // Acumulado até nível 4
        5: 1125   // Acumulado até nível 5
    }

    RETURN expectedGoldTable[PlayerLevel]
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Fontes:** Quests, tesouros de masmorras, loot de inimigos, venda de itens
- **Drenos:** Equipamento, reparo, descanso, serviços, consumíveis
- **Balanceamento:** Saldo líquido deve estar entre -50 e +200 GP por sessão
- **Acumulação:** Jogador deve ter ~1125 GP acumulado ao final da campanha (nível 5)
- **Reparo:** 10% do valor do item (regra D&D 5e)
- **Venda:** 50% do valor de compra (regra D&D 5e)

---

## 📖 Referências

- **GDD:** [Fontes e Drenos - Análise de Equilíbrio](../05-economia/fontes-drenos.md#-análise-de-equilíbrio-econômico)
- **D&D 5e:** Player's Handbook - Starting Equipment, Dungeon Master's Guide - Treasure

---

**Navegação:** [← Voltar ao Índice](index.md)
