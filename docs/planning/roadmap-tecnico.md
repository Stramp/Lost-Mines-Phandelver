---
title: "Roadmap Técnico - Bugs, Correções e Melhorias"
category: planning
tags: [roadmap, technical, bugs, improvements]
last_updated: 2024-12-27
---

**Navegação:** [Home](../../README.md) > [Documentação](../index.md) > [Planejamento](index.md) > Roadmap Técnico

# Roadmap Técnico - Bugs, Correções e Melhorias

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este roadmap detalha todas as **tarefas técnicas** do projeto: bugs conhecidos, correções necessárias e melhorias de código.
>
> **Organização:**
>
> - 🔴 **Alta Prioridade** - Bloqueia funcionalidades ou causa problemas críticos
> - 🟡 **Média Prioridade** - Importante mas não bloqueante
> - 🟢 **Baixa Prioridade** - Melhorias e polish
>
> **Metodologia:** 🧪 TDD obrigatório para todas as funções helper/motor

</details>

---

## 🔴 Alta Prioridade

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🐛 Bugs Críticos</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 TEC-001: Corrigir Testes de Proficiency Bonus</summary>
>
> > **User Story:** Como desenvolvedor, eu quero que os testes de Proficiency Bonus passem corretamente para validar que o sistema calcula valores corretos conforme D&D 5e.
> >
> > **Prioridade MoSCoW:** 🔴 **M - Must Have**
> >
> > **Status:** ⚠️ Pendente
> >
> > **Problema:**
> >
> > - Testes esperam valores incorretos (base 1 ao invés de base 2)
> > - Código está correto: `PROFICIENCY_BONUS_BASE (2) + floor((TotalLevel - MIN_LEVEL) / PROFICIENCY_BONUS_DIVISOR)`
> >
> > **Definition of Done:**
> >
> > - ✅ Todos os testes de Proficiency Bonus passam
> > - ✅ Valores esperados corrigidos para todos os níveis (1-20)
> > - ✅ Código não foi alterado (apenas testes)
> - ✅ Testes executados e validados
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-001-01:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 1 (esperado: 2, não 1) - **30 min**
> > 2. **TEC-001-02:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 5 (esperado: 3, não 2) - **30 min**
> > 3. **TEC-001-03:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 9 (esperado: 4, não 3) - **30 min**
> > 4. **TEC-001-04:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 13 (esperado: 5, não 4) - **30 min**
> > 5. **TEC-001-05:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 17 (esperado: 6, não 5) - **30 min**
> > 6. **TEC-001-06:** Corrigir valor esperado em `CalculationHelpersTests.cpp` para nível 20 (esperado: 6, não 5) - **30 min**
> > 7. **TEC-001-07:** Executar todos os testes e validar que passam - **15 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:** Nenhuma
> >
> > **Critério de Conclusão:** Todos os testes de Proficiency Bonus passam
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 TEC-002: Implementar HP Inicial (Step 6)</summary>
>
> > **User Story:** Como jogador, eu quero que meu personagem tenha HP inicial calculado corretamente no Step 6 para completar a criação de personagem.
> >
> > **Prioridade MoSCoW:** 🔴 **M - Must Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Problema:**
> >
> > - HP inicial não está sendo calculado no Step 6
> > - Teste E2E falha: `TestTrue("HP inicial deve estar implementado", false);`
> >
> > **Definition of Done:**
> >
> > - ✅ Função `CalculateInitialHP()` implementada com testes TDD
> > - ✅ Campo `InitialHP` adicionado em `CharacterDataComponent`
> > - ✅ Integrado no fluxo de criação de personagem
> > - ✅ Teste E2E passa validando HP inicial
> > - ✅ Suporta multiclasse (HP por classe)
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-002-01:** Adicionar campo `InitialHP` em `CharacterDataComponent.h` (calculado) - **15 min**
> > 2. **TEC-002-02:** Criar função `CalculateInitialHP()` em `CalculationHelpers.cpp` usando `CalculateMaxHP()` - **1 hora** 🧪 TDD
> > 3. **TEC-002-03:** Criar testes para `CalculateInitialHP()` (nível 1, multiclasse, edge cases) - **1 hora** 🧪 TDD
> > 4. **TEC-002-04:** Adicionar updater `UpdateInitialHP()` em `CharacterSheetDataAssetUpdaters.cpp` - **30 min**
> > 5. **TEC-002-05:** Integrar cálculo de HP inicial no `CharacterSheetComponent::InitializeFromDataAsset()` - **30 min**
> > 6. **TEC-002-06:** Atualizar teste E2E para validar HP inicial calculado corretamente - **30 min**
> >
> > **Estimativa Total:** 3.5 horas
> >
> > **Dependências:**
> > - ✅ `CalculateMaxHP()` já existe
> >
> > **Critério de Conclusão:** Teste E2E passa validando HP inicial
>
> </details>

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚠️ Validações Pendentes</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 TEC-003: Validação Completa do Sistema de Multiclasse</summary>
>
> > **Status:** ⚠️ Pendente
> >
> > **Prioridade:** 🔴 Alta - Sistema crítico precisa validação end-to-end
> >
> > **Problema:**
> >
> > - Falta testes end-to-end completos para multiclasse
> > - Validação de integridade de dados não cobre todos os casos
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-003-01:** Criar teste E2E para multiclasse simples (2 classes, nível 1 cada) - **1 hora** 🧪 TDD
> > 2. **TEC-003-02:** Criar teste E2E para multiclasse complexa (3 classes, níveis variados) - **1 hora** 🧪 TDD
> > 3. **TEC-003-03:** Criar teste para validação de requisitos de multiclasse (requisitos não atendidos) - **1 hora** 🧪 TDD
> > 4. **TEC-003-04:** Adicionar validação de integridade de dados em `CharacterDataComponent::ValidateDataIntegrity()` para multiclasse - **1 hora**
> > 5. **TEC-003-05:** Executar todos os testes de multiclasse e validar cobertura - **30 min**
> >
> > **Estimativa Total:** 4.5 horas
> >
> > **Dependências:**
> > - ✅ Sistema de multiclasse já implementado
> >
> > **Critério de Conclusão:** Todos os testes de multiclasse passam e cobertura > 80%
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔴 TEC-004: Validar Criação de Feat no Editor</summary>
>
> > **User Story:** Como designer, eu quero criar feats no editor e ter validação de pré-requisitos para garantir que feats são configurados corretamente.
> >
> > **Prioridade MoSCoW:** 🟡 **S - Should Have**
> >
> > **Status:** ⚠️ Pendente
> >
> > **Problema:**
> >
> > - Não está claro se criação de feat no editor funciona corretamente
> > - Falta validação de pré-requisitos no editor
> >
> > **Definition of Done:**
> >
> > - ✅ Criação de feat no editor testada e documentada
> > - ✅ Validação de pré-requisitos funciona no editor
> > - ✅ Teste automatizado para criação de feat via Data Asset
> > - ✅ Processo documentado (se necessário)
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-004-01:** Testar criação de feat no editor manualmente e documentar processo - **1 hora**
> > 2. **TEC-004-02:** Verificar se validação de pré-requisitos funciona no editor - **30 min**
> > 3. **TEC-004-03:** Criar teste automatizado para criação de feat via Data Asset - **1 hora** 🧪 TDD
> > 4. **TEC-004-04:** Documentar processo de criação de feat no editor (se necessário) - **30 min**
> >
> > **Estimativa Total:** 3 horas
> >
> > **Dependências:**
> > - ✅ Sistema de feats já implementado
> >
> > **Critério de Conclusão:** Criação de feat no editor validada e documentada
>
> </details>

