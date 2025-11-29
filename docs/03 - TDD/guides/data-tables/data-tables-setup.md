---
title: "Data Tables Setup"
category: technical
subcategory: guides
tags: [data-tables, setup, json, configuration]
last_updated: 2024-12-27
difficulty: intermediate
related: [data-tables.md, ../data-architecture/index.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Data Tables Setup

# Guia de Configuração de Data Tables - MyProject2

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este guia explica como criar e configurar os Data Tables necessários para o sistema de fichas de personagem D&D 5e funcionar corretamente.
>

</details>

## 🎯 Data Tables Necessários

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Lista Completa</b></summary>

> O sistema requer **4 Data Tables principais:**
>

> 1. **Race Data Table** - Raças e sub-raças D&D 5e
> 2. **Class Data Table** - Classes e progressão de níveis
> 3. **Background Data Table** - Backgrounds e suas características
> 4. **Feat Data Table** - Feats e pré-requisitos
>
> **Importante:** Todos os Data Tables devem ser configurados antes de criar personagens.
>
</details>
---

## 🏗️ Estrutura dos Data Tables

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Filosofia de Estrutura</b></summary>

> **Princípios Fundamentais:**
>

> - **Estrutura "Flat" (Plana)**: JSONs relacionais e planos, não profundamente aninhados
> - O importador do Unreal Engine quebra com estruturas muito aninhadas
> - Use referências por ID ao invés de estruturas aninhadas complexas
> - **Padrão "ID + Tags + Payload"**: Cada entrada tem um ID único, tags para categorização, e payload com dados específicos
> - **Separação Static/Dynamic**: Data Tables contêm apenas definições estáticas (o que o item "é"), não estado dinâmico
> - **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança
>
> **📖 Para estruturas completas, veja:**
>
> - **[RaceDataTable.h](../../../Source/MyProject2/Data/Tables/RaceDataTable.h)** - Estrutura `FRaceDataRow`
> - **[ClassDataTable.h](../../../Source/MyProject2/Data/Tables/ClassDataTable.h)** - Estrutura `FClassDataRow`
> - **[BackgroundDataTable.h](../../../Source/MyProject2/Data/Tables/BackgroundDataTable.h)** - Estrutura `FBackgroundDataRow`
> - **[FeatDataTable.h](../../../Source/MyProject2/Data/Tables/FeatDataTable.h)** - Estrutura `FFeatDataRow`
>
> **📖 Para mais detalhes sobre arquitetura de dados, veja:**
>
> - [Estrutura de Dados Ideal](../data-architecture/ideal-data-structure-report.md)
> - [Arquiteturas de Alta Performance](../data-architecture/high-performance-architectures-report.md)
>
</details>
---

## 🎨 Passo 1: Criar Race Data Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👥 Configurar Raças</b></summary>

> ### 1.1 Criar Data Table
>

> 1. No **Content Browser**, navegue até a pasta desejada
> 2. Clique com botão direito → **Miscellaneous** → **Data Table**
> 3. Selecione **Race Data Row** como Row Structure
> 4. Nomeie como `DT_Races`
>
</details>
    ### 1.2 Estrutura Esperada

    Cada linha deve ter:

    - **Name** (FName) - Nome da raça (ex: "Human", "Elf", "Dwarf")
    - **FC_ID** (FName) - ID único (ex: "Race_Human", "Race_Elf")
    - **Description** (FText) - Descrição da raça
    - **AbilityScoreBonuses** (TMap<FName, int32>) - Bônus de atributos
    - **Traits** (TArray<FRaceTrait>) - Traits da raça (Darkvision, Fey Ancestry, etc.)
    - **Subraces** (TArray<FRaceDataRow>) - Sub-raças (se aplicável)

    ### 1.3 Exemplo de Dados

    **Human (Base):**

    ```
    Name: "Human"
    FC_ID: "Race_Human"
    AbilityScoreBonuses: { "Strength": 1, "Dexterity": 1, "Constitution": 1, "Intelligence": 1, "Wisdom": 1, "Charisma": 1 }
    Traits: [] (sem traits base)
    ```

    **Variant Human (Sub-raça):**

    ```
    Name: "Variant Human"
    FC_ID: "Race_VariantHuman"
    AbilityScoreBonuses: {} (sem bônus fixos - escolhe 2x +1)
    Traits: [] (sem traits base)
    ```

    **📖 Para estrutura completa, veja [RaceDataTable.h](../../../Source/MyProject2/Data/Tables/RaceDataTable.h)**

---

## ⚔️ Passo 2: Criar Class Data Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎭 Configurar Classes</b></summary>

> ### 2.1 Criar Data Table
>

> 1. No **Content Browser**, clique com botão direito → **Miscellaneous** → **Data Table**
> 2. Selecione **Class Data Row** como Row Structure
> 3. Nomeie como `DT_Classes`
>
</details>
    ### 2.2 Estrutura Esperada

    Cada linha deve ter:

    - **Name** (FName) - Nome da classe (ex: "Fighter", "Wizard", "Cleric")
    - **FC_ID** (FName) - ID único (ex: "Class_Fighter", "Class_Wizard")
    - **Description** (FText) - Descrição da classe
    - **HitDie** (int32) - Dado de vida (6, 8, 10, 12)
    - **Proficiencies** (TArray<FProficienciesEntry>) - Proficiências da classe
    - **Progression** (TArray<FProgressEntry>) - Progressão por nível (features, spells, etc.)

    ### 2.3 Exemplo de Dados

    **Fighter (Nível 1):**

    ```
    Name: "Fighter"
    FC_ID: "Class_Fighter"
    HitDie: 10
    Proficiencies: ["Armor: All", "Weapons: Simple, Martial", "Saving Throws: Strength, Constitution"]
    Progression: [
    { Level: 1, Features: ["Fighting Style", "Second Wind"] },
    { Level: 2, Features: ["Action Surge"] },
    ...
    ]
    ```

    **📖 Para estrutura completa, veja [ClassDataTable.h](../../../Source/MyProject2/Data/Tables/ClassDataTable.h)**

---

## 📜 Passo 3: Criar Background Data Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Configurar Backgrounds</b></summary>

> ### 3.1 Criar Data Table
>

> 1. No **Content Browser**, clique com botão direito → **Miscellaneous** → **Data Table**
> 2. Selecione **Background Data Row** como Row Structure
> 3. Nomeie como `DT_Backgrounds`
>
</details>
    ### 3.2 Estrutura Esperada

    Cada linha deve ter:

    - **Name** (FName) - Nome do background (ex: "Acolyte", "Folk Hero")
    - **FC_ID** (FName) - ID único (ex: "Background_Acolyte")
    - **Description** (FText) - Descrição do background
    - **SkillProficiencies** (TArray<FName>) - Skills proficientes
    - **Languages** (TArray<FName>) - Idiomas conhecidos
    - **Equipment** (TArray<FName>) - Equipamentos iniciais

    ### 3.3 Exemplo de Dados

    **Acolyte:**

    ```
    Name: "Acolyte"
    FC_ID: "Background_Acolyte"
    SkillProficiencies: ["Insight", "Religion"]
    Languages: ["Two languages of choice"]
    Equipment: ["Holy Symbol", "Prayer Book", "5 sticks of incense", ...]
    ```

    **📖 Para estrutura completa, veja [BackgroundDataTable.h](../../../Source/MyProject2/Data/Tables/BackgroundDataTable.h)**

---

## ⭐ Passo 4: Criar Feat Data Table

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💫 Configurar Feats</b></summary>

> ### 4.1 Criar Data Table
>

> 1. No **Content Browser**, clique com botão direito → **Miscellaneous** → **Data Table**
> 2. Selecione **Feat Data Row** como Row Structure
> 3. Nomeie como `DT_Feats`
>
</details>
    ### 4.2 Estrutura Esperada

    Cada linha deve ter:

    - **Name** (FName) - Nome do feat (ex: "Alert", "Great Weapon Master")
    - **FC_ID** (FName) - ID único (ex: "Feat_Alert", "Feat_GreatWeaponMaster")
    - **Description** (FText) - Descrição do feat
    - **FeatureData** (TMap<FString, FString>) - Dados do feat
    - Chave `"Prerequisites"` - Pré-requisitos (ex: "Strength 13", "Dexterity 13, Wisdom 13")

    ### 4.3 Exemplo de Dados

    **Alert:**

    ```
    Name: "Alert"
    FC_ID: "Feat_Alert"
    FeatureData: {
    "Prerequisites": ""  (sem pré-requisitos)
    }
    ```

    **Great Weapon Master:**

    ```
    Name: "Great Weapon Master"
    FC_ID: "Feat_GreatWeaponMaster"
    FeatureData: {
    "Prerequisites": "Strength 13"
    }
    ```

    **📖 Para estrutura completa, veja [FeatDataTable.h](../../../Source/MyProject2/Data/Tables/FeatDataTable.h)**

---

## 🔗 Passo 5: Atribuir Data Tables ao CharacterSheetDataAsset

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Conectar Data Tables</b></summary>

> ### 5.1 Criar CharacterSheetDataAsset
>

> 1. No **Content Browser**, clique com botão direito → **Miscellaneous** → **Data Asset**
> 2. Selecione **Character Sheet Data Asset**
> 3. Nomeie como `DA_CharacterSheet_Test`
>
</details>
    ### 5.2 Atribuir Data Tables

    No `CharacterSheetDataAsset` criado, na categoria **Data Tables**:

    1. **Race Data Table:** Atribua `DT_Races`
    2. **Class Data Table:** Atribua `DT_Classes`
    3. **Background Data Table:** Atribua `DT_Backgrounds`
    4. **Feat Data Table:** Atribua `DT_Feats`

    **Importante:** Após atribuir todos os Data Tables, todas as categorias da ficha ficarão visíveis automaticamente.

    ### 5.3 Verificar

    Após atribuir os Data Tables, você deve ver:

    - Dropdowns populados em **Selected Race**, **Selected Class**, etc.
    - Categorias aparecendo (Ability Scores, Variant Human, etc.)
    - Sistema funcionando corretamente

---

## ✅ Validação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Verificar Configuração</b></summary>

> ### Checklist de Validação
>

> - [ ] Race Data Table criado e populado
> - [ ] Class Data Table criado e populado
> - [ ] Background Data Table criado e populado
> - [ ] Feat Data Table criado e populado
> - [ ] Todos os Data Tables atribuídos ao CharacterSheetDataAsset
> - [ ] Dropdowns aparecem no editor
> - [ ] Sistema valida dados corretamente
>
</details>
    ### Testar Configuração

    1. Crie um `CharacterSheetDataAsset`
    2. Atribua todos os Data Tables
    3. Tente selecionar uma raça no dropdown
    4. Se aparecerem opções, está funcionando! ✅

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Guia de Início Rápido](getting-started.md)** - Usar Data Tables para criar personagem
> - **[API Reference](../../api.md)** - Estruturas completas dos Data Tables
> - **[Arquitetura](../../architecture.md)** - Como Data Tables se integram ao sistema
> - **[Regras D&D 5e](../../../03 - TDD/dnd-rules/)** - Regras oficiais para referência
>

</details>

## 🐛 Troubleshooting

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❓ Problemas Comuns</b></summary>

> ### Problema: Dropdowns não aparecem
>

> **Solução:**
>
> 1. Verifique se todos os Data Tables foram atribuídos
> 2. Verifique se os Data Tables têm dados (não estão vazios)
> 3. Verifique se a estrutura (Row Structure) está correta
>
</details>
    ### Problema: Estrutura não encontrada

    **Solução:**

    1. Compile o projeto primeiro (as structs são geradas em C++)
    2. Verifique se os arquivos `.h` das structs existem
    3. Regenere os arquivos do projeto se necessário

    ### Problema: Dados não validam

    **Solução:**

    1. Verifique se os dados seguem a estrutura esperada
    2. Verifique os logs do editor para erros específicos
    3. Consulte a documentação da struct para formato correto
