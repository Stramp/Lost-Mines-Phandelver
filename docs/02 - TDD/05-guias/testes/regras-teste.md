# 🎯 Regras de Teste

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Princípios Fundamentais</b></summary>

> **1. Testes Independentes**
>
> - Cada teste deve poder rodar isoladamente
> - Não depender de ordem de execução
> - Estado limpo entre testes
>
> **2. Testes Rápidos**
>
> - Evitar operações lentas (I/O, network)
> - Usar mocks quando necessário
> - Unit tests < 1 segundo cada
>
> **3. Testes Determinísticos**
>
> - Sempre produzem o mesmo resultado
> - Não usar valores aleatórios sem seed fixo
> - Evitar dependências de tempo/data
>
> **4. Um Teste = Uma Coisa**
>
> - Testar uma funcionalidade por vez
> - Nome do teste deve deixar claro o que está sendo testado
> - Se precisa testar múltiplas coisas, criar múltiplos testes

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚨 REGRA CRÍTICA: Testes NUNCA Podem Ter Lógica Interna</b></summary>

> **⚠️ REGRA ABSOLUTA:** Testes **NUNCA** podem passar com lógica interna. O teste deve **sempre** enviar dados para o módulo oficial que será testado.
>
> **Princípios:**
>
> 1. **Teste usa mocks para simular dados** - Não para implementar lógica
> 2. **Teste envia dados para módulo oficial** - Sempre chama a função real
> 3. **Teste não resolve por si só** - Não tem lógica interna que faça passar
> 4. **Valor esperado é hardcoded** - Não calculado internamente
>
> **❌ ERRADO - Teste com lógica interna:**
>
> ```cpp
> It("deve calcular modificador correto para score 15", [this]()
> {
> // ❌ ERRADO: Teste calcula o resultado internamente
> int32 Score = 15;
> int32 ExpectedModifier = (Score - 10) / 2;  // ❌ Lógica interna!
>
> int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);
>
> TestEqual("Modificador deve ser correto", Result, ExpectedModifier);
> // ❌ Este teste passaria mesmo se CalculateAbilityModifier estivesse errado!
> });
> ```
>
> **✅ CORRETO - Teste sem lógica interna:**
>
> ```cpp
> It("deve calcular modificador correto para score 15 (modificador +2)", [this]()
> {
> // ✅ CORRETO: Valor esperado é hardcoded, não calculado
> int32 Score = 15;
> int32 ExpectedModifier = 2;  // ✅ Valor fixo conhecido
>
> // Act: Envia para o módulo oficial
> int32 Result = CalculationHelpers::CalculateAbilityModifier(Score);
>
> // Assert: Compara com valor fixo
> TestEqual("Modificador para score 15 deve ser +2", Result, ExpectedModifier);
> // ✅ Este teste falha se CalculateAbilityModifier estiver errado!
> });
> ```
>
> **🎭 Uso Correto de Mocks:**
>
> **Mocks são para simular dados, NÃO para implementar lógica:**
>
> ```cpp
> // ✅ CORRETO: Mock simula dados conhecidos
> It("deve encontrar feat row quando existe", [this]()
> {
> // Arrange: Mock de DataTable com dados conhecidos
> UDataTable* MockDataTable = NewObject<UDataTable>();
> FFeatDataRow* TestRow = new FFeatDataRow();
> TestRow->FeatName = TEXT("Great Weapon Master");
> MockDataTable->AddRow(FName(TEXT("Great Weapon Master")), *TestRow);
>
> // Act: Envia para o módulo oficial
> FFeatDataRow* Result = DataTableHelpers::FindFeatRow(
> TEXT("Great Weapon Master"),
> MockDataTable  // ✅ Mock apenas simula dados, não implementa lógica
> );
>
> // Assert: Verifica resultado com valor conhecido
> TestNotNull("Deve encontrar row", Result);
> TestEqual("FeatName deve ser Great Weapon Master",
> Result->FeatName, TEXT("Great Weapon Master"));  // ✅ Valor fixo
> // ✅ Teste falha se FindFeatRow estiver errado!
> });
> ```
>
> **❌ ERRADO - Mock implementa lógica:**
>
> ```cpp
> // ❌ ERRADO: Teste implementa lógica de busca internamente
> It("deve encontrar feat row quando existe", [this]()
> {
> UDataTable* MockDataTable = NewObject<UDataTable>();
> // ... setup mock ...
>
> // ❌ ERRADO: Teste implementa lógica de busca
> FFeatDataRow* ExpectedRow = nullptr;
> for (auto& Pair : MockDataTable->GetRowMap())
> {
> if (Pair.Key == TEXT("Great Weapon Master"))
> {
> ExpectedRow = (FFeatDataRow*)Pair.Value;
> break;
> }
> }
>
> FFeatDataRow* Result = DataTableHelpers::FindFeatRow(TEXT("Great Weapon Master"), MockDataTable);
>
> TestEqual("Deve ser o mesmo row", Result, ExpectedRow);
> // ❌ Este teste passaria mesmo se FindFeatRow estiver errado!
> });
> ```
>
> **Regra de Ouro:**
>
> > **"Se você pode remover a função sendo testada e o teste ainda passa, o teste está errado."**
>
> **Checklist:**
>
> - [ ] Valor esperado é hardcoded (não calculado)?
> - [ ] Teste chama a função real do módulo oficial?
> - [ ] Mock apenas simula dados (não implementa lógica)?
> - [ ] Teste falharia se o código estivesse errado?
> - [ ] Não há lógica de cálculo no teste?

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](./index.md)
- [✅ Casos de Teste Obrigatórios](./casos-obrigatorios.md)
- [💡 Dicas](./dicas.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
