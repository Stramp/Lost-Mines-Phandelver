# Passo 3: Ability Scores - Guia Algorítmico

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia do passo 3 |

---

## 🎯 Objetivo

Implementar alocação de atributos usando Strategy Pattern para diferentes métodos (Point Buy, Standard Array, Roll).

---

## 🏗️ Design Pattern: Strategy

### Estrutura

```cpp
// Interface Strategy
class IAbilityScoreStrategy
{
public:
    virtual ~IAbilityScoreStrategy() = default;
    virtual TMap<FName, int32> AllocateAbilityScores() = 0;
};

// Strategy: Point Buy
class FPointBuyStrategy : public IAbilityScoreStrategy
{
public:
    TMap<FName, int32> AllocateAbilityScores() override;
};

// Strategy: Standard Array
class FStandardArrayStrategy : public IAbilityScoreStrategy
{
public:
    TMap<FName, int32> AllocateAbilityScores() override;
};

// Strategy: Roll
class FRollStrategy : public IAbilityScoreStrategy
{
public:
    TMap<FName, int32> AllocateAbilityScores() override;
};
```

### Implementação

```cpp
// Passo 3: Alocar Ability Scores
FCharacterBuilder& FCharacterBuilder::SetAbilityScores(
    IAbilityScoreStrategy* Strategy)
{
    // 1. Usar Strategy para alocar scores
    TMap<FName, int32> BaseScores = Strategy->AllocateAbilityScores();

    // 2. Validar alocação (se Point Buy)
    if (FPointBuyStrategy* PointBuyStrategy = Cast<FPointBuyStrategy>(Strategy))
    {
        if (!FPointBuyValidator::ValidateAllocation(BaseScores, 27))
        {
            // Erro: Alocação inválida
            return *this;
        }
    }

    // 3. Aplicar Point Buy
    FPointBuyMotor::ApplyPointBuy(CharacterData, BaseScores);

    // 4. Calcular scores finais (BASE + RACIAL + POINT_BUY)
    FCharacterSheetCore::CalculateFinalAbilityScores(CharacterData);

    return *this;
}
```

### Strategy: Point Buy

```cpp
TMap<FName, int32> FPointBuyStrategy::AllocateAbilityScores()
{
    // Alocação manual do jogador (0-7 pontos por atributo)
    // Validação feita no Builder
    return PointBuyAllocation; // Dados do jogador
}
```

### Strategy: Standard Array

```cpp
TMap<FName, int32> FStandardArrayStrategy::AllocateAbilityScores()
{
    // Standard Array D&D 5e: 15, 14, 13, 12, 10, 8
    TArray<int32> StandardArray = {15, 14, 13, 12, 10, 8};

    // Jogador distribui os valores
    TMap<FName, int32> BaseScores;
    // ... distribuição manual

    return BaseScores;
}
```

### Strategy: Roll

```cpp
TMap<FName, int32> FRollStrategy::AllocateAbilityScores()
{
    // Rolar 4d6, descartar menor, somar 3 maiores
    TMap<FName, int32> BaseScores;

    for (const FName& AbilityName : GetAllAbilityNames())
    {
        TArray<int32> Rolls;
        for (int32 i = 0; i < 4; i++)
        {
            Rolls.Add(FMath::RandRange(1, 6));
        }

        // Ordenar e descartar menor
        Rolls.Sort();
        Rolls.RemoveAt(0);

        // Somar 3 maiores
        int32 Total = 0;
        for (int32 Roll : Rolls)
        {
            Total += Roll;
        }

        BaseScores.Add(AbilityName, Total);
    }

    return BaseScores;
}
```

---

## 🔄 Fluxo Completo

```
1. Usuário escolhe método → Point Buy, Standard Array, ou Roll
2. Builder cria Strategy apropriada → new FPointBuyStrategy()
3. Strategy aloca scores → Strategy->AllocateAbilityScores()
4. Builder valida (se Point Buy) → FPointBuyValidator::ValidateAllocation()
5. Builder aplica Point Buy → FPointBuyMotor::ApplyPointBuy()
6. Builder calcula scores finais → FCharacterSheetCore::CalculateFinalAbilityScores()
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Point Buy Algorithm](../../../../04-regras-dnd/criacao/point-buy-algorithm.md) - Algoritmo técnico
> - [Point Buy Motor](../../../../02-api/motores/index.md) - Motor de Point Buy
> - [Design Patterns](design-patterns.md) - Padrões utilizados

</details>

---

**Navegação:** [← Passo 2: Class](passo-2-class.md) | [→ Passo 4: Describe](passo-4-describe.md)

**Última atualização:** 2024-12-27
