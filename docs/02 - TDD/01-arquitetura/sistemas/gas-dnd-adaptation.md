# Adaptação D&D 5e para Unreal Engine 5 com GAS

> **Documento de Design:** Explica como adaptar as regras de D&D 5e para um jogo Action RPG no Unreal Engine 5 usando Gameplay Ability System (GAS).

**⚠️ Status do Projeto:**

**✅ Implementado Atualmente:**
- Sistema de fichas completo: `UCharacterSheetDataAsset`, `UCharacterSheetComponent`, `UCharacterDataComponent`
- Replicação multiplayer: `DOREPLIFETIME` em `UCharacterDataComponent` (13 propriedades replicáveis)
- Motores desacoplados: `FMulticlassMotor`, `FPointBuyMotor`, `FRaceBonusMotor`, `FCharacterSheetCore`
- Arquitetura em 4 camadas: Data Assets → Bridge Components → Runtime Data Components → Feature Components
- Sistema de cálculo: `FinalScore = BASE_ABILITY_SCORE (8) + RacialBonuses + PointBuyAllocation` (ordem de aplicação)
- Testes completos: 100% cobertura de testes para todos os motores críticos (TDD)

**🔮 Planejado (Futuro):**
- Migração para GAS (Gameplay Ability System) - este documento explica como será implementado
- Feature Components (Fase 5): `USpellcastingComponent`, `USecondWindComponent`, `UActionSurgeComponent`
- Motor de escolhas: `FChoiceMotor` (🔮 Planejado - escolhas atualmente gerenciadas por handlers/validators)

**Referências:**

