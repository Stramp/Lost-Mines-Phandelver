# Schema CSV - AbilityScoreDataTable

## 📋 Informações da Tabela

- **Struct C++**: `FAbilityScoreDataRow`
- **Arquivo**: `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h`
- **Tipo**: Master Data (Tabela de referência usada por todas as outras tabelas)
- **Sistema**: D&D 5e - Ability Scores (Atributos)

## 🎯 Propósito

Define os 6 atributos fundamentais do D&D 5e:
- **Physical**: Strength, Dexterity, Constitution
- **Mental**: Intelligence, Wisdom, Charisma

## 📊 Estrutura do CSV

### Header (Cabeçalho)

```csv
,Name,ID,Abbreviation,Description,TypeTags
```

**Nota:** Primeira célula (A1) está vazia, primeira coluna é RowName (sem cabeçalho).

### Ordem das Colunas

A ordem **DEVE** corresponder exatamente à ordem na struct C++:

1. **RowName** (primeira coluna, sem cabeçalho) - Usa `ID` como valor
2. **Name** (FName) - Nome do atributo
3. **ID** (FName) - ID único do atributo
4. **Abbreviation** (FName) - Abreviação do atributo
5. **Description** (FText) - Descrição do atributo
6. **TypeTags** (FGameplayTagContainer) - Tags de categorização

## 📝 Detalhamento das Colunas

### 1. RowName (Primeira Coluna)

- **Tipo**: FName (implícito - primeira coluna)
- **Formato**: ID do atributo (ex: `ABL_Strength`, `ABL_Dexterity`)
- **Obrigatório**: ✅ Sim
- **Exemplo**: `ABL_Strength`

**Padrão de Nomenclatura:**
- Prefixo: `ABL_`
- Nome: Nome do atributo em PascalCase
- Exemplos: `ABL_Strength`, `ABL_Intelligence`

### 2. Name

- **Tipo**: FName
- **Descrição**: Nome legível do atributo
- **Obrigatório**: ✅ Sim
- **Valores Esperados (D&D 5e)**:
  - `Strength`
  - `Dexterity`
  - `Constitution`
  - `Intelligence`
  - `Wisdom`
  - `Charisma`
- **Exemplo**: `Strength`

### 3. ID

- **Tipo**: FName
- **Descrição**: ID único do atributo (deve corresponder ao RowName)
- **Obrigatório**: ✅ Sim
- **Formato**: Mesmo que RowName
- **Exemplo**: `ABL_Strength`

### 4. Abbreviation

- **Tipo**: FName
- **Descrição**: Abreviação padrão do atributo (usada em cálculos e UI)
- **Obrigatório**: ✅ Sim
- **Valores Esperados (D&D 5e)**:
  - `STR` (Strength)
  - `DEX` (Dexterity)
  - `CON` (Constitution)
  - `INT` (Intelligence)
  - `WIS` (Wisdom)
  - `CHA` (Charisma)
- **Exemplo**: `STR`

### 5. Description

- **Tipo**: FText
- **Descrição**: Descrição textual do atributo (localizável)
- **Obrigatório**: ✅ Sim
- **Formato**: Texto livre (pode conter vírgulas - usar aspas se necessário)
- **Exemplos**:
  - `Physical power and athletic ability`
  - `"Agility, reflexes, and balance"` (com aspas se contém vírgula)
  - `Reasoning, memory, and analytical thought`

### 6. TypeTags

- **Tipo**: FGameplayTagContainer
- **Descrição**: Tags de categorização (Physical ou Mental)
- **Obrigatório**: ✅ Sim
- **Formato**: `(GameplayTags=((TagName="Ability.Physical")))` ou `(GameplayTags=((TagName="Ability.Mental")))`
- **Valores Esperados**:
  - `Ability.Physical` - Para STR, DEX, CON
  - `Ability.Mental` - Para INT, WIS, CHA
- **Exemplo**: `(GameplayTags=((TagName="Ability.Physical")))`

**Importante:**
- Tags devem existir em `Config/DefaultGameplayTags.ini`
- Formato com aspas duplas escapadas: `""` dentro do CSV

## ✅ Validação D&D 5e

### Ability Scores Obrigatórios

O CSV **DEVE** conter exatamente 6 linhas (uma para cada ability score):

1. ✅ **Strength** (ABL_Strength, STR) - Physical
2. ✅ **Dexterity** (ABL_Dexterity, DEX) - Physical
3. ✅ **Constitution** (ABL_Constitution, CON) - Physical
4. ✅ **Intelligence** (ABL_Intelligence, INT) - Mental
5. ✅ **Wisdom** (ABL_Wisdom, WIS) - Mental
6. ✅ **Charisma** (ABL_Charisma, CHA) - Mental

