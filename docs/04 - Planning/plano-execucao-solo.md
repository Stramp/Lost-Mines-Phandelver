# Plano de Execução - Desenvolvimento Solo

**Data:** 2024-12-27

**Baseado em:** [Roadmap](../../04%20-%20Planning/roadmap/Roadmap.md) e [Metodologia Ágil](../../Referencias%20Tecnicas/MetodologiaAgil.md)

**Metodologia:** Personal Kanban + Micro-Milestones (2-4 horas por tarefa)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Visão Geral</b></summary>

> Este documento quebra cada item do roadmap em **micro-tarefas atômicas** (2-4 horas cada), seguindo a metodologia de desenvolvimento solo:
>
> - **Personal Kanban:** WIP limitado a 1-2 tarefas
> - **Micro-Milestones:** Tarefas completáveis em uma sessão
> - **Data-Driven First:** Sempre priorizar Data Tables/Assets
> - **TDD:** Testes antes da implementação
> - **Vertical Slice:** Prova de conceito completa primeiro
>
> **Estrutura:** Cada categoria do roadmap é quebrada em subcategorias e micro-tarefas específicas.

</details>

---

## 🚀 FASE 1: COMEÇO (Fundação e Vertical Slice)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>1. Fundação Técnica e Infraestrutura</b></summary>

> ### 1.1. Configuração do Projeto
>
> - [ ] Criar estrutura de pastas base (Source/, Content/, Config/)
> - [ ] Configurar .uproject e módulos
> - [ ] Configurar .Build.cs com dependências mínimas
> - [ ] Gerar arquivos de projeto (RunUBT)
> - [ ] Verificar compilação inicial
>
> ### 1.2. Sistema de Logging ✅
>
> - [x] Criar LoggingSystem.h com categorias
> - [x] Implementar LoggingSystem.cpp
> - [x] Definir categorias de log por módulo
> - [x] Testar logs no editor e runtime
>
> ### 1.3. Arquitetura de Componentes ✅
>
> - [x] Definir 4 camadas (Data Asset, Bridge, Runtime, Features)
> - [x] Criar estrutura de pastas por camada
> - [x] Documentar responsabilidades de cada camada
>
> ### 1.4. Sistema de Data Tables Base ✅
>
> - [x] Criar DataTableCache.h/cpp
> - [x] Implementar carregamento e cache
> - [x] Criar DataTableHelpers.h/cpp
> - [x] Implementar validação básica
>
> ### 1.5. Sistema de Data Assets Base ✅
>
> - [x] Criar CharacterSheetDataAsset.h/cpp
> - [x] Implementar estrutura base
> - [x] Implementar validação no editor
>
> ### 1.6. Sistema de Salvamento Básico
>
> - [ ] Criar SaveGame class base
> - [ ] Definir estrutura de dados a salvar
> - [ ] Implementar serialização básica
> - [ ] Implementar SaveGameToSlot()
> - [ ] Implementar LoadGameFromSlot()
> - [ ] Testar save/load básico
>
> ### 1.7. Sistema de Input Básico
>
> - [ ] Criar InputAction mappings (WASD, Mouse)
> - [ ] Configurar InputComponent no Character
> - [ ] Implementar movimento básico (WASD)
> - [ ] Implementar rotação (Mouse)
> - [ ] Testar input no editor
>
> ### 1.8. Câmera Top-Down
>
> - [ ] Criar CameraActor ou CameraComponent
> - [ ] Configurar projeção ortográfica
> - [ ] Implementar seguir personagem
> - [ ] Implementar limites de área
> - [ ] Testar câmera no editor
>
> ### 1.9. Sistema de Física Básico
>
> - [ ] Configurar CharacterMovementComponent
> - [ ] Ajustar velocidade e aceleração
> - [ ] Configurar colisões (Capsule)
> - [ ] Testar movimento e colisão
>
> ### 1.10. Sistema de Iluminação Básico
>
> - [ ] Adicionar DirectionalLight ao nível
> - [ ] Configurar iluminação ambiente
> - [ ] Ajustar intensidade e cor
> - [ ] Testar iluminação no editor
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>2. Data Tables Essenciais (Data-Driven First)</b></summary>

> ### 2.1. Data Table de Raças ✅
>
> - [x] Criar RaceDataTable.h (estrutura FTableRowBase)
> - [x] Definir campos (Name, AbilityBonuses, Traits, etc.)
> - [x] Criar Data Table asset no editor
> - [x] Preencher todas as raças D&D 5e
> - [x] Validar dados no editor
>
> ### 2.2. Data Table de Classes ✅
>
> - [x] Criar ClassDataTable.h (estrutura)
> - [x] Definir campos (HitDie, Proficiencies, Features, etc.)
> - [x] Criar Data Table asset
> - [x] Preencher todas as classes D&D 5e
> - [x] Validar dados
>
> ### 2.3. Data Table de Backgrounds ✅
>
> - [x] Criar BackgroundDataTable.h
> - [x] Definir campos (Skills, Equipment, etc.)
> - [x] Criar Data Table asset
> - [x] Preencher todos os backgrounds
> - [x] Validar dados
>
> ### 2.4. Data Table de Skills ✅
>
> - [x] Criar SkillDataTable.h
> - [x] Definir todas as 18 skills D&D 5e
> - [x] Criar Data Table asset
> - [x] Preencher skills
>
> ### 2.5. Data Table de Proficiências ✅
>
> - [x] Criar ProficiencyDataTable.h
> - [x] Definir tipos (Armas, Armaduras, Ferramentas)
> - [x] Criar Data Table asset
> - [x] Preencher proficiências
>
> ### 2.6. Data Table de Itens Básicos ✅
>
> - [x] Criar ItemDataTable.h
> - [x] Definir campos (Name, Type, Cost, Weight, etc.)
> - [x] Criar Data Table asset
> - [x] Preencher itens básicos (armas, armaduras, consumíveis)
>
> ### 2.7. Validação de Data Tables ✅
>
> - [x] Implementar PostEditChangeProperty em cada Data Table
> - [x] Criar validações básicas (campos obrigatórios)
> - [x] Testar validação no editor
>
> ### 2.8. Sistema de Carregamento e Cache ✅
>
> - [x] Implementar DataTableCache
> - [x] Implementar cache por tipo
> - [x] Testar carregamento
>
> ### 2.9. Testes de Carregamento ✅
>
> - [x] Criar testes de carregamento
> - [x] Testar cache
> - [x] Validar integridade
>
> ### 2.10. Documentação ✅
>
> - [x] Documentar estrutura de cada Data Table
> - [x] Criar exemplos de uso
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>3. Criação de Personagem (MVP) - TDD</b></summary>

