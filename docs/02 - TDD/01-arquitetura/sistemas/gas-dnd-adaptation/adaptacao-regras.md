# Adaptação de Regras D&D 5e

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de gas-dnd-adaptation.md |

---

## 🎯 Princípios de Adaptação

### 1. Fidelidade às Regras

- ✅ Todas as regras oficiais de D&D 5e são mantidas
- ✅ Fórmulas de cálculo são idênticas
- ✅ Condições e efeitos funcionam igual
- ✅ Balanceamento não é alterado

### 2. Automação Inteligente

- ✅ Sistema calcula automaticamente (não precisa rolar dados manualmente)
- ✅ Aplica modificadores automaticamente
- ✅ Gerencia duração de efeitos automaticamente
- ✅ Valida condições automaticamente

### 3. Feedback Visual

- ✅ Jogador vê resultados de rolagens (opcional)
- ✅ Efeitos visuais para condições
- ✅ Feedback de acerto/erro
- ✅ Indicadores de buffs/debuffs

### 4. Action RPG: Colisão Real

- ✅ Combate é em tempo real (não turn-based)
- ✅ Colisão física real (não abstrata)
- ✅ Projéteis têm física real
- ✅ Áreas de efeito são visuais e físicas

**⚠️ IMPORTANTE:** As regras de D&D 5e são mantidas, mas a execução é adaptada para tempo real.

---

## 📊 Atributos e Cálculos

### Ability Scores (AttributeSet)

**Armazenados:**

- Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
- Base Value (valor base da ficha)
- Current Value (valor atual com modificadores)

**Modificadores:**

- Calculados automaticamente: `(Score - 10) / 2` (arredondado para baixo)
- Exemplo: Strength 16 → Modifier +3

### Atributos Derivados (Meta-Attributes)

**MaxHealth:**

- **Level 1:** `Hit Die + Constitution Modifier`
- **Level 2+:** `(Hit Die / 2) + 1 + Constitution Modifier` (por nível adicional)
- Recalcula automaticamente quando Constitution muda ou nível aumenta
- **⚠️ IMPORTANTE:** Constitution Modifier é calculado a partir do Final Constitution Score

**ArmorClass (AC):**

- Fórmula: `10 + Dexterity Modifier + Armor Bonus`
- Recalcula automaticamente quando Dexterity ou Armor muda

**ProficiencyBonus:**

- Tabela fixa baseada no **Total Level** (soma de todos os níveis de classes):
- Níveis 1-4: +2
- Níveis 5-8: +3
- Níveis 9-12: +4
- Níveis 13-16: +5
- Níveis 17-20: +6
- Fórmula: `2 + floor((TotalLevel - 1) / 4)`
- Recalcula automaticamente quando Total Level muda
- **⚠️ IMPORTANTE:** Em multiclassing, usa Total Level, não nível de classe específica

**🎯 Vantagem do GAS:**

- Todos os cálculos são automáticos
- Modificadores temporários são aplicados automaticamente
- Sistema notifica quando valores mudam (para UI reativa)

---

**Navegação:** [← Fluxos Práticos](fluxos-praticos.md) | [→ Action RPG Combate](action-rpg-combate.md)

**Última atualização:** 2024-12-27
