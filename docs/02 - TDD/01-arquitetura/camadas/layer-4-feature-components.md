# Camada 4: Feature Components (Lógica Específica)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## ⚡ Feature Components (Lógica Específica)

**Responsabilidade:** Gerenciar features específicas de classes (spells, abilities, etc.).

**Características:**

- Herda de `UActorComponent`
- Cada um gerencia uma feature específica
- Podem ser migrados para GAS Abilities no futuro
- Exemplos planejados: `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`

**Padrão de Implementação:**

```cpp
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT2_API USpellcastingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Spellcasting")
    void CastSpell(int32 SpellSlot);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerCastSpell(int32 SpellSlot);

    UPROPERTY(Replicated)
    TArray<FSpellSlot> SpellSlots;

    UPROPERTY(Replicated)
    int32 SpellSlotsUsed;
};
```

---

**Navegação:** [← Camada 3](layer-3-runtime-data.md) | [→ Voltar para Camadas](index.md)

**Última atualização:** 2024-12-27
