# 2.7. Sistema de Spellcasting (Conjuração de Magias)

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Sistema de Spellcasting</b></summary>

> Sistema completo de conjuração de magias seguindo fielmente as regras oficiais D&D 5e. Todas as mecânicas de spellcasting seguem o Player's Handbook (PHB) da 5ª Edição, adaptadas para gameplay em tempo real.

</details>

---

## 🎯 Classes Conjuradoras

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Tipos de Conjuradores</b></summary>

> **Full Casters (Conjuradores Completos):**
>
> - **Bard:** Carisma (CHA) - Magias conhecidas
> - **Cleric:** Sabedoria (WIS) - Magias preparadas
> - **Druid:** Sabedoria (WIS) - Magias preparadas
> - **Sorcerer:** Carisma (CHA) - Magias conhecidas
> - **Wizard:** Inteligência (INT) - Magias preparadas (livro de magias)
>
> **Half Casters (Meio Conjuradores):**
>
> - **Paladin:** Carisma (CHA) - Magias preparadas (níveis 2+)
> - **Ranger:** Sabedoria (WIS) - Magias conhecidas (níveis 2+)
>
> **Pact Magic (Magia de Pacto):**
>
> - **Warlock:** Carisma (CHA) - Magias conhecidas (sistema especial de slots)

</details>

---

## 📊 Spell Slots (Espaços de Magia)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Sistema de Spell Slots</b></summary>

> **Regra Oficial D&D 5e:**
>
> Spell Slots representam a energia mágica disponível para conjurar magias. Cada magia consome um spell slot do nível correspondente ou superior.
>
> **Tabela de Spell Slots (Full Casters - Níveis 1-5):**
>
> | Level | 1st | 2nd | 3rd | 4th | 5th |
> |-------|-----|-----|-----|-----|-----|
> | 1     | 2   | -   | -   | -   | -   |
> | 2     | 3   | -   | -   | -   | -   |
> | 3     | 4   | 2   | -   | -   | -   |
> | 4     | 4   | 3   | -   | -   | -   |
> | 5     | 4   | 3   | 2   | -   | -   |
>
> **Tabela de Spell Slots (Half Casters - Níveis 1-5):**
>
> | Level | 1st | 2nd |
> |-------|-----|-----|
> | 1     | -   | -   |
> | 2     | 2   | -   |
> | 3     | 3   | -   |
> | 4     | 3   | -   |
> | 5     | 4   | 2   |
>
> **Warlock (Pact Magic - Níveis 1-5):**
>
> | Level | Spell Slots | Slot Level |
> |-------|-------------|------------|
> | 1     | 1           | 1st        |
> | 2     | 2           | 1st        |
> | 3     | 2           | 2nd        |
> | 4     | 2           | 2nd        |
> | 5     | 2           | 3rd        |
>
> **Recuperação de Spell Slots:**
>
> - **Full Casters / Half Casters:** Recuperam todos os spell slots em **Long Rest** (8 horas)
> - **Warlock:** Recupera todos os spell slots em **Short Rest** (1 hora)
> - **Wizard (Arcane Recovery):** Pode recuperar alguns spell slots durante Short Rest (nível 1+)

</details>

---

## 🎲 Cantrips (Truques)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Magias de Nível 0</b></summary>

> **Regra Oficial D&D 5e:**
>
> Cantrips são magias de nível 0 que podem ser conjuradas **à vontade**, sem gastar spell slots.
>
> **Número de Cantrips Conhecidos:**
>
> | Classe | Nível 1 | Nível 4 | Nível 10 |
> |--------|---------|---------|----------|
> | Bard   | 2       | 2       | 3        |
> | Cleric | 3       | 3       | 4        |
> | Druid  | 2       | 2       | 3        |
> | Sorcerer | 4     | 4       | 5        |
> | Warlock | 2      | 2       | 3        |
> | Wizard | 3       | 3       | 4        |
>
> **Cantrips Comuns na Campanha Phandelver:**
>
> - **Fire Bolt:** Ataque à distância (1d10 de dano de fogo)
> - **Eldritch Blast:** Ataque à distância (1d10 de dano de força) - Warlock
> - **Guidance:** Bônus em skill checks (+1d4)
> - **Light:** Cria luz (útil em masmorras escuras)
> - **Mending:** Repara objetos quebrados
> - **Sacred Flame:** Ataque à distância (1d8 de dano radiante) - Cleric
> - **Shocking Grasp:** Ataque corpo a corpo (1d8 de dano de raio)

