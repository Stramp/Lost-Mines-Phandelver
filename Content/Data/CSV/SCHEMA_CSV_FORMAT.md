# Schema de Formato CSV para Unreal Engine 5.7

## 📚 Schemas Específicos por Tabela

Para schemas detalhados de tabelas específicas, consulte:

- **`SCHEMA_AbilityScoreDataTable.md`** - Schema completo do AbilityScoreDataTable
- (Outros schemas específicos serão adicionados conforme necessário)

---

## 📋 Formato Base

### Estrutura do Cabeçalho
- **Primeira célula (A1)**: Vazia
- **Primeira coluna**: RowName (sem cabeçalho) - usa `ID` do JSON
- **Demais colunas**: Nomes exatos dos campos da struct

### Exemplo de Cabeçalho
```csv
,Name,ID,Abbreviation,Description,TypeTags
```

### Exemplo de Linha
```csv
ABL_Strength,Strength,ABL_Strength,STR,Physical power and athletic ability,(GameplayTags=((TagName="Ability.Physical")))
```

## 🏷️ Formato TypeTags (FGameplayTagContainer)

### Tag Única
```
(GameplayTags=((TagName="Ability.Physical")))
```

### Múltiplas Tags
```
(GameplayTags=((TagName="Feature.FightingStyle"),(TagName="Feature.Combat")))
```

### Tags Vazias
```
(vazio - string vazia "")
```

## 🔗 Formato FDataTableRowHandle

### Handle Único (Preenchido)
```
(DataTable="/Game/Data/SkillDataTable",RowName="PSK_Insight")
```

### Handle Único (Vazio)
```
(DataTable=None,RowName=None)
```

**Importante:** Campos vazios de `FDataTableRowHandle` **DEVEM** usar `(DataTable=None,RowName=None)`, não apenas `None` ou string vazia.

### Array de Handles
```
((DataTable="/Game/Data/SkillDataTable",RowName="PSK_Insight"),(DataTable="/Game/Data/SkillDataTable",RowName="PSK_Religion"))
```

**Importante:** Arrays sempre têm parênteses externos duplos: `((Entry1),(Entry2))`

## 📊 Formato Arrays de Structs

### FAbilityScoreImprovement
```
((AbilityID="ABL_Constitution",Bonus=2))
```

### Múltiplos Improvements
```
((AbilityID="ABL_Strength",Bonus=2),(AbilityID="ABL_Charisma",Bonus=1))
```

## 🔤 Formato FLanguageChoices

```
(Count=2)
```

## 📝 Regras Gerais

1. **Encoding**: UTF-8 com BOM (`utf-8-sig`)
2. **Aspas**: Campos com vírgulas devem estar entre aspas
3. **Campos Vazios**:
   - `FDataTableRowHandle`: `(DataTable=None,RowName=None)`
   - `TSoftObjectPtr`: `None` ou string vazia `""`
   - Outros: string vazia `""`
4. **Ordem das Colunas**: Deve corresponder exatamente à ordem na struct C++
5. **RowName**: Sempre a primeira coluna, sem cabeçalho

## ✅ Checklist de Validação

Antes de importar no Unreal Engine, verifique:

- [ ] Primeira célula (A1) está vazia?
- [ ] Primeira coluna é RowName (sem cabeçalho)?
- [ ] Todas as colunas da struct estão presentes?
- [ ] TypeTags no formato `(GameplayTags=((TagName="...")))`?
- [ ] Arrays de handles com parênteses duplos `((Entry1),(Entry2))`?
- [ ] Campos vazios de Handle como `(DataTable=None,RowName=None)`?
- [ ] Encoding UTF-8 com BOM?

## 📚 Exemplos Completos

### AbilityScoreDataTable

**Schema Completo:** Ver `SCHEMA_AbilityScoreDataTable.md`

**Exemplo:**
```csv
,Name,ID,Abbreviation,Description,TypeTags
ABL_Strength,Strength,ABL_Strength,STR,Physical power and athletic ability,"(GameplayTags=((TagName=""Ability.Physical"")))"
```

### BackgroundDataTable (com arrays)
```csv
,Name,ID,Description,TypeTags,SkillProficiencyHandles,LanguageHandles,LanguageChoices,Equipment,FeatureHandle,FeatureDescription
BG_Acolyte,Acolyte,BG_Acolyte,"Description...",(Background.Acolyte),"((DataTable=""/Game/Data/SkillDataTable"",RowName=""PSK_Insight""),(DataTable=""/Game/Data/SkillDataTable"",RowName=""PSK_Religion""))",,(Count=2),"[...]",(DataTable="/Game/Data/TraitDataTable",RowName="TR_ShelterOfTheFaithful"),"Description..."
```

### RaceDataTable (com structs)
```csv
,Name,ID,Description,TypeTags,AbilityScoreImprovements,Size,BaseSpeed,TraitHandles,SubraceHandles,LanguageHandles,IconTexture
RACE_Dwarf,Dwarf,RACE_Dwarf,Description...,(Race.Dwarf),"((AbilityID=""ABL_Constitution"",Bonus=2))",Medium,25,"((DataTable=""/Game/Data/TraitDataTable"",RowName=""TR_Darkvision""))","((DataTable=""/Game/Data/RaceDataTable"",RowName=""RACE_HillDwarf""))","((DataTable=""/Game/Data/LanguageDataTable"",RowName=""PL_Common""))",None
```

---

**Última Atualização:** Baseado em exportação real do Unreal Engine 5.7
**Formato Validado:** ✅ Testado e funcionando
