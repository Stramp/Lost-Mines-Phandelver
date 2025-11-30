# Damage Calculation Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de cálculo de dano |

---

## 🎯 Objetivo

Algoritmo técnico de cálculo de dano D&D 5e, definindo como calcular dano de ataques, magias, críticos e aplicar resistências/vulnerabilidades.

---

## 📋 Fórmulas de Dano

| Tipo de Ataque | Fórmula |
|----------------|---------|
| **Melee Weapon** | Weapon Die Roll + STR Modifier |
| **Ranged Weapon** | Weapon Die Roll + DEX Modifier |
| **Spell** | Spell Damage (conforme descrição) |
| **Critical Hit** | (Weapon Die Roll × 2) + Modifier |

---

## 🔄 Algoritmo de Cálculo

### Passo 1: Calcular Dano Base do Ataque

```cpp
// Calcular dano base de ataque melee
int32 CalculateMeleeWeaponDamage(
    const FCharacterData& Attacker,
    FName WeaponName,
    bool bIsCritical = false)
{
    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* WeaponRow = ItemDataTable->FindRow<FItemDataRow>(WeaponName, TEXT("DamageCalculation"));

    if (!WeaponRow)
    {
        return 0;
    }

    // Obter dados da arma
    FString DamageDie = WeaponRow->WeaponData.FindRef(TEXT("DamageDie")); // Ex: "1d8"
    int32 STRModifier = GetAbilityModifier(Attacker, TEXT("Strength"));

    // Rolar dano
    int32 DieRoll = RollDamageDie(DamageDie, bIsCritical);

    // Calcular dano total
    int32 TotalDamage = DieRoll + STRModifier;

    return FMath::Max(TotalDamage, 1); // Mínimo 1 de dano
}

// Calcular dano base de ataque ranged
int32 CalculateRangedWeaponDamage(
    const FCharacterData& Attacker,
    FName WeaponName,
    bool bIsCritical = false)
{
    // Similar ao melee, mas usa DEX modifier
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* WeaponRow = ItemDataTable->FindRow<FItemDataRow>(WeaponName, TEXT("DamageCalculation"));

    if (!WeaponRow)
    {
        return 0;
    }

    FString DamageDie = WeaponRow->WeaponData.FindRef(TEXT("DamageDie"));
    int32 DEXModifier = GetAbilityModifier(Attacker, TEXT("Dexterity"));

    int32 DieRoll = RollDamageDie(DamageDie, bIsCritical);
    int32 TotalDamage = DieRoll + DEXModifier;

    return FMath::Max(TotalDamage, 1);
}
```

### Passo 2: Rolar Dados de Dano

```cpp
// Rolar dados de dano (com suporte a crítico)
int32 RollDamageDie(const FString& DamageDie, bool bIsCritical)
{
    // Parse: "1d8" -> Count=1, Sides=8
    int32 Count = 1;
    int32 Sides = 8;
    ParseDamageDie(DamageDie, Count, Sides);

    // Se crítico, dobra a quantidade de dados
    if (bIsCritical)
    {
        Count *= 2;
    }

    // Rolar dados
    int32 TotalRoll = 0;
    for (int32 i = 0; i < Count; i++)
    {
        TotalRoll += FMath::RandRange(1, Sides);
    }

    return TotalRoll;
}
```

### Passo 3: Calcular Dano de Magia

```cpp
// Calcular dano de magia
int32 CalculateSpellDamage(
    const FCharacterData& Caster,
    FName SpellName,
    int32 SpellLevel = 1)
{
    // Carregar SpellDataTable
    UDataTable* SpellDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Spells"));
    FSpellDataRow* SpellRow = SpellDataTable->FindRow<FSpellDataRow>(SpellName, TEXT("DamageCalculation"));

    if (!SpellRow)
    {
        return 0;
    }

    // Obter dano base da magia
    FString DamageDie = SpellRow->SpellData.FindRef(TEXT("DamageDie")); // Ex: "8d6"

    // Calcular dano base
    int32 BaseDamage = RollDamageDie(DamageDie, false);

    // Aplicar modificador de spellcasting ability (se aplicável)
    FName SpellcastingAbility = GetSpellcastingAbility(Caster);
    int32 AbilityModifier = GetAbilityModifier(Caster, SpellcastingAbility);

    // Nota: A maioria das magias não adiciona ability modifier ao dano
    // (exceto algumas específicas como Eldritch Blast)
    int32 TotalDamage = BaseDamage;

    return FMath::Max(TotalDamage, 0);
}
```

### Passo 4: Aplicar Crítico

