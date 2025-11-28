---
title: "ClassDataTable - Documentação Técnica"
category: technical
subcategory: data-tables
tags: [class, datatable, documentation, dnd-5e, multiclassing]
last_updated: 2024-12-27
difficulty: intermediate
related: [../../design/dnd-rules/character-creation.md, ../../design/dnd-rules/multiclassing.md, ../data-architecture/index.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../index.md) > [Técnico](../technical/index.md) > [Data Tables](index.md) > ClassDataTable

# ClassDataTable - Documentação Técnica

> **Objetivo:** Documentação completa da estrutura, campos e uso do `ClassDataTable`.
>
> **Público-alvo:** Desenvolvedores e designers que precisam trabalhar com dados de classes.

---

## 📋 Visão Geral

O `ClassDataTable` armazena todas as informações sobre classes do D&D 5e, incluindo Hit Die, proficiências, saving throws, skills disponíveis, features por nível e requisitos de multiclasse.

**Localização:**
- **JSON:** `Content/Data/JSON/ClassDataTable.json`
- **Schema:** `Content/Data/JSON/Schemas/ClassDataTable.schema.json`
- **C++ Struct:** `Source/MyProject2/Data/Tables/ClassDataTable.h` → `FClassDataRow`

---

## 🔢 Campos da Estrutura

### Campos Obrigatórios

#### `SchemaVersion` (string)
- **Formato:** `MAJOR.MINOR.PATCH` (ex: `"1.0.0"`)
- **Descrição:** Versão do schema usado por esta entrada
- **Exemplo:** `"1.0.0"`

#### `DataVersion` (string)
- **Formato:** `YYYY-MM-DD` (ex: `"2024-12-27"`)
- **Descrição:** Data da última modificação dos dados
- **Exemplo:** `"2024-12-27"`

#### `Name` (string)
- **Descrição:** Nome da classe (Key Field para Unreal Engine)
- **Uso:** Usado como chave primária no Data Table
- **Exemplo:** `"Class_Fighter"`, `"Class_Wizard"`, `"Class_Cleric"`

#### `ID` (string)
- **Padrão:** `^CLASS_[A-Z][a-zA-Z0-9_]*$`
- **Descrição:** Identificador único da classe
- **Exemplo:** `"CLASS_Fighter"`, `"CLASS_Wizard"`, `"CLASS_Cleric"`

### Campos Opcionais

#### `TypeTags` (array of strings)
- **Padrão:** `^Class\\.`
- **Descrição:** Gameplay Tags para categorização
- **Exemplo:** `["Class.Fighter", "Class.Martial"]`, `["Class.Wizard", "Class.Spellcaster"]`

#### `ClassName` (string)
- **Descrição:** Nome de exibição da classe
- **Exemplo:** `"Fighter"`, `"Wizard"`, `"Cleric"`

#### `HitDie` (integer)
- **Valores possíveis:** `6`, `8`, `10`, `12`
- **Descrição:** Dado de vida da classe (Hit Die)
- **Mapeamento:**
  - `6`: Wizard, Sorcerer
  - `8`: Bard, Cleric, Druid, Monk, Rogue, Warlock
  - `10`: Fighter, Paladin, Ranger
  - `12`: Barbarian
- **Exemplo:** `10` (Fighter)

#### `MulticlassRequirementGroups` (array of objects) ⭐ **NOVO**
- **Descrição:** Requisitos de atributo para multiclasse (estrutura normalizada)
- **Estrutura:**
  ```json
  {
    "Operator": "OR",
    "Requirements": [
      {
        "AbilityID": "ABL_Strength",
        "Value": 13
      },
      {
        "AbilityID": "ABL_Dexterity",
        "Value": 13
      }
    ]
  }
  ```
- **Operadores:**
  - `"OR"`: Qualquer um dos requisitos deve ser satisfeito
  - `"AND"`: Todos os requisitos devem ser satisfeitos
- **Lógica entre grupos:** Grupos são combinados com lógica AND (todos os grupos devem ser satisfeitos)
- **Exemplo (Fighter - STR/13 OU DEX/13):**
  ```json
  [
    {
      "Operator": "OR",
      "Requirements": [
        {"AbilityID": "ABL_Strength", "Value": 13},
        {"AbilityID": "ABL_Dexterity", "Value": 13}
      ]
    }
  ]
  ```

