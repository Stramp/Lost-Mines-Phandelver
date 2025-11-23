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

Este projeto implementa um sistema de fichas de personagem para D&D 5e no Unreal Engine, com foco em:

- ✅ **Data-Driven**: Todas as regras vêm de Data Tables/Assets
- ✅ **Modularidade**: Código organizado por responsabilidade única
- ✅ **Multiplayer-Ready**: Preparado para replicação desde o início
- ✅ **Editor-Friendly**: Configuração completa no editor
- ✅ **Clean Code**: Seguindo princípios de código limpo e design patterns

## 🔧 Requisitos

- **Unreal Engine**: 5.7
- **Plataforma**: Windows (Win64)
- **IDE**: Cursor/VS Code (recomendado) ou Visual Studio
- **Compilador**: Visual Studio 2022 com componentes C++
- **LLVM**: Para clangd (opcional, mas recomendado)

## 📁 Estrutura do Projeto

```
MyProject2/
├── Source/MyProject2/          # Código C++ principal
│   ├── Characters/             # Personagens e raças
│   │   ├── Data/              # Data Assets de personagens
│   │   └── Components/        # Componentes de personagem
│   ├── Components/            # Componentes reutilizáveis
│   ├── Data/                  # Data Assets e Data Tables
│   ├── Gameplay/              # Mecânicas de jogo
│   └── Utils/                 # Utilitários e helpers
├── Content/                    # Assets (Blueprints, Texturas, Modelos)
├── Config/                     # Configurações (.ini)
├── .cursor/                    # Regras e configurações do Cursor
│   └── rules/                 # Regras de código e arquitetura
├── ARCHITECTURE.md            # Documentação de arquitetura completa
└── README.md                  # Este arquivo
```

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

> O projeto segue uma arquitetura em 4 camadas:
>
> ### Camada 1: Data Assets (Editor)
>
> - Configuração estática editável no editor
> - Exemplo: `UCharacterSheetDataAsset`
>
> ### Camada 2: Bridge Components
>
> - Faz ponte entre Data Asset e Runtime Component
> - Aplica regras de raça e classe
> - Exemplo: `UCharacterSheetComponent`
>
> ### Camada 3: Runtime Data Components
>
> - Armazena dados replicáveis do personagem
> - Calcula atributos finais, HP, proficiência
> - Exemplo: `UCharacterDataComponent`
>
> ### Camada 4: Feature Components
>
> - Gerencia features específicas (spells, abilities)
> - Preparado para migração futura para GAS
> - Exemplos: `USpellcastingComponent`, `USecondWindComponent`
>
> **📖 Para mais detalhes, veja [ARCHITECTURE.md](ARCHITECTURE.md)**

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

- [Unreal Engine 5.7 Documentation](https://docs.unrealengine.com/5.7/)
- [Unreal Engine API Reference](https://docs.unrealengine.com/5.7/en-US/API/)
- [C++ Programming Guide](https://docs.unrealengine.com/5.7/en-US/cpp-programming-in-unreal-engine/)

## 🗺️ Roadmap

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🚀 Próximas Features Planejadas</b></summary>

> Próximas features planejadas para o sistema de fichas:
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⏱️ Curto Prazo</summary>
>
> > - 🔄 **Sistema básico de fichas** - Em desenvolvimento
> >   - ⚠️ Validação do sistema de Point Buy (pendente)
> >   - ⚠️ Validação do sistema de Multiclasse (pendente)
> >   - ⚠️ Conferir criação de feat no editor no config do Data Asset (pendente)
> > - ⚠️ **Validação de integridade de dados** - Pendente de validação (standby)
> > - ⚠️ **Suporte para Variant Human** - Pendente de validação (standby)
> > - 📋 **Combat Components** - Integração de ability scores e modifiers em sistema de combate
> > - 📋 **HP/MaxHP Calculation** - Cálculo automático de HP baseado em Constitution e Hit Die
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📅 Médio Prazo</summary>
>
> > - 📋 **OnRep Callbacks** - Callbacks de replicação para atualizar UI automaticamente
> > - 📋 **Skill System** - Sistema completo de skills com modifiers
> > - 📋 **Saving Throws** - Cálculo automático de saving throws
> > - 📋 **Feature Components** - Implementação de features de classes (Second Wind, Action Surge, etc.)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 Longo Prazo</summary>
>
> > - 🔮 **GAS Migration** - Migração para Gameplay Ability System
> >   - Dados → GAS Attributes
> >   - Features → GAS Abilities
> >   - Effects → GAS Gameplay Effects
> > - 🔮 **Spellcasting System** - Sistema completo de magia
> > - 🔮 **Equipment System** - Sistema de equipamentos e itens
> > - 🔮 **Character Progression** - Sistema de progressão e leveling up
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

Ao contribuir, certifique-se de:

1. Seguir todas as regras em `.cursor/rules/`
2. Manter código limpo e documentado
3. Testar no editor antes de commitar
4. Atualizar documentação quando necessário

---

**Desenvolvido com ❤️ seguindo princípios de Clean Code e Design Patterns**
