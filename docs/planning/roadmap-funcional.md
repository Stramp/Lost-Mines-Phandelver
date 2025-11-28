---
title: "Roadmap Funcional - Features por Categoria"
category: planning
tags: [roadmap, functional, features, dnd5e]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Roadmap Funcional

# Roadmap Funcional - Features por Categoria

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este roadmap detalha todas as **features funcionais** faltantes, organizadas pelos **6 passos do D&D 5e** para criação de personagem.
>
> **Organização:**
>
> - **Step 3:** Determine Ability Scores (Standard Array, Roll 4d6)
> - **Step 4:** Describe Your Character (Personality Traits, Ideals, Bonds, Flaws)
> - **Step 5:** Choose Equipment (Starting Equipment, Carrying Capacity, Armor Class)
> - **Step 6:** Finalize Character (HP Inicial - já coberto em roadmap-tecnico.md)
>
> **Metodologia:** 🧪 TDD obrigatório para todas as funções helper/motor

</details>

---

## Step 3: Determine Ability Scores

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Métodos Alternativos de Ability Scores</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 FUNC-001: Implementar Standard Array</summary>
>
> > **User Story:** Como jogador, eu quero escolher Standard Array (15, 14, 13, 12, 10, 8) para distribuir ability scores de forma balanceada e rápida.
> >
> > **Prioridade MoSCoW:** 🟡 **S - Should Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Standard Array: 15, 14, 13, 12, 10, 8
> > - Permite distribuir valores fixos entre atributos
> >
> > **Definition of Done:**
> >
> > - ✅ Função `GetStandardArrayValues()` implementada com testes TDD
> > - ✅ Motor `StandardArrayMotor` criado e integrado
> > - ✅ Integrado no `CharacterSheetCore`
> > - ✅ Teste E2E passa validando Standard Array
> > - ✅ UI permite seleção de Standard Array
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-001-01:** Criar struct `FStandardArrayData` em `Data/Structures/FStandardArrayData.h` - **30 min**
> > 2. **FUNC-001-02:** Criar função `GetStandardArrayValues()` em `Utils/AbilityScoreHelpers.h/cpp` retornando `TArray<int32>` - **30 min** 🧪 TDD
> > 3. **FUNC-001-03:** Criar testes para `GetStandardArrayValues()` (valores corretos, ordem) - **1 hora** 🧪 TDD
> > 4. **FUNC-001-04:** Adicionar campo `bUseStandardArray` em `CharacterSheetDataAsset.h` - **15 min**
> > 5. **FUNC-001-05:** Criar função `ApplyStandardArray()` em `CreateSheet/StandardArray/StandardArrayMotor.h/cpp` - **2 horas** 🧪 TDD
> > 6. **FUNC-001-06:** Criar testes para `ApplyStandardArray()` (distribuição válida, inválida) - **1 hora** 🧪 TDD
> > 7. **FUNC-001-07:** Integrar Standard Array no `CharacterSheetCore::RecalculateFinalScores()` - **1 hora**
> > 8. **FUNC-001-08:** Adicionar handler `HandleStandardArraySelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 9. **FUNC-001-09:** Atualizar teste E2E para validar Standard Array - **30 min**
> >
> > **Estimativa Total:** 7.5 horas
> >
> > **Dependências:**
> > - ✅ Point Buy já implementado (referência de arquitetura)
> >
> > **Critério de Conclusão:** Teste E2E passa validando Standard Array
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 FUNC-002: Implementar Roll 4d6 Drop Lowest</summary>
>
> > **User Story:** Como jogador, eu quero rolar 4d6 e descartar o menor para gerar ability scores aleatórios e únicos.
> >
> > **Prioridade MoSCoW:** 🟡 **S - Should Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Roll 4d6, descarta menor, soma os 3 maiores
> > - Repete 6 vezes (um para cada atributo)
> >
> > **Definition of Done:**
> >
> > - ✅ Função `Roll4d6DropLowest()` implementada com testes TDD
> > - ✅ Função `RollAbilityScores()` implementada com testes TDD
> > - ✅ Motor `Roll4d6Motor` criado e integrado
> > - ✅ Integrado no `CharacterSheetCore`
> > - ✅ Teste E2E passa validando Roll 4d6
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-002-01:** Criar função `Roll4d6DropLowest()` em `Utils/DiceHelpers.h/cpp` retornando `int32` - **1 hora** 🧪 TDD
> > 2. **FUNC-002-02:** Criar testes para `Roll4d6DropLowest()` (valores entre 3-18, distribuição) - **1 hora** 🧪 TDD
> > 3. **FUNC-002-03:** Criar função `RollAbilityScores()` em `Utils/DiceHelpers.h/cpp` retornando `TArray<int32>` (6 valores) - **1 hora** 🧪 TDD
> > 4. **FUNC-002-04:** Criar testes para `RollAbilityScores()` (6 valores, todos entre 3-18) - **1 hora** 🧪 TDD
> > 5. **FUNC-002-05:** Adicionar campo `bUseRoll4d6` e `RolledAbilityScores` em `CharacterSheetDataAsset.h` - **15 min**
> > 6. **FUNC-002-06:** Criar função `ApplyRolledScores()` em `CreateSheet/Roll4d6/Roll4d6Motor.h/cpp` - **2 horas** 🧪 TDD
> > 7. **FUNC-002-07:** Criar testes para `ApplyRolledScores()` (valores aplicados corretamente) - **1 hora** 🧪 TDD
> > 8. **FUNC-002-08:** Integrar Roll 4d6 no `CharacterSheetCore::RecalculateFinalScores()` - **1 hora**
> > 9. **FUNC-002-09:** Adicionar handler `HandleRoll4d6Selection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 10. **FUNC-002-10:** Atualizar teste E2E para validar Roll 4d6 - **30 min**
> >
> > **Estimativa Total:** 9.75 horas
> >
> > **Dependências:**
> > - ✅ Point Buy já implementado (referência de arquitetura)
> >
> > **Critério de Conclusão:** Teste E2E passa validando Roll 4d6
>
> </details>

