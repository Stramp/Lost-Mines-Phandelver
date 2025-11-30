# Attack Verification - Pseudocódigo Técnico

---

## 🎯 Objetivo

Especificação técnica de implementação da verificação de acerto, incluindo estruturas C++ e componentes.

---

## 📐 Estrutura de Dados

### FAttackResult

```cpp
USTRUCT(BlueprintType)
struct FAttackResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bHit;

    UPROPERTY(BlueprintReadOnly)
    bool bIsCritical;

    UPROPERTY(BlueprintReadOnly)
    bool bIsCriticalMiss;

    UPROPERTY(BlueprintReadOnly)
    int32 AttackRoll;

    UPROPERTY(BlueprintReadOnly)
    int32 TargetAC;

    UPROPERTY(BlueprintReadOnly)
    int32 DieRoll;
};
```

---

## 🏗️ Implementação

### UCombatComponent::PerformAttack()

```cpp
// Realizar ataque completo
FAttackResult UCombatComponent::PerformAttack(
    AActor* Target,
    FName WeaponName) const
{
    FAttackResult Result;

    if (!Target)
    {
        Result.bHit = false;
        return Result;
    }

    // 1. Rolar d20
    int32 DieRoll = FMath::RandRange(1, 20);
    Result.DieRoll = DieRoll;

    // 2. Verificar natural 20 (crítico)
    if (DieRoll == 20)
    {
        Result.bHit = true;
        Result.bIsCritical = true;
        Result.bIsNatural20 = true;
        return Result; // Crítico sempre acerta
    }

    // 3. Verificar natural 1 (falha crítica)
    if (DieRoll == 1)
    {
        Result.bHit = false;
        Result.bIsCriticalMiss = true;
        Result.bIsNatural1 = true;
        return Result; // Natural 1 sempre erra
    }

    // 4. Calcular attack roll completo
    int32 AttackRoll = CalculateAttackRoll(WeaponName);
    Result.AttackRoll = AttackRoll;

    // 5. Obter AC do alvo
    UCombatComponent* TargetCombat = Target->FindComponentByClass<UCombatComponent>();
    if (!TargetCombat)
    {
        Result.bHit = false;
        return Result;
    }

    int32 TargetAC = TargetCombat->CalculateAC();
    Result.TargetAC = TargetAC;

    // 6. Comparar attack roll com AC
    Result.bHit = (AttackRoll >= TargetAC);

    return Result;
}

// Calcular attack roll
int32 UCombatComponent::CalculateAttackRoll(FName WeaponName) const
{
    if (!CharacterDataComponent)
    {
        return 0;
    }

    // Rolar d20
    int32 DieRoll = FMath::RandRange(1, 20);

    // Obter modificadores
    int32 ProficiencyBonus = CharacterDataComponent->GetProficiencyBonus();
    int32 AbilityModifier = GetAbilityModifierForWeapon(WeaponName);

    // Verificar proficiência
    bool bHasProficiency = HasWeaponProficiency(WeaponName);

    // Calcular attack roll
    int32 AttackRoll = DieRoll;

    if (bHasProficiency)
    {
        AttackRoll += ProficiencyBonus;
    }

    AttackRoll += AbilityModifier;

    return AttackRoll;
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
    FItemDataRow* WeaponRow = ItemDataTable->FindRow<FItemDataRow>(WeaponName, TEXT("AttackVerification"));

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

---

## 📖 Design Relacionado

Este documento implementa as seguintes regras de design:

- **[GDD: Sistema de Combate - Ataques](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#ataques-e-acertos)** - Regras de ataque D&D 5e

- **GDD:** Define O QUÊ (natural 20/1, advantage/disadvantage, spell attacks) e PORQUÊ (combate D&D 5e)
- **TDD Seção 04:** Define algoritmos técnicos (como verificar acerto)
- **TDD Seção 08:** Define pseudocódigo técnico (estruturas C++, classes, componentes)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Algoritmos (TDD)</b></summary>

> - [Attack Roll Algorithm](../../04-regras-dnd/combate/attack-roll-algorithm.md) - Algoritmo técnico
> - [Combat System](combat-system.md) - Sistema completo

</details>

---

**Navegação:** [← Damage Calculation](damage-calculation.md) | [→ Voltar para Index](index.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do pseudocódigo técnico de verificação de ataque |
