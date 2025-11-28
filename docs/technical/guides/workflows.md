---
title: "Workflows"
category: technical
subcategory: guides
tags: [workflows, processes, character-creation, point-buy, multiclassing]
last_updated: 2024-12-27
difficulty: intermediate
related: [getting-started.md, algorithmic/character-creation.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Técnico](../technical/index.md) > [Guias](guides/index.md) > Workflows

# Guia de Fluxos Principais - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este guia documenta os fluxos principais do sistema, explicando passo a passo como cada processo funciona de ponta a ponta.

</details>

---

## 🎯 Fluxo 1: Criação Completa de Personagem

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 End-to-End: Editor → Runtime</b></summary>

> ### Visão Geral
>
> Este fluxo documenta o processo completo desde a criação no editor até a inicialização em runtime.
>
> ### Passo 1: Configurar no Editor
>
> 1. **Criar CharacterSheetDataAsset**
>    - Content Browser → Right Click → Data Asset → Character Sheet Data Asset
>    - Nomear (ex: `DA_CharacterSheet_Elias`)
>
> 2. **Atribuir Data Tables**
>    - Race Data Table
>    - Class Data Table
>    - Background Data Table
>    - Feat Data Table
>
> 3. **Preencher Ficha**
>    - Character Name: "Elias"
>    - Selected Race: "Human"
>    - Selected Subrace: "Variant Human" (se aplicável)
>    - Selected Background: "Acolyte"
>    - Point Buy: Alocar 27 pontos
>    - Classes: Adicionar níveis de classe
>
> ### Passo 2: Sistema Processa (Automático)
>
> O sistema processa automaticamente via `PostEditChangeProperty`:
>
> 1. **Handlers** detectam mudanças
> 2. **Validators** validam dados
> 3. **Motores** calculam valores finais:
>    - `FRaceBonusMotor` - Aplica bônus raciais
>    - `FPointBuyMotor` - Aplica Point Buy
>    - `FMulticlassMotor` - Calcula progressão multiclass
> 4. **Updaters** atualizam campos calculados
>
> ### Passo 3: Inicializar em Runtime
>
> 1. **Criar Actor** no mapa
> 2. **Adicionar Componentes:**
>    - `CharacterDataComponent` (Camada 3)
>    - `CharacterSheetComponent` (Camada 2)
> 3. **Atribuir Data Asset** ao `CharacterSheetComponent`
> 4. **BeginPlay** executa automaticamente:
>    - `CharacterSheetComponent::BeginPlay()` chama `InitializeFromDataAsset()`
>    - Dados são copiados do Data Asset para `CharacterDataComponent`
>    - `CharacterDataComponent::BeginPlay()` valida e faz log
>
> ### Passo 4: Validar Resultado
>
> Verificar no **Output Log**:
>
> ```
> === Character Sheet ===
> Name: Elias
> Level Total: 1
> Race: Human (Variant Human)
> Background: Acolyte
> --- Ability Scores ---
>   Strength: 16
>   Dexterity: 14
>   ...
> --- Data Integrity ---
>   ✅ Todos os dados estão válidos
> ```
>
> **📖 Para guia passo a passo, veja [getting-started.md](getting-started.md)**

</details>

---

## 💰 Fluxo 2: Point Buy System

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Alocação de Ability Scores</b></summary>

> ### Visão Geral
>
> O sistema Point Buy permite alocar 27 pontos entre os 6 ability scores, com cada score entre 8 e 15.
>
> ### Fórmula de Custo
>
> ```
> Score 8-13: Custo = Score - 8
> Score 14: Custo = 7
> Score 15: Custo = 9
> ```
>
> **Exemplo:**
>
> - Score 8 = 0 pontos
> - Score 10 = 2 pontos
> - Score 14 = 7 pontos
> - Score 15 = 9 pontos
>
> ### Fluxo de Validação
>
> 1. **Usuário ajusta scores** no editor (8-15 cada)
> 2. **PointBuyValidator** valida:
>    - Cada score entre 8 e 15? ✅
>    - Total de pontos ≤ 27? ✅
> 3. **PointBuyMotor** calcula:
>    - Custo total atual
>    - Pontos restantes
> 4. **Se exceder 27 pontos:**
>    - Sistema ajusta automaticamente (reduz do final da fila)
>    - Mostra warning (sem popup - correção automática)
>
> ### Exemplo de Alocação Válida
>
> ```
> Strength: 15 (9 pontos)
> Dexterity: 14 (7 pontos)
> Constitution: 13 (5 pontos)
> Intelligence: 12 (4 pontos)
> Wisdom: 10 (2 pontos)
> Charisma: 8 (0 pontos)
> ------------------------
> Total: 27 pontos ✅
> ```
>
> **📖 Para regras completas, veja [docs/design/dnd-rules/point-buy.md](../../../design/dnd-rules/point-buy.md)**

