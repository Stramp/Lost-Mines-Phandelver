# Rest Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de descanso |

---

## 🎯 Objetivo

Algoritmo técnico de descanso D&D 5e, definindo como aplicar Short Rest e Long Rest e recuperar recursos.

---

## 📋 Tipos de Descanso

| Tipo | Duração | Recupera |
|------|---------|----------|
| **Short Rest** | 1 hora | Hit Dice, Warlock Spell Slots, Features de Short Rest |
| **Long Rest** | 8 horas | HP completo, Spell Slots, Hit Dice (metade), Features |

---

## 🔄 Algoritmo de Short Rest

### Passo 1: Validar Short Rest

```cpp
// Validar se pode fazer Short Rest
bool ValidateShortRest(const FCharacterData& CharacterData)
{
    // Verificar se está em área segura (implementação específica)
    if (!IsInSafeArea(CharacterData))
    {
        return false; // Não está em área segura
    }

    // Verificar se não está em combate
    if (IsInCombat(CharacterData))
    {
        return false; // Não pode descansar em combate
    }

    return true;
}
```

### Passo 2: Usar Hit Dice

```cpp
// Usar Hit Dice para recuperar HP
FHitDiceResult UseHitDice(
    FCharacterData& CharacterData,
    int32 HitDiceToSpend)
{
    FHitDiceResult Result;

    // Validar Hit Dice disponíveis
    int32 AvailableHitDice = CharacterData.AvailableHitDice;
    int32 HitDiceSpent = FMath::Min(HitDiceToSpend, AvailableHitDice);

    if (HitDiceSpent <= 0)
    {
        Result.bSuccess = false;
        return Result;
    }

    // Obter Hit Die da classe principal
    int32 HitDie = GetClassHitDie(CharacterData, CharacterData.PrimaryClass);
    int32 CONModifier = GetAbilityModifier(CharacterData, TEXT("Constitution"));

    // Rolar Hit Dice
    int32 TotalHPRecovered = 0;
    for (int32 i = 0; i < HitDiceSpent; i++)
    {
        int32 HitDieRoll = FMath::RandRange(1, HitDie);
        int32 HPRecovered = HitDieRoll + CONModifier;
        TotalHPRecovered += FMath::Max(HPRecovered, 1); // Mínimo 1
    }

    // Aplicar HP recuperado
    CharacterData.CurrentHP = FMath::Min(
        CharacterData.CurrentHP + TotalHPRecovered,
        CharacterData.MaxHP
    );

    // Reduzir Hit Dice disponíveis
    CharacterData.AvailableHitDice -= HitDiceSpent;

    Result.bSuccess = true;
    Result.HPRecovered = TotalHPRecovered;
    Result.HitDiceSpent = HitDiceSpent;

    return Result;
}
```

### Passo 3: Recuperar Warlock Spell Slots

```cpp
// Recuperar spell slots de Warlock
void RecoverWarlockSpellSlots(FCharacterData& CharacterData)
{
    // Verificar se tem níveis de Warlock
    if (!CharacterData.ClassLevels.Contains(TEXT("Warlock")))
    {
        return; // Não é Warlock
    }

    // Recuperar todos os spell slots de Warlock
    TMap<int32, int32>& WarlockSpellSlots = CharacterData.WarlockSpellSlots;
    TMap<int32, int32> MaxWarlockSpellSlots = GetMaxWarlockSpellSlots(CharacterData);

    for (const auto& Pair : MaxWarlockSpellSlots)
    {
        int32 SlotLevel = Pair.Key;
        int32 MaxSlots = Pair.Value;
        WarlockSpellSlots[SlotLevel] = MaxSlots;
    }
}
```

### Passo 4: Aplicar Short Rest

```cpp
// Aplicar Short Rest completo
FRestResult ApplyShortRest(FCharacterData& CharacterData)
{
    FRestResult Result;

    // Validar
    if (!ValidateShortRest(CharacterData))
    {
        Result.bSuccess = false;
        Result.ErrorMessage = TEXT("Não pode fazer Short Rest");
        return Result;
    }

    // 1. Recuperar Warlock Spell Slots
    RecoverWarlockSpellSlots(CharacterData);

    // 2. Recuperar features de Short Rest
    RecoverShortRestFeatures(CharacterData);

    // 3. Hit Dice são usados manualmente pelo jogador
    // (não recupera automaticamente)

    Result.bSuccess = true;
    Result.RestType = TEXT("Short");

    return Result;
}
```

