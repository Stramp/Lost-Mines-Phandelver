# Estrutura Comum de Data Tables

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de data-tables.md |

---

## 📊 Padrões e Estruturas Compartilhadas

### Padrão "ID + Tags + Payload"

Cada entrada em um Data Table segue o padrão:

- **ID:** Identificador único (ex: `"PW_Simple_Weapons"`, `"ABL_Strength"`)
- **Tags:** Categorização via `FGameplayTagContainer` (ex: `["Proficiency.Weapon.Simple"]`)
- **Payload:** Dados específicos via `TMap<FName, FString>` ou estruturas customizadas

### Estruturas Compartilhadas

#### FAbilityScoreImprovement

```cpp
USTRUCT(BlueprintType)
struct FAbilityScoreImprovement
{
    FName AbilityName;  // Nome do atributo (ex: "Strength", "Constitution")
    int32 Bonus;        // Valor do bônus (geralmente +1 ou +2)
};
```

**Nota Especial:** Para Variant Human, use `AbilityName = "Custom"` com `Bonus = 1`. O sistema aplicará +1 para cada atributo escolhido em `CustomAbilityScoreChoices`.

#### FRaceTrait

```cpp
USTRUCT(BlueprintType)
struct FRaceTrait
{
    FName TraitName;                    // Nome do trait (ex: "Darkvision")
    FText Description;                  // Descrição textual
    TMap<FName, FString> TraitData;     // Dados estruturados opcionais
};
```

#### FClassProficiency

```cpp
USTRUCT(BlueprintType)
struct FClassProficiency
{
    FName ProficiencyType;  // Tipo: "Weapon", "Armor", "SavingThrow", "Skill"
    FName ProficiencyName; // Nome específico (ex: "Longsword", "Light Armor", "Strength", "Athletics")
};
```

#### FClassFeature

```cpp
USTRUCT(BlueprintType)
struct FClassFeature
{
    FName FeatureName;                    // Nome da feature (ex: "Second Wind", "Action Surge")
    FText Description;                    // Descrição textual
    int32 LevelUnlocked;                  // Nível em que é desbloqueada
    FName FeatureType;                    // Tipo: "Automatic", "SubclassSelection", "ASI", "Choice"
    TMap<FName, FString> FeatureData;     // Dados estruturados opcionais
};
```

---

## 🔧 Como Criar/Editar Data Tables no Editor

### 1. Criar Data Table

1. No Content Browser, navegue até a pasta desejada
2. Clique com botão direito → **Miscellaneous** → **Data Table**
3. Selecione o struct apropriado:
   - `Race Data Row` para raças
   - `Class Data Row` para classes
   - `Background Data Row` para backgrounds
   - `Feat Data Row` para feats
   - `Feature Data Row` para features
   - `Proficiency Data Row` para proficiências
   - `Skill Data Row` para skills
   - `Language Data Row` para idiomas
   - `Spell Data Row` para magias
   - `Spell School Data Row` para escolas de magia
   - `Damage Type Data Row` para tipos de dano
   - `Condition Data Row` para condições
   - `Ability Score Data Row` para atributos
   - `Trait Data Row` para traits
   - `Item Data Row` para itens
4. Nomeie o Data Table (ex: `DT_Races`, `DT_Classes`, `DT_Features`)

### 2. Importar JSON

1. Selecione o Data Table criado
2. No Details Panel, clique em **Import**
3. Selecione o arquivo JSON
4. O sistema importará automaticamente os dados

**Formato JSON esperado:**
- Array de objetos
- Cada objeto representa uma linha
- Campo `Name` é usado como Row Name no Data Table

### 3. Editar Manualmente

1. Selecione o Data Table
2. No Details Panel, clique em **Add Row** para adicionar nova entrada
3. Preencha os campos conforme necessário
4. Use **Remove Row** para remover entradas

---

## ✅ Validações Aplicadas

### RaceDataTable

- **Custom ASI:** Variant Human com `AbilityName = "Custom"` é tratado especialmente
- **Traits:** Traits `FeatChoice` e `SkillChoice` habilitam escolhas do jogador
- **Bônus Raciais:** Calculados automaticamente por `FRaceBonusMotor` que processa bônus de raça base, sub-raça e Variant Human

### ClassDataTable

- **Features por nível:** Sistema coleta features baseado no nível do personagem
- **Subclasses:** Sistema valida que subclasse pertence à classe selecionada
- **Proficiências:** Sistema agrega proficiências de todas as classes do personagem

### BackgroundDataTable

- **Proficiências:** Sistema agrega skill proficiencies ao personagem
- **Features:** Features de background são adicionadas automaticamente

### FeatDataTable

- **Pré-requisitos:** Sistema valida pré-requisitos antes de permitir seleção
- **Disponibilidade:** Apenas feats sem pré-requisitos de nível aparecem no nível 1

### Point Buy System

- **Validação:** Point Buy é validado por `FPointBuyValidator` que verifica se não excede 27 pontos e se todos os scores estão no range [8, 15]
- **Aplicação:** Point Buy é aplicado por `FPointBuyMotor` que ajusta automaticamente se exceder 27 pontos
- **Cálculo Final:** Ability scores finais são calculados via `FCharacterSheetCore` que orquestra `FRaceBonusMotor` e `FPointBuyMotor` sequencialmente

---

## 📋 Boas Práticas

1. **Nomes consistentes:** Use nomes consistentes entre Data Tables (ex: "Human" em RaceDataTable deve corresponder a "Human" em CharacterSheetDataAsset)
2. **Row Names:** Use o campo `Name` como Row Name (facilita busca com `FindRow`)
3. **Localização:** Use `FText` para descrições (suporta localização)
4. **Dados estruturados:** Use `TMap<FName, FString>` para dados programáticos quando necessário
5. **Validação:** Sempre valide JSON antes de importar (use validação JSON online)

---

## ⚠️ Troubleshooting

### Problema: Sub-raça não aparece no dropdown

**Solução:** Verifique se a sub-raça está listada em `SubraceNames` da raça base no RaceDataTable.

### Problema: Feat não aparece para Variant Human

**Solução:** Verifique se o feat não tem pré-requisitos de nível ou ability score que o personagem não atende.

### Problema: Bônus raciais não aplicando

**Solução:** Verifique se `AbilityName` corresponde exatamente aos nomes dos atributos ("Strength", "Dexterity", etc.) ou "Custom" para Variant Human.

---

**Navegação:** [← Visão Geral](visao-geral.md) | [→ RaceDataTable](personagem/race-datatable.md)

**Última atualização:** 2024-12-27
