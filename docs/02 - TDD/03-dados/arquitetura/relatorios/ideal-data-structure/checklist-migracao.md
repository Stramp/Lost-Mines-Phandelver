# Checklist de Migração Completo - ✅ CONCLUÍDO

## Fase 1: Tabelas de Referência (CRÍTICO) - ✅ CONCLUÍDO

- [x] Criar `AbilityScoreDataTable.json` com 6 atributos
- [x] Criar `TraitDataTable.json` com todos os traits únicos
- [x] Criar `LanguageDataTable.json` com todos os idiomas
- [x] Criar `SkillDataTable.json` com todas as 18 skills
- [x] Criar `SpellDataTable.json` com todas as magias D&D 5e
- [x] Criar `SpellSchoolDataTable.json` com 8 escolas
- [x] Criar `DamageTypeDataTable.json` com 10 tipos de dano
- [x] Criar `ConditionDataTable.json` com 14 condições

## Fase 2: IDs Únicos em Tabelas Principais - ✅ CONCLUÍDO

- [x] Adicionar `Name` (Key Field) e `ID` em `RaceDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ClassDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `BackgroundDataTable.json`
- [x] Consolidar múltiplos arquivos → `FeatDataTable.json` com `Name` e `ID`
- [x] Adicionar `Name` (Key Field) e `ID` em `FeatureDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ProficiencyDataTable.json`
- [x] Adicionar `Name` (Key Field) e `ID` em `ItemDataTable.json`

## Fase 3: Conversão de Referências Embutidas - ✅ CONCLUÍDO

- [x] Converter `Race.Traits[]` → `Race.TraitHandles[]` (FDataTableRowHandle)
- [x] Converter `Race.Languages[]` → `Race.LanguageHandles[]` (FDataTableRowHandle)
- [x] Converter `Class.savingThrows[]` → `Class.SavingThrowIDs[]` (FName array)
- [x] Converter `Class.FSkills.available[]` → `Class.AvailableSkillHandles[]` (FDataTableRowHandle)
- [x] Converter `Background.SkillProficiencies[]` → `Background.SkillProficiencyHandles[]` (FDataTableRowHandle)
- [x] Converter `Background.Languages[]` → `Background.LanguageHandles[]` (FDataTableRowHandle)
- [x] Converter `AbilityScoreImprovements.AbilityName` → `AbilityID` (FName)

## Fase 4: Validação e Integridade - ✅ PARCIALMENTE CONCLUÍDO

- [x] Criar validadores de integridade referencial (ID inexistente = erro)
- [x] Atualizar código C++ para usar IDs em todas as buscas
- [x] Remover buscas por string/Name (substituídas por buscas por ID)
- [x] Implementar helpers para resolução de `FDataTableRowHandle` (type-safe)
- [ ] Implementar cache de lookups (ID → dados) - **Opcional para otimização futura**

## Fase 5: Performance e Escalabilidade

- [ ] Considerar SoA para dados hot-path (se necessário)
- [ ] Implementar serialização binária (FlatBuffers) para saves
- [ ] Implementar serialização diferencial (apenas deltas)
- [ ] Criar índices para buscas frequentes (ID → row)

---

## 🔗 Navegação

- [📚 Relatório - Índice](./index.md)
- [📊 Comparação: Antes vs Depois](./comparacao-antes-depois.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
