# PointBuyMotor

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motor de Point Buy</b></summary>

> **Caminho:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyMotor.h`
>
> **Responsabilidade:** Aplicar alocação de Point Buy nos Final Scores.
>
> **Características:**
>
> - Motor puro: apenas aplica, sem validação, logging, conversão ou formatação
> - Motor independente: não conhece bônus raciais, apenas aplica Point Buy
> - Única responsabilidade: aplicar alocação de Point Buy nos Final Scores

</details>

---

## 📐 Estrutura da Classe

```cpp
class MYPROJECT2_API FPointBuyMotor
{
public:
    static void ApplyPointBuy(const TMap<FName, int32>& PointBuyAllocation,
                              int32& FinalStrength,
                              int32& FinalDexterity,
                              int32& FinalConstitution,
                              int32& FinalIntelligence,
                              int32& FinalWisdom,
                              int32& FinalCharisma);
};
```

---

## 🔧 Métodos Públicos

### ApplyPointBuy()

Aplica alocação de Point Buy nos Final Scores.

**Assinatura:**

```cpp
static void ApplyPointBuy(const TMap<FName, int32>& PointBuyAllocation,
                          int32& FinalStrength,
                          int32& FinalDexterity,
                          int32& FinalConstitution,
                          int32& FinalIntelligence,
                          int32& FinalWisdom,
                          int32& FinalCharisma);
```

**Parâmetros:**

- `PointBuyAllocation` - Alocação de Point Buy já convertida (TMap<FName, int32>)
  - Chave: Nome do atributo (ex: "Strength", "Dexterity")
  - Valor: Alocação de Point Buy (0-7)
- `FinalStrength` [OUT] - Referência para Final Strength (será modificado)
- `FinalDexterity` [OUT] - Referência para Final Dexterity (será modificado)
- `FinalConstitution` [OUT] - Referência para Final Constitution (será modificado)
- `FinalIntelligence` [OUT] - Referência para Final Intelligence (será modificado)
- `FinalWisdom` [OUT] - Referência para Final Wisdom (será modificado)
- `FinalCharisma` [OUT] - Referência para Final Charisma (será modificado)

**Descrição:**

Motor puro que apenas aplica alocação de Point Buy nos Final Scores. Assume que:

- Dados são válidos e já convertidos
- Alocação não excede 27 pontos (validação deve ser feita antes)
- Final Scores já foram resetados para base (8) e bônus raciais já foram aplicados

**Comportamento:**

- Incrementa cada Final Score com a alocação correspondente de Point Buy
- Não valida, não ajusta, não loga
- Motor independente: não conhece bônus raciais ou outros sistemas

**Pré-condições:**

- `PointBuyAllocation` contém apenas chaves válidas de atributos
- Valores estão no range [0, 7]
- Final Scores já foram resetados e bônus raciais já foram aplicados

**Pós-condições:**

- Final Scores são incrementados com alocação de Point Buy

---

## 💡 Exemplos de Uso

### Exemplo 1: Aplicar Point Buy Básico

```cpp
// Setup: Final Scores já resetados (8) e bônus raciais já aplicados
int32 FinalStrength = 10;      // Base 8 + Racial +2
int32 FinalDexterity = 8;       // Base 8 + Racial 0
int32 FinalConstitution = 8;    // Base 8 + Racial 0
int32 FinalIntelligence = 8;    // Base 8 + Racial 0
int32 FinalWisdom = 8;          // Base 8 + Racial 0
int32 FinalCharisma = 8;        // Base 8 + Racial 0

// Alocação de Point Buy (7 pontos para Strength)
TMap<FName, int32> PointBuyAllocation;
PointBuyAllocation.Add(TEXT("Strength"), 7);  // 7 pontos = score 15

// Aplicar Point Buy
FPointBuyMotor::ApplyPointBuy(PointBuyAllocation,
                               FinalStrength, FinalDexterity, FinalConstitution,
                               FinalIntelligence, FinalWisdom, FinalCharisma);

