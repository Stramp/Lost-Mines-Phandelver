# Arquitetura de Dados de Alto Desempenho: Carregamento Centralizado via Data Registry

**Data:** 2024-12-27
**Versão:** 1.0
**Status:** ✅ **Especificação Técnica Completa**

---

## 📊 Resumo Executivo

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Filosofia Arquitetural</b></summary>

> **Paradigma:** Carregamento Centralizado com Acesso em Tempo Real (Centralized Loading with Real-Time Access)
>
> **Premissa Fundamental:**
>
> - ✅ Inicialização única de tabelas via subsistema singleton
> - ✅ Eliminação de carregamentos redundantes por ativo
> - ✅ Acesso em tempo constante O(1) via Hash Maps
> - ✅ Alinhado com Data-Oriented Design (DOD)
> - ✅ Preparado para simulações em larga escala
>
> **Mecanismo:** `UDataRegistrySubsystem` (plugin Data Registry nativo do Unreal Engine 5.7)
>
> **Diretriz Arquitetural:** Tabelas Centralizadas são **estritamente imutáveis (Estáticas)** durante a sessão de jogo

</details>

</details>

## 🏗️ Arquitetura: Subsistemas vs Singletons Manuais

### 2.1 O Declínio do GameInstance Monolítico

**Problema Histórico:**
- Uso excessivo de `UGameInstance` resultava em "God Classes"
- Acoplamento excessivo e responsabilidades difusas
- Dificuldade de manutenção e teste

**Solução Moderna (UE5):**
- **Programming Subsystems** emergiram como padrão de facto
- Objetos gerenciados automaticamente (`USubsystem`)
- Ciclo de vida controlado pela engine
- Elimina necessidade de hooks manuais de inicialização

### 2.2 UDataRegistrySubsystem: A Solução Nativa

**Por que usar Data Registry ao invés de subsistema manual:**

| Característica | Subsistema Manual | Data Registry |
|----------------|-------------------|---------------|
| **Gerenciamento de Ciclo de Vida** | Manual (necessita overrides) | Automático (Gerenciado pela Engine) |
| **Resolução de Dependências** | Manual (LoadObject/StaticLoadObject) | Automática via AssetManager |
| **Estratégia de Cache** | Implementação customizada | Políticas configuráveis (Preload/LRU) |
| **Complexidade de Acesso** | Depende da implementação | **O(1) via Hash Map interno** |
| **Suporte a Modding/DLC** | Complexo (merge manual) | Nativo (Prioridade de Fontes) |
| **Carregamento Assíncrono** | Implementação manual | API nativa (AcquireItem) |

**Benefícios do Data Registry:**
- ✅ Cache centralizado (previne I/O redundante)
- ✅ Camada de indireção (ID Mapping via `FDataRegistryId`)
- ✅ Carregamento assíncrono nativo (evita hitches)
- ✅ Suporte a DLC/patches (sobrescrita de dados base)

---

## ⚙️ Implementação Técnica

### 3.1 Fase de Inicialização: Configuração do Registry

**Passos de Configuração:**

1. **Habilitar Plugin:**
   ```cpp
   // MyProject2.Build.cs
   PublicDependencyModuleNames.AddRange(new string[] {
       "DataRegistry"  // Adicionar plugin Data Registry
   });
   ```

2. **Criar Data Registry Asset:**
   - Criar ativo `UDataRegistry` (ex: `DR_GameItems`)
   - Atua como manifesto de configuração

3. **Configurar Fontes de Dados:**
   - Usar **Meta Sources** para descoberta automática
   - Escanear diretórios específicos (ex: `/Game/Data/Tables/Items`)
   - Registrar automaticamente Data Tables com estrutura específica

4. **Política de Cache:**
   - Configurar para **Preload** ou **CacheAll**
   - Carrega e mantém todas as tabelas residentes na inicialização
   - Elimina latência de carregamento durante gameplay

### 3.2 Fluxo de Requisição em Tempo Real

**Mecanismo de Acesso:**

