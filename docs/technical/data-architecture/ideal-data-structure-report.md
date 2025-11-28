# Relatório: Estrutura de Dados Ideal para Projeto AAA (Estilo Baldur's Gate 3)

## 🎯 Filosofia Fundamental: Composição sobre Herança

Para iniciar uma "estrutura perfeita" no Unreal Engine 5 (UE5) para um jogo complexo como Baldur's Gate 3, você deve seguir o princípio da **Composição sobre Herança** e a **Separação entre Definição (Static) e Estado (Dynamic)**.

### ⚠️ O Erro Mais Comum

O erro mais comum é tentar criar uma única Struct gigante com todos os campos possíveis (Dano, Cura, Armadura, Texto de Lore, etc.). Isso cria dados "sujos" e pesados.

### ✅ A Arquitetura Ideal

Abaixo apresento a arquitetura de dados ideal. Você terá:

- **Tabelas de Definição (Static)**: O que o item "é" - dados imutáveis armazenados em Data Tables
- **Estruturas de Instância (Dynamic)**: O que o item "tem" agora - dados mutáveis em runtime

### 📋 O Padrão "ID + Tags + Payload"

No Unreal Engine, JSON é apenas o meio de transporte. A estrutura real na engine deve usar:

- **Data Tables** para dados estáticos (definições)
- **Structs leves** para dados dinâmicos (estado em runtime)

**Filosofia:**
- **ID**: Identificador único (ex: `RaceID`, `ClassID`, `ItemID`)
- **Tags**: Metadados e categorização (ex: `Tags: ["Vision", "Racial"]`)
- **Payload**: Dados específicos do item (ex: `TraitData`, `FeatureData`)

### 📐 Estrutura JSON "Flat" (Plana)

Ao invés de um JSON profundo e aninhado (que o importador do Unreal odeia e quebra frequentemente), use uma estrutura relacional **"flat" (plana)**.

**Exemplo:** `DT_MasterItemDatabase.json` - Esta é a tabela mestra. Ela não contém stats de combate, apenas identidade e visual.

---

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

**Princípios Fundamentais:**

1. **Data-Oriented Design (DOD)**: Organizar dados por layout de memória, não por hierarquia de classes
2. **Entity Component System (ECS)**: Desacoplar identidade de dados e comportamento
3. **Separação Static/Dynamic**: Definições em Data Tables, estado em componentes runtime
4. **Composição sobre Herança**: Usar composição de componentes ao invés de árvores de herança

**Para mais detalhes sobre DOD e ECS, veja [high-performance-architectures-report.md](./high-performance-architectures-report.md)**

## Tabelas de Referência (Master Data) - Prioridade 1