</details>

---

## 📖 Spells Known vs Spells Prepared

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Conhecimento e Preparação</b></summary>

> **Spells Known (Magias Conhecidas):**
>
> Classes: **Bard, Ranger, Sorcerer, Warlock**
>
> - Lista **fixa** de magias conhecidas
> - Não pode mudar exceto em level up
> - Número conhecido aumenta com o nível
>
> **Spells Prepared (Magias Preparadas):**
>
> Classes: **Cleric, Druid, Paladin, Wizard**
>
> - Prepara magias da lista de classe após **Long Rest**
> - Número preparado = **SpellcastingAbilityModifier + ClassLevel** (mínimo 1)
> - Pode mudar lista preparada a cada Long Rest
>
> **Wizard (Livro de Magias):**
>
> - Conhece todas as magias do livro (começa com 6 magias nível 1)
> - Pode aprender novas magias de pergaminhos ou livros
> - Prepara magias do livro após Long Rest
>
> **Exemplo de Preparação (Cleric nível 3, WIS +3):**
>
> - Número preparado = 3 (WIS modifier) + 3 (nível) = **6 magias**
> - Escolhe 6 magias da lista de Cleric (níveis 1-2)
> - Pode mudar lista após Long Rest

</details>

---

## 🎯 Spell Save DC e Spell Attack

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Cálculo de Dificuldade</b></summary>

> **Spell Save DC (Classe de Dificuldade):**
>
> ```
> Spell Save DC = 8 + Proficiency Bonus + Spellcasting Ability Modifier
> ```
>
> **Exemplo (Wizard nível 3, INT +4, Proficiency +2):**
>
> - Spell Save DC = 8 + 2 + 4 = **14**
> - Inimigos devem rolar Saving Throw contra DC 14
>
> **Spell Attack Modifier (Modificador de Ataque de Magia):**
>
> ```
> Spell Attack Modifier = Proficiency Bonus + Spellcasting Ability Modifier
> ```
>
> **Exemplo (Wizard nível 3, INT +4, Proficiency +2):**
>
> - Spell Attack = 2 + 4 = **+6**
> - Rola d20 + 6 para acertar com magias de ataque

</details>

---

## ⚡ Componentes das Magias

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔮 Componentes Verbais, Somáticos e Materiais</b></summary>

> **Componente Verbal (V):**
>
> - Palavras ou sons específicos necessários
> - Se conjurador estiver **silenciado** (Silence spell, mordaça), não pode conjurar
> - **Adaptação Tempo Real:** Magia pode ser interrompida se conjurador for silenciado durante conjuração
>
> **Componente Somático (S):**
>
> - Gestos manuais ou corporais
> - Conjurador deve ter **pelo menos uma mão livre**
> - Se mãos estiverem atadas/agarradas, não pode conjurar
> - **Adaptação Tempo Real:** Magia pode ser interrompida se conjurador for agarrado durante conjuração
>
> **Componente Material (M):**
>
> - Objetos ou substâncias específicas
> - **Foco de Conjuração** pode substituir componentes materiais comuns
> - Componentes com **custo em ouro** ou **consumidos** não podem ser substituídos
> - **Adaptação Tempo Real:** Conjurador precisa ter foco ou componentes no inventário
>
> **Focos de Conjuração:**
>
> - **Arcane Focus:** Cajado, orbe, cristal (Wizard, Sorcerer, Warlock)
> - **Holy Symbol:** Símbolo sagrado (Cleric, Paladin)
> - **Druidic Focus:** Caule de visco, ramo de azevinho (Druid)
> - **Instrument:** Instrumento musical (Bard)

</details>

---

## ⏱️ Tempo de Conjuração

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏰ Adaptação para Tempo Real</b></summary>

