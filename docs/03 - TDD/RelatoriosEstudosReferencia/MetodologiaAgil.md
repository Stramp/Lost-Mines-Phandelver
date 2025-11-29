# Padrões de Relatórios - MyProject2

Este documento define os padrões de formatação e estrutura para relatórios técnicos e estudos de referência do projeto, integrando numeração hierárquica com colapsos e organização visual.

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Este documento estabelece os padrões para criação de relatórios técnicos extensos e estudos de referência, combinando:
>
> - **Numeração hierárquica** (1., 1.1., 1.1.1.) para estrutura lógica
> - **Colapsos e blocos de citação** para organização visual
> - **Estilo acadêmico mas acessível** para conteúdo denso em informação
> - **Referências concretas** a exemplos reais (jogos, desenvolvedores, ferramentas)

</details>

---

## Estrutura Padrão de Relatórios

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>1. Título e Introdução</b></summary>

> **Formato do Título:**
>
> - Título principal em negrito, descritivo e específico
> - Subtítulo opcional para contexto adicional
> - Numeração de seções hierárquica (1., 1.1., 1.1.1.)
>
> **Exemplo:**
>
> ```
> Arquitetura de Resiliência: Metodologias Ágeis e Estratégias de Engenharia de Sistemas para o Desenvolvimento Solo de RPGs de Alta Complexidade
>
> 1. Introdução: A Assimetria da Ambição no Desenvolvimento Solo
> ```
>
> **Características da Introdução:**
>
> - Contexto amplo e problematização
> - Estabelecimento da premissa central
> - Referências a exemplos concretos (jogos, desenvolvedores, casos de uso)
> - Linguagem acadêmica mas acessível
> - Parágrafos longos e densos em informação

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>2. Estrutura de Seções</b></summary>

> **Hierarquia de Seções:**
>
> ```
> 1. Título Principal
>    1.1. Subtítulo
>        1.1.1. Sub-subtítulo
> ```
>
> **Padrão de Numeração:**
>
> - Seções principais: `1.`, `2.`, `3.`
> - Subseções: `1.1.`, `1.2.`, `1.3.`
> - Sub-subseções: `1.1.1.`, `1.1.2.`
>
> **Características:**
>
> - Cada seção deve ter um propósito claro
> - Transições suaves entre seções
> - Uso de subtítulos descritivos e específicos
>
> **Integração com Colapsos:**
>
> - Seções principais podem usar `<details>` para organização visual
> - Numeração hierárquica mantida dentro dos colapsos
> - Blocos de citação (`>`) para hierarquia visual adicional

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>3. Estilo de Escrita</b></summary>

> **Tom e Linguagem:**
>
> - **Acadêmico mas acessível:** Linguagem técnica precisa, mas compreensível
> - **Denso em informação:** Parágrafos longos com múltiplas ideias relacionadas
> - **Referências concretas:** Sempre que possível, citar exemplos reais (jogos, desenvolvedores, ferramentas)
> - **Problematização:** Apresentar problemas antes de soluções
> - **Argumentação:** Construir argumentos logicamente, com premissas e conclusões
>
> **Exemplo de Parágrafo Padrão:**
>
> ```
> O desenvolvimento de jogos digitais, em sua encarnação moderna, é frequentemente
> percebido como um esforço industrial massivo, exemplificado por títulos como Baldur's
> Gate 3 (BG3), que mobilizou centenas de desenvolvedores, um orçamento multimilionário
> e anos de iteração sobre um conjunto de regras preexistente e robusto (Dungeons &
> Dragons 5ª Edição). Para um desenvolvedor solo, a aspiração de replicar a densidade
> mecânica e a profundidade sistêmica de um título dessa magnitude representa um desafio
> de assimetria extrema.
> ```
>
> **Características:**
>
> - Frases longas e complexas
> - Múltiplas ideias por parágrafo
> - Uso de parênteses para informações adicionais
> - Referências a exemplos concretos
> - Linguagem descritiva e precisa

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>4. Tabelas e Estruturas de Dados</b></summary>

