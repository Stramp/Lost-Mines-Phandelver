# API Reference - MyProject2

Referência completa da API das classes principais do sistema de fichas de personagem D&D 5e.

## Índice

- [CharacterDataComponent](#characterdatacomponent)
- [CharacterSheetComponent](#charactersheetcomponent)
- [CharacterSheetDataAsset](#charactersheetdataasset)

---

## CharacterDataComponent

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 CharacterDataComponent - Runtime Data Components</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Components/CharacterDataComponent.h`
>
> **Camada:** 3 - Runtime Data Components
>
> **Responsabilidade:** Armazenar dados replicáveis do personagem em runtime.
>
> ### Propriedades Replicáveis

#### CharacterName
```cpp
UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
FName CharacterName = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Nome do personagem
- **Uso:** Identificação do personagem

#### CharacterDescription
```cpp
UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
FText CharacterDescription = FText::GetEmpty();
```
- **Tipo:** `FText`
- **Replicável:** Sim
- **Descrição:** Descrição do personagem (localizável)
- **Uso:** Descrição textual do personagem

#### CharacterTotalLvl
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
int32 CharacterTotalLvl = 0;
```
- **Tipo:** `int32`
- **Replicável:** Sim
- **ReadOnly:** Sim (calculado automaticamente)
- **Descrição:** Nível total do personagem (soma de todos os níveis de classes, máximo 20)
- **Validação:** Deve estar entre 1 e 20

#### SelectedRace
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedRace = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Raça selecionada do personagem
- **Validação:** Não pode ser `NAME_None`

#### SelectedSubrace
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedSubrace = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Sub-raça selecionada (se aplicável)
- **Nota:** Pode ser `NAME_None` se raça não tem sub-raças

#### SelectedBackground
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedBackground = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Background selecionado
- **Validação:** Não pode ser `NAME_None`

#### Proficiencies
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
TArray<FName> Proficiencies;
```
- **Tipo:** `TArray<FName>`
- **Replicável:** Sim
- **Descrição:** Proficiências do personagem (raça + classe + background)
- **Uso:** Lista de skills, armas, armaduras em que o personagem é proficiente

#### AbilityScores
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
TMap<FName, int32> AbilityScores;
```
- **Tipo:** `TMap<FName, int32>`
- **Replicável:** Sim
- **Descrição:** Ability scores finais (chave: nome do atributo, valor: score final)
- **Chaves esperadas:** "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"
- **Validação:** Cada score deve estar entre 1 e 30

### Métodos Públicos

#### ValidateDataIntegrity()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character Data")
bool ValidateDataIntegrity() const;
```

**Descrição:** Valida integridade dos dados do personagem. Verifica se todos os dados necessários estão presentes e consistentes.

**Validações realizadas:**
1. **Ability Scores:** Verifica se todos os 6 atributos estão presentes e com valores válidos (1-30)
2. **Raça:** Verifica se `SelectedRace` não é `NAME_None`
3. **Background:** Verifica se `SelectedBackground` não é `NAME_None`
4. **Nível Total:** Verifica se está entre 1 e 20
5. **Nome:** Avisa se `CharacterName` está vazio (warning, não erro)

**Retorno:**
- `true` - Todos os dados estão válidos
- `false` - Dados inválidos ou incompletos

**Quando usar:**
- No `BeginPlay()` para garantir dados válidos antes de usar
- Antes de usar dados em combat components
- Antes de calcular valores derivados (HP, modifiers, etc.)

**Exemplo de uso:**

```cpp
void UMyCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    UCharacterDataComponent* DataComponent = GetCharacterDataComponent();
    if (DataComponent && DataComponent->ValidateDataIntegrity())
    {
        // Dados válidos, pode usar com segurança
        int32 Strength = DataComponent->AbilityScores[TEXT("Strength")];
        // ...
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Character data is invalid!"));
    }
}
```

**Integração com LogCharacterSheet():**

O método `LogCharacterSheet()` chama automaticamente `ValidateDataIntegrity()` e exibe o resultado:

```cpp
void UCharacterDataComponent::LogCharacterSheet() const
{
    // ... exibe dados ...

    // Validação de integridade
    bool bIsValid = ValidateDataIntegrity();
    if (bIsValid)
    {
        UE_LOG(LogTemp, Warning, TEXT("  ✅ Todos os dados estão válidos e organizados corretamente"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("  ❌ Dados inválidos ou incompletos! Verifique os erros acima."));
    }
}
```

#### LogCharacterSheet()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character Data")
void LogCharacterSheet() const;
```

**Descrição:** Faz log completo da ficha do personagem no console, incluindo validação de integridade.

**O que exibe:**
- Nome e descrição
- Nível total
- Raça (com sub-raça se houver)
- Background
- Ability Scores (todos os 6 atributos)
- Proficiências (lista formatada)
- Status de validação de integridade

**Uso:** Chamado automaticamente no `BeginPlay()`, ou manualmente para debug.

**Exemplo de saída:**
```
=== Character Sheet ===
Name: Elias
Description: Severino
Level Total: 1
Race: Human (Variant Human)
Background: Acolyte
--- Ability Scores ---
  Strength: 10
  Dexterity: 12
  Constitution: 14
  Intelligence: 13
  Wisdom: 15
  Charisma: 11
--- Proficiencies (4) ---
  Insight, Religion, Perception, Investigation
--- Data Integrity ---
  ✅ Todos os dados estão válidos e organizados corretamente
======================
```

### Replicação

Todas as propriedades são replicáveis via `DOREPLIFETIME`:

```cpp
void UCharacterDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCharacterDataComponent, CharacterName);
    DOREPLIFETIME(UCharacterDataComponent, CharacterDescription);
    DOREPLIFETIME(UCharacterDataComponent, CharacterTotalLvl);
    DOREPLIFETIME(UCharacterDataComponent, SelectedRace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedSubrace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedBackground);
    DOREPLIFETIME(UCharacterDataComponent, Proficiencies);
    DOREPLIFETIME(UCharacterDataComponent, AbilityScores);
}
```

</details>

---

## CharacterSheetComponent

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌉 CharacterSheetComponent - Bridge Components</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Components/CharacterSheetComponent.h`
>
> **Camada:** 2 - Bridge Components
>
> **Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.
>
> ### Propriedades

#### SourceDataAsset
```cpp
UPROPERTY(EditAnywhere, Category = "Character Sheet")
UCharacterSheetDataAsset *SourceDataAsset;
```
- **Tipo:** `UCharacterSheetDataAsset*`
- **Editável:** Sim (no editor)
- **Descrição:** Data Asset fonte (template) para inicialização

### Métodos Públicos

#### InitializeFromDataAsset()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character")
void InitializeFromDataAsset(UCharacterSheetDataAsset *DataAsset);
```

**Descrição:** Inicializa o componente a partir de um Data Asset. Lê os dados do Data Asset e copia para o `CharacterDataComponent`.

**Fluxo:**
1. Valida Data Asset (não pode ser nullptr)
2. Busca `CharacterDataComponent` no Actor
3. Copia dados do Data Asset para Runtime Component:
   - Nome, descrição, nível total
   - Raça, sub-raça, background
   - Proficiências
   - Ability scores (valores finais)

**Chamado automaticamente:**
- No `BeginPlay()` se `SourceDataAsset` estiver atribuído

**Exemplo de uso:**

```cpp
// No editor: atribuir SourceDataAsset no CharacterSheetComponent
// Ou programaticamente:
UCharacterSheetComponent* SheetComponent = GetCharacterSheetComponent();
if (SheetComponent && MyDataAsset)
{
    SheetComponent->InitializeFromDataAsset(MyDataAsset);
}
```

</details>

---

## CharacterSheetDataAsset

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 CharacterSheetDataAsset - Data Assets</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
>
> **Camada:** 1 - Data Assets
>
> **Responsabilidade:** Armazenar configuração estática editável no editor.
>
> ### Propriedades Principais

#### CharacterName
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Basic Info")
FName CharacterName = NAME_None;
```
- **Tipo:** `FName`
- **Editável:** Apenas em defaults
- **Descrição:** Nome do personagem

#### SelectedRace
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race & Background",
          meta = (GetOptions = "GetRaceNames"))
