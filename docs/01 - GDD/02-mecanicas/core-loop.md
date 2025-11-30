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

## 💡 Exemplo Prático: Sessão Completa

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Jornada Completa - Cragmaw Hideout</b></summary>

> **Cenário:** Grupo de nível 1 explora Cragmaw Hideout para resgatar Sildar Hallwinter.
>
> **1. Exploração (10 minutos):**
>
> - Grupo chega à entrada da caverna
> - Rogue faz teste de **Furtividade** (DEX +3, proficiency +2) = d20+5
> - Rola 15, total 20 → **Sucesso!** Detecta goblins dentro sem ser detectado
> - Grupo planeja estratégia de entrada
>
> **2. Combate Inicial (5 minutos):**
>
> - Grupo entra na caverna, encontra 2 goblins
> - **Fighter** ataca goblin 1: Espada longa (1d8+3), acerta, 7 de dano → **Goblin morre**
> - **Wizard** usa **Magic Missile**: 3 dardos, 1d4+1 cada = 9 de dano total → **Goblin 2 morre**
> - **Recompensa:** 50 XP cada (100 XP total), loot: 2d6 CP (moedas de cobre)
>
> **3. Exploração da Caverna (15 minutos):**
>
> - Grupo explora salas, encontra baú com 50 GP
> - Rogue detecta armadilha (teste de **Percepção** passou)
> - Grupo desarma armadilha, abre baú com sucesso
> - Encontra passagem secreta
>
> **4. Combate contra Klarg (Boss) (10 minutos):**
>
> - Grupo encontra Klarg (Bugbear, CR 1) e seu lobo
> - **Combate difícil:** Klarg tem 27 HP, AC 16, ataca com 2d8+2
> - **Fighter** recebe 12 de dano, cai para 0 HP → **Inconsciente**
> - **Clérigo** usa **Healing Word** (ação bônus): Cura Fighter com 1d4+3 = 6 HP
> - **Wizard** usa **Sleep**: Adormece lobo (HP total ≤ 5d8)
> - Grupo foca em Klarg, derrota após 3 rounds
> - **Recompensa:** 200 XP (Klarg), 50 GP + item incomum (arma mágica)
>
> **5. Resgate de Sildar (2 minutos):**
>
> - Grupo encontra Sildar preso
> - **Interação Social:** Diálogo com Sildar
> - Sildar oferece recompensa: 50 GP + informação sobre Phandalin
> - **Quest completa:** "Resgatar Sildar" → 100 XP adicional
>
> **6. Level Up (se aplicável):**
>
> - **XP Total:** 100 (goblins) + 200 (Klarg) + 100 (quest) = **400 XP**
> - Fighter tinha 0 XP, agora tem 400 XP
> - **Nível 2 requer:** 300 XP → **Level Up!**
> - Fighter ganha: +1d10+2 HP, nova feature de classe
>
> **7. Descanso (Short Rest):**
>
> - Grupo decide fazer **Short Rest** (1 hora) antes de sair
> - Fighter gasta 1 Hit Die: d10+2 = 8 HP recuperados
> - Warlock (se houver) recupera spell slots
> - Grupo está pronto para continuar
>
> **8. Retorno a Phandalin:**
>
> - Grupo sai da caverna, retorna para Phandalin
> - Entrega Sildar, recebe recompensa
> - **Nova Quest desbloqueada:** "Investigar Redbrands"
> - **Loop continua:** Próxima exploração/combate/quest
>
> **Tempo Total da Sessão:** ~45-60 minutos
>
> **Progressão:**
>
> - XP ganho: 400 XP
> - Level up: Fighter nível 1 → 2
> - Loot: 50 GP + item mágico
> - Quests: 1 completa, 1 nova desbloqueada

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Core Loop baseado em D&D 5e (Exploração, Combate, Interação Social) |

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima: Sistemas de Personagem](sistemas-personagem.md)
