# Padrão de Nomenclatura de IDs (Completo) - ✅ IMPLEMENTADO

```
RACE_<Name>           → RACE_Dwarf, RACE_Elf, RACE_HighElf
CLASS_<Name>          → CLASS_Fighter, CLASS_Wizard
BG_<Name>             → BG_Acolyte, BG_Criminal
FEAT_<Name>           → FEAT_Alert, FEAT_Athlete
FC_<Name>             → FC_SecondWind, FC_Spellcasting
TR_<Name>             → TR_Darkvision, TR_FeyAncestry
PL_<Name>             → PL_Common, PL_Elvish
PSK_<Name>            → PSK_Acrobatics, PSK_Stealth
ABL_<Name>            → ABL_Strength, ABL_Dexterity
SPL_<Name>            → SPL_Fireball, SPL_MagicMissile
SCH_<Name>            → SCH_Evocation, SCH_Abjuration
DMG_<Name>            → DMG_Fire, DMG_Cold (⚠️ Prefixo é DMG_, não DAM_)
COND_<Name>           → COND_Poisoned, COND_Charmed (⚠️ Prefixo é COND_, não CON_)
PW_<Name>             → PW_Simple_Weapons
PA_<Name>             → PA_Light_Armor
PT_<Name>             → PT_Thieves_Tools
ITM_<Category>_<Name> → ITM_ARM_ChainMail
```

**⚠️ IMPORTANTE:**
- Todos os IDs seguem o padrão `<PREFIX>_<Name>` em UPPERCASE
- Prefixos de dano usam `DMG_` (não `DAM_`)
- Prefixos de condição usam `COND_` (não `CON_`)

---

## 🔗 Navegação

- [📚 Relatório - Índice](./index.md)
- [✅ Checklist de Migração](./checklist-migracao.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de ideal-data-structure-report.md |
