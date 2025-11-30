# CharacterDataComponent

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 CharacterDataComponent - Runtime Data Components</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Components/CharacterDataComponent.h`
>
> **Camada:** 3 - Runtime Data Components
>
> **Responsabilidade:** Armazenar dados replicáveis do personagem em runtime.

</details>

### Propriedades Replicáveis

#### CharacterName
```cpp
UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
FName CharacterName = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Nome do personagem
- **Uso:** Identificação do personagem

#### CharacterDescription
```cpp
UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character Data")
FText CharacterDescription = FText::GetEmpty();
```
- **Tipo:** `FText`
- **Replicável:** Sim
- **Descrição:** Descrição do personagem (localizável)
- **Uso:** Descrição textual do personagem

#### CharacterTotalLvl
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
int32 CharacterTotalLvl = 0;
```
- **Tipo:** `int32`
- **Replicável:** Sim
- **ReadOnly:** Sim (calculado automaticamente)
- **Descrição:** Nível total do personagem (soma de todos os níveis de classes, máximo 20)
- **Validação:** Deve estar entre 1 e 20

#### SelectedRace
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedRace = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Raça selecionada do personagem
- **Validação:** Não pode ser `NAME_None`

#### SelectedSubrace
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedSubrace = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Sub-raça selecionada (se aplicável)
- **Nota:** Pode ser `NAME_None` se raça não tem sub-raças

#### SelectedBackground
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
FName SelectedBackground = NAME_None;
```
- **Tipo:** `FName`
- **Replicável:** Sim
- **Descrição:** Background selecionado
- **Validação:** Não pode ser `NAME_None`

#### Proficiencies
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
TArray<FName> Proficiencies;
```
- **Tipo:** `TArray<FName>`
- **Replicável:** Sim
- **Descrição:** Proficiências do personagem (raça + classe + background)
- **Uso:** Lista de skills, armas, armaduras em que o personagem é proficiente

#### AbilityScores
```cpp
UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
TMap<FName, int32> AbilityScores;
```
- **Tipo:** `TMap<FName, int32>`
- **Replicável:** Sim
- **Descrição:** Ability scores finais (chave: nome do atributo, valor: score final)
- **Chaves esperadas:** "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"
- **Validação:** Cada score deve estar entre 1 e 30

### Métodos Públicos

#### ValidateDataIntegrity()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character Data")
bool ValidateDataIntegrity() const;
```

**Descrição:** Valida integridade dos dados do personagem. Verifica se todos os dados necessários estão presentes e consistentes.

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Validações Realizadas</b></summary>

> **Validações realizadas:**
>
> 1. **Ability Scores:** Verifica se todos os 6 atributos estão presentes e com valores válidos (1-30)
> 2. **Raça:** Verifica se `SelectedRace` não é `NAME_None`
> 3. **Background:** Verifica se `SelectedBackground` não é `NAME_None`
> 4. **Nível Total:** Verifica se está entre 1 e 20
> 5. **Nome:** Avisa se `CharacterName` está vazio (warning, não erro)
>
> **Retorno:**
> - `true` - Todos os dados estão válidos
> - `false` - Dados inválidos ou incompletos
>
> **Quando usar:**
> - No `BeginPlay()` para garantir dados válidos antes de usar
> - Antes de usar dados em combat components
> - Antes de calcular valores derivados (HP, modifiers, etc.)
>
> **Exemplo de uso:**
>
> ```cpp
> void UMyCombatComponent::BeginPlay()
> {
>     Super::BeginPlay();
>
>     UCharacterDataComponent* DataComponent = GetCharacterDataComponent();
>     if (DataComponent && DataComponent->ValidateDataIntegrity())
>     {
>         // Dados válidos, pode usar com segurança
>         int32 Strength = DataComponent->AbilityScores[TEXT("Strength")];
>         // ...
>     }
>     else
>     {
>         UE_LOG(LogTemp, Error, TEXT("Character data is invalid!"));
>     }
> }
> ```
>
> **Integração com LogCharacterSheet():**
>
> O método `LogCharacterSheet()` chama automaticamente `ValidateDataIntegrity()` e exibe o resultado:
>
> ```cpp
> void UCharacterDataComponent::LogCharacterSheet() const
> {
>     // ... exibe dados ...
>
>     // Validação de integridade
>     bool bIsValid = ValidateDataIntegrity();
>     if (bIsValid)
>     {
>         UE_LOG(LogTemp, Warning, TEXT("  ✅ Todos os dados estão válidos e organizados corretamente"));
>     }
>     else
>     {
>         UE_LOG(LogTemp, Error, TEXT("  ❌ Dados inválidos ou incompletos! Verifique os erros acima."));
>     }
> }
> ```

