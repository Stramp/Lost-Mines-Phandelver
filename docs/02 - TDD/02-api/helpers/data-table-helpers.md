# DataTableHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Data Tables</b></summary>

> **Caminho:** `Source/MyProject2/Utils/DataTableHelpers.h`
>
> **Responsabilidade:** Busca de rows em Data Tables com fallback manual.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Centraliza lógica de busca que pode falhar com FindRow direto
> - Status de Testes: ✅ 23 testes implementados (`DataTableHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace DataTableHelpers
{
    // Ability Score Data Table Helpers
    FAbilityScoreDataRow* FindAbilityScoreRow(FName AbilityName, UDataTable* AbilityScoreDataTable);
    TArray<FName> GetAllAbilityScoreNames(UDataTable* AbilityScoreDataTable);

    // Race Data Table Helpers
    FRaceDataRow* FindRaceRow(FName RaceName, UDataTable* RaceDataTable);
    FRaceDataRow* FindSubraceRow(FName SubraceName, UDataTable* RaceDataTable);

    // Class Data Table Helpers
    FClassDataRow* FindClassRow(FName ClassName, UDataTable* ClassDataTable);

    // Feat Data Table Helpers
    FFeatDataRow* FindFeatRow(FName FeatName, UDataTable* FeatDataTable);
    FName ConvertFeatNameToFCID(FName FeatName, UDataTable* FeatDataTable);

    // Background Data Table Helpers
    FBackgroundDataRow* FindBackgroundRow(FName BackgroundName, UDataTable* BackgroundDataTable);

    // Proficiency Data Table Helpers
    FProficiencyDataRow* FindProficiencyRowByID(FName ProficiencyID, UDataTable* ProficiencyDataTable);
    TArray<FName> GetProficiencyNamesByType(UDataTable* ProficiencyDataTable, FName ProficiencyType);
    TArray<FName> GetAllSkillNames(UDataTable* ProficiencyDataTable);
    TArray<FName> GetAllLanguageNames(UDataTable* ProficiencyDataTable);

    // Feature Data Table Helpers
    FFeatureDataRow* FindFeatureRowByID(FName FeatureID, UDataTable* FeatureDataTable);

    // Data Table Type Validation Helpers
    bool ValidateDataTableRowStruct(UDataTable* DataTable, const UScriptStruct* ExpectedStruct);
    bool IsRaceDataTable(UDataTable* DataTable);
    bool IsClassDataTable(UDataTable* DataTable);
    bool IsBackgroundDataTable(UDataTable* DataTable);
    bool IsFeatDataTable(UDataTable* DataTable);
    bool IsFeatureDataTable(UDataTable* DataTable);
    bool IsProficiencyDataTable(UDataTable* DataTable);
    bool IsItemDataTable(UDataTable* DataTable);
}
```

---

## 🔧 Funções Principais

### FindRaceRow()

Busca row de raça no Data Table.

**Assinatura:**

```cpp
FRaceDataRow* FindRaceRow(FName RaceName, UDataTable* RaceDataTable);
```

**Parâmetros:**

- `RaceName` - Nome da raça para buscar
- `RaceDataTable` - Data Table de raças (pode ser nullptr)

**Retorno:**

- `FRaceDataRow*` - Row encontrado, ou `nullptr` se não encontrado ou Data Table inválido

**Descrição:**

Tenta `FindRow` direto primeiro, depois busca manual O(n) como fallback. Centraliza lógica de busca que pode falhar com `FindRow` direto.

**Exemplo:**

```cpp
UDataTable* RaceDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Races"));

FRaceDataRow* ElfRow = DataTableHelpers::FindRaceRow(TEXT("Elf"), RaceDataTable);

if (ElfRow)
{
    // Row encontrado, pode usar
    int32 DexBonus = ElfRow->DexterityBonus;
    UE_LOG(LogTemp, Warning, TEXT("Elf encontrado! Bônus DEX: %d"), DexBonus);
}
else
{
    // Row não encontrado ou Data Table inválido
    UE_LOG(LogTemp, Error, TEXT("Elf não encontrado no Data Table"));
}
```

---

### FindClassRow()

Busca row de classe no Data Table.

**Assinatura:**

```cpp
FClassDataRow* FindClassRow(FName ClassName, UDataTable* ClassDataTable);
```

**Parâmetros:**

- `ClassName` - Nome da classe para buscar
- `ClassDataTable` - Data Table de classes (pode ser nullptr)

**Retorno:**

- `FClassDataRow*` - Row encontrado, ou `nullptr` se não encontrado ou Data Table inválido

**Exemplo:**

```cpp
UDataTable* ClassDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Classes"));

FClassDataRow* FighterRow = DataTableHelpers::FindClassRow(TEXT("Fighter"), ClassDataTable);

if (FighterRow)
{
    // Row encontrado, pode usar
    int32 HitDie = FighterRow->HitDie;
    UE_LOG(LogTemp, Warning, TEXT("Fighter encontrado! Hit Die: d%d"), HitDie);
}
```

---

### FindFeatRow()

Busca row de feat no Data Table.

**Assinatura:**

```cpp
FFeatDataRow* FindFeatRow(FName FeatName, UDataTable* FeatDataTable);
```

**Parâmetros:**

- `FeatName` - Nome do feat para buscar
- `FeatDataTable` - Data Table de feats (pode ser nullptr)

**Retorno:**

- `FFeatDataRow*` - Row encontrado, ou `nullptr` se não encontrado ou Data Table inválido

**Exemplo:**

```cpp
UDataTable* FeatDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DT_Feats"));

FFeatDataRow* GreatWeaponMasterRow = DataTableHelpers::FindFeatRow(TEXT("Great Weapon Master"), FeatDataTable);

if (GreatWeaponMasterRow)
{
    // Row encontrado, pode usar
    UE_LOG(LogTemp, Warning, TEXT("Great Weapon Master encontrado!"));
}
```

---

### ValidateDataTableRowStruct()

Valida se DataTable tem RowStruct do tipo esperado.

**Assinatura:**

```cpp
bool ValidateDataTableRowStruct(UDataTable* DataTable, const UScriptStruct* ExpectedStruct);
```

**Parâmetros:**

- `DataTable` - Data Table a validar (pode ser nullptr)
- `ExpectedStruct` - Struct esperado (ex: `FRaceDataRow::StaticStruct()`)

**Retorno:**

- `bool` - true se RowStruct corresponde ao esperado, false caso contrário

**Exemplo:**

```cpp
UDataTable* SomeDataTable = ...;

// Validar se é RaceDataTable
bool bIsRaceDataTable = DataTableHelpers::ValidateDataTableRowStruct(
    SomeDataTable,
    FRaceDataRow::StaticStruct()
);

if (bIsRaceDataTable)
{
    // É RaceDataTable, pode usar FindRaceRow com segurança
    FRaceDataRow* RaceRow = DataTableHelpers::FindRaceRow(TEXT("Elf"), SomeDataTable);
}
else
{
    // Não é RaceDataTable, mostrar erro
    UE_LOG(LogTemp, Error, TEXT("Data Table não é do tipo RaceDataTable"));
}
```

---

### IsRaceDataTable() / IsClassDataTable() / etc.

Validações de tipo específicas para cada tipo de Data Table.

**Assinaturas:**

```cpp
bool IsRaceDataTable(UDataTable* DataTable);
bool IsClassDataTable(UDataTable* DataTable);
bool IsBackgroundDataTable(UDataTable* DataTable);
bool IsFeatDataTable(UDataTable* DataTable);
bool IsFeatureDataTable(UDataTable* DataTable);
bool IsProficiencyDataTable(UDataTable* DataTable);
bool IsItemDataTable(UDataTable* DataTable);
```

**Exemplo:**

```cpp
UDataTable* SomeDataTable = ...;

// Validar tipo antes de usar
if (DataTableHelpers::IsRaceDataTable(SomeDataTable))
{
    // É RaceDataTable, pode usar FindRaceRow
    FRaceDataRow* RaceRow = DataTableHelpers::FindRaceRow(TEXT("Elf"), SomeDataTable);
}
else if (DataTableHelpers::IsClassDataTable(SomeDataTable))
{
    // É ClassDataTable, pode usar FindClassRow
    FClassDataRow* ClassRow = DataTableHelpers::FindClassRow(TEXT("Fighter"), SomeDataTable);
}
else
{
    // Tipo desconhecido
    UE_LOG(LogTemp, Error, TEXT("Tipo de Data Table desconhecido"));
}
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Buscar Raça com Validação de Tipo

```cpp
UDataTable* RaceDataTable = CharacterSheetDataAsset->RaceDataTable;

// Validar tipo antes de usar
if (!DataTableHelpers::IsRaceDataTable(RaceDataTable))
{
    UE_LOG(LogTemp, Error, TEXT("RaceDataTable inválido!"));
    return;
}

// Buscar raça com segurança
FRaceDataRow* ElfRow = DataTableHelpers::FindRaceRow(TEXT("Elf"), RaceDataTable);

if (ElfRow)
{
    // Usar dados da raça
    int32 DexBonus = ElfRow->DexterityBonus;
    // ...
}
```

### Exemplo 2: Buscar Classe e Features

```cpp
UDataTable* ClassDataTable = CharacterSheetDataAsset->ClassDataTable;

// Buscar classe
FClassDataRow* FighterRow = DataTableHelpers::FindClassRow(TEXT("Fighter"), ClassDataTable);

if (FighterRow)
{
    // Buscar features do nível 3
    UDataTable* FeatureDataTable = CharacterSheetDataAsset->FeatureDataTable;
    FFeatureDataRow* SecondWindRow = DataTableHelpers::FindFeatureRowByID(
        TEXT("FC_SecondWind"),
        FeatureDataTable
    );

    if (SecondWindRow)
    {
        // Feature encontrada
        UE_LOG(LogTemp, Warning, TEXT("Second Wind encontrado!"));
    }
}
```

---

## 🧪 Testes

**Status:** ✅ 23 testes implementados (`DataTableHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ Busca de Rows (Race, Class, Feat, Background, etc.)
- ✅ Validação de Tipo de Data Table
- ✅ Fallback Manual (quando FindRow falha)
- ✅ Casos de Erro (nullptr, Data Table inválido, row não encontrado)

---

## 🔗 Integração com Outros Sistemas

### Uso em Motores

Estas funções são usadas pelos motores:

- `FRaceBonusMotor` - Usa `FindRaceRow()` e `FindSubraceRow()`
- `FMulticlassMotor` - Usa `FindClassRow()`
- `FPointBuyMotor` - Usa validações de tipo

### Uso em Componentes

- `CharacterSheetDataAsset` - Usa todas as funções de busca
- Widgets de UI - Buscam rows para exibir opções

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Data Tables](../../../05-guias/data-tables/index.md)** - Guia completo de Data Tables
- **[TDD: Arquitetura - Data-Driven](../../../01-arquitetura/principios/data-driven.md)** - Princípio Data-Driven

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para busca de rows
- **Data Table:** Armazena dados de configuração
- **Motor/Componente:** Usa helpers para buscar dados

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Motores - RaceBonusMotor](../motores/race-bonus-motor.md)** - Motor que usa estas funções
> - **[Guia - Data Tables](../../../05-guias/data-tables/index.md)** - Guia completo de Data Tables
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← ValidationHelpers](validation-helpers.md) | [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
