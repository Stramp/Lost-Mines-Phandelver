# Sistema de Logging

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 📝 FLoggingSystem - Sistema Centralizado de Logging

**Caminho:** `Source/MyProject2/Logging/LoggingSystem.h`

**Responsabilidade:** Sistema centralizado de logging com suporte a popups no editor e throttle para evitar poluição visual.

---

## Arquitetura do Sistema

O sistema de logging segue uma arquitetura em camadas:

1. **Camada de Interface:** Métodos públicos (`LogError`, `LogWarning`, etc.)
2. **Camada de Formatação:** Formatação de mensagens com contexto
3. **Camada de Output:** `UE_LOG` (sempre imediato) + Popups no editor (opcional, com throttle)

---

## Métodos Padrão vs Métodos com Throttle

**Métodos Padrão:**
- `LogError()`, `LogWarning()`, `LogFatal()` - Popup imediato
- Usados para erros únicos e críticos

**Métodos com Throttle:**
- `LogErrorWithThrottledPopup()`, `LogWarningWithThrottledPopup()` - Popup throttled
- Log (UE_LOG) sempre imediato, popup visual limitado a 0.5s entre chamadas
- Usados em loops de validação que podem gerar múltiplos erros

---

## Implementação do Throttle

O throttle usa `FTimerHandle` estático compartilhado:
- Cancela popup anterior quando nova chamada é feita
- Mostra apenas o último popup após delay (padrão: 0.5s)
- Mantém logging imediato (UE_LOG não é afetado)

**Benefícios:**
- ✅ Editor não fica poluído com múltiplos popups
- ✅ Logging sempre imediato (não perde informações)
- ✅ Configurável (delay ajustável)
- ✅ Nomes descritivos indicam comportamento exato

**📖 Para documentação completa da API, veja [API Reference](../../02-api/reference.md#sistema-de-logging-floggingsystem)**

---

**Navegação:** [← Estrutura de Arquivos](estrutura-arquivos.md) | [→ Referências](referencias.md)

**Última atualização:** 2024-12-27
