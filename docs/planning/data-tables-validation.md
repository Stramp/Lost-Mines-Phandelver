---
title: "Validação de Data Tables - Checklist Detalhado"
category: planning
tags: [data-tables, validation, checklist, phase-0]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Validação de Data Tables

# Validação de Data Tables - Checklist Detalhado

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este documento contém o checklist detalhado para validação de cada Data Table do projeto.
>
> **Objetivo:** Garantir que todas as 15 Data Tables estejam 100% configuradas, validadas e prontas antes de continuar com funcionalidades.
>
> **Metodologia:** Validar uma tabela por vez, confirmando cada item do checklist antes de passar para a próxima.
>
> **Status Geral:** 🔄 **Em Andamento** - Nenhuma tabela validada ainda

</details>

---

## 📋 Tabelas de Referência (Master Data) - 9 Tabelas

### DT-001: AbilityScoreDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/AbilityScoreDataTable.csv`
> - `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FAbilityScoreDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Abbreviation, Description
> - [ ] **IDs Válidos:** ABL_Strength, ABL_Dexterity, ABL_Constitution, ABL_Intelligence, ABL_Wisdom, ABL_Charisma
> - [ ] **Dados Completos:** 6 ability scores presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** Outras tabelas referenciam corretamente (ex: SkillDataTable usa AbilityID)
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-002: TraitDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/TraitDataTable.csv`
> - `Source/MyProject2/Data/Tables/TraitDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FTraitDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Description, TraitData
> - [ ] **IDs Válidos:** TR_Darkvision, TR_FeyAncestry, TR_Trance, etc.
> - [ ] **Dados Completos:** Todos os traits raciais presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** RaceDataTable referencia corretamente via TraitHandles
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-003: LanguageDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/LanguageDataTable.csv`
> - `Source/MyProject2/Data/Tables/LanguageDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FLanguageDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Description, Script, Type
> - [ ] **IDs Válidos:** PL_Common, PL_Elvish, PL_Dwarvish, etc.
> - [ ] **Dados Completos:** Todos os idiomas D&D 5e presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** RaceDataTable e BackgroundDataTable referenciam corretamente
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-004: SkillDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/SkillDataTable.csv`
> - `Source/MyProject2/Data/Tables/SkillDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FSkillDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, AbilityID, Description
> - [ ] **IDs Válidos:** PSK_Acrobatics, PSK_AnimalHandling, etc. (18 skills)
> - [ ] **Dados Completos:** Todos os 18 skills D&D 5e presentes
> - [ ] **Referências:** AbilityID referencia AbilityScoreDataTable corretamente
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** ClassDataTable e BackgroundDataTable referenciam corretamente
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-005: SpellDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/SpellDataTable.csv`
> - `Source/MyProject2/Data/Tables/SpellDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FSpellDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Level, SchoolID, Description
> - [ ] **IDs Válidos:** SPL_MagicMissile, SPL_Fireball, etc.
> - [ ] **Dados Completos:** Magias essenciais presentes (pelo menos cantrips e nível 1)
> - [ ] **Referências:** SchoolID referencia SpellSchoolDataTable corretamente
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-006: SpellSchoolDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/SpellSchoolDataTable.csv`
> - `Source/MyProject2/Data/Tables/SpellSchoolDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FSpellSchoolDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Description
> - [ ] **IDs Válidos:** SSCH_Abjuration, SSCH_Conjuration, SSCH_Divination, SSCH_Enchantment, SSCH_Evocation, SSCH_Illusion, SSCH_Necromancy, SSCH_Transmutation
> - [ ] **Dados Completos:** 8 escolas de magia presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** SpellDataTable referencia corretamente
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-007: DamageTypeDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/DamageTypeDataTable.csv`
> - `Source/MyProject2/Data/Tables/DamageTypeDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FDamageTypeDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Description
> - [ ] **IDs Válidos:** DMG_Acid, DMG_Cold, DMG_Fire, DMG_Force, DMG_Lightning, DMG_Necrotic, DMG_Poison, DMG_Psychic, DMG_Radiant, DMG_Thunder
> - [ ] **Dados Completos:** 10 tipos de dano presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-008: ConditionDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/ConditionDataTable.csv`
> - `Source/MyProject2/Data/Tables/ConditionDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FConditionDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Description
> - [ ] **IDs Válidos:** COND_Blinded, COND_Charmed, COND_Deafened, COND_Frightened, COND_Grappled, COND_Incapacitated, COND_Invisible, COND_Paralyzed, COND_Petrified, COND_Poisoned, COND_Prone, COND_Restrained, COND_Stunned, COND_Unconscious, COND_Exhaustion
> - [ ] **Dados Completos:** 15 condições D&D 5e presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-009: ProficiencyDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/ProficiencyDataTable.csv`
> - `Source/MyProject2/Data/Tables/ProficiencyDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FProficiencyDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, ProficiencyType, Description
> - [ ] **IDs Válidos:** PROF_Skill, PROF_Language, PROF_Weapon, PROF_Armor, PROF_Tool, etc.
> - [ ] **Dados Completos:** Proficiências de Skills, Languages, Weapons, Armor, Tools presentes
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Referências:** RaceDataTable, ClassDataTable, BackgroundDataTable referenciam corretamente
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

## 📋 Tabelas Principais - 6 Tabelas

### DT-010: RaceDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/RaceDataTable.csv`
> - `Source/MyProject2/Data/Tables/RaceDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FRaceDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, RaceType, AbilityScoreBonuses, TraitHandles, LanguageHandles
> - [ ] **IDs Válidos:** RACE_Human, RACE_Elf, RACE_Dwarf, RACE_Halfling, RACE_Dragonborn, RACE_Gnome, RACE_HalfElf, RACE_HalfOrc, RACE_Tiefling
> - [ ] **Dados Completos:** 9 raças principais + sub-raças presentes
> - [ ] **Referências:** TraitHandles referencia TraitDataTable corretamente
> - [ ] **Referências:** LanguageHandles referencia LanguageDataTable corretamente
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-011: ClassDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/ClassDataTable.csv`
> - `Source/MyProject2/Data/Tables/ClassDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FClassDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, HitDie, SavingThrows, SkillProficiencies, Progression
> - [ ] **IDs Válidos:** CLASS_Barbarian, CLASS_Bard, CLASS_Cleric, CLASS_Druid, CLASS_Fighter, CLASS_Monk, CLASS_Paladin, CLASS_Ranger, CLASS_Rogue, CLASS_Sorcerer, CLASS_Warlock, CLASS_Wizard
> - [ ] **Dados Completos:** 12 classes principais + progressão completa (níveis 1-20)
> - [ ] **Referências:** SavingThrows referencia AbilityScoreDataTable corretamente
> - [ ] **Referências:** SkillProficiencies referencia SkillDataTable corretamente
> - [ ] **Referências:** Progression referencia FeatureDataTable corretamente
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-012: BackgroundDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/BackgroundDataTable.csv`
> - `Source/MyProject2/Data/Tables/BackgroundDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FBackgroundDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, SkillProficiencies, LanguageHandles, FeatureHandles
> - [ ] **IDs Válidos:** BG_Acolyte, BG_Criminal, BG_FolkHero, BG_Noble, BG_Sage, BG_Soldier, etc.
> - [ ] **Dados Completos:** Backgrounds principais D&D 5e presentes
> - [ ] **Referências:** SkillProficiencies referencia SkillDataTable corretamente
> - [ ] **Referências:** LanguageHandles referencia LanguageDataTable corretamente
> - [ ] **Referências:** FeatureHandles referencia FeatureDataTable corretamente
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-013: FeatDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/FeatDataTable.csv`
> - `Source/MyProject2/Data/Tables/FeatDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FFeatDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, Prerequisites, Description
> - [ ] **IDs Válidos:** FEAT_GreatWeaponMaster, FEAT_Sharpshooter, FEAT_Alert, etc.
> - [ ] **Dados Completos:** Feats principais D&D 5e presentes
> - [ ] **Referências:** Prerequisites referencia AbilityScoreDataTable corretamente (se aplicável)
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset (Variant Human)
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-014: FeatureDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/FeatureDataTable.csv`
> - `Source/MyProject2/Data/Tables/FeatureDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FFeatureDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, FeatureType, Description, Choices (se aplicável)
> - [ ] **IDs Válidos:** FC_FightingStyle, FC_Spellcasting, FC_ActionSurge, etc.
> - [ ] **Dados Completos:** Features de classes principais presentes
> - [ ] **Referências:** Choices referencia outras tabelas corretamente (se aplicável)
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset e ClassDataTable
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

### DT-015: ItemDataTable

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Checklist de Validação</summary>

> **Status:** ⚠️ Aguardando Validação
>
> **Arquivos:**
>
> - `Content/Data/CSV/ItemDataTable.csv`
> - `Source/MyProject2/Data/Tables/ItemDataTable.h` (se existir)
>
> **Checklist:**
>
> - [ ] **Estrutura C++:** Struct `FItemDataRow` existe e está correta
> - [ ] **Campos Obrigatórios:** Name, ID, ItemType, Weight, Cost, Description
> - [ ] **IDs Válidos:** ITM_Longsword, ITM_LeatherArmor, ITM_Shield, etc.
> - [ ] **Dados Completos:** Itens essenciais para Starting Equipment presentes
> - [ ] **Referências:** ItemType referencia outras tabelas corretamente (se aplicável)
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Funciona com CharacterSheetDataAsset (Step 5 - Starting Equipment)
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> **Observações:**
>
> - [ ] Anotar problemas encontrados
> - [ ] Anotar dependências de outras tabelas
>
> **✅ Validada:** [ ] Sim [ ] Não
>
> **Data de Validação:** _______________

</details>

---

## 📊 Resumo de Progresso

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Status Geral</b></summary>

> **Tabelas Validadas:** 0/15 (0%)
>
> **Tabelas de Referência:** 0/9 (0%)
>
> **Tabelas Principais:** 0/6 (0%)
>
> **Próxima Tabela a Validar:** DT-001 (AbilityScoreDataTable)
>
> **Última Atualização:** 2024-12-27

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
