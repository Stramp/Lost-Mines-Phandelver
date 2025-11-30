# 2. Referência de API

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔌 API Reference</b></summary>

> Esta seção contém a referência completa de todas as classes, funções e componentes disponíveis no projeto.

</details>

---

## 📊 Estrutura da API

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Diagrama da Estrutura</b></summary>

> ```mermaid
> graph TB
>     subgraph Components["📦 Componentes"]
>         CDC[CharacterDataComponent<br/>💾 Dados Replicáveis]
>         CSC[CharacterSheetComponent<br/>🔗 Bridge]
>         UI1[InventoryWidget<br/>🎒 Inventário]
>         UI2[HUDWidget<br/>📊 HUD]
>         UI3[MenuWidget<br/>📋 Menus]
>     end
>
>     subgraph Motors["⚙️ Motores"]
>         PBM[PointBuyMotor<br/>📊 Point Buy]
>         MCM[MulticlassMotor<br/>🔄 Multiclass]
>         RBM[RaceBonusMotor<br/>🏛️ Race Bonus]
>     end
>
>     subgraph Helpers["🛠️ Helpers"]
>         CH[ComponentHelpers<br/>🔍 Busca Componentes]
>         CALC[CalculationHelpers<br/>📐 Cálculos]
>         VAL[ValidationHelpers<br/>✅ Validações]
>         DT[DataTableHelpers<br/>📊 Data Tables]
>         FMT[FormattingHelpers<br/>📝 Formatação]
>         CHOICE[ChoiceHelpers<br/>🎯 Escolhas]
>         CSH[CharacterSheetHelpers<br/>📋 Character Sheet]
>         PROF[ProficiencyHelpers<br/>⚔️ Proficiências]
>         CSDAH[CharacterSheetDataAssetHelpers<br/>🔧 Data Asset]
>     end
>
>     CSC -->|Usa| PBM
>     CSC -->|Usa| MCM
>     CSC -->|Usa| RBM
>     CSC -->|SetData| CDC
>     CDC -->|Usa| CH
>     PBM -->|Usa| CALC
>     PBM -->|Usa| VAL
>     MCM -->|Usa| DT
>     UI1 -->|Usa| CDC
>     UI2 -->|Usa| CDC
>
>     style Components fill:#e3f2fd
>     style Motors fill:#fff3e0
>     style Helpers fill:#f3e5f5
> ```
>
> **📖 [Ver documentação completa da API](componentes/index.md)**

</details>

---

## Navegação

- [2.1. Componentes](componentes/index.md) - Componentes principais e UI
- [2.2. Motores](motores/index.md) - Motores de criação de personagem
- [2.3. Helpers](helpers/index.md) - Funções utilitárias reutilizáveis
- [2.4. Interfaces](interfaces/) (a ser documentado)

---

**Navegação Principal:** [← Seção Anterior: Arquitetura](../01-arquitetura/index.md) | [→ Próxima Seção: Dados](../03-dados/index.md)

---

**Última atualização:** 2024-12-27
