# 📝 Nomenclatura de Testes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏷️ Formato</b></summary>

> **Formato:** `<TestSuite>.<FunctionName>_<Scenario>_<ExpectedResult>`
>
> **Exemplos:**
>
> - `MyProject2.Utils.ComponentHelpers.FindCharacterDataComponent_WithValidOwner_ReturnsComponent`
> - `MyProject2.Utils.ComponentHelpers.FindCharacterDataComponent_WithNullOwner_ReturnsNullptr`
> - `MyProject2.Data.Tables.FeatDataTable.GetPrerequisites_WithSinglePrerequisite_ReturnsArray`
> - `MyProject2.Data.Tables.FeatDataTable.GetPrerequisites_WithMultiplePrerequisites_ReturnsArray`
>
> **Padrão:** `<Módulo>.<Classe>.<Função>_<Condição>_<ResultadoEsperado>`

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [✅ Casos de Teste Obrigatórios](./casos-obrigatorios.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
