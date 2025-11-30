# Attack Roll Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de verificação de acerto |

---

## 🎯 Objetivo

Algoritmo técnico de verificação de acerto D&D 5e, definindo como calcular attack roll e comparar com AC do alvo.

---

## 📋 Fórmulas de Ataque

| Tipo de Ataque | Fórmula |
|----------------|---------|
| **Melee Weapon** | d20 + Proficiency Bonus + STR Modifier |
| **Ranged Weapon** | d20 + Proficiency Bonus + DEX Modifier |
| **Spell Attack** | d20 + Proficiency Bonus + Spellcasting Ability Modifier |

**Comparação:**
- `Attack Roll >= Target AC` → **Hit (Acertou)**
- `Attack Roll < Target AC` → **Miss (Errou)**
- `Natural 20` → **Critical Hit (Sempre acerta)**
- `Natural 1` → **Critical Miss (Sempre erra)**

---

## 🔄 Algoritmo de Verificação

### Passo 1: Calcular Attack Roll

```cpp
// Calcular attack roll para ataque melee
int32 CalculateMeleeAttackRoll(
    const FCharacterData& Attacker,
    FName WeaponName,
    bool bHasProficiency = true)
{
    // Rolar d20
    int32 DieRoll = FMath::RandRange(1, 20);

    // Obter modificadores
    int32 STRModifier = GetAbilityModifier(Attacker, TEXT("Strength"));
    int32 ProficiencyBonus = Attacker.ProficiencyBonus;

    // Calcular attack roll
    int32 AttackRoll = DieRoll;

    if (bHasProficiency)
    {
        AttackRoll += ProficiencyBonus;
    }

    AttackRoll += STRModifier;

    return AttackRoll;
}

// Calcular attack roll para ataque ranged
int32 CalculateRangedAttackRoll(
    const FCharacterData& Attacker,
    FName WeaponName,
    bool bHasProficiency = true)
{
    int32 DieRoll = FMath::RandRange(1, 20);
    int32 DEXModifier = GetAbilityModifier(Attacker, TEXT("Dexterity"));
    int32 ProficiencyBonus = Attacker.ProficiencyBonus;

    int32 AttackRoll = DieRoll;

    if (bHasProficiency)
    {
        AttackRoll += ProficiencyBonus;
    }

    AttackRoll += DEXModifier;

    return AttackRoll;
}

// Calcular attack roll para spell attack
int32 CalculateSpellAttackRoll(
    const FCharacterData& Caster,
    FName SpellName)
{
    int32 DieRoll = FMath::RandRange(1, 20);
    FName SpellcastingAbility = GetSpellcastingAbility(Caster);
    int32 AbilityModifier = GetAbilityModifier(Caster, SpellcastingAbility);
    int32 ProficiencyBonus = Caster.ProficiencyBonus;

    int32 AttackRoll = DieRoll + ProficiencyBonus + AbilityModifier;

    return AttackRoll;
}
```

### Passo 2: Verificar Natural 20 e Natural 1

```cpp
// Verificar se é natural 20 (crítico)
bool IsNatural20(int32 DieRoll)
{
    return DieRoll == 20;
}

// Verificar se é natural 1 (falha crítica)
bool IsNatural1(int32 DieRoll)
{
    return DieRoll == 1;
}
```

### Passo 3: Aplicar Vantagem/Desvantagem

```cpp
// Aplicar vantagem (rola 2d20, usa o maior)
int32 ApplyAdvantage(int32& DieRoll1, int32& DieRoll2)
{
    DieRoll1 = FMath::RandRange(1, 20);
    DieRoll2 = FMath::RandRange(1, 20);
    return FMath::Max(DieRoll1, DieRoll2);
}

// Aplicar desvantagem (rola 2d20, usa o menor)
int32 ApplyDisadvantage(int32& DieRoll1, int32& DieRoll2)
{
    DieRoll1 = FMath::RandRange(1, 20);
    DieRoll2 = FMath::RandRange(1, 20);
    return FMath::Min(DieRoll1, DieRoll2);
}

// Verificar se tem vantagem ou desvantagem
int32 CalculateAttackRollWithAdvantage(
    const FCharacterData& Attacker,
    bool bHasAdvantage,
    bool bHasDisadvantage)
{
    int32 DieRoll1 = 0;
    int32 DieRoll2 = 0;
    int32 DieRoll = 0;

    if (bHasAdvantage && !bHasDisadvantage)
    {
        DieRoll = ApplyAdvantage(DieRoll1, DieRoll2);
    }
    else if (bHasDisadvantage && !bHasAdvantage)
    {
        DieRoll = ApplyDisadvantage(DieRoll1, DieRoll2);
    }
    else
    {
        DieRoll = FMath::RandRange(1, 20);
    }

    // Continuar cálculo normal com DieRoll
    return DieRoll;
}
```

