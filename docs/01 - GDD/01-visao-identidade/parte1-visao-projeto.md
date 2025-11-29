# Parte 1: Visão do Projeto - MyProject2

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Este documento estabelece a visão fundamental do projeto, definindo identidade, mecânicas principais e escopo técnico. Baseado no questionário de fundação, serve como referência para todas as decisões de design e desenvolvimento.

</details>

---

## A. Identidade e Visão (High Concept)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 A.1. O "Elevator Pitch"</b></summary>

> **Conceito:**
>
> Uma versão fiel e adaptada da campanha **Minas de Phandelver** para jogar uma experiência de RPG de mesa com jogabilidade **ACTION** e não em turnos.
>
> "É como uma experiencia de RPG de mesa num mundo de games actions"
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏛️ A.2. Os 3 Pilares de Design</b></summary>

> Como é uma adaptação fiel da campanha oficial de D&D 5e (Minas de Phandelver), os pilares refletem a essência do D&D: fidelidade às regras, experiência de mesa (mas adaptada para tempo real), e seguir a narrativa oficial da campanha.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📜 Pilar 1: Fidelidade às Regras D&D 5e</summary>
>
> > - Todas as mecânicas seguem as regras oficiais do D&D 5ª Edição
> > - Ability Scores, modificadores, proficiências, level up, classes, raças
> > - Sistema de combate baseado em D&D 5e adaptado para tempo real
> > - Qualquer mecânica que não siga D&D 5e deve ser cortada
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 Pilar 2: Experiência de Mesa Digitalizada (mas em tempo real)</summary>
>
> > - Manter a essência de uma sessão de RPG de mesa
> > - Visual estilo top-down similar a mapas e tokens de mesa
> > - Narrativa e diálogos seguem o livro oficial
> > - Multiplayer cooperativo (um jogador como host/DM)
> > - Adaptação de turnos para tempo real mantendo as regras
> > - Troca em tempo real entre os integrantes da PT em jogo solo
> >
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📖 Pilar 3: Narrativa da Campanha Phandelver (seguir a história oficial)</summary>
>
> > - Seguir exatamente a estrutura da campanha oficial
> > - Quests, NPCs, locais e eventos baseados no livro
> > - Progressão por capítulos da campanha
> > - Decisões do jogador dentro dos limites da campanha oficial
>
> </details>
>
> **Regra de Corte:** Qualquer mecânica que não suporte esses pilares deve ser cortada para manter a integridade da adaptação.

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 A.3. A Fantasia do Jogador</b></summary>

> **Quem o jogador finge ser:**
>
> Um aventureiro de D&D 5e explorando a região de Phandalin, vivendo a campanha oficial **Minas de Phandelver** em tempo real.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📝 Detalhamento</summary>
>
> > - O jogador cria seu personagem seguindo as regras completas de D&D 5e (raça, classe, background)
> > - Vive as aventuras da campanha oficial
> > - Jogabilidade em tempo real ao invés de turnos
> > - Progressão de nível 1 a 5 (escopo da campanha Phandelver)
> > - Experiência imersiva de RPG de mesa digitalizada
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎨 Implicações para Design</summary>
>
> > - Sistema de criação de personagem completo (Point Buy, raças, classes, multiclassing)
> > - Todas as mecânicas devem reforçar a fantasia de ser um aventureiro D&D
> > - Visual e narrativa devem manter a essência de mesa de RPG
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌐 A.4. Público e Plataforma</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👥 Público-Alvo</summary>
>
> > - Jogadores de D&D 5e que querem viver a campanha Minas de Phandelver em formato digital
> > - Fãs de RPGs que querem experiência fiel a D&D 5e
> > - Grupos de amigos que querem jogar a campanha juntos
> > - Público que busca jogabilidade em tempo real ao invés de turnos
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💻 Plataforma(s)</summary>
>
> > - **PC (Windows)** - Plataforma principal
> > - **Mobile (Android/iOS)** - Suporte futuro
> > - **Cross-platform multiplayer** - Jogadores de diferentes plataformas podem jogar juntos
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⏱️ Duração de Sessão Esperada</summary>
>
> > - **2-4 horas por sessão** (similar a uma sessão de RPG de mesa)
> > - Sessões podem ser salvas e continuadas posteriormente
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔧 Implicações para Design</summary>
>
> > - Sistema de salvamento robusto (sessões podem ser longas)
> > - Interface adaptável para mobile e PC
> > - Multiplayer cooperativo (host local ou servidor dedicado)
> > - Sistema de pausa/salvamento para não perder progresso
> > - Modelo: Gratuito (fangame) ou possível monetização futura
>
> </details>

