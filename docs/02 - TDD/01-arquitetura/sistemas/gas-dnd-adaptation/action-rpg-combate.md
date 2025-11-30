# Action RPG: Colisão Real e Combate

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🎮 Combate em Tempo Real

### Diferenças do RPG de Mesa:

**RPG de Mesa (Turn-Based):**

- Jogadores agem em turnos
- Cada ação é declarada e resolvida antes da próxima
- Tempo é abstrato (rounds, turns)

**Jogo Digital (Action RPG):**

- Combate é em tempo real
- Jogador controla movimento e ataques diretamente
- Colisão física real (não abstrata)

---

## 🔄 Como Adaptar

**1. Ataques:**

- **RPG de Mesa:** "Eu ataco" → Rola d20 → DM diz se acertou
- **Jogo Digital:** Jogador pressiona botão → Sistema verifica se hitbox colidiu → Aplica dano

**2. Saving Throws:**

- **RPG de Mesa:** "Faça saving throw" → Rola d20 → DM diz resultado
- **Jogo Digital:** Sistema detecta efeito → Calcula saving throw automaticamente → Aplica resultado

**3. Áreas de Efeito:**

- **RPG de Mesa:** "Fireball em área de 6 metros" → DM decide quem está na área
- **Jogo Digital:** Sistema detecta colisão física → Aplica efeito em todos os alvos na área

**4. Projéteis:**

- **RPG de Mesa:** "Eu atiro uma flecha" → DM decide se acertou
- **Jogo Digital:** Flecha é objeto físico → Colisão real determina acerto → Aplica dano

**🎯 Vantagem do GAS:**

- Sistema gerencia regras automaticamente
- Colisão física é gerenciada pelo Unreal Engine
- GAS aplica efeitos baseados em regras D&D 5e

---

## 💥 Sistema de Dano e Colisão

### Fluxo de Ataque com Colisão Real:

1. **Jogador:** Pressiona botão de ataque → **GameplayAbility** (ação)
2. **Sistema:** Ativa hitbox de ataque (collision component) → **Unreal Engine** (física)
3. **Sistema:** Detecta colisão com inimigo → **Unreal Engine** (detecção)
4. **Sistema:** Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
   - `d20 + Strength Modifier + Proficiency Bonus vs AC`
5. **Sistema:** Se acertou, calcula dano → **GameplayEffect** (fórmula)
   - `Weapon Damage + Strength Modifier`
6. **Sistema:** Aplica dano no alvo → **AttributeSet** (atualiza HP)
7. **Sistema:** Mostra feedback visual → **GameplayAbility** (feedback)

### Fluxo de Projétil com Colisão Real:

1. **Jogador:** Pressiona botão de tiro → **GameplayAbility** (ação)
2. **Sistema:** Spawna projétil físico → **Unreal Engine** (física)
3. **Sistema:** Projétil voa com física real → **Unreal Engine** (movimento)
4. **Sistema:** Projétil colide com alvo → **Unreal Engine** (colisão)
5. **Sistema:** Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
   - `d20 + Dexterity Modifier + Proficiency Bonus vs AC`
6. **Sistema:** Se acertou, calcula dano → **GameplayEffect** (fórmula)
   - `Weapon Damage + Dexterity Modifier`
7. **Sistema:** Aplica dano no alvo → **AttributeSet** (atualiza HP)

**🎯 Vantagem:**

- Colisão física real (não abstrata)
- Regras D&D 5e são mantidas
- Sistema automatiza cálculos

---

**Navegação:** [← Adaptação de Regras](adaptacao-regras.md) | [→ Condições e Efeitos](condicoes-efeitos.md)

**Última atualização:** 2024-12-27
