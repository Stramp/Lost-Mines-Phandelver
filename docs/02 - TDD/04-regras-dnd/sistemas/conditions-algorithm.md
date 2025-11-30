# Conditions Algorithm

---

## 🎯 Objetivo

Algoritmo técnico de condições D&D 5e, definindo como aplicar, gerenciar duração e remover condições.

---

## 📋 Condições Principais (MVP)

| Condição | Efeitos |
|----------|---------|
| **Poisoned** | Desvantagem em ataques e testes |
| **Stunned** | Incapacitado, ataques recebidos têm vantagem |
| **Paralyzed** | Incapacitado, críticos automáticos |
| **Prone** | Deitado, vantagem em melee, desvantagem em ranged |
| **Frightened** | Desvantagem enquanto vê fonte do medo |

---

## 🔄 Algoritmo de Aplicação

### Passo 1: Estrutura de Condição

```cpp
USTRUCT(BlueprintType)
struct FCondition
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName ConditionName;

    UPROPERTY(BlueprintReadOnly)
    float Duration; // Em segundos (0 = permanente até remoção)

    UPROPERTY(BlueprintReadOnly)
    float TimeRemaining; // Tempo restante

    UPROPERTY(BlueprintReadOnly)
    bool bIsConcentration; // Remove quando concentração quebra

    UPROPERTY(BlueprintReadOnly)
    AActor* Source; // Fonte da condição (para Frightened, etc.)
};
```

### Passo 2: Aplicar Condição

```cpp
// Aplicar condição no personagem
void ApplyCondition(
    FCharacterData& CharacterData,
    FName ConditionName,
    float Duration = 0.0f,
    bool bIsConcentration = false,
    AActor* Source = nullptr)
{
    // Criar condição
    FCondition NewCondition;
    NewCondition.ConditionName = ConditionName;
    NewCondition.Duration = Duration;
    NewCondition.TimeRemaining = Duration;
    NewCondition.bIsConcentration = bIsConcentration;
    NewCondition.Source = Source;

    // Adicionar à lista de condições ativas
    CharacterData.ActiveConditions.Add(NewCondition);

    // Aplicar efeitos da condição
    ApplyConditionEffects(CharacterData, ConditionName);
}
```

### Passo 3: Aplicar Efeitos de Condição

```cpp
// Aplicar efeitos específicos de cada condição
void ApplyConditionEffects(FCharacterData& CharacterData, FName ConditionName)
{
    if (ConditionName == TEXT("Poisoned"))
    {
        // Desvantagem em ataques e testes
        CharacterData.bHasDisadvantageOnAttacks = true;
        CharacterData.bHasDisadvantageOnAbilityChecks = true;
    }
    else if (ConditionName == TEXT("Stunned"))
    {
        // Incapacitado, ataques recebidos têm vantagem
        CharacterData.bIsIncapacitated = true;
        CharacterData.bAttacksHaveAdvantage = true;
    }
    else if (ConditionName == TEXT("Paralyzed"))
    {
        // Incapacitado, críticos automáticos
        CharacterData.bIsIncapacitated = true;
        CharacterData.bAutoCritical = true;
    }
    else if (ConditionName == TEXT("Prone"))
    {
        // Deitado, vantagem em melee, desvantagem em ranged
        CharacterData.bIsProne = true;
        CharacterData.bMeleeAttacksHaveAdvantage = true;
        CharacterData.bRangedAttacksHaveDisadvantage = true;
    }
    else if (ConditionName == TEXT("Frightened"))
    {
        // Desvantagem enquanto vê fonte do medo
        CharacterData.bHasDisadvantageWhileSeeingSource = true;
    }
}
```

### Passo 4: Atualizar Condições (Tick)

```cpp
// Atualizar condições (chamado a cada frame/tick)
void UpdateConditions(FCharacterData& CharacterData, float DeltaTime)
{
    for (int32 i = CharacterData.ActiveConditions.Num() - 1; i >= 0; i--)
    {
        FCondition& Condition = CharacterData.ActiveConditions[i];

        // Verificar se é concentração e se quebrou
        if (Condition.bIsConcentration && !HasConcentration(CharacterData))
        {
            RemoveCondition(CharacterData, Condition.ConditionName);
            continue;
        }

        // Atualizar tempo restante
        if (Condition.Duration > 0.0f)
        {
            Condition.TimeRemaining -= DeltaTime;

            // Remover se tempo acabou
            if (Condition.TimeRemaining <= 0.0f)
            {
                RemoveCondition(CharacterData, Condition.ConditionName);
            }
        }
    }
}
```

### Passo 5: Remover Condição

```cpp
// Remover condição
void RemoveCondition(FCharacterData& CharacterData, FName ConditionName)
{
    // Remover da lista
    CharacterData.ActiveConditions.RemoveAll(
        [ConditionName](const FCondition& Condition)
        {
            return Condition.ConditionName == ConditionName;
        }
    );

    // Remover efeitos da condição
    RemoveConditionEffects(CharacterData, ConditionName);
}

// Remover efeitos específicos
void RemoveConditionEffects(FCharacterData& CharacterData, FName ConditionName)
{
    if (ConditionName == TEXT("Poisoned"))
    {
        CharacterData.bHasDisadvantageOnAttacks = false;
        CharacterData.bHasDisadvantageOnAbilityChecks = false;
    }
    else if (ConditionName == TEXT("Stunned"))
    {
        CharacterData.bIsIncapacitated = false;
        CharacterData.bAttacksHaveAdvantage = false;
    }
    // ... (similar para outras condições)
}
```

### Passo 6: Verificar Condição

```cpp
// Verificar se tem condição ativa
bool HasCondition(const FCharacterData& CharacterData, FName ConditionName)
{
    return CharacterData.ActiveConditions.ContainsByPredicate(
        [ConditionName](const FCondition& Condition)
        {
            return Condition.ConditionName == ConditionName;
        }
    );
}
```

---

## 📖 Design Relacionado

Este documento implementa as seguintes regras de design:

- **[GDD: Sistema de Combate - Condições](../../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#condições-conditions)** - Regras de condições D&D 5e

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Rest Algorithm](rest-algorithm.md) - Algoritmo de descanso
> - [API - Componentes](../../../02-api/componentes/index.md) - Componentes de combate

</details>

---

**Navegação:** [← Rest Algorithm](rest-algorithm.md) | [→ Voltar para Index](../index.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de condições |
