# Menu Widget - API Reference

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação de Menu Widget |

---

## 🎯 Objetivo

Referência de API dos menus do jogo, correspondente ao design do GDD.

---

## 📐 Classes

### UMainMenuWidget

```cpp
UCLASS()
class MYPROJECT2_API UMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void OpenOptions();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void OpenCharacterCreation();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    void QuitGame();
};
```

### UOptionsMenuWidget

```cpp
UCLASS()
class MYPROJECT2_API UOptionsMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Options")
    void ApplySettings();

    UFUNCTION(BlueprintCallable, Category = "Options")
    void ResetToDefaults();
};
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Abrir Menu Principal

```cpp
// Em um GameMode ou PlayerController
void AMyGameMode::OpenMainMenu()
{
    if (!MainMenuWidget)
    {
        MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
    }

    MainMenuWidget->AddToViewport();

    // Pausar jogo
    GetWorld()->GetFirstPlayerController()->SetPause(true);

    // Mostrar cursor
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}
```

### Exemplo 2: Navegar para Opções

```cpp
// Em resposta a clique do botão "Opções"
void UMainMenuWidget::OnOptionsButtonClicked()
{
    // Criar widget de opções
    if (!OptionsMenuWidget)
    {
        OptionsMenuWidget = CreateWidget<UOptionsMenuWidget>(GetOwningPlayer(), OptionsMenuWidgetClass);
    }

    // Remover menu principal
    RemoveFromParent();

    // Adicionar menu de opções
    OptionsMenuWidget->AddToViewport();
}
```

### Exemplo 3: Aplicar Configurações

```cpp
// Em resposta a clique do botão "Aplicar"
void UOptionsMenuWidget::OnApplyButtonClicked()
{
    // Salvar configurações
    ApplySettings();

    // Voltar para menu principal
    RemoveFromParent();

    // Recriar menu principal
    if (MainMenuWidget)
    {
        MainMenuWidget->AddToViewport();
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
> - **[GDD: Fluxo de Navegação](../../../01%20-%20GDD/07-ui-ux/fluxo-navegacao.md)** - Navegação entre telas
> - **[GDD: Wireframes](../../../01%20-%20GDD/07-ui-ux/wireframes.md)** - Esboços de UI
>
> **Separação de Responsabilidades:**
>
> - **GDD:** Define O QUÊ (menus, navegação, opções) e PORQUÊ (experiência do usuário)
> - **TDD:** Define COMO implementar (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Componentes Relacionados</b></summary>

> - **[Character Creation Widget](../../../05-guias/algoritmicos/character-creation/index.md)** - Criação de personagem
> - **[Inventory Widget](inventory-widget.md)** - Widget de inventário

</details>

---

**Navegação:** [← HUD Widget](hud-widget.md) | [→ Voltar para Componentes](../index.md)

**Última atualização:** 2024-12-27
