# Multiplayer: Sincronização e Autoridade

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🎮 Princípios de Multiplayer no GAS

### Autoridade do Servidor (Server Authority)

**Regra Fundamental:**

- ✅ **Servidor é autoridade:** Todas as decisões importantes acontecem no servidor
- ✅ **Cliente é visualização:** Cliente apenas mostra o que o servidor autoriza
- ✅ **Validação sempre:** Servidor valida todas as ações do cliente
- ❌ **Nunca confiar no cliente:** Cliente pode ser modificado (cheating)

---

## 🔄 Como GAS Gerencia Multiplayer

**1. AttributeSet - Replicação Automática:**

- **Servidor:** Calcula valores (HP, atributos, modificadores)
- **Cliente:** Recebe valores replicados automaticamente
- **Sincronização:** GAS replica automaticamente quando valores mudam
- **Eventos:** Cliente recebe notificações quando valores mudam (OnRep)

**2. GameplayEffect - Aplicação Autoritativa:**

- **Servidor:** Aplica efeitos (dano, buffs, debuffs)
- **Cliente:** Recebe notificação de efeitos aplicados
- **Validação:** Servidor valida se efeito pode ser aplicado
- **Duração:** Servidor gerencia duração de efeitos

**3. GameplayAbility - Execução Autoritativa:**

- **Cliente:** Solicita ação (pressiona botão)
- **Servidor:** Valida e executa ação
- **Resultado:** Servidor aplica resultado e replica para clientes
- **Feedback:** Cliente recebe feedback visual do resultado

**🎯 Vantagem do GAS:**

- Replicação automática de atributos
- Validação automática de ações
- Sincronização de estados garantida
- Prevenção de cheating nativa

---

## ⚔️ Exemplo: Ataque em Multiplayer

### Fluxo Completo:

**1. Cliente (Jogador A):**

- Pressiona botão de ataque → **GameplayAbility** (solicitação)
- Envia RPC para servidor → **Network** (comunicação)

**2. Servidor:**

- Recebe solicitação de ataque → **GameplayAbility** (validação)
- Valida se jogador pode atacar → **GameplayAbility** (autoridade)
- Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
- Lê valores "Strength: 16 (+3), Proficiency: +3" → **AttributeSet** (valores)
- Calcula 12 + 3 + 3 = 18 vs AC 15 → **Acertou!**
- Calcula dano 1d8 + 3 = 8 → **GameplayEffect** (fórmula)
- Aplica dano no alvo → **AttributeSet** (atualiza HP: 10 → 2)

**3. Replicação:**

- Servidor replica HP atualizado → **AttributeSet** (replicação)
- Todos os clientes recebem HP atualizado → **Network** (sincronização)
- Cliente (Jogador B) vê HP mudar → **UI** (feedback visual)

**4. Feedback Visual:**

- Servidor envia feedback de acerto → **GameplayAbility** (notificação)
- Todos os clientes mostram efeito visual → **UI** (feedback)

**🎯 Pontos Importantes:**

- ✅ Cálculo acontece no servidor (autoridade)
- ✅ Cliente apenas solicita ação
- ✅ Todos os clientes veem o mesmo resultado
- ✅ Impossível trapacear (servidor valida tudo)

---

## 🛡️ Prevenção de Cheating

### Como GAS Previne Cheating:

**1. Autoridade do Servidor:**

- ✅ Todas as ações são validadas no servidor
- ✅ Cliente não pode modificar valores diretamente
- ✅ Servidor é a única fonte de verdade

**2. Validação de GameplayAbility:**

- ✅ Servidor valida se ação é permitida
- ✅ Servidor valida se tem recursos (spell slots, ações)
- ✅ Servidor valida se condições são atendidas

**3. Replicação de AttributeSet:**

- ✅ Valores são calculados no servidor
- ✅ Cliente recebe apenas valores replicados
- ✅ Cliente não pode modificar valores diretamente

**4. Validação de GameplayEffect:**

- ✅ Efeitos são aplicados no servidor
- ✅ Servidor valida se efeito pode ser aplicado
- ✅ Duração é gerenciada no servidor

**🎯 Exemplo de Tentativa de Cheating:**

**Cliente tenta:**

- Modificar HP diretamente → **FALHA:** AttributeSet replica do servidor
- Aplicar buff sem custo → **FALHA:** Servidor valida custo
- Usar spell sem slot → **FALHA:** Servidor valida spell slots
- Aplicar dano infinito → **FALHA:** Servidor calcula dano

**Resultado:**

- ✅ Servidor sempre tem autoridade
- ✅ Cliente não pode trapacear
- ✅ Todos os jogadores veem o mesmo resultado

---

**Navegação:** [← Magias e Habilidades](magias-habilidades.md) | [→ Voltar para Índice](index.md)

**Última atualização:** 2024-12-27
