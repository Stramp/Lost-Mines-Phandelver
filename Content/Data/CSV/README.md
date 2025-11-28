# 📊 Tabelas CSV - Formato Final Validado

Esta pasta contém todos os arquivos CSV no formato correto para importação no Unreal Engine 5.7.

## ✅ Status

**Formato Validado:** ✅ Testado e funcionando no Unreal Engine 5.7

Todos os CSVs foram gerados com o formato correto baseado na exportação real do Unreal Engine.

## 📁 Arquivos

- `AbilityScoreDataTable.csv` - Atributos (Strength, Dexterity, etc.)
- `BackgroundDataTable.csv` - Backgrounds (Acolyte, Criminal, etc.)
- `ClassDataTable.csv` - Classes (Fighter, Wizard, etc.)
- `ConditionDataTable.csv` - Condições (Blinded, Poisoned, etc.)
- `DamageTypeDataTable.csv` - Tipos de dano (Fire, Cold, etc.)
- `FeatDataTable.csv` - Feats (Alert, Athlete, etc.)
- `FeatureDataTable.csv` - Features de classe (Second Wind, Fighting Style, etc.)
- `ItemDataTable.csv` - Itens (Armas, Armaduras, etc.)
- `LanguageDataTable.csv` - Idiomas (Common, Elvish, etc.)
- `ProficiencyDataTable.csv` - Proficiências (Weapons, Armor, Skills, etc.)
- `RaceDataTable.csv` - Raças (Dwarf, Elf, Human, etc.)
- `SkillDataTable.csv` - Skills (Acrobatics, Athletics, etc.)
- `SpellDataTable.csv` - Magias (Fireball, Mage Hand, etc.)
- `SpellSchoolDataTable.csv` - Escolas de magia (Evocation, Abjuration, etc.)
- `TraitDataTable.csv` - Traits (Darkvision, Fey Ancestry, etc.)

## 📋 Documentação

- **`SCHEMA_CSV_FORMAT.md`** - Documentação completa do formato CSV
  - Formato TypeTags
  - Formato FDataTableRowHandle
  - Formato Arrays de Structs
  - Regras gerais e checklist

## 🔄 Como Usar

1. **Importar no Unreal Engine:**
   - No Content Browser, clique em "Import"
   - Selecione o arquivo CSV desejado
   - Escolha a Row Struct correspondente
   - Clique em "Import"

2. **Reimportar (se já existe):**
   - Clique com botão direito na Data Table
   - Selecione "Reimport"
   - Escolha o arquivo CSV atualizado

## ⚠️ Importante

- **NÃO edite manualmente** os CSVs sem conhecer o formato exato
- **SEMPRE use o script** `scripts/convert_json_to_csv.py` para gerar CSVs
- **Mantenha o schema atualizado** se houver mudanças nas structs

## 🔧 Geração de CSVs

Para regenerar todos os CSVs:

```bash
python scripts/convert_json_to_csv.py
```

Os CSVs serão gerados em `Content/Data/CSV/` e depois copiados para esta pasta.

---

**Última Atualização:** Formato validado e testado no Unreal Engine 5.7
