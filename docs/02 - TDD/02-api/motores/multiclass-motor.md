# MulticlassMotor

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motor de Multiclasse</b></summary>

> **Caminho:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassMotor.h`
>
> **Responsabilidade:** Validar e aplicar regras de multiclasse D&D 5e.
>
> **Características:**
>
> - Motor independente: não conhece outros motores, apenas aplica regras de multiclasse
> - Genérico: recebe dados puros (FCharacterSheetData), não objetos concretos
> - Validação automática de requisitos de atributo para multiclassing D&D 5e

</details>

---

## 📐 Estrutura da Classe

```cpp
class MYPROJECT2_API FMulticlassMotor
{
public:
    static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable,
                                              int32 FinalStrength,
                                              int32 FinalDexterity,
                                              int32 FinalConstitution,
                                              int32 FinalIntelligence,
                                              int32 FinalWisdom,
                                              int32 FinalCharisma,
                                              const UDataTable *AbilityScoreDataTable = nullptr);

    static void LoadClassProficiencies(const FMulticlassProficienciesEntry& Entry,
                                       TArray<FMulticlassProficienciesEntry>& OutProficiencies);

    static bool LoadClassProgression(FName ClassName,
                                     int32 LevelInClass,
                                     const UDataTable *ClassDataTable,
                                     const UDataTable *FeatureDataTable,
                                     TArray<FMulticlassProgressEntry> &OutProgression);
};
```

---

## 🔧 Métodos Públicos

### GetAvailableClasses()

Retorna todas as classes disponíveis com validação de requisitos de atributo.

**Assinatura:**

```cpp
static TArray<FName> GetAvailableClasses(const UDataTable *ClassDataTable,
                                         int32 FinalStrength,
                                         int32 FinalDexterity,
                                         int32 FinalConstitution,
                                         int32 FinalIntelligence,
                                         int32 FinalWisdom,
                                         int32 FinalCharisma,
                                         const UDataTable *AbilityScoreDataTable = nullptr);
```

**Parâmetros:**

- `ClassDataTable` - Data Table de classes (pode ser nullptr)
- `FinalStrength` - Strength final do personagem
- `FinalDexterity` - Dexterity final do personagem
- `FinalConstitution` - Constitution final do personagem
- `FinalIntelligence` - Intelligence final do personagem
- `FinalWisdom` - Wisdom final do personagem
- `FinalCharisma` - Charisma final do personagem
- `AbilityScoreDataTable` - Data Table de Ability Scores (opcional, necessário para nova estrutura normalizada)

**Retorno:**

- `TArray<FName>` - Array com nomes de classes disponíveis (que atendem requisitos de atributo)

**Descrição:**

Filtra classes que o personagem pode pegar baseado nos atributos finais. Suporta requisitos complexos como "STR/13|DEX/13" (STR ou DEX >= 13).

**Exemplo:**

```cpp
// Personagem com atributos finais
int32 FinalStrength = 15;
int32 FinalDexterity = 13;
int32 FinalConstitution = 14;
int32 FinalIntelligence = 12;
int32 FinalWisdom = 10;
int32 FinalCharisma = 8;

// Buscar classes disponíveis
TArray<FName> AvailableClasses = FMulticlassMotor::GetAvailableClasses(
    ClassDataTable,
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);

// Resultado: ["Fighter", "Ranger", "Paladin", ...]
// Classes que requerem STR >= 13 ou DEX >= 13 estão disponíveis
```

---

### LoadClassProficiencies()

Carrega proficiências de uma classe para multiclasse.

**Assinatura:**

```cpp
static void LoadClassProficiencies(const FMulticlassProficienciesEntry& Entry,
                                   TArray<FMulticlassProficienciesEntry>& OutProficiencies);
```

**Parâmetros:**

- `Entry` - Entry de proficiências já convertida
- `OutProficiencies` [OUT] - Array de proficiências (será modificado)

**Descrição:**

Motor puro que apenas adiciona entry ao array. Assume que dados já foram convertidos.

**Exemplo:**

```cpp
TArray<FMulticlassProficienciesEntry> Proficiencies;

FMulticlassProficienciesEntry FighterProficiencies;
// ... preencher FighterProficiencies ...

FMulticlassMotor::LoadClassProficiencies(FighterProficiencies, Proficiencies);
// Proficiencies agora contém proficiências de Fighter
```

---

### LoadClassProgression()

Carrega progressão de features de uma classe para multiclasse.

**Assinatura:**

```cpp
static bool LoadClassProgression(FName ClassName,
                                 int32 LevelInClass,
                                 const UDataTable *ClassDataTable,
                                 const UDataTable *FeatureDataTable,
                                 TArray<FMulticlassProgressEntry> &OutProgression);