> **Regra Base D&D 5e:**
>
> - **Ação:** Maioria das magias (1 ação = 6 segundos em D&D)
> - **Ação Bônus:** Magias rápidas (ex: Healing Word)
> - **Reação:** Magias em resposta a eventos (ex: Shield, Counterspell)
> - **Tempo Prolongado:** 1 minuto, 10 minutos, 1 hora, etc.
>
> **Adaptação para Tempo Real:**
>
> **Magias de Ação (1 ação):**
>
> - **Cooldown:** 6 segundos (mantém ritmo D&D de 1 round)
> - **Casting Time:** 1-2 segundos (tempo de animação de conjuração)
> - **Exemplos:** Fireball, Magic Missile, Cure Wounds
>
> **Magias de Ação Bônus:**
>
> - **Cooldown:** 3 segundos (mais rápido que ação normal)
> - **Casting Time:** 0.5-1 segundo (conjuração rápida)
> - **Exemplos:** Healing Word, Misty Step
>
> **Magias de Reação:**
>
> - **Cooldown:** 6 segundos (1 reação por round)
> - **Casting Time:** Instantâneo (resposta imediata)
> - **Exemplos:** Shield, Counterspell, Absorb Elements
>
> **Magias de Tempo Prolongado:**
>
> - **1 minuto:** Cooldown de 60 segundos (não usável em combate)
> - **10 minutos:** Cooldown de 600 segundos (rituais)
> - **1 hora:** Cooldown de 3600 segundos (rituais longos)

</details>

---

## 🎯 Alcance e Área de Efeito

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📏 Sistema de Alcance</b></summary>

> **Tipos de Alcance:**
>
> - **Pessoal:** Afeta apenas o conjurador
> - **Toque:** Requer toque físico no alvo
> - **Distância Específica:** 30 pés (9m), 60 pés (18m), 120 pés (36m), etc.
> - **Área de Efeito:** Cone, esfera, cilindro, linha, cubo
>
> **Áreas de Efeito Comuns:**
>
> - **Cone (15 pés):** 4.5m de comprimento, 4.5m de largura no final
> - **Esfera (20 pés de raio):** 6m de raio
> - **Cilindro (10 pés de raio, 40 pés de altura):** 3m de raio, 12m de altura
> - **Linha (30 pés de comprimento, 5 pés de largura):** 9m × 1.5m
> - **Cubo (15 pés):** 4.5m × 4.5m × 4.5m
>
> **Adaptação para Tempo Real:**
>
> - Sistema de **indicador visual** mostra área de efeito antes de conjurar
> - Jogador pode ajustar posição e direção da área
> - Confirmação necessária antes de conjurar (evita erros)

</details>

---

## 🧠 Concentração

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Sistema de Concentração</b></summary>

> **Regra Oficial D&D 5e:**
>
> Algumas magias requerem **concentração** para manter seus efeitos. O conjurador deve manter o foco para sustentar a magia.
>
> **Regras de Concentração:**
>
> 1. **Apenas uma magia de concentração por vez:** Se conjurar nova magia de concentração, a anterior termina
> 2. **Concentração pode ser quebrada:** Se conjurador sofrer dano, deve fazer Saving Throw de Constituição (DC 10 ou metade do dano, o que for maior)
> 3. **Falha no Saving Throw:** Magia de concentração termina imediatamente
> 4. **Ações que quebram concentração:** Ser incapacitado, morrer, conjurar outra magia de concentração
>
> **Saving Throw de Concentração:**
>
> ```
> Concentration Save = d20 + CON Modifier + Proficiency Bonus (se proficiente)
> ```
>
> **DC do Saving Throw:**
>
> ```
> DC = 10 OU (Dano Recebido / 2), o que for MAIOR
> ```
>
> **Exemplo:**
>
> - Clérigo está concentrando em **Bless** (bênção)
> - Recebe 8 de dano de um goblin
> - DC = max(10, 8/2) = **10**
> - Rola d20 + CON modifier
> - Se passar (≥10): mantém concentração
> - Se falhar (<10): **Bless** termina
>
> **Magias de Concentração Comuns:**
>
> - **Bless:** Bônus em ataques e saving throws (+1d4)
> - **Bane:** Penalidade em ataques e saving throws (-1d4)
> - **Hunter's Mark:** Dano extra em alvo específico (+1d6)
> - **Shield of Faith:** +2 AC
> - **Haste:** Velocidade dobrada, ação extra
> - **Invisibility:** Invisibilidade
> - **Fly:** Voo

</details>

---

## 📚 Magias da Campanha Phandelver

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Magias Encontradas na Campanha</b></summary>

