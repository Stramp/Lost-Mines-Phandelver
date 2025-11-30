# UPROPERTY Cheatsheet - Referência Rápida

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do cheatsheet de UPROPERTY |

---

## 🎯 Specifiers Principais

| Specifier | Descrição | Exemplo |
|-----------|-----------|---------|
| `BlueprintReadOnly` | Leitura no Blueprint | `UPROPERTY(BlueprintReadOnly)` |
| `BlueprintReadWrite` | Leitura/escrita no Blueprint | `UPROPERTY(BlueprintReadWrite)` |
| `EditAnywhere` | Editável em instâncias | `UPROPERTY(EditAnywhere)` |
| `EditDefaultsOnly` | Editável apenas em defaults | `UPROPERTY(EditDefaultsOnly)` |
| `Replicated` | Replicável em multiplayer | `UPROPERTY(Replicated)` |
| `ReplicatedUsing` | Replicável com callback | `UPROPERTY(ReplicatedUsing = OnRep_Health)` |

---

## 📋 Exemplos Comuns

### Propriedade Editável no Editor

```cpp
UPROPERTY(EditDefaultsOnly, Category = "Character")
int32 MaxHealth;
```

### Propriedade Replicável

```cpp
UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
float Health;

UFUNCTION()
void OnRep_Health();
```

### Array Editável

```cpp
UPROPERTY(EditAnywhere, Category = "Items")
TArray<FName> Inventory;
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação</b></summary>

> - [UPROPERTY Documentation](https://docs.unrealengine.com/5.7/en-US/unreal-engine-uproperty/)

</details>

---

**Navegação:** [← Unreal Engine Cheatsheet](cheatsheet-unreal.md) | [→ UFUNCTION Cheatsheet](cheatsheet-ufunction.md)

**Última atualização:** 2024-12-27