</details>

---

## 🎭 Fluxo 3: Multiclassing

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Múltiplas Classes</b></summary>

> ### Visão Geral
>
> O sistema permite que um personagem tenha múltiplas classes, cada uma com seu próprio nível.
>
> ### Regras de Multiclassing
>
> 1. **Nível Total:** Soma de todos os níveis de classe (máximo 20)
> 2. **Requisitos:** Cada classe tem requisitos de atributo
> 3. **Proficiências:** Apenas da primeira classe
> 4. **Features:** Ganha features de cada classe conforme nível
>
> ### Fluxo de Criação
>
> 1. **Adicionar Primeira Classe:**
>    - Class Name: "Fighter"
>    - Level: 1
>
> 2. **Adicionar Segunda Classe:**
>    - Class Name: "Wizard"
>    - Level: 1
>
> 3. **Sistema Calcula:**
>    - Total Level: 2 (1 + 1)
>    - Proficiency Bonus: +2 (nível 2)
>    - Features: Fighter 1 + Wizard 1
>
> ### Fluxo de Validação
>
> 1. **MulticlassValidator** valida:
>    - Requisitos de atributo atendidos? ✅
>    - Nível total ≤ 20? ✅
>    - Pelo menos 1 nível em alguma classe? ✅
>
> 2. **MulticlassMotor** processa:
>    - Carrega progressão de cada classe
>    - Calcula features disponíveis
>    - Calcula proficiências combinadas
>
> **📖 Para regras completas, veja [docs/design/dnd-rules/multiclassing.md](../../../design/dnd-rules/multiclassing.md)**

</details>

---

## 🧬 Fluxo 4: Variant Human

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👥 Raça Customizável</b></summary>

> ### Visão Geral
>
> Variant Human permite escolher 2 atributos para +1 cada, 1 feat e 1 skill proficiente.
>
> ### Fluxo de Configuração
>
> 1. **Selecionar Variant Human:**
>    - Selected Race: "Human"
>    - Selected Subrace: "Variant Human"
>
> 2. **Escolher Ability Scores (2x +1):**
>    - Custom Ability Score Choices: ["Strength", "Dexterity"]
>    - Sistema aplica +1 em cada
>
> 3. **Escolher Feat:**
>    - Selected Feat: "Alert"
>    - Sistema valida pré-requisitos
>
> 4. **Escolher Skill:**
>    - Selected Skill: "Perception"
>    - Sistema adiciona à lista de proficiências
>
> ### Fluxo de Validação
>
> 1. **VariantHumanValidator** valida:
>    - Exatamente 2 ability scores escolhidos? ✅
>    - Feat disponível (sem pré-requisitos de nível)? ✅
>    - Skill válida? ✅
>
> 2. **Sistema aplica:**
>    - Bônus de +1 nos 2 atributos escolhidos
>    - Feat adicionado às features disponíveis
>    - Skill adicionado às proficiências
>
> **📖 Para regras completas, veja [docs/design/dnd-rules/races.md](../../../design/dnd-rules/races.md)**

</details>

---

## 🔄 Fluxo 5: Validação e Correção Automática

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Sistema de Validação</b></summary>