> **Formato de Tabelas:**
>
> - Cabeçalhos claros e descritivos
> - Colunas bem definidas
> - Justificativa técnica quando aplicável
> - Uso de markdown para tabelas
>
> **Exemplo:**
>
> ```
> | Coluna | Função no Contexto Solo RPG | Limite de WIP (Recomendado) | Justificativa Técnica |
> |--------|------------------------------|------------------------------|----------------------|
> | Backlog | Armazena todas as ideias de mecânicas | Infinito | Evita que ideias soltas distraiam o foco atual |
> | Ready | Tarefas quebradas em unidades atômicas | 10-15 itens | Garante que há trabalho preparatório feito |
> | Doing | O foco absoluto do momento | 1-2 itens | Previne a alternância de contexto |
> ```
>
> **Características:**
>
> - Tabelas comparativas quando útil
> - Dados quantitativos quando disponíveis
> - Justificativas técnicas claras
>
> **Organização Visual:**
>
> - Tabelas podem estar dentro de colapsos para melhor navegação
> - Usar blocos de citação (`>`) quando dentro de seções colapsadas

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>5. Exemplos e Casos de Uso</b></summary>

> **Formato de Exemplos:**
>
> - Exemplos "Errado" vs "Correto"
> - Exemplos práticos e específicos
> - Contexto claro para cada exemplo
>
> **Exemplo:**
>
> ```
> Exemplos de Micro-milestones para um RPG estilo BG3:
>
> Errado (Macro): "Implementar classes de mago."
>
> Correto (Micro): "Configurar a estrutura de dados para o feitiço 'Mísseis Mágicos'."
>
> Correto (Micro): "Criar o efeito visual de impacto do projétil de força."
>
> Correto (Micro): "Implementar a subtração de slots de magia ao conjurar."
> ```
>
> **Características:**
>
> - Contraste claro entre abordagens
> - Especificidade nos exemplos corretos
> - Múltiplos exemplos para reforçar o ponto
>
> **Organização Visual:**
>
> - Exemplos podem estar em colapsos separados por categoria
> - Usar emojis descritivos (✅ para correto, ❌ para errado)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>6. Estudos de Caso</b></summary>

> **Estrutura de Estudos de Caso:**
>
> - Título com nome do desenvolvedor/jogo
> - Contexto e background
> - Metodologia utilizada
> - Arquitetura técnica
> - Insights específicos
> - Lições aprendidas
>
> **Exemplo:**
>
> ```
> 5.1. Dwarf Fortress (Tarn Adams): O Épico da Persistência
>
> Dwarf Fortress é o exemplo máximo de complexidade sistêmica criada por uma equipe
> mínima (originalmente apenas Tarn Adams na programação).
>
> Metodologia: Desenvolvimento contínuo sem prazos (mais de 20 anos). Foco total em simulação.
>
> Arquitetura: Tarn utiliza uma estrutura de código monolítica mas logicamente segmentada.
> Ele enfatiza a importância de "nomes sensíveis" e organização de IDs para gerenciar
> centenas de milhares de linhas de código.
>
> Insight de Complexidade: A complexidade famosa do jogo (ex: gatos morrendo por intoxicação
> alcoólica após lamberem cerveja das patas) não foi "scriptada". Ela emergiu da interação
> de sistemas independentes...
> ```
>
> **Características:**
>
> - Foco em lições práticas
> - Detalhes técnicos específicos
> - Insights únicos de cada caso
> - Aplicabilidade para o contexto do projeto
>
> **Organização Visual:**
>
> - Cada estudo de caso pode estar em um colapso separado
> - Usar hierarquia visual com blocos de citação aninhados
> - Emojis descritivos (📚 para estudos, 💡 para insights)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>7. Recomendações e Conclusões</b></summary>