</details>

---

## Step 4: Describe Your Character

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Personalidade e Características</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 FUNC-003: Implementar Personality Traits</summary>
>
> > **User Story:** Como jogador, eu quero escolher 2 personality traits do meu background para personalizar meu personagem.
> >
> > **Prioridade MoSCoW:** 🟢 **C - Could Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Personality Traits vêm do Background
> > - Personagem escolhe 2 traits do background
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `PersonalityTraits` adicionado em `BackgroundDataTable`
> > - ✅ Função `GetPersonalityTraitsForBackground()` implementada com testes TDD
> > - ✅ Handler `HandlePersonalityTraitSelection()` criado
> > - ✅ Teste E2E passa validando Personality Traits
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-003-01:** Adicionar campo `PersonalityTraits` (TArray<FString>) em `BackgroundDataTable` - **15 min**
> > 2. **FUNC-003-02:** Adicionar campo `SelectedPersonalityTraits` (TArray<FName>) em `CharacterSheetDataAsset.h` - **15 min**
> > 3. **FUNC-003-03:** Criar função `GetPersonalityTraitsForBackground()` em `Utils/BackgroundHelpers.h/cpp` - **30 min** 🧪 TDD
> > 4. **FUNC-003-04:** Criar testes para `GetPersonalityTraitsForBackground()` - **1 hora** 🧪 TDD
> > 5. **FUNC-003-05:** Adicionar handler `HandlePersonalityTraitSelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 6. **FUNC-003-06:** Atualizar teste E2E para validar Personality Traits - **30 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:**
> > - ✅ Background já implementado
> >
> > **Critério de Conclusão:** Teste E2E passa validando Personality Traits
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 FUNC-004: Implementar Ideals</summary>
>
> > **User Story:** Como jogador, eu quero escolher um ideal do meu background para definir os valores e princípios do meu personagem.
> >
> > **Prioridade MoSCoW:** 🟢 **C - Could Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-004-01:** Adicionar campo `Ideals` (TArray<FString>) em `BackgroundDataTable` - **15 min**
> > 2. **FUNC-004-02:** Adicionar campo `SelectedIdeal` (FName) em `CharacterSheetDataAsset.h` - **15 min**
> > 3. **FUNC-004-03:** Criar função `GetIdealsForBackground()` em `Utils/BackgroundHelpers.h/cpp` - **30 min** 🧪 TDD
> > 4. **FUNC-004-04:** Criar testes para `GetIdealsForBackground()` - **1 hora** 🧪 TDD
> > 5. **FUNC-004-05:** Adicionar handler `HandleIdealSelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 6. **FUNC-004-06:** Atualizar teste E2E para validar Ideals - **30 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:**
> > - ✅ Background já implementado
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `Ideals` adicionado em `BackgroundDataTable`
> > - ✅ Função `GetIdealsForBackground()` implementada com testes TDD
> > - ✅ Handler `HandleIdealSelection()` criado
> > - ✅ Teste E2E passa validando Ideals
> >
> > **Critério de Conclusão:** Teste E2E passa validando Ideals
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 FUNC-005: Implementar Bonds</summary>
>
> > **User Story:** Como jogador, eu quero escolher um bond do meu background para definir conexões e relacionamentos importantes do meu personagem.
> >
> > **Prioridade MoSCoW:** 🟢 **C - Could Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-005-01:** Adicionar campo `Bonds` (TArray<FString>) em `BackgroundDataTable` - **15 min**
> > 2. **FUNC-005-02:** Adicionar campo `SelectedBond` (FName) em `CharacterSheetDataAsset.h` - **15 min**
> > 3. **FUNC-005-03:** Criar função `GetBondsForBackground()` em `Utils/BackgroundHelpers.h/cpp` - **30 min** 🧪 TDD
> > 4. **FUNC-005-04:** Criar testes para `GetBondsForBackground()` - **1 hora** 🧪 TDD
> > 5. **FUNC-005-05:** Adicionar handler `HandleBondSelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 6. **FUNC-005-06:** Atualizar teste E2E para validar Bonds - **30 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:**
> > - ✅ Background já implementado
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `Bonds` adicionado em `BackgroundDataTable`
> > - ✅ Função `GetBondsForBackground()` implementada com testes TDD
> > - ✅ Handler `HandleBondSelection()` criado
> > - ✅ Teste E2E passa validando Bonds
> >
> > **Critério de Conclusão:** Teste E2E passa validando Bonds
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 FUNC-006: Implementar Flaws</summary>
>
> > **User Story:** Como jogador, eu quero escolher um flaw do meu background para adicionar profundidade e vulnerabilidades ao meu personagem.
> >
> > **Prioridade MoSCoW:** 🟢 **C - Could Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-006-01:** Adicionar campo `Flaws` (TArray<FString>) em `BackgroundDataTable` - **15 min**
> > 2. **FUNC-006-02:** Adicionar campo `SelectedFlaw` (FName) em `CharacterSheetDataAsset.h` - **15 min**
> > 3. **FUNC-006-03:** Criar função `GetFlawsForBackground()` em `Utils/BackgroundHelpers.h/cpp` - **30 min** 🧪 TDD
> > 4. **FUNC-006-04:** Criar testes para `GetFlawsForBackground()` - **1 hora** 🧪 TDD
> > 5. **FUNC-006-05:** Adicionar handler `HandleFlawSelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 6. **FUNC-006-06:** Atualizar teste E2E para validar Flaws - **30 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:**
> > - ✅ Background já implementado
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `Flaws` adicionado em `BackgroundDataTable`
> > - ✅ Função `GetFlawsForBackground()` implementada com testes TDD
> > - ✅ Handler `HandleFlawSelection()` criado
> > - ✅ Teste E2E passa validando Flaws
> >
> > **Critério de Conclusão:** Teste E2E passa validando Flaws
>
> </details>

