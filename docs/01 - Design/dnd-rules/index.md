---
title: "D&D 5e Rules"
category: design
subcategory: dnd-rules
tags: [dnd-5e, rules, algorithmic, character-creation]
last_updated: 2024-12-27
difficulty: intermediate
related: [../gdd.md, ../../technical/guides/algorithmic/character-creation.md]
---

**Navegação:** [Home](../../../README.md) > [Documentação](index.md) > [Design](../design/index.md) > Regras D&D 5e

# Regras D&D 5e - Documentação Algorítmica

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Esta seção contém documentação algorítmica das regras do D&D 5ª edição implementadas no projeto. Esses documentos servem como referência rápida para implementar lógica de validação e cálculo.
>

> **Uso:** Referência durante implementação de features e validação de regras.
>
</details>
---

## Documentos Disponíveis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Regras de Criação de Personagem</b></summary>

> - **[Ability Scores](ability-scores.md)** - Ability scores, modificadores, ASI
>

> - **[Point Buy System](point-buy.md)** - Sistema de distribuição de pontos (27 pontos)
>
> - **[Raças e Sub-raças](races.md)** - Relação raça/sub-raça e bônus
>
> - **[Passos de Criação](character-creation.md)** - Ordem de criação de personagem
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Regras de Progressão</b></summary>

> - **[Multiclassing](multiclassing.md)** - Regras de multi-classing e pré-requisitos
>

> - **[Level Up](level-up.md)** - Sistema de level up e features
>
> - **[Spellcasting](spellcasting.md)** - Regras de spellcasting, CD, spell slots, cantrips
>
</details>
---

## Links Relacionados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Documentação Técnica</b></summary>

> - **[Arquitetura Técnica](../../technical/architecture.md)** - Como as regras são implementadas
>

> - **[API Reference](../../technical/api.md)** - Classes e funções disponíveis
>
> - **[GDD](../gdd.md)** - Visão do jogo final
>
> - **[GAS + D&D Adaptation](../gas-dnd-adaptation.md)** - Como D&D 5e é adaptado para GAS
>
> - **[Data Architecture](../../technical/data-architecture/index.md)** - Estrutura de dados do projeto
>
</details>
---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Implementação Atual</b></summary>

> **Status de Implementação:**
>

> - ✅ **Point Buy System:** Implementado com validação de 27 pontos
>
> - ✅ **Racial Bonuses:** Implementado com suporte a Variant Human
>
> - ✅ **Multiclassing:** Implementado com validação de pré-requisitos
>
> - ✅ **Fórmula de Cálculo:** `FinalScore = BASE_ABILITY_SCORE (8) + RacialBonuses + PointBuyAllocation` (ordem de aplicação)
>
> - ✅ **Testes:** 100% cobertura de testes para todos os motores críticos
>
> **📖 Ver também:** [gas-dnd-adaptation.md](../gas-dnd-adaptation.md) - Status completo do projeto
>
</details>
---

**Última atualização:** 2024-12-27
