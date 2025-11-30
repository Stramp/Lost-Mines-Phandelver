# Character Creation Algorithm

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do algoritmo de criação de personagem |

---

## 🎯 Objetivo

Algoritmo técnico passo a passo para criação de personagem D&D 5e, definindo a ordem de execução e validações necessárias.

---

## 📋 Algoritmo Completo

### Passo 1: Seleção de Raça

```cpp
// 1. Carregar RaceDataTable
UDataTable* RaceDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Races"));

// 2. Validar raça selecionada
FName SelectedRace = "Human";
FRaceDataRow* RaceRow = RaceDataTable->FindRow<FRaceDataRow>(SelectedRace, TEXT("CharacterCreation"));

if (!RaceRow)
{
    // Erro: Raça não encontrada
    return false;
}

// 3. Aplicar bônus raciais base
FRaceBonusMotor::ApplyBaseRaceBonuses(CharacterData, RaceRow);

// 4. Se houver sub-raça, aplicar bônus de sub-raça
if (SelectedSubrace != NAME_None)
{
    FRaceDataRow* SubraceRow = RaceDataTable->FindRow<FRaceDataRow>(SelectedSubrace, TEXT("CharacterCreation"));
    if (SubraceRow && RaceRow->SubraceNames.Contains(SelectedSubrace))
    {
        FRaceBonusMotor::ApplySubraceBonuses(CharacterData, SubraceRow);
    }
}
```

### Passo 2: Seleção de Classe

```cpp
// 1. Carregar ClassDataTable
UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));

// 2. Validar classe selecionada
FName SelectedClass = "Fighter";
FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(SelectedClass, TEXT("CharacterCreation"));

if (!ClassRow)
{
    // Erro: Classe não encontrada
    return false;
}

// 3. Aplicar proficiências da classe
FMulticlassMotor::ApplyClassProficiencies(CharacterData, ClassRow);

// 4. Aplicar features de nível 1
TArray<FClassFeature> Level1Features = FMulticlassMotor::GetFeaturesForLevel(ClassRow, 1);
for (const FClassFeature& Feature : Level1Features)
{
    ApplyFeature(CharacterData, Feature);
}
```

### Passo 3: Alocação de Ability Scores (Point Buy)

```cpp
// 1. Validar alocação de Point Buy
TMap<FName, int32> BaseScores = {
    {TEXT("Strength"), 15},
    {TEXT("Dexterity"), 14},
    {TEXT("Constitution"), 13},
    {TEXT("Intelligence"), 12},
    {TEXT("Wisdom"), 10},
    {TEXT("Charisma"), 8}
};

// 2. Validar com FPointBuyValidator
if (!FPointBuyValidator::ValidateAllocation(BaseScores, 27))
{
    // Erro: Alocação inválida
    return false;
}

// 3. Aplicar Point Buy
FPointBuyMotor::ApplyPointBuy(CharacterData, BaseScores);

// 4. Calcular scores finais (BASE + RACIAL + POINT_BUY)
FCharacterSheetCore::CalculateFinalAbilityScores(CharacterData);
```

### Passo 4: Seleção de Background

```cpp
// 1. Carregar BackgroundDataTable
UDataTable* BackgroundDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Backgrounds"));

// 2. Validar background selecionado
FName SelectedBackground = "Acolyte";
FBackgroundDataRow* BackgroundRow = BackgroundDataTable->FindRow<FBackgroundDataRow>(SelectedBackground, TEXT("CharacterCreation"));

if (!BackgroundRow)
{
    // Erro: Background não encontrado
    return false;
}

// 3. Aplicar skill proficiencies do background
for (const FName& Skill : BackgroundRow->SkillProficiencies)
{
    AddSkillProficiency(CharacterData, Skill);
}

// 4. Aplicar language proficiencies
for (const FName& Language : BackgroundRow->LanguageProficiencies)
{
    AddLanguageProficiency(CharacterData, Language);
}

// 5. Aplicar feature do background
ApplyBackgroundFeature(CharacterData, BackgroundRow->FeatureName);
```