### Passo 4: Verificar Acerto

```cpp
// Verificar se ataque acertou
FAttackResult VerifyAttack(
    const FCharacterData& Attacker,
    const FCharacterData& Target,
    FName WeaponOrSpellName,
    bool bIsMelee = true,
    bool bHasAdvantage = false,
    bool bHasDisadvantage = false)
{
    FAttackResult Result;

    // 1. Rolar d20 (com vantagem/desvantagem se aplicável)
    int32 DieRoll = CalculateAttackRollWithAdvantage(Attacker, bHasAdvantage, bHasDisadvantage);
    Result.DieRoll = DieRoll;

    // 2. Verificar natural 20 (crítico)
    if (IsNatural20(DieRoll))
    {
        Result.bHit = true;
        Result.bIsCritical = true;
        Result.bIsNatural20 = true;
        return Result; // Crítico sempre acerta
    }

    // 3. Verificar natural 1 (falha crítica)
    if (IsNatural1(DieRoll))
    {
        Result.bHit = false;
        Result.bIsCriticalMiss = true;
        Result.bIsNatural1 = true;
        return Result; // Natural 1 sempre erra
    }

    // 4. Calcular attack roll completo
    int32 AttackRoll = 0;
    if (bIsMelee)
    {
        AttackRoll = CalculateMeleeAttackRoll(Attacker, WeaponOrSpellName);
    }
    else
    {
        if (IsSpell(WeaponOrSpellName))
        {
            AttackRoll = CalculateSpellAttackRoll(Attacker, WeaponOrSpellName);
        }
        else
        {
            AttackRoll = CalculateRangedAttackRoll(Attacker, WeaponOrSpellName);
        }
    }

    Result.AttackRoll = AttackRoll;

    // 5. Obter AC do alvo
    int32 TargetAC = CalculateAC(Target);
    Result.TargetAC = TargetAC;

    // 6. Comparar attack roll com AC
    Result.bHit = (AttackRoll >= TargetAC);

    return Result;
}
```

---

## 📊 Exemplos

### Exemplo 1: Ataque Normal - Acertou

```cpp
// Attacker: Fighter nível 1, STR 16 (+3), Proficiency +2
// Target: AC 15
// Weapon: Longsword (proficiente)

FAttackResult Result = VerifyAttack(Attacker, Target, TEXT("Longsword"), true);
// DieRoll: 12
// AttackRoll: 12 + 2 (proficiency) + 3 (STR) = 17
// TargetAC: 15
// Result: bHit = true (17 >= 15)
```

### Exemplo 2: Ataque Normal - Errou

```cpp
// Attacker: Fighter nível 1, STR 16 (+3), Proficiency +2
// Target: AC 18
// Weapon: Longsword

FAttackResult Result = VerifyAttack(Attacker, Target, TEXT("Longsword"), true);
// DieRoll: 8
// AttackRoll: 8 + 2 + 3 = 13
// TargetAC: 18
// Result: bHit = false (13 < 18)
```

### Exemplo 3: Natural 20 (Crítico)

```cpp
// Attacker: Fighter nível 1, STR 16 (+3), Proficiency +2
// Target: AC 25 (muito alto)
// Weapon: Longsword

FAttackResult Result = VerifyAttack(Attacker, Target, TEXT("Longsword"), true);
// DieRoll: 20 (natural 20)
// Result: bHit = true, bIsCritical = true, bIsNatural20 = true
// (Crítico sempre acerta, independente de AC)
```

### Exemplo 4: Natural 1 (Falha Crítica)

```cpp
// Attacker: Fighter nível 1, STR 16 (+3), Proficiency +2
// Target: AC 5 (muito baixo)
// Weapon: Longsword

FAttackResult Result = VerifyAttack(Attacker, Target, TEXT("Longsword"), true);
// DieRoll: 1 (natural 1)
// Result: bHit = false, bIsCriticalMiss = true, bIsNatural1 = true
// (Natural 1 sempre erra, independente de AC)
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate - Ataques](../../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#ataques-e-acertos)** - Regras de ataque D&D 5e

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [AC Calculation Algorithm](ac-calculation-algorithm.md) - Algoritmo de AC
> - [Damage Calculation Algorithm](damage-calculation-algorithm.md) - Algoritmo de dano
> - [Pseudocódigo de Combate](../../../08-pseudocodigo/combate/) - Implementação técnica

</details>

---

**Navegação:** [← Damage Calculation](damage-calculation-algorithm.md) | [→ Progressão Algorithms](../progressao/index.md)

**Última atualização:** 2024-12-27
