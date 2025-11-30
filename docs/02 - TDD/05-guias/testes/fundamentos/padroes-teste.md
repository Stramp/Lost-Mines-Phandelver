# 💻 Padrões de Teste

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Padrão 1: IMPLEMENT_SIMPLE_AUTOMATION_TEST</b></summary>

> **Para testes simples/unitários:**
>
> ```cpp
> #include "Misc/AutomationTest.h"
> #include "Utils/ComponentHelpers.h"
>
> IMPLEMENT_SIMPLE_AUTOMATION_TEST(
> FComponentHelpersTest,
> "MyProject2.Utils.ComponentHelpers.FindCharacterDataComponent",
> EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter
> )
>
> bool FComponentHelpersTest::RunTest(const FString& Parameters)
> {
> // Arrange
> AActor* TestActor = NewObject<AActor>();
> UCharacterDataComponent* ExpectedComponent = NewObject<UCharacterDataComponent>(TestActor);
> TestActor->AddComponent(ExpectedComponent);
>
> // Act
> UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(TestActor);
>
> // Assert
> TestNotNull("Result should not be null", Result);
> TestEqual("Result should be the same component", Result, ExpectedComponent);
>
> return true;
> }
> ```

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Padrão 2: BEGIN_DEFINE_SPEC (BDD-style)</b></summary>

> **Para testes estilo BDD (Describe/It):**
>
> ```cpp
> #include "Misc/AutomationTest.h"
> #include "Utils/ComponentHelpers.h"
>
> BEGIN_DEFINE_SPEC(ComponentHelpersSpec, "MyProject2.Utils.ComponentHelpers",
> EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
>
> AActor* TestActor;
> UCharacterDataComponent* TestComponent;
>
> END_DEFINE_SPEC(ComponentHelpersSpec)
>
> void ComponentHelpersSpec::Define()
> {
> BeforeEach([this]()
> {
> // Arrange: Criar Actor e Component para cada teste
> TestActor = NewObject<AActor>();
> TestComponent = NewObject<UCharacterDataComponent>(TestActor);
> TestActor->AddComponent(TestComponent);
> });
>
> AfterEach([this]()
> {
> // Cleanup após cada teste
> if (TestActor)
> {
> TestActor->ConditionalBeginDestroy();
> }
> });
>
> Describe("FindCharacterDataComponent", [this]()
> {
> It("should return component when owner has it", [this]()
> {
> // Act
> UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(TestActor);
>
> // Assert
> TestNotNull("Result should not be null", Result);
> TestEqual("Result should be the same component", Result, TestComponent);
> });
>
> It("should return nullptr when owner is null", [this]()
> {
> // Act
> UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(nullptr);
>
> // Assert
> TestNull("Result should be null", Result);
> });
> });
> }
> ```

</details>

---

## 🔗 Navegação

- [📚 Guia de Testes - Índice](../index.md)
- [🎯 O Que Testar](./o-que-testar.md)
- [🏗️ Estrutura de Testes](./estrutura-testes.md)
- [🎯 Padrão AAA](../padrao-aaa.md)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Documentação inicial extraída de testing.md |