> ### 3.1. Point Buy (TDD)
>
> - [x] Escrever testes de Point Buy (Red)
> - [x] Implementar PointBuyMotor mínimo (Green)
> - [ ] Refatorar PointBuyMotor (Refactor)
> - [ ] Escrever testes de validação (27 pontos)
> - [ ] Implementar validação
> - [ ] Escrever testes de custos por score
> - [ ] Implementar tabela de custos D&D 5e
>
> ### 3.2. Race Bonus (TDD)
>
> - [ ] Escrever testes de Race Bonus (Red)
> - [ ] Implementar RaceBonusMotor mínimo (Green)
> - [ ] Refatorar com testes garantindo
> - [ ] Testar todas as raças
>
> ### 3.3. Ability Modifiers (TDD) ✅
>
> - [x] Escrever testes de Ability Modifiers (Red)
> - [x] Implementar CalculationHelpers::CalculateAbilityModifier (Green)
> - [x] Refatorar com testes garantindo
> - [x] Testar edge cases (1-30)
>
> ### 3.4. Proficiency Bonus (TDD) ✅
>
> - [x] Escrever testes de Proficiency Bonus (Red)
> - [x] Implementar CalculationHelpers::CalculateProficiencyBonus (Green)
> - [x] Refatorar com testes garantindo
> - [x] Testar progressão por nível
>
> ### 3.5. AC Base (TDD)
>
> - [ ] Escrever testes de AC base (Red)
> - [ ] Implementar cálculo de AC (Green)
> - [ ] Refatorar com testes garantindo
> - [ ] Testar com diferentes armaduras
>
> ### 3.6. HP/MaxHP (TDD)
>
> - [ ] Escrever testes de HP/MaxHP (Red)
> - [ ] Implementar cálculo de HP (Green)
> - [ ] Refatorar com testes garantindo
> - [ ] Testar com diferentes classes e níveis
>
> ### 3.7. UI de Seleção de Raça
>
> - [ ] Criar Widget de seleção de raça
> - [ ] Carregar raças da Data Table
> - [ ] Exibir bônus raciais
> - [ ] Implementar seleção
> - [ ] Testar UI
>
> ### 3.8. UI de Seleção de Classe
>
> - [ ] Criar Widget de seleção de classe
> - [ ] Carregar classes da Data Table
> - [ ] Exibir proficiências
> - [ ] Implementar seleção
> - [ ] Testar UI
>
> ### 3.9. UI de Seleção de Background
>
> - [ ] Criar Widget de seleção de background
> - [ ] Carregar backgrounds da Data Table
> - [ ] Exibir skills
> - [ ] Implementar seleção
> - [ ] Testar UI
>
> ### 3.10. Tela de Criação Completa
>
> - [ ] Criar Widget principal de criação
> - [ ] Integrar todos os passos (1-6 D&D 5e)
> - [ ] Implementar navegação entre passos
> - [ ] Implementar validação final
> - [ ] Testar fluxo completo
>
> ### 3.11. Validação de Criação
>
> - [ ] Implementar validação de requisitos
> - [ ] Validar Point Buy (27 pontos)
> - [ ] Validar proficiências
> - [ ] Testar validações
>
> ### 3.12. Teste de Integração
>
> - [ ] Criar teste E2E de criação completa
> - [ ] Testar todos os passos integrados
> - [ ] Validar dados finais
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>4. Vertical Slice - Cragmaw Hideout</b></summary>

> ### 4.1. Mapa Básico
>
> - [ ] Criar nível básico (1 sala)
> - [ ] Adicionar geometria básica (paredes, chão)
> - [ ] Configurar colisões
> - [ ] Adicionar iluminação básica
> - [ ] Testar navegação
>
> ### 4.2. Personagem Controlável
>
> - [ ] Criar Character Blueprint base
> - [ ] Configurar movimento WASD
> - [ ] Implementar rotação (Mouse)
> - [ ] Adicionar animação básica (idle, walk)
> - [ ] Testar controle
>
> ### 4.3. Sistema de Combate Básico
>
> - [ ] Criar função de ataque melee
> - [ ] Implementar cálculo de dano básico
> - [ ] Implementar sistema de HP
> - [ ] Adicionar feedback visual básico (HP bar)
> - [ ] Testar combate básico
>
> ### 4.4. Inimigo Goblin
>
> - [ ] Criar Goblin Blueprint
> - [ ] Configurar stats D&D (HP, AC, Attack)
> - [ ] Implementar IA básica FSM (Ocioso → Alerta → Combate)
> - [ ] Implementar pathfinding básico
> - [ ] Testar comportamento
>
> ### 4.5. Sistema de Interação Básico
>
> - [ ] Criar interface IInteractable
> - [ ] Implementar interação com porta (abre/fecha)
> - [ ] Implementar interação com baú (abre/coleta item)
> - [ ] Adicionar feedback visual (highlight)
> - [ ] Testar interações
>
> ### 4.6. Sistema de Diálogo Básico
>
> - [ ] Criar estrutura de diálogo (árvore simples)
> - [ ] Criar Widget de diálogo básico
> - [ ] Implementar 1 NPC com 1 diálogo
> - [ ] Adicionar botões de escolha
> - [ ] Testar diálogo
>
> ### 4.7. Sistema de Inventário Básico
>
> - [ ] Criar estrutura de inventário (TArray de itens)
> - [ ] Implementar coletar item
> - [ ] Criar Widget de inventário básico
> - [ ] Implementar visualizar itens
> - [ ] Implementar equipar básico
> - [ ] Testar inventário
>
> ### 4.8. Sistema de Save/Load Funcional
>
> - [ ] Estender SaveGame com dados do jogo
> - [ ] Implementar salvar posição do personagem
> - [ ] Implementar salvar inventário
> - [ ] Implementar salvar progresso de quests
> - [ ] Implementar carregar todos os dados
> - [ ] Testar save/load completo
>
> ### 4.9. HUD Básico
>
> - [ ] Criar Widget de HUD
> - [ ] Implementar HP bar
> - [ ] Implementar minimapa básico (placeholder)
> - [ ] Implementar hotbar básica (slots 1-0)
> - [ ] Testar HUD
>
> ### 4.10. Teste Completo da Vertical Slice
>
> - [ ] Criar cena completa (mapa + personagem + inimigo + NPC)
> - [ ] Testar fluxo completo: entrar → combate → diálogo → item → save
> - [ ] Validar todos os sistemas integrados
> - [ ] Documentar problemas encontrados
> - [ ] Corrigir bugs críticos
>
>___

</details>

---

## 🏗️ FASE 2: MEIO (Sistemas Completos)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>5. Data Tables Completas (Expansão)</b></summary>

