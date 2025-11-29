# Guia de GDD Orgânico: Questionário de Fundação e Implementação Passo a Passo

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Com base na análise do relatório anterior e nas melhores práticas da indústria para documentos vivos ("organic GDDs"), este guia fornece um questionário de fundação e um guia de implementação passo a passo. O objetivo é evitar a "paralisia por análise" e garantir que o documento cresça junto com o jogo.

</details>

---

## Parte 1: O Questionário de Fundação (The Pre-GDD Probe)

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Introdução ao Questionário</b></summary>

> Antes de escrever uma única linha de documentação técnica, você deve responder a estas perguntas. Elas servem para definir os limites do escopo e a alma do projeto. Se você não conseguir responder a alguma delas, é um sinal de que a ideia ainda precisa de amadurecimento no estágio de brainstorming.

</details>

---

### A. Identidade e Visão (High Concept)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>A.1. O "Elevator Pitch"</b></summary>

> **Pergunta:** Como você descreveria seu jogo em uma frase para um estranho no elevador?
>
> **Formato Sugerido:** "É como [Jogo A] misturado com [Jogo B] no cenário de [Contexto]"
>
> **Espaço para Resposta:**
>
> ```
>
>
>
>
> ```
>
> **Dica:** Se você não conseguir formular isso em uma frase, a visão do jogo ainda não está clara o suficiente.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>A.2. Os 3 Pilares de Design</b></summary>

> **Pergunta:** Quais são os três sentimentos ou conceitos que devem estar presentes em cada momento do jogo?
>
> **Exemplo:** Tensão, Solidão, Descoberta
>
> **Regra de Corte:** Se uma nova mecânica não apoiar um desses pilares, ela deve ser cortada.
>
> **Espaço para Resposta:**
>
> **Pilar 1:**
> ```
>
>
> ```
>
> **Pilar 2:**
> ```
>
>
> ```
>
> **Pilar 3:**
> ```
>
>
> ```
>
> **Justificativa (Por que estes pilares?):**
> ```
>
>
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>A.3. A Fantasia do Jogador</b></summary>

> **Pergunta:** Quem o jogador finge ser?
>
> **Exemplos:**
> - Um comandante espacial
> - Uma mãe ganso
> - Um detetive falido
> - Um guerreiro em busca de vingança
>
> **Espaço para Resposta:**
>
> ```
>
>
>
>
> ```
>
> **Dica:** Esta resposta deve guiar todas as decisões de design. Se o jogador é um "comandante espacial", as mecânicas devem reforçar essa fantasia.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>A.4. Público e Plataforma</b></summary>

> **Pergunta:** Quem vai comprar isso? É um jogo mobile para sessões de 5 minutos ou um RPG de PC para sessões de 4 horas?
>
> **Considerações:**
> - Isso define a interface e o sistema de salvamento
> - Define o modelo de monetização (se aplicável)
> - Define as limitações técnicas
>
> **Espaço para Resposta:**
>
> **Público-Alvo:**
> ```
>
>
> ```
>
> **Plataforma(s):**
> ```
>
>
> ```
>
> **Duração de Sessão Esperada:**
> ```
>
>
> ```
>
> **Implicações para Design:**
> ```
>
>
>
>
> ```

</details>

---

### B. Mecânica e Loop (Gameplay)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>B.1. O Loop Segundo-a-Segundo</b></summary>

> **Pergunta:** O que o jogador faz com as mãos na maior parte do tempo?
>
> **Exemplos:**
> - Pular, atirar, clicar, arrastar
> - Navegar menus, gerenciar recursos
> - Explorar, coletar, combater
>
> **Espaço para Resposta:**
>
> ```
>
>
>
>
> ```
>
> **Ações Primárias (Top 3):**
> ```
> 1.
> 2.
> 3.
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>B.2. O Loop Minuto-a-Minuto</b></summary>

