# Changelog

Todas as mudanças notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Semantic Versioning](https://semver.org/lang/pt-BR/).

<details open>
<summary>📋 Versões</summary>

- **[Unreleased](#unreleased)** - Mudanças em desenvolvimento
- **[0.4.0](#040---2024-11-25)** - Sistema de multiclassing completo e melhorias de qualidade de código
- **[0.3.0](#030---2024-12-20)** - Sistema completo de raça e background com escolhas de idiomas
- **[0.2.0](#020---2024-12-xx)** - Refatoração modular e validação de integridade
- **[0.1.0](#010---2024-12-xx)** - Sistema básico de fichas de personagem

</details>

---

## Versões

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[Unreleased]</b></summary>

> 🔄 Mudanças em desenvolvimento
>
> Melhorias contínuas de qualidade de código, implementação de TDD, testes automatizados e novas funcionalidades.

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
>
> > 1. **Ciclo 1.1: Setup Projeto** (2024-12-30)
> >    - Projeto Unreal Engine 5.7 configurado e funcional
> >    - Estrutura de pastas criada (Source/, Content/, Config/)
> >    - Arquivo `.uproject` configurado com módulo MyProject2
> >    - Arquivo `.Build.cs` configurado com dependências básicas
> >    - Compilação validada (46.06s, 0 erros, 0 warnings)
> >    - Editor abre e funciona corretamente
> >    - Assets do Unreal Engine commitados via Git LFS
> >    - Script `create-task-branch.ps1` para criar branches conectadas com GitHub issues
> >
> > 2. **Ciclo 1.2: Sistema de Logging MVP** (2024-12-30)
> >    - `FLoggingSystem` implementado com categorias de log por módulo
> >    - Suporte para Debug, Info, Warning, Error e Fatal
> >    - `FLogContext` para rastreamento contextual (Module, Function, AssetName, LineNumber)
> >    - Feedback no editor (popups para erros, mensagens throttled para warnings)
> >    - `ULoggingSystemBlueprintLibrary` criada para expor funções ao Blueprint
> >    - Funções simplificadas (Module + Message) e completas (Module + Function + Message + AssetName)
> >    - Testado em C++ e Blueprint
> >    - Compilação validada (19.85s, 0 erros, 0 warnings)
>
> > 2. Commit [`302c25c`] - Adicionar regra de Test-Driven Development (TDD)
> >    - Criada regra `test-driven-development.mdc` com metodologia TDD completa
> >    - Definido ciclo Red-Green-Refactor obrigatório para código crítico
> >    - Test-first obrigatório para Helpers/Utils, Motores, Validators e lógica de negócio
> >    - Exceções pragmáticas para casos simples (getters, wrappers, etc.)
> >    - Checklist TDD obrigatório integrado ao clean-code-mandatory
> >    - Integração com testing.mdc (HOW vs WHEN)
> >    - Referências ao TDD.md e documentação do projeto
> >    - Exemplos práticos de implementação TDD
> >    - Fluxo de trabalho completo documentado
>
> > 2. Commit [`7824315`] - Adicionar DJ_FeatsGerais.json e padronizar class features
> >    - Adicionado arquivo JSON com feats gerais D&D 5e
> >    - Padronização de class features
>
> > 3. Commit [`62c32e4`] - Adicionar guia completo de testes com referências oficiais Epic Games
> >    - Guia abrangente de testes automatizados
> >    - Referências oficiais da Epic Games
> >    - Documentação de Automation Spec e Low-Level Tests
>
> > 4. Commit [`e2fe4dd`] - Implementar sistema de logging com throttle
> >    - Adicionado `LogWarningWithThrottledPopup()` - Warning com popup throttled
> >    - Adicionado `LogErrorWithThrottledPopup()` - Error com popup throttled
> >    - Throttle limita frequência de popups no editor (padrão: 0.5s)
> >    - Log (UE_LOG) sempre imediato, apenas popup visual é throttled
> >    - Previne poluição do editor com múltiplos popups em loops de validação
> >    - Aplicado em validações de ability scores e multiclass requirements
>
> > 5. Commit [`8c090b5`] - Implementar GetOptions filtrado por feature
> >    - Adicionado `GetAvailableChoiceNamesForFeature()` - Filtra escolhas por FC_ID
> >    - Dropdown de Available Choices agora mostra apenas escolhas da feature específica
> >    - Fighting Style mostra apenas estilos de luta, não todas as escolhas
> >    - Meta tag atualizado: `GetOptionsFunctionParams = "FC_ID"`
> >    - Função original `GetAvailableChoiceNames()` mantida intacta
>
> > 6. Enhancement de ProficiencyDataTable
> >    - Adicionado campo `ProficiencyData` (TMap<FName, FString>) em `FProficiencyDataRow` para suportar regras complexas de proficiências
> >    - Criado `ProficiencyHelpers` namespace com funções helper para ler ProficiencyData
> >    - Adicionados testes para `ProficiencyDataTable` (4 testes) e `ProficiencyHelpers` (12 testes)
> >    - Corrigido JSON `DJ_Proficiencie.json`: `type` → `Type`, `description` → `Description` (case-sensitive)
> >    - Estrutura backward compatible (proficiências sem ProficiencyData continuam funcionando)
> >    - Preparação para migração futura para GAS (Gameplay Ability System)
>
> > 7. Reorganização completa da documentação e correção de links
> >    - Corrigidos todos os links duplicados em arquivos de motores e revisões
> >    - Corrigidas referências `docs/02 - TDD/` → `02-TDD/` em arquivos de pseudocódigo
> >    - Sidebar reorganizado com estrutura hierárquica completa usando colapsos
> >    - Sidebar agora corresponde exatamente à estrutura de pastas (GDD, TDD, Planning)
> >    - Removidos scripts temporários PowerShell da pasta de ciclos
> >    - Removidos relatórios consolidados obsoletos
> >    - Criado INDEX.md centralizado na raiz da documentação
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
>
> > 1. Enhancement de ProficiencyDataTable
> >    - Corrigido JSON `DJ_Proficiencie.json`: `type` → `Type`, `description` → `Description` (case-sensitive para compatibilidade com Unreal Engine)
>
> > 2. Commit [`be8dbcd`] - Tornar todas as 6 tabelas obrigatórias e remover popup
> >    - Todas as 6 Data Tables agora são obrigatórias para visibilidade da ficha
> >    - Removidos popups de alerta para tabelas faltantes
> >    - Sistema usa apenas efeito visual de esconder propriedades
> >    - Popups mantidos apenas para erros críticos (ex: classe sem requisitos)
>
> > 2. Commit [`013bc58`] - Remover funções obsoletas e refatorar handlers
> >    - Remoção de funções obsoletas e depreciadas
> >    - Refatoração completa de handlers seguindo Clean Code
> >    - Melhor separação de responsabilidades
>
> > 3. Correção de links e organização da documentação
> >    - Corrigidos links duplicados em `motores.md`, `multiclass-motor.md`, `point-buy-motor.md`, `race-bonus-motor.md`
> >    - Corrigidos links duplicados em `REVIEW_SUMMARY.md`
> >    - Corrigidas referências `docs/02 - TDD/` → `02-TDD/` em `08-pseudocodigo.md`
> >    - Sidebar reorganizado com colapsos hierárquicos correspondendo à estrutura de pastas
> >    - Removidos arquivos obsoletos e scripts temporários
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚡ Performance</summary>
>
> > Melhorias de Performance
>
> > 1. Commit [`f331765`] - Otimizar FindClassRow e melhorar logs de proficiências
> >    - Otimização de busca em Data Tables
> >    - Melhorias nos logs de proficiências
> >    - Performance aprimorada em operações críticas
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🧪 Test</summary>
>
> > Testes Automatizados
>
> > 1. Commit [`c87468c`] - Adicionar testes para Variant Human e refatorar testes existentes
> >    - Adicionados testes completos para validação de `CustomAbilityScoreChoices` (Variant Human)
> >    - Testes cobrem: limite máximo (2 itens), duplicatas, elementos inválidos, casos combinados
> >    - Refatorados testes para remover lógica interna e focar em comportamento público
> >    - Separados testes com múltiplas responsabilidades em testes individuais (SRP)
> >    - Garantido que testes falham quando código está errado (sem lógica interna)
> >    - Aplicados princípios de Clean Code e TDD rigorosamente
> >    - Corrigido `ApplyClearArray` para `CustomAbilityScoreChoices` (truncar ou limpar corretamente)
>
> > 2. Commit [`16f6461`] - Implementar e corrigir testes unitários
> >    - Implementação de testes unitários para Utils
> >    - Correções em testes existentes
> >    - Melhoria na cobertura de testes
> >    - Total de 166 testes implementados (atualizado de 138)
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Rules</summary>
>
> > Regras do Projeto
>
> > 1. Commit [`9a45bfd`] - Adicionar regra crítica de lógica interna em testes
> >    - Adicionada seção crítica em `test-driven-development.mdc`
> >    - **Regra de Ouro:** "Se você pode remover a função sendo testada e o teste ainda passa, o teste está errado"
> >    - Testes nunca podem ter lógica interna (valor esperado deve ser hardcoded)
> >    - Mocks apenas simulam dados, não implementam lógica
> >    - Teste deve falhar se código estiver errado
> >    - Exemplos práticos de uso correto e incorreto
> >    - Checklist obrigatório atualizado com 5 itens críticos
> >    - Integração com Clean Code e TDD
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Docs</summary>
>
> > Documentação
>
> > 1. Commit [`57e4149`] - Adicionar guia TDD completo e atualizar documentação de testes
> >    - Adicionado guia completo de TDD (`tdd-complete-guide.md`) consolidando todo conhecimento
> >    - Adicionada regra crítica: testes nunca podem ter lógica interna
> >    - Adicionado guia algorítmico de criação de ficha D&D (`algorithmic/character-creation.md`)
> >    - Alinhada ordem de criação com D&D Beyond (ordem oficial vs técnica)
> >    - Adicionadas referências cruzadas em toda documentação
> >    - Atualizados README, CHANGELOG e CONTRIBUTING com links corretos
> >    - Documentação de testes atualizada com regra crítica de lógica interna
> >    - Exemplos práticos de uso correto e incorreto de mocks em testes
>
> > 2. Commit [`c36ee16`] - Atualizar toda documentação com números corretos de testes
> >    - Corrigido total de testes: 56 → 138 testes implementados
> >    - Adicionados FormattingHelpers (10 testes) e ChoiceHelpers (7 testes)
> >    - Atualizados números corretos por módulo:
> >      - CalculationHelpers: 28 testes
> >      - ValidationHelpers: 35 testes
> >      - CharacterSheetHelpers: 36 testes
> >      - DataTableHelpers: 13 testes
> >      - FormattingHelpers: 10 testes
> >      - ChoiceHelpers: 7 testes
> >      - FeatDataTable: 6 testes
> >      - ComponentHelpers: 3 testes
> >    - Atualizado ARCHITECTURE.md com seção completa de testes
> >    - Atualizado README.md com estrutura completa de testes
> >    - Atualizado docs/planning/roadmap.md com progresso ~80%
> >    - Atualizado docs/technical/api.md com status de testes de todos os helpers
> >    - Atualizado docs/technical/guides/testing*.md com números corretos
> >    - Adicionado FFeatDataRow na documentação da API
> >    - Atualizado docs/index.md com histórico correto
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">♻️ Refactor</summary>
>
> > Refatorações
>
> > 1. Commit [`9539f94`] - Remover chamada obsoleta LogPropertyChange
> >    - Removida chamada a LogPropertyChange em HandleRaceChange
> >    - Parte da limpeza de código obsoleto
>
> > 2. Commit [`e09672b`] - Remover função obsoleta LogPropertyChange
> >    - Removida declaração e implementação de LogPropertyChange
> >    - Função estava vazia/comentada e não é mais necessária
> >    - Limpeza de código obsoleto seguindo Clean Code
>
> </details>

</details>

---

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.4.0] - 2024-11-25</b></summary>

> ✨ Sistema de multiclassing completo e melhorias de qualidade de código
>
> Esta versão implementa o sistema completo de multiclassing com filtro de classes baseado em requisitos de atributo, refatoração completa do motor de multiclasse, melhorias de performance e qualidade de código seguindo Clean Code e Design Patterns.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
>
> > 1. Commit [`6a52e7d`] - Implementar Core genérico e motor de PointBuy com validação automática
> >    - Criada estrutura genérica `FCharacterSheetData` para desacoplar motores (funciona em Data Asset e Widget)
> >    - Criado `CreateSheet/Core/` com Core genérico (`FCharacterSheetCore`)
> >    - Criado `CreateSheet/PointBuy/PointBuyResult.h` com struct de feedback
> >    - Motor de PointBuy valida e ajusta automaticamente se exceder 27 pontos
> >    - Motor reduz do final da fila (Charisma → Wisdom → Intelligence → Constitution → Dexterity → Strength)
> >    - Motor retorna `FPointBuyResult` com feedback para caller ajustar UI
> >    - Data Asset atualiza propriedades automaticamente quando motor ajusta
>
> > 2. Commit [`c6102f5`] - Adicionar acesso a ClassDataTable em ProcessLevelChange
> >    - `ProcessLevelChange` agora recebe `ClassDataTable` como parâmetro
> >    - Permite busca de informações de classe diretamente no motor
> >    - Melhora desacoplamento e testabilidade do motor
>
> > 3. Commit [`583e148`] - Implementar filtro de classes com requisitos de atributo
> >    - Implementado `GetAvailableClasses()` que filtra classes baseado em requisitos de atributo
> >    - Suporte para requisitos complexos (ex: "STR/13|DEX/13" - STR ou DEX >= 13)
> >    - Validação automática de requisitos de multiclassing D&D 5e
> >    - Helper `GetAvailableClassWithTagRequirements()` para parsing de requisitos
>
> > 4. Commit [`09162ce`] - Reiniciar motor multiclasse
> >    - Criado novo `FMulticlassMotor` simplificado e focado
> >    - Removido `MulticlassingMotor` antigo com dependências complexas
> >    - Removido `MulticlassingResult` e `MulticlassingValidator` (lógica movida para helpers)
> >    - Motor agora é genérico e desacoplado
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
>
> > 1. Commit [`6a52e7d`] - Refatoração arquitetural completa
> >    - Movido Core de `Characters/Data/CoreSheet/` para `CreateSheet/Core/` (genérico)
> >    - Refatorado motores para receber `FCharacterSheetData` (dados puros, não objetos concretos)
> >    - `PointBuyMotor` e `RaceBonusMotor` agora são genéricos (funcionam em Data Asset e Widget)
> >    - Core retorna resultado do PointBuy via parâmetro opcional
> >    - Data Asset cria `FCharacterSheetData` e chama Core genérico
> >    - Removido `CoreSheet` antigo específico do Data Asset
> >    - Removidas funções duplicadas `CalculateRacialBonuses` e `IncrementFinalScoresWithRacialBonuses` de `CalculationHelpers`
> >    - Funções movidas para `CreateSheet/RaceBonus/RaceBonusHelpers`
>
> > 2. Commit [`22c7b4e`] - Implementar motores desacoplados para racial bonuses e point buy
> >    - Criado `ResetFinalScoresToBase()` helper puro
> >    - Refatorado `ApplyRacialBonusesToFinalScores()` → `IncrementFinalScoresWithRacialBonuses()` (apenas incrementa)
> >    - Refatorado `ApplyPointBuyToFinalScores()` → `IncrementFinalScoresWithPointBuy()` (apenas incrementa, desacoplado)
> >    - Criado `RecalculateFinalScores()` orquestrador centralizado
> >    - Refatorado `UpdateRacialBonuses()` e `UpdatePointBuyAllocation()` para usar orquestrador
> >    - Removido `CalculatePointBuyAllocation()` obsoleta
> >    - Corrigida ordem de includes (.generated.h deve ser último)
> >    - Adicionados getters/setters públicos para propriedades privadas
> >    - Substituído `GET_MEMBER_NAME_CHECKED` por `FName(TEXT(...))` para evitar acesso a privados
> >    - Motores totalmente desacoplados, sem cache, seguindo Clean Code e Design Patterns
>
> > 3. Commit [`ada1b15`] - Limpar handlers e melhorar detecção de propriedades aninhadas
> >    - Refatoração completa de `PostEditChangeProperty` para melhor detecção de propriedades aninhadas
> >    - Melhorada lógica de lookup de handlers usando `PropertyHandlers` map
> >    - Handlers agora suportam propriedades aninhadas (ex: `MulticlassEntries[0].ClassName`)
> >    - Código mais limpo e manutenível
>
> > 4. Commit [`9680efd`] - Melhorar qualidade de código com Clean Code e Design Patterns
> >    - Extraídas funções helper reutilizáveis para `CharacterSheetDataAssetHelpers`
> >    - Aplicados princípios DRY (Don't Repeat Yourself)
> >    - Funções menores e mais focadas (< 50 linhas)
> >    - Melhorada organização de código
>
> > 5. Commit [`0215c04`] - Aplicar princípios Clean Code e melhorar qualidade
> >    - Refatoração de `GetOptions` para reduzir duplicação
> >    - Extraídas funções helper comuns
> >    - Melhorada documentação de arquitetura
> >    - Atualizado workspace com configurações otimizadas
>
> > 6. Commit [`742f6f3`] - Remover todas as dependências de classes do Data Asset
> >    - Data Asset agora não depende diretamente de classes concretas
> >    - Melhor desacoplamento seguindo Dependency Inversion Principle
> >    - Facilita testes e manutenção
>
> > 7. Commit [`ccfc396`] - Configurar include paths e otimizar performance
> >    - Otimizados include paths no workspace
> >    - Melhorada performance de compilação
> >    - Configurações de build otimizadas
>
> > 8. Commit [`816bdab`] - Atualizar documentação completa para incluir CreateSheet/ e motores desacoplados
> >    - Adicionado `CreateSheet/` na estrutura de diretórios em README.md e ARCHITECTURE.md
> >    - Documentada arquitetura CreateSheet/ com motores desacoplados (RaceBonus, PointBuy)
> >    - Atualizados diagramas de fluxo de dados para incluir CharacterSheetCore
> >    - Adicionada seção completa de CreateSheet/ na API.md
> >    - Expandida documentação de Helpers e Utilitários com novas funções
> >    - Atualizados guias práticos (getting-started, data-tables) para mencionar motores
> >    - Adicionados padrões de CreateSheet/ no CONTRIBUTING.md
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚡ Performance</summary>
>
> > Melhorias de Performance
>
> > 1. Commit [`d54c2d4`] - Otimizar performance O(n²) para O(n) e implementar RAII pattern
> >    - Otimizados algoritmos de busca de O(n²) para O(n)
> >    - Implementado padrão RAII para gerenciamento de recursos
> >    - Melhorada eficiência de operações em Data Tables
> >    - Redução significativa de tempo de execução em operações críticas
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Docs</summary>
>
> > Documentação
>
> > 1. Commit [`6457d86`] - Atualizar documentação com novos motores CreateSheet
> >    - Documentação atualizada para refletir nova arquitetura de motores
> >    - Adicionados exemplos de uso dos novos motores
> >    - Atualizados diagramas de arquitetura
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
>
> > 1. Commit [`29c4411`] - Corrigir bug de bônus de atributo racial pós refatoração
> >    - Corrigida lógica de Variant Human: 1 item no array = +2, 2 items = +1 cada
> >    - Simplificado código usando `BonusPerItem` calculado dinamicamente
> >    - Adicionados logs de depuração para diagnóstico
> >    - Corrigido acesso a membros privados usando getters/setters públicos
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔧 Chore</summary>
>
> > Manutenção
>
> > 1. Commit [`d369ea5`] - Adicionar arquivos de crash dump do bash ao .gitignore
> >    - Adicionados arquivos de crash dump ao .gitignore
> >    - Melhorada organização do repositório
>
> </details>
>
</details>

---

> 🔄 Mudanças em desenvolvimento (legado)
>
> Refatoração arquitetural completa: Core genérico, motores desacoplados e validação automática de Point Buy.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
>
> > 1. Commit [`6a52e7d`] - Implementar Core genérico e motor de PointBuy com validação automática
> >    - Criada estrutura genérica `FCharacterSheetData` para desacoplar motores (funciona em Data Asset e Widget)
> >    - Criado `CreateSheet/Core/` com Core genérico (`FCharacterSheetCore`)
> >    - Criado `CreateSheet/PointBuy/PointBuyResult.h` com struct de feedback
> >    - Motor de PointBuy valida e ajusta automaticamente se exceder 27 pontos
> >    - Motor reduz do final da fila (Charisma → Wisdom → Intelligence → Constitution → Dexterity → Strength)
> >    - Motor retorna `FPointBuyResult` com feedback para caller ajustar UI
> >    - Data Asset atualiza propriedades automaticamente quando motor ajusta
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
>
> > 1. Commit [`6a52e7d`] - Refatoração arquitetural completa
> >    - Movido Core de `Characters/Data/CoreSheet/` para `CreateSheet/Core/` (genérico)
> >    - Refatorado motores para receber `FCharacterSheetData` (dados puros, não objetos concretos)
> >    - `PointBuyMotor` e `RaceBonusMotor` agora são genéricos (funcionam em Data Asset e Widget)
> >    - Core retorna resultado do PointBuy via parâmetro opcional
> >    - Data Asset cria `FCharacterSheetData` e chama Core genérico
> >    - Removido `CoreSheet` antigo específico do Data Asset
> >    - Removidas funções duplicadas `CalculateRacialBonuses` e `IncrementFinalScoresWithRacialBonuses` de `CalculationHelpers`
> >    - Funções movidas para `CreateSheet/RaceBonus/RaceBonusHelpers`
>
> > 2. Commit [`22c7b4e`] - Implementar motores desacoplados para racial bonuses e point buy
> >    - Criado `ResetFinalScoresToBase()` helper puro
> >    - Refatorado `ApplyRacialBonusesToFinalScores()` → `IncrementFinalScoresWithRacialBonuses()` (apenas incrementa)
> >    - Refatorado `ApplyPointBuyToFinalScores()` → `IncrementFinalScoresWithPointBuy()` (apenas incrementa, desacoplado)
> >    - Criado `RecalculateFinalScores()` orquestrador centralizado
> >    - Refatorado `UpdateRacialBonuses()` e `UpdatePointBuyAllocation()` para usar orquestrador
> >    - Removido `CalculatePointBuyAllocation()` obsoleta
> >    - Corrigida ordem de includes (.generated.h deve ser último)
> >    - Adicionados getters/setters públicos para propriedades privadas
> >    - Substituído `GET_MEMBER_NAME_CHECKED` por `FName(TEXT(...))` para evitar acesso a privados
> >    - Motores totalmente desacoplados, sem cache, seguindo Clean Code e Design Patterns
>
> > 3. Commit [`816bdab`] - Atualizar documentação completa para incluir CreateSheet/ e motores desacoplados
> >    - Adicionado `CreateSheet/` na estrutura de diretórios em README.md e ARCHITECTURE.md
> >    - Documentada arquitetura CreateSheet/ com motores desacoplados (RaceBonus, PointBuy)
> >    - Atualizados diagramas de fluxo de dados para incluir CharacterSheetCore
> >    - Adicionada seção completa de CreateSheet/ na API.md
> >    - Expandida documentação de Helpers e Utilitários com novas funções
> >    - Atualizados guias práticos (getting-started, data-tables) para mencionar motores
> >    - Adicionados padrões de CreateSheet/ no CONTRIBUTING.md
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
>
> > 1. Commit [`29c4411`] - Corrigir bug de bônus de atributo racial pós refatoração
> >    - Corrigida lógica de Variant Human: 1 item no array = +2, 2 items = +1 cada
> >    - Simplificado código usando `BonusPerItem` calculado dinamicamente
> >    - Adicionados logs de depuração para diagnóstico
> >    - Corrigido acesso a membros privados usando getters/setters públicos
>
> </details>

</details>

---

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.3.0] - 2024-12-20</b></summary>

> ✨ Sistema completo de raça e background com escolhas de idiomas
>
> Esta versão finaliza o sistema de raça e background com suporte completo para escolhas de idiomas, filtros automáticos, correções de raças faltantes e melhorias na arquitetura e documentação.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
>
> > 1. Commit [`3c8c31c`] - Implementar sistema completo de raça e background com escolhas de idiomas
> >    - Corrigido `GetAllRaceNames()` para mostrar todas as raças base (Dragonborn, Half-Elf, Half-Orc, Tiefling)
> >    - Adicionada flag `bHasSubraces` para ocultar campo de sub-raça quando raça não tem sub-raças
> >    - Implementado `UpdateSubraceFlag()` seguindo padrão de `bIsVariantHuman`
> >    - Adicionado sistema de escolhas de idiomas com filtro automático
> >    - Filtro de idiomas disponíveis exclui idiomas já conhecidos automaticamente
> >    - Ajuste automático do array `SelectedLanguages` quando `MaxLanguageChoices` diminui
> >    - Adicionada propriedade `Languages` ao `CharacterDataComponent` (replicável)
> >    - Adicionada seção de idiomas no log da ficha (`LogCharacterSheet()`)
> >    - Todos os dados do personagem agora acessíveis em qualquer sistema/componente para GAS e replicação
>
> > 2. Commit [`9a98032`] - Implementar sistema de escolhas de idiomas com filtro automático
> >    - Adicionado array `SelectedLanguages` com dropdown filtrado
> >    - Filtro exclui idiomas automáticos de raça/background
> >    - Adicionadas propriedades `MaxLanguageChoices` e `bHasLanguageChoices`
> >    - Implementado helper `GetAvailableLanguagesForChoice`
> >    - Adicionada validação e handlers para idiomas
> >    - Categoria "Language Choices" oculta quando não há escolhas disponíveis
>
> > 3. Commit [`9fa0946`] - Implementar sistema de escolhas de idiomas
> >    - Refatorado `BackgroundDataTable` para separar idiomas automáticos de escolhas
> >    - Criado struct `FLanguageChoices` para escolhas de idiomas
> >    - Implementado `CalculateLanguages()` para compilar lista final de idiomas conhecidos
>
> > 4. Commit [`f625bf6`] - Adicionar escolhas de Variant Human, race traits e melhorar log da ficha
> >    - Adicionado suporte para escolhas customizadas de Variant Human
> >    - Adicionado sistema de race traits
> >    - Melhorado sistema de logging da ficha do personagem
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
>
> > 1. Commit [`6c500f5`] - Refatoração do ValidateVariantHumanChoices
> >    - Dividida em 3 funções separadas seguindo Clean Code (Validators)
> >    - Reorganização de categorias no editor do CharacterSheetDataAsset
>
> > 2. Commit [`e14a162`] - Extração de helpers reutilizáveis para Utils/
> >    - Movidos helpers para `Utils/` seguindo Clean Code
> >    - Funções puras e testáveis isoladas
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
>
> > 1. Commit [`3c8c31c`] - Remoção de logs de DEBUG
> >    - Removidos todos os logs temporários de DEBUG de handlers, updaters e calculation helpers
> >    - Mantido `LogCharacterSheet()` intacto conforme solicitado
>
> > 2. Commit [`e2b34ec`] - Correção do cálculo de bônus para Variant Human
> >    - Corrigido cálculo de bônus raciais para Variant Human
> >    - Ajuste em CalculationHelpers para aplicar escolhas customizadas apenas uma vez
>
> > 3. Commit [`a9ef548`] - Correção de arrays hardcoded e centralização de helpers
> >    - Removidos arrays hardcoded
> >    - Centralizados helpers em Utils/
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Docs</summary>
>
> > Documentação
>
> > 1. Commit [`275db60`] - Atualização do roadmap no README
> >    - Adicionado roadmap detalhado com 10 fases do Action RPG
> >    - Incluída seção de NPCs e Monsters
>
> > 2. Commit [`6737271`] - Adição de seção Skill Helpers e documentação completa de helpers
> >    - Adicionada seção Skill Helpers na documentação da API
> >    - Documentação completa de todas as funções helper
>
> > 3. Commit [`271f1f9`] - Correção de line endings e formatação da API
> >    - Normalização de line endings (LF vs CRLF)
> >    - Correção de formatação na documentação da API
>
> > 4. Commit [`6369309`] - Adição de hash de commit para atualização do changelog
> >    - Adicionado hash de commit para rastreabilidade
>
> > 5. Commit [`5d47179`] - Adição de hash de commit para atualização do changelog
> >    - Adicionado hash de commit para rastreabilidade
>
> > 6. Commit [`7b5040e`] - Adição de hashes de commits em todas as entradas do CHANGELOG
> >    - Adicionados hashes de commits para rastreabilidade completa
>
> > 7. Commit [`cf8ec7d`] - Aplicação de padrão de organização Markdown em guias
> >    - Aplicado padrão markdown-organization.mdc em `docs/GUIDES/`
>
> > 8. Commit [`4d11ca4`] - Aplicação de padrão de organização Markdown em ARCHITECTURE.md
> >    - Aplicado padrão markdown-organization.mdc com seções colapsáveis
>
> > 9. Commit [`d4d8a80`] - Adição de regra de honestidade e perguntas para IA
> >    - Adicionada regra honesty-and-questions.mdc
>
> </details>

</details>

---

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.2.0] - 2024-12-XX</b></summary>

> ✨ Refatoração modular e validação de integridade
>
> Esta versão introduz uma refatoração completa da arquitetura do `CharacterSheetDataAsset` para uma organização modular, implementa validação de integridade de dados e adiciona suporte completo para Variant Human.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Novas Funcionalidades
>
> > 1. Commit [`c90d893`] - Sistema de validação de integridade de dados
> >    - Implementado `ValidateDataIntegrity()` em `CharacterDataComponent`
> >    - Sistema de logging completo da ficha do personagem (`LogCharacterSheet()`)
>
> > 2. Commit [`8460879`] - Suporte completo para Variant Human
> >    - Atributos customizados, feat e skill
> >    - Visibilidade condicional de categorias baseada em seleção de Data Tables
>
> > 3. Commit [`1cd52b3`] - Organização modular do CharacterSheetDataAsset
> >    - `Handlers/` - Processamento de mudanças de propriedades
>
> > 4. Commit [`8899eed`] - Organização modular do CharacterSheetDataAsset
> >    - `Validators/` - Validação de dados
> >    - `Updaters/` - Atualização de campos calculados
>
> > 5. Commit [`e899bf8`] - Organização modular do CharacterSheetDataAsset
> >    - `Helpers/` - Funções auxiliares reutilizáveis
>
> > 6. Commit [`c20b354`] - Organização modular do CharacterSheetDataAsset
> >    - `GetOptions/` - Lógica para dropdowns no editor
>
> > 7. Commit [`503e553`] - Padrão Map/Table-Driven com ponteiros de função estáticos
> >    - Implementado padrão Map/Table-Driven para handlers
>
> > 8. Commit [`cf8ec7d`] - Documentação completa
> >    - `docs/GUIDES/getting-started.md` - Guia prático passo a passo
> >    - `docs/GUIDES/data-tables.md` - Documentação dos Data Tables
> >    - `docs/GUIDES/troubleshooting.md` - Problemas comuns e soluções
>
> > 9. Commit [`886ca0f`] - CharacterSheetHelpers para operações com Data Tables D&D 5e
>
> > 10. Commit [`47198fe`] - FeatDataTable para feats gerais D&D 5e
>
> > 11. Commit [`80d152e`] - Expansão de ClassDataTable
> >     - Adicionado `FeatureType` e `SubclassNames`
>
> > 12. Commit [`b526ff9`, `30a5b7a`] - Funções GetOptions para dropdowns no editor
> >     - Dropdowns para raças, classes, backgrounds, feats, skills
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Changed</summary>
>
> > Mudanças em Funcionalidades Existentes
>
> > 1. Commit [`503e553`] - Refatoração completa do PostEditChangeProperty
> >    - Implementado padrão Map/Table-Driven com lookup table
>
> > 2. Commit [`b00fad8`] - Substituição de std::function por ponteiros de função estáticos
> >    - Mais seguro e eficiente
>
> > 3. Commit [`d3d87b1`] - Otimização de handlers
> >    - Handlers agora chamam apenas funções necessárias (não mais `ValidateAndUpdate` completo)
>
> > 4. Commit [`c20b354`] - Movida lógica de GetOptions para módulo separado
> >    - Criado `FCharacterSheetDataAssetGetOptions`
>
> > 5. Commit [`1cd52b3`] - Movidas funções wrapper de handlers para módulo Handlers
>
> > 6. Commit [`e899bf8`] - Simplificado construtor de CharacterSheetDataAsset
> >    - Removidas inicializações redundantes de `PointsRemaining` e `TotalLevel`
> >    - Extraída inicialização de `AbilityScores` para helper
>
> > 7. Commit [`8899eed`] - Melhorada organização de código
> >    - Separação de responsabilidades
> >    - `CharacterSheetDataAssetTypes.h` criado para evitar dependências circulares
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🐛 Fixed</summary>
>
> > Correções de Bugs
>
> > 1. Commit [`b00fad8`] - Correção de crash do editor ao selecionar raça
> >    - Resolvido com implementação de `PostLoad()` para inicializar `PropertyHandlers`
> >    - Substituído `std::function` por ponteiros de função estáticos (resolve problemas de lifetime)
>
> > 2. Commit [`8899eed`] - Correção de recursão infinita em PostEditChangeProperty
> >    - Resolvido com flag `bIsValidatingProperties` para evitar re-disparo de handlers
> >    - Handlers agora gerenciam a flag corretamente
>
> > 3. Commit [`30a5b7a`] - Correção de validação de sub-raças
> >    - Agora valida corretamente se sub-raça pertence à raça selecionada
> >    - Reset automático de sub-raça quando raça muda
> >    - Filtro de raças base corrigido (apenas raças base aparecem no dropdown principal)
>
> > 4. Commit [`6b8621f`] - Proteção de modificações de propriedades
> >    - Adicionado `Modify()` antes de modificar propriedades em `UpdateCalculatedFields`
>
> > 5. Commit [`ff5d537`] - Evita validação redundante ao resetar sub-raça
>
> > 6. Commit [`22c1991`] - Correção de range de validação de ability scores
> >    - Correção de range de validação de ability scores em criação de personagem
>
> > 7. Commit [`a3ce3e7`] - Correção de tabela de custos Point Buy
> >    - Correção de tabela de custos Point Buy para corresponder às regras oficiais D&D 5e
>
> > 8. Commit [`b81bab2`] - Remoção de replicação desnecessária
> >    - Removida replicação de `TMap` de `CharacterDataComponent` (não suportado nativamente)
>
> </details>

</details>

---

<details>

<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>[0.1.0] - 2024-12-XX</b></summary>

> 🎯 Sistema básico de fichas de personagem
>
> Versão inicial do sistema de fichas de personagem D&D 5e com funcionalidades básicas.
>
> > **Nota:** Esta versão representa os commits iniciais do projeto que estabeleceram a arquitetura base e funcionalidades fundamentais.
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">➕ Added</summary>
>
> > Funcionalidades Iniciais
>
> > 1. Sistema básico de fichas de personagem D&D 5e
> >    - `UCharacterSheetDataAsset` - Data Asset para configuração no editor
> >    - `UCharacterDataComponent` - Componente de dados replicáveis em runtime
> >    - `UCharacterSheetComponent` - Bridge component para inicialização
>
> > 2. Suporte para Point Buy system
> >    - 27 pontos, scores 8-15
>
> > 3. Suporte para multi-classing
> >    - Múltiplas classes, nível total máximo 20
>
> > 4. Data Tables para raças, classes, backgrounds e feats
>
> > 5. Sistema de proficiências
> >    - Proficiências de raça + classe + background
>
> > 6. Bônus raciais automáticos nos ability scores
>
> > 7. Validação automática no editor
> >    - `PostEditChangeProperty`
>
> > 8. Replicação completa para multiplayer
> >    - `DOREPLIFETIME`
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏗️ Architecture</summary>
>
> > Arquitetura Inicial
>
> > - Arquitetura em 4 camadas:
> >   - **Camada 1:** Data Assets (Editor/Configuração)
> >   - **Camada 2:** Bridge Components (Aplicação de Regras)
> >   - **Camada 3:** Runtime Data Components (Dados Replicáveis)
> >   - **Camada 4:** Feature Components (Lógica Específica)
> > - Preparação para migração futura para GAS
> > - Data-Driven design (todas as regras vêm de Data Tables)
> > - Editor-Friendly (configuração completa no editor)
>
> </details>

</details>

---

<details>
<summary>📚 Tipos de Mudanças</summary>

- **Added** - Novas funcionalidades
- **Changed** - Mudanças em funcionalidades existentes
- **Deprecated** - Funcionalidades que serão removidas
- **Removed** - Funcionalidades removidas
- **Fixed** - Correções de bugs
- **Security** - Correções de segurança

</details>

---

## 🔗 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Documentação Relacionada</b></summary>

> - **[README.md](README.md)** - Visão geral do projeto
> - **[ARCHITECTURE.md](ARCHITECTURE.md)** - Resumo da arquitetura
> - **[Documentação Completa](docs/index.md)** - Índice completo da documentação
> - **[Arquitetura Técnica](docs/technical/architecture.md)** - Arquitetura detalhada
> - **[API Reference](docs/technical/api.md)** - Referência completa da API
> - **[Guias Práticos](docs/technical/guides/)** - Guias passo a passo

</details>
