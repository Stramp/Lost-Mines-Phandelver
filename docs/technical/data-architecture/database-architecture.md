# Arquitetura de Banco de Dados - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo Executivo</b></summary>

> Este documento descreve a **arquitetura de banco de dados normalizada** implementada no projeto, baseada em princípios de **Data-Oriented Design** e **Composição sobre Herança**, inspirada em jogos AAA como Baldur's Gate 3.
>
> **Princípios Fundamentais:**
>
> - ✅ **Normalização:** Dados organizados em tabelas relacionais, sem duplicação
> - ✅ **ID + Tags + Payload:** Padrão para estruturação de dados
> - ✅ **FDataTableRowHandle:** Referências type-safe entre Data Tables
> - ✅ **Gameplay Tags:** Categorização flexível e hierárquica
> - ✅ **Soft References:** Lazy loading de assets para performance
> - ✅ **Separação Static/Dynamic:** Definições em Data Tables, estado em runtime

</details>

---

## 🎯 Padrão "ID + Tags + Payload"

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Conceito Fundamental</b></summary>

> Cada entrada em uma Data Table segue o padrão **"ID + Tags + Payload"**:
>
> - **ID**: Identificador único (ex: `RaceID`, `ClassID`, `ItemID`)
> - **Tags**: Metadados e categorização via Gameplay Tags (ex: `TypeTags`)
> - **Payload**: Dados específicos do item (ex: `TraitData`, `FeatureData`, `ProficiencyData`)
>
> **Exemplo:**
>
> ```cpp
> USTRUCT(BlueprintType)
> struct FRaceDataRow : public FTableRowBase
> {
>     GENERATED_BODY()
>
>     // ID: Identificador único
>     UPROPERTY(EditAnywhere, BlueprintReadWrite)
>     FName RaceID;  // Ex: "RACE_Elf"
>
>     // Tags: Categorização flexível
>     UPROPERTY(EditAnywhere, BlueprintReadWrite)
>     FGameplayTagContainer TypeTags;  // Ex: ["Race.Elf", "Race.Fey"]
>
>     // Payload: Dados específicos
>     UPROPERTY(EditAnywhere, BlueprintReadWrite)
>     TMap<FName, FString> RaceData;  // Dados customizados
> };
> ```

</details>

---

## 🔗 FDataTableRowHandle: Referências Type-Safe

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Sistema de Referências</b></summary>

> **FDataTableRowHandle** é usado para criar referências type-safe entre Data Tables, substituindo strings e arrays diretos.
>
> **Antes (❌ ERRADO):**
>
> ```cpp
> // Strings diretas - sem type safety
> UPROPERTY(EditAnywhere)
> TArray<FName> Traits;  // ["Darkvision", "FeyAncestry"]
>
> UPROPERTY(EditAnywhere)
> TArray<FName> Languages;  // ["Common", "Elvish"]
> ```
>
> **Depois (✅ CORRETO):**
>
> ```cpp
> // Referências type-safe via FDataTableRowHandle
> UPROPERTY(EditAnywhere)
> TArray<FDataTableRowHandle> TraitHandles;  // Referências para TraitDataTable
>
> UPROPERTY(EditAnywhere)
> TArray<FDataTableRowHandle> LanguageHandles;  // Referências para LanguageDataTable
> ```
>
> **Benefícios:**
>
> - ✅ **Type Safety:** Editor valida referências automaticamente
> - ✅ **Integridade Referencial:** Não pode referenciar row inexistente
> - ✅ **Refatoração Segura:** Renomear row atualiza todas as referências
> - ✅ **Performance:** Resolução eficiente de referências
>
> **Uso:**
>
> ```cpp
> // Resolver referência
> if (const FTraitDataRow* TraitRow = DataTableRowHandleHelpers::ResolveHandle<FTraitDataRow>(TraitHandle))
> {
>     // Usar dados do trait
>     FString TraitName = TraitRow->TraitName.ToString();
> }
> ```

</details>

---

## 🏷️ Gameplay Tags: Categorização Flexível

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏷️ Sistema de Tags</b></summary>

