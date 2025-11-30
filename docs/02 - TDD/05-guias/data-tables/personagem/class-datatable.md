# ClassDataTable

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

---

## ⚔️ ClassDataTable

**Caminho:** `Source/MyProject2/Data/Tables/ClassDataTable.h`

**Struct:** `FClassDataRow`

---

## Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome da classe (ex: "Fighter", "Wizard", "Rogue") - Campo principal usado como chave e nome de exibição |
| `Description` | `FText` | Descrição textual da classe |
| `HitDie` | `int32` | Tipo de dado de vida (ex: 8 para d8, 10 para d10) |
| `Proficiencies` | `TArray<FClassProficiency>` | Proficiências da classe |
| `Features` | `TArray<FClassFeature>` | Features da classe por nível |
| `SubclassNames` | `TArray<FName>` | Lista de subclasses disponíveis |

---

## Estruturas

### FClassProficiency

```cpp
USTRUCT(BlueprintType)
struct FClassProficiency
{
    FName ProficiencyType;  // Tipo: "Weapon", "Armor", "SavingThrow", "Skill"
    FName ProficiencyName; // Nome específico (ex: "Longsword", "Light Armor", "Strength", "Athletics")
};
```

### FClassFeature

```cpp
USTRUCT(BlueprintType)
struct FClassFeature
{
    FName FeatureName;                    // Nome da feature (ex: "Second Wind", "Action Surge")
    FText Description;                    // Descrição textual
    int32 LevelUnlocked;                  // Nível em que é desbloqueada
    FName FeatureType;                    // Tipo: "Automatic", "SubclassSelection", "ASI", "Choice"
    TMap<FName, FString> FeatureData;     // Dados estruturados opcionais
};
```

**Tipos de Features:**

- **"Automatic"**: Feature aplicada automaticamente (ex: Second Wind, Action Surge)
- **"Choice"**: Jogador escolhe entre opções (ex: Fighting Style)
- **"SubclassSelection"**: Jogador escolhe subclasse (ex: Martial Archetype)
- **"ASI"**: Ability Score Improvement
- **"FeatSelection"**: Jogador pode escolher um Feat ao invés de ASI

---

## Exemplos de JSON

### Fighter

```json
{
  "Name": "Fighter",
  "Description": "A master of martial combat, skilled with a variety of weapons and armor.",
  "HitDie": 10,
  "Proficiencies": [
    {
      "ProficiencyType": "Armor",
      "ProficiencyName": "All Armor"
    },
    {
      "ProficiencyType": "Weapon",
      "ProficiencyName": "Simple Weapons"
    },
    {
      "ProficiencyType": "Weapon",
      "ProficiencyName": "Martial Weapons"
    },
    {
      "ProficiencyType": "SavingThrow",
      "ProficiencyName": "Strength"
    },
    {
      "ProficiencyType": "SavingThrow",
      "ProficiencyName": "Constitution"
    }
  ],
  "Features": [
    {
      "FeatureName": "Second Wind",
      "Description": "You have a limited well of stamina that you can draw on to protect yourself from harm.",
      "LevelUnlocked": 1,
      "FeatureType": "Automatic",
      "FeatureData": {
        "UsesPerRest": "1",
        "Type": "BonusAction"
      }
    },
    {
      "FeatureName": "Action Surge",
      "Description": "You can push yourself beyond your normal limits for a moment.",
      "LevelUnlocked": 2,
      "FeatureType": "Automatic",
      "FeatureData": {
        "UsesPerRest": "1"
      }
    },
    {
      "FeatureName": "Martial Archetype",
      "Description": "You choose an archetype that you strive to emulate.",
      "LevelUnlocked": 3,
      "FeatureType": "SubclassSelection",
      "FeatureData": {}
    }
  ],
  "SubclassNames": ["Champion", "Battle Master", "Eldritch Knight"]
}
```

### Wizard

```json
{
  "Name": "Wizard",
  "Description": "A scholarly magic-user capable of manipulating the structures of reality.",
  "HitDie": 6,
  "Proficiencies": [
    {
      "ProficiencyType": "Weapon",
      "ProficiencyName": "Daggers"
    },
    {
      "ProficiencyType": "Weapon",
      "ProficiencyName": "Darts"
    },
    {
      "ProficiencyType": "SavingThrow",
      "ProficiencyName": "Intelligence"
    },
    {
      "ProficiencyType": "SavingThrow",
      "ProficiencyName": "Wisdom"
    }
  ],
  "Features": [
    {
      "FeatureName": "Spellcasting",
      "Description": "As a student of arcane magic, you have a spellbook containing spells.",
      "LevelUnlocked": 1,
      "FeatureType": "Automatic",
      "FeatureData": {
        "SpellcastingAbility": "Intelligence",
        "SpellSaveDC": "8 + Proficiency + Intelligence Modifier"
      }
    },
    {
      "FeatureName": "Arcane Tradition",
      "Description": "You choose an arcane tradition.",
      "LevelUnlocked": 2,
      "FeatureType": "SubclassSelection",
      "FeatureData": {}
    }
  ],
  "SubclassNames": ["Evocation", "Abjuration", "Necromancy"]
}
```

---

## Validações

- **Features por nível:** Sistema coleta features baseado no nível do personagem
- **Subclasses:** Sistema valida que subclasse pertence à classe selecionada
- **Proficiências:** Sistema agrega proficiências de todas as classes do personagem

---

**Navegação:** [← RaceDataTable](race-datatable.md) | [→ ProficiencyDataTable](../suporte/proficiency-datatable.md)

**Última atualização:** 2024-12-27
