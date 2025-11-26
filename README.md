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
> │   │   └── Choices/           # Motor de escolhas de classe
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
> │       └── ComponentHelpers   # Helpers de componentes
> ├── Content/                    # Assets (Blueprints, Texturas, Modelos)
> ├── Config/                     # Configurações (.ini)
> ├── .cursor/                    # Regras e configurações do Cursor
> │   └── rules/                 # Regras de código e arquitetura
> ├── ARCHITECTURE.md            # Documentação de arquitetura completa
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
> ### 2. Gerar Arquivos do Projeto
>
> Se for usar Visual Studio ou gerar arquivos do projeto:
>
> ```bash
> # No Unreal Editor:
> # Tools → Refresh Visual Studio Project
>
> # Ou via linha de comando:
> "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\RunUBT.bat" -projectfiles -project="F:\UNREAL GAME\MyProject2\MyProject2.uproject" -game -engine
> ```
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
> ### 4. Configurar um Personagem
>
> 1. Crie um Actor no editor
> 2. Adicione os componentes:
>    - `CharacterDataComponent`
>    - `CharacterSheetComponent`
> 3. No `CharacterSheetComponent`, atribua um `CharacterSheetDataAsset`
> 4. O sistema inicializará automaticamente no `BeginPlay`

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
> > - Exemplos: `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`
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
>     subgraph Layer4["Camada 4: Features"]
>         F1[USpellcastingComponent]
>         F2[USecondWindComponent]
>         F3[UActionSurgeComponent]
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
> - **`FRaceBonusMotor`** - Motor independente para bônus raciais
> - **`FPointBuyMotor`** - Motor independente para alocação de Point Buy
> - **`FMulticlassMotor`** - Motor independente para cálculo de multiclassing
> - **`FChoiceMotor`** - Motor independente para processar escolhas de classe
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
> **📖 Para mais detalhes sobre o fluxo de dados, veja [ARCHITECTURE.md](ARCHITECTURE.md)**

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
> - **[ARCHITECTURE.md](ARCHITECTURE.md)** - Arquitetura completa do projeto
> - **[API.md](docs/API.md)** - Referência completa da API
> - **[CHANGELOG.md](CHANGELOG.md)** - Histórico de mudanças
> - **[CONTRIBUTING.md](CONTRIBUTING.md)** - Guia para contribuidores
> - **[.cursor/rules/](.cursor/rules/)** - Regras de código e padrões
>
> ### Guias Práticos
>
> - **[Getting Started](docs/GUIDES/getting-started.md)** - Guia passo a passo para criar personagens
> - **[Data Tables](docs/GUIDES/data-tables.md)** - Documentação completa dos Data Tables
> - **[Troubleshooting](docs/GUIDES/troubleshooting.md)** - Problemas comuns e soluções
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
> ### Checklist Antes de Commitar
>
> - [ ] Código segue Clean Code e Design Patterns?
> - [ ] Funções helper estão em `Utils/`?
> - [ ] Compila sem erros ou warnings?
> - [ ] Segue padrões de nomenclatura?
> - [ ] Está documentado?
> - [ ] Testado no editor?

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
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Próximas Features Planejadas</b></summary>

