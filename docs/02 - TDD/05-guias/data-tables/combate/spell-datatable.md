# SpellDataTable e Tabelas de Combate

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

---

## 🔮 SpellDataTable

**Caminho:** `Source/MyProject2/Data/Tables/SpellDataTable.h`

**Struct:** `FSpellDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome da magia (ex: "Fireball", "Mage Hand", "Magic Missile") |
| `ID` | `FName` | ID único (ex: "SPL_Fireball", "SPL_MageHand") |
| `SpellLevel` | `int32` | Nível da magia (0 = Cantrip, 1-9 = Spell Level) |
| `SchoolReference` | `FDataTableRowHandle` | Referência à escola da magia |
| `DamageTypeReference` | `FDataTableRowHandle` | Referência ao tipo de dano (se aplicável) |
| `Description` | `FText` | Descrição da magia (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
| `SpellData` | `TMap<FName, FString>` | Dados estruturados (Range, Components, Duration, etc.) |

### Exemplo de JSON - Fireball

```json
{
  "Name": "Fireball",
  "ID": "SPL_Fireball",
  "SpellLevel": 3,
  "SchoolReference": {
    "DataTable": "DT_SpellSchools",
    "RowName": "Evocation"
  },
  "DamageTypeReference": {
    "DataTable": "DT_DamageTypes",
    "RowName": "Fire"
  },
  "Description": "A bright streak flashes from your pointing finger to a point you choose within range.",
  "TypeTags": ["Spell.Damage", "Spell.Area"],
  "SpellData": {
    "Range": "150 feet",
    "Components": "V, S, M",
    "Duration": "Instantaneous",
    "CastingTime": "1 action"
  }
}
```

---

## 🎓 SpellSchoolDataTable

**Caminho:** `Source/MyProject2/Data/Tables/SpellSchoolDataTable.h`

**Struct:** `FSpellSchoolDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome da escola (ex: "Abjuration", "Evocation", "Necromancy") |
| `ID` | `FName` | ID único (ex: "SCH_Abjuration", "SCH_Evocation") |
| `Description` | `FText` | Descrição da escola (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

### Exemplo de JSON - Evocation

```json
{
  "Name": "Evocation",
  "ID": "SCH_Evocation",
  "Description": "Evocation spells manipulate magical energy to produce a desired effect.",
  "TypeTags": ["SpellSchool.Evocation"]
}
```

---

## 🔥 DamageTypeDataTable

**Caminho:** `Source/MyProject2/Data/Tables/DamageTypeDataTable.h`

**Struct:** `FDamageTypeDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome do tipo de dano (ex: "Fire", "Cold", "Lightning") |
| `ID` | `FName` | ID único (ex: "DAM_Fire", "DAM_Cold", "DAM_Lightning") |
| `Description` | `FText` | Descrição do tipo de dano (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

### Exemplo de JSON - Fire

```json
{
  "Name": "Fire",
  "ID": "DAM_Fire",
  "Description": "Fire damage is dealt by flames, heat, and magical fire effects.",
  "TypeTags": ["DamageType.Fire", "DamageType.Elemental"]
}
```

---

## ⚠️ ConditionDataTable

**Caminho:** `Source/MyProject2/Data/Tables/ConditionDataTable.h`

**Struct:** `FConditionDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome da condição (ex: "Blinded", "Poisoned", "Charmed") |
| `ID` | `FName` | ID único (ex: "CON_Blinded", "CON_Poisoned", "CON_Charmed") |
| `Description` | `FText` | Descrição da condição (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

### Exemplo de JSON - Blinded

```json
{
  "Name": "Blinded",
  "ID": "CON_Blinded",
  "Description": "A blinded creature can't see and automatically fails any ability check that requires sight.",
  "TypeTags": ["Condition.Blinded", "Condition.Debuff"]
}
```

---

## 💪 AbilityScoreDataTable

**Caminho:** `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h`

**Struct:** `FAbilityScoreDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome do atributo (ex: "Strength", "Dexterity", "Constitution") |
| `ID` | `FName` | ID único (ex: "ABL_Strength", "ABL_Dexterity", "ABL_Constitution") |
| `Abbreviation` | `FName` | Abreviação (ex: "STR", "DEX", "CON") |
| `Description` | `FText` | Descrição do atributo (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

### Exemplo de JSON - Strength

```json
{
  "Name": "Strength",
  "ID": "ABL_Strength",
  "Abbreviation": "STR",
  "Description": "Strength measures bodily power, athletic training, and the extent to which you can exert raw physical force.",
  "TypeTags": ["Ability.Physical", "Ability.Strength"]
}
```

---

## 🏷️ TraitDataTable

**Caminho:** `Source/MyProject2/Data/Tables/TraitDataTable.h`

**Struct:** `FTraitDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome do trait (ex: "Darkvision", "Fey Ancestry", "Trance") |
| `ID` | `FName` | ID único (ex: "TR_Darkvision", "TR_FeyAncestry", "TR_Trance") |
| `Description` | `FText` | Descrição textual do trait (localizável) |
| `TraitData` | `TMap<FName, FString>` | Dados estruturados (ex: Range para Darkvision) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
| `SpellReference` | `FDataTableRowHandle` | Referência a uma magia (se aplicável) |

### Exemplo de JSON - Darkvision

```json
{
  "Name": "Darkvision",
  "ID": "TR_Darkvision",
  "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
  "TraitData": {
    "Range": "60"
  },
  "TypeTags": ["Trait.Vision.Darkvision", "Trait.Racial"],
  "SpellReference": {}
}
```

---

## 🎒 ItemDataTable

**Caminho:** `Source/MyProject2/Data/Tables/ItemDataTable.h`

**Struct:** `FItemDataRow`

### Campos

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `Name` | `FName` | Nome do item (ex: "Longsword", "Chain Mail", "15 gp") |
| `ID` | `FName` | ID único (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail", "ITM_GOLD_15gp") |
| `ItemType` | `FName` | Tipo: "Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold" |
| `Weight` | `float` | Peso do item em libras (lbs) |
| `Value` | `int32` | Valor do item em ouro (gp) |
| `Description` | `FText` | Descrição do item (localizável) |
| `TypeTags` | `FGameplayTagContainer` | Tags para categorização |

### Padrão de Nomenclatura de IDs

- **ITM_WPN_*** = Item Weapon
- **ITM_ARM_*** = Item Armor
- **ITM_TOL_*** = Item Tool
- **ITM_PCK_*** = Item Pack
- **ITM_CNM_*** = Item Consumable
- **ITM_OTH_*** = Item Other
- **ITM_GOLD_*** = Item Gold (ouro)

### Exemplo de JSON - Longsword

```json
{
  "Name": "Longsword",
  "ID": "ITM_WPN_Longsword",
  "ItemType": "Weapon",
  "Weight": 3.0,
  "Value": 15,
  "Description": "A versatile melee weapon.",
  "TypeTags": ["Item.Weapon.Martial", "Item.Weapon.Melee"]
}
```

---

**Navegação:** [← ProficiencyDataTable](../suporte/proficiency-datatable.md) | [→ Voltar para Índice](../index.md)

**Última atualização:** 2024-12-27
