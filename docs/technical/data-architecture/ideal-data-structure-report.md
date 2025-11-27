# Relatório: Estrutura de Dados Ideal para Projeto AAA (Estilo Baldur's Gate 3)

## Análise Completa dos JSONs Existentes

### Arquivos Encontrados

1. `Race_All.json` - Raças e sub-raças
2. `DJ_Class.json` - Classes e progressão
3. `Background_All.json` - Backgrounds
4. `DJ_FeatsGerais.json` - Feats gerais (com `FC_ID`)
5. `Feat_All.json` - Feats alternativos (sem `FC_ID`)
6. `DJ_FeaturesClass.json` - Features de classe (com `FC_ID`)
7. `DJ_Proficiencie.json` - Proficiências (com `ProficiencyID`)
8. `Item_All.json` - Itens (com `ItemID`)

### ⚠️ CRÍTICO: O Que Falta

- **`SpellDataTable.json`** - Sistema de magias completamente ausente
- Referências a spells em traits (High Elf Cantrip) sem tabela de spells

---

## Problemas Críticos Identificados

### 1. Falta de IDs Únicos (Normalização)

| Arquivo | Status | Problema |
|---------|--------|----------|
| `Race_All.json` | ❌ | Sem `RaceID`, usa `Name` como chave |
| `DJ_Class.json` | ❌ | Sem `ClassID`, usa `Name` como chave |
| `Background_All.json` | ❌ | Sem `BackgroundID`, usa `Name` como chave |
| `Feat_All.json` | ❌ | Sem `FeatID`, duplicado com `DJ_FeatsGerais.json` |
| `DJ_FeatsGerais.json` | ✅ | Tem `FC_ID` |
| `DJ_FeaturesClass.json` | ✅ | Tem `FC_ID` |
| `DJ_Proficiencie.json` | ✅ | Tem `ProficiencyID` |
| `Item_All.json` | ✅ | Tem `ItemID` |

### 2. Dados Embutidos (Não Normalizados)

- **`Race_All.json`**: `Traits` embutidos (sem `TraitID`), `Languages` como strings (sem `LanguageID`)
- **`DJ_Class.json`**: `savingThrows` como strings (sem `AbilityID`), `FSkills.available` como strings (sem `SkillID`)
- **`Background_All.json`**: `SkillProficiencies` como strings (sem `SkillID`), `Languages` como strings (sem `LanguageID`)
- **Traits Repetidos**: `Darkvision` aparece em Elf, Dwarf, etc. (duplicação massiva)

### 3. Falta de Tabelas de Referência (Master Data)

- ❌ `TraitDataTable.json` - Traits reutilizáveis
- ❌ `LanguageDataTable.json` - Idiomas reutilizáveis
- ❌ `SkillDataTable.json` - Skills reutilizáveis
- ❌ `AbilityScoreDataTable.json` - Atributos padronizados
- ❌ `SpellDataTable.json` - **MAGIAS (CRÍTICO, NÃO EXISTE)**
- ❌ `SpellSchoolDataTable.json` - Escolas de magia
- ❌ `DamageTypeDataTable.json` - Tipos de dano
- ❌ `ConditionDataTable.json` - Condições (Poisoned, Charmed, etc.)

### 4. Duplicação de Dados

- `Feat_All.json` e `DJ_FeatsGerais.json` - Mesma informação, formatos diferentes
- Traits duplicados entre raças
- Languages duplicados entre raças/backgrounds
- Skills duplicados entre classes/backgrounds

---

## Estrutura Ideal (Projeto Zerado)

### Arquitetura Baseada em ECS + Data-Oriented Design

## Tabelas de Referência (Master Data) - Prioridade 1

### 1. `AbilityScoreDataTable.json`

```json
{
  "AbilityID": "ABL_Strength",
  "AbilityName": "Strength",
  "Abbreviation": "STR",
  "Description": "Physical power and athletic ability"
}
```

**IDs Necessários:**
- `ABL_Strength`, `ABL_Dexterity`, `ABL_Constitution`, `ABL_Intelligence`, `ABL_Wisdom`, `ABL_Charisma`

