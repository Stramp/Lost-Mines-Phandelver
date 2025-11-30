# 4.2. Algoritmos de Combate

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Criação da seção de algoritmos de combate |

---

## 📊 Fluxo de Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Diagrama de Fluxo</b></summary>

> ```mermaid
> graph LR
>     A[Atacante] -->|1. PerformAttack| B[Verificar Acerto]
>     B -->|Natural 20| C[Crítico]
>     B -->|Natural 1| D[Erro]
>     B -->|Attack Roll >= AC| E[Acertou]
>     B -->|Attack Roll < AC| D
>     C -->|2. CalculateDamage| F[Calcular Dano]
>     E -->|2. CalculateDamage| F
>     F -->|3. ApplyResistance| G[Aplicar Resistências]
>     G -->|4. TakeDamage| H[Alvo]
>     D -->|Fim| I[Sem Dano]
>
>     style A fill:#e3f2fd
>     style H fill:#ffcdd2
>     style C fill:#ffcdd2
>     style E fill:#c8e6c9
>     style D fill:#ffcdd2
> ```
>
> **📖 [Ver pseudocódigo técnico completo](../../08-pseudocodigo/combate/combat-system.md)**

</details>

---

## 📖 Algoritmos Disponíveis

- **[AC Calculation Algorithm](ac-calculation-algorithm.md)** - Como calcular AC tecnicamente
- **[Damage Calculation Algorithm](damage-calculation-algorithm.md)** - Como calcular dano tecnicamente
- **[Attack Roll Algorithm](attack-roll-algorithm.md)** - Como verificar acerto tecnicamente

---

**Navegação:** [← Voltar](../index.md) | [→ Próxima Seção: Progressão](../progressao/index.md)

**Última atualização:** 2024-12-27
