# C++ Cheatsheet - Referência Rápida

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do cheatsheet de C++ |

---

## 🔧 Tipos Básicos

| Tipo | Descrição | Exemplo |
|------|-----------|---------|
| `int32` | Inteiro 32 bits | `int32 Health = 100;` |
| `float` | Ponto flutuante | `float Speed = 500.0f;` |
| `bool` | Booleano | `bool bIsAlive = true;` |
| `FString` | String Unreal | `FString Name = TEXT("Player");` |
| `FName` | Nome (hash) | `FName RaceName = TEXT("Human");` |
| `TArray<T>` | Array dinâmico | `TArray<int32> Scores;` |
| `TMap<K, V>` | Mapa | `TMap<FName, int32> Attributes;` |

---

## 🏗️ Classes e Structs

### Struct

```cpp
USTRUCT(BlueprintType)
struct FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Value;
};
```

### Classe

```cpp
UCLASS(BlueprintType)
class MYPROJECT2_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
    int32 Health;
};
```

---

## 📦 Containers Unreal

### TArray

```cpp
TArray<int32> Numbers = {1, 2, 3};
Numbers.Add(4);
Numbers.Remove(2);
int32 Count = Numbers.Num();
bool bContains = Numbers.Contains(3);
```

### TMap

```cpp
TMap<FName, int32> Attributes;
Attributes.Add(TEXT("Strength"), 16);
int32 Value = Attributes.FindRef(TEXT("Strength"));
bool bHasKey = Attributes.Contains(TEXT("Strength"));
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação</b></summary>

> - [Unreal Engine C++ Documentation](https://docs.unrealengine.com/5.7/en-US/cpp-in-unreal-engine/)
> - [C++ Standard Library](https://en.cppreference.com/)

</details>

---

**Navegação:** [← Index](index.md) | [→ Unreal Engine Cheatsheet](cheatsheet-unreal.md)

**Última atualização:** 2024-12-27