> **Pergunta:** Qual é o ciclo de recompensa curto?
>
> **Exemplo:** Matar monstro -> Ganhar XP -> Abrir Baú -> Encontrar Item -> Equipar -> Matar Monstro Mais Forte
>
> **Espaço para Resposta:**
>
> **Fluxo do Loop:**
> ```
> 1.
> 2.
> 3.
> 4.
> 5.
> ```
>
> **Tempo Médio do Loop:**
> ```
>
> ```
>
> **Ponto de Recompensa:**
> ```
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>B.3. Condição de Vitória/Derrota</b></summary>

> **Pergunta:** Como o jogo termina ou reinicia? Existe um "Game Over" ou apenas contratempos?
>
> **Considerações:**
> - Jogos roguelike: morte = reinício
> - Jogos narrativos: conclusão da história
> - Jogos sandbox: sem fim definido
>
> **Espaço para Resposta:**
>
> **Condição de Vitória:**
> ```
>
>
>
> ```
>
> **Condição de Derrota:**
> ```
>
>
>
> ```
>
> **Sistema de Progressão Permanente (se houver):**
> ```
>
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>B.4. A "Cola" do Sistema</b></summary>

> **Pergunta:** Como a narrativa se conecta com a mecânica? A história avança por fases, por tempo ou por exploração?
>
> **Exemplos:**
> - Por fases: Cada nível conta uma parte da história
> - Por tempo: Eventos narrativos ocorrem em momentos específicos
> - Por exploração: O jogador descobre a história ao explorar
>
> **Espaço para Resposta:**
>
> **Método de Progressão Narrativa:**
> ```
>
>
> ```
>
> **Como Mecânicas e Narrativa se Conectam:**
> ```
>
>
>
>
> ```
>
> **Exemplo Concreto:**
> ```
>
>
>
>
> ```

</details>

---

### C. Escopo Técnico e Artístico

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>C.1. Estilo Visual (Mínimo Viável)</b></summary>

> **Pergunta:** Se tivéssemos que lançar amanhã, qual seria o estilo visual mais simples aceitável?
>
> **Opções Comuns:**
> - Pixel Art
> - Low Poly
> - Vetorial
> - Estilizado 2D
> - Realista Simplificado
>
> **Espaço para Resposta:**
>
> **Estilo Visual Escolhido:**
> ```
>
> ```
>
> **Justificativa:**
> ```
>
>
>
> ```
>
> **Referências Visuais (links ou descrições):**
> ```
>
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>C.2. Tecnologia</b></summary>

> **Pergunta:** Unity, Unreal, Godot? 2D ou 3D? A equipe atual sabe usar essas ferramentas ou precisará aprender durante a produção?
>
> **Espaço para Resposta:**
>
> **Engine Escolhida:**
> ```
>
> ```
>
> **Dimensão (2D/3D):**
> ```
>
> ```
>
> **Nível de Conhecimento da Equipe:**
> ```
>
> ```
>
> **Tempo Estimado para Aprendizado (se necessário):**
> ```
>
> ```
>
> **Riscos Técnicos Identificados:**
> ```
>
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>C.3. Áudio</b></summary>

> **Pergunta:** A música é dinâmica (muda com o combate) ou estática? Quantos efeitos sonoros (SFX) são críticos para o feedback do jogador?
>
> **Espaço para Resposta:**
>
> **Sistema de Música:**
> ```
> [ ] Dinâmica (muda com contexto)
> [ ] Estática (uma trilha por área)
> [ ] Adaptativa (camadas de intensidade)
> ```
>
> **SFX Críticos (Lista):**
> ```
> 1.
> 2.
> 3.
> 4.
> 5.
> ```
>
> **Middleware de Áudio (se aplicável):**
> ```
>
> ```
>
> **Prioridades de Áudio:**
> ```
>
>
>
> ```

</details>

---

## Parte 2: Guia Passo a Passo para um GDD Orgânico

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Introdução ao Guia</b></summary>

> Um GDD orgânico não é um arquivo Word de 100 páginas; é uma base de dados conectada. Recomendamos fortemente o uso de ferramentas como Notion ou Confluence para esta estrutura, pois permitem linkar páginas como uma "Wiki" e criar bancos de dados relacionais.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Passo 1: Configuração da Ferramenta (A "Wiki" Central)</b></summary>

