# Helpers e Utilitários

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Funções Helper Reutilizáveis</b></summary>

> Funções helper organizadas em namespaces em `Utils/`:
>
> **Princípios:**
> - Funções puras (sem efeitos colaterais)
> - Parametrizadas (sem dependência de estado interno)
> - Testáveis isoladamente
> - < 50 linhas cada
> - Reutilizáveis em editor e runtime

</details>

## ComponentHelpers

**Caminho:** `Source/MyProject2/Utils/ComponentHelpers.h`

**Status de Testes:** ✅ 3 testes implementados (`ComponentHelpersTests.cpp`)

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

## ValidationHelpers

**Caminho:** `Source/MyProject2/Utils/ValidationHelpers.h`

Funções helper para validação de dados de personagem D&D 5e.

**Status de Testes:** ✅ 35 testes implementados (`ValidationHelpersTests.cpp`)

**Principais Funções:**

- `ValidatePointBuy()` - Valida alocação de Point Buy e calcula pontos restantes
- `ValidatePointBuyAllocation()` - Valida alocação completa de Point Buy (range + pontos)
- `ValidateTotalLevel()` - Calcula nível total e valida se está dentro do range permitido
- `ValidateTotalLevelRange()` - Valida se um nível total está dentro do range permitido
- `ValidateAbilityScoreRange()` - Valida se um ability score está dentro do range permitido
- `ValidateAbilityScoreChoices()` - Valida escolhas de ability scores (ex: Variant Human)
- `ValidateFeatSelection()` - Valida se uma seleção de feat está disponível
- `ValidateSkillSelection()` - Valida se uma seleção de skill é válida

**Uso:** Todas as funções são usadas em `CharacterSheetDataAssetValidators` e podem ser reutilizadas em widgets, combat components e outras mecânicas do jogo.

---

## CalculationHelpers

**Caminho:** `Source/MyProject2/Utils/CalculationHelpers.h`

Funções helper para cálculos de dados de personagem D&D 5e.

**Status de Testes:** ✅ 28 testes implementados (`CalculationHelpersTests.cpp`)

**Principais Funções:**

- `CalculateAbilityModifier()` - Calcula o modificador de ability score. Fórmula D&D 5e: `floor((Score - 10) / 2)`
- `ResetFinalScoresToBase()` - Reseta Final Scores para valor base (8)
- `IncrementFinalScoresWithPointBuy()` - Incrementa Final Scores com alocação de Point Buy
- `CalculateProficiencyBonus()` - Calcula o bônus de proficiência baseado no nível total
- `CalculateAvailableFeatures()` - Calcula features disponíveis baseado em níveis de classes
- `CalculateProficiencies()` - Calcula proficiências do personagem
- `CalculateLanguages()` - Calcula idiomas finais do personagem

**Uso:** Usadas em `CharacterSheetDataAssetUpdaters` e podem ser reutilizadas em combat components para cálculos de dano, AC, etc.

---

## DataTableHelpers

**Caminho:** `Source/MyProject2/Utils/DataTableHelpers.h`

Funções helper para busca de rows em Data Tables com fallback manual.

**Status de Testes:** ✅ 23 testes implementados (`DataTableHelpersTests.cpp`) - Inclui validação de tipo de Data Tables

**Principais Funções:**

- `FindRaceRow()` - Busca row de raça no Data Table
- `FindSubraceRow()` - Busca row de sub-raça no Data Table
- `FindClassRow()` - Busca row de classe no Data Table
- `FindFeatRow()` - Busca row de feat no Data Table
- `ValidateDataTableRowStruct()` - Valida se DataTable tem RowStruct do tipo esperado
- `IsRaceDataTable()`, `IsClassDataTable()`, `IsBackgroundDataTable()`, etc. - Validações de tipo específicas

**Uso:** Centraliza lógica de busca que pode falhar com `FindRow` direto. Reutilizável em qualquer lugar que precise buscar rows em Data Tables.

---

## FormattingHelpers

**Caminho:** `Source/MyProject2/Utils/FormattingHelpers.h`

Funções helper para formatação de dados de personagem D&D 5e.

**Status de Testes:** ✅ 10 testes implementados (`FormattingHelpersTests.cpp`)

**Funções:**

- `FormatRaceDisplay()` - Formata display de raça com sub-raça (se houver)
- `FormatProficienciesList()` - Formata lista de proficiências como string separada por vírgulas
- `FormatAbilityScores()` - Formata ability scores para log/display

**Uso:** Usadas em `CharacterDataComponent::LogCharacterSheet()` e podem ser reutilizadas em widgets de UI para formatação de display.

---

## ChoiceHelpers

**Caminho:** `Source/MyProject2/Utils/ChoiceHelpers.h`