**Uso:** Substituir strings "Strength", "Dexterity" em todo o sistema

### 2. `TraitDataTable.json`

```json
{
  "TraitID": "TR_Darkvision",
  "TraitName": "Darkvision",
  "Description": "...",
  "TraitData": {
    "Range": "60",
    "Type": "Vision"
  },
  "Tags": ["Vision", "Racial"]
}
```

**IDs Necessários:**
- `TR_Darkvision`, `TR_FeyAncestry`, `TR_Trance`, `TR_Stonecunning`, etc.

**Uso:** Referenciado por `RaceID.TraitIDs[]`

### 3. `LanguageDataTable.json`

```json
{
  "LanguageID": "PL_Common",
  "LanguageName": "Common",
  "Description": "The most widely spoken language",
  "Script": "Common",
  "Type": "Standard"
}
```

**IDs Necessários:**
- `PL_Common`, `PL_Elvish`, `PL_Dwarvish`, `PL_Abyssal`, etc.

**Uso:** Substituir strings "Common", "Elvish" em raças/backgrounds

### 4. `SkillDataTable.json`

```json
{
  "SkillID": "PSK_Acrobatics",
  "SkillName": "Acrobatics",
  "AbilityID": "ABL_Dexterity",
  "Description": "Your Dexterity (Acrobatics) check covers..."
}
```

**IDs Necessários:**
- `PSK_Acrobatics`, `PSK_Athletics`, `PSK_Stealth`, etc.

**Uso:** Substituir strings em classes/backgrounds

### 5. `SpellDataTable.json` - ⚠️ CRÍTICO, NÃO EXISTE

```json
{
  "SpellID": "SPL_Fireball",
  "SpellName": "Fireball",
  "Level": 3,
  "SchoolID": "SCH_Evocation",
  "CastingTime": "1 action",
  "Range": "150 feet",
  "Components": {
    "Verbal": true,
    "Somatic": true,
    "Material": "A tiny ball of bat guano and sulfur"
  },
  "Duration": "Instantaneous",
  "Description": "...",
  "SpellData": {
    "Damage": "8d6",
    "DamageTypeID": "DAM_Fire",
    "SaveAbilityID": "ABL_Dexterity",
    "SaveType": "Half",
    "Area": "20-foot-radius sphere"
  },
  "Classes": ["CLASS_Wizard", "CLASS_Sorcerer"],
  "Tags": ["Damage", "Area", "Evocation"]
}
```

**Estrutura Completa:** Todas as magias D&D 5e

**Uso:** Referenciado por classes, features, items, etc.

### 6. `SpellSchoolDataTable.json`

```json
{
  "SchoolID": "SCH_Evocation",
  "SchoolName": "Evocation",
  "Description": "Spells that manipulate energy..."
}
```

**IDs Necessários:**
- `SCH_Abjuration`, `SCH_Conjuration`, `SCH_Divination`, `SCH_Enchantment`, `SCH_Evocation`, `SCH_Illusion`, `SCH_Necromancy`, `SCH_Transmutation`

### 7. `DamageTypeDataTable.json`

```json
{
  "DamageTypeID": "DAM_Fire",
  "DamageTypeName": "Fire",
  "Description": "Fire damage from flames..."
}
```

**IDs Necessários:**
- `DAM_Fire`, `DAM_Cold`, `DAM_Lightning`, `DAM_Poison`, `DAM_Psychic`, `DAM_Radiant`, `DAM_Necrotic`, `DAM_Acid`, `DAM_Force`, `DAM_Thunder`

### 8. `ConditionDataTable.json`

```json
{
  "ConditionID": "CON_Poisoned",
  "ConditionName": "Poisoned",
  "Description": "A poisoned creature has disadvantage...",
  "ConditionData": {
    "DisadvantageOn": ["AttackRolls", "AbilityChecks"]
  }
}
```

