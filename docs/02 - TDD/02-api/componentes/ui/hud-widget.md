# HUD Widget - API Reference

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação de HUD Widget |

---

## 🎯 Objetivo

Referência de API do HUD principal, correspondente ao design do GDD.

---

## 📐 Classe

```cpp
UCLASS()
class MYPROJECT2_API UHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Inicialização
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void InitializeHUD(UCharacterDataComponent* CharacterData);

    // Atualização
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealthBar(float CurrentHP, float MaxHP);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateManaBar(float CurrentMana, float MaxMana);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowDamageNumber(int32 Damage, FVector WorldPosition, bool bIsCritical);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowFloatingText(const FString& Text, FVector WorldPosition, FLinearColor Color);

protected:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* ManaBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ManaText;
};
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Inicializar HUD

```cpp
// Em um PlayerController ou HUD
void AMyPlayerController::CreateHUD()
{
    if (!HUDWidget)
    {
        HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
    }

    // Obter CharacterDataComponent do personagem
    APawn* PlayerPawn = GetPawn();
    UCharacterDataComponent* CharacterData = PlayerPawn->FindComponentByClass<UCharacterDataComponent>();

    // Inicializar HUD
    HUDWidget->InitializeHUD(CharacterData);
    HUDWidget->AddToViewport();
}
```

### Exemplo 2: Atualizar Health Bar

```cpp
// Em resposta a mudança de HP
void UHUDWidget::OnHealthChanged(float NewHealth, float MaxHealth)
{
    UpdateHealthBar(NewHealth, MaxHealth);

    // Atualizar texto
    HealthText->SetText(FText::FromString(
        FString::Printf(TEXT("%.0f / %.0f"), NewHealth, MaxHealth)
    ));

    // Mudar cor se HP baixo
    if (NewHealth / MaxHealth < 0.25f)
    {
        HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
    }
    else if (NewHealth / MaxHealth < 0.5f)
    {
        HealthBar->SetFillColorAndOpacity(FLinearColor::Yellow);
    }
    else
    {
        HealthBar->SetFillColorAndOpacity(FLinearColor::Green);
    }
}
```

### Exemplo 3: Mostrar Número de Dano

```cpp
// Em resposta a dano recebido
void UHUDWidget::OnTakeDamage(int32 Damage, FVector HitLocation, bool bIsCritical)
{
    // Converter posição do mundo para tela
    FVector2D ScreenPosition;
    APlayerController* PC = GetOwningPlayer();
    if (PC && PC->ProjectWorldLocationToScreen(HitLocation, ScreenPosition))
    {
        ShowDamageNumber(Damage, HitLocation, bIsCritical);
    }
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: UI/UX](../../../01%20-%20GDD/07-ui-ux/index.md)** - Design de interface
> - **[GDD: Feedback Visual](../../../01%20-%20GDD/07-ui-ux/feedback-visual.md)** - Feedback de ações
> - **[GDD: Sistema de Combate](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md)** - Sistema de combate
>
> **Separação de Responsabilidades:**
>
> - **GDD:** Define O QUÊ (HUD mostra HP, Mana, dano) e PORQUÊ (feedback visual claro)
> - **TDD:** Define COMO implementar (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Componentes Relacionados</b></summary>

> - **[CharacterDataComponent](../character-data-component/index.md)** - Componente que armazena dados de HP/Mana
> - **[CombatComponent](../../../08-pseudocodigo/combate/combat-system.md)** - Sistema de combate

</details>

---

**Navegação:** [← Inventory Widget](inventory-widget.md) | [→ Menu Widget](menu-widget.md)

**Última atualização:** 2024-12-27
