# Guia de Testes Automatizados - MyProject2

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🧪 Visão Geral</b></summary>

> Este guia explica como implementar e executar testes automatizados no projeto MyProject2 usando o **Automation Test Framework** do Unreal Engine 5.7.
>

</details>

## 📚 Referências Oficiais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Documentação Epic Games</b></summary>

> **Links principais da documentação oficial:**
>

> - **[Automation Test Framework](https://dev.epicgames.com/documentation/en-us/unreal-engine/automation-test-framework-in-unreal-engine)** - Visão geral do framework de testes
> - **[Escrevendo Testes em C](https://dev.epicgames.com/documentation/en-us/unreal-engine/write-cplusplus-tests-in-unreal-engine)** - Guia completo para escrever testes em C
> - **[Automation System Overview](https://dev.epicgames.com/documentation/en-us/unreal-engine/automation-system-in-unreal-engine)** - Visão geral do sistema de automação
> - **[Automation Specs (BDD-style)](https://dev.epicgames.com/documentation/en-us/unreal-engine/automation-specs-in-unreal-engine)** - Testes estilo BDD com Describe/It
>
> **Base de navegação:** `dev.epicgames.com/documentation/en-us/unreal-engine/`
>
</details>
---

## 🎯 O Que Testar

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
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❌ Não Precisa Testar</b></summary>

> **Don't need to test:**
>

> - ❌ Simple Getters/Setters
> - ❌ Simple wrappers de Unreal API
> - ❌ Código gerado automaticamente
>
</details>
---

## 🏗️ Estrutura de Testes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📁 Organização de Arquivos</b></summary>

> **Estrutura de diretórios:**
>

> ```
> Source/MyProject2/
> ├── Utils/
> │   ├── ComponentHelpers.h
> │   ├── ComponentHelpers.cpp
> │   └── Tests/
> │       └── ComponentHelpersTests.cpp
> ├── Data/Tables/
> │   ├── FeatDataTable.h
> │   ├── FeatDataTable.cpp
> │   └── Tests/
> │       └── FeatDataTableTests.cpp
> └── Tests/
> └── Integration/
> ├── CharacterCreationE2ETests.cpp
> └── README.md
> ```
>
> **Padrão:**
> - **Testes Unitários:** Cada módulo tem uma pasta `Tests/` com seus arquivos de teste (próximos ao código testado)
> - **Testes de Integração:** Centralizados em `Tests/Integration/` (testam fluxos completos entre múltiplos sistemas)
>
</details>
---

## 💻 Padrões de Teste

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Padrão 1: IMPLEMENT_SIMPLE_AUTOMATION_TEST</b></summary>

> **Para testes simples/unitários:**
>

> ```cpp
</details>
    #include "Misc/AutomationTest.h"
    #include "Utils/ComponentHelpers.h"

    IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FComponentHelpersTest,
    "MyProject2.Utils.ComponentHelpers.FindCharacterDataComponent",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter
    )

    bool FComponentHelpersTest::RunTest(const FString& Parameters)
    {
    // Arrange
    AActor* TestActor = NewObject<AActor>();
    UCharacterDataComponent* ExpectedComponent = NewObject<UCharacterDataComponent>(TestActor);
    TestActor->AddComponent(ExpectedComponent);

    // Act
    UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(TestActor);

    // Assert
    TestNotNull("Result should not be null", Result);
    TestEqual("Result should be the same component", Result, ExpectedComponent);

    return true;
    }
    ```

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Padrão 2: BEGIN_DEFINE_SPEC (BDD-style)</b></summary>

> **Para testes estilo BDD (Describe/It):**
>

> ```cpp
</details>
    #include "Misc/AutomationTest.h"
    #include "Utils/ComponentHelpers.h"

    BEGIN_DEFINE_SPEC(ComponentHelpersSpec, "MyProject2.Utils.ComponentHelpers",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

    AActor* TestActor;
    UCharacterDataComponent* TestComponent;

    END_DEFINE_SPEC(ComponentHelpersSpec)

    void ComponentHelpersSpec::Define()
    {
    BeforeEach([this]()
    {
    // Arrange: Criar Actor e Component para cada teste
    TestActor = NewObject<AActor>();
    TestComponent = NewObject<UCharacterDataComponent>(TestActor);
    TestActor->AddComponent(TestComponent);
    });

    AfterEach([this]()
    {
    // Cleanup após cada teste
    if (TestActor)
    {
    TestActor->ConditionalBeginDestroy();
    }
    });

    Describe("FindCharacterDataComponent", [this]()
    {
    It("should return component when owner has it", [this]()
    {
    // Act
    UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(TestActor);

    // Assert
    TestNotNull("Result should not be null", Result);
    TestEqual("Result should be the same component", Result, TestComponent);
    });

    It("should return nullptr when owner is null", [this]()
    {
    // Act
    UCharacterDataComponent* Result = ComponentHelpers::FindCharacterDataComponent(nullptr);

    // Assert
    TestNull("Result should be null", Result);
    });
    });
    }
    ```

---

## 🎯 Padrão AAA (Arrange-Act-Assert)

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
>
</details>
---

## 🏃 Executando Testes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🖥️ No Editor</b></summary>

> **Método 1: Automation Tool (GUI)**
>

> 1. Abra o Editor
> 2. Menu: **Window → Developer Tools → Automation Tool**
> 3. Selecione os testes desejados
> 4. Clique em **Start Tests**
>
> **Método 2: Linha de Comando (Terminal)**
>
> **Comando oficial da Epic Games:**
>
> ```batch
> UnrealEditor-Cmd.exe "F:\UNREAL GAME\MyProject2\MyProject2.uproject" ^
> -ExecCmds="Automation RunTests MyProject2" ^
> -unattended ^
> -nopause ^
> -nullrhi ^
> -NoSound ^
> -NoSplash ^
> -testexit="Automation Test Queue Empty" ^
> -log ^
> -stdout
> ```
>
> **Scripts do projeto:**
>
> ```bash
</details>
    # Todos os testes
    run_tests.bat

    # Teste específico
    run_tests.bat MyProject2.Data.Tables.FeatDataTable

    # Versão rápida otimizada
    run_tests_quick.bat
    ```

    **Nota:** A inicialização do Unreal Engine pode levar 1-2 minutos. Isso é normal.

    **Referência:** [Write C++ Tests](https://dev.epicgames.com/documentation/en-us/unreal-engine/write-cplusplus-tests-in-unreal-engine)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 CI/CD</b></summary>

> **Integração com GitHub Actions:**
>

> ```yaml
> - name: Run Tests
> run: |
> "C:\Program Files\Epic Games\UE_5.7\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
> "F:\UNREAL GAME\MyProject2\MyProject2.uproject"
> -ExecCmds="Automation RunTests MyProject2"
> -unattended
> -nopause
> -nullrhi
> -NoSound
> -NoSplash
> -testexit="Automation Test Queue Empty"
> -log
> -stdout
> ```
>
</details>
---

## 📝 Nomenclatura de Testes

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
>
</details>
---

## ✅ Casos de Teste Obrigatórios

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Para Helper Functions</b></summary>

> **ALWAYS test:**
>

> 1. **Valid case/happy path**
> - Função funciona com entrada válida
>
> 2. **Nullptr/null input**
> - Função lida corretamente com nullptr
>
> 3. **Not found case**
> - Função retorna valor apropriado quando não encontra
>
> **Exemplo para `FindFeatRow()`:**
>
> - ✅ Com FeatName válido → retorna row
> - ✅ Com FeatName nullptr → retorna nullptr
> - ✅ Com FeatName inexistente → retorna nullptr
> - ✅ Com FeatDataTable nullptr → retorna nullptr
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Para Funções de Cálculo</b></summary>

> **ALWAYS test:**
>

> 1. **Valores normais**
> - Função funciona com valores típicos
>
> 2. **Valores extremos**
> - 0, máximo, negativo (se aplicável)
>
> 3. **Valores inválidos**
> - nullptr, valores fora de range
>
> **Exemplo para `GetPrerequisites()`:**
>
> - ✅ Com string única → retorna array com 1 item
> - ✅ Com múltiplas strings (vírgula) → retorna array com N itens
> - ✅ Com string vazia → retorna array vazio
> - ✅ Sem chave "Prerequisites" → retorna array vazio
>
</details>
---

## 🎯 Regras de Teste

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
>
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
</details>
    > **"Se você pode remover a função sendo testada e o teste ainda passa, o teste está errado."**

    **Checklist:**

    - [ ] Valor esperado é hardcoded (não calculado)?
    - [ ] Teste chama a função real do módulo oficial?
    - [ ] Mock apenas simula dados (não implementa lógica)?
    - [ ] Teste falharia se o código estivesse errado?
    - [ ] Não há lógica de cálculo no teste?

    </details>

    </details>

    ## 📚 Referências do Projeto

    <details>
    <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Internos</b></summary>

    > **Guias e Documentação:**

    > - **[TDD Complete Guide](tdd-complete-guide.md)** - Guia completo de Test-Driven Development
    > - Ciclo Red-Green-Refactor
    > - Princípios fundamentais
    > - Quando aplicar TDD
    > - Erros comuns e anti-padrões
    > - Benefícios e boas práticas

    > **Regras e Padrões:**

    > - **[Regras de TDD](../../../.cursor/rules/test-driven-development.mdc)** - Regras obrigatórias de TDD do projeto
    > - **[Regras de Teste](../../../.cursor/rules/testing.mdc)** - Regras completas de teste do projeto
    > - **[Clean Code](../../../.cursor/rules/clean-code-mandatory.mdc)** - Princípios de Clean Code
    > - **[Arquitetura](../architecture.md)** - Arquitetura técnica do projeto

    > **Exemplos:**

    > - `Source/MyProject2/Utils/Tests/ComponentHelpersTests.cpp.example` - Exemplo de teste

---

> ## 🚀 Próximos Passos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Checklist de Implementação</b></summary>

> **Status atual:**
>

> - [x] Configurar módulo de testes no `.Build.cs` (AutomationTest adicionado)
> - [x] Criar estrutura de pastas `Tests/` em cada módulo
> - [x] Implementar testes para helpers críticos:
> - [x] `CalculationHelpers` - ✅ 28 testes
> - [x] `ValidationHelpers` - ✅ 35 testes
> - [x] `CharacterSheetHelpers` - ✅ 36 testes
> - [x] `DataTableHelpers` - ✅ 13 testes
> - [x] `FormattingHelpers` - ✅ 10 testes
> - [x] `ChoiceHelpers` - ✅ 7 testes
> - [x] `FeatDataTable` - ✅ 6 testes
> - [x] `ComponentHelpers` - ✅ 3 testes
> - [x] Executar testes no Editor (Automation Tool)
> - [ ] Integrar testes no CI/CD (planejado)
>
> **Total:** 275+ testes implementados e funcionando
>
</details>
---

## 💡 Dicas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Boas Práticas</b></summary>

> **Quando escrever testes:**
>

> - ✅ Criar nova função helper em `Utils/`
> - ✅ Implementar lógica de cálculo complexa
> - ✅ Refatorar código crítico
> - ✅ Corrigir bug (adicionar teste que reproduz o bug)
>
> **Quando pular testes:**
>
> - ❌ Código muito simples (getter/setter)
> - ❌ Wrapper direto de Unreal API
> - ❌ Código temporário (mas lembre-se: não deveria ter código temporário!)
>
</details>
---

## 🧪 Testes de Integração End-to-End

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Diferença: Unit Tests vs Integration Tests</b></summary>

> **Testes Unitários** (em `Utils/Tests/`, `Data/Tables/Tests/`, etc.):
>

> - Testam **funções isoladas**
> - Exemplo: `CalculateAbilityModifier(15)` retorna `+2`
> - Rápidos (< 1 segundo cada)
> - Não dependem de outros sistemas
>
> **Testes de Integração** (em `Tests/Integration/`):
>
> - Testam **fluxos completos** do sistema
> - Exemplo: Criar personagem completo → Validar tudo funcionou
> - Testam interação entre múltiplos componentes
> - Mais lentos (testam sistemas completos)
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Testes de Integração Implementados</b></summary>

> **CharacterCreationE2ETests.cpp** - Testa o fluxo completo de criação de personagem:
>

> 1. **Personagem Básico** - Raça, background, ability scores
> 2. **Variant Human Completo** - Feat, skill, custom ability scores
> 3. **Multiclasse Básico** - Múltiplas classes
> 4. **Tratamento de Erros** - DataAsset nullptr
>
> **Executar Testes de Integração:**
>
> ```bash
</details>
    # Todos os testes de integração
    run_tests.bat MyProject2.Integration

    # Teste específico
    run_tests.bat MyProject2.Integration.CharacterCreation
    ```

    **📖 Para mais detalhes, veja [Tests/Integration/README.md](../../../Source/MyProject2/Tests/Integration/README.md)**

---

## 📖 Benefícios

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Por Que Testar?</b></summary>

> **Benefícios:**
>

> - ✅ Detecta bugs antes de commitar
> - ✅ Confiança ao refatorar
> - ✅ Documentação viva (testes mostram como usar)
> - ✅ Facilita CI/CD
> - ✅ Melhora qualidade do código
> - ✅ Reduz regressões
>
</details>
