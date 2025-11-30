# CharacterSheetComponent

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌉 CharacterSheetComponent - Bridge Components</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Components/CharacterSheetComponent.h`
>
> **Camada:** 2 - Bridge Components
>
> **Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.

</details>

### Propriedades

#### SourceDataAsset
```cpp
UPROPERTY(EditAnywhere, Category = "Character Sheet")
UCharacterSheetDataAsset *SourceDataAsset;
```
- **Tipo:** `UCharacterSheetDataAsset*`
- **Editável:** Sim (no editor)
- **Descrição:** Data Asset fonte (template) para inicialização

### Métodos Públicos

#### InitializeFromDataAsset()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character")
void InitializeFromDataAsset(UCharacterSheetDataAsset *DataAsset);
```

**Descrição:** Inicializa o componente a partir de um Data Asset. Lê os dados do Data Asset e copia para o `CharacterDataComponent`.

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Fluxo de Inicialização</b></summary>

> **Fluxo:**
>
> 1. Valida Data Asset (não pode ser nullptr)
> 2. Busca `CharacterDataComponent` no Actor
> 3. Copia dados do Data Asset para Runtime Component:
>    - Nome, descrição, nível total
>    - Raça, sub-raça, background
>    - Proficiências
>    - Ability scores (valores finais)
>
> **Chamado automaticamente:**
> - No `BeginPlay()` se `SourceDataAsset` estiver atribuído
>
> **Exemplo de uso:**
>
> ```cpp
> // No editor: atribuir SourceDataAsset no CharacterSheetComponent
> // Ou programaticamente:
> UCharacterSheetComponent* SheetComponent = GetCharacterSheetComponent();
> if (SheetComponent && MyDataAsset)
> {
>     SheetComponent->InitializeFromDataAsset(MyDataAsset);
> }
> ```

</details>

---

## 📖 Design Relacionado

Este componente implementa as seguintes regras de design:

- **[GDD: Sistemas de Personagem](../../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md)** - Regras de criação de personagem D&D 5e

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (criação de personagem D&D 5e) e PORQUÊ (fidelidade às regras oficiais)
- **TDD:** Define COMO (classe `UCharacterSheetComponent`, método `InitializeFromDataAsset()`, estruturas C++)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[CharacterDataComponent](../character-data-component/index.md)** - Runtime Component que recebe os dados
> - **[CharacterSheetDataAsset](../character-sheet-data-asset/index.md)** - Data Asset fonte de dados
> - **[Índice de Componentes](../index.md)** - Lista de todos os componentes

</details>