</details>

---

## B. Mecânica e Loop (Gameplay)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ B.1. O Loop Segundo-a-Segundo</b></summary>

> **O que o jogador faz com as mãos na maior parte do tempo:**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎯 Ações Primárias (Top 3)</summary>
>
> > 1. **Movimentação e exploração do mundo** - Navegar por Phandalin e áreas da campanha
> > 2. **Combate em tempo real** - Ataques, habilidades, spells baseados em D&D 5e
> > 3. **Interação com NPCs e objetos** - Diálogos, quests, loot, exploração
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⌨️ Ações Detalhadas</summary>
>
> > - **Movimentar personagem:** WASD (PC) ou analógico (mobile)
> > - **Atacar inimigos:** Clique ou botão de ação (ataques baseados em D&D 5e)
> > - **Interagir com objetos/ambientes:** Tecla E ou botão de interação
> > - **Usar habilidades/spells:** Teclas numéricas ou hotbar (cooldowns baseados em D&D)
> > - **Gerenciar inventário:** Tecla I ou menu
> > - **Navegar diálogos e quests:** Cliques em opções de diálogo
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 B.2. O Loop Minuto-a-Minuto</b></summary>

> **Ciclo de recompensa curto:**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Fluxo do Loop</summary>
>
> > 1. **Explorar área da campanha** - Phandalin, masmorras, locais da campanha
> > 2. **Encontrar combate/quest/desafio** - Encontros baseados na campanha oficial
> > 3. **Resolver desafio** - Combate, puzzle, diálogo (seguindo regras D&D 5e)
> > 4. **Ganhar XP e loot** - Seguindo tabelas oficiais de XP e loot da campanha
> > 5. **Level up** - Quando atingir XP necessário (tabela oficial D&D 5e)
> > 6. **Desbloquear nova área/quest** - Progressão na campanha oficial
> > 7. **Explorar próxima área** - Continuar a aventura
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⏱️ Tempo Médio do Loop</summary>
>
> > - **10-30 minutos por ciclo** (dependendo da complexidade do desafio)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎁 Pontos de Recompensa</summary>
>
> > - Ganho de XP após combates/quests
> > - Loot de inimigos e baús (baseado na campanha oficial)
> > - Level up e novas habilidades (seguindo D&D 5e)
> > - Progressão na narrativa da campanha
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏆 B.3. Condição de Vitória/Derrota</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✅ Condição de Vitória</summary>
>
> > Completar a campanha oficial **Minas de Phandelver** seguindo a narrativa do livro. Resolver todos os capítulos principais da campanha.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">❌ Condição de Derrota</summary>
>
> > Morte do personagem seguindo regras D&D 5e:
> >
> > - **Morte permanente** (modo hardcore) OU
> > - **Respawn em checkpoint** com penalidade (XP perdido, tempo) OU
> > - **Sistema de morte/ressurreição** seguindo D&D 5e (spells, itens)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📈 Sistema de Progressão Permanente</summary>
>
> > - Personagem mantém nível e progressão entre sessões
> > - Salvamento de progresso da campanha
> > - Itens e equipamentos mantidos
> > - Histórico de decisões e consequências salvas
> > - Progressão de nível 1 a 5 (escopo da campanha)
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 B.4. A "Cola" do Sistema</b></summary>

> **Método de Progressão Narrativa:**
>
> Por exploração e completação de quests da campanha oficial. Cada capítulo da campanha é desbloqueado ao completar o anterior, seguindo a estrutura do livro oficial **Minas de Phandelver**.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 Como Mecânicas e Narrativa se Conectam</summary>
>
> > - Cada capítulo da campanha é desbloqueado ao completar o anterior
> > - Quests da campanha guiam o jogador pela narrativa oficial
> > - NPCs e diálogos seguem o livro oficial
> > - Locais e eventos são baseados na campanha oficial
> > - Decisões do jogador podem afetar o desenrolar (dentro dos limites da campanha)
> > - Sistema de XP e level up permite progressão conforme a narrativa avança
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💡 Exemplo Concreto</summary>
>
> > Ao chegar em Phandalin (capítulo 1), o jogador recebe as quests oficiais da campanha (ex: "Ataque Goblin", "Cragmaw Hideout"). Ao completar "Ataque Goblin", desbloqueia o acesso à Cragmaw Hideout, seguindo exatamente a progressão do livro. O level up acontece conforme o jogador ganha XP completando quests, permitindo acesso a áreas mais difíceis da campanha.
>
> </details>

