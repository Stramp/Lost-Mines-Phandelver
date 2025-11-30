# Combat System - Pseudocódigo Técnico

---

## 🎯 Objetivo

Especificação técnica de implementação do sistema de combate, incluindo estruturas C++, classes e componentes.

---

## 📐 Estruturas de Dados

### FCombatData

```cpp
USTRUCT(BlueprintType)
struct FCombatData
{
    GENERATED_BODY()

    // AC e Defesa
    UPROPERTY(BlueprintReadOnly)
    int32 AC;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentHP;

    UPROPERTY(BlueprintReadOnly)
    int32 MaxHP;

    // Ataque
    UPROPERTY(BlueprintReadOnly)
    int32 AttackBonus;

    UPROPERTY(BlueprintReadOnly)
    int32 DamageBonus;

    // Condições
    UPROPERTY(BlueprintReadOnly)
    TArray<FName> ActiveConditions;

    // Resistências e Vulnerabilidades
    UPROPERTY(BlueprintReadOnly)
    TArray<FName> Resistances;

    UPROPERTY(BlueprintReadOnly)
    TArray<FName> Vulnerabilities;
};
```

### FAttackResult

```cpp
USTRUCT(BlueprintType)
struct FAttackResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bHit;

    UPROPERTY(BlueprintReadOnly)
    bool bIsCritical;

    UPROPERTY(BlueprintReadOnly)
    bool bIsCriticalMiss;

    UPROPERTY(BlueprintReadOnly)
    int32 AttackRoll;

    UPROPERTY(BlueprintReadOnly)
    int32 TargetAC;

    UPROPERTY(BlueprintReadOnly)
    int32 DieRoll;
};
```

### FDamageResult

```cpp
USTRUCT(BlueprintType)
struct FDamageResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 BaseDamage;

    UPROPERTY(BlueprintReadOnly)
    int32 FinalDamage;

    UPROPERTY(BlueprintReadOnly)
    FName DamageType;

    UPROPERTY(BlueprintReadOnly)
    bool bWasCritical;

    UPROPERTY(BlueprintReadOnly)
    bool bWasResisted;

    UPROPERTY(BlueprintReadOnly)
    bool bWasVulnerable;
};
```

---

## 🏗️ Classes e Componentes

### UCombatComponent

```cpp
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYPROJECT2_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Inicialização
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void InitializeCombat(const FCharacterData& CharacterData);

    // Ataques
    UFUNCTION(BlueprintCallable, Category = "Combat")
    FAttackResult PerformAttack(AActor* Target, FName WeaponName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    FDamageResult CalculateDamage(const FAttackResult& AttackResult, FName WeaponName, FName DamageType);

    // Defesa
    UFUNCTION(BlueprintCallable, Category = "Combat")
    int32 CalculateAC() const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TakeDamage(const FDamageResult& DamageResult);

    // Condições
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ApplyCondition(FName ConditionName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void RemoveCondition(FName ConditionName);

protected:
    UPROPERTY(Replicated)
    FCombatData CombatData;

    UPROPERTY()
    UCharacterDataComponent* CharacterDataComponent;
};
```

---

## 🔄 Fluxo de Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Diagrama de Fluxo de Ataque</b></summary>

> ```mermaid
> graph TD
>     Start([Iniciar Ataque]) --> Roll[1. Rolar d20]
>     Roll --> Check20{Natural 20?}
>     Check20 -->|Sim| Critical[Crítico!<br/>Sempre Acerta]
>     Check20 -->|Não| Check1{Natural 1?}
>     Check1 -->|Sim| Miss[Falha Crítica!<br/>Sempre Erra]
>     Check1 -->|Não| CalcRoll[2. Calcular Attack Roll<br/>d20 + Proficiency + Modifier]
>     CalcRoll --> GetAC[3. Obter AC do Alvo]
>     GetAC --> Compare{Attack Roll<br/>>= AC?}
>     Compare -->|Sim| Hit[Acertou!]
>     Compare -->|Não| Miss
>     Critical --> CalcDamage[4. Calcular Dano<br/>Base + Modifier]
>     Hit --> CalcDamage
>     CalcDamage --> CheckCrit{Crítico?}
>     CheckCrit -->|Sim| DoubleDice[Dobrar Dados]
>     CheckCrit -->|Não| NormalDice[Dados Normais]
>     DoubleDice --> ApplyResist[5. Aplicar<br/>Resistências/Vulnerabilidades]
>     NormalDice --> ApplyResist
>     ApplyResist --> ApplyDamage[6. Aplicar Dano<br/>no Alvo]
>     ApplyDamage --> End([Ataque Completo])
>     Miss --> End
>
>     style Start fill:#c8e6c9
>     style End fill:#c8e6c9
>     style Critical fill:#ffcdd2
>     style Miss fill:#ffcdd2
>     style Hit fill:#c8e6c9
>     style Check20 fill:#fff3e0
>     style Check1 fill:#fff3e0
>     style Compare fill:#fff3e0
>     style CheckCrit fill:#fff3e0
> ```
>
> **📖 [Ver algoritmo técnico completo](../../04-regras-dnd/combate/attack-roll-algorithm.md)**

</details>

---

### Fluxo Completo de Ataque

```cpp
// Fluxo completo: Ataque → Verificação → Dano → Aplicação
FCombatResult UCombatComponent::PerformCombatAction(
    AActor* Target,
    FName WeaponName,
    FName DamageType)
{
    // 1. Verificar acerto
    FAttackResult AttackResult = PerformAttack(Target, WeaponName);

    if (!AttackResult.bHit)
    {
        return FCombatResult(AttackResult, FDamageResult(), false);
    }

    // 2. Calcular dano
    FDamageResult DamageResult = CalculateDamage(AttackResult, WeaponName, DamageType);

    // 3. Aplicar dano no alvo
    if (UCombatComponent* TargetCombat = Target->FindComponentByClass<UCombatComponent>())
    {
        TargetCombat->TakeDamage(DamageResult);
    }

    return FCombatResult(AttackResult, DamageResult, true);
}
```

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Design Relacionado</b></summary>

> Este documento implementa as seguintes regras de design:
>
> - **[GDD: Sistema de Combate](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md)** - Regras de combate D&D 5e
>
> - **GDD:** Define O QUÊ (combate em tempo real adaptado de D&D 5e) e PORQUÊ (experiência fiel)
> - **TDD Seção 04:** Define algoritmos técnicos (como calcular AC, dano, acerto)
> - **TDD Seção 08:** Define pseudocódigo técnico (estruturas C++, classes, componentes)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💻 Algoritmos (TDD)</b></summary>

> - [AC Calculation Algorithm](../../04-regras-dnd/combate/ac-calculation-algorithm.md) - Algoritmo técnico
> - [Damage Calculation Algorithm](../../04-regras-dnd/combate/damage-calculation-algorithm.md) - Algoritmo técnico
> - [Attack Roll Algorithm](../../04-regras-dnd/combate/attack-roll-algorithm.md) - Algoritmo técnico

</details>

---

**Navegação:** [← Voltar](index.md) | [→ AC Calculation](ac-calculation.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação do pseudocódigo técnico de combate |
