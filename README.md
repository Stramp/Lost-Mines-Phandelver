# MyProject2 - Sistema de Fichas de Personagem D&D 5e

Projeto Unreal Engine 5.7 para implementação de um sistema completo de fichas de personagem baseado em D&D 5e, seguindo princípios de Clean Code, Design Patterns e arquitetura preparada para multiplayer.

## 📋 Índice

- [Visão Geral](#visão-geral)
- [Requisitos](#requisitos)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Começar](#como-começar)
- [Arquitetura](#arquitetura)
- [Princípios de Design](#princípios-de-design)
- [Documentação](#documentação)
- [Desenvolvimento](#desenvolvimento)

## 🎯 Visão Geral

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Sobre o Projeto</b></summary>

> Este projeto implementa um sistema de fichas de personagem para D&D 5e no Unreal Engine, com foco em:
>
> - ✅ **Data-Driven**: Todas as regras vêm de Data Tables/Assets
> - ✅ **Modularidade**: Código organizado por responsabilidade única
> - ✅ **Multiplayer-Ready**: Preparado para replicação desde o início
> - ✅ **Editor-Friendly**: Configuração completa no editor
> - ✅ **Clean Code**: Seguindo princípios de código limpo e design patterns

</details>

## 🔧 Requisitos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Ferramentas e Dependências</b></summary>

> Requisitos para desenvolvimento:
>
> - **Unreal Engine**: 5.7
> - **Plataforma**: Windows (Win64)
> - **IDE**: Cursor/VS Code (recomendado) ou Visual Studio
> - **Compilador**: Visual Studio 2022 com componentes C++
> - **LLVM**: Para clangd (opcional, mas recomendado)

</details>

## 📁 Estrutura do Projeto

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📂 Organização de Diretórios</b></summary>

> Estrutura de diretórios do projeto:
>
> ```
> MyProject2/
> ├── Source/MyProject2/          # Código C++ principal
> │   ├── Characters/             # Personagens e raças
> │   │   ├── Data/              # Data Assets de personagens
> │   │   └── Components/        # Componentes de personagem
> │   ├── CreateSheet/            # Motores de criação de personagem
> │   │   ├── Core/              # Core genérico e CharacterSheetData
> │   │   ├── RaceBonus/         # Motor de bônus raciais
> │   │   ├── PointBuy/          # Motor de Point Buy
> │   │   ├── Multiclass/         # Motor de multiclassing
> │   │   └── (Choices/ - 🔮 Planejado)
> │   ├── Components/            # Componentes reutilizáveis
> │   ├── Data/                  # Data Assets e Data Tables
> │   │   └── Tables/            # Data Tables (Race, Class, Background, Feat)
> │   ├── Gameplay/              # Mecânicas de jogo
> │   └── Utils/                 # Utilitários e helpers
> │       ├── CalculationHelpers # Cálculos puros
> │       ├── CharacterSheetHelpers # Helpers específicos de fichas
> │       ├── DataTableHelpers   # Busca centralizada em Data Tables
> │       ├── ValidationHelpers  # Validações reutilizáveis
> │       ├── FormattingHelpers  # Formatação de dados
> │       ├── ComponentHelpers   # Helpers de componentes
> │       └── Tests/             # Testes automatizados
> │           ├── Unit/          # Testes unitários (próximos ao código)
> │           │   ├── CalculationHelpersTests.cpp (28 testes)
> │           │   ├── ValidationHelpersTests.cpp (35 testes)
> │           │   ├── CharacterSheetHelpersTests.cpp (36 testes)
> │           │   ├── DataTableHelpersTests.cpp (13 testes)
> │           │   ├── FormattingHelpersTests.cpp (10 testes)
> │           │   ├── ChoiceHelpersTests.cpp (7 testes)
> │           │   └── ComponentHelpersTests.cpp (3 testes)
> │           └── Integration/  # Testes end-to-end (fluxos completos)
> │               └── CharacterCreationE2ETests.cpp (4 testes)
> ├── Content/                    # Assets (Blueprints, Texturas, Modelos)
> ├── Config/                     # Configurações (.ini)
> ├── .cursor/                    # Regras e configurações do Cursor
> │   └── rules/                 # Regras de código e arquitetura
> ├── docs/                      # Documentação completa organizada
│   ├── design/               # Design (GDD, regras D&D 5e)
│   └── technical/            # Técnico (arquitetura, API, guias)
├── ARCHITECTURE.md            # Resumo da arquitetura (linka para docs/)
> └── README.md                  # Este arquivo
> ```

</details>

## 🚀 Como Começar

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Guia Passo a Passo</b></summary>

> ### 1. Clonar e Abrir o Projeto
>
> ```bash
> # Clonar o repositório
> git clone <repository-url>
> cd MyProject2
>
> # Abrir no Cursor/VS Code
> # File → Open Workspace from File → MyProject2.code-workspace
> ```
>
> **📖 Para instruções completas de setup, veja [docs/technical/guides/setup.md](docs/technical/guides/setup.md)**
>
> ### 2. Gerar Arquivos do Projeto
>
> Se for usar Visual Studio ou gerar arquivos do projeto:
>
> ```bash
> # No Unreal Editor:
> # Tools → Refresh Visual Studio Project
>
> # Ou via linha de comando (substitua os caminhos pelos seus):
> # Descubra o caminho do Unreal Engine (geralmente em C:\Program Files\Epic Games\UE_5.7)
> # Substitua "SEU_CAMINHO_UE" pelo caminho real do Unreal Engine 5.7
> # Substitua "SEU_CAMINHO_PROJETO" pelo caminho real do projeto
>
> "SEU_CAMINHO_UE\Engine\Build\BatchFiles\RunUBT.bat" -projectfiles -project="SEU_CAMINHO_PROJETO\MyProject2.uproject" -game -engine
> ```
>
> **📖 Para instruções completas de setup, veja [docs/technical/guides/setup.md](docs/technical/guides/setup.md)**
>
> ### 3. Compilar o Projeto
>
> **No Cursor/VS Code:**
>
> - `Ctrl+Shift+P` → "Tasks: Run Task"
> - Selecione "MyProject2Editor Win64 Development Build"
>
> **No Unreal Editor:**
>
> - Abra o projeto, o editor compilará automaticamente
>
> ### 4. Configurar Data Tables
>
> **📖 Para instruções completas, veja [docs/technical/guides/data-tables-setup.md](docs/technical/guides/data-tables-setup.md)**
>
> Resumo rápido:
>
> 1. Crie os 4 Data Tables necessários (Race, Class, Background, Feat)
> 2. Configure a estrutura de cada um
> 3. Preencha com dados válidos
>
> ### 5. Configurar um Personagem
>
> **📖 Para guia completo, veja [docs/technical/guides/getting-started.md](docs/technical/guides/getting-started.md)**
>
> Resumo rápido:
>
> 1. Crie um `CharacterSheetDataAsset`
> 2. Atribua os Data Tables
> 3. Preencha a ficha do personagem
> 4. Crie um Actor no editor
> 5. Adicione os componentes (`CharacterDataComponent`, `CharacterSheetComponent`)
> 6. Atribua o Data Asset ao `CharacterSheetComponent`
> 7. O sistema inicializará automaticamente no `BeginPlay`

</details>

## 🏗️ Arquitetura

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Arquitetura em 4 Camadas</b></summary>

> > **💡 Dica:** Veja o diagrama visual abaixo para entender melhor a arquitetura em camadas.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📝 Camada 1: Data Assets (Editor/Configuração)</summary>
>
> > **Responsabilidade:** Armazenar configuração estática, não contém lógica.
> >
> > **Características:**
> >
> > - Herda de `UDataAsset`
> > - `UPROPERTY(EditDefaultsOnly)` - editável apenas em defaults
> > - Não é replicável (não precisa em runtime)
> > - Funciona apenas no editor para designers
> > - Exemplo: `UCharacterSheetDataAsset`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌉 Camada 2: Bridge Components (Aplicação de Regras)</summary>
>
> > **Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.
> >
> > **Características:**
> >
> > - Herda de `UActorComponent`
> > - Executa apenas no servidor/local (não replicável)
> > - Aplica regras de raça e classe (`ApplyRaceBonuses()`, `ApplyClassFeatures()`)
> > - Carrega dados do Data Asset para Runtime Component
> > - Exemplo: `UCharacterSheetComponent`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💾 Camada 3: Runtime Data Components (Dados Replicáveis)</summary>
>
> > **Responsabilidade:** Armazenar dados do personagem em runtime, todas as propriedades replicáveis.
> >
> > **Características:**
> >
> > - Herda de `UActorComponent`
> > - Todas as propriedades são replicáveis (`DOREPLIFETIME`)
> > - Calcula atributos finais, HP, proficiência
> > - Preparado para migração futura para GAS Attributes
> > - Exemplo: `UCharacterDataComponent`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚡ Camada 4: Feature Components (Lógica Específica)</summary>
>
> > **Responsabilidade:** Gerenciar features específicas de classes (spells, abilities, etc.).
> >
> > **Características:**
> >
> > - Herda de `UActorComponent`
> > - Cada um gerencia uma feature específica
> > - Podem ser migrados para GAS Abilities no futuro
> > - Exemplos planejados (Fase 5): `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`
>
> </details>
>
> <details>
> <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Diagrama Visual das Camadas</b></summary>
>
> >
>
> ```mermaid
> graph LR
>     subgraph Layer1["Camada 1: Data Assets"]
>         DA1[UCharacterSheetDataAsset<br/>📝 Editor Only<br/>⚙️ Configuração Estática]
>     end
>
>     subgraph Layer2["Camada 2: Bridge Components"]
>         BC1[UCharacterSheetComponent<br/>🔗 Ponte Data → Runtime<br/>📋 Aplica Regras]
>     end
>
>     subgraph Layer3["Camada 3: Runtime Data"]
>         RD1[UCharacterDataComponent<br/>💾 Dados Replicáveis<br/>📊 Atributos Finais]
>     end
>
>     subgraph Layer4["Camada 4: Features (Planejado)"]
>         F1[USpellcastingComponent<br/>🔮 Planejado]
>         F2[USecondWindComponent<br/>🔮 Planejado]
>         F3[UActionSurgeComponent<br/>🔮 Planejado]
>     end
>
>     DA1 -->|InitializeFromDataAsset| BC1
>     BC1 -->|SetData| RD1
>     RD1 -->|Usa dados| F1
>     RD1 -->|Usa dados| F2
>     RD1 -->|Usa dados| F3
>
>     style Layer1 fill:#e3f2fd
>     style Layer2 fill:#fff3e0
>     style Layer3 fill:#f3e5f5
>     style Layer4 fill:#e8f5e9
> ```
>
> </details>
>
> **📖 Para mais detalhes, veja [ARCHITECTURE.md](ARCHITECTURE.md)**

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Arquitetura CreateSheet/ - Motores Desacoplados</b></summary>

> O sistema utiliza uma arquitetura modular com motores desacoplados para cálculo de ability scores finais.
>
> **Componentes Principais:**
>
> - **`FCharacterSheetCore`** - Orquestrador genérico que coordena todos os motores
> - **`FCharacterSheetData`** - Estrutura genérica de dados (funciona em Data Asset e Widget)
> - **`FRaceBonusMotor`** - Motor independente para bônus raciais ✅ Implementado
> - **`FPointBuyMotor`** - Motor independente para alocação de Point Buy ✅ Implementado
> - **`FMulticlassMotor`** - Motor independente para cálculo de multiclassing ✅ Implementado
>
> **Fórmula de Cálculo:**
>
> ```
> FinalScore = 8 (base) + RacialBonus + PointBuyAllocation
> ```
>
> **Características:**
>
> - ✅ **Genérico:** Funciona tanto no Data Asset quanto em Widgets
> - ✅ **Desacoplado:** Motores não conhecem uns aos outros
> - ✅ **Independente:** Cada motor pode ser testado isoladamente
> - ✅ **Reutilizável:** Core pode ser usado em diferentes contextos
>
> **📖 Para mais detalhes, veja [ARCHITECTURE.md](ARCHITECTURE.md)**

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Fluxo de Dados</b></summary>

> Diagrama completo do fluxo de dados do sistema:
>
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
>             MCM[MulticlassMotor<br/>Multiclass]
>             CM[ChoiceMotor<br/>Escolhas]
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
>     style MCM fill:#fff59d
>     style CM fill:#fff59d
> ```
>
> **📖 Para mais detalhes sobre o fluxo de dados, veja [ARCHITECTURE.md](ARCHITECTURE.md) ou [documentação completa](docs/technical/architecture.md)**

</details>

## 🎨 Princípios de Design

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 5 Princípios Fundamentais</b></summary>

> ### 1. Data-Driven
>
> Todas as regras vêm de Data Tables ou Data Assets, nunca hardcoded.
>
> ### 2. Modularidade
>
> Código organizado por domínio, cada parte com responsabilidade única.
>
> ### 3. Editor-Friendly
>
> Sistema funciona perfeitamente no editor, permitindo configuração sem rodar o jogo.
>
> ### 4. Multiplayer-Ready
>
> Preparado para multiplayer desde o início, não precisa refatorar depois.
>
> ### 5. Clean Code
>
> Seguindo princípios de código limpo e design patterns em **TODAS** as situações.
>
> **⚠️ IMPORTANTE:** Ver regra crítica em [`.cursor/rules/clean-code-mandatory.mdc`](.cursor/rules/clean-code-mandatory.mdc)

</details>

## 📚 Documentação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Documentação Completa</b></summary>

> ### Documentação Principal
>
> **📖 Para documentação completa e organizada, veja [docs/index.md](docs/index.md)**
>
> ### Documentação Principal
>
> - **[ARCHITECTURE.md](ARCHITECTURE.md)** - Resumo da arquitetura (veja [completo](docs/technical/architecture.md))
> - **[GDD](docs/design/gdd.md)** - Game Design Document (visão do jogo final)
> - **[API Reference](docs/technical/api.md)** - Referência completa da API (inclui sistema de logging)
> - **[CHANGELOG.md](CHANGELOG.md)** - Histórico de mudanças
> - **[CONTRIBUTING.md](CONTRIBUTING.md)** - Guia para contribuidores
> - **[.cursor/rules/](.cursor/rules/)** - Regras de código e padrões
>
> ### Documentação Organizada
>
> - **[Design](docs/design/)** - GDD e regras D&D 5e
> - **[Técnico](docs/technical/)** - Arquitetura, API e guias
> - **[Índice Completo](docs/index.md)** - Organização da documentação
>
> ### Regras Críticas
>
> - **Clean Code Obrigatório**: `.cursor/rules/clean-code-mandatory.mdc`
> - **Padrões Unreal Engine**: `.cursor/rules/unreal-engine-cpp.mdc`
> - **Arquitetura**: `.cursor/rules/project-architecture.mdc`

</details>

## 💻 Desenvolvimento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛠️ Convenções e Padrões</b></summary>

> ### Convenções de Código
>
> - **Classes**: Prefixos Unreal (`A` para Actors, `U` para UObjects, `F` para Structs)
> - **Variáveis**: PascalCase (booleanos com `b` prefix)
> - **Funções**: PascalCase
> - **Constantes**: `const` + PascalCase
>
> ### Helpers e Utilitários
>
> **REGRA CRÍTICA:** Funções helper reutilizáveis DEVEM estar em `Utils/`:
>
> ```cpp
> // ✅ CORRETO
> #include "../../Utils/ComponentHelpers.h"
> UCharacterDataComponent* Component = ComponentHelpers::FindCharacterDataComponent(Owner);
>
> // ❌ ERRADO - função privada acoplada
> private:
>     UCharacterDataComponent* FindOrGetCharacterDataComponent();
> ```
>
> ### Build e Compilação
>
> - Use as tasks do workspace (Ctrl+Shift+P → Tasks: Run Task)
> - Configurações disponíveis: Debug, DebugGame, Development, Test, Shipping
> - **SEMPRE** verifique se compila antes de commitar
>
> ### Testes Automatizados
>
> **Status:** ✅ 275+ testes implementados e funcionando
>
> O projeto utiliza o **Automation Test Framework** do Unreal Engine 5.7 para testes automatizados:
>
> **Testes Unitários** (próximos ao código testado):
>
> - ✅ **CalculationHelpers** - 28 testes (modificadores, proficiência, cálculos)
> - ✅ **ValidationHelpers** - 35 testes (validações de ability scores, point buy, escolhas)
> - ✅ **CharacterSheetHelpers** - 36 testes (feats, pré-requisitos, helpers de fichas)
> - ✅ **DataTableHelpers** - 13 testes (busca em Data Tables)
> - ✅ **FormattingHelpers** - 10 testes (formatação de dados)
> - ✅ **ChoiceHelpers** - 7 testes (parsing e formatação de escolhas)
> - ✅ **FeatDataTable** - 6 testes (pré-requisitos de feats)
> - ✅ **ComponentHelpers** - 3 testes (busca de componentes)
> - ✅ **MulticlassHelpers** - Testes de conversão de features e flags
> - ✅ **MulticlassMotor** - Testes de carregamento de progressão multiclass
> - ✅ **CharacterSheetDataAssetLoaders** - Testes de loaders de dados
> - ✅ **CharacterSheetDataAssetValidators** - Testes de validadores (Variant Human)
> - ✅ **ProficiencyHelpers** - Testes de helpers de proficiência
> - ✅ **ProficiencyDataTable** - Testes de Data Table de proficiências
> - ✅ **CharacterCreation Steps** - Testes por etapa de criação (Step 1-5)
>
> **Testes de Integração End-to-End** (fluxos completos):
>
> - ✅ **CharacterCreationE2E** - 4 testes (criação completa de personagem)
> - ✅ **CompleteCharacterCreationE2E** - Testes completos de criação
>
> **Executar Testes:**
>
> - **No Editor:** Window → Developer Tools → Automation Tool
> - **Linha de Comando:** `run_tests.bat` ou `run_tests_quick.bat`
> - **Testes de Integração:** `run_tests.bat MyProject2.Integration`
>
> **📖 Documentação:**
- **[Guia de Testes](docs/technical/guides/testing.md)** - Implementação e execução de testes
- **[TDD Complete Guide](docs/technical/guides/tdd-complete-guide.md)** - Guia completo de Test-Driven Development
>
> ### Checklist Antes de Commitar
>
> - [ ] Código segue Clean Code e Design Patterns?
> - [ ] Funções helper estão em `Utils/`?
> - [ ] Compila sem erros ou warnings?
> - [ ] Segue padrões de nomenclatura?
> - [ ] Está documentado?
> - [ ] Testado no editor?
> - [ ] Testes passam? (se adicionou/modificou helpers críticos)

</details>

## 🔗 Links Úteis

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação e Recursos</b></summary>

> Links úteis para desenvolvimento:
>
> - [Unreal Engine 5.7 Documentation](https://docs.unrealengine.com/5.7/)
> - [Unreal Engine API Reference](https://docs.unrealengine.com/5.7/en-US/API/)
> - [C++ Programming Guide](https://docs.unrealengine.com/5.7/en-US/cpp-programming-in-unreal-engine/)

</details>

## 🗺️ Roadmap

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Resumo do Roadmap</b></summary>

> **Roadmap resumido** - Para versão completa e detalhada, veja [docs/planning/roadmap.md](docs/planning/roadmap.md)
>
> **Status Atual:**
>
> - ✅ **Fase 1:** Sistema de Fichas (Core Completo - 80%)
>   - ✅ Motores básicos (RaceBonus, PointBuy, Multiclass)
>   - ✅ Sistema de validação completo
>   - ✅ Variant Human completo
>   - ⚠️ Itens iniciais e inventário (planejado)
> - 📋 **Fase 2:** Combate Básico com GAS (Próxima - 2-3 semanas)
> - 📋 **Fases 3-10:** Planejadas
>
> **Próximas Fases:**
>
> - 📋 **Fase 2:** Combate Básico com GAS (AttributeSet, ASC, Gameplay Effects)
> - 📋 **Fase 3:** NPCs e Monsters
> - 📋 **Fase 4:** Equipamentos e Recursos
> - 📋 **Fase 5:** Features e Habilidades (via GAS)
> - 📋 **Fase 6:** Skills e Saving Throws
> - 🔮 **Fases 7-10:** Sistemas Avançados
>
> **📖 Para roadmap completo com prazos, dependências e status detalhado, veja [docs/planning/roadmap.md](docs/planning/roadmap.md)**

</details>

## 📝 Licença

Copyright Epic Games, Inc. All Rights Reserved.

## 🤝 Contribuindo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Diretrizes para Contribuidores</b></summary>

> Ao contribuir, certifique-se de:
>
> 1. Seguir todas as regras em `.cursor/rules/`
> 2. Manter código limpo e documentado
> 3. Testar no editor antes de commitar
> 4. Atualizar documentação quando necessário
>
> **📖 Para mais detalhes, veja [CONTRIBUTING.md](CONTRIBUTING.md)**

</details>

---

**Desenvolvido com ❤️ seguindo princípios de Clean Code e Design Patterns**
