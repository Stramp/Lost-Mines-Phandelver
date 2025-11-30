# 2.10. Sistema de Quests

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📜 Sistema de Quests</b></summary>

> Sistema completo de missões seguindo a estrutura da campanha oficial "Minas de Phandelver". Quests principais, secundárias e de facção com rastreamento de progresso e recompensas.

</details>

---

## 📋 Tipos de Quests

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Classificação de Missões</b></summary>

> **Quests Principais:**
>
> - Seguem a narrativa central da campanha
> - Obrigatórias para progressão
> - Exemplos: "Resgatar Gundren", "Derrotar Nezznar"
>
> **Quests Secundárias:**
>
> - Opcionais, enriquecem a narrativa
> - Recompensas adicionais (XP, loot, informação)
> - Exemplos: "Ajudar Phandalin", "Investigar Redbrands"
>
> **Quests de Facção:**
>
> - Relacionadas a facções (Guilda dos Lordes, Harpers, etc.)
> - Desbloqueiam benefícios de facção
> - Exemplos: "Missão da Guilda", "Tarefa dos Harpers"

</details>

---

## 📊 Quests da Campanha Phandelver

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗺️ Lista Completa de Missões</b></summary>

> **Capítulo 1: Goblin Arrows**
>
> - **Quest Principal:** "Resgatar Sildar Hallwinter"
>   - Objetivo: Encontrar e resgatar Sildar em Cragmaw Hideout
>   - Recompensa: 50 GP + informação sobre Phandalin
>   - XP: 100 XP
>
> **Capítulo 2: Phandalin**
>
> - **Quest Principal:** "Encontrar Gundren Busca-Rocha"
>   - Objetivo: Descobrir paradeiro de Gundren
>   - Recompensa: Informação sobre Cragmaw Castle
>   - XP: 200 XP
>
> - **Quest Secundária:** "Investigar Redbrands"
>   - Objetivo: Descobrir esconderijo dos Redbrands
>   - Recompensa: 50 GP + item mágico
>   - XP: 150 XP
>
> **Capítulo 3: Spider's Web**
>
> - **Quest Principal:** "Resgatar Gundren"
>   - Objetivo: Resgatar Gundren de Cragmaw Castle
>   - Recompensa: 200 GP + informação sobre Wave Echo Cave
>   - XP: 300 XP
>
> **Capítulo 4: Wave Echo Cave**
>
> - **Quest Principal:** "Derrotar Nezznar (Black Spider)"
>   - Objetivo: Derrotar Nezznar e recuperar Wave Echo Cave
>   - Recompensa: 500 GP + itens mágicos + conclusão da campanha
>   - XP: 500 XP

</details>

---

## 🎯 Sistema de Rastreamento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Progresso de Quests</b></summary>

> **Estados de Quest:**
>
> - **Não Aceita:** Quest disponível mas não aceita
> - **Ativa:** Quest aceita, em progresso
> - **Completa:** Todos os objetivos concluídos
> - **Falhada:** Quest falhou (opcional, se aplicável)
>
> **Objetivos:**
>
> - Cada quest tem 1 ou mais objetivos
> - Objetivos podem ser sequenciais ou paralelos
> - Progresso é rastreado automaticamente
>
> **Exemplo (Quest "Resgatar Sildar"):**
>
> - **Objetivo 1:** Encontrar Cragmaw Hideout ✅
> - **Objetivo 2:** Derrotar Klarg (boss) ✅
> - **Objetivo 3:** Resgatar Sildar ✅
> - **Status:** Completa
> - **Recompensa:** 50 GP + informação

</details>

---

## 💡 Exemplos Práticos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Quests em Ação</b></summary>

> **Exemplo 1: Aceitar Quest "Resgatar Sildar"**
>
> **Situação:** Grupo encontra Gundren na estrada. Ele oferece quest para resgatar Sildar.
>
> **Execução:**
>
> 1. Gundren explica situação: Sildar foi capturado por goblins
> 2. Grupo aceita quest
> 3. Quest aparece no log: "Resgatar Sildar Hallwinter"
> 4. Objetivos listados: "Encontrar Cragmaw Hideout", "Derrotar Klarg", "Resgatar Sildar"
> 5. Grupo segue para Cragmaw Hideout
>
> **Resultado:** Quest ativa, progresso rastreado automaticamente.
>
> **Exemplo 2: Completar Quest "Investigar Redbrands"**
>
> **Situação:** Grupo completa todos os objetivos da quest secundária.
>
> **Execução:**
>
> 1. **Objetivo 1:** Descobrir esconderijo ✅ (encontrado em Redbrand Hideout)
> 2. **Objetivo 2:** Derrotar Glasstaff ✅ (boss derrotado)
> 3. **Objetivo 3:** Reportar a Harbin Wester ✅ (NPC informado)
> 4. Quest marcada como **Completa**
> 5. Recompensa entregue: 50 GP + item mágico
> 6. XP ganho: 150 XP
>
> **Resultado:** Quest completa, recompensas recebidas, progresso na campanha.

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Sistema de Diálogos](dialogos.md)
> - [→ Próxima: Sistema de Save/Load](save-load.md) | [→ Próxima: Sistema de Equipamentos](equipamentos.md)
> - [📖 Narrativa - Quests](../04-narrativa/capitulos-encontros.md)
> - [📊 Dashboard GDD](../dashboard-template.md)

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistema completo de quests baseado na campanha Phandelver |

**Última atualização:** 2024-12-27
