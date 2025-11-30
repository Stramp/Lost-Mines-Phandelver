# 5.2. Tabelas de Loot

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 Tabelas de Loot</b></summary>

> Probabilidades de drop baseadas na raridade e nível do inimigo.

</details>

---

## Probabilidades de Drop por Raridade

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Tabela de Probabilidades Base</summary>

> **Probabilidades Gerais (D&D 5e):**
>
> | Raridade | Probabilidade | Valor Médio (GP) | Exemplos |
> |----------|--------------|------------------|----------|
> | **Comum** | 80% | 1-50 GP | Armas básicas, armaduras simples, poções comuns |
> | **Incomum** | 15% | 50-500 GP | Armas +1, armaduras +1, poções melhores |
> | **Raro** | 4% | 500-5000 GP | Armas +2, armaduras +2, itens mágicos poderosos |
> | **Muito Raro** | 1% | 5000+ GP | Armas +3, armaduras +3, artefatos |
> | **Lendário** | 0.1% | 50000+ GP | Artefatos únicos, itens de boss final |
>
> **Nota:** Probabilidades baseadas em D&D 5e Dungeon Master's Guide (Tabela de Tesouro).
>
> **📖 Pseudocódigo:** Ver [Cálculo de Probabilidades de Loot](../../pseudocodigo/probabilidades-loot.md)

</details>

## Probabilidades por Nível do Inimigo

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👹 Ajuste por CR (Challenge Rating)</summary>

> **Multiplicadores por CR:**
>
> | CR do Inimigo | Multiplicador Comum | Multiplicador Incomum | Multiplicador Raro |
> |---------------|---------------------|----------------------|-------------------|
> | CR 0-1/4 (Goblin) | 1.0x (80%) | 0.5x (7.5%) | 0x (0%) |
> | CR 1/2-1 (Orc) | 1.0x (80%) | 1.0x (15%) | 0.5x (2%) |
> | CR 2-4 (Bugbear) | 1.0x (80%) | 1.0x (15%) | 1.0x (4%) |
> | CR 5-7 (Boss) | 0.8x (64%) | 1.2x (18%) | 1.5x (6%) |
> | CR 8+ (Boss Final) | 0.5x (40%) | 1.5x (22.5%) | 2.0x (8%) |
>
> **Exemplo:**
>
> - **Goblin (CR 1/4):** 80% comum, 7.5% incomum, 0% raro
> - **Bugbear (CR 1):** 80% comum, 15% incomum, 2% raro
> - **Nezznar (CR 2):** 80% comum, 15% incomum, 4% raro
> - **Green Dragon (CR 8):** 40% comum, 22.5% incomum, 8% raro

</details>

## Tabela de Loot por Tipo de Inimigo

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎲 Loot Específico da Campanha</summary>

> **Humanóides (Goblin, Orc, Redbrand):**
>
> | Item | Raridade | Probabilidade | Valor (GP) |
> |------|----------|---------------|------------|
> | Moedas (CP/SP) | Comum | 60-80% | 0.1-5 GP |
> | Arma Básica | Comum | 70% | 5-25 GP |
> | Armadura Básica | Comum | 30% | 5-10 GP |
> | Poção de Cura | Incomum | 5% | 50 GP |
> | Item Mágico +1 | Raro | 1% | 500 GP |
>
> **Mortos-Vivos (Skeleton, Zombie, Ghoul):**
>
> | Item | Raridade | Probabilidade | Valor (GP) |
> |------|----------|---------------|------------|
> | Moedas (CP/SP) | Comum | 40-60% | 0.1-2 GP |
> | Arma Antiga | Comum | 50% | 3-15 GP |
> | Gemas | Incomum | 10% | 10-50 GP |
> | Item Mágico | Raro | 2% | 500 GP |
>
> **Bosses (Klarg, Glasstaff, Nezznar):**
>
> | Item | Raridade | Probabilidade | Valor (GP) |
> |------|----------|---------------|------------|
> | Moedas (GP) | Comum | 100% | 10-100 GP |
> | Arma Mágica +1 | Incomum | 50% | 500 GP |
> | Armadura Mágica +1 | Incomum | 30% | 500 GP |
> | Item Mágico Raro | Raro | 20% | 5000 GP |
> | Artefato | Muito Raro | 5% | 50000 GP |

</details>

## Tabela de Loot por Masmorra

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏔️ Tesouros de Masmorras</summary>

> **Cragmaw Hideout (Nível 1):**
>
> - **Tesouro de Klarg:** 100-200 GP + item incomum (50% chance)
> - **Baús:** 2-3 baús com 10-50 GP cada
> - **Total médio:** ~200 GP
>
> **Redbrand Hideout (Nível 2):**
>
> - **Tesouro de Glasstaff:** 150-300 GP + item incomum (70% chance)
> - **Baús:** 3-4 baús com 25-75 GP cada
> - **Total médio:** ~400 GP
>
> **Wave Echo Cave (Nível 4-5):**
>
> - **Tesouro Final:** 500-1000 GP + item raro (100% chance)
> - **Baús:** 5-8 baús com 50-200 GP cada
> - **Total médio:** ~1200 GP

</details>

## Probabilidades de Drop de Moedas

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💰 Sistema de Moedas</summary>

> **Conversão D&D 5e:**
>
> - 1 GP (Gold Piece) = 10 SP (Silver Piece) = 100 CP (Copper Piece)
>
> **Loot de Moedas por Inimigo:**
>
> | Inimigo | Moedas | Valor Médio (GP) | Probabilidade |
> |---------|--------|------------------|---------------|
> | Goblin | 1d6 CP | 0.035 GP | 60% |
> | Orc | 1d10 SP | 0.55 GP | 70% |
> | Bugbear | 1d10 SP | 0.55 GP | 80% |
> | Redbrand | 1d4 SP | 0.25 GP | 75% |
> | Skeleton | 1d6 CP | 0.035 GP | 40% |
> | Zombie | 1d6 CP | 0.035 GP | 30% |
> | Ghoul | 1d4 SP | 0.25 GP | 50% |
> | Doppelganger | 2d6 GP | 7 GP | 100% |
> | Boss (Klarg/Glasstaff) | 3d6 GP | 10.5 GP | 100% |
> | Nezznar (Final) | 5d10 GP | 27.5 GP | 100% |
>
> **Cálculo por Encontro:**
>
> - Encontro fácil (4 goblins): 4 × 0.035 × 0.6 = **0.084 GP**
> - Encontro médio (2 orcs): 2 × 0.55 × 0.7 = **0.77 GP**
> - Encontro difícil (1 bugbear + 4 goblins): 1 × 0.55 × 0.8 + 4 × 0.035 × 0.6 = **0.644 GP**
> - Boss: **7-27.5 GP**

</details>

## Implementação Técnica

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💻 Data Tables e Sistema</summary>

> **Estrutura de Dados:**
>
> O sistema utiliza tabelas de dados para configurar probabilidades de loot, valores de itens e tesouros de masmorras. Valores devem ser configuráveis para facilitar balanceamento.
>
> **📖 Pseudocódigo de Regras:** Ver [Sistema Completo de Roll de Loot](../../02-mecanicas/pseudocodigo/sistema-loot.md)
>
> **📖 Especificações Técnicas (Data Tables):** Ver [Loot Tables Implementation (TDD)](../../../02%20-%20TDD/08-pseudocodigo/economia/loot-tables.md)

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Tabelas de loot baseadas em D&D 5e |
| v1.1 | 2024-12-27 | Adicionado pseudocódigo para cálculo de probabilidades e sistema de roll de loot |

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima: Monetização](monetizacao.md)
