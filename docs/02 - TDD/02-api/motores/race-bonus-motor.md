# RaceBonusMotor

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motor de Bônus Raciais</b></summary>

> **Caminho:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusMotor.h`
>
> **Responsabilidade:** Aplicar bônus raciais nos Final Scores.
>
> **Características:**
>
> - Motor puro: apenas aplica, sem validação, logging, busca de dados ou cálculo
> - Motor independente: não conhece Point Buy, apenas aplica bônus raciais
> - Única responsabilidade: aplicar bônus raciais nos Final Scores

</details>

---

## 📐 Estrutura da Classe

```cpp
class MYPROJECT2_API FRaceBonusMotor
{
public:
    static void ApplyRacialBonuses(const TMap<FName, int32>& RacialBonuses,
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

### ApplyRacialBonuses()

Aplica bônus raciais nos Final Scores.

**Assinatura:**

```cpp
static void ApplyRacialBonuses(const TMap<FName, int32>& RacialBonuses,
                               int32& FinalStrength,
                               int32& FinalDexterity,
                               int32& FinalConstitution,
                               int32& FinalIntelligence,
                               int32& FinalWisdom,
                               int32& FinalCharisma);
```

**Parâmetros:**

- `RacialBonuses` - Map com bônus raciais já calculados (chave: FName do atributo, valor: bônus)
- `FinalStrength` [OUT] - Referência para Final Strength (será modificado)
- `FinalDexterity` [OUT] - Referência para Final Dexterity (será modificado)
- `FinalConstitution` [OUT] - Referência para Final Constitution (será modificado)
- `FinalIntelligence` [OUT] - Referência para Final Intelligence (será modificado)
- `FinalWisdom` [OUT] - Referência para Final Wisdom (será modificado)
- `FinalCharisma` [OUT] - Referência para Final Charisma (será modificado)

**Descrição:**

Motor puro que apenas aplica bônus raciais nos Final Scores. Assume que:

- Bônus raciais já foram calculados (raça base + sub-raça + Variant Human)
- Final Scores já foram resetados para base (8)
- Bônus estão no formato correto (TMap<FName, int32>)

**Comportamento:**

- Incrementa cada Final Score com o bônus racial correspondente
- Não valida, não calcula, não busca dados, não loga
- Motor independente: não conhece Point Buy ou outros sistemas

**Pré-condições:**

- `RacialBonuses` contém apenas chaves válidas de atributos
- Final Scores já foram resetados para base (8)
- Bônus raciais já foram calculados

**Pós-condições:**

- Final Scores são incrementados com bônus raciais

---

## 💡 Exemplos de Uso

### Exemplo 1: Aplicar Bônus Racial Básico (Elf)

```cpp
// Setup: Final Scores resetados para base
int32 FinalStrength = 8;
int32 FinalDexterity = 8;
int32 FinalConstitution = 8;
int32 FinalIntelligence = 8;
int32 FinalWisdom = 8;
int32 FinalCharisma = 8;

// Bônus raciais de Elf (DEX +2)
TMap<FName, int32> RacialBonuses;
RacialBonuses.Add(TEXT("Dexterity"), 2);

// Aplicar bônus raciais
FRaceBonusMotor::ApplyRacialBonuses(RacialBonuses,
                                     FinalStrength, FinalDexterity, FinalConstitution,
                                     FinalIntelligence, FinalWisdom, FinalCharisma);

// Resultado:
// FinalStrength = 8 (sem mudança)
// FinalDexterity = 8 + 2 = 10
// FinalConstitution = 8 (sem mudança)
// FinalIntelligence = 8 (sem mudança)
// FinalWisdom = 8 (sem mudança)
// FinalCharisma = 8 (sem mudança)
```

### Exemplo 2: Aplicar Bônus Racial com Sub-raça (High Elf)

```cpp
// Setup: Final Scores resetados para base
int32 FinalStrength = 8;
int32 FinalDexterity = 8;
int32 FinalConstitution = 8;
int32 FinalIntelligence = 8;
int32 FinalWisdom = 8;
int32 FinalCharisma = 8;

// Bônus raciais de High Elf (DEX +2, INT +1)
// Calculados previamente por FRaceBonusHelpers::CalculateRacialBonuses()
TMap<FName, int32> RacialBonuses;
RacialBonuses.Add(TEXT("Dexterity"), 2);      // Raça base
RacialBonuses.Add(TEXT("Intelligence"), 1);  // Sub-raça

// Aplicar bônus raciais
FRaceBonusMotor::ApplyRacialBonuses(RacialBonuses,
                                     FinalStrength, FinalDexterity, FinalConstitution,
                                     FinalIntelligence, FinalWisdom, FinalCharisma);

// Resultado:
// FinalStrength = 8 (sem mudança)
// FinalDexterity = 8 + 2 = 10
// FinalConstitution = 8 (sem mudança)
// FinalIntelligence = 8 + 1 = 9
// FinalWisdom = 8 (sem mudança)
// FinalCharisma = 8 (sem mudança)
```

### Exemplo 3: Aplicar Bônus de Variant Human

```cpp
// Setup: Final Scores resetados para base
int32 FinalStrength = 8;
int32 FinalDexterity = 8;
int32 FinalConstitution = 8;
int32 FinalIntelligence = 8;
int32 FinalWisdom = 8;
int32 FinalCharisma = 8;

// Bônus raciais de Variant Human (+1 em dois atributos escolhidos)
// Escolhas: STR +1, CON +1
TMap<FName, int32> RacialBonuses;
RacialBonuses.Add(TEXT("Strength"), 1);
RacialBonuses.Add(TEXT("Constitution"), 1);

// Aplicar bônus raciais
FRaceBonusMotor::ApplyRacialBonuses(RacialBonuses,
                                     FinalStrength, FinalDexterity, FinalConstitution,
                                     FinalIntelligence, FinalWisdom, FinalCharisma);

// Resultado:
// FinalStrength = 8 + 1 = 9
// FinalDexterity = 8 (sem mudança)
// FinalConstitution = 8 + 1 = 9
// FinalIntelligence = 8 (sem mudança)
// FinalWisdom = 8 (sem mudança)
// FinalCharisma = 8 (sem mudança)
```

---

## 🔗 Integração com Outros Sistemas

### Fluxo Completo de Criação

O `FRaceBonusMotor` é usado em conjunto com outros motores:

1. **Reset Final Scores** → `CalculationHelpers::ResetFinalScoresToBase()`
2. **Calcular Bônus Raciais** → `FRaceBonusHelpers::CalculateRacialBonuses()`
3. **Aplicar Bônus Raciais** → `FRaceBonusMotor::ApplyRacialBonuses()` ← **Você está aqui**
4. **Aplicar Point Buy** → `FPointBuyMotor::ApplyPointBuy()`
5. **Recalcular Stats Derivados** → `CharacterSheetDataAssetUpdaters`

### Cálculo de Bônus Antes de Aplicar

**IMPORTANTE:** Calcule bônus antes de aplicar:

```cpp
// Calcular bônus raciais antes de aplicar
TMap<FName, int32> RacialBonuses;
FRaceBonusHelpers::CalculateRacialBonuses(
    RaceRow,           // Row de raça base
    SubraceRow,        // Row de sub-raça (pode ser nullptr)
    CustomChoices,     // Escolhas de Variant Human (pode estar vazio)
    RacialBonuses      // [OUT] Bônus calculados
);

// Aplicar bônus raciais (agora seguro)
FRaceBonusMotor::ApplyRacialBonuses(RacialBonuses, ...);
```

---

## 📖 Design Relacionado

Este motor implementa as seguintes regras de design:

- **[GDD: Sistemas de Personagem - Raças](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#raças)** - Regras de raças D&D 5e
- **[TDD: Character Creation Algorithm](../../../04-regras-dnd/criacao/character-creation-algorithm.md)** - Algoritmo técnico completo

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (bônus raciais por raça) e PORQUÊ (diversidade de personagens D&D 5e)
- **TDD:** Define COMO (classe `FRaceBonusMotor`, método `ApplyRacialBonuses()`, estruturas C++)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers - RaceBonusHelpers](../../helpers/index.md#racebonushelpers)** - Cálculo de bônus raciais
> - **[Helpers - DataTableHelpers](../../helpers/data-table-helpers.md)** - Busca de rows de raças
> - **[Índice de Motores](../index.md)** - Lista de todos os motores

</details>

---

**Navegação:** [← MulticlassMotor](multiclass-motor.md) | [← Voltar para Motores](../index.md)

**Última atualização:** 2024-12-27