```cpp
// 1. Aquisição (Acquire)
// Com política Preload, itens já estão "Acquired" na memória

// 2. Recuperação (Retrieval) - O(1)
UDataRegistrySubsystem* Registry = UDataRegistrySubsystem::Get();
const FGameItemDefinition* ItemData = Registry->GetCachedItem<FGameItemDefinition>(ItemID);
```

**Vantagem Arquitetural:**
- Desacopla consumidor da fonte de dados
- Actor conhece apenas ID (`Weapon_Rifle_01`)
- Subsistema resolve ID para endereço de memória instantaneamente
- Elimina referências fortes (Hard References) que causam carregamento em cascata

---

## 🔬 Análise Algorítmica: O(1) e FindRow

### 4.1 Estrutura Interna do UDataTable

**Representação em Memória:**
```cpp
// Estrutura interna do UDataTable
TMap<FName, uint8*> RowMap;
```

- **Chave (Key):** `FName` - Identificador leve (comparação de inteiros, não strings)
- **Valor (Value):** `uint8*` - Ponteiro genérico para dados da linha

### 4.2 Complexidade Temporal do FindRow

**Processo de Busca:**
1. **Hashing:** Calcula hash do `RowName` (trivial para `FName`)
2. **Indexação:** Usa hash para indexar tabela esparsa (`TMap`)
3. **Resolução de Colisões:** Encadeamento ou endereçamento aberto
4. **Resultado:** **Complexidade média O(1)**

**Confirmação Técnica:**
- ✅ `FindRow` executa busca em Hash Map
- ✅ Não ocorre iteração linear O(n)
- ✅ Tempo de acesso não escala com número de linhas
- ✅ Busca em 10 linhas ≈ busca em 10.000 linhas

### 4.3 Coerência de Cache e DOD

**Considerações:**
- `RowMap` armazena ponteiros (não dados contíguos)
- Pode causar Cache Misses ao dereferenciar ponteiros
- Para gameplay padrão (UI, Inventário): custo negligenciável
- Para simulação massiva (100.000+ unidades): considerar MassEntity (SoA)

---

## 🎯 Diretriz: Dados Estáticos vs Dinâmicos

### 5.1 Veredito: Imutabilidade Estrita

**Regra Arquitetural:** Tabelas de Dados devem ser **estritamente imutáveis (Estáticas)** durante a sessão.

**Justificativa Técnica:**

1. **Thread Safety:**
   - Unreal Engine é altamente paralelizado
   - `TMap` não é thread-safe para escrita concorrente
   - Modificações em runtime causam race conditions

2. **Integridade do Ativo:**
   - `UDataTable` é ativo serializado
   - Modificações em runtime confundem "Definição" vs "Estado"
   - Quebra Hot Reload/Live Coding no editor

3. **Fragmentação de Memória:**
   - Inserção dinâmica causa rehash/realocação
   - Invalida ponteiros cacheados
   - Quebra estabilidade da referência global

### 5.2 Padrão Flyweight para Dados Dinâmicos

**Arquitetura Híbrida:**

**Estado Intrínseco (Estático/Pesado):**
- Armazenado no Data Registry
- Dados comuns a todas as instâncias (Nome, Dano Base, Mesh, Ícone)
- Carregado uma única vez

**Estado Extrínseco (Dinâmico/Leve):**
- Armazenado na Instância do Actor/Componente
- Dados únicos da instância (ID, Durabilidade Atual, Nível de Upgrade)
- Mutável durante gameplay

**Exemplo de Fluxo:**
```cpp
// Consulta Estado Extrínseco (instância)
int32 CurrentAmmo = WeaponActor->CurrentAmmo;

// Consulta Estado Intrínseco (Registry)
const FWeaponDefinition* WeaponDef = Registry->GetCachedItem<FWeaponDefinition>(WeaponID);
float BaseDamage = WeaponDef->BaseDamage;

// Cálculo combina ambos
float FinalDamage = BaseDamage * WeaponActor->UpgradeMultiplier;
```

**Benefício:** Memória da "Definição da Arma" paga apenas uma vez, independente de 1 ou 1.000 armas instanciadas.

---

## 💻 Guia de Implementação (C++)

### 6.1 Definição das Estruturas de Dados