</details>

---

## Step 5: Choose Equipment

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎒 Equipamentos e Inventário</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 FUNC-007: Implementar Starting Equipment da Classe</summary>
>
> > **User Story:** Como jogador, eu quero receber equipamentos iniciais da minha classe para começar o jogo com equipamento adequado.
> >
> > **Prioridade MoSCoW:** 🔴 **M - Must Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Cada classe tem starting equipment definido
> > - Pode ter escolhas (ex: Fighter escolhe entre armas)
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `StartingEquipment` adicionado em `ClassDataTable`
> > - ✅ Funções `GetStartingEquipmentForClass()` e `GetStartingEquipmentChoicesForClass()` implementadas com testes TDD
> > - ✅ Handler `HandleStartingEquipmentSelection()` criado
> > - ✅ Teste E2E passa validando Starting Equipment da classe
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-007-01:** Adicionar campo `StartingEquipment` (TArray<FName>) em `ClassDataTable` - **15 min**
> > 2. **FUNC-007-02:** Adicionar campo `StartingEquipmentChoices` (TArray<FEquipmentChoice>) em `ClassDataTable` - **30 min**
> > 3. **FUNC-007-03:** Criar struct `FEquipmentChoice` em `Data/Structures/FEquipmentChoice.h` - **30 min**
> > 4. **FUNC-007-04:** Adicionar campo `SelectedStartingEquipment` (TArray<FName>) em `CharacterSheetDataAsset.h` - **15 min**
> > 5. **FUNC-007-05:** Criar função `GetStartingEquipmentForClass()` em `Utils/ClassHelpers.h/cpp` - **1 hora** 🧪 TDD
> > 6. **FUNC-007-06:** Criar testes para `GetStartingEquipmentForClass()` - **1 hora** 🧪 TDD
> > 7. **FUNC-007-07:** Criar função `GetStartingEquipmentChoicesForClass()` em `Utils/ClassHelpers.h/cpp` - **1 hora** 🧪 TDD
> > 8. **FUNC-007-08:** Criar testes para `GetStartingEquipmentChoicesForClass()` - **1 hora** 🧪 TDD
> > 9. **FUNC-007-09:** Adicionar handler `HandleStartingEquipmentSelection()` em `CharacterSheetDataAssetHandlers.cpp` - **30 min**
> > 10. **FUNC-007-10:** Atualizar teste E2E para validar Starting Equipment - **30 min**
> >
> > **Estimativa Total:** 6.5 horas
> >
> > **Dependências:**
> > - ✅ Class já implementado
> > - 📋 ItemDataTable (pode ser criado básico primeiro)
> >
> > **Critério de Conclusão:** Teste E2E passa validando Starting Equipment
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 FUNC-008: Implementar Starting Equipment do Background</summary>
>
> > **User Story:** Como jogador, eu quero receber equipamentos iniciais do meu background para começar o jogo com equipamento adequado ao meu background.
> >
> > **Prioridade MoSCoW:** 🔴 **M - Must Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-008-01:** Adicionar campo `StartingEquipment` (TArray<FName>) em `BackgroundDataTable` - **15 min**
> > 2. **FUNC-008-02:** Criar função `GetStartingEquipmentForBackground()` em `Utils/BackgroundHelpers.h/cpp` - **30 min** 🧪 TDD
> > 3. **FUNC-008-03:** Criar testes para `GetStartingEquipmentForBackground()` - **1 hora** 🧪 TDD
> > 4. **FUNC-008-04:** Integrar Starting Equipment do Background no handler de equipment - **30 min**
> > 5. **FUNC-008-05:** Atualizar teste E2E para validar Starting Equipment do Background - **30 min**
> >
> > **Estimativa Total:** 2.75 horas
> >
> > **Dependências:**
> > - ✅ Background já implementado
> > - 📋 ItemDataTable (pode ser criado básico primeiro)
> >
> > **Definition of Done:**
> >
> > - ✅ Campo `StartingEquipment` adicionado em `BackgroundDataTable`
> > - ✅ Função `GetStartingEquipmentForBackground()` implementada com testes TDD
> > - ✅ Integrado no handler de equipment
> > - ✅ Teste E2E passa validando Starting Equipment do Background
> >
> > **Critério de Conclusão:** Teste E2E passa validando Starting Equipment do Background
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 FUNC-009: Implementar Carrying Capacity</summary>
>
> > **User Story:** Como jogador, eu quero que o sistema calcule minha capacidade de carga baseada em Strength para validar se posso carregar meus equipamentos.
> >
> > **Prioridade MoSCoW:** 🟡 **S - Should Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Fórmula: `StrengthScore * 15` (lbs)
> > - Valida se personagem pode carregar equipamentos
> >
> > **Definition of Done:**
> >
> > - ✅ Função `CalculateCarryingCapacity()` implementada com testes TDD
> > - ✅ Função `CalculateCurrentWeight()` implementada com testes TDD
> > - ✅ Função `ValidateCarryingCapacity()` implementada com testes TDD
> > - ✅ Campos `CarryingCapacity` e `CurrentWeight` adicionados
> > - ✅ Validação integrada no handler de equipment
> > - ✅ Teste E2E passa validando Carrying Capacity
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-009-01:** Criar função `CalculateCarryingCapacity()` em `Utils/InventoryHelpers.h/cpp` - **1 hora** 🧪 TDD
> > 2. **FUNC-009-02:** Criar testes para `CalculateCarryingCapacity()` (valores corretos, edge cases) - **1 hora** 🧪 TDD
> > 3. **FUNC-009-03:** Adicionar campo `CarryingCapacity` (calculado) em `CharacterDataComponent.h` - **15 min**
> > 4. **FUNC-009-04:** Adicionar campo `CurrentWeight` (calculado) em `CharacterDataComponent.h` - **15 min**
> > 5. **FUNC-009-05:** Criar função `CalculateCurrentWeight()` em `Utils/InventoryHelpers.h/cpp` - **1 hora** 🧪 TDD
> > 6. **FUNC-009-06:** Criar testes para `CalculateCurrentWeight()` - **1 hora** 🧪 TDD
> > 7. **FUNC-009-07:** Criar função `ValidateCarryingCapacity()` em `Utils/InventoryHelpers.h/cpp` - **30 min** 🧪 TDD
> > 8. **FUNC-009-08:** Criar testes para `ValidateCarryingCapacity()` - **1 hora** 🧪 TDD
> > 9. **FUNC-009-09:** Integrar validação de peso no handler de equipment - **30 min**
> > 10. **FUNC-009-10:** Atualizar teste E2E para validar Carrying Capacity - **30 min**
> >
> > **Estimativa Total:** 7.5 horas
> >
> > **Dependências:**
> > - ✅ Strength score já implementado
> > - 📋 ItemDataTable com peso dos itens
> >
> > **Critério de Conclusão:** Teste E2E passa validando Carrying Capacity
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 FUNC-010: Implementar Armor Class (AC)</summary>
>
> > **User Story:** Como jogador, eu quero que o sistema calcule minha Armor Class baseada em Dexterity e armadura equipada para determinar minha defesa.
> >
> > **Prioridade MoSCoW:** 🟡 **S - Should Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Fórmula base: `10 + DexterityModifier`
> > - Com armadura: `ArmorBaseAC + DexterityModifier (limitado)`
> >
> > **Definition of Done:**
> >
> > - ✅ Função `CalculateArmorClass()` implementada com testes TDD
> > - ✅ Suporta cálculo sem armadura (10 + Dex Mod)
> > - ✅ Suporta cálculo com armadura (ArmorBaseAC + Dex Mod limitado)
> > - ✅ Campo `ArmorClass` adicionado e integrado
> > - ✅ Teste E2E passa validando Armor Class
> >
> > **Tarefas Puras:**
> >
> > 1. **FUNC-010-01:** Criar função `CalculateArmorClass()` em `Utils/CombatHelpers.h/cpp` - **2 horas** 🧪 TDD
> > 2. **FUNC-010-02:** Criar testes para `CalculateArmorClass()` (sem armadura, com armadura, limites) - **2 horas** 🧪 TDD
> > 3. **FUNC-010-03:** Adicionar campo `ArmorClass` (calculado) em `CharacterDataComponent.h` - **15 min**
> > 4. **FUNC-010-04:** Integrar cálculo de AC no updater - **30 min**
> > 5. **FUNC-010-05:** Atualizar teste E2E para validar Armor Class - **30 min**
> >
> > **Estimativa Total:** 5.25 horas
> >
> > **Dependências:**
> > - ✅ Dexterity modifier já implementado
> > - 📋 ItemDataTable com dados de armaduras
> >
> > **Critério de Conclusão:** Teste E2E passa validando Armor Class
>
> </details>

