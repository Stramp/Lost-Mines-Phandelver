# Revisão de Migração - Problemas Encontrados

## 🔴 Problemas Críticos

### 1. FRaceTrait não existe mais
**Status:** ❌ Código ainda usa estrutura antiga

**Arquivos afetados:**
- `CharacterSheetComponent.cpp` (linhas 104, 119) - usa `RaceRow->Traits`
- `CharacterSheetHelpers.cpp` (linhas 380, 405) - usa `RaceRow->Traits` e `SubraceRow->Traits`
- `Step1_ChooseRaceTests.cpp` (linhas 100-103, 115) - cria `FRaceTrait` que não existe

**Solução:**
- Usar `RaceRow->TraitHandles` e resolver via `TraitDataTable`
- Criar helper `DataTableHelpers::ResolveTraitHandles()` ou usar `DataTableRowHandleHelpers::ResolveHandle<FTraitDataRow>()`

### 2. AbilityName → AbilityID
**Status:** ❌ Código ainda usa AbilityName

**Arquivos afetados:**
- `RaceBonusHelpers.cpp` (linhas 20, 22, 29, 42, 74, 76, 83) - usa `Improvement.AbilityName`

**Solução:**
- Substituir `AbilityName` por `AbilityID`
- Converter `AbilityID` para `FName` de ability score (ex: "ABL_Strength" → "Strength") quando necessário

### 3. savingThrows → SavingThrowIDs
**Status:** ⚠️ Inconsistência entre estruturas

**Arquivos afetados:**
- `FMulticlassProficienciesEntry` (linha 79) - ainda tem `savingThrows`
- `Step2_ChooseClassTests.cpp` (linha 203) - usa `savingThrows`
- `CharacterSheetDataAssetLoadersTests.cpp` (linhas 151-152) - usa `savingThrows`
- `MulticlassHelpers.cpp` (linha 191) - usa `savingThrows`

**Solução:**
- Atualizar `FMulticlassProficienciesEntry` para usar `SavingThrowIDs` (consistência com `FProficienciesEntry`)
- Atualizar todos os usos

### 4. FMulticlassSkills vs FSkills
**Status:** ✅ Estruturas diferentes (runtime vs definition)

**Observação:**
- `FSkills` (em `FProficienciesEntry`) - JÁ ATUALIZADO para `AvailableSkillHandles` e `Count` ✅
- `FMulticlassSkills` (em `FMulticlassProficienciesEntry`) - Estrutura RUNTIME diferente, mantém `available`, `qtdAvailable`, `InitialAvailable` por enquanto

**Ação:** Manter `FMulticlassSkills` como está por enquanto (estrutura runtime para UI/Editor)

---

## 📋 Checklist de Correções

- [ ] Corrigir `CharacterSheetComponent.cpp` - usar `TraitHandles` ao invés de `Traits`
- [ ] Corrigir `CharacterSheetHelpers.cpp` - usar `TraitHandles` ao invés de `Traits`
- [ ] Corrigir `Step1_ChooseRaceTests.cpp` - remover criação de `FRaceTrait`
- [ ] Corrigir `RaceBonusHelpers.cpp` - usar `AbilityID` ao invés de `AbilityName`
- [ ] Atualizar `FMulticlassProficienciesEntry` - `savingThrows` → `SavingThrowIDs`
- [ ] Corrigir `Step2_ChooseClassTests.cpp` - usar `SavingThrowIDs`
- [ ] Corrigir `CharacterSheetDataAssetLoadersTests.cpp` - usar `SavingThrowIDs`
- [ ] Corrigir `MulticlassHelpers.cpp` - usar `SavingThrowIDs`

---

**Data:** 2024-12-XX
**Fase:** Revisão pós-Fase 3
