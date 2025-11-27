# Roadmap Completo - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral do Roadmap</b></summary>

> Este documento contém o **roadmap completo e detalhado** para transformação do projeto em um **Action RPG baseado em D&D 5e**.
>
> **Objetivo:** Transformar o sistema de fichas atual em um jogo completo, mantendo fidelidade às regras D&D 5ª edição.
>
> **Status Geral:**
>
> - ✅ **Fase 1:** Sistema de Fichas (Completo)
> - 📋 **Fase 2:** Combate Básico com GAS (Próxima)
> - 📋 **Fases 3-10:** Planejadas

</details>

---

## 📊 Legenda de Status

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔖 Status e Símbolos</b></summary>

> **Status:**
>
> - ✅ **Completo** - Implementado e testado
> - 🔄 **Em desenvolvimento** - Trabalho em andamento
> - ⚠️ **Pendente/Validação** - Aguardando validação ou decisão
> - ⏳ **Standby** - Planejado mas não iniciado
> - 📋 **Planejado** - Definido no roadmap
> - 🔮 **Futuro** - Planejado para longo prazo
>
> **Prioridade:**
>
> - 🔴 **Alta** - Crítico para próxima fase
> - 🟡 **Média** - Importante mas não bloqueante
> - 🟢 **Baixa** - Melhorias e polish

</details>

---