### Passo 5: Escolhas Especiais (Variant Human, Feats, etc.)

```cpp
// 1. Verificar se é Variant Human
if (SelectedRace == TEXT("Variant Human"))
{
    // 2. Aplicar Custom ASI (+1 em 2 atributos escolhidos)
    TArray<FName> CustomAttributes = {TEXT("Strength"), TEXT("Dexterity")};
    FRaceBonusMotor::ApplyCustomASI(CharacterData, CustomAttributes);

    // 3. Permitir seleção de Feat
    FName SelectedFeat = "Alert";
    if (FFeatValidator::ValidateFeat(CharacterData, SelectedFeat))
    {
        ApplyFeat(CharacterData, SelectedFeat);
    }

    // 4. Permitir seleção de Skill adicional
    FName SelectedSkill = "Athletics";
    AddSkillProficiency(CharacterData, SelectedSkill);
}
```

### Passo 6: Cálculo de Stats Derivados

```cpp
// 1. Calcular modificadores de atributos
for (const FName& AbilityName : GetAllAbilityNames())
{
    int32 FinalScore = GetFinalAbilityScore(CharacterData, AbilityName);
    int32 Modifier = CalculationHelpers::CalculateAbilityModifier(FinalScore);
    SetAbilityModifier(CharacterData, AbilityName, Modifier);
}

// 2. Calcular HP inicial
int32 HitDie = GetClassHitDie(CharacterData, SelectedClass);
int32 ConstitutionModifier = GetAbilityModifier(CharacterData, TEXT("Constitution"));
int32 MaxHP = HitDie + ConstitutionModifier;
SetMaxHP(CharacterData, MaxHP);
SetCurrentHP(CharacterData, MaxHP);

// 3. Calcular Proficiency Bonus (nível 1 = +2)
int32 ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(1);
SetProficiencyBonus(CharacterData, ProficiencyBonus);

// 4. Calcular AC base
int32 AC = CalculationHelpers::CalculateAC(CharacterData);
SetAC(CharacterData, AC);
```

### Passo 7: Validação Final

```cpp
// 1. Validar que todos os campos obrigatórios estão preenchidos
if (!ValidateCharacterComplete(CharacterData))
{
    // Erro: Personagem incompleto
    return false;
}

// 2. Validar regras D&D 5e
if (!ValidateDnDRules(CharacterData))
{
    // Erro: Violação de regras D&D
    return false;
}

// 3. Salvar personagem
SaveCharacter(CharacterData);
```

---

## 🔄 Fluxo Completo

```
1. Selecionar Raça → Aplicar Bônus Raciais
2. Selecionar Classe → Aplicar Proficiências e Features
3. Alocar Point Buy → Validar e Aplicar
4. Selecionar Background → Aplicar Skills e Languages
5. Escolhas Especiais → Variant Human, Feats, etc.
6. Calcular Stats Derivados → Modificadores, HP, AC, Proficiency
7. Validação Final → Verificar completude e regras D&D
```

---

## 📖 Design Relacionado

Este documento implementa as seguintes regras de design:

- **[GDD: Sistemas de Personagem](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md)** - Regras de criação D&D 5e
- **[GDD: Ordem de Criação](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#ordem-de-criação-de-personagem)** - Ordem oficial D&D 5e


---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Point Buy Algorithm](point-buy-algorithm.md) - Algoritmo de Point Buy
> - [Multiclass Algorithm](multiclass-algorithm.md) - Algoritmo de Multiclassing
> - [API - Motores](../../../02-api/motores/index.md) - Motores de criação
> - [API - Componentes](../../../02-api/componentes/index.md) - Componentes de personagem

</details>

---

**Navegação:** [← Voltar](index.md) | [→ Point Buy Algorithm](point-buy-algorithm.md)

**Última atualização:** 2024-12-27
