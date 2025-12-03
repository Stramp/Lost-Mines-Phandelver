# Testes de Integração End-to-End

## 📋 Visão Geral

Esta pasta contém **testes de integração end-to-end** que validam o fluxo completo do sistema, testando a interação entre múltiplos componentes e sistemas.

## 🎯 Diferença: Unit Tests vs Integration Tests

### Unit Tests (em `Utils/Tests/`, `Data/Tables/Tests/`, etc.)
- Testam **funções isoladas**
- Exemplo: `CalculateAbilityModifier(15)` retorna `+2`
- Rápidos (< 1 segundo cada)
- Não dependem de outros sistemas

### Integration Tests (aqui em `Tests/Integration/`)
- Testam **fluxos completos** do sistema
- Exemplo: Criar personagem completo → Validar tudo funcionou
- Testam interação entre múltiplos componentes
- Mais lentos (testam sistemas completos)

## 📁 Estrutura

```
Tests/Integration/
├── CharacterCreationE2ETests.cpp  # Testes de criação completa de personagem
└── README.md                       # Este arquivo
```

## 🧪 Como Usar

### Executar Todos os Testes de Integração

```bash
run_tests.bat MyProject2.Integration
```

### Executar Teste Específico

```bash
run_tests.bat MyProject2.Integration.CharacterCreation
```

### No Editor

1. **Window → Developer Tools → Automation Tool**
2. Filtre por `MyProject2.Integration`
3. Selecione os testes desejados
4. Clique em **Start Tests**

## 📝 Padrão de Teste

Todos os testes seguem o padrão **BEGIN_DEFINE_SPEC** (BDD-style):

```cpp
BEGIN_DEFINE_SPEC(CharacterCreationE2ESpec, "MyProject2.Integration.CharacterCreation",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Variáveis de teste aqui

END_DEFINE_SPEC(CharacterCreationE2ESpec)

void CharacterCreationE2ESpec::Define()
{
    BeforeEach([this]()
    {
        // Arrange: Preparar dados para cada teste
    });

    AfterEach([this]()
    {
        // Cleanup após cada teste
    });

    Describe("Cenário de Teste", [this]()
    {
        It("deve fazer algo específico", [this]()
        {
            // Act: Executar fluxo completo
            // Assert: Validar resultado final
        });
    });
}
```

## ✅ Testes Implementados

### CharacterCreationE2ETests.cpp

Testa o fluxo completo de criação de personagem:

1. **Personagem Básico** - Raça, background, ability scores
2. **Variant Human Completo** - Feat, skill, custom ability scores
3. **Multiclasse Básico** - Múltiplas classes
4. **Tratamento de Erros** - DataAsset nullptr

## 🚀 Próximos Testes a Implementar

- `MulticlassE2ETests.cpp` - Fluxo completo de multiclasse
- `PointBuyE2ETests.cpp` - Fluxo completo de Point Buy
- `VariantHumanE2ETests.cpp` - Fluxo completo de Variant Human

## 📚 Referências

- **[Guia de Testes](../../../docs/technical/guides/testing.md)** - Documentação completa
- **[Regras de Teste](../../../.cursor/rules/testing.mdc)** - Regras do projeto
