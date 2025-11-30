# FormattingHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Formatação</b></summary>

> **Caminho:** `Source/MyProject2/Utils/FormattingHelpers.h`
>
> **Responsabilidade:** Formatação de dados de personagem D&D 5e para display e logs.
>
> **Características:**
>
> - Funções puras e reutilizáveis para formatação de strings e logs
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Todas as funções < 50 linhas
> - Status de Testes: ✅ 10 testes implementados (`FormattingHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace FormattingHelpers
{
    FString FormatRaceDisplay(FName RaceName, FName SubraceName);
    FString FormatProficienciesList(const TArray<FName> &Proficiencies);
    FString FormatAbilityScores(const TMap<FName, int32> &AbilityScores);
}
```

---

## 🔧 Funções Disponíveis

### FormatRaceDisplay()

Formata display de raça com sub-raça (se houver).

**Assinatura:**

```cpp
FString FormatRaceDisplay(FName RaceName, FName SubraceName);
```

**Parâmetros:**

- `RaceName` - Nome da raça
- `SubraceName` - Nome da sub-raça (pode ser NAME_None)

**Retorno:**

- `FString` - String formatada (ex: "Elf" ou "Elf (High Elf)")

**Exemplo:**

```cpp
FString Display1 = FormattingHelpers::FormatRaceDisplay(TEXT("Elf"), NAME_None);
// Resultado: "Elf"

FString Display2 = FormattingHelpers::FormatRaceDisplay(TEXT("Elf"), TEXT("High Elf"));
// Resultado: "Elf (High Elf)"
```

---

### FormatProficienciesList()

Formata lista de proficiências como string separada por vírgulas.

**Assinatura:**

```cpp
FString FormatProficienciesList(const TArray<FName> &Proficiencies);
```

**Parâmetros:**

- `Proficiencies` - Array de nomes de proficiências

**Retorno:**

- `FString` - String formatada (ex: "Athletics, Acrobatics, Stealth")

**Exemplo:**

```cpp
TArray<FName> Proficiencies;
Proficiencies.Add(TEXT("Athletics"));
Proficiencies.Add(TEXT("Acrobatics"));
Proficiencies.Add(TEXT("Stealth"));

FString Formatted = FormattingHelpers::FormatProficienciesList(Proficiencies);
// Resultado: "Athletics, Acrobatics, Stealth"
```

---

### FormatAbilityScores()

Formata ability scores para log/display.

**Assinatura:**

```cpp
FString FormatAbilityScores(const TMap<FName, int32> &AbilityScores);
```

**Parâmetros:**

- `AbilityScores` - Map com ability scores (chave: FName do atributo, valor: score)

**Retorno:**

- `FString` - String formatada com todos os ability scores em ordem padrão

**Exemplo:**

```cpp
TMap<FName, int32> AbilityScores;
AbilityScores.Add(TEXT("Strength"), 15);
AbilityScores.Add(TEXT("Dexterity"), 13);
AbilityScores.Add(TEXT("Constitution"), 14);
AbilityScores.Add(TEXT("Intelligence"), 12);
AbilityScores.Add(TEXT("Wisdom"), 10);
AbilityScores.Add(TEXT("Charisma"), 8);

FString Formatted = FormattingHelpers::FormatAbilityScores(AbilityScores);
// Resultado:
// "  Strength: 15
//    Dexterity: 13
//    Constitution: 14
//    Intelligence: 12
//    Wisdom: 10
//    Charisma: 8"
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Formatar Display de Personagem para UI

```cpp
// Em um Widget de UI
void UCharacterDisplayWidget::UpdateCharacterDisplay()
{
    // Formatar raça
    FString RaceDisplay = FormattingHelpers::FormatRaceDisplay(
        CharacterData->GetRaceName(),
        CharacterData->GetSubraceName()
    );
    RaceTextBlock->SetText(FText::FromString(RaceDisplay));

    // Formatar proficiências
    TArray<FName> Proficiencies = CharacterData->GetProficiencies();
    FString ProficienciesList = FormattingHelpers::FormatProficienciesList(Proficiencies);
    ProficienciesTextBlock->SetText(FText::FromString(ProficienciesList));
}
```

### Exemplo 2: Formatar Log de Personagem

```cpp
// Em CharacterDataComponent::LogCharacterSheet()
void UCharacterDataComponent::LogCharacterSheet()
{
    // Formatar ability scores para log
    TMap<FName, int32> AbilityScores;
    AbilityScores.Add(TEXT("Strength"), FinalStrength);
    AbilityScores.Add(TEXT("Dexterity"), FinalDexterity);
    // ... outros scores ...

    FString FormattedScores = FormattingHelpers::FormatAbilityScores(AbilityScores);
    UE_LOG(LogTemp, Warning, TEXT("Ability Scores:\n%s"), *FormattedScores);
}
```

---

## 🧪 Testes

**Status:** ✅ 10 testes implementados (`FormattingHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ FormatRaceDisplay (com e sem sub-raça)
- ✅ FormatProficienciesList (vários casos)
- ✅ FormatAbilityScores (validação de formatação)

---

## 🔗 Integração com Outros Sistemas

### Uso em Componentes

- `CharacterDataComponent` - Usa `FormatAbilityScores()` para logs
- Widgets de UI - Usam todas as funções para formatação de display

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Arquitetura - Clean Code](../../../01-arquitetura/principios/clean-code.md)** - Princípios de Clean Code

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para formatação
- **Componente/Widget:** Usa helper para formatar dados para display

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Componentes - CharacterDataComponent](../componentes/character-data-component/index.md)** - Componente que usa estas funções
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← Voltar para Helpers](../index.md) | [→ ChoiceHelpers](choice-helpers.md)

**Última atualização:** 2024-12-27