#### `MulticlassRequirements` (array of strings) ⚠️ **DEPRECATED**
- **Descrição:** Formato antigo de requisitos de multiclasse (mantido para compatibilidade)
- **Formato antigo:** `"STR/13|DEX/13"` (string com separadores)
- **Status:** Será removido após migração completa
- **Recomendação:** Use `MulticlassRequirementGroups` ao invés deste campo

#### `WeaponProficiencyHandles` (array of objects)
- **Descrição:** Lista de handles para proficiências com armas
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/ProficiencyDataTable",
    "RowName": "PW_Simple_Weapons"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PW_Simple_Weapons"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PW_Martial_Weapons"
    }
  ]
  ```

#### `ArmorProficiencyHandles` (array of objects)
- **Descrição:** Lista de handles para proficiências com armaduras
- **Estrutura:** Similar a `WeaponProficiencyHandles`
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Light_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Medium_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Heavy_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PS_Shields"
    }
  ]
  ```

#### `SavingThrowHandles` (array of objects)
- **Descrição:** Lista de handles para saving throws proficientes da classe
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/AbilityScoreDataTable",
    "RowName": "ABL_Strength"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/AbilityScoreDataTable",
      "RowName": "ABL_Strength"
    },
    {
      "DataTable": "/Game/Data/AbilityScoreDataTable",
      "RowName": "ABL_Constitution"
    }
  ]
  ```

#### `AvailableSkillHandles` (array of objects)
- **Descrição:** Lista de handles para skills disponíveis para escolha (classe escolhe 2-4 destes)
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/SkillDataTable",
    "RowName": "PSK_Athletics"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_Acrobatics"
    },
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_AnimalHandling"
    },
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_Athletics"
    }
  ]
  ```

#### `FeatureHandles` (array of objects)
- **Descrição:** Lista de handles para features de classe por nível
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/FeatureDataTable",
    "RowName": "FC_FightingStyle"
  }
  ```
- **Padrão RowName:** `^FC_[A-Z][a-zA-Z0-9_]*$` ou `"Feature_Geral"`
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/FeatureDataTable",
      "RowName": "FC_FightingStyle"
    },
    {
      "DataTable": "/Game/Data/FeatureDataTable",
      "RowName": "FC_SecondWind"
    }
  ]
  ```

#### `ProgressEntries` (array of objects)
- **Descrição:** Progressão de features por nível (estrutura `FProgressEntry`)
- **Estrutura:**
  ```json
  {
    "Level": 1,
    "Features": [
      {
        "DataTable": "/Game/Data/FeatureDataTable",
        "RowName": "FC_FightingStyle"
      }
    ],
    "SpellSlots": [],
    "CantripsKnown": 0,
    "SpellsKnown": 0
  }
  ```
- **Campos:**
  - `Level` (integer): Nível da classe
  - `Features` (array): Features ganhas neste nível
  - `SpellSlots` (array): Spell slots disponíveis (para spellcasters)
  - `CantripsKnown` (integer): Cantrips conhecidos
  - `SpellsKnown` (integer): Spells conhecidos

---

## 📝 Exemplo Completo

