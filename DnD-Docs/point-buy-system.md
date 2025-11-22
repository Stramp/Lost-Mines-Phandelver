# Point Buy System

## Cost Table

| Ability Score | Cost |
|---------------|------|
| 8             | 0    |
| 9             | 1    |
| 10            | 1    |
| 11            | 1    |
| 12            | 1    |
| 13            | 1    |
| 14            | 2    |
| 15            | 3    |

## Rules

- Starting points: 27
- Minimum score: 8
- Maximum score: 15 (before racial bonuses)
- All 6 abilities start at 8
- Total cost must equal 27

## Validation

```
AvailablePoints = 27 - sum(cost for each ability)
Valid if: AvailablePoints == 0 AND all scores >= 8 AND all scores <= 15
```

## Calculation Function

```
function CalculateCost(score):
    if score == 8: return 0
    if score <= 13: return score - 8
    if score == 14: return 6
    if score == 15: return 9
```
