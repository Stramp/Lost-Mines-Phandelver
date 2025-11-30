# Fluxo de Dados

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🔄 Diagrama de Fluxo de Dados

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Fluxo Completo Editor → Servidor → Cliente</b></summary>

> ```mermaid
> graph TB
>     subgraph Editor["📝 EDITOR"]
>         DA[CharacterSheetDataAsset<br/>- Raça, Classe<br/>- Habilidades<br/>- Dados Estáticos]
>         subgraph Modules["Módulos Modulares"]
>             H[Handlers<br/>Processa mudanças]
>             V[Validators<br/>Valida dados]
>             U[Updaters<br/>Atualiza campos]
>         end
>         subgraph CreateSheet["CreateSheet/ - Motores"]
>             Core[CharacterSheetCore<br/>Orquestrador]
>             RBM[RaceBonusMotor<br/>Bônus Raciais]
>             PBM[PointBuyMotor<br/>Point Buy]
>         end
>         DA -->|PostEditChangeProperty| H
>         H -->|Valida| V
>         H -->|RecalculateFinalScoresFromDataAsset| Core
>         Core -->|Aplica| RBM
>         Core -->|Aplica| PBM
>         Core -->|Final Scores atualizados| DA
>         H -->|Atualiza| U
>         U -->|Dados atualizados| DA
>     end
>
>     subgraph Server["🖥️ RUNTIME - SERVIDOR"]
>         SC[CharacterSheetComponent<br/>- Aplica regras de raça<br/>- Aplica regras de classe<br/>- Carrega dados]
>         DC[CharacterDataComponent<br/>- Armazena dados replicáveis<br/>- Calcula atributos finais<br/>- Valida integridade]
>
>         SC -->|InitializeFromDataAsset| DA
>         SC -->|SetData| DC
>         DC -->|ValidateDataIntegrity| DC
>     end
>
>     subgraph Client["💻 RUNTIME - CLIENTE"]
>         DCC[CharacterDataComponent<br/>- Recebe dados replicados<br/>- Atualiza UI]
>         FC1[SpellcastingComponent]
>         FC2[SecondWindComponent]
>         FC3[ActionSurgeComponent]
>         FC4[Outros Feature Components]
>
>         DCC -->|Usa dados| FC1
>         DCC -->|Usa dados| FC2
>         DCC -->|Usa dados| FC3
>         DCC -->|Usa dados| FC4
>     end
>
>     DC -->|DOREPLIFETIME<br/>Replicação| DCC
>
>     style Editor fill:#e1f5ff
>     style Server fill:#fff4e1
>     style Client fill:#e8f5e9
>     style DA fill:#bbdefb
>     style SC fill:#ffe0b2
>     style DC fill:#ffe0b2
>     style DCC fill:#c8e6c9
>     style FC1 fill:#c8e6c9
>     style FC2 fill:#c8e6c9
>     style FC3 fill:#c8e6c9
>     style FC4 fill:#c8e6c9
>     style Modules fill:#f3e5f5
>     style H fill:#e1bee7
>     style V fill:#e1bee7
>     style U fill:#e1bee7
>     style CreateSheet fill:#fff9c4
>     style Core fill:#fff59d
>     style RBM fill:#fff59d
>     style PBM fill:#fff59d
> ```
>
> **Fluxo de Dados:**
>
> 1. **Editor:** Data Asset é configurado → Handlers processam → Validators validam → Motores calculam → Updaters atualizam
> 2. **Servidor:** CharacterSheetComponent carrega do Data Asset → Aplica regras → CharacterDataComponent armazena dados replicáveis
> 3. **Cliente:** CharacterDataComponent recebe dados replicados → Feature Components usam os dados

</details>

---

**Navegação:** [← Voltar para Arquitetura](index.md) | [→ CreateSheet](createsheet.md)

**Última atualização:** 2024-12-27
