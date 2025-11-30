# 2.5. Sistema de Inventário

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎒 Sistema de Inventário</b></summary>

> Sistema completo de gerenciamento de inventário seguindo regras D&D 5e. Capacidade de carga, organização, itens consumíveis e sistema de moedas.

</details>

---

## 📦 Capacidade de Carga (Carrying Capacity)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Sistema de Peso</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Capacidade de Carga:**
>
> ```
> Carrying Capacity = STR Score × 15 libras (lbs)
> ```
>
> **Tabela de Referência:**
>
> | STR Score | Capacidade (lbs) | Capacidade (kg) |
> |-----------|------------------|-----------------|
> | 8         | 120 lbs          | 54 kg           |
> | 10        | 150 lbs          | 68 kg           |
> | 12        | 180 lbs          | 82 kg           |
> | 14        | 210 lbs          | 95 kg           |
> | 16        | 240 lbs          | 109 kg          |
> | 18        | 270 lbs          | 122 kg          |
> | 20        | 300 lbs          | 136 kg          |
>
> **Encumbrance (Sobrecarga):**
>
> - **Sem sobrecarga:** Peso ≤ Capacidade de Carga
> - **Encumbered (Sobrecarregado):** Peso > Capacidade de Carga
>   - Velocidade reduzida em 3m (10 pés)
> - **Heavily Encumbered (Muito Sobrecarregado):** Peso > 2× Capacidade de Carga
>   - Velocidade reduzida em 6m (20 pés)
>   - Desvantagem em testes de Força, Destreza e Constituição
>
> **Exemplo (Fighter STR 16):**
>
> - **Capacidade:** 16 × 15 = **240 lbs**
> - **Peso Atual:** Chain Mail (55 lbs) + Espada Longa (3 lbs) + Escudo (6 lbs) + Itens (50 lbs) = **114 lbs**
> - **Status:** Sem sobrecarga (114 < 240)
> - **Se adicionar 150 lbs:** 264 lbs > 240 → **Encumbered** (velocidade -3m)
> - **Se adicionar 400 lbs:** 514 lbs > 480 → **Heavily Encumbered** (velocidade -6m, desvantagem)

</details>

---

## 💰 Sistema de Moedas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🪙 Moedas D&D 5e</b></summary>

> **Conversão de Moedas:**
>
> - **1 GP (Gold Piece)** = 10 SP (Silver Piece)
> - **1 SP (Silver Piece)** = 10 CP (Copper Piece)
> - **1 GP** = 100 CP
>
> **Peso das Moedas:**
>
> - **50 moedas** = 1 lb (0.45 kg)
> - **1 moeda** = 0.02 lbs (9 gramas)
>
> **Exemplo de Cálculo:**
>
> - **100 GP:** Peso = 100 / 50 = **2 lbs**
> - **500 SP:** Peso = 500 / 50 = **10 lbs**
> - **1000 CP:** Peso = 1000 / 50 = **20 lbs**
>
> **Valores Típicos na Campanha:**
>
> - **Goblin:** 1d6 CP (0.01-0.06 GP)
> - **Orc:** 1d10 SP (0.1-1 GP)
> - **Bugbear:** 1d10 SP (0.1-1 GP)
> - **Boss (Klarg):** 3d6 GP (3-18 GP)
> - **Boss Final (Nezznar):** 5d10 GP (5-50 GP)

</details>

---

## 📋 Organização do Inventário

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗂️ Categorias de Itens</b></summary>

> **Categorias:**
>
> 1. **Armas:** Armas corpo a corpo e à distância
> 2. **Armaduras:** Armaduras, escudos, roupas
> 3. **Itens Mágicos:** Armas, armaduras e itens mágicos
> 4. **Consumíveis:** Poções, pergaminhos, itens de uso único
> 5. **Ferramentas:** Ferramentas de artesão, kits, instrumentos
> 6. **Material:** Componentes de magia, materiais de crafting
> 7. **Moedas:** GP, SP, CP
> 8. **Miscelânea:** Itens diversos, chaves, documentos
>
> **Slots de Equipamento:**
>
> - **Mão Principal:** 1 arma corpo a corpo OU 1 arma à distância
> - **Mão Secundária:** 1 arma leve OU 1 escudo OU vazio
> - **Corpo:** 1 armadura
> - **Acessórios:** 2 anéis, 1 amuleto, 1 capa (se aplicável)
>
> **Inventário Geral:**
>
> - **Slots:** 30 slots padrão (pode ser expandido com mochilas)
> - **Peso Total:** Soma de todos os itens (incluindo equipados)
> - **Organização:** Jogador pode organizar manualmente ou por categoria

