# Pseudocódigo - Cálculo de Probabilidades de Loot

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Probabilidades de Loot</b></summary>

> Pseudocódigo para cálculo de probabilidades de raridade de loot baseado em CR (Challenge Rating) do inimigo, seguindo D&D 5e.

</details>

---

## Pseudocódigo

```
FUNCTION CalculateLootRarityProbabilities(EnemyCR)
    // Probabilidades base
    baseCommon = 0.80      // 80%
    baseUncommon = 0.15    // 15%
    baseRare = 0.04       // 4%
    baseVeryRare = 0.01   // 1%
    baseLegendary = 0.001 // 0.1%

    // Ajustar por CR do inimigo
    IF EnemyCR <= 1 THEN
        // CR baixo: reduz raro, remove muito raro/lendário
        commonMultiplier = 1.0
        uncommonMultiplier = 0.5
        rareMultiplier = 0.0
        veryRareMultiplier = 0.0
        legendaryMultiplier = 0.0
    ELSE IF EnemyCR <= 4 THEN
        // CR médio: normal
        commonMultiplier = 1.0
        uncommonMultiplier = 1.0
        rareMultiplier = 1.0
        veryRareMultiplier = 0.0
        legendaryMultiplier = 0.0
    ELSE IF EnemyCR <= 7 THEN
        // CR alto: aumenta raro
        commonMultiplier = 0.8
        uncommonMultiplier = 1.2
        rareMultiplier = 1.5
        veryRareMultiplier = 0.5
        legendaryMultiplier = 0.0
    ELSE
        // CR muito alto (boss): aumenta muito raro/lendário
        commonMultiplier = 0.5
        uncommonMultiplier = 1.5
        rareMultiplier = 2.0
        veryRareMultiplier = 1.0
        legendaryMultiplier = 0.5
    END IF

    // Calcular probabilidades finais
    commonProb = baseCommon * commonMultiplier
    uncommonProb = baseUncommon * uncommonMultiplier
    rareProb = baseRare * rareMultiplier
    veryRareProb = baseVeryRare * veryRareMultiplier
    legendaryProb = baseLegendary * legendaryMultiplier

    // Normalizar para somar 100%
    total = commonProb + uncommonProb + rareProb + veryRareProb + legendaryProb
    IF total > 1.0 THEN
        commonProb = commonProb / total
        uncommonProb = uncommonProb / total
        rareProb = rareProb / total
        veryRareProb = veryRareProb / total
        legendaryProb = legendaryProb / total
    END IF

    RETURN {
        Common: commonProb,
        Uncommon: uncommonProb,
        Rare: rareProb,
        VeryRare: veryRareProb,
        Legendary: legendaryProb
    }
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Probabilidades Base:** 80% comum, 15% incomum, 4% raro, 1% muito raro, 0.1% lendário
- **CR Baixo (≤1):** Remove raro/muito raro/lendário
- **CR Médio (2-4):** Probabilidades normais
- **CR Alto (5-7):** Aumenta raro
- **CR Muito Alto (8+):** Aumenta muito raro/lendário
- **Normalização:** Probabilidades sempre somam 100%

---

## 📖 Referências

- **GDD:** [Tabelas de Loot - Probabilidades](../05-economia/tabelas-loot.md#probabilidades-de-drop-por-raridade)
- **D&D 5e:** Dungeon Master's Guide - Treasure Tables

---

**Navegação:** [← Voltar ao Índice](index.md)
