# RaceDataTable

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

---

## 👤 RaceDataTable

**Caminho:** `Source/MyProject2/Data/Tables/RaceDataTable.h`

**Struct:** `FRaceDataRow`

---

## Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `RaceName` | `FName` | Nome da raça (ex: "Human", "Elf", "Dwarf") |
| `Description` | `FText` | Descrição textual da raça (localizável) |
| `AbilityScoreImprovements` | `TArray<FAbilityScoreImprovement>` | Bônus de atributos da raça |
| `Size` | `FName` | Tamanho da raça (ex: "Small", "Medium") |
| `BaseSpeed` | `int32` | Velocidade base em pés |
| `Traits` | `TArray<FRaceTrait>` | Traits da raça (Darkvision, etc.) |
| `SubraceNames` | `TArray<FName>` | Lista de sub-raças disponíveis |

---

## Estruturas

### FAbilityScoreImprovement

```cpp
USTRUCT(BlueprintType)
struct FAbilityScoreImprovement
{
    FName AbilityName;  // Nome do atributo (ex: "Strength", "Constitution")
    int32 Bonus;        // Valor do bônus (geralmente +1 ou +2)
};
```

**Nota Especial:** Para Variant Human, use `AbilityName = "Custom"` com `Bonus = 1`. O sistema aplicará +1 para cada atributo escolhido em `CustomAbilityScoreChoices`.

### FRaceTrait

```cpp
USTRUCT(BlueprintType)
struct FRaceTrait
{
    FName TraitName;                    // Nome do trait (ex: "Darkvision")
    FText Description;                  // Descrição textual
    TMap<FName, FString> TraitData;     // Dados estruturados opcionais
};
```

---

## Exemplos de JSON

### Human

```json
{
  "Name": "Human",
  "RaceName": "Human",
  "Description": "Humans are the most adaptable and ambitious people among the common races.",
  "AbilityScoreImprovements": [
    {
      "AbilityName": "Strength",
      "Bonus": 1
    },
    {
      "AbilityName": "Dexterity",
      "Bonus": 1
    },
    {
      "AbilityName": "Constitution",
      "Bonus": 1
    },
    {
      "AbilityName": "Intelligence",
      "Bonus": 1
    },
    {
      "AbilityName": "Wisdom",
      "Bonus": 1
    },
    {
      "AbilityName": "Charisma",
      "Bonus": 1
    }
  ],
  "Size": "Medium",
  "BaseSpeed": 30,
  "Traits": [],
  "SubraceNames": ["Standard Human", "Variant Human"]
}
```

### Variant Human

```json
{
  "Name": "Variant Human",
  "RaceName": "Variant Human",
  "Description": "Some humans are more versatile than others.",
  "AbilityScoreImprovements": [
    {
      "AbilityName": "Custom",
      "Bonus": 1
    }
  ],
  "Size": "Medium",
  "BaseSpeed": 30,
  "Traits": [
    {
      "TraitName": "FeatChoice",
      "Description": "You gain one feat of your choice.",
      "TraitData": {}
    },
    {
      "TraitName": "SkillChoice",
      "Description": "You gain proficiency in one skill of your choice.",
      "TraitData": {}
    }
  ],
  "SubraceNames": []
}
```

**Importante:**
- `AbilityName = "Custom"` indica que o jogador escolhe 2 atributos para receber +1 cada
- Traits `FeatChoice` e `SkillChoice` indicam escolhas do jogador

### Dwarf (Exemplo Completo)

```json
{
  "Name": "Dwarf",
  "RaceName": "Dwarf",
  "Description": "Bold and hardy dwarves are known as skilled warriors miners and workers of stone and metal",
  "AbilityScoreImprovements": [
    {
      "AbilityName": "Constitution",
      "Bonus": 2
    }
  ],
  "Size": "Medium",
  "BaseSpeed": 25,
  "Traits": [
    {
      "TraitName": "Darkvision",
      "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
      "TraitData": {
        "Range": "60",
        "Type": "Vision"
      }
    },
    {
      "TraitName": "Dwarven Resilience",
      "Description": "You have advantage on saving throws against poison.",
      "TraitData": {
        "Advantage": "Poison",
        "Resistance": "Poison"
      }
    }
  ],
  "SubraceNames": ["Hill Dwarf", "Mountain Dwarf"]
}
```

---

**Navegação:** [← Estrutura Comum](../estrutura-comum.md) | [→ ClassDataTable](class-datatable.md)

**Última atualização:** 2024-12-27
