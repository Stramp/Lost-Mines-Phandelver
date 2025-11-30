# Point Buy Algorithm

---

## 🎯 Objetivo

Algoritmo técnico de validação e cálculo do sistema Point Buy D&D 5e, definindo como validar alocações e calcular custos.

---

## 📋 Tabela de Custos Point Buy

| Score | Custo | Score | Custo |
|-------|-------|-------|-------|
| 8 | 0 | 12 | 4 |
| 9 | 1 | 13 | 5 |
| 10 | 2 | 14 | 7 |
| 11 | 3 | 15 | 9 |

**Total de Pontos Disponíveis:** 27 pontos

**Range Válido:** 8-15 (antes de bônus raciais)

---

## 🔄 Algoritmo de Validação

### Passo 1: Validar Range de Scores

```cpp
// 1. Validar que todos os scores estão no range [8, 15]
bool ValidatePointBuyRange(const TMap<FName, int32>& BaseScores)
{
    for (const auto& Pair : BaseScores)
    {
        int32 Score = Pair.Value;
        if (Score < DnDConstants::MIN_POINT_BUY_SCORE ||
            Score > DnDConstants::MAX_POINT_BUY_SCORE)
        {
            return false; // Score fora do range válido
        }
    }
    return true;
}
```

### Passo 2: Calcular Custo Total

```cpp
// 2. Calcular custo total da alocação
int32 CalculatePointBuyCost(int32 Score)
{
    // Tabela de custos D&D 5e
    const TMap<int32, int32> CostTable = {
        {8, 0}, {9, 1}, {10, 2}, {11, 3},
        {12, 4}, {13, 5}, {14, 7}, {15, 9}
    };

    return CostTable.Contains(Score) ? CostTable[Score] : 0;
}

int32 CalculateTotalPointBuyCost(const TMap<FName, int32>& BaseScores)
{
    int32 TotalCost = 0;
    for (const auto& Pair : BaseScores)
    {
        TotalCost += CalculatePointBuyCost(Pair.Value);
    }
    return TotalCost;
}
```

### Passo 3: Validar Alocação Completa

```cpp
// 3. Validar que exatamente 27 pontos foram gastos
FPointBuyValidationResult ValidatePointBuy(
    int32 PointBuyStrength,
    int32 PointBuyDexterity,
    int32 PointBuyConstitution,
    int32 PointBuyIntelligence,
    int32 PointBuyWisdom,
    int32 PointBuyCharisma)
{
    // Converter alocação (0-7) para score base (8-15)
    TMap<FName, int32> BaseScores = {
        {TEXT("Strength"), DnDConstants::BASE_ABILITY_SCORE + PointBuyStrength},
        {TEXT("Dexterity"), DnDConstants::BASE_ABILITY_SCORE + PointBuyDexterity},
        {TEXT("Constitution"), DnDConstants::BASE_ABILITY_SCORE + PointBuyConstitution},
        {TEXT("Intelligence"), DnDConstants::BASE_ABILITY_SCORE + PointBuyIntelligence},
        {TEXT("Wisdom"), DnDConstants::BASE_ABILITY_SCORE + PointBuyWisdom},
        {TEXT("Charisma"), DnDConstants::BASE_ABILITY_SCORE + PointBuyCharisma}
    };

    // Validar range
    int32 PointsRemaining = 0;
    bool bAllScoresValid = ValidatePointBuyRange(BaseScores);

    if (bAllScoresValid)
    {
        // Calcular pontos restantes
        int32 TotalCost = CalculateTotalPointBuyCost(BaseScores);
        PointsRemaining = DnDConstants::MAX_POINT_BUY_POINTS - TotalCost;
    }

    // Alocação válida se: range válido E exatamente 27 pontos gastos
    bool bIsValid = (PointsRemaining == 0 && bAllScoresValid);

    return FPointBuyValidationResult(PointsRemaining, bAllScoresValid, bIsValid);
}
```

---

## 🔄 Algoritmo de Aplicação

### Passo 1: Aplicar Point Buy nos Final Scores

```cpp
// Aplicar Point Buy nos Final Scores (após bônus raciais)
void ApplyPointBuy(
    const TMap<FName, int32>& PointBuyMap,
    int32& FinalStrength,
    int32& FinalDexterity,
    int32& FinalConstitution,
    int32& FinalIntelligence,
    int32& FinalWisdom,
    int32& FinalCharisma)
{
    // Point Buy é aplicado DEPOIS dos bônus raciais
    // Fórmula: FinalScore = BASE (8) + RacialBonus + PointBuyAllocation

    FinalStrength = DnDConstants::BASE_ABILITY_SCORE +
                    PointBuyMap.FindRef(TEXT("Strength"));
    FinalDexterity = DnDConstants::BASE_ABILITY_SCORE +
                     PointBuyMap.FindRef(TEXT("Dexterity"));
    FinalConstitution = DnDConstants::BASE_ABILITY_SCORE +
                        PointBuyMap.FindRef(TEXT("Constitution"));
    FinalIntelligence = DnDConstants::BASE_ABILITY_SCORE +
                        PointBuyMap.FindRef(TEXT("Intelligence"));
    FinalWisdom = DnDConstants::BASE_ABILITY_SCORE +
                  PointBuyMap.FindRef(TEXT("Wisdom"));
    FinalCharisma = DnDConstants::BASE_ABILITY_SCORE +
                    PointBuyMap.FindRef(TEXT("Charisma"));
}
```

