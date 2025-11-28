---
title: "RaceDataTable - Documentação Técnica"
category: technical
subcategory: data-tables
tags: [race, datatable, documentation, dnd-5e]
last_updated: 2024-12-27
difficulty: intermediate
related: [../../design/dnd-rules/races.md, ../data-architecture/index.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](../index.md) > [Técnico](../technical/index.md) > [Data Tables](index.md) > RaceDataTable

# RaceDataTable - Documentação Técnica

> **Objetivo:** Documentação completa da estrutura, campos e uso do `RaceDataTable`.
>
> **Público-alvo:** Desenvolvedores e designers que precisam trabalhar com dados de raças.

---

## 📋 Visão Geral

O `RaceDataTable` armazena todas as informações sobre raças e sub-raças do D&D 5e, incluindo bônus de atributos, traits, idiomas e sub-raças disponíveis.

**Localização:**
- **JSON:** `Content/Data/JSON/RaceDataTable.json`
- **Schema:** `Content/Data/JSON/Schemas/RaceDataTable.schema.json`
- **C++ Struct:** `Source/MyProject2/Data/Tables/RaceDataTable.h` → `FRaceDataRow`

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
- **Descrição:** Nome de exibição da raça (Key Field para Unreal Engine)
- **Uso:** Usado como chave primária no Data Table
- **Exemplo:** `"Dwarf"`, `"Elf"`, `"Human"`

#### `ID` (string)
- **Padrão:** `^RACE_[A-Z][a-zA-Z0-9_]*$`
- **Descrição:** Identificador único da raça
- **Exemplo:** `"RACE_Dwarf"`, `"RACE_Elf"`, `"RACE_HillDwarf"`

### Campos Opcionais

#### `Description` (string)
- **Descrição:** Descrição textual da raça (localizável)
- **Exemplo:** `"Bold and hardy dwarves are known as skilled warriors..."`

#### `TypeTags` (array of strings)
- **Padrão:** `^Race\\.`
- **Descrição:** Gameplay Tags para categorização
- **Exemplo:** `["Race.Dwarf"]`, `["Race.Elf", "Race.Subrace.HighElf"]`

#### `AbilityScoreImprovements` (array of objects)
- **Descrição:** Lista de modificadores de Ability Score que a raça fornece
- **Estrutura:**
  ```json
  {
    "AbilityID": "ABL_Constitution",
    "Bonus": 2
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "AbilityID": "ABL_Constitution",
      "Bonus": 2
    },
    {
      "AbilityID": "ABL_Strength",
      "Bonus": 1
    }
  ]
  ```

#### `Size` (string)
- **Valores possíveis:** `"Small"`, `"Medium"`, `"Large"`
- **Descrição:** Tamanho da raça
- **Exemplo:** `"Medium"`

#### `BaseSpeed` (integer)
- **Descrição:** Velocidade base da raça em pés
- **Padrão:** `30` (para maioria das raças)
- **Exemplo:** `25` (Dwarf), `30` (Human), `35` (Wood Elf)

#### `TraitHandles` (array of objects)
- **Descrição:** Lista de handles type-safe para traits especiais da raça
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/TraitDataTable",
    "RowName": "TR_Darkvision"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Darkvision"
    },
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_DwarvenResilience"
    }
  ]
  ```

#### `SubraceHandles` (array of objects)
- **Descrição:** Lista de handles para sub-raças disponíveis para esta raça
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/RaceDataTable",
    "RowName": "RACE_HillDwarf"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/RaceDataTable",
      "RowName": "RACE_HillDwarf"
    },
    {
      "DataTable": "/Game/Data/RaceDataTable",
      "RowName": "RACE_MountainDwarf"
    }
  ]
  ```

#### `LanguageHandles` (array of objects)
- **Descrição:** Lista de handles para idiomas que a raça conhece automaticamente
- **Estrutura:**
  ```json
  {
    "DataTable": "/Game/Data/LanguageDataTable",
    "RowName": "PL_Common"
  }
  ```
