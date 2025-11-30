# Inventory Widget - API Reference

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação de Inventory Widget |

---

## 🎯 Objetivo

Referência de API do widget de inventário, correspondente ao design do GDD.

---

## 📐 Classe

```cpp
UCLASS()
class MYPROJECT2_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Inicialização
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void InitializeInventory(UCharacterDataComponent* CharacterData);

    // Exibição
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RefreshInventory();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ShowItemDetails(FName ItemID);

    // Interação
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void EquipItem(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UnequipItem(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void DropItem(FName ItemID);

protected:
    UPROPERTY(meta = (BindWidget))
    class UListView* ItemListView;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* WeightText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CapacityText;
};
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Inicializar Widget

```cpp
// Em um PlayerController ou HUD
void AMyPlayerController::OpenInventory()
{
    if (!InventoryWidget)
    {
        InventoryWidget = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
    }

    // Obter CharacterDataComponent do personagem
    APawn* PlayerPawn = GetPawn();
    UCharacterDataComponent* CharacterData = PlayerPawn->FindComponentByClass<UCharacterDataComponent>();

    // Inicializar widget
    InventoryWidget->InitializeInventory(CharacterData);
    InventoryWidget->AddToViewport();
}
```

### Exemplo 2: Equipar Item

```cpp
// Em resposta a clique do jogador
void UInventoryWidget::OnItemEquipButtonClicked(FName ItemID)
{
    // Validar se pode equipar
    if (CanEquipItem(ItemID))
    {
        EquipItem(ItemID);
        RefreshInventory(); // Atualizar display
    }
    else
    {
        ShowError(TEXT("Não é possível equipar este item"));
    }
}
```

### Exemplo 3: Atualizar Peso e Capacidade

```cpp
void UInventoryWidget::RefreshInventory()
{
    if (!CharacterDataComponent)
    {
        return;
    }

    // Atualizar lista de itens
    UpdateItemList();

    // Atualizar peso e capacidade
    float CurrentWeight = CharacterDataComponent->GetCurrentWeight();
    float MaxWeight = CharacterDataComponent->GetMaxWeight();

    WeightText->SetText(FText::FromString(
        FString::Printf(TEXT("Peso: %.1f / %.1f kg"), CurrentWeight, MaxWeight)
    ));

    int32 CurrentCapacity = CharacterDataComponent->GetItemCount();
    int32 MaxCapacity = CharacterDataComponent->GetMaxItemCapacity();

    CapacityText->SetText(FText::FromString(
        FString::Printf(TEXT("Itens: %d / %d"), CurrentCapacity, MaxCapacity)
    ));
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Inventário](../../../01%20-%20GDD/02-mecanicas/inventario.md)** - Regras de inventário D&D 5e
> - **[GDD: UI/UX](../../../01%20-%20GDD/07-ui-ux/index.md)** - Design de interface
> - **[GDD: Wireframes](../../../01%20-%20GDD/07-ui-ux/wireframes.md)** - Esboços de UI
>
> **Separação de Responsabilidades:**
>
> - **GDD:** Define O QUÊ (sistema de inventário, peso, capacidade) e PORQUÊ (experiência D&D 5e)
> - **TDD:** Define COMO implementar (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Componentes Relacionados</b></summary>

> - **[CharacterDataComponent](../character-data-component/index.md)** - Componente que armazena dados de inventário
> - **[Data Tables - Items](../../../05-guias/data-tables/index.md)** - Data Tables de itens

</details>

---

**Navegação:** [← Voltar](index.md) | [→ HUD Widget](hud-widget.md)

**Última atualização:** 2024-12-27
