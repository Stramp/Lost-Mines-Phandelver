# Passo 4: Describe - Guia Algorítmico

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia do passo 4 |

---

## 🎯 Objetivo

Implementar seleção de background e descrição do personagem usando Builder Pattern.

---

## 🏗️ Design Pattern: Builder

### Implementação

```cpp
// Passo 4: Selecionar Background
FCharacterBuilder& FCharacterBuilder::SetBackground(FName BackgroundName)
{
    // 1. Carregar BackgroundDataTable
    UDataTable* BackgroundDataTable = LoadObject<UDataTable>(
        nullptr, TEXT("/Game/Data/DT_Backgrounds"));

    // 2. Validar background
    FBackgroundDataRow* BackgroundRow = BackgroundDataTable->FindRow<FBackgroundDataRow>(
        BackgroundName, TEXT("CharacterCreation"));

    if (!BackgroundRow)
    {
        // Erro: Background não encontrado
        return *this;
    }

    // 3. Aplicar skill proficiencies do background
    for (const FName& Skill : BackgroundRow->SkillProficiencies)
    {
        AddSkillProficiency(CharacterData, Skill);
    }

    // 4. Aplicar language proficiencies
    for (const FName& Language : BackgroundRow->LanguageProficiencies)
    {
        AddLanguageProficiency(CharacterData, Language);
    }

    // 5. Aplicar feature do background
    ApplyBackgroundFeature(CharacterData, BackgroundRow->FeatureName);

    // 6. Armazenar background selecionado
    CharacterData.SelectedBackground = BackgroundName;

    return *this;
}

// Passo 4b: Definir Personalidade (opcional)
FCharacterBuilder& FCharacterBuilder::SetPersonality(
    const FString& PersonalityTrait1,
    const FString& PersonalityTrait2,
    const FString& Ideal,
    const FString& Bond,
    const FString& Flaw)
{
    CharacterData.PersonalityTrait1 = PersonalityTrait1;
    CharacterData.PersonalityTrait2 = PersonalityTrait2;
    CharacterData.Ideal = Ideal;
    CharacterData.Bond = Bond;
    CharacterData.Flaw = Flaw;

    return *this;
}

// Passo 4c: Definir Alinhamento (opcional)
FCharacterBuilder& FCharacterBuilder::SetAlignment(EAlignment Alignment)
{
    CharacterData.Alignment = Alignment;
    return *this;
}
```

---

## 🔄 Fluxo Completo

```
1. Usuário seleciona background → SetBackground("Acolyte")
2. Builder valida background → Carrega BackgroundDataTable
3. Builder aplica skills → AddSkillProficiency()
4. Builder aplica languages → AddLanguageProficiency()
5. Builder aplica feature → ApplyBackgroundFeature()
6. Usuário define personalidade → SetPersonality()
7. Usuário define alinhamento → SetAlignment()
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](../../../../04-regras-dnd/criacao/character-creation-algorithm.md) - Algoritmo técnico
> - [Design Patterns](design-patterns.md) - Padrões utilizados

</details>

---

**Navegação:** [← Passo 3: Ability Scores](passo-3-ability-scores.md) | [→ Passo 5: Equipment](passo-5-equipment.md)

**Última atualização:** 2024-12-27
