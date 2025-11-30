# 🎯 O Que Testar

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Sempre Testar</b></summary>

> **ALWAYS test:**
>
> - ✅ Helper/utility functions (em `Utils/`)
> - ✅ Funções puras (sem side effects)
> - ✅ Lógica de cálculo complexa
> - ✅ Validações e edge cases
> - ✅ Funções críticas de gameplay
>
> **Exemplos no projeto:**
>
> - `GetPrerequisites()` em `FeatDataTable.cpp` - ✅ 6 testes
> - `FindFeatRow()` em `DataTableHelpers.cpp` - ✅ 13 testes (melhorados)
> - `MeetsFeatPrerequisites()` em `CharacterSheetHelpers.cpp` - ✅ 36 testes
> - `CalculateAbilityModifier()` em `CalculationHelpers.cpp` - ✅ 28 testes
> - `CalculateProficiencyBonus()` em `CalculationHelpers.cpp` - ✅ 28 testes
> - `ValidateAbilityScoreRange()` em `ValidationHelpers.cpp` - ✅ 35 testes
> - `ValidatePointBuy()` em `ValidationHelpers.cpp` - ✅ 35 testes
> - `FormatRaceDisplay()` em `FormattingHelpers.cpp` - ✅ 10 testes
> - `ParseOptionsString()` em `ChoiceHelpers.cpp` - ✅ 7 testes
> - `FindCharacterDataComponent()` em `ComponentHelpers.cpp` - ✅ 3 testes

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❌ Não Precisa Testar</b></summary>

> **Don't need to test:**
>
> - ❌ Simple Getters/Setters
> - ❌ Simple wrappers de Unreal API
> - ❌ Código gerado automaticamente

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](../index.md)
- [🏗️ Estrutura de Testes](./estrutura-testes.md)
- [💻 Padrões de Teste](./padroes-teste.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
