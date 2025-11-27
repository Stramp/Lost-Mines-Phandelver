# Arquitetura do Projeto - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo Executivo</b></summary>

> Este documento fornece uma **visão resumida** da arquitetura do projeto. Para documentação completa e detalhada, veja **[docs/technical/architecture.md](docs/technical/architecture.md)**.
>
> **Princípios Fundamentais:**
>
> - ✅ **Data-Driven:** Todas as regras vêm de Data Tables/Assets
> - ✅ **Modularidade:** Código organizado por responsabilidade única
> - ✅ **Editor-Friendly:** Configuração completa no editor
> - ✅ **Multiplayer-Ready:** Preparado para replicação desde o início
> - ✅ **Clean Code:** Seguindo princípios de código limpo e design patterns

</details>

---

## 🏗️ Arquitetura em 4 Camadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Visão Geral das Camadas</b></summary>

> **Camada 1: Data Assets (Editor/Configuração)**
> - Armazena configuração estática
> - Exemplo: `UCharacterSheetDataAsset`
>
> **Camada 2: Bridge Components (Aplicação de Regras)**
> - Ponte entre Data Asset e Runtime Component
> - Exemplo: `UCharacterSheetComponent`
>
> **Camada 3: Runtime Data Components (Dados Replicáveis)**
> - Armazena dados do personagem em runtime
> - Exemplo: `UCharacterDataComponent`
>
> **Camada 4: Feature Components (Lógica Específica)**
> - Gerencia features específicas de classes
> - Exemplos: `USpellcastingComponent`, `USecondWindComponent`
>
> **📖 Para diagramas e detalhes completos, veja [docs/technical/architecture.md](docs/technical/architecture.md#arquitetura-em-camadas)**

</details>

---

## ⚙️ Arquitetura CreateSheet/

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Motores Desacoplados</b></summary>

> Sistema modular com motores desacoplados para cálculo de ability scores:
>
> - **`FCharacterSheetCore`** - Orquestrador genérico
> - **`FRaceBonusMotor`** - Bônus raciais
> - **`FPointBuyMotor`** - Point Buy
> - **`FMulticlassMotor`** - Multiclassing
> - **`FChoiceMotor`** - Escolhas de classe (planejado)
>
> **📖 Para detalhes completos, veja [docs/technical/architecture.md](docs/technical/architecture.md#arquitetura-createsheet)**

</details>

---

## 🔮 Preparação para GAS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Visão Geral</b></summary>

> O projeto está preparado para migração futura para GAS (Gameplay Ability System), incorporando os melhores padrões:
>
> - Localização do ASC (PlayerState para Player, Character para AI)
> - AttributeSet em C++ com Meta-Atributos
> - UI Reativa (Event-Driven)
> - Gerenciamento de Habilidades (Handles)
> - Data Assets concedendo habilidades
> - Replication Modes (Mixed/Minimal)
>
> **📖 Para documentação completa de GAS, veja [docs/technical/architecture.md](docs/technical/architecture.md#preparação-para-gas-gameplay-ability-system)**

</details>

---

## 📚 Documentação Completa

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links para Documentação Detalhada</b></summary>

> - **[Arquitetura Técnica Completa](docs/technical/architecture.md)** - Documentação completa da arquitetura
> - **[API Reference](docs/technical/api.md)** - Referência completa da API
> - **[Guias Práticos](docs/technical/guides/)** - Guias passo a passo
> - **[GDD](docs/design/gdd.md)** - Game Design Document
> - **[Adaptação D&D 5e + GAS](docs/design/gas-dnd-adaptation.md)** - Como adaptar D&D 5e para Unreal Engine 5 com GAS
> - **[Regras D&D 5e](docs/design/dnd-rules/)** - Regras implementadas
> - **[Índice de Documentação](docs/index.md)** - Organização completa da documentação

</details>

---

## 🧪 Testes Automatizados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Status dos Testes</b></summary>

> **Total:** 138 testes automatizados implementados e funcionando
>
> **Cobertura:**
>
> - ✅ **CalculationHelpers** - 28 testes
>   - `CalculateAbilityModifier()` - 8 testes
>   - `CalculateProficiencyBonus()` - 9 testes
>   - Outros cálculos - 11 testes
>
> - ✅ **ValidationHelpers** - 35 testes
>   - `ValidateAbilityScoreRange()` - 6 testes
>   - `ValidatePointBuy()` - 6 testes
>   - `ValidatePointBuyAllocation()` - 3 testes
>   - Outras validações - 20 testes
>
> - ✅ **CharacterSheetHelpers** - 36 testes
>   - `MeetsFeatPrerequisites()` - 6 testes
>   - `ValidateAbilityScorePrerequisite()` - 4 testes
>   - Outros helpers - 26 testes
>
> - ✅ **DataTableHelpers** - 13 testes (melhorados)
>   - `FindFeatRow()` - 5 testes com supressão de logs
>   - Outras funções de busca - 8 testes
>
> - ✅ **FormattingHelpers** - 10 testes (novo)
>   - `FormatRaceDisplay()` - 4 testes
>   - `FormatProficienciesList()` - 3 testes
>   - `FormatAbilityScores()` - 3 testes
>
> - ✅ **ChoiceHelpers** - 7 testes (novo)
>   - `ParseOptionsString()` - 4 testes
>   - `FormatOptionsString()` - 3 testes
>
> - ✅ **FeatDataTable** - 6 testes
>   - `GetPrerequisites()` - 6 testes
>
> - ✅ **ComponentHelpers** - 3 testes
>   - `FindCharacterDataComponent()` - 3 testes
>
> **Melhorias Aplicadas:**
>
> - ✅ Supressão de warnings esperados (`FScopedLogCategorySuppression`)
> - ✅ Mensagens descritivas em português
> - ✅ Logs informativos com `AddInfo()` para melhor UX
> - ✅ Cobertura completa de casos críticos
>
> **📖 Para documentação completa de testes, veja [docs/technical/guides/testing.md](docs/technical/guides/testing.md)**

</details>

---

## ✅ Checklist de Arquitetura

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Antes de Criar Novo Código</b></summary>

> Antes de criar novo código, verifique:
>
> - [ ] É Data-Driven? (usa Data Tables/Assets?)
> - [ ] É Modular? (responsabilidade única?)
> - [ ] Funciona no Editor? (pode configurar sem rodar?)
> - [ ] É Multiplayer-Ready? (replicação correta?)
> - [ ] Separação de Responsabilidades? (camada correta?)
> - [ ] Tem testes? (funções helper críticas devem ter testes)
>
> **📖 Para checklist completo e regras de implementação, veja [docs/technical/architecture.md](docs/technical/architecture.md#regras-de-implementação)**

</details>

---

**📖 Para documentação completa e detalhada, veja [docs/technical/architecture.md](docs/technical/architecture.md)**
