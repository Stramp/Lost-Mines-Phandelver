---
title: "Data Tables"
category: technical
subcategory: guides
tags: [data-tables, json, data-driven, normalization]
last_updated: 2024-12-27
difficulty: intermediate
related: [data-tables-setup.md, ../data-architecture/index.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Data Tables

# Documentação de Data Tables

Guia completo sobre a estrutura, criação e uso dos Data Tables no sistema de fichas D&D 5e.

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Os Data Tables armazenam dados estruturados de D&D 5e (raças, classes, backgrounds, feats) em formato JSON, permitindo que designers modifiquem regras sem alterar código.
> >
> **Filosofia de Estrutura:**
> >
> - **Estrutura "Flat" (Plana)**: JSONs relacionais e planos, não profundamente aninhados (o importador do Unreal quebra com estruturas muito aninhadas)
> - **Padrão "ID + Tags + Payload"**: Cada entrada tem um ID único, tags para categorização, e payload com dados específicos
> - **Separação Static/Dynamic**: Data Tables contêm apenas definições estáticas (o que o item "é"), não estado dinâmico (o que o item "tem" agora)
> - **Composição sobre Herança**: Use referências por ID ao invés de estruturas aninhadas complexas
> >
> **📖 Para mais detalhes sobre arquitetura de dados, veja:**
> >
> - [Estrutura de Dados Ideal](../data-architecture/ideal-data-structure-report.md)
> - [Arquiteturas de Alta Performance](../data-architecture/high-performance-architectures-report.md)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Estrutura de Relacionamento</b></summary>

> ```mermaid
> erDiagram
>     RaceDataTable ||--o{ Subrace : contains
>     ClassDataTable ||--o{ Subclass : contains
>     CharacterSheetDataAsset }o--|| RaceDataTable : uses
>     CharacterSheetDataAsset }o--|| ClassDataTable : uses
>     CharacterSheetDataAsset }o--|| BackgroundDataTable : uses
>     CharacterSheetDataAsset }o--|| FeatDataTable : uses
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 RaceDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/RaceDataTable.h`
>
> **Struct:** `FRaceDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `RaceName` | `FName` | Nome da raça (ex: "Human", "Elf", "Dwarf") |
> > | `Description` | `FText` | Descrição textual da raça (localizável) |
> > | `AbilityScoreImprovements` | `TArray<FAbilityScoreImprovement>` | Bônus de atributos da raça |
> > | `Size` | `FName` | Tamanho da raça (ex: "Small", "Medium") |
> > | `BaseSpeed` | `int32` | Velocidade base em pés |
> > | `Traits` | `TArray<FRaceTrait>` | Traits da raça (Darkvision, etc.) |
> > | `SubraceNames` | `TArray<FName>` | Lista de sub-raças disponíveis |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FAbilityScoreImprovement</summary>
>
> > ```cpp
> > USTRUCT(BlueprintType)
> > struct FAbilityScoreImprovement
> > {
> >     FName AbilityName;  // Nome do atributo (ex: "Strength", "Constitution")
> >     int32 Bonus;        // Valor do bônus (geralmente +1 ou +2)
> > };
> > ```
> >
> > **Nota Especial:** Para Variant Human, use `AbilityName = "Custom"` com `Bonus = 1`. O sistema aplicará +1 para cada atributo escolhido em `CustomAbilityScoreChoices`.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FRaceTrait</summary>
>
> > ```cpp
> > USTRUCT(BlueprintType)
> > struct FRaceTrait
> > {
> >     FName TraitName;                    // Nome do trait (ex: "Darkvision")
> >     FText Description;                  // Descrição textual
> >     TMap<FName, FString> TraitData;     // Dados estruturados opcionais
> > };
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Human</summary>
>
> > ```json
> > {
> >   "Name": "Human",
> >   "RaceName": "Human",
> >   "Description": "Humans are the most adaptable and ambitious people among the common races.",
> >   "AbilityScoreImprovements": [
> >     {
> >       "AbilityName": "Strength",
> >       "Bonus": 1
> >     },
> >     {
> >       "AbilityName": "Dexterity",
> >       "Bonus": 1
> >     },
> >     {
> >       "AbilityName": "Constitution",
> >       "Bonus": 1
> >     },
> >     {
> >       "AbilityName": "Intelligence",
> >       "Bonus": 1
> >     },
> >     {
> >       "AbilityName": "Wisdom",
> >       "Bonus": 1
> >     },
> >     {
> >       "AbilityName": "Charisma",
> >       "Bonus": 1
> >     }
> >   ],
> >   "Size": "Medium",
> >   "BaseSpeed": 30,
> >   "Traits": [],
> >   "SubraceNames": ["Standard Human", "Variant Human"]
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Variant Human</summary>
>
> > ```json
> > {
> >   "Name": "Variant Human",
> >   "RaceName": "Variant Human",
> >   "Description": "Some humans are more versatile than others.",
> >   "AbilityScoreImprovements": [
> >     {
> >       "AbilityName": "Custom",
> >       "Bonus": 1
> >     }
> >   ],
> >   "Size": "Medium",
> >   "BaseSpeed": 30,
> >   "Traits": [
> >     {
> >       "TraitName": "FeatChoice",
> >       "Description": "You gain one feat of your choice.",
> >       "TraitData": {}
> >     },
> >     {
> >       "TraitName": "SkillChoice",
> >       "Description": "You gain proficiency in one skill of your choice.",
> >       "TraitData": {}
> >     }
> >   ],
> >   "SubraceNames": []
> > }
> > ```
> >
> > **Importante:**
> > - `AbilityName = "Custom"` indica que o jogador escolhe 2 atributos para receber +1 cada
> > - Traits `FeatChoice` e `SkillChoice` indicam escolhas do jogador
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ ClassDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/ClassDataTable.h`
>
> **Struct:** `FClassDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `ClassName` | `FName` | Nome da classe (ex: "Fighter", "Wizard", "Rogue") |
> > | `Description` | `FText` | Descrição textual da classe |
> > | `HitDie` | `int32` | Tipo de dado de vida (ex: 8 para d8, 10 para d10) |
> > | `Proficiencies` | `TArray<FClassProficiency>` | Proficiências da classe |
> > | `Features` | `TArray<FClassFeature>` | Features da classe por nível |
> > | `SubclassNames` | `TArray<FName>` | Lista de subclasses disponíveis |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FClassProficiency</summary>
>
> > ```cpp
> > USTRUCT(BlueprintType)
> > struct FClassProficiency
> > {
> >     FName ProficiencyType;  // Tipo: "Weapon", "Armor", "SavingThrow", "Skill"
> >     FName ProficiencyName; // Nome específico (ex: "Longsword", "Light Armor", "Strength", "Athletics")
> > };
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FClassFeature</summary>
>
> > ```cpp
> > USTRUCT(BlueprintType)
> > struct FClassFeature
> > {
> >     FName FeatureName;                    // Nome da feature (ex: "Second Wind", "Action Surge")
> >     FText Description;                    // Descrição textual
> >     int32 LevelUnlocked;                  // Nível em que é desbloqueada
> >     FName FeatureType;                    // Tipo: "Automatic", "SubclassSelection", "ASI", "Choice"
> >     TMap<FName, FString> FeatureData;     // Dados estruturados opcionais
> > };
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Fighter</summary>
>
> > ```json
> > {
> >   "Name": "Fighter",
> >   "ClassName": "Fighter",
> >   "Description": "A master of martial combat, skilled with a variety of weapons and armor.",
> >   "HitDie": 10,
> >   "Proficiencies": [
> >     {
> >       "ProficiencyType": "Armor",
> >       "ProficiencyName": "All Armor"
> >     },
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Simple Weapons"
> >     },
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Martial Weapons"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Strength"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Constitution"
> >     }
> >   ],
> >   "Features": [
> >     {
> >       "FeatureName": "Second Wind",
> >       "Description": "You have a limited well of stamina that you can draw on to protect yourself from harm.",
> >       "LevelUnlocked": 1,
> >       "FeatureType": "Automatic",
> >       "FeatureData": {
> >         "UsesPerRest": "1",
> >         "Type": "BonusAction"
> >       }
> >     },
> >     {
> >       "FeatureName": "Action Surge",
> >       "Description": "You can push yourself beyond your normal limits for a moment.",
> >       "LevelUnlocked": 2,
> >       "FeatureType": "Automatic",
> >       "FeatureData": {
> >         "UsesPerRest": "1"
> >       }
> >     },
> >     {
> >       "FeatureName": "Martial Archetype",
> >       "Description": "You choose an archetype that you strive to emulate.",
> >       "LevelUnlocked": 3,
> >       "FeatureType": "SubclassSelection",
> >       "FeatureData": {}
> >     }
> >   ],
> >   "SubclassNames": ["Champion", "Battle Master", "Eldritch Knight"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 BackgroundDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/BackgroundDataTable.h`
>
> **Struct:** `FBackgroundDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `BackgroundName` | `FName` | Nome do background (ex: "Acolyte", "Criminal", "Noble") |
> > | `Description` | `FText` | Descrição textual do background |
> > | `SkillProficiencies` | `TArray<FName>` | Skills em que o background fornece proficiência |
> > | `LanguageProficiencies` | `TArray<FName>` | Idiomas em que o background fornece proficiência |
> > | `Equipment` | `TArray<FName>` | Equipamento inicial (FNames de itens) |
> > | `FeatureName` | `FName` | Nome da feature especial do background |
> > | `FeatureDescription` | `FText` | Descrição da feature |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Acolyte</summary>
>
> > ```json
> > {
> >   "Name": "Acolyte",
> >   "BackgroundName": "Acolyte",
> >   "Description": "You have spent your life in the service of a temple.",
> >   "SkillProficiencies": ["Insight", "Religion"],
> >   "LanguageProficiencies": ["Common", "One additional language"],
> >   "Equipment": ["Holy Symbol", "Prayer Book", "Common Clothes", "15 Gold"],
> >   "FeatureName": "Shelter of the Faithful",
> >   "FeatureDescription": "You and your adventuring companions can receive free healing and care at a temple."
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⭐ FeatDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/FeatDataTable.h`
>
> **Struct:** `FFeatDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `FeatName` | `FName` | Nome do feat (ex: "Alert", "Magic Initiate", "War Caster") |
> > | `Description` | `FText` | Descrição textual do feat |
> > | `Prerequisites` | `TArray<FName>` | Pré-requisitos para adquirir o feat |
> > | `Benefits` | `TMap<FName, FString>` | Benefícios estruturados (dados programáticos) |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Alert</summary>
>
> > ```json
> > {
> >   "Name": "Alert",
> >   "FeatName": "Alert",
> >   "Description": "Always on the lookout for danger, you gain the following benefits.",
> >   "Prerequisites": [],
> >   "Benefits": {
> >     "InitiativeBonus": "5",
> >     "CannotBeSurprised": "true"
> >   }
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - War Caster (com pré-requisitos)</summary>
>
> > ```json
> > {
> >   "Name": "War Caster",
> >   "FeatName": "War Caster",
> >   "Description": "You have practiced casting spells in the midst of combat.",
> >   "Prerequisites": ["Ability to cast at least one spell"],
> >   "Benefits": {
> >     "AdvantageOnConcentration": "true",
> >     "CanCastSpellAsOpportunityAttack": "true"
> >   }
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ FeatureDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/FeatureDataTable.h`
>
> **Struct:** `FFeatureDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da feature (ex: "Second Wind", "Fighting Style") |
> > | `ID` | `FName` | ID único da feature (ex: "FC_SecondWind", "FC_FightingStyle") |
> > | `FeatureID` | `FName` | Alias de ID (mantido para compatibilidade) |
> > | `Description` | `FText` | Descrição textual da feature (localizável) |
> > | `LevelUnlocked` | `int32` | Nível em que a feature é desbloqueada |
> > | `FeatureType` | `FName` | Tipo: "Automatic", "Choice", "SubclassSelection", "ASI", "FeatSelection" |
> > | `FeatureData` | `TMap<FName, FString>` | Dados estruturados opcionais (ex: UsesPerRest, Type) |
> > | `AvailableChoices` | `TArray<FFeatureChoice>` | Escolhas disponíveis para features do tipo "Choice" |
> > | `bAllowMultipleChoices` | `bool` | Permite múltiplas escolhas (padrão: false) |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Tipos de Features</summary>
>
> > - **"Automatic"**: Feature aplicada automaticamente (ex: Second Wind, Action Surge)
> > - **"Choice"**: Jogador escolhe entre opções (ex: Fighting Style)
> > - **"SubclassSelection"**: Jogador escolhe subclasse (ex: Martial Archetype)
> > - **"ASI"**: Ability Score Improvement
> > - **"FeatSelection"**: Jogador pode escolher um Feat ao invés de ASI
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Second Wind</summary>
>
> > ```json
> > {
> >   "Name": "Second Wind",
> >   "ID": "FC_SecondWind",
> >   "FeatureID": "FC_SecondWind",
> >   "Description": "You have a limited well of stamina that you can draw on to protect yourself from harm.",
> >   "LevelUnlocked": 1,
> >   "FeatureType": "Automatic",
> >   "FeatureData": {
> >     "UsesPerRest": "1",
> >     "Type": "BonusAction"
> >   },
> >   "AvailableChoices": [],
> >   "bAllowMultipleChoices": false
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Fighting Style (Choice)</summary>
>
> > ```json
> > {
> >   "Name": "Fighting Style",
> >   "ID": "FC_FightingStyle",
> >   "FeatureID": "FC_FightingStyle",
> >   "Description": "You adopt a particular style of fighting as your specialty.",
> >   "LevelUnlocked": 1,
> >   "FeatureType": "Choice",
> >   "FeatureData": {},
> >   "AvailableChoices": [
> >     { "ID": "FC_Archery", "Name": "Archery" },
> >     { "ID": "FC_Defense", "Name": "Defense" },
> >     { "ID": "FC_Dueling", "Name": "Dueling" }
> >   ],
> >   "bAllowMultipleChoices": false
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 ProficiencyDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/ProficiencyDataTable.h`
>
> **Struct:** `FProficiencyDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da proficiência (ex: "Simple Weapons", "Thieves' Tools") |
> > | `ID` | `FName` | ID único (ex: "PW_Simple_Weapons", "PT_Thieves_Tools") |
> > | `Type` | `FName` | Tipo: "Weapon", "Armor", "Shield", "Tool", "Skill", "SavingThrow", "Language" |
> > | `Description` | `FText` | Descrição textual (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
> > | `ProficiencyData` | `TMap<FName, FString>` | Dados estruturados opcionais |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Tipos de Proficiências</summary>
>
> > - **"Weapon"**: Proficiências com armas (ex: Simple Weapons, Martial Weapons)
> > - **"Armor"**: Proficiências com armaduras (ex: Light Armor, Medium Armor, Heavy Armor)
> > - **"Shield"**: Proficiências com escudos
> > - **"Tool"**: Proficiências com ferramentas (ex: Thieves' Tools, Herbalism Kit)
> > - **"Skill"**: Proficiências com skills (ex: Acrobatics, Athletics)
> > - **"SavingThrow"**: Proficiências com saving throws (ex: Strength, Dexterity)
> > - **"Language"**: Proficiências com idiomas (ex: Common, Elvish)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Simple Weapons</summary>
>
> > ```json
> > {
> >   "Name": "Simple Weapons",
> >   "ID": "PW_Simple_Weapons",
> >   "Type": "Weapon",
> >   "Description": "Proficiency with all simple weapons.",
> >   "TypeTags": ["Proficiency.Weapon.Simple"],
> >   "ProficiencyData": {}
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏋️ SkillDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/SkillDataTable.h`
>
> **Struct:** `FSkillDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da skill (ex: "Acrobatics", "Athletics", "Stealth") |
> > | `ID` | `FName` | ID único (ex: "PSK_Acrobatics", "PSK_Athletics") |
> > | `AbilityID` | `FName` | ID do Ability Score associado (ex: "ABL_Dexterity", "ABL_Strength") |
> > | `Description` | `FText` | Descrição da skill (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Acrobatics</summary>
>
> > ```json
> > {
> >   "Name": "Acrobatics",
> >   "ID": "PSK_Acrobatics",
> >   "AbilityID": "ABL_Dexterity",
> >   "Description": "Your Dexterity (Acrobatics) check covers your attempt to stay on your feet in a tricky situation.",
> >   "TypeTags": ["Skill.Physical", "Skill.Dexterity"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗣️ LanguageDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/LanguageDataTable.h`
>
> **Struct:** `FLanguageDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome do idioma (ex: "Common", "Elvish", "Dwarvish") |
> > | `ID` | `FName` | ID único (ex: "PL_Common", "PL_Elvish", "PL_Dwarvish") |
> > | `Description` | `FText` | Descrição do idioma (localizável) |
> > | `Script` | `FName` | Script usado pelo idioma (ex: "Common", "Elvish") |
> > | `Type` | `FName` | Tipo: "Standard", "Exotic" |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Common</summary>
>
> > ```json
> > {
> >   "Name": "Common",
> >   "ID": "PL_Common",
> >   "Description": "The most widely spoken language in the world.",
> >   "Script": "Common",
> >   "Type": "Standard",
> >   "TypeTags": ["Language.Standard"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 SpellDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/SpellDataTable.h`
>
> **Struct:** `FSpellDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da magia (ex: "Fireball", "Mage Hand", "Magic Missile") |
> > | `ID` | `FName` | ID único (ex: "SPL_Fireball", "SPL_MageHand") |
> > | `SpellLevel` | `int32` | Nível da magia (0 = Cantrip, 1-9 = Spell Level) |
> > | `SchoolReference` | `FDataTableRowHandle` | Referência à escola da magia |
> > | `DamageTypeReference` | `FDataTableRowHandle` | Referência ao tipo de dano (se aplicável) |
> > | `Description` | `FText` | Descrição da magia (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
> > | `SpellData` | `TMap<FName, FString>` | Dados estruturados (Range, Components, Duration, etc.) |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Fireball</summary>
>
> > ```json
> > {
> >   "Name": "Fireball",
> >   "ID": "SPL_Fireball",
> >   "SpellLevel": 3,
> >   "SchoolReference": {
> >     "DataTable": "DT_SpellSchools",
> >     "RowName": "Evocation"
> >   },
> >   "DamageTypeReference": {
> >     "DataTable": "DT_DamageTypes",
> >     "RowName": "Fire"
> >   },
> >   "Description": "A bright streak flashes from your pointing finger to a point you choose within range.",
> >   "TypeTags": ["Spell.Damage", "Spell.Area"],
> >   "SpellData": {
> >     "Range": "150 feet",
> >     "Components": "V, S, M",
> >     "Duration": "Instantaneous",
> >     "CastingTime": "1 action"
> >   }
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎓 SpellSchoolDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/SpellSchoolDataTable.h`
>
> **Struct:** `FSpellSchoolDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da escola (ex: "Abjuration", "Evocation", "Necromancy") |
> > | `ID` | `FName` | ID único (ex: "SCH_Abjuration", "SCH_Evocation") |
> > | `Description` | `FText` | Descrição da escola (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Evocation</summary>
>
> > ```json
> > {
> >   "Name": "Evocation",
> >   "ID": "SCH_Evocation",
> >   "Description": "Evocation spells manipulate magical energy to produce a desired effect.",
> >   "TypeTags": ["SpellSchool.Evocation"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔥 DamageTypeDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/DamageTypeDataTable.h`
>
> **Struct:** `FDamageTypeDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome do tipo de dano (ex: "Fire", "Cold", "Lightning") |
> > | `ID` | `FName` | ID único (ex: "DAM_Fire", "DAM_Cold", "DAM_Lightning") |
> > | `Description` | `FText` | Descrição do tipo de dano (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Fire</summary>
>
> > ```json
> > {
> >   "Name": "Fire",
> >   "ID": "DAM_Fire",
> >   "Description": "Fire damage is dealt by flames, heat, and magical fire effects.",
> >   "TypeTags": ["DamageType.Fire", "DamageType.Elemental"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚠️ ConditionDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/ConditionDataTable.h`
>
> **Struct:** `FConditionDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome da condição (ex: "Blinded", "Poisoned", "Charmed") |
> > | `ID` | `FName` | ID único (ex: "CON_Blinded", "CON_Poisoned", "CON_Charmed") |
> > | `Description` | `FText` | Descrição da condição (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Blinded</summary>
>
> > ```json
> > {
> >   "Name": "Blinded",
> >   "ID": "CON_Blinded",
> >   "Description": "A blinded creature can't see and automatically fails any ability check that requires sight.",
> >   "TypeTags": ["Condition.Blinded", "Condition.Debuff"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💪 AbilityScoreDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/AbilityScoreDataTable.h`
>
> **Struct:** `FAbilityScoreDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome do atributo (ex: "Strength", "Dexterity", "Constitution") |
> > | `ID` | `FName` | ID único (ex: "ABL_Strength", "ABL_Dexterity", "ABL_Constitution") |
> > | `Abbreviation` | `FName` | Abreviação (ex: "STR", "DEX", "CON") |
> > | `Description` | `FText` | Descrição do atributo (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Strength</summary>
>
> > ```json
> > {
> >   "Name": "Strength",
> >   "ID": "ABL_Strength",
> >   "Abbreviation": "STR",
> >   "Description": "Strength measures bodily power, athletic training, and the extent to which you can exert raw physical force.",
> >   "TypeTags": ["Ability.Physical", "Ability.Strength"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏷️ TraitDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/TraitDataTable.h`
>
> **Struct:** `FTraitDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome do trait (ex: "Darkvision", "Fey Ancestry", "Trance") |
> > | `ID` | `FName` | ID único (ex: "TR_Darkvision", "TR_FeyAncestry", "TR_Trance") |
> > | `Description` | `FText` | Descrição textual do trait (localizável) |
> > | `TraitData` | `TMap<FName, FString>` | Dados estruturados (ex: Range para Darkvision) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
> > | `SpellReference` | `FDataTableRowHandle` | Referência a uma magia (se aplicável) |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Darkvision</summary>
>
> > ```json
> > {
> >   "Name": "Darkvision",
> >   "ID": "TR_Darkvision",
> >   "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
> >   "TraitData": {
> >     "Range": "60"
> >   },
> >   "TypeTags": ["Trait.Vision.Darkvision", "Trait.Racial"],
> >   "SpellReference": {}
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎒 ItemDataTable</b></summary>

> **Caminho:** `Source/MyProject2/Data/Tables/ItemDataTable.h`
>
> **Struct:** `FItemDataRow`
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Campos</summary>
>
> > | Campo | Tipo | Descrição |
> > |-------|------|-----------|
> > | `Name` | `FName` | Nome do item (ex: "Longsword", "Chain Mail", "15 gp") |
> > | `ID` | `FName` | ID único (ex: "ITM_WPN_Longsword", "ITM_ARM_ChainMail", "ITM_GOLD_15gp") |
> > | `ItemType` | `FName` | Tipo: "Weapon", "Armor", "Tool", "Consumable", "Pack", "Other", "Gold" |
> > | `Weight` | `float` | Peso do item em libras (lbs) |
> > | `Value` | `int32` | Valor do item em ouro (gp) |
> > | `Description` | `FText` | Descrição do item (localizável) |
> > | `TypeTags` | `FGameplayTagContainer` | Tags para categorização |
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Padrão de Nomenclatura de IDs</summary>
>
> > - **ITM_WPN_*** = Item Weapon
> > - **ITM_ARM_*** = Item Armor
> > - **ITM_TOL_*** = Item Tool
> > - **ITM_PCK_*** = Item Pack
> > - **ITM_CNM_*** = Item Consumable
> > - **ITM_OTH_*** = Item Other
> > - **ITM_GOLD_*** = Item Gold (ouro)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Exemplo de JSON - Longsword</summary>
>
> > ```json
> > {
> >   "Name": "Longsword",
> >   "ID": "ITM_WPN_Longsword",
> >   "ItemType": "Weapon",
> >   "Weight": 3.0,
> >   "Value": 15,
> >   "Description": "A versatile melee weapon.",
> >   "TypeTags": ["Item.Weapon.Martial", "Item.Weapon.Melee"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Como Criar/Editar Data Tables no Editor</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1. Criar Data Table</summary>
>
> > 1. No Content Browser, navegue até a pasta desejada
> > 2. Clique com botão direito → **Miscellaneous** → **Data Table**
> > 3. Selecione o struct apropriado:
> >    - `Race Data Row` para raças
> >    - `Class Data Row` para classes
> >    - `Background Data Row` para backgrounds
> >    - `Feat Data Row` para feats
> >    - `Feature Data Row` para features
> >    - `Proficiency Data Row` para proficiências
> >    - `Skill Data Row` para skills
> >    - `Language Data Row` para idiomas
> >    - `Spell Data Row` para magias
> >    - `Spell School Data Row` para escolas de magia
> >    - `Damage Type Data Row` para tipos de dano
> >    - `Condition Data Row` para condições
> >    - `Ability Score Data Row` para atributos
> >    - `Trait Data Row` para traits
> >    - `Item Data Row` para itens
> > 4. Nomeie o Data Table (ex: `DT_Races`, `DT_Classes`, `DT_Features`)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">2. Importar JSON</summary>
>
> > 1. Selecione o Data Table criado
> > 2. No Details Panel, clique em **Import**
> > 3. Selecione o arquivo JSON
> > 4. O sistema importará automaticamente os dados
> >
> > **Formato JSON esperado:**
> > - Array de objetos
> > - Cada objeto representa uma linha
> > - Campo `Name` é usado como Row Name no Data Table
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">3. Editar Manualmente</summary>
>
> > 1. Selecione o Data Table
> > 2. No Details Panel, clique em **Add Row** para adicionar nova entrada
> > 3. Preencha os campos conforme necessário
> > 4. Use **Remove Row** para remover entradas
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Validações Aplicadas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">RaceDataTable</summary>
>
> > - **Sub-raças:** Sistema valida que sub-raça pertence à raça selecionada
> > - **Custom ASI:** Variant Human com `AbilityName = "Custom"` é tratado especialmente
> > - **Traits:** Traits `FeatChoice` e `SkillChoice` habilitam escolhas do jogador
> > - **Bônus Raciais:** Calculados automaticamente por `FRaceBonusMotor` que processa bônus de raça base, sub-raça e Variant Human
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">ClassDataTable</summary>
>
> > - **Features por nível:** Sistema coleta features baseado no nível do personagem
> > - **Subclasses:** Sistema valida que subclasse pertence à classe selecionada
> > - **Proficiências:** Sistema agrega proficiências de todas as classes do personagem
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">BackgroundDataTable</summary>
>
> > - **Proficiências:** Sistema agrega skill proficiencies ao personagem
> > - **Features:** Features de background são adicionadas automaticamente
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FeatDataTable</summary>
>
> > - **Pré-requisitos:** Sistema valida pré-requisitos antes de permitir seleção
> > - **Disponibilidade:** Apenas feats sem pré-requisitos de nível aparecem no nível 1
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Point Buy System</summary>
>
> > - **Validação:** Point Buy é validado por `FPointBuyValidator` que verifica se não excede 27 pontos e se todos os scores estão no range [8, 15]
> > - **Aplicação:** Point Buy é aplicado por `FPointBuyMotor` que ajusta automaticamente se exceder 27 pontos
> > - **Cálculo Final:** Ability scores finais são calculados via `FCharacterSheetCore` que orquestra `FRaceBonusMotor` e `FPointBuyMotor` sequencialmente
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplos de JSON Válido</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Raça Completa (Dwarf)</summary>
>
> > ```json
> > {
> >   "Name": "Dwarf",
> >   "RaceName": "Dwarf",
> >   "Description": "Bold and hardy dwarves are known as skilled warriors miners and workers of stone and metal",
> >   "AbilityScoreImprovements": [
> >     {
> >       "AbilityName": "Constitution",
> >       "Bonus": 2
> >     }
> >   ],
> >   "Size": "Medium",
> >   "BaseSpeed": 25,
> >   "Traits": [
> >     {
> >       "TraitName": "Darkvision",
> >       "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
> >       "TraitData": {
> >         "Range": "60",
> >         "Type": "Vision"
> >       }
> >     },
> >     {
> >       "TraitName": "Dwarven Resilience",
> >       "Description": "You have advantage on saving throws against poison.",
> >       "TraitData": {
> >         "Advantage": "Poison",
> >         "Resistance": "Poison"
> >       }
> >     }
> >   ],
> >   "SubraceNames": ["Hill Dwarf", "Mountain Dwarf"]
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Classe Completa (Wizard)</summary>
>
> > ```json
> > {
> >   "Name": "Wizard",
> >   "ClassName": "Wizard",
> >   "Description": "A scholarly magic-user capable of manipulating the structures of reality.",
> >   "HitDie": 6,
> >   "Proficiencies": [
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Daggers"
> >     },
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Darts"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Intelligence"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Wisdom"
> >     }
> >   ],
> >   "Features": [
> >     {
> >       "FeatureName": "Spellcasting",
> >       "Description": "As a student of arcane magic, you have a spellbook containing spells.",
> >       "LevelUnlocked": 1,
> >       "FeatureType": "Automatic",
> >       "FeatureData": {
> >         "SpellcastingAbility": "Intelligence",
> >         "SpellSaveDC": "8 + Proficiency + Intelligence Modifier"
> >       }
> >     },
> >     {
> >       "FeatureName": "Arcane Tradition",
> >       "Description": "You choose an arcane tradition.",
> >       "LevelUnlocked": 2,
> >       "FeatureType": "SubclassSelection",
> >       "FeatureData": {}
> >     }
> >   ],
> >   "SubclassNames": ["Evocation", "Abjuration", "Necromancy"]
> > }
> > ```
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Boas Práticas</b></summary>

> 1. **Nomes consistentes:** Use nomes consistentes entre Data Tables (ex: "Human" em RaceDataTable deve corresponder a "Human" em CharacterSheetDataAsset)
> 2. **Row Names:** Use o campo `Name` como Row Name (facilita busca com `FindRow`)
> 3. **Localização:** Use `FText` para descrições (suporta localização)
> 4. **Dados estruturados:** Use `TMap<FName, FString>` para dados programáticos quando necessário
> 5. **Validação:** Sempre valide JSON antes de importar (use validação JSON online)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚠️ Troubleshooting</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Problema: Sub-raça não aparece no dropdown</summary>
>
> > **Solução:** Verifique se `SubraceNames` na raça base contém o nome da sub-raça, e se a sub-raça existe no Data Table.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Problema: Feat não aparece para Variant Human</summary>
>
> > **Solução:** Verifique se o feat não tem pré-requisitos de nível ou ability score que o personagem não atende.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Problema: Bônus raciais não aplicando</summary>
>
> > **Solução:** Verifique se `AbilityName` corresponde exatamente aos nomes dos atributos ("Strength", "Dexterity", etc.) ou "Custom" para Variant Human.
>
> </details>

</details>
