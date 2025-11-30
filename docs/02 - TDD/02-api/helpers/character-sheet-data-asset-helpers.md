# CharacterSheetDataAssetHelpers

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de CharacterSheetDataAsset</b></summary>

> **Caminho:** `Source/MyProject2/Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h`
>
> **Responsabilidade:** Funções helper reutilizáveis para `CharacterSheetDataAsset`, seguindo princípios de Clean Code e Design Patterns.
>
> **Características:**
>
> - Funções estáticas puras e testáveis
> - Seguem princípios de Clean Code (DRY, Single Responsibility, Testability)
> - Status de Testes: ✅ 18 testes implementados (`CharacterSheetDataAssetHelpersTests.cpp`)

</details>

---

## 📐 Estrutura da Classe

```cpp
class FCharacterSheetDataAssetHelpers
{
public:
    // Variant Human Helpers
    static void ResetVariantHumanChoices(UCharacterSheetDataAsset* Asset);

    // Ability Scores Helpers
    static TMap<FName, int32> CreateAbilityScoresMap(...);
    static TArray<int32> CreateAttributesArray(...);

    // Point Buy Helpers
    static void UpdatePointBuyFromFinalAllocation(...);

    // Property Validation Helpers
    static bool IsCalculatedProperty(FName PropertyName);

    // Handler Helpers
    static bool ValidateAsset(UCharacterSheetDataAsset* Asset);
    static void ResetSubraceIfRaceChanged(...);
    static void LogDataTableStatus(...);
    static FString GetFormattedClassName(const FString& ClassName);
    static bool ExtractRequirementTag(...);
    static bool ParseRequirementTag(...);
    static FString GetFullAttributeName(const FString& AttributeAbbr);
    static bool HasRequirementTag(FName ClassName);
    static bool IsValidClassWithoutTag(FName ClassName);

    // Multiclass Helpers
    static void AdjustProgressionFallback(...);
    static bool DetectNestedMulticlassProperty(...);
    static bool DetectLevelInClassCorrections(...);

    // Data Table Type Validation Helpers
    static bool ValidateDataTableType(...);

    // Multiple Choice Feature Helpers
    static void ForEachMultipleChoiceFeature(...);
    static int32 GetMaxChoicesLimit(...);
    static bool CanAddChoice(...);
    static bool CleanInvalidAndDuplicateChoices(...);
};
```

---

## 🔧 Categorias de Funções

### Variant Human Helpers

Funções para gerenciar escolhas de Variant Human.

#### ResetVariantHumanChoices()

Reseta todas as escolhas de Variant Human quando a raça muda.

**Assinatura:**

```cpp
static void ResetVariantHumanChoices(UCharacterSheetDataAsset* Asset);
```

**Parâmetros:**

- `Asset` - Character Sheet Data Asset

**Descrição:**

Limpa `CustomAbilityScoreChoices`, `SelectedFeat` e `SelectedSkill` quando a raça não é mais Variant Human.

**Exemplo:**

```cpp
// Quando raça muda de Variant Human para outra raça
if (OldRace == TEXT("Variant Human") && NewRace != TEXT("Variant Human"))
{
    FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(Asset);
    // CustomAbilityScoreChoices, SelectedFeat e SelectedSkill são limpos
}
```

---

### Ability Scores Helpers

Funções para criar e manipular ability scores.

#### CreateAbilityScoresMap()

Cria um mapa de ability scores a partir dos valores finais.

**Assinatura:**

```cpp
static TMap<FName, int32> CreateAbilityScoresMap(
    int32 FinalStrength,
    int32 FinalDexterity,
    int32 FinalConstitution,
    int32 FinalIntelligence,
    int32 FinalWisdom,
    int32 FinalCharisma
);
```

**Retorno:**

- `TMap<FName, int32>` - Map de ability score names para valores finais

**Exemplo:**

```cpp
TMap<FName, int32> AbilityScores = FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(
    15,  // Strength
    13,  // Dexterity
    14,  // Constitution
    12,  // Intelligence
    10,  // Wisdom
    8    // Charisma
);

// Usado para validação de feats
bool bCanTakeFeat = CharacterSheetHelpers::MeetsFeatPrerequisites(FeatRow, AbilityScores);
```

#### CreateAttributesArray()

Cria array de atributos em ordem padrão [STR, DEX, CON, INT, WIS, CHA].

**Assinatura:**

