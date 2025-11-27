# Plano Técnico: Sistema de Itens Iniciais - D&D 5e

> **Documento Técnico:** Plano detalhado de implementação do sistema de itens iniciais na criação de ficha, seguindo regras D&D 5e e arquitetura do projeto.

**Status:** 📋 Planejado
**Prioridade:** 🟡 Média
**Estimativa:** 13-18 horas (2-3 dias)
**Fase:** Fase 1 - Sistema de Fichas (Expansão)

---

## 📚 Análise das Regras D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Regras Oficiais</b></summary>

> **1. Starting Equipment por Classe:**
>
> - Cada classe fornece equipamentos iniciais específicos
> - Exemplo: Fighter recebe Chain Mail OU Leather Armor + Longbow + Arrows
> - Algumas classes permitem escolhas (ex: Fighter escolhe entre Chain Mail ou Leather Armor + Longbow)
> - Alternativa: Ouro inicial baseado na classe (ex: Fighter: 5d4 × 10 gp = média 125 gp)
>
> **2. Equipment do Background:**
>
> - Cada background fornece itens adicionais
> - Exemplo: Acolyte recebe Holy Symbol, Prayer Book, 5 sticks of incense, vestments, 15 gp
> - Sempre adiciona ao equipamento da classe (não substitui)
>
> **3. Validações Necessárias:**
>
> - Peso total não pode exceder Carrying Capacity (Strength × 15 lbs)
> - Proficiências necessárias para usar equipamentos (futuro)
> - Itens devem existir no ItemDataTable

</details>

---

## 🏗️ Arquitetura Proposta

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Padrões e Princípios</b></summary>

> **Seguindo Padrões Existentes:**
>
> - ✅ **Data-Driven:** Itens vêm de Data Tables (ItemDataTable)
> - ✅ **Handlers Pattern:** `HandleStartingEquipmentChange` (similar a `HandleBackgroundChange`)
> - ✅ **Helpers Pattern:** Funções reutilizáveis em `*Helpers.h/cpp`
> - ✅ **Modular:** Separação de responsabilidades (Handlers, Helpers, Validators)
> - ✅ **Clean Code:** Funções pequenas, testáveis, sem duplicação

</details>

---

## 📋 Implementação Detalhada

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Fases de Implementação</b></summary>

