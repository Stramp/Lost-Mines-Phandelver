# CalculationHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Cálculo</b></summary>

> **Caminho:** `Source/MyProject2/Utils/CalculationHelpers.h`
>
> **Responsabilidade:** Cálculos de dados de personagem D&D 5e.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Todas as funções < 50 linhas
> - Status de Testes: ✅ 28 testes implementados (`CalculationHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace CalculationHelpers
{
    // Ability Score Calculations
    int32 CalculateAbilityModifier(int32 Score);
    void ResetFinalScoresToBase(int32 &FinalStrength, ...);
    void IncrementFinalScoresWithPointBuy(const TMap<FName, int32> &PointBuyAllocation, ...);

    // Proficiency Calculations
    int32 CalculateProficiencyBonus(int32 TotalLevel);
    TArray<FName> CollectProficienciesFromBackgroundAndVariantHuman(...);

    // Language Calculations
    TArray<FName> CollectLanguagesFromAllSources(...);

    // Feature Calculations
    TArray<FName> CalculateAvailableFeatures(...);

    // Proficiency Calculations
    TArray<FName> CalculateProficiencies(...);
}
```

---

## 🔧 Funções Principais

### CalculateAbilityModifier()

Calcula o modificador de ability score (Ability Modifier).

**Assinatura:**

```cpp
int32 CalculateAbilityModifier(int32 Score);
```

**Parâmetros:**

- `Score` - Ability score (MIN_ABILITY_SCORE - MAX_ABILITY_SCORE)

**Retorno:**

- `int32` - Modificador calculado (pode ser negativo)

**Fórmula D&D 5e:**

```
Modifier = floor((Score - 10) / 2)
```

**Exemplo:**

```cpp
int32 Modifier = CalculationHelpers::CalculateAbilityModifier(15);
// Resultado: Modifier = floor((15 - 10) / 2) = floor(5 / 2) = 2

int32 NegativeModifier = CalculationHelpers::CalculateAbilityModifier(8);
// Resultado: NegativeModifier = floor((8 - 10) / 2) = floor(-2 / 2) = -1
```

---

### CalculateProficiencyBonus()

Calcula o bônus de proficiência baseado no nível total.

**Assinatura:**

```cpp
int32 CalculateProficiencyBonus(int32 TotalLevel);
```

**Parâmetros:**

- `TotalLevel` - Nível total do personagem (MIN_LEVEL - MAX_LEVEL)

**Retorno:**

- `int32` - Bônus de proficiência

**Fórmula D&D 5e:**

```
Proficiency Bonus = 2 + floor((TotalLevel - 1) / 4)
```

**Tabela de Referência:**

| Nível | Bônus |
|-------|-------|
| 1-4   | +2    |
| 5-8   | +3    |
| 9-12  | +4    |
| 13-16 | +5    |
| 17-20 | +6    |

**Exemplo:**

```cpp
int32 ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(5);
// Resultado: ProficiencyBonus = 2 + floor((5 - 1) / 4) = 2 + 1 = 3
```

---

### ResetFinalScoresToBase()

Reseta Final Scores para valor base (BASE_ABILITY_SCORE = 8).

**Assinatura:**

```cpp
void ResetFinalScoresToBase(int32 &FinalStrength,
                            int32 &FinalDexterity,
                            int32 &FinalConstitution,
                            int32 &FinalIntelligence,
                            int32 &FinalWisdom,
                            int32 &FinalCharisma);
```

**Parâmetros:**

- `FinalStrength` [IN/OUT] - Score final de Strength
- `FinalDexterity` [IN/OUT] - Score final de Dexterity
- `FinalConstitution` [IN/OUT] - Score final de Constitution
- `FinalIntelligence` [IN/OUT] - Score final de Intelligence
- `FinalWisdom` [IN/OUT] - Score final de Wisdom
- `FinalCharisma` [IN/OUT] - Score final de Charisma

**Descrição:**

Função pura que apenas reseta valores para base (8). Usada no início do cálculo de ability scores finais.

**Exemplo:**

```cpp
int32 FinalStrength = 15;
int32 FinalDexterity = 13;
// ... outros scores ...

// Resetar para base
CalculationHelpers::ResetFinalScoresToBase(
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);

// Resultado: Todos os scores agora são 8
```

---

### IncrementFinalScoresWithPointBuy()

Incrementa Final Scores com alocação de Point Buy.

**Assinatura:**

```cpp
void IncrementFinalScoresWithPointBuy(const TMap<FName, int32> &PointBuyAllocation,
                                      int32 &FinalStrength,
                                      int32 &FinalDexterity,
                                      int32 &FinalConstitution,
                                      int32 &FinalIntelligence,
                                      int32 &FinalWisdom,
                                      int32 &FinalCharisma);
```

**Parâmetros:**

- `PointBuyAllocation` - Map com alocação de Point Buy (chave: FName do atributo, valor: 0-7)
- `FinalStrength` [IN/OUT] - Score final de Strength
- `FinalDexterity` [IN/OUT] - Score final de Dexterity
- `FinalConstitution` [IN/OUT] - Score final de Constitution
- `FinalIntelligence` [IN/OUT] - Score final de Intelligence
- `FinalWisdom` [IN/OUT] - Score final de Wisdom
- `FinalCharisma` [IN/OUT] - Score final de Charisma

**Descrição:**

Motor independente que apenas incrementa, não reseta, não conhece bônus racial. Usado pelo `FPointBuyMotor`.

**Exemplo:**

```cpp
// Final Scores já resetados e bônus raciais aplicados
int32 FinalStrength = 10;  // Base 8 + Racial +2
int32 FinalDexterity = 8;
// ... outros scores ...

// Alocação de Point Buy
TMap<FName, int32> PointBuyAllocation;
PointBuyAllocation.Add(TEXT("Strength"), 7);  // 7 pontos

// Incrementar com Point Buy
CalculationHelpers::IncrementFinalScoresWithPointBuy(
    PointBuyAllocation,
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);

// Resultado:
// FinalStrength = 10 + 7 = 17
// FinalDexterity = 8 (sem mudança)
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Calcular Modificador para Ataque

```cpp
// Personagem com Strength 16
int32 Strength = 16;
int32 Modifier = CalculationHelpers::CalculateAbilityModifier(Strength);
// Modifier = 3

// Ataque com arma corpo a corpo
int32 AttackRoll = RollD20() + Modifier + ProficiencyBonus;
```

### Exemplo 2: Calcular Bônus de Proficiência para Skill Check

```cpp
// Personagem nível 5
int32 TotalLevel = 5;
int32 ProficiencyBonus = CalculationHelpers::CalculateProficiencyBonus(TotalLevel);
// ProficiencyBonus = 3

// Skill check de Athletics (proficiente)
int32 SkillModifier = StrengthModifier + ProficiencyBonus;
int32 SkillRoll = RollD20() + SkillModifier;
```

### Exemplo 3: Fluxo Completo de Cálculo de Ability Scores

```cpp
// 1. Resetar para base
int32 FinalStrength = 15;  // Valor anterior
int32 FinalDexterity = 13;
// ... outros scores ...

CalculationHelpers::ResetFinalScoresToBase(
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);
// Agora todos são 8

// 2. Aplicar bônus raciais (já aplicados por FRaceBonusMotor)
// FinalStrength = 8 + 2 = 10 (exemplo)

// 3. Aplicar Point Buy
TMap<FName, int32> PointBuyAllocation;
PointBuyAllocation.Add(TEXT("Strength"), 7);

CalculationHelpers::IncrementFinalScoresWithPointBuy(
    PointBuyAllocation,
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);
// FinalStrength = 10 + 7 = 17

// 4. Calcular modificador
int32 StrengthModifier = CalculationHelpers::CalculateAbilityModifier(FinalStrength);
// StrengthModifier = 3
```

---

## 🧪 Testes

**Status:** ✅ 28 testes implementados (`CalculationHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ Ability Modifier Calculations (múltiplos casos)
- ✅ Proficiency Bonus Calculations (todos os níveis)
- ✅ Final Scores Reset (validação de reset)
- ✅ Point Buy Increment (validação de incremento)

---

## 🔗 Integração com Outros Sistemas

### Uso em Motores

Estas funções são usadas pelos motores:

- `FPointBuyMotor` - Usa `IncrementFinalScoresWithPointBuy()`
- `CharacterSheetDataAssetUpdaters` - Usa todas as funções de cálculo

### Uso em Componentes

- `CharacterDataComponent` - Usa `CalculateAbilityModifier()` e `CalculateProficiencyBonus()`
- Sistemas de combate - Usam modificadores para cálculos de ataque/dano

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[GDD: Sistemas de Personagem - Ability Scores](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#-atributos-ability-scores)** - Regras de ability scores D&D 5e
- **[TDD: Algoritmos de Criação](../../../04-regras-dnd/criacao/index.md)** - Algoritmos técnicos de criação

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (fórmulas D&D 5e) e PORQUÊ (balanceamento)
- **TDD:** Define COMO (funções helper, implementação técnica)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Motores - PointBuyMotor](../motores/point-buy-motor.md)** - Motor que usa estas funções
> - **[Helpers - ValidationHelpers](validation-helpers.md)** - Validação de ability scores
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← ComponentHelpers](component-helpers.md) | [→ ValidationHelpers](validation-helpers.md) | [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
