---
title: "Technical Plan: Inventory Boilerplate"
category: planning
tags: [technical-plan, inventory, boilerplate, module]
last_updated: 2024-12-27
difficulty: advanced
related: [roadmap.md, roadmap-tecnico-itens-iniciais.md]
---

**Navegação:** [Home](../../README.md) > [Documentação](index.md) > [Planejamento](planning/index.md) > Technical Plan: Inventory

# Plano Técnico: Boilerplate do Módulo de Inventário - D&D 5e

> **Documento Técnico:** Plano detalhado para criação do boilerplate do módulo de inventário na criação de ficha, seguindo abordagem modular e expansível.

**Status:** 📋 Planejado
**Prioridade:** 🟡 Média
**Estimativa:** 8-12 horas (1-2 dias)
**Fase:** Fase 1 - Sistema de Fichas (Expansão) → Fase 4 - Equipamentos (Módulo Completo)

---

## 🎯 Estratégia Modular

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Abordagem em 3 Fases</b></summary>

> **Fase 1 (Boilerplate - Agora):** Mockup simples na ficha com estruturas modulares alinhadas
>

> - Estruturas em `Data/Structures/` (independentes, reutilizáveis)
> - Mockup hardcoded: 1 slot de corpo que aceita 1 mochila
> - Helpers básicos em `Utils/` (sem acoplamento)
> - Permite finalizar criação de ficha sem módulo completo
>
> **Fase 2 (Módulo Completo - Futuro):** Criar `Source/MyProject2/Inventory/`
>
> - `UInventoryComponent` (runtime, replicável)
> - `FInventoryMotor` (lógica de inventário)
> - Reutiliza estruturas já criadas (zero refatoração)
>
> **Fase 3 (Integração - Futuro):** Conectar ficha com módulo
>
> - Migrar dados do mockup para componente
> - Remover mockup hardcoded
> - Sistema completo funcional
>
</details>
---

## 📚 Análise das Regras D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Regras de Inventário</b></summary>

> **1. Carrying Capacity:**
>

> - Peso máximo = Strength Score × 15 lbs
> - Exemplo: Strength 16 = 240 lbs máximo
> - Itens têm peso individual (ex: Longsword = 3 lbs)
>
> **2. Slots e Containers:**
>
> - Personagem tem 1 slot de corpo (pode equipar mochila)
> - Mochila é um container com slots internos
> - Cada mochila tem capacidade de slots e peso máximo
> - Exemplo: Backpack padrão = 30 slots, peso máximo 30 lbs
>
> **3. Itens Iniciais:**
>
> - Classe fornece equipamentos iniciais
> - Background adiciona itens adicionais
> - Itens começam no inventário (não equipados)
> - Validação de peso ao criar ficha
>
</details>
---

## 🏗️ Arquitetura Proposta

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Padrões e Princípios</b></summary>

> **Seguindo Padrões Existentes:**
>

> - ✅ **Data-Driven:** Estruturas em `Data/Structures/`, dados em Data Tables
> - ✅ **Modular:** Estruturas independentes, reutilizáveis no futuro módulo
> - ✅ **Clean Code:** Helpers puros em `Utils/`, sem acoplamento
> - ✅ **Expansível:** Mockup simples que evolui para módulo completo sem quebrar
> - ✅ **Single Responsibility:** Cada estrutura tem responsabilidade única
>
</details>
---

## 📋 Implementação Detalhada - Fase 1 (Boilerplate)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Estruturas e Mockup</b></summary>

> ### **Fase 1.1: Estruturas Modulares (Data/Structures/)**
>