> ### **Fase 1.1: Estrutura de Dados (Data Tables)**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.1 - Expandir ClassDataTable.h</summary>
>
> > **Arquivo:** `Source/MyProject2/Data/Tables/ClassDataTable.h`
> >
> > **Mudanças:**
> >
> > ```cpp
> > // Adicionar em FClassData:
> > /** Equipamentos iniciais da classe (FNames de itens) */
> > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
> > TArray<FName> StartingEquipment;
> >
> > /** Ouro inicial alternativo (se jogador escolher ouro ao invés de equipamentos) */
> > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Class")
> > int32 StartingGold = 0; // Ex: Fighter = 5d4 × 10 = média 125 gp
> > ```
> >
> > **Nota:** Campo `StartingEquipment` já existe no JSON (`Class_All.json`), precisa ser carregado para Data Table.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.2 - Criar ItemDataTable.h (Estrutura Básica)</summary>
>
> > **Arquivo:** `Source/MyProject2/Data/Tables/ItemDataTable.h` (NOVO)
> >
> > **Estrutura:**
> >
> > ```cpp
> > USTRUCT(BlueprintType)
> > struct MYPROJECT2_API FItemDataRow : public FTableRowBase
> > {
> >     GENERATED_BODY()
> >
> >     /** Nome do item (ex: "Chain Mail", "Longsword", "Dungeoneer's Pack") */
> >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
> >     FName ItemName;
> >
> >     /** Tipo do item: "Weapon", "Armor", "Tool", "Consumable", "Pack", "Other" */
> >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
> >     FName ItemType;
> >
> >     /** Peso do item em libras (lbs) */
> >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
> >     float Weight = 0.0f;
> >
> >     /** Valor do item em ouro (gp) */
> >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
> >     int32 Value = 0;
> >
> >     /** Descrição do item (localizável) */
> >     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
> >     FText Description;
> > };
> > ```
> >
> > **Nota:** Estrutura básica para Fase 1. Expansão futura na Fase 4 (Equipamentos).
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.3 - Atualizar JSON → Data Table</summary>
>
> > **Tarefas:**
> >
> > - Carregar `StartingEquipment` do `Class_All.json` para `ClassDataTable`
> > - Criar `ItemDataTable` a partir de lista de itens D&D 5e
> > - Validar todos os itens referenciados existem no `ItemDataTable`
>
> </details>
>
> ### **Fase 1.2: CharacterSheetDataAsset**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.2.1 - Adicionar Campos</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
> >
> > **Campos a Adicionar:**
> >
> > ```cpp
> > /** Itens iniciais do personagem (classe + background) */
> > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Equipment")
> > TArray<FName> StartingItems;
> >
> > /** Ouro inicial do personagem (se escolheu ouro ao invés de equipamentos) */
> > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Equipment")
> > int32 StartingGold = 0;
> >
> > /** Flag: jogador escolheu ouro ao invés de equipamentos padrão */
> > UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Starting Equipment")
> > bool bChoseGoldInsteadOfEquipment = false;
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.2.2 - Adicionar Referência a ItemDataTable</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/CharacterSheetDataAsset.h`
> >
> > **Campo a Adicionar:**
> >
> > ```cpp
> > /** Data Table de itens D&D 5e */
> > UPROPERTY(EditDefaultsOnly, Category = "Data Tables")
> > UDataTable* ItemDataTable;
> > ```
>
> </details>
>
> ### **Fase 1.3: Handlers**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.3.1 - Criar HandleStartingEquipmentChange</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.cpp`
> >
> > **Padrão:** Similar a `HandleBackgroundChange`
> >
> > **Lógica:**
> >
> > 1. Quando classe muda → carrega `StartingEquipment` da classe
> > 2. Quando background muda → adiciona `Equipment` do background
> > 3. Combina itens de classe + background em `StartingItems`
> > 4. Remove duplicatas
> > 5. Valida itens existem no `ItemDataTable`
> >
> > **Assinatura:**
> >
> > ```cpp
> > static void HandleStartingEquipmentChange(UCharacterSheetDataAsset* Asset);
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.3.2 - Criar HandleStartingGoldChange</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.cpp`
> >
> > **Lógica:**
> >
> > - Quando `bChoseGoldInsteadOfEquipment` muda:
> >   - Se `true`: limpa `StartingItems`, define `StartingGold` da classe
> >   - Se `false`: limpa `StartingGold`, recarrega `StartingItems`
> >
> > **Assinatura:**
> >
> > ```cpp
> > static void HandleStartingGoldChange(UCharacterSheetDataAsset* Asset);
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.3.3 - Registrar Handlers</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/Initializers/CharacterSheetDataAssetInitializers.cpp`
> >
> > **Mudanças:**
> >
> > ```cpp
> > // Adicionar em InitializeAllPropertyHandlers:
> > InitializeStartingEquipmentHandlers(Asset);
> >
> > // Criar nova função:
> > void FCharacterSheetDataAssetInitializers::InitializeStartingEquipmentHandlers(UCharacterSheetDataAsset* Asset)
> > {
> >     Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, StartingItems),
> >                                 FCharacterSheetDataAssetHandlers::HandleStartingEquipmentWrapper);
> >     Asset->PropertyHandlers.Add(GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, bChoseGoldInsteadOfEquipment),
> >                                 FCharacterSheetDataAssetHandlers::HandleStartingGoldWrapper);
> > }
> > ```
>
> </details>
>
> ### **Fase 1.4: Helpers**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.4.1 - Criar StartingEquipmentHelpers.h/cpp</summary>
>
> > **Arquivos:**
> > - `Source/MyProject2/Characters/Data/Helpers/StartingEquipmentHelpers.h` (NOVO)
> > - `Source/MyProject2/Characters/Data/Helpers/StartingEquipmentHelpers.cpp` (NOVO)
> >
> > **Funções:**
> >
> > ```cpp
> > namespace FStartingEquipmentHelpers
> > {
> >     /** Carrega equipamentos iniciais da classe */
> >     static TArray<FName> LoadClassStartingEquipment(
> >         const FName& ClassName,
> >         UDataTable* ClassDataTable);
> >
> >     /** Carrega equipamentos do background */
> >     static TArray<FName> LoadBackgroundEquipment(
> >         const FName& BackgroundName,
> >         UDataTable* BackgroundDataTable);
> >
> >     /** Combina e remove duplicatas de arrays de itens */
> >     static TArray<FName> CombineAndRemoveDuplicates(
> >         const TArray<FName>& ClassItems,
> >         const TArray<FName>& BackgroundItems);
> >
> >     /** Valida se todos os itens existem no ItemDataTable */
> >     static bool ValidateItemsExist(
> >         const TArray<FName>& Items,
> >         UDataTable* ItemDataTable);
> >
> >     /** Calcula peso total dos itens */
> >     static float CalculateTotalWeight(
> >         const TArray<FName>& Items,
> >         UDataTable* ItemDataTable);
> >
> >     /** Valida se peso não excede Carrying Capacity (Strength × 15) */
> >     static bool ValidateCarryingCapacity(
> >         const TArray<FName>& Items,
> >         int32 StrengthScore,
> >         UDataTable* ItemDataTable);
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.4.2 - Criar ItemDataTableHelpers.h/cpp</summary>
>
> > **Arquivos:**
> > - `Source/MyProject2/Utils/ItemDataTableHelpers.h` (NOVO)
> > - `Source/MyProject2/Utils/ItemDataTableHelpers.cpp` (NOVO)
> >
> > **Funções:**
> >
> > ```cpp
> > namespace FItemDataTableHelpers
> > {
> >     /** Busca item no ItemDataTable */
> >     static FItemDataRow* FindItemRow(
> >         const FName& ItemName,
> >         UDataTable* ItemDataTable);
> >
> >     /** Valida se item existe */
> >     static bool ItemExists(
> >         const FName& ItemName,
> >         UDataTable* ItemDataTable);
> > }
> > ```
>
> </details>
>
> ### **Fase 1.5: Validators**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.5.1 - Adicionar Validações</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Data/Validators/CharacterSheetDataAssetValidators.cpp`
> >
> > **Função a Adicionar:**
> >
> > ```cpp
> > /** Valida itens iniciais */
> > static bool ValidateStartingEquipment(UCharacterSheetDataAsset* Asset)
> > {
> >     // 1. Valida ItemDataTable existe
> >     // 2. Valida todos os itens existem no ItemDataTable
> >     // 3. Valida peso não excede Carrying Capacity
> >     // 4. Valida proficiências necessárias (se aplicável - futuro)
> > }
> > ```
>
> </details>
>
> ### **Fase 1.6: CharacterDataComponent**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.6.1 - Adicionar Campos Replicáveis</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Components/CharacterDataComponent.h`
> >
> > **Campos a Adicionar:**
> >
> > ```cpp
> > /** Itens iniciais do personagem (replicável) */
> > UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
> > TArray<FName> StartingItems;
> >
> > /** Ouro inicial do personagem (replicável) */
> > UPROPERTY(Replicated, BlueprintReadOnly, Category = "Character Data")
> > int32 StartingGold = 0;
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.6.2 - Adicionar Replicação</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Components/CharacterDataComponent.cpp`
> >
> > **Mudanças:**
> >
> > ```cpp
> > void UCharacterDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
> > {
> >     // ... código existente ...
> >     DOREPLIFETIME(UCharacterDataComponent, StartingItems);
> >     DOREPLIFETIME(UCharacterDataComponent, StartingGold);
> > }
> > ```
>
> </details>
>
> ### **Fase 1.7: CharacterSheetComponent**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.7.1 - Atualizar InitializeFromDataAsset</summary>
>
> > **Arquivo:** `Source/MyProject2/Characters/Components/CharacterSheetComponent.cpp`
> >
> > **Mudanças:**
> >
> > - Copiar `StartingItems` do Data Asset para `CharacterDataComponent`
> > - Copiar `StartingGold` do Data Asset para `CharacterDataComponent`
>
> </details>

