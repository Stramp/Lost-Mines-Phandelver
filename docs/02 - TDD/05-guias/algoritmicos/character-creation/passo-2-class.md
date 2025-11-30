# Passo 2: Class - Guia Algorítmico

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia do passo 2 |

---

## 🎯 Objetivo

Implementar seleção de classe e aplicação de proficiências usando Builder Pattern.

---

## 🏗️ Design Pattern: Builder

### Implementação

```cpp
// Passo 2: Selecionar Classe
FCharacterBuilder& FCharacterBuilder::SetClass(FName ClassName)
{
    // 1. Carregar ClassDataTable
    UDataTable* ClassDataTable = LoadObject<UDataTable>(
        nullptr, TEXT("/Game/Data/DT_Classes"));

    // 2. Validar classe
    FClassDataRow* ClassRow = ClassDataTable->FindRow<FClassDataRow>(
        ClassName, TEXT("CharacterCreation"));

    if (!ClassRow)
    {
        // Erro: Classe não encontrada
        return *this;
    }

    // 3. Aplicar proficiências da classe
    FMulticlassMotor::ApplyClassProficiencies(CharacterData, ClassRow);

    // 4. Aplicar features de nível 1
    TArray<FClassFeature> Level1Features = FMulticlassMotor::GetFeaturesForLevel(
        ClassRow, 1);

    for (const FClassFeature& Feature : Level1Features)
    {
        ApplyFeature(CharacterData, Feature);
    }

    // 5. Armazenar classe selecionada
    CharacterData.SelectedClass = ClassName;
    CharacterData.ClassLevels.Add(ClassName, 1);

    return *this;
}
```

---

## 🔄 Fluxo Completo

```
1. Usuário seleciona classe → SetClass("Fighter")
2. Builder valida classe → Carrega ClassDataTable
3. Builder aplica proficiências → FMulticlassMotor::ApplyClassProficiencies()
4. Builder aplica features nível 1 → GetFeaturesForLevel(ClassRow, 1)
5. Builder armazena classe → CharacterData.ClassLevels["Fighter"] = 1
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](../../../../04-regras-dnd/criacao/character-creation-algorithm.md) - Algoritmo técnico
> - [Multiclass Motor](../../../../02-api/motores/index.md) - Motor de multiclassing
> - [Design Patterns](design-patterns.md) - Padrões utilizados

</details>

---

**Navegação:** [← Passo 1: Race](passo-1-race.md) | [→ Passo 3: Ability Scores](passo-3-ability-scores.md)

**Última atualização:** 2024-12-27