**IDs Necessários:**
- `CON_Blinded`, `CON_Charmed`, `CON_Deafened`, `CON_Frightened`, `CON_Grappled`, `CON_Incapacitated`, `CON_Invisible`, `CON_Paralyzed`, `CON_Petrified`, `CON_Poisoned`, `CON_Prone`, `CON_Restrained`, `CON_Stunned`, `CON_Unconscious`

---

## Tabelas Principais (Com IDs Únicos) - Prioridade 2

### 9. `RaceDataTable.json` (Refatorar `Race_All.json`)

```json
{
  "RaceID": "RACE_Elf",
  "RaceName": "Elf",
  "Description": "...",
  "Size": "Medium",
  "BaseSpeed": 30,
  "AbilityScoreImprovements": [
    {"AbilityID": "ABL_Dexterity", "Bonus": 2}
  ],
  "TraitIDs": ["TR_Darkvision", "TR_FeyAncestry", "TR_Trance"],
  "LanguageIDs": ["PL_Common", "PL_Elvish"],
  "LanguageChoiceCount": 0,
  "SubraceIDs": ["RACE_HighElf", "RACE_WoodElf", "RACE_Drow"]
}
```

**Mudanças Necessárias:**
- Adicionar `RaceID`
- Converter `Traits[]` → `TraitIDs[]` (referências)
- Converter `Languages[]` → `LanguageIDs[]` (referências)

### 10. `ClassDataTable.json` (Refatorar `DJ_Class.json`)

```json
{
  "ClassID": "CLASS_Fighter",
  "ClassName": "Fighter",
  "HitDie": 10,
  "MulticlassRequirements": [
    {"AbilityID": "ABL_Strength", "Value": 13, "Operator": "OR"},
    {"AbilityID": "ABL_Dexterity", "Value": 13, "Operator": "OR"}
  ],
  "ProficiencyIDs": {
    "Weapons": ["PW_Simple_Weapons", "PW_Martial_Weapons"],
    "Armor": ["PA_Light_Armor", "PA_Medium_Armor", "PA_Heavy_Armor"],
    "Shields": ["PS_Shields"],
    "SavingThrows": ["ABL_Strength", "ABL_Constitution"],
    "Skills": {
      "AvailableSkillIDs": ["PSK_Acrobatics", "PSK_Athletics", ...],
      "Count": 2
    }
  },
  "Progression": [
    {"Level": 1, "FeatureIDs": ["FC_SecondWind", "FC_FightingStyle"]}
  ],
  "StartingEquipmentIDs": ["ITM_ARM_ChainMail", "ITM_WPN_Longsword"],
  "StartingGold": 125,
  "Spellcasting": {
    "HasSpellcasting": false,
    "SpellcastingAbilityID": null,
    "SpellListID": null
  }
}
```

**Mudanças Necessárias:**
- Adicionar `ClassID`
- Converter `savingThrows[]` → `AbilityIDs[]` (referências)
- Converter `FSkills.available[]` → `SkillIDs[]` (referências)

### 11. `BackgroundDataTable.json` (Refatorar `Background_All.json`)

```json
{
  "BackgroundID": "BG_Acolyte",
  "BackgroundName": "Acolyte",
  "Description": "...",
  "SkillProficiencyIDs": ["PSK_Insight", "PSK_Religion"],
  "LanguageIDs": [],
  "LanguageChoiceCount": 2,
  "EquipmentIDs": ["ITM_OTH_HolySymbol", "ITM_OTH_PrayerBook", ...],
  "FeatureID": "TR_ShelterOfTheFaithful"
}
```

**Mudanças Necessárias:**
- Adicionar `BackgroundID`
- Converter `SkillProficiencies[]` → `SkillIDs[]` (referências)
- Converter `Languages[]` → `LanguageIDs[]` (referências)

### 12. `FeatDataTable.json` (Consolidar `DJ_FeatsGerais.json` + `Feat_All.json`)

```json
{
  "FeatID": "FEAT_Alert",
  "FeatName": "Alert",
  "FC_ID": "Feat_Alert",
  "Description": "...",
  "Prerequisites": [],
  "LevelUnlocked": 4,
  "FeatureData": {
    "InitiativeBonus": "5",
    "CannotBeSurprised": "true"
  }
}
```

