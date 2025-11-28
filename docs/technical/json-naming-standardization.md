# Padronização de Nomenclatura JSON - Padrão Name/ID

## 📋 Resumo

Todos os JSONs foram padronizados para seguir o padrão **Name/ID** consistente, garantindo compatibilidade total com os structs C++.

## ✅ Correções Aplicadas

### 1. FeatDataTable.json

**Problemas Encontrados:**
- ❌ Algumas entradas usavam `"FC_ID"` ao invés de `"ID"`
- ❌ Todas as entradas tinham `"FeatID"` (duplicado/redundante)

**Correções:**
- ✅ Todos `"FC_ID"` substituídos por `"ID"`
- ✅ Todos `"FeatID"` removidos (redundante)
- ✅ Ordem padronizada: `Name`, `ID` primeiro

**Resultado:**
```json
{
  "Name": "Alert",
  "ID": "Feat_Alert",
  "Description": "...",
  "TypeTags": [...]
}
```

### 2. FeatureDataTable.json

**Problemas Encontrados:**
- ❌ Algumas entradas usavam `"FC_ID"` ao invés de `"ID"`
- ❌ Todas as entradas tinham `"FeatureID"` (duplicado/redundante)

**Correções:**
- ✅ Todos `"FC_ID"` substituídos por `"ID"`
- ✅ Todos `"FeatureID"` removidos (redundante)
- ✅ Ordem padronizada: `Name`, `ID` primeiro

**Resultado:**
```json
{
  "Name": "Second Wind",
  "ID": "FC_SecondWind",
  "Description": "...",
  "TypeTags": [...]
}
```

### 3. ProficiencyDataTable.json

**Problemas Encontrados:**
- ❌ Primeira entrada tinha `"ID"` (correto)
- ❌ Todas as outras entradas usavam `"ProficiencyID"` ao invés de `"ID"`

**Correções:**
- ✅ Todos `"ProficiencyID"` substituídos por `"ID"`
- ✅ Ordem padronizada: `Name`, `ID` primeiro

**Resultado:**
```json
{
  "Name": "Martial Weapons",
  "ID": "PW_Martial_Weapons",
  "Type": "Weapon",
  "Description": "..."
}
```

## 📊 Status Final de Todos os JSONs

### ✅ JSONs Corretos (já seguiam padrão)

- ✅ **ConditionDataTable.json** - Name, ID (correto)
- ✅ **DamageTypeDataTable.json** - Name, ID (correto)
- ✅ **SpellSchoolDataTable.json** - Name, ID (correto)
- ✅ **SpellDataTable.json** - Name, ID (correto)
- ✅ **RaceDataTable.json** - Name, ID (correto)
- ✅ **BackgroundDataTable.json** - Name, ID (correto)
- ✅ **SkillDataTable.json** - Name, ID (correto)
- ✅ **AbilityScoreDataTable.json** - Name, ID (correto)
- ✅ **TraitDataTable.json** - Name, ID (correto)
- ✅ **LanguageDataTable.json** - Name, ID (correto)
- ✅ **ItemDataTable.json** - Name, ID (correto)
- ✅ **ClassDataTable.json** - Name, ID (correto)

### ✅ JSONs Corrigidos

- ✅ **FeatDataTable.json** - Corrigido (81 correções)
- ✅ **FeatureDataTable.json** - Corrigido (187 correções)
- ✅ **ProficiencyDataTable.json** - Corrigido (63 correções)

## 🎯 Padrão Aplicado

Todos os JSONs agora seguem o padrão consistente:

1. **Name** - Primeiro campo (Key Field, nome legível)
2. **ID** - Segundo campo (identificador único)
3. **TypeTags** - Terceiro campo (Gameplay Tags)
4. **Outros campos** - Campos específicos (Description, SpellLevel, etc.)
5. **Payload** - Dados estruturados (SpellData, FeatureData, etc.)

## 📦 Backups Criados

Backups automáticos foram criados antes das correções:

- `FeatDataTable.json.backup2`
- `FeatureDataTable.json.backup2`
- `ProficiencyDataTable.json.backup2`

## ⚠️ Nota sobre Structs C++

Os structs C++ `FFeatDataRow` e `FFeatureDataRow` ainda contêm os campos `FeatID` e `FeatureID` respectivamente, mas:

- ✅ **Não são usados no código** - O código usa apenas `ID`
- ✅ **São inicializados automaticamente** - Construtores definem `FeatID = ID` e `FeatureID = ID`
- ✅ **Compatibilidade mantida** - Se algum código legado usar esses campos, ainda funcionará
- ⚠️ **Recomendação futura** - Considerar remover esses campos dos structs para seguir padrão estrito Name/ID

## ✅ Validação Final

- ✅ Todos os campos JSON correspondem aos structs C++
- ✅ Nomenclatura padronizada (`ID` único, sem duplicados)
- ✅ Ordem dos campos otimizada (Name, ID primeiro)
- ✅ Padrão "ID + Tags + Payload" mantido
- ✅ Compatibilidade total com importador Unreal Engine
- ✅ Sem campos redundantes nos JSONs

## 📈 Estatísticas

- **Total de JSONs revisados:** 15
- **JSONs corrigidos:** 3
- **Total de correções:** 331
  - FeatDataTable: 81 correções
  - FeatureDataTable: 187 correções
  - ProficiencyDataTable: 63 correções

## 🎯 Benefícios

1. **Consistência Total** - Todos os JSONs seguem o mesmo padrão
2. **Manutenibilidade** - Fácil identificar campos principais
3. **Type Safety** - Importador Unreal valida campos automaticamente
4. **Legibilidade** - Campos ordenados logicamente
5. **Compatibilidade** - Total compatibilidade com structs C++

---

**Data da Padronização:** 2024-12-XX
**Status:** ✅ Completo - Todos os JSONs seguem padrão Name/ID
