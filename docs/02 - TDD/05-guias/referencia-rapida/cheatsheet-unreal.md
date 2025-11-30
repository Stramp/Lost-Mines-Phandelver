# Unreal Engine Cheatsheet - Referência Rápida

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do cheatsheet de Unreal Engine |

---

## 🎯 Macros Principais

| Macro | Uso |
|-------|-----|
| `UCLASS()` | Marca classe para reflexão |
| `USTRUCT()` | Marca struct para reflexão |
| `UPROPERTY()` | Marca propriedade para reflexão |
| `UFUNCTION()` | Marca função para reflexão |
| `GENERATED_BODY()` | Gera código de reflexão |

---

## 📦 Tipos Unreal

| Tipo | Descrição |
|------|-----------|
| `AActor*` | Actor no mundo |
| `UActorComponent*` | Componente de actor |
| `UDataAsset*` | Data Asset |
| `UDataTable*` | Data Table |
| `UObject*` | Objeto base Unreal |

---

## 🔧 Funções Comuns

### Carregar Data Table

```cpp
UDataTable* DataTable = LoadObject<UDataTable>(
    nullptr, TEXT("/Game/Data/DT_Races"));
```

### Buscar Row

```cpp
FRaceDataRow* Row = DataTable->FindRow<FRaceDataRow>(
    TEXT("Human"), TEXT("Context"));
```

### Logging

```cpp
UE_LOG(LogTemp, Warning, TEXT("Message: %s"), *StringValue);
UE_LOG(LogTemp, Error, TEXT("Error: %d"), IntValue);
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação</b></summary>

> - [Unreal Engine Documentation](https://docs.unrealengine.com/5.7/)
> - [Unreal Engine C++ API Reference](https://docs.unrealengine.com/5.7/en-US/API/)

</details>

---

**Navegação:** [← C++ Cheatsheet](cheatsheet-cpp.md) | [→ UPROPERTY Cheatsheet](cheatsheet-uproperty.md)

**Última atualização:** 2024-12-27