> **Magias de Nível 1 (Disponíveis Níveis 1-2):**
>
> - **Cure Wounds:** Cura 1d8+modifier HP (toque)
> - **Healing Word:** Cura 1d4+modifier HP (ação bônus, 60 pés)
> - **Magic Missile:** 3 dardos, 1d4+1 cada, acerto automático (120 pés)
> - **Shield:** +5 AC como reação (1 round)
> - **Burning Hands:** Cone de fogo, 3d6 de dano (15 pés)
> - **Detect Magic:** Detecta magia em 30 pés (concentração, 10 minutos)
> - **Identify:** Identifica propriedades mágicas de item
> - **Sleep:** Adormece criaturas com HP total ≤ 5d8 (90 pés)
>
> **Magias de Nível 2 (Disponíveis Níveis 3-4):**
>
> - **Scorching Ray:** 3 raios de fogo, 2d6 cada (120 pés)
> - **Misty Step:** Teletransporte 30 pés (ação bônus)
> - **Spiritual Weapon:** Arma espiritual ataca, 1d8+modifier (60 pés, concentração)
> - **Hold Person:** Paralisia humanoide (concentração, 60 pés)
> - **Invisibility:** Invisibilidade (concentração, toque)
> - **Lesser Restoration:** Remove condições (cegueira, surdez, envenenado, paralisado)
>
> **Magias de Nível 3 (Disponíveis Nível 5):**
>
> - **Fireball:** Esfera de fogo, 8d6 de dano (150 pés, raio 20 pés)
> - **Lightning Bolt:** Linha de raio, 8d6 de dano (100 pés, linha 5×100 pés)
> - **Revivify:** Ressuscita criatura morta há menos de 1 minuto (componente 300gp)
> - **Counterspell:** Cancela magia sendo conjurada (reação, 60 pés)
> - **Dispel Magic:** Remove efeitos mágicos (120 pés)
>
> **Magias Usadas por Inimigos:**
>
> - **Glasstaff (Wizard):** Magic Missile, Shield, Misty Step
> - **Nezznar (Black Spider - Wizard):** Web, Magic Missile, Shield, Misty Step
> - **Flameskull:** Fireball, Ray of Frost
> - **Green Dragon:** Breath Weapon (não é magia, mas similar)

</details>

---

## 🎮 Adaptação para Tempo Real

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Conversão de Turnos para Tempo Real</b></summary>

> **Sistema de Cooldowns:**
>
> - **Magias de Ação:** Cooldown de 6 segundos (1 round)
> - **Magias de Ação Bônus:** Cooldown de 3 segundos
> - **Magias de Reação:** Cooldown de 6 segundos (1 reação por round)
> - **Cantrips:** Sem cooldown (podem ser usados continuamente)
>
> **Sistema de Casting Time:**
>
> - **Magias de Ação:** 1-2 segundos de animação de conjuração
> - **Magias de Ação Bônus:** 0.5-1 segundo de animação
> - **Magias de Reação:** Instantâneo (sem animação)
> - **Magias Ritual:** 10 minutos (não usável em combate)
>
> **Interrupção de Conjuração:**
>
> - Se conjurador sofrer dano durante casting time, magia pode ser interrompida
> - Saving Throw de Constituição para manter concentração (se aplicável)
> - Se falhar: magia é cancelada, spell slot não é gasto
>
> **Sistema de Área de Efeito:**
>
> - Indicador visual mostra área antes de conjurar
> - Jogador pode ajustar posição e direção
> - Confirmação necessária (botão ou clique)
> - Área de efeito persiste por duração da magia (se aplicável)

</details>

---

## 💡 Exemplos Práticos de Uso

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Cenários da Campanha Phandelver</b></summary>