- **Exemplo:**
  ```json
  [
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Common"
    },
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Dwarvish"
    }
  ]
  ```

#### `IconTexture` (string, opcional)
- **Descrição:** Referência suave para o ícone visual da raça
- **Formato:** Caminho do asset no Unreal Engine
- **Exemplo:** `"/Game/UI/Icons/Race_Dwarf"`

---

## 📝 Exemplo Completo

```json
{
  "SchemaVersion": "1.0.0",
  "DataVersion": "2024-12-27",
  "Name": "Dwarf",
  "ID": "RACE_Dwarf",
  "Description": "Bold and hardy dwarves are known as skilled warriors miners and workers of stone and metal",
  "TypeTags": [
    "Race.Dwarf"
  ],
  "AbilityScoreImprovements": [
    {
      "AbilityID": "ABL_Constitution",
      "Bonus": 2
    }
  ],
  "Size": "Medium",
  "BaseSpeed": 25,
  "TraitHandles": [
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Darkvision"
    },
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_DwarvenResilience"
    },
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Stonecunning"
    }
  ],
  "LanguageHandles": [
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Common"
    },
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Dwarvish"
    }
  ],
  "SubraceHandles": [
    {
      "DataTable": "/Game/Data/RaceDataTable",
      "RowName": "RACE_HillDwarf"
    },
    {
      "DataTable": "/Game/Data/RaceDataTable",
      "RowName": "RACE_MountainDwarf"
    }
  ]
}
```

---

## 🔧 Uso no Código

### Buscar Raça

```cpp
#include "Utils/DataTableHelpers.h"
#include "Data/Tables/RaceDataTable.h"

// Buscar raça por nome
FRaceDataRow* RaceRow = DataTableHelpers::FindRaceRow(
    FName("Dwarf"),
    RaceDataTable
);

if (RaceRow)
{
    // Usar dados da raça
    int32 Speed = RaceRow->BaseSpeed;
    // ...
}
```

### Aplicar Bônus de Atributos

```cpp
// Iterar sobre AbilityScoreImprovements
for (const FAbilityScoreImprovement& Improvement : RaceRow->AbilityScoreImprovements)
{
    // Aplicar bônus ao atributo correspondente
    ApplyAbilityScoreBonus(Improvement.AbilityID, Improvement.Bonus);
}
```

### Carregar Traits

```cpp
// Carregar traits da raça
for (const FDataTableRowHandle& TraitHandle : RaceRow->TraitHandles)
{
    FTraitDataRow* TraitRow = TraitHandle.GetRow<FTraitDataRow>();
    if (TraitRow)
    {
        // Aplicar trait
        ApplyTrait(TraitRow);
    }
}
```

---

## ✅ Validações

### Validação de Schema

O schema JSON valida:
- ✅ Presença de campos obrigatórios (`Name`, `ID`, `SchemaVersion`, `DataVersion`)
- ✅ Formato do `ID` (deve começar com `RACE_`)
- ✅ Formato de `TypeTags` (deve começar com `Race.`)
- ✅ Estrutura de `AbilityScoreImprovements` (deve ter `AbilityID` e `Bonus`)
- ✅ Referências `FDataTableRowHandle` (DataTable e RowName válidos)

### Validação no Editor

O `FDataTableSchemaValidator` valida:
- ✅ Estrutura básica do JSON
- ✅ Padrões de nomenclatura
- ✅ Referências a outras Data Tables

---

## 📚 Referências

- **[Regras D&D 5e - Raças](../../design/dnd-rules/races.md)** - Regras de raças no D&D 5e
- **[Data Architecture](../data-architecture/index.md)** - Arquitetura de dados do projeto
- **[JSON Schema Validation Guide](../guides/json-schema-validation-guide.md)** - Como validar schemas
- **[Schema Versioning Guide](../guides/schema-versioning-guide.md)** - Versionamento de schemas

---

**Última atualização:** 2024-12-27