// Resultado:
// FinalStrength = 10 + 7 = 17
// FinalDexterity = 8 (sem mudança)
// FinalConstitution = 8 (sem mudança)
// FinalIntelligence = 8 (sem mudança)
// FinalWisdom = 8 (sem mudança)
// FinalCharisma = 8 (sem mudança)
```

### Exemplo 2: Aplicar Point Buy Completo (27 pontos)

```cpp
// Setup: Final Scores já resetados e bônus raciais aplicados
int32 FinalStrength = 8;
int32 FinalDexterity = 8;
int32 FinalConstitution = 8;
int32 FinalIntelligence = 8;
int32 FinalWisdom = 8;
int32 FinalCharisma = 8;

// Alocação completa de 27 pontos
TMap<FName, int32> PointBuyAllocation;
PointBuyAllocation.Add(TEXT("Strength"), 7);      // 9 pontos
PointBuyAllocation.Add(TEXT("Dexterity"), 5);     // 5 pontos
PointBuyAllocation.Add(TEXT("Constitution"), 5);  // 5 pontos
PointBuyAllocation.Add(TEXT("Intelligence"), 3);  // 3 pontos
PointBuyAllocation.Add(TEXT("Wisdom"), 3);        // 3 pontos
PointBuyAllocation.Add(TEXT("Charisma"), 2);      // 2 pontos
// Total: 27 pontos

// Aplicar Point Buy
FPointBuyMotor::ApplyPointBuy(PointBuyAllocation,
                               FinalStrength, FinalDexterity, FinalConstitution,
                               FinalIntelligence, FinalWisdom, FinalCharisma);

// Resultado:
// FinalStrength = 8 + 7 = 15
// FinalDexterity = 8 + 5 = 13
// FinalConstitution = 8 + 5 = 13
// FinalIntelligence = 8 + 3 = 11
// FinalWisdom = 8 + 3 = 11
// FinalCharisma = 8 + 2 = 10
```

---

## 🔗 Integração com Outros Sistemas

### Fluxo Completo de Criação

O `FPointBuyMotor` é usado em conjunto com outros motores:

1. **Reset Final Scores** → `CalculationHelpers::ResetFinalScoresToBase()`
2. **Aplicar Bônus Raciais** → `FRaceBonusMotor::ApplyRacialBonuses()`
3. **Aplicar Point Buy** → `FPointBuyMotor::ApplyPointBuy()` ← **Você está aqui**
4. **Recalcular Stats Derivados** → `CharacterSheetDataAssetUpdaters`

### Validação Antes de Aplicar

**IMPORTANTE:** Valide antes de aplicar:

```cpp
// Validar alocação antes de aplicar
int32 PointsRemaining = 0;
bool bIsValid = ValidationHelpers::ValidatePointBuy(PointBuyAllocation, PointsRemaining, 27);

if (!bIsValid || PointsRemaining < 0)
{
    // Ajustar alocação ou mostrar erro
    return;
}

// Aplicar Point Buy (agora seguro)
FPointBuyMotor::ApplyPointBuy(PointBuyAllocation, ...);
```

---

## 📖 Design Relacionado

Este motor implementa as seguintes regras de design:

- **[GDD: Sistemas de Personagem - Point Buy](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#point-buy-system)** - Regras de Point Buy D&D 5e
- **[TDD: Point Buy Algorithm](../../../04-regras-dnd/criacao/point-buy-algorithm.md)** - Algoritmo técnico completo

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (27 pontos, custos por score) e PORQUÊ (balanceamento D&D 5e)
- **TDD:** Define COMO (classe `FPointBuyMotor`, método `ApplyPointBuy()`, estruturas C++)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers - ValidationHelpers](../../helpers/validation-helpers.md)** - Validação de Point Buy
> - **[Helpers - CalculationHelpers](../../helpers/calculation-helpers.md)** - Cálculos de ability scores
> - **[Helpers - CharacterSheetHelpers](../../helpers/index.md#charactersheethelpers)** - Helpers de Point Buy
> - **[Índice de Motores](../index.md)** - Lista de todos os motores

</details>

---

**Navegação:** [← Voltar para Motores](../index.md) | [→ MulticlassMotor](multiclass-motor.md)

**Última atualização:** 2024-12-27