</details>

---

## 🎯 Ordem de Implementação Recomendada

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📅 Sequência de Execução</b></summary>

> **Ordem Lógica:**
>
> 1. **Fase 1.1:** Estrutura de Dados (ItemDataTable + expandir ClassDataTable)
> 2. **Fase 1.2:** Adicionar campos no CharacterSheetDataAsset
> 3. **Fase 1.4:** Criar Helpers (reutilizáveis primeiro)
> 4. **Fase 1.3:** Criar Handlers (usam Helpers)
> 5. **Fase 1.5:** Adicionar Validators
> 6. **Fase 1.6:** Adicionar em CharacterDataComponent
> 7. **Fase 1.7:** Integrar em CharacterSheetComponent
>
> **Razão:** Helpers são base para Handlers, que são base para Validators. Estrutura de dados primeiro, depois lógica.

</details>

---

## 💡 Decisões de Design

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎨 Escolhas Arquiteturais</b></summary>

> **1. Escolha de Equipamentos vs Ouro:**
>
> - Implementar flag `bChoseGoldInsteadOfEquipment`
> - Se `true`: `StartingItems` vazio, `StartingGold` preenchido
> - Se `false`: `StartingItems` preenchido, `StartingGold` = 0
>
> **2. Escolhas de Equipamentos (ex: Fighter escolhe Chain Mail OU Leather Armor):**
>
> - **Fase 1:** Apenas equipamentos padrão (primeira opção)
> - **Fase Futura:** Sistema de escolhas (similar a Variant Human)
>
> **3. Validação de Peso:**
>
> - **Fase 1:** Validação básica (Strength × 15)
> - **Fase Futura:** Cálculo completo com encumbrance
>
> **4. Proficiências:**
>
> - **Fase 1:** Apenas validação de existência dos itens
> - **Fase Futura:** Validação de proficiências necessárias