### Passo 2: Ajuste Automático (se necessário)

```cpp
// Ajustar automaticamente se exceder 27 pontos
FString AdjustPointBuyAllocation(TMap<FName, int32>& PointBuyMap, int32 MaxPoints)
{
    int32 TotalCost = CalculateTotalPointBuyCost(PointBuyMap);

    if (TotalCost <= MaxPoints)
    {
        return TEXT("Alocação válida");
    }

    // Reduzir scores mais altos até atingir MaxPoints
    while (TotalCost > MaxPoints)
    {
        // Encontrar score mais alto
        FName HighestScore = NAME_None;
        int32 HighestValue = 0;

        for (auto& Pair : PointBuyMap)
        {
            if (Pair.Value > HighestValue)
            {
                HighestValue = Pair.Value;
                HighestScore = Pair.Key;
            }
        }

        // Reduzir em 1
        if (HighestScore != NAME_None && PointBuyMap[HighestScore] > 0)
        {
            PointBuyMap[HighestScore]--;
            TotalCost = CalculateTotalPointBuyCost(PointBuyMap);
        }
        else
        {
            break; // Não pode reduzir mais
        }
    }

    return FString::Printf(TEXT("Alocação ajustada para %d pontos"), TotalCost);
}
```

---

## 📊 Exemplo Completo

### Exemplo 1: Alocação Válida

```cpp
// Input: Alocação que gasta exatamente 27 pontos
TMap<FName, int32> PointBuyMap = {
    {TEXT("Strength"), 7},      // Score 15 (custo 9)
    {TEXT("Dexterity"), 4},     // Score 12 (custo 4)
    {TEXT("Constitution"), 2},  // Score 10 (custo 2)
    {TEXT("Intelligence"), 2},  // Score 10 (custo 2)
    {TEXT("Wisdom"), 2},        // Score 10 (custo 2)
    {TEXT("Charisma"), 0}       // Score 8 (custo 0)
};
// Total: 9 + 4 + 2 + 2 + 2 + 0 = 19 pontos ❌ (faltam 8 pontos)

// Correção: Ajustar para 27 pontos
PointBuyMap[TEXT("Strength")] = 7;  // 9 pontos
PointBuyMap[TEXT("Dexterity")] = 5; // 5 pontos
PointBuyMap[TEXT("Constitution")] = 3; // 3 pontos
PointBuyMap[TEXT("Intelligence")] = 3; // 3 pontos
PointBuyMap[TEXT("Wisdom")] = 2; // 2 pontos
PointBuyMap[TEXT("Charisma")] = 2; // 2 pontos
// Total: 9 + 5 + 3 + 3 + 2 + 2 = 24 pontos ❌ (faltam 3 pontos)

// Correção final:
PointBuyMap[TEXT("Wisdom")] = 3; // 3 pontos (era 2)
PointBuyMap[TEXT("Charisma")] = 3; // 3 pontos (era 2)
// Total: 9 + 5 + 3 + 3 + 3 + 3 = 26 pontos ❌ (falta 1 ponto)

// Correção final:
PointBuyMap[TEXT("Constitution")] = 4; // 4 pontos (era 3)
// Total: 9 + 5 + 4 + 3 + 3 + 3 = 27 pontos ✅
```

### Exemplo 2: Aplicação com Bônus Raciais

```cpp
// 1. Base: 8 (reset)
// 2. Racial: Dwarf +2 Constitution
// 3. Point Buy: +7 Strength, +0 Constitution
// 4. Final: Strength = 8 + 0 + 7 = 15, Constitution = 8 + 2 + 0 = 10

int32 FinalStrength = DnDConstants::BASE_ABILITY_SCORE + 0 + 7; // 15
int32 FinalConstitution = DnDConstants::BASE_ABILITY_SCORE + 2 + 0; // 10
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistemas de Personagem - Point Buy](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md)** - Regras de Point Buy D&D 5e
> - **[GDD: Cálculo de Ability Scores](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#cálculo-de-ability-scores-finais)** - Fórmula de cálculo
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](character-creation-algorithm.md) - Algoritmo completo
> - [API - PointBuyMotor](../../../02-api/motores/index.md) - Motor de Point Buy
> - [API - ValidationHelpers](../../../02-api/helpers/index.md) - Helpers de validação

</details>

---

**Navegação:** [← Character Creation](character-creation-algorithm.md) | [→ Multiclass Algorithm](multiclass-algorithm.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de Point Buy |