> **Estrutura de Recomendações:**
>
> - Seção numerada (ex: "7. Recomendação de Alto Nível")
> - Subseções organizadas por categoria
> - Recomendações específicas e acionáveis
> - Justificativas técnicas
>
> **Exemplo:**
>
> ```
> 7. Recomendação de Alto Nível: O "Solo RPG Stack"
>
> 7.1. O Processo (Agile Solo Híbrido)
> Metodologia: Personal Kanban Rigoroso.
> Ciclo de Vida: Desenvolvimento em Espiral (Spiral Development).
> ...
>
> 7.2. A Tecnologia (A Pilha Técnica)
> Engine: Unity ou Godot (pela facilidade de extensão do editor).
> Arquitetura: Híbrida Data-Driven + Componentes.
> ...
> ```
>
> **Características:**
>
> - Recomendações práticas e específicas
> - Organização clara por categoria
> - Justificativas técnicas
> - Aplicabilidade imediata
>
> **Organização Visual:**
>
> - Recomendações principais em colapsos abertos (`<details open>`)
> - Subcategorias em colapsos aninhados
> - Usar emojis (🎯 para recomendações, 🔧 para tecnologia)

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>8. Referências e Citações</b></summary>

> **Formato de Referências:**
>
> - Nota sobre citações no final
> - Links para fontes quando disponíveis
> - Referências integradas no texto quando possível
>
> **Exemplo:**
>
> ```
> Nota sobre Citações: As referências correspondem aos snippets de pesquisa fornecidos
> e foram integradas para validar as afirmações técnicas e metodológicas apresentadas.
> ```
>
> **Características:**
>
> - Transparência sobre fontes
> - Validação de afirmações
> - Referências quando necessário
>
> **Organização Visual:**
>
> - Seção de referências pode estar em colapso no final
> - Links organizados em lista dentro de blocos de citação

</details>

---

## 9. Princípios Práticos para Desenvolvimento Solo de RPGs

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>9.1. Metodologia: Personal Kanban e Micro-Tarefas</b></summary>

> Para um desenvolvedor solo, o Scrum tradicional cria burocracia desnecessária. A solução é o **Personal Kanban**, focado em visualizar o fluxo e limitar o trabalho em andamento (WIP). Este método elimina a sobrecarga administrativa de cerimônias como daily standups e retrospectivas em equipe, permitindo que o desenvolvedor solo mantenha foco total na execução técnica.
>
> **Regra de Ouro:** Tenha no máximo 1 ou 2 tarefas na coluna "Fazendo" (Doing) para evitar a fragmentação mental. Esta limitação rigorosa de WIP previne o fenômeno conhecido como "context switching", onde a alternância constante entre múltiplas tarefas reduz drasticamente a produtividade. Para um desenvolvedor solo trabalhando em sistemas complexos como RPGs, onde cada sistema (combate, inventário, diálogo, progressão) possui profundidade técnica significativa, manter apenas uma ou duas tarefas ativas garante que o contexto completo esteja carregado na memória de trabalho, facilitando decisões arquiteturais coerentes e implementações mais robustas.
>
> **Micro-Milestones:** Quebre tarefas grandes em unidades que possam ser concluídas em uma sessão de 2 a 4 horas. Isso gera motivação constante e ajuda a identificar erros de arquitetura cedo. A fragmentação de tarefas macro (ex: "Implementar sistema de magias") em micro-tarefas atômicas (ex: "Configurar estrutura de dados para o feitiço 'Mísseis Mágicos'", "Criar efeito visual de impacto do projétil de força", "Implementar subtração de slots de magia ao conjurar") não apenas facilita o rastreamento de progresso, mas também expõe dependências arquiteturais e problemas de design antes que sejam incorporados profundamente no código. Cada micro-milestone concluído representa um incremento verificável de funcionalidade, criando um ciclo de feedback positivo que mantém o desenvolvedor engajado mesmo em projetos de longa duração.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>9.2. Arquitetura: Data-Driven e Composição</b></summary>