</details>

---

## 🔗 Integração com Roadmap Existente

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Onde se EncaiXa</b></summary>

> **Fase 1 (Sistema de Fichas):**
>
> - Adicionar seção "6. Itens Iniciais" na Fase 1
> - Status: 📋 Planejado
> - Prioridade: 🟡 Média (não bloqueia outras funcionalidades)
>
> **Fase 4 (Equipamentos):**
>
> - Sistema completo de equipar/desequipar
> - Usa `StartingItems` como base
> - Expande `ItemDataTable` com propriedades completas

</details>

---

## ✅ Testes Necessários

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🧪 Estratégia de Testes</b></summary>

> **1. Unit Tests:**
>
> - `LoadClassStartingEquipment` retorna itens corretos
> - `CombineAndRemoveDuplicates` remove duplicatas
> - `ValidateItemsExist` valida corretamente
> - `CalculateTotalWeight` calcula corretamente
>
> **2. Integration Tests:**
>
> - Handler carrega itens quando classe muda
> - Handler combina classe + background
> - Validação de peso funciona
> - Replicação funciona
>
> **3. End-to-End:**
>
> - Criar personagem completo com itens iniciais
> - Validar todos os itens carregados
> - Testar escolha de ouro vs equipamentos

</details>

---

## ⏱️ Estimativa de Tempo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Breakdown por Fase</b></summary>

> - **Fase 1.1:** 2-3 horas (estrutura de dados)
> - **Fase 1.2:** 1 hora (campos no Data Asset)
> - **Fase 1.4:** 3-4 horas (Helpers)
> - **Fase 1.3:** 2-3 horas (Handlers)
> - **Fase 1.5:** 1-2 horas (Validators)
> - **Fase 1.6:** 1 hora (CharacterDataComponent)
> - **Fase 1.7:** 1 hora (CharacterSheetComponent)
> - **Testes:** 2-3 horas
>
> **Total:** 13-18 horas (2-3 dias de trabalho)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[D&D Beyond - Starting Equipment](https://www.dndbeyond.com/sources/dnd/br-2024)** - Regras oficiais
> - **[Roadmap Principal](../planning/roadmap.md)** - Contexto geral
> - **[Arquitetura Técnica](../technical/architecture.md)** - Padrões do projeto
> - **[Handlers Pattern](../technical/architecture.md#handlers-pattern)** - Padrão usado
> - **[Helpers Pattern](../technical/architecture.md#helpers-pattern)** - Padrão usado

</details>

---

**Última atualização:** 2024-12-XX
**Versão:** 1.0.0
**Autor:** MyProject2 Team
