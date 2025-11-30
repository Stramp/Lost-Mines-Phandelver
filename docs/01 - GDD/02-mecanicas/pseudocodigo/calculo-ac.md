# Pseudocódigo - Cálculo de Armor Class (AC)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Cálculo de AC</b></summary>

> Pseudocódigo para cálculo de Armor Class baseado em armadura, modificadores DEX e escudos, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo

```
FUNCTION CalculateAC(Character)
    baseAC = 10
    dexModifier = GetDexterityModifier(Character)
    armor = GetEquippedArmor(Character)
    shield = GetEquippedShield(Character)
    hasUnarmoredDefense = Character.HasUnarmoredDefense()

    IF hasUnarmoredDefense THEN
        // Unarmored Defense (Monk, Barbarian)
        conModifier = GetConstitutionModifier(Character)
        baseAC = 10 + dexModifier + conModifier
    ELSE IF armor == NULL THEN
        // Sem armadura
        baseAC = 10 + dexModifier
    ELSE IF armor.Type == LIGHT_ARMOR THEN
        // Armadura leve: AC base + DEX completo
        baseAC = armor.BaseAC + dexModifier
    ELSE IF armor.Type == MEDIUM_ARMOR THEN
        // Armadura média: AC base + DEX (máximo +2)
        dexBonus = MIN(dexModifier, 2)
        baseAC = armor.BaseAC + dexBonus
    ELSE IF armor.Type == HEAVY_ARMOR THEN
        // Armadura pesada: AC base (sem DEX)
        baseAC = armor.BaseAC
    END IF

    // Adicionar escudo (+2 AC)
    IF shield != NULL THEN
        baseAC = baseAC + 2
    END IF

    RETURN baseAC
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **Sem Armadura:** AC = 10 + DEX modifier
- **Armadura Leve:** AC = Armor Base AC + DEX modifier (sem limite)
- **Armadura Média:** AC = Armor Base AC + DEX modifier (máximo +2)
- **Armadura Pesada:** AC = Armor Base AC (sem bônus de DEX)
- **Escudo:** +2 AC (adiciona a qualquer tipo de armadura)
- **Unarmored Defense:** AC = 10 + DEX + CON (Monk/Barbarian)

---

## 📖 Referências

- **GDD:** [Sistema de Combate - AC](../02-mecanicas/sistema-combate.md#-cálculo-de-ac)
- **D&D 5e:** Player's Handbook - Armor Class

---

**Navegação:** [← Voltar ao Índice](index.md)
