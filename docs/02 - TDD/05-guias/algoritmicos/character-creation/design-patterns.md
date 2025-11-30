# Design Patterns - Character Creation

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia de Design Patterns |

---

## 🎯 Objetivo

Documentar os Design Patterns utilizados na criação de personagem.

---

## 🏗️ Design Patterns Utilizados

### 1. Builder Pattern

**Objetivo:** Construir objeto complexo passo a passo.

**Implementação:**

```cpp
class FCharacterBuilder
{
public:
    FCharacterBuilder& SetRace(FName RaceName);
    FCharacterBuilder& SetClass(FName ClassName);
    FCharacterBuilder& SetAbilityScores(IAbilityScoreStrategy* Strategy);
    FCharacterBuilder& SetBackground(FName BackgroundName);
    FCharacterBuilder& ApplyStartingEquipment();
    FCharacterData Build();
};
```

**Uso:**

```cpp
FCharacterData Character = FCharacterBuilder()
    .SetRace(TEXT("Human"))
    .SetSubrace(TEXT("Variant Human"))
    .SetClass(TEXT("Fighter"))
    .SetAbilityScores(new FPointBuyStrategy())
    .SetBackground(TEXT("Acolyte"))
    .ApplyStartingEquipment()
    .Build();
```

**Benefícios:**

- ✅ Construção passo a passo
- ✅ Validação em cada passo
- ✅ Código legível e fluente
- ✅ Flexível (pode pular passos opcionais)

---

### 2. Strategy Pattern

**Objetivo:** Intercambiar algoritmos de alocação de atributos.

**Implementação:**

```cpp
class IAbilityScoreStrategy
{
public:
    virtual TMap<FName, int32> AllocateAbilityScores() = 0;
};

class FPointBuyStrategy : public IAbilityScoreStrategy { ... };
class FStandardArrayStrategy : public IAbilityScoreStrategy { ... };
class FRollStrategy : public IAbilityScoreStrategy { ... };
```

**Uso:**

```cpp
// Point Buy
IAbilityScoreStrategy* Strategy = new FPointBuyStrategy();
Builder.SetAbilityScores(Strategy);

// Standard Array
Strategy = new FStandardArrayStrategy();
Builder.SetAbilityScores(Strategy);

// Roll
Strategy = new FRollStrategy();
Builder.SetAbilityScores(Strategy);
```

**Benefícios:**

- ✅ Fácil adicionar novos métodos
- ✅ Código desacoplado
- ✅ Testável isoladamente

---

### 3. Template Method Pattern

**Objetivo:** Definir ordem fixa de criação.

**Implementação:**

```cpp
class FCharacterBuilder
{
public:
    FCharacterData Build()
    {
        // Template Method: ordem fixa
        ValidateRace();
        ValidateClass();
        ValidateAbilityScores();
        ValidateBackground();
        ValidateEquipment();

        return CharacterData;
    }

protected:
    virtual void ValidateRace() { /* validação base */ }
    virtual void ValidateClass() { /* validação base */ }
    // ... outros passos
};
```

**Benefícios:**

- ✅ Ordem garantida
- ✅ Validação em cada passo
- ✅ Extensível (pode sobrescrever passos)

---

### 4. Factory Pattern

**Objetivo:** Criar itens de equipamento.

**Implementação:**

```cpp
class FItemFactory
{
public:
    static FItem* CreateItem(FName ItemName)
    {
        // Carregar ItemDataTable
        UDataTable* ItemDataTable = LoadObject<UDataTable>(
            nullptr, TEXT("/Game/Data/DT_Items"));

        FItemDataRow* ItemRow = ItemDataTable->FindRow<FItemDataRow>(
            ItemName, TEXT("ItemFactory"));

        if (!ItemRow)
        {
            return nullptr;
        }

        // Criar item baseado no tipo
        if (ItemRow->ItemType == TEXT("Weapon"))
        {
            return new FWeapon(ItemRow);
        }
        else if (ItemRow->ItemType == TEXT("Armor"))
        {
            return new FArmor(ItemRow);
        }
        // ... outros tipos

        return nullptr;
    }
};
```

**Benefícios:**

- ✅ Criação centralizada
- ✅ Fácil adicionar novos tipos
- ✅ Desacoplado do código cliente

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Design Patterns</b></summary>

> - **Builder Pattern:** Construção passo a passo de objetos complexos
> - **Strategy Pattern:** Algoritmos intercambiáveis
> - **Template Method Pattern:** Ordem fixa de execução
> - **Factory Pattern:** Criação de objetos

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](../../../../04-regras-dnd/criacao/character-creation-algorithm.md) - Algoritmo técnico
> - [Passo 1: Race](passo-1-race.md) - Builder Pattern
> - [Passo 3: Ability Scores](passo-3-ability-scores.md) - Strategy Pattern

</details>

---

**Navegação:** [← Passo 5: Equipment](passo-5-equipment.md) | [→ Voltar para Index](index.md)

**Última atualização:** 2024-12-27
