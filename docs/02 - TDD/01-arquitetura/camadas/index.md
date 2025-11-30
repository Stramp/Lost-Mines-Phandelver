# Arquitetura em Camadas

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Índice criado após divisão de architecture.md |

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Visão Geral</b></summary>

> A arquitetura do projeto é organizada em **4 camadas** distintas, cada uma com responsabilidade única e bem definida:
>
> 1. **Camada 1: Data Assets** (Editor/Configuração) - Armazena configuração estática
> 2. **Camada 2: Bridge Components** (Aplicação de Regras) - Ponte entre Data Asset e Runtime
> 3. **Camada 3: Runtime Data Components** (Dados Replicáveis) - Armazena dados em runtime
> 4. **Camada 4: Feature Components** (Lógica Específica) - Gerencia features específicas

</details>

---

## 📖 Camadas

- **[Camada 1: Data Assets](layer-1-data-assets.md)** - Editor/Configuração
- **[Camada 2: Bridge Components](layer-2-bridge-components.md)** - Aplicação de Regras
- **[Camada 3: Runtime Data Components](layer-3-runtime-data.md)** - Dados Replicáveis
- **[Camada 4: Feature Components](layer-4-feature-components.md)** - Lógica Específica

---

## 📊 Diagrama Visual das Camadas

```mermaid
graph LR
subgraph Layer1["Camada 1: Data Assets"]
DA1[UCharacterSheetDataAsset<br/>📝 Editor Only<br/>⚙️ Configuração Estática]
end

subgraph Layer2["Camada 2: Bridge Components"]
BC1[UCharacterSheetComponent<br/>🔗 Ponte Data → Runtime<br/>📋 Aplica Regras]
end

subgraph Layer3["Camada 3: Runtime Data"]
RD1[UCharacterDataComponent<br/>💾 Dados Replicáveis<br/>📊 Atributos Finais]
end

subgraph Layer4["Camada 4: Features (Planejado)"]
F1[USpellcastingComponent<br/>🔮 Planejado]
F2[USecondWindComponent<br/>🔮 Planejado]
F3[UActionSurgeComponent<br/>🔮 Planejado]
end

DA1 -->|InitializeFromDataAsset| BC1
BC1 -->|SetData| RD1
RD1 -->|Usa dados| F1
RD1 -->|Usa dados| F2
RD1 -->|Usa dados| F3

style Layer1 fill:#e3f2fd
style Layer2 fill:#fff3e0
style Layer3 fill:#f3e5f5
style Layer4 fill:#e8f5e9
```

---

**Navegação:** [← Voltar para Arquitetura](../index.md) | [→ Princípios](../principios/index.md)

**Última atualização:** 2024-12-27
