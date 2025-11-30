# Spellcasting Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de spellcasting |

---

## 🎯 Objetivo

Algoritmo técnico de spellcasting D&D 5e, definindo como calcular Spell Save DC, Spell Attack, Spell Slots e aplicar magias.

---

## 📋 Fórmulas de Spellcasting

| Cálculo | Fórmula |
|---------|---------|
| **Spell Save DC** | 8 + Proficiency Bonus + Spellcasting Ability Modifier |
| **Spell Attack** | d20 + Proficiency Bonus + Spellcasting Ability Modifier |
| **Spells Prepared** | Spellcasting Ability Modifier + Class Level (mínimo 1) |

---

## 🔄 Algoritmo de Cálculo

### Passo 1: Calcular Spell Save DC

```cpp
// Calcular Spell Save DC
int32 CalculateSpellSaveDC(const FCharacterData& CharacterData)
{
    int32 ProficiencyBonus = CharacterData.ProficiencyBonus;
    FName SpellcastingAbility = GetSpellcastingAbility(CharacterData);
    int32 AbilityModifier = GetAbilityModifier(CharacterData, SpellcastingAbility);

    int32 SpellSaveDC = 8 + ProficiencyBonus + AbilityModifier;

    return SpellSaveDC;
}
```

### Passo 2: Calcular Spell Attack Modifier

```cpp
// Calcular Spell Attack Modifier
int32 CalculateSpellAttackModifier(const FCharacterData& CharacterData)
{
    int32 ProficiencyBonus = CharacterData.ProficiencyBonus;
    FName SpellcastingAbility = GetSpellcastingAbility(CharacterData);
    int32 AbilityModifier = GetAbilityModifier(CharacterData, SpellcastingAbility);

    int32 SpellAttackModifier = ProficiencyBonus + AbilityModifier;

    return SpellAttackModifier;
}
```

### Passo 3: Obter Spellcasting Ability

```cpp
// Obter spellcasting ability da classe
FName GetSpellcastingAbility(const FCharacterData& CharacterData)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));

    // Verificar cada classe do personagem
    for (const auto& Pair : CharacterData.ClassLevels)
    {
        FName ClassName = Pair.Key;
        FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(ClassName, TEXT("Spellcasting"));

        if (ClassRow && ClassRow->bIsSpellcaster)
        {
            return ClassRow->SpellcastingAbility;
        }
    }

    return NAME_None; // Não é spellcaster
}
```

### Passo 4: Calcular Spell Slots

```cpp
// Calcular spell slots disponíveis
TMap<int32, int32> CalculateSpellSlots(const FCharacterData& CharacterData)
{
    TMap<int32, int32> SpellSlots;

    // Calcular caster level
    int32 CasterLevel = CalculateCasterLevel(CharacterData);

    // Obter tabela de spell slots
    TMap<int32, TMap<int32, int32>> SpellSlotTable = GetSpellSlotTable();

    if (SpellSlotTable.Contains(CasterLevel))
    {
        SpellSlots = SpellSlotTable[CasterLevel];
    }

    return SpellSlots;
}

// Calcular caster level (para multiclassing)
int32 CalculateCasterLevel(const FCharacterData& CharacterData)
{
    int32 FullCasterLevels = 0;
    int32 HalfCasterLevels = 0;

    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));

    for (const auto& Pair : CharacterData.ClassLevels)
    {
        FName ClassName = Pair.Key;
        int32 ClassLevel = Pair.Value;

        FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(ClassName, TEXT("Spellcasting"));

        if (ClassRow)
        {
            if (ClassRow->CasterType == TEXT("Full"))
            {
                FullCasterLevels += ClassLevel;
            }
            else if (ClassRow->CasterType == TEXT("Half"))
            {
                HalfCasterLevels += ClassLevel;
            }
        }
    }

    // Fórmula: FullCasterLevels + floor(HalfCasterLevels / 2)
    int32 CasterLevel = FullCasterLevels + FMath::FloorToInt(HalfCasterLevels / 2.0f);

    return CasterLevel;
}
```

### Passo 5: Verificar se Pode Conjurar Magia

```cpp
// Verificar se pode conjurar magia
bool CanCastSpell(
    const FCharacterData& CharacterData,
    FName SpellName,
    int32 SpellLevel)
{
    // 1. Verificar se tem spell slot do nível necessário
    TMap<int32, int32> SpellSlots = CalculateSpellSlots(CharacterData);

    if (!SpellSlots.Contains(SpellLevel) || SpellSlots[SpellLevel] <= 0)
    {
        return false; // Sem spell slots disponíveis
    }

    // 2. Verificar se conhece/prepara a magia
    if (!KnowsSpell(CharacterData, SpellName))
    {
        return false; // Não conhece a magia
    }

    // 3. Verificar componentes (se aplicável)
    if (!HasSpellComponents(CharacterData, SpellName))
    {
        return false; // Sem componentes necessários
    }

    return true;
}
```

### Passo 6: Conjurar Magia

```cpp
// Conjurar magia
FSpellCastResult CastSpell(
    FCharacterData& CharacterData,
    FName SpellName,
    int32 SpellLevel,
    AActor* Target = nullptr)
{
    FSpellCastResult Result;

    // 1. Validar se pode conjurar
    if (!CanCastSpell(CharacterData, SpellName, SpellLevel))
    {
        Result.bSuccess = false;
        Result.ErrorMessage = TEXT("Não pode conjurar esta magia");
        return Result;
    }

    // 2. Gastar spell slot
    TMap<int32, int32>& SpellSlots = CharacterData.SpellSlots;
    if (SpellSlots.Contains(SpellLevel))
    {
        SpellSlots[SpellLevel]--;
    }

    // 3. Calcular efeito da magia
    FSpellEffect SpellEffect = CalculateSpellEffect(CharacterData, SpellName, SpellLevel, Target);

    // 4. Aplicar efeito
    ApplySpellEffect(SpellEffect, Target);

    Result.bSuccess = true;
    Result.SpellEffect = SpellEffect;

    return Result;
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Spellcasting](../../../../01%20-%20GDD/02-mecanicas/spellcasting.md)** - Regras de spellcasting D&D 5e
> - **[GDD: Sistemas de Personagem - Spellcasting](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#spellcasting-básico)** - Spellcasting básico
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Level Up Algorithm](level-up-algorithm.md) - Algoritmo de level up
> - [API - Componentes](../../../02-api/componentes/index.md) - Componentes de personagem

</details>

---

**Navegação:** [← Level Up Algorithm](level-up-algorithm.md) | [→ Sistemas Algorithms](../sistemas/index.md)

**Última atualização:** 2024-12-27
