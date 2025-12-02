# 🧪 Guia de Testes de Integração - Unreal Engine 5.7

## 📋 O Que São Testes de Integração?

**Testes de Integração** verificam se múltiplos componentes funcionam juntos corretamente, testando o sistema como um todo, não apenas partes isoladas.

### Diferença: Unit Tests vs Integration Tests

| Aspecto | Unit Tests | Integration Tests |
|---------|------------|-------------------|
| **Escopo** | Função/Classe isolada | Múltiplos componentes juntos |
| **Dependências** | Mocks/Stubs | Dependências reais |
| **Mundo** | Não precisa de UWorld | Precisa de UWorld |
| **Velocidade** | Rápido (< 1s) | Mais lento (segundos) |
| **Complexidade** | Baixa | Alta |

---

## 🎯 Quando Usar Testes de Integração?

### ✅ Use Quando:

1. **Verificar integração entre componentes**
   - Exemplo: `MyCharacter` + `InputActionManagerComponent` + `CharacterMovementComponent`

2. **Testar fluxo completo**
   - Exemplo: Input → Move → Movement → Position

3. **Validar configuração**
   - Exemplo: Verificar se componentes estão configurados corretamente

4. **Testar comportamento em runtime**
   - Exemplo: Verificar se movimento funciona quando character está no mundo

### ❌ NÃO Use Para:

1. **Testar lógica isolada** → Use Unit Tests
2. **Testar cálculos matemáticos** → Use Unit Tests
3. **Testar helpers puros** → Use Unit Tests

---

## 🛠️ Como Criar Testes de Integração no Unreal Engine

### 1. Estrutura Básica

```cpp
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

BEGIN_DEFINE_SPEC(MyCharacterIntegrationSpec, "MyProject2.Characters.MyCharacter.Integration",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ClientContext)
    AMyCharacter* TestCharacter;
    UWorld* TestWorld;
END_DEFINE_SPEC(MyCharacterIntegrationSpec)

void MyCharacterIntegrationSpec::Define()
{
    BeforeEach([this]()
    {
        // Setup: Criar mundo e spawnar actors
        TestWorld = FAutomationTestFramework::Get().GetWorld();
        if (!TestWorld)
        {
            TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
        }
        
        FActorSpawnParameters SpawnParams;
        TestCharacter = TestWorld->SpawnActor<AMyCharacter>(...);
    });

    Describe("Feature Name", [this]()
    {
        It("should do something", [this]()
        {
            // Test implementation
        });
    });

    AfterEach([this]()
    {
        // Cleanup: Destruir actors
        if (TestCharacter)
        {
            TestCharacter->Destroy();
        }
    });
}
```

### 2. Flags Importantes

```cpp
EAutomationTestFlags::EditorContext      // Roda no editor
EAutomationTestFlags::ProductFilter      // Aparece no Test Runner
EAutomationTestFlags::ClientContext      // Precisa de contexto de cliente (para PlayerController)
```

### 3. Criar Mundo de Teste

```cpp
// Opção 1: Usar mundo existente
TestWorld = FAutomationTestFramework::Get().GetWorld();

// Opção 2: Criar novo mundo
TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
```

### 4. Spawnar Actors

```cpp
FActorSpawnParameters SpawnParams;
SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

TestCharacter = TestWorld->SpawnActor<AMyCharacter>(
    AMyCharacter::StaticClass(),
    FVector::ZeroVector,
    FRotator::ZeroRotator,
    SpawnParams
);
```

### 5. Simular Tick

```cpp
// Simular passagem de tempo
TestWorld->Tick(LEVELTICK_All, 0.1f);
```

---

## 📝 Exemplo Prático: Teste de Integração do MyCharacter

### Teste: Configuração de Componentes

```cpp
It("deve ter InputActionManager configurado corretamente", [this]()
{
    // Arrange
    if (!TestCharacter) { TestTrue("Character deve existir", false); return; }
    
    // Act & Assert
    UInputActionManagerComponent* InputManager = TestCharacter->InputActionManager;
    TestNotNull("InputActionManager deve existir", InputManager);
    
    if (InputManager)
    {
        TestTrue("Move Action deve estar registrada", 
                 InputManager->HasInputAction(EInputActionType::Move));
    }
});
```

### Teste: Modo de Rotação

```cpp
It("deve configurar modo 1 (movimento) corretamente", [this]()
{
    // Arrange
    UCharacterMovementComponent* MovementComp = TestCharacter->GetCharacterMovement();
    
    // Act
    TestCharacter->SetRotationMode(false); // Modo 1
    
    // Assert
    TestFalse("bOrientRotationToMovement deve ser false", 
              MovementComp->bOrientRotationToMovement);
    TestTrue("bUseControllerDesiredRotation deve ser true", 
             MovementComp->bUseControllerDesiredRotation);
});
```

---

## ⚠️ Limitações e Desafios

### 1. Funções Protected/Private

**Problema:** Funções `protected` ou `private` não podem ser chamadas diretamente em testes.