**Mudanças Necessárias:**
- Consolidar os dois arquivos
- Usar `FeatID` como chave primária

### 13. `FeatureDataTable.json` (Já existe como `DJ_FeaturesClass.json`)

- **Status:** ✅ Já tem `FC_ID`
- **Melhorias:** Adicionar `FeatureID` como alias, garantir referências por ID

### 14. `ProficiencyDataTable.json` (Já existe como `DJ_Proficiencie.json`)

- **Status:** ✅ Já tem `ProficiencyID`
- **Sem mudanças necessárias**

### 15. `ItemDataTable.json` (Já existe como `Item_All.json`)

- **Status:** ✅ Já tem `ItemID`
- **Melhorias:** Adicionar referências a `SpellID` para itens mágicos, `DamageTypeID` para armas

---

## Estrutura de Dados Orientada a Performance (Data-Oriented Design)

### Estrutura Atual (Array of Structures - AoS)

```cpp
// ❌ INEFICIENTE - Dados espalhados na memória
TArray<FRaceData> Races; // Cada objeto tem todos os campos juntos
```

### Estrutura Ideal (Structure of Arrays - SoA)

```cpp
// ✅ EFICIENTE - Dados contíguos, cache-friendly
struct FRaceDataSoA {
    TArray<FName> RaceIDs;           // Array contíguo de IDs
    TArray<FName> RaceNames;         // Array contíguo de nomes
    TArray<int32> BaseSpeeds;        // Array contíguo de speeds
    TArray<TArray<FName>> TraitIDs;  // Array de arrays de traits
    // ... permite SIMD, prefetching, cache hits
};
```

### Serialização Binária (Estilo LSF/Baldur's Gate 3)

- **Formato:** FlatBuffers ou Protobuf (não JSON para runtime)
- **Versionamento:** Schema registry para backward/forward compatibility
- **Diferencial:** Salvar apenas deltas, não estado completo

---

## Padrão de Nomenclatura de IDs (Completo)

```
RACE_<Name>           → RACE_Dwarf, RACE_Elf, RACE_HighElf
CLASS_<Name>          → CLASS_Fighter, CLASS_Wizard
BG_<Name>             → BG_Acolyte, BG_Criminal
FEAT_<Name>           → FEAT_Alert, FEAT_Athlete
FC_<Name>             → FC_SecondWind, FC_Spellcasting (já existe)
TR_<Name>             → TR_Darkvision, TR_FeyAncestry
PL_<Name>             → PL_Common, PL_Elvish
PSK_<Name>            → PSK_Acrobatics, PSK_Stealth
ABL_<Name>            → ABL_Strength, ABL_Dexterity
SPL_<Name>            → SPL_Fireball, SPL_MagicMissile
SCH_<Name>            → SCH_Evocation, SCH_Abjuration
DAM_<Name>            → DAM_Fire, DAM_Cold
CON_<Name>            → CON_Poisoned, CON_Charmed
PW_<Name>             → PW_Simple_Weapons (já existe)
PA_<Name>             → PA_Light_Armor (já existe)
PT_<Name>             → PT_Thieves_Tools (já existe)
ITM_<Category>_<Name> → ITM_ARM_ChainMail (já existe)
```

---

## Checklist de Migração Completo

### Fase 1: Tabelas de Referência (CRÍTICO)

- [ ] Criar `AbilityScoreDataTable.json` com 6 atributos
- [ ] Criar `TraitDataTable.json` com todos os traits únicos
- [ ] Criar `LanguageDataTable.json` com todos os idiomas
- [ ] Criar `SkillDataTable.json` com todas as 18 skills
- [ ] Criar `SpellDataTable.json` com todas as magias D&D 5e
- [ ] Criar `SpellSchoolDataTable.json` com 8 escolas
- [ ] Criar `DamageTypeDataTable.json` com 10 tipos de dano
- [ ] Criar `ConditionDataTable.json` com 14 condições

### Fase 2: IDs Únicos em Tabelas Principais

