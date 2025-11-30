# Arquitetura do Projeto - MyProject2

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v2.0 | 2024-12-27 | Refatoração: removido frontmatter, atualizado para estrutura numerada |
| v1.0 | 2024-12-27 | Versão inicial |

---

## 📋 Índice deste Documento

1. [Visão Geral](#visão-geral)
2. [Princípios de Design](#princípios-de-design)
3. [Arquitetura em Camadas](#arquitetura-em-camadas)
4. [Fluxo de Dados](#fluxo-de-dados)
5. [Arquitetura CreateSheet/](#arquitetura-createsheet)
6. [Data-Oriented Design e ECS](#-data-oriented-design-e-ecs)
7. [Preparação para GAS](#preparação-para-gas-gameplay-ability-system)
8. [Regras de Implementação](#regras-de-implementação)
9. [Checklist de Arquitetura](#checklist-de-arquitetura)
10. [Estrutura de Arquivos Recomendada](#estrutura-de-arquivos-recomendada)
11. [Sistema de Logging](#sistema-de-logging)
12. [Referências](#referências)

---

## Visão Geral

Este documento descreve a arquitetura do projeto, baseada em princípios de design que garantem código limpo, manutenível, escalável e preparado para multiplayer.

## Princípios de Design

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 5 Princípios Fundamentais</b></summary>

> Os 5 princípios fundamentais que guiam a arquitetura do projeto:
>

</details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 1. Data-Driven</summary>

    > **Conceito:** Todas as regras vêm de Data Tables ou Data Assets, não de código hardcoded.
    >
    > **Benefícios:**
    >
    > - ✅ Designers podem modificar regras sem programadores
    > - ✅ Fácil adicionar novo conteúdo
    > - ✅ Suporte a localização
    > - ✅ Validação automática
    >
    > **Implementação:**
    >
    > - Use `UDataTable` para dados tabulares (raças, classes, itens)
    > - Use `UDataAsset` para configurações complexas (fichas de personagem)
    > - Valide dados no editor com `PostEditChangeProperty()`
    > - Use `FTableRowBase` para estruturas de dados
    >
    > **Exemplo:**
    >
    > ```cpp
    > // ✅ CORRETO - Data-Driven
    > UPROPERTY(EditDefaultsOnly, Category = "Data")
    > UDataTable* RaceDataTable;
    >
    > // ❌ ERRADO - Hardcoded
    > const float DwarfConstitutionBonus = 2.0f;
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧩 2. Modularidade</summary>

    > **Conceito:** Código organizado por domínio, cada parte com responsabilidade única e clara. Baseado em **Composição sobre Herança** e **Data-Oriented Design**.
    >
    > **Benefícios:**
    >
    > - ✅ Fácil manutenção
    > - ✅ Fácil expansão
    > - ✅ Código limpo e organizado
    > - ✅ Reutilização de componentes
    > - ✅ Performance otimizada (layout de memória eficiente)
    > - ✅ Flexibilidade através de composição
    >
    > **Filosofia:**
    >
    > - **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
    > - **Separação Static/Dynamic**: Definições em Data Tables (static), estado em componentes runtime (dynamic)
    > - **Data-Oriented Design**: Organize dados por layout de memória, não por hierarquia de classes
    >
    > **Estrutura de Diretórios:**
    >
    > ```
    > Source/MyProject2/
    > ├── Characters/          # Personagens e raças
    > │   ├── Data/           # Data Assets de personagens
    > │   └── Components/      # Componentes de personagem
    > ├── Components/          # Componentes reutilizáveis
    > │   ├── Data/           # Componentes de dados
    > │   ├── Features/        # Componentes de features
    > │   └── UI/             # Componentes de UI
    > ├── Data/               # Data Assets e Data Tables
    > │   ├── Tables/         # Data Tables
    > │   └── Assets/         # Data Assets
    > ├── Gameplay/           # Mecânicas de jogo
    > │   ├── Abilities/      # Habilidades
    > │   └── Systems/        # Sistemas de jogo
    > └── Utils/              # Utilitários
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🛠️ 3. Editor-Friendly</summary>

    > **Conceito:** Sistema funciona perfeitamente no editor, permitindo configuração rápida sem rodar o jogo.
    >
    > **Benefícios:**
    >
    > - ✅ Designers podem trabalhar sem rodar o jogo
    > - ✅ Testes rápidos
    > - ✅ Iteração rápida
    > - ✅ Validação em tempo real
    >
    > **Implementação:**
    >
    > - Use `WITH_EDITOR` para código específico do editor
    > - Valide dados em `PostEditChangeProperty()`
    > - Use `UPROPERTY(EditAnywhere)` para propriedades editáveis
    > - Forneça feedback visual no editor quando possível
    >
    > **Exemplo:**
    >
    > ```cpp
    > #if WITH_EDITOR
    > void UCharacterSheetDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
    > {
    >     Super::PostEditChangeProperty(PropertyChangedEvent);
    >     ValidateData();
    > }
    > #endif
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌐 4. Preparação para Multiplayer</summary>

    > **Conceito:** Sistema preparado para multiplayer desde o início, não precisa refatorar depois.
    >
    > **Benefícios:**
    >
    > - ✅ Não precisa refatorar depois
    > - ✅ Lógica autoritária correta desde o início
    > - ✅ Sincronização automática
    > - ✅ Escalável para servidor dedicado
    >
    > **Implementação:**
    >
    > - **SEMPRE** use `DOREPLIFETIME` para propriedades replicáveis
    > - **SEMPRE** valide RPCs com `WithValidation`
    > - **SEMPRE** execute lógica autoritária no servidor
    > - **SEMPRE** use `GetLocalRole()` para verificar autoridade
    > - **NUNCA** confie em dados do cliente sem validação
    >
    > **Exemplo:**
    >
    > ```cpp
    > // ✅ CORRETO - Replicação
    > void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
    > {
    >     Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    >     DOREPLIFETIME(AMyCharacter, CharacterData);
    > }
    >
    > // ✅ CORRETO - RPC com validação
    > UFUNCTION(Server, Reliable, WithValidation)
    > void ServerTakeDamage(float DamageAmount);
    >
    > bool ServerTakeDamage_Validate(float DamageAmount)
    > {
    >     return DamageAmount >= 0.0f && DamageAmount <= 1000.0f;
    > }
    >
    > void ServerTakeDamage_Implementation(float DamageAmount)
    > {
    >     // Lógica autoritária apenas no servidor
    >     if (GetLocalRole() == ROLE_Authority)
    >     {
    >         Health -= DamageAmount;
    >     }
    > }
    > ```

    </details>

    </details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 5. Separação de Responsabilidades (Component-Based Architecture)</b></summary>

>     **Conceito:** Cada camada tem responsabilidade única e bem definida.
>

>     **Benefícios:**
>
>     - ✅ Separação clara entre configuração (Editor) e execução (Runtime)
>     - ✅ Fácil testar cada camada independentemente
>     - ✅ Preparado para GAS (dados em Component, lógica em Abilities)
>     - ✅ Replicação eficiente (apenas dados necessários)
>
</details>
---

## Arquitetura em Camadas

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Arquitetura em 4 Camadas</b></summary>

> > **💡 Dica:** Veja o diagrama visual abaixo para entender melhor a arquitetura em camadas.
>

</details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📝 Camada 1: Data Assets (Editor/Configuração)</summary>

    > **Responsabilidade:** Armazenar configuração estática, não contém lógica.
    >
    > **Características:**
    >
    > - Herda de `UDataAsset`
    > - `UPROPERTY(EditDefaultsOnly)` - editável apenas em defaults
    > - Não é replicável (não precisa em runtime)
    > - Funciona apenas no editor para designers
    > - Exemplo: `UCharacterSheetDataAsset`
    >
    > **Padrão de Implementação:**
    >
    > ```cpp
    > UCLASS(BlueprintType)
    > class MYPROJECT2_API UCharacterSheetDataAsset : public UDataAsset
    > {
    >     GENERATED_BODY()
    >
    > public:
    >     UPROPERTY(EditDefaultsOnly, Category = "Character")
    >     ERace Race;
    >
    >     UPROPERTY(EditDefaultsOnly, Category = "Character")
    >     EClass Class;
    >
    >     UPROPERTY(EditDefaultsOnly, Category = "Character")
    >     TArray<FAbilityScore> BaseAbilityScores;
    >
    > #if WITH_EDITOR
    >     virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
    > #endif
    > };
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌉 Camada 2: Bridge Components (Aplicação de Regras)</summary>

    > **Responsabilidade:** Fazer ponte entre Data Asset e Runtime Component, aplicar regras de raça e classe.
    >
    > **Características:**
    >
    > - Herda de `UActorComponent`
    > - Executa apenas no servidor/local (não replicável)
    > - Aplica regras de raça e classe (`ApplyRaceBonuses()`, `ApplyClassFeatures()`)
    > - Carrega dados do Data Asset para Runtime Component
    > - Exemplo: `UCharacterSheetComponent`
    >
    > **Padrão de Implementação:**
    >
    > ```cpp
    > UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
    > class MYPROJECT2_API UCharacterSheetComponent : public UActorComponent
    > {
    >     GENERATED_BODY()
    >
    > public:
    >     UFUNCTION(BlueprintCallable, Category = "Character")
    >     void InitializeFromDataAsset(UCharacterSheetDataAsset* DataAsset);
    >
    >     UFUNCTION(BlueprintCallable, Category = "Character")
    >     void ApplyRaceBonuses();
    >
    >     UFUNCTION(BlueprintCallable, Category = "Character")
    >     void ApplyClassFeatures();
    >
    > private:
    >     UPROPERTY()
    >     UCharacterSheetDataAsset* SourceDataAsset;
    >
    >     UPROPERTY()
    >     class UCharacterDataComponent* CharacterDataComponent;
    > };
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💾 Camada 3: Runtime Data Components (Dados Replicáveis)</summary>

    > **Responsabilidade:** Armazenar dados do personagem em runtime, todas as propriedades replicáveis.
    >
    > **Características:**
    >
    > - Herda de `UActorComponent`
    > - Todas as propriedades são replicáveis (`DOREPLIFETIME`)
    > - Calcula atributos finais, HP, proficiência
    > - Preparado para migração futura para GAS Attributes
    > - Exemplo: `UCharacterDataComponent`
    >
    > **Padrão de Implementação:**
    >
    > ```cpp
    > UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
    > class MYPROJECT2_API UCharacterDataComponent : public UActorComponent
    > {
    >     GENERATED_BODY()
    >
    > public:
    >     virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    >
    >     UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
    >     float Health;
    >
    >     UPROPERTY(Replicated)
    >     float MaxHealth;
    >
    >     UPROPERTY(Replicated)
    >     FAbilityScores FinalAbilityScores;
    >
    >     UFUNCTION()
    >     void OnRep_Health();
    >
    >     UFUNCTION(BlueprintCallable, Category = "Character")
    >     void CalculateFinalAttributes();
    >
    >     UFUNCTION(BlueprintCallable, Category = "Character")
    >     void CalculateMaxHealth();
    > };
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚡ Camada 4: Feature Components (Lógica Específica)</summary>

    > **Responsabilidade:** Gerenciar features específicas de classes (spells, abilities, etc.).
    >
    > **Características:**
    >
    > - Herda de `UActorComponent`
    > - Cada um gerencia uma feature específica
    > - Podem ser migrados para GAS Abilities no futuro
    > - Exemplos planejados (Fase 5): `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`
    >
    > **Padrão de Implementação:**
    >
    > ```cpp
    > UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
    > class MYPROJECT2_API USpellcastingComponent : public UActorComponent
    > {
    >     GENERATED_BODY()
    >
    > public:
    >     virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    >
    >     UFUNCTION(BlueprintCallable, Category = "Spellcasting")
    >     void CastSpell(int32 SpellSlot);
    >
    >     UFUNCTION(Server, Reliable, WithValidation)
    >     void ServerCastSpell(int32 SpellSlot);
    >
    >     UPROPERTY(Replicated)
    >     TArray<FSpellSlot> SpellSlots;
    >
    >     UPROPERTY(Replicated)
    >     int32 SpellSlotsUsed;
    > };
    > ```

    </details>

    </details>
    <summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Diagrama Visual das Camadas</b></summary>

    >

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

    </details>

    </details>

## Fluxo de Dados

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Diagrama de Fluxo de Dados</b></summary>

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
>     style MCM fill:#fff59d
>     style CM fill:#fff59d
> ```
>
</details>
---

## Arquitetura CreateSheet/

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚙️ Motores Desacoplados para Criação de Personagem</b></summary>

> O sistema utiliza uma arquitetura modular com motores desacoplados para cálculo de ability scores finais. Esta arquitetura permite reutilização em diferentes contextos (Data Asset, Widgets) e facilita testes e manutenção.
>

</details>

    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FCharacterSheetCore - Orquestrador</summary>

    > **Localização:** `Source/MyProject2/CreateSheet/Core/CharacterSheetCore.h`
    >
    > **Responsabilidade:** Orquestrar todos os motores de criação de personagem de forma genérica.
    >
    > **Características:**
    >
    > - Função estática `RecalculateFinalScores()` que coordena todos os motores
    > - Recebe `FCharacterSheetData` (estrutura genérica) ao invés de objetos concretos
    > - Reseta scores para base (8) e aplica cada motor sequencialmente
    > - Funciona tanto no Data Asset quanto em Widgets
    >
    > **Fórmula de Cálculo:**
    >
    > ```
    > FinalScore = 8 (base) + RacialBonus + PointBuyAllocation
    > ```
    >
    > **Fluxo:**
    >
    > 1. Reseta todos os Final Scores para 8 (base)
    > 2. Aplica `FRaceBonusMotor::ApplyRacialBonuses()`
    > 3. Aplica `FPointBuyMotor::ApplyPointBuy()`

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FMulticlassMotor - Motor de Multiclassing</summary>

    > **Localização:** `Source/MyProject2/CreateSheet/Multiclass/MulticlassMotor.h`
    >
    > **Responsabilidade:** Validar e aplicar regras de multiclassing D&D 5e.
    >
    > **Características:**
    >
    > - Motor independente: não conhece outros motores, apenas aplica regras de multiclasse
    > - Genérico: recebe dados puros (`FCharacterSheetData`), não objetos concretos
    > - Valida requisitos de atributo para multiclassing D&D 5e (`GetAvailableClasses()`)
    > - Suporte para requisitos complexos (ex: "STR/13|DEX/13" - STR ou DEX >= 13)
    > - Processa mudanças de nível em classes específicas (`ProcessLevelChange()`)
    > - Busca informações de classe diretamente na ClassDataTable
    >
    > **Funções Principais:**
    >
    > - `GetAvailableClasses()` - Retorna classes disponíveis baseado em requisitos de atributo
    > - `ValidateMulticlassRequirements()` - Valida se personagem atende requisitos para nova classe
    > - `ProcessLevelChange()` - Processa mudança de nível e loga features ganhas

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔮 FChoiceMotor - Motor de Escolhas de Classe (Planejado)</summary>

    > **Status:** 🔮 Planejado para implementação futura
    >
    > **Localização Planejada:** `Source/MyProject2/CreateSheet/Choices/ChoiceMotor.h`
    >
    > **Responsabilidade Planejada:** Processar escolhas de classe (subclasses, fighting styles, etc.) baseadas em `FClassFeatureChoice` do DataTable.
    >
    > **Nota:** Atualmente, escolhas são gerenciadas por handlers/validators. Um motor dedicado pode ser criado no futuro se necessário.
    >
    > **Características Planejadas:**
    >
    > - Coletar escolhas disponíveis para uma classe até um determinado nível
    > - Buscar features do tipo "Choice" ou "SubclassSelection" no DataTable
    > - Validar escolhas contra regras do DataTable
    > - Resolver dependências entre escolhas
    > - Converter `FClassFeatureChoice` (do DataTable) para `FClassChoice` (do Data Asset)
    >
    > **Funções Planejadas:**
    >
    > - `CollectAvailableChoices()` - Coletar todas as escolhas disponíveis
    > - `ValidateChoice()` - Validar uma escolha contra as regras
    > - `ResolveDependencies()` - Resolver dependências entre escolhas
    >
    > **📖 Para mais detalhes sobre planejamento, veja [docs/planning/roadmaps/roadmap.md](../../planning/roadmaps/roadmap.md)**

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FCharacterSheetData - Estrutura Genérica</summary>

    > **Localização:** `Source/MyProject2/CreateSheet/Core/CharacterSheetData.h`
    >
    > **Responsabilidade:** Estrutura genérica de dados que permite o Core funcionar em diferentes contextos.
    >
    > **Características:**
    >
    > - Struct C++ normal (não USTRUCT) - contém ponteiros e não precisa ser exposta ao Blueprint
    > - Contém dados de entrada (Point Buy, Race, Subrace, Custom Choices)
    > - Contém referências de saída (ponteiros para Final Scores)
    > - Permite reutilização: mesmo Core funciona no Data Asset e em Widgets
    >
    > **Princípio:** "Program to an interface, not an implementation" (Design Patterns)

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FRaceBonusMotor - Motor de Bônus Raciais</summary>

    > **Localização:** `Source/MyProject2/CreateSheet/RaceBonus/RaceBonusMotor.h`
    >
    > **Responsabilidade:** Calcular e aplicar bônus raciais nos Final Scores.
    >
    > **Características:**
    >
    > - Motor independente: não conhece Point Buy, apenas aplica bônus raciais
    > - Recebe `FCharacterSheetData` (dados puros), não objetos concretos
    > - Usa `FRaceBonusHelpers` para cálculos puros
    > - Suporta Variant Human com escolhas customizadas
    >
    > **Fluxo:**
    >
    > 1. Busca RaceRow e SubraceRow usando `DataTableHelpers`
    > 2. Calcula bônus usando `FRaceBonusHelpers::CalculateRacialBonuses()`
    > 3. Incrementa Final Scores usando `FRaceBonusHelpers::IncrementFinalScoresWithRacialBonuses()`

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">FPointBuyMotor - Motor de Point Buy</summary>

    > **Localização:** `Source/MyProject2/CreateSheet/PointBuy/PointBuyMotor.h`
    >
    > **Responsabilidade:** Aplicar alocação de Point Buy nos Final Scores com validação automática.
    >
    > **Características:**
    >
    > - Motor independente: não conhece bônus raciais, apenas aplica Point Buy
    > - Valida automaticamente se não excede 27 pontos
    > - Ajusta automaticamente se exceder (reduz do final da fila)
    > - Retorna `FPointBuyResult` com feedback para o caller ajustar a UI
    >
    > **Fluxo:**
    >
    > 1. Converte dados de entrada para `TMap<FName, int32>`
    > 2. Calcula custo total usando `CharacterSheetHelpers::CalculateTotalPointBuyCost()`
    > 3. Se exceder 27 pontos, ajusta usando `AdjustPointBuyAllocation()`
    > 4. Incrementa Final Scores usando `CalculationHelpers::IncrementFinalScoresWithPointBuy()`
    > 5. Retorna `FPointBuyResult` com feedback

    </details>

    </details>

    **Princípio Fundamental:** Motores são completamente desacoplados e não conhecem uns aos outros.

    - ✅ `FRaceBonusMotor` não conhece `FPointBuyMotor`
    - ✅ `FPointBuyMotor` não conhece `FRaceBonusMotor`
    - ✅ `FMulticlassMotor` não conhece outros motores
    - ✅ `FChoiceMotor` não conhece outros motores
    - ✅ Ambos apenas incrementam Final Scores (não resetam)
    - ✅ `FCharacterSheetCore` é responsável por resetar e orquestrar

    **Benefícios:**

    - ✅ Fácil testar cada motor isoladamente
    - ✅ Fácil adicionar novos motores (ex: LevelUpMotor, FeatMotor)
    - ✅ Fácil modificar ordem de aplicação
    - ✅ Reutilização em diferentes contextos

    ### Diagrama de Arquitetura

    ```mermaid
    graph TB
    subgraph Core["CharacterSheetCore"]
    CoreFunc[RecalculateFinalScores]
    end

    subgraph Data["FCharacterSheetData"]
    Input[Point Buy, Race, Subrace]
    Output[Final Scores - Referências]
    end

    subgraph RaceMotor["RaceBonusMotor"]
    RaceApply[ApplyRacialBonuses]
    RaceHelpers[RaceBonusHelpers]
    end

    subgraph PointBuyMotor["PointBuyMotor"]
    PointBuyApply[ApplyPointBuy]
    PointBuyValidator[PointBuyValidator]
    end

    CoreFunc -->|Reseta para base 8| Output
    CoreFunc -->|Aplica| RaceApply
    CoreFunc -->|Aplica| PointBuyApply
    RaceApply -->|Usa| RaceHelpers
    PointBuyApply -->|Valida| PointBuyValidator
    RaceApply -->|Incrementa| Output
    PointBuyApply -->|Incrementa| Output
    Input -->|Dados de entrada| CoreFunc

    style Core fill:#fff59d
    style Data fill:#e1f5ff
    style RaceMotor fill:#c8e6c9
    style PointBuyMotor fill:#c8e6c9
    style MulticlassMotor fill:#c8e6c9
    ```

    **📖 Para mais detalhes sobre a implementação, veja os arquivos em `Source/MyProject2/CreateSheet/`**

---

## 🎯 Data-Oriented Design e ECS

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Princípios de Performance e Arquitetura</b></summary>

> O projeto segue princípios de **Data-Oriented Design (DOD)** e está preparado para evoluir para um padrão **Entity Component System (ECS)** quando necessário.
> >
> **Filosofia Fundamental:**
> >
> - **Composição sobre Herança**: Use composição de componentes ao invés de árvores de herança complexas
> - **Separação Static/Dynamic**: Definições em Data Tables (o que o item "é"), estado em componentes runtime (o que o item "tem" agora)
> - **Padrão "ID + Tags + Payload"**: Identificador único + metadados + dados específicos
> - **Estrutura "Flat"**: JSONs planos e relacionais, não profundamente aninhados
> >
> **Benefícios:**
> >
> - ✅ Performance otimizada (layout de memória eficiente, cache-friendly)
> - ✅ Flexibilidade através de composição
> - ✅ Escalabilidade para sistemas complexos (estilo Baldur's Gate 3)
> - ✅ Facilita migração futura para ECS completo
> >
> **Aplicação no Projeto:**
> >
> - Data Tables contêm apenas definições estáticas (raça, classe, traits)
> - Componentes runtime contêm estado dinâmico (HP atual, buffs ativos, escolhas do jogador)
> - Referências por ID, nunca por string/Name
> - Estruturas JSON planas e relacionais
> >
> **📖 Para detalhes completos sobre DOD, ECS e arquiteturas de alta performance, veja:**
> >
> - [Relatório de Arquiteturas de Alta Performance](data-architecture/high-performance-architectures-report.md)
> - [Relatório de Estrutura de Dados Ideal](data-architecture/ideal-data-structure-report.md)
> - [Arquitetura de Carregamento Centralizado (Data Registry)](data-architecture/data-registry-architecture.md) - Carregamento único e acesso O(1)
>

</details>

## Preparação para GAS (Gameplay Ability System)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Arquitetura GAS - Preparação e Padrões</b></summary>

> **Visão Geral:** O projeto está preparado para migração futura para GAS, mantendo todos os princípios fundamentais (Data-Driven, Editor-Friendly, Modularidade) e incorporando os melhores padrões de runtime do GAS.
>

> **Arquitetura Híbrida:**
> - **Dados (C):** Atributos e lógica complexa de processamento
> - **Lógica Visual (Blueprint):** Habilidades e fluxo de animações
> - **Comunicação (Tags e Events):** Sistema desacoplado via ASC
>
> **Princípio Central:** Nada é "hardcoded". Tudo se comunica via Tags, Events e Delegates, mantendo Editor-Friendly e Data-Driven.
>
</details>
    <details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📐 1. Localização do ASC (Ability System Component)</summary>

    > **Regra Fundamental:** Onde o ASC é criado depende do tipo de ator.
    >
    > **Player (Jogador):**
    > - ✅ ASC criado no **PlayerState**
    > - **Motivo:** Em multiplayer, se o peão morre, o PlayerState persiste
    > - **Benefícios:**
    >   - Atributos (vida/mana) intactos após morte
    >   - Habilidades intactas
    >   - Estado do jogador preservado
    >
    > **AI (Inimigos):**
    > - ✅ ASC criado no **próprio Character**
    > - **Motivo:** Inimigos não respawnam com persistência de dados
    > - **Benefícios:**
    >   - Morreu = destruiu (sem overhead desnecessário)
    >   - Não precisa persistir entre mortes
    >
    > **Inicialização (`InitAbilityActorInfo`):**
    > - **Server:** No `PossessedBy`
    > - **Client:** No `OnRep_PlayerState`
    > - **Garante:** Replicação correta desde o início

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💾 2. AttributeSet em C (Dados)</summary>

    > **Responsabilidade:** Definir atributos e lógica complexa de processamento.
    >
    > **Padrão:**
    > - Herda de `UAttributeSet`
    > - Define atributos (`Health`, `MaxHealth`, `Stamina`, etc.)
    > - Usa macros `ATTRIBUTE_ACCESSORS` para gerar Getters/Setters automáticos
    >
    > **Replicação:**
    > - Usa `DOREPLIFETIME_CONDITION_NOTIFY` para sincronizar atributos
    > - Sincroniza com UI do cliente automaticamente
    >
    > **Meta-Atributos (Processamento de Dano):**
    > - Cria atributos "falsos" para processamento (ex: `IncomingDamage`)
    > - **Fluxo:**
    >   1. GameplayEffect aplica valor ao `IncomingDamage`
    >   2. `PostGameplayEffectExecute` captura esse valor
    >   3. Deduz da Vida real (`Health = Health - IncomingDamage`)
    >   4. Zera o `IncomingDamage` para próximo golpe
    >
    > **Clamping:**
    > - Usa `PreAttributeChange` para garantir limites
    > - Vida nunca excede `MaxHealth` ou cai abaixo de `0`
    > - Antes mesmo da modificação ocorrer
    >
    > **Migração do Projeto:**
    > ```
    > CharacterDataComponent → GAS AttributeSet
    > - Health, MaxHealth → GAS Attributes
    > - FinalAbilityScores → GAS Attributes
    > - Lógica de cálculo → PostGameplayEffectExecute
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎨 3. Gameplay Abilities em Blueprint (Lógica Visual)</summary>

    > **Responsabilidade:** Controlar fluxo de habilidades e animações.
    >
    > **Padrão Modular:**
    > - **Habilidade Base (C ou BP):** Contém lógica comum (tocar montages, aplicar dano)
    > - **Habilidades Filhas (BP):** Apenas definem parâmetros (Montage, Efeito)
    >
    > **Fluxo de Ativação:**
    > 1. `ActivateAbility`
    > 2. Toca Animação (Montage)
    > 3. Aplica efeito (força, dano, etc.)
    > 4. `EndAbility`
    >
    > **Input Binding:**
    > - Associa Input Action (Enhanced Input) a Gameplay Tag ou ID
    > - ASC ativa habilidade correspondente àquela tag
    >
    > **Cancelamento:**
    > - Configura habilidade para ser cancelada automaticamente
    > - Se certas Tags (ex: `State.Dead`) estiverem presentes, cancela
    >
    > **Gameplay Effects (GE):**
    > - **Duration:** Para recarga (Cooldown)
    > - **Instant:** Para custos (reduz Stamina imediatamente)
    > - **Infinite:** Para regeneração passiva (Regen Stamina)
    > - Vincula GEs nos campos `CostGameplayEffectClass` e `CooldownGameplayEffectClass`
    >
    > **Migração do Projeto:**
    > ```
    > Feature Components → GAS Abilities
    > - SpellcastingComponent → GA_Spellcasting (BP)
    > - SecondWindComponent → GA_SecondWind (BP)
    > - ActionSurgeComponent → GA_ActionSurge (BP)
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📡 4. UI Reativa (Event-Driven)</summary>

    > **Responsabilidade:** Atualizar UI sem usar Tick, via Delegates.
    >
    > **Padrão:**
    > - ✅ UI **não verifica valores no Tick**
    > - ✅ UI se inscreve (Bind) em Delegates do ASC
    >
    > **Atributos:**
    > - Usa `GetGameplayAttributeValueChangeDelegate` para ouvir mudanças
    > - Quando Vida/Mana muda, atualiza barra automaticamente
    > - **Desacoplado:** UI não conhece lógica de negócio
    >
    > **Habilidades:**
    > - Escuta mudanças de Tags de Cooldown
    > - Usa `RegisterGameplayTagEvent`
    > - Desenha overlay escuro no ícone quando habilidade indisponível
    >
    > **Benefícios:**
    > - Performance (sem Tick constante)
    > - Reatividade automática
    > - Desacoplamento completo

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔧 5. Gerenciamento de Habilidades (Handles)</summary>

    > **Responsabilidade:** Gerenciar concessão e remoção de habilidades sem vazamento de memória.
    >
    > **Padrão:**
    > - Armazena `FGameplayAbilitySpecHandle` (identificadores) em `TArray`
    > - Ao conceder habilidade, salva o Handle
    > - Ao remover, usa Handle para `ClearAbility`
    >
    > **Troca de Arma/Equipamento:**
    > 1. Usa Handles para remover (`ClearAbility`) habilidades antigas
    > 2. Antes de adicionar novas
    > 3. Evita vazamento de memória ou habilidades duplicadas
    >
    > **Exemplo:**
    > ```cpp
    > UPROPERTY()
    > TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;
    >
    > void EquipWeapon(UWeaponDataAsset* WeaponData)
    > {
    >     // Remove habilidades antigas
    >     for (const FGameplayAbilitySpecHandle& Handle : GrantedAbilityHandles)
    >     {
    >         AbilitySystemComponent->ClearAbility(Handle);
    >     }
    >     GrantedAbilityHandles.Empty();
    >
    >     // Concede novas habilidades
    >     for (TSubclassOf<UGameplayAbility> AbilityClass : WeaponData->GrantedAbilities)
    >     {
    >         FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(
    >             FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this)
    >         );
    >         GrantedAbilityHandles.Add(Handle);
    >     }
    > }
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 6. Data Assets Concedendo Habilidades (Data-Driven)</summary>

    > **Responsabilidade:** Usar Data Assets para conceder habilidades, mantendo Data-Driven.
    >
    > **Padrão:**
    > - Cria DataAsset (ex: `UWeaponDataAsset`) com:
    >   - Mesh da arma
    >   - Animações associadas
    >   - **Crucialmente:** Lista de Habilidades (Classes) que a arma concede
    >
    > **Equipamento:**
    > - Ao equipar, sistema lê DataAsset
    > - Chama `GiveAbility` no ASC para cada habilidade listada
    > - **Data-Driven:** Designers podem modificar habilidades sem código
    >
    > **Exemplo:**
    > ```cpp
    > UCLASS(BlueprintType)
    > class MYPROJECT2_API UWeaponDataAsset : public UDataAsset
    > {
    >     GENERATED_BODY()
    >
    > public:
    >     UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    >     UStaticMesh* WeaponMesh;
    >
    >     UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    >     TArray<UAnimMontage*> AttackAnimations;
    >
    >     // ✅ Data-Driven: Habilidades concedidas pela arma
    >     UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    >     TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities;
    > };
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌐 7. Replication Modes (Multiplayer)</summary>

    > **Responsabilidade:** Configurar replicação adequada para Player e AI.
    >
    > **Player:**
    > - ✅ Replication Mode: **Mixed**
    > - **Motivo:** Dono vê tudo (prediction), outros veem essencial
    > - **Benefícios:**
    >   - Responsividade para o dono
    >   - Eficiência de rede (outros não recebem tudo)
    >
    > **AI:**
    > - ✅ Replication Mode: **Minimal**
    > - **Motivo:** Apenas servidor controla, clientes veem resultado visual
    > - **Benefícios:**
    >   - Economia de banda
    >   - Segurança (servidor autoritário)
    >
    > **NetMulticast:**
    > - Para tocar sons/partículas que precisam aparecer para todos
    > - Lógica (dano) roda apenas no servidor (`HasAuthority`)

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 8. Migração do Projeto Atual</summary>

    > **Preparação Atual:**
    >
    > - ✅ Dados em Components (fácil migrar para Attributes)
    > - ✅ Lógica em Components separados (fácil migrar para Abilities)
    > - ✅ Interfaces bem definidas (fácil refatorar)
    > - ✅ Replicação já configurada (GAS usa mesmo sistema)
    > - ✅ Data-Driven já implementado (Data Assets/Data Tables)
    > - ✅ Editor-Friendly já implementado (validação em tempo real)
    >
    > **Migração Futura:**
    >
    > ```
    > CharacterDataComponent → GAS AttributeSet
    > - Health, MaxHealth → GAS Attributes
    > - FinalAbilityScores → GAS Attributes
    > - Lógica de cálculo → PostGameplayEffectExecute
    >
    > Feature Components → GAS Abilities
    > - SpellcastingComponent → GA_Spellcasting (BP)
    > - SecondWindComponent → GA_SecondWind (BP)
    > - ActionSurgeComponent → GA_ActionSurge (BP)
    >
    > CharacterSheetComponent → GAS Gameplay Effects
    > - Aplicação de regras → Gameplay Effects
    > - Bônus raciais → GE Duration/Infinite
    > - Features de classe → GE com Tags
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 9. Checklist de Implementação GAS</summary>

    > **Antes de implementar GAS:**
    >
    > - [ ] ASC criado no local correto (PlayerState para Player, Character para AI)
    > - [ ] AttributeSet em C com Meta-Atributos para dano
    > - [ ] Gameplay Abilities em Blueprint (modular: Base + Filhas)
    > - [ ] UI usando Delegates (sem Tick)
    > - [ ] Handles para gerenciar concessão/remoção de habilidades
    > - [ ] Data Assets concedendo habilidades (Data-Driven)
    > - [ ] Replication Modes configurados (Mixed para Player, Minimal para AI)
    > - [ ] Validação no editor mantida (Editor-Friendly)
    > - [ ] Data Tables para regras (Data-Driven)

    </details>

    </details>

## Regras de Implementação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Guia de Regras e Padrões</b></summary>

> ### Ao Criar Novos Componentes
>

> 1. ✅ **SEMPRE** defina responsabilidade única
> 2. ✅ **SEMPRE** use `UPROPERTY()` apropriado (EditAnywhere, Replicated, etc.)
> 3. ✅ **SEMPRE** implemente `GetLifetimeReplicatedProps()` se tiver dados replicáveis
> 4. ✅ **SEMPRE** valide dados no editor quando possível
> 5. ❌ **NUNCA** misture lógica de diferentes camadas
>
</details>
    ### Ao Criar Data Assets

    1. ✅ **SEMPRE** herde de `UDataAsset`
    2. ✅ **SEMPRE** use `UPROPERTY(EditDefaultsOnly)`
    3. ❌ **NUNCA** adicione lógica, apenas dados
    4. ✅ **SEMPRE** valide dados no editor

    ### Ao Criar Features

    1. ✅ **SEMPRE** crie componente separado para cada feature
    2. ✅ **SEMPRE** use interfaces para comunicação
    3. ✅ **SEMPRE** prepare para migração futura para GAS
    4. ❌ **NUNCA** acople features diretamente

    ### Ao Implementar Multiplayer

    1. ✅ **SEMPRE** use `DOREPLIFETIME` para propriedades replicáveis
    2. ✅ **SEMPRE** valide RPCs com `WithValidation`
    3. ✅ **SEMPRE** execute lógica autoritária no servidor
    4. ✅ **SEMPRE** use `GetLocalRole() == ROLE_Authority` para verificar autoridade
    5. ❌ **NUNCA** confie em dados do cliente sem validação

---

## Checklist de Arquitetura

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Checklist Antes de Criar Novo Código</b></summary>

> Antes de criar novo código, verifique:
>

> - [ ] É Data-Driven? (usa Data Tables/Assets?)
> - [ ] É Modular? (responsabilidade única?)
> - [ ] Funciona no Editor? (pode configurar sem rodar?)
> - [ ] É Multiplayer-Ready? (replicação correta?)
> - [ ] Separação de Responsabilidades? (camada correta?)
> - [ ] Segue padrões de nomenclatura?
> - [ ] Está documentado?
> - [ ] Compila sem warnings?
>
</details>
---

## Estrutura de Arquivos Recomendada

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📁 Organização de Diretórios e Arquivos</b></summary>

> ```mermaid
> graph TD
> Root[Source/MyProject2/] --> Chars[Characters/]
> Root --> CreateSheet[CreateSheet/]
> Root --> Comp[Components/]
> Root --> Data[Data/]
> Root --> Gameplay[Gameplay/]
> Root --> Utils[Utils/]
>

> Chars --> CharsData[Data/<br/>CharacterSheetDataAsset]
> Chars --> CharsComp[Components/<br/>CharacterSheetComponent<br/>CharacterDataComponent]
>
> CreateSheet --> CreateSheetCore[Core/<br/>CharacterSheetCore<br/>CharacterSheetData]
> CreateSheet --> CreateSheetRace[RaceBonus/<br/>RaceBonusMotor<br/>RaceBonusHelpers]
> CreateSheet --> CreateSheetPointBuy[PointBuy/<br/>PointBuyMotor<br/>PointBuyValidator]
> CreateSheet --> CreateSheetMulticlass[Multiclass/<br/>MulticlassMotor<br/>MulticlassHelpers]
> CreateSheet --> CreateSheetChoices[Choices/<br/>🔮 Planejado]
>
> Comp --> CompFeat[Features/<br/>🔮 Planejado<br/>SpellcastingComponent<br/>SecondWindComponent]
> Comp --> CompData[Data/]
>
> Data --> DataTab[Tables/<br/>RaceDataTable<br/>ClassDataTable]
> Data --> DataAssets[Assets/]
>
> Gameplay --> GameplayAbil[Abilities/]
> Gameplay --> GameplaySys[Systems/]
>
> Utils --> UtilsCalc[CalculationHelpers]
> Utils --> UtilsChar[CharacterSheetHelpers]
> Utils --> UtilsData[DataTableHelpers]
> Utils --> UtilsVal[ValidationHelpers]
> Utils --> UtilsFmt[FormattingHelpers]
> Utils --> UtilsComp[ComponentHelpers]
>
> style Root fill:#2196f3,color:#fff
> style Chars fill:#4caf50,color:#fff
> style CreateSheet fill:#ffc107,color:#000
> style Comp fill:#ff9800,color:#fff
> style Data fill:#9c27b0,color:#fff
> style Gameplay fill:#f44336,color:#fff
> style Utils fill:#00bcd4,color:#fff
> ```
>
</details>
    ### Estrutura Detalhada

    ```
    Source/MyProject2/
    ├── Characters/
    │   ├── Data/
    │   │   ├── CharacterSheetDataAsset.h
    │   │   ├── CharacterSheetDataAsset.cpp
    │   │   ├── Handlers/
    │   │   │   ├── CharacterSheetDataAssetHandlers.h
    │   │   │   └── CharacterSheetDataAssetHandlers.cpp
    │   │   ├── Validators/
    │   │   │   ├── CharacterSheetDataAssetValidators.h
    │   │   │   └── CharacterSheetDataAssetValidators.cpp
    │   │   ├── Updaters/
    │   │   │   ├── CharacterSheetDataAssetUpdaters.h
    │   │   │   └── CharacterSheetDataAssetUpdaters.cpp
    │   │   ├── Helpers/
    │   │   │   ├── CharacterSheetDataAssetHelpers.h
    │   │   │   ├── CharacterSheetDataAssetHelpers.cpp
    │   │   │   ├── ValidationGuard.h
    │   │   │   └── ValidationGuard.cpp
    │   │   └── GetOptions/
    │   │       ├── CharacterSheetDataAssetGetOptions.h
    │   │       └── CharacterSheetDataAssetGetOptions.cpp
    │   └── Components/
    │       ├── CharacterSheetComponent.h
    │       ├── CharacterSheetComponent.cpp
    │       ├── CharacterDataComponent.h
    │       └── CharacterDataComponent.cpp
    ├── CreateSheet/
    │   ├── Core/
    │   │   ├── CharacterSheetCore.h
    │   │   ├── CharacterSheetCore.cpp
    │   │   └── CharacterSheetData.h
    │   ├── RaceBonus/
    │   │   ├── RaceBonusMotor.h
    │   │   ├── RaceBonusMotor.cpp
    │   │   ├── RaceBonusHelpers.h
    │   │   └── RaceBonusHelpers.cpp
    │   ├── PointBuy/
    │   │   ├── PointBuyMotor.h
    │   │   ├── PointBuyMotor.cpp
    │   │   ├── PointBuyValidator.h
    │   │   ├── PointBuyValidator.cpp
    │   │   └── PointBuyResult.h
    │   ├── Multiclass/
    │   │   ├── MulticlassMotor.h
    │   │   ├── MulticlassMotor.cpp
    │   │   ├── MulticlassHelpers.h
    │   │   └── MulticlassHelpers.cpp
    │   └── (Choices/ - 🔮 Planejado)
    ├── Components/
    │   ├── (Features/ - 🔮 Planejado para Fase 5)
    │   │   │   ├── SpellcastingComponent.h
    │   │   │   ├── SpellcastingComponent.cpp
    │   │   │   ├── SecondWindComponent.h
    │   │   │   └── SecondWindComponent.cpp
    │   └── Data/
    │       └── (componentes de dados genéricos)
    ├── Logging/
    │   ├── LoggingSystem.h
    │   └── LoggingSystem.cpp
    ├── Data/
    │   ├── Tables/
    │   │   ├── RaceDataTable.h
    │   │   ├── ClassDataTable.h
    │   │   ├── BackgroundDataTable.h
    │   │   └── FeatDataTable.h
    │   └── Assets/
    │       └── (data assets)
    ├── Gameplay/
    │   ├── Abilities/
    │   └── Systems/
    └── Utils/
    ├── CalculationHelpers.h
    ├── CalculationHelpers.cpp
    ├── CharacterSheetHelpers.h
    ├── CharacterSheetHelpers.cpp
    ├── DataTableHelpers.h
    ├── DataTableHelpers.cpp
    ├── ValidationHelpers.h
    ├── ValidationHelpers.cpp
    ├── FormattingHelpers.h
    ├── FormattingHelpers.cpp
    ├── ComponentHelpers.h
    └── ComponentHelpers.cpp
    ```

---

### Organização Modular do CharacterSheetDataAsset

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔧 Arquitetura Modular do CharacterSheetDataAsset</b></summary>

> O `CharacterSheetDataAsset` utiliza uma arquitetura modular baseada em responsabilidades separadas, seguindo princípios de Clean Code e Design Patterns. A organização em módulos facilita manutenção, testes e extensibilidade.
>

> **Estrutura Modular:**
>
> ```mermaid
> graph TD
> CSDA[CharacterSheetDataAsset] --> H[Handlers]
> CSDA --> V[Validators]
> CSDA --> U[Updaters]
> CSDA --> HLP[Helpers]
> CSDA --> GO[GetOptions]
> CSDA --> T[Types]
>
> H --> |Handle Property Changes| CSDA
> V --> |Validate Data| CSDA
> U --> |Update Calculated Fields| CSDA
> HLP --> |Helper Functions| CSDA
> GO --> |Dropdown Options| CSDA
> T --> |Type Definitions| CSDA
> ```
>
> **Módulos e Responsabilidades:**
>
</details>
    #### Handlers (`Handlers/CharacterSheetDataAssetHandlers`)

    **Responsabilidade:** Processar mudanças de propriedades no editor via `PostEditChangeProperty()`.

    **Padrão:** Map/Table-Driven com ponteiros de função estáticos (Lookup Table Pattern).

    **Funções principais:**

    - `HandleRaceChange()` - Processa mudanças em raça/sub-raça
    - `HandleAbilityScoresChange()` - Processa mudanças em ability scores
    - `HandleClassLevelsChange()` - Processa mudanças em níveis de classe
    - `HandleBackgroundChange()` - Processa mudanças em background
    - `HandleVariantHumanChoicesChange()` - Processa escolhas de Variant Human
    - `HandleDataTableChange()` - Processa seleção de Data Tables

    **Exemplo de uso:**

    ```cpp
    // PostEditChangeProperty usa lookup table para encontrar handler
    if (PropertyHandlerFunction *HandlerPtr = PropertyHandlers.Find(PropertyName))
    {
    (*HandlerPtr)(this, PropertyName);
    }
    ```

    #### Validators (`Validators/CharacterSheetDataAssetValidators`)

    **Responsabilidade:** Validar integridade e consistência dos dados.

    **Funções principais:**

    - `ValidatePointBuy()` - Valida sistema Point Buy (27 pontos, scores 8-15)
    - `ValidateTotalLevel()` - Valida nível total (máximo 20)
    - `ValidateVariantHumanChoices()` - Valida escolhas de Variant Human

    **Características:**

    - Funções puras (sem side effects além de validação)
    - Retornam void (modificam Asset diretamente se necessário)
    - Logam erros quando dados inválidos

    #### Updaters (`Updaters/CharacterSheetDataAssetUpdaters`)

    **Responsabilidade:** Atualizar campos calculados baseados em dados do personagem.

    **Funções principais:**

    - `UpdateRacialBonuses()` - Calcula e aplica bônus raciais nos ability scores
    - `UpdateCalculatedFields()` - Atualiza proficiências, features disponíveis
    - `UpdateVariantHumanFlag()` - Atualiza flag bIsVariantHuman
    - `UpdateSheetVisibility()` - Controla visibilidade de categorias no editor

    **Características:**

    - Executam cálculos baseados em dados atuais
    - Atualizam campos derivados automaticamente
    - Garantem consistência entre dados relacionados

    #### Helpers (`Helpers/CharacterSheetDataAssetHelpers`)

    **Responsabilidade:** Funções auxiliares reutilizáveis.

    **Funções principais:**

    - `InitializeDefaultAbilityScores()` - Inicializa ability scores padrão (todos em 8)
    - `ResetVariantHumanChoices()` - Reseta escolhas de Variant Human

    **Características:**

    - Funções puras e parametrizadas
    - Reutilizáveis em diferentes contextos
    - Testáveis isoladamente

    #### GetOptions (`GetOptions/CharacterSheetDataAssetGetOptions`)

    **Responsabilidade:** Lógica para popular dropdowns no editor.

    **Funções principais:**

    - `GetRaceNames()` - Retorna nomes de raças disponíveis
    - `GetSubraceNames()` - Retorna sub-raças para raça selecionada
    - `GetClassNames()` - Retorna nomes de classes
    - `GetAbilityScoreNames()` - Retorna nomes dos 6 atributos
    - `GetAvailableFeatNames()` - Retorna feats disponíveis
    - `GetAvailableChoiceNames()` - Retorna todas as escolhas de todas as features
    - `GetAvailableChoiceNamesForFeature(FName FeatureFC_ID)` - Retorna escolhas filtradas por FC_ID de feature específica

    **Filtro por Feature:**
    - `GetAvailableChoiceNamesForFeature()` filtra escolhas por `FC_ID` da feature
    - Usado em `FMulticlassClassFeature.AvailableChoices` para mostrar apenas escolhas da feature específica
    - Meta tag: `GetOptionsFunctionParams = "FC_ID"` passa o FC_ID automaticamente
    - Exemplo: Fighting Style mostra apenas estilos de luta, não todas as escolhas de todas as features

    **Nota:** As funções `UFUNCTION(CallInEditor)` devem permanecer na classe `UCharacterSheetDataAsset` (requisito do Unreal Engine), mas a lógica foi extraída para este módulo.

    #### Types (`CharacterSheetDataAssetTypes.h`)

    **Responsabilidade:** Definições de tipos compartilhados.

    **Tipos definidos:**

    - `FAbilityScoreEntry` - Estrutura para ability scores (BaseScore, RacialBonus, FinalScore)

    **Benefício:** Evita dependências circulares e facilita reutilização.

    **Fluxo de Validação e Atualização:**

    ```mermaid
    sequenceDiagram
    participant Editor
    participant CSDA as CharacterSheetDataAsset
    participant Handler
    participant Validator
    participant Updater

    Editor->>CSDA: Modifica propriedade
    CSDA->>Handler: PostEditChangeProperty
    Handler->>Validator: ValidatePointBuy
    Handler->>Validator: ValidateTotalLevel
    Handler->>Updater: UpdateRacialBonuses
    Handler->>Updater: UpdateCalculatedFields
    Updater-->>CSDA: Dados atualizados
    CSDA-->>Editor: UI atualizada
    ```

    **Vantagens da Organização Modular:**

    - **Manutenibilidade:** Cada módulo tem responsabilidade única e clara
    - **Testabilidade:** Funções estáticas podem ser testadas isoladamente
    - **Extensibilidade:** Fácil adicionar novos handlers, validators ou updaters
    - **Clean Code:** Funções pequenas (< 50 linhas), focadas, reutilizáveis
    - **Performance:** Lookup table com ponteiros de função estáticos (sem overhead de std::function)

---

## Sistema de Logging

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 FLoggingSystem - Sistema Centralizado de Logging</b></summary>

> **Caminho:** `Source/MyProject2/Logging/LoggingSystem.h`
>

> **Responsabilidade:** Sistema centralizado de logging com suporte a popups no editor e throttle para evitar poluição visual.
>
</details>
    ### Arquitetura do Sistema

    O sistema de logging segue uma arquitetura em camadas:

    1. **Camada de Interface:** Métodos públicos (`LogError`, `LogWarning`, etc.)
    2. **Camada de Formatação:** Formatação de mensagens com contexto
    3. **Camada de Output:** `UE_LOG` (sempre imediato) + Popups no editor (opcional, com throttle)

    ### Métodos Padrão vs Métodos com Throttle

    **Métodos Padrão:**
    - `LogError()`, `LogWarning()`, `LogFatal()` - Popup imediato
    - Usados para erros únicos e críticos

    **Métodos com Throttle:**
    - `LogErrorWithThrottledPopup()`, `LogWarningWithThrottledPopup()` - Popup throttled
    - Log (UE_LOG) sempre imediato, popup visual limitado a 0.5s entre chamadas
    - Usados em loops de validação que podem gerar múltiplos erros

    ### Implementação do Throttle

    O throttle usa `FTimerHandle` estático compartilhado:
    - Cancela popup anterior quando nova chamada é feita
    - Mostra apenas o último popup após delay (padrão: 0.5s)
    - Mantém logging imediato (UE_LOG não é afetado)

    **Benefícios:**
    - ✅ Editor não fica poluído com múltiplos popups
    - ✅ Logging sempre imediato (não perde informações)
    - ✅ Configurável (delay ajustável)
    - ✅ Nomes descritivos indicam comportamento exato

    **📖 Para documentação completa da API, veja [docs/technical/api.md](api.md#sistema-de-logging-floggingsystem)**

---

## Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação do Projeto</b></summary>

> - **[README Principal](../../README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](../../ARCHITECTURE.md)** - Resumo da arquitetura
> - **[CHANGELOG.md](../../CHANGELOG.md)** - Histórico de mudanças
> - **[Índice de Documentação](../index.md)** - Organização completa da documentação
> - **[API Reference](api.md)** - Referência completa da API
> - **[Guias Práticos](guides/)** - Guias passo a passo
>

</details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links e Documentação Externa</b></summary>

> - [Unreal Engine 5.7 Documentation](https://docs.unrealengine.com/5.7/)
> - [Replication Documentation](https://docs.unrealengine.com/5.7/en-US/replication-in-unreal-engine/)
> - [Component System](https://docs.unrealengine.com/5.7/en-US/components-in-unreal-engine/)
> - [Data Assets](https://docs.unrealengine.com/5.7/en-US/data-assets-in-unreal-engine/)
>

</details>