```cpp
// GameItemDefinitions.h
#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameItemDefinitions.generated.h"

/**
 * Dados Intrínsecos (Estáticos) - Vivem no Data Registry
 */
USTRUCT(BlueprintType)
struct FGameItemDefinition : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
    FText DisplayName;

    // Referência Suave (evita carregamento imediato)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
    TSoftObjectPtr<UStaticMesh> WorldMesh;

    // Atributos base imutáveis
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    float BaseDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
    int32 MaxStackSize;
};

/**
 * Dados Extrínsecos (Dinâmicos) - Vivem no Inventário/Actor
 */
USTRUCT(BlueprintType)
struct FGameItemInstance
{
    GENERATED_BODY()

    // Link para definição estática no Registry
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FDataRegistryId ItemID;

    // Estado mutável único desta instância
    UPROPERTY(SaveGame, BlueprintReadWrite)
    int32 CurrentStackCount;

    UPROPERTY(SaveGame, BlueprintReadWrite)
    float CurrentDurability;
};
```

### 6.2 Acesso ao Subsistema

```cpp
// GameDataHelpers.cpp
#include "DataRegistrySubsystem.h"

const FGameItemDefinition* UGameDataHelpers::GetItemDefinition(FDataRegistryId ItemID)
{
    UDataRegistrySubsystem* RegistrySubsystem = UDataRegistrySubsystem::Get();

    if (RegistrySubsystem)
    {
        // Acesso O(1) via GetCachedItem
        return RegistrySubsystem->GetCachedItem<FGameItemDefinition>(ItemID);
    }

    return nullptr;
}
```

### 6.3 Carregamento Assíncrono (Opcional)

```cpp
void UInventoryComponent::EquipItem(FDataRegistryId ItemID)
{
    UDataRegistrySubsystem* Registry = UDataRegistrySubsystem::Get();

    // Tenta obter do cache primeiro (O(1))
    const FGameItemDefinition* CachedData =
        Registry->GetCachedItem<FGameItemDefinition>(ItemID);

    if (CachedData)
    {
        SpawnEquippedItem(CachedData);
    }
    else
    {
        // Carregamento assíncrono se não estiver em cache
        FDataRegistryItemAcquiredCallback Callback;
        Callback.BindUObject(this, &UInventoryComponent::OnItemDataLoaded);
        Registry->AcquireItem(ItemID, Callback);
    }
}
```

---

## 💾 Gerenciamento de Memória: Hard vs Soft References

### 7.1 O Perigo das Referências Fortes

**Problema:**
```cpp
// ❌ ERRADO - Hard Reference
UPROPERTY(EditAnywhere)
UStaticMesh* WorldMesh;  // Força carregamento imediato de todos os meshes
```

**Consequência:**
- Carregamento de 1.000 itens = carregamento de 1.000 meshes
- Gigabytes de geometria/texturas na VRAM instantaneamente
- Travamentos massivos de inicialização
- Exaustão de memória

### 7.2 Solução: TSoftObjectPtr

**Correto:**
```cpp
// ✅ CORRETO - Soft Reference
UPROPERTY(EditAnywhere)
TSoftObjectPtr<UStaticMesh> WorldMesh;  // Apenas caminho (string leve)
```

**Benefícios:**
- Data Registry carrega apenas metadados (texto, números)
- Ativos pesados permanecem descarregados
- Carregamento sob demanda via `UAssetManager` ou `StreamableManager`
- Pegada de memória do subsistema extremamente baixa

**Alinhamento DOD:**
- Dados "quentes" (frequentemente acessados) = compactos
- Dados "frios" (ativos pesados) = separados e carregados sob demanda

---

## 🔄 Comparativo: Lyra vs Data Registry

### 8.1 Abordagem Lyra (PrimaryDataAssets)

**Características:**
- Utiliza `UAssetManager` e `PrimaryDataAssets`
- Definições são subclasses de `UObject` (ex: `ULyraInventoryItemDefinition`)
- Permite herança e lógica encapsulada

**Overhead:**
- Cada definição = overhead de `UObject`
- Funções virtuais, reflexão complexa, GC individual
- Maior consumo de memória