## ⏱️ Curto Prazo (Próximas 4-6 semanas)

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Fases Imediatas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Fase 1: Sistema de Fichas (75% Completo - Em Andamento)</summary>
>
> > **Status:** 🔄 Em desenvolvimento
> >
> > **Progresso:** ~75% completo
> >
> > **Objetivo:** Sistema completo de criação de personagens D&D 5e
> >
> > **O Que Foi Implementado:**
> >
> > **1. Motores Básicos (100% Completo):**
> >
> > - ✅ **RaceBonusMotor** - Completo
> >   - Aplica bônus raciais e sub-raças
> >   - Suporta Variant Human (Custom Ability Score Choices)
> >   - Integrado no CharacterSheetCore
> >
> > - ✅ **PointBuyMotor** - Completo
> >   - Validação de 27 pontos máximo
> >   - Ajuste automático se exceder limite
> >   - Feedback de pontos restantes
> >   - Integrado no CharacterSheetCore
> >
> > - ✅ **CharacterSheetCore** - Completo
> >   - Orquestra RaceBonus + PointBuy
> >   - Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation
> >   - Genérico (funciona em Data Asset e Widget)
> >
> > **2. Sistema de Validação (100% Completo):**
> >
> > - ✅ **Validators** - Completos
> >   - ValidateVariantHumanChoices (feat, skill, ability scores)
> >   - ValidateLanguageChoices
> >   - ValidateMulticlassNameLevelConsistency
> >   - ValidateMulticlassProgression
> >   - Boot Protocol (ValidateAll)
> >
> > - ✅ **Handlers** - Completos
> >   - HandleRaceChange (reseta sub-raça se necessário)
> >   - HandlePointBuyAllocationChange (valida e recalcula)
> >   - HandleBackgroundChange
> >   - HandleVariantHumanChoicesChange
> >   - HandleLanguageChoicesChange
> >   - HandleLevelInClassChange (processa features por nível)
> >   - HandleMulticlassClassNameChange
> >   - HandleProficienciesChange
> >
> > - ✅ **Updaters** - Completos
> >   - RecalculateFinalScores (integra CharacterSheetCore)
> >   - UpdateVariantHumanFlag
> >   - UpdateLanguageChoices
> >   - UpdateCalculatedFields
> >
> > **3. Variant Human (100% Completo):**
> >
> > - ✅ Feat selection (GetAvailableFeatNames com filtro por ability scores)
> > - ✅ Skill selection (GetSkillNames)
> > - ✅ Custom Ability Score Choices (2x +1 para distribuir)
> > - ✅ Validação completa (feat, skill, ability scores)
> > - ✅ Handlers dedicados
> > - ✅ Reset automático quando não é mais Variant Human
> >
> > **4. Multiclasse - Estrutura (80% Completo):**
> >
> > - ✅ **ProcessLevelChange** - Funcional
> >   - Carrega features do nível específico da tabela
> >   - Valida entradas
> >   - Loga features ganhas
> >
> > - ✅ **LoadClassProficiencies** - Funcional
> >   - Carrega proficiências quando LevelInClass == 1
> >   - Converte de FProficienciesEntry (tabela) para FMulticlassProficienciesEntry (Data Asset)
> >   - Suporta armas, armaduras, saving throws, skills
> >
> > - ✅ **GetAvailableClasses** - Funcional
> >   - Filtra classes por requisitos de atributo
> >   - Usa FMulticlassValidators para validar requisitos
> >   - Suporta AND (múltiplos requisitos) e OR (requisitos alternativos)
> >   - Adiciona tags visuais quando requisitos não atendidos (ex: "[STR +2] Fighter")
> >
> > - ✅ **Estrutura de Dados** - Completa
> >   - FMulticlassEntry, FMulticlassClassData
> >   - FMulticlassProgressEntry, FMulticlassClassFeature
> >   - FMulticlassProficienciesEntry, FMulticlassSkills
> >   - Integração completa com Data Asset
> >
> > **5. Sistema de Dropdowns (100% Completo):**
> >
> > - ✅ GetRaceNames, GetSubraceNames (dependentes)
> > - ✅ GetBackgroundNames
> > - ✅ GetAvailableFeatNames (filtrado por ability scores)
> > - ✅ GetSkillNames
> > - ✅ GetListClassAvaible (filtrado por requisitos de atributo)
> > - ✅ GetAvailableLanguageNames
> >
> > **6. Itens Iniciais e Boilerplate de Inventário (📋 Planejado):**
> >
> > - 📋 **Sistema de Itens Iniciais** - Planejado
> >   - StartingEquipment por classe (TArray<FName>)
> >   - StartingGold alternativo (int32)
> >   - Integração com Background equipment
> >   - Validação de peso (Carrying Capacity)
> >   - **📖 Plano Detalhado:** [roadmap-tecnico-itens-iniciais.md](roadmap-tecnico-itens-iniciais.md)
> >
> > - 📋 **Boilerplate de Inventário** - Planejado
> >   - Estruturas modulares: `FInventorySlot`, `FInventoryContainer`
> >   - Mockup hardcoded: 1 slot de corpo + 1 container (mochila)
> >   - Helpers básicos em `Utils/InventoryHelpers`
> >   - Preparação para módulo `Inventory/` completo (Fase 4)
> >   - **📖 Plano Detalhado:** [roadmap-tecnico-inventario-boilerplate.md](roadmap-tecnico-inventario-boilerplate.md)
> >
> > **O Que Está Faltando:**
> >
> > **1. MulticlassMotor - Funções Críticas (20% Faltando):**
> >
> > - ❌ **ValidateMulticlassRequirements** - TODO (linha 60)
> >   - Atualmente retorna `true` sempre
> >   - **Precisa:** Implementar validação usando FMulticlassValidators já existente
> >   - **Impacto:** Não valida requisitos ao adicionar nova classe
> >
> > - ❌ **ApplyMulticlassRules** - TODO (linha 73)
> >   - Atualmente vazio
> >   - **Precisa:** Implementar aplicação de regras de multiclasse
> >   - **Impacto:** Regras de multiclasse não são aplicadas automaticamente
> >
> > **2. Integração MulticlassMotor:**
> >
> > - ⚠️ **Não integrado no CharacterSheetCore**
> >   - Apenas RaceBonus + PointBuy são orquestrados
> >   - Multiclass roda separadamente via handlers
> >   - **Precisa:** Decidir se integra no Core ou mantém separado
> >
> > **3. ChoiceMotor:**
> >
> > - ⚠️ **Pasta `CreateSheet/Choices/` existe mas está vazia**
> >   - Atualmente escolhas gerenciadas por handlers/validators
> >   - **Precisa:** Decidir se cria motor dedicado ou mantém handlers
> >
> > **4. Validação e Testes:**
> >
> > - ⚠️ Validação completa do sistema de Multiclasse (testes end-to-end)
> > - ⚠️ Conferir criação de feat no editor no config do Data Asset
> > - ⚠️ Validar integridade de dados completa
> >
> > **5. Itens Iniciais e Inventário:**
> >
> > - 📋 Implementar sistema de itens iniciais (classe + background)
> > - 📋 Criar boilerplate de inventário (estruturas modulares)
> > - 📋 Mockup hardcoded para finalizar criação de ficha
> > - 📋 Preparar estruturas para módulo `Inventory/` completo (Fase 4)
> >
> > **Próximos Passos Imediatos:**
> >
> > 1. **Implementar ValidateMulticlassRequirements:**
> >    - Usar FMulticlassValidators::ValidateMulticlassRequirements já existente
> >    - Integrar com FCharacterSheetData
> >    - Testar validação de requisitos AND/OR
> >
> > 2. **Implementar ApplyMulticlassRules:**
> >    - Aplicar regras de multiclasse (proficiências, features, etc.)
> >    - Integrar com ProcessLevelChange e LoadClassProficiencies
> >    - Testar aplicação completa
> >
> > 3. **Decidir Integração:**
> >    - Integrar MulticlassMotor no CharacterSheetCore?
> >    - Ou manter separado (atual)?
> >
> > 4. **Testes End-to-End:**
> >    - Criar personagem completo no editor
> >    - Validar todas as escolhas
> >    - Testar multiclasse com múltiplas classes
> >    - Validar Variant Human completo
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 2: Combate Básico com GAS (2-3 semanas) 🔴 ALTA PRIORIDADE</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Implementar sistema de combate básico usando GAS desde o início
> >
> > **Decisão Arquitetural:** Adiantar GAS para Fase 2 para evitar retrabalho futuro
> >
> > **Componentes Principais:**
> >
> > - 📋 **GAS AttributeSet (C++)**
> >   - Health, MaxHealth
> >   - Stamina (se necessário)
> >   - Meta-Atributos para processamento de dano
> >   - PostGameplayEffectExecute para lógica de dano
> >   - PreAttributeChange para clamping
> >
> > - 📋 **GAS Ability System Component**
> >   - ASC no PlayerState (Player)
> >   - ASC no Character (AI)
> >   - InitAbilityActorInfo configurado corretamente
> >
> > - 📋 **CombatComponent**
> >   - Calcular AC (10 + Dex Mod + Armor)
> >   - Calcular dano de ataque (weapon dice + ability modifier)
> >   - Aplicar dano via Gameplay Effects
> >   - Sistema de ações básico (Attack, Dodge, Dash)
> >
> > - 📋 **WeaponDataTable**
> >   - Armas D&D 5e
> >   - Propriedades (versatile, finesse, two-handed, etc.)
> >   - Damage dice e tipos
> >
> > - 📋 **Gameplay Effects Básicos**
> >   - GE_Damage (Instant) - Aplicar dano
> >   - GE_Heal (Instant) - Curar
> >   - GE_Death (Infinite) - Estado de morte
> >
> > - 📋 **CombatHelpers** (em `Utils/`)
> >   - `CalculateArmorClass()`
> >   - `CalculateAttackRoll()`
> >   - `CalculateDamage()`
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores e modifiers
> >
> > **Entregáveis:**
> >
> > - Sistema de combate funcional com GAS
> > - Health/MaxHealth via AttributeSet
> > - Aplicação de dano via Gameplay Effects
> > - Sistema de morte básico
>
> </details>