</details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.1 - Criar FInventorySlot.h</summary>

    > **Arquivo:** `Source/MyProject2/Data/Structures/FInventorySlot.h` (NOVO)
    >
    > **Estrutura:**
    >
    > ```cpp
    > USTRUCT(BlueprintType)
    > struct MYPROJECT2_API FInventorySlot
    > {
    >     GENERATED_BODY()
    >
    >     /**
    >      * ID do item neste slot (ex: "ITM_WPN_Longsword").
    >      * NAME_None se slot vazio.
    >      */
    >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    >     FName ItemID = NAME_None;
    >
    >     /**
    >      * Quantidade do item neste slot (para itens stackáveis).
    >      * Padrão: 1 (itens não stackáveis).
    >      */
    >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    >     int32 Quantity = 1;
    >
    >     FInventorySlot() : ItemID(NAME_None), Quantity(1) {}
    >
    >     FInventorySlot(const FName& InItemID, int32 InQuantity = 1)
    >         : ItemID(InItemID), Quantity(InQuantity) {}
    >
    >     /** Retorna true se slot está vazio */
    >     bool IsEmpty() const { return ItemID == NAME_None; }
    > };
    > ```
    >
    > **Nota:** Estrutura modular, será reutilizada no módulo completo.

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.2 - Criar FInventoryContainer.h</summary>

    > **Arquivo:** `Source/MyProject2/Data/Structures/FInventoryContainer.h` (NOVO)
    >
    > **Estrutura:**
    >
    > ```cpp
    > USTRUCT(BlueprintType)
    > struct MYPROJECT2_API FInventoryContainer
    > {
    >     GENERATED_BODY()
    >
    >     /**
    >      * ID do container (ex: "ITM_OTH_Backpack").
    >      * NAME_None se não há container.
    >      */
    >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    >     FName ContainerItemID = NAME_None;
    >
    >     /**
    >      * Slots dentro do container.
    >      * Tamanho máximo determinado por MaxSlots do ItemDataTable.
    >      */
    >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
    >     TArray<FInventorySlot> Slots;
    >
    >     FInventoryContainer() : ContainerItemID(NAME_None) {}
    >
    >     /** Retorna true se container está vazio */
    >     bool IsEmpty() const { return ContainerItemID == NAME_None; }
    >
    >     /** Retorna número de slots ocupados */
    >     int32 GetOccupiedSlots() const;
    >
    >     /** Retorna peso total dos itens no container */
    >     float GetTotalWeight(UDataTable* ItemDataTable) const;
    > };
    > ```
    >
    > **Nota:** Estrutura modular, será reutilizada no módulo completo.

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.3 - Expandir FItemDataRow.h (Preparação para Containers)</summary>

    > **Arquivo:** `Source/MyProject2/Data/Tables/ItemDataTable.h`
    >
    > **Mudanças:**
    >
    > ```cpp
    > // Adicionar em FItemDataRow:
    >
    > /**
    >  * Número máximo de slots se item é container (ex: Backpack = 30).
    >  * 0 se item não é container.
    >  */
    > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    > int32 MaxSlots = 0;
    >
    > /**
    >  * Peso máximo suportado pelo container em lbs (ex: Backpack = 30 lbs).
    >  * 0 se item não é container.
    >  */
    > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    > float MaxWeight = 0.0f;
    > ```
    >
    > **Nota:** Preparação para Fase 2 (módulo completo). Na Fase 1, apenas estrutura.

    </details>

    </details>

    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.2.1 - Adicionar Campos Mockup</summary>

    > **Arquivo:** `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
    >
    > **Campos a Adicionar:**
    >
    > ```cpp
    > /**
    >  * Mockup de inventário inicial (1 slot de corpo + 1 container).
    >  * Estrutura alinhada com futuro módulo Inventory/.
    >  *
    >  * NOTA: Este é um mockup hardcoded para finalizar criação de ficha.
    >  * Futuramente será migrado para UInventoryComponent.
    >  */
    > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Inventory")
    > FInventoryContainer BodySlot;
    >
    > /**
    >  * Peso total do inventário inicial em lbs.
    >  * Calculado automaticamente quando itens mudam.
    >  */
    > UPROPERTY(BlueprintReadOnly, Category = "Starting Inventory", meta = (Hidden))
    > float TotalWeight = 0.0f;
    >
    > /**
    >  * Carrying Capacity baseada em Strength (Strength × 15 lbs).
    >  * Calculado automaticamente quando Strength muda.
    >  */
    > UPROPERTY(BlueprintReadOnly, Category = "Starting Inventory", meta = (Hidden))
    > float CarryingCapacity = 0.0f;
    > ```
    >
    > **Nota:** Mockup simples, estrutura alinhada com módulo futuro.

    </details>

    </details>

    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.3.1 - Criar InventoryHelpers.h/cpp</summary>

    > **Arquivos:**
    > - `Source/MyProject2/Utils/InventoryHelpers.h` (NOVO)
    > - `Source/MyProject2/Utils/InventoryHelpers.cpp` (NOVO)
    >
    > **Funções:**
    >
    > ```cpp
    > namespace FInventoryHelpers
    > {
    >     /**
    >      * Calcula peso total de um array de slots de inventário.
    >      * Busca peso de cada item no ItemDataTable.
    >      */
    >     static float CalculateSlotsWeight(
    >         const TArray<FInventorySlot>& Slots,
    >         UDataTable* ItemDataTable);
    >
    >     /**
    >      * Calcula peso total de um container (incluindo peso do container).
    >      */
    >     static float CalculateContainerWeight(
    >         const FInventoryContainer& Container,
    >         UDataTable* ItemDataTable);
    >
    >     /**
    >      * Calcula Carrying Capacity baseada em Strength (Strength × 15).
    >      */
    >     static float CalculateCarryingCapacity(int32 StrengthScore);
    >
    >     /**
    >      * Valida se peso total não excede Carrying Capacity.
    >      */
    >     static bool ValidateCarryingCapacity(
    >         float TotalWeight,
    >         float CarryingCapacity);
    >
    >     /**
    >      * Valida se container não excede MaxSlots e MaxWeight.
    >      */
    >     static bool ValidateContainerCapacity(
    >         const FInventoryContainer& Container,
    >         UDataTable* ItemDataTable);
    > }
    > ```
    >
    > **Nota:** Helpers puros, sem acoplamento, reutilizáveis no módulo futuro.

    </details>

    </details>

    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.4.1 - Criar HandleInventoryChange</summary>

    > **Arquivo:** `Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.cpp`
    >
    > **Lógica:**
    >
    > - Quando `BodySlot` muda:
    >   - Recalcula `TotalWeight` usando `FInventoryHelpers::CalculateContainerWeight`
    >   - Valida `CarryingCapacity` usando `FInventoryHelpers::ValidateCarryingCapacity`
    >   - Valida `ContainerCapacity` usando `FInventoryHelpers::ValidateContainerCapacity`
    >
    > - Quando `Strength` muda:
    >   - Recalcula `CarryingCapacity` usando `FInventoryHelpers::CalculateCarryingCapacity`
    >   - Revalida peso total
    >
    > **Assinatura:**
    >
    > ```cpp
    > static void HandleInventoryChange(UCharacterSheetDataAsset* Asset);
    > static void HandleStrengthChange(UCharacterSheetDataAsset* Asset);
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.4.2 - Integrar com StartingItems</summary>

    > **Lógica:**
    >
    > - Quando `StartingItems` é carregado (via `HandleStartingEquipmentChange`):
    >   - Adiciona itens ao `BodySlot.Slots`
    >   - Se item é container (ex: Backpack), define `BodySlot.ContainerItemID`
    >   - Recalcula peso total
    >
    > **Nota:** Integração com sistema de itens iniciais já planejado.

    </details>

    </details>

    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.5.1 - Criar ValidateInventory</summary>

    > **Arquivo:** `Source/MyProject2/Characters/Data/Validators/CharacterSheetDataAssetValidators.cpp`
    >
    > **Validações:**
    >
    > - Peso total não excede Carrying Capacity
    > - Container não excede MaxSlots
    > - Container não excede MaxWeight
    > - Todos os ItemIDs existem no ItemDataTable
    >
    > **Assinatura:**
    >
    > ```cpp
    > static FValidationResult ValidateInventory(UCharacterSheetDataAsset* Asset);
    > ```

    </details>

    </details>

