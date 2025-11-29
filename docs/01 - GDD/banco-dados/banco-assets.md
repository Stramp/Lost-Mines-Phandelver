# Banco de Dados: Assets (Arte, Som e Scripts)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este banco de dados lista todos os assets necessários para o projeto, incluindo arte, som e scripts. Organiza por tipo, status, prioridade e dependências.

</details>

---

## 📋 Estrutura da Tabela

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Colunas do Banco de Dados</b></summary>

> | Coluna | Tipo | Descrição |
> |--------|------|-----------|
> | **Nome do Asset** | Texto | Nome descritivo do asset |
> | **Tipo** | Select | Arte / Som / Script / UI |
> | **Categoria** | Select | Personagem / Inimigo / Ambiente / UI / SFX / Música / etc. |
> | **Status** | Select | Não Iniciado / Em Produção / Pronto / Bloqueado |
> | **Prioridade** | Select | Alta / Média / Baixa |
> | **Dependências** | Texto | Assets ou mecânicas que devem estar prontos antes |
> | **Especificações Técnicas** | Texto | Polycount, resolução, formato, etc. |
> | **Responsável** | Texto | Pessoa/equipe responsável |
> | **Notas** | Texto | Observações e considerações |

</details>

---

## 🎨 Assets de Arte - Personagens

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Modelos 3D de Personagens</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Modelo Base - Humano | Arte | Personagem | 📝 Não Iniciado | Alta | Polycount: ~5000 | - |
> | Modelo Base - Elfo | Arte | Personagem | 📝 Não Iniciado | Alta | Polycount: ~5000 | Modelo Base Humano |
> | Modelo Base - Anão | Arte | Personagem | 📝 Não Iniciado | Alta | Polycount: ~5000 | Modelo Base Humano |
> | Modelo Base - Halfling | Arte | Personagem | 📝 Não Iniciado | Média | Polycount: ~4000 | Modelo Base Humano |
> | Modelo Base - Tiefling | Arte | Personagem | 📝 Não Iniciado | Média | Polycount: ~5000 | Modelo Base Humano |
> | Animações - Movimento | Arte | Personagem | 📝 Não Iniciado | Alta | Walk, Run, Idle | Modelos Base |
> | Animações - Combate | Arte | Personagem | 📝 Não Iniciado | Alta | Attack, Block, Dodge | Modelos Base |
> | Animações - Interação | Arte | Personagem | 📝 Não Iniciado | Média | Talk, Pickup, Use | Modelos Base |

</details>

---

## 👹 Assets de Arte - Inimigos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🐉 Modelos 3D de Inimigos (Campanha Phandelver)</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Goblin | Arte | Inimigo | 📝 Não Iniciado | Alta | Polycount: ~2000 | - |
> | Bugbear | Arte | Inimigo | 📝 Não Iniciado | Alta | Polycount: ~3000 | - |
> | Orc | Arte | Inimigo | 📝 Não Iniciado | Alta | Polycount: ~3000 | - |
> | Hobgoblin | Arte | Inimigo | 📝 Não Iniciado | Média | Polycount: ~3000 | - |
> | Worg | Arte | Inimigo | 📝 Não Iniciado | Média | Polycount: ~4000 | - |
> | Animações - Inimigos | Arte | Inimigo | 📝 Não Iniciado | Alta | Attack, Patrol, Alert | Modelos Inimigos |

</details>

---

## 🏛️ Assets de Arte - Ambiente

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌍 Cenários e Locais</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Phandalin (Vila) | Arte | Ambiente | 📝 Não Iniciado | Alta | Modular buildings | - |
> | Cragmaw Hideout | Arte | Ambiente | 📝 Não Iniciado | Alta | Dungeon tileset | - |
> | Redbrand Hideout | Arte | Ambiente | 📝 Não Iniciado | Alta | Dungeon tileset | Cragmaw Hideout |
> | Wave Echo Cave | Arte | Ambiente | 📝 Não Iniciado | Alta | Dungeon tileset | Redbrand Hideout |
> | Texturas e Materiais (PBR) | Arte | Ambiente | 📝 Não Iniciado | Alta | 2K/4K resolution | - |
> | Props (Baús, Portas, etc.) | Arte | Ambiente | 📝 Não Iniciado | Média | Modular props | - |