### 8.2 Abordagem Data Registry (Proposta)

**Características:**
- Utiliza `UScriptStructs` (Tabelas)
- Structs são significativamente mais leves que `UObjects`
- Sem overhead de funções virtuais ou GC individual

**Vantagem:**
- ✅ Performance bruta superior (milhares de definições)
- ✅ Throughput de memória e CPU otimizado
- ✅ Carregamento centralizado puro
- ⚠️ Sacrifica capacidade de herança de dados

**Conclusão:** Para carregamento centralizado puro e performance bruta, Data Registry + Structs é superior.

---

## 🚀 Integração Futura: MassEntity (ECS)

### 9.1 Escalabilidade Massiva

**Cenário:** Simulação de 50.000+ unidades

**Problema:** Acesso individual via `FindRow` pode se tornar gargalo devido à dispersão de memória.

**Solução:** Integração com MassEntity

### 9.2 Conversão para Shared Fragments

**Processo:**
1. Na inicialização, iterar dados estáticos do Registry
2. Converter em **Shared Fragments** no MassEntity
3. Shared Fragment armazenado uma única vez na memória
4. Apontado por todos os arquétipos de entidades que o utilizam

**Benefício:**
- Implementação DOD definitiva do padrão Flyweight
- Estrutura `FGameItemDefinition` mapeia diretamente para `FMassSharedFragment`
- Mesma definição alimenta gameplay tradicional (Actors) e simulação de massa (ECS)
- Sem duplicação de autoria

---

## ✅ Diretrizes Finais de Engenharia

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Checklist de Implementação</b></summary>

> **Mecanismo:**
>
> - [ ] Adotar `UDataRegistrySubsystem` com fontes baseadas em MetaSource
> - [ ] Configurar descoberta automática de tabelas
> - [ ] Política de cache: Preload ou CacheAll
>
> **Algoritmo:**
>
> - [ ] Confiar na complexidade O(1) do `FindRow` (via `GetCachedItem`)
> - [ ] Garantida pela implementação interna de Hashing do `TMap`
> - [ ] Evitar iterações lineares O(n) no fluxo de acesso em tempo real
>
> **Mutabilidade:**
>
> - [ ] Manter tabelas estritamente Estáticas
> - [ ] Gerenciar estado dinâmico via instâncias de structs leves
> - [ ] Aplicar padrão Flyweight (Estado Intrínseco vs Extrínseco)
>
> **Memória:**
>
> - [ ] Utilizar `TSoftObjectPtr` para todos os ativos pesados
> - [ ] Prevenir saturação de memória na inicialização
> - [ ] Carregamento sob demanda via `UAssetManager` ou `StreamableManager`

</details>

</details>

## 🎯 Conclusão

A arquitetura de **Carregamento Centralizado com Acesso em Tempo Real** no Unreal Engine 5.7 deve ser implementada utilizando o `UDataRegistrySubsystem`. Esta escolha fornece:

- ✅ Infraestrutura robusta e testada em produção
- ✅ Otimizada pela Epic Games
- ✅ Elimina fragilidade de soluções manuais
- ✅ Equilíbrio ideal entre desempenho, segurança de memória e manutenibilidade

**Próximos Passos:**
1. Configurar Data Registry Asset no projeto
2. Migrar Data Tables para Registry Sources
3. Implementar helpers de acesso (`GetCachedItem`)
4. Aplicar padrão Flyweight para dados dinâmicos
5. Preparar integração futura com MassEntity (se necessário)

---

## 📚 Referências

- [UDataRegistrySubsystem Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/udataregistrysubsystem-in-unreal-engine)
- [Data Registries Quick Start Guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/quick-start-guide-for-unreal-engine-data-registries)
- [Programming Subsystems](https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-subsystems-in-unreal-engine)
- [Flyweight Pattern - Game Programming Patterns](https://gameprogrammingpatterns.com/flyweight.html)
- [Mass Gameplay Overview](https://dev.epicgames.com/documentation/en-us/unreal-engine/overview-of-mass-gameplay-in-unreal-engine)

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
**Status:** ✅ **Especificação Técnica Completa**