> Para atingir a complexidade de Baldur's Gate 3 sozinho, você não pode "codar" cada feitiço ou item individualmente. A abordagem tradicional de criar classes específicas para cada entidade do jogo (ex: `class FireballSpell`, `class LightningBoltSpell`, `class HealingPotion`, `class ManaPotion`) resulta em explosão combinatória de código que é impossível de manter para um desenvolvedor solo. A solução está em separar radicalmente a lógica dos dados, permitindo que o conteúdo seja criado através de configuração ao invés de programação.
>
> **Data-Driven Design:** Separe a lógica dos dados. Use ScriptableObjects (Unity) ou Resources (Godot) para criar milhares de itens/feitiços apenas ajustando variáveis em inspetores, sem escrever código novo para cada um. Em Unreal Engine, isso se traduz em Data Tables e Data Assets, onde cada feitiço, item, ou habilidade é definido como uma linha em uma tabela estruturada, com propriedades como dano, alcance, custo de mana, tipo de elemento, etc. Esta abordagem permite que designers (ou o próprio desenvolvedor atuando como designer) criem conteúdo rapidamente através de interfaces visuais, enquanto o código permanece genérico e reutilizável. Um sistema de spellcasting bem arquitetado pode suportar centenas de feitiços diferentes com uma única implementação de código, onde cada feitiço é apenas uma configuração de dados.
>
> **Composição sobre Herança:** Em vez de hierarquias rígidas, use componentes modulares (ex: um objeto tem componente Inflamável e Comestível). Isso permite interações sistêmicas emergentes como em Caves of Qud. A herança tradicional (ex: `class Item : public GameObject`, `class Weapon : public Item`, `class Sword : public Weapon`) cria árvores de herança profundas e rígidas que dificultam a combinação de características. A composição por componentes (ex: um objeto pode ter `UFlammableComponent`, `UEdibleComponent`, `UWeaponComponent`, `UPoisonableComponent`) permite que características sejam combinadas dinamicamente, criando comportamentos emergentes. Um item pode ser simultaneamente uma arma, inflamável, e comestível, permitindo interações como "comer uma espada envenenada que está em chamas" - comportamento que não foi explicitamente programado, mas emerge da interação dos componentes. Este padrão é fundamental em jogos como Caves of Qud, onde a complexidade sistêmica emerge de componentes simples combinados de forma não-linear.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>9.3. Escopo: Fatia Vertical Sistêmica</b></summary>

> Não tente construir o mundo todo de uma vez. Foque na Vertical Slice (Fatia Vertical), uma pequena área onde todos os sistemas centrais funcionam juntos. Esta abordagem é fundamental para validar a viabilidade técnica do projeto antes de investir anos em criação de conteúdo. A tentação de construir sistemas isolados (ex: "primeiro vou fazer todo o sistema de combate, depois todo o sistema de diálogo, depois todo o sistema de inventário") resulta em integrações complexas e problemas arquiteturais descobertos tarde demais.
>
> **Objetivo:** Crie uma pequena área onde todos os sistemas centrais (combate, diálogo, inventário, salvamento) funcionem juntos. Isso prova que o jogo é tecnicamente viável antes de você gastar anos criando conteúdo. Uma vertical slice completa pode ser uma única dungeon com um combate, um diálogo com um NPC, um item coletado e usado, e um save/load funcionando. Esta fatia vertical serve como prova de conceito arquitetural, validando que todos os sistemas podem coexistir e interagir corretamente. Se problemas fundamentais de arquitetura existem, eles serão descobertos nesta fase inicial, quando o custo de refatoração é mínimo.
>
> **Pilares de Design:** Defina 3 pilares imutáveis (ex: "Combate Tático", "Interação Elemental", "Narrativa Ramificada"). Se uma ideia não fortalece um desses pilares, ela deve ser cortada impiedosamente. Para um desenvolvedor solo, a disciplina de escopo é crítica. Cada feature adicionada multiplica a complexidade de manutenção, testes, e integração. Os pilares de design servem como filtro objetivo para decisões de escopo: se uma mecânica proposta não contribui diretamente para um dos três pilares fundamentais, ela deve ser rejeitada, independentemente de quão "legal" ou "interessante" pareça. Esta disciplina previne o "feature creep" que é a causa de morte de muitos projetos solo ambiciosos.

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>9.4. Produção: Proceduralismo Assistido</b></summary>

