# Level Up System

## Level Progression

- Level 1: Class features at level 1
- Levels 2-20: Features unlock at specific levels per class
- ASI at: 4, 8, 12, 16, 19 (some classes get extra)

## Feature Unlocking

```
function GetFeaturesAtLevel(className, level):
    features = []
    classData = GetClassData(className)
    for feature in classData.Features:
        if feature.LevelUnlocked <= level:
            features.add(feature)
    return features
```

## Hit Points

```
Level1HP = HitDie + CON modifier
Level2PlusHP = HitDie/2 + 1 + CON modifier (or roll)
MaxHP = sum of all level HP gains
```

## Proficiency Bonus

| Level | Proficiency Bonus |
|-------|-------------------|
| 1-4   | +2                |
| 5-8   | +3                |
| 9-12  | +4                |
| 13-16 | +5                |
| 17-20 | +6                |

```
ProficiencyBonus = ceil(TotalLevel / 4) + 1
```
