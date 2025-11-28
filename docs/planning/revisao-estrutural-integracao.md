# Revisão Estrutural - Integração no Roadmap

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo Executivo</b></summary>

> Este documento detalha a **revisão estrutural completa** realizada em 2024-12-XX, comparando a estrutura atual do projeto com os princípios de `planos5.md` e as regras D&D 5e documentadas em `dnd-rules/`.
>
> **Resultado:** Identificação de sistemas D&D 5e documentados mas não implementados, resultando na criação da **Fase 1.5 - Melhorias e Completude D&D 5e** no roadmap.
>
> **Status:** ✅ Integrado no roadmap principal

</details>

---

## ✅ Pontos Fortes Identificados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Estrutura Alinhada com planos5.md</b></summary>

> **1. Padrão "ID + Tags + Payload" - ✅ Implementado Corretamente**
> >
> > - Todas as 15 Data Tables seguem o padrão
> > - `Name` como primeiro campo (Key Field obrigatório)
> > - `ID` como segundo campo (identificador único)
> > - `TypeTags` (FGameplayTagContainer) para categorização
> > - Payload (TMap<FName, FString>) para dados específicos
>
> **2. Data-Oriented Design - ✅ Seguido Corretamente**
> >
> > - Separação Static/Dynamic (Data Tables vs Components)
> > - Estrutura flat (JSONs planos, sem aninhamento profundo)
> > - Composição sobre Herança (Component-Based Architecture)
> > - Normalização de dados (FDataTableRowHandle, Gameplay Tags)
>
> **3. Component-Based Architecture - ✅ Implementado Corretamente**
> >
> > - Arquitetura em 4 camadas bem definida
> > - Separação de responsabilidades clara
> > - Motores desacoplados (RaceBonus, PointBuy, Multiclass)
> > - Preparação para GAS (dados em Components, fácil migração)
>
> **4. Data-Driven - ✅ Implementado Corretamente**
> >
> > - Todas as regras vêm de Data Tables/Assets
> > - Sem hardcode de valores
> > - Validação no editor
> > - Editor-Friendly completo
>
> **5. Normalização - ✅ Implementado Corretamente**
> >
> > - FDataTableRowHandle para referências type-safe
> > - Gameplay Tags para categorização flexível
> > - Soft References para lazy loading
> > - Estrutura relacional (sem duplicação)

</details>

---

## ⚠️ Melhorias Identificadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔍 Sistemas D&D 5e Documentados mas Não Implementados</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 1. Sistema de Spellcasting - NÃO IMPLEMENTADO</summary>
>
> > **Documentação:** `docs/design/dnd-rules/spellcasting.md`
> >
> > **Status:** 📋 Documentado mas não implementado
> >
> > **Prioridade:** 🔴 Alta - Base para Fase 5 (Features e Habilidades)
> >
> > **Sistemas Faltantes:**
> >
> > - ❌ **Spell Save DC:** `8 + ProficiencyBonus + SpellcastingAbilityModifier`
> > - ❌ **Spell Attack Modifier:** `ProficiencyBonus + SpellcastingAbilityModifier`
> > - ❌ **Spell Slots por nível:** Tabelas para Full Casters, Half Casters, Warlock
> > - ❌ **Cantrips Known:** Por nível e classe
> > - ❌ **Spells Known vs Spells Prepared:** Sistema de preparação
> > - ❌ **Spell Slot Recovery:** Long Rest, Short Rest, Arcane Recovery
> > - ❌ **Multiclassing Spell Slots:** Caster Level calculation
> >
> > **Solução Proposta:**
> >
> > - ✅ Criar `SpellcastingHelpers` em `Utils/` com funções puras
> > - ✅ Seguir TDD obrigatório (testes ANTES da implementação)
> > - ✅ Integrar com CharacterSheetDataAsset
> > - ✅ **Integrado no roadmap:** Fase 1.5.1
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 2. Sistema de ASI (Ability Score Improvements) - PARCIAL</summary>
>
> > **Documentação:** `docs/design/dnd-rules/ability-scores.md`
> >
> > **Status:** ⚠️ Parcial - Documentado mas sem sistema completo
> >
> > **Prioridade:** 🔴 Alta - Essencial para progressão de personagem
> >
> > **Sistemas Faltantes:**
> >
> > - ❌ **Níveis de ASI:** 4, 8, 12, 16, 19 (Fighter/Rogue extras: 6, 10, 14)
> > - ❌ **Opções de ASI:** +2 em um atributo OU +1 em dois atributos
> > - ❌ **Máximo:** 20 (exceto com itens mágicos)
> > - ❌ **Sistema de seleção:** Interface para escolher ASI
> >
> > **Solução Proposta:**
> >
> > - ✅ Criar `ASIHelpers` em `Utils/` com funções puras
> > - ✅ Seguir TDD obrigatório (testes ANTES da implementação)
> > - ✅ Integrar com CharacterSheetDataAsset
> > - ✅ **Integrado no roadmap:** Fase 1.5.2
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 3. Level Up System Completo - PARCIAL</summary>
>
> > **Documentação:** `docs/design/dnd-rules/level-up.md`
> >
> > **Status:** ⚠️ Parcial - Features desbloqueadas, mas sem processo de level up
> >
> > **Prioridade:** 🟡 Média - Importante mas não bloqueante
> >
> > **Sistemas Faltantes:**
> >
> > - ❌ **Processo de level up:** Fluxo completo de ganhar nível
> > - ❌ **Escolhas durante level up:** ASI, Feat, Features
> > - ❌ **Validação de pré-requisitos:** Para level up
> >
> > **Solução Proposta:**
> >
> > - ✅ Criar `LevelUpMotor` em `CreateSheet/LevelUp/`
> > - ✅ Seguir TDD obrigatório (testes ANTES da implementação)
> > - ✅ Integrar com CharacterSheetDataAsset
> > - ✅ **Integrado no roadmap:** Fase 1.5.3
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 4. Correção de Testes Proficiency Bonus - BUG</summary>
>
> > **Problema:** Testes esperam valores incorretos (base 1 ao invés de base 2)
> >
> > **Status:** ⚠️ Bug nos testes (código está correto)
> >
> > **Prioridade:** 🟡 Média - Correção de testes existentes
> >
> > **Detalhes:**
> >
> > - Código correto: `PROFICIENCY_BONUS_BASE (2) + floor((TotalLevel - MIN_LEVEL) / PROFICIENCY_BONUS_DIVISOR)`
> > - Testes esperam: Base 1 (incorreto)
> > - **Solução:** Corrigir valores esperados nos testes
> > - ✅ **Integrado no roadmap:** Fase 1.5.4
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 5. Multiclassing Spell Slots - INTEGRADO</summary>
>
> > **Documentação:** `docs/design/dnd-rules/multiclassing.md` e `spellcasting.md`
> >
> > **Status:** 📋 Planejado (integrado em Spellcasting)
> >
> > **Prioridade:** 🟢 Baixa - Já coberto em SpellcastingHelpers
> >
> > **Nota:** `CalculateMulticlassCasterLevel()` já está incluído em Fase 1.5.1 (Spellcasting)
> >
> > - ✅ **Integrado no roadmap:** Fase 1.5.5 (mencionado como integrado)