## 🔗 Integração com Sistema de Itens Iniciais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Fluxo de Dados</b></summary>

> **Fluxo Completo:**
>

> 1. **Classe muda** → `HandleClassChange`
> 2. **Carrega StartingEquipment** → `HandleStartingEquipmentChange`
> 3. **Adiciona itens ao BodySlot** → `HandleInventoryChange`
> 4. **Background muda** → `HandleBackgroundChange`
> 5. **Adiciona itens do background ao BodySlot** → `HandleInventoryChange`
> 6. **Recalcula peso total** → `FInventoryHelpers::CalculateContainerWeight`
> 7. **Valida Carrying Capacity** → `FInventoryHelpers::ValidateCarryingCapacity`
>
> **Nota:** Integração completa com sistema de itens iniciais já planejado.
>
</details>
---

## 🔮 Fase 2: Módulo Inventory/ Completo (Futuro)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Estrutura do Módulo</b></summary>

> **Diretório:** `Source/MyProject2/Inventory/`
>

> **Componentes:**
>
> - `UInventoryComponent.h/cpp` - Componente runtime, replicável
> - `FInventoryMotor.h/cpp` - Motor de lógica de inventário
> - `InventoryHelpers.h/cpp` - Helpers específicos (reutiliza Utils/InventoryHelpers)
> - `InventoryValidators.h/cpp` - Validators específicos
>
> **Reutilização:**
>
> - ✅ `FInventorySlot` (já criado em Fase 1)
> - ✅ `FInventoryContainer` (já criado em Fase 1)
> - ✅ `FInventoryHelpers` (já criado em Fase 1)
> - ✅ `FItemDataRow` (já expandido em Fase 1)
>
> **Zero Refatoração:** Todas as estruturas já estão modulares e prontas.
>
</details>
---

