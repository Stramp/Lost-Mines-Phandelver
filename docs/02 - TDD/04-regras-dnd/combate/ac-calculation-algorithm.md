# AC Calculation Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de cálculo de AC |

---

## 🎯 Objetivo

Algoritmo técnico de cálculo de Armor Class (AC) D&D 5e, definindo como calcular AC baseado em armadura, DEX modifier e escudo.

---

## 📋 Regras de AC por Tipo de Armadura

| Tipo | Fórmula | Limite DEX |
|------|---------|------------|
| **Sem Armadura** | 10 + DEX Modifier | Sem limite |
| **Light Armor** | Armor Base AC + DEX Modifier | Sem limite |
| **Medium Armor** | Armor Base AC + DEX Modifier | Máximo +2 |
| **Heavy Armor** | Armor Base AC | Sem bônus de DEX |
| **Shield** | AC Atual + 2 | - |

---

## 🔄 Algoritmo de Cálculo

### Passo 1: Determinar Tipo de Armadura

```cpp
// Determinar tipo de armadura equipada
FName GetArmorType(const FCharacterData& CharacterData)
{
    if (!CharacterData.EquippedArmor)
    {
        return TEXT("None"); // Sem armadura
    }

    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* ArmorRow = ItemDataTable->FindRow<FItemDataRow>(
        CharacterData.EquippedArmor, TEXT("ACCalculation"));

    if (!ArmorRow)
    {
        return TEXT("None");
    }

    // Verificar tipo de armadura
    if (ArmorRow->ItemType == TEXT("LightArmor"))
    {
        return TEXT("Light");
    }
    else if (ArmorRow->ItemType == TEXT("MediumArmor"))
    {
        return TEXT("Medium");
    }
    else if (ArmorRow->ItemType == TEXT("HeavyArmor"))
    {
        return TEXT("Heavy");
    }

    return TEXT("None");
}
```

### Passo 2: Obter AC Base da Armadura

```cpp
// Obter AC base da armadura
int32 GetArmorBaseAC(const FCharacterData& CharacterData)
{
    if (!CharacterData.EquippedArmor)
    {
        return 10; // AC base sem armadura
    }

    // Carregar ItemDataTable
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Items"));
    FItemDataRow* ArmorRow = ItemDataTable->FindRow<FItemDataRow>(
        CharacterData.EquippedArmor, TEXT("ACCalculation"));

    if (!ArmorRow)
    {
        return 10;
    }

    // Obter AC base do ArmorData
    return ArmorRow->ArmorData.FindRef(TEXT("BaseAC"));
}
```

### Passo 3: Calcular Bônus de DEX

```cpp
// Calcular bônus de DEX aplicável ao AC
int32 CalculateDexterityBonusForAC(
    const FCharacterData& CharacterData,
    FName ArmorType)
{
    int32 DEXModifier = GetAbilityModifier(CharacterData, TEXT("Dexterity"));

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
```

### Passo 4: Calcular Bônus de Escudo

```cpp
// Calcular bônus de escudo
int32 CalculateShieldBonus(const FCharacterData& CharacterData)
{
    if (CharacterData.EquippedShield)
    {
        return 2; // Escudo sempre dá +2 AC
    }
    return 0;
}
```

### Passo 5: Cálculo Completo de AC

```cpp
// Calcular AC completo
int32 CalculateAC(const FCharacterData& CharacterData)
{
    // 1. Determinar tipo de armadura
    FName ArmorType = GetArmorType(CharacterData);

    // 2. Obter AC base
    int32 BaseAC = GetArmorBaseAC(CharacterData);

    // 3. Calcular bônus de DEX
    int32 DEXBonus = CalculateDexterityBonusForAC(CharacterData, ArmorType);

    // 4. Calcular bônus de escudo
    int32 ShieldBonus = CalculateShieldBonus(CharacterData);

    // 5. Calcular AC final
    int32 FinalAC = BaseAC + DEXBonus + ShieldBonus;

    return FinalAC;
}
```

---

## 📊 Exemplos

### Exemplo 1: Sem Armadura, DEX +3

```cpp
FCharacterData CharacterData;
CharacterData.EquippedArmor = NAME_None;
CharacterData.FinalDexterity = 16; // Modifier +3

int32 AC = CalculateAC(CharacterData);
// BaseAC = 10
// DEXBonus = +3
// ShieldBonus = 0
// AC = 10 + 3 + 0 = 13
```

### Exemplo 2: Leather Armor (Light), DEX +3

```cpp
FCharacterData CharacterData;
CharacterData.EquippedArmor = TEXT("LeatherArmor"); // Base AC 11
CharacterData.FinalDexterity = 16; // Modifier +3

int32 AC = CalculateAC(CharacterData);
// BaseAC = 11
// DEXBonus = +3 (sem limite)
// ShieldBonus = 0
// AC = 11 + 3 + 0 = 14
```

### Exemplo 3: Scale Mail (Medium), DEX +4, Escudo

```cpp
FCharacterData CharacterData;
CharacterData.EquippedArmor = TEXT("ScaleMail"); // Base AC 14
CharacterData.FinalDexterity = 18; // Modifier +4 (limitado a +2)
CharacterData.EquippedShield = TEXT("Shield");

int32 AC = CalculateAC(CharacterData);
// BaseAC = 14
// DEXBonus = +2 (limitado, não +4)
// ShieldBonus = +2
// AC = 14 + 2 + 2 = 18
```

### Exemplo 4: Chain Mail (Heavy), Escudo

```cpp
FCharacterData CharacterData;
CharacterData.EquippedArmor = TEXT("ChainMail"); // Base AC 16
CharacterData.FinalDexterity = 18; // Modifier +4 (não aplica)
CharacterData.EquippedShield = TEXT("Shield");

int32 AC = CalculateAC(CharacterData);
// BaseAC = 16
// DEXBonus = 0 (Heavy Armor não usa DEX)
// ShieldBonus = +2
// AC = 16 + 0 + 2 = 18
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate - AC](../../../../01%20-%20GDD/02-mecanicas/sistema-combate.md#armor-class-ac---classe-de-armadura)** - Regras de AC D&D 5e

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Damage Calculation Algorithm](damage-calculation-algorithm.md) - Algoritmo de dano
> - [Attack Roll Algorithm](attack-roll-algorithm.md) - Algoritmo de ataque
> - [Pseudocódigo de Combate](../../../08-pseudocodigo/combate/) - Implementação técnica

</details>

---

**Navegação:** [← Voltar](index.md) | [→ Damage Calculation](damage-calculation-algorithm.md)

**Última atualização:** 2024-12-27
