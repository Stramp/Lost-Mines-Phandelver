# AC Calculation - Pseudocódigo Técnico

---

## 🎯 Objetivo

Especificação técnica de implementação do cálculo de AC, incluindo estruturas C++ e componentes.

---

## 📐 Estrutura de Dados

### FArmorData

```cpp
USTRUCT(BlueprintType)
struct FArmorData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName ArmorName;

    UPROPERTY(BlueprintReadOnly)
    int32 BaseAC;

    UPROPERTY(BlueprintReadOnly)
    FName ArmorType; // Light, Medium, Heavy

    UPROPERTY(BlueprintReadOnly)
    int32 MaxDexBonus; // -1 = sem limite, 0 = sem bônus de DEX
};
```

### FACCalculationResult

```cpp
USTRUCT(BlueprintType)
struct FACCalculationResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 FinalAC;

    UPROPERTY(BlueprintReadOnly)
    int32 BaseAC;

    UPROPERTY(BlueprintReadOnly)
    int32 DexBonus;

    UPROPERTY(BlueprintReadOnly)
    int32 ShieldBonus;

    UPROPERTY(BlueprintReadOnly)
    FString CalculationBreakdown;
};
```

---

## 🏗️ Implementação

### UCombatComponent::CalculateAC()

```cpp
// Calcular AC completo
int32 UCombatComponent::CalculateAC() const
{
    // 1. Obter AC base
    int32 BaseAC = GetArmorBaseAC();

    // 2. Calcular bônus de DEX
    int32 DexBonus = CalculateDexterityBonusForAC();

    // 3. Calcular bônus de escudo
    int32 ShieldBonus = CalculateShieldBonus();

    // 4. Calcular AC final
    int32 FinalAC = BaseAC + DexBonus + ShieldBonus;

    return FinalAC;
}

// Obter AC base da armadura
int32 UCombatComponent::GetArmorBaseAC() const
{
    if (!CombatData.EquippedArmor)
    {
        return 10; // AC base sem armadura
    }

    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* ArmorRow = ItemDataTable->FindRow<FItemDataRow>(
        CombatData.EquippedArmor, TEXT("ACCalculation"));

    if (!ArmorRow)
    {
        return 10;
    }

    return ArmorRow->ArmorData.BaseAC;
}

// Calcular bônus de DEX aplicável
int32 UCombatComponent::CalculateDexterityBonusForAC() const
{
    if (!CharacterDataComponent)
    {
        return 0;
    }

    int32 DEXModifier = CharacterDataComponent->GetAbilityModifier(TEXT("Dexterity"));
    FName ArmorType = GetArmorType();

    if (ArmorType == TEXT("None") || ArmorType == TEXT("Light"))
    {
        return DEXModifier; // Sem limite
    }
    else if (ArmorType == TEXT("Medium"))
    {
        return FMath::Min(DEXModifier, 2); // Máximo +2
    }
    else if (ArmorType == TEXT("Heavy"))
    {
        return 0; // Sem bônus de DEX
    }

    return 0;
}

// Calcular bônus de escudo
int32 UCombatComponent::CalculateShieldBonus() const
{
    if (CombatData.EquippedShield)
    {
        return 2; // Escudo sempre dá +2 AC
    }
    return 0;
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate - AC](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#armor-class-ac---classe-de-armadura)** - Regras de AC D&D 5e
>
> - **GDD:** Define O QUÊ (AC baseado em armadura, DEX, shield) e PORQUÊ (defesa D&D 5e)
> - **TDD Seção 04:** Define algoritmos técnicos (como calcular AC)
> - **TDD Seção 08:** Define pseudocódigo técnico (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Algoritmos (TDD)</b></summary>

> - [AC Calculation Algorithm](../../04-regras-dnd/combate/ac-calculation-algorithm.md) - Algoritmo técnico
> - [Combat System](combat-system.md) - Sistema completo

</details>

---

**Navegação:** [← Combat System](combat-system.md) | [→ Damage Calculation](damage-calculation.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do pseudocódigo técnico de AC |