---

## 🔄 Algoritmo de Long Rest

### Passo 1: Validar Long Rest

```cpp
// Validar se pode fazer Long Rest
bool ValidateLongRest(const FCharacterData& CharacterData)
{
    // Verificar se está em área segura
    if (!IsInSafeArea(CharacterData))
    {
        return false;
    }

    // Verificar se não está em combate
    if (IsInCombat(CharacterData))
    {
        return false;
    }

    // Verificar se já fez Long Rest nas últimas 24 horas
    if (HasRestrictedRecently(CharacterData, TEXT("LongRest"), 24.0f))
    {
        return false; // Apenas 1 Long Rest por 24 horas
    }

    return true;
}
```

### Passo 2: Recuperar HP Completo

```cpp
// Recuperar HP completo
void RecoverFullHP(FCharacterData& CharacterData)
{
    CharacterData.CurrentHP = CharacterData.MaxHP;
}
```

### Passo 3: Recuperar Spell Slots

```cpp
// Recuperar spell slots (exceto Warlock)
void RecoverSpellSlots(FCharacterData& CharacterData)
{
    // Calcular spell slots máximos
    TMap<int32, int32> MaxSpellSlots = CalculateSpellSlots(CharacterData);

    // Recuperar todos os spell slots
    TMap<int32, int32>& SpellSlots = CharacterData.SpellSlots;
    for (const auto& Pair : MaxSpellSlots)
    {
        int32 SlotLevel = Pair.Key;
        int32 MaxSlots = Pair.Value;
        SpellSlots[SlotLevel] = MaxSlots;
    }

    // Nota: Warlock spell slots são recuperados em Short Rest, não Long Rest
}
```

### Passo 4: Recuperar Hit Dice (Metade)

```cpp
// Recuperar metade dos Hit Dice gastos
void RecoverHitDice(FCharacterData& CharacterData)
{
    int32 TotalHitDice = CalculateTotalHitDice(CharacterData);
    int32 AvailableHitDice = CharacterData.AvailableHitDice;
    int32 SpentHitDice = TotalHitDice - AvailableHitDice;

    // Recupera metade dos gastos (mínimo 1)
    int32 HitDiceRecovered = FMath::Max(FMath::FloorToInt(SpentHitDice / 2.0f), 1);

    CharacterData.AvailableHitDice = FMath::Min(
        CharacterData.AvailableHitDice + HitDiceRecovered,
        TotalHitDice
    );
}
```

### Passo 5: Aplicar Long Rest

```cpp
// Aplicar Long Rest completo
FRestResult ApplyLongRest(FCharacterData& CharacterData)
{
    FRestResult Result;

    // Validar
    if (!ValidateLongRest(CharacterData))
    {
        Result.bSuccess = false;
        Result.ErrorMessage = TEXT("Não pode fazer Long Rest");
        return Result;
    }

    // 1. Recuperar HP completo
    RecoverFullHP(CharacterData);

    // 2. Recuperar Spell Slots (exceto Warlock)
    RecoverSpellSlots(CharacterData);

    // 3. Recuperar Hit Dice (metade)
    RecoverHitDice(CharacterData);

    // 4. Recuperar features de Long Rest
    RecoverLongRestFeatures(CharacterData);

    // 5. Registrar tempo do Long Rest
    CharacterData.LastLongRestTime = GetCurrentGameTime();

    Result.bSuccess = true;
    Result.RestType = TEXT("Long");

    return Result;
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Rest](../../../../01%20-%20GDD/02-mecanicas/rest.md)** - Regras de descanso D&D 5e
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Conditions Algorithm](conditions-algorithm.md) - Algoritmo de condições
> - [API - Componentes](../../../02-api/componentes/index.md) - Componentes de personagem

</details>

---

**Navegação:** [← Voltar](index.md) | [→ Conditions Algorithm](conditions-algorithm.md)

**Última atualização:** 2024-12-27
