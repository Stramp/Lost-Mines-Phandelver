# Level Up Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de level up |

---

## 🎯 Objetivo

Algoritmo técnico de level up D&D 5e, definindo como aplicar melhorias de nível, ASI, features e recalcular stats derivados.

---

## 📋 Melhorias por Nível

| Nível | Melhorias Típicas |
|-------|-------------------|
| **1** | Features iniciais, Proficiências |
| **2** | Features de classe |
| **3** | Subclass Selection |
| **4, 8, 12, 16, 19** | ASI ou Feat |
| **5+** | Extra Attack, Features avançadas |

---

## 🔄 Algoritmo de Level Up

### Passo 1: Validar Level Up

```cpp
// Validar que pode fazer level up
bool ValidateLevelUp(
    const FCharacterData& CharacterData,
    FName ClassToLevel,
    int32 CurrentXP,
    int32 RequiredXP)
{
    // 1. Validar que tem XP suficiente
    if (CurrentXP < RequiredXP)
    {
        return false; // XP insuficiente
    }

    // 2. Validar que nível total não excede 20
    int32 TotalLevel = CalculateTotalLevel(CharacterData);
    if (TotalLevel >= 20)
    {
        return false; // Já está no nível máximo
    }

    // 3. Validar que a classe existe
    if (!CharacterData.ClassLevels.Contains(ClassToLevel))
    {
        return false; // Classe não encontrada
    }

    return true;
}
```

### Passo 2: Incrementar Nível da Classe

```cpp
// Incrementar nível da classe
void IncrementClassLevel(FCharacterData& CharacterData, FName ClassToLevel)
{
    // Incrementar nível
    CharacterData.ClassLevels[ClassToLevel]++;

    // Recalcular nível total
    CharacterData.TotalLevel = CalculateTotalLevel(CharacterData);
}
```

### Passo 3: Aplicar Features do Nível

```cpp
// Aplicar features do nível atual
void ApplyLevelFeatures(
    FCharacterData& CharacterData,
    FName ClassToLevel,
    int32 NewLevel)
{
    // Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));
    FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(ClassToLevel, TEXT("LevelUp"));

    if (!ClassRow)
    {
        return;
    }

    // Obter features para este nível
    TArray<FClassFeature> Features = GetFeaturesForLevel(ClassRow, NewLevel);

    // Aplicar cada feature
    for (const FClassFeature& Feature : Features)
    {
        if (Feature.FeatureType == TEXT("Automatic"))
        {
            ApplyAutomaticFeature(CharacterData, Feature);
        }
        else if (Feature.FeatureType == TEXT("ASI"))
        {
            // ASI será aplicado em passo separado (escolha do jogador)
            QueueASI(CharacterData, Feature);
        }
        else if (Feature.FeatureType == TEXT("SubclassSelection"))
        {
            // Subclass já foi selecionada anteriormente
            ApplySubclassFeatures(CharacterData, ClassToLevel, NewLevel);
        }
    }
}
```

### Passo 4: Aplicar ASI (Ability Score Improvement)

```cpp
// Aplicar ASI (escolha do jogador)
void ApplyASI(
    FCharacterData& CharacterData,
    EASIOption Option,
    FName Ability1 = NAME_None,
    FName Ability2 = NAME_None)
{
    if (Option == EASIOption::PlusTwo)
    {
        // +2 em um atributo
        if (Ability1 != NAME_None)
        {
            int32 CurrentScore = GetFinalAbilityScore(CharacterData, Ability1);
            int32 NewScore = FMath::Min(CurrentScore + 2, 20); // Limite máximo 20
            SetFinalAbilityScore(CharacterData, Ability1, NewScore);
        }
    }
    else if (Option == EASIOption::PlusOnePlusOne)
    {
        // +1 em dois atributos
        if (Ability1 != NAME_None)
        {
            int32 CurrentScore = GetFinalAbilityScore(CharacterData, Ability1);
            int32 NewScore = FMath::Min(CurrentScore + 1, 20);
            SetFinalAbilityScore(CharacterData, Ability1, NewScore);
        }
        if (Ability2 != NAME_None)
        {
            int32 CurrentScore = GetFinalAbilityScore(CharacterData, Ability2);
            int32 NewScore = FMath::Min(CurrentScore + 1, 20);
            SetFinalAbilityScore(CharacterData, Ability2, NewScore);
        }
    }
    else if (Option == EASIOption::Feat)
    {
        // Escolher Feat ao invés de ASI
        // (aplicado em passo separado)
    }
}
```

### Passo 5: Aumentar HP

```cpp
// Aumentar HP ao fazer level up
void IncreaseHPOnLevelUp(
    FCharacterData& CharacterData,
    FName ClassToLevel)
{
    // Obter Hit Die da classe
    int32 HitDie = GetClassHitDie(CharacterData, ClassToLevel);

    // Rolar Hit Die
    int32 HitDieRoll = FMath::RandRange(1, HitDie);

    // Adicionar Constitution modifier
    int32 CONModifier = GetAbilityModifier(CharacterData, TEXT("Constitution"));

    // Calcular aumento de HP
    int32 HPIncrease = FMath::Max(HitDieRoll + CONModifier, 1); // Mínimo 1

    // Aumentar Max HP
    CharacterData.MaxHP += HPIncrease;

    // Aumentar Current HP pelo mesmo valor
    CharacterData.CurrentHP += HPIncrease;
}
```

