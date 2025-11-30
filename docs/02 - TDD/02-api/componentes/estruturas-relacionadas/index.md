# Estruturas Relacionadas

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 Structs e Tipos de Dados</b></summary>

> Estruturas auxiliares usadas no sistema de fichas:

</details>

## FFeatDataRow

**Caminho:** `Source/MyProject2/Data/Tables/FeatDataTable.h`

Struct principal para dados de feats D&D 5e. Herda de `FTableRowBase` para uso em `UDataTable`.

**Status de Testes:** ✅ 6 testes implementados (`FeatDataTableTests.cpp`)

**Propriedades Principais:**

- `Name` - Nome do feat (ex: "Alert", "Magic Initiate")
- `FC_ID` - ID único (ex: "Feat_Alert")
- `Description` - Descrição textual (localizável)
- `LevelUnlocked` - Nível mínimo para adquirir (padrão: 4)
- `FeatureType` - Tipo da feature ("Feat")
- `FeatureData` - Dados estruturados (Prerequisites, Benefits, etc.)
- `AvailableChoices` - Escolhas disponíveis (geralmente vazio)

**Métodos:**

#### GetPrerequisites()

```cpp
TArray<FName> GetPrerequisites() const;
```

Retorna array de pré-requisitos do feat parseados de `FeatureData["Prerequisites"]`.

**Uso:** Usado para validar se personagem pode adquirir o feat.

---

## FProficiencyDataRow

**Caminho:** `Source/MyProject2/Data/Tables/ProficiencyDataTable.h`

Struct principal para dados de proficiências D&D 5e. Herda de `FTableRowBase` para uso em `UDataTable`.

**Status de Testes:** ✅ 4 testes implementados (`ProficiencyDataTableTests.cpp`)

**Propriedades Principais:**

- `Name` - Nome da proficiência (ex: "Simple Weapons", "Thieves' Tools", "Acrobatics")
- `ProficiencyID` - ID único (ex: "PW_Simple_Weapons", "PT_Thieves_Tools", "PSK_Acrobatics")
- `Type` - Tipo da proficiência ("Weapon", "Armor", "Shield", "Tool", "Skill", "SavingThrow", "Language")
- `Description` - Descrição textual (localizável)
- `ProficiencyData` - Dados estruturados opcionais para regras complexas (TMap<FName, FString>)

**ProficiencyData:**

Campo opcional que permite armazenar informações programáticas além da descrição textual.

**Exemplos de uso:**
- **Weapons:** `{"Damage": "1d4", "DamageType": "Bludgeoning", "Properties": "Light,Finesse"}`
- **Armor:** `{"AC": "15", "MaxDexBonus": "2", "StealthDisadvantage": "true"}`
- **Tools:** `{"UsesPerRest": "1", "ActionType": "Action"}`
- **Skills:** `{"AbilityModifier": "DEX"}` (para skills que usam modificador específico)

**Uso:** Vazio para proficiências passivas (Languages, SavingThrows básicos). Preparado para migração futura para GAS (Gameplay Ability System).

---

## FAbilityScoreEntry

**Caminho:** `Source/MyProject2/Characters/Data/CharacterSheetDataAssetTypes.h`

```cpp
USTRUCT(BlueprintType)
struct MYPROJECT2_API FAbilityScoreEntry
{
    GENERATED_BODY()

    /** Score base (8-15 para Point Buy) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    int32 BaseScore = 8;

    /** Bônus racial aplicado (calculado automaticamente) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 RacialBonus = 0;

    /** Score final (BaseScore + RacialBonus) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 FinalScore = 8;
};
```

**Uso:** Armazena ability score com base, bônus racial e score final.

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[CharacterSheetDataAsset](../character-sheet-data-asset/index.md)** - Data Asset que usa estas estruturas
> - **[Índice de Componentes](../index.md)** - Lista de todos os componentes

</details>
