# Passo 5: Equipment - Guia Algorítmico

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do guia do passo 5 |

---

## 🎯 Objetivo

Implementar seleção de equipamento inicial usando Factory Pattern e Builder Pattern.

---

## 🏗️ Design Pattern: Factory + Builder

### Implementação

```cpp
// Passo 5: Aplicar Equipamento Inicial
FCharacterBuilder& FCharacterBuilder::ApplyStartingEquipment()
{
    // 1. Obter equipamento inicial da classe
    TArray<FName> ClassEquipment = GetClassStartingEquipment(CharacterData.SelectedClass);

    // 2. Obter equipamento inicial do background
    TArray<FName> BackgroundEquipment = GetBackgroundStartingEquipment(
        CharacterData.SelectedBackground);

    // 3. Usar Factory para criar itens
    for (const FName& ItemName : ClassEquipment)
    {
        FItem* Item = FItemFactory::CreateItem(ItemName);
        if (Item)
        {
            CharacterData.Inventory.Add(Item);
        }
    }

    for (const FName& ItemName : BackgroundEquipment)
    {
        FItem* Item = FItemFactory::CreateItem(ItemName);
        if (Item)
        {
            CharacterData.Inventory.Add(Item);
        }
    }

    // 4. Equipar itens padrão (se aplicável)
    EquipDefaultItems(CharacterData);

    return *this;
}
```

---

## 🔄 Fluxo Completo

```
1. Builder obtém equipamento da classe → GetClassStartingEquipment()
2. Builder obtém equipamento do background → GetBackgroundStartingEquipment()
3. Factory cria itens → FItemFactory::CreateItem()
4. Builder adiciona ao inventário → CharacterData.Inventory.Add()
5. Builder equipa itens padrão → EquipDefaultItems()
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Character Creation Algorithm](../../../../04-regras-dnd/criacao/character-creation-algorithm.md) - Algoritmo técnico
> - [Design Patterns](design-patterns.md) - Padrões utilizados

</details>

---

**Navegação:** [← Passo 4: Describe](passo-4-describe.md) | [→ Design Patterns](design-patterns.md)

**Última atualização:** 2024-12-27
