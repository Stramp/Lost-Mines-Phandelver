---
title: "JSON Schema"
category: technical
subcategory: data-architecture
tags: [json-schema, data-tables, validation, structure]
last_updated: 2024-12-27
difficulty: intermediate
related: [database-architecture.md, ../../guides/data-tables.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Data Architecture](data-architecture/index.md) > JSON Schema

# JSON Schema - Padrão de Estrutura para Data Tables

> **Documentação:** Define o formato esperado para arquivos JSON de Data Tables no projeto.
>
> **Objetivo:** Garantir consistência na estrutura de dados e facilitar onboarding de designers.

---

## 📋 Estrutura Obrigatória

Toda entrada em uma Data Table JSON deve seguir o padrão **"Name + ID + Tags + Payload"**:

### Campos Obrigatórios

1. **`Name`** (String, obrigatório)
   - Nome de exibição (Key Field do Unreal Engine)
   - Usado como chave primária na Data Table
   - Exemplo: `"Elf"`, `"Fighter"`, `"Longsword"`

2. **`ID`** (String, obrigatório)
   - Identificador único interno
   - Padrão de nomenclatura: `PREFIX_Name` (ex: `RACE_Elf`, `CLASS_Fighter`, `ITM_Longsword`)
   - Usado para referências no código
   - Deve ser único dentro da tabela

3. **`TypeTags`** (Array de Strings, obrigatório)
   - Gameplay Tags para categorização hierárquica
   - Exemplo: `["Race.Elf", "Race.Fey"]`, `["Item.Weapon", "Item.Melee"]`

### Campos Opcionais

4. **`Description`** (String, opcional)
   - Descrição textual (localizável)
   - Usado para exibição na UI

5. **`*Data`** (Object, opcional)
   - Payload estruturado (TMap<FName, FString>)
   - Dados específicos do item
   - Exemplo: `FeatureData`, `TraitData`, `ItemData`

---

## 🔗 Referências: FDataTableRowHandle

Para referenciar outras Data Tables, use a estrutura `FDataTableRowHandle`:

```json
{
  "DataTable": "/Game/Data/TraitDataTable",
  "RowName": "TR_Darkvision"
}
```

### Campos

- **`DataTable`** (String, obrigatório)
  - Caminho do asset da Data Table (ex: `/Game/Data/TraitDataTable`)
  - Deve ser um caminho válido no Unreal Engine

- **`RowName`** (String, obrigatório)
  - Nome da row (Key Field) na Data Table referenciada
  - Deve existir na Data Table referenciada

### Exemplo Completo

```json
{
  "Name": "Elf",
  "ID": "RACE_Elf",
  "TypeTags": ["Race.Elf", "Race.Fey"],
  "Description": "Elves are a magical people...",
  "TraitHandles": [
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Darkvision"
    },
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_FeyAncestry"
    }
  ]
}
```

---

## 📦 Payload: TMap<FName, FString>

Dados específicos são armazenados em objetos `*Data` (ex: `FeatureData`, `TraitData`, `ItemData`):

### Estrutura

```json
{
  "FeatureData": {
    "Damage": "1d8",
    "Range": "30",
    "DamageTypeID": "DMG_Fire"
  }
}
```

### Exemplos por Tipo

#### Armas (ItemDataTable.json)

**Nota:** Atualmente `FItemDataRow` não possui campo `ItemData`. Para armas, use os campos existentes:
- `DamageTypeID` para tipo de dano
- `Weight` e `Value` para stats básicos
- `Description` para informações adicionais

**Exemplo Atual:**
```json
{
  "Name": "Longsword",
  "ID": "ITM_WPN_Longsword",
  "ItemType": "Weapon",
  "Weight": 3.0,
  "Value": 15,
  "Description": "A versatile melee weapon...",
  "TypeTags": ["Item.Weapon", "Item.Melee", "Item.Martial"],
  "DamageTypeID": "DMG_Slashing",
  "IconTexture": null,
  "MeshReference": null,
  "SpellHandle": null
}
```

