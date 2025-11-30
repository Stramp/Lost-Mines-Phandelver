# Sistema de Condições e Efeitos

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 💀 Condições D&D 5e

### Condições Implementadas:

**Blinded (Cego):**

- **RPG de Mesa:** "Você não pode ver, falha em checks que requerem visão"
- **Jogo Digital:** Sistema aplica desvantagem automaticamente → **GameplayEffect** (regra)
- **Visual:** Tela escurecida ou efeito visual

**Charmed (Enfeitiçado):**

- **RPG de Mesa:** "Você não pode atacar o encantador"
- **Jogo Digital:** Sistema bloqueia ataques no encantador → **GameplayAbility** (validação)
- **Visual:** Aura ou efeito visual no personagem

**Frightened (Amedrontado):**

- **RPG de Mesa:** "Você tem desvantagem em checks enquanto o causador do medo estiver visível"
- **Jogo Digital:** Sistema aplica desvantagem automaticamente → **GameplayEffect** (regra)
- **Visual:** Personagem treme ou efeito visual

**Poisoned (Envenenado):**

- **RPG de Mesa:** "Você tem desvantagem em todos os checks e ataques"
- **Jogo Digital:** Sistema aplica -1 em todos os checks → **AttributeSet** (modificador)
- **Visual:** Personagem fica verde ou efeito visual

**Stunned (Atordoado):**

- **RPG de Mesa:** "Você está incapacitado, não pode se mover ou agir"
- **Jogo Digital:** Sistema bloqueia ações → **GameplayAbility** (validação)
- **Visual:** Personagem fica parado ou efeito visual

**🎯 Vantagem do GAS:**

- Cada condição é um **GameplayEffect**
- Sistema aplica modificadores automaticamente
- Duração é gerenciada automaticamente
- Pode combinar múltiplas condições

---

## ⚡ Efeitos Temporários

### Buffs (Efeitos Positivos):

**Bull's Strength (Spell):**

- **RPG de Mesa:** "+2 Strength por 1 hora"
- **Jogo Digital:** **GameplayEffect** aplica +2 em Strength → **AttributeSet** (atualiza)
- **Duração:** 1 hora (gerenciada automaticamente)
- **Visual:** Aura ou efeito visual no personagem

**Haste (Spell):**

- **RPG de Mesa:** "Velocidade dobra, +1 ação, +2 AC"
- **Jogo Digital:** **GameplayEffect** aplica modificadores → **AttributeSet** (atualiza)
- **Duração:** 1 minuto (gerenciada automaticamente)
- **Visual:** Personagem fica mais rápido visualmente

### Debuffs (Efeitos Negativos):

**Slow (Spell):**

- **RPG de Mesa:** "Velocidade reduzida, -2 AC, -2 em saving throws"
- **Jogo Digital:** **GameplayEffect** aplica modificadores → **AttributeSet** (atualiza)
- **Duração:** 1 minuto (gerenciada automaticamente)
- **Visual:** Personagem fica mais lento visualmente

**Curse (Maldição):**

- **RPG de Mesa:** "Atributo reduzido permanentemente até remover maldição"
- **Jogo Digital:** **GameplayEffect** aplica modificador permanente → **AttributeSet** (atualiza)
- **Duração:** Até remover (gerenciada por condição)
- **Visual:** Aura escura ou efeito visual

**🎯 Vantagem do GAS:**

- Efeitos são aplicados automaticamente
- Duração é gerenciada automaticamente
- Múltiplos efeitos podem ser combinados
- Sistema notifica quando efeitos expiram

---

**Navegação:** [← Action RPG Combate](action-rpg-combate.md) | [→ Magias e Habilidades](magias-habilidades.md)

**Última atualização:** 2024-12-27
