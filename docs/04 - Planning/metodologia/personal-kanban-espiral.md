# Metodologia de Desenvolvimento: Personal Kanban + Espiral

**Metodologia:** Personal Kanban + Desenvolvimento em Espiral
**Data:** 2024-12-27
**Baseado em:** [Roadmap](../roadmap/Roadmap.md) e [Metodologia Ágil](../../Referencias%20Tecnicas/MetodologiaAgil.md)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este plano integra **Personal Kanban** (visualização de fluxo) com **Desenvolvimento em Espiral** (ciclos incrementais) aplicado ao roadmap de 211 itens em 3 fases. Cada ciclo espiral valida a arquitetura antes de expandir, garantindo que problemas sejam descobertos cedo e motivação seja mantida através de micro-milestones constantes.

</details>

---

## 🎯 Princípios Fundamentais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>1. Personal Kanban - Visualização do Fluxo</b></summary>

> **Colunas do Kanban:**
>
> - **Backlog:** Todas as tarefas identificadas (sem limite)
> - **Ready:** Tarefas quebradas em micro-tarefas (10-15 itens)
> - **Doing:** Foco absoluto do momento (1-2 tarefas máximo)
> - **Done:** Tarefas concluídas (arquivo histórico)
>
> **Regra de Ouro:** Máximo 1-2 tarefas em "Doing" para evitar context switching.
>
> **Micro-Milestones:** Cada tarefa deve ser completável em 2-4 horas.

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>2. Desenvolvimento em Espiral - Ciclos Incrementais</b></summary>

> **Conceito:** Em vez de fazer tudo de uma vez, criar MVPs funcionais e expandir incrementalmente.
>
> **Estrutura de Ciclo:**
>
> 1. **MVP Mínimo:** Funcionalidade básica que valida arquitetura
> 2. **Teste e Validação:** Verificar que funciona e arquitetura suporta expansão
> 3. **Expansão Incremental:** Adicionar complexidade gradualmente
> 4. **Próximo Ciclo:** Repetir até completar a fase
>
> **Benefícios:**
>
> - Problemas arquiteturais descobertos cedo
> - Motivação constante (algo sempre funciona)
> - Flexibilidade para ajustar direção
> - Menos risco de refatoração massiva

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>3. Micro-Tarefas - Unidades Atômicas</b></summary>

> **Definição:** Tarefas que podem ser completadas em uma sessão de 2-4 horas.
>
> **Exemplos:**
>
> ❌ **Errado (Macro):** "Implementar sistema de combate completo"
>
> ✅ **Correto (Micro):** "Criar estrutura de dados para cálculo de AC básico (10 + DEX)"
>
> ✅ **Correto (Micro):** "Implementar função CalculateAC() com testes unitários"
>
> ✅ **Correto (Micro):** "Adicionar suporte para armaduras leves no cálculo de AC"
>
> **Benefícios:**
>
> - Progresso visível constante
> - Erros de arquitetura expostos cedo
> - Facilita rastreamento de progresso
> - Mantém motivação alta

</details>

---

## 📊 Sistema de Personal Kanban

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Estrutura de Colunas</b></summary>

> ### Backlog (Sem Limite)
>
> Todas as tarefas identificadas do roadmap, organizadas por fase e ciclo.
>
> **Exemplo:**
>
> - Fase 1 - Ciclo 1: Setup projeto Unreal
> - Fase 1 - Ciclo 1: Configurar compilação
> - Fase 1 - Ciclo 2: Criar RaceDataTable
> - ... (todas as 211 tarefas do roadmap)
>
> ### Ready (10-15 Itens)
>
> Tarefas quebradas em micro-tarefas (2-4 horas cada), prontas para execução.
>
> **Critérios para estar em Ready:**
>
> - [ ] Tarefa está quebrada em unidades atômicas
> - [ ] Dependências identificadas e resolvidas
> - [ ] Critérios de sucesso definidos
> - [ ] Estimativa de tempo (2-4 horas)
>
> **Exemplo:**
>
> - [ ] Criar estrutura de pastas Source/MyProject2/ (2h)
> - [ ] Configurar .Build.cs com dependências básicas (2h)
> - [ ] Testar compilação e verificar que roda (1h)
>
> ### Doing (1-2 Itens Máximo)
>
> Foco absoluto do momento. **Regra de Ouro:** Nunca mais de 2 tarefas simultâneas.
>
> **Exemplo:**
>
> - [ ] Criar estrutura de pastas Source/MyProject2/ (2h) ← **FAZENDO AGORA**
> - [ ] Configurar .Build.cs com dependências básicas (2h) ← **PRÓXIMA**
>
> ### Done (Arquivo Histórico)
>
> Tarefas concluídas, organizadas por ciclo e data.
>
> **Exemplo:**
>
> - [x] Setup projeto Unreal Engine 5.7 (2024-12-27) ✅
> - [x] Sistema de logging básico (2024-12-27) ✅

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Fluxo de Trabalho Diário</b></summary>

