# Race and Subrace

## Structure

```
Race
├── Base Race (e.g., "Elf")
│   ├── Ability Score Improvements
│   ├── Base Traits
│   └── Subraces: ["High Elf", "Wood Elf", "Drow"]
└── Subrace (selected from parent race)
    ├── Additional Ability Score Improvements
    └── Additional Traits
```

## Selection Rules

- Must select Race first
- Subrace dropdown filtered by selected Race
- Subrace can be "None" if race has no subraces
- Final bonuses = Race bonuses + Subrace bonuses

## Ability Score Bonuses

```
FinalAbilityScore = BaseAbilityScore + RaceBonuses + SubraceBonuses
```

## Example: Elf

- Race: Elf → +2 DEX
- Subrace: High Elf → +1 INT
- Total: +2 DEX, +1 INT