> Roadmap detalhado para transformação em Action RPG D&D 5e:
>
> <details open>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⏱️ Curto Prazo (Próximas 4-6 semanas)</summary>
>
> > **Fase 1: Finalizar Sistema de Fichas**
> >
> > - ✅ Sistema de Point Buy completo com validação automática
> > - ✅ Sistema de Multiclasse completo com filtro de classes por requisitos de atributo
> > - ✅ Motor de multiclasse refatorado e desacoplado
> > - ⚠️ Validação do sistema de Multiclasse (em testes)
> > - ⚠️ Conferir criação de feat no editor no config do Data Asset
> > - ⏳ Validar suporte para Variant Human (standby)
> > - ⏳ Validar integridade de dados (standby)
> >
> > **Fase 2: Combate Básico (2-3 semanas)**
> >
> > - 📋 **CombatComponent**
> >   - Calcular AC (10 + Dex Mod + Armor)
> >   - Calcular dano de ataque (weapon dice + ability modifier)
> >   - Aplicar dano
> >   - Sistema de ações básico (Attack, Dodge, Dash)
> > - 📋 **HealthComponent**
> >   - HP/MaxHP (replicável)
> >   - Healing/Damage
> >   - Death system
> > - 📋 **WeaponDataTable**
> >   - Armas D&D 5e
> >   - Propriedades (versatile, finesse, two-handed, etc.)
> > - 📋 **CombatHelpers** (em `Utils/`)
> >   - `CalculateArmorClass()`
> >   - `CalculateAttackRoll()`
> >   - `CalculateDamage()`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📅 Médio Prazo (6-12 semanas)</summary>
>
> > **Fase 3: Sistema de Fichas - NPCs e Monsters (2-3 semanas)**
> >
> > - 📋 **NPCDataAsset**
> >   - Ability Scores fixos (não Point Buy)
> >   - Classe opcional (não obrigatória)
> >   - Stat blocks simplificados
> >   - Validações específicas para NPCs
> > - 📋 **MonsterDataAsset**
> >   - Challenge Rating (CR) ao invés de Level
> >   - Hit Dice variados (d8, d10, d12, d20)
> >   - Armor Class natural
> >   - Traits e Actions customizados
> >   - Resistances/Immunities
> >   - Legendary Actions (monsters especiais)
> > - 📋 **NPCComponent e MonsterComponent**
> >   - Bridge Components para NPCs/Monsters
> >   - Integração com CharacterDataComponent (ou componentes específicos)
> > - 📋 **NPC/Monster Helpers** (em `Utils/`)
> >   - Helpers para cálculos de NPCs/Monsters
> >   - Reutilização de helpers comuns quando aplicável
> >
> > **Fase 4: Equipamentos e Recursos (2 semanas)**
> >
> > - 📋 **EquipmentComponent**
> >   - Equipar/desequipar armas e armaduras
> >   - Bônus de equipamentos (AC, dano, etc.)
> >   - Slots de equipamento (Main Hand, Off Hand, Armor, etc.)
> > - 📋 **InventoryComponent**
> >   - Inventário com peso (Carrying Capacity)
> >   - Gerenciamento de itens
> > - 📋 **ItemDataTable**
> >   - Itens D&D 5e (armas, armaduras, consumíveis)
> > - 📋 **ResourceComponent**
> >   - Spell Slots (por nível)
> >   - Ki Points
> >   - Rage, etc.
> >
> > **Fase 5: Features e Habilidades (2-3 semanas)**
> >
> > - 📋 **AbilityComponent**
> >   - Second Wind (Fighter)
> >   - Action Surge (Fighter)
> >   - Cunning Action (Rogue)
> >   - Outras features de classes
> > - 📋 **SpellcastingComponent**
> >   - Spell slots (por nível)
> >   - Preparar magias
> >   - Casting de magias
> > - 📋 **SpellDataTable**
> >   - Magias D&D 5e
> >   - Componentes, duração, alcance
> >
> > **Fase 6: Sistema de Skills e Saving Throws (1-2 semanas)**
> >
> > - 📋 **Skill System**
> >   - Skills com modifiers
> >   - Expertise (Rogue, Bard)
> >   - Skill checks
> > - 📋 **Saving Throws**
> >   - Cálculo automático de saving throws
> >   - Saving throw checks
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Longo Prazo (12+ semanas)</summary>
>
> > **Fase 7: Movimento e Física (2 semanas)**
> >
> > - 📋 **MovementComponent**
> >   - Velocidade baseada em raça/classe
> >   - Dash, Disengage actions
> > - 📋 **JumpComponent**
> >   - Altura baseada em Strength
> >   - Long jump, high jump
> > - 📋 **InteractionComponent**
> >   - Interação com objetos
> >   - Pick up, drop, use items
> >
> > **Fase 8: UI e Feedback (2-3 semanas)**
> >
> > - 📋 **OnRep Callbacks**
> >   - Callbacks de replicação para atualizar UI automaticamente
> >   - Delegates para eventos (HP changed, Level up, etc.)
> > - 📋 **UI Components**
> >   - Health bar
> >   - Action bar
> >   - Inventory UI
> >   - Character sheet UI
> >
> > **Fase 9: GAS Migration (4-6 semanas)**
> >
> > - 🔮 **Migração para Gameplay Ability System**
> >   - Dados → GAS Attributes
> >   - Features → GAS Abilities
> >   - Effects → GAS Gameplay Effects
> >   - Status Effects → GAS Gameplay Effects
> >
> > **Fase 10: Sistemas Avançados (4-6 semanas)**
> >
> > - 🔮 **Character Progression**
> >   - Level up system
> >   - ASI (Ability Score Improvement)
> >   - Feat selection
> > - 🔮 **Equipment System Avançado**
> >   - Weapon enchantments
> >   - Armor properties
> >   - Item sets
>
> </details>
>
> **Status:**
>
> - ✅ Completo
> - 🔄 Em desenvolvimento
> - ⚠️ Pendente/Validação necessária
> - 📋 Planejado
> - 🔮 Futuro

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
