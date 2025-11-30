# ChoiceHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Escolhas</b></summary>

> **Caminho:** `Source/MyProject2/Utils/ChoiceHelpers.h`
>
> **Responsabilidade:** Parsing e formatação de strings de escolhas (opções separadas por vírgulas).
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Status de Testes: ✅ 7 testes implementados (`ChoiceHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace ChoiceHelpers
{
    TArray<FName> ParseOptionsString(const FString &OptionsString);
    FString FormatOptionsString(const TArray<FName> &Options);
}

namespace ChoiceMetadataKeys
{
    constexpr const TCHAR *AvailableOptions = TEXT("AvailableOptions");
    constexpr const TCHAR *ChoicesAllowed = TEXT("ChoicesAllowed");
    constexpr const TCHAR *DependsOn = TEXT("DependsOn");
    constexpr const TCHAR *RequiredValue = TEXT("RequiredValue");
}
```

---

## 🔧 Funções Disponíveis

### ParseOptionsString()

Converte string separada por vírgulas em `TArray<FName>`.

**Assinatura:**

```cpp
TArray<FName> ParseOptionsString(const FString &OptionsString);
```

**Parâmetros:**

- `OptionsString` - String com opções separadas por vírgulas (ex: "Archery,Defense,Dueling")

**Retorno:**

- `TArray<FName>` - Array de FName com as opções parseadas

**Descrição:**

Remove espaços em branco e valores vazios. Usado para processar escolhas de features de classes (ex: Fighting Style options).

**Exemplo:**

```cpp
FString OptionsString = TEXT("Archery,Defense,Dueling");
TArray<FName> Options = ChoiceHelpers::ParseOptionsString(OptionsString);

// Resultado: Options = ["Archery", "Defense", "Dueling"]
```

---

### FormatOptionsString()

Converte `TArray<FName>` em string separada por vírgulas.

**Assinatura:**

```cpp
FString FormatOptionsString(const TArray<FName> &Options);
```

**Parâmetros:**

- `Options` - Array de opções

**Retorno:**

- `FString` - String formatada (ex: "Archery,Defense,Dueling")

**Exemplo:**

```cpp
TArray<FName> Options;
Options.Add(TEXT("Archery"));
Options.Add(TEXT("Defense"));
Options.Add(TEXT("Dueling"));

FString OptionsString = ChoiceHelpers::FormatOptionsString(Options);
// Resultado: "Archery,Defense,Dueling"
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Processar Escolhas de Fighting Style

```cpp
// Em ClassDataTable, Fighting Style tem opções: "Archery,Defense,Dueling"
FString FightingStyleOptions = ClassRow->FightingStyleOptions; // "Archery,Defense,Dueling"

// Parsear opções
TArray<FName> AvailableOptions = ChoiceHelpers::ParseOptionsString(FightingStyleOptions);

// Mostrar opções para o jogador escolher
for (const FName& Option : AvailableOptions)
{
    UE_LOG(LogTemp, Warning, TEXT("Opção disponível: %s"), *Option.ToString());
}
```

### Exemplo 2: Salvar Escolhas do Jogador

```cpp
// Jogador escolheu "Archery" e "Defense"
TArray<FName> SelectedChoices;
SelectedChoices.Add(TEXT("Archery"));
SelectedChoices.Add(TEXT("Defense"));

// Formatar para salvar em Data Asset
FString SavedChoices = ChoiceHelpers::FormatOptionsString(SelectedChoices);
// Resultado: "Archery,Defense"

// Salvar em CharacterSheetDataAsset
CharacterSheetDataAsset->SelectedChoices = SavedChoices;
```

---

## 🧪 Testes

**Status:** ✅ 7 testes implementados (`ChoiceHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ ParseOptionsString (vários formatos de string)
- ✅ FormatOptionsString (vários arrays)

---

## 🔗 Integração com Outros Sistemas

### Uso em Data Tables

Estas funções são usadas para processar escolhas de features de classes:

- Fighting Style options
- Maneuver options
- Spell selection options

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Arquitetura - Clean Code](../../../01-arquitetura/principios/clean-code.md)** - Princípios de Clean Code (DRY)

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para parsing/formatação
- **Data Table/Component:** Usa helper para processar escolhas

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Guia - Data Tables](../../../05-guias/data-tables/index.md)** - Guia de Data Tables
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← FormattingHelpers](formatting-helpers.md) | [→ ProficiencyHelpers](proficiency-helpers.md) | [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