- [ ] Adicionar `RaceID` em `Race_All.json` → `RaceDataTable.json`
- [ ] Adicionar `ClassID` em `DJ_Class.json` → `ClassDataTable.json`
- [ ] Adicionar `BackgroundID` em `Background_All.json` → `BackgroundDataTable.json`
- [ ] Consolidar `DJ_FeatsGerais.json` + `Feat_All.json` → `FeatDataTable.json` com `FeatID`

### Fase 3: Conversão de Referências Embutidas

- [ ] Converter `Race.Traits[]` → `Race.TraitIDs[]` (referências)
- [ ] Converter `Race.Languages[]` → `Race.LanguageIDs[]` (referências)
- [ ] Converter `Class.savingThrows[]` → `Class.SavingThrowIDs[]` (referências)
- [ ] Converter `Class.FSkills.available[]` → `Class.SkillIDs[]` (referências)
- [ ] Converter `Background.SkillProficiencies[]` → `Background.SkillIDs[]` (referências)
- [ ] Converter `Background.Languages[]` → `Background.LanguageIDs[]` (referências)
- [ ] Converter `AbilityScoreImprovements.AbilityName` → `AbilityID` (referências)

### Fase 4: Validação e Integridade

- [ ] Criar validadores de integridade referencial (ID inexistente = erro)
- [ ] Atualizar código C++ para usar IDs em todas as buscas
- [ ] Remover buscas por string/Name
- [ ] Implementar cache de lookups (ID → dados)

### Fase 5: Performance e Escalabilidade

- [ ] Considerar SoA para dados hot-path (se necessário)
- [ ] Implementar serialização binária (FlatBuffers) para saves
- [ ] Implementar serialização diferencial (apenas deltas)
- [ ] Criar índices para buscas frequentes (ID → row)

---

## Comparação: Antes vs Depois

| Aspecto | Antes (Atual) | Depois (Ideal) |
|---------|---------------|----------------|
| **Busca de Raça** | `FindRaceByName("Elf")` - O(n) string comparison | `FindRaceByID("RACE_Elf")` - O(1) hash lookup |
| **Traits Duplicados** | Darkvision definido 5x (Elf, Dwarf, etc.) | Darkvision definido 1x, referenciado 5x |
| **Manutenção** | Alterar trait = editar 5 arquivos | Alterar trait = editar 1 arquivo |
| **Integridade** | Nenhuma validação (typos aceitos) | Validação automática (ID inexistente = erro) |
| **Localização** | Nomes hardcoded | IDs estáveis, nomes traduzíveis |
| **Escalabilidade** | Adicionar raça = duplicar traits | Adicionar raça = referenciar traits existentes |
| **Spells** | ❌ Não existe | ✅ Tabela completa com todas as magias |

---

## Benefícios da Estrutura Ideal

1. **Escalabilidade:** Suporta milhares de spells, items, classes sem duplicação
2. **Performance:** Buscas por ID são O(1) vs O(n) por string
3. **Manutenção:** Alterar trait uma vez reflete em todas as raças
4. **Integridade:** Validação automática de referências
5. **Localização:** IDs estáveis, nomes traduzíveis
6. **GAS-ready:** Estrutura preparada para migração futura
7. **Baldur's Gate 3-ready:** Suporta complexidade similar (milhares de variáveis, estados, interações)

---

## Prioridade de Implementação

1. **CRÍTICO:** `SpellDataTable.json` (sistema de magias completamente ausente)
2. **CRÍTICO:** IDs únicos em todas as tabelas principais
3. **CRÍTICO:** Tabelas de referência (Trait, Language, Skill, AbilityScore)
4. **IMPORTANTE:** Conversão de referências embutidas para IDs
5. **IMPORTANTE:** Validadores de integridade referencial
6. **DESEJÁVEL:** Otimizações de performance (SoA, serialização binária)

---

## Conclusão

Esta estrutura suporta projetos AAA como Baldur's Gate 3, com milhares de spells, items, classes, diálogos e estados, mantendo dados organizados, escaláveis e performáticos. A chave é a normalização completa, uso consistente de IDs, e preparação para escalabilidade massiva desde o início.