**Soluções:**

#### Opção A: Tornar Público para Testes

```cpp
// No header
public:
    UFUNCTION(BlueprintCallable, Category = "Character|Rotation")
    void SetRotationMode(bool bLookAtCamera) { UpdateRotationMode(bLookAtCamera); }

protected:
    void UpdateRotationMode(bool bLookAtCamera);
```

#### Opção B: Friend Class

```cpp
// No header
friend class FMyCharacterTestHelper;

// No arquivo de teste
class FMyCharacterTestHelper
{
public:
    static void TestUpdateRotationMode(AMyCharacter* Character, bool bLookAtCamera)
    {
        Character->UpdateRotationMode(bLookAtCamera);
    }
};
```

#### Opção C: Testar Através de Input Real

```cpp
// Simular input através do sistema Enhanced Input
// Mais complexo, mas mais realista
```

### 2. Simulação de Input

**Problema:** Simular input real é complexo no Unreal Engine.

**Soluções:**

- **Testar configuração** (mais fácil)
- **Testar através de funções públicas** (médio)
- **Usar Enhanced Input System** (complexo, mas realista)

### 3. Física e Movimento

**Problema:** Movimento depende de física, que pode variar.

**Soluções:**

- **Testar configuração** em vez de movimento real
- **Usar valores fixos** para física
- **Tolerar pequenas variações** em testes de movimento

---

## 🎯 Estratégias de Teste

### 1. Teste de Configuração (Mais Fácil)

**O que testa:** Verifica se componentes estão configurados corretamente.

```cpp
It("deve ter InputActionManager configurado", [this]()
{
    TestNotNull("InputActionManager deve existir", TestCharacter->InputActionManager);
});
```

**Vantagens:**
- ✅ Fácil de implementar
- ✅ Rápido
- ✅ Não depende de física

**Desvantagens:**
- ❌ Não testa comportamento em runtime
- ❌ Não testa integração real

### 2. Teste de Estado (Médio)

**O que testa:** Verifica se estado muda corretamente após ações.

```cpp
It("deve alternar modo de rotação", [this]()
{
    TestCharacter->SetRotationMode(false);
    TestFalse("Modo 1 configurado", MovementComp->bOrientRotationToMovement);
    
    TestCharacter->SetRotationMode(true);
    TestTrue("Modo 2 configurado", MovementComp->bOrientRotationToMovement);
});
```

**Vantagens:**
- ✅ Testa comportamento real
- ✅ Não depende de física
- ✅ Rápido

**Desvantagens:**
- ❌ Requer funções públicas
- ❌ Não testa input real

### 3. Teste de Integração Completa (Complexo)

**O que testa:** Testa fluxo completo com input real.

```cpp
// Mais complexo, requer simulação de input
// Geralmente feito com Functional Tests
```

**Vantagens:**
- ✅ Testa sistema completo
- ✅ Mais realista

**Desvantagens:**
- ❌ Muito complexo
- ❌ Lento
- ❌ Difícil de manter

---

## 📊 Exemplo Completo: MyCharacterIntegrationTests

O arquivo `MyCharacterIntegrationTests.cpp` contém exemplos de:

1. ✅ **Setup de mundo e actors**
2. ✅ **Teste de configuração de componentes**
3. ✅ **Teste de modo de rotação**
4. ✅ **Cleanup adequado**

**Localização:** `Source/MyProject2/Characters/Tests/MyCharacterIntegrationTests.cpp`

---

## 🚀 Como Executar Testes de Integração

### No Editor

1. **Abrir Test Runner**
   - `Window` → `Developer Tools` → `Test Automation`

2. **Filtrar Testes**
   - Buscar por `Integration`

3. **Executar**
   - Clicar em `Start Tests`

### Via Linha de Comando

```bash
UnrealEditor.exe MyProject.uproject -NullRHI -Unattended -NoSound -ExecCmds="Automation RunTests MyProject2.Characters.MyCharacter.Integration;Quit"
```

---

## ✅ Checklist para Testes de Integração

Antes de considerar um teste de integração "pronto":

- [ ] Mundo de teste criado corretamente?
- [ ] Actors spawnados corretamente?
- [ ] Componentes configurados corretamente?
- [ ] Testes são independentes (não dependem de ordem)?
- [ ] Cleanup adequado (actors destruídos)?
- [ ] Testes são determinísticos (mesmo resultado sempre)?
- [ ] Testes são rápidos (< 5 segundos cada)?

---

## 📚 Referências

- [Unreal Engine Automation Testing](https://docs.unrealengine.com/5.3/en-US/automation-technical-guide/)
- [Automation Spec Framework](https://docs.unrealengine.com/5.3/en-US/automation-spec-framework-in-unreal-engine/)
- [Functional Testing](https://docs.unrealengine.com/5.3/en-US/functional-testing-in-unreal-engine/)

---

**Última Atualização:** 2024-12-XX
**Versão:** 1.0.0