> ### Visão Geral
>
> O sistema valida dados automaticamente e corrige problemas quando possível.
>
> ### Fluxo de Validação
>
> 1. **Trigger:** Mudança em qualquer propriedade do Data Asset
> 2. **PostEditChangeProperty** é chamado
> 3. **Handlers** processam mudança:
>    - Identificam qual propriedade mudou
>    - Chamam Validator apropriado
> 4. **Validators** validam:
>    - PointBuyValidator - Valida alocação de pontos
>    - MulticlassValidator - Valida requisitos de multiclasse
>    - VariantHumanValidator - Valida escolhas de Variant Human
> 5. **Se inválido:**
>    - Sistema tenta corrigir automaticamente (se possível)
>    - Mostra warning (sem popup - correção automática)
>    - Loga erro (com popup - requer ação manual)
>
> ### Tipos de Correção
>
> **Correção Automática (sem popup):**
>
> - Point Buy excede 27 pontos → Reduz automaticamente
> - Nível total > 20 → Ajusta para 20
> - Valores fora de range → Clampa para range válido
>
> **Requer Ação Manual (com popup):**
>
> - Raça não selecionada → Erro crítico
> - Background não selecionado → Erro crítico
> - Dados inconsistentes → Erro crítico
>
> **📖 Para detalhes técnicos, veja [architecture.md](../../architecture.md#sistema-de-validação)**

</details>

---

## 📊 Diagrama de Fluxo Completo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Visualização</b></summary>

> ```mermaid
> graph TB
>     Start[Usuário cria CharacterSheetDataAsset] --> Assign[Atribui Data Tables]
>     Assign --> Fill[Preenche dados básicos]
>     Fill --> Change[Muda propriedade]
>     Change --> Handler[Handler detecta mudança]
>     Handler --> Validator[Validator valida]
>     Validator -->|Válido| Motor[Motor calcula]
>     Validator -->|Inválido| Correct{Sistema pode corrigir?}
>     Correct -->|Sim| Auto[Correção automática]
>     Correct -->|Não| Error[Erro com popup]
>     Auto --> Motor
>     Motor --> Update[Updater atualiza campos]
>     Update --> Runtime[Runtime: InitializeFromDataAsset]
>     Runtime --> Validate[ValidateDataIntegrity]
>     Validate -->|Válido| Success[✅ Personagem criado]
>     Validate -->|Inválido| Fail[❌ Dados inválidos]
> ```
>
> **📖 Para diagramas completos, veja [ARCHITECTURE.md](../../../ARCHITECTURE.md)**

</details>

---

## 🎯 Casos de Uso Comuns

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplos Práticos</b></summary>

> ### Caso 1: Criar Fighter Nível 1
>
> 1. Race: Human
> 2. Background: Soldier
> 3. Point Buy: 15 STR, 14 CON, 13 DEX, 12 INT, 10 WIS, 8 CHA
> 4. Class: Fighter Level 1
> 5. Resultado: Personagem válido com todas as features de Fighter nível 1
>
> ### Caso 2: Criar Variant Human Wizard
>
> 1. Race: Human (Variant Human)
> 2. Custom Ability Scores: Intelligence +1, Dexterity +1
> 3. Feat: Alert
> 4. Skill: Perception
> 5. Background: Sage
> 6. Point Buy: 8 STR, 14 DEX, 12 CON, 15 INT, 10 WIS, 8 CHA
> 7. Class: Wizard Level 1
> 8. Resultado: INT final = 16 (15 + 1), DEX final = 15 (14 + 1), com Alert feat
>
> ### Caso 3: Criar Multiclasse Fighter/Wizard
>
> 1. Race: High Elf
> 2. Background: Acolyte
> 3. Point Buy: 13 STR, 14 DEX, 12 CON, 15 INT, 10 WIS, 8 CHA
> 4. Classes:
>    - Fighter Level 1
>    - Wizard Level 1
> 5. Resultado: Total Level 2, features de ambas as classes
>
> **📖 Para mais exemplos, veja [getting-started.md](getting-started.md)**

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Guia de Início Rápido](getting-started.md)** - Criar primeiro personagem
> - **[Arquitetura](../../architecture.md)** - Como os fluxos se integram
> - **[API Reference](../../api.md)** - Classes e métodos usados nos fluxos
> - **[Regras D&D 5e](../../../design/dnd-rules/)** - Regras oficiais

</details>