> ### 5.1. Data Table de Magias
>
> - [ ] Criar SpellDataTable.h (estrutura completa)
> - [ ] Definir campos (Level, Components, CastingTime, Range, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher todas as magias necessárias da campanha
> - [ ] Validar dados
>
> ### 5.2. Data Table de Inimigos/Bestiário
>
> - [ ] Criar EnemyDataTable.h (estrutura)
> - [ ] Definir campos (CR, HP, AC, Attacks, Abilities, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher todas as criaturas da campanha
> - [ ] Validar dados
>
> ### 5.3. Data Table de Quests
>
> - [ ] Criar QuestDataTable.h (estrutura)
> - [ ] Definir campos (Type, Objectives, Rewards, Prerequisites, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher todas as quests da campanha
> - [ ] Validar dados
>
> ### 5.4. Data Table de NPCs
>
> - [ ] Criar NPCDataTable.h (estrutura)
> - [ ] Definir campos (Name, DialogueTree, Role, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher todos os NPCs principais
> - [ ] Validar dados
>
> ### 5.5. Data Table de Itens Mágicos
>
> - [ ] Criar MagicItemDataTable.h (estrutura)
> - [ ] Definir campos (Rarity, Properties, Lore, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher itens especiais da campanha
> - [ ] Validar dados
>
> ### 5.6. Data Table de Loot Tables
>
> - [ ] Criar LootTableDataTable.h (estrutura)
> - [ ] Definir campos (Probabilities, Rarities, ItemLists, etc.)
> - [ ] Criar Data Table asset
> - [ ] Preencher loot tables da campanha
> - [ ] Validar dados
>
> ### 5.7. Validação Completa
>
> - [ ] Criar validações específicas por Data Table
> - [ ] Implementar validações cruzadas (referências)
> - [ ] Testar todas as validações
>
> ### 5.8. Ferramentas de Editor
>
> - [ ] Criar helper para gerar itens base
> - [ ] Criar helper para validar referências
> - [ ] Criar helper para exportar/importar dados
> - [ ] Documentar ferramentas
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>6. Sistema de Combate Completo</b></summary>

> ### 6.1. Sistema de Ataques
>
> - [ ] Criar estrutura de ataques (melee, ranged)
> - [ ] Implementar cooldowns baseados em rounds
> - [ ] Implementar cálculo de to-hit (d20 + modifiers)
> - [ ] Implementar cálculo de dano
> - [ ] Testar ataques
>
> ### 6.2. Sistema de Magias
>
> - [ ] Implementar spell slots por nível
> - [ ] Implementar cantrips (sem limite)
> - [ ] Implementar cooldowns de magias
> - [ ] Implementar verificação de spell slots
> - [ ] Testar sistema de magias
>
> ### 6.3. Sistema de Condições
>
> - [ ] Criar estrutura de condições (enum/struct)
> - [ ] Implementar aplicação de condições
> - [ ] Implementar duração e remoção
> - [ ] Implementar efeitos por condição
> - [ ] Testar condições
>
> ### 6.4. Sistema de Tipos de Dano
>
> - [ ] Criar enum de tipos de dano
> - [ ] Implementar resistências
> - [ ] Implementar vulnerabilidades
> - [ ] Implementar imunidades
> - [ ] Testar tipos de dano
>
> ### 6.5. Sistema de Críticos
>
> - [ ] Implementar detecção de d20 natural 20
> - [ ] Implementar detecção de d20 natural 1
> - [ ] Implementar cálculo de dano crítico (dobro de dados)
> - [ ] Implementar falha crítica
> - [ ] Testar críticos
>
> ### 6.6. Sistema de Vantagem/Desvantagem
>
> - [ ] Implementar rolagem 2d20
> - [ ] Implementar escolha do melhor (vantagem)
> - [ ] Implementar escolha do pior (desvantagem)
> - [ ] Implementar cancelamento (vantagem + desvantagem)
> - [ ] Testar vantagem/desvantagem
>
> ### 6.7. Sistema de Death Saving Throws
>
> - [ ] Implementar contador de sucessos/falhas
> - [ ] Implementar rolagem d20 (10+ = sucesso)
> - [ ] Implementar 3 sucessos = estável
> - [ ] Implementar 3 falhas = morte
> - [ ] Testar death saving throws
>
> ### 6.8. Sistema de Ressurreição
>
> - [ ] Implementar Revivify (nível 3)
> - [ ] Implementar Raise Dead (nível 5)
> - [ ] Implementar limitações (tempo, corpo)
> - [ ] Testar ressurreição
>
> ### 6.9. Feedback Visual Completo
>
> - [ ] Implementar dano flutuante (números)
> - [ ] Implementar partículas por tipo de dano
> - [ ] Implementar cores por tipo (fogo=vermelho, etc.)
> - [ ] Implementar animações de impacto
> - [ ] Testar feedback visual
>
> ### 6.10. Feedback Sonoro Completo
>
> - [ ] Criar SFX de ataques melee
> - [ ] Criar SFX de ataques ranged
> - [ ] Criar SFX de hits
> - [ ] Criar SFX de críticos
> - [ ] Criar SFX por tipo de dano
> - [ ] Testar feedback sonoro
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>7. Sistema de Personagem Completo</b></summary>

> ### 7.1. Sistema de Level Up
>
> - [ ] Implementar tabela XP D&D 5e (níveis 1-5)
> - [ ] Implementar verificação de XP
> - [ ] Implementar trigger de level up
> - [ ] Implementar aumento de HP por nível
> - [ ] Testar level up
>
> ### 7.2. Sistema de ASI
>
> - [ ] Implementar ASI nível 4 (+2 em 1 ability ou +1 em 2)
> - [ ] Criar UI de escolha de ASI
> - [ ] Implementar validação de escolha
> - [ ] Testar ASI
>
> ### 7.3. Sistema de Features de Classe
>
> - [ ] Implementar carregamento de features da Data Table
> - [ ] Implementar aplicação de features por nível
> - [ ] Implementar features específicas (Second Wind, Action Surge, etc.)
> - [ ] Testar features
>
> ### 7.4. Sistema de Multiclassing
>
> - [ ] Implementar validação de requisitos (13+ em abilities)
> - [ ] Implementar aplicação de proficiências parciais
> - [ ] Implementar cálculo de spell slots multiclass
> - [ ] Testar multiclassing
>
> ### 7.5. Sistema de Feats
>
> - [ ] Criar FeatDataTable.h (estrutura)
> - [ ] Preencher feats básicos
> - [ ] Implementar aplicação de feats
> - [ ] Implementar Variant Human (feat nível 1)
> - [ ] Testar feats
>
> ### 7.6. Sistema de Skills Completo
>
> - [ ] Implementar todas as 18 skills
> - [ ] Implementar cálculo de modificadores
> - [ ] Implementar proficiência em skills
> - [ ] Testar skills
>
> ### 7.7. Sistema de Saving Throws Completo
>
> - [ ] Implementar 6 saving throws
> - [ ] Implementar proficiência por classe
> - [ ] Implementar cálculo de modificadores
> - [ ] Testar saving throws
>
> ### 7.8. Ficha de Personagem Completa (UI)
>
> - [ ] Criar Widget de ficha completa
> - [ ] Exibir todos os atributos
> - [ ] Exibir skills e saves
> - [ ] Exibir proficiências
> - [ ] Testar UI
>
> ### 7.9. Sistema de Proficiências Completo
>
> - [ ] Implementar proficiências de armas
> - [ ] Implementar proficiências de armaduras
> - [ ] Implementar proficiências de ferramentas
> - [ ] Implementar proficiências de salvamentos
> - [ ] Testar proficiências
>
> ### 7.10. Sistema de Variant Human
>
> - [ ] Implementar escolha de feat
> - [ ] Implementar escolha de skill
> - [ ] Implementar escolha de ability (+1 em 2)
> - [ ] Testar Variant Human
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>8. Sistema de Equipamentos e Inventário</b></summary>

> ### 8.1. Sistema de Equipamento Completo
>
> - [ ] Criar estrutura de slots (Head, Body, Weapon, Shield, etc.)
> - [ ] Implementar equipar item
> - [ ] Implementar desequipar item
> - [ ] Implementar validação de slots
> - [ ] Testar equipamento
>
> ### 8.2. Sistema de Cálculo de AC Completo
>
> - [ ] Implementar AC base (10 + DEX)
> - [ ] Implementar AC com armadura
> - [ ] Implementar AC com escudo (+2)
> - [ ] Implementar todas as regras D&D 5e
> - [ ] Testar cálculo de AC
>
> ### 8.3. Sistema de Propriedades de Armas
>
> - [ ] Implementar propriedades (versátil, leve, pesada, etc.)
> - [ ] Implementar dano versátil (1d8/1d10)
> - [ ] Implementar duas armas (leve)
> - [ ] Testar propriedades
>
> ### 8.4. Sistema de Capacidade de Carga
>
> - [ ] Implementar cálculo (STR × 15 lbs)
> - [ ] Implementar peso de itens
> - [ ] Implementar verificação de sobrecarga
> - [ ] Testar capacidade de carga
>
> ### 8.5. Sistema de Moedas
>
> - [ ] Criar estrutura de moedas (CP, SP, GP)
> - [ ] Implementar conversão automática
> - [ ] Implementar adicionar/remover moedas
> - [ ] Testar sistema de moedas
>
> ### 8.6. Sistema de Itens Consumíveis
>
> - [ ] Implementar uso de poções
> - [ ] Implementar uso de scrolls
> - [ ] Implementar efeitos temporários
> - [ ] Testar consumíveis
>
> ### 8.7. UI de Inventário Completa
>
> - [ ] Criar Widget de inventário
> - [ ] Implementar organização por categorias
> - [ ] Implementar busca/filtro
> - [ ] Implementar drag & drop
> - [ ] Testar UI
>
> ### 8.8. UI de Equipamento Completa
>
> - [ ] Criar Widget de equipamento
> - [ ] Implementar slots visuais
> - [ ] Implementar drag & drop
> - [ ] Implementar preview de stats
> - [ ] Testar UI
>
> ### 8.9. Sistema de Itens Mágicos Básicos
>
> - [ ] Implementar propriedades especiais
> - [ ] Implementar ativação de itens mágicos
> - [ ] Testar itens mágicos
>
> ### 8.10. Sistema de Venda/Compra
>
> - [ ] Criar sistema de comerciantes
> - [ ] Implementar preços base D&D 5e
> - [ ] Implementar compra de itens
> - [ ] Implementar venda de itens
> - [ ] Testar comércio
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>9. Sistema de Spellcasting Completo</b></summary>

> ### 9.1. Sistema de Spell Slots por Nível
>
> - [ ] Implementar tabela D&D 5e por classe
> - [ ] Implementar spell slots por nível de classe
> - [ ] Implementar recuperação de slots
> - [ ] Testar spell slots
>
> ### 9.2. Sistema de Preparação de Magias
>
> - [ ] Implementar classes preparadoras (Clérigo, Druida)
> - [ ] Implementar preparação diária
> - [ ] Implementar limite de preparação
> - [ ] Testar preparação
>
> ### 9.3. Sistema de Magias Conhecidas
>
> - [ ] Implementar classes espontâneas (Sorcerer, Warlock)
> - [ ] Implementar magias conhecidas por nível
> - [ ] Implementar troca de magias conhecidas
> - [ ] Testar magias conhecidas
>
> ### 9.4. Sistema de Componentes de Magia
>
> - [ ] Implementar componentes verbais
> - [ ] Implementar componentes somáticos
> - [ ] Implementar componentes materiais
> - [ ] Implementar custos de material
> - [ ] Testar componentes
>
> ### 9.5. Sistema de Concentração
>
> - [ ] Implementar 1 magia ativa por vez
> - [ ] Implementar quebra por dano (CON save)
> - [ ] Implementar quebra por nova concentração
> - [ ] Testar concentração
>
> ### 9.6. Sistema de Spell Save DC
>
> - [ ] Implementar cálculo (8 + proficiência + modificador)
> - [ ] Implementar aplicação em magias
> - [ ] Testar spell save DC
>
> ### 9.7. Sistema de Spell Attack Bonus
>
> - [ ] Implementar cálculo (proficiência + modificador)
> - [ ] Implementar aplicação em magias de ataque
> - [ ] Testar spell attack bonus
>
> ### 9.8. UI de Spellbook Completa
>
> - [ ] Criar Widget de spellbook
> - [ ] Implementar visualização de magias
> - [ ] Implementar preparação (classes preparadoras)
> - [ ] Implementar seleção para casting
> - [ ] Implementar visualização de slots
> - [ ] Testar UI
>
> ### 9.9. Sistema de Cantrips
>
> - [ ] Implementar cantrips (sem limite de uso)
> - [ ] Implementar sem spell slots
> - [ ] Testar cantrips
>
> ### 9.10. Implementação de Magias da Campanha
>
> - [ ] Preencher Data Table com todas as magias necessárias
> - [ ] Validar magias
> - [ ] Testar magias em jogo
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>10. Sistema de Rest e Recuperação</b></summary>

> ### 10.1. Sistema de Short Rest
>
> - [ ] Implementar duração (1 hora)
> - [ ] Implementar uso de Hit Dice
> - [ ] Implementar recuperação de algumas habilidades
> - [ ] Testar Short Rest
>
> ### 10.2. Sistema de Long Rest
>
> - [ ] Implementar duração (8 horas)
> - [ ] Implementar recuperação completa de HP
> - [ ] Implementar recuperação de spell slots
> - [ ] Implementar recuperação de habilidades
> - [ ] Testar Long Rest
>
> ### 10.3. Sistema de Hit Dice
>
> - [ ] Implementar quantidade por nível
> - [ ] Implementar uso em Short Rest
> - [ ] Implementar recuperação de Hit Dice
> - [ ] Testar Hit Dice
>
> ### 10.4. Recuperação de Spell Slots
>
> - [ ] Implementar Warlock (Short Rest)
> - [ ] Implementar outras classes (Long Rest)
> - [ ] Testar recuperação
>
> ### 10.5. Recuperação de Habilidades de Classe
>
> - [ ] Implementar Second Wind (Fighter)
> - [ ] Implementar Action Surge (Fighter)
> - [ ] Implementar outras habilidades
> - [ ] Testar recuperação
>
> ### 10.6. Limitações de Rest
>
> - [ ] Implementar verificação de combate recente
> - [ ] Implementar verificação de área segura
> - [ ] Implementar outras limitações
> - [ ] Testar limitações
>
> ### 10.7. UI de Rest
>
> - [ ] Criar Widget de rest
> - [ ] Implementar escolha Short/Long
> - [ ] Implementar visualização de recursos
> - [ ] Testar UI
>
> ### 10.8. Sistema de Acampamento
>
> - [ ] Criar visual básico de acampamento
> - [ ] Implementar área segura
> - [ ] Testar acampamento
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>11. Sistema de Diálogos e Quests</b></summary>

> ### 11.1. Sistema de Diálogos Ramificados
>
> - [ ] Criar estrutura de árvore de decisões
> - [ ] Implementar nós de diálogo
> - [ ] Implementar ramificações
> - [ ] Testar diálogos ramificados
>
> ### 11.2. Sistema de Condições de Diálogo
>
> - [ ] Implementar verificação de quests completas
> - [ ] Implementar verificação de itens possuídos
> - [ ] Implementar outras condições
> - [ ] Testar condições
>
> ### 11.3. Sistema de Quests
>
> - [ ] Criar estrutura de quest (main, secondary, faction)
> - [ ] Implementar carregamento da Data Table
> - [ ] Implementar estados (ativa, completa, falhada)
> - [ ] Testar sistema de quests
>
> ### 11.4. Sistema de Rastreamento de Quests
>
> - [ ] Criar Widget de quests
> - [ ] Implementar lista de quests
> - [ ] Implementar progresso visual
> - [ ] Testar rastreamento
>
> ### 11.5. Sistema de Objetivos de Quest
>
> - [ ] Implementar múltiplos objetivos
> - [ ] Implementar atualização automática
> - [ ] Implementar validação de objetivos
> - [ ] Testar objetivos
>
> ### 11.6. Sistema de Recompensas de Quest
>
> - [ ] Implementar XP como recompensa
> - [ ] Implementar ouro como recompensa
> - [ ] Implementar itens como recompensa
> - [ ] Implementar desbloqueios
> - [ ] Testar recompensas
>
> ### 11.7. Sistema de Progressão de Quest
>
> - [ ] Implementar estados (ativa, completa, falhada)
> - [ ] Implementar transições de estado
> - [ ] Testar progressão
>
> ### 11.8. Diálogos com NPCs Principais
>
> - [ ] Preencher Data Table com diálogos
> - [ ] Implementar diálogos principais
> - [ ] Testar diálogos
>
> ### 11.9. Implementação de Quests da Campanha
>
> - [ ] Preencher Data Table com todas as quests
> - [ ] Validar quests
> - [ ] Testar quests em jogo
>
> ### 11.10. Sistema de Decisões e Ramificações
>
> - [ ] Implementar consequências de decisões
> - [ ] Implementar ramificações narrativas
> - [ ] Testar decisões
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>12. Sistema de IA e Comportamento</b></summary>

> ### 12.1. FSM Completa para Inimigos
>
> - [ ] Implementar estado Ocioso
> - [ ] Implementar estado Alerta
> - [ ] Implementar estado Investigação
> - [ ] Implementar estado Combate
> - [ ] Implementar estado Fuga
> - [ ] Implementar transições entre estados
> - [ ] Testar FSM
>
> ### 12.2. IA de Combate
>
> - [ ] Implementar lógica de ataque
> - [ ] Implementar lógica de defesa
> - [ ] Implementar uso de habilidades
> - [ ] Implementar posicionamento tático
> - [ ] Testar IA de combate
>
> ### 12.3. IA de Patrulha
>
> - [ ] Implementar waypoints
> - [ ] Implementar rotas
> - [ ] Implementar tempo de espera
> - [ ] Testar patrulha
>
> ### 12.4. IA de Detecção
>
> - [ ] Implementar percepção passiva
> - [ ] Implementar stealth
> - [ ] Implementar campo de visão
> - [ ] Testar detecção
>
> ### 12.5. IA de NPCs
>
> - [ ] Implementar rotinas de NPCs
> - [ ] Implementar diálogo automático
> - [ ] Implementar comércio
> - [ ] Implementar quest giver
> - [ ] Testar IA de NPCs
>
> ### 12.6. Sistema de Aggro e Threat
>
> - [ ] Implementar priorização de alvos
> - [ ] Implementar cálculo de threat
> - [ ] Testar aggro
>
> ### 12.7. Sistema de Fuga e Retirada
>
> - [ ] Implementar verificação de HP baixo
> - [ ] Implementar condições de fuga
> - [ ] Testar fuga
>
> ### 12.8. Implementação de Inimigos da Campanha
>
> - [ ] Preencher Data Table com todos os inimigos
> - [ ] Implementar comportamentos específicos
> - [ ] Testar inimigos
>
> ### 12.9. Comportamentos Específicos
>
> - [ ] Implementar Goblin emboscada
> - [ ] Implementar Bugbear líder
> - [ ] Implementar outros comportamentos
> - [ ] Testar comportamentos
>
> ### 12.10. Sistema de Spawn
>
> - [ ] Implementar triggers de spawn
> - [ ] Implementar áreas de spawn
> - [ ] Implementar respawn (se aplicável)
> - [ ] Testar spawn
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>13. Sistema de Economia e Loot</b></summary>

> ### 13.1. Sistema de Loot Tables Completo
>
> - [ ] Criar estrutura de loot table (Data Table)
> - [ ] Implementar probabilidades
> - [ ] Implementar seleção de loot
> - [ ] Testar loot tables
>
> ### 13.2. Sistema de Probabilidades de Drop
>
> - [ ] Implementar cálculo por raridade
> - [ ] Implementar ajuste por nível do inimigo
> - [ ] Testar probabilidades
>
> ### 13.3. Sistema de Raridade de Itens
>
> - [ ] Implementar enum de raridades
> - [ ] Implementar cores por raridade
> - [ ] Testar raridades
>
> ### 13.4. Sistema de Tesouros de Masmorras
>
> - [ ] Implementar baús com loot fixo
> - [ ] Implementar baús com loot aleatório
> - [ ] Testar tesouros
>
> ### 13.5. Sistema de Recompensas de Quests
>
> - [ ] Integrar recompensas com sistema de quests
> - [ ] Implementar XP, ouro, itens
> - [ ] Testar recompensas
>
> ### 13.6. Sistema de Compra/Venda com NPCs
>
> - [ ] Implementar comerciantes
> - [ ] Implementar preços base D&D 5e
> - [ ] Testar comércio
>
> ### 13.7. Sistema de Preços
>
> - [ ] Implementar preços base
> - [ ] Implementar ajustes por raridade
> - [ ] Testar preços
>
> ### 13.8. Sistema de Inflação/Equilíbrio
>
> - [ ] Analisar fontes de ouro
> - [ ] Analisar drenos de ouro
> - [ ] Balancear economia
> - [ ] Testar equilíbrio
>
> ### 13.9. Implementação de Itens da Campanha
>
> - [ ] Preencher Data Table completa
> - [ ] Validar itens
> - [ ] Testar itens
>
> ### 13.10. Sistema de Itens Únicos
>
> - [ ] Implementar propriedades especiais
> - [ ] Implementar lore de itens
> - [ ] Testar itens únicos
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>14. Sistema de Progressão e XP</b></summary>

> ### 14.1. Sistema de XP por Encontro
>
> - [ ] Implementar cálculo baseado em CR
> - [ ] Implementar XP por quests fixas
> - [ ] Testar XP por encontro
>
> ### 14.2. Sistema de XP por Nível
>
> - [ ] Implementar tabela D&D 5e completa
> - [ ] Implementar níveis 1-5
> - [ ] Testar XP por nível
>
> ### 14.3. Sistema de Level Up Automático
>
> - [ ] Implementar verificação de XP
> - [ ] Implementar trigger de level up
> - [ ] Testar level up automático
>
> ### 14.4. Sistema de Notificação de Level Up
>
> - [ ] Criar Widget de notificação
> - [ ] Implementar animação
> - [ ] Implementar som
> - [ ] Testar notificação
>
> ### 14.5. Sistema de Escolhas de Level Up
>
> - [ ] Implementar escolha de ASI nível 4
> - [ ] Implementar escolha de feats
> - [ ] Implementar escolha de features
> - [ ] Testar escolhas
>
> ### 14.6. Sistema de Progressão de Proficiência
>
> - [ ] Implementar +2 a cada 4 níveis
> - [ ] Testar progressão
>
> ### 14.7. Sistema de Progressão de Spell Slots
>
> - [ ] Implementar tabela por classe e nível
> - [ ] Testar progressão
>
> ### 14.8. Barra de XP no HUD
>
> - [ ] Criar Widget de XP bar
> - [ ] Implementar visual
> - [ ] Implementar porcentagem
> - [ ] Implementar próximo nível
> - [ ] Testar XP bar
>
> ### 14.9. Sistema de Milestone XP
>
> - [ ] Implementar desbloqueio por quests principais
> - [ ] Testar milestone XP
>
> ### 14.10. Validação de Progressão
>
> - [ ] Criar testes de progressão
> - [ ] Validar balanceamento
> - [ ] Ajustar se necessário
>
>___

</details>

---

## 🎯 FASE 3: FIM (Conteúdo e Polimento)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>15. Conteúdo da Campanha - Capítulo 1</b></summary>

> ### 15.1. Mapa Completo da Cragmaw Hideout
>
> - [ ] Criar todas as salas
> - [ ] Criar corredores
> - [ ] Adicionar áreas especiais
> - [ ] Configurar colisões
> - [ ] Adicionar iluminação
> - [ ] Testar navegação completa
>
> ### 15.2. Todos os Encontros do Capítulo 1
>
> - [ ] Posicionar todos os combates
> - [ ] Configurar triggers
> - [ ] Testar encontros
>
> ### 15.3. Todos os NPCs do Capítulo 1
>
> - [ ] Criar Sildar
> - [ ] Criar Goblins
> - [ ] Criar Klarg
> - [ ] Configurar diálogos
> - [ ] Testar NPCs
>
> ### 15.4. Todas as Quests do Capítulo 1
>
> - [ ] Implementar Ataque Goblin
> - [ ] Implementar Resgate Sildar
> - [ ] Testar quests
>
> ### 15.5. Todos os Itens e Tesouros
>
> - [ ] Posicionar loot fixo
> - [ ] Configurar loot aleatório
> - [ ] Testar loot
>
> ### 15.6. Diálogos Completos
>
> - [ ] Implementar diálogos de todos os NPCs
> - [ ] Implementar ramificações
> - [ ] Testar diálogos
>
> ### 15.7. Teste Completo do Capítulo 1
>
> - [ ] Playthrough completo
> - [ ] Validar todos os sistemas
> - [ ] Corrigir bugs encontrados
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>16. Conteúdo da Campanha - Capítulo 2</b></summary>

> ### 16.1. Mapa Completo de Phandalin
>
> - [ ] Criar vila completa
> - [ ] Criar edifícios
> - [ ] Criar áreas exploráveis
> - [ ] Configurar colisões
> - [ ] Testar navegação
>
> ### 16.2. Todos os Encontros do Capítulo 2
>
> - [ ] Posicionar Redbrands
> - [ ] Posicionar encontros opcionais
> - [ ] Configurar triggers
> - [ ] Testar encontros
>
> ### 16.3. Todos os NPCs do Capítulo 2
>
> - [ ] Criar Harbin
> - [ ] Criar Sildar
> - [ ] Criar Sister Garaele
> - [ ] Criar outros NPCs
> - [ ] Configurar diálogos
> - [ ] Testar NPCs
>
> ### 16.4. Todas as Quests do Capítulo 2
>
> - [ ] Implementar Redbrands
> - [ ] Implementar quests secundárias
> - [ ] Testar quests
>
> ### 16.5. Redbrand Hideout Completo
>
> - [ ] Criar mapa completo
> - [ ] Posicionar encontros
> - [ ] Criar boss Iarno
> - [ ] Testar hideout
>
> ### 16.6. Quests Secundárias
>
> - [ ] Implementar Agatha
> - [ ] Implementar Orc Trouble
> - [ ] Implementar outras quests
> - [ ] Testar quests
>
> ### 16.7. Diálogos Completos
>
> - [ ] Implementar diálogos de todos os NPCs
> - [ ] Implementar ramificações
> - [ ] Testar diálogos
>
> ### 16.8. Teste Completo do Capítulo 2
>
> - [ ] Playthrough completo
> - [ ] Validar todos os sistemas
> - [ ] Corrigir bugs
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>17. Conteúdo da Campanha - Capítulo 3</b></summary>

> ### 17.1. Mapa Completo do Cragmaw Castle
>
> - [ ] Criar todas as salas
> - [ ] Criar áreas secretas
> - [ ] Configurar colisões
> - [ ] Testar navegação
>
> ### 17.2. Todos os Encontros do Capítulo 3
>
> - [ ] Posicionar Goblins
> - [ ] Posicionar Hobgoblin
> - [ ] Posicionar King Grol
> - [ ] Configurar triggers
> - [ ] Testar encontros
>
> ### 17.3. Todos os NPCs do Capítulo 3
>
> - [ ] Criar Gundren
> - [ ] Criar King Grol
> - [ ] Criar Doppelganger
> - [ ] Configurar diálogos
> - [ ] Testar NPCs
>
> ### 17.4. Todas as Quests do Capítulo 3
>
> - [ ] Implementar Resgate Gundren
> - [ ] Implementar descoberta do plano
> - [ ] Testar quests
>
> ### 17.5. Diálogos Completos
>
> - [ ] Implementar diálogos
> - [ ] Implementar revelações
> - [ ] Testar diálogos
>
> ### 17.6. Teste Completo do Capítulo 3
>
> - [ ] Playthrough completo
> - [ ] Validar sistemas
> - [ ] Corrigir bugs
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>18. Conteúdo da Campanha - Capítulo 4</b></summary>

> ### 18.1. Mapa Completo da Wave Echo Cave
>
> - [ ] Criar todas as áreas
> - [ ] Criar salas e corredores
> - [ ] Configurar colisões
> - [ ] Testar navegação
>
> ### 18.2. Todos os Encontros do Capítulo 4
>
> - [ ] Posicionar Mortos-vivos
> - [ ] Posicionar Nothic
> - [ ] Posicionar Flameskull
> - [ ] Posicionar outros encontros
> - [ ] Configurar triggers
> - [ ] Testar encontros
>
> ### 18.3. Boss Fight com Nezznar
>
> - [ ] Criar Nezznar (Black Spider)
> - [ ] Implementar IA especial
> - [ ] Implementar diálogo
> - [ ] Implementar mecânicas especiais
> - [ ] Testar boss fight
>
> ### 18.4. Todos os NPCs do Capítulo 4
>
> - [ ] Criar Nezznar
> - [ ] Criar Gundren resgatado
> - [ ] Configurar diálogos
> - [ ] Testar NPCs
>
> ### 18.5. Forja das Magias
>
> - [ ] Criar área final
> - [ ] Implementar visual especial
> - [ ] Implementar recompensas
> - [ ] Testar área
>
> ### 18.6. Diálogos Completos
>
> - [ ] Implementar diálogos
> - [ ] Implementar revelações finais
> - [ ] Testar diálogos
>
> ### 18.7. Final da Campanha
>
> - [ ] Criar cutscene/sequência
> - [ ] Implementar conclusão narrativa
> - [ ] Testar final
>
> ### 18.8. Teste Completo do Capítulo 4
>
> - [ ] Playthrough completo
> - [ ] Validar sistemas
> - [ ] Corrigir bugs
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>19. UI/UX Completo</b></summary>

> ### 19.1. Menu Principal Completo
>
> - [ ] Criar Widget de menu principal
> - [ ] Implementar Novo Jogo
> - [ ] Implementar Continuar
> - [ ] Implementar Opções
> - [ ] Implementar Sair
> - [ ] Testar menu
>
> ### 19.2. HUD Completo
>
> - [ ] Criar Widget de HUD
> - [ ] Implementar HP bar
> - [ ] Implementar Mana/Spell Slots bar
> - [ ] Implementar XP bar
> - [ ] Implementar minimapa
> - [ ] Implementar hotbar (1-0)
> - [ ] Testar HUD
>
> ### 19.3. Tela de Inventário Completa
>
> - [ ] Criar Widget de inventário
> - [ ] Implementar organização
> - [ ] Implementar categorias
> - [ ] Implementar busca
> - [ ] Implementar drag & drop
> - [ ] Testar inventário
>
> ### 19.4. Tela de Ficha de Personagem Completa
>
> - [ ] Criar Widget de ficha
> - [ ] Exibir todos os atributos
> - [ ] Exibir skills
> - [ ] Exibir saves
> - [ ] Testar ficha
>
> ### 19.5. Tela de Spellbook Completa
>
> - [ ] Criar Widget de spellbook
> - [ ] Implementar preparação
> - [ ] Implementar seleção
> - [ ] Implementar casting
> - [ ] Implementar slots visíveis
> - [ ] Testar spellbook
>
> ### 19.6. Tela de Quests Completa
>
> - [ ] Criar Widget de quests
> - [ ] Implementar lista
> - [ ] Implementar progresso
> - [ ] Implementar objetivos
> - [ ] Implementar recompensas
> - [ ] Testar quests
>
> ### 19.7. Tela de Mapa do Mundo
>
> - [ ] Criar Widget de mapa
> - [ ] Implementar Phandalin e áreas
> - [ ] Implementar marcadores
> - [ ] Implementar zoom
> - [ ] Testar mapa
>
> ### 19.8. Tela de Opções/Settings
>
> - [ ] Criar Widget de opções
> - [ ] Implementar áudio
> - [ ] Implementar vídeo
> - [ ] Implementar controles
> - [ ] Implementar salvamento
> - [ ] Testar opções
>
> ### 19.9. Tela de Pause
>
> - [ ] Criar Widget de pause
> - [ ] Implementar menu durante jogo
> - [ ] Implementar salvamento rápido
> - [ ] Testar pause
>
> ### 19.10. Fluxo de Navegação Completo
>
> - [ ] Implementar transições entre telas
> - [ ] Implementar atalhos de teclado
> - [ ] Testar navegação
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>20. Áudio Completo</b></summary>

> ### 20.1. SFX de Combate
>
> - [ ] Criar SFX de ataques melee
> - [ ] Criar SFX de ataques ranged
> - [ ] Criar SFX de hits
> - [ ] Criar SFX de críticos
> - [ ] Criar SFX de bloqueios
> - [ ] Integrar SFX
> - [ ] Testar SFX
>
> ### 20.2. SFX de Magias
>
> - [ ] Criar SFX por tipo de dano
> - [ ] Criar SFX de casting
> - [ ] Criar SFX de impactos
> - [ ] Integrar SFX
> - [ ] Testar SFX
>
> ### 20.3. SFX de Interação
>
> - [ ] Criar SFX de portas
> - [ ] Criar SFX de baús
> - [ ] Criar SFX de diálogos
> - [ ] Criar SFX de objetos
> - [ ] Integrar SFX
> - [ ] Testar SFX
>
> ### 20.4. SFX Ambientais
>
> - [ ] Criar SFX de passos por terreno
> - [ ] Criar SFX de ambiente
> - [ ] Criar SFX de vento
> - [ ] Criar SFX de água
> - [ ] Integrar SFX
> - [ ] Testar SFX
>
> ### 20.5. Música de Exploração
>
> - [ ] Criar música para Phandalin
> - [ ] Criar música para áreas abertas
> - [ ] Criar música de calmaria
> - [ ] Integrar música
> - [ ] Testar música
>
> ### 20.6. Música de Combate
>
> - [ ] Criar música de combate
> - [ ] Implementar intensidade
> - [ ] Implementar loops
> - [ ] Implementar transições
> - [ ] Testar música
>
> ### 20.7. Música de Masmorras
>
> - [ ] Criar música para Cragmaw Hideout
> - [ ] Criar música para Wave Echo Cave
> - [ ] Criar música de tensão
> - [ ] Integrar música
> - [ ] Testar música
>
> ### 20.8. Música de Tensão/Suspense
>
> - [ ] Criar música para momentos críticos
> - [ ] Criar música para boss fights
> - [ ] Integrar música
> - [ ] Testar música
>
> ### 20.9. SFX de UI
>
> - [ ] Criar SFX de cliques
> - [ ] Criar SFX de notificações
> - [ ] Criar SFX de level up
> - [ ] Criar SFX de quests
> - [ ] Integrar SFX
> - [ ] Testar SFX
>
> ### 20.10. Sistema de Áudio Espacial
>
> - [ ] Configurar áudio 3D
> - [ ] Implementar distância
> - [ ] Implementar oclusão
> - [ ] Testar áudio espacial
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>21. Polimento e Balanceamento</b></summary>

> ### 21.1. Balanceamento de Combate
>
> - [ ] Analisar dificuldade por nível
> - [ ] Ajustar CR dos encontros
> - [ ] Testar balanceamento
> - [ ] Ajustar se necessário
>
> ### 21.2. Balanceamento de Economia
>
> - [ ] Analisar ouro por sessão
> - [ ] Analisar preços
> - [ ] Analisar fontes e drenos
> - [ ] Ajustar balanceamento
> - [ ] Testar economia
>
> ### 21.3. Balanceamento de Progressão
>
> - [ ] Analisar XP por encontro
> - [ ] Analisar curva de level up
> - [ ] Ajustar progressão
> - [ ] Testar progressão
>
> ### 21.4. Otimização de Performance
>
> - [ ] Fazer profiling
> - [ ] Implementar LODs
> - [ ] Implementar culling
> - [ ] Implementar pooling
> - [ ] Testar performance
>
> ### 21.5. Correção de Bugs Críticos
>
> - [ ] Identificar bugs game-breaking
> - [ ] Identificar crashes
> - [ ] Identificar data loss
> - [ ] Corrigir bugs críticos
> - [ ] Testar correções
>
> ### 21.6. Correção de Bugs Menores
>
> - [ ] Identificar bugs de UI
> - [ ] Identificar bugs visuais
> - [ ] Identificar edge cases
> - [ ] Corrigir bugs menores
> - [ ] Testar correções
>
> ### 21.7. Melhorias de UX
>
> - [ ] Coletar feedback de testes
> - [ ] Identificar problemas de usabilidade
> - [ ] Implementar melhorias
> - [ ] Testar melhorias
>
> ### 21.8. Ajustes de Feedback Visual
>
> - [ ] Ajustar partículas
> - [ ] Ajustar números flutuantes
> - [ ] Ajustar indicadores
> - [ ] Testar feedback visual
>
> ### 21.9. Ajustes de Feedback Sonoro
>
> - [ ] Ajustar volume
> - [ ] Ajustar timing
> - [ ] Ajustar mixagem
> - [ ] Testar feedback sonoro
>
> ### 21.10. Testes de Gameplay Completos
>
> - [ ] Fazer playthrough completo
> - [ ] Validar todos os sistemas
> - [ ] Documentar problemas
> - [ ] Corrigir problemas encontrados
>
>___

</details>

---

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>22. Finalização</b></summary>

> ### 22.1. Sistema de Save/Load Completo e Robusto
>
> - [ ] Estender SaveGame com todos os dados
> - [ ] Implementar validação de dados
> - [ ] Implementar versionamento de saves
> - [ ] Testar save/load completo
>
> ### 22.2. Sistema de Múltiplos Saves
>
> - [ ] Implementar slots de save
> - [ ] Implementar nomes de save
> - [ ] Implementar timestamps
> - [ ] Testar múltiplos saves
>
> ### 22.3. Sistema de Autosave
>
> - [ ] Implementar checkpoints
> - [ ] Implementar autosave em eventos importantes
> - [ ] Testar autosave
>
> ### 22.4. Teste Completo da Campanha
>
> - [ ] Fazer playthrough completo (início ao fim)
> - [ ] Testar todos os capítulos
> - [ ] Validar todos os sistemas
> - [ ] Documentar problemas
>
> ### 22.5. Documentação Final do Projeto
>
> - [ ] Atualizar README
> - [ ] Atualizar guias
> - [ ] Criar changelog completo
> - [ ] Validar documentação
>
> ### 22.6. Build de Release
>
> - [ ] Configurar build Windows
> - [ ] Otimizar build
> - [ ] Remover debug
> - [ ] Testar build de release
>
> ### 22.7. Testes Finais de QA
>
> - [ ] Testar todos os sistemas
> - [ ] Testar edge cases
> - [ ] Testar performance
> - [ ] Documentar resultados
>
> ### 22.8. Preparação para Distribuição
>
> - [ ] Criar instalador
> - [ ] Documentar requisitos
> - [ ] Preparar licença
> - [ ] Validar distribuição
>
>___

</details>

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Resumo e Metodologia</b></summary>

> **Total de Micro-Tarefas:** ~400+ tarefas atômicas (2-4 horas cada)
>
> **Metodologia Aplicada:**
>
> - ✅ **Personal Kanban:** WIP limitado a 1-2 tarefas
> - ✅ **Micro-Milestones:** Cada tarefa completável em uma sessão
> - ✅ **Data-Driven First:** Sempre priorizar Data Tables/Assets
> - ✅ **TDD:** Testes antes da implementação quando aplicável
> - ✅ **Vertical Slice:** Prova de conceito completa primeiro
>
> **Como Usar:**
>
> 1. Escolha 1-2 tarefas da categoria atual
> 2. Complete em 2-4 horas
> 3. Teste imediatamente
> 4. Marque como concluído
> 5. Mova para próxima tarefa
>
> **Prioridade:** Sempre seguir ordem do roadmap (Fase 1 → 2 → 3)

</details>

---

**Última atualização:** 2024-12-27
