# 2.1. Core Loop (Loop Central)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Core Loop</b></summary>

> O ciclo de atividades repetitivas e gratificantes que define a experiência do jogo.

</details>

---

## Fluxo do Core Loop

```
1. Explorar área da campanha (Phandalin, masmorras, locais)
   ↓
2. Encontrar combate/quest/desafio
   ↓
3. Resolver desafio (combate, puzzle, diálogo)
   ↓
4. Ganhar XP e loot (seguindo regras D&D 5e)
   ↓
5. Level up (quando atingir XP necessário)
   ↓
6. Desbloquear nova área/quest da campanha
   ↓
7. Explorar próxima área (volta ao passo 1)
```

## Tempo Médio do Loop

**10-30 minutos por ciclo** (dependendo da complexidade do desafio)

## Pontos de Recompensa

- Ganho de XP após combates/quests
- Loot de inimigos e baús (baseado na campanha oficial)
- Level up e novas habilidades (seguindo D&D 5e)
- Progressão na narrativa da campanha

## Diagrama Visual

```mermaid
flowchart TD
    Start([Início da Sessão]) --> Explore[🗺️ EXPLORAÇÃO<br/>Explorar Área da Campanha<br/>Phandalin, Masmorras, Locais]

    Explore --> Encounter{Encontrar<br/>Encontro?}

    Encounter -->|Combate| Combat[⚔️ COMBATE<br/>Encontro de Combate<br/>Tempo Real - Regras D&D 5e]
    Encounter -->|NPC/Diálogo| Social[💬 INTERAÇÃO SOCIAL<br/>Diálogo com NPCs<br/>Quests, Informações, Negociação]
    Encounter -->|Exploração| Exploration[🔍 EXPLORAÇÃO<br/>Descobrir Segredos<br/>Puzzles, Baús, Locais]
    Encounter -->|Nada| Explore

    Combat --> CombatResult{Resultado<br/>do Combate}
    CombatResult -->|Vitória| Reward[💰 RECOMPENSAS<br/>XP + Loot<br/>Seguindo Tabelas D&D 5e]
    CombatResult -->|Derrota| Death{Estado<br/>do Personagem}
    Death -->|Morte| GameOver([Game Over<br/>ou Ressurreição])
    Death -->|Inconsciente| RestDecision

    Social --> SocialResult{Resultado<br/>da Interação}
    SocialResult -->|Quest Aceita| Quest[📜 QUEST ATIVA<br/>Objetivo Definido]
    SocialResult -->|Informação| Info[ℹ️ NOVA INFORMAÇÃO<br/>Pistas, Localizações]
    SocialResult -->|Negociação| Trade[🤝 COMÉRCIO<br/>Comprar/Vender Itens]
    SocialResult -->|Fim| RestDecision

    Exploration --> ExplorationResult{Resultado<br/>da Exploração}
    ExplorationResult -->|Loot Encontrado| Loot[💎 LOOT<br/>Itens, Tesouros]
    ExplorationResult -->|Puzzle Resolvido| Puzzle[🧩 PUZZLE RESOLVIDO<br/>Desbloqueio de Área]
    ExplorationResult -->|Nada| RestDecision

    Quest --> QuestProgress[📋 PROGRESSO DA QUEST<br/>Completar Objetivos]
    QuestProgress --> QuestComplete{Quest<br/>Completa?}
    QuestComplete -->|Sim| Reward
    QuestComplete -->|Não| RestDecision

    Reward --> CheckLevel{XP Suficiente<br/>para Level Up?}
    CheckLevel -->|Sim| LevelUp[📈 LEVEL UP<br/>Novas Habilidades<br/>ASI, Features, Spell Slots]
    CheckLevel -->|Não| RestDecision

    LevelUp --> Unlock[🔓 DESBLOQUEIO<br/>Nova Área/Quest<br/>Progressão na Campanha]
    Unlock --> RestDecision

    Info --> RestDecision
    Trade --> RestDecision
    Loot --> RestDecision
    Puzzle --> RestDecision

    RestDecision{Precisa<br/>Descansar?}
    RestDecision -->|Recursos Baixos| RestChoice{Tipo de<br/>Descanso?}
    RestDecision -->|Recursos OK| Explore

    RestChoice -->|Short Rest<br/>1 hora| ShortRest[⏳ SHORT REST<br/>Recupera Hit Dice<br/>Algumas Habilidades<br/>Warlock: Spell Slots]
    RestChoice -->|Long Rest<br/>8 horas| LongRest[😴 LONG REST<br/>Recupera Tudo:<br/>HP, Spell Slots<br/>Habilidades, Hit Dice]

    ShortRest --> RestComplete[✅ DESCANSO COMPLETO<br/>Recursos Restaurados]
    LongRest --> RestComplete

    RestComplete --> CheckCampaign{Campanha<br/>Completa?}
    CheckCampaign -->|Não| Explore
    CheckCampaign -->|Sim| Victory([🏆 VITÓRIA<br/>Campanha Completa])

    GameOver --> End([Fim])
    Victory --> End

    style Start fill:#4caf50,color:#fff,stroke:#2e7d32,stroke-width:3px
    style Explore fill:#2196f3,color:#fff,stroke:#1565c0,stroke-width:2px
    style Combat fill:#f44336,color:#fff,stroke:#c62828,stroke-width:2px
    style Social fill:#ff9800,color:#fff,stroke:#e65100,stroke-width:2px
    style Exploration fill:#9c27b0,color:#fff,stroke:#6a1b9a,stroke-width:2px
    style Reward fill:#00bcd4,color:#fff,stroke:#00838f,stroke-width:2px
    style LevelUp fill:#8bc34a,color:#fff,stroke:#558b2f,stroke-width:2px
    style ShortRest fill:#ffc107,color:#000,stroke:#f57c00,stroke-width:2px
    style LongRest fill:#795548,color:#fff,stroke:#3e2723,stroke-width:2px
    style Victory fill:#4caf50,color:#fff,stroke:#1b5e20,stroke-width:3px
    style GameOver fill:#616161,color:#fff,stroke:#212121,stroke-width:2px
    style End fill:#9e9e9e,color:#fff,stroke:#424242,stroke-width:2px
```

**Legenda dos Pilares D&D 5e:**

- 🗺️ **Exploração:** Explorar o mundo, descobrir locais, encontrar segredos
- ⚔️ **Combate:** Encontros de combate em tempo real seguindo regras D&D 5e
- 💬 **Interação Social:** Diálogos, negociações, coleta de informações com NPCs
- ⏳ **Short Rest (1 hora):** Recupera Hit Dice, algumas habilidades (ex: Warlock spell slots)
- 😴 **Long Rest (8 horas):** Recupera tudo (HP, Spell Slots, habilidades, Hit Dice)

---

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima: Sistemas de Personagem](sistemas-personagem.md)
