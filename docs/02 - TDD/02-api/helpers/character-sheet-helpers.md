# CharacterSheetHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Character Sheet</b></summary>

> **Caminho:** `Source/MyProject2/Utils/CharacterSheetHelpers.h`
>
> **Responsabilidade:** Leitura, filtragem e validação de Data Tables de D&D 5e.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Todas as funções < 50 linhas
> - Status de Testes: ✅ 36 testes implementados (`CharacterSheetHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace CharacterSheetHelpers
{
    // Race Data Table Helpers
    TArray<FName> GetAllRaceNames(UDataTable* RaceDataTable);
    TArray<FName> GetAvailableSubraces(FName RaceName, UDataTable* RaceDataTable);

    // Class Data Table Helpers
    TArray<FName> GetAllClassNames(UDataTable* ClassDataTable);
    TArray<FName> GetAvailableSubclasses(FName ClassName, UDataTable* ClassDataTable);
    bool CanSelectSubclass(FName ClassName, int32 ClassLevel, UDataTable* ClassDataTable);
    TArray<FName> GetFeaturesAtLevel(FName ClassName, int32 Level, UDataTable* ClassDataTable);

    // Background Data Table Helpers
    TArray<FName> GetAllBackgroundNames(UDataTable* BackgroundDataTable);

    // Feat Data Table Helpers
    TArray<FName> GetAvailableFeats(int32 TotalLevel, const TMap<FName, int32>& AbilityScores, UDataTable* FeatDataTable);
    TArray<FName> GetAvailableFeatsForVariantHuman(const TMap<FName, int32>& AbilityScores, UDataTable* FeatDataTable);
    bool CanTakeFeatAtLevel(int32 TotalLevel);
    bool ValidateAbilityScorePrerequisite(const FName& Prerequisite, const TMap<FName, int32>& AbilityScores);
    bool MeetsFeatPrerequisites(const FFeatDataRow* Row, const TMap<FName, int32>& AbilityScores);

    // Ability Score Helpers
    TArray<FName> GetAbilityScoreNames(UDataTable* AbilityScoreDataTable = nullptr);

    // Skill Helpers
    TArray<FName> GetSkillNames(UDataTable* ProficiencyDataTable = nullptr);

    // Language Helpers
    TArray<FName> GetAvailableLanguageNames(UDataTable* ProficiencyDataTable = nullptr);
    bool HasLanguageChoiceFromRace(FName RaceName, FName SubraceName, UDataTable* RaceDataTable, int32& OutCount);
    bool HasLanguageChoiceFromBackground(FName BackgroundName, UDataTable* BackgroundDataTable, int32& OutCount);
    TArray<FName> GetAutomaticLanguages(FName RaceName, FName SubraceName, FName BackgroundName, ...);
    TArray<FName> GetAvailableLanguagesForChoice(FName RaceName, FName SubraceName, FName BackgroundName, ...);

    // Point Buy System Helpers
    int32 CalculatePointBuyCost(int32 Score);
    int32 CalculateTotalPointBuyCost(const TMap<FName, int32>& AbilityScores);
    TMap<FName, int32> CreatePointBuyMapFromData(int32 PointBuyStrength, ...);
    TMap<FName, int32> CreateBaseScoresFromPointBuy(const TMap<FName, int32>& PointBuyMap);
    FString AdjustPointBuyAllocation(TMap<FName, int32>& PointBuyMap, int32 MaxPoints = 27);

    // Level Calculation Helpers
    int32 CalculateTotalLevel(const TArray<FClassLevelEntry>& ClassLevels);
}
```

---

## 🔧 Categorias de Funções

### Race Data Table Helpers

Funções para buscar e filtrar dados de raças.

**Funções Principais:**

- `GetAllRaceNames()` - Retorna todos os nomes de raças disponíveis
- `GetAvailableSubraces()` - Retorna sub-raças disponíveis para uma raça

**Exemplo:**

```cpp
UDataTable* RaceDataTable = CharacterSheetDataAsset->RaceDataTable;

// Buscar todas as raças
TArray<FName> AllRaces = CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);

// Buscar sub-raças de Elf
TArray<FName> ElfSubraces = CharacterSheetHelpers::GetAvailableSubraces(TEXT("Elf"), RaceDataTable);
// Resultado: ["High Elf", "Wood Elf", "Drow"]
```

---

### Class Data Table Helpers

Funções para buscar e filtrar dados de classes.

**Funções Principais:**

- `GetAllClassNames()` - Retorna todos os nomes de classes disponíveis
- `GetAvailableSubclasses()` - Retorna subclasses disponíveis para uma classe
- `CanSelectSubclass()` - Verifica se pode selecionar subclasse (nível >= 3)
- `GetFeaturesAtLevel()` - Retorna features disponíveis em um nível específico

**Exemplo:**

```cpp
UDataTable* ClassDataTable = CharacterSheetDataAsset->ClassDataTable;

// Buscar todas as classes
TArray<FName> AllClasses = CharacterSheetHelpers::GetAllClassNames(ClassDataTable);

// Verificar se pode selecionar subclasse
bool bCanSelect = CharacterSheetHelpers::CanSelectSubclass(TEXT("Fighter"), 3, ClassDataTable);
// Resultado: true (nível 3 permite escolher subclasse)

// Buscar features do nível 3 de Fighter
TArray<FName> Features = CharacterSheetHelpers::GetFeaturesAtLevel(TEXT("Fighter"), 3, ClassDataTable);
```

---

### Feat Data Table Helpers

Funções para buscar e validar feats disponíveis.

**Funções Principais:**

- `GetAvailableFeats()` - Retorna feats disponíveis baseado em nível e ability scores
- `GetAvailableFeatsForVariantHuman()` - Retorna feats disponíveis para Variant Human (nível 1)
- `CanTakeFeatAtLevel()` - Verifica se pode escolher feat no nível (4, 8, 12, 16, 19)
- `ValidateAbilityScorePrerequisite()` - Valida pré-requisito de ability score
- `MeetsFeatPrerequisites()` - Verifica se atende todos os pré-requisitos de um feat

**Exemplo:**

```cpp
UDataTable* FeatDataTable = CharacterSheetDataAsset->FeatDataTable;

// Criar map de ability scores
TMap<FName, int32> AbilityScores;
AbilityScores.Add(TEXT("Strength"), 15);
AbilityScores.Add(TEXT("Dexterity"), 13);
// ... outros scores ...

// Buscar feats disponíveis no nível 4
int32 TotalLevel = 4;
TArray<FName> AvailableFeats = CharacterSheetHelpers::GetAvailableFeats(
    TotalLevel,
    AbilityScores,
    FeatDataTable
);

// Verificar se pode escolher feat neste nível
bool bCanTakeFeat = CharacterSheetHelpers::CanTakeFeatAtLevel(TotalLevel);
// Resultado: true (nível 4 permite escolher feat)
```

---

### Point Buy System Helpers

Funções para cálculos e manipulação de Point Buy.

**Funções Principais:**

- `CalculatePointBuyCost()` - Calcula custo em pontos para um ability score
- `CalculateTotalPointBuyCost()` - Calcula custo total de todos os ability scores
- `CreatePointBuyMapFromData()` - Cria map de Point Buy a partir de valores individuais
- `CreateBaseScoresFromPointBuy()` - Cria BaseScores (8 + PointBuy) a partir de PointBuyMap
- `AdjustPointBuyAllocation()` - Ajusta alocação para não exceder máximo de pontos

**Exemplo:**

```cpp
// Calcular custo de um score específico
int32 Cost = CharacterSheetHelpers::CalculatePointBuyCost(15);
// Resultado: 9 pontos

// Criar map de Point Buy
TMap<FName, int32> PointBuyMap = CharacterSheetHelpers::CreatePointBuyMapFromData(
    7,  // Strength
    5,  // Dexterity
    5,  // Constitution
    3,  // Intelligence
    3,  // Wisdom
    2   // Charisma
);

// Calcular custo total
int32 TotalCost = CharacterSheetHelpers::CalculateTotalPointBuyCost(PointBuyMap);
// Resultado: 27 pontos

// Ajustar se exceder
if (TotalCost > 27)
{
    FString Feedback = CharacterSheetHelpers::AdjustPointBuyAllocation(PointBuyMap, 27);
    // PointBuyMap agora ajustado para não exceder 27 pontos
}
```

---

### Language Helpers

Funções para gerenciar idiomas do personagem.

**Funções Principais:**

- `GetAvailableLanguageNames()` - Retorna todos os idiomas disponíveis
- `HasLanguageChoiceFromRace()` - Detecta se raça permite escolha de idiomas
- `GetAutomaticLanguages()` - Calcula idiomas automáticos (raça + sub-raça + background)
- `GetAvailableLanguagesForChoice()` - Retorna idiomas disponíveis para escolha (excluindo já conhecidos)

**Exemplo:**

```cpp
// Buscar idiomas automáticos
TArray<FName> AutomaticLanguages = CharacterSheetHelpers::GetAutomaticLanguages(
    TEXT("Elf"),
    TEXT("High Elf"),
    TEXT("Sage"),
    RaceDataTable,
    BackgroundDataTable
);
// Resultado: ["Common", "Elvish", "Draconic", "Dwarvish"]

// Buscar idiomas disponíveis para escolha (excluindo já conhecidos)
TArray<FName> AvailableForChoice = CharacterSheetHelpers::GetAvailableLanguagesForChoice(
    TEXT("Elf"),
    TEXT("High Elf"),
    TEXT("Sage"),
    SelectedLanguages,  // Idiomas já escolhidos pelo jogador
    RaceDataTable,
    BackgroundDataTable,
    ProficiencyDataTable
);
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Popular Dropdown de Raças em Widget

```cpp
// Em um Widget de criação de personagem
void UCharacterCreationWidget::PopulateRaceDropdown()
{
    UDataTable* RaceDataTable = CharacterSheetDataAsset->RaceDataTable;

    // Buscar todas as raças
    TArray<FName> AllRaces = CharacterSheetHelpers::GetAllRaceNames(RaceDataTable);

    // Popular dropdown
    for (const FName& RaceName : AllRaces)
    {
        RaceComboBox->AddOption(RaceName.ToString());
    }
}
```

### Exemplo 2: Validar Feat Antes de Aplicar

```cpp
// Validar se personagem pode escolher Great Weapon Master
TMap<FName, int32> AbilityScores = CreateAbilityScoresMap(...);
int32 TotalLevel = 4;

// Verificar se pode escolher feat neste nível
if (!CharacterSheetHelpers::CanTakeFeatAtLevel(TotalLevel))
{
    ShowError(TEXT("Feats só podem ser escolhidos nos níveis 4, 8, 12, 16, 19"));
    return;
}

// Buscar row do feat
FFeatDataRow* FeatRow = DataTableHelpers::FindFeatRow(TEXT("Great Weapon Master"), FeatDataTable);

if (FeatRow)
{
    // Validar pré-requisitos
    bool bMeetsPrerequisites = CharacterSheetHelpers::MeetsFeatPrerequisites(FeatRow, AbilityScores);

    if (bMeetsPrerequisites)
    {
        // Aplicar feat
        ApplyFeat(TEXT("Great Weapon Master"));
    }
    else
    {
        ShowError(TEXT("Pré-requisitos não atendidos para Great Weapon Master"));
    }
}
```

---

## 🧪 Testes

**Status:** ✅ 36 testes implementados (`CharacterSheetHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ Race Data Table Helpers (múltiplos casos)
- ✅ Class Data Table Helpers (múltiplos casos)
- ✅ Feat Data Table Helpers (validação de pré-requisitos)
- ✅ Point Buy System Helpers (cálculos e ajustes)
- ✅ Language Helpers (filtragem e escolhas)

---

## 🔗 Integração com Outros Sistemas

### Uso em Data Assets

- `CharacterSheetDataAsset` - Usa todas as funções para funções `GetOptions`
- Widgets de UI - Usam para popular dropdowns e validar escolhas

### Uso em Motores

- `FPointBuyMotor` - Usa `CalculatePointBuyCost()` e `AdjustPointBuyAllocation()`
- `FMulticlassMotor` - Usa `GetAllClassNames()` e validações

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Arquitetura - Data-Driven](../../../01-arquitetura/principios/data-driven.md)** - Princípio Data-Driven
- **[GDD: Sistemas de Personagem](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md)** - Regras de criação de personagem

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para leitura/filtragem de Data Tables
- **Data Table:** Armazena dados de configuração
- **Componente/Widget:** Usa helper para buscar opções e validar escolhas

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers - DataTableHelpers](data-table-helpers.md)** - Busca de rows em Data Tables
> - **[Motores - PointBuyMotor](../motores/point-buy-motor.md)** - Motor que usa estas funções
> - **[Guia - Data Tables](../../../05-guias/data-tables/index.md)** - Guia completo de Data Tables
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
