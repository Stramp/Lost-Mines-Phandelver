---
title: "Roadmap Completo"
category: planning
tags: [roadmap, planning, phases, development]
last_updated: 2024-12-27
difficulty: intermediate
related: [revisao-estrutural-integracao.md, technical/architecture.md]
---

**Navegação:** [Home](../../README.md) > [Documentação](index.md) > [Planejamento](planning/index.md) > Roadmap

# Roadmap Completo - MyProject2

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral do Roadmap</b></summary>

> Este documento contém o **roadmap completo e detalhado** para transformação do projeto em um **Action RPG baseado em D&D 5e**.
>

> **Objetivo:** Transformar o sistema de fichas atual em um jogo completo, mantendo fidelidade às regras D&D 5ª edição.
>
> **Status Geral:**
>
> - 🔄 **Fase 0:** Configuração de Data Tables (Em andamento - validando tabela por tabela)
> - ⏳ **Fase 1:** Sistema de Fichas (Aguardando Fase 0 - Core funcional parcial, faltam Step 3-6)
> - 📋 **Fase 1.5:** Melhorias e Completude D&D 5e (Aguardando Fase 1 - Spellcasting, ASI, Level Up)
> - 📋 **Fase 2:** Combate Básico com GAS (Aguardando Fase 1.5)
> - 📋 **Fases 3-10:** Planejadas
>
> **📖 Última Revisão:** 2024-12-27 - Fase 0 adicionada (Configuração de Data Tables)
>
> **🗺️ Roadmaps Específicos:**
>
> - **[Validação de Data Tables](data-tables-validation.md)** - Checklist detalhado para validação de cada tabela (Fase 0)
> - **[Roadmap Técnico](roadmap-tecnico.md)** - Bugs, correções e melhorias técnicas
> - **[Roadmap Funcional](roadmap-funcional.md)** - Features por categoria (Step 3-6)
> - **[Estrutura de Roadmaps](roadmap-estrutura.md)** - Documentação da hierarquia
>
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
>
> **Metodologia:**
>
> - 🧪 **TDD** - Test-Driven Development obrigatório (testes ANTES da implementação)
> - 📝 **Test-After** - Testes depois são aceitáveis (Getters/Setters, wrappers simples)
>
</details>
---

## 🔄 Fase 0: Configuração de Data Tables (PRIORIDADE CRÍTICA)

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Configuração e Validação de Data Tables</b></summary>

> **Status:** 🔄 **Em Andamento** - Validando tabela por tabela
>
> **Objetivo:** Garantir que todas as Data Tables estejam 100% configuradas, validadas e prontas antes de continuar com funcionalidades.
>
> **Metodologia:** Confirmar uma tabela por vez, validando estrutura, dados e integração com o sistema.
>
> **Prioridade:** 🔴 **CRÍTICA** - Bloqueia todas as outras fases
>
> ### 📋 Tabelas a Configurar e Validar
>
> <details open>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Tabelas de Referência (Master Data) - 9 Tabelas</summary>
>
> > 1. **DT-001:** AbilityScoreDataTable - ⚠️ Aguardando Validação
> > 2. **DT-002:** TraitDataTable - ⚠️ Aguardando Validação
> > 3. **DT-003:** LanguageDataTable - ⚠️ Aguardando Validação
> > 4. **DT-004:** SkillDataTable - ⚠️ Aguardando Validação
> > 5. **DT-005:** SpellDataTable - ⚠️ Aguardando Validação
> > 6. **DT-006:** SpellSchoolDataTable - ⚠️ Aguardando Validação
> > 7. **DT-007:** DamageTypeDataTable - ⚠️ Aguardando Validação
> > 8. **DT-008:** ConditionDataTable - ⚠️ Aguardando Validação
> > 9. **DT-009:** ProficiencyDataTable - ⚠️ Aguardando Validação
>
> </details>
>
> <details open>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Tabelas Principais - 6 Tabelas</summary>
>
> > 10. **DT-010:** RaceDataTable - ⚠️ Aguardando Validação
> > 11. **DT-011:** ClassDataTable - ⚠️ Aguardando Validação
> > 12. **DT-012:** BackgroundDataTable - ⚠️ Aguardando Validação
> > 13. **DT-013:** FeatDataTable - ⚠️ Aguardando Validação
> > 14. **DT-014:** FeatureDataTable - ⚠️ Aguardando Validação
> > 15. **DT-015:** ItemDataTable - ⚠️ Aguardando Validação
>
> </details>
>
> ### ✅ Checklist de Validação por Tabela
>
> Para cada tabela, validar:
>
> - [ ] **Estrutura:** Struct C++ corresponde ao CSV/JSON
> - [ ] **Dados:** Todos os dados necessários estão presentes
> - [ ] **IDs:** Todos os IDs seguem padrão de nomenclatura
> - [ ] **Referências:** Todas as referências (FDataTableRowHandle) estão corretas
> - [ ] **Validação:** Schema JSON validado (se existir)
> - [ ] **Importação:** Tabela importa corretamente no Unreal Engine
> - [ ] **Integração:** Tabela funciona com CharacterSheetDataAsset
> - [ ] **Testes:** Testes básicos passam (se existirem)
>
> ### 📝 Processo de Validação
>
> 1. **Revisar estrutura** da tabela (struct C++ vs CSV/JSON)
> 2. **Validar dados** (completude, consistência)
> 3. **Testar importação** no Unreal Engine
> 4. **Validar integração** com sistema existente
> 5. **Marcar como ✅ Validada** quando 100% pronta
> 6. **Passar para próxima tabela**
>
> **Status Atual:** Nenhuma tabela validada ainda - começando validação uma por uma.

</details>

---

## ⏱️ Curto Prazo (Próximas 4-6 semanas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Fases Imediatas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Fase 1: Sistema de Fichas (Core Completo - 80%)</summary>
>

