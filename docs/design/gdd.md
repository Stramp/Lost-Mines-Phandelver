---
title: "Game Design Document"
category: design
tags: [gdd, game-design, vision, dnd-5e, action-rpg]
last_updated: 2024-12-27
difficulty: beginner
related: [gas-dnd-adaptation.md, dnd-rules/index.md]
---

**Navegação:** [Home](../../README.md) > [Documentação](index.md) > [Design](design/index.md) > GDD

# Game Design Document (GDD) - MyProject2

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Visão do Jogo Final</b></summary>

> **MyProject2** é um **Action RPG baseado em D&D 5e** desenvolvido no Unreal Engine 5.7, onde os jogadores criam e controlam personagens seguindo as regras completas do D&D 5ª edição em um ambiente de ação em tempo real.
>

> **Objetivo Principal:** Transformar a experiência de mesa do D&D 5e em um jogo de ação, mantendo fidelidade às regras originais e permitindo que jogadores explorem mundos fantásticos com seus personagens customizados.
>
</details>
---

## 🎮 Conceito do Jogo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Gênero e Estilo</b></summary>

> **Gênero:** Action RPG (ARPG) com elementos de D&D 5e
>

> **Estilo de Jogo:**
> - Combate em tempo real com mecânicas baseadas em D&D 5e
> - Criação de personagem completa seguindo regras D&D 5e
> - Progressão de personagem através de níveis e features
> - Exploração de mundos fantásticos
> - Multiplayer cooperativo (planejado)
>
> **Público-Alvo:**
> - Jogadores de D&D 5e que querem jogar em um ambiente digital
> - Fãs de Action RPG que querem profundidade de customização
> - Desenvolvedores interessados em sistemas de fichas complexos
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Mecânicas Principais</b></summary>

> ### Sistema de Fichas D&D 5e
>

> - ✅ Criação completa de personagem (raça, classe, background)
> - ✅ Sistema Point Buy para ability scores
> - ✅ Multiclassing completo
> - ✅ Features de classes
> - ✅ Spellcasting (planejado)
> - ✅ Skills e Proficiencies
>
</details>
    ### Combate

    - 📋 Sistema de turnos adaptado para tempo real
    - 📋 Ações baseadas em D&D 5e (Attack, Dodge, Dash, etc.)
    - 📋 Cálculo de AC, dano, e ataques seguindo regras D&D
    - 📋 Sistema de HP/MaxHP
    - 📋 Death system

    ### Progressão

    - 📋 Level up system (1-20)
    - 📋 ASI (Ability Score Improvement)
    - 📋 Feat selection
    - 📋 Features de classes por nível

    ### Equipamentos

    - 📋 Sistema de armas e armaduras D&D 5e
    - 📋 Propriedades de armas (versatile, finesse, two-handed, etc.)
    - 📋 Bônus de equipamentos
    - 📋 Inventário com peso (Carrying Capacity)

---

## 🗺️ Roadmap de Desenvolvimento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📅 Fases de Desenvolvimento</b></summary>

> **Roadmap resumido** - Para versão completa e detalhada, veja [docs/planning/roadmap.md](../planning/roadmap.md)
>

> **Status Atual:**
>
> - ✅ **Fase 1:** Sistema de Fichas (Core Completo - 80%)
> - 📋 **Fase 2:** Combate Básico com GAS (Próxima)
> - 📋 **Fases 3-10:** Planejadas
>
> **Fases Principais:**
>
> - ✅ **Fase 1:** Sistema de Fichas (Point Buy, Multiclasse, Motores desacoplados)
> - 📋 **Fase 2:** Combate Básico com GAS (AttributeSet, ASC, Gameplay Effects)
> - 📋 **Fase 3:** NPCs e Monsters
> - 📋 **Fase 4:** Equipamentos e Recursos
> - 📋 **Fase 5:** Features e Habilidades (via GAS)
> - 📋 **Fase 6:** Skills e Saving Throws
> - 🔮 **Fases 7-10:** Sistemas Avançados
>
> **📖 Para roadmap completo com prazos, dependências, status detalhado e decisões arquiteturais, veja [docs/planning/roadmap.md](../planning/roadmap.md)**
>
</details>
---

## 🎯 Objetivos de Gameplay

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Experiência do Jogador</b></summary>

> ### Criação de Personagem
>

> - Criar personagens únicos seguindo regras D&D 5e
> - Customização completa (raça, classe, background, ability scores)
> - Multiclassing para builds complexos
> - Escolhas de features e feats
>
</details>
    ### Combate

    - Combate estratégico baseado em D&D 5e
    - Uso de habilidades e features de classes
    - Spellcasting completo
    - Sistema de ações e recursos

    ### Progressão

    - Level up de 1 a 20
    - Ganho de features por nível
    - ASI e feat selection
    - Customização contínua do personagem

    ### Exploração

    - Mundos fantásticos para explorar
    - Interação com NPCs e monsters
    - Quests e missões
    - Descoberta de itens e equipamentos

---

## 🔗 Integração com Sistema Técnico

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Como o Sistema de Fichas se Encaixa</b></summary>

> O sistema de fichas atual é a **base fundamental** do jogo:
>

> - **Criação de Personagem:** Sistema completo de fichas permite criar qualquer personagem D&D 5e
> - **Dados de Combate:** Ability scores, modifiers, proficiencies alimentam sistema de combate
> - **Progressão:** Level up e features são gerenciados pelo sistema de fichas
> - **Features de Classes:** Spellcasting, abilities, e recursos são baseados no sistema de fichas
>
> **📖 Para detalhes técnicos, veja [Arquitetura Técnica](../technical/architecture.md)**
>
</details>
---

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Relacionada</b></summary>

> - **[Regras D&D 5e](dnd-rules/)** - Regras implementadas
> - **[Arquitetura Técnica](../technical/architecture.md)** - Como está implementado
> - **[API Reference](../technical/api.md)** - Classes e funções disponíveis
> - **[README Principal](../../README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](../../ARCHITECTURE.md)** - Resumo da arquitetura
> - **[CHANGELOG.md](../../CHANGELOG.md)** - Histórico de mudanças
> - **[Índice de Documentação](../index.md)** - Organização completa
>

</details>