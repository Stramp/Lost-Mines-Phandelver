# Gameplay Ability System (GAS) - Conceitos Fundamentais

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🏗️ Os 3 Pilares do GAS

### 1. **AttributeSet - A Ficha do Personagem**

**Responsabilidade EXCLUSIVA:**

- ✅ Armazenar valores de atributos (Base e Current)
- ✅ Gerenciar modificadores temporários
- ✅ Replicar em multiplayer
- ✅ Notificar mudanças (eventos)
- ✅ Validar/Clamp valores (ex: Strength entre 1-30)

**O que NÃO faz:**

- ❌ Aplicar lógica de gameplay (isso é GameplayEffect)
- ❌ Decidir quando aplicar modificadores (isso é GameplayEffect)
- ❌ Gerenciar habilidades (isso é GameplayAbility)

**Para D&D 5e, armazena:**

- **Ability Scores:** Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
- **Derivados:** Modifiers, MaxHealth, ArmorClass, ProficiencyBonus
- **Meta-Attributes:** Health atual, Temporary modifiers

### 2. **GameplayEffect - O Livro de Regras**

**Responsabilidade EXCLUSIVA:**

- ✅ Definir o que acontece e quando
- ✅ Aplicar modificadores de atributos
- ✅ Definir duração de efeitos
- ✅ Estabelecer condições de aplicação

**Para D&D 5e, define:**

- **Fórmulas:** "Ataque = d20 + Strength modifier + Proficiency"
- **Efeitos Temporários:** "+2 Strength por 1 hora (spell)"
- **Condições:** "Envenenado = -1 em todos os checks"
- **Duração:** Instantâneo, 1 turno, 1 hora, permanente

### 3. **GameplayAbility - A Ação do Jogador**

**Responsabilidade EXCLUSIVA:**

- ✅ Executar ações e coordenar
- ✅ Orquestrar fluxo completo
- ✅ Chamar GameplayEffects
- ✅ Gerenciar cooldowns e custos

**Para D&D 5e, executa:**

- **Ataques:** "Ataque com espada", "Ataque à distância"
- **Spells:** "Fireball", "Cure Wounds", "Shield"
- **Habilidades:** "Action Surge", "Second Wind", "Rage"
- **Skills:** "Stealth", "Perception", "Athletics"

---

**Navegação:** [← Visão Geral](visao-geral.md) | [→ Fluxos Práticos](fluxos-praticos.md)

**Última atualização:** 2024-12-27