### 1. `AbilityScoreDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Strength",
  "ID": "ABL_Strength",
  "Abbreviation": "STR",
  "Description": "Physical power and athletic ability",
  "TypeTags": ["Ability.Physical"]
}
```

**⚠️ IMPORTANTE:** O padrão atual usa `Name` como primeiro campo (Key Field do Unreal Engine) e `ID` como segundo campo.

**IDs Necessários:**
- `ABL_Strength`, `ABL_Dexterity`, `ABL_Constitution`, `ABL_Intelligence`, `ABL_Wisdom`, `ABL_Charisma`

**Uso:** Substituir strings "Strength", "Dexterity" em todo o sistema

### 2. `TraitDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Darkvision",
  "ID": "TR_Darkvision",
  "Description": "...",
  "TraitData": {
    "Range": "60",
    "Type": "Vision"
  },
  "TypeTags": ["Trait.Vision", "Trait.Racial"]
}
```

**⚠️ IMPORTANTE:** O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo. `TypeTags` é um `FGameplayTagContainer`, não um array de strings simples.

**IDs Necessários:**
- `TR_Darkvision`, `TR_FeyAncestry`, `TR_Trance`, `TR_Stonecunning`, etc.

**Uso:** Referenciado por `RaceID.TraitIDs[]`

### 3. `LanguageDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Common",
  "ID": "PL_Common",
  "Description": "The most widely spoken language",
  "Script": "Common",
  "Type": "Standard",
  "TypeTags": []
}
```

**⚠️ IMPORTANTE:** O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.

**IDs Necessários:**
- `PL_Common`, `PL_Elvish`, `PL_Dwarvish`, `PL_Abyssal`, etc.

**Uso:** Substituir strings "Common", "Elvish" em raças/backgrounds

### 4. `SkillDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Acrobatics",
  "ID": "PSK_Acrobatics",
  "AbilityID": "ABL_Dexterity",
  "Description": "Your Dexterity (Acrobatics) check covers...",
  "TypeTags": []
}
```

**⚠️ IMPORTANTE:** O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.

**IDs Necessários:**
- `PSK_Acrobatics`, `PSK_Athletics`, `PSK_Stealth`, etc.

**Uso:** Substituir strings em classes/backgrounds

### 5. `SpellDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Fireball",
  "ID": "SPL_Fireball",
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
    "DamageTypeID": "DMG_Fire",
    "SaveAbilityID": "ABL_Dexterity",
    "SaveType": "Half",
    "Area": "20-foot-radius sphere"
  },
  "TypeTags": ["Spell.Damage", "Spell.Area", "Spell.Evocation"]
}
```

**⚠️ IMPORTANTE:**
- O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.
- `DamageTypeID` usa prefixo `DMG_` (não `DAM_`).
- `TypeTags` é um `FGameplayTagContainer`, não um array de strings simples.

**Estrutura Completa:** Todas as magias D&D 5e

**Uso:** Referenciado por classes, features, items, etc.

### 6. `SpellSchoolDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Evocation",
  "ID": "SCH_Evocation",
  "Description": "Spells that manipulate energy...",
  "TypeTags": []
}
```

**⚠️ IMPORTANTE:** O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.

**IDs Necessários:**
- `SCH_Abjuration`, `SCH_Conjuration`, `SCH_Divination`, `SCH_Enchantment`, `SCH_Evocation`, `SCH_Illusion`, `SCH_Necromancy`, `SCH_Transmutation`

### 7. `DamageTypeDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Fire",
  "ID": "DMG_Fire",
  "Description": "Fire damage from flames...",
  "TypeTags": []
}
```

**⚠️ IMPORTANTE:**
- O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.
- Prefixo de ID é `DMG_` (não `DAM_`).

**IDs Necessários:**
- `DAM_Fire`, `DAM_Cold`, `DAM_Lightning`, `DAM_Poison`, `DAM_Psychic`, `DAM_Radiant`, `DAM_Necrotic`, `DAM_Acid`, `DAM_Force`, `DAM_Thunder`

### 8. `ConditionDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Poisoned",
  "ID": "COND_Poisoned",
  "Description": "A poisoned creature has disadvantage...",
  "ConditionData": {
    "DisadvantageOn": ["AttackRolls", "AbilityChecks"]
  },
  "TypeTags": []
}
```

**⚠️ IMPORTANTE:**
- O padrão atual usa `Name` como primeiro campo (Key Field) e `ID` como segundo campo.
- Prefixo de ID é `COND_` (não `CON_`).

**IDs Necessários:**
- `CON_Blinded`, `CON_Charmed`, `CON_Deafened`, `CON_Frightened`, `CON_Grappled`, `CON_Incapacitated`, `CON_Invisible`, `CON_Paralyzed`, `CON_Petrified`, `CON_Poisoned`, `CON_Prone`, `CON_Restrained`, `CON_Stunned`, `CON_Unconscious`

---

## Tabelas Principais (Com IDs Únicos) - Prioridade 2

### 9. `RaceDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Elf",
  "ID": "RACE_Elf",
  "Description": "...",
  "Size": "Medium",
  "BaseSpeed": 30,
  "TypeTags": ["Race.Elf", "Race.Fey"],
  "AbilityScoreImprovements": [
    {"AbilityID": "ABL_Dexterity", "Bonus": 2}
  ],
  "TraitHandles": [
    {"DataTable": "TraitDataTable", "RowName": "Darkvision"},
    {"DataTable": "TraitDataTable", "RowName": "FeyAncestry"},
    {"DataTable": "TraitDataTable", "RowName": "Trance"}
  ],
  "LanguageHandles": [
    {"DataTable": "LanguageDataTable", "RowName": "Common"},
    {"DataTable": "LanguageDataTable", "RowName": "Elvish"}
  ],
  "SubraceHandles": [
    {"DataTable": "RaceDataTable", "RowName": "HighElf"},
    {"DataTable": "RaceDataTable", "RowName": "WoodElf"},
    {"DataTable": "RaceDataTable", "RowName": "Drow"}
  ]
}
```

**✅ Implementado:**
- ✅ `Name` como Key Field, `ID` como segundo campo
- ✅ `TraitHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `LanguageHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `SubraceHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `TypeTags` para categorização via Gameplay Tags