</details>
    >
    > **Progresso:** ~70% completo (core funcional, faltam Step 3-6)
    >
    > **Objetivo:** Sistema completo de criação de personagens D&D 5e
    >
    > **O Que Foi Implementado:**
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 1. Motores Básicos (100% Completo)</summary>
    >
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
    > > - ✅ **MulticlassMotor** - Completo
    > >   - GetAvailableClasses (filtra por requisitos)
    > >   - LoadClassProficiencies (carrega proficiências)
    > >   - LoadClassProgression (carrega features por nível)
    > >   - ValidateMulticlassRequirements (via FMulticlassValidators)
    > >
    > > - ✅ **CharacterSheetCore** - Completo
    > >   - Orquestra RaceBonus + PointBuy
    > >   - Fórmula: FinalScore = 8 + RacialBonus + PointBuyAllocation
    > >   - Genérico (funciona em Data Asset e Widget)

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 2. Sistema de Validação (100% Completo)</summary>
    >
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
    > >   - RecalculateMaxHP

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 3. Variant Human (100% Completo)</summary>
    >
    > > - ✅ Feat selection (GetAvailableFeatNames com filtro por ability scores)
    > > - ✅ Skill selection (GetSkillNames)
    > > - ✅ Custom Ability Score Choices (2x +1 para distribuir)
    > > - ✅ Validação completa (feat, skill, ability scores)
    > > - ✅ Handlers dedicados
    > > - ✅ Reset automático quando não é mais Variant Human

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 4. Multiclasse - Estrutura (✅ Completo)</summary>
    >
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

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 5. Sistema de Dropdowns (100% Completo)</summary>
    >
    > > - ✅ GetRaceNames, GetSubraceNames (dependentes)
    > > - ✅ GetBackgroundNames
    > > - ✅ GetAvailableFeatNames (filtrado por ability scores)
    > > - ✅ GetSkillNames
    > > - ✅ GetListClassAvaible (filtrado por requisitos de atributo)
    > > - ✅ GetAvailableLanguageNames

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 6. Cálculos Básicos (✅ Completo)</summary>
    >
    > > - ✅ CalculateAbilityModifier (fórmula D&D 5e)
    > > - ✅ CalculateProficiencyBonus (fórmula D&D 5e)
    > > - ✅ CalculateHPGainForLevel (HP por nível)
    > > - ✅ CalculateMaxHP (HP total multiclasse)
    > > - ✅ CalculateProficiencies (background + Variant Human)
    > > - ✅ CalculateLanguages (raça + background + escolhas)

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ 7. Testes Automatizados (✅ Completo)</summary>
    >
    > > - ✅ **275+ testes implementados**
    > >   - CalculationHelpers (28 testes) - Modificadores, proficiência e cálculos
    > >   - ValidationHelpers (35 testes) - Validações críticas e escolhas
    > >   - CharacterSheetHelpers (36 testes) - Feats, pré-requisitos e helpers
    > >   - DataTableHelpers (13 testes) - Busca em Data Tables
    > >   - FormattingHelpers (10 testes) - Formatação de dados
    > >   - ChoiceHelpers (7 testes) - Parsing e formatação de escolhas
    > >   - FeatDataTable (6 testes) - Pré-requisitos de feats
    > >   - ComponentHelpers (3 testes) - Busca de componentes

    > </details>
    >
    > **O Que Está Faltando:**
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 1. Itens Iniciais e Boilerplate de Inventário (📋 Planejado)</summary>
    >
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

    > </details>
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚠️ 2. Validação e Testes</summary>
    >
    > > - ⚠️ Validação completa do sistema de Multiclasse (testes end-to-end)
    > > - ⚠️ Conferir criação de feat no editor no config do Data Asset
    > > - ⚠️ Validar integridade de dados completa
    > > - ⚠️ **Corrigir testes de Proficiency Bonus** (valores esperados incorretos)

    > </details>

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 1.5: Melhorias e Completude D&D 5e 🔴 ALTA PRIORIDADE</summary>

    > **Status:** 📋 Planejado (Baseado em Revisão Estrutural)
    >
    > **Objetivo:** Completar sistemas D&D 5e documentados mas não implementados
    >
    > **Prioridade:** 🔴 Alta - Essencial para fidelidade às regras D&D 5e
    >
    > **Duração Estimada:** 3-4 semanas
    >
    > **Metodologia:** 🧪 TDD obrigatório para todas as funções helper/motor
    >
    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 1.5.1 - Sistema de Spellcasting (1-2 semanas)</summary>
    >
    > > **Status:** 📋 Planejado
    >
    > > **Prioridade:** 🔴 Alta - Base para Fase 5 (Features e Habilidades)
    >
    > > **Documentação:** `docs/design/dnd-rules/spellcasting.md`
    >
    > > **Tarefas (TDD obrigatório):**
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 1. SpellcastingHelpers (Utils/SpellcastingHelpers.h/cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 **CalculateSpellSaveDC()** - 🧪 TDD
    > > >   - Fórmula: `8 + ProficiencyBonus + SpellcastingAbilityModifier`
    > > >   - Parâmetros: `int32 ProficiencyBonus, int32 SpellcastingAbilityModifier`
    > > >   - Retorno: `int32 SpellSaveDC`
    > > >   - **Testes:** Casos válidos, edge cases (modificadores negativos)
    > > >
    > > > - 📋 **CalculateSpellAttackModifier()** - 🧪 TDD
    > > >   - Fórmula: `ProficiencyBonus + SpellcastingAbilityModifier`
    > > >   - Parâmetros: `int32 ProficiencyBonus, int32 SpellcastingAbilityModifier`
    > > >   - Retorno: `int32 SpellAttackModifier`
    > > >   - **Testes:** Casos válidos, edge cases
    > > >
    > > > - 📋 **GetSpellcastingAbilityByClass()** - 🧪 TDD
    > > >   - Retorna ability score usado para spellcasting por classe
    > > >   - Tabela: Bard/CHA, Cleric/WIS, Druid/WIS, Paladin/CHA, Ranger/WIS, Sorcerer/CHA, Warlock/CHA, Wizard/INT
    > > >   - Parâmetros: `FName ClassName`
    > > >   - Retorno: `FName AbilityID` (ex: "ABL_Charisma")
    > > >   - **Testes:** Todas as classes, classe inválida
    > > >
    > > > - 📋 **CalculateSpellSlotsForLevel()** - 🧪 TDD
    > > >   - Calcula spell slots por nível baseado em tipo de caster
    > > >   - Tipos: Full Caster (Wizard, Cleric, Druid, Sorcerer, Bard), Half Caster (Paladin, Ranger), Warlock (Pact Magic)
    > > >   - Parâmetros: `FName ClassName, int32 ClassLevel, ECasterType CasterType`
    > > >   - Retorno: `TMap<int32, int32>` (SpellLevel → Count)
    > > >   - **Testes:** Todos os níveis (1-20), todos os tipos de caster, edge cases
    > > >
    > > > - 📋 **CalculateCantripsKnown()** - 🧪 TDD
    > > >   - Calcula cantrips conhecidos por nível e classe
    > > >   - Tabela por classe: Bard (2,3,4), Cleric (3,4,5), Druid (2,3,4), Sorcerer (4,5,6), Warlock (2,3,4), Wizard (3,4,5)
    > > >   - Parâmetros: `FName ClassName, int32 ClassLevel`
    > > >   - Retorno: `int32 CantripsKnown`
    > > >   - **Testes:** Todas as classes, todos os níveis relevantes, classes sem cantrips
    > > >
    > > > - 📋 **CalculateSpellsPrepared()** - 🧪 TDD
    > > >   - Fórmula: `SpellcastingAbilityModifier + ClassLevel` (mínimo 1)
    > > >   - Apenas para: Cleric, Druid, Paladin, Wizard
    > > >   - Parâmetros: `int32 SpellcastingAbilityModifier, int32 ClassLevel`
    > > >   - Retorno: `int32 SpellsPrepared`
    > > >   - **Testes:** Casos válidos, modificador negativo (mínimo 1), edge cases
    > > >
    > > > - 📋 **CalculateMulticlassCasterLevel()** - 🧪 TDD
    > > >   - Fórmula: `FullCasterLevels + floor(HalfCasterLevels / 2)`
    > > >   - Warlock é separado (Pact Magic, não combina)
    > > >   - Parâmetros: `TMap<FName, int32> ClassLevels` (ClassName → Level)
    > > >   - Retorno: `int32 CasterLevel`
    > > >   - **Testes:** Combinações de classes, Warlock separado, edge cases
    > > >
    > > > - 📋 **GetSpellSlotRecoveryType()** - 🧪 TDD
    > > >   - Retorna tipo de recuperação: Long Rest, Short Rest, Arcane Recovery
    > > >   - Parâmetros: `FName ClassName`
    > > >   - Retorno: `ESpellSlotRecoveryType`
    > > >   - **Testes:** Todas as classes, classe inválida

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 2. SpellcastingConstants (Utils/DnDConstants.h)</summary>
    >
    > > > - 📋 Adicionar constantes de spellcasting
    > > >   - `SPELL_SAVE_DC_BASE = 8`
    > > >   - `SPELL_SAVE_DC_PROFICIENCY_MULTIPLIER = 1`
    > > >   - Tabelas de spell slots (Full Caster, Half Caster, Warlock)
    > > >   - Tabelas de cantrips conhecidos por classe

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 3. Testes Automatizados (Utils/Tests/SpellcastingHelpersTests.cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 Testes para todas as funções acima
    > > >   - Casos válidos (happy path)
    > > >   - Edge cases (valores extremos, modificadores negativos)
    > > >   - Validação de fórmulas D&D 5e
    > > >   - **Estimativa:** 50-70 testes

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔗 4. Integração com CharacterSheetDataAsset</summary>
    >
    > > > - 📋 Adicionar campos calculados:
    > > >   - `SpellSaveDC` (calculado)
    > > >   - `SpellAttackModifier` (calculado)
    > > >   - `SpellSlots` (TMap<int32, int32> - SpellLevel → Count)
    > > >   - `CantripsKnown` (int32)
    > > >   - `SpellsPrepared` (int32, se aplicável)
    > > >   - Updaters para recalcular quando classe/nível muda
    > > >
    > > > **Dependências:**
    > > >
    > > > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores e modifiers
    > > > - ✅ CalculateProficiencyBonus (já implementado)
    > > >
    > > > **Entregáveis:**
    > > >
    > > > - SpellcastingHelpers completo com testes
    > > > - Cálculos de Spell Save DC, Spell Attack, Spell Slots
    > > > - Suporte a multiclassing spell slots
    > > > - Integração com CharacterSheetDataAsset

    > > </details>

    > </details>

    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 1.5.2 - Sistema de ASI (Ability Score Improvements) (1 semana)</summary>
    >
    > > **Status:** 📋 Planejado
    >
    > > **Prioridade:** 🔴 Alta - Essencial para progressão de personagem
    >
    > > **Documentação:** `docs/design/dnd-rules/ability-scores.md`
    >
    > > **Tarefas (TDD obrigatório):**
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 1. ASIHelpers (Utils/ASIHelpers.h/cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 **GetASILevelsForClass()** - 🧪 TDD
    > > >   - Retorna níveis que concedem ASI para uma classe
    > > >   - Padrão: 4, 8, 12, 16, 19
    > > >   - Exceções: Fighter/Rogue recebem extras (6, 10, 14)
    > > >   - Parâmetros: `FName ClassName`
    > > >   - Retorno: `TArray<int32>` (níveis com ASI)
    > > >   - **Testes:** Todas as classes, Fighter/Rogue extras, classe inválida
    > > >
    > > > - 📋 **CanTakeASIAtLevel()** - 🧪 TDD
    > > >   - Verifica se personagem pode tomar ASI em um nível específico
    > > >   - Considera nível total e classe específica
    > > >   - Parâmetros: `int32 TotalLevel, FName ClassName, int32 ClassLevel`
    > > >   - Retorno: `bool`
    > > >   - **Testes:** Níveis válidos, níveis inválidos, multiclasse
    > > >
    > > > - 📋 **GetASIOptions()** - 🧪 TDD
    > > >   - Retorna opções de ASI disponíveis
    > > >   - Opção 1: +2 em um atributo
    > > >   - Opção 2: +1 em dois atributos
    > > >   - Parâmetros: `TMap<FName, int32> CurrentAbilityScores`
    > > >   - Retorno: `TArray<FASIOption>` (estrutura com opções)
    > > >   - **Testes:** Validação de máximo (20), opções válidas, edge cases
    > > >
    > > > - 📋 **ValidateASISelection()** - 🧪 TDD
    > > >   - Valida seleção de ASI
    > > >   - Verifica se não excede máximo (20)
    > > >   - Verifica se opção é válida (+2 em um OU +1 em dois)
    > > >   - Parâmetros: `FASIOption SelectedOption, TMap<FName, int32> CurrentAbilityScores`
    > > >   - Retorno: `bool`
    > > >   - **Testes:** Seleções válidas, inválidas, máximo atingido

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 2. ASIStructs (Data/Structures/FASIStructs.h)</summary>
    >
    > > > - 📋 Criar estruturas:
    > > >   - `FASIOption` (tipo: +2 em um OU +1 em dois)
    > > >   - `FASIEntry` (nível, classe, opção selecionada)

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 3. Testes Automatizados (Utils/Tests/ASIHelpersTests.cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 Testes para todas as funções acima
    > > >   - Casos válidos
    > > >   - Edge cases
    > > >   - Validação de regras D&D 5e
    > > >   - **Estimativa:** 30-40 testes

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔗 4. Integração com CharacterSheetDataAsset</summary>
    >
    > > > - 📋 Adicionar campo:
    > > >   - `ASISelections` (TArray<FASIEntry>)
    > > >   - Updaters para recalcular ability scores finais com ASIs
    > > >   - Handlers para processar seleção de ASI
    > > >
    > > > **Dependências:**
    > > >
    > > > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores
    > > > - ✅ CalculateProficiencyBonus (já implementado)
    > > >
    > > > **Entregáveis:**
    > > >
    > > > - ASIHelpers completo com testes
    > > > - Sistema de seleção de ASI
    > > > - Integração com CharacterSheetDataAsset

    > > </details>

    > </details>

    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 1.5.3 - Level Up System Completo (1 semana)</summary>
    >
    > > **Status:** 📋 Planejado
    >
    > > **Prioridade:** 🟡 Média - Importante mas não bloqueante
    >
    > > **Documentação:** `docs/design/dnd-rules/level-up.md`
    >
    > > **Tarefas (TDD obrigatório):**
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 1. LevelUpMotor (CreateSheet/LevelUp/LevelUpMotor.h/cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 **ProcessLevelUp()** - 🧪 TDD
    > > >   - Processa ganho de nível completo
    > > >   - Valida pré-requisitos
    > > >   - Aplica features do nível
    > > >   - Oferece escolhas (ASI, Feat, Features)
    > > >   - Parâmetros: `FCharacterSheetData& Data, FName ClassName, int32 NewLevel`
    > > >   - Retorno: `FLevelUpResult` (estrutura com escolhas disponíveis)
    > > >   - **Testes:** Level up válido, inválido, multiclasse, edge cases
    > > >
    > > > - 📋 **GetAvailableChoicesAtLevel()** - 🧪 TDD
    > > >   - Retorna escolhas disponíveis em um nível
    > > >   - ASI (se nível apropriado)
    > > >   - Feat (se nível apropriado)
    > > >   - Features de classe (se houver)
    > > >   - Parâmetros: `FName ClassName, int32 Level`
    > > >   - Retorno: `TArray<FLevelUpChoice>`
    > > >   - **Testes:** Todos os níveis, todas as classes, escolhas corretas
    > > >
    > > > - 📋 **ValidateLevelUpPrerequisites()** - 🧪 TDD
    > > >   - Valida pré-requisitos para level up
    > > >   - Verifica nível máximo (20)
    > > >   - Verifica pré-requisitos de features
    > > >   - Parâmetros: `FCharacterSheetData& Data, FName ClassName, int32 NewLevel`
    > > >   - Retorno: `bool`
    > > >   - **Testes:** Pré-requisitos válidos, inválidos, nível máximo

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 2. LevelUpHelpers (CreateSheet/LevelUp/LevelUpHelpers.h/cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 **CalculateHPGainForLevelUp()** - 🧪 TDD
    > > >   - Calcula HP ganho ao subir de nível
    > > >   - Usa CalculateHPGainForLevel (já existe)
    > > >   - Parâmetros: `int32 HitDie, int32 NewLevel, int32 ConstitutionModifier`
    > > >   - Retorno: `int32 HPGain`
    > > >   - **Testes:** Todos os níveis, todos os hit dice, modificadores negativos
    > > >
    > > > - 📋 **GetFeaturesUnlockedAtLevel()** - 🧪 TDD
    > > >   - Retorna features desbloqueadas em um nível específico
    > > >   - Usa ClassDataTable
    > > >   - Parâmetros: `FName ClassName, int32 Level, UDataTable* ClassDataTable`
    > > >   - Retorno: `TArray<FDataTableRowHandle>` (FeatureHandles)
    > > >   - **Testes:** Todos os níveis, todas as classes, features corretas

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 3. Testes Automatizados (CreateSheet/LevelUp/Tests/LevelUpMotorTests.cpp) - 🧪 TDD</summary>
    >
    > > > - 📋 Testes para todas as funções acima
    > > >   - Casos válidos
    > > >   - Edge cases
    > > >   - Validação de regras D&D 5e
    > > >   - **Estimativa:** 40-50 testes

    > > </details>
    >
    > > <details>
    > > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔗 4. Integração com CharacterSheetDataAsset</summary>
    >
    > > > - 📋 Handlers para processar level up
    > > >   - `HandleLevelUp()` - Processa level up completo
    > > >   - `HandleASISelection()` - Processa seleção de ASI
    > > >   - `HandleFeatSelection()` - Processa seleção de Feat
    > > >   - Updaters para recalcular após level up
    > > >
    > > > **Dependências:**
    > > >
    > > > - ✅ Fase 1 (Sistema de Fichas) - Para estrutura base
    > > > - ✅ Fase 1.5.2 (ASI) - Para sistema de ASI
    > > > - ✅ CalculateHPGainForLevel (já implementado)
    > > >
    > > > **Entregáveis:**
    > > >
    > > > - LevelUpMotor completo com testes
    > > > - Sistema de level up funcional
    > > > - Integração com CharacterSheetDataAsset

    > > </details>

    > </details>

    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 1.5.4 - Correção de Testes Proficiency Bonus (2-4 horas)</summary>
    >
    > > **Status:** ⚠️ Pendente
    >
    > > **Prioridade:** 🟡 Média - Correção de testes existentes
    >
    > > **Problema Identificado:**
    >
    > > - Testes esperam valores incorretos (base 1 ao invés de base 2)
    > > - Código está correto: `PROFICIENCY_BONUS_BASE (2) + floor((TotalLevel - MIN_LEVEL) / PROFICIENCY_BONUS_DIVISOR)`
    >
    > > **Tarefas:**
    >
    > > - 📋 Corrigir valores esperados em `CalculationHelpersTests.cpp`
    > >   - Nível 1: Esperado 2 (não 1)
    > >   - Nível 5: Esperado 3 (não 2)
    > >   - Nível 9: Esperado 4 (não 3)
    > >   - Nível 13: Esperado 5 (não 4)
    > >   - Nível 17: Esperado 6 (não 5)
    > >   - Nível 20: Esperado 6 (não 5)
    > >
    > > **Dependências:**
    >
    > > - ✅ Código já está correto
    >
    > > **Entregáveis:**
    >
    > > - Testes corrigidos e passando

    > </details>

    > <details>
    > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 1.5.5 - Multiclassing Spell Slots (Integrado em 1.5.1)</summary>
    >
    > > **Status:** 📋 Planejado (Integrado em Spellcasting)
    >
    > > **Prioridade:** 🟢 Baixa - Já coberto em SpellcastingHelpers
    >
    > > **Nota:** `CalculateMulticlassCasterLevel()` já está incluído em Fase 1.5.1 (Spellcasting)

    > </details>

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 2: Combate Básico com GAS (2-3 semanas) 🔴 ALTA PRIORIDADE</summary>

    > **Status:** 📋 Planejado
    >
    > **Objetivo:** Implementar sistema de combate básico usando GAS desde o início
    >
    > **Decisão Arquitetural:** Adiantar GAS para Fase 2 para evitar retrabalho futuro
    >
    > **Componentes Principais:**
    >
    > - 📋 **GAS AttributeSet (C++)**
    >   - Health, MaxHealth
    >   - Stamina (se necessário)
    >   - Meta-Atributos para processamento de dano
    >   - PostGameplayEffectExecute para lógica de dano
    >   - PreAttributeChange para clamping
    >
    > - 📋 **GAS Ability System Component**
    >   - ASC no PlayerState (Player)
    >   - ASC no Character (AI)
    >   - InitAbilityActorInfo configurado corretamente
    >
    > - 📋 **CombatComponent**
    >   - Calcular AC (10 + Dex Mod + Armor)
    >   - Calcular dano de ataque (weapon dice + ability modifier)
    >   - Aplicar dano via Gameplay Effects
    >   - Sistema de ações básico (Attack, Dodge, Dash)
    >
    > - 📋 **WeaponDataTable**
    >   - Armas D&D 5e
    >   - Propriedades (versatile, finesse, two-handed, etc.)
    >   - Damage dice e tipos
    >
    > - 📋 **Gameplay Effects Básicos**
    >   - GE_Damage (Instant) - Aplicar dano
    >   - GE_Heal (Instant) - Curar
    >   - GE_Death (Infinite) - Estado de morte
    >
    > - 📋 **CombatHelpers** (em `Utils/`) - 🧪 TDD
    >   - `CalculateArmorClass()` - 🧪 TDD
    >   - `CalculateAttackRoll()` - 🧪 TDD
    >   - `CalculateDamage()` - 🧪 TDD
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores e modifiers
    > - ✅ Fase 1.5 (Melhorias D&D 5e) - Para spellcasting e ASI
    >
    > **Entregáveis:**
    >
    > - Sistema de combate funcional com GAS
    > - Health/MaxHealth via AttributeSet
    > - Aplicação de dano via Gameplay Effects
    > - Sistema de morte básico

    </details>

    </details>

## 📅 Médio Prazo (6-12 semanas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Fases Intermediárias</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 3: Sistema de Fichas - NPCs e Monsters (2-3 semanas)</summary>
>

</details>
    >
    > **Objetivo:** Expandir sistema de fichas para NPCs e Monsters
    >
    > **Componentes:**
    >
    > - 📋 **NPCDataAsset**
    >   - Ability Scores fixos (não Point Buy)
    >   - Classe opcional (não obrigatória)
    >   - Stat blocks simplificados
    >   - Validações específicas para NPCs
    >
    > - 📋 **MonsterDataAsset**
    >   - Challenge Rating (CR) ao invés de Level
    >   - Hit Dice variados (d8, d10, d12, d20)
    >   - Armor Class natural
    >   - Traits e Actions customizados
    >   - Resistances/Immunities
    >   - Legendary Actions (monsters especiais)
    >
    > - 📋 **NPCComponent e MonsterComponent**
    >   - Bridge Components para NPCs/Monsters
    >   - Integração com CharacterDataComponent (ou componentes específicos)
    >
    > - 📋 **NPC/Monster Helpers** (em `Utils/`) - 🧪 TDD
    >   - Helpers para cálculos de NPCs/Monsters
    >   - Reutilização de helpers comuns quando aplicável
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas)
    > - ✅ Fase 2 (Combate Básico) - Para integração com combate

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 4: Equipamentos e Recursos (2 semanas)</summary>

    > **Status:** 📋 Planejado
    >
    > **Objetivo:** Sistema completo de equipamentos e recursos
    >
    > **Componentes:**
    >
    > - 📋 **EquipmentComponent**
    >   - Equipar/desequipar armas e armaduras
    >   - Bônus de equipamentos (AC, dano, etc.)
    >   - Slots de equipamento (Main Hand, Off Hand, Armor, etc.)
    >   - Integração com GAS (Gameplay Effects para bônus)
    >
    > - 📋 **InventoryComponent** (Módulo Completo)
    >   - Componente runtime, replicável
    >   - Inventário com peso (Carrying Capacity)
    >   - Gerenciamento de itens e containers
    >   - Reutiliza estruturas do boilerplate (Fase 1)
    >   - **📖 Plano Detalhado:** [roadmap-tecnico-inventario-boilerplate.md](roadmap-tecnico-inventario-boilerplate.md) (Fase 2)
    >
    > - 📋 **ItemDataTable**
    >   - Itens D&D 5e (armas, armaduras, consumíveis)
    >   - Propriedades e bônus
    >   - MaxSlots e MaxWeight para containers (já preparado no boilerplate)
    >
    > - 📋 **ResourceComponent** (ou via GAS Attributes)
    >   - Spell Slots (por nível) - Usa SpellcastingHelpers da Fase 1.5.1
    >   - Ki Points
    >   - Rage, etc.
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas) - Boilerplate de inventário já criado
    > - ✅ Fase 1.5.1 (Spellcasting) - Para spell slots
    > - ✅ Fase 2 (Combate Básico) - Para integração com armas
    > - ✅ Fase 3 (NPCs/Monsters) - Para loot e drops

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 5: Features e Habilidades (2-3 semanas)</summary>

    > **Status:** 📋 Planejado
    >
    > **Objetivo:** Implementar features de classes e spellcasting via GAS
    >
    > **Componentes:**
    >
    > - 📋 **GAS Abilities (Blueprint)**
    >   - GA_SecondWind (Fighter)
    >   - GA_ActionSurge (Fighter)
    >   - GA_CunningAction (Rogue)
    >   - GA_CastSpell (Spellcasting) - Usa SpellcastingHelpers da Fase 1.5.1
    >   - Habilidades modulares (Base + Filhas)
    >
    > - 📋 **SpellcastingComponent** (Gerenciador de Dados)
    >   - Spell slots (por nível) - Usa SpellcastingHelpers
    >   - Preparar magias
    >   - Lista de magias conhecidas
    >   - **NOTA:** Execução via GAS Abilities, componente apenas gerencia dados
    >
    > - 📋 **SpellDataTable**
    >   - Magias D&D 5e (já existe estrutura básica)
    >   - Componentes, duração, alcance
    >   - Nível, escola, etc.
    >
    > - 📋 **Gameplay Effects para Features**
    >   - GE_Cooldown (Duration) - Recarga de habilidades
    >   - GE_Cost (Instant) - Custo de recursos
    >   - GE_Feature (Infinite/Duration) - Features ativas
    >
    > **Dependências:**
    >
    > - ✅ Fase 1.5.1 (Spellcasting) - Para cálculos de spellcasting
    > - ✅ Fase 2 (GAS Básico) - Para Abilities e Effects
    > - ✅ Fase 4 (Recursos) - Para spell slots e recursos

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 6: Sistema de Skills e Saving Throws (1-2 semanas)</summary>

    > **Status:** 📋 Planejado
    >
    > **Objetivo:** Sistema completo de skills e saving throws
    >
    > **Componentes:**
    >
    > - 📋 **Skill System**
    >   - Skills com modifiers
    >   - Expertise (Rogue, Bard)
    >   - Skill checks
    >   - Integração com GAS (Tags para condições)
    >
    > - 📋 **Saving Throws**
    >   - Cálculo automático de saving throws
    >   - Saving throw checks
    >   - Integração com GAS (Gameplay Effects para condições)
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas) - Para proficiencies
    > - ✅ Fase 1.5.1 (Spellcasting) - Para Spell Save DC
    > - ✅ Fase 2 (GAS) - Para condições e effects

    </details>

    </details>

## 🔮 Longo Prazo (12+ semanas)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌟 Fases Avançadas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 7: Movimento e Física (2 semanas)</summary>
>

</details>
    >
    > **Objetivo:** Sistema de movimento baseado em D&D 5e
    >
    > **Componentes:**
    >
    > - 📋 **MovementComponent**
    >   - Velocidade baseada em raça/classe
    >   - Dash, Disengage actions
    >   - Integração com GAS (Gameplay Effects para modificadores)
    >
    > - 📋 **JumpComponent**
    >   - Altura baseada em Strength
    >   - Long jump, high jump
    >
    > - 📋 **InteractionComponent**
    >   - Interação com objetos
    >   - Pick up, drop, use items
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas) - Para ability scores
    > - ✅ Fase 2 (GAS) - Para modificadores de movimento

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Fase 8: UI e Feedback (2-3 semanas)</summary>

    > **Status:** 📋 Planejado
    >
    > **Objetivo:** UI reativa e feedback visual
    >
    > **Componentes:**
    >
    > - 📋 **UI Reativa (Event-Driven)**
    >   - Bind em Delegates do GAS (sem Tick)
    >   - GetGameplayAttributeValueChangeDelegate para atributos
    >   - RegisterGameplayTagEvent para habilidades
    >
    > - 📋 **UI Components**
    >   - Health bar (reativa via GAS)
    >   - Action bar (reativa via GAS Tags)
    >   - Inventory UI
    >   - Character sheet UI
    >
    > **Dependências:**
    >
    > - ✅ Fase 2 (GAS) - Para Delegates
    > - ✅ Fase 4 (Equipamentos) - Para Inventory UI
    > - ✅ Fase 5 (Habilidades) - Para Action bar

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Fase 9: Expansão GAS (4-6 semanas)</summary>

    > **Status:** 🔮 Futuro
    >
    > **Objetivo:** Expandir GAS para sistemas avançados
    >
    > **Componentes:**
    >
    > - 🔮 **GAS Attributes Expandidos**
    >   - Todos os ability scores como Attributes
    >   - Recursos (Mana, Ki, Rage, etc.)
    >   - Stats derivados (AC, Speed, etc.)
    >
    > - 🔮 **Gameplay Effects Avançados**
    >   - Status Effects (Poisoned, Stunned, etc.)
    >   - Buffs/Debuffs complexos
    >   - Stacking de efeitos
    >
    > - 🔮 **Gameplay Abilities Avançadas**
    >   - Combos e chains
    >   - Habilidades com múltiplos estágios
    >   - Motion Warping para melee
    >
    > **Dependências:**
    >
    > - ✅ Fase 2 (GAS Básico) - Base já implementada
    > - ✅ Fase 5 (Features) - Para expandir

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Fase 10: Sistemas Avançados (4-6 semanas)</summary>

    > **Status:** 🔮 Futuro
    >
    > **Objetivo:** Sistemas avançados de progressão e equipamentos
    >
    > **Componentes:**
    >
    > - 🔮 **Character Progression**
    >   - Level up system (1-20) - Já implementado em Fase 1.5.3
    >   - ASI (Ability Score Improvement) - Já implementado em Fase 1.5.2
    >   - Feat selection - Já implementado (Fase 1)
    >   - Features de classes por nível - Já implementado (Fase 1)
    >
    > - 🔮 **Equipment System Avançado**
    >   - Weapon enchantments
    >   - Armor properties
    >   - Item sets
    >   - Integração com GAS (Gameplay Effects para bônus)
    >
    > **Dependências:**
    >
    > - ✅ Fase 1 (Sistema de Fichas) - Base
    > - ✅ Fase 1.5 (Melhorias D&D 5e) - Level up e ASI
    > - ✅ Fase 4 (Equipamentos) - Para expandir
    > - ✅ Fase 9 (GAS Expandido) - Para bônus complexos

    </details>

    </details>

## 🔄 Histórico de Mudanças no Planejamento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📅 Mudanças Importantes</b></summary>

> **2024-12-XX - Revisão Estrutural: Nova Fase 1.5 - Melhorias D&D 5e**
> >
> > **Motivo:** Revisão completa da estrutura identificou sistemas D&D 5e documentados mas não implementados.
> >
> > **Mudança:**
> >
> > - Nova **Fase 1.5** adicionada: Melhorias e Completude D&D 5e
> > - **Fase 1.5.1:** Sistema de Spellcasting (Spell Save DC, Spell Attack, Spell Slots)
> > - **Fase 1.5.2:** Sistema de ASI (Ability Score Improvements)
> > - **Fase 1.5.3:** Level Up System Completo
> > - **Fase 1.5.4:** Correção de Testes Proficiency Bonus
> > - **Fase 1.5.5:** Multiclassing Spell Slots (integrado em Spellcasting)
> >
> > **Impacto:**
> >
> > - Fidelidade completa às regras D&D 5e
> > - Base sólida para Fase 5 (Features e Habilidades)
> > - Todas as tarefas seguem TDD obrigatório
> > - Estimativa: 3-4 semanas adicionais
>

> **2024-12-XX - Decisão: Adiantar GAS para Fase 2**
</details>
    >
    > **Motivo:** Evitar retrabalho futuro. GAS é necessário para D&D 5e (múltiplas condições, buffs/debuffs).
    >
    > **Mudança:**
    >
    > - Fase 2 agora inclui GAS básico (AttributeSet, ASC, Gameplay Effects simples)
    > - HealthComponent removido do planejamento (substituído por GAS AttributeSet)
    > - Combate básico será testado já com GAS
    >
    > **Impacto:**
    >
    > - Curva de aprendizado inicial maior
    > - Mas evita migração futura e retrabalho
    > - Sistema final desde o início

---

## 📊 Dependências entre Fases

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Mapa de Dependências</b></summary>

> ```text
> Fase 1 (Sistema de Fichas - 80%)
> ↓
> Fase 1.5 (Melhorias D&D 5e) ← NOVA
> ├── 1.5.1: Spellcasting
> ├── 1.5.2: ASI
> ├── 1.5.3: Level Up System
> ├── 1.5.4: Correção Testes
> └── 1.5.5: Multiclassing Spell Slots (integrado)
> ↓
> Fase 2 (Combate Básico + GAS)
> ↓
> Fase 3 (NPCs/Monsters) ──┐
> ↓                      │
> Fase 4 (Equipamentos) ←─┘
> ↓
> Fase 5 (Features/Habilidades)
> ↓
> Fase 6 (Skills/Saving Throws)
> ↓
> Fase 7 (Movimento)
> ↓
> Fase 8 (UI/Feedback)
> ↓
> Fase 9 (GAS Expandido)
> ↓
> Fase 10 (Sistemas Avançados)
> ```
>

> **Nota:** Fases 7-10 podem ser desenvolvidas em paralelo após Fase 6, dependendo da equipe.
>
</details>
---

## 🎯 Próximos Passos Imediatos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Ações Imediatas</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1. Finalizar Fase 1 (Sistema de Fichas)</summary>
>

</details>
    > - ✅ MulticlassMotor funcional (GetAvailableClasses, LoadClassProficiencies, LoadClassProgression)
    > - ✅ **Testes unitários de helpers críticos (275+ testes implementados)**
    > - ⚠️ Testes de integração end-to-end completos
    > - ⚠️ Validar criação de feat no editor
    > - ⚠️ **Corrigir testes de Proficiency Bonus** (valores esperados incorretos)
    > - 📋 Implementar sistema de itens iniciais
    > - 📋 Criar boilerplate de inventário (estruturas modulares)

    </details>

    </details>
>
> **📋 Após Completar Prioridades 1-3, iniciar Fase 1.5:**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Fase 1.5: Melhorias e Completude D&D 5e</summary>
>
> > **Status:** 📋 Aguardando conclusão de Fase 1
> >
> > **Duração Estimada:** 3-4 semanas
> >
> > **Sub-fases:**
> >
> > 1. **1.5.1:** Sistema de Spellcasting (1-2 semanas) - 🧪 TDD obrigatório
> > 2. **1.5.2:** Sistema de ASI (1 semana) - 🧪 TDD obrigatório
> > 3. **1.5.3:** Level Up System Completo (1 semana) - 🧪 TDD obrigatório
> >
> > **📖 Detalhes completos:** Ver seção "Fase 1.5" abaixo neste documento

</details>
>
> **📋 Preparação para Fase 2:**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Preparação para Combate Básico com GAS</summary>
>
> > **Status:** 📋 Aguardando Fase 1.5
> >
> > **Tarefas:**
> >
> > - Estudar documentação oficial do GAS
> > - Revisar padrões do Ali Elzoheiry (já integrados na arquitetura)
> > - Preparar estruturas de dados para combate

</details>

</details>

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[GDD](../design/gdd.md)** - Visão do jogo final
> - **[Arquitetura Técnica](../technical/architecture.md)** - Decisões técnicas e preparação GAS
> - **[Regras D&D 5e](../design/dnd-rules/)** - Regras implementadas
> - **[Spellcasting](../design/dnd-rules/spellcasting.md)** - Regras de spellcasting
> - **[Ability Scores](../design/dnd-rules/ability-scores.md)** - Regras de ASI
> - **[Level Up](../design/dnd-rules/level-up.md)** - Sistema de level up
> - **[Multiclassing](../design/dnd-rules/multiclassing.md)** - Regras de multiclassing
> - **[README Principal](../../README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](../../ARCHITECTURE.md)** - Resumo da arquitetura
> - **[CHANGELOG.md](../../CHANGELOG.md)** - Histórico de mudanças
> - **[Índice de Documentação](../index.md)** - Organização completa
> - **[Plano Técnico: Itens Iniciais](roadmap-tecnico-itens-iniciais.md)** - Implementação detalhada
> > - **[Plano Técnico: Boilerplate de Inventário](roadmap-tecnico-inventario-boilerplate.md)** - Estruturas modulares
> > - **[Roadmap Técnico](roadmap-tecnico.md)** - Bugs, correções e melhorias técnicas
> > - **[Roadmap Funcional](roadmap-funcional.md)** - Features por categoria (Step 3-6)
> > - **[Estrutura de Roadmaps](roadmap-estrutura.md)** - Documentação da hierarquia
>
>
</details>

---

## 📐 Estrutura Hierárquica e Metodologia Ágil

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Navegação entre Níveis</b></summary>

> Este roadmap principal fornece **visão estratégica** e **fases principais (Epics)**.
>
> **Para tarefas detalhadas e acionáveis, consulte os roadmaps específicos:**
>
> 1. **[Roadmap Técnico](roadmap-tecnico.md)** - Bugs, correções e melhorias técnicas
>    - User Stories técnicas
>    - Tarefas puras com estimativas
>    - Priorização MoSCoW
>    - Definition of Done
>
> 2. **[Roadmap Funcional](roadmap-funcional.md)** - Features por categoria
>    - User Stories funcionais
>    - Organizado pelos 6 passos do D&D 5e
>    - Tarefas puras para cada feature
>    - Dependências explícitas
>
> 3. **[Backlog](backlog.md)** - Lista priorizada de trabalho
>    - Organizado por MoSCoW (Must/Should/Could/Won't)
>    - Atualizado continuamente
>    - Base para planejamento de sprints
>
> 4. **[Sprints](sprints.md)** - Planejamento de iterações
>    - Sprints de 1-2 semanas
>    - Velocity tracking
>    - Burndown charts
>
> 5. **[Metodologia Ágil](agile-methodology.md)** - Guia completo de uso
>    - Epics, User Stories, Tasks
>    - Definition of Done
>    - Cerimônias ágeis
>
> 6. **[Estrutura de Roadmaps](roadmap-estrutura.md)** - Documentação completa da hierarquia
>    - Explica níveis hierárquicos
>    - Checklist de tarefa pura
>    - Navegação entre níveis
>
> **Fluxo Recomendado (Ágil):**
>
> ```
> Epic (Fase) → User Story → Task → Backlog → Sprint → Done
> ```

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 3.0 - Estrutura Hierárquica e Caminho Claro
