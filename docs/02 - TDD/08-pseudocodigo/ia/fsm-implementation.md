# Implementação Técnica - FSM (Finite State Machine)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Extraído do GDD para TDD |

---

## Estrutura de Dados Técnica

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Classe Base: AIStateMachine</b></summary>

> **Implementação C++ (Unreal Engine 5.7):**
>
> ```cpp
> enum class EAIState {
>     Idle,
>     Patrol,
>     Alert,
>     Investigation,
>     Combat,
>     Flee
> };
>
> class AIStateMachine {
>     EAIState CurrentState;
>     float DetectionRadius;
>     float FleeHealthThreshold;
>     float InvestigationDuration;
>     // ... métodos de transição
> };
> ```
>
> **Comportamentos Específicos:**
>
> - Herdar de `AIStateMachine` base
> - Implementar transições específicas por tipo de inimigo
> - Configurar valores de detecção e fuga por CR

</details>

---

## Referências

- **GDD:** [FSM - Máquinas de Estados Finitos](../../../01%20-%20GDD/03-ia-comportamento/fsm.md) - Descrição conceitual dos estados
- **Arquitetura:** [Architecture](../../../01-arquitetura/principios/architecture.md) - Arquitetura completa do projeto

---

**Última atualização:** 2024-12-27