### 10. `ClassDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Fighter",
  "ID": "CLASS_Fighter",
  "HitDie": 10,
  "TypeTags": ["Class.Fighter", "Class.Martial"],
  "MulticlassRequirements": [
    {"AbilityID": "ABL_Strength", "Value": 13, "Operator": "OR"},
    {"AbilityID": "ABL_Dexterity", "Value": 13, "Operator": "OR"}
  ],
  "Proficiencies": {
    "SavingThrowIDs": ["ABL_Strength", "ABL_Constitution"],
    "AvailableSkillHandles": [
      {"DataTable": "SkillDataTable", "RowName": "Acrobatics"},
      {"DataTable": "SkillDataTable", "RowName": "Athletics"}
    ],
    "SkillChoiceCount": 2
  },
  "Progression": [
    {
      "Level": 1,
      "FeatureHandles": [
        {"DataTable": "FeatureDataTable", "RowName": "SecondWind"},
        {"DataTable": "FeatureDataTable", "RowName": "FightingStyle"}
      ]
    }
  ],
  "StartingEquipment": ["ITM_ARM_ChainMail", "ITM_WPN_Longsword"],
  "StartingGold": 125
}
```

**✅ Implementado:**
- ✅ `Name` como Key Field, `ID` como segundo campo
- ✅ `SavingThrowIDs` usando IDs diretos (FName array)
- ✅ `AvailableSkillHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `FeatureHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `TypeTags` para categorização via Gameplay Tags

### 11. `BackgroundDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Acolyte",
  "ID": "BG_Acolyte",
  "Description": "...",
  "TypeTags": ["Background.Acolyte", "Background.Religious"],
  "SkillProficiencyHandles": [
    {"DataTable": "SkillDataTable", "RowName": "Insight"},
    {"DataTable": "SkillDataTable", "RowName": "Religion"}
  ],
  "LanguageHandles": [],
  "LanguageChoiceCount": 2,
  "EquipmentIDs": ["ITM_OTH_HolySymbol", "ITM_OTH_PrayerBook"],
  "FeatureHandle": {"DataTable": "FeatureDataTable", "RowName": "ShelterOfTheFaithful"}
}
```

**✅ Implementado:**
- ✅ `Name` como Key Field, `ID` como segundo campo
- ✅ `SkillProficiencyHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `LanguageHandles` usando `FDataTableRowHandle` (type-safe)
- ✅ `FeatureHandle` usando `FDataTableRowHandle` (type-safe)
- ✅ `TypeTags` para categorização via Gameplay Tags

### 12. `FeatDataTable.json` - ✅ IMPLEMENTADO

```json
{
  "Name": "Alert",
  "ID": "FEAT_Alert",
  "Description": "...",
  "Prerequisites": [],
  "LevelUnlocked": 4,
  "FeatureType": "FEAT_Alert",
  "FeatureData": {
    "InitiativeBonus": "5",
    "CannotBeSurprised": "true"
  },
  "TypeTags": ["Feat.Alert", "Feat.Combat"]
}
```