> Use a geração procedural para fazer o "trabalho braçal", não apenas para criar aleatoriedade. A geração procedural é frequentemente associada apenas à criação de conteúdo aleatório (ex: dungeons gerados proceduralmente, loot aleatório), mas seu verdadeiro poder para um desenvolvedor solo está na automação de tarefas repetitivas que consumiriam tempo excessivo se feitas manualmente.
>
> **Ossos e Carne:** Gere a estrutura base (mapas, descrições de itens, nomes de NPCs) via algoritmos e refine manualmente apenas o que é crítico para a experiência. Isso multiplica sua capacidade de produção. Um algoritmo pode gerar milhares de descrições de itens baseadas em templates e regras gramaticais, mas o desenvolvedor pode então revisar e polir manualmente apenas os itens raros ou narrativamente importantes. Da mesma forma, um gerador procedural de mapas pode criar a estrutura básica de uma dungeon (salas, corredores, posicionamento de portas), enquanto o desenvolvedor adiciona manualmente apenas elementos narrativos críticos (ex: um baú especial com um item único, um diálogo importante com um NPC). Esta divisão entre "ossos" (estrutura gerada) e "carne" (conteúdo manualmente refinado) permite escalar a produção de conteúdo sem sacrificar qualidade narrativa ou design intencional.
>
> **Ferramentas Próprias:** Gaste tempo criando ferramentas de edição dentro da engine. É mais rápido criar um "Gerador de Quests" do que escrever 100 quests à mão. Para um desenvolvedor solo, o investimento inicial em ferramentas de automação paga dividendos exponenciais. Um editor de quests customizado dentro do Unreal Engine, por exemplo, pode permitir que o desenvolvedor crie quests através de uma interface visual, com validação automática de pré-requisitos, geração automática de objetivos secundários, e integração direta com sistemas de diálogo e recompensas. O tempo investido em criar esta ferramenta (ex: 1-2 semanas) é recuperado após criar apenas algumas dezenas de quests, e continua gerando economia de tempo para centenas de quests futuras. Esta filosofia de "automatizar o repetitivo, manualizar o único" é fundamental para projetos solo de grande escala.

</details>

---

## Elementos Específicos do Estilo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Formatação de Texto</b></summary>

> **Uso de Aspas e Ênfase:**
>
> - **Aspas para termos técnicos ou conceitos:** "teatro de produtividade", "Paradoxo do Chapéu"
> - **Itálico para ênfase:** *dopamina*, *maratona*
> - **Negrito para conceitos-chave:** **Data-Driven Design**, **Personal Kanban**
>
> **Parênteses e Informações Adicionais:**
>
> - Uso extensivo de parênteses para informações complementares
> - Exemplos: "(ex: 'Alquimia', 'Romance')", "(Work In Progress)"
>
> **Listas e Enumerações:**
>
> - Listas numeradas para sequências lógicas
> - Listas com marcadores para itens relacionados
> - Hierarquia clara com indentação

</details>

---

## Integração com Colapsos e Organização Visual

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎨 Padrões de Colapsos</b></summary>

> **Hierarquia Visual:**
>
> - **Nível 1 (Principal):** Fundo `#e8e8e8` + Bloco de citação `>`
> - **Nível 2 (Sub-seção):** Fundo `#d8d8d8` + Bloco de citação aninhado `>>`
> - **Nível 3 (Itens):** Dentro de `>>` para manter hierarquia
>
> **Padrão de Estilo para Títulos:**
>
> - Títulos principais: `background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;`
> - Sub-seções: `background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;`
> - Usar `<b>` para negrito nos títulos principais
>
> **Emojis no Summary:**
>
> - 📊 Para resumos/estatísticas
> - ✅ Para pontos positivos
> - ⚠️ Para avisos/problemas
> - 🔴 Para crítico/alta prioridade
> - 🟡 Para médio/média prioridade
> - 🟢 Para baixo/baixa prioridade
> - 📋 Para listas/checklists
> - 💡 Para dicas/sugestões
> - 🎯 Para objetivos/metas
> - 📈 Para métricas/analises
> - 🔧 Para ferramentas/configurações
> - 📚 Para documentação/referências
>
> **Estado Padrão:**
>
> - Usar `<details open>` para:
>   - ✅ Resumo executivo
>   - ✅ Conclusões principais
>   - ✅ Informações críticas
>   - ✅ Primeira seção importante
>
> - NÃO usar `open` para:
>   - ❌ Detalhes técnicos extensos
>   - ❌ Listas longas de problemas
>   - ❌ Informações secundárias
>   - ❌ Sub-seções aninhadas

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Exemplo Completo de Estrutura Integrada</b></summary>

