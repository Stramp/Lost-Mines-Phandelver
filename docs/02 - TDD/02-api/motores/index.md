# Motores de Criação

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motores Desacoplados para Criação de Personagem</b></summary>

> Sistema modular com motores desacoplados para cálculo de ability scores finais. Arquitetura genérica que funciona tanto no Data Asset quanto em Widgets.

</details>

## FCharacterSheetCore

**Caminho:** `Source/MyProject2/CreateSheet/Core/CharacterSheetCore.h`

**Responsabilidade:** Orquestrador genérico que coordena todos os motores de criação de personagem.

**Método Principal:**

#### RecalculateFinalScores()
```cpp
static void RecalculateFinalScores(FCharacterSheetData &Data, FPointBuyResult *OutPointBuyResult = nullptr);
```

- **Parâmetros:**
  - `Data` - Estrutura genérica com dados de entrada e referências de saída
  - `OutPointBuyResult` - [OPCIONAL] Resultado do motor de Point Buy (feedback e ajustes)
- **Descrição:** Reseta scores para base (8) e aplica cada motor sequencialmente
- **Fórmula:** `FinalScore = 8 (base) + RacialBonus + PointBuyAllocation`
- **Fluxo:**
  1. Reseta todos os Final Scores para 8 (base)
  2. Aplica `FRaceBonusMotor::ApplyRacialBonuses()`
  3. Aplica `FPointBuyMotor::ApplyPointBuy()`

### FCharacterSheetData

**Caminho:** `Source/MyProject2/CreateSheet/Core/CharacterSheetData.h`

**Responsabilidade:** Estrutura genérica de dados que permite o Core funcionar em diferentes contextos.

**Campos Principais:**

**Input (Dados de Entrada):**
- `PointBuyStrength`, `PointBuyDexterity`, etc. - Alocação de Point Buy (0-7 cada)
- `SelectedRace`, `SelectedSubrace` - Raça e sub-raça selecionadas
- `CustomAbilityScoreChoices` - Escolhas customizadas (Variant Human)
- `RaceDataTable` - Data Table de raças

**Output (Referências de Saída):**
- `FinalStrength`, `FinalDexterity`, etc. - Ponteiros para Final Scores (serão modificados)

**Características:**
- Struct C++ normal (não USTRUCT) - contém ponteiros
- Permite reutilização: mesmo Core funciona no Data Asset e em Widgets
- Princípio: "Program to an interface, not an implementation"

---

## FRaceBonusMotor

**Caminho:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusMotor.h`

**Responsabilidade:** Calcular e aplicar bônus raciais nos Final Scores.

**Método Principal:**

#### ApplyRacialBonuses()
```cpp
static void ApplyRacialBonuses(FCharacterSheetData &Data);
```

- **Parâmetros:**
  - `Data` - Estrutura genérica com dados de raça e referências de Final Scores
- **Descrição:** Calcula bônus de raça base, sub-raça e Variant Human, e aplica nos Final Scores
- **Fluxo:**
  1. Busca RaceRow e SubraceRow usando `DataTableHelpers`
  2. Calcula bônus usando `FRaceBonusHelpers::CalculateRacialBonuses()`
  3. Incrementa Final Scores usando `FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses()`

**Características:**
- Motor independente: não conhece Point Buy, apenas aplica bônus raciais
- Suporta Variant Human com escolhas customizadas
- Usa helpers puros para cálculos

### FRaceBonusHelpers

**Caminho:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusHelpers.h`

**Responsabilidade:** Funções helper puras para cálculo de bônus raciais.

**Métodos:**

#### CalculateRacialBonuses()
```cpp
static void CalculateRacialBonuses(const FRaceDataRow *RaceRow, const FRaceDataRow *SubraceRow,
const TArray<FName> &CustomChoices, TMap<FName, int32> &RacialBonuses);
```
- Calcula bônus raciais de ability scores (raça base + sub-raça + Variant Human)

#### IncrementFinalScoresWithRacialBonuses()
```cpp
static void IncrementFinalScoresWithRacialBonuses(const TMap<FName, int32> &RacialBonuses,
int32 &FinalStrength, int32 &FinalDexterity, ...);
```
- Incrementa Final Scores com bônus raciais calculados

---

## FPointBuyMotor

**Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyMotor.h`

**Responsabilidade:** Aplicar alocação de Point Buy nos Final Scores com validação automática.

**Método Principal:**

#### ApplyPointBuy()
```cpp
static FPointBuyResult ApplyPointBuy(FCharacterSheetData &Data);
```

- **Parâmetros:**
  - `Data` - Estrutura genérica com dados de Point Buy e referências de Final Scores
- **Retorno:** `FPointBuyResult` com feedback sobre validação e ajustes realizados
- **Descrição:** Valida se não excede 27 pontos e ajusta automaticamente se necessário
- **Fluxo:**
  1. Converte dados de entrada para `TMap<FName, int32>`
  2. Calcula custo total usando `CharacterSheetHelpers::CalculateTotalPointBuyCost()`
  3. Se exceder 27 pontos, ajusta usando `AdjustPointBuyAllocation()`
  4. Incrementa Final Scores usando `CalculationHelpers::IncrementFinalScoresWithPointBuy()`
  5. Retorna `FPointBuyResult` com feedback

**Características:**
- Motor independente: não conhece bônus raciais, apenas aplica Point Buy
- Validação automática: ajusta se exceder 27 pontos
- Ajuste automático: reduz do final da fila (Charisma → Wisdom → ... → Strength)

### FPointBuyValidator

**Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyValidator.h`