</details>

---

## C. Escopo Técnico e Artístico

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎨 C.1. Estilo Visual (Mínimo Viável)</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🖼️ Estilo Visual Escolhido</summary>
>
> > Top-down com mapas e tokens seguindo o estilo dos mapas e tokens de mesa. Visual similar a jogos como **Divinity: Original Sin** ou **Baldur's Gate**, mas com foco em representar os mapas da campanha de forma fiel.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💭 Justificativa</summary>
>
> > Mais viável para replicar a aventura. O estilo top-down permite representar os mapas da campanha de forma clara e fiel, mantendo a essência visual de uma sessão de RPG de mesa digitalizada. Facilita a criação de assets (tokens, mapas) e permite foco na jogabilidade e narrativa ao invés de gráficos complexos.
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 C.2. Tecnologia</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚙️ Engine Escolhida</summary>
>
> > **Unreal Engine 5.7**
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📐 Dimensão</summary>
>
> > **3D ou 2D(decidindo) com câmera top-down** (estilo isométrico ou overhead). Permite mais flexibilidade visual e melhor representação dos mapas da campanha, mantendo a perspectiva de mesa de RPG.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚠️ Riscos Técnicos Identificados</summary>
>
> > - **Escala do mundo:** Phandalin e áreas da campanha (múltiplos locais)
> > - **Sistema de quests e diálogos:** Complexo, baseado na campanha oficial
> > - **Múltiplos locais:** Masmorras, cidades, áreas selvagens da campanha
> > - **Multiplayer cooperativo:** Sincronização, host, networking
> > - **Sistema de salvamento robusto:** Progresso da campanha, decisões, estado do mundo
> > - **Adaptação de regras D&D 5e para tempo real:** Transformar sistema de turnos em tempo real mantendo fidelidade
>
> </details>

</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔊 C.3. Áudio</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎵 Sistema de Música</summary>
>
> > **Estática (uma trilha por área)** - Mais simples para começar. Para MVP, música estática por área é suficiente. Pode evoluir para sistema dinâmico no futuro se necessário.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎯 SFX Críticos (Lista)</summary>
>
> > 1. **Som de ataque** (espada, magia, arco)
> > 2. **Som de dano recebido** (feedback de hit)
> > 3. **Som de interação** (porta, baú, objeto)
> > 4. **Som de passos/ambientação** (imersão)
> > 5. **Feedback de UI** (cliques, seleção, notificações)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔌 Middleware de Áudio</summary>
>
> > **Unreal Audio System (nativo)** - Para começar simples. Pode evoluir para FMOD ou Wwise no futuro se necessário para sistema de música dinâmica mais complexo.
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Prioridades de Áudio</summary>
>
> > 1. **SFX de combate** (crítico para feedback de ações)
> > 2. **Música ambiente por área** (Phandalin, masmorras, etc.)
> > 3. **SFX de interação** (portas, baús, diálogos)
> > 4. **Vozes de NPCs** (opcional inicialmente, pode ser texto apenas)
> > 5. **SFX ambientais** (vento, fogo, água - opcional inicialmente)
>
> </details>

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Resumo Executivo</b></summary>

> **Projeto:** Adaptação fiel da campanha oficial D&D 5e "Minas de Phandelver" para Action RPG em tempo real.
>
> **Pilares Fundamentais:**
>
> 1. Fidelidade às Regras D&D 5e
> 2. Experiência de Mesa Digitalizada (tempo real)
> 3. Narrativa da Campanha Phandelver (oficial)
>
> **Plataformas:** PC (Windows) e Mobile (Android/iOS) - Cross-platform multiplayer
>
> **Engine:** Unreal Engine 5.7 - 3D Top-down
>
> **Escopo:** Campanha completa de nível 1 a 5, seguindo o livro oficial
>
> **Próximo Passo:** Continuar desenvolvimento seguindo o GDD completo

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Navegação</b></summary>

> **Documentos Relacionados:**
>
> - [Dashboard GDD](../dashboard-template.md) - Visão geral do projeto
> - [📝 Versão Questionário (para preencher)](parte1-questionario-fundacao.md)
> - [✅ Versão Completa (questionário preenchido)](parte1-questionario-fundacao-completo.md)

</details>

---

**Última atualização:** 2024-12-27