> Não comece com um documento em branco. Crie uma estrutura de pastas ou páginas iniciais no Notion/Confluence.
>
> **Estrutura Recomendada:**
>
> **1. Página Mestre (Dashboard):**
>
> - Contém o High Concept, Pilares e Links rápidos
> - Status do projeto
> - Métricas principais
>
> **Espaço para Configuração:**
>
> ```
> Link da Página Mestre:
>
>
> ```
>
> **2. Banco de Dados de Mecânicas:**
>
> - Uma lista de todas as mecânicas planejadas
> - Status: Conceito, Em Progresso, Implementado
> - Prioridade e Estimativa
>
> **Espaço para Configuração:**
>
> ```
> Link do Banco de Dados:
>
>
> ```
>
> **Colunas do Banco de Dados:**
> ```
> - Nome da Mecânica
> - Status: [ ] Conceito [ ] Em Progresso [ ] Implementado
> - Prioridade:
> - Estimativa:
> - Responsável:
> ```
>
> **3. Banco de Dados de Assets:**
>
> - Listas de Arte, Som e Scripts necessários
> - Status de produção
> - Dependências
>
> **Espaço para Configuração:**
>
> ```
> Link do Banco de Dados:
>
>
> ```
>
> **Colunas do Banco de Dados:**
> ```
> - Nome do Asset
> - Tipo: [ ] Arte [ ] Som [ ] Script
> - Status:
> - Prioridade:
> - Dependências:
> ```
>
> **4. Lore & Mundo:**
>
> - Onde a história vive separada da regra técnica
> - Personagens, locais, eventos
>
> **Espaço para Configuração:**
>
> ```
> Link da Seção:
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Passo 2: O "One-Pager" (A Primeira Semana)</b></summary>

> Antes de detalhar, crie a página de visão geral.
>
> **1. Resumo Executivo:**
>
> - Escreva o resumo baseado nas respostas da seção A do questionário acima
>
> **Espaço para Resumo Executivo:**
>
> ```
>
>
>
>
>
>
>
>
>
> ```
>
> **2. Diagrama de Fluxo (Flowchart) do Core Loop:**
>
> - Use ferramentas como Miro ou Whimsical
> - Incorpore a imagem na página
> - O visual elimina ambiguidades que o texto cria
>
> **Espaço para Link/Referência:**
>
> ```
> Link do Diagrama:
>
>
> ```
>
> **Descrição do Core Loop:**
> ```
>
>
>
>
> ```
>
> **3. USP (Unique Selling Point):**
>
> - O que seu jogo tem que nenhum outro tem?
>
> **Espaço para USP:**
>
> ```
>
>
>
>
> ```
>
> **Justificativa da USP:**
> ```
>
>
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Passo 3: Estruturação de Dados Relacionados (O "Segredo" Orgânico)</b></summary>

