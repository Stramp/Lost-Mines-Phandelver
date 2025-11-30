# Fluxos Práticos: Do RPG de Mesa para o Jogo

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🎲 Exemplo 1: Ataque Básico

### **RPG de Mesa:**

1. **Jogador:** "Eu ataco o goblin com minha espada!"
2. **DM:** "Rola d20 para acerto"
3. **Jogador:** Rola d20 = 12
4. **Jogador:** "Meu Strength é 16 (+3) e tenho Proficiency +3, então 12 + 3 + 3 = 18"
5. **DM:** "AC do goblin é 15, você acertou! Rola dano"
6. **Jogador:** Rola 1d8 = 5, "5 + 3 (Strength) = 8 de dano"
7. **DM:** "Goblin perde 8 HP, agora tem 2/10 HP"

### **No Jogo (GAS):**

1. **Jogador:** Pressiona botão de ataque → **GameplayAbility** (ação)
2. **Sistema:** Consulta regra "Ataque = d20 + Strength + Proficiency" → **GameplayEffect** (fórmula)
3. **Sistema:** Lê valores "Strength: 16 (+3), Proficiency: +3" → **AttributeSet** (valores)
4. **Sistema:** Calcula 12 + 3 + 3 = 18 vs AC 15 → **Acertou!**
5. **Sistema:** Aplica regra "Dano = 1d8 + Strength modifier" → **GameplayEffect**
6. **Sistema:** Atualiza "HP do goblin: 10 → 2" → **AttributeSet** (atualiza)

**🎯 Diferença Principal:**

- **RPG de Mesa:** Jogador e DM fazem tudo manualmente
- **Jogo Digital:** Sistema automatiza cálculos, mas segue as mesmas regras

---

## 💀 Exemplo 2: Condição Envenenado

### **RPG de Mesa:**

1. **DM:** "O goblin te acerta com uma adaga envenenada"
2. **DM:** "Faça um saving throw de Constitution"
3. **Jogador:** Rola d20 = 8, "Meu Constitution é 14 (+2), então 8 + 2 = 10"
4. **DM:** "DC é 12, você falhou. Você está envenenado"
5. **DM:** "Enquanto envenenado, você tem desvantagem em todos os checks e ataques"
6. **Jogador:** "Ok, vou rolar com desvantagem nos próximos ataques"
7. **DM:** "A cada turno, você pode tentar fazer outro saving throw para se curar"

### **No Jogo (GAS):**

1. **Sistema:** Goblin aplica ataque envenenado → **GameplayAbility** (ação)
2. **Sistema:** Cria efeito "Poison Effect" → **GameplayEffect** (regra)
3. **Sistema:** Solicita saving throw de Constitution → **GameplayEffect** (condição)
4. **Sistema:** Jogador falha (10 < 12) → Aplica condição "Envenenado"
5. **Sistema:** Modifica atributos "-1 em todos os checks e ataques" → **AttributeSet** (atualiza)
6. **Sistema:** A cada turno, permite novo saving throw → **GameplayEffect** (duração)
7. **Sistema:** Quando passar, remove efeito → **AttributeSet** (restaura valores)

**🎯 Diferença Principal:**

- **RPG de Mesa:** DM lembra de aplicar desvantagem manualmente
- **Jogo Digital:** Sistema aplica automaticamente, mas jogador vê feedback visual

---

## 🔥 Exemplo 3: Spell Fireball

### **RPG de Mesa:**

1. **Jogador:** "Eu lanço Fireball na área de 6 metros!"
2. **DM:** "Todos na área fazem saving throw de Dexterity"
3. **DM:** "DC é 15"
4. **Jogador:** Rola 8d6 = 28 de dano
5. **DM:** "Quem passou no saving throw toma metade (14), quem falhou toma total (28)"
6. **DM:** "Goblin 1: 10 → 0 HP (morto), Goblin 2: 15 → 1 HP"

### **No Jogo (GAS):**

1. **Jogador:** Pressiona botão "Fireball" → **GameplayAbility** (ação)
2. **Sistema:** Valida se tem spell slot nível 3 → **GameplayAbility** (validação)
3. **Sistema:** Jogador escolhe área → **GameplayAbility** (targeting)
4. **Sistema:** Identifica todos os alvos na área → **GameplayAbility** (detecção)
5. **Sistema:** Para cada alvo, aplica "Fireball Damage Effect" → **GameplayEffect** (regra)
6. **Sistema:** Cada alvo faz saving throw → **GameplayEffect** (condição)
7. **Sistema:** Calcula dano 8d6 = 28 → **GameplayEffect** (fórmula)
8. **Sistema:** Aplica dano (total ou metade) → **AttributeSet** (atualiza HP)
9. **Sistema:** Consome spell slot → **AttributeSet** (atualiza slots)

**🎯 Diferença Principal:**

- **RPG de Mesa:** DM calcula tudo manualmente
- **Jogo Digital:** Sistema calcula automaticamente, mas segue as mesmas regras

---

**Navegação:** [← Conceitos Fundamentais](conceitos-fundamentais.md) | [→ Adaptação de Regras](adaptacao-regras.md)

**Última atualização:** 2024-12-27