```cpp
static TArray<int32> CreateAttributesArray(
    int32 FinalStrength,
    int32 FinalDexterity,
    int32 FinalConstitution,
    int32 FinalIntelligence,
    int32 FinalWisdom,
    int32 FinalCharisma
);
```

**Retorno:**

- `TArray<int32>` - Array de atributos em ordem padrão

**Exemplo:**

```cpp
TArray<int32> Attributes = FCharacterSheetDataAssetHelpers::CreateAttributesArray(
    15, 13, 14, 12, 10, 8
);
// Resultado: [15, 13, 14, 12, 10, 8]
```

---

### Point Buy Helpers

Funções para gerenciar Point Buy.

#### UpdatePointBuyFromFinalAllocation()

Atualiza campos Point Buy a partir de uma alocação final ajustada.

**Assinatura:**

```cpp
static void UpdatePointBuyFromFinalAllocation(
    UCharacterSheetDataAsset* Asset,
    const TMap<FName, int32>& FinalAllocation
);
```

**Parâmetros:**

- `Asset` - Character Sheet Data Asset a atualizar
- `FinalAllocation` - Map de ability score names para valores finais ajustados

**Exemplo:**

```cpp
// Quando Point Buy é ajustado automaticamente
TMap<FName, int32> AdjustedAllocation;
// ... ajuste de alocação ...

FCharacterSheetDataAssetHelpers::UpdatePointBuyFromFinalAllocation(Asset, AdjustedAllocation);
// PointBuyStrength, PointBuyDexterity, etc. são atualizados
```

---

### Property Validation Helpers

Funções para validar propriedades.

#### IsCalculatedProperty()

Verifica se a propriedade é calculada (não deve disparar handlers).

**Assinatura:**

```cpp
static bool IsCalculatedProperty(FName PropertyName);
```

**Parâmetros:**

- `PropertyName` - Nome da propriedade a verificar

**Retorno:**

- `bool` - true se a propriedade é calculada, false caso contrário

**Propriedades Calculadas:**

- `bIsVariantHuman`
- `bHasLanguageChoices`
- `bHasSubraces`
- `bCanShowSheet`

**Exemplo:**

```cpp
if (FCharacterSheetDataAssetHelpers::IsCalculatedProperty(PropertyName))
{
    // Não dispara handlers para propriedades calculadas (evita recursão)
    return;
}
```

---

### Handler Helpers

Funções auxiliares para handlers de propriedades.

#### ValidateAsset()

Valida se Asset é válido.

**Assinatura:**

```cpp
static bool ValidateAsset(UCharacterSheetDataAsset* Asset);
```

**Exemplo:**

```cpp
if (!FCharacterSheetDataAssetHelpers::ValidateAsset(Asset))
{
    return; // Asset inválido, aborta operação
}
```

#### ResetSubraceIfRaceChanged()

Reseta sub-raça quando raça principal muda.

**Assinatura:**

```cpp
static void ResetSubraceIfRaceChanged(UCharacterSheetDataAsset* Asset, FName PropertyName);
```

**Exemplo:**

```cpp
// Em PostEditChangeProperty
FCharacterSheetDataAssetHelpers::ResetSubraceIfRaceChanged(Asset, PropertyChangedEvent.Property->GetFName());
// Se SelectedRace mudou, SelectedSubrace é resetado para NAME_None
```

#### LogDataTableStatus()

Loga informações sobre status dos Data Tables.

**Assinatura:**

```cpp
static void LogDataTableStatus(UCharacterSheetDataAsset* Asset);
```

**Exemplo:**

```cpp
FCharacterSheetDataAssetHelpers::LogDataTableStatus(Asset);
// Loga quais Data Tables estão selecionados e quais faltam
```

---

### Requirement Tag Helpers

Funções para processar tags de requerimento em nomes de classes.

#### ExtractRequirementTag()

Extrai tag de requerimento do nome da classe.

**Assinatura:**

```cpp
static bool ExtractRequirementTag(const FString& ClassName, FString& OutTag);
```

**Exemplo:**

```cpp
FString ClassName = TEXT("[INT +3] Wizard");
FString Tag;
if (FCharacterSheetDataAssetHelpers::ExtractRequirementTag(ClassName, Tag))
{
    // Tag = "[INT +3]"
}
```

#### ParseRequirementTag()

Parseia tag de requerimento para obter atributo e valor faltante.

**Assinatura:**

```cpp
static bool ParseRequirementTag(
    const FString& Tag,
    FString& OutAttributeAbbr,
    int32& OutMissingValue
);
```

