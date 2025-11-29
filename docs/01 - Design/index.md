---
title: "Design Documentation"
category: design
tags: [design, game-design, dnd-5e, rules]
last_updated: 2024-12-27
---

# Documentação de Design

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Esta seção contém toda a documentação relacionada ao **design do jogo**, incluindo:
>

> - Visão do produto final (GDD)
>
> - Regras D&D 5e implementadas
>
> - Mecânicas de gameplay
>
> - Design de sistemas
>
</details>
---

## Documentos Principais


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Game Design Document</b></summary>

> ### Game Design Document (GDD)
>
> [**gdd.md**](gdd.md) - Documento completo descrevendo a visão do jogo final
>
> | Aspecto | Descrição |
> |---------|-----------|
> | **Tipo de Jogo** | Action RPG baseado em D&D 5e |
> | **Objetivos** | Experiência de jogo imersiva e fiel às regras |
> | **Jogador** | Criação e progressão de personagens D&D 5e |
> | **Roadmap** | Integração com desenvolvimento |
> | **Sistema de Fichas** | Base para todas as mecânicas do jogo |
>
> [Ver GDD completo](gdd.md)

</details>


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Regras D&D 5e</b></summary>

> ### Regras D&D 5ª Edição
>
> [**dnd-rules/**](dnd-rules/) - Documentação algorítmica das regras
>
> | Regra | Status | Documento |
> |-------|--------|-----------|
> | **Ability Scores** | ✅ Completo | [ability-scores.md](dnd-rules/ability-scores.md) |
> | **Point Buy** | ✅ Completo | [point-buy.md](dnd-rules/point-buy.md) |
> | **Raças** | ✅ Completo | [races.md](dnd-rules/races.md) |
> | **Criação de Personagem** | ✅ Completo | [character-creation.md](dnd-rules/character-creation.md) |
> | **Multiclassing** | ✅ Completo | [multiclassing.md](dnd-rules/multiclassing.md) |
> | **Level Up** | ✅ Completo | [level-up.md](dnd-rules/level-up.md) |
> | **Spellcasting** | 🔮 Planejado | [spellcasting.md](dnd-rules/spellcasting.md) |
>
> [Ver regras D&D 5e completas](dnd-rules/index.md)

</details>


<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Adaptação D&D 5e + GAS</b></summary>


</details>
    ### Adaptação para Unreal Engine 5

    [**gas-dnd-adaptation.md**](gas-dnd-adaptation.md) - Como adaptar D&D 5e para Action RPG

    | Tópico | Conteúdo |
    |--------|----------|
    | **Adaptação de Regras** | RPG de Mesa vs Jogo Digital |
    | **GAS** | Gameplay Ability System - conceitos fundamentais |
    | **Fluxos Práticos** | Ataques, condições, magias, habilidades |
    | **Combate** | Sistema de colisão real e combate em tempo real |
    | **Fidelidade** | Manter regras D&D 5e adaptadas |

    [Ver adaptação completa](gas-dnd-adaptation.md)

---

## Regras D&D 5e Detalhadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Ability Scores e Modificadores</b></summary>

> **[ability-scores.md](dnd-rules/ability-scores.md)**
>

> - Cálculo de modificadores (Score - 10) / 2
>
> - Ranges válidos (1-30)
>
> - Modificadores para saves, skills, etc.
>
> [Ver regras de Ability Scores](dnd-rules/ability-scores.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💰 Sistema Point Buy</b></summary>

> **[point-buy.md](dnd-rules/point-buy.md)**
>

> - Máximo de 27 pontos para distribuir
>
> - Scores base começam em 8
>
> - Custo exponencial (8=0, 9=1, ..., 15=9)
>
> - Ajuste automático se exceder limite
>
> [Ver sistema Point Buy](dnd-rules/point-buy.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👥 Raças e Sub-raças</b></summary>

> **[races.md](dnd-rules/races.md)**
>

> - Bônus de Ability Scores por raça
>
> - Features raciais
>
> - Sub-raças e variantes
>
> - Variant Human (feat adicional)
>
> [Ver regras de raças](dnd-rules/races.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎭 Multiclassing</b></summary>

> **[multiclassing.md](dnd-rules/multiclassing.md)**
>

> - Requisitos de Ability Scores
>
> - Máximo de 20 níveis totais
>
> - Progressão independente por classe
>
> - Combinação de features
>
> [Ver regras de multiclassing](dnd-rules/multiclassing.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Level Up e Features</b></summary>

> **[level-up.md](dnd-rules/level-up.md)**
>

> - Progressão por nível
>
> - Features de classe por nível
>
> - ASI (Ability Score Improvement)
>
> - Feats opcionais
>
> [Ver regras de level up](dnd-rules/level-up.md)
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Spellcasting</b></summary>

> **[spellcasting.md](dnd-rules/spellcasting.md)** - 🔮 Planejado
>

> - Slots de magia por nível
>
> - Preparação de magias
>
> - Componentes (verbal, somático, material)
>
> - Spell DC e Attack Bonus
>
> [Ver regras de spellcasting](dnd-rules/spellcasting.md)
>
</details>
---

## Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> **Documentação Principal:**
>

> - [GDD](gdd.md) - Visão completa do jogo
>
> - [Adaptação D&D 5e + GAS](gas-dnd-adaptation.md) - Como adaptar D&D 5e para Unreal Engine 5
>
> - [Regras D&D 5e](dnd-rules/) - Referência de regras
>
> **Outras Seções:**
>
> - [Documentação Técnica](../technical/) - Arquitetura e implementação
>
> - [Planejamento](../planning/) - Roadmap e planos
>
> **Recursos:**
>
> - [README Principal](../../README.md) - Visão geral do projeto
>
> - [ARCHITECTURE.md](../../ARCHITECTURE.md) - Resumo da arquitetura
>
> - [Índice de Documentação](../index.md) - Organização completa
>
</details>
---

**Última atualização:** 2024-12-27
