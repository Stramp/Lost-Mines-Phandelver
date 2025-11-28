---
title: "Glossary"
category: root
tags: [glossary, concepts, definitions, terminology]
last_updated: 2024-12-27
---

**Navegação:** [Home](../README.md) > [Documentação](index.md) > Glossary

# 📚 Glossário de Conceitos - MyProject2

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Sobre este Glossário</b></summary>

> Este glossário define todos os conceitos fundamentais, padrões de design e termos técnicos usados no projeto. Use este documento para entender rapidamente qualquer conceito mencionado na documentação.

</details>

---

## 🎯 Conceitos Fundamentais

### Data-Driven Design

**Definição:** Todas as regras vêm de Data Tables ou Data Assets, nunca hardcoded no código.

**Características:**
- Designers podem modificar regras sem programadores
- Fácil adicionar novo conteúdo
- Suporte a localização
- Validação automática

**Onde encontrar:**
- [Arquitetura Técnica](technical/architecture.md#data-driven)
- [Arquitetura de Dados](technical/data-architecture/database-architecture.md)
- [ARCHITECTURE.md](../ARCHITECTURE.md#princípios-fundamentais)

**Relacionado:**
- Data Tables
- UDataAsset
- Normalização
- FDataTableRowHandle

---

### Component-Based Architecture

**Definição:** Separação de responsabilidades em componentes independentes, baseado em Composição sobre Herança.

**Características:**
- Cada componente tem responsabilidade única
- Componentes são independentes e reutilizáveis
- Comunicação via interfaces
- Preparado para migração para GAS

**Onde encontrar:**
- [ARCHITECTURE.md](../ARCHITECTURE.md#arquitetura-em-4-camadas)
- [Arquitetura Técnica](technical/architecture.md#component-based-architecture)
- [API Reference](technical/api.md)

**Relacionado:**
- UActorComponent
- Separation of Concerns
- Modularity
- GAS (Gameplay Ability System)

---

### Point Buy System

**Definição:** Sistema de alocação de Ability Scores onde o jogador distribui pontos (máximo 27) para aumentar scores base (8) até 15.

**Características:**
- Máximo de 27 pontos para distribuir
- Scores base começam em 8
- Custo aumenta exponencialmente (8=0, 9=1, 10=2, ..., 15=9)
- Ajuste automático se exceder 27 pontos

**Onde encontrar:**
- [Regras D&D 5e](design/dnd-rules/point-buy.md)
- [Workflows](technical/guides/workflows.md#point-buy-system)
- [API Reference](technical/api.md#point-buy-motor)

**Relacionado:**
- Ability Scores
- FPointBuyMotor
- FPointBuyValidator
- PointBuyHelpers

---

### Multiclassing

**Definição:** Sistema que permite um personagem ter múltiplas classes, combinando features e progressão de cada classe.

**Características:**
- Personagem pode ter até 20 níveis totais (soma de todas as classes)
- Cada classe mantém progressão independente
- Features são combinadas
- Requisitos de Ability Scores devem ser atendidos

**Onde encontrar:**
- [Regras D&D 5e](design/dnd-rules/multiclassing.md)
- [Workflows](technical/guides/workflows.md#multiclassing)
- [API Reference](technical/api.md#multiclass-motor)

**Relacionado:**
- FMulticlassMotor
- FMulticlassClassFeature
- Class Features
- Character Level

---

### Gameplay Ability System (GAS)

**Definição:** Sistema nativo do Unreal Engine para gerenciar habilidades, efeitos e atributos de personagens.

**Características:**
- Attributes: valores numéricos (HP, Mana, etc.)
- Abilities: ações que o personagem pode executar
- Effects: modificadores temporários (buffs/debuffs)
- Preparado para multiplayer

**Status no Projeto:**
- 🔮 Planejado para Fase 5
- Arquitetura atual preparada para migração
- Componentes podem ser migrados para GAS Attributes/Abilities

**Onde encontrar:**
- [Adaptação D&D 5e + GAS](design/gas-dnd-adaptation.md)
- [Arquitetura Técnica](technical/architecture.md#preparation-for-gas)
- [ARCHITECTURE.md](../ARCHITECTURE.md#preparation-for-gas)

**Relacionado:**
- UCharacterDataComponent
- Feature Components
- Attributes
- Abilities

---

### Data-Oriented Design (DOD)

**Definição:** Organização de dados focada no layout físico na memória, priorizando cache hits e performance sobre modelagem orientada a objetos.

**Princípios:**
- Array of Structures (AoS) → Structure of Arrays (SoA)
- Cache-Friendly: dados organizados para maximizar cache hits
- SIMD-Friendly: estrutura que permite processamento paralelo

**Onde encontrar:**
- [Arquiteturas de Alta Performance](technical/data-architecture/high-performance-architectures-report.md)
- [Arquitetura Técnica](technical/architecture.md#data-oriented-design)

**Relacionado:**
- ECS (Entity Component System)
- Performance
- Memory Layout

---

### Entity Component System (ECS)

**Definição:** Padrão arquitetural que desacopla identidade (Entity), dados (Component) e lógica (System), permitindo composição dinâmica e escalabilidade.

**Estratégias:**
- Arquétipos (Archetypes): agrupa entidades com mesma combinação de componentes
- Sparse Sets: arrays esparsos para flexibilidade dinâmica

**Onde encontrar:**
- [Arquiteturas de Alta Performance](technical/data-architecture/high-performance-architectures-report.md)
- [Arquitetura Técnica](technical/architecture.md#entity-component-system)

**Relacionado:**
- Data-Oriented Design
- Component-Based Architecture
- Performance

---

### Normalização de Dados

**Definição:** Eliminação de redundância através de tabelas de referência (Master Data) e uso consistente de IDs únicos para todas as entidades.

**Padrão Implementado:**
- **Name + ID + Tags + Payload:**
  - `Name`: Key Field (obrigatório pelo Unreal Engine)
  - `ID`: Identificador único interno
  - `Tags`: Gameplay Tags para categorização
  - `Payload`: Dados específicos da entidade

**Onde encontrar:**
- [Arquitetura de Banco de Dados](technical/data-architecture/database-architecture.md)
- [Estrutura de Dados Ideal](technical/data-architecture/ideal-data-structure-report.md)

**Relacionado:**
- FDataTableRowHandle
- Gameplay Tags
- Master Data
- Referências Type-Safe

---

## 🎨 Padrões de Design

### Strategy Pattern

**Definição:** Permite definir uma família de algoritmos, encapsulá-los e torná-los intercambiáveis.

**Uso no Projeto:**
- Handlers de propriedades (CharacterSheetDataAssetHandlers)
- Validators (FPointBuyValidator, FMulticlassValidator)
- Motores (FPointBuyMotor, FMulticlassMotor)

**Onde encontrar:**
- [Arquitetura Técnica](technical/architecture.md)
- [CharacterSheetDataAssetHandlers](../Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h)

**Relacionado:**
- Factory Pattern
- Command Pattern
- Template Method Pattern

---

### Factory Pattern

**Definição:** Fornece uma interface para criar objetos sem especificar suas classes concretas.

**Uso no Projeto:**
- Criação de handlers (CharacterSheetDataAssetInitializers)
- Criação de FLogContext
- Inicialização de componentes

**Onde encontrar:**
- [Arquitetura Técnica](technical/architecture.md)
- [CharacterSheetDataAssetInitializers](../Source/MyProject2/Characters/Data/Initializers/CharacterSheetDataAssetInitializers.h)

**Relacionado:**
- Strategy Pattern
- Builder Pattern

---

### Observer Pattern

**Definição:** Define uma dependência um-para-muitos entre objetos, de modo que quando um objeto muda de estado, todos os dependentes são notificados.

**Uso no Projeto:**
- 🔮 Planejado: múltiplos observers por propriedade
- Handlers de mudança de propriedade (PostEditChangeProperty)

**Onde encontrar:**
- [Arquitetura Técnica](technical/architecture.md)
- [CharacterSheetDataAssetHandlers](../Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h)

**Relacionado:**
- Strategy Pattern
- Command Pattern

---

### Template Method Pattern

**Definição:** Define o esqueleto de um algoritmo em uma classe base, deixando subclasses sobrescreverem etapas específicas.

**Uso no Projeto:**
- Processo de criação de personagem (CharacterSheetCore)
- Algoritmo de criação de ficha (algorithmic/character-creation.md)

**Onde encontrar:**
- [Guia Algorítmico](technical/guides/algorithmic/character-creation.md)
- [CharacterSheetCore](../Source/MyProject2/CreateSheet/Core/CharacterSheetCore.h)

**Relacionado:**
- Strategy Pattern
- Builder Pattern

---

### Command Pattern

**Definição:** Encapsula uma solicitação como um objeto, permitindo parametrizar clientes com diferentes solicitações.

**Uso no Projeto:**
- Wrapper functions (CharacterSheetDataAssetHandlers)
- Operações de atualização (CharacterSheetDataAssetUpdaters)

**Onde encontrar:**
- [Arquitetura Técnica](technical/architecture.md)
- [CharacterSheetDataAssetHandlers](../Source/MyProject2/Characters/Data/Handlers/CharacterSheetDataAssetHandlers.h)

**Relacionado:**
- Strategy Pattern
- Factory Pattern

---

### RAII Pattern

**Definição:** Resource Acquisition Is Initialization - recursos são adquiridos na inicialização e liberados na destruição.

**Uso no Projeto:**
- FValidationGuard: gerencia `bIsValidatingProperties` automaticamente
- Garante limpeza de recursos mesmo em caso de exceção

**Onde encontrar:**
- [CharacterSheetDataAssetHelpers](../Source/MyProject2/Characters/Data/Helpers/CharacterSheetDataAssetHelpers.h)

**Relacionado:**
- Guard Pattern
- Clean Code

---

## 🔧 Componentes e Estruturas

### UCharacterSheetDataAsset

**Definição:** Data Asset que armazena configuração estática de uma ficha de personagem no editor.

**Características:**
- Camada 1: Data Assets (Editor/Configuração)
- Editável apenas em defaults
- Não replicável (não necessário em runtime)
- Validação em `PostEditChangeProperty()`

**Onde encontrar:**
- [API Reference](technical/api.md#charactersheetdataasset)
- [Arquitetura Técnica](technical/architecture.md#camada-1-data-assets)

**Relacionado:**
- UCharacterSheetComponent
- UCharacterDataComponent
- Data-Driven Design

---

### UCharacterSheetComponent

**Definição:** Bridge Component que aplica regras do Data Asset para o Runtime Component.

**Características:**
- Camada 2: Bridge Components (Aplicação de Regras)
- Executa apenas no server/local
- Aplica regras de raça e classe
- Carrega dados do Data Asset para Runtime Component

**Onde encontrar:**
- [API Reference](technical/api.md#charactersheetcomponent)
- [Arquitetura Técnica](technical/architecture.md#camada-2-bridge-components)

**Relacionado:**
- UCharacterSheetDataAsset
- UCharacterDataComponent
- FCharacterSheetCore

---

### UCharacterDataComponent

**Definição:** Runtime Component que armazena dados do personagem em runtime, todas as propriedades são replicáveis.

**Características:**
- Camada 3: Runtime Data Components (Dados Replicáveis)
- Todas as propriedades são replicáveis (`DOREPLIFETIME`)
- Calcula atributos finais, HP, proficiência
- Preparado para migração para GAS Attributes

**Onde encontrar:**
- [API Reference](technical/api.md#characterdatacomponent)
- [Arquitetura Técnica](technical/architecture.md#camada-3-runtime-data-components)

**Relacionado:**
- UCharacterSheetComponent
- GAS Attributes
- Replication

---

### FCharacterSheetCore

**Definição:** Core genérico de criação de ficha - Orquestrador de motores.

**Características:**
- Orquestra todos os motores de criação de personagem
- Genérico: funciona tanto no Data Asset quanto no Widget
- Fórmula: `FinalScore = BASE_ABILITY_SCORE + RacialBonus + PointBuyAllocation`

**Onde encontrar:**
- [API Reference](technical/api.md#charactersheetcore)
- [CharacterSheetCore](../Source/MyProject2/CreateSheet/Core/CharacterSheetCore.h)

**Relacionado:**
- FPointBuyMotor
- FMulticlassMotor
- FRaceBonusMotor

---

## 🎮 Sistemas de Jogo

### Ability Scores

**Definição:** Os 6 atributos principais de um personagem D&D 5e: Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma.

**Valores:**
- Range: 1-30 (padrão: 8-15 para Point Buy)
- Modificador: `(Score - 10) / 2` (arredondado para baixo)
- Base: 8 (para Point Buy)

**Onde encontrar:**
- [Regras D&D 5e](design/dnd-rules/ability-scores.md)
- [API Reference](technical/api.md#ability-scores)

**Relacionado:**
- Point Buy System
- Modifiers
- Saving Throws

---

### Proficiencies

**Definição:** Habilidades, armas, armaduras ou ferramentas em que o personagem é proficiente, recebendo bônus de proficiência.

**Bônus de Proficiência:**
- Nível 1-4: +2
- Nível 5-8: +3
- Nível 9-12: +4
- Nível 13-16: +5
- Nível 17-20: +6

**Onde encontrar:**
- [Regras D&D 5e](design/dnd-rules/)
- [API Reference](technical/api.md#proficiencies)

**Relacionado:**
- Skills
- Saving Throws
- Weapon Proficiencies

---

### Features

**Definição:** Habilidades especiais que um personagem ganha através de classe, raça ou feats.

**Tipos:**
1. **Automático:** Aplicado automaticamente
2. **Escolha Única:** Escolher 1 item de uma lista (ex: Fighting Style)
3. **Escolhas Múltiplas:** Escolher várias opções de uma lista (ex: Maneuvers, Metamagic)

**Onde encontrar:**
- [Regras D&D 5e](design/dnd-rules/level-up.md)
- [API Reference](technical/api.md#features)

**Relacionado:**
- Class Features
- Race Features
- Feats

---

## 📊 Estruturas de Dados

### FDataTableRowHandle

**Definição:** Referência type-safe entre Data Tables, garantindo que referências sejam válidas em tempo de compilação.

**Características:**
- Type-safe: compilador verifica tipos
- Não permite referências por string/Name
- Resolve para `FTableRowBase*` em runtime

**Onde encontrar:**
- [Arquitetura de Banco de Dados](technical/data-architecture/database-architecture.md)
- [API Reference](technical/api.md#datatablerowhandle)

**Relacionado:**
- Data Tables
- Normalização
- Referências Type-Safe

---

### Gameplay Tags

**Definição:** Sistema de tags hierárquicas do Unreal Engine para categorização flexível de entidades.

**Características:**
- Hierárquico: `Character.Race.Dwarf`
- Query flexível: `Character.Race.*`
- Categorização sem hardcoding

**Onde encontrar:**
- [Arquitetura de Banco de Dados](technical/data-architecture/database-architecture.md)
- [MyProject2Tags.ini](../Content/Data/GameplayTags/MyProject2Tags.ini)

**Relacionado:**
- TypeTags
- Categorização
- FGameplayTagContainer

---

### TSoftObjectPtr

**Definição:** Soft reference para lazy loading de assets, permitindo referenciar assets sem carregá-los imediatamente.

**Características:**
- Lazy loading: carrega apenas quando necessário
- Não bloqueia carregamento de nível
- Útil para assets grandes

**Onde encontrar:**
- [Arquitetura de Banco de Dados](technical/data-architecture/database-architecture.md)

**Relacionado:**
- Soft References
- Lazy Loading
- Performance

---

## 🧪 Testes

### Test-Driven Development (TDD)

**Definição:** Metodologia de desenvolvimento onde testes são escritos ANTES da implementação, seguindo o ciclo Red-Green-Refactor.

**Ciclo:**
1. **Red:** Escrever teste que falha
2. **Green:** Implementação mínima que faz teste passar
3. **Refactor:** Melhorar código com testes garantindo comportamento

**Onde encontrar:**
- [TDD Complete Guide](technical/guides/tdd-complete-guide.md)
- [Testing Guide](technical/guides/testing.md)

**Relacionado:**
- Unit Tests
- Integration Tests
- Clean Code

---

### Unit Tests

**Definição:** Testes que verificam unidades individuais de código em isolamento.

**Padrões no Projeto:**
- `IMPLEMENT_SIMPLE_AUTOMATION_TEST` - Testes simples
- `BEGIN_DEFINE_SPEC` - Testes BDD-style (Describe/It)

**Onde encontrar:**
- [Testing Guide](technical/guides/testing.md)
- [Source/MyProject2/Utils/Tests/](../Source/MyProject2/Utils/Tests/)

**Relacionado:**
- Integration Tests
- TDD
- Test Coverage

---

### Integration Tests

**Definição:** Testes que verificam a interação entre diferentes unidades ou componentes.

**Tipos no Projeto:**
- End-to-End (E2E): fluxo completo de criação de personagem
- Component Integration: interação entre componentes

**Onde encontrar:**
- [Testing Guide](technical/guides/testing.md)
- [Source/MyProject2/Tests/Integration/](../Source/MyProject2/Tests/Integration/)

**Relacionado:**
- Unit Tests
- E2E Tests
- Test Coverage

---

## 🔗 Referências Cruzadas

### Por Categoria

**Arquitetura:**
- Data-Driven Design
- Component-Based Architecture
- Data-Oriented Design
- ECS

**Padrões de Design:**
- Strategy Pattern
- Factory Pattern
- Observer Pattern
- Template Method Pattern
- Command Pattern
- RAII Pattern

**Sistemas de Jogo:**
- Point Buy System
- Multiclassing
- Ability Scores
- Proficiencies
- Features

**Estruturas de Dados:**
- FDataTableRowHandle
- Gameplay Tags
- TSoftObjectPtr
- Normalização

**Testes:**
- TDD
- Unit Tests
- Integration Tests

---

## 📖 Como Usar Este Glossário

1. **Busca Rápida:** Use Ctrl+F para encontrar conceitos
2. **Referências:** Cada entrada tem links para documentação relacionada
3. **Relacionados:** Veja conceitos relacionados no final de cada entrada
4. **Navegação:** Use [NAVIGATION.md](NAVIGATION.md) para encontrar documentos específicos

---

**Última atualização:** 2024-12-27