</details>

---

## 🛡️ Assets de Arte - Equipamentos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Armas e Armaduras</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Armas Melee (Espadas, Machados, etc.) | Arte | Equipamento | 📝 Não Iniciado | Alta | Polycount: ~500-1000 | - |
> | Armas Ranged (Arcos, Bestas) | Arte | Equipamento | 📝 Não Iniciado | Alta | Polycount: ~500-1000 | - |
> | Armaduras (Light, Medium, Heavy) | Arte | Equipamento | 📝 Não Iniciado | Alta | Polycount: ~2000-3000 | Modelos Personagem |
> | Shields | Arte | Equipamento | 📝 Não Iniciado | Média | Polycount: ~500 | - |
> | Itens Mágicos (Visuais) | Arte | Equipamento | 📝 Não Iniciado | Média | VFX particles | Sistema de Itens |

</details>

---

## 🎨 Assets de Arte - UI

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🖥️ Interface de Usuário</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Ícones de Habilidades | Arte | UI | 📝 Não Iniciado | Alta | 64x64, 128x128 | - |
> | Ícones de Itens | Arte | UI | 📝 Não Iniciado | Alta | 64x64, 128x128 | - |
> | Ícones de Status | Arte | UI | 📝 Não Iniciado | Média | 32x32, 64x64 | - |
> | UI Art (Menus, HUD) | Arte | UI | 📝 Não Iniciado | Alta | Style guide definido | Wireframes |
> | Fontes Customizadas | Arte | UI | 📝 Não Iniciado | Média | TTF/OTF | - |

</details>

---

## ✨ Assets de Arte - Efeitos Visuais (VFX)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌟 Partículas e Efeitos</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | VFX - Magias (Fireball, Magic Missile, etc.) | Arte | VFX | 📝 Não Iniciado | Alta | Particle systems | Sistema de Spellcasting |
> | VFX - Combate (Impactos, Sangue) | Arte | VFX | 📝 Não Iniciado | Média | Particle systems | Sistema de Combate |
> | VFX - Ambiente (Fumaça, Fogo, Água) | Arte | VFX | 📝 Não Iniciado | Baixa | Particle systems | - |
> | VFX - UI (Feedback Visual) | Arte | VFX | 📝 Não Iniciado | Média | Particle systems | UI Implementada |

</details>

---

## 🔊 Assets de Áudio - SFX

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔊 Efeitos Sonoros</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | SFX - Combate (Ataques, Dano) | Som | SFX | 📝 Não Iniciado | Alta | WAV/OGG, 44.1kHz | Sistema de Combate |
> | SFX - Magias | Som | SFX | 📝 Não Iniciado | Alta | WAV/OGG, 44.1kHz | Sistema de Spellcasting |
> | SFX - Interação (Portas, Baús) | Som | SFX | 📝 Não Iniciado | Média | WAV/OGG, 44.1kHz | Sistema de Interação |
> | SFX - Ambiente (Passos, Vento) | Som | SFX | 📝 Não Iniciado | Média | WAV/OGG, 44.1kHz | - |
> | SFX - UI (Cliques, Notificações) | Som | SFX | 📝 Não Iniciado | Média | WAV/OGG, 44.1kHz | UI Implementada |

</details>

---

## 🎵 Assets de Áudio - Música

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎼 Trilhas Sonoras</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Música - Exploração | Som | Música | 📝 Não Iniciado | Alta | OGG/MP3, loops | - |
> | Música - Combate | Som | Música | 📝 Não Iniciado | Alta | OGG/MP3, loops | - |
> | Música - Masmorras | Som | Música | 📝 Não Iniciado | Média | OGG/MP3, loops | - |
> | Música - Tensão | Som | Música | 📝 Não Iniciado | Média | OGG/MP3, loops | - |
> | Música - Menu Principal | Som | Música | 📝 Não Iniciado | Baixa | OGG/MP3, loops | - |