</details>

---

## 📊 Resumo de Prioridades

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Estatísticas</b></summary>

> **Alta Prioridade:**
>
> - 2 tarefas principais (Starting Equipment Classe/Background)
> - ~9.25 horas de trabalho estimado
> - Bloqueiam criação completa de personagem
>
> **Média Prioridade:**
>
> - 4 tarefas principais (Standard Array, Roll 4d6, Carrying Capacity, AC)
> - ~31.5 horas de trabalho estimado
> - Importantes mas não bloqueantes
>
> **Baixa Prioridade:**
>
> - 4 tarefas principais (Personality Traits, Ideals, Bonds, Flaws)
> - ~12 horas de trabalho estimado
> - Flavor, não crítico para gameplay
>
> **Total Estimado:** ~52.75 horas de trabalho funcional

</details>

---

## 🔗 Links Relacionados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Referências</b></summary>

> - **[Roadmap Principal](roadmap.md)** - Visão estratégica
> > - **[Roadmap Técnico](roadmap-tecnico.md)** - Bugs e correções
> > - **[Roadmap de Testes](roadmap-testes.md)** - Testes e validações
> > - **[Estrutura de Roadmaps](roadmap-estrutura.md)** - Documentação da estrutura hierárquica
> > - **[Plano Técnico: Itens Iniciais](roadmap-tecnico-itens-iniciais.md)** - Implementação detalhada de equipment

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
