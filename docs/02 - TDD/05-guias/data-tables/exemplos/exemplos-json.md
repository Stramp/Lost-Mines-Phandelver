# Exemplos de JSON Válido - Data Tables

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Exemplos Completos</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Raça Completa (Dwarf)</summary>
>
> > ```json
> > {
> >   "Name": "Dwarf",
> >   "RaceName": "Dwarf",
> >   "Description": "Bold and hardy dwarves are known as skilled warriors miners and workers of stone and metal",
> >   "AbilityScoreImprovements": [
> >     {
> >       "AbilityName": "Constitution",
> >       "Bonus": 2
> >     }
> >   ],
> >   "Size": "Medium",
> >   "BaseSpeed": 25,
> >   "Traits": [
> >     {
> >       "TraitName": "Darkvision",
> >       "Description": "Accustomed to life underground, you have superior vision in dark and dim conditions.",
> >       "TraitData": {
> >         "Range": "60",
> >         "Type": "Vision"
> >       }
> >     },
> >     {
> >       "TraitName": "Dwarven Resilience",
> >       "Description": "You have advantage on saving throws against poison.",
> >       "TraitData": {
> >         "Advantage": "Poison",
> >         "Resistance": "Poison"
> >       }
> >     }
> >   ],
> >   "SubraceNames": ["Hill Dwarf", "Mountain Dwarf"]
> > }
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">Classe Completa (Wizard)</summary>
>
> > ```json
> > {
> >   "Name": "Wizard",
> >   "Description": "A scholarly magic-user capable of manipulating the structures of reality.",
> >   "HitDie": 6,
> >   "Proficiencies": [
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Daggers"
> >     },
> >     {
> >       "ProficiencyType": "Weapon",
> >       "ProficiencyName": "Darts"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Intelligence"
> >     },
> >     {
> >       "ProficiencyType": "SavingThrow",
> >       "ProficiencyName": "Wisdom"
> >     }
> >   ],
> >   "Features": [
> >     {
> >       "FeatureName": "Spellcasting",
> >       "Description": "As a student of arcane magic, you have a spellbook containing spells.",
> >       "LevelUnlocked": 1,
> >       "FeatureType": "Automatic",
> >       "FeatureData": {
> >         "SpellcastingAbility": "Intelligence",
> >         "SpellSaveDC": "8 + Proficiency + Intelligence Modifier"
> >       }
> >     },
> >     {
> >       "FeatureName": "Arcane Tradition",
> >       "Description": "You choose an arcane tradition.",
> >       "LevelUnlocked": 2,
> >       "FeatureType": "SubclassSelection",
> >       "FeatureData": {}
> >     }
> >   ],
> >   "SubclassNames": ["Evocation", "Abjuration", "Necromancy"]
> > }
> > ```
>
> </details>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

**Navegação:** [← Índice](../index.md) | [→ Boas Práticas](../boas-praticas.md)

**Última atualização:** 2024-12-27
