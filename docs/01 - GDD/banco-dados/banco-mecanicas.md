# Banco de Dados: Mecânicas de Jogo

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este banco de dados lista todas as mecânicas de jogo planejadas para o projeto, incluindo status, prioridade, estimativa e responsável. Mantém rastreabilidade e facilita planejamento.

</details>

---

## 📋 Estrutura da Tabela

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Colunas do Banco de Dados</b></summary>

> | Coluna | Tipo | Descrição |
> |--------|------|-----------|
> | **Nome da Mecânica** | Texto | Nome descritivo da mecânica |
> | **Status** | Select | Conceito / Em Progresso / Implementado / Bloqueado |
> | **Prioridade** | Select | Alta / Média / Baixa |
> | **Data Table** | Link | Referência ao Data Table técnico (TDD) |
> | **Estimativa** | Texto | Tempo estimado (ex: "2 semanas") |
> | **Responsável** | Texto | Pessoa/equipe responsável |
> | **Dependências** | Relação | Mecânicas que devem ser implementadas antes |
> | **Seção GDD** | Link | Link para seção do GDD relacionada |
> | **Notas** | Texto | Observações e considerações |

</details>

---

## 🎮 Mecânicas de Criação de Personagem

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Sistema de Fichas</b></summary>

> | Mecânica | Status | Prioridade | Data Table | Estimativa | Responsável | Seção GDD |
> |----------|--------|------------|------------|-------------|-------------|-----------|
> | Ability Scores (Atributos) | ✅ Implementado | Alta | [AbilityScoreDataTable](../../../../Content/Data/DataTable/AbilityScoreDataTable.json) | - | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Point Buy System | ✅ Implementado | Alta | - | - | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Raças e Sub-raças | ✅ Implementado | Alta | [RaceDataTable](../../../../Content/Data/DataTable/RaceDataTable.json) | - | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Classes e Subclasses | 🔮 Data Table Existe | Alta | [ClassDataTable](../../../../Content/Data/DataTable/ClassDataTable%20copy.json) | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Backgrounds | 🔮 Data Table Existe | Alta | [BackgroundDataTable](../../../../Content/Data/DataTable/BackgroundDataTable%20copy.json) | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Level Up e ASI | 🔮 Planejado | Alta | - | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Multiclassing | ✅ Implementado | Alta | - | - | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Proficiencies | 🔮 Data Table Existe | Alta | [ProficiencyDataTable](../../../../Content/Data/DataTable/ProficiencyDataTable.json) | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Languages | 🔮 Data Table Existe | Média | [LanguageDataTable](../../../../Content/Data/DataTable/LanguageDataTable.json) | 3 dias | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Features de Classe | 🔮 Data Table Existe | Alta | [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json) | 3 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Skills | 🔮 Data Table Existe | Alta | [SkillDataTable](../../../../Content/Data/DataTable/SkillDataTable.json) | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Feats | 🔮 Data Table Existe | Média | [FeatDataTable](../../../../Content/Data/DataTable/FeatDataTable.json) | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Traits | 🔮 Data Table Existe | Baixa | [TraitDataTable](../../../../Content/Data/DataTable/TraitDataTable.json) | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |

</details>

---

## ⚔️ Mecânicas de Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗡️ Sistema de Combate</b></summary>

> | Mecânica | Status | Prioridade | Data Table | Estimativa | Responsável | Seção GDD |
> |----------|--------|------------|------------|-------------|-------------|-----------|
> | Ataques em Tempo Real | 📝 Conceito | Alta | - | 3 semanas | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Cálculo de Dano | 📝 Conceito | Alta | [DamageTypeDataTable](../../../../Content/Data/DataTable/DamageTypeDataTable.json) | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Armor Class (AC) | 📝 Conceito | Alta | - | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Saving Throws | 📝 Conceito | Alta | - | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Condições (Stunned, Paralyzed, etc.) | 🔮 Data Table Existe | Média | [ConditionDataTable](../../../../Content/Data/DataTable/ConditionDataTable.json) | 2 semanas | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Critical Hits | 📝 Conceito | Média | - | 3 dias | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Death Saving Throws | 📝 Conceito | Média | - | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Short Rest | 📝 Conceito | Média | - | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |
> | Long Rest | 📝 Conceito | Média | - | 1 semana | - | [Sistema de Combate](../02-mecanicas/sistema-combate.md) |