> **Gameplay Tags** fornecem categorização hierárquica e flexível, substituindo enums rígidos e strings.
>
> **Configuração:**
>
> ```ini
> # Content/Data/GameplayTags/MyProject2Tags.ini
> [GameplayTags]
> +GameplayTagList=(Tag="Race.Elf",DevComment="Elf race")
> +GameplayTagList=(Tag="Race.Dwarf",DevComment="Dwarf race")
> +GameplayTagList=(Tag="Item.Weapon",DevComment="Weapon item")
> +GameplayTagList=(Tag="Item.Armor",DevComment="Armor item")
> ```
>
> **Uso em C++:**
>
> ```cpp
> UPROPERTY(EditAnywhere, BlueprintReadWrite)
> FGameplayTagContainer TypeTags;  // ["Race.Elf", "Race.Fey"]
>
> // Verificar tags
> if (GameplayTagHelpers::HasTag(TypeTags, FGameplayTag::RequestGameplayTag("Race.Elf")))
> {
>     // É um Elf
> }
>
> // Verificar grupo de tags
> if (GameplayTagHelpers::HasAnyTagInGroup(TypeTags, FGameplayTag::RequestGameplayTag("Race")))
> {
>     // É uma raça
> }
> ```
>
> **Benefícios:**
>
> - ✅ **Flexibilidade:** Adicionar novas categorias sem modificar código
> - ✅ **Hierarquia:** Tags podem ter parent tags (ex: `Race.Elf` é filho de `Race`)
> - ✅ **Performance:** Comparação eficiente via FName
> - ✅ **Editor-Friendly:** Seleção visual de tags no editor

</details>

---

## 📦 Soft References: Lazy Loading

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 Referências Suaves</b></summary>

> **TSoftObjectPtr** é usado para referências a assets que são carregados sob demanda (lazy loading).
>
> **Uso:**
>
> ```cpp
> UPROPERTY(EditAnywhere, BlueprintReadWrite)
> TSoftObjectPtr<UTexture2D> IconTexture;  // Ícone do item
>
> UPROPERTY(EditAnywhere, BlueprintReadWrite)
> TSoftObjectPtr<UStaticMesh> MeshReference;  // Mesh 3D do item
> ```
>
> **Carregamento:**
>
> ```cpp
> // Carregar asset quando necessário
> if (UTexture2D* LoadedTexture = SoftReferenceHelpers::LoadSoftReference(IconTexture))
> {
>     // Usar texture carregada
> }
> ```
>
> **Benefícios:**
>
> - ✅ **Performance:** Assets só são carregados quando necessários
> - ✅ **Memória:** Reduz uso de memória em runtime
> - ✅ **Streaming:** Suporta streaming de assets

</details>

---

## 📊 Estrutura de Data Tables

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Tabelas de Referência (Master Data)</b></summary>

> **Tabelas de Referência** contêm dados reutilizáveis referenciados por outras tabelas:
>
> 1. **`AbilityScoreDataTable`** - Atributos (Strength, Dexterity, etc.)
> 2. **`TraitDataTable`** - Traits reutilizáveis (Darkvision, FeyAncestry, etc.)
> 3. **`LanguageDataTable`** - Idiomas (Common, Elvish, etc.)
> 4. **`SkillDataTable`** - Skills (Acrobatics, Athletics, etc.)
> 5. **`SpellDataTable`** - Magias (Fireball, Magic Missile, etc.)
> 6. **`SpellSchoolDataTable`** - Escolas de magia (Evocation, Abjuration, etc.)
> 7. **`DamageTypeDataTable`** - Tipos de dano (Fire, Cold, etc.)
> 8. **`ConditionDataTable`** - Condições (Poisoned, Charmed, etc.)
> 9. **`ProficiencyDataTable`** - Proficiências (Armor, Weapons, etc.)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Tabelas Principais</b></summary>

> **Tabelas Principais** contêm dados de entidades principais do jogo:
>
> 1. **`RaceDataTable`** - Raças e sub-raças
>    - Referencia: `TraitDataTable`, `LanguageDataTable`, `AbilityScoreDataTable`
>    - Usa: `TraitHandles`, `LanguageHandles`, `SubraceHandles`
>
> 2. **`ClassDataTable`** - Classes e progressão
>    - Referencia: `AbilityScoreDataTable`, `SkillDataTable`, `ProficiencyDataTable`
>    - Usa: `SavingThrowIDs`, `AvailableSkillHandles`
>
> 3. **`BackgroundDataTable`** - Backgrounds
>    - Referencia: `SkillDataTable`, `LanguageDataTable`, `FeatureDataTable`
>    - Usa: `SkillProficiencyHandles`, `LanguageHandles`, `FeatureHandle`
>
> 4. **`FeatDataTable`** - Feats
>    - Referencia: `FeatureDataTable` (via `FC_ID`)
>
> 5. **`FeatureDataTable`** - Features de classe
>    - Dados estruturados em `FeatureData` (TMap)
>
> 6. **`ItemDataTable`** - Itens
>    - Referencia: `SpellDataTable` (via `SpellHandle`)
>    - Usa: `IconTexture`, `MeshReference` (Soft References)