</details>

---

## 🟡 Média Prioridade

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Melhorias de Código</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟡 TEC-005: Refatorar Orquestradores para Handlers</summary>
>
> > **Status:** 📋 Planejado
> >
> > **Prioridade:** 🟡 Média - Melhoria de arquitetura (Fase 3)
> >
> > **Descrição:**
> >
> > - Orquestradores atuais podem ser refatorados para handlers mais específicos
> > - Melhorar separação de responsabilidades
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-005-01:** Analisar orquestradores atuais e identificar oportunidades de refatoração - **2 horas**
> > 2. **TEC-005-02:** Criar plano de refatoração detalhado - **1 hora**
> > 3. **TEC-005-03:** Implementar refatoração (quando priorizado) - **8 horas**
> >
> > **Estimativa Total:** 11 horas (quando priorizado)
> >
> > **Dependências:**
> > - ✅ Fase 1 completa
> >
> > **Critério de Conclusão:** Orquestradores refatorados e testes passando
>
> </details>

</details>

---

## 🟢 Baixa Prioridade

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Melhorias e Polish</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🟢 TEC-006: Melhorar Logging e Debugging</summary>
>
> > **User Story:** Como desenvolvedor, eu quero ter logs mais informativos e mensagens de erro mais descritivas para facilitar debugging e manutenção.
> >
> > **Prioridade MoSCoW:** 🟢 **C - Could Have**
> >
> > **Status:** 📋 Planejado
> >
> > **Descrição:**
> >
> > - Adicionar mais logs informativos
> > - Melhorar mensagens de erro
> >
> > **Definition of Done:**
> >
> > - ✅ Sistema de logging revisado
> > - ✅ Logs informativos adicionados em pontos críticos
> > - ✅ Mensagens de erro melhoradas e mais descritivas
> > - ✅ Documentação de logging atualizada (se necessário)
> >
> > **Tarefas Puras:**
> >
> > 1. **TEC-006-01:** Revisar sistema de logging atual - **1 hora**
> > 2. **TEC-006-02:** Adicionar logs informativos em pontos críticos - **2 horas**
> > 3. **TEC-006-03:** Melhorar mensagens de erro para serem mais descritivas - **2 horas**
> >
> > **Estimativa Total:** 5 horas
> >
> > **Dependências:** Nenhuma
> >
> > **Critério de Conclusão:** Logs mais informativos e mensagens de erro melhoradas
>
> </details>

</details>

---

## 📊 Resumo de Prioridades

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Estatísticas</b></summary>

> **Alta Prioridade:**
>
> - 4 tarefas principais
> - ~14 horas de trabalho estimado
> - Bloqueiam funcionalidades críticas
>
> **Média Prioridade:**
>
> - 1 tarefa principal
> - ~11 horas de trabalho estimado (quando priorizado)
> - Melhorias de arquitetura
>
> **Baixa Prioridade:**
>
> - 1 tarefa principal
> - ~5 horas de trabalho estimado
> - Melhorias e polish
>
> **Total Estimado:** ~30 horas de trabalho técnico

</details>

---

## 🔗 Links Relacionados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Referências</b></summary>

> - **[Roadmap Principal](roadmap.md)** - Visão estratégica
> > - **[Roadmap Funcional](roadmap-funcional.md)** - Features por categoria
> > - **[Roadmap de Testes](roadmap-testes.md)** - Testes e validações
> > - **[Estrutura de Roadmaps](roadmap-estrutura.md)** - Documentação da estrutura hierárquica

</details>

---

**Última atualização:** 2024-12-27
**Versão:** 1.0
