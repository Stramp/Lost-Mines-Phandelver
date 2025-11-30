# Componentes - API Reference

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v2.0 | 2024-12-27 | Refatoração: api.md dividido em subpastas por componente |
| v1.0 | 2024-12-27 | Versão inicial |

---

Referência completa da API das classes principais do sistema de fichas de personagem D&D 5e.

## 📋 Componentes Principais

### 1. CharacterDataComponent

**Camada:** 3 - Runtime Data Components

**Responsabilidade:** Armazenar dados replicáveis do personagem em runtime.

**Documentação:** [CharacterDataComponent](./character-data-component/index.md)

---

### 2. CharacterSheetComponent

**Camada:** 2 - Bridge Components

**Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.

**Documentação:** [CharacterSheetComponent](./character-sheet-component/index.md)

---

### 3. CharacterSheetDataAsset

**Camada:** 1 - Data Assets

**Responsabilidade:** Armazenar configuração estática editável no editor.

**Documentação:** [CharacterSheetDataAsset](./character-sheet-data-asset/index.md)

---

### 4. Estruturas Relacionadas

Structs auxiliares usadas no sistema de fichas:

- **FFeatDataRow** - Dados de feats D&D 5e (6 testes)
- **FProficiencyDataRow** - Dados de proficiências D&D 5e (4 testes)
- **FAbilityScoreEntry** - Entrada de ability score com base/racial/final

**Documentação:** [Estruturas Relacionadas](./estruturas-relacionadas/index.md)

---

### 5. UI Components

Componentes de interface de usuário:

- **UInventoryWidget** - Widget de inventário
- **UHUDWidget** - HUD principal
- **UMainMenuWidget** - Menu principal

**Documentação:** [UI Components](./ui/index.md)

---

## ⚙️ Motores de Criação

Sistema modular com motores desacoplados para cálculo de ability scores finais.

**Documentação:** [Motores de Criação](../../motores/index.md)

- **FCharacterSheetCore** - Orquestrador genérico
- **FRaceBonusMotor** - Aplicar bônus raciais
- **FPointBuyMotor** - Aplicar Point Buy
- **FMulticlassMotor** - Regras de multiclassing

---

## 🛠️ Helpers e Utilitários

Funções helper organizadas em namespaces em `Utils/`:

**Documentação:** [Helpers](../../helpers/index.md)

- **ComponentHelpers** - 3 testes
- **ValidationHelpers** - 35 testes
- **CalculationHelpers** - 28 testes
- **DataTableHelpers** - 13 testes
- **FormattingHelpers** - 10 testes
- **ChoiceHelpers** - 7 testes
- **CharacterSheetHelpers** - 36 testes
- **CharacterSheetDataAssetHelpers** - 18 testes
- **ProficiencyHelpers** - 12 testes

---

## 📝 Sistema de Logging

**FLoggingSystem** - Sistema centralizado de logging com suporte a popups no editor e throttle.

**Documentação:** [Sistema de Logging](../../helpers/logging-system/index.md)

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação do Projeto</b></summary>

> - **[README Principal](../../../README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](../../../ARCHITECTURE.md)** - Resumo da arquitetura
> - **[CHANGELOG.md](../../../CHANGELOG.md)** - Histórico de mudanças
> - **[Índice de Documentação](../../index.md)** - Organização completa
> - **[Índice da API](../index.md)** - Organização da API

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Documentação de Design (GDD)</b></summary>

> **Regras de Gameplay:**
>
> - [Sistemas de Personagem (GDD)](../../../01%20-%20GDD/02-mecanicas/sistemas-personagem.md) - Regras D&D 5e de criação de personagem
> - [Sistema de Combate (GDD)](../../../01%20-%20GDD/02-mecanicas/sistema-combate.md) - Regras de combate D&D 5e
> - [Mecânicas (GDD)](../../../01%20-%20GDD/02-mecanicas/index.md) - Visão geral das mecânicas

</details>

---

## 🔄 Integração com Refatorações

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Benefícios das Refatorações</b></summary>

> Todas as funções helper foram extraídas de código acoplado seguindo princípios de Clean Code:
>
> **Antes:** Validações e cálculos acoplados a `CharacterSheetDataAsset`
>
> **Depois:** Funções puras em namespaces reutilizáveis em `Utils/`
>
> **Benefícios:**
> - ✅ Reutilizáveis em widgets, combat components e outras mecânicas
> - ✅ Testáveis isoladamente
> - ✅ Funções < 50 linhas (Clean Code)
> - ✅ Sem dependência de estado interno
> - ✅ Preparadas para uso em runtime e editor

</details>
