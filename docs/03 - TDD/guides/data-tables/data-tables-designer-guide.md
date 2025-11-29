---
title: "Data Tables - Guia para Designers"
category: technical
subcategory: guides
tags: [data-tables, designer, guide, json]
last_updated: 2024-12-27
difficulty: beginner
related: [data-tables.md, data-tables-setup.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Data Tables - Guia para Designers

# Guia para Designers - Data Tables D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este guia é destinado a **designers e game designers** que precisam criar ou editar dados de D&D 5e no projeto. Você não precisa saber programação, apenas entender a estrutura JSON e seguir os exemplos.
>

> **Objetivo:** Permitir que designers modifiquem regras, adicionem novas raças, classes, itens, etc. sem precisar alterar código C.
>
</details>
---

## 🎯 O Que São Data Tables?

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Conceito</b></summary>

> **Data Tables** são tabelas de dados que armazenam informações do jogo (raças, classes, itens, magias, etc.) em formato JSON.
>

> **Por que usar Data Tables?**
>
> - ✅ Permite modificar regras sem recompilar código
> - ✅ Facilita balanceamento e iteração rápida
> - ✅ Designers podem trabalhar independentemente de programadores
> - ✅ Dados podem ser versionados e compartilhados facilmente
>
> **Onde ficam os arquivos?**
>
> - Arquivos JSON: `Content/Data/JSON/`
> - Schemas de validação: `Content/Data/JSON/Schemas/`
> - Importados no Unreal Editor como Data Tables
>
</details>
---

## 📝 Formato JSON Básico

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔤 Estrutura Básica</b></summary>

> **Formato geral:**
>

> ```json
> [
> {
> "Name": "Nome da Entrada",
> "ID": "ID_Unico",
> "Campo1": "Valor1",
> "Campo2": 123,
> "Campo3": ["Item1", "Item2"]
> },
> {
> "Name": "Outra Entrada",
> ...
> }
> ]
> ```
>
> **Regras importantes:**
>
> 1. **Sempre comece com `[` e termine com `]`** (array de objetos)
> 2. **Cada entrada é um objeto dentro de `{}`**
> 3. **Use vírgulas entre campos**, mas **não após o último campo**
> 4. **Strings sempre entre aspas duplas `"`**
> 5. **Números sem aspas**
> 6. **Arrays entre `[]`**
>
> **Exemplo prático:**
>
> ```json
> [
> {
> "Name": "Human",
> "ID": "RACE_Human",
> "Description": "Humans are adaptable."
> },
> {
> "Name": "Elf",
> "ID": "RACE_Elf",
> "Description": "Elves are graceful."
> }
> ]
> ```
>
</details>
---

## 🛠️ Ferramentas Recomendadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Editores e Validadores</b></summary>

> ### Editores de JSON
>

> - **VS Code** (recomendado) - Com extensão JSON
> - **Notepad** - Com plugin JSON
> - **Qualquer editor de texto** - Mas cuidado com formatação
>
</details>
    ### Validadores Online

    - **JSONLint** (https://jsonlint.com/) - Valida sintaxe JSON
    - **JSON Schema Validator** - Valida contra schema (quando disponível)

    ### Dicas

    - ✅ Use um editor com syntax highlighting para JSON
    - ✅ Valide sempre antes de importar no Unreal
    - ✅ Use formatação consistente (indentação de 2 espaços)
    - ❌ Não use tabs, use espaços
    - ❌ Não adicione vírgulas extras no final

---

## 📚 Guia Rápido por Data Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Referência Rápida</b></summary>

> ### Data Tables Principais (Criação de Personagem)
>

> 1. **[RaceDataTable](#racedatatable)** - Raças e sub-raças
> 2. **[ClassDataTable](#classdatatable)** - Classes e progressão
> 3. **[BackgroundDataTable](#backgrounddatatable)** - Backgrounds
> 4. **[FeatDataTable](#featdatatable)** - Feats
>
</details>
    ### Data Tables de Referência (Master Data)

    5. **[AbilityScoreDataTable](#abilityscoredatatable)** - Atributos (STR, DEX, etc.)
    6. **[SkillDataTable](#skilldatatable)** - Skills (Acrobatics, Athletics, etc.)
    7. **[LanguageDataTable](#languagedatatable)** - Idiomas
    8. **[ProficiencyDataTable](#proficiencydatatable)** - Proficiências gerais
    9. **[TraitDataTable](#traitdatatable)** - Traits especiais

    ### Data Tables de Magia

    10. **[SpellDataTable](#spelldatatable)** - Magias
    11. **[SpellSchoolDataTable](#spellschooldatatable)** - Escolas de magia

    ### Data Tables de Combate

    12. **[DamageTypeDataTable](#damagetypedatatable)** - Tipos de dano
    13. **[ConditionDataTable](#conditiondatatable)** - Condições

    ### Data Tables de Itens

    14. **[ItemDataTable](#itemdatatable)** - Itens (armas, armaduras, etc.)

    ### Data Tables de Features

    15. **[FeatureDataTable](#featuredatatable)** - Features de classe

---

## 👥 RaceDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏃 Criar/Editar Raças</b></summary>

> **Arquivo:** `Content/Data/JSON/RaceDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da raça (ex: "Human", "Elf")
> - `ID` - ID único (ex: "RACE_Human", "RACE_Elf")
> - `Description` - Descrição textual
> - `AbilityScoreImprovements` - Array de bônus de atributos
> - `Size` - Tamanho ("Small", "Medium", "Large")
> - `BaseSpeed` - Velocidade em pés (geralmente 30)
>
> **Exemplo completo:**
>
> ```json
> {
> "Name": "Dwarf",
> "ID": "RACE_Dwarf",
> "Description": "Bold and hardy dwarves are known as skilled warriors.",
> "AbilityScoreImprovements": [
> {
> "AbilityID": "ABL_Constitution",
> "Bonus": 2
> }
> ],
> "Size": "Medium",
> "BaseSpeed": 25,
> "TraitHandles": [],
> "SubraceHandles": [],
> "LanguageHandles": []
> }
> ```
>
> **💡 Dica:** Use `AbilityID` ao invés de `AbilityName`. Os IDs estão em `AbilityScoreDataTable`.
>
</details>
---

## ⚔️ ClassDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎭 Criar/Editar Classes</b></summary>

> **Arquivo:** `Content/Data/JSON/ClassDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da classe (ex: "Fighter", "Wizard")
> - `ID` - ID único (ex: "CLASS_Fighter", "CLASS_Wizard")
> - `Description` - Descrição textual
> - `HitDie` - Dado de vida (6, 8, 10, 12)
> - `Proficiencies` - Array de proficiências
> - `Progression` - Array de progressão por nível
>
> **Exemplo simplificado:**
>
> ```json
> {
> "Name": "Fighter",
> "ID": "CLASS_Fighter",
> "Description": "A master of martial combat.",
> "HitDie": 10,
> "Proficiencies": [
> {
> "ProficiencyType": "Armor",
> "ProficiencyName": "All Armor"
> }
> ],
> "Progression": [
> {
> "Level": 1,
> "Features": ["Fighting Style", "Second Wind"]
> }
> ]
> }
> ```
>
> **💡 Dica:** A progressão é complexa. Consulte a documentação completa em [data-tables.md](data-tables.md#classdatatable).
>
</details>
---

## 📚 BackgroundDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Criar/Editar Backgrounds</b></summary>

> **Arquivo:** `Content/Data/JSON/BackgroundDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do background (ex: "Acolyte", "Criminal")
> - `ID` - ID único (ex: "BG_Acolyte", "BG_Criminal")
> - `Description` - Descrição textual
> - `SkillProficiencies` - Array de skills proficientes
> - `LanguageProficiencies` - Array de idiomas
> - `Equipment` - Array de equipamentos iniciais
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Acolyte",
> "ID": "BG_Acolyte",
> "Description": "You have spent your life in the service of a temple.",
> "SkillProficiencies": ["Insight", "Religion"],
> "LanguageProficiencies": ["Common", "One additional language"],
> "Equipment": ["Holy Symbol", "Prayer Book", "15 Gold"]
> }
> ```
>
</details>
---

## ⭐ FeatDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💫 Criar/Editar Feats</b></summary>

> **Arquivo:** `Content/Data/JSON/FeatDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do feat (ex: "Alert", "Great Weapon Master")
> - `ID` - ID único (ex: "FEAT_Alert", "FEAT_GreatWeaponMaster")
> - `Description` - Descrição textual
> - `Prerequisites` - Array de pré-requisitos (pode ser vazio)
> - `Benefits` - Map de benefícios estruturados
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Alert",
> "ID": "FEAT_Alert",
> "Description": "Always on the lookout for danger.",
> "Prerequisites": [],
> "Benefits": {
> "InitiativeBonus": "5",
> "CannotBeSurprised": "true"
> }
> }
> ```
>
</details>
---

## 💪 AbilityScoreDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Criar/Editar Atributos</b></summary>

> **Arquivo:** `Content/Data/JSON/AbilityScoreDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do atributo (ex: "Strength", "Dexterity")
> - `ID` - ID único (ex: "ABL_Strength", "ABL_Dexterity")
> - `Abbreviation` - Abreviação (ex: "STR", "DEX")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Strength",
> "ID": "ABL_Strength",
> "Abbreviation": "STR",
> "Description": "Strength measures bodily power."
> }
> ```
>
> **⚠️ Importante:** Não modifique os IDs dos atributos padrão (STR, DEX, CON, INT, WIS, CHA) - eles são usados como referência em outras tabelas.
>
</details>
---

## 🏋️ SkillDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Criar/Editar Skills</b></summary>

> **Arquivo:** `Content/Data/JSON/SkillDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da skill (ex: "Acrobatics", "Athletics")
> - `ID` - ID único (ex: "PSK_Acrobatics", "PSK_Athletics")
> - `AbilityID` - ID do atributo associado (ex: "ABL_Dexterity", "ABL_Strength")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Acrobatics",
> "ID": "PSK_Acrobatics",
> "AbilityID": "ABL_Dexterity",
> "Description": "Your Dexterity (Acrobatics) check covers your attempt to stay on your feet."
> }
> ```
>
> **💡 Dica:** O `AbilityID` deve referenciar um ID válido de `AbilityScoreDataTable`.
>
</details>
---

## 🗣️ LanguageDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌍 Criar/Editar Idiomas</b></summary>

> **Arquivo:** `Content/Data/JSON/LanguageDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do idioma (ex: "Common", "Elvish")
> - `ID` - ID único (ex: "PL_Common", "PL_Elvish")
> - `Description` - Descrição textual
> - `Script` - Script usado (ex: "Common", "Elvish")
> - `Type` - Tipo ("Standard", "Exotic")
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Common",
> "ID": "PL_Common",
> "Description": "The most widely spoken language in the world.",
> "Script": "Common",
> "Type": "Standard"
> }
> ```
>
</details>
---

## 🎯 ProficiencyDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Criar/Editar Proficiências</b></summary>

> **Arquivo:** `Content/Data/JSON/ProficiencyDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da proficiência (ex: "Simple Weapons", "Light Armor")
> - `ID` - ID único (ex: "PW_Simple_Weapons", "PA_Light_Armor")
> - `Type` - Tipo ("Weapon", "Armor", "Shield", "Tool", "Skill", "SavingThrow", "Language")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Simple Weapons",
> "ID": "PW_Simple_Weapons",
> "Type": "Weapon",
> "Description": "Proficiency with all simple weapons."
> }
> ```
>
</details>
---

## 🏷️ TraitDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Criar/Editar Traits</b></summary>

> **Arquivo:** `Content/Data/JSON/TraitDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do trait (ex: "Darkvision", "Fey Ancestry")
> - `ID` - ID único (ex: "TR_Darkvision", "TR_FeyAncestry")
> - `Description` - Descrição textual
> - `TraitData` - Map de dados estruturados (opcional)
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Darkvision",
> "ID": "TR_Darkvision",
> "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
> "TraitData": {
> "Range": "60"
> }
> }
> ```
>
</details>
---

## 🔮 SpellDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Criar/Editar Magias</b></summary>

> **Arquivo:** `Content/Data/JSON/SpellDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da magia (ex: "Fireball", "Mage Hand")
> - `ID` - ID único (ex: "SPL_Fireball", "SPL_MageHand")
> - `SpellLevel` - Nível (0 = Cantrip, 1-9 = Spell Level)
> - `Description` - Descrição textual
> - `SpellData` - Map de dados estruturados (Range, Components, etc.)
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Fireball",
> "ID": "SPL_Fireball",
> "SpellLevel": 3,
> "Description": "A bright streak flashes from your pointing finger.",
> "SpellData": {
> "Range": "150 feet",
> "Components": "V, S, M",
> "Duration": "Instantaneous"
> }
> }
> ```
>
</details>
---

## 🎓 SpellSchoolDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Criar/Editar Escolas de Magia</b></summary>

> **Arquivo:** `Content/Data/JSON/SpellSchoolDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da escola (ex: "Abjuration", "Evocation")
> - `ID` - ID único (ex: "SCH_Abjuration", "SCH_Evocation")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Evocation",
> "ID": "SCH_Evocation",
> "Description": "Evocation spells manipulate magical energy to produce a desired effect."
> }
> ```
>
</details>
---

## 🔥 DamageTypeDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Criar/Editar Tipos de Dano</b></summary>

> **Arquivo:** `Content/Data/JSON/DamageTypeDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do tipo (ex: "Fire", "Cold", "Lightning")
> - `ID` - ID único (ex: "DAM_Fire", "DAM_Cold")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Fire",
> "ID": "DAM_Fire",
> "Description": "Fire damage is dealt by flames, heat, and magical fire effects."
> }
> ```
>
</details>
---

## ⚠️ ConditionDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Criar/Editar Condições</b></summary>

> **Arquivo:** `Content/Data/JSON/ConditionDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da condição (ex: "Blinded", "Poisoned")
> - `ID` - ID único (ex: "CON_Blinded", "CON_Poisoned")
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Blinded",
> "ID": "CON_Blinded",
> "Description": "A blinded creature can't see and automatically fails any ability check that requires sight."
> }
> ```
>
</details>
---

## 🎒 ItemDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛍️ Criar/Editar Itens</b></summary>

> **Arquivo:** `Content/Data/JSON/ItemDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome do item (ex: "Longsword", "Chain Mail")
> - `ID` - ID único (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail")
> - `ItemType` - Tipo ("Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold")
> - `Weight` - Peso em libras (float)
> - `Value` - Valor em ouro (int32)
> - `Description` - Descrição textual
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Longsword",
> "ID": "ITM_WPN_Longsword",
> "ItemType": "Weapon",
> "Weight": 3.0,
> "Value": 15,
> "Description": "A versatile melee weapon."
> }
> ```
>
> **💡 Dica:** Use o padrão de nomenclatura de IDs:
> - `ITM_WPN_*` = Weapon
> - `ITM_ARM_*` = Armor
> - `ITM_TOL_*` = Tool
> - `ITM_GOLD_*` = Gold
>
</details>
---

## ⚙️ FeatureDataTable

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎁 Criar/Editar Features</b></summary>

> **Arquivo:** `Content/Data/JSON/FeatureDataTable.json`
>

> **Campos obrigatórios:**
>
> - `Name` - Nome da feature (ex: "Second Wind", "Fighting Style")
> - `ID` - ID único (ex: "FC_SecondWind", "FC_FightingStyle")
> - `Description` - Descrição textual
> - `LevelUnlocked` - Nível em que é desbloqueada
> - `FeatureType` - Tipo ("Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection")
>
> **Exemplo:**
>
> ```json
> {
> "Name": "Second Wind",
> "ID": "FC_SecondWind",
> "Description": "You have a limited well of stamina.",
> "LevelUnlocked": 1,
> "FeatureType": "Automatic",
> "FeatureData": {
> "UsesPerRest": "1"
> }
> }
> ```
>
</details>
---

## ✅ Checklist de Validação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Antes de Importar</b></summary>

> Antes de importar um JSON no Unreal Editor, verifique:
>

> - [ ] **Sintaxe JSON válida** (use JSONLint)
> - [ ] **Todos os campos obrigatórios presentes**
> - [ ] **IDs únicos** (não duplicados)
> - [ ] **Referências válidas** (IDs referenciados existem)
> - [ ] **Tipos corretos** (strings, números, arrays)
> - [ ] **Formatação consistente** (2 espaços de indentação)
>
> **Validação automática:**
>
> - O sistema valida automaticamente contra schemas JSON
> - Erros aparecem no Output Log do Unreal Editor
> - Corrija erros antes de continuar
>
</details>
---

## 🐛 Problemas Comuns

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❓ Troubleshooting</b></summary>

> ### Erro: "Invalid JSON"
>

> **Solução:**
> - Verifique vírgulas extras ou faltando
> - Verifique aspas fechadas corretamente
> - Use um validador JSON online
>
</details>
    ### Erro: "Missing required field"

    **Solução:**
    - Verifique se todos os campos obrigatórios estão presentes
    - Consulte a documentação da Data Table específica

    ### Erro: "Invalid reference"

    **Solução:**
    - Verifique se IDs referenciados existem
    - Verifique se o nome do Data Table está correto
    - Verifique se a referência está no formato correto

    ### Dados não aparecem no editor

    **Solução:**
    - Verifique se o Data Table foi atribuído ao CharacterSheetDataAsset
    - Verifique se o JSON foi importado corretamente
    - Verifique os logs do editor para erros

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Documentação Completa de Data Tables](data-tables.md)** - Referência completa de todas as Data Tables
> - **[Guia de Setup](data-tables-setup.md)** - Como criar e configurar Data Tables no editor
> - **[JSON Schema Validation](../data-architecture/json-schema.md)** - Validação automática de schemas
> - **[Regras D&D 5e](../../../03 - TDD/dnd-rules/)** - Regras oficiais para referência
>

</details>

**Última atualização:** 2024-12-27
