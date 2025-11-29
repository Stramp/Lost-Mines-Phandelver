# Banco de Dados: Lore & Mundo (Campanha Phandelver)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Visão Geral</b></summary>

> Este banco de dados organiza todo o conteúdo narrativo da campanha oficial D&D 5e "Lost Mine of Phandelver", incluindo personagens, locais, eventos e quests. Mantém a fidelidade à campanha original.

</details>

---

## 📋 Estrutura da Tabela

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Colunas do Banco de Dados</b></summary>

> | Coluna | Tipo | Descrição |
> |--------|------|-----------|
> | **Nome** | Texto | Nome da entidade (Personagem, Local, Evento) |
> | **Tipo** | Select | Personagem / Local / Quest / Evento / Item de Lore |
> | **Categoria** | Select | Principal / Secundário / Ambientação |
> | **Status** | Select | Documentado / Em Progresso / Não Iniciado |
> | **Fonte** | Texto | Referência na campanha oficial (capítulo, página) |
> | **Relacionamentos** | Relação | Outras entidades relacionadas |
> | **Notas** | Texto | Observações e adaptações para o jogo |

</details>

---

## 👥 Personagens - NPCs Principais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎭 Personagens Importantes</b></summary>

> | Personagem | Tipo | Categoria | Status | Fonte | Relacionamentos | Notas |
> |------------|------|-----------|--------|-------|-----------------|-------|
> | Gundren Rockseeker | Personagem | Principal | 📝 Não Iniciado | Cap. 1 | Phandalin, Wave Echo Cave | Anão, irmão de Nundro e Tharden |
> | Sildar Hallwinter | Personagem | Principal | 📝 Não Iniciado | Cap. 1 | Phandalin, Lord's Alliance | Guia de Gundren, capturado |
> | Harbin Wester | Personagem | Principal | 📝 Não Iniciado | Cap. 2 | Phandalin, Redbrands | Prefeito de Phandalin |
> | Iarno Albrek (Glasstaff) | Personagem | Principal | 📝 Não Iniciado | Cap. 2 | Redbrands, Black Spider | Mago, líder dos Redbrands |
> | The Black Spider (Nezznar) | Personagem | Principal | 📝 Não Iniciado | Cap. 4 | Wave Echo Cave, Drow | Antagonista principal |
> | Sister Garaele | Personagem | Secundário | 📝 Não Iniciado | Cap. 2 | Phandalin, Harpers | Clériga, quest giver |
> | Halia Thornton | Personagem | Secundário | 📝 Não Iniciado | Cap. 2 | Phandalin, Zhentarim | Comerciante, quest giver |
> | Daran Edermath | Personagem | Secundário | 📝 Não Iniciado | Cap. 2 | Phandalin | Ex-aventureiro, quest giver |
> | Toblen Stonehill | Personagem | Secundário | 📝 Não Iniciado | Cap. 2 | Phandalin | Dono da taverna |
> | Linene Graywind | Personagem | Secundário | 📝 Não Iniciado | Cap. 2 | Phandalin | Comerciante de equipamentos |

</details>

---

## 🏛️ Locais - Áreas da Campanha

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Locais e Áreas</b></summary>

> | Local | Tipo | Categoria | Status | Fonte | Relacionamentos | Notas |
> |-------|------|-----------|--------|-------|-----------------|-------|
> | Phandalin | Local | Principal | 📝 Não Iniciado | Cap. 2 | Todos os NPCs, Quests | Vila principal da campanha |
> | Cragmaw Hideout | Local | Principal | 📝 Não Iniciado | Cap. 1 | Goblins, Gundren | Primeira masmorra |
> | Cragmaw Castle | Local | Principal | 📝 Não Iniciado | Cap. 3 | Goblins, Grol | Fortaleza dos goblins |
> | Redbrand Hideout | Local | Principal | 📝 Não Iniciado | Cap. 2 | Redbrands, Glasstaff | Masmorra sob Phandalin |
> | Wave Echo Cave | Local | Principal | 📝 Não Iniciado | Cap. 4 | Black Spider, Final | Masmorra final |
> | Old Owl Well | Local | Secundário | 📝 Não Iniciado | Cap. 3 | Hamun Kost, Quest | Ruínas antigas |
> | Ruins of Thundertree | Local | Secundário | 📝 Não Iniciado | Cap. 3 | Reidoth, Quest | Vila destruída |
> | Wyvern Tor | Local | Secundário | 📝 Não Iniciado | Cap. 3 | Orcs, Quest | Acampamento de orcs |
> | Conyberry | Local | Secundário | 📝 Não Iniciado | Cap. 3 | Agatha, Quest | Vila abandonada |

</details>

---

## 📜 Quests - Missões da Campanha

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Quests Principais e Secundárias</b></summary>

> | Quest | Tipo | Categoria | Status | Fonte | Relacionamentos | Notas |
> |-------|------|-----------|--------|-------|-----------------|-------|
> | Find Gundren | Quest | Principal | 📝 Não Iniciado | Cap. 1 | Gundren, Cragmaw Hideout | Quest inicial |
> | Rescue Sildar | Quest | Principal | 📝 Não Iniciado | Cap. 1 | Sildar, Cragmaw Hideout | Parte da quest inicial |
> | Clear Redbrands | Quest | Principal | 📝 Não Iniciado | Cap. 2 | Redbrands, Phandalin | Quest principal de Phandalin |
> | Find Cragmaw Castle | Quest | Principal | 📝 Não Iniciado | Cap. 3 | Gundren, Grol | Continuidade da quest inicial |
> | Wave Echo Cave | Quest | Principal | 📝 Não Iniciado | Cap. 4 | Black Spider, Final | Quest final |
> | Agatha's Locket | Quest | Secundário | 📝 Não Iniciado | Cap. 3 | Sister Garaele, Agatha | Quest de Sister Garaele |
> | Orc Trouble | Quest | Secundário | 📝 Não Iniciado | Cap. 3 | Daran, Wyvern Tor | Quest de Daran |
> | Old Owl Well | Quest | Secundário | 📝 Não Iniciado | Cap. 3 | Hamun Kost | Quest de exploração |
> | Thundertree | Quest | Secundário | 📝 Não Iniciado | Cap. 3 | Reidoth | Quest de Reidoth |
> | Banshee's Bargain | Quest | Secundário | 📝 Não Iniciado | Cap. 3 | Sister Garaele, Agatha | Parte da quest de Agatha |