### Passo 6: Recalcular Stats Derivados

```cpp
// Recalcular todos os stats derivados
void RecalculateDerivedStatsOnLevelUp(FCharacterData& CharacterData)
{
    // 1. Recalcular Proficiency Bonus
    int32 ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(CharacterData.TotalLevel);
    CharacterData.ProficiencyBonus = ProficiencyBonus;

    // 2. Recalcular modificadores de atributos
    for (const FName& AbilityName : GetAllAbilityNames())
    {
        int32 FinalScore = GetFinalAbilityScore(CharacterData, AbilityName);
        int32 Modifier = CalculationHelpers::CalculateAbilityModifier(FinalScore);
        SetAbilityModifier(CharacterData, AbilityName, Modifier);
    }

    // 3. Recalcular AC (pode mudar se DEX mudou)
    int32 NewAC = CalculationHelpers::CalculateAC(CharacterData);
    CharacterData.AC = NewAC;

    // 4. Recalcular Spell Slots (se aplicável)
    if (HasSpellcasting(CharacterData))
    {
        RecalculateSpellSlots(CharacterData);
    }
}
```

### Passo 7: Algoritmo Completo de Level Up

```cpp
// Algoritmo completo de level up
FLevelUpResult PerformLevelUp(
    FCharacterData& CharacterData,
    FName ClassToLevel,
    int32 CurrentXP,
    int32 RequiredXP,
    EASIOption ASIOption = EASIOption::None,
    FName ASIAbility1 = NAME_None,
    FName ASIAbility2 = NAME_None)
{
    FLevelUpResult Result;

    // 1. Validar level up
    if (!ValidateLevelUp(CharacterData, ClassToLevel, CurrentXP, RequiredXP))
    {
        Result.bSuccess = false;
        Result.ErrorMessage = TEXT("Não pode fazer level up");
        return Result;
    }

    // 2. Obter nível atual
    int32 CurrentLevel = CharacterData.ClassLevels[ClassToLevel];
    int32 NewLevel = CurrentLevel + 1;

    // 3. Incrementar nível
    IncrementClassLevel(CharacterData, ClassToLevel);

    // 4. Aumentar HP
    IncreaseHPOnLevelUp(CharacterData, ClassToLevel);

    // 5. Aplicar features do nível
    ApplyLevelFeatures(CharacterData, ClassToLevel, NewLevel);

    // 6. Aplicar ASI (se nível 4, 8, 12, 16, 19)
    if (NewLevel == 4 || NewLevel == 8 || NewLevel == 12 ||
        NewLevel == 16 || NewLevel == 19)
    {
        if (ASIOption != EASIOption::None)
        {
            ApplyASI(CharacterData, ASIOption, ASIAbility1, ASIAbility2);
        }
    }

    // 7. Recalcular stats derivados
    RecalculateDerivedStatsOnLevelUp(CharacterData);

    // 8. Atualizar XP
    CharacterData.CurrentXP = CurrentXP;
    CharacterData.RequiredXP = GetRequiredXPForNextLevel(CharacterData.TotalLevel);

    Result.bSuccess = true;
    Result.NewLevel = NewLevel;
    Result.NewTotalLevel = CharacterData.TotalLevel;

    return Result;
}
```

---

## 📊 Exemplo Completo

### Exemplo: Fighter Nível 3 → Nível 4

```cpp
FCharacterData CharacterData;
CharacterData.ClassLevels.Add(TEXT("Fighter"), 3);
CharacterData.TotalLevel = 3;
CharacterData.CurrentXP = 3000; // XP suficiente para nível 4
CharacterData.RequiredXP = 2700;

// Level up para Fighter nível 4
FLevelUpResult Result = PerformLevelUp(
    CharacterData,
    TEXT("Fighter"),
    3000,
    2700,
    EASIOption::PlusTwo,
    TEXT("Strength"),
    NAME_None
);

// Processo:
// 1. Validação: ✅ XP suficiente, nível < 20
// 2. Incrementar: Fighter 3 → 4, TotalLevel 3 → 4
// 3. HP: Rolar 1d10 + CON modifier, aumentar MaxHP e CurrentHP
// 4. Features: Nenhuma feature automática no nível 4
// 5. ASI: +2 Strength (de 16 para 18)
// 6. Recalcular: Proficiency Bonus +2 → +2 (não muda), Modifiers atualizados, AC recalculado
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistemas de Personagem - Level Up](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#progressão-de-níveis-level-up)** - Regras de level up D&D 5e
>
> - **GDD:** Define O QUÊ (HP gain, features, ASI/Feats) e PORQUÊ (progressão D&D 5e)
> - **TDD:** Define COMO (algoritmo de level up, cálculo HP, aplicação de features, estruturas C++)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Spellcasting Algorithm](spellcasting-algorithm.md) - Algoritmo de spellcasting
> - [API - Componentes](../../../02-api/componentes/index.md) - Componentes de personagem

</details>

---

**Navegação:** [← Voltar](index.md) | [→ Spellcasting Algorithm](spellcasting-algorithm.md)

**Última atualização:** 2024-12-27