**✅ Implementado:**
- ✅ `Name` como Key Field, `ID` como segundo campo
- ✅ Consolidado de múltiplos arquivos
- ✅ `TypeTags` para categorização via Gameplay Tags

### 13. `FeatureDataTable.json` - ✅ IMPLEMENTADO

- **Status:** ✅ Implementado com `Name` (Key Field) e `ID`
- **Estrutura:** Suporta features automáticas, escolhas únicas e escolhas múltiplas
- **Referências:** Usa `AvailableChoices` (TArray<FFeatureChoice>) para opções de escolha
- **TypeTags:** Categorização via Gameplay Tags

### 14. `ProficiencyDataTable.json` - ✅ IMPLEMENTADO

- **Status:** ✅ Implementado com `Name` (Key Field) e `ID`
- **Estrutura:** Normalizado com `Name` e `ID` como primeiros campos
- **TypeTags:** Categorização via Gameplay Tags

### 15. `ItemDataTable.json` - ✅ IMPLEMENTADO

- **Status:** ✅ Implementado com `Name` (Key Field) e `ID`
- **Referências:**
  - ✅ `SpellHandle` (FDataTableRowHandle) para itens mágicos
  - ✅ `DamageTypeID` (FName) para armas
  - ✅ `IconTexture`, `MeshReference` (TSoftObjectPtr) para assets
- **TypeTags:** Categorização via Gameplay Tags

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

## Padrão de Nomenclatura de IDs (Completo) - ✅ IMPLEMENTADO

```
RACE_<Name>           → RACE_Dwarf, RACE_Elf, RACE_HighElf
CLASS_<Name>          → CLASS_Fighter, CLASS_Wizard
BG_<Name>             → BG_Acolyte, BG_Criminal
FEAT_<Name>           → FEAT_Alert, FEAT_Athlete
FC_<Name>             → FC_SecondWind, FC_Spellcasting
TR_<Name>             → TR_Darkvision, TR_FeyAncestry
PL_<Name>             → PL_Common, PL_Elvish
PSK_<Name>            → PSK_Acrobatics, PSK_Stealth
ABL_<Name>            → ABL_Strength, ABL_Dexterity
SPL_<Name>            → SPL_Fireball, SPL_MagicMissile
SCH_<Name>            → SCH_Evocation, SCH_Abjuration
DMG_<Name>            → DMG_Fire, DMG_Cold (⚠️ Prefixo é DMG_, não DAM_)
COND_<Name>           → COND_Poisoned, COND_Charmed (⚠️ Prefixo é COND_, não CON_)
PW_<Name>             → PW_Simple_Weapons
PA_<Name>             → PA_Light_Armor
PT_<Name>             → PT_Thieves_Tools
ITM_<Category>_<Name> → ITM_ARM_ChainMail
```

**⚠️ IMPORTANTE:**
- Todos os IDs seguem o padrão `<PREFIX>_<Name>` em UPPERCASE
- Prefixos de dano usam `DMG_` (não `DAM_`)
- Prefixos de condição usam `COND_` (não `CON_`)

---

## Checklist de Migração Completo - ✅ CONCLUÍDO

### Fase 1: Tabelas de Referência (CRÍTICO) - ✅ CONCLUÍDO

- [x] Criar `AbilityScoreDataTable.json` com 6 atributos
- [x] Criar `TraitDataTable.json` com todos os traits únicos
- [x] Criar `LanguageDataTable.json` com todos os idiomas
- [x] Criar `SkillDataTable.json` com todas as 18 skills
- [x] Criar `SpellDataTable.json` com todas as magias D&D 5e
- [x] Criar `SpellSchoolDataTable.json` com 8 escolas
- [x] Criar `DamageTypeDataTable.json` com 10 tipos de dano
- [x] Criar `ConditionDataTable.json` com 14 condições

### Fase 2: IDs Únicos em Tabelas Principais - ✅ CONCLUÍDO

