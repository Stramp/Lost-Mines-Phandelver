# Camada 2: Bridge Components (Aplicação de Regras)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🌉 Bridge Components (Aplicação de Regras)

**Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.

**Características:**

- Herda de `UActorComponent`
- Executa apenas no servidor/local (não replicável)
- Aplica regras de raça e classe (`ApplyRaceBonuses()`, `ApplyClassFeatures()`)
- Carrega dados do Data Asset para Runtime Component
- Exemplo: `UCharacterSheetComponent`

**Padrão de Implementação:**

```cpp
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT2_API UCharacterSheetComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Character")
    void InitializeFromDataAsset(UCharacterSheetDataAsset* DataAsset);

    UFUNCTION(BlueprintCallable, Category = "Character")
    void ApplyRaceBonuses();

    UFUNCTION(BlueprintCallable, Category = "Character")
    void ApplyClassFeatures();

private:
    UPROPERTY()
    UCharacterSheetDataAsset* SourceDataAsset;

    UPROPERTY()
    class UCharacterDataComponent* CharacterDataComponent;
};
```

---

**Navegação:** [← Camada 1](layer-1-data-assets.md) | [→ Camada 3](layer-3-runtime-data.md)

**Última atualização:** 2024-12-27
