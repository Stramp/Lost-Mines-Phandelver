# Pseudocódigo - Sistema de Level Up

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⬆️ Sistema de Level Up</b></summary>

> Pseudocódigo completo para processamento de level up, incluindo HP, ASI, features de classe e spell slots, seguindo regras D&D 5e.

</details>

---

## Pseudocódigo

```
FUNCTION ProcessLevelUp(Character, NewLevel)
    oldLevel = Character.GetLevel()
    characterClass = Character.GetPrimaryClass()

    // 1. Aumentar nível
    Character.SetLevel(NewLevel)

    // 2. Calcular e adicionar HP
    hitDie = GetClassHitDie(characterClass)
    conModifier = GetConstitutionModifier(Character)

    IF NewLevel == 1 THEN
        // Nível 1: HP máximo do dado
        hpGain = hitDie + conModifier
    ELSE
        // Níveis 2+: Rolagem com mínimo garantido
        roll = RollDice(hitDie)
        halfDie = CEIL(hitDie / 2)

        IF roll > halfDie THEN
            hpGain = roll + conModifier
        ELSE
            hpGain = halfDie + conModifier
        END IF
    END IF

    Character.IncreaseMaxHP(hpGain)
    Character.SetCurrentHP(Character.GetCurrentHP() + hpGain)  // Recupera HP ao level up

    // 3. Aplicar Features de Classe
    classFeatures = GetClassFeaturesForLevel(characterClass, NewLevel)
    FOR EACH feature IN classFeatures DO
        ApplyFeature(Character, feature)
    END FOR

    // 4. ASI ou Feat (níveis 4, 8, 12, 16, 19)
    IF NewLevel IN [4, 8, 12, 16, 19] THEN
        // Jogador escolhe: +2 em um atributo OU +1 em dois atributos OU Feat
        choice = PlayerChooseASIOrFeat()

        IF choice.Type == ASI THEN
            IF choice.Option == "+2_ONE" THEN
                ability = PlayerChooseAbility()
                IF GetAbilityScore(Character, ability) < 20 THEN
                    newScore = MIN(GetAbilityScore(Character, ability) + 2, 20)
                    SetAbilityScore(Character, ability, newScore)
                END IF
            ELSE IF choice.Option == "+1_TWO" THEN
                ability1 = PlayerChooseAbility()
                ability2 = PlayerChooseAbility()

                IF GetAbilityScore(Character, ability1) < 20 THEN
                    newScore1 = MIN(GetAbilityScore(Character, ability1) + 1, 20)
                    SetAbilityScore(Character, ability1, newScore1)
                END IF

                IF GetAbilityScore(Character, ability2) < 20 THEN
                    newScore2 = MIN(GetAbilityScore(Character, ability2) + 1, 20)
                    SetAbilityScore(Character, ability2, newScore2)
                END IF
            END IF
        ELSE IF choice.Type == FEAT THEN
            ApplyFeat(Character, choice.Feat)
        END IF
    END IF

    // 5. Atualizar Spell Slots (se spellcaster)
    IF IsSpellcaster(characterClass) THEN
        spellSlots = GetSpellSlotsForLevel(characterClass, NewLevel)
        Character.SetSpellSlots(spellSlots)

        // Adicionar Cantrips em níveis específicos
        IF ShouldGainCantrip(characterClass, NewLevel) THEN
            cantrip = PlayerChooseCantrip(characterClass)
            Character.AddCantrip(cantrip)
        END IF
    END IF

    // 6. Atualizar Proficiency Bonus (baseado em Total Level)
    totalLevel = CalculateTotalLevel(Character)  // Soma de todas as classes
    proficiencyBonus = 2 + FLOOR((totalLevel - 1) / 4)
    Character.SetProficiencyBonus(proficiencyBonus)

    // 7. Recalcular valores derivados
    RecalculateDerivedStats(Character)
END FUNCTION
```

---

## 📋 Regras Aplicadas

- **HP Nível 1:** Hit Die máximo + CON modifier
- **HP Níveis 2+:** Roll Hit Die (mínimo = metade do dado) + CON modifier
- **ASI:** Níveis 4, 8, 12, 16, 19 (+2 em um OU +1 em dois OU Feat)
- **Features:** Desbloqueadas conforme nível da classe
- **Spell Slots:** Atualizados conforme nível de spellcaster
- **Proficiency Bonus:** Baseado em Total Level (soma de todas as classes)

---

## 📖 Referências

- **GDD:** [Sistemas de Personagem - Level Up](../02-mecanicas/sistemas-personagem.md#-level-up-e-progressão)
- **D&D 5e:** Player's Handbook - Leveling Up

---

**Navegação:** [← Voltar ao Índice](index.md)