- [x] Adicionar `Name` (Key Field) e `ID` em `RaceDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ClassDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `BackgroundDataTable.json`
- [x] Consolidar múltiplos arquivos → `FeatDataTable.json` com `Name` e `ID`
- [x] Adicionar `Name` (Key Field) e `ID` em `FeatureDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ProficiencyDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ItemDataTable.json`

### Fase 3: Conversão de Referências Embutidas - ✅ CONCLUÍDO

- [x] Converter `Race.Traits[]` → `Race.TraitHandles[]` (FDataTableRowHandle)
- [x] Converter `Race.Languages[]` → `Race.LanguageHandles[]` (FDataTableRowHandle)
- [x] Converter `Class.savingThrows[]` → `Class.SavingThrowIDs[]` (FName array)
- [x] Converter `Class.FSkills.available[]` → `Class.AvailableSkillHandles[]` (FDataTableRowHandle)
- [x] Converter `Background.SkillProficiencies[]` → `Background.SkillProficiencyHandles[]` (FDataTableRowHandle)
- [x] Converter `Background.Languages[]` → `Background.LanguageHandles[]` (FDataTableRowHandle)
- [x] Converter `AbilityScoreImprovements.AbilityName` → `AbilityID` (FName)

### Fase 4: Validação e Integridade - ✅ PARCIALMENTE CONCLUÍDO

- [x] Criar validadores de integridade referencial (ID inexistente = erro)
- [x] Atualizar código C++ para usar IDs em todas as buscas
- [x] Remover buscas por string/Name (substituídas por buscas por ID)
- [x] Implementar helpers para resolução de `FDataTableRowHandle` (type-safe)
- [ ] Implementar cache de lookups (ID → dados) - **Opcional para otimização futura**

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

## Prioridade de Implementação - ✅ CONCLUÍDO

1. ✅ **CONCLUÍDO:** `SpellDataTable.json` (sistema de magias implementado)
2. ✅ **CONCLUÍDO:** IDs únicos em todas as tabelas principais (padrão Name + ID)
3. ✅ **CONCLUÍDO:** Tabelas de referência (Trait, Language, Skill, AbilityScore, Spell, SpellSchool, DamageType, Condition)
4. ✅ **CONCLUÍDO:** Conversão de referências embutidas para `FDataTableRowHandle` (type-safe)
5. ✅ **CONCLUÍDO:** Validadores de integridade referencial via `DataTableRowHandleHelpers`
6. ⏳ **FUTURO:** Otimizações de performance (SoA, serialização binária) - **Opcional para projetos AAA**

---

## Conclusão

✅ **ESTRUTURA IMPLEMENTADA:** Esta estrutura suporta projetos AAA como Baldur's Gate 3, com milhares de spells, items, classes, diálogos e estados, mantendo dados organizados, escaláveis e performáticos.

**Princípios Implementados:**
- ✅ Normalização completa (15 Data Tables normalizadas)
- ✅ Uso consistente de IDs únicos (padrão Name + ID)
- ✅ Referências type-safe via `FDataTableRowHandle`
- ✅ Categorização flexível via Gameplay Tags (`TypeTags`)
- ✅ Separação de responsabilidades (Name para UI, ID para código)
- ✅ Preparação para escalabilidade massiva

**Próximos Passos (Opcionais):**
- ⏳ Otimizações de performance (SoA, serialização binária) para projetos AAA
- ⏳ Cache de lookups (ID → dados) para hot-paths
- ⏳ Serialização diferencial para saves complexos

**Referências:**
- [Arquitetura de Banco de Dados](./database-architecture.md) - Documentação completa da implementação atual
- [Gameplay Tags (Epic Games)](https://docs.unrealengine.com/5.7/en-US/gameplay-tags-in-unreal-engine/) - Documentação oficial
- [FDataTableRowHandle (Epic Games)](https://docs.unrealengine.com/5.7/en-US/data-table-row-handle-in-unreal-engine/) - Documentação oficial