FName SelectedRace = NAME_None;
```
- **Tipo:** `FName`
- **GetOptions:** `GetRaceNames()` - Dropdown com raças disponíveis
- **Descrição:** Raça selecionada

#### AbilityScores
```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Scores")
TMap<FName, FAbilityScoreEntry> AbilityScores;
```
- **Tipo:** `TMap<FName, FAbilityScoreEntry>`
- **Descrição:** Ability scores do personagem (chave: nome do atributo, valor: entrada com base/racial/final)
- **Estrutura:** Cada entrada contém `BaseScore`, `RacialBonus`, `FinalScore`

### Métodos GetOptions

Funções `UFUNCTION(CallInEditor)` para popular dropdowns no editor:

- `GetRaceNames()` - Retorna nomes de raças
- `GetSubraceNames()` - Retorna sub-raças para raça selecionada
- `GetBackgroundNames()` - Retorna nomes de backgrounds
- `GetClassNames()` - Retorna nomes de classes
- `GetSubclassNames(FName ClassName)` - Retorna subclasses para classe
- `GetAbilityScoreNames()` - Retorna nomes dos 6 atributos
- `GetAvailableFeatNames()` - Retorna feats disponíveis
- `GetSkillNames()` - Retorna nomes de skills

**Nota:** A lógica de implementação está em `FCharacterSheetDataAssetGetOptions`, mas as funções devem permanecer na classe para o sistema `GetOptions` do Unreal funcionar.

### Validação no Editor

O `CharacterSheetDataAsset` valida dados automaticamente no editor via `PostEditChangeProperty()`:

- Valida Point Buy (27 pontos, scores 8-15)
- Valida nível total (máximo 20)
- Valida escolhas de Variant Human
- Atualiza bônus raciais automaticamente
- Atualiza campos calculados (proficiências, features)

---

## Estruturas Relacionadas

### FAbilityScoreEntry

**Caminho:** `Source/MyProject2/Characters/Data/CharacterSheetDataAssetTypes.h`

```cpp
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreEntry
{
    GENERATED_BODY()

    /** Score base (8-15 para Point Buy) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    int32 BaseScore = 8;

    /** Bônus racial aplicado (calculado automaticamente) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 RacialBonus = 0;

    /** Score final (BaseScore + RacialBonus) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 FinalScore = 8;
};
```

**Uso:** Armazena ability score com base, bônus racial e score final.

---

## Helpers e Utilitários

### ComponentHelpers

**Caminho:** `Source/MyProject2/Utils/ComponentHelpers.h`

```cpp
namespace ComponentHelpers
{
    UCharacterDataComponent* FindCharacterDataComponent(AActor* Owner);
}
```

**Uso:** Busca `CharacterDataComponent` em um Actor.

### CharacterSheetHelpers

**Caminho:** `Source/MyProject2/Utils/CharacterSheetHelpers.h`

Funções helper para leitura e validação de Data Tables:
- `GetAllRaceNames()` - Filtra apenas raças base (não sub-raças)
- `GetAvailableFeats()` - Retorna feats disponíveis baseado em pré-requisitos
- `CalculateTotalLevel()` - Calcula nível total de ClassLevels
- E outras funções utilitárias

---

## Preparação para Combat Components

O `CharacterDataComponent` está preparado para uso em combat components:

- **Ability Scores:** Acessíveis via `AbilityScores` map
- **Validação:** `ValidateDataIntegrity()` garante dados válidos antes de usar
- **Replicação:** Todos os dados são replicáveis para multiplayer
- **Estrutura:** Dados organizados e consistentes

**Exemplo de integração futura:**

```cpp
// Em um CombatComponent futuro:
int32 GetAbilityModifier(FName AbilityName) const
{
    if (UCharacterDataComponent* DataComp = GetCharacterDataComponent())
    {
        if (DataComp->AbilityScores.Contains(AbilityName))
        {
            int32 Score = DataComp->AbilityScores[AbilityName];
            return (Score - 10) / 2; // Modifier = (Score - 10) / 2
        }
    }
    return 0;
}
```

</details>

---

## Preparação para GAS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Migração Futura para Gameplay Ability System</b></summary>

> A estrutura atual facilita migração futura para GAS:
>
> - **Dados em Components:** Fácil migrar para GAS Attributes
> - **Replicação configurada:** GAS usa mesmo sistema
> - **Validação implementada:** Pode ser migrada para GAS validators
> - **Estrutura modular:** Lógica pode ser migrada para GAS Abilities

</details>
