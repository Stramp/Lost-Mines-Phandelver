# 2.11. Sistema de Save/Load

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💾 Sistema de Save/Load</b></summary>

> Sistema completo de salvamento e carregamento de progresso. Múltiplos slots de save, salvamento automático e manual, com pontos de salvamento estratégicos.

</details>

---

## 💾 Tipos de Salvamento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📁 Salvamento Automático e Manual</b></summary>

> **Salvamento Automático:**
>
> - Ocorre automaticamente em pontos específicos
> - Não sobrescreve saves manuais
> - Slots separados (Auto Save 1, Auto Save 2, Auto Save 3)
> - **Pontos de Auto Save:**
>   - Ao entrar em nova área
>   - Ao completar quest
>   - Ao fazer level up
>   - Ao entrar em masmorra
>   - Ao derrotar boss
>
> **Salvamento Manual:**
>
> - Jogador pode salvar a qualquer momento (exceto em combate)
> - Múltiplos slots disponíveis (Save 1-10)
> - Pode nomear saves para identificação
> - **Limitações:**
>   - Não pode salvar durante combate
>   - Não pode salvar durante diálogo
>   - Não pode salvar durante cutscene
>
> **Salvamento Rápido (Quick Save):**
>
> - Slot único de salvamento rápido
>   - Sobrescreve save anterior
>   - Acesso rápido (tecla F5)
>   - Carregamento rápido (tecla F9)

</details>

---

## 📊 Dados Salvos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💾 Informações Armazenadas</b></summary>

> **Dados do Personagem:**
>
> - Nível, classe, raça, background
> - Ability Scores, modificadores
> - HP atual/máximo, Hit Dice
> - Spell Slots usados/disponíveis
> - Skills, proficiencies
> - Features de classe desbloqueadas
>
> **Inventário:**
>
> - Todos os itens no inventário
> - Itens equipados
> - Moedas (GP, SP, CP)
> - Capacidade de carga atual
>
> **Progresso:**
>
> - XP atual
> - Quests ativas/completas
> - NPCs conhecidos, atitudes
> - Áreas desbloqueadas
> - Itens mágicos encontrados
>
> **Localização:**
>
> - Posição do personagem
> - Área atual
> - Estado do mundo (portas abertas, baús saqueados, etc.)

</details>

---

## 💡 Exemplos Práticos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Cenários de Uso</b></summary>

> **Exemplo 1: Salvamento Antes de Boss**
>
> **Situação:** Grupo está prestes a enfrentar Klarg (boss de Cragmaw Hideout).
>
> **Execução:**
>
> 1. Jogador abre menu (ESC)
> 2. Seleciona "Salvar Jogo"
> 3. Escolhe slot "Save 1" ou cria novo save "Antes de Klarg"
> 4. Jogo salva estado atual
> 5. Se grupo morrer, pode carregar este save
>
> **Resultado:** Jogador pode tentar boss múltiplas vezes sem perder progresso.
>
> **Exemplo 2: Auto Save Após Quest**
>
> **Situação:** Grupo completa quest "Resgatar Sildar".
>
> **Execução:**
>
> 1. Quest marcada como completa
> 2. Recompensas entregues
> 3. **Auto Save ativado automaticamente**
> 4. Progresso salvo em "Auto Save 1"
> 5. Jogador pode continuar sem perder progresso
>
> **Resultado:** Progresso protegido automaticamente após marcos importantes.
>
> **Exemplo 3: Carregamento de Save**
>
> **Situação:** Jogador quer voltar a um ponto anterior.
>
> **Execução:**
>
> 1. Jogador abre menu (ESC)
> 2. Seleciona "Carregar Jogo"
> 3. Vê lista de saves disponíveis:
>   - Auto Save 1 (há 10 minutos)
>   - Save 1 "Antes de Klarg" (há 30 minutos)
>   - Save 2 "Phandalin" (há 1 hora)
> 4. Seleciona save desejado
> 5. Jogo carrega estado salvo
>
> **Resultado:** Jogador pode voltar a qualquer ponto salvo anteriormente.

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Sistema de Quests](quests.md)
> - [→ Próxima: Controles e Inputs](controles-inputs.md) | [→ Próxima: Sistema de Equipamentos](equipamentos.md)
> - [📊 Dashboard GDD](../dashboard-template.md)

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistema completo de salvamento e carregamento |

**Última atualização:** 2024-12-27
