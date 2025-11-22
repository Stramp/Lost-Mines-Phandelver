# Multiclassing

## Level Calculation

```
TotalLevel = sum(levels in all classes)
MaximumTotalLevel = 20
```

## Prerequisites

Each class has ability score prerequisites. Must meet prerequisites for BOTH current class AND new class.

| Class | Prerequisites |
|-------|---------------|
| Barbarian | Strength 13 |
| Bard | Charisma 13 |
| Cleric | Wisdom 13 |
| Druid | Wisdom 13 |
| Fighter | Strength 13 **OR** Dexterity 13 |
| Monk | Dexterity 13 **AND** Wisdom 13 |
| Paladin | Strength 13 **AND** Charisma 13 |
| Ranger | Dexterity 13 **AND** Wisdom 13 |
| Rogue | Dexterity 13 |
| Sorcerer | Charisma 13 |
| Warlock | Charisma 13 |
| Wizard | Intelligence 13 |

## Validation

```
CanMulticlassTo(newClass) =
    MeetsPrerequisite(currentClass) AND MeetsPrerequisite(newClass)
```

## Feature Calculation

```
AvailableFeatures = []
for each class in ClassLevels:
    classFeatures = GetClassFeatures(className)
    for feature in classFeatures:
        if feature.LevelUnlocked <= ClassLevels[className]:
            AvailableFeatures.add(feature)
```

## Proficiencies

When gaining first level in new class, you get LIMITED proficiencies (not all starting proficiencies):

### Armor and Weapon Proficiencies

| Class | Armor | Weapons | Shields |
|-------|-------|---------|---------|
| Barbarian | Light, Medium | Simple, Martial | No |
| Bard | Light | Simple, Hand Crossbow, Longsword, Rapier, Shortsword | No |
| Cleric | Light, Medium | Simple | Yes |
| Druid | Light, Medium (no metal) | Simple (clubs, daggers, darts, javelins, maces, quarterstaffs, scimitars, sickles, slings, spears) | Yes (no metal) |
| Fighter | Light, Medium, Heavy | Simple, Martial | Yes |
| Monk | None | Simple, Shortsword | No |
| Paladin | Light, Medium, Heavy | Simple, Martial | Yes |
| Ranger | Light, Medium | Simple, Martial | Yes |
| Rogue | Light | Simple, Hand Crossbow, Longsword, Rapier, Shortsword | No |
| Sorcerer | None | Simple (daggers, darts, slings, quarterstaffs, light crossbows) | No |
| Warlock | Light | Simple | No |
| Wizard | None | Simple (daggers, darts, slings, quarterstaffs, light crossbows) | No |

### Skill Proficiencies

- Gain proficiency in ONE skill from new class's skill list
- Exception: Rogue multiclass gains proficiency in ONE skill from Rogue list

### Tool Proficiencies

- Some classes grant tool proficiencies (check class description)

## Spell Slots (if multiclassing spellcasters)

### Caster Level Calculation

Combine caster levels from different classes:
- **Full Caster** (Bard, Cleric, Druid, Sorcerer, Wizard): Counts as 1 level
- **Half Caster** (Paladin, Ranger): Counts as 0.5 level (rounded down)
- **Warlock**: Separate (Pact Magic, does NOT combine)

```
CasterLevel = FullCasterLevels + floor(HalfCasterLevels / 2)
```

### Full Casters
- Bard, Cleric, Druid, Sorcerer, Wizard

### Half Casters
- Paladin, Ranger

### Special Case: Warlock
- Pact Magic slots are separate
- Do NOT combine with other spell slots
- Recover on short rest (not long rest)

### Example
- Wizard 3 + Paladin 2
- CasterLevel = 3 + floor(2/2) = 3 + 1 = 4
- Use spell slot table for level 4 caster

See `spellcasting.md` for full spell slot tables.
