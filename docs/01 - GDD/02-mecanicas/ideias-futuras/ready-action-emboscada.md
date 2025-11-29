# Ready Action + Sistema de Surprise (Emboscadas Coordenadas)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Ideia em Consideração</b></summary>

> **Status:** 🟡 Em Consideração
>
> **Relacionado:**
>
> - [Sistema de Combate](../sistema-combate.md)
> - Sistema de Surprise (a ser implementado)
>
> **Descrição:** Mecânica de "Ready Action" adaptada para funcionar apenas no início do combate, alinhada com sistema de Surprise e emboscadas coordenadas.

</details>

---

## 🎯 Conceito Principal

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 A Ideia</b></summary>

> **Ready Action** não seria uma ação genérica em tempo real, mas sim uma mecânica específica para:
>
> - **Início do Combate:** Apenas quando combate começa (com ou sem Surprise)
> - **Emboscadas Coordenadas:** Permite que grupo prepare ações coordenadas
> - **Estratégia Tática:** Adiciona camada de planejamento antes do combate em tempo real começar
>
> **Por que isso faz sentido:**
>
> - Em tempo real, "Ready Action" genérico seria difícil de implementar bem
> - Mas no início do combate, há um momento de "setup" onde isso faz sentido
> - Alinha com sistema de Surprise (D&D 5e tem Surprise Round)
> - Permite gameplay mais tático e estratégico

</details>

---

## ⚔️ Como Funcionaria

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Mecânica Proposta</b></summary>

> **Fase de Preparação (Início do Combate):**
>
> 1. **Combate é Iniciado:**
>    - Surprise Round (se aplicável)
>    - Ou Round Normal
>
> 2. **Fase de "Ready Action" (Opcional):**
>    - Jogador pode escolher preparar uma ação
>    - Define trigger (ex: "quando inimigo X se mover", "quando aliado Y atacar")
>    - Ação é executada automaticamente quando trigger acontece
>    - **Limitação:** Apenas no primeiro round do combate
>
> 3. **Combate em Tempo Real Começa:**
>    - Após Ready Actions serem configuradas (ou não)
>    - Combate segue normalmente em tempo real
>
> **Exemplos de Uso:**
>
> - **Emboscada Coordenada:** "Quando o Rogue atacar, eu também ataco o mesmo alvo"
> - **Proteção:** "Quando inimigo se aproximar do Clérigo, eu ataco"
> - **Combo:** "Quando Fighter usar Action Surge, eu uso Help para dar vantagem"
>
> **❓ Decisões Pendentes:**
>
> - Ready Action funciona apenas no primeiro round?
> - Quantas Ready Actions por personagem?
> - Ready Action consome Action do primeiro round?
> - Como mostrar visualmente (UI de preparação)?

</details>

---

## ✅ Prós e Contras

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Análise</b></summary>

> **✅ Prós:**
>
> - Adiciona camada tática interessante
> - Alinha com sistema de Surprise (D&D 5e)
> - Permite combos coordenados entre membros do grupo
> - Não interfere no combate em tempo real (apenas no início)
> - Faz sentido narrativamente (preparar emboscada)
>
> **❌ Contras:**
>
> - Adiciona complexidade ao sistema
> - Pode ser confuso para jogadores novos
> - Requer UI adicional para configurar triggers
> - Pode ser difícil balancear (muito poderoso ou muito fraco)
> - Pode não ser necessário se combate em tempo real já for satisfatório
>
> **🤔 Considerações:**
>
> - Se implementar Surprise, Ready Action faz muito sentido
> - Se não implementar Surprise, Ready Action perde parte do propósito
> - Pode ser opcional (ativar/desativar nas opções)
> - Pode ser simplificado (apenas "atacar quando combate começar")

</details>

---

## 🔗 Integração com Outros Sistemas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Dependências</b></summary>

> **Sistemas Necessários:**
>
> - **Sistema de Surprise:** Para funcionar bem, precisa de Surprise Round
> - **Sistema de Triggers:** Para detectar quando condições são atendidas
> - **UI de Preparação:** Interface para configurar Ready Actions
>
> **Sistemas Relacionados:**
>
> - Sistema de Combate (base)
> - Sistema de Iniciativa (se implementar)
> - Sistema de Coordenação (se multiplayer)

</details>

---

## 📝 Notas de Design

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💭 Observações</b></summary>

> **Inspirações:**
>
> - D&D 5e Surprise Round + Ready Action
> - XCOM: Enemy Unknown (preparar emboscadas)
> - Divinity: Original Sin (combos coordenados)
>
> **Alternativas Simples:**
>
> - Se muito complexo, pode ser simplificado para "atacar automaticamente quando combate começa"
> - Ou apenas para Surprise Round (se grupo surpreender inimigos)
> - Ou remover completamente se não adicionar valor suficiente

</details>

---

## 🎯 Próximos Passos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Ações</b></summary>

> **Para Avaliar:**
>
> - [ ] Implementar sistema de Surprise primeiro
> - [ ] Testar se combate em tempo real precisa dessa mecânica
> - [ ] Prototipar UI de preparação
> - [ ] Playtest com e sem Ready Action
> - [ ] Decidir se vale a complexidade adicional
>
> **Status Atual:**
>
> - **2024-12-27:** Ideia documentada, aguardando decisão sobre sistema de Surprise

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice de Ideias Futuras](index.md)
> - [Sistema de Combate](../sistema-combate.md)
> - [Dashboard GDD](../../dashboard-template.md)

</details>

---

**Última atualização:** 2024-12-27