> Aqui é onde o GDD se torna "orgânico". Em vez de escrever "O Inimigo X dropa a Espada Y" em um texto corrido, use bancos de dados relacionais.
>
> **Exemplo Prático:**
>
> **1. Tabela "Itens":**
>
> - Colunas: Nome, Dano, Valor, Ícone, Tipo
>
> **Espaço para Configuração:**
>
> ```
> Link da Tabela:
>
>
> ```
>
> **Estrutura da Tabela:**
> ```
> - Nome:
> - Dano:
> - Valor:
> - Ícone:
> - Tipo:
> - Raridade:
> ```
>
> **2. Tabela "Inimigos":**
>
> - Colunas: Nome, HP, Comportamento, Loot
>
> **Espaço para Configuração:**
>
> ```
> Link da Tabela:
>
>
> ```
>
> **Estrutura da Tabela:**
> ```
> - Nome:
> - HP:
> - Comportamento:
> - Loot (Relação com Tabela Itens):
> - Probabilidade de Drop:
> ```
>
> **3. Propriedade de "Relação" (Relation):**
>
> - Conecte as duas tabelas
> - Se você mudar o dano da Espada Y na tabela de Itens, essa informação é atualizada automaticamente na página do Inimigo X que a utiliza
>
> **Benefícios:**
>
> - Evita informações contraditórias no documento
> - Mantém consistência automática
> - Facilita atualizações em massa
>
> **Outras Tabelas Relacionadas (Personalize conforme necessário):**
>
> ```
> Tabela 1:
> Tabela 2:
> Tabela 3:
> Relação entre elas:
>
>
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Passo 4: Integração com Tarefas (Agile/Scrum)</b></summary>

> O GDD morre quando ele se desconecta do trabalho real.
>
> **1. Integração Confluence + Jira:**
>
> - Crie um ticket no Jira ("Programar Pulo Duplo") diretamente a partir da frase no GDD que descreve o pulo duplo
> - Use macros do Confluence para exibir tickets relacionados
>
> **Espaço para Configuração:**
>
> ```
> Workspace do Jira:
>
>
> ```
>
> **Exemplo de Linkagem:**
> ```
> Mecânica: Pulo Duplo
> Ticket Jira:
> Status:
>
> ```
>
> **2. Sistema de Tasks no Notion:**
>
> - Cada página de mecânica deve ter uma checklist de implementação
>
> **Template de Checklist:**
> ```
> [ ] Arte Pronta?
> [ ] Código Pronto?
> [ ] SFX Pronto?
> [ ] Testes Prontos?
> [ ] Documentação Atualizada?
> ```
>
> **Espaço para Exemplo:**
>
> ```
> Mecânica:
>
> [ ] Arte Pronta?
> [ ] Código Pronto?
> [ ] SFX Pronto?
> [ ] Testes Prontos?
> [ ] Documentação Atualizada?
> ```
>
> **3. Regra de Ouro:**
>
> - Nenhuma tarefa de programação deve começar sem um link para a página do GDD que explica o que deve ser feito
> - Se a página não existe, a tarefa é bloqueada
>
> **Espaço para Registro:**
>
> ```
> Tarefas Bloqueadas (aguardando GDD):
>
> 1.
> 2.
> 3.
> ```

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>Passo 5: A Rotina de Manutenção (Jardinagem)</b></summary>

> Um GDD orgânico precisa ser regado.
>
> **1. Revisão de Sprint:**
>
> - Ao final de cada ciclo de trabalho (Sprint), reserve 30 minutos para atualizar o GDD
> - Se uma mecânica mudou durante os testes (ex: "o pulo agora é mais alto"), atualize o documento imediatamente
>
> **Espaço para Registro de Revisões:**
>
> ```
> Sprint 1 - Data:
> Mudanças:
>
>
>
>
>
> Sprint 2 - Data:
> Mudanças:
>
>
>
>
>
> ```
>
> **2. Versionamento:**
>
> - Use o histórico da página para marcar grandes mudanças
> - Exemplo: "v0.5 - Sistema de Inventário removido"
> - Isso ajuda a entender por que certas decisões foram tomadas no passado
>
> **Espaço para Log de Versões:**
>
> ```
> v0.1 - Data:
> Mudança:
>
>
> v0.2 - Data:
> Mudança:
>
>
> v0.3 - Data:
> Mudança:
>
>
> ```
>
> **3. Ownership (Dono da Página):**
>
> - Cada seção deve ter um responsável
> - O Artista Chefe cuida da "Art Bible"
> - O Game Designer cuida das "Mecânicas"
> - Sem donos, o documento vira terra de ninguém
>
> **Espaço para Registro de Ownership:**
>
> ```
> Seção: High Concept
> Dono:
>
> Seção: Mecânicas
> Dono:
>
> Seção: Art Bible
> Dono:
>
> Seção: Lore & Mundo
> Dono:
>
> Seção: Áudio
> Dono:
>
> ```

</details>

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Conclusão</b></summary>

> Ao seguir este roteiro, você cria uma estrutura que começa pequena (apenas o essencial) e cresce em complexidade apenas quando necessário, mantendo a equipe sempre alinhada com a versão mais atual da verdade do projeto.
>
> **Checklist Final:**
>
> - [ ] Questionário de Fundação completo
> - [ ] Ferramenta configurada (Notion/Confluence)
> - [ ] One-Pager criado
> - [ ] Bancos de dados relacionais configurados
> - [ ] Integração com sistema de tarefas funcionando
> - [ ] Rotina de manutenção estabelecida
> - [ ] Ownership definido para cada seção

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Referências</b></summary>

> **Ferramentas Recomendadas:**
>
> - [Notion](https://www.notion.so/) - Base de conhecimento e wikis
> - [Confluence](https://www.atlassian.com/software/confluence) - Wiki corporativa
> - [Jira](https://www.atlassian.com/software/jira) - Gestão de tarefas
> - [Miro](https://miro.com/) - Diagramas e fluxogramas
> - [Whimsical](https://whimsical.com/) - Diagramas visuais
>
> **Documentação Relacionada:**
>
> - [Compêndio de Arquitetura de Design de Jogos](./compendio-arquitetura-design-jogos.md) - Guia completo sobre GDDs
> - [Padrões de Relatórios](./padroes-relatorios.md) - Padrões de formatação

</details>

---

**Última atualização:** 2024-12-27
