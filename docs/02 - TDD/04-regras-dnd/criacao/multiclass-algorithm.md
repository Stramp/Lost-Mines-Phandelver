# Multiclass Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de multiclassing |

---

## 🎯 Objetivo

Algoritmo técnico de validação e aplicação de multiclassing D&D 5e, definindo como validar pré-requisitos e aplicar proficiências.

---

## 📋 Pré-requisitos por Classe

| Classe | Pré-requisitos |
|--------|----------------|
| **Barbarian** | STR 13 |
| **Bard** | CHA 13 |
| **Cleric** | WIS 13 |
| **Druid** | WIS 13 |
| **Fighter** | STR 13 **OU** DEX 13 |
| **Monk** | DEX 13 **E** WIS 13 |
| **Paladin** | STR 13 **E** CHA 13 |
| **Ranger** | DEX 13 **E** WIS 13 |
| **Rogue** | DEX 13 |
| **Sorcerer** | CHA 13 |
| **Warlock** | CHA 13 |
| **Wizard** | INT 13 |

**Nota:** Pré-requisitos são baseados nos **Final Ability Scores** (após bônus raciais e ASI).

---

## 🔄 Algoritmo de Validação

### Passo 1: Validar Pré-requisitos da Classe Atual

```cpp
// Validar que personagem atende pré-requisitos da classe atual
bool ValidateCurrentClassPrerequisites(
    const FCharacterData& CharacterData,
    FName CurrentClass)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));
    FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(CurrentClass, TEXT("Multiclass"));

    if (!ClassRow)
    {
        return false;
    }

    // Validar pré-requisitos da classe atual
    return ValidateClassPrerequisites(CharacterData, ClassRow->Prerequisites);
}
```

### Passo 2: Validar Pré-requisitos da Nova Classe

```cpp
// Validar que personagem atende pré-requisitos da nova classe
bool ValidateNewClassPrerequisites(
    const FCharacterData& CharacterData,
    FName NewClass)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));
    FClassDataRow* NewClassRow = ClassDataTable->FindRow<FClassDataRow>(NewClass, TEXT("Multiclass"));

    if (!NewClassRow)
    {
        return false;
    }

    // Validar pré-requisitos da nova classe
    return ValidateClassPrerequisites(CharacterData, NewClassRow->Prerequisites);
}
```

### Passo 3: Validar Pré-requisitos Específicos

```cpp
// Validar pré-requisitos específicos de uma classe
bool ValidateClassPrerequisites(
    const FCharacterData& CharacterData,
    const TArray<FClassPrerequisite>& Prerequisites)
{
    for (const FClassPrerequisite& Prereq : Prerequisites)
    {
        int32 FinalScore = GetFinalAbilityScore(CharacterData, Prereq.AbilityName);

        // Validar operador (AND, OR)
        if (Prereq.Operator == TEXT("AND"))
        {
            if (FinalScore < Prereq.RequiredScore)
            {
                return false; // Falha em pré-requisito AND
            }
        }
        else if (Prereq.Operator == TEXT("OR"))
        {
            // Para OR, pelo menos um deve passar
            // (validado separadamente para cada pré-requisito OR)
        }
    }

    return true;
}

// Exemplo: Fighter (STR 13 OU DEX 13)
bool ValidateFighterPrerequisites(const FCharacterData& CharacterData)
{
    int32 FinalSTR = GetFinalAbilityScore(CharacterData, TEXT("Strength"));
    int32 FinalDEX = GetFinalAbilityScore(CharacterData, TEXT("Dexterity"));

    return (FinalSTR >= 13 || FinalDEX >= 13);
}

// Exemplo: Monk (DEX 13 E WIS 13)
bool ValidateMonkPrerequisites(const FCharacterData& CharacterData)
{
    int32 FinalDEX = GetFinalAbilityScore(CharacterData, TEXT("Dexterity"));
    int32 FinalWIS = GetFinalAbilityScore(CharacterData, TEXT("Wisdom"));

    return (FinalDEX >= 13 && FinalWIS >= 13);
}
```

### Passo 4: Validar Nível Total

```cpp
// Validar que nível total não excede 20
bool ValidateTotalLevel(const FCharacterData& CharacterData)
{
    int32 TotalLevel = CalculateTotalLevel(CharacterData);
    return TotalLevel < 20; // Pode multiclassar se < 20
}

int32 CalculateTotalLevel(const FCharacterData& CharacterData)
{
    int32 TotalLevel = 0;
    for (const auto& Pair : CharacterData.ClassLevels)
    {
        TotalLevel += Pair.Value;
    }
    return TotalLevel;
}
```

### Passo 5: Validação Completa

```cpp
// Validação completa de multiclassing
FMulticlassValidationResult ValidateMulticlassing(
    const FCharacterData& CharacterData,
    FName CurrentClass,
    FName NewClass)
{
    // 1. Validar pré-requisitos da classe atual
    if (!ValidateCurrentClassPrerequisites(CharacterData, CurrentClass))
    {
        return FMulticlassValidationResult(false, TEXT("Não atende pré-requisitos da classe atual"));
    }

    // 2. Validar pré-requisitos da nova classe
    if (!ValidateNewClassPrerequisites(CharacterData, NewClass))
    {
        return FMulticlassValidationResult(false, TEXT("Não atende pré-requisitos da nova classe"));
    }

    // 3. Validar nível total
    if (!ValidateTotalLevel(CharacterData))
    {
        return FMulticlassValidationResult(false, TEXT("Nível total já é 20"));
    }

    // 4. Validar que não está tentando adicionar classe que já tem
    if (CharacterData.ClassLevels.Contains(NewClass))
    {
        return FMulticlassValidationResult(false, TEXT("Já possui esta classe"));
    }

    return FMulticlassValidationResult(true, TEXT("Multiclassing válido"));
}
```