## 🔮 Fase 3: Integração (Futuro)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Migração de Dados</b></summary>

> **Processo:**
>

> 1. **Criar UInventoryComponent** no Character
> 2. **Migrar dados** de `CharacterSheetDataAsset.BodySlot` → `UInventoryComponent`
> 3. **Remover mockup** de `CharacterSheetDataAsset`
> 4. **Atualizar handlers** para usar `UInventoryComponent`
> 5. **Testar integração** completa
>
> **Nota:** Migração simples, estruturas já alinhadas.
>
</details>
---

## ✅ Garantias de Expansão

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Princípios Aplicados</b></summary>

> **1. Estruturas Modulares:**
>

> - ✅ `FInventorySlot` e `FInventoryContainer` em `Data/Structures/`
> - ✅ Independentes, reutilizáveis
> - ✅ Zero acoplamento com Data Asset
>
> **2. Helpers Puros:**
>
> - ✅ `FInventoryHelpers` em `Utils/`
> - ✅ Funções puras, sem side effects
> - ✅ Testáveis isoladamente
>
> **3. Mockup Alinhado:**
>
> - ✅ Usa mesmas estruturas do módulo futuro
> - ✅ Zero refatoração na migração
> - ✅ Permite finalizar ficha sem módulo completo
>
> **4. Preparação para Expansão:**
>
> - ✅ `FItemDataRow` já tem `MaxSlots` e `MaxWeight`
> - ✅ Estruturas prontas para containers aninhados (futuro)
> - ✅ Helpers prontos para lógica complexa (futuro)
>
</details>
---

## ⏱️ Estimativa de Tempo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Breakdown por Fase</b></summary>

> **Fase 1 (Boilerplate):**
>

> - **Fase 1.1:** 2-3 horas (estruturas modulares)
> - **Fase 1.2:** 1 hora (mockup no Data Asset)
> - **Fase 1.3:** 2-3 horas (Helpers)
> - **Fase 1.4:** 1-2 horas (Handlers)
> - **Fase 1.5:** 1 hora (Validators)
> - **Testes:** 1-2 horas
>
> **Total Fase 1:** 8-12 horas (1-2 dias)
>
> **Fase 2 (Módulo Completo):** Estimativa futura (2-3 semanas)
>
> **Fase 3 (Integração):** Estimativa futura (1 semana)
>
</details>
---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[D&D Beyond - Equipment](https://www.dndbeyond.com/sources/dnd/br-2024)** - Regras oficiais
> - **[Plano Técnico: Itens Iniciais](roadmap-tecnico-itens-iniciais.md)** - Sistema de itens iniciais
> - **[Roadmap Principal](roadmap.md)** - Contexto geral
> - **[Arquitetura Técnica](../technical/architecture.md)** - Padrões do projeto
> - **[Clean Code Mandatory](../../.cursor/rules/clean-code-mandatory.mdc)** - Regras de código
>

</details>

**Última atualização:** 2024-12-XX
**Versão:** 1.0.0
**Autor:** MyProject2 Team