> **Exemplo 1: Combate contra Goblins (Cragmaw Hideout)**
>
> **Situação:** Grupo encontra 4 goblins em emboscada. Clérigo decide usar **Bless** para ajudar aliados.
>
> **Execução:**
>
> 1. Clérigo gasta **1 spell slot de nível 1** para conjurar **Bless**
> 2. **Casting Time:** 1 segundo (animação de conjuração)
> 3. **Alcance:** 30 pés - Clérigo escolhe 3 aliados dentro do alcance
> 4. **Duração:** Concentração, até 1 minuto (10 rounds = 60 segundos)
> 5. **Efeito:** Aliados ganham +1d4 em ataques e saving throws
> 6. **Concentração:** Clérigo deve manter concentração. Se sofrer dano, faz Saving Throw de CON
>
> **Resultado:** Aliados têm maior chance de acertar goblins e resistir a ataques.
>
> **Exemplo 2: Combate contra Klarg (Boss Cragmaw Hideout)**
>
> **Situação:** Klarg (Bugbear) está atacando grupo. Wizard decide usar **Magic Missile** para garantir dano.
>
> **Execução:**
>
> 1. Wizard gasta **1 spell slot de nível 1** para conjurar **Magic Missile**
> 2. **Casting Time:** 1 segundo
> 3. **Alcance:** 120 pés - Klarg está a 30 pés (dentro do alcance)
> 4. **Efeito:** 3 dardos mágicos, cada um causa **1d4+1 de dano de força**
> 5. **Acerto:** Automático (não precisa rolar ataque)
> 6. **Dano Total:** 3×(1d4+1) = mínimo 6, máximo 15 de dano
>
> **Resultado:** Klarg recebe dano garantido, mesmo com AC alto.
>
> **Exemplo 3: Exploração de Masmorra Escura**
>
> **Situação:** Grupo entra em área escura da Wave Echo Cave. Clérigo usa **Light** (cantrip) para iluminar.
>
> **Execução:**
>
> 1. Clérigo conjura **Light** (cantrip, não gasta spell slot)
> 2. **Casting Time:** 1 segundo
> 3. **Alcance:** Toque - Clérigo toca sua arma
> 4. **Duração:** 1 hora (não requer concentração)
> 5. **Efeito:** Arma emite luz brilhante em raio de 20 pés, luz fraca em raio de 40 pés
>
> **Resultado:** Grupo pode ver na masmorra escura, evitando armadilhas e detectando inimigos.
>
> **Exemplo 4: Combate contra Nezznar (Black Spider)**
>
> **Situação:** Nezznar (Wizard) está conjurando **Fireball**. Wizard do grupo usa **Counterspell** para cancelar.
>
> **Execução:**
>
> 1. Nezznar começa a conjurar **Fireball** (nível 3)
> 2. Wizard do grupo usa **reação** para conjurar **Counterspell**
> 3. **Casting Time:** Instantâneo (reação)
> 4. **Alcance:** 60 pés - Nezznar está a 40 pés (dentro do alcance)
> 5. **Teste:** Wizard rola d20 + nível de magia (3) vs DC 10 + nível de magia de Nezznar
> 6. **Se passar:** **Fireball** é cancelado, Nezznar perde spell slot
> 7. **Se falhar:** **Fireball** é conjurado normalmente
>
> **Resultado:** Wizard pode proteger grupo de magia poderosa, mas gasta spell slot de nível 3.
>
> **Exemplo 5: Cura em Combate**
>
> **Situação:** Fighter está com HP baixo (5/25). Clérigo usa **Healing Word** para curar.
>
> **Execução:**
>
> 1. Clérigo gasta **1 spell slot de nível 1** para conjurar **Healing Word**
> 2. **Casting Time:** 0.5 segundo (ação bônus, rápida)
> 3. **Alcance:** 60 pés - Fighter está a 20 pés (dentro do alcance)
> 4. **Efeito:** Fighter recupera **1d4+3 HP** (WIS modifier +3)
> 5. **Dano Total:** Mínimo 4, máximo 7 HP recuperados
> 6. **Vantagem:** Clérigo ainda pode fazer ação normal (ataque, movimento, etc.)
>
> **Resultado:** Fighter recupera HP rapidamente sem perder ação do clérigo.

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Física e Interação](fisica-interacao.md)
> - [→ Próxima: Sistema de Rest](rest.md)
> **🔗 Implementação Técnica (TDD):**
>
> Para detalhes de implementação técnica, consulte:
>
> - **[TDD: Algoritmo de Spellcasting](../../02%20-%20TDD/04-regras-dnd/progressao/spellcasting-algorithm.md)** - Algoritmo técnico completo
> - **[TDD: Data Tables - Spells](../../02%20-%20TDD/05-guias/data-tables/combate/spell-datatable.md)** - SpellDataTable
> - **[TDD: API de Componentes](../../02%20-%20TDD/02-api/componentes/index.md)** - Componentes de spellcasting
>

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistema completo de spellcasting baseado em D&D 5e |

**Última atualização:** 2024-12-27