</details>

</details>

---

## 📋 Integração no Roadmap

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Nova Fase 1.5 Criada</b></summary>

> **Fase 1.5: Melhorias e Completude D&D 5e**
>
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
> **Sub-fases:**
>
> - **1.5.1:** Sistema de Spellcasting (1-2 semanas) - 🔴 Alta
> - **1.5.2:** Sistema de ASI (1 semana) - 🔴 Alta
> - **1.5.3:** Level Up System Completo (1 semana) - 🟡 Média
> - **1.5.4:** Correção de Testes Proficiency Bonus (2-4 horas) - 🟡 Média
> - **1.5.5:** Multiclassing Spell Slots (integrado em 1.5.1) - 🟢 Baixa
>
> **📖 Detalhes completos:** [roadmap.md](roadmap.md#fase-15-melhorias-e-completude-dd-5e)

</details>

---

## 🎯 Conclusão

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Resumo da Revisão</b></summary>

> **Estrutura Atual:**
>
> - ✅ **Alinhada com planos5.md:** Padrão "ID + Tags + Payload", Data-Oriented Design, Component-Based Architecture
> - ✅ **Data-Driven:** Todas as regras vêm de Data Tables/Assets
> - ✅ **Normalização:** FDataTableRowHandle, Gameplay Tags, Soft References
> - ✅ **Testes:** 275+ testes automatizados implementados
>
> **Melhorias Necessárias:**
>
> - 🔴 **Alta Prioridade:** Spellcasting e ASI (essenciais para D&D 5e)
> - 🟡 **Média Prioridade:** Level Up System completo e correção de testes
> - 🟢 **Baixa Prioridade:** Multiclassing Spell Slots (já integrado)
>
> **Ação Tomada:**
>
> - ✅ **Nova Fase 1.5 criada** no roadmap com todas as melhorias
> - ✅ **TDD obrigatório** para todas as funções helper/motor
> - ✅ **Tarefas bem divididas** seguindo padrões do projeto
> - ✅ **Integração completa** com roadmap existente
>
> **Próximos Passos:**
>
> 1. Finalizar Fase 1 (Sistema de Fichas - 80%)
> 2. Iniciar Fase 1.5 (Melhorias D&D 5e)
> 3. Preparar Fase 2 (Combate Básico com GAS)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Roadmap Principal](roadmap.md)** - Roadmap completo com Fase 1.5 integrada
> - **[Regras D&D 5e](../design/dnd-rules/)** - Documentação das regras
>   - **[Spellcasting](../design/dnd-rules/spellcasting.md)** - Regras de spellcasting
>   - **[Ability Scores](../design/dnd-rules/ability-scores.md)** - Regras de ASI
>   - **[Level Up](../design/dnd-rules/level-up.md)** - Sistema de level up
>   - **[Multiclassing](../design/dnd-rules/multiclassing.md)** - Regras de multiclassing
> - **[planos5.md](../../memorias/planos5.md)** - Princípios de arquitetura
> - **[Arquitetura Técnica](../technical/architecture.md)** - Decisões técnicas
> - **[Database Architecture](../technical/data-architecture/database-architecture.md)** - Arquitetura de dados

</details>

---

**Última atualização:** 2024-12-XX
**Versão:** 1.0 - Revisão Estrutural Completa