**Exemplo Futuro (com ItemData - quando implementado):**
```json
{
  "Name": "Longsword",
  "ID": "ITM_WPN_Longsword",
  "TypeTags": ["Item.Weapon", "Item.Melee", "Item.Martial"],
  "ItemType": "Weapon",
  "ItemData": {
    "WeaponType": "Melee",
    "Damage": "1d8",
    "DamageTypeID": "DMG_Slashing",
    "Properties": "Versatile",
    "VersatileDamage": "1d10",
    "Range": "5"
  },
  "Weight": 3.0,
  "Value": 15
}
```

#### Armaduras (ItemDataTable.json)

**Exemplo Atual:**
```json
{
  "Name": "Chain Mail",
  "ID": "ITM_ARM_ChainMail",
  "ItemType": "Armor",
  "Weight": 55.0,
  "Value": 75,
  "Description": "Made of interlocking metal rings...",
  "TypeTags": ["Item.Armor", "Item.Heavy"],
  "IconTexture": null,
  "MeshReference": null,
  "SpellHandle": null,
  "DamageTypeID": null
}
```

**Exemplo Futuro (com ItemData - quando implementado):**
```json
{
  "Name": "Chain Mail",
  "ID": "ITM_ARM_ChainMail",
  "TypeTags": ["Item.Armor", "Item.Heavy"],
  "ItemType": "Armor",
  "ItemData": {
    "ArmorType": "Heavy",
    "AC": "16",
    "MaxDexBonus": "0",
    "StealthDisadvantage": "true"
  },
  "Weight": 55.0,
  "Value": 75
}
```

#### Traits (TraitDataTable.json)

```json
{
  "Name": "Darkvision",
  "ID": "TR_Darkvision",
  "TypeTags": ["Trait.Vision.Darkvision"],
  "Description": "You can see in dim light...",
  "TraitData": {
    "Range": "60",
    "Type": "Vision"
  }
}
```

---

## 🏷️ Gameplay Tags: Padrão de Nomenclatura

Gameplay Tags seguem hierarquia de pontos (`.`):

### Formato

```
Category.Subcategory.Item
```

### Exemplos

- **Raças:** `Race.Elf`, `Race.Dwarf`, `Race.Subrace.HighElf`
- **Classes:** `Class.Fighter`, `Class.Martial`, `Class.Spellcaster`
- **Itens:** `Item.Weapon`, `Item.Armor`, `Item.Consumable`
- **Traits:** `Trait.Vision.Darkvision`, `Trait.Racial.FeyAncestry`
- **Skills:** `Skill.Physical`, `Skill.Social`, `Skill.Knowledge`

### Regras

1. **Sempre começar com categoria principal** (ex: `Race`, `Class`, `Item`)
2. **Usar pontos para hierarquia** (ex: `Race.Subrace.HighElf`)
3. **Manter consistência** (ex: todas as raças começam com `Race.`)
4. **Evitar tags muito específicas** (preferir hierarquia)

---

## 📝 Exemplos Completos por Tipo

### RaceDataTable.json

```json
{
  "Name": "Elf",
  "ID": "RACE_Elf",
  "Description": "Elves are a magical people...",
  "TypeTags": ["Race.Elf", "Race.Fey"],
  "AbilityScoreImprovements": [
    {
      "AbilityID": "ABL_Dexterity",
      "Bonus": 2
    }
  ],
  "Size": "Medium",
  "BaseSpeed": 30,
  "TraitHandles": [
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Darkvision"
    }
  ],
  "LanguageHandles": [
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Common"
    },
    {
      "DataTable": "/Game/Data/LanguageDataTable",
      "RowName": "PL_Elvish"
    }
  ],
  "SubraceHandles": [
    {
      "DataTable": "/Game/Data/RaceDataTable",
      "RowName": "High Elf"
    }
  ]
}
```

### ClassDataTable.json

**Formato Antigo (Deprecated):**
```json
{
  "Name": "Class_Fighter",
  "ID": "CLASS_Fighter",
  "TypeTags": ["Class.Fighter", "Class.Martial"],
  "Name": "Fighter",
  "HitDie": 10,
  "MulticlassRequirements": ["STR/13|DEX/13"],
  "WeaponProficiencyHandles": [...]
}
```