</details>

---

## 📅 Médio Prazo (6-12 semanas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Fases Intermediárias</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 3: Sistema de Fichas - NPCs e Monsters (2-3 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Expandir sistema de fichas para NPCs e Monsters
> >
> > **Componentes:**
> >
> > - 📋 **NPCDataAsset**
> >   - Ability Scores fixos (não Point Buy)
> >   - Classe opcional (não obrigatória)
> >   - Stat blocks simplificados
> >   - Validações específicas para NPCs
> >
> > - 📋 **MonsterDataAsset**
> >   - Challenge Rating (CR) ao invés de Level
> >   - Hit Dice variados (d8, d10, d12, d20)
> >   - Armor Class natural
> >   - Traits e Actions customizados
> >   - Resistances/Immunities
> >   - Legendary Actions (monsters especiais)
> >
> > - 📋 **NPCComponent e MonsterComponent**
> >   - Bridge Components para NPCs/Monsters
> >   - Integração com CharacterDataComponent (ou componentes específicos)
> >
> > - 📋 **NPC/Monster Helpers** (em `Utils/`)
> >   - Helpers para cálculos de NPCs/Monsters
> >   - Reutilização de helpers comuns quando aplicável
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas)
> > - ✅ Fase 2 (Combate Básico) - Para integração com combate
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 4: Equipamentos e Recursos (2 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Sistema completo de equipamentos e recursos
> >
> > **Componentes:**
> >
> > - 📋 **EquipmentComponent**
> >   - Equipar/desequipar armas e armaduras
> >   - Bônus de equipamentos (AC, dano, etc.)
> >   - Slots de equipamento (Main Hand, Off Hand, Armor, etc.)
> >   - Integração com GAS (Gameplay Effects para bônus)
> >
> > - 📋 **InventoryComponent** (Módulo Completo)
> >   - Componente runtime, replicável
> >   - Inventário com peso (Carrying Capacity)
> >   - Gerenciamento de itens e containers
> >   - Reutiliza estruturas do boilerplate (Fase 1)
> >   - **📖 Plano Detalhado:** [roadmap-tecnico-inventario-boilerplate.md](roadmap-tecnico-inventario-boilerplate.md) (Fase 2)
> >
> > - 📋 **ItemDataTable**
> >   - Itens D&D 5e (armas, armaduras, consumíveis)
> >   - Propriedades e bônus
> >   - MaxSlots e MaxWeight para containers (já preparado no boilerplate)
> >
> > - 📋 **ResourceComponent** (ou via GAS Attributes)
> >   - Spell Slots (por nível)
> >   - Ki Points
> >   - Rage, etc.
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas) - Boilerplate de inventário já criado
> > - ✅ Fase 2 (Combate Básico) - Para integração com armas
> > - ✅ Fase 3 (NPCs/Monsters) - Para loot e drops
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 5: Features e Habilidades (2-3 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Implementar features de classes e spellcasting via GAS
> >
> > **Componentes:**
> >
> > - 📋 **GAS Abilities (Blueprint)**
> >   - GA_SecondWind (Fighter)
> >   - GA_ActionSurge (Fighter)
> >   - GA_CunningAction (Rogue)
> >   - GA_CastSpell (Spellcasting)
> >   - Habilidades modulares (Base + Filhas)
> >
> > - 📋 **SpellcastingComponent** (Gerenciador de Dados)
> >   - Spell slots (por nível)
> >   - Preparar magias
> >   - Lista de magias conhecidas
> >   - **NOTA:** Execução via GAS Abilities, componente apenas gerencia dados
> >
> > - 📋 **SpellDataTable**
> >   - Magias D&D 5e
> >   - Componentes, duração, alcance
> >   - Nível, escola, etc.
> >
> > - 📋 **Gameplay Effects para Features**
> >   - GE_Cooldown (Duration) - Recarga de habilidades
> >   - GE_Cost (Instant) - Custo de recursos
> >   - GE_Feature (Infinite/Duration) - Features ativas
> >
> > **Dependências:**
> >
> > - ✅ Fase 2 (GAS Básico) - Para Abilities e Effects
> > - ✅ Fase 4 (Recursos) - Para spell slots e recursos
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 6: Sistema de Skills e Saving Throws (1-2 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Sistema completo de skills e saving throws
> >
> > **Componentes:**
> >
> > - 📋 **Skill System**
> >   - Skills com modifiers
> >   - Expertise (Rogue, Bard)
> >   - Skill checks
> >   - Integração com GAS (Tags para condições)
> >
> > - 📋 **Saving Throws**
> >   - Cálculo automático de saving throws
> >   - Saving throw checks
> >   - Integração com GAS (Gameplay Effects para condições)
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas) - Para proficiencies
> > - ✅ Fase 2 (GAS) - Para condições e effects
>
> </details>

</details>

---

## 🔮 Longo Prazo (12+ semanas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌟 Fases Avançadas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 7: Movimento e Física (2 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** Sistema de movimento baseado em D&D 5e
> >
> > **Componentes:**
> >
> > - 📋 **MovementComponent**
> >   - Velocidade baseada em raça/classe
> >   - Dash, Disengage actions
> >   - Integração com GAS (Gameplay Effects para modificadores)
> >
> > - 📋 **JumpComponent**
> >   - Altura baseada em Strength
> >   - Long jump, high jump
> >
> > - 📋 **InteractionComponent**
> >   - Interação com objetos
> >   - Pick up, drop, use items
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores
> > - ✅ Fase 2 (GAS) - Para modificadores de movimento
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 8: UI e Feedback (2-3 semanas)</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Objetivo:** UI reativa e feedback visual
> >
> > **Componentes:**
> >
> > - 📋 **UI Reativa (Event-Driven)**
> >   - Bind em Delegates do GAS (sem Tick)
> >   - GetGameplayAttributeValueChangeDelegate para atributos
> >   - RegisterGameplayTagEvent para habilidades
> >
> > - 📋 **UI Components**
> >   - Health bar (reativa via GAS)
> >   - Action bar (reativa via GAS Tags)
> >   - Inventory UI
> >   - Character sheet UI
> >
> > **Dependências:**
> >
> > - ✅ Fase 2 (GAS) - Para Delegates
> > - ✅ Fase 4 (Equipamentos) - Para Inventory UI
> > - ✅ Fase 5 (Habilidades) - Para Action bar
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Fase 9: Expansão GAS (4-6 semanas)</summary>
>
> > **Status:** 🔮 Futuro
> >
> > **Objetivo:** Expandir GAS para sistemas avançados
> >
> > **Componentes:**
> >
> > - 🔮 **GAS Attributes Expandidos**
> >   - Todos os ability scores como Attributes
> >   - Recursos (Mana, Ki, Rage, etc.)
> >   - Stats derivados (AC, Speed, etc.)
> >
> > - 🔮 **Gameplay Effects Avançados**
> >   - Status Effects (Poisoned, Stunned, etc.)
> >   - Buffs/Debuffs complexos
> >   - Stacking de efeitos
> >
> > - 🔮 **Gameplay Abilities Avançadas**
> >   - Combos e chains
> >   - Habilidades com múltiplos estágios
> >   - Motion Warping para melee
> >
> > **Dependências:**
> >
> > - ✅ Fase 2 (GAS Básico) - Base já implementada
> > - ✅ Fase 5 (Features) - Para expandir
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Fase 10: Sistemas Avançados (4-6 semanas)</summary>
>
> > **Status:** 🔮 Futuro
> >
> > **Objetivo:** Sistemas avançados de progressão e equipamentos
> >
> > **Componentes:**
> >
> > - 🔮 **Character Progression**
> >   - Level up system (1-20)
> >   - ASI (Ability Score Improvement)
> >   - Feat selection
> >   - Features de classes por nível
> >
> > - 🔮 **Equipment System Avançado**
> >   - Weapon enchantments
> >   - Armor properties
> >   - Item sets
> >   - Integração com GAS (Gameplay Effects para bônus)
> >
> > **Dependências:**
> >
> > - ✅ Fase 1 (Sistema de Fichas) - Base
> > - ✅ Fase 4 (Equipamentos) - Para expandir
> > - ✅ Fase 9 (GAS Expandido) - Para bônus complexos
>
> </details>

</details>

---

## 🔄 Histórico de Mudanças no Planejamento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📅 Mudanças Importantes</b></summary>

> **2024-12-XX - Decisão: Adiantar GAS para Fase 2**
> >
> > **Motivo:** Evitar retrabalho futuro. GAS é necessário para D&D 5e (múltiplas condições, buffs/debuffs).
> >
> > **Mudança:**
> >
> > - Fase 2 agora inclui GAS básico (AttributeSet, ASC, Gameplay Effects simples)
> > - HealthComponent removido do planejamento (substituído por GAS AttributeSet)
> > - Combate básico será testado já com GAS
> >
> > **Impacto:**
> >
> > - Curva de aprendizado inicial maior
> > - Mas evita migração futura e retrabalho
> > - Sistema final desde o início
>
> </details>

---

## 📊 Dependências entre Fases

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Mapa de Dependências</b></summary>

> ```
> Fase 1 (Sistema de Fichas)
>   ↓
> Fase 2 (Combate Básico + GAS)
>   ↓
> Fase 3 (NPCs/Monsters) ──┐
>   ↓                      │
> Fase 4 (Equipamentos) ←──┘
>   ↓
> Fase 5 (Features/Habilidades)
>   ↓
> Fase 6 (Skills/Saving Throws)
>   ↓
> Fase 7 (Movimento)
>   ↓
> Fase 8 (UI/Feedback)
>   ↓
> Fase 9 (GAS Expandido)
>   ↓
> Fase 10 (Sistemas Avançados)
> ```
>
> **Nota:** Fases 7-10 podem ser desenvolvidas em paralelo após Fase 6, dependendo da equipe.

</details>

---

## 🎯 Próximos Passos Imediatos

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Ações Imediatas</b></summary>

> 1. **Finalizar Fase 1 (Sistema de Fichas):**
>    - ❌ Implementar ValidateMulticlassRequirements (TODO linha 60)
>    - ❌ Implementar ApplyMulticlassRules (TODO linha 73)
>    - ⚠️ Decidir integração MulticlassMotor no CharacterSheetCore
>    - ⚠️ Testes end-to-end completos
>    - ⚠️ Validar criação de feat no editor
>    - 📋 Implementar sistema de itens iniciais
>    - 📋 Criar boilerplate de inventário (estruturas modulares)
>
> 2. **Iniciar Fase 2:**
>    - 📋 Configurar GAS no projeto
>    - 📋 Criar AttributeSet básico (Health, MaxHealth)
>    - 📋 Configurar ASC (PlayerState para Player, Character para AI)
>    - 📋 Criar Gameplay Effects básicos (Damage, Heal, Death)
>    - 📋 Implementar CombatComponent com integração GAS
>    - 📋 Criar WeaponDataTable
>
> 3. **Preparação:**
>    - 📋 Estudar documentação oficial do GAS
>    - 📋 Revisar padrões do Ali Elzoheiry (já integrados na arquitetura)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[GDD](../design/gdd.md)** - Visão do jogo final
> - **[Arquitetura Técnica](../technical/architecture.md)** - Decisões técnicas e preparação GAS
> - **[Regras D&D 5e](../design/dnd-rules/)** - Regras implementadas
> - **[README Principal](../../README.md)** - Visão geral do projeto

</details>