</details>

---

## 🔄 Migração de Dados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Scripts de Migração</b></summary>

> Scripts Python foram criados para migrar dados antigos para a nova estrutura:
>
> - `scripts/migrate_race_json.py` - Migra `Race_All.json` → `RaceDataTable.json`
> - `scripts/migrate_class_json.py` - Migra `DJ_Class.json` → `ClassDataTable.json`
> - `scripts/migrate_background_json.py` - Migra `Background_All.json` → `BackgroundDataTable.json`
> - `scripts/migrate_feat_json.py` - Consolida `DJ_FeatsGerais.json` + `Feat_All.json` → `FeatDataTable.json`
> - `scripts/migrate_feature_json.py` - Migra `DJ_FeaturesClass.json` → `FeatureDataTable.json`
> - `scripts/migrate_proficiency_json.py` - Migra `DJ_Proficiencie.json` → `ProficiencyDataTable.json`
> - `scripts/migrate_item_json.py` - Migra `Item_All.json` → `ItemDataTable.json`
>
> **Transformações Aplicadas:**
>
> - ✅ Adição de IDs únicos (`RaceID`, `ClassID`, etc.)
> - ✅ Conversão de arrays diretos para `FDataTableRowHandle`
> - ✅ Adição de `TypeTags` (Gameplay Tags)
> - ✅ Normalização de dados duplicados
> - ✅ Estrutura "flat" (sem aninhamento profundo)

</details>

---

## 🛠️ Helpers e Utilitários

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Funções Helper</b></summary>

> **DataTableRowHandleHelpers:**
>
> ```cpp
> // Resolver referência para row específica
> template<typename RowType>
> const RowType* ResolveHandle(const FDataTableRowHandle& Handle);
>
> // Criar handle de referência
> FDataTableRowHandle CreateHandle(UDataTable* DataTable, FName RowName);
>
> // Validar handle
> bool IsHandleValid(const FDataTableRowHandle& Handle);
> ```
>
> **GameplayTagHelpers:**
>
> ```cpp
> // Verificar se container tem tag específica
> bool HasTag(const FGameplayTagContainer& Container, const FGameplayTag& Tag);
>
> // Verificar se container tem qualquer tag de um grupo
> bool HasAnyTagInGroup(const FGameplayTagContainer& Container, const FGameplayTag& TagGroup);
>
> // Converter FName para FGameplayTag
> FGameplayTag NameToTag(const FName& TagName);
>
> // Converter FGameplayTag para FName
> FName TagToName(const FGameplayTag& Tag);
> ```
>
> **SoftReferenceHelpers:**
>
> ```cpp
> // Carregar asset de soft reference
> template<typename AssetType>
> AssetType* LoadSoftReference(const TSoftObjectPtr<AssetType>& SoftRef);
>
> // Validar soft reference
> template<typename AssetType>
> bool IsSoftReferenceValid(const TSoftObjectPtr<AssetType>& SoftRef);
> ```

</details>

---

## 📋 Checklist de Implementação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Ao Criar Nova Data Table</b></summary>

> **Sempre seguir:**
>
> - [ ] Adicionar campo `*ID` (ex: `RaceID`, `ClassID`)
> - [ ] Adicionar campo `TypeTags` (FGameplayTagContainer)
> - [ ] Usar `FDataTableRowHandle` para referências a outras tabelas
> - [ ] Usar `TSoftObjectPtr` para referências a assets
> - [ ] Usar `TMap<FName, FString>` para dados customizados (Payload)
> - [ ] Criar struct que herda de `FTableRowBase`
> - [ ] Adicionar testes para carregamento e validação
> - [ ] Documentar referências e dependências

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Arquitetura Completa](../architecture.md)** - Arquitetura geral do projeto
> - **[Estrutura de Dados Ideal](./ideal-data-structure-report.md)** - Relatório completo da estrutura ideal
> - **[Guia de Data Tables](../guides/data-tables.md)** - Como usar Data Tables
> - **[Gameplay Tags (Epic Games)](https://docs.unrealengine.com/5.3/en-US/gameplay-tags-in-unreal-engine/)** - Documentação oficial
> - **[FDataTableRowHandle (Epic Games)](https://docs.unrealengine.com/5.3/en-US/data-table-row-handle-in-unreal-engine/)** - Documentação oficial

</details>

---

**Última atualização:** 2024-12-26
**Versão:** 1.0
