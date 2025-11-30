# Damage Calculation - Pseudocódigo Técnico

---

## 🎯 Objetivo

Especificação técnica de implementação do cálculo de dano, incluindo estruturas C++ e componentes.

---

## 📐 Estrutura de Dados

### FWeaponData

```cpp
USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName WeaponName;

    UPROPERTY(BlueprintReadOnly)
    FString DamageDie; // Ex: "1d8"

    UPROPERTY(BlueprintReadOnly)
    FName DamageType; // Slashing, Piercing, Bludgeoning

    UPROPERTY(BlueprintReadOnly)
    FName WeaponType; // Melee, Ranged
};
```

### FDamageResult

```cpp
USTRUCT(BlueprintType)
struct FDamageResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 BaseDamage;

    UPROPERTY(BlueprintReadOnly)
    int32 FinalDamage;

    UPROPERTY(BlueprintReadOnly)
    FName DamageType;

    UPROPERTY(BlueprintReadOnly)
    bool bWasCritical;

    UPROPERTY(BlueprintReadOnly)
    bool bWasResisted;

    UPROPERTY(BlueprintReadOnly)
    bool bWasVulnerable;
};
```

---

## 🏗️ Implementação

### UCombatComponent::CalculateDamage()

```cpp
// Calcular dano completo
FDamageResult UCombatComponent::CalculateDamage(
    const FAttackResult& AttackResult,
    FName WeaponName,
    FName DamageType) const
{
    FDamageResult Result;

    // 1. Calcular dano base
    int32 BaseDamage = CalculateBaseDamage(WeaponName, AttackResult.bIsCritical);
    Result.BaseDamage = BaseDamage;

    // 2. Aplicar modificador de atributo
    int32 AbilityModifier = GetAbilityModifierForWeapon(WeaponName);
    int32 TotalDamage = BaseDamage + AbilityModifier;

    // 3. Aplicar resistências/vulnerabilidades (no alvo)
    // Nota: Isso é feito no alvo, não no atacante

    Result.DamageType = DamageType;
    Result.bWasCritical = AttackResult.bIsCritical;

    return Result;
}

// Calcular dano base
int32 UCombatComponent::CalculateBaseDamage(FName WeaponName, bool bIsCritical) const
{
    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* WeaponRow = ItemDataTable->FindRow<FItemDataRow>(WeaponName, TEXT("DamageCalculation"));

    if (!WeaponRow)
    {
        return 0;
    }

    FString DamageDie = WeaponRow->WeaponData.DamageDie;

    // Rolar dano
    int32 DieRoll = RollDamageDie(DamageDie, bIsCritical);

    return DieRoll;
}

// Rolar dados de dano
int32 UCombatComponent::RollDamageDie(const FString& DamageDie, bool bIsCritical) const
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

// Obter modificador de atributo para arma
int32 UCombatComponent::GetAbilityModifierForWeapon(FName WeaponName) const
{
    if (!CharacterDataComponent)
    {
        return 0;
    }

    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* WeaponRow = ItemDataTable->FindRow<FItemDataRow>(WeaponName, TEXT("DamageCalculation"));

    if (!WeaponRow)
    {
        return 0;
    }

    // Melee usa STR, Ranged usa DEX
    if (WeaponRow->WeaponData.WeaponType == TEXT("Melee"))
    {
        return CharacterDataComponent->GetAbilityModifier(TEXT("Strength"));
    }
    else if (WeaponRow->WeaponData.WeaponType == TEXT("Ranged"))
    {
        return CharacterDataComponent->GetAbilityModifier(TEXT("Dexterity"));
    }

    return 0;
}
```

### UCombatComponent::ApplyResistanceAndVulnerability()

```cpp
// Aplicar resistências e vulnerabilidades (chamado no alvo)
int32 UCombatComponent::ApplyResistanceAndVulnerability(
    int32 BaseDamage,
    FName DamageType) const
{
    int32 FinalDamage = BaseDamage;

    // Verificar resistência
    if (CombatData.Resistances.Contains(DamageType))
    {
        FinalDamage = FMath::FloorToInt(FinalDamage / 2.0f); // Reduz pela metade
    }

    // Verificar vulnerabilidade
    if (CombatData.Vulnerabilities.Contains(DamageType))
    {
        FinalDamage *= 2; // Dobra o dano
    }

    return FMath::Max(FinalDamage, 0);
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate - Dano](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#cálculo-de-dano)** - Regras de dano D&D 5e
>
> - **GDD:** Define O QUÊ (dano base, modificadores, críticos, resistências) e PORQUÊ (combate D&D 5e)
> - **TDD Seção 04:** Define algoritmos técnicos (como calcular dano)
> - **TDD Seção 08:** Define pseudocódigo técnico (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Algoritmos (TDD)</b></summary>

> - [Damage Calculation Algorithm](../../04-regras-dnd/combate/damage-calculation-algorithm.md) - Algoritmo técnico
> - [Combat System](combat-system.md) - Sistema completo

</details>

---

**Navegação:** [← AC Calculation](ac-calculation.md) | [→ Attack Verification](attack-verification.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do pseudocódigo técnico de dano |
