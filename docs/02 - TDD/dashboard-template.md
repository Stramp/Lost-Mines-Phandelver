# TDD Dashboard - MyProject2

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral Técnica</b></summary>

> **Projeto:** Documentação técnica completa da implementação do MyProject2.
>
> **Última Atualização:** 2024-12-27
>
> **Status:** ✅ **98% Completo** - 6/7 fases concluídas

</details>

---

## 🏗️ Estrutura Técnica

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Seções Principais</b></summary>

> - **[1. Arquitetura](01-arquitetura/index.md)** - Princípios, sistemas e camadas
> - **[2. API](02-api/index.md)** - Referência completa de componentes, motores e helpers
> - **[3. Dados](03-dados/index.md)** - Arquitetura de dados e Data Tables
> - **[4. Regras D&D Algorítmicas](04-regras-dnd/index.md)** - Algoritmos técnicos D&D 5e
> - **[5. Guias](05-guias/index.md)** - Guias práticos de setup, uso e testes
> - **[8. Pseudocódigo Técnico](08-pseudocodigo/index.md)** - Implementações técnicas

</details>

---

## 📊 Arquitetura em 4 Camadas

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Diagrama Visual das Camadas</b></summary>

> ```mermaid
> graph TB
>     subgraph Layer1["📝 Camada 1: Data Assets (Editor)"]
>         DA[UCharacterSheetDataAsset<br/>⚙️ Configuração Estática<br/>📋 EditDefaultsOnly]
>     end
>
>     subgraph Layer2["🌉 Camada 2: Bridge Components (Server)"]
>         BC[UCharacterSheetComponent<br/>🔗 Ponte Data → Runtime<br/>📋 Aplica Regras]
>     end
>
>     subgraph Layer3["💾 Camada 3: Runtime Data (Replicável)"]
>         RD[UCharacterDataComponent<br/>📊 Dados Replicáveis<br/>🔄 DOREPLIFETIME]
>     end
>
>     subgraph Layer4["⚡ Camada 4: Feature Components (Específicos)"]
>         FC1[USpellcastingComponent<br/>🔮 Spellcasting]
>         FC2[USecondWindComponent<br/>💪 Second Wind]
>         FC3[UActionSurgeComponent<br/>⚔️ Action Surge]
>     end
>
>     DA -->|InitializeFromDataAsset| BC
>     BC -->|SetData| RD
>     RD -->|Usa dados| FC1
>     RD -->|Usa dados| FC2
>     RD -->|Usa dados| FC3
>
>     style Layer1 fill:#e3f2fd
>     style Layer2 fill:#fff3e0
>     style Layer3 fill:#f3e5f5
>     style Layer4 fill:#e8f5e9
>     style DA fill:#bbdefb
>     style BC fill:#ffe0b2
>     style RD fill:#ce93d8
>     style FC1 fill:#c8e6c9
>     style FC2 fill:#c8e6c9
>     style FC3 fill:#c8e6c9
> ```
>
> **📖 [Ver documentação completa das camadas](01-arquitetura/camadas/index.md)**

</details>

---

## 🔄 Fluxo de Dados Completo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Editor → Runtime → Cliente</b></summary>

> ```mermaid
> graph TB
>     subgraph Editor["📝 EDITOR"]
>         DA[CharacterSheetDataAsset<br/>Configuração]
>         subgraph CreateSheet["CreateSheet/ - Motores"]
>             Core[CharacterSheetCore<br/>Orquestrador]
>             RBM[RaceBonusMotor]
>             PBM[PointBuyMotor]
>             MCM[MulticlassMotor]
>         end
>         DA -->|Recalculate| Core
>         Core -->|Aplica| RBM
>         Core -->|Aplica| PBM
>         Core -->|Aplica| MCM
>     end
>
>     subgraph Server["🖥️ RUNTIME - SERVIDOR"]
>         SC[CharacterSheetComponent<br/>Aplica Regras]
>         DC[CharacterDataComponent<br/>Dados Replicáveis]
>         SC -->|InitializeFromDataAsset| DA
>         SC -->|SetData| DC
>     end
>
>     subgraph Client["💻 RUNTIME - CLIENTE"]
>         DCC[CharacterDataComponent<br/>Recebe Dados]
>         FC[Feature Components<br/>Usa Dados]
>         DCC -->|Usa| FC
>     end
>
>     DC -->|DOREPLIFETIME| DCC
>
>     style Editor fill:#e1f5ff
>     style Server fill:#fff4e1
>     style Client fill:#e8f5e9
> ```
>
> **📖 [Ver fluxo de dados completo](01-arquitetura/fluxo-dados.md)**

</details>

---

## 🔗 Navegação Rápida

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Documentação Relacionada</b></summary>

> - **[GDD Dashboard](../01%20-%20GDD/dashboard-template.md)** - Game Design Document
> - **[Planning](../02%20-%20Planning/index.md)** - Planejamento e roadmaps
> - **[Home](../../README.md)** - Visão geral do projeto

</details>

---

**Última atualização:** 2024-12-27
