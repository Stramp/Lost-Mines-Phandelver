# Camada 3: Runtime Data Components (Dados Replicáveis)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 💾 Runtime Data Components (Dados Replicáveis)

**Responsabilidade:** Armazenar dados do personagem em runtime, todas as propriedades replicáveis.

**Características:**

- Herda de `UActorComponent`
- Todas as propriedades são replicáveis (`DOREPLIFETIME`)
- Calcula atributos finais, HP, proficiência
- Preparado para migração futura para GAS Attributes
- Exemplo: `UCharacterDataComponent`

**Padrão de Implementação:**

```cpp
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT2_API UCharacterDataComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
    float Health;

    UPROPERTY(Replicated)
    float MaxHealth;

    UPROPERTY(Replicated)
    FAbilityScores FinalAbilityScores;

    UFUNCTION()
    void OnRep_Health();

    UFUNCTION(BlueprintCallable, Category = "Character")
    void CalculateFinalAttributes();

    UFUNCTION(BlueprintCallable, Category = "Character")
    void CalculateMaxHealth();
};
```

---

**Navegação:** [← Camada 2](layer-2-bridge-components.md) | [→ Camada 4](layer-4-feature-components.md)

**Última atualização:** 2024-12-27