</details>

---

## 💻 Assets de Scripts/Código

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Scripts e Ferramentas</b></summary>

> | Asset | Tipo | Categoria | Status | Prioridade | Especificações | Dependências |
> |-------|------|-----------|--------|------------|----------------|--------------|
> | Editor de Diálogo (Tool) | Script | Tool | 📝 Conceito | Média | Unreal Editor Tool | Sistema de Diálogo |
> | Editor de Quests (Tool) | Script | Tool | 📝 Conceito | Média | Unreal Editor Tool | Sistema de Quests |
> | Balanceador de Loot (Tool) | Script | Tool | 📝 Conceito | Baixa | Unreal Editor Tool | Sistema de Loot |
> | Scripts de IA (FSM) | Script | Gameplay | 📝 Conceito | Alta | C++/Blueprint | Sistema de IA |
> | Scripts de Combate | Script | Gameplay | 📝 Conceito | Alta | C++/Blueprint | Sistema de Combate |

</details>

---

## 📊 Estatísticas do Banco

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Resumo</b></summary>

> **Total de Assets:** ~60+
>
> **Por Tipo:**
>
> - Arte: ~40
> - Som: ~15
> - Script: ~5
>
> **Por Status:**
>
> - 📝 Não Iniciado: ~60+
> - 🔄 Em Produção: 0
> - ✅ Pronto: 0
>
> **Por Prioridade:**
>
> - Alta: ~30
> - Média: ~20
> - Baixa: ~10

</details>

---

## 🔗 Referências aos Data Tables (TDD)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Mapeamento Assets ↔ Data Tables</b></summary>

> Alguns assets se relacionam diretamente com Data Tables técnicos. Esta seção mapeia essas relações para facilitar rastreabilidade.
>
> **Assets de Personagens:**
>
> - Modelos de Raças → [RaceDataTable](../../../../Content/Data/DataTable/RaceDataTable.json)
> - Modelos de Classes → [ClassDataTable](../../../../Content/Data/DataTable/ClassDataTable%20copy.json)
> - Animações de Features → [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json)
>
> **Assets de Itens:**
>
> - Modelos de Armas/Armaduras → [ItemDataTable](../../../../Content/Data/DataTable/ItemDataTable%20copy.json)
> - Ícones de Itens (UI) → [ItemDataTable](../../../../Content/Data/DataTable/ItemDataTable%20copy.json)
>
> **Assets de Magias:**
>
> - VFX de Magias → [SpellDataTable](../../../../Content/Data/DataTable/SpellDataTable%20copy.json)
> - Ícones de Magias (UI) → [SpellDataTable](../../../../Content/Data/DataTable/SpellDataTable%20copy.json)
> - VFX por Escola de Magia → [SpellSchoolDataTable](../../../../Content/Data/DataTable/SpellSchoolDataTable%20copy.json)
>
> **Assets de Combate:**
>
> - VFX de Condições → [ConditionDataTable](../../../../Content/Data/DataTable/ConditionDataTable.json)
> - VFX de Tipos de Dano → [DamageTypeDataTable](../../../../Content/Data/DataTable/DamageTypeDataTable.json)
>
> **📖 Documentação Técnica:**
>
> - [Regras D&D 5e (TDD)](../../../03%20-%20TDD/dnd-rules/index.md) - Documentação algorítmica
> - [Banco de Mecânicas](banco-mecanicas.md) - Mecânicas com referências aos Data Tables

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [Dashboard GDD](../dashboard-template.md)
> - [Banco de Mecânicas](banco-mecanicas.md)
> - [Banco de Lore & Mundo](banco-lore-mundo.md)
> - [Lista de Assets de Áudio](../08-audio/lista-assets.md)

</details>

---

**Última atualização:** 2024-12-27
**Próxima revisão:** Após definir style guide e priorizar assets para MVP