Funções helper para parsing e formatação de strings de escolhas (opções separadas por vírgulas).

**Status de Testes:** ✅ 7 testes implementados (`ChoiceHelpersTests.cpp`)

**Funções:**

- `ParseOptionsString()` - Parseia string de opções separadas por vírgulas em array de FName
- `FormatOptionsString()` - Formata array de opções em string separada por vírgulas

**Uso:** Usadas para processar escolhas de features de classes (ex: Fighting Style options).

---

## CharacterSheetHelpers

**Caminho:** `Source/MyProject2/Utils/CharacterSheetHelpers.h`

Funções helper para leitura, filtragem e validação de Data Tables de D&D 5e.

**Status de Testes:** ✅ 36 testes implementados (`CharacterSheetHelpersTests.cpp`)

**Principais Categorias:**

- **Race Data Table Helpers:** `GetAllRaceNames()`, `GetAvailableSubraces()`
- **Class Data Table Helpers:** `GetAllClassNames()`, `GetAvailableSubclasses()`, `CanSelectSubclass()`, `GetFeaturesAtLevel()`
- **Background Data Table Helpers:** `GetAllBackgroundNames()`
- **Feat Data Table Helpers:** `GetAvailableFeats()`, `CanTakeFeatAtLevel()`, `ValidateAbilityScorePrerequisite()`, `MeetsFeatPrerequisites()`
- **Ability Score Helpers:** `GetAbilityScoreNames()`, `CreatePointBuyMapFromData()`, `CreateBaseScoresFromPointBuy()`
- **Skill Helpers:** `GetSkillNames()`
- **Point Buy System Helpers:** `CreatePointBuyMapFromData()`, `CreateBaseScoresFromPointBuy()`, `CalculatePointBuyCost()`, `CalculateTotalPointBuyCost()`, `AdjustPointBuyAllocation()`
- **Level Calculation Helpers:** `CalculateTotalLevel()`

**Uso:** Usadas em `CharacterSheetDataAsset` para funções `GetOptions` e podem ser reutilizadas em widgets e outras mecânicas.

---

## CharacterSheetDataAssetHelpers

**Caminho:** `Source/MyProject2/Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h`

Funções helper reutilizáveis para `CharacterSheetDataAsset`, seguindo princípios de Clean Code e Design Patterns.

**Status de Testes:** ✅ 18 testes implementados (`CharacterSheetDataAssetHelpersTests.cpp`)

**Principais Funções:**

- `ValidateDataTableType()` - Valida tipo de Data Table específica e exibe popup de erro se tipo incorreto
- `ForEachMultipleChoiceFeature()` - Itera por todas as features de múltiplas escolhas (Tipo 3) em todas as entradas de multiclasse
- `GetMaxChoicesLimit()` - Obtém limite máximo de escolhas para uma feature
- `CanAddChoice()` - Valida se uma escolha pode ser adicionada (não excede limite, não é duplicata)
- `CleanInvalidAndDuplicateChoices()` - Remove escolhas inválidas e duplicatas de `SelectedChoices`

**Uso:** Helpers reutilizáveis para `CharacterSheetDataAsset`, seguindo princípios de Clean Code (DRY, Single Responsibility, Testability).

---

## ProficiencyHelpers

**Caminho:** `Source/MyProject2/Utils/ProficiencyHelpers.h`

Funções helper para ler e processar `ProficiencyData` de proficiências. Funções puras e reutilizáveis seguindo princípios de Clean Code.

**Status de Testes:** ✅ 12 testes implementados (`ProficiencyHelpersTests.cpp`)

**Funções:**

- `GetProficiencyDataValue()` - Obtém valor de ProficiencyData como FString
- `HasProficiencyData()` - Verifica se ProficiencyData não está vazio
- `GetProficiencyDataAsInt()` - Obtém valor de ProficiencyData como int32
- `GetProficiencyDataAsFloat()` - Obtém valor de ProficiencyData como float
- `GetProficiencyDataAsBool()` - Obtém valor de ProficiencyData como bool

---

## Sistema de Logging (FLoggingSystem)

**Caminho:** `Source/MyProject2/Logging/LoggingSystem.h`

**Responsabilidade:** Sistema centralizado de logging com suporte a popups no editor e throttle para evitar poluição visual.

**Documentação:** [Sistema de Logging](./logging-system/index.md)

**Status de Testes:** Sistema de logging não requer testes (wrapper de UE_LOG e notificações do editor)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Componentes](../componentes/index.md)** - Componentes que usam os helpers
> - **[Motores](../motores/index.md)** - Motores que usam os helpers
> - **[Índice da API](../index.md)** - Organização da API

</details>