> ### Início do Dia
>
> 1. **Revisar Done:** Ver o que foi concluído ontem
> 2. **Mover de Ready para Doing:** Pegar 1-2 tarefas prontas
> 3. **Focar:** Trabalhar apenas nas tarefas em Doing
>
> ### Durante o Trabalho
>
> 1. **Foco Total:** Apenas 1-2 tarefas ativas
> 2. **Micro-Milestones:** Completar tarefas em 2-4 horas
> 3. **Validação:** Testar após cada tarefa concluída
> 4. **Mover para Done:** Quando tarefa está completa e testada
>
> ### Fim do Dia
>
> 1. **Mover para Done:** Tarefas concluídas
> 2. **Reabastecer Ready:** Quebrar próximas tarefas do Backlog
> 3. **Planejar Amanhã:** Definir 1-2 tarefas para Doing
>
> ### Fim do Ciclo
>
> 1. **Validar Ciclo:** Critério de sucesso foi atingido?
> 2. **Documentar Aprendizados:** O que funcionou? O que não funcionou?
> 3. **Ajustar Próximo Ciclo:** Baseado em aprendizados
> 4. **Iniciar Próximo Ciclo:** MVP → Teste → Expansão

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Progressão do Ciclo 1</b></summary>

> ### Dia 1 - Manhã
>
> **Doing:**
>
> - [ ] Criar projeto Unreal Engine 5.7 (2h) ← **FAZENDO**
>
> **Ação:** Criar projeto, configurar estrutura básica.
>
> **Resultado:** Projeto criado e compilando.
>
> **Mover para Done:**
>
> - [x] Criar projeto Unreal Engine 5.7 (2h) ✅
>
> **Mover de Ready para Doing:**
>
> - [ ] Configurar estrutura de pastas Source/MyProject2/ (2h) ← **PRÓXIMA**
>
> ### Dia 1 - Tarde
>
> **Doing:**
>
> - [ ] Configurar estrutura de pastas Source/MyProject2/ (2h) ← **FAZENDO**
>
> **Ação:** Criar pastas, organizar estrutura.
>
> **Resultado:** Estrutura de pastas criada.
>
> **Mover para Done:**
>
> - [x] Configurar estrutura de pastas Source/MyProject2/ (2h) ✅
>
> **Mover de Ready para Doing:**
>
> - [ ] Configurar .Build.cs com dependências básicas (2h) ← **PRÓXIMA**
>
> ### Dia 2 - Manhã
>
> **Doing:**
>
> - [ ] Configurar .Build.cs com dependências básicas (2h) ← **FAZENDO**
> - [ ] Testar compilação e verificar que roda (1h) ← **PRÓXIMA** (pode fazer junto)
>
> **Ação:** Configurar build, testar compilação.
>
> **Resultado:** Projeto compila e roda.
>
> **Mover para Done:**
>
> - [x] Configurar .Build.cs com dependências básicas (2h) ✅
> - [x] Testar compilação e verificar que roda (1h) ✅
>
> **Validação do Ciclo 1:**
>
> ✅ Projeto compila e roda sem erros → **Ciclo 1 completo!**
>
> **Próximo Ciclo:** Ciclo 2 - MVP Data Tables

</details>

---

## 🎯 Critérios de Sucesso por Ciclo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Checklist de Validação</b></summary>

> Para cada ciclo, verificar:
>
> - [ ] **Funcionalidade:** O MVP funciona como esperado?
> - [ ] **Arquitetura:** A arquitetura suporta expansão?
> - [ ] **Testes:** Testes unitários passam (quando aplicável)?
> - [ ] **Integração:** Integra com sistemas existentes (quando aplicável)?
> - [ ] **Documentação:** Código está documentado (quando necessário)?
>
> **Se TODOS os critérios passam:** → Próximo ciclo
>
> **Se ALGUM critério falha:** → Corrigir antes de avançar

</details>

---

## 📈 Acompanhamento de Progresso

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Métricas Simples</b></summary>

> ### Por Ciclo
>
> - **Tarefas Concluídas:** X de Y micro-tarefas
> - **Tempo Estimado:** X horas
> - **Tempo Real:** Y horas
> - **Critério de Sucesso:** ✅ Passou / ❌ Falhou
>
> ### Por Fase
>
> - **Ciclos Completos:** X de Y ciclos
> - **Tarefas Concluídas:** X de Y tarefas
> - **Status Geral:** 🔄 Em Progresso / ✅ Completo
>
> ### Geral
>
> - **Fases Completas:** X de 3 fases
> - **Tarefas Concluídas:** X de 211 tarefas
> - **Progresso:** X% completo

</details>

---

## 🚨 Regras Críticas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚠️ Nunca Violar</b></summary>

> 1. **WIP Limit:** Nunca mais de 2 tarefas em Doing simultaneamente
> 2. **Micro-Tarefas:** Nunca tarefas maiores que 4 horas (quebrar se necessário)
> 3. **Validação:** Nunca avançar para próximo ciclo sem validar o atual
> 4. **Arquitetura:** Nunca ignorar problemas arquiteturais (corrigir cedo)
> 5. **Testes:** Nunca pular testes quando aplicável (TDD para código crítico)

</details>

---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - [Roadmap do Projeto](../roadmap/Roadmap.md) - 211 itens em 3 fases
> - [Metodologia Ágil](../../Referencias%20Tecnicas/MetodologiaAgil.md) - Personal Kanban e Desenvolvimento em Espiral
> - [Arquitetura do Projeto](../../02%20-%20TDD/01-arquitetura/index.md) - Estrutura técnica

</details>

---

**Última atualização:** 2024-12-27