```json
{
  "SchemaVersion": "1.0.0",
  "DataVersion": "2024-12-27",
  "Name": "Class_Fighter",
  "ID": "CLASS_Fighter",
  "TypeTags": [
    "Class.Fighter",
    "Class.Martial"
  ],
  "ClassName": "Fighter",
  "HitDie": 10,
  "MulticlassRequirementGroups": [
    {
      "Operator": "OR",
      "Requirements": [
        {
          "AbilityID": "ABL_Strength",
          "Value": 13
        },
        {
          "AbilityID": "ABL_Dexterity",
          "Value": 13
        }
      ]
    }
  ],
  "WeaponProficiencyHandles": [
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PW_Simple_Weapons"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PW_Martial_Weapons"
    }
  ],
  "ArmorProficiencyHandles": [
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Light_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Medium_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PA_Heavy_Armor"
    },
    {
      "DataTable": "/Game/Data/ProficiencyDataTable",
      "RowName": "PS_Shields"
    }
  ],
  "SavingThrowHandles": [
    {
      "DataTable": "/Game/Data/AbilityScoreDataTable",
      "RowName": "ABL_Strength"
    },
    {
      "DataTable": "/Game/Data/AbilityScoreDataTable",
      "RowName": "ABL_Constitution"
    }
  ],
  "AvailableSkillHandles": [
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_Acrobatics"
    },
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_AnimalHandling"
    },
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_Athletics"
    }
  ],
  "FeatureHandles": [
    {
      "DataTable": "/Game/Data/FeatureDataTable",
      "RowName": "FC_FightingStyle"
    },
    {
      "DataTable": "/Game/Data/FeatureDataTable",
      "RowName": "FC_SecondWind"
    }
  ],
  "ProgressEntries": [
    {
      "Level": 1,
      "Features": [
        {
          "DataTable": "/Game/Data/FeatureDataTable",
          "RowName": "FC_FightingStyle"
        },
        {
          "DataTable": "/Game/Data/FeatureDataTable",
          "RowName": "FC_SecondWind"
        }
      ],
      "SpellSlots": [],
      "CantripsKnown": 0,
      "SpellsKnown": 0
    }
  ]
}
```

---

## 🔧 Uso no Código

### Buscar Classe

```cpp
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/ClassDataTable.h"

// Buscar classe por nome
FClassDataRow* ClassRow = DataTableHelpers::FindClassRow(
    FName("Class_Fighter"),
    ClassDataTable
);

if (ClassRow)
{
    // Usar dados da classe
    int32 HitDie = ClassRow->HitDie;
    // ...
}
```

### Validar Requisitos de Multiclasse

```cpp
#include "CreateSheet/Multiclass/MulticlassValidators.h"

// Validar requisitos de multiclasse
FString MissingTag;
bool IsValid = FMulticlassValidators::ValidateMulticlassRequirementGroups(
    ClassRow->MulticlassRequirementGroups,
    Attributes,  // TArray<int32> com valores de atributos
    AbilityScoreDataTable,
    MissingTag
);

if (IsValid)
{
    // Classe pode ser selecionada para multiclasse
}
```

### Carregar Features por Nível

```cpp
// Iterar sobre ProgressEntries
for (const FProgressEntry& Progress : ClassRow->ProgressEntries)
{
    if (Progress.Level == TargetLevel)
    {
        // Carregar features deste nível
        for (const FDataTableRowHandle& FeatureHandle : Progress.Features)
        {
            FFeatureDataRow* FeatureRow = FeatureHandle.GetRow<FFeatureDataRow>();
            if (FeatureRow)
            {
                // Aplicar feature
                ApplyFeature(FeatureRow);
            }
        }
    }
}
```

---

## ✅ Validações

### Validação de Schema

O schema JSON valida:
- ✅ Presença de campos obrigatórios (`Name`, `ID`, `SchemaVersion`, `DataVersion`)
- ✅ Formato do `ID` (deve começar com `CLASS_`)
- ✅ Formato de `TypeTags` (deve começar com `Class.`)
- ✅ Estrutura de `MulticlassRequirementGroups` (Operator e Requirements válidos)
- ✅ Referências `FDataTableRowHandle` (DataTable e RowName válidos)
- ✅ Estrutura de `ProgressEntries` (Level, Features, etc.)

### Validação no Editor

O `FDataTableSchemaValidator` valida:
- ✅ Estrutura básica do JSON
- ✅ Padrões de nomenclatura
- ✅ Referências a outras Data Tables
- ✅ Validação de `AbilityID` em `MulticlassRequirementGroups`

---

## 📚 Referências

- **[Regras D&D 5e - Classes](../../design/dnd-rules/character-creation.md)** - Regras de classes no D&D 5e
- **[Regras D&D 5e - Multiclassing](../../design/dnd-rules/multiclassing.md)** - Regras de multiclassing
- **[Data Architecture](../data-architecture/index.md)** - Arquitetura de dados do projeto
- **[JSON Schema Validation Guide](../guides/json-schema-validation-guide.md)** - Como validar schemas
- **[Schema Versioning Guide](../guides/schema-versioning-guide.md)** - Versionamento de schemas

---

**Última atualização:** 2024-12-27
