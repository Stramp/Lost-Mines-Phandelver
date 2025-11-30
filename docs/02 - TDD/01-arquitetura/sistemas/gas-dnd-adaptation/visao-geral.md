# Visão Geral: RPG de Mesa vs Jogo Digital

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🎯 Analogia: Sessão de RPG de Mesa

Em uma sessão de RPG de mesa, temos três elementos principais:

### 📋 Ficha do Personagem (AttributeSet)

**Responsabilidade:** Guardar todos os números do personagem.

- **Exemplos:** "Strength: 16", "HP: 45/50", "Proficiency: +3", "AC: 18"
- **Não decide:** Não rola dados, não aplica regras, não executa ações
- **Apenas armazena:** Valores que podem mudar durante o jogo

### 📖 Livro de Regras (GameplayEffect)

**Responsabilidade:** Definir o que acontece e quando.

- **Exemplos:** "Ataque = d20 + Strength modifier + Proficiency", "Dano = 1d8 + Strength modifier", "Acerto reduz HP do alvo"
- **Define:** Fórmulas, condições, consequências, duração de efeitos
- **Não executa:** Apenas define as regras

### ⚔️ Ação do Jogador (GameplayAbility)

**Responsabilidade:** Executar a ação declarada.

- **Exemplos:** "Eu ataco com espada!", "Uso spell Fireball", "Faço um teste de skill"
- **Orquestra:** Declara ação → Consulta regras (GameplayEffect) → Atualiza ficha (AttributeSet)
- **Coordena:** Todo o fluxo de execução

**🔄 Fluxo Completo:**

1. **Jogador:** "Eu ataco!" → GameplayAbility (ação)
2. **Regra:** "Rola d20 + Strength + Proficiency" → GameplayEffect (fórmula)
3. **Ficha:** "Strength: 16 (+3), Proficiency: +3" → AttributeSet (valores)
4. **Resultado:** d20(12) + 3 + 3 = 18 vs AC 15 → **Acertou!**
5. **Regra:** "Dano = 1d8 + Strength modifier" → GameplayEffect
6. **Ficha:** "HP do alvo: 50 → 42" → AttributeSet (atualiza)

---

**Navegação:** [← Índice](index.md) | [→ Conceitos Fundamentais](conceitos-fundamentais.md)

**Última atualização:** 2024-12-27
