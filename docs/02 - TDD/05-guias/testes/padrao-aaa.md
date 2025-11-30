# 🎯 Padrão AAA (Arrange-Act-Assert)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Estrutura de Teste</b></summary>

> **Todo teste deve seguir o padrão AAA:**
>
> 1. **Arrange** - Preparar dados e contexto
> 2. **Act** - Executar a função sendo testada
> 3. **Assert** - Verificar o resultado
>
> **Exemplo:**
>
> ```cpp
> It("should return prerequisites from FeatureData", [this]()
> {
> // Arrange
> FFeatDataRow TestRow;
> TestRow.FeatureData.Add(TEXT("Prerequisites"), TEXT("Strength 13"));
>
> // Act
> TArray<FName> Prerequisites = TestRow.GetPrerequisites();
>
> // Assert
> TestEqual("Should have one prerequisite", Prerequisites.Num(), 1);
> TestEqual("Prerequisite should be Strength 13", Prerequisites[0], FName(TEXT("Strength 13")));
> });
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [💻 Padrões de Teste](./fundamentos/padroes-teste.md)
- [✅ Casos de Teste Obrigatórios](./casos-obrigatorios.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