```

**Parâmetros:**

- `ClassName` - Nome da classe
- `LevelInClass` - Nível na classe (1-20)
- `ClassDataTable` - Data Table de classes (pode ser nullptr)
- `FeatureDataTable` - Data Table de features (pode ser nullptr)
- `OutProgression` [OUT] - Array de progressão populada com features detalhadas

**Retorno:**

- `bool` - true se progressão foi carregada com sucesso, false caso contrário

**Descrição:**

Popula array Progression com features detalhadas do ClassFeaturesDataTable. Para cada nível de 1 até LevelInClass, busca features do ClassDataTable e converte para FMulticlassClassFeature.

**Exemplo:**

```cpp
TArray<FMulticlassProgressEntry> Progression;

bool bSuccess = FMulticlassMotor::LoadClassProgression(
    TEXT("Fighter"),
    3,  // Nível 3 de Fighter
    ClassDataTable,
    FeatureDataTable,
    Progression
);

if (bSuccess)
{
    // Progression agora contém features de Fighter níveis 1, 2 e 3
    // Cada entry tem features detalhadas do FeatureDataTable
}
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Verificar Classes Disponíveis para Multiclasse

```cpp
// Personagem Fighter nível 3 quer pegar Ranger
int32 FinalStrength = 15;
int32 FinalDexterity = 13;  // Requisito mínimo para Ranger
int32 FinalConstitution = 14;
int32 FinalIntelligence = 12;
int32 FinalWisdom = 13;     // Requisito mínimo para Ranger
int32 FinalCharisma = 8;

// Verificar se pode pegar Ranger
TArray<FName> AvailableClasses = FMulticlassMotor::GetAvailableClasses(
    ClassDataTable,
    FinalStrength, FinalDexterity, FinalConstitution,
    FinalIntelligence, FinalWisdom, FinalCharisma
);

if (AvailableClasses.Contains(TEXT("Ranger")))
{
    // Pode pegar Ranger (atende requisitos: DEX >= 13 e WIS >= 13)
    UE_LOG(LogTemp, Warning, TEXT("Ranger disponível para multiclasse"));
}
else
{
    // Não pode pegar Ranger (não atende requisitos)
    UE_LOG(LogTemp, Warning, TEXT("Ranger não disponível - requisitos não atendidos"));
}
```

### Exemplo 2: Carregar Progressão Completa de Multiclasse

```cpp
// Personagem Fighter 3 / Ranger 2
TArray<FMulticlassProgressEntry> FighterProgression;
TArray<FMulticlassProgressEntry> RangerProgression;

// Carregar progressão de Fighter
FMulticlassMotor::LoadClassProgression(
    TEXT("Fighter"),
    3,
    ClassDataTable,
    FeatureDataTable,
    FighterProgression
);

// Carregar progressão de Ranger
FMulticlassMotor::LoadClassProgression(
    TEXT("Ranger"),
    2,
    ClassDataTable,
    FeatureDataTable,
    RangerProgression
);

// Agora temos progressão completa de ambas as classes
// FighterProgression: features de níveis 1, 2, 3
// RangerProgression: features de níveis 1, 2
```

---

## 🔗 Integração com Outros Sistemas

### Fluxo de Multiclasse

1. **Validar Requisitos** → `FMulticlassMotor::GetAvailableClasses()`
2. **Carregar Proficiências** → `FMulticlassMotor::LoadClassProficiencies()`
3. **Carregar Progressão** → `FMulticlassMotor::LoadClassProgression()`
4. **Aplicar Features** → `CharacterSheetDataAssetUpdaters`

### Helpers Relacionados

- `MulticlassHelpers` - Funções helper para processamento de multiclasse
- `MulticlassValidators` - Validadores de multiclasse
- `MulticlassDataLoadingHelpers` - Helpers de carregamento de dados

---

## 📖 Design Relacionado

Este motor implementa as seguintes regras de design:

- **[GDD: Multiclassing](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md#multiclassing)** - Regras D&D 5e de multiclassing
- **[TDD: Multiclass Algorithm](../../../04-regras-dnd/criacao/multiclass-algorithm.md)** - Algoritmo técnico completo

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (pré-requisitos, proficiências ganhas) e PORQUÊ (multiclassing D&D 5e)
- **TDD:** Define COMO (classe `FMulticlassMotor`, métodos de validação e carregamento, estruturas C++)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers - ValidationHelpers](../../helpers/validation-helpers.md)** - Validação de multiclasse
> - **[Helpers - DataTableHelpers](../../helpers/data-table-helpers.md)** - Busca de rows em Data Tables
> - **[Índice de Motores](../index.md)** - Lista de todos os motores

</details>

---

**Navegação:** [← PointBuyMotor](point-buy-motor.md) | [→ RaceBonusMotor](race-bonus-motor.md) | [← Voltar para Motores](../index.md)

**Última atualização:** 2024-12-27