### Classificação Physical vs Mental

**Physical (Ability.Physical):**
- Strength
- Dexterity
- Constitution

**Mental (Ability.Mental):**
- Intelligence
- Wisdom
- Charisma

## 📋 Exemplo Completo

```csv
,Name,ID,Abbreviation,Description,TypeTags
ABL_Strength,Strength,ABL_Strength,STR,Physical power and athletic ability,"(GameplayTags=((TagName=""Ability.Physical"")))"
ABL_Dexterity,Dexterity,ABL_Dexterity,DEX,"Agility, reflexes, and balance","(GameplayTags=((TagName=""Ability.Physical"")))"
ABL_Constitution,Constitution,ABL_Constitution,CON,"Endurance, health, and stamina","(GameplayTags=((TagName=""Ability.Physical"")))"
ABL_Intelligence,Intelligence,ABL_Intelligence,INT,"Reasoning, memory, and analytical thought","(GameplayTags=((TagName=""Ability.Mental"")))"
ABL_Wisdom,Wisdom,ABL_Wisdom,WIS,"Awareness, intuition, and insight","(GameplayTags=((TagName=""Ability.Mental"")))"
ABL_Charisma,Charisma,ABL_Charisma,CHA,"Force of personality, persuasiveness, and leadership","(GameplayTags=((TagName=""Ability.Mental"")))"
```

## 🔍 Checklist de Validação

Antes de importar no Unreal Engine, verifique:

- [ ] Primeira célula (A1) está vazia?
- [ ] Primeira coluna é RowName (sem cabeçalho)?
- [ ] Todas as 6 ability scores estão presentes?
- [ ] Nomes estão corretos (Strength, Dexterity, etc.)?
- [ ] IDs seguem o padrão `ABL_*`?
- [ ] Abreviações estão corretas (STR, DEX, CON, INT, WIS, CHA)?
- [ ] TypeTags no formato `(GameplayTags=((TagName="...")))`?
- [ ] TypeTags usam `Ability.Physical` ou `Ability.Mental`?
- [ ] Classificação Physical/Mental está correta?
- [ ] Encoding UTF-8 com BOM?
- [ ] RowName = ID em cada linha?

## 🎯 Regras Específicas

### 1. RowName = ID

**CRÍTICO:** O valor da primeira coluna (RowName) **DEVE** ser idêntico ao valor da coluna `ID`.

**✅ CORRETO:**
```csv
ABL_Strength,Strength,ABL_Strength,STR,...
```

**❌ ERRADO:**
```csv
STR_Strength,Strength,ABL_Strength,STR,...  # RowName diferente de ID
```

### 2. TypeTags Obrigatório

**CRÍTICO:** Cada ability score **DEVE** ter uma TypeTag (`Ability.Physical` ou `Ability.Mental`).

**NÃO** pode estar vazio.

### 3. Abreviações Padrão D&D 5e

As abreviações **DEVEM** seguir o padrão oficial do D&D 5e:
- STR (não ST ou STRENGTH)
- DEX (não DX ou DEXTERITY)
- CON (não CN ou CONSTITUTION)
- INT (não IN ou INTELLIGENCE)
- WIS (não WS ou WISDOM)
- CHA (não CH ou CHARISMA)

### 4. Ordem das Linhas

A ordem das linhas **NÃO** importa para o Unreal Engine, mas é recomendado seguir a ordem padrão D&D 5e:
1. Strength
2. Dexterity
3. Constitution
4. Intelligence
5. Wisdom
6. Charisma

## 🔗 Dependências

### Gameplay Tags Necessárias

As seguintes tags **DEVEM** existir em `Config/DefaultGameplayTags.ini`:

```ini
+GameplayTagList=(Tag="Ability.Physical",DevComment="Physical ability score")
+GameplayTagList=(Tag="Ability.Mental",DevComment="Mental ability score")
```

### Uso em Outras Tabelas

Esta tabela é referenciada por:
- `RaceDataTable` - AbilityScoreImprovements
- `ClassDataTable` - SavingThrowHandles
- `SkillDataTable` - AbilityID
- Qualquer tabela que use ability scores

## 📚 Referências

- **Struct C++**: `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h`
- **D&D 5e Rules**: Player's Handbook, Chapter 1 - Ability Scores
- **Formato CSV Geral**: `Content/Data/CSV/SCHEMA_CSV_FORMAT.md`

---

**Última Atualização:** Baseado em validação manual e struct C++ atual
**Status:** ✅ Validado e funcionando no Unreal Engine 5.7