</details>

---

## 🧪 Itens Consumíveis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚗️ Poções e Consumíveis</b></summary>

> **Poções de Cura:**
>
> | Poção | Cura | Peso | Custo | Raridade |
> |-------|------|------|-------|----------|
> | Poção de Cura | 2d4+2 HP | 0.5 lb | 50 GP | Comum |
> | Poção de Cura Maior | 4d4+4 HP | 0.5 lb | 100 GP | Incomum |
> | Poção de Cura Superior | 8d4+8 HP | 0.5 lb | 500 GP | Raro |
>
> **Pergaminhos de Magia:**
>
> | Pergaminho | Magia | Nível | Peso | Custo | Raridade |
> |------------|-------|-------|------|-------|----------|
> | Magic Missile | Magic Missile | 1 | 0.1 lb | 50 GP | Comum |
> | Fireball | Fireball | 3 | 0.1 lb | 500 GP | Raro |
> | Cure Wounds | Cure Wounds | 1 | 0.1 lb | 50 GP | Comum |
>
> **Outros Consumíveis:**
>
> | Item | Efeito | Peso | Custo |
> |------|--------|------|-------|
> | Antitoxina | Vantagem em saves contra veneno (1 hora) | 0.1 lb | 50 GP |
> | Kit de Cura | Cura 1 HP (usa ação) | 1 lb | 5 GP |
> | Ração | Alimenta por 1 dia | 2 lb | 5 SP |
> | Água | Necessária para sobrevivência | 1 lb | 1 CP |

</details>

---

## 💡 Exemplos Práticos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Cenários da Campanha</b></summary>

> **Exemplo 1: Fighter Gerencia Inventário**
>
> **Situação:** Fighter nível 1 (STR 16) precisa carregar equipamentos para masmorra.
>
> **Inventário:**
>
> - Chain Mail: 55 lbs
> - Espada Longa: 3 lbs
> - Escudo: 6 lbs
> - Arco Curto: 2 lbs
> - 20 Flechas: 1 lb
> - Kit de Aventura: 30 lbs
> - 50 GP: 1 lb
> - 3 Poções de Cura: 1.5 lbs
> - **Total:** 99.5 lbs
> - **Capacidade:** 240 lbs
> - **Status:** Sem sobrecarga (99.5 < 240)
>
> **Resultado:** Fighter pode carregar mais itens sem problemas.
>
> **Exemplo 2: Rogue Encontra Tesouro**
>
> **Situação:** Rogue nível 2 (STR 8) encontra 200 GP em baú.
>
> **Cálculo:**
>
> - **200 GP:** Peso = 200 / 50 = 4 lbs
> - **Capacidade Rogue:** 8 × 15 = 120 lbs
> - **Peso Atual:** 30 lbs (equipamentos leves)
> - **Novo Total:** 34 lbs
> - **Status:** Sem sobrecarga (34 < 120)
>
> **Resultado:** Rogue pode carregar o tesouro sem problemas.
>
> **Exemplo 3: Uso de Poção em Combate**
>
> **Situação:** Fighter está com 5/25 HP em combate. Usa Poção de Cura.
>
> **Execução:**
>
> 1. Fighter abre inventário (ação bônus ou ação, dependendo da implementação)
> 2. Seleciona Poção de Cura
> 3. Usa poção (ação)
> 4. **Cura:** 2d4+2 = 4-10 HP recuperados
> 5. Rola 2d4 = 6, total **8 HP recuperados**
> 6. **HP Final:** 5 + 8 = **13/25 HP**
> 7. Poção é consumida (removida do inventário)
>
> **Resultado:** Fighter recupera HP suficiente para continuar lutando.

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Sistema de Equipamentos](equipamentos.md)
> - [→ Próxima: Sistema de Equipamentos](equipamentos.md) | [→ Próxima: Controles e Inputs](controles-inputs.md)
> **🔗 Implementação Técnica (TDD):**
>
> Para detalhes de implementação técnica, consulte:
>
> - **[TDD: UI Components - Inventory Widget](../../02%20-%20TDD/02-api/componentes/ui/inventory-widget.md)** - Widget de inventário
> - **[TDD: Data Tables](../../02%20-%20TDD/05-guias/data-tables/index.md)** - Data Tables de itens
>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistema de inventário baseado em D&D 5e |

**Última atualização:** 2024-12-27
