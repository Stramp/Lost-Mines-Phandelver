# ProficiencyHelpers

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da documentação completa da API |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Helpers de Proficiências</b></summary>

> **Caminho:** `Source/MyProject2/Utils/ProficiencyHelpers.h`
>
> **Responsabilidade:** Leitura e processamento de `ProficiencyData` de proficiências.
>
> **Características:**
>
> - Funções puras e reutilizáveis seguindo princípios de Clean Code
> - Sem efeitos colaterais, parametrizadas e testáveis isoladamente
> - Todas as funções < 50 linhas
> - Status de Testes: ✅ 12 testes implementados (`ProficiencyHelpersTests.cpp`)

</details>

---

## 📐 Estrutura do Namespace

```cpp
namespace ProficiencyHelpers
{
    FString GetProficiencyDataValue(const FProficiencyDataRow& ProficiencyRow, const FName& Key);
    bool HasProficiencyData(const FProficiencyDataRow& ProficiencyRow);
    int32 GetProficiencyDataAsInt(const FProficiencyDataRow& ProficiencyRow, const FName& Key, int32 DefaultValue = -1);
    float GetProficiencyDataAsFloat(const FProficiencyDataRow& ProficiencyRow, const FName& Key, float DefaultValue = 0.0f);
    bool GetProficiencyDataAsBool(const FProficiencyDataRow& ProficiencyRow, const FName& Key, bool DefaultValue = false);
}
```

---

## 🔧 Funções Disponíveis

### GetProficiencyDataValue()

Obtém valor de ProficiencyData como FString.

**Assinatura:**

```cpp
FString GetProficiencyDataValue(const FProficiencyDataRow& ProficiencyRow, const FName& Key);
```

**Parâmetros:**

- `ProficiencyRow` - Row da proficiência
- `Key` - Chave a buscar (ex: "Damage", "AC")

**Retorno:**

- `FString` - Valor da chave ou string vazia se não existe

**Exemplo:**

```cpp
FProficiencyDataRow* WeaponRow = DataTableHelpers::FindProficiencyRowByID(TEXT("PW_Simple_Weapons"), ProficiencyDataTable);

if (WeaponRow)
{
    FString DamageValue = ProficiencyHelpers::GetProficiencyDataValue(*WeaponRow, TEXT("Damage"));
    // Resultado: Valor da chave "Damage" ou string vazia
}
```

---

### GetProficiencyDataAsInt()

Obtém valor de ProficiencyData como int32.

**Assinatura:**

```cpp
int32 GetProficiencyDataAsInt(const FProficiencyDataRow& ProficiencyRow, const FName& Key, int32 DefaultValue = -1);
```

**Parâmetros:**

- `ProficiencyRow` - Row da proficiência
- `Key` - Chave a buscar (ex: "AC", "MaxDexBonus")
- `DefaultValue` - Valor padrão se chave não existe ou inválida (padrão: -1)

**Retorno:**

- `int32` - Valor convertido para int32 ou DefaultValue

**Exemplo:**

```cpp
FProficiencyDataRow* ArmorRow = DataTableHelpers::FindProficiencyRowByID(TEXT("PW_Heavy_Armor"), ProficiencyDataTable);

if (ArmorRow)
{
    int32 AC = ProficiencyHelpers::GetProficiencyDataAsInt(*ArmorRow, TEXT("AC"), 10);
    // Resultado: Valor AC ou 10 se não encontrado
}
```

---

### GetProficiencyDataAsBool()

Obtém valor de ProficiencyData como bool.

**Assinatura:**

```cpp
bool GetProficiencyDataAsBool(const FProficiencyDataRow& ProficiencyRow, const FName& Key, bool DefaultValue = false);
```

**Parâmetros:**

- `ProficiencyRow` - Row da proficiência
- `Key` - Chave a buscar (ex: "StealthDisadvantage")
- `DefaultValue` - Valor padrão se chave não existe (padrão: false)

**Retorno:**

- `bool` - Valor convertido para bool ou DefaultValue

**Valores Válidos:**

- "true", "True", "1" → true
- "false", "False", "0" → false

**Exemplo:**

```cpp
FProficiencyDataRow* ArmorRow = DataTableHelpers::FindProficiencyRowByID(TEXT("PW_Heavy_Armor"), ProficiencyDataTable);

if (ArmorRow)
{
    bool bStealthDisadvantage = ProficiencyHelpers::GetProficiencyDataAsBool(
        *ArmorRow,
        TEXT("StealthDisadvantage"),
        false
    );
    // Resultado: true se armadura causa desvantagem em Stealth, false caso contrário
}
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Ler Dados de Proficiência de Arma

```cpp
// Buscar row de proficiência de arma
FProficiencyDataRow* WeaponRow = DataTableHelpers::FindProficiencyRowByID(
    TEXT("PW_Simple_Weapons"),
    ProficiencyDataTable
);

if (WeaponRow)
{
    // Ler dados da proficiência
    FString WeaponType = ProficiencyHelpers::GetProficiencyDataValue(*WeaponRow, TEXT("WeaponType"));
    int32 Damage = ProficiencyHelpers::GetProficiencyDataAsInt(*WeaponRow, TEXT("Damage"), 0);

    UE_LOG(LogTemp, Warning, TEXT("Tipo: %s, Dano: %d"), *WeaponType, Damage);
}
```

### Exemplo 2: Verificar Desvantagem em Stealth

```cpp
// Verificar se armadura causa desvantagem em Stealth
FProficiencyDataRow* ArmorRow = DataTableHelpers::FindProficiencyRowByID(
    TEXT("PW_Heavy_Armor"),
    ProficiencyDataTable
);

if (ArmorRow)
{
    bool bHasStealthDisadvantage = ProficiencyHelpers::GetProficiencyDataAsBool(
        *ArmorRow,
        TEXT("StealthDisadvantage"),
        false
    );

    if (bHasStealthDisadvantage)
    {
        // Aplicar desvantagem em Stealth checks
        ApplyStealthDisadvantage();
    }
}
```

---

## 🧪 Testes

**Status:** ✅ 12 testes implementados (`ProficiencyHelpersTests.cpp`)

**Categorias de Testes:**

- ✅ GetProficiencyDataValue (vários tipos de valores)
- ✅ GetProficiencyDataAsInt (conversão e valores padrão)
- ✅ GetProficiencyDataAsFloat (conversão e valores padrão)
- ✅ GetProficiencyDataAsBool (conversão de strings para bool)

---

## 🔗 Integração com Outros Sistemas

### Uso em Componentes

- `CharacterDataComponent` - Usa para ler dados de proficiências
- Sistemas de combate - Usam para cálculos de AC, dano, etc.

---

## 📖 Design Relacionado

Estas funções helper implementam as seguintes regras de design:

- **[TDD: Arquitetura - Data-Driven](../../../01-arquitetura/principios/data-driven.md)** - Princípio Data-Driven

**Separação de Responsabilidades:**

- **Helper:** Função pura e reutilizável para leitura de ProficiencyData
- **Data Table:** Armazena dados de proficiências
- **Componente:** Usa helper para ler dados

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers - DataTableHelpers](data-table-helpers.md)** - Busca de rows de proficiências
> - **[Guia - Data Tables](../../../05-guias/data-tables/index.md)** - Guia de Data Tables
> - **[Índice de Helpers](../index.md)** - Lista de todos os helpers

</details>

---

**Navegação:** [← ChoiceHelpers](choice-helpers.md) | [← Voltar para Helpers](../index.md)

**Última atualização:** 2024-12-27