</details>

#### LogCharacterSheet()

```cpp
UFUNCTION(BlueprintCallable, Category = "Character Data")
void LogCharacterSheet() const;
```

**Descrição:** Faz log completo da ficha do personagem no console, incluindo validação de integridade.

**O que exibe:**
- Nome e descrição
- Nível total
- Raça (com sub-raça se houver)
- Background
- Ability Scores (todos os 6 atributos)
- Proficiências (lista formatada)
- Status de validação de integridade

**Uso:** Chamado automaticamente no `BeginPlay()`, ou manualmente para debug.

**Exemplo de saída:**
```
=== Character Sheet ===
Name: Elias
Description: Severino
Level Total: 1
Race: Human (Variant Human)
Background: Acolyte
--- Ability Scores ---
  Strength: 10
  Dexterity: 12
  Constitution: 14
  Intelligence: 13
  Wisdom: 15
  Charisma: 11
--- Proficiencies (4) ---
  Insight, Religion, Perception, Investigation
--- Data Integrity ---
  ✅ Todos os dados estão válidos e organizados corretamente
======================
```

### Replicação

Todas as propriedades são replicáveis via `DOREPLIFETIME`:

```cpp
void UCharacterDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(UCharacterDataComponent, CharacterName);
    DOREPLIFETIME(UCharacterDataComponent, CharacterDescription);
    DOREPLIFETIME(UCharacterDataComponent, CharacterTotalLvl);
    DOREPLIFETIME(UCharacterDataComponent, SelectedRace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedSubrace);
    DOREPLIFETIME(UCharacterDataComponent, SelectedBackground);
    DOREPLIFETIME(UCharacterDataComponent, Proficiencies);
    DOREPLIFETIME(UCharacterDataComponent, AbilityScores);
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[CharacterSheetComponent](../character-sheet-component/index.md)** - Bridge Component que inicializa este componente
> - **[CharacterSheetDataAsset](../character-sheet-data-asset/index.md)** - Data Asset fonte de dados
> - **[Helpers](../../helpers/index.md)** - Funções helper para trabalhar com este componente
> - **[Índice de Componentes](../index.md)** - Lista de todos os componentes

</details>

---

## ⚔️ Preparação para Combat Components

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Integração com Sistema de Combate</b></summary>

> O `CharacterDataComponent` está preparado para uso em combat components:
>
> - **Ability Scores:** Acessíveis via `AbilityScores` map
> - **Validação:** `ValidateDataIntegrity()` garante dados válidos antes de usar
> - **Replicação:** Todos os dados são replicáveis para multiplayer
> - **Estrutura:** Dados organizados e consistentes
>
> **Exemplo de integração futura:**
>
> ```cpp
> // Em um CombatComponent futuro:
> int32 GetAbilityModifier(FName AbilityName) const
> {
>     if (UCharacterDataComponent* DataComp = GetCharacterDataComponent())
>     {
>         if (DataComp->AbilityScores.Contains(AbilityName))
>         {
>             int32 Score = DataComp->AbilityScores[AbilityName];
>             return (Score - 10) / 2; // Modifier = (Score - 10) / 2
>         }
>     }
>     return 0;
> }
> ```

</details>

---

## 🔮 Preparação para GAS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Migração Futura para Gameplay Ability System</b></summary>

> A estrutura atual facilita migração futura para GAS:
>
> - **Dados em Components:** Fácil migrar para GAS Attributes
> - **Replicação configurada:** GAS usa mesmo sistema
> - **Validação implementada:** Pode ser migrada para GAS validators
> - **Estrutura modular:** Lógica pode ser migrada para GAS Abilities

</details>