**Responsabilidade:** Validar alocação de Point Buy.

**Métodos:**

#### ValidatePointBuy()
```cpp
static bool ValidatePointBuy(const TMap<FName, int32> &PointBuyAllocation, int32 MaxPoints = 27);
```
- Valida se alocação não excede MaxPoints e se todos os scores estão no range [8, 15]

### FPointBuyResult

**Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyResult.h`

**Responsabilidade:** Struct de feedback sobre aplicação de Point Buy.

**Campos:**
- `bWasAdjusted` - Se o motor teve que ajustar a alocação (excedeu 27 pontos)
- `AdjustedAllocation` - Alocação ajustada (pode ser diferente da original)
- `PointsRemaining` - Pontos restantes após alocação
- `FeedbackMessage` - Mensagem de feedback para o caller ajustar a UI

**Uso:** Retornado por `FPointBuyMotor::ApplyPointBuy()` para informar o caller sobre ajustes realizados.

---

## FMulticlassMotor

**Caminho:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassMotor.h`

**Responsabilidade:** Validar e aplicar regras de multiclassing D&D 5e.

**Métodos Principais:**

#### GetAvailableClasses()
```cpp
static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable,
int32 FinalStrength, int32 FinalDexterity,
int32 FinalConstitution, int32 FinalIntelligence,
int32 FinalWisdom, int32 FinalCharisma);
```
- **Parâmetros:**
  - `ClassDataTable` - Data Table de classes (pode ser nullptr)
  - `FinalStrength`, `FinalDexterity`, etc. - Atributos finais do personagem
- **Retorno:** Array com nomes de classes disponíveis (que atendem requisitos de atributo)
- **Descrição:** Filtra classes que o personagem pode pegar baseado nos atributos finais
- **Suporte para requisitos complexos:** Ex: "STR/13|DEX/13" (STR ou DEX >= 13)

#### ProcessLevelChange()
```cpp
static void ProcessLevelChange(FName ClassName, int32 LevelInClass, const UDataTable *ClassDataTable);
```
- **Parâmetros:**
  - `ClassName` - Nome da classe que teve o nível alterado
  - `LevelInClass` - Novo nível na classe (1-20)
  - `ClassDataTable` - Data Table de classes para buscar informações
- **Descrição:** Processa mudança de nível em uma classe específica, busca informações da classe na tabela e loga features ganhas no nível

**Características:**
- Motor independente: não conhece outros motores, apenas aplica regras de multiclasse
- Genérico: recebe dados puros, não objetos concretos
- Validação automática de requisitos de atributo para multiclassing D&D 5e

### FMulticlassHelpers

**Caminho:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassHelpers.h`

**Responsabilidade:** Funções helper para processamento de multiclassing.

**Métodos:**

#### GetAvailableClassWithTagRequirements()
```cpp
static TArray<FName> GetAvailableClassWithTagRequirements(const UDataTable *ClassDataTable,
const TArray<int32> &CharacterAttributes);
```
- **Descrição:** Busca classes disponíveis baseado em requisitos de atributo
- **Suporte para parsing de requisitos:** Ex: "STR/13|DEX/13" (STR ou DEX >= 13)

#### AdjustProgressionArraySize()
```cpp
static void AdjustProgressionArraySize(TArray<FClassLevelEntry> &Progression, int32 LevelInClass);
```
- **Descrição:** Ajusta tamanho do array de progressão baseado no nível da classe

---

## 📊 Fluxo dos Motores

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Diagrama de Orquestração</b></summary>

> ```mermaid
> graph TD
>     Start([RecalculateFinalScores]) --> Reset[1. Reset Final Scores<br/>para 8 base]
>     Reset --> RaceMotor[2. RaceBonusMotor<br/>ApplyRacialBonuses]
>     RaceMotor --> PointBuyMotor[3. PointBuyMotor<br/>ApplyPointBuy]
>     PointBuyMotor --> Validate{Point Buy<br/>Válido?}
>     Validate -->|Não| Adjust[Ajustar Alocação]
>     Adjust --> PointBuyMotor
>     Validate -->|Sim| End([Final Scores<br/>Calculados])
>
>     style Start fill:#c8e6c9
>     style End fill:#c8e6c9
>     style RaceMotor fill:#fff3e0
>     style PointBuyMotor fill:#e3f2fd
>     style Validate fill:#fff3e0
> ```
>
> **📖 [Ver documentação completa do Core](../../01-arquitetura/createsheet.md)**

</details>

---

## 📖 Motores Disponíveis

- **[PointBuyMotor](point-buy-motor.md)** - Motor de Point Buy para criação de personagem
- **[MulticlassMotor](multiclass-motor.md)** - Motor de Multiclasse para validação e aplicação de regras
- **[RaceBonusMotor](race-bonus-motor.md)** - Motor de Bônus Raciais para aplicação de bônus

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Componentes](../componentes/index.md)** - Componentes que usam os motores
> - **[Helpers](../helpers/index.md)** - Funções helper usadas pelos motores
> - **[Índice da API](../index.md)** - Organização da API

</details>
