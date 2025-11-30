# UFUNCTION Cheatsheet - Referência Rápida

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do cheatsheet de UFUNCTION |

---

## 🎯 Specifiers Principais

| Specifier | Descrição | Exemplo |
|-----------|-----------|---------|
| `BlueprintCallable` | Chamável do Blueprint | `UFUNCTION(BlueprintCallable)` |
| `BlueprintPure` | Função pura (sem side effects) | `UFUNCTION(BlueprintPure)` |
| `BlueprintImplementableEvent` | Implementável no Blueprint | `UFUNCTION(BlueprintImplementableEvent)` |
| `BlueprintNativeEvent` | Implementação padrão em C++, sobrescrevível no Blueprint | `UFUNCTION(BlueprintNativeEvent)` |
| `Server` | RPC no servidor | `UFUNCTION(Server, Reliable)` |
| `Client` | RPC no cliente | `UFUNCTION(Client, Reliable)` |
| `NetMulticast` | RPC para todos os clientes | `UFUNCTION(NetMulticast, Reliable)` |
| `WithValidation` | Validação de RPC | `UFUNCTION(Server, Reliable, WithValidation)` |

---

## 📋 Exemplos Comuns

### Função Chamável do Blueprint

```cpp
UFUNCTION(BlueprintCallable, Category = "Character")
void InitializeCharacter();
```

### Função Pura (Sem Side Effects)

```cpp
UFUNCTION(BlueprintPure, Category = "Character")
int32 GetMaxHealth() const;
```

### RPC no Servidor

```cpp
UFUNCTION(Server, Reliable, WithValidation)
void ServerTakeDamage(float DamageAmount);

bool ServerTakeDamage_Validate(float DamageAmount);
void ServerTakeDamage_Implementation(float DamageAmount);
```

### Evento Implementável no Blueprint

```cpp
UFUNCTION(BlueprintImplementableEvent, Category = "Character")
void OnCharacterCreated();
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação</b></summary>

> - [UFUNCTION Documentation](https://docs.unrealengine.com/5.7/en-US/unreal-engine-ufunction/)

</details>

---

**Navegação:** [← UPROPERTY Cheatsheet](cheatsheet-uproperty.md) | [→ Tabelas de Referência](tabelas-referencia.md)

**Última atualização:** 2024-12-27
