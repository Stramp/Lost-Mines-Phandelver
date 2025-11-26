# API Reference - MyProject2

Referência completa da API das classes principais do sistema de fichas de personagem D&D 5e.

## Índice

- [CharacterDataComponent](#characterdatacomponent)
- [CharacterSheetComponent](#charactersheetcomponent)
- [CharacterSheetDataAsset](#charactersheetdataasset)
- [CreateSheet - Motores de Criação](#createsheet---motores-de-criação)
- [Helpers e Utilitários](#helpers-e-utilitários)

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

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 Structs e Tipos de Dados</b></summary>

> Estruturas auxiliares usadas no sistema de fichas:
>
> ### FAbilityScoreEntry

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

</details>

---

## CreateSheet - Motores de Criação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motores Desacoplados para Criação de Personagem</b></summary>

> Sistema modular com motores desacoplados para cálculo de ability scores finais. Arquitetura genérica que funciona tanto no Data Asset quanto em Widgets.

> ### FCharacterSheetCore

> **Caminho:** `Source/MyProject2/CreateSheet/Core/CharacterSheetCore.h`
>
> **Responsabilidade:** Orquestrador genérico que coordena todos os motores de criação de personagem.
>
> **Método Principal:**
>
> #### RecalculateFinalScores()
> ```cpp
> static void RecalculateFinalScores(FCharacterSheetData &Data, FPointBuyResult *OutPointBuyResult = nullptr);
> ```
>
> - **Parâmetros:**
>   - `Data` - Estrutura genérica com dados de entrada e referências de saída
>   - `OutPointBuyResult` - [OPCIONAL] Resultado do motor de Point Buy (feedback e ajustes)
> - **Descrição:** Reseta scores para base (8) e aplica cada motor sequencialmente
> - **Fórmula:** `FinalScore = 8 (base) + RacialBonus + PointBuyAllocation`
> - **Fluxo:**
>   1. Reseta todos os Final Scores para 8 (base)
>   2. Aplica `FRaceBonusMotor::ApplyRacialBonuses()`
>   3. Aplica `FPointBuyMotor::ApplyPointBuy()`
>
> ### FCharacterSheetData

> **Caminho:** `Source/MyProject2/CreateSheet/Core/CharacterSheetData.h`
>
> **Responsabilidade:** Estrutura genérica de dados que permite o Core funcionar em diferentes contextos.
>
> **Campos Principais:**
>
> **Input (Dados de Entrada):**
> - `PointBuyStrength`, `PointBuyDexterity`, etc. - Alocação de Point Buy (0-7 cada)
> - `SelectedRace`, `SelectedSubrace` - Raça e sub-raça selecionadas
> - `CustomAbilityScoreChoices` - Escolhas customizadas (Variant Human)
> - `RaceDataTable` - Data Table de raças
>
> **Output (Referências de Saída):**
> - `FinalStrength`, `FinalDexterity`, etc. - Ponteiros para Final Scores (serão modificados)
>
> **Características:**
> - Struct C++ normal (não USTRUCT) - contém ponteiros
> - Permite reutilização: mesmo Core funciona no Data Asset e em Widgets
> - Princípio: "Program to an interface, not an implementation"
>
> ### FRaceBonusMotor

> **Caminho:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusMotor.h`
>
> **Responsabilidade:** Calcular e aplicar bônus raciais nos Final Scores.
>
> **Método Principal:**
>
> #### ApplyRacialBonuses()
> ```cpp
> static void ApplyRacialBonuses(FCharacterSheetData &Data);
> ```
>
> - **Parâmetros:**
>   - `Data` - Estrutura genérica com dados de raça e referências de Final Scores
> - **Descrição:** Calcula bônus de raça base, sub-raça e Variant Human, e aplica nos Final Scores
> - **Fluxo:**
>   1. Busca RaceRow e SubraceRow usando `DataTableHelpers`
>   2. Calcula bônus usando `FRaceBonusHelpers::CalculateRacialBonuses()`
>   3. Incrementa Final Scores usando `FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses()`
>
> **Características:**
> - Motor independente: não conhece Point Buy, apenas aplica bônus raciais
> - Suporta Variant Human com escolhas customizadas
> - Usa helpers puros para cálculos
>
> ### FRaceBonusHelpers

> **Caminho:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusHelpers.h`
>
> **Responsabilidade:** Funções helper puras para cálculo de bônus raciais.
>
> **Métodos:**
>
> #### CalculateRacialBonuses()
> ```cpp
> static void CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
>                                    const TArray<FName> &CustomChoices, TMap<FName, int32> &RacialBonuses);
> ```
> - Calcula bônus raciais de ability scores (raça base + sub-raça + Variant Human)
>
> #### IncrementFinalScoresWithRacialBonuses()
> ```cpp
> static void IncrementFinalScoresWithRacialBonuses(const TMap<FName, int32> &RacialBonuses,
>                                                    int32 &FinalStrength, int32 &FinalDexterity, ...);
> ```
> - Incrementa Final Scores com bônus raciais calculados
>
> ### FPointBuyMotor

> **Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyMotor.h`
>
> **Responsabilidade:** Aplicar alocação de Point Buy nos Final Scores com validação automática.
>
> **Método Principal:**
>
> #### ApplyPointBuy()
> ```cpp
> static FPointBuyResult ApplyPointBuy(FCharacterSheetData &Data);
> ```
>
> - **Parâmetros:**
>   - `Data` - Estrutura genérica com dados de Point Buy e referências de Final Scores
> - **Retorno:** `FPointBuyResult` com feedback sobre validação e ajustes realizados
> - **Descrição:** Valida se não excede 27 pontos e ajusta automaticamente se necessário
> - **Fluxo:**
>   1. Converte dados de entrada para `TMap<FName, int32>`
>   2. Calcula custo total usando `CharacterSheetHelpers::CalculateTotalPointBuyCost()`
>   3. Se exceder 27 pontos, ajusta usando `AdjustPointBuyAllocation()`
>   4. Incrementa Final Scores usando `CalculationHelpers::IncrementFinalScoresWithPointBuy()`
>   5. Retorna `FPointBuyResult` com feedback
>
> **Características:**
> - Motor independente: não conhece bônus raciais, apenas aplica Point Buy
> - Validação automática: ajusta se exceder 27 pontos
> - Ajuste automático: reduz do final da fila (Charisma → Wisdom → ... → Strength)
>
> ### FPointBuyValidator

> **Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyValidator.h`
>
> **Responsabilidade:** Validar alocação de Point Buy.
>
> **Métodos:**
>
> #### ValidatePointBuy()
> ```cpp
> static bool ValidatePointBuy(const TMap<FName, int32> &PointBuyAllocation, int32 MaxPoints = 27);
> ```
> - Valida se alocação não excede MaxPoints e se todos os scores estão no range [8, 15]
>
> ### FPointBuyResult

> **Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyResult.h`
>
> **Responsabilidade:** Struct de feedback sobre aplicação de Point Buy.
>
> **Campos:**
> - `bWasAdjusted` - Se o motor teve que ajustar a alocação (excedeu 27 pontos)
> - `AdjustedAllocation` - Alocação ajustada (pode ser diferente da original)
> - `PointsRemaining` - Pontos restantes após alocação
> - `FeedbackMessage` - Mensagem de feedback para o caller ajustar a UI
>
> **Uso:** Retornado por `FPointBuyMotor::ApplyPointBuy()` para informar o caller sobre ajustes realizados.

### FMulticlassMotor

> **Caminho:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassMotor.h`
>
> **Responsabilidade:** Validar e aplicar regras de multiclassing D&D 5e.
>
> **Métodos Principais:**
>
> #### GetAvailableClasses()
> ```cpp
> static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable,
>                                          int32 FinalStrength, int32 FinalDexterity,
>                                          int32 FinalConstitution, int32 FinalIntelligence,
>                                          int32 FinalWisdom, int32 FinalCharisma);
> ```
> - **Parâmetros:**
>   - `ClassDataTable` - Data Table de classes (pode ser nullptr)
>   - `FinalStrength`, `FinalDexterity`, etc. - Atributos finais do personagem
> - **Retorno:** Array com nomes de classes disponíveis (que atendem requisitos de atributo)
> - **Descrição:** Filtra classes que o personagem pode pegar baseado nos atributos finais
> - **Suporte para requisitos complexos:** Ex: "STR/13|DEX/13" (STR ou DEX >= 13)
>
> #### ProcessLevelChange()
> ```cpp
> static void ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);
> ```
> - **Parâmetros:**
>   - `ClassName` - Nome da classe que teve o nível alterado
>   - `LevelInClass` - Novo nível na classe (1-20)
>   - `ClassDataTable` - Data Table de classes para buscar informações
> - **Descrição:** Processa mudança de nível em uma classe específica, busca informações da classe na tabela e loga features ganhas no nível
>
> **Características:**
> - Motor independente: não conhece outros motores, apenas aplica regras de multiclasse
> - Genérico: recebe dados puros, não objetos concretos
> - Validação automática de requisitos de atributo para multiclassing D&D 5e

### FMulticlassHelpers

> **Caminho:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassHelpers.h`
>
> **Responsabilidade:** Funções helper para processamento de multiclassing.
>
> **Métodos:**
>
> #### GetAvailableClassWithTagRequirements()
> ```cpp
> static TArray<FName> GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
>                                                           const TArray<int32> &CharacterAttributes);
> ```
> - **Descrição:** Busca classes disponíveis baseado em requisitos de atributo
> - **Suporte para parsing de requisitos:** Ex: "STR/13|DEX/13" (STR ou DEX >= 13)
>
> #### AdjustProgressionArraySize()
> ```cpp
> static void AdjustProgressionArraySize(TArray<FClassLevelEntry> &Progression, int32 LevelInClass);
> ```
> - **Descrição:** Ajusta tamanho do array de progressão baseado no nível da classe

</details>

---

## Helpers e Utilitários

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Funções Helper Reutilizáveis</b></summary>

> Funções helper organizadas em namespaces em `Utils/`:

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Utils - Funções Helper Reutilizáveis</b></summary>

> Todas as funções helper estão organizadas em namespaces no diretório `Source/MyProject2/Utils/`.
>
> **Princípios:**
> - Funções puras (sem efeitos colaterais)
> - Parametrizadas (sem dependência de estado interno)
> - Testáveis isoladamente
> - < 50 linhas cada
> - Reutilizáveis em editor e runtime

### ComponentHelpers

**Caminho:** `Source/MyProject2/Utils/ComponentHelpers.h`

```cpp
namespace ComponentHelpers
{
    UCharacterDataComponent* FindCharacterDataComponent(AActor* Owner);
}
```

**Funções:**

#### FindCharacterDataComponent()

Busca `CharacterDataComponent` em um Actor.

**Parâmetros:**
- `Owner` - Actor onde buscar o componente (pode ser nullptr)

**Retorno:**
- `UCharacterDataComponent*` - Componente encontrado, ou `nullptr` se não encontrado ou Owner inválido

**Uso:** Reutilizável em qualquer lugar que precise buscar o componente de dados do personagem.

---

### ValidationHelpers

**Caminho:** `Source/MyProject2/Utils/ValidationHelpers.h`

Funções helper para validação de dados de personagem D&D 5e.

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Point Buy Validation</summary>

> **ValidatePointBuy()**
>
> ```cpp
> bool ValidatePointBuy(const TMap<FName, int32> &BaseScores,
>                       int32 &PointsRemaining,
>                       int32 MaxPoints = 27);
> ```
>
> Valida alocação de Point Buy e calcula pontos restantes.
>
> **Parâmetros:**
> - `BaseScores` - Map com ability scores base (chave: FName do atributo, valor: score)
> - `PointsRemaining` [OUT] - Pontos restantes após alocação (pode ser negativo se excedeu)
> - `MaxPoints` - Pontos máximos disponíveis (padrão: 27 para D&D 5e)
>
> **Retorno:** `true` se todos os scores estão no range válido [8, 15], `false` caso contrário
>
> ---
>
> **ValidatePointBuyAllocation()**
>
> ```cpp
> bool ValidatePointBuyAllocation(const TMap<FName, int32> &BaseScores,
>                                  int32 MaxPoints = 27);
> ```
>
> Valida alocação completa de Point Buy (range + pontos).
>
> **Retorno:** `true` se válido (range correto E exatamente MaxPoints gastos), `false` caso contrário

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Level Validation</summary>

> **ValidateTotalLevel()**
>
> ```cpp
> bool ValidateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels,
>                         int32 &TotalLevel,
>                         int32 MaxLevel = 20);
> ```
>
> Calcula nível total e valida se está dentro do range permitido.
>
> **Parâmetros:**
> - `ClassLevels` - Array com entradas de nível por classe
> - `TotalLevel` [OUT] - Nível total calculado
> - `MaxLevel` - Nível máximo permitido (padrão: 20 para D&D 5e)
>
> **Retorno:** `true` se nível total <= MaxLevel, `false` caso contrário
>
> ---
>
> **ValidateTotalLevelRange()**
>
> ```cpp
> bool ValidateTotalLevelRange(int32 Level, int32 MaxLevel = 20);
> ```
>
> Valida se um nível total está dentro do range permitido.
>
> **Retorno:** `true` se 1 <= Level <= MaxLevel, `false` caso contrário

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Ability Score Validation</summary>

> **ValidateAbilityScoreRange()**
>
> ```cpp
> bool ValidateAbilityScoreRange(int32 Score, int32 Min = 1, int32 Max = 30);
> ```
>
> Valida se um ability score está dentro do range permitido.
>
> **Retorno:** `true` se Min <= Score <= Max, `false` caso contrário
>
> ---
>
> **ValidateAbilityScoreChoices()**
>
> ```cpp
> bool ValidateAbilityScoreChoices(TArray<FName> &Choices,
>                                   const TArray<FName> &ValidNames,
>                                   int32 MaxChoices = 2);
> ```
>
> Valida escolhas de ability scores (ex: Variant Human). Remove duplicatas e valores inválidos.
>
> **Parâmetros:**
> - `Choices` [IN/OUT] - Array de escolhas (será modificado: duplicatas removidas, valores inválidos corrigidos)
> - `ValidNames` - Array com nomes válidos de ability scores
> - `MaxChoices` - Número máximo de escolhas permitidas (padrão: 2)
>
> **Retorno:** `true` se válido (1 <= Choices.Num() <= MaxChoices e todos os nomes são válidos), `false` caso contrário

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Selection Validation</summary>

> **ValidateFeatSelection()**
>
> ```cpp
> bool ValidateFeatSelection(FName &SelectedFeat,
>                             const TArray<FName> &AvailableFeats);
> ```
>
> Valida se uma seleção de feat está disponível.
>
> **Parâmetros:**
> - `SelectedFeat` [IN/OUT] - Feat selecionado (será resetado para NAME_None se inválido)
> - `AvailableFeats` - Array com feats disponíveis
>
> **Retorno:** `true` se SelectedFeat está em AvailableFeats ou é NAME_None, `false` caso contrário
>
> ---
>
> **ValidateSkillSelection()**
>
> ```cpp
> bool ValidateSkillSelection(FName &SelectedSkill,
>                             const TArray<FName> &ValidSkills);
> ```
>
> Valida se uma seleção de skill é válida.
>
> **Parâmetros:**
> - `SelectedSkill` [IN/OUT] - Skill selecionado (será resetado para NAME_None se inválido)
> - `ValidSkills` - Array com skills válidas
>
> **Retorno:** `true` se SelectedSkill está em ValidSkills ou é NAME_None, `false` caso contrário

</details>

**Uso:** Todas as funções são usadas em `CharacterSheetDataAssetValidators` e podem ser reutilizadas em widgets, combat components e outras mecânicas do jogo.

---

### CalculationHelpers

**Caminho:** `Source/MyProject2/Utils/CalculationHelpers.h`

Funções helper para cálculos de dados de personagem D&D 5e.

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Ability Score Calculations</summary>

> **CalculateAbilityModifier()**
>
> ```cpp
> int32 CalculateAbilityModifier(int32 Score);
> ```
>
> Calcula o modificador de ability score. Fórmula D&D 5e: `floor((Score - 10) / 2)`
>
> **Parâmetros:**
> - `Score` - Ability score (1-30)
>
> **Retorno:** Modificador calculado (pode ser negativo)
>
> ---
>
> **ResetFinalScoresToBase()**
>
> ```cpp
> void ResetFinalScoresToBase(int32 &FinalStrength, int32 &FinalDexterity,
>                             int32 &FinalConstitution, int32 &FinalIntelligence,
>                             int32 &FinalWisdom, int32 &FinalCharisma);
> ```
>
> Reseta Final Scores para valor base (8). Função pura que apenas reseta valores.
>
> **Parâmetros:**
> - `FinalStrength`, `FinalDexterity`, etc. [IN/OUT] - Scores finais (serão resetados para 8)
>
> **Uso:** Chamado pelo `FCharacterSheetCore` antes de aplicar motores.
>
> ---
>
> **IncrementFinalScoresWithPointBuy()**
>
> ```cpp
> void IncrementFinalScoresWithPointBuy(const TMap<FName, int32> &PointBuyAllocation,
>                                        int32 &FinalStrength, int32 &FinalDexterity, ...);
> ```
>
> Incrementa Final Scores com alocação de Point Buy. Motor independente: apenas incrementa, não reseta, não conhece bônus racial.
>
> **Parâmetros:**
> - `PointBuyAllocation` - Map com alocação de Point Buy (chave: FName do atributo, valor: 0-7)
> - `FinalStrength`, `FinalDexterity`, etc. [IN/OUT] - Scores finais (serão incrementados)
>
> **Uso:** Chamado pelo `FPointBuyMotor` para aplicar Point Buy.

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Proficiency Calculations</summary>

> **CalculateProficiencyBonus()**
>
> ```cpp
> int32 CalculateProficiencyBonus(int32 TotalLevel);
> ```
>
> Calcula o bônus de proficiência baseado no nível total. Fórmula D&D 5e: `1 + floor((TotalLevel - 1) / 4)`
>
> **Parâmetros:**
> - `TotalLevel` - Nível total do personagem (1-20)
>
> **Retorno:** Bônus de proficiência

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Feature Calculations</summary>

> **CalculateAvailableFeatures()**
>
> ```cpp
> TArray<FName> CalculateAvailableFeatures(const TArray<FClassLevelEntry> &ClassLevels,
>                                          UDataTable *ClassDataTable);
> ```
>
> Calcula features disponíveis baseado em níveis de classes.
>
> **Retorno:** Array com nomes de features disponíveis
>
> ---
>
> **CalculateProficiencies()**
>
> ```cpp
> TArray<FName> CalculateProficiencies(FName RaceName, FName SubraceName,
>                                      FName BackgroundName, FName SelectedSkill,
>                                      UDataTable *RaceDataTable, UDataTable *BackgroundDataTable);
> ```
>
> Calcula proficiências do personagem (background + Variant Human skill). Nota: Sem classes, proficiências vêm apenas de background e Variant Human.
>
> **Parâmetros:**
> - `RaceName` - Nome da raça selecionada (para Variant Human)
> - `SubraceName` - Nome da sub-raça selecionada (pode ser NAME_None)
> - `BackgroundName` - Nome do background selecionado
> - `SelectedSkill` - Skill escolhido para Variant Human (pode ser NAME_None)
> - `RaceDataTable` - Data Table de raças (pode ser nullptr)
> - `BackgroundDataTable` - Data Table de backgrounds (pode ser nullptr)
>
> **Retorno:** Array com nomes de proficiências
>
> ---
>
> **CalculateLanguages()**
>
> ```cpp
> TArray<FName> CalculateLanguages(FName RaceName, FName SubraceName,
>                                  FName BackgroundName, const TArray<FName> &SelectedLanguages,
>                                  UDataTable *RaceDataTable, UDataTable *BackgroundDataTable);
> ```
>
> Calcula idiomas finais do personagem (raça + background + escolhas do jogador + feats).
>
> **Parâmetros:**
> - `RaceName` - Nome da raça selecionada
> - `SubraceName` - Nome da sub-raça selecionada (pode ser NAME_None)
> - `BackgroundName` - Nome do background selecionado
> - `SelectedLanguages` - Array com idiomas escolhidos pelo jogador (quando há escolhas)
> - `RaceDataTable` - Data Table de raças (pode ser nullptr)
> - `BackgroundDataTable` - Data Table de backgrounds (pode ser nullptr)
>
> **Retorno:** Array com nomes de idiomas que o personagem fala

</details>

**Uso:** Usadas em `CharacterSheetDataAssetUpdaters` e podem ser reutilizadas em combat components para cálculos de dano, AC, etc.

---

### DataTableHelpers

**Caminho:** `Source/MyProject2/Utils/DataTableHelpers.h`

Funções helper para busca de rows em Data Tables com fallback manual.

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Race Data Table Helpers</summary>

> **FindRaceRow()**
>
> ```cpp
> FRaceDataRow* FindRaceRow(FName RaceName, UDataTable* RaceDataTable);
> ```
>
> Busca row de raça no Data Table. Tenta `FindRow` direto primeiro, depois busca manual O(n) como fallback.
>
> **Retorno:** Row encontrado, ou `nullptr` se não encontrado ou Data Table inválido
>
> ---
>
> **FindSubraceRow()**
>
> ```cpp
> FRaceDataRow* FindSubraceRow(FName SubraceName, UDataTable* RaceDataTable);
> ```
>
> Busca row de sub-raça no Data Table.

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Class Data Table Helpers</summary>

> **FindClassRow()**
>
> ```cpp
> FClassDataRow* FindClassRow(FName ClassName, UDataTable* ClassDataTable);
> ```
>
> Busca row de classe no Data Table.

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Feat Data Table Helpers</summary>

> **FindFeatRow()**
>
> ```cpp
> FFeatDataRow* FindFeatRow(FName FeatName, UDataTable* FeatDataTable);
> ```
>
> Busca row de feat no Data Table.

</details>

**Uso:** Centraliza lógica de busca que pode falhar com `FindRow` direto. Reutilizável em qualquer lugar que precise buscar rows em Data Tables.

---

### FormattingHelpers

**Caminho:** `Source/MyProject2/Utils/FormattingHelpers.h`

Funções helper para formatação de dados de personagem D&D 5e.

**FormatRaceDisplay()**
```cpp
FString FormatRaceDisplay(FName RaceName, FName SubraceName);
```
Formata display de raça com sub-raça (se houver). Ex: "Elf" ou "Elf (High Elf)"

**FormatProficienciesList()**
```cpp
FString FormatProficienciesList(const TArray<FName> &Proficiencies);
```
Formata lista de proficiências como string separada por vírgulas. Ex: "Athletics, Acrobatics, Stealth"

**FormatAbilityScores()**
```cpp
FString FormatAbilityScores(const TMap<FName, int32> &AbilityScores);
```
Formata ability scores para log/display. Retorna string formatada com todos os ability scores em ordem padrão.

**Uso:** Usadas em `CharacterDataComponent::LogCharacterSheet()` e podem ser reutilizadas em widgets de UI para formatação de display.

---

### CharacterSheetHelpers

**Caminho:** `Source/MyProject2/Utils/CharacterSheetHelpers.h`

Funções helper para leitura, filtragem e validação de Data Tables de D&D 5e.

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Race Data Table Helpers</summary>

> - `GetAllRaceNames()` - Retorna todos os nomes de raças (filtra apenas raças base, não sub-raças)
> - `GetAvailableSubraces()` - Retorna todas as sub-raças disponíveis para uma raça específica

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Class Data Table Helpers</summary>

> - `GetAllClassNames()` - Retorna todos os nomes de classes
> - `GetAvailableSubclasses()` - Retorna todas as subclasses disponíveis para uma classe
> - `CanSelectSubclass()` - Verifica se pode selecionar subclasse no nível dado
> - `GetFeaturesAtLevel()` - Retorna features desbloqueadas em um nível específico

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Background Data Table Helpers</summary>

> - `GetAllBackgroundNames()` - Retorna todos os nomes de backgrounds

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Feat Data Table Helpers</summary>

> - `GetAvailableFeats()` - Retorna feats disponíveis baseado em pré-requisitos (nível e ability scores)
> - `CanTakeFeatAtLevel()` - Verifica se pode escolher feat no nível especificado
> - `ValidateAbilityScorePrerequisite()` - Parseia e valida pré-requisito de ability score
> - `MeetsFeatPrerequisites()` - Verifica se personagem atende aos pré-requisitos de um feat

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Ability Score Helpers</summary>

> - `GetAbilityScoreNames()` - Retorna array estático com os 6 nomes de ability scores padrão D&D 5e

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Skill Helpers</summary>

> - `GetSkillNames()` - Retorna array estático com os 18 nomes de skills padrão D&D 5e

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Point Buy System Helpers</summary>

> - `CalculatePointBuyCost()` - Calcula custo em pontos do Point Buy para um score específico
> - `CalculateTotalPointBuyCost()` - Calcula custo total do Point Buy para todos os scores

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Level Calculation Helpers</summary>

> - `CalculateTotalLevel()` - Calcula nível total somando todos os níveis de classes

</details>

> **Uso:** Usadas em `CharacterSheetDataAsset` para funções `GetOptions` e podem ser reutilizadas em widgets e outras mecânicas.

</details>

---

## Integração com Refatorações

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Refatorações e Melhorias</b></summary>

> Informações sobre refatorações realizadas e seus benefícios:
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📈 Benefícios das Refatorações</summary>

> Todas as funções helper foram extraídas de código acoplado seguindo princípios de Clean Code:
>
> **Antes:** Validações e cálculos acoplados a `CharacterSheetDataAsset`
>
> **Depois:** Funções puras em namespaces reutilizáveis em `Utils/`
>
> **Benefícios:**
> - ✅ Reutilizáveis em widgets, combat components e outras mecânicas
> - ✅ Testáveis isoladamente
> - ✅ Funções < 50 linhas (Clean Code)
> - ✅ Sem dependência de estado interno
> - ✅ Preparadas para uso em runtime e editor

</details>

</details>

---

## Preparação para Combat Components

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Integração com Sistema de Combate</b></summary>

> O `CharacterDataComponent` está preparado para uso em combat components:

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
