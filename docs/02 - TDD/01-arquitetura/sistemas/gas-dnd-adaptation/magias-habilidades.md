# Magias e Habilidades Especiais

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## ✨ Sistema de Spellcasting

### Spell Slots (GameplayAbility):

**RPG de Mesa:**

- Jogador tem X spell slots por nível
- Usa slot para lançar spell
- Recupera slots em long rest

**Jogo Digital:**

- **AttributeSet** armazena spell slots disponíveis
- **GameplayAbility** valida se tem slot disponível
- **GameplayEffect** consome slot ao lançar
- **GameplayEffect** restaura slots em long rest

---

## 📜 Spell Components (GameplayAbility)

**RPG de Mesa:**

- Verbal (V): Precisa falar
- Somatic (S): Precisa fazer gestos
- Material (M): Precisa de componente material

**Jogo Digital:**

- **GameplayAbility** valida componentes antes de lançar
- **GameplayAbility** verifica se tem material (se necessário)
- **GameplayAbility** bloqueia se componentes não disponíveis

---

## 📈 Spell Levels e Scaling

**RPG de Mesa:**

- Spells têm níveis (1-9)
- Alguns spells podem ser upcast (usar slot maior)
- Dano/efeito aumenta com nível do slot

**Jogo Digital:**

- **GameplayEffect** define nível base do spell
- **GameplayEffect** calcula dano/efeito baseado no slot usado
- **GameplayAbility** permite escolher nível do slot (upcast)

**🎯 Exemplo: Fireball:**

1. **Jogador:** Escolhe spell "Fireball" nível 3 → **GameplayAbility** (ação)
2. **Sistema:** Valida se tem spell slot nível 3 → **GameplayAbility** (validação)
3. **Sistema:** Jogador escolhe área → **GameplayAbility** (targeting)
4. **Sistema:** Aplica "Fireball Effect" nível 3 → **GameplayEffect** (regra)
5. **Sistema:** Calcula dano 8d6 → **GameplayEffect** (fórmula)
6. **Sistema:** Se upcast para nível 4, dano = 9d6 → **GameplayEffect** (scaling)
7. **Sistema:** Aplica dano em todos os alvos na área → **AttributeSet** (atualiza HP)
8. **Sistema:** Consome spell slot → **AttributeSet** (atualiza slots)

---

## ⚔️ Habilidades de Classe

### Action Surge (Fighter):

**RPG de Mesa:**

- "Você ganha uma ação extra neste turno"
- Usa 1x por short rest

**Jogo Digital:**

- **GameplayAbility** valida se está disponível (cooldown)
- **GameplayEffect** aplica "+1 ação extra"
- **AttributeSet** atualiza "ActionsAvailable: 1 → 2"
- **GameplayEffect** aplica cooldown "1x por short rest"

### 😤 Rage (Barbarian):

**RPG de Mesa:**

- "+2 dano em ataques corpo a corpo"
- Resistência a dano físico
- Duração: 1 minuto ou até perder concentração

**Jogo Digital:**

- **GameplayAbility** ativa Rage
- **GameplayEffect** aplica "+2 dano corpo a corpo"
- **GameplayEffect** aplica "50% redução de dano físico"
- **AttributeSet** atualiza modificadores
- **GameplayEffect** gerencia duração (1 minuto ou até perder concentração)

### 🗡️ Sneak Attack (Rogue):

**RPG de Mesa:**

- "Dano extra se tiver vantagem ou aliado próximo ao alvo"
- Dano aumenta com nível (1d6 a cada 2 níveis)

**Jogo Digital:**

- **GameplayAbility** valida condições (vantagem ou aliado próximo)
- **GameplayEffect** calcula dano extra baseado no nível
- **GameplayEffect** aplica dano extra no ataque
- **AttributeSet** atualiza HP do alvo

**🎯 Vantagem do GAS:**

- Cada habilidade é um **GameplayAbility**
- Efeitos são **GameplayEffects** reutilizáveis
- Sistema gerencia cooldowns e custos automaticamente
- Pode combinar múltiplas habilidades

---

**Navegação:** [← Condições e Efeitos](condicoes-efeitos.md) | [→ Multiplayer](multiplayer.md)

**Última atualização:** 2024-12-27