> **Estrutura combinando numeração hierárquica com colapsos:**
>
> ```markdown
> # Título: Arquitetura de Resiliência: [Tema Principal]
>
> <details open>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo Executivo</b></summary>
>
> > Resumo com métricas e conclusões rápidas.
>
> </details>
>
> ---
>
> ## 1. Introdução: [Contexto e Problematização]
>
> <details>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>1.1. Subtema</b></summary>
>
> > Conteúdo da subseção com parágrafos densos em informação...
> >
> > <details>
> > <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">1.1.1. Detalhamento</summary>
> >
> > > Conteúdo detalhado...
> >
> > </details>
>
> </details>
>
> ---
>
> ## 2. [Tema Principal 1]
>
> <details>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>2.1. Subtema</b></summary>
>
> > Tabelas quando útil
> > Exemplos práticos
>
> </details>
>
> ---
>
> ## 5. Estudos de Caso: [Lições de Longa Duração]
>
> <details>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>5.1. Caso 1</b></summary>
>
> > Metodologia
> > Arquitetura
> > Insights
>
> </details>
>
> ---
>
> ## 7. Recomendação de Alto Nível: [Síntese]
>
> <details open>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>7.1. Processo</b></summary>
>
> > Recomendações práticas...
>
> </details>
>
> ---
>
> <details open>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Conclusão</b></summary>
>
> > Síntese e Próximos Passos
>
> </details>
> ```
>
> **Benefícios da Integração:**
>
> - Numeração hierárquica para estrutura lógica
> - Colapsos para navegação visual
> - Blocos de citação para hierarquia visual
> - Melhor organização de conteúdo extenso
> - Separadores `---` entre seções principais

</details>

---

## Checklist de Qualidade

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Checklist Completo</b></summary>

> Antes de considerar um relatório completo, verificar:
>
> **Estrutura e Conteúdo:**
>
> - [ ] Título descritivo e específico
> - [ ] Introdução com problematização clara
> - [ ] Estrutura hierárquica de seções (1., 1.1., 1.1.1.)
> - [ ] Parágrafos densos em informação
> - [ ] Referências a exemplos concretos (jogos, desenvolvedores, ferramentas)
> - [ ] Tabelas quando útil para comparação
> - [ ] Exemplos práticos (Errado vs Correto)
> - [ ] Estudos de caso com lições aprendidas
> - [ ] Recomendações específicas e acionáveis
> - [ ] Linguagem acadêmica mas acessível
> - [ ] Transições suaves entre seções
> - [ ] Conclusão que sintetiza os pontos principais
>
> **Organização Visual:**
>
> - [ ] Seções principais estão com `<details>`?
> - [ ] Títulos principais têm estilo com fundo `#e8e8e8`?
> - [ ] Sub-seções têm estilo com fundo `#d8d8d8`?
> - [ ] Blocos de citação (`>`) estão criando hierarquia visual?
> - [ ] Sub-seções importantes estão aninhadas?
> - [ ] Emojis descritivos no `<summary>`?
> - [ ] Seções críticas têm `<details open>`?
> - [ ] Listas longas estão colapsadas?
> - [ ] Estrutura hierárquica está clara?
> - [ ] Separadores `---` entre seções principais?

</details>

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Referências</b></summary>

> **Documentação Relacionada:**
>
> - [Markdown Organization Rules](../../../../.cursor/rules/markdown-organization.mdc) - Padrões completos de organização visual
> - [GitHub Flavored Markdown - Details](https://github.github.com/gfm/)
> - [HTML Details Element](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/details)
>
> **Lembre-se:**
>
> - Combine numeração hierárquica com colapsos para melhor navegação
> - Use blocos de citação para criar hierarquia visual
> - Mantenha consistência nos estilos e emojis
> - O objetivo é melhorar a legibilidade e organização, não complicar

</details>

---

**Última atualização:** 2024-12-27