</details>

---

## ✨ Mecânicas de Spellcasting

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🧙 Magias e Habilidades</b></summary>

> | Mecânica | Status | Prioridade | Data Table | Estimativa | Responsável | Seção GDD |
> |----------|--------|------------|------------|-------------|-------------|-----------|
> | Spells (Magias) | 🔮 Data Table Existe | Alta | [SpellDataTable](../../../../Content/Data/DataTable/SpellDataTable%20copy.json) | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Schools (Escolas de Magia) | 🔮 Data Table Existe | Alta | [SpellSchoolDataTable](../../../../Content/Data/DataTable/SpellSchoolDataTable%20copy.json) | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Slots | 📝 Conceito | Alta | - | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Preparation | 📝 Conceito | Alta | - | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Cantrips | 📝 Conceito | Alta | - | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Save DC | 📝 Conceito | Alta | - | 3 dias | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Attack Modifier | 📝 Conceito | Alta | - | 3 dias | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Componentes de Magia (V, S, M) | 📝 Conceito | Média | - | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Ritual Casting | 📝 Conceito | Baixa | - | 1 semana | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |
> | Spell Concentration | 📝 Conceito | Média | - | 2 semanas | - | [Sistemas de Personagem](../02-mecanicas/sistemas-personagem.md) |

</details>

---

## 🎒 Mecânicas de Inventário e Equipamentos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Itens e Equipamentos</b></summary>

> | Mecânica | Status | Prioridade | Data Table | Estimativa | Responsável | Seção GDD |
> |----------|--------|------------|------------|-------------|-------------|-----------|
> | Itens (Geral) | 🔮 Data Table Existe | Alta | [ItemDataTable](../../../../Content/Data/DataTable/ItemDataTable%20copy.json) | 2 semanas | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Sistema de Inventário Básico | 📝 Conceito | Alta | - | 2 semanas | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Equipar/Desequipar Itens | 📝 Conceito | Alta | - | 1 semana | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Armas (Melee e Ranged) | 📝 Conceito | Alta | - | 2 semanas | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Armaduras (Light, Medium, Heavy) | 📝 Conceito | Alta | - | 2 semanas | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Shields | 📝 Conceito | Média | - | 3 dias | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Itens Mágicos | 📝 Conceito | Média | - | 3 semanas | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Consumíveis (Poções, etc.) | 📝 Conceito | Média | - | 1 semana | - | [Equipamentos](../02-mecanicas/equipamentos.md) |
> | Carrying Capacity | 📝 Conceito | Baixa | - | 3 dias | - | [Equipamentos](../02-mecanicas/equipamentos.md) |

</details>

---

## 🎮 Mecânicas de Gameplay

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Interação e Exploração</b></summary>

> | Mecânica | Status | Prioridade | Data Table | Estimativa | Responsável | Seção GDD |
> |----------|--------|------------|------------|-------------|-------------|-----------|
> | Movimentação de Personagem | 📝 Conceito | Alta | - | 1 semana | - | [Controles e Inputs](../02-mecanicas/controles-inputs.md) |
> | Câmera Top-Down | 📝 Conceito | Alta | - | 1 semana | - | [Controles e Inputs](../02-mecanicas/controles-inputs.md) |
> | Sistema de Interação (Portas, Baús, NPCs) | 📝 Conceito | Alta | - | 2 semanas | - | [Física e Interação](../02-mecanicas/fisica-interacao.md) |
> | Sistema de Diálogo Básico | 📝 Conceito | Alta | - | 2 semanas | - | [Narrativa](../04-narrativa/personagens.md) |
> | Sistema de Quests | 📝 Conceito | Alta | - | 3 semanas | - | [Narrativa](../04-narrativa/sinopse-plot.md) |
> | Sistema de Save/Load | 📝 Conceito | Alta | - | 2 semanas | - | - |
> | Feedback Visual (Dano Flutuante, Efeitos) | 📝 Conceito | Média | - | 2 semanas | - | [UI/UX](../07-ui-ux/feedback-visual.md) |
> | Feedback Sonoro (SFX) | 📝 Conceito | Média | - | 1 semana | - | [Áudio](../08-audio/lista-assets.md) |

