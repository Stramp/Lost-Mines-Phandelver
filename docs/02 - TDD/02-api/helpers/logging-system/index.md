# Sistema de Logging (FLoggingSystem)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de api.md para arquivo dedicado |

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 FLoggingSystem - Sistema Centralizado de Logging</b></summary>

> **Caminho:** `Source/MyProject2/Logging/LoggingSystem.h`
>
> **Responsabilidade:** Sistema centralizado de logging com suporte a popups no editor e throttle para evitar poluição visual.

</details>

## Métodos de Logging Padrão

#### LogDebug()
```cpp
static void LogDebug(const FLogContext &Context, const FString &Message);
```
- **Descrição:** Log temporário para debug (não persiste)
- **Uso:** Durante desenvolvimento para rastreamento
- **Popup:** Não mostra popup no editor

#### LogInfo()
```cpp
static void LogInfo(const FLogContext &Context, const FString &Message);
```
- **Descrição:** Log de informação geral (não persiste)
- **Uso:** Eventos normais do sistema
- **Popup:** Não mostra popup no editor

#### LogWarning()
```cpp
static void LogWarning(const FLogContext &Context, const FString &Message, bool bRequiresAction = true);
```
- **Descrição:** Log de aviso sobre configuração incorreta (persiste até correção)
- **Parâmetros:**
  - `bRequiresAction`: Se `true`, mostra popup no editor e adiciona `[REQUIRES ACTION]` ao log
- **Popup:** Mostra popup se `bRequiresAction = true`

#### LogError()
```cpp
static void LogError(const FLogContext &Context, const FString &Message, bool bShowInEditor = true);
```
- **Descrição:** Log de erro crítico que requer ação humana (persiste permanentemente)
- **Parâmetros:**
  - `bShowInEditor`: Se `true`, mostra popup no editor
- **Popup:** Mostra popup se `bShowInEditor = true`

#### LogFatal()
```cpp
static void LogFatal(const FLogContext &Context, const FString &Message);
```
- **Descrição:** Log de erro fatal que impede funcionamento (persiste permanentemente)
- **Popup:** Sempre mostra popup no editor

## Métodos de Logging com Throttle

**⚠️ IMPORTANTE:** Use métodos com throttle quando múltiplos logs podem ser disparados rapidamente (ex: loops de validação).

#### LogWarningWithThrottledPopup()
```cpp
static void LogWarningWithThrottledPopup(const FLogContext &Context, const FString &Message, float ThrottleDelay = 0.5f);
```
- **Descrição:** Log de warning com popup throttled (limita frequência de popups no editor)
- **Comportamento:**
  - `UE_LOG` é **imediato** (sempre executa)
  - Popup visual é **throttled** (limitado a 0.5s entre popups por padrão)
- **Uso:** Quando múltiplos warnings podem ser disparados rapidamente (ex: loops de validação)
- **Exemplo:** Validação de múltiplos ability scores em loop

#### LogErrorWithThrottledPopup()
```cpp
static void LogErrorWithThrottledPopup(const FLogContext &Context, const FString &Message, float ThrottleDelay = 0.5f);
```
- **Descrição:** Log de erro com popup throttled (limita frequência de popups no editor)
- **Comportamento:**
  - `UE_LOG` é **imediato** (sempre executa)
  - Popup visual é **throttled** (limitado a 0.5s entre popups por padrão)
- **Uso:** Quando múltiplos erros podem ser disparados rapidamente (ex: loops de validação)
- **Exemplo:** Validação de múltiplos ability scores em loop

## Quando Usar Throttle

**✅ Use métodos com throttle quando:**
- Loops de validação que podem gerar múltiplos erros
- Validações em arrays que podem falhar várias vezes
- Processamento em lote que pode gerar muitos popups

**❌ NÃO use throttle quando:**
- Erro único e crítico (use `LogError` normal)
- Erro que precisa ser visto imediatamente
- Logs informativos (use `LogInfo` ou `LogDebug`)

## Exemplo de Uso

```cpp
// ❌ ERRADO - Pode gerar múltiplos popups em loop
for (const FName &AbilityName : RequiredAbilities)
{
    if (!AbilityScores.Contains(AbilityName))
    {
        FLoggingSystem::LogError(Context, FString::Printf(TEXT("Ability Score '%s' está faltando!"), *AbilityName.ToString()), true);
    }
}

// ✅ CORRETO - Popup throttled, log imediato
for (const FName &AbilityName : RequiredAbilities)
{
    if (!AbilityScores.Contains(AbilityName))
    {
        FLoggingSystem::LogErrorWithThrottledPopup(Context, FString::Printf(TEXT("Ability Score '%s' está faltando!"), *AbilityName.ToString()), 0.5f);
    }
}
```

## FLogContext

```cpp
struct FLogContext
{
    FString Module;      // Módulo/sistema (ex: "CharacterSheet", "Validation")
    FString Function;    // Função/componente (ex: "ValidateDataIntegrity")
    FString AssetName;   // Asset relacionado (opcional)
    int32 LineNumber;    // Linha do código (opcional, para debug)
};
```

**Uso:**
```cpp
FLogContext Context(TEXT("CharacterSheet"), TEXT("ValidateDataIntegrity"));
FLoggingSystem::LogError(Context, TEXT("Raça não foi selecionada!"), true);
```

## Categorias de Log

O sistema usa categorias automáticas baseadas no módulo:
- `LogMyProject2DataTable` - Para módulos de Data Table
- `LogMyProject2Validation` - Para módulos de validação
- `LogMyProject2Multiclass` - Para módulos de multiclass

**Status de Testes:** Sistema de logging não requer testes (wrapper de UE_LOG e notificações do editor)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[Helpers](../index.md)** - Índice de helpers
> - **[Índice da API](../../index.md)** - Organização da API

</details>
