# Plano de Desenvolvimento Completo - MyProject2

**Metodologia:** Personal Kanban + Desenvolvimento em Espiral  
**Data:** 2024-12-27  
**Baseado em:** [Roadmap](../../04%20-%20Planning/roadmap/Roadmap.md) e [Metodologia Ágil](../../Referencias%20Tecnicas/MetodologiaAgil.md)

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

---

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

---

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

## 🔄 Estrutura de Ciclos Espirais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 FASE 1: COMEÇO (Fundação e Vertical Slice)</b></summary>

> **Objetivo:** Validar arquitetura e criar vertical slice jogável.
>
> **Total de Itens:** 48 | **Status:** 🔄 Em Progresso
>
> ### Ciclo 1: MVP Fundação Técnica
>
> **Objetivo:** Provar que projeto compila e roda.
>
> **Micro-Tarefas (Doing - 1-2 por vez):**
>
> - [ ] Setup projeto Unreal Engine 5.7 (estrutura de pastas básica)
> - [ ] Configurar compilação e verificar que roda (mesmo que vazio)
> - [ ] Criar estrutura de pastas base (Source/, Content/, Config/)
> - [ ] Sistema de logging básico (UE_LOG funcionando)
>
> **Critério de Sucesso:** Projeto compila e roda sem erros.
>
> **Validação:** Arquitetura básica está correta? → Se SIM, próximo ciclo.
>
> ### Ciclo 2: MVP Data Tables
>
> **Objetivo:** Validar que sistema de dados funciona.
>
> **Micro-Tarefas:**
>
> - [ ] Criar estrutura base de Data Table (RaceDataTable vazia)
> - [ ] Criar struct FRaceDataRow básica (apenas Name)
> - [ ] Implementar carregamento de Data Table no componente
> - [ ] Testar carregamento de 1 raça (Humano) e validar dados
>
> **Critério de Sucesso:** É possível carregar dados de uma Data Table.
>
> **Validação:** Sistema de dados funciona? → Se SIM, próximo ciclo.
>
> ### Ciclo 3: MVP Criação de Personagem
>
> **Objetivo:** Validar que criação de personagem funciona.
>
> **Micro-Tarefas:**
>
> - [ ] Criar personagem básico (apenas nome e raça)
> - [ ] Salvar personagem em arquivo (serialização básica)
> - [ ] Carregar personagem de arquivo (deserialização básica)
> - [ ] Validar que dados persistem corretamente
>
> **Critério de Sucesso:** É possível criar, salvar e carregar um personagem básico.
>
> **Validação:** Sistema de personagem funciona? → Se SIM, próximo ciclo.
>
> ### Ciclo 4: MVP Vertical Slice
>
> **Objetivo:** Validar que todos os sistemas funcionam juntos.
>
> **Micro-Tarefas:**
>
> - [ ] Criar uma sala básica da dungeon (Cragmaw Hideout - entrada)
> - [ ] Spawnar um goblin básico (sem IA, apenas modelo)
> - [ ] Implementar combate mínimo (ataque, dano, morte)
> - [ ] Adicionar um item coletável (moeda ou poção)
> - [ ] Testar fluxo completo: entrar → combater → coletar → salvar
>
> **Critério de Sucesso:** É possível jogar do início ao fim (mesmo que simples).
>
> **Validação:** Vertical slice funciona? → Se SIM, próximo ciclo.
>
> ### Ciclo 5: Expandir Vertical Slice
>
> **Objetivo:** Adicionar complexidade incremental.
>
> **Micro-Tarefas:**
>
> - [ ] Adicionar mais raças (Elfo, Anão) à Data Table
> - [ ] Implementar cálculo de atributos básico (sem modificadores complexos)
> - [ ] Adicionar IA básica para goblins (patrulha simples)
> - [ ] Expandir dungeon (mais 2-3 salas)
> - [ ] Adicionar sistema de HP completo (cura, morte, UI básica)
>
> **Critério de Sucesso:** Vertical slice mais completa e jogável.
>
> **Validação:** Arquitetura suporta expansão? → Se SIM, Fase 1 completa!

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 FASE 2: MEIO (Sistemas Completos)</b></summary>