</details>

---

## 📊 Estatísticas do Banco

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Resumo</b></summary>

> **Total de Mecânicas:** ~50+
>
> **Por Status:**
>
> - ✅ Implementado: 4
> - 🔮 Data Table Existe: 12 (estrutura pronta, falta implementação)
> - 🔮 Planejado: 0
> - 📝 Conceito: 34+
>
> **Por Prioridade:**
>
> - Alta: ~30
> - Média: ~15
> - Baixa: ~5
>
> **Data Tables Mapeados:**
>
> - ✅ 12 Data Tables referenciados
> - ⚠️ Alguns Data Tables existem mas mecânica ainda não implementada

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [Dashboard GDD](../dashboard-template.md)
> - [Banco de Assets](banco-assets.md)
> - [Banco de Lore & Mundo](banco-lore-mundo.md)

</details>

---

**Última atualização:** 2024-12-27
**Próxima revisão:** Após completar detalhamento de sistemas core

---

## 🔗 Referências aos Data Tables (TDD)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Mapeamento GDD ↔ TDD</b></summary>

> Este banco de dados agora inclui referências diretas aos Data Tables técnicos (TDD), permitindo rastreabilidade entre design (GDD) e implementação (TDD).
>
> **Data Tables Disponíveis:**
>
> - [AbilityScoreDataTable](../../../../Content/Data/DataTable/AbilityScoreDataTable.json) - Ability Scores
> - [RaceDataTable](../../../../Content/Data/DataTable/RaceDataTable.json) - Raças e Sub-raças
> - [ClassDataTable](../../../../Content/Data/DataTable/ClassDataTable%20copy.json) - Classes e Subclasses
> - [BackgroundDataTable](../../../../Content/Data/DataTable/BackgroundDataTable%20copy.json) - Backgrounds
> - [ProficiencyDataTable](../../../../Content/Data/DataTable/ProficiencyDataTable.json) - Proficiencies
> - [LanguageDataTable](../../../../Content/Data/DataTable/LanguageDataTable.json) - Languages
> - [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json) - Features de Classe
> - [SkillDataTable](../../../../Content/Data/DataTable/SkillDataTable.json) - Skills
> - [FeatDataTable](../../../../Content/Data/DataTable/FeatDataTable.json) - Feats
> - [TraitDataTable](../../../../Content/Data/DataTable/TraitDataTable.json) - Traits
> - [SpellDataTable](../../../../Content/Data/DataTable/SpellDataTable%20copy.json) - Spells
> - [SpellSchoolDataTable](../../../../Content/Data/DataTable/SpellSchoolDataTable%20copy.json) - Escolas de Magia
> - [ItemDataTable](../../../../Content/Data/DataTable/ItemDataTable%20copy.json) - Itens
> - [ConditionDataTable](../../../../Content/Data/DataTable/ConditionDataTable.json) - Condições de Combate
> - [DamageTypeDataTable](../../../../Content/Data/DataTable/DamageTypeDataTable.json) - Tipos de Dano
>
> **📖 Documentação Técnica:**
>
> - [Algoritmos D&D 5e (TDD)](../../../02%20-%20TDD/04-regras-dnd/index.md) - Documentação algorítmica
> - [Arquitetura Técnica](../../../02%20-%20TDD/01-arquitetura/principios/architecture.md) - Como os Data Tables são usados

</details>