- [D&D Beyond Basic Rules](https://www.dndbeyond.com/sources/dnd/br-2024)
- [Unreal Engine GAS Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine)

---

## 📋 Índice deste Documento

1. [Visão Geral: RPG de Mesa vs Jogo Digital](#visão-geral-rpg-de-mesa-vs-jogo-digital)
2. [Gameplay Ability System (GAS) - Conceitos Fundamentais](#gameplay-ability-system-gas---conceitos-fundamentais)
3. [Fluxos Práticos: Do RPG de Mesa para o Jogo](#fluxos-práticos-do-rpg-de-mesa-para-o-jogo)
4. [Adaptação de Regras D&D 5e](#adaptação-de-regras-dd-5e)
5. [Action RPG: Colisão Real e Combate](#action-rpg-colisão-real-e-combate)
6. [Sistema de Condições e Efeitos](#sistema-de-condições-e-efeitos)
7. [Magias e Habilidades Especiais](#magias-e-habilidades-especiais)
8. [Multiplayer: Sincronização e Autoridade](#multiplayer-sincronização-e-autoridade)

---

---

## 🎲 Visão Geral: RPG de Mesa vs Jogo Digital

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Analogia: Sessão de RPG de Mesa</b></summary>

> Em uma sessão de RPG de mesa, temos três elementos principais:
>

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Ficha do Personagem (AttributeSet)</summary>

> **Responsabilidade:** Guardar todos os números do personagem.
>
> - **Exemplos:** "Strength: 16", "HP: 45/50", "Proficiency: +3", "AC: 18"
> - **Não decide:** Não rola dados, não aplica regras, não executa ações
> - **Apenas armazena:** Valores que podem mudar durante o jogo

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📖 Livro de Regras (GameplayEffect)</summary>

> **Responsabilidade:** Definir o que acontece e quando.
>
> - **Exemplos:** "Ataque = d20 + Strength modifier + Proficiency", "Dano = 1d8 + Strength modifier", "Acerto reduz HP do alvo"
> - **Define:** Fórmulas, condições, consequências, duração de efeitos
> - **Não executa:** Apenas define as regras

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Ação do Jogador (GameplayAbility)</summary>

> **Responsabilidade:** Executar a ação declarada.
>
> - **Exemplos:** "Eu ataco com espada!", "Uso spell Fireball", "Faço um teste de skill"
> - **Orquestra:** Declara ação → Consulta regras (GameplayEffect) → Atualiza ficha (AttributeSet)
> - **Coordena:** Todo o fluxo de execução
>
> **🔄 Fluxo Completo:**
>
> 1. **Jogador:** "Eu ataco!" → GameplayAbility (ação)
> 2. **Regra:** "Rola d20 + Strength + Proficiency" → GameplayEffect (fórmula)
> 3. **Ficha:** "Strength: 16 (+3), Proficiency: +3" → AttributeSet (valores)
> 4. **Resultado:** d20(12) + 3 + 3 = 18 vs AC 15 → **Acertou!**
> 5. **Regra:** "Dano = 1d8 + Strength modifier" → GameplayEffect
> 6. **Ficha:** "HP do alvo: 50 → 42" → AttributeSet (atualiza)

</details>

---

## 🎮 Gameplay Ability System (GAS) - Conceitos Fundamentais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏗️ Os 3 Pilares do GAS</b></summary>

> ### 1. **AttributeSet - A Ficha do Personagem**
>

> **Responsabilidade EXCLUSIVA:**
>
> - ✅ Armazenar valores de atributos (Base e Current)
> - ✅ Gerenciar modificadores temporários
> - ✅ Replicar em multiplayer
> - ✅ Notificar mudanças (eventos)
> - ✅ Validar/Clamp valores (ex: Strength entre 1-30)
>
> **O que NÃO faz:**
>
> - ❌ Aplicar lógica de gameplay (isso é GameplayEffect)
> - ❌ Decidir quando aplicar modificadores (isso é GameplayEffect)
> - ❌ Gerenciar habilidades (isso é GameplayAbility)
>
> **Para D&D 5e, armazena:**
>
> - **Ability Scores:** Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
> - **Derivados:** Modifiers, MaxHealth, ArmorClass, ProficiencyBonus
> - **Meta-Attributes:** Health atual, Temporary modifiers
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📖 GameplayEffect - O Livro de Regras</summary>

> **Responsabilidade EXCLUSIVA:**
>
> - ✅ Definir o que acontece e quando
> - ✅ Aplicar modificadores de atributos
> - ✅ Definir duração de efeitos
> - ✅ Estabelecer condições de aplicação
>
> **Para D&D 5e, define:**
>
> - **Fórmulas:** "Ataque = d20 + Strength modifier + Proficiency"
> - **Efeitos Temporários:** "+2 Strength por 1 hora (spell)"
> - **Condições:** "Envenenado = -1 em todos os checks"
> - **Duração:** Instantâneo, 1 turno, 1 hora, permanente

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ GameplayAbility - A Ação do Jogador</summary>

> **Responsabilidade EXCLUSIVA:**
>
> - ✅ Executar ações e coordenar
> - ✅ Orquestrar fluxo completo
> - ✅ Chamar GameplayEffects
> - ✅ Gerenciar cooldowns e custos
>
> **Para D&D 5e, executa:**
>
> - **Ataques:** "Ataque com espada", "Ataque à distância"
> - **Spells:** "Fireball", "Cure Wounds", "Shield"
> - **Habilidades:** "Action Surge", "Second Wind", "Rage"
> - **Skills:** "Stealth", "Perception", "Athletics"

</details>

---

## ⚔️ Fluxos Práticos: Do RPG de Mesa para o Jogo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Exemplo 1: Ataque Básico</b></summary>

> ### **RPG de Mesa:**
>

> 1. **Jogador:** "Eu ataco o goblin com minha espada!"
> 2. **DM:** "Rola d20 para acerto"
> 3. **Jogador:** Rola d20 = 12
> 4. **Jogador:** "Meu Strength é 16 (+3) e tenho Proficiency +3, então 12 + 3 + 3 = 18"
> 5. **DM:** "AC do goblin é 15, você acertou! Rola dano"
> 6. **Jogador:** Rola 1d8 = 5, "5 + 3 (Strength) = 8 de dano"
> 7. **DM:** "Goblin perde 8 HP, agora tem 2/10 HP"
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 No Jogo (GAS)</summary>

> 1. **Jogador:** Pressiona botão de ataque → **GameplayAbility** (ação)
> 2. **Sistema:** Consulta regra "Ataque = d20 + Strength + Proficiency" → **GameplayEffect** (fórmula)
> 3. **Sistema:** Lê valores "Strength: 16 (+3), Proficiency: +3" → **AttributeSet** (valores)
> 4. **Sistema:** Calcula 12 + 3 + 3 = 18 vs AC 15 → **Acertou!**
> 5. **Sistema:** Aplica regra "Dano = 1d8 + Strength modifier" → **GameplayEffect**
> 6. **Sistema:** Atualiza "HP do goblin: 10 → 2" → **AttributeSet** (atualiza)
>
> **🎯 Diferença Principal:**
>
> - **RPG de Mesa:** Jogador e DM fazem tudo manualmente
> - **Jogo Digital:** Sistema automatiza cálculos, mas segue as mesmas regras

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💀 Exemplo 2: Condição Envenenado</b></summary>

> ### **RPG de Mesa:**
>

> 1. **DM:** "O goblin te acerta com uma adaga envenenada"
> 2. **DM:** "Faça um saving throw de Constitution"
> 3. **Jogador:** Rola d20 = 8, "Meu Constitution é 14 (+2), então 8 + 2 = 10"
> 4. **DM:** "DC é 12, você falhou. Você está envenenado"
> 5. **DM:** "Enquanto envenenado, você tem desvantagem em todos os checks e ataques"
> 6. **Jogador:** "Ok, vou rolar com desvantagem nos próximos ataques"
> 7. **DM:** "A cada turno, você pode tentar fazer outro saving throw para se curar"
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 No Jogo (GAS)</summary>

> 1. **Sistema:** Goblin aplica ataque envenenado → **GameplayAbility** (ação)
> 2. **Sistema:** Cria efeito "Poison Effect" → **GameplayEffect** (regra)
> 3. **Sistema:** Solicita saving throw de Constitution → **GameplayEffect** (condição)
> 4. **Sistema:** Jogador falha (10 < 12) → Aplica condição "Envenenado"
> 5. **Sistema:** Modifica atributos "-1 em todos os checks e ataques" → **AttributeSet** (atualiza)
> 6. **Sistema:** A cada turno, permite novo saving throw → **GameplayEffect** (duração)
> 7. **Sistema:** Quando passar, remove efeito → **AttributeSet** (restaura valores)
>
> **🎯 Diferença Principal:**
>
> - **RPG de Mesa:** DM lembra de aplicar desvantagem manualmente
> - **Jogo Digital:** Sistema aplica automaticamente, mas jogador vê feedback visual

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔥 Exemplo 3: Spell Fireball</b></summary>

> ### **RPG de Mesa:**
>

> 1. **Jogador:** "Eu lanço Fireball no grupo de goblins!"
> 2. **DM:** "Fireball é uma área de 6 metros de raio. Onde você quer lançar?"
> 3. **Jogador:** "No centro do grupo"
> 4. **DM:** "Todos os goblins fazem saving throw de Dexterity"
> 5. **Jogador:** "Fireball causa 8d6 de dano de fogo, metade se passar no saving throw"
> 6. **DM:** "Goblin 1: 15 (passou), Goblin 2: 8 (falhou), Goblin 3: 12 (passou)"
> 7. **DM:** "Rola dano"
> 8. **Jogador:** Rola 8d6 = 28
> 9. **DM:** "Goblin 1: 14 de dano (metade), Goblin 2: 28 de dano (total), Goblin 3: 14 de dano (metade)"
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 No Jogo (GAS)</summary>

> 1. **Jogador:** Pressiona botão "Fireball" → **GameplayAbility** (ação)
> 2. **Sistema:** Verifica se tem spell slot disponível → **GameplayAbility** (custo)
> 3. **Sistema:** Jogador escolhe área (raio de 6 metros) → **GameplayAbility** (targeting)
> 4. **Sistema:** Identifica todos os alvos na área → **GameplayAbility** (detecção)
> 5. **Sistema:** Para cada alvo, aplica "Fireball Damage Effect" → **GameplayEffect** (regra)
> 6. **Sistema:** Cada alvo faz saving throw de Dexterity → **GameplayEffect** (condição)
> 7. **Sistema:** Calcula dano 8d6 = 28 → **GameplayEffect** (fórmula)
> 8. **Sistema:** Aplica dano (total ou metade) → **AttributeSet** (atualiza HP)
> 9. **Sistema:** Aplica efeito visual de explosão → **GameplayAbility** (feedback)
>
> **🎯 Diferença Principal:**
>
> - **RPG de Mesa:** DM calcula área e dano manualmente
> - **Jogo Digital:** Sistema calcula automaticamente, mas jogador vê área e explosão visual

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Exemplo 4: Habilidade Action Surge (Fighter)</b></summary>

> ### **RPG de Mesa:**
>

> 1. **Jogador:** "Eu uso Action Surge para ter uma ação extra!"
> 2. **DM:** "Ok, você tem uma ação extra neste turno"
> 3. **Jogador:** "Agora eu ataco novamente!"
> 4. **DM:** "Rola ataque"
> 5. **Jogador:** Rola e ataca normalmente
> 6. **DM:** "Action Surge só pode ser usada uma vez por short rest"
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 No Jogo (GAS)</summary>

> 1. **Jogador:** Pressiona botão "Action Surge" → **GameplayAbility** (ação)
> 2. **Sistema:** Verifica se está disponível (cooldown) → **GameplayAbility** (validação)
> 3. **Sistema:** Aplica efeito "+1 ação extra neste turno" → **GameplayEffect** (regra)
> 4. **Sistema:** Modifica "ActionsAvailable: 1 → 2" → **AttributeSet** (atualiza)
> 5. **Sistema:** Jogador pode atacar novamente → **GameplayAbility** (permissão)
> 6. **Sistema:** Após usar, aplica cooldown "1x por short rest" → **GameplayEffect** (duração)
> 7. **Sistema:** Após short rest, restaura disponibilidade → **AttributeSet** (restaura)
>
> **🎯 Diferença Principal:**
>
> - **RPG de Mesa:** Jogador e DM lembram de aplicar ação extra
> - **Jogo Digital:** Sistema gerencia automaticamente, mas jogador vê feedback de ações disponíveis

</details>

---

## 📖 Adaptação de Regras D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Princípios de Adaptação</b></summary>

> ### **1. Fidelidade às Regras**
>

> - ✅ Todas as regras oficiais de D&D 5e são mantidas
> - ✅ Fórmulas de cálculo são idênticas
> - ✅ Condições e efeitos funcionam igual
> - ✅ Balanceamento não é alterado
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🤖 Automação Inteligente</summary>

> - ✅ Sistema calcula automaticamente (não precisa rolar dados manualmente)
> - ✅ Aplica modificadores automaticamente
> - ✅ Gerencia duração de efeitos automaticamente
> - ✅ Valida condições automaticamente

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👁️ Feedback Visual</summary>

> - ✅ Jogador vê resultados de rolagens (opcional)
> - ✅ Efeitos visuais para condições
> - ✅ Feedback de acerto/erro
> - ✅ Indicadores de buffs/debuffs

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Action RPG: Colisão Real</summary>

> - ✅ Combate é em tempo real (não turn-based)
> - ✅ Colisão física real (não abstrata)
> - ✅ Projéteis têm física real
> - ✅ Áreas de efeito são visuais e físicas
>
> **⚠️ IMPORTANTE:** As regras de D&D 5e são mantidas, mas a execução é adaptada para tempo real.

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Atributos e Cálculos</b></summary>

> ### **Ability Scores (AttributeSet)**
>

> **Armazenados:**
>
> - Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma
> - Base Value (valor base da ficha)
> - Current Value (valor atual com modificadores)
>
> **Modificadores:**
>
> - Calculados automaticamente: `(Score - 10) / 2` (arredondado para baixo)
> - Exemplo: Strength 16 → Modifier +3
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Atributos Derivados (Meta-Attributes)</summary>

> **MaxHealth:**
>
> - **Level 1:** `Hit Die + Constitution Modifier`
> - **Level 2+:** `(Hit Die / 2) + 1 + Constitution Modifier` (por nível adicional)
> - Recalcula automaticamente quando Constitution muda ou nível aumenta
> - **⚠️ IMPORTANTE:** Constitution Modifier é calculado a partir do Final Constitution Score (BASE_ABILITY_SCORE + Racial + PointBuy + ASI)
> - **📖 Ver também:** [dnd-rules/level-up.md](../dnd-rules/level-up.md) - Fórmula completa de HP
>
> **ArmorClass (AC):**
>
> - Fórmula: `10 + Dexterity Modifier + Armor Bonus`
> - Recalcula automaticamente quando Dexterity ou Armor muda
>
> **ProficiencyBonus:**
>
> - Tabela fixa baseada no **Total Level** (soma de todos os níveis de classes):
> - Níveis 1-4: +2
> - Níveis 5-8: +3
> - Níveis 9-12: +4
> - Níveis 13-16: +5
> - Níveis 17-20: +6
> - Fórmula: `2 + floor((TotalLevel - 1) / 4)`
> - Recalcula automaticamente quando Total Level muda
> - **⚠️ IMPORTANTE:** Em multiclassing, usa Total Level, não nível de classe específica
> - **📖 Ver também:** [dnd-rules/level-up.md](../dnd-rules/level-up.md) - Tabela completa de Proficiency Bonus
>
> **🎯 Vantagem do GAS:**
>
> - Todos os cálculos são automáticos
> - Modificadores temporários são aplicados automaticamente
> - Sistema notifica quando valores mudam (para UI reativa)

</details>

---

## ⚔️ Action RPG: Colisão Real e Combate

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Combate em Tempo Real</b></summary>

> ### **Diferenças do RPG de Mesa:**
>

> **RPG de Mesa (Turn-Based):**
>
> - Jogadores agem em turnos
> - Cada ação é declarada e resolvida antes da próxima
> - Tempo é abstrato (rounds, turns)
>
> **Jogo Digital (Action RPG):**
>
> - Combate é em tempo real
> - Jogador controla movimento e ataques diretamente
> - Colisão física real (não abstrata)
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Como Adaptar</summary>

> **1. Ataques:**
>
> - **RPG de Mesa:** "Eu ataco" → Rola d20 → DM diz se acertou
> - **Jogo Digital:** Jogador pressiona botão → Sistema verifica se hitbox colidiu → Aplica dano
>
> **2. Saving Throws:**
>
> - **RPG de Mesa:** "Faça saving throw" → Rola d20 → DM diz resultado
> - **Jogo Digital:** Sistema detecta efeito → Calcula saving throw automaticamente → Aplica resultado
>
> **3. Áreas de Efeito:**
>
> - **RPG de Mesa:** "Fireball em área de 6 metros" → DM decide quem está na área
> - **Jogo Digital:** Sistema detecta colisão física → Aplica efeito em todos os alvos na área
>
> **4. Projéteis:**
>
> - **RPG de Mesa:** "Eu atiro uma flecha" → DM decide se acertou
> - **Jogo Digital:** Flecha é objeto físico → Colisão real determina acerto → Aplica dano
>
> **🎯 Vantagem do GAS:**
>
> - Sistema gerencia regras automaticamente
> - Colisão física é gerenciada pelo Unreal Engine
> - GAS aplica efeitos baseados em regras D&D 5e

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💥 Sistema de Dano e Colisão</b></summary>

> ### **Fluxo de Ataque com Colisão Real:**
>

> 1. **Jogador:** Pressiona botão de ataque → **GameplayAbility** (ação)
> 2. **Sistema:** Ativa hitbox de ataque (collision component) → **Unreal Engine** (física)
> 3. **Sistema:** Detecta colisão com inimigo → **Unreal Engine** (detecção)
> 4. **Sistema:** Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
> - `d20 + Strength Modifier + Proficiency Bonus vs AC`
> 5. **Sistema:** Se acertou, calcula dano → **GameplayEffect** (fórmula)
> - `Weapon Damage + Strength Modifier`
> 6. **Sistema:** Aplica dano no alvo → **AttributeSet** (atualiza HP)
> 7. **Sistema:** Mostra feedback visual → **GameplayAbility** (feedback)
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏹 Fluxo de Projétil com Colisão Real</summary>

> 1. **Jogador:** Pressiona botão de tiro → **GameplayAbility** (ação)
> 2. **Sistema:** Spawna projétil físico → **Unreal Engine** (física)
> 3. **Sistema:** Projétil voa com física real → **Unreal Engine** (movimento)
> 4. **Sistema:** Projétil colide com alvo → **Unreal Engine** (colisão)
> 5. **Sistema:** Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
>    - `d20 + Dexterity Modifier + Proficiency Bonus vs AC`
> 6. **Sistema:** Se acertou, calcula dano → **GameplayEffect** (fórmula)
>    - `Weapon Damage + Dexterity Modifier`
> 7. **Sistema:** Aplica dano no alvo → **AttributeSet** (atualiza HP)
>
> **🎯 Vantagem:**
>
> - Colisão física real (não abstrata)
> - Regras D&D 5e são mantidas
> - Sistema automatiza cálculos

</details>

---

## 🧪 Sistema de Condições e Efeitos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💀 Condições D&D 5e</b></summary>

> ### **Condições Implementadas:**
>

> **Blinded (Cego):**
>
> - **RPG de Mesa:** "Você não pode ver, falha em checks que requerem visão"
> - **Jogo Digital:** Sistema aplica desvantagem automaticamente → **GameplayEffect** (regra)
> - **Visual:** Tela escurecida ou efeito visual
>
> **Charmed (Enfeitiçado):**
>
> - **RPG de Mesa:** "Você não pode atacar o encantador"
> - **Jogo Digital:** Sistema bloqueia ataques no encantador → **GameplayAbility** (validação)
> - **Visual:** Aura ou efeito visual no personagem
>
> **Frightened (Amedrontado):**
>
> - **RPG de Mesa:** "Você tem desvantagem em checks enquanto o causador do medo estiver visível"
> - **Jogo Digital:** Sistema aplica desvantagem automaticamente → **GameplayEffect** (regra)
> - **Visual:** Personagem treme ou efeito visual
>
> **Poisoned (Envenenado):**
>
> - **RPG de Mesa:** "Você tem desvantagem em todos os checks e ataques"
> - **Jogo Digital:** Sistema aplica -1 em todos os checks → **AttributeSet** (modificador)
> - **Visual:** Personagem fica verde ou efeito visual
>
> **Stunned (Atordoado):**
>
> - **RPG de Mesa:** "Você está incapacitado, não pode se mover ou agir"
> - **Jogo Digital:** Sistema bloqueia ações → **GameplayAbility** (validação)
> - **Visual:** Personagem fica parado ou efeito visual
>
> **🎯 Vantagem do GAS:**
>
> - Cada condição é um **GameplayEffect**
> - Sistema aplica modificadores automaticamente
> - Duração é gerenciada automaticamente
> - Pode combinar múltiplas condições
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Efeitos Temporários</b></summary>

> ### **Buffs (Efeitos Positivos):**
>

> **Bull's Strength (Spell):**
>
> - **RPG de Mesa:** "+2 Strength por 1 hora"
> - **Jogo Digital:** **GameplayEffect** aplica +2 em Strength → **AttributeSet** (atualiza)
> - **Duração:** 1 hora (gerenciada automaticamente)
> - **Visual:** Aura ou efeito visual no personagem
>
> **Haste (Spell):**
>
> - **RPG de Mesa:** "Velocidade dobra, +1 ação, +2 AC"
> - **Jogo Digital:** **GameplayEffect** aplica modificadores → **AttributeSet** (atualiza)
> - **Duração:** 1 minuto (gerenciada automaticamente)
> - **Visual:** Personagem fica mais rápido visualmente
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⬇️ Debuffs (Efeitos Negativos)</summary>

> **Slow (Spell):**
>
> - **RPG de Mesa:** "Velocidade reduzida, -2 AC, -2 em saving throws"
> - **Jogo Digital:** **GameplayEffect** aplica modificadores → **AttributeSet** (atualiza)
> - **Duração:** 1 minuto (gerenciada automaticamente)
> - **Visual:** Personagem fica mais lento visualmente
>
> **Curse (Maldição):**
>
> - **RPG de Mesa:** "Atributo reduzido permanentemente até remover maldição"
> - **Jogo Digital:** **GameplayEffect** aplica modificador permanente → **AttributeSet** (atualiza)
> - **Duração:** Até remover (gerenciada por condição)
> - **Visual:** Aura escura ou efeito visual
>
> **🎯 Vantagem do GAS:**
>
> - Efeitos são aplicados automaticamente
> - Duração é gerenciada automaticamente
> - Múltiplos efeitos podem ser combinados
> - Sistema notifica quando efeitos expiram

</details>

---

## 🔮 Magias e Habilidades Especiais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Sistema de Spellcasting</b></summary>

> ### **Spell Slots (GameplayAbility):**
>

> **RPG de Mesa:**
>
> - Jogador tem X spell slots por nível
> - Usa slot para lançar spell
> - Recupera slots em long rest
>
> **Jogo Digital:**
>
> - **AttributeSet** armazena spell slots disponíveis
> - **GameplayAbility** valida se tem slot disponível
> - **GameplayEffect** consome slot ao lançar
> - **GameplayEffect** restaura slots em long rest
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📜 Spell Components (GameplayAbility)</summary>

> **RPG de Mesa:**
>
> - Verbal (V): Precisa falar
> - Somatic (S): Precisa fazer gestos
> - Material (M): Precisa de componente material
>
> **Jogo Digital:**
>
> - **GameplayAbility** valida componentes antes de lançar
> - **GameplayAbility** verifica se tem material (se necessário)
> - **GameplayAbility** bloqueia se componentes não disponíveis

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📈 Spell Levels e Scaling</summary>

> **RPG de Mesa:**
>
> - Spells têm níveis (1-9)
> - Alguns spells podem ser upcast (usar slot maior)
> - Dano/efeito aumenta com nível do slot
>
> **Jogo Digital:**
>
> - **GameplayEffect** define nível base do spell
> - **GameplayEffect** calcula dano/efeito baseado no slot usado
> - **GameplayAbility** permite escolher nível do slot (upcast)
>
> **🎯 Exemplo: Fireball:**
>
> 1. **Jogador:** Escolhe spell "Fireball" nível 3 → **GameplayAbility** (ação)
> 2. **Sistema:** Valida se tem spell slot nível 3 → **GameplayAbility** (validação)
> 3. **Sistema:** Jogador escolhe área → **GameplayAbility** (targeting)
> 4. **Sistema:** Aplica "Fireball Effect" nível 3 → **GameplayEffect** (regra)
> 5. **Sistema:** Calcula dano 8d6 → **GameplayEffect** (fórmula)
> 6. **Sistema:** Se upcast para nível 4, dano = 9d6 → **GameplayEffect** (scaling)
> 7. **Sistema:** Aplica dano em todos os alvos na área → **AttributeSet** (atualiza HP)
> 8. **Sistema:** Consome spell slot → **AttributeSet** (atualiza slots)

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Habilidades de Classe</b></summary>

> ### **Action Surge (Fighter):**
>

> **RPG de Mesa:**
>
> - "Você ganha uma ação extra neste turno"
> - Usa 1x por short rest
>
> **Jogo Digital:**
>
> - **GameplayAbility** valida se está disponível (cooldown)
> - **GameplayEffect** aplica "+1 ação extra"
> - **AttributeSet** atualiza "ActionsAvailable: 1 → 2"
> - **GameplayEffect** aplica cooldown "1x por short rest"
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">😤 Rage (Barbarian)</summary>

> **RPG de Mesa:**
>
> - "+2 dano em ataques corpo a corpo"
> - Resistência a dano físico
> - Duração: 1 minuto ou até perder concentração
>
> **Jogo Digital:**
>
> - **GameplayAbility** ativa Rage
> - **GameplayEffect** aplica "+2 dano corpo a corpo"
> - **GameplayEffect** aplica "50% redução de dano físico"
> - **AttributeSet** atualiza modificadores
> - **GameplayEffect** gerencia duração (1 minuto ou até perder concentração)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🗡️ Sneak Attack (Rogue)</summary>

> **RPG de Mesa:**
>
> - "Dano extra se tiver vantagem ou aliado próximo ao alvo"
> - Dano aumenta com nível (1d6 a cada 2 níveis)
>
> **Jogo Digital:**
>
> - **GameplayAbility** valida condições (vantagem ou aliado próximo)
> - **GameplayEffect** calcula dano extra baseado no nível
> - **GameplayEffect** aplica dano extra no ataque
> - **AttributeSet** atualiza HP do alvo
>
> **🎯 Vantagem do GAS:**
>
> - Cada habilidade é um **GameplayAbility**
> - Efeitos são **GameplayEffects** reutilizáveis
> - Sistema gerencia cooldowns e custos automaticamente
> - Pode combinar múltiplas habilidades

</details>

---

## 🌐 Multiplayer: Sincronização e Autoridade

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Princípios de Multiplayer no GAS</b></summary>

> ### **Autoridade do Servidor (Server Authority)**
>

> **Regra Fundamental:**
>
> - ✅ **Servidor é autoridade:** Todas as decisões importantes acontecem no servidor
> - ✅ **Cliente é visualização:** Cliente apenas mostra o que o servidor autoriza
> - ✅ **Validação sempre:** Servidor valida todas as ações do cliente
> - ❌ **Nunca confiar no cliente:** Cliente pode ser modificado (cheating)
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Como GAS Gerencia Multiplayer</summary>

> **1. AttributeSet - Replicação Automática:**
>
> - **Servidor:** Calcula valores (HP, atributos, modificadores)
> - **Cliente:** Recebe valores replicados automaticamente
> - **Sincronização:** GAS replica automaticamente quando valores mudam
> - **Eventos:** Cliente recebe notificações quando valores mudam (OnRep)
>
> **2. GameplayEffect - Aplicação Autoritativa:**
>
> - **Servidor:** Aplica efeitos (dano, buffs, debuffs)
> - **Cliente:** Recebe notificação de efeitos aplicados
> - **Validação:** Servidor valida se efeito pode ser aplicado
> - **Duração:** Servidor gerencia duração de efeitos
>
> **3. GameplayAbility - Execução Autoritativa:**
>
> - **Cliente:** Solicita ação (pressiona botão)
> - **Servidor:** Valida e executa ação
> - **Resultado:** Servidor aplica resultado e replica para clientes
> - **Feedback:** Cliente recebe feedback visual do resultado
>
> **🎯 Vantagem do GAS:**
>
> - Replicação automática de atributos
> - Validação automática de ações
> - Sincronização de estados garantida
> - Prevenção de cheating nativa

</details>

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Exemplo: Ataque em Multiplayer</b></summary>

> ### **Fluxo Completo:**
>

> **1. Cliente (Jogador A):**
>
> - Pressiona botão de ataque → **GameplayAbility** (solicitação)
> - Envia RPC para servidor → **Network** (comunicação)
>
> **2. Servidor:**
>
> - Recebe solicitação de ataque → **GameplayAbility** (validação)
> - Valida se jogador pode atacar → **GameplayAbility** (autoridade)
> - Calcula acerto usando regras D&D → **GameplayEffect** (fórmula)
> - Lê valores "Strength: 16 (+3), Proficiency: +3" → **AttributeSet** (valores)
> - Calcula 12 + 3 + 3 = 18 vs AC 15 → **Acertou!**
> - Calcula dano 1d8 + 3 = 8 → **GameplayEffect** (fórmula)
> - Aplica dano no alvo → **AttributeSet** (atualiza HP: 10 → 2)
>
> **3. Replicação:**
>
> - Servidor replica HP atualizado → **AttributeSet** (replicação)
> - Todos os clientes recebem HP atualizado → **Network** (sincronização)
> - Cliente (Jogador B) vê HP mudar → **UI** (feedback visual)
>
> **4. Feedback Visual:**
>
> - Servidor envia feedback de acerto → **GameplayAbility** (notificação)
> - Todos os clientes mostram efeito visual → **UI** (feedback)
>
> **🎯 Pontos Importantes:**
>
> - ✅ Cálculo acontece no servidor (autoridade)
> - ✅ Cliente apenas solicita ação
> - ✅ Todos os clientes veem o mesmo resultado
> - ✅ Impossível trapacear (servidor valida tudo)
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔥 Exemplo: Spell Fireball em Multiplayer</b></summary>

> ### **Fluxo Completo:**
>

> **1. Cliente (Jogador A):**
>
> - Pressiona botão "Fireball" → **GameplayAbility** (solicitação)
> - Escolhe área (raio de 6 metros) → **GameplayAbility** (targeting)
> - Envia RPC para servidor → **Network** (comunicação)
>
> **2. Servidor:**
>
> - Recebe solicitação de Fireball → **GameplayAbility** (validação)
> - Valida se tem spell slot disponível → **GameplayAbility** (autoridade)
> - Valida se área é válida → **GameplayAbility** (autoridade)
> - Identifica todos os alvos na área → **GameplayAbility** (detecção)
> - Para cada alvo, aplica "Fireball Damage Effect" → **GameplayEffect** (regra)
> - Cada alvo faz saving throw → **GameplayEffect** (condição)
> - Calcula dano 8d6 = 28 → **GameplayEffect** (fórmula)
> - Aplica dano (total ou metade) → **AttributeSet** (atualiza HP)
> - Consome spell slot → **AttributeSet** (atualiza slots)
>
> **3. Replicação:**
>
> - Servidor replica HP de todos os alvos → **AttributeSet** (replicação)
> - Servidor replica spell slots do jogador → **AttributeSet** (replicação)
> - Todos os clientes recebem atualizações → **Network** (sincronização)
>
> **4. Feedback Visual:**
>
> - Servidor envia evento de explosão → **GameplayAbility** (notificação)
> - Todos os clientes mostram explosão visual → **UI** (feedback)
> - Todos os clientes mostram dano nos alvos → **UI** (feedback)
>
> **🎯 Pontos Importantes:**
>
> - ✅ Detecção de área acontece no servidor (autoridade)
> - ✅ Saving throws calculados no servidor (autoridade)
> - ✅ Dano aplicado no servidor (autoridade)
> - ✅ Todos os clientes veem o mesmo resultado
> - ✅ Impossível trapacear (servidor valida tudo)
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💀 Exemplo: Condição Envenenado em Multiplayer</b></summary>

> ### **Fluxo Completo:**
>

> **1. Servidor (Goblin ataca Jogador A):**
>
> - Goblin aplica ataque envenenado → **GameplayAbility** (ação)
> - Cria efeito "Poison Effect" → **GameplayEffect** (regra)
> - Solicita saving throw de Constitution → **GameplayEffect** (condição)
> - Jogador A falha (10 < 12) → Aplica condição "Envenenado"
> - Modifica atributos "-1 em todos os checks" → **AttributeSet** (atualiza)
>
> **2. Replicação:**
>
> - Servidor replica modificadores atualizados → **AttributeSet** (replicação)
> - Servidor replica condição "Envenenado" → **GameplayEffect** (replicação)
> - Todos os clientes recebem atualizações → **Network** (sincronização)
>
> **3. Cliente (Jogador A):**
>
> - Recebe notificação de condição → **GameplayEffect** (notificação)
> - Mostra efeito visual de envenenado → **UI** (feedback visual)
> - Aplica desvantagem em checks automaticamente → **GameplayEffect** (regra)
>
> **4. Cliente (Jogador B):**
>
> - Recebe notificação de condição do Jogador A → **GameplayEffect** (notificação)
> - Mostra efeito visual no Jogador A → **UI** (feedback visual)
> - Vê que Jogador A está envenenado → **UI** (informação)
>
> **5. Servidor (A cada turno):**
>
> - Permite novo saving throw → **GameplayEffect** (duração)
> - Jogador A passa no saving throw → Remove condição
> - Replica remoção de condição → **GameplayEffect** (replicação)
> - Todos os clientes recebem atualização → **Network** (sincronização)
>
> **🎯 Pontos Importantes:**
>
> - ✅ Condições aplicadas no servidor (autoridade)
> - ✅ Modificadores replicados automaticamente
> - ✅ Todos os clientes veem condições dos outros jogadores
> - ✅ Duração gerenciada no servidor (autoridade)
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Prevenção de Cheating</b></summary>

> ### **Como GAS Previne Cheating:**
>

> **1. Autoridade do Servidor:**
>
> - ✅ Todas as ações são validadas no servidor
> - ✅ Cliente não pode modificar valores diretamente
> - ✅ Servidor é a única fonte de verdade
>
> **2. Validação de GameplayAbility:**
>
> - ✅ Servidor valida se ação é permitida
> - ✅ Servidor valida se tem recursos (spell slots, ações)
> - ✅ Servidor valida se condições são atendidas
>
> **3. Replicação de AttributeSet:**
>
> - ✅ Valores são calculados no servidor
> - ✅ Cliente recebe apenas valores replicados
> - ✅ Cliente não pode modificar valores diretamente
>
> **4. Validação de GameplayEffect:**
>
> - ✅ Efeitos são aplicados no servidor
> - ✅ Servidor valida se efeito pode ser aplicado
> - ✅ Duração é gerenciada no servidor
>
> **🎯 Exemplo de Tentativa de Cheating:**
>
> **Cliente tenta:**
>
> - Modificar HP diretamente → **FALHA:** AttributeSet replica do servidor
> - Aplicar buff sem custo → **FALHA:** Servidor valida custo
> - Usar spell sem slot → **FALHA:** Servidor valida spell slots
> - Aplicar dano infinito → **FALHA:** Servidor calcula dano
>
> **Resultado:**
>
> - ✅ Servidor sempre tem autoridade
> - ✅ Cliente não pode trapacear
> - ✅ Todos os jogadores veem o mesmo resultado
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Sincronização de Estados</b></summary>

> ### **Como Estados São Sincronizados:**
>

> **1. AttributeSet - Sincronização Automática:**
>
> - **Servidor:** Calcula valores (HP, atributos, modificadores)
> - **Replicação:** GAS replica automaticamente quando valores mudam
> - **Cliente:** Recebe valores e atualiza UI automaticamente
> - **Eventos:** Cliente recebe OnRep quando valores mudam
>
> **2. GameplayEffect - Sincronização de Efeitos:**
>
> - **Servidor:** Aplica efeitos (buffs, debuffs, condições)
> - **Replicação:** GAS replica efeitos ativos
> - **Cliente:** Recebe lista de efeitos ativos
> - **Visual:** Cliente mostra efeitos visuais baseados em efeitos ativos
>
> **3. GameplayAbility - Sincronização de Ações:**
>
> - **Servidor:** Executa ações e valida resultados
> - **Replicação:** GAS replica resultados de ações
> - **Cliente:** Recebe feedback de ações executadas
> - **Visual:** Cliente mostra feedback visual de ações
>
> **🎯 Vantagem do GAS:**
>
> - Sincronização automática de estados
> - Todos os clientes veem o mesmo estado
> - Impossível ter estados diferentes entre clientes
> - Prevenção de desincronização nativa
>
</details>
---

## 📚 Referências e Recursos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links Úteis</b></summary>

> ### **D&D 5e:**
>

> - [D&D Beyond Basic Rules](https://www.dndbeyond.com/sources/dnd/br-2024) - Regras oficiais de D&D 5e
> - [D&D 5e SRD](https://dnd.wizards.com/resources/systems-reference-document) - System Reference Document
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎮 Unreal Engine GAS</summary>

> - [GAS Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-ability-system-for-unreal-engine) - Documentação oficial do GAS
> - [GAS Community Wiki](https://github.com/tranek/GASDocumentation) - Documentação da comunidade

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Projeto</summary>

> - [ARCHITECTURE.md](../../ARCHITECTURE.md) - Arquitetura do projeto
> - [GDD](gdd.md) - Game Design Document
> - [Regras D&D 5e](dnd-rules/) - Regras implementadas

</details>

---

## ✅ Resumo: Do RPG de Mesa para o Jogo

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Princípios Fundamentais</b></summary>

> ### **1. Fidelidade às Regras**
>

> - ✅ Todas as regras oficiais de D&D 5e são mantidas
> - ✅ Fórmulas de cálculo são idênticas
> - ✅ Condições e efeitos funcionam igual
>
</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🤖 Automação Inteligente</summary>

> - ✅ Sistema calcula automaticamente (não precisa rolar dados manualmente)
> - ✅ Aplica modificadores automaticamente
> - ✅ Gerencia duração de efeitos automaticamente

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👁️ Feedback Visual</summary>

> - ✅ Jogador vê resultados de rolagens (opcional)
> - ✅ Efeitos visuais para condições
> - ✅ Feedback de acerto/erro

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Action RPG: Colisão Real</summary>

> - ✅ Combate é em tempo real (não turn-based)
> - ✅ Colisão física real (não abstrata)
> - ✅ Projéteis têm física real

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏗️ GAS: Os 3 Pilares</summary>

> - ✅ **AttributeSet** = Ficha do personagem (armazena valores)
> - ✅ **GameplayEffect** = Livro de regras (define o que acontece)
> - ✅ **GameplayAbility** = Ação do jogador (executa ações)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌐 Multiplayer: Autoridade do Servidor</summary>

> - ✅ Servidor é autoridade (todas as decisões importantes)
> - ✅ Replicação automática de atributos e efeitos
> - ✅ Validação automática de ações
> - ✅ Prevenção de cheating nativa

</details>

> **🎯 Resultado Final:**
>
> Um jogo Action RPG multiplayer que mantém todas as regras de D&D 5e, executa tudo automaticamente em tempo real com colisão física real, e garante sincronização perfeita entre todos os jogadores.
>
> **📌 Nota Importante:**
>
> Este documento descreve a **arquitetura futura** usando GAS. O projeto atual usa:
>
> - ✅ `UCharacterDataComponent` com replicação (`DOREPLIFETIME`) para dados em runtime
> - 13 propriedades replicáveis: CharacterName, CharacterDescription, CharacterTotalLvl, SelectedRace, SelectedSubrace, SelectedBackground, Proficiencies, AvailableFeatures, SelectedFeat, SelectedSkill, CustomAbilityScoreChoices, RaceTraits, Languages
> - `AbilityScores` (TMap) não é replicável diretamente (limitação do Unreal Engine)
> - ✅ `UCharacterSheetComponent` como bridge component para aplicar regras
> - ✅ `UCharacterSheetDataAsset` para configuração no editor
> - 🔮 Migração futura para GAS manterá a mesma arquitetura de camadas, mas usando `AttributeSet`, `GameplayEffect` e `GameplayAbility`

---

**Última atualização:** 2024-12-27
**Versão:** 1.0.0
**Autor:** MyProject2 Team
