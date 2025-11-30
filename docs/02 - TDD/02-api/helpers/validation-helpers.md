# ValidationHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Validação</b></summary>

> **Caminho:** `Source/MyProject2/Utils/ValidationHelpers.h`
>
> **Responsabilidade:** Validação de dados de personagem D&D 5e.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Todas as funções < 50 linhas
> - Status de Testes: ✅ 35 testes implementados (`ValidationHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace ValidationHelpers
{
    // Point Buy Validation
    bool ValidatePointBuy(const TMap<FName, int32> &BaseScores, int32 &PointsRemaining, int32 MaxPoints = 27);
    bool ValidatePointBuyAllocation(const TMap<FName, int32> &BaseScores, int32 MaxPoints = 27);

    // Level Validation
    bool ValidateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels, int32 &TotalLevel, int32 MaxLevel = 20);
    bool ValidateTotalLevelRange(int32 Level, int32 MaxLevel = 20);

    // Ability Score Validation
    bool ValidateAbilityScoreRange(int32 Score, int32 Min = 1, int32 Max = 30);
    bool ValidateAbilityScoreChoicesPure(const TArray<FName> &Choices, ...);

    // Selection Validation
    bool ValidateFeatSelectionPure(FName SelectedFeat, const TArray<FName> &AvailableFeats);
    bool ValidateSkillSelectionPure(FName SelectedSkill, const TArray<FName> &ValidSkills);
}
```

---

## 🔧 Funções Principais

### ValidatePointBuy()

Valida alocação de Point Buy e calcula pontos restantes.

**Assinatura:**

```cpp
bool ValidatePointBuy(const TMap<FName, int32> &BaseScores,
                      int32 &PointsRemaining,
                      int32 MaxPoints = 27);
```

**Parâmetros:**

- `BaseScores` - Map com ability scores base (chave: FName do atributo, valor: score)
- `PointsRemaining` [OUT] - Pontos restantes após alocação (pode ser negativo se excedeu)
- `MaxPoints` - Pontos máximos disponíveis (padrão: 27)

**Retorno:**

- `bool` - true se todos os scores estão no range válido [8, 15], false caso contrário

**Exemplo:**

```cpp
TMap<FName, int32> BaseScores;
BaseScores.Add(TEXT("Strength"), 15);
BaseScores.Add(TEXT("Dexterity"), 13);
BaseScores.Add(TEXT("Constitution"), 13);
BaseScores.Add(TEXT("Intelligence"), 11);
BaseScores.Add(TEXT("Wisdom"), 11);
BaseScores.Add(TEXT("Charisma"), 10);

int32 PointsRemaining = 0;
bool bIsValid = ValidationHelpers::ValidatePointBuy(BaseScores, PointsRemaining, 27);

if (bIsValid && PointsRemaining == 0)
{
    // Alocação válida e exatamente 27 pontos gastos
    UE_LOG(LogTemp, Warning, TEXT("Point Buy válido!"));
}
else if (bIsValid && PointsRemaining > 0)
{
    // Alocação válida mas ainda há pontos disponíveis
    UE_LOG(LogTemp, Warning, TEXT("Point Buy válido, mas %d pontos restantes"), PointsRemaining);
}
else
{
    // Alocação inválida (excedeu 27 pontos ou scores fora do range)
    UE_LOG(LogTemp, Error, TEXT("Point Buy inválido! Pontos restantes: %d"), PointsRemaining);
}
```

---

### ValidateAbilityScoreRange()

Valida se um ability score está dentro do range permitido.

**Assinatura:**

```cpp
bool ValidateAbilityScoreRange(int32 Score, int32 Min = 1, int32 Max = 30);
```

**Parâmetros:**

- `Score` - Ability score a validar
- `Min` - Valor mínimo permitido (padrão: 1)
- `Max` - Valor máximo permitido (padrão: 30)

**Retorno:**

- `bool` - true se Min <= Score <= Max, false caso contrário

**Exemplo:**

```cpp
int32 Strength = 15;
bool bIsValid = ValidationHelpers::ValidateAbilityScoreRange(Strength, 1, 30);
// Resultado: bIsValid = true (15 está entre 1 e 30)

int32 InvalidScore = 35;
bool bIsInvalid = ValidationHelpers::ValidateAbilityScoreRange(InvalidScore, 1, 30);
// Resultado: bIsInvalid = false (35 > 30)
```

---

### ValidateTotalLevel()

Calcula nível total e valida se está dentro do range permitido.

**Assinatura:**

```cpp
bool ValidateTotalLevel(const TArray<FClassLevelEntry> &ClassLevels,
                        int32 &TotalLevel,
                        int32 MaxLevel = 20);
```

**Parâmetros:**

- `ClassLevels` - Array com entradas de nível por classe
- `TotalLevel` [OUT] - Nível total calculado
- `MaxLevel` - Nível máximo permitido (padrão: 20)

**Retorno:**

- `bool` - true se nível total <= MaxLevel, false caso contrário

**Exemplo:**

```cpp
TArray<FClassLevelEntry> ClassLevels;
FClassLevelEntry FighterEntry;
FighterEntry.ClassName = TEXT("Fighter");
FighterEntry.LevelInClass = 3;
ClassLevels.Add(FighterEntry);

FClassLevelEntry RangerEntry;
RangerEntry.ClassName = TEXT("Ranger");
RangerEntry.LevelInClass = 2;
ClassLevels.Add(RangerEntry);

int32 TotalLevel = 0;
bool bIsValid = ValidationHelpers::ValidateTotalLevel(ClassLevels, TotalLevel, 20);

if (bIsValid)
{
    // TotalLevel = 5 (3 + 2), válido
    UE_LOG(LogTemp, Warning, TEXT("Nível total válido: %d"), TotalLevel);
}
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Validar Point Buy Antes de Aplicar

```cpp
// Alocação de Point Buy do jogador
TMap<FName, int32> PointBuyAllocation;
PointBuyAllocation.Add(TEXT("Strength"), 7);      // 9 pontos
PointBuyAllocation.Add(TEXT("Dexterity"), 5);      // 5 pontos
PointBuyAllocation.Add(TEXT("Constitution"), 5);  // 5 pontos
PointBuyAllocation.Add(TEXT("Intelligence"), 3);  // 3 pontos
PointBuyAllocation.Add(TEXT("Wisdom"), 3);        // 3 pontos
PointBuyAllocation.Add(TEXT("Charisma"), 2);      // 2 pontos
// Total: 27 pontos

// Validar antes de aplicar
int32 PointsRemaining = 0;
bool bIsValid = ValidationHelpers::ValidatePointBuy(PointBuyAllocation, PointsRemaining, 27);

if (bIsValid && PointsRemaining == 0)
{
    // Aplicar Point Buy (agora seguro)
    FPointBuyMotor::ApplyPointBuy(PointBuyAllocation, ...);
}
else
{
    // Mostrar erro ao jogador
    ShowErrorToPlayer(TEXT("Alocação de Point Buy inválida!"));
}
```

### Exemplo 2: Validar Ability Score em Múltiplos Pontos

```cpp
// Validar todos os ability scores
int32 Strength = 15;
int32 Dexterity = 13;
int32 Constitution = 14;
int32 Intelligence = 12;
int32 Wisdom = 10;
int32 Charisma = 8;

bool bAllValid =
    ValidationHelpers::ValidateAbilityScoreRange(Strength) &&
    ValidationHelpers::ValidateAbilityScoreRange(Dexterity) &&
    ValidationHelpers::ValidateAbilityScoreRange(Constitution) &&
    ValidationHelpers::ValidateAbilityScoreRange(Intelligence) &&
    ValidationHelpers::ValidateAbilityScoreRange(Wisdom) &&
    ValidationHelpers::ValidateAbilityScoreRange(Charisma);

if (bAllValid)
{
    // Todos os scores são válidos
    UE_LOG(LogTemp, Warning, TEXT("Todos os ability scores são válidos"));
}
```

---

## 🧪 Testes

**Status:** ✅ 35 testes implementados (`ValidationHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ Point Buy Validation (múltiplos casos: válido, inválido, excedido)
- ✅ Level Validation (todos os níveis, multiclasse)
- ✅ Ability Score Range Validation (valores válidos e inválidos)
- ✅ Selection Validation (feats, skills)

---

## 🔗 Integração com Outros Sistemas

### Uso em Motores

Estas funções são usadas pelos motores:

- `FPointBuyMotor` - Usa `ValidatePointBuy()` antes de aplicar
- `CharacterSheetDataAssetValidators` - Usa todas as funções de validação

### Uso em Componentes

- `CharacterSheetDataAsset` - Valida dados antes de aplicar mudanças
- Widgets de UI - Valida entrada do usuário antes de processar

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[GDD: Sistemas de Personagem - Point Buy](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#point-buy-system)** - Regras de Point Buy D&D 5e
- **[TDD: Point Buy Algorithm](../../../04-regras-dnd/criacao/point-buy-algorithm.md)** - Algoritmo técnico de validação

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (27 pontos, range 8-15) e PORQUÊ (balanceamento D&D 5e)
- **TDD:** Define COMO (funções helper, implementação técnica)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Motores - PointBuyMotor](../motores/point-buy-motor.md)** - Motor que usa estas funções
> - **[Helpers - CalculationHelpers](calculation-helpers.md)** - Cálculos relacionados
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← CalculationHelpers](calculation-helpers.md) | [→ DataTableHelpers](data-table-helpers.md) | [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
