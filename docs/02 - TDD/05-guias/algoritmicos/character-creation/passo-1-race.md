# Passo 1: Race - Guia Algorítmico

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia do passo 1 |

---

## 🎯 Objetivo

Implementar seleção de raça e aplicação de bônus raciais usando Builder Pattern.

---

## 🏗️ Design Pattern: Builder

### Estrutura

```cpp
// Builder para criação de personagem
class FCharacterBuilder
{
public:
    FCharacterBuilder& SetRace(FName RaceName);
    FCharacterBuilder& SetSubrace(FName SubraceName);
    FCharacterBuilder& Build();

private:
    FCharacterData CharacterData;
};
```

### Implementação

```cpp
// Passo 1: Selecionar Raça
FCharacterBuilder& FCharacterBuilder::SetRace(FName RaceName)
{
    // 1. Carregar RaceDataTable
    UDataTable* RaceDataTable = LoadObject<UDataTable>(
        nullptr, TEXT("/Game/Data/DT_Races"));

    // 2. Validar raça
    FRaceDataRow* RaceRow = RaceDataTable->FindRow<FRaceDataRow>(
        RaceName, TEXT("CharacterCreation"));

    if (!RaceRow)
    {
        // Erro: Raça não encontrada
        return *this;
    }

    // 3. Aplicar bônus raciais base
    FRaceBonusMotor::ApplyBaseRaceBonuses(CharacterData, RaceRow);

    // 4. Armazenar raça selecionada
    CharacterData.SelectedRace = RaceName;

    return *this;
}

// Passo 1b: Selecionar Sub-raça (opcional)
FCharacterBuilder& FCharacterBuilder::SetSubrace(FName SubraceName)
{
    if (CharacterData.SelectedRace == NAME_None)
    {
        // Erro: Deve selecionar raça primeiro
        return *this;
    }

    // Carregar RaceDataTable
    UDataTable* RaceDataTable = LoadObject<UDataTable>(
        nullptr, TEXT("/Game/Data/DT_Races"));

    FRaceDataRow* RaceRow = RaceDataTable->FindRow<FRaceDataRow>(
        CharacterData.SelectedRace, TEXT("CharacterCreation"));

    if (!RaceRow)
    {
        return *this;
    }

    // Validar que sub-raça pertence à raça
    if (!RaceRow->SubraceNames.Contains(SubraceName))
    {
        // Erro: Sub-raça inválida
        return *this;
    }

    // Aplicar bônus de sub-raça
    FRaceDataRow* SubraceRow = RaceDataTable->FindRow<FRaceDataRow>(
        SubraceName, TEXT("CharacterCreation"));

    if (SubraceRow)
    {
        FRaceBonusMotor::ApplySubraceBonuses(CharacterData, SubraceRow);
    }

    CharacterData.SelectedSubrace = SubraceName;

    return *this;
}
```

---

## 🔄 Fluxo Completo

```
1. Usuário seleciona raça → SetRace("Human")
2. Builder valida raça → Carrega RaceDataTable
3. Builder aplica bônus → FRaceBonusMotor::ApplyBaseRaceBonuses()
4. Se houver sub-raça → SetSubrace("Variant Human")
5. Builder aplica bônus de sub-raça → FRaceBonusMotor::ApplySubraceBonuses()
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](../../../../04-regras-dnd/criacao/character-creation-algorithm.md) - Algoritmo técnico
> - [Race Bonus Motor](../../../../02-api/motores/index.md) - Motor de bônus raciais
> - [Design Patterns](design-patterns.md) - Padrões utilizados

</details>

---

**Navegação:** [← Index](index.md) | [→ Passo 2: Class](passo-2-class.md)

**Última atualização:** 2024-12-27