**Exemplo:**

```cpp
FString Tag = TEXT("[INT +3]");
FString AttributeAbbr;
int32 MissingValue;
if (FCharacterSheetDataAssetHelpers::ParseRequirementTag(Tag, AttributeAbbr, MissingValue))
{
    // AttributeAbbr = "INT"
    // MissingValue = 3
}
```

#### GetFullAttributeName()

Obtém nome completo do atributo a partir da abreviação.

**Assinatura:**

```cpp
static FString GetFullAttributeName(const FString& AttributeAbbr);
```

**Exemplo:**

```cpp
FString FullName = FCharacterSheetDataAssetHelpers::GetFullAttributeName(TEXT("INT"));
// Resultado: "Intelligence"
```

---

### Multiclass Helpers

Funções para gerenciar multiclassing.

#### AdjustProgressionFallback()

Ajusta array de Progression manualmente como fallback quando LoadClassProgression falha.

**Assinatura:**

```cpp
static void AdjustProgressionFallback(
    TArray<FMulticlassProgressEntry>* Progression,
    int32 LevelInClass
);
```

**Exemplo:**

```cpp
if (LoadClassProgressionFailed)
{
    FCharacterSheetDataAssetHelpers::AdjustProgressionFallback(&Progression, LevelInClass);
    // Progression é ajustado para ter LevelInClass entradas
}
```

#### DetectNestedMulticlassProperty()

Detecta se a propriedade mudada é uma propriedade aninhada dentro do array Multiclass.

**Assinatura:**

```cpp
static bool DetectNestedMulticlassProperty(
    const FPropertyChangedEvent& PropertyChangedEvent,
    FName& HandlerPropertyName
);
```

**Exemplo:**

```cpp
FName HandlerPropertyName;
if (FCharacterSheetDataAssetHelpers::DetectNestedMulticlassProperty(PropertyChangedEvent, HandlerPropertyName))
{
    // Propriedade aninhada detectada, usa handler específico
    HandleNestedMulticlassProperty(HandlerPropertyName);
}
```

---

### Data Table Type Validation Helpers

Funções para validar tipos de Data Tables.

#### ValidateDataTableType()

Valida tipo de Data Table específica e exibe popup de erro se tipo incorreto.

**Assinatura:**

```cpp
static bool ValidateDataTableType(
    UCharacterSheetDataAsset* Asset,
    UDataTable* DataTable,
    const FName& PropertyName,
    const FString& ExpectedTypeName,
    bool (*ValidationFunction)(UDataTable*)
);
```

**Exemplo:**

```cpp
bool bIsValid = FCharacterSheetDataAssetHelpers::ValidateDataTableType(
    Asset,
    Asset->RaceDataTable,
    GET_MEMBER_NAME_CHECKED(UCharacterSheetDataAsset, RaceDataTable),
    TEXT("FRaceDataRow"),
    DataTableHelpers::IsRaceDataTable
);

if (!bIsValid)
{
    // Data Table foi resetado para nullptr e popup de erro foi exibido
}
```

---

### Multiple Choice Feature Helpers

Funções para gerenciar features de múltiplas escolhas.

#### ForEachMultipleChoiceFeature()

Itera por todas as features de múltiplas escolhas (Tipo 3) em todas as entradas de multiclasse.

**Assinatura:**

```cpp
static void ForEachMultipleChoiceFeature(
    UCharacterSheetDataAsset* Asset,
    TFunctionRef<void(FMulticlassClassFeature& Feature, const TArray<FName>& ValidChoices)> Callback
);
```

**Exemplo:**

```cpp
FCharacterSheetDataAssetHelpers::ForEachMultipleChoiceFeature(
    Asset,
    [](FMulticlassClassFeature& Feature, const TArray<FName>& ValidChoices)
    {
        // Processa cada feature de múltiplas escolhas
        CleanInvalidChoices(Feature.SelectedChoices, ValidChoices);
    }
);
```

#### GetMaxChoicesLimit()

Obtém limite máximo de escolhas para uma feature.

**Assinatura:**

```cpp
static int32 GetMaxChoicesLimit(const FMulticlassClassFeature& Feature);
```

**Retorno:**

- `int32` - Limite máximo de escolhas, ou -1 se não há limite definido

**Exemplo:**

```cpp
int32 MaxChoices = FCharacterSheetDataAssetHelpers::GetMaxChoicesLimit(Feature);
if (MaxChoices > 0 && SelectedChoices.Num() >= MaxChoices)
{
    // Limite atingido, não pode adicionar mais escolhas
}
```

