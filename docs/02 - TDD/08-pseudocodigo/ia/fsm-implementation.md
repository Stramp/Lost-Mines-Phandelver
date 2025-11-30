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

## 📖 Design Relacionado

Este documento implementa as seguintes regras de design:

- **[GDD: FSM - Máquinas de Estados Finitos](../../../../01%20-%20GDD/03-ia-comportamento/fsm.md)** - Diagramas de estado e gatilhos de transição
- **[GDD: Bestiário](../../../../01%20-%20GDD/03-ia-comportamento/bestiario.md)** - Comportamentos específicos por criatura
- **[GDD: IA e Comportamento](../../../../01%20-%20GDD/03-ia-comportamento/index.md)** - Visão geral do sistema de IA

**Separação de Responsabilidades:**

- **GDD:** Define O QUÊ (estados Ocioso, Alerta, Combate, Fuga) e PORQUÊ (comportamento realista de IA)
- **TDD:** Define COMO (classe `AIStateMachine`, enum `EAIState`, métodos de transição, estruturas C++)

---

## 🔗 Referências Técnicas

- **[Arquitetura](../../../01-arquitetura/principios/index.md)** - Arquitetura completa do projeto

---

**Última atualização:** 2024-12-27
