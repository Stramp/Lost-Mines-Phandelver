# ComponentHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helper de Componentes</b></summary>

> **Caminho:** `Source/MyProject2/Utils/ComponentHelpers.h`
>
> **Responsabilidade:** Busca e manipulação de componentes.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Status de Testes: ✅ 3 testes implementados (`ComponentHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace ComponentHelpers
{
    UCharacterDataComponent* FindCharacterDataComponent(AActor* Owner);
}
```

---

## 🔧 Funções Disponíveis

### FindCharacterDataComponent()

Busca o `CharacterDataComponent` no Actor especificado.

**Assinatura:**

```cpp
UCharacterDataComponent* FindCharacterDataComponent(AActor* Owner);
```

**Parâmetros:**

- `Owner` - Actor onde buscar o componente (pode ser nullptr)

**Retorno:**

- `UCharacterDataComponent*` - Componente encontrado, ou `nullptr` se não encontrado ou Owner inválido

**Descrição:**

Função pura, sem efeitos colaterais, parametrizada e reutilizável. Busca o `CharacterDataComponent` usando `FindComponentByClass<UCharacterDataComponent>()`.

**Comportamento:**

- Se `Owner` for `nullptr`, retorna `nullptr` imediatamente
- Busca componente usando `Owner->FindComponentByClass<UCharacterDataComponent>()`
- Retorna `nullptr` se componente não for encontrado

**Pré-condições:**

- Nenhuma (função valida `Owner` internamente)

**Pós-condições:**

- Retorna componente encontrado ou `nullptr`

---

## 💡 Exemplos de Uso

### Exemplo 1: Buscar Componente em Actor

```cpp
// Actor com CharacterDataComponent
AActor* MyCharacter = GetWorld()->SpawnActor<ACharacter>(...);

// Buscar componente
UCharacterDataComponent* CharacterData = ComponentHelpers::FindCharacterDataComponent(MyCharacter);

if (CharacterData)
{
    // Componente encontrado, pode usar
    int32 CurrentHP = CharacterData->GetCurrentHP();
    UE_LOG(LogTemp, Warning, TEXT("HP atual: %d"), CurrentHP);
}
else
{
    // Componente não encontrado
    UE_LOG(LogTemp, Error, TEXT("CharacterDataComponent não encontrado"));
}
```

### Exemplo 2: Validação Segura com Nullptr

```cpp
// Função que recebe Actor (pode ser nullptr)
void ProcessCharacter(AActor* CharacterActor)
{
    // Buscar componente (seguro mesmo se CharacterActor for nullptr)
    UCharacterDataComponent* CharacterData = ComponentHelpers::FindCharacterDataComponent(CharacterActor);

    if (!CharacterData)
    {
        // Tratamento seguro: componente não encontrado ou Actor inválido
        return;
    }

    // Usar componente com segurança
    CharacterData->CalculateFinalAttributes();
}
```

### Exemplo 3: Uso em Widget ou Outro Sistema

```cpp
// Em um Widget ou sistema que precisa acessar CharacterDataComponent
void UMyWidget::UpdateCharacterDisplay()
{
    // Buscar componente do personagem do jogador
    AActor* PlayerCharacter = GetOwningPlayerPawn();
    UCharacterDataComponent* CharacterData = ComponentHelpers::FindCharacterDataComponent(PlayerCharacter);

    if (CharacterData)
    {
        // Atualizar UI com dados do personagem
        UpdateHPBar(CharacterData->GetCurrentHP(), CharacterData->GetMaxHP());
        UpdateLevelDisplay(CharacterData->GetTotalLevel());
    }
}
```

---

## 🧪 Testes

**Status:** ✅ 3 testes implementados (`ComponentHelpersTests.cpp`)

**Casos de Teste:**

1. ✅ `FindCharacterDataComponent_WithValidOwner_ReturnsComponent` - Retorna componente quando Owner tem componente
2. ✅ `FindCharacterDataComponent_WithNullOwner_ReturnsNullptr` - Retorna nullptr quando Owner é null
3. ✅ `FindCharacterDataComponent_WithoutComponent_ReturnsNullptr` - Retorna nullptr quando Owner não tem componente

---

## 🔗 Integração com Outros Sistemas

### Uso em Componentes

Esta função é usada em vários lugares do código:

- `CharacterSheetComponent` - Busca `CharacterDataComponent` para aplicar regras
- Widgets de UI - Busca componente para exibir dados
- Sistemas de combate - Busca componente para cálculos de dano/AC

### Princípios de Clean Code

Esta função segue os princípios de Clean Code:

- ✅ **DRY (Don't Repeat Yourself):** Centraliza lógica de busca de componente
- ✅ **Single Responsibility:** Apenas busca componente, não faz mais nada
- ✅ **Testability:** Função pura, testável isoladamente
- ✅ **Reusability:** Pode ser usada em qualquer lugar que precise buscar o componente

---

## 📖 Design Relacionado

Esta função helper implementa as seguintes regras de design:

- **[TDD: Arquitetura - Component-Based](../../../01-arquitetura/camadas/index.md)** - Arquitetura baseada em componentes
- **[TDD: CharacterDataComponent](../componentes/character-data-component/index.md)** - Componente que esta função busca

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para busca de componentes
- **Componente:** Lógica de negócio e dados do personagem

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[CharacterDataComponent](../componentes/character-data-component/index.md)** - Componente que esta função busca
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← Voltar para Helpers](../index.md) | [→ CalculationHelpers](calculation-helpers.md)

**Última atualização:** 2024-12-27