**Formato Novo (Normalizado - Recomendado):**
```json
{
  "Name": "Class_Fighter",
  "ID": "CLASS_Fighter",
  "TypeTags": ["Class.Fighter", "Class.Martial"],
  "Name": "Fighter",
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
    }
  ],
  "SavingThrowHandles": [
    {
      "DataTable": "/Game/Data/AbilityScoreDataTable",
      "RowName": "ABL_Strength"
    }
  ],
  "AvailableSkillHandles": [
    {
      "DataTable": "/Game/Data/SkillDataTable",
      "RowName": "PSK_Acrobatics"
    }
  ]
}
```

**Nota:** O formato antigo `MulticlassRequirements` ainda é suportado para compatibilidade, mas o formato novo `MulticlassRequirementGroups` é recomendado. Use o script `scripts/migrate_multiclass_requirements.py` para migrar.

### FeatDataTable.json

```json
{
  "Name": "Alert",
  "ID": "FEAT_Alert",
  "Description": "Always on the lookout for danger...",
  "LevelUnlocked": 4,
  "FeatureType": "Feat",
  "FeatureData": {
    "InitiativeBonus": "5",
    "CannotBeSurprised": "true",
    "NoAdvantageFromHidden": "true"
  },
  "AvailableChoices": [],
  "TypeTags": ["Feat.Alert", "Feat.Combat"]
}
```

---

## ✅ Checklist de Validação

Antes de considerar um JSON válido, verificar:

- [ ] `Name` está presente e não é vazio
- [ ] `ID` está presente e segue padrão `PREFIX_Name`
- [ ] `ID` é único dentro da tabela
- [ ] `TypeTags` está presente e é um array
- [ ] Todas as referências `FDataTableRowHandle` são válidas
- [ ] `DataTable` em handles aponta para asset válido
- [ ] `RowName` em handles existe na Data Table referenciada
- [ ] Payload `*Data` usa apenas strings (valores são sempre strings)
- [ ] Gameplay Tags seguem padrão hierárquico

---

## 🚫 Erros Comuns a Evitar

### ❌ ERRADO: ID sem prefixo

```json
{
  "Name": "Elf",
  "ID": "Elf"  // ❌ Deve ser "RACE_Elf"
}
```

### ❌ ERRADO: Referência direta por string

```json
{
  "Traits": ["Darkvision", "FeyAncestry"]  // ❌ Deve usar TraitHandles
}
```

### ❌ ERRADO: Payload com tipos incorretos

```json
{
  "FeatureData": {
    "Damage": 1,  // ❌ Deve ser string: "1"
    "Range": 30   // ❌ Deve ser string: "30"
  }
}
```

### ✅ CORRETO: Estrutura completa

```json
{
  "Name": "Elf",
  "ID": "RACE_Elf",
  "TypeTags": ["Race.Elf"],
  "TraitHandles": [
    {
      "DataTable": "/Game/Data/TraitDataTable",
      "RowName": "TR_Darkvision"
    }
  ],
  "FeatureData": {
    "Damage": "1d8",
    "Range": "30"
  }
}
```

---

## 🔍 Validação de Schemas

O projeto implementa validação de JSON Schema em três níveis:

### 1. Validação Local (Python)

Execute antes de importar no Unreal Engine:

```bash
python scripts/validate_json_schemas.py
```

### 2. Validação no Editor (C++)

Validação automática quando Data Tables são alteradas. Ver logs no Output Log do Unreal Engine.

### 3. Validação no CI/CD (GitHub Actions)

Validação automática em cada commit/PR. Ver workflow `.github/workflows/validate-json-schemas.yml`.

**Para mais detalhes:** Veja [Guia de Validação JSON Schema](../guides/json-schema-validation-guide.md)

---

## 📚 Referências

- [Guia de Validação JSON Schema](../guides/json-schema-validation-guide.md) - Como usar o sistema de validação
- [Arquitetura de Banco de Dados](database-architecture.md) - Arquitetura completa
- [Data Table Helpers](../../../Source/MyProject2/Utils/DataTableRowHandleHelpers.h) - Funções helper
- [Gameplay Tags](../../../Content/Data/GameplayTags/MyProject2Tags.ini) - Configuração de tags

---

**Última atualização:** 2024-12-27