```cpp
// Aplicar dano crítico (dobra dados, não modificador)
int32 ApplyCriticalDamage(int32 BaseDamage, int32 Modifier)
{
    // Crítico dobra apenas os dados, não o modificador
    // Exemplo: 1d8+3 crítico = 2d8+3 (não 2d8+6)

    // Nota: O cálculo já foi feito em RollDamageDie com bIsCritical=true
    // Aqui apenas retornamos o dano base + modificador
    return BaseDamage + Modifier;
}
```

### Passo 5: Aplicar Resistências e Vulnerabilidades

```cpp
// Aplicar resistências e vulnerabilidades
int32 ApplyResistanceAndVulnerability(
    int32 BaseDamage,
    FName DamageType,
    const FCharacterData& Target)
{
    // Verificar resistência
    if (HasResistance(Target, DamageType))
    {
        BaseDamage = FMath::FloorToInt(BaseDamage / 2.0f); // Reduz pela metade
    }

    // Verificar vulnerabilidade
    if (HasVulnerability(Target, DamageType))
    {
        BaseDamage *= 2; // Dobra o dano
    }

    return FMath::Max(BaseDamage, 0);
}
```

### Passo 6: Cálculo Completo de Dano

```cpp
// Calcular dano completo (ataque + crítico + resistências)
FDamageResult CalculateCompleteDamage(
    const FCharacterData& Attacker,
    const FCharacterData& Target,
    FName WeaponOrSpellName,
    FName DamageType,
    bool bIsCritical = false,
    bool bIsMelee = true)
{
    FDamageResult Result;

    // 1. Calcular dano base
    int32 BaseDamage = 0;
    if (bIsMelee)
    {
        BaseDamage = CalculateMeleeWeaponDamage(Attacker, WeaponOrSpellName, bIsCritical);
    }
    else
    {
        // Verificar se é ranged weapon ou spell
        if (IsSpell(WeaponOrSpellName))
        {
            BaseDamage = CalculateSpellDamage(Attacker, WeaponOrSpellName);
        }
        else
        {
            BaseDamage = CalculateRangedWeaponDamage(Attacker, WeaponOrSpellName, bIsCritical);
        }
    }

    // 2. Aplicar resistências/vulnerabilidades
    int32 FinalDamage = ApplyResistanceAndVulnerability(BaseDamage, DamageType, Target);

    Result.BaseDamage = BaseDamage;
    Result.FinalDamage = FinalDamage;
    Result.DamageType = DamageType;
    Result.bWasCritical = bIsCritical;
    Result.bWasResisted = (FinalDamage < BaseDamage);
    Result.bWasVulnerable = (FinalDamage > BaseDamage);

    return Result;
}
```

---

## 📊 Exemplos

### Exemplo 1: Ataque Melee Normal

```cpp
// Longsword (1d8), STR +3, ataque normal
FCharacterData Attacker;
Attacker.FinalStrength = 16; // Modifier +3

FDamageResult Result = CalculateCompleteDamage(
    Attacker,
    Target,
    TEXT("Longsword"),
    TEXT("Slashing"),
    false, // Não crítico
    true   // Melee
);
// DieRoll: 1d8 = 5
// BaseDamage: 5 + 3 = 8
// FinalDamage: 8 (sem resistências)
```

### Exemplo 2: Ataque Crítico

```cpp
// Longsword (1d8), STR +3, crítico
FDamageResult Result = CalculateCompleteDamage(
    Attacker,
    Target,
    TEXT("Longsword"),
    TEXT("Slashing"),
    true,  // Crítico
    true   // Melee
);
// DieRoll: 2d8 = 12 (dobrado)
// BaseDamage: 12 + 3 = 15
// FinalDamage: 15
```

### Exemplo 3: Dano com Resistência

```cpp
// Fireball (8d6), alvo com resistência a fogo
FDamageResult Result = CalculateCompleteDamage(
    Caster,
    Target, // Com resistência a Fire
    TEXT("Fireball"),
    TEXT("Fire"),
    false,
    false
);
// DieRoll: 8d6 = 28
// BaseDamage: 28
// FinalDamage: 14 (reduzido pela metade)
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate - Dano](../../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#cálculo-de-dano)** - Regras de dano D&D 5e

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [AC Calculation Algorithm](ac-calculation-algorithm.md) - Algoritmo de AC
> - [Attack Roll Algorithm](attack-roll-algorithm.md) - Algoritmo de ataque
> - [Pseudocódigo de Combate](../../../08-pseudocodigo/combate/) - Implementação técnica

</details>

---

**Navegação:** [← AC Calculation](ac-calculation-algorithm.md) | [→ Attack Roll](attack-roll-algorithm.md)

**Última atualização:** 2024-12-27
