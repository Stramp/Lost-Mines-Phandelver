# Problemas Críticos Identificados

## 1. Falta de IDs Únicos (Normalização)

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

## 2. Dados Embutidos (Não Normalizados)

- **`Race_All.json`**: `Traits` embutidos (sem `TraitID`), `Languages` como strings (sem `LanguageID`)
- **`DJ_Class.json`**: `savingThrows` como strings (sem `AbilityID`), `FSkills.available` como strings (sem `SkillID`)
- **`Background_All.json`**: `SkillProficiencies` como strings (sem `SkillID`), `Languages` como strings (sem `LanguageID`)
- **Traits Repetidos**: `Darkvision` aparece em Elf, Dwarf, etc. (duplicação massiva)

## 3. Falta de Tabelas de Referência (Master Data)

- ❌ `TraitDataTable.json` - Traits reutilizáveis
- ❌ `LanguageDataTable.json` - Idiomas reutilizáveis
- ❌ `SkillDataTable.json` - Skills reutilizáveis
- ❌ `AbilityScoreDataTable.json` - Atributos padronizados
- ❌ `SpellDataTable.json` - **MAGIAS (CRÍTICO, NÃO EXISTE)**
- ❌ `SpellSchoolDataTable.json` - Escolas de magia
- ❌ `DamageTypeDataTable.json` - Tipos de dano
- ❌ `ConditionDataTable.json` - Condições (Poisoned, Charmed, etc.)

## 4. Duplicação de Dados

- `Feat_All.json` e `DJ_FeatsGerais.json` - Mesma informação, formatos diferentes
- Traits duplicados entre raças
- Languages duplicados entre raças/backgrounds
- Skills duplicados entre classes/backgrounds

---

## 🔗 Navegação

- [📚 Relatório - Índice](./index.md)
- [📊 Análise dos JSONs Existentes](./analise-jsons-existentes.md)
- [✅ Estrutura Ideal](./estrutura-ideal.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