#### CanAddChoice()

Valida se uma escolha pode ser adicionada.

**Assinatura:**

```cpp
static bool CanAddChoice(
    FName Choice,
    const TArray<FName>& ValidChoices,
    const TArray<FName>& SelectedChoices,
    int32 MaxChoices
);
```

**Exemplo:**

```cpp
if (FCharacterSheetDataAssetHelpers::CanAddChoice(Choice, ValidChoices, SelectedChoices, MaxChoices))
{
    SelectedChoices.Add(Choice);
}
else
{
    ShowError(TEXT("Escolha inválida ou limite atingido"));
}
```

#### CleanInvalidAndDuplicateChoices()

Remove escolhas inválidas e duplicatas de SelectedChoices.

**Assinatura:**

```cpp
static bool CleanInvalidAndDuplicateChoices(
    TArray<FName>& SelectedChoices,
    const TArray<FName>& ValidChoices
);
```

**Retorno:**

- `bool` - true se houve mudanças (escolhas removidas), false caso contrário

**Exemplo:**

```cpp
bool bChanged = FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(
    Feature.SelectedChoices,
    ValidChoices
);

if (bChanged)
{
    // Escolhas foram limpas, atualizar UI
    RefreshFeatureDisplay();
}
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Resetar Variant Human ao Mudar Raça

```cpp
void HandleRaceChange(UCharacterSheetDataAsset* Asset, FName NewRace)
{
    // Se não é mais Variant Human, limpar escolhas
    if (NewRace != TEXT("Variant Human"))
    {
        FCharacterSheetDataAssetHelpers::ResetVariantHumanChoices(Asset);
    }
}
```

### Exemplo 2: Validar Feat com Ability Scores

```cpp
bool CanTakeFeat(UCharacterSheetDataAsset* Asset, FName FeatName)
{
    // Criar map de ability scores
    TMap<FName, int32> AbilityScores = FCharacterSheetDataAssetHelpers::CreateAbilityScoresMap(
        Asset->FinalStrength,
        Asset->FinalDexterity,
        Asset->FinalConstitution,
        Asset->FinalIntelligence,
        Asset->FinalWisdom,
        Asset->FinalCharisma
    );

    // Buscar row do feat
    FFeatDataRow* FeatRow = DataTableHelpers::FindFeatRow(FeatName, Asset->FeatDataTable);

    // Validar pré-requisitos
    return CharacterSheetHelpers::MeetsFeatPrerequisites(FeatRow, AbilityScores);
}
```

### Exemplo 3: Limpar Escolhas Inválidas de Features

```cpp
void CleanAllFeatureChoices(UCharacterSheetDataAsset* Asset)
{
    FCharacterSheetDataAssetHelpers::ForEachMultipleChoiceFeature(
        Asset,
        [](FMulticlassClassFeature& Feature, const TArray<FName>& ValidChoices)
        {
            // Limpar escolhas inválidas e duplicatas
            FCharacterSheetDataAssetHelpers::CleanInvalidAndDuplicateChoices(
                Feature.SelectedChoices,
                ValidChoices
            );
        }
    );
}
```

---

## 🧪 Testes

**Status:** ✅ 18 testes implementados (`CharacterSheetDataAssetHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ Variant Human Helpers
- ✅ Ability Scores Helpers
- ✅ Point Buy Helpers
- ✅ Property Validation Helpers
- ✅ Handler Helpers
- ✅ Requirement Tag Helpers
- ✅ Multiclass Helpers
- ✅ Data Table Validation Helpers
- ✅ Multiple Choice Feature Helpers

---

## 🔗 Integração com Outros Sistemas

### Uso em CharacterSheetDataAsset

- `PostEditChangeProperty()` - Usa vários helpers para processar mudanças
- Handlers - Usam helpers para validação e processamento
- Validators - Usam helpers para criar maps de ability scores

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Arquitetura - Clean Code](../../../01-arquitetura/principios/clean-code.md)** - Princípios de Clean Code (DRY, Single Responsibility, Testability)

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para operações específicas
- **CharacterSheetDataAsset:** Usa helpers para evitar duplicação de código

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Componentes - CharacterSheetDataAsset](../componentes/character-sheet-component/index.md)** - Componente que usa estes helpers
> - **[Helpers - CharacterSheetHelpers](character-sheet-helpers.md)** - Helpers relacionados
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← Voltar para Helpers](../index.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |
