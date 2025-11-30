# Exemplos Comuns de Código

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação dos exemplos comuns |

---

## 🔧 Exemplos de Uso Comum

### Carregar Data Table

```cpp
UDataTable* RaceDataTable = LoadObject<UDataTable>(
    nullptr, TEXT("/Game/Data/DT_Races"));
```

### Buscar Row em Data Table

```cpp
FRaceDataRow* RaceRow = RaceDataTable->FindRow<FRaceDataRow>(
    TEXT("Human"), TEXT("Context"));
```

### Calcular Modificador de Atributo

```cpp
int32 Modifier = (Score - 10) / 2;
```

### Calcular Proficiency Bonus

```cpp
int32 ProficiencyBonus = 2 + ((TotalLevel - 1) / 4);
```

### Calcular AC

```cpp
int32 AC = 10 + DEXModifier; // Sem armadura
int32 AC = ArmorBaseAC + DEXModifier; // Light Armor
int32 AC = ArmorBaseAC + FMath::Min(DEXModifier, 2); // Medium Armor
int32 AC = ArmorBaseAC; // Heavy Armor
```

### Rolar d20

```cpp
int32 DieRoll = FMath::RandRange(1, 20);
```

### Rolar Dano

```cpp
// 1d8
int32 Damage = FMath::RandRange(1, 8);

// 2d6
int32 Damage = 0;
for (int32 i = 0; i < 2; i++)
{
    Damage += FMath::RandRange(1, 6);
}
```

### Verificar Acerto

```cpp
int32 AttackRoll = d20 + ProficiencyBonus + AbilityModifier;
bool bHit = (AttackRoll >= TargetAC);
```

### Aplicar Dano

```cpp
int32 FinalDamage = BaseDamage + AbilityModifier;
TargetHP = FMath::Max(0, TargetHP - FinalDamage);
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Implementação (TDD)</b></summary>

> - [Algoritmos D&D](../../04-regras-dnd/index.md) - Algoritmos técnicos completos
> - [Calculation Helpers](../../02-api/helpers/index.md) - Helpers de cálculo

</details>

---

**Navegação:** [← Tabelas de Referência](tabelas-referencia.md) | [→ Voltar para Index](index.md)

**Última atualização:** 2024-12-27