</details>

---

## 👹 Inimigos - Bestiário da Campanha

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🐉 Criaturas e Inimigos</b></summary>

> | Inimigo | Tipo | Categoria | Status | Fonte | Localização | Notas |
> |---------|------|-----------|--------|-------|-------------|-------|
> | Goblin | Inimigo | Principal | 📝 Não Iniciado | MM | Cragmaw Hideout, Castle | Inimigo comum |
> | Bugbear | Inimigo | Principal | 📝 Não Iniciado | MM | Cragmaw Hideout, Castle | Inimigo médio |
> | Orc | Inimigo | Principal | 📝 Não Iniciado | MM | Wyvern Tor | Inimigo médio |
> | Hobgoblin | Inimigo | Principal | 📝 Não Iniciado | MM | Cragmaw Castle | Inimigo médio |
> | Worg | Inimigo | Principal | 📝 Não Iniciado | MM | Cragmaw Castle | Montaria dos goblins |
> | Redbrand Ruffian | Inimigo | Principal | 📝 Não Iniciado | LMoP | Redbrand Hideout | Bandidos humanos |
> | Nothic | Inimigo | Principal | 📝 Não Iniciado | MM | Redbrand Hideout | Criatura mágica |
> | Flameskull | Inimigo | Principal | 📝 Não Iniciado | MM | Wave Echo Cave | Inimigo mágico |
> | Spectator | Inimigo | Principal | 📝 Não Iniciado | MM | Wave Echo Cave | Guardião mágico |
> | Young Green Dragon (Venomfang) | Inimigo | Principal | 📝 Não Iniciado | MM | Thundertree | Boss opcional |
> | Black Spider (Nezznar) | Inimigo | Principal | 📝 Não Iniciado | LMoP | Wave Echo Cave | Boss final |

</details>

---

## 📖 Itens de Lore - Objetos e Informações

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Itens Narrativos</b></summary>

> | Item | Tipo | Categoria | Status | Fonte | Relacionamentos | Notas |
> |------|------|-----------|--------|-------|-----------------|-------|
> | Carta de Gundren | Item de Lore | Principal | 📝 Não Iniciado | Cap. 1 | Gundren, Quest | Item inicial |
> | Locket de Agatha | Item de Lore | Secundário | 📝 Não Iniciado | Cap. 3 | Sister Garaele, Quest | Item de quest |
> | Forge of Spells | Item de Lore | Principal | 📝 Não Iniciado | Cap. 4 | Wave Echo Cave, Final | Objetivo final |
> | Livros e Documentos | Item de Lore | Ambientação | 📝 Não Iniciado | Vários | Locais diversos | Lore do mundo |

</details>

---

## 🎭 Eventos - Momentos Importantes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Eventos Scriptados</b></summary>

> | Evento | Tipo | Categoria | Status | Fonte | Relacionamentos | Notas |
> |-------|------|-----------|--------|-------|-----------------|-------|
> | Emboscada Inicial | Evento | Principal | 📝 Não Iniciado | Cap. 1 | Goblins, Caminho | Evento de abertura |
> | Chegada em Phandalin | Evento | Principal | 📝 Não Iniciado | Cap. 2 | Phandalin, NPCs | Introdução à vila |
> | Encontro com Redbrands | Evento | Principal | 📝 Não Iniciado | Cap. 2 | Redbrands, Phandalin | Conflito inicial |
> | Descoberta de Gundren | Evento | Principal | 📝 Não Iniciado | Cap. 3 | Gundren, Cragmaw Castle | Revelação |
> | Confronto Final | Evento | Principal | 📝 Não Iniciado | Cap. 4 | Black Spider, Wave Echo Cave | Clímax da campanha |

</details>

---

## 📊 Estatísticas do Banco

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Resumo</b></summary>

> **Total de Entidades:** ~40+
>
> **Por Tipo:**
>
> - Personagens: ~10
> - Locais: ~9
> - Quests: ~10
> - Inimigos: ~12
> - Itens de Lore: ~4
> - Eventos: ~5
>
> **Por Status:**
>
> - 📝 Não Iniciado: ~40+
> - 🔄 Em Progresso: 0
> - ✅ Documentado: 0
>
> **Por Categoria:**
>
> - Principal: ~25
> - Secundário: ~15
> - Ambientação: ~5

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [Dashboard GDD](../dashboard-template.md)
> - [Banco de Mecânicas](banco-mecanicas.md)
> - [Banco de Assets](banco-assets.md)
> - [Narrativa - Sinopse](../04-narrativa/sinopse-plot.md)
> - [Narrativa - Personagens](../04-narrativa/personagens.md)
> - [Bestiário](../03-ia-comportamento/bestiario.md)

</details>

---

**Última atualização:** 2024-12-27
**Fonte Principal:** Lost Mine of Phandelver (D&D 5e Official Campaign)
**Próxima revisão:** Após detalhar narrativa e bestiário no GDD