---

## 🔄 Algoritmo de Aplicação

### Passo 1: Adicionar Nível na Nova Classe

```cpp
// Adicionar nível na nova classe
void AddClassLevel(FCharacterData& CharacterData, FName NewClass)
{
    // Incrementar nível da classe
    if (CharacterData.ClassLevels.Contains(NewClass))
    {
        CharacterData.ClassLevels[NewClass]++;
    }
    else
    {
        CharacterData.ClassLevels.Add(NewClass, 1);
    }

    // Recalcular nível total
    CharacterData.TotalLevel = CalculateTotalLevel(CharacterData);
}
```

### Passo 2: Aplicar Proficiências Limitadas

```cpp
// Aplicar proficiências limitadas ao multiclassar
void ApplyMulticlassProficiencies(
    FCharacterData& CharacterData,
    FName NewClass)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));
    FClassDataRow* NewClassRow = ClassDataTable->FindRow<FClassDataRow>(NewClass, TEXT("Multiclass"));

    if (!NewClassRow)
    {
        return;
    }

    // Ganha proficiência em UMA skill da nova classe
    // (escolha do jogador, não automática)

    // Ganha proficiências de armadura/armas conforme classe
    for (const FClassProficiency& Proficiency : NewClassRow->Proficiencies)
    {
        // Aplicar apenas se não tiver já
        if (!HasProficiency(CharacterData, Proficiency))
        {
            AddProficiency(CharacterData, Proficiency);
        }
    }
}
```

### Passo 3: Aplicar Features de Nível

```cpp
// Aplicar features da nova classe no nível atual
void ApplyClassFeaturesForLevel(
    FCharacterData& CharacterData,
    FName NewClass,
    int32 Level)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));
    FClassDataRow* NewClassRow = ClassDataTable->FindRow<FClassDataRow>(NewClass, TEXT("Multiclass"));

    if (!NewClassRow)
    {
        return;
    }

    // Obter features para este nível
    TArray<FClassFeature> Features = GetFeaturesForLevel(NewClassRow, Level);

    // Aplicar cada feature
    for (const FClassFeature& Feature : Features)
    {
        ApplyFeature(CharacterData, Feature);
    }
}
```

### Passo 4: Recalcular Stats Derivados

```cpp
// Recalcular stats derivados após multiclassing
void RecalculateDerivedStats(FCharacterData& CharacterData)
{
    // 1. Recalcular Proficiency Bonus (baseado em TotalLevel)
    int32 ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(CharacterData.TotalLevel);
    CharacterData.ProficiencyBonus = ProficiencyBonus;

    // 2. Recalcular HP (soma de todos os Hit Dice)
    int32 NewMaxHP = CalculateMaxHP(CharacterData);
    CharacterData.MaxHP = NewMaxHP;

    // 3. Recalcular Spell Slots (se aplicável)
    if (HasSpellcasting(CharacterData))
    {
        RecalculateSpellSlots(CharacterData);
    }
}
```

---

## 📊 Exemplo Completo

### Exemplo: Fighter 3 → Rogue 1

```cpp
// Personagem: Fighter nível 3, quer adicionar Rogue nível 1

// 1. Validar pré-requisitos
FCharacterData CharacterData;
CharacterData.FinalDexterity = 14; // Atende DEX 13 para Rogue

FMulticlassValidationResult Validation = ValidateMulticlassing(
    CharacterData,
    TEXT("Fighter"),
    TEXT("Rogue")
);
// Resultado: ✅ Válido (DEX 14 >= 13)

// 2. Adicionar nível
AddClassLevel(CharacterData, TEXT("Rogue"));
// CharacterData.ClassLevels: {Fighter: 3, Rogue: 1}
// CharacterData.TotalLevel: 4

// 3. Aplicar proficiências limitadas
ApplyMulticlassProficiencies(CharacterData, TEXT("Rogue"));
// Ganha: UMA skill de Rogue (escolha do jogador)
// Ganha: Light Armor proficiency (se não tiver)
// Ganha: Thieves' Tools proficiency (se não tiver)

// 4. Aplicar features de nível 1 de Rogue
ApplyClassFeaturesForLevel(CharacterData, TEXT("Rogue"), 1);
// Ganha: Sneak Attack (1d6)
// Ganha: Expertise (2 skills)

// 5. Recalcular stats
RecalculateDerivedStats(CharacterData);
// Proficiency Bonus: +2 (nível 4)
// HP: +1d8 (Hit Die de Rogue)
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Multiclassing](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#multiclassing)** - Regras D&D 5e de multiclassing
>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](character-creation-algorithm.md) - Algoritmo completo
> - [API - MulticlassMotor](../../../02-api/motores/index.md) - Motor de Multiclassing
> - [API - ValidationHelpers](../../../02-api/helpers/index.md) - Helpers de validação

</details>

---

**Navegação:** [← Point Buy Algorithm](point-buy-algorithm.md) | [→ Combate Algorithms](../combate/index.md)

**Última atualização:** 2024-12-27