> **Objetivo:** Expandir sistemas para completude, mantendo arquitetura validada.
>
> **Total de Itens:** 96 | **Status:** ⏳ Pendente
>
> ### Ciclo 6: MVP Combate
>
> **Objetivo:** Sistema de combate básico funcional.
>
> **Micro-Tarefas:**
>
> - [ ] Implementar cálculo de AC completo (armaduras, escudos, DEX)
> - [ ] Sistema de rolagem de dados (d20 para acerto, dano por tipo)
> - [ ] Tipos de dano básicos (Físico, Fogo, Gelo)
> - [ ] Sistema de HP e morte
> - [ ] Testes unitários para cálculos de combate
>
> **Critério de Sucesso:** Combate funciona com múltiplos tipos de ataque.
>
> ### Ciclo 7: Expandir Combate
>
> **Micro-Tarefas:**
>
> - [ ] Sistema de condições (veneno, queimadura, sangramento)
> - [ ] Combate tático (cobertura, terreno, altura)
> - [ ] Mais tipos de armas (espada, arco, cajado)
> - [ ] Sistema de crítico e fumble
>
> **Critério de Sucesso:** Combate completo e balanceado.
>
> ### Ciclo 8: MVP Spellcasting
>
> **Objetivo:** Sistema de magias básico funcional.
>
> **Micro-Tarefas:**
>
> - [ ] Estrutura de dados para magias (SpellDataTable)
> - [ ] Sistema de slots de magia (nível 1-9)
> - [ ] 3 magias básicas (Mísseis Mágicos, Cura, Bola de Fogo)
> - [ ] Efeitos visuais básicos (partículas simples)
> - [ ] Testes unitários para sistema de magias
>
> **Critério de Sucesso:** É possível conjurar magias e ver efeitos.
>
> ### Ciclo 9: Expandir Spellcasting
>
> **Micro-Tarefas:**
>
> - [ ] Adicionar mais magias (10-15 magias)
> - [ ] Escolas de magia (Evocação, Abjuração, etc.)
> - [ ] Sistema de componentes de magia (V, S, M)
> - [ ] Magias de área e alvos múltiplos
> - [ ] Integração com sistema de combate
>
> **Critério de Sucesso:** Sistema de magias completo e integrado.
>
> ### Ciclo 10-14: Outros Sistemas
>
> Seguir mesmo padrão para:
>
> - Sistema de Equipamentos e Inventário
> - Sistema de Rest e Recuperação
> - Sistema de Diálogos e Quests
> - Sistema de IA e Comportamento
> - Sistema de Economia e Loot
> - Sistema de Progressão e XP
>
> **Padrão:** MVP mínimo → Teste → Expansão incremental → Próximo sistema.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 FASE 3: FIM (Conteúdo e Polimento)</b></summary>

> **Objetivo:** Criar conteúdo completo e polir experiência.
>
> **Total de Itens:** 67 | **Status:** ⏳ Pendente
>
> ### Ciclo 15-18: Conteúdo da Campanha
>
> **Padrão por Capítulo:**
>
> - **Ciclo MVP:** Criar estrutura básica do capítulo (1-2 quests principais)
> - **Ciclo Expansão:** Adicionar quests secundárias, NPCs, diálogos
> - **Ciclo Polimento:** Balanceamento, testes, ajustes
>
> **Micro-Tarefas (exemplo Capítulo 1):**
>
> - [ ] Criar mapa básico de Phandalin
> - [ ] Implementar 3 NPCs principais com diálogos básicos
> - [ ] Quest principal: "Encontrar Gundren" (estrutura básica)
> - [ ] Adicionar quests secundárias (2-3)
> - [ ] Testar fluxo narrativo completo
>
> ### Ciclo 19: UI/UX Completo
>
> **Micro-Tarefas:**
>
> - [ ] HUD básico (HP, Mana, XP)
> - [ ] Menu de inventário funcional
> - [ ] Menu de personagem (atributos, equipamentos)
> - [ ] Menu de diálogo melhorado
> - [ ] Menu principal (New Game, Load, Settings)
>
> ### Ciclo 20: Áudio Completo
>
> **Micro-Tarefas:**
>
> - [ ] Música ambiente por área
> - [ ] Efeitos sonoros de combate
> - [ ] Vozes de NPCs (ou placeholder)
> - [ ] Sistema de áudio espacial
> - [ ] Mixer de áudio e volumes
>
> ### Ciclo 21: Polimento e Balanceamento
>
> **Micro-Tarefas:**
>
> - [ ] Balanceamento de combate (dano, HP, AC)
> - [ ] Balanceamento de economia (preços, loot)
> - [ ] Otimização de performance
> - [ ] Correção de bugs críticos
> - [ ] Testes de gameplay completos
>
> ### Ciclo 22: Finalização
>
> **Micro-Tarefas:**
>
> - [ ] Build final de produção
> - [ ] Testes finais completos
> - [ ] Documentação final
> - [ ] Preparação para release

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

---

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

---

## 📋 Exemplo Prático: Ciclo 1 - MVP Fundação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Estado Inicial do Kanban</b></summary>

> ### Backlog
>
> - Fase 1 - Ciclo 1: Setup projeto Unreal Engine 5.7
> - Fase 1 - Ciclo 1: Configurar compilação
> - Fase 1 - Ciclo 1: Criar estrutura de pastas
> - Fase 1 - Ciclo 1: Sistema de logging básico
> - ... (outras tarefas do roadmap)
>
> ### Ready (10-15 itens)
>
> - [ ] Criar projeto Unreal Engine 5.7 (2h)
> - [ ] Configurar estrutura de pastas Source/MyProject2/ (2h)
> - [ ] Configurar .Build.cs com dependências básicas (2h)
> - [ ] Testar compilação e verificar que roda (1h)
> - [ ] Criar sistema de logging básico (UE_LOG) (2h)
> - ... (mais 5-10 tarefas prontas)
>
> ### Doing (1-2 itens)
>
> - [ ] Criar projeto Unreal Engine 5.7 (2h) ← **FAZENDO AGORA**
>
> ### Done
>
> (vazio no início)

</details>

---

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

> - [Roadmap do Projeto](../../04%20-%20Planning/roadmap/Roadmap.md) - 211 itens em 3 fases
> - [Metodologia Ágil](../../Referencias%20Tecnicas/MetodologiaAgil.md) - Personal Kanban e Desenvolvimento em Espiral
> - [Arquitetura do Projeto](../../02%20-%20TDD/01-arquitetura/index.md) - Estrutura técnica

</details>

---

**Última atualização:** 2024-12-27

