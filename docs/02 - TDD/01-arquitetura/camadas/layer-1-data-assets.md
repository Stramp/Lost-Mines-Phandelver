# Camada 1: Data Assets (Editor/Configuração)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 📝 Data Assets (Editor/Configuração)

**Responsabilidade:** Armazenar configuração estática, não contém lógica.

**Características:**

- Herda de `UDataAsset`
- `UPROPERTY(EditDefaultsOnly)` - editável apenas em defaults
- Não é replicável (não precisa em runtime)
- Funciona apenas no editor para designers
- Exemplo: `UCharacterSheetDataAsset`

**Padrão de Implementação:**

```cpp
UCLASS(BlueprintType)
class MYPROJECT2_API UCharacterSheetDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Character")
    ERace Race;

    UPROPERTY(EditDefaultsOnly, Category = "Character")
    EClass Class;

    UPROPERTY(EditDefaultsOnly, Category = "Character")
    TArray<FAbilityScore> BaseAbilityScores;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
```

---

**Navegação:** [← Voltar para Camadas](index.md) | [→ Camada 2](layer-2-bridge-components.md)

**Última atualização:** 2024-12-27
