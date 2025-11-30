# 2.2. Sistemas de Personagem

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Sistemas de Personagem</b></summary>

> Sistema completo de criação e progressão de personagens seguindo regras oficiais D&D 5e. Todas as mecânicas seguem fielmente o Player's Handbook (PHB) da 5ª Edição.

</details>

---

## 📋 Sistema de Fichas D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Status de Implementação</b></summary>

> - ✅ Criação completa de personagem (raça, classe, background)
> - ✅ Sistema Point Buy para ability scores (27 pontos)
> - ✅ Multiclassing completo com validação de pré-requisitos
> - ✅ Features de classes (estrutura pronta)
> - ✅ Skills e Proficiencies (estrutura pronta)
> - ✅ Spellcasting (detalhado - ver [Sistema de Spellcasting](spellcasting.md))
>
> **📖 Documentação Técnica:** [Regras D&D 5e (TDD)](../../03%20-%20TDD/dnd-rules/index.md)

</details>

---

## 🎯 Atributos (Ability Scores)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Os 6 Atributos</b></summary>

> **Força (STR - Strength):**
>
> - Ataques corpo a corpo (melee)
> - Skills: Atletismo (Athletics)
> - Carregamento de peso
>
> **Destreza (DEX - Dexterity):**
>
> - AC (com armadura leve ou sem armadura)
> - Ataques à distância (ranged)
> - Skills: Acrobacia, Furtividade, Prestidigitação
> - Iniciativa em combate
>
> **Constituição (CON - Constitution):**
>
> - HP máximo (Hit Points)
> - Saving Throws de concentração
> - Resistência a venenos e doenças
>
> **Inteligência (INT - Intelligence):**
>
> - Magias de mago (Wizard)
> - Skills: Arcanismo, História, Investigação, Natureza, Religião
> - Línguas adicionais
>
> **Sabedoria (WIS - Wisdom):**
>
> - Magias de clérigo (Cleric) e druida (Druid)
> - Skills: Adestrar Animais, Intuição, Medicina, Percepção, Sobrevivência
> - Percepção passiva
>
> **Carisma (CHA - Charisma):**
>
> - Magias de bardo (Bard), paladino (Paladin) e bruxo (Warlock)
> - Skills: Atuação, Enganação, Intimidação, Persuasão
> - Interação social

</details>

---

## 🧮 Modificadores de Atributos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📐 Cálculo de Modificadores</b></summary>

> **Fórmula Oficial D&D 5e:**
>
> ```
> Modifier = floor((Ability Score - 10) / 2)
> ```
>
> **Tabela de Referência:**
>
> | Score | Modifier |
> |-------|----------|
> | 1     | -5       |
> | 2-3   | -4       |
> | 4-5   | -3       |
> | 6-7   | -2       |
> | 8-9   | -1       |
> | 10-11 | 0        |
> | 12-13 | +1       |
> | 14-15 | +2       |
> | 16-17 | +3       |
> | 18-19 | +4       |
> | 20    | +5       |
>
> **Exemplos:**
>
> - STR 8 → Modifier = -1
> - STR 15 → Modifier = +2
> - STR 18 → Modifier = +4
>
> **📖 Ver também:** [Ability Scores (TDD)](../../03%20-%20TDD/dnd-rules/ability-scores.md)

</details>

---

## 📈 Cálculo de Ability Scores Finais

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔢 Fórmula de Cálculo</b></summary>

> **Fórmula Oficial:**
>
> ```
> FinalScore = BASE_ABILITY_SCORE (8) + RacialBonuses + PointBuyAllocation + ASI
> ```
>
> **Ordem de Aplicação:**
>
> 1. **BASE_ABILITY_SCORE:** Valor base fixo = **8** (reset inicial)
> 2. **RacialBonuses:** Bônus da raça/sub-raça (ex: Dwarf +2 CON)
> 3. **PointBuyAllocation:** Alocação do Point Buy (0-7 pontos, resultando em scores 8-15)
> 4. **ASI:** Ability Score Improvements (de level up, níveis 4, 8, 12, 16, 19)
>
> **Faixas de Valores:**
>
> - **Point Buy:** 8-15 (antes de bônus raciais)
> - **Após Bônus Raciais:** 8-17 (tipicamente)
> - **Máximo com ASI:** 20 (limite máximo D&D 5e)
>
> **Exemplo:**
>
> - Reset: 8 (BASE_ABILITY_SCORE)
> - Racial: +2 (Dwarf Constitution) → 10
> - Point Buy: +7 (alocação para Strength) → 15
> - **Final Strength:** 8 + 0 (racial) + 7 (point buy) = 15
> - **Final Constitution:** 8 + 2 (racial) + 0 (point buy) = 10
>
> **📖 Pseudocódigo:** Ver [Cálculo de Atributos Finais](../../pseudocodigo/atributos-finais.md)
>
> **📖 Ver também:** [Ability Scores (TDD)](../../03%20-%20TDD/dnd-rules/ability-scores.md) | [Point Buy System (TDD)](../../03%20-%20TDD/dnd-rules/point-buy.md)

</details>

---

## ⬆️ Ability Score Improvements (ASI)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Níveis de ASI</b></summary>

> **Classes recebem ASI nos níveis:** 4, 8, 12, 16, 19
>
> **Opções:**
>
> - **+2 em um atributo** OU
> - **+1 em dois atributos**
>
> **Exceções:**
>
> - **Fighter/Rogue** recebem ASI extra nos níveis: 6, 10, 14
>
> **Limite Máximo:**
>
> - Ability Score máximo = **20** (sem itens mágicos)
> - ASI não pode exceder 20
>
> **Exemplo (Fighter nível 4):**
>
> - Opção 1: STR +2 (de 16 para 18)
> - Opção 2: STR +1 e DEX +1 (de 16 para 17 e de 14 para 15)
>
> **📖 Ver também:** [Level Up (TDD)](../../03%20-%20TDD/dnd-rules/level-up.md)

</details>

---

## 🎯 Proficiências (Proficiencies)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Tipos de Proficiências</b></summary>

> **Proficiency Bonus:**
>
> - Baseado no **Total Level** (soma de todos os níveis de classes)
> - Fórmula: `ProficiencyBonus = 2 + floor((TotalLevel - 1) / 4)`
>
> | Total Level | Proficiency Bonus |
> |-------------|-------------------|
> | 1-4         | +2                |
> | 5-8         | +3                |
> | 9-12        | +4                |
> | 13-16       | +5                |
> | 17-20       | +6                |
>
> **Tipos de Proficiências:**
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📚 Skills (18 Skills D&D 5e)</summary>
>
> > **Força (STR):**
> >
> > - Atletismo (Athletics)
> >
> > **Destreza (DEX):**
> >
> > - Acrobacia (Acrobatics)
> > - Furtividade (Stealth)
> > - Prestidigitação (Sleight of Hand)
> >
> > **Inteligência (INT):**
> >
> > - Arcanismo (Arcana)
> > - História (History)
> > - Investigação (Investigation)
> > - Natureza (Nature)
> > - Religião (Religion)
> >
> > **Sabedoria (WIS):**
> >
> > - Adestrar Animais (Animal Handling)
> > - Intuição (Insight)
> > - Medicina (Medicine)
> > - Percepção (Perception)
> > - Sobrevivência (Survival)
> >
> > **Carisma (CHA):**
> >
> > - Atuação (Performance)
> > - Enganação (Deception)
> > - Intimidação (Intimidation)
> > - Persuasão (Persuasion)
> >
> > **Cálculo de Skill Check:**
> >
> > ```
> > SkillCheck = d20 + AbilityModifier + ProficiencyBonus (se proficiente)
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🛡️ Saving Throws</summary>
>
> > Cada classe tem proficiência em **2 Saving Throws**:
> >
> > - **Força (STR):** Resistir a efeitos físicos (empurrões, quedas)
> > - **Destreza (DEX):** Esquivar de efeitos (explosões, armadilhas)
> > - **Constituição (CON):** Resistir a venenos, doenças, concentração
> > - **Inteligência (INT):** Resistir a efeitos mentais (ilusões)
> > - **Sabedoria (WIS):** Resistir a efeitos mentais (encantamentos, medo)
> > - **Carisma (CHA):** Resistir a efeitos de banimento, possessão
> >
> > **Cálculo de Saving Throw:**
> >
> > ```
> > SavingThrow = d20 + AbilityModifier + ProficiencyBonus (se proficiente)
> > ```
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Armor e Weapon Proficiencies</summary>
>
> > **Armor Proficiencies:**
> >
> > - Light Armor (Armadura Leve)
> > - Medium Armor (Armadura Média)
> > - Heavy Armor (Armadura Pesada)
> > - Shields (Escudos)
> >
> > **Weapon Proficiencies:**
> >
> > - Simple Weapons (Armas Simples)
> > - Martial Weapons (Armas Marciais)
> > - Specific Weapons (Armas Específicas)
> >
> > **Consequências:**
> >
> > - Sem proficiência em armadura: desvantagem em todas as rolagens
> > - Sem proficiência em arma: não adiciona Proficiency Bonus ao ataque
>
> </details>
>
> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔧 Tool Proficiencies</summary>
>
> > **Tipos:**
> >
> > - Artisan's Tools (Ferramentas de Artesão)
> > - Musical Instruments (Instrumentos Musicais)
> > - Gaming Sets (Conjuntos de Jogos)
> > - Vehicles (Veículos)
> >
> > **Uso:**
> >
> > - Permitem fazer certas ações com vantagem
> > - Algumas features de classe requerem proficiência em tools específicas
>
> </details>
>
> **📖 Ver também:** [ProficiencyDataTable](../../../../Content/Data/DataTable/ProficiencyDataTable.json) | [SkillDataTable](../../../../Content/Data/DataTable/SkillDataTable.json)

</details>

---

## 💡 Exemplos Práticos de Skills

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Cenários da Campanha Phandelver</b></summary>

> **Exemplo 1: Rogue Usa Furtividade (Stealth)**
>
> **Situação:** Rogue nível 2 (DEX +3, proficiency +2) tenta se aproximar furtivamente de goblins em Cragmaw Hideout.
>
> **Execução:**
>
> 1. Rogue ativa ação **Furtividade**
> 2. **Skill Check:** d20 + 3 (DEX) + 2 (proficiency) = d20+5
> 3. Rola 14, total **19**
> 4. **DC:** 15 (Percepção passiva dos goblins)
> 5. **Resultado:** **Sucesso!** (19 > 15)
> 6. Rogue se move furtivamente sem ser detectado
>
> **Resultado:** Rogue pode se aproximar para ataque furtivo ou emboscada.
>
> **Exemplo 2: Clérigo Usa Percepção (Perception)**
>
> **Situação:** Clérigo nível 1 (WIS +3, proficiency +2) explora masmorra escura procurando armadilhas.
>
> **Execução:**
>
> 1. Clérigo faz teste de **Percepção** ativa
> 2. **Skill Check:** d20 + 3 (WIS) + 2 (proficiency) = d20+5
> 3. Rola 12, total **17**
> 4. **DC:** 15 (dificuldade de detectar armadilha)
> 5. **Resultado:** **Sucesso!** (17 > 15)
> 6. Clérigo detecta armadilha de poço antes de pisar
>
> **Resultado:** Grupo evita armadilha e pode desarmá-la ou contorná-la.
>
> **Exemplo 3: Fighter Usa Atletismo (Athletics)**
>
> **Situação:** Fighter nível 1 (STR +3, proficiency +2) precisa escalar parede de 6m em Cragmaw Hideout.
>
> **Execução:**
>
> 1. Fighter faz teste de **Atletismo**
> 2. **Skill Check:** d20 + 3 (STR) + 2 (proficiency) = d20+5
> 3. Rola 8, total **13**
> 4. **DC:** 15 (dificuldade de escalada)
> 5. **Resultado:** **Falha!** (13 < 15)
> 6. Fighter cai, sofre 1d6 de dano de queda = 4 de dano
>
> **Resultado:** Fighter precisa tentar novamente ou encontrar outra rota.
>
> **Exemplo 4: Wizard Usa Investigação (Investigation)**
>
> **Situação:** Wizard nível 3 (INT +4, proficiency +2) examina porta secreta em Wave Echo Cave.
>
> **Execução:**
>
> 1. Wizard faz teste de **Investigação**
> 2. **Skill Check:** d20 + 4 (INT) + 2 (proficiency) = d20+6
> 3. Rola 15, total **21**
> 4. **DC:** 20 (dificuldade de encontrar mecanismo secreto)
> 5. **Resultado:** **Sucesso!** (21 > 20)
> 6. Wizard encontra alavanca escondida e abre passagem secreta
>
> **Resultado:** Grupo descobre área secreta com tesouro adicional.
>
> **Exemplo 5: Bard Usa Persuasão (Persuasion)**
>
> **Situação:** Bard nível 2 (CHA +3, proficiency +2) tenta convencer NPC em Phandalin a dar informação.
>
> **Execução:**
>
> 1. Bard faz teste de **Persuasão**
> 2. **Skill Check:** d20 + 3 (CHA) + 2 (proficiency) = d20+5
> 3. Rola 18, total **23**
> 4. **DC:** 15 (NPC é amigável, DC baixo)
> 5. **Resultado:** **Sucesso!** (23 > 15)
> 6. NPC fornece informação sobre Redbrands e localização do esconderijo
>
> **Resultado:** Grupo obtém informação valiosa sem precisar de combate ou roubo.

</details>

---

## 📊 Tabela de Experiência (XP) e Curvas de Nível

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📈 Progressão de XP</b></summary>

> **Tabela Oficial D&D 5e (Níveis 1-5 - Escopo da Campanha):**
>
> | Level | XP Required | Total XP |
> |-------|-------------|----------|
> | 1     | 0           | 0        |
> | 2     | 300         | 300      |
> | 3     | 900         | 1,200    |
> | 4     | 2,700       | 3,900    |
> | 5     | 6,500       | 10,400   |
>
> **Sistema de Level Up:**
>
> - Level up automático ao atingir XP necessário
> - XP é ganho após combates, quests e desafios
> - Seguindo tabelas oficiais da campanha Phandelver
>
> **📖 Ver também:** [Level Up (TDD)](../../03%20-%20TDD/dnd-rules/level-up.md)

</details>

---

## ⬆️ Progressão de Níveis (Level Up)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔓 O Que Ganha em Cada Nível</b></summary>

> **Ao fazer Level Up, o personagem ganha:**
>
> 1. **Features de Classe** (conforme tabela da classe)
> 2. **HP Adicional** (Hit Die + CON modifier)
> 3. **ASI ou Feat** (nos níveis 4, 8, 12, 16, 19)
> 4. **Spell Slots** (se for spellcaster)
> 5. **Cantrips** (se for spellcaster, em níveis específicos)
>
> **Features por Nível:**
>
> - Cada classe tem features específicas em cada nível
> - Features são desbloqueadas conforme o nível da classe
> - Em multiclassing, features são calculadas por classe individual
>
> **📖 Pseudocódigo:** Ver [Sistema de Level Up](../../pseudocodigo/level-up.md)
>
> **📖 Ver também:** [Level Up (TDD)](../../03%20-%20TDD/dnd-rules/level-up.md) | [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json)

</details>

---

## ❤️ Hit Points (HP) e Hit Dice

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💚 Sistema de HP</b></summary>

> **Cálculo de HP Máximo (Regra Customizada):**
>
> **Nível 1 (Fixo):**
>
> ```
> Level1HP = HitDie + Constitution Modifier
> ```
>
> **Níveis 2+ (Rolagem com Mínimo Garantido):**
>
> ```
> Roll = RollHitDie()
> HalfDie = ceil(HitDie / 2)
>
> if Roll > HalfDie:
>     LevelHP = Roll + Constitution Modifier
> else:
>     LevelHP = HalfDie + Constitution Modifier
>
> MaxHP = sum of all level HP gains
> ```
>
> **Regra:**
>
> - A cada nível (2+), rola o Hit Die
> - Se rolar **mais que a metade**: usa o valor rolado + CON modifier
> - Se rolar **menos ou igual à metade**: usa metade (arredondado para cima) + CON modifier
> - Garante mínimo de metade do dado, mas permite valores maiores com sorte
>
> **Hit Dice por Classe:**
>
> - **d6:** Sorcerer, Wizard (metade = 3)
> - **d8:** Bard, Cleric, Druid, Monk, Rogue, Warlock (metade = 4)
> - **d10:** Fighter, Paladin, Ranger (metade = 5)
> - **d12:** Barbarian (metade = 6)
>
> **Exemplo (Fighter nível 3, CON +2, d10):**
>
> - **Level 1:** 10 (d10 máximo) + 2 = **12 HP** (fixo)
> - **Level 2:** Rola d10
>   - Se rolar 1-5: 5 (metade) + 2 = **7 HP adicional** → Total: 19 HP
>   - Se rolar 6-10: valor rolado (ex: 8) + 2 = **10 HP adicional** → Total: 22 HP
> - **Level 3:** Rola d10 novamente (mesma lógica)
>   - Se rolar 1-5: 5 + 2 = **7 HP adicional**
>   - Se rolar 6-10: valor rolado + 2
>
> **Vantagem da Regra:**
>
> - Garante mínimo de metade do dado (evita HP muito baixo)
> - Permite valores maiores com sorte (recompensa rolagens boas)
> - Mais emocionante que sempre pegar metade fixa
>
> **Uso de Hit Dice (Short Rest):**
>
> - Personagem pode gastar Hit Dice para recuperar HP
> - Recupera HP = rolagem de Hit Die + CON modifier
> - Recupera todos os Hit Dice em Long Rest
>
> **📖 Ver também:** [Level Up (TDD)](../../03%20-%20TDD/dnd-rules/level-up.md)

</details>

---

## 🔄 Multiclassing

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Sistema de Multiclassing</b></summary>

> **Pré-requisitos:**
>
> - Cada classe tem ability score prerequisites
> - Deve atender pré-requisitos da classe atual E da nova classe
> - Pré-requisitos são baseados nos **Final Ability Scores** (após bônus raciais e ASI)
>
> **Pré-requisitos por Classe:**
>
> - **Barbarian:** STR 13
> - **Bard:** CHA 13
> - **Cleric:** WIS 13
> - **Druid:** WIS 13
> - **Fighter:** STR 13 **OU** DEX 13
> - **Monk:** DEX 13 **E** WIS 13
> - **Paladin:** STR 13 **E** CHA 13
> - **Ranger:** DEX 13 **E** WIS 13
> - **Rogue:** DEX 13
> - **Sorcerer:** CHA 13
> - **Warlock:** CHA 13
> - **Wizard:** INT 13
>
> **Cálculo de Nível Total:**
>
> ```
> TotalLevel = sum(levels in all classes)
> MaximumTotalLevel = 20
> ```
>
> **Proficiencies ao Multiclassar:**
>
> - Ganha proficiências **LIMITADAS** (não todas as starting proficiencies)
> - Ganha proficiência em **UMA skill** da nova classe
> - Armor/Weapon proficiencies conforme classe
>
> **Spell Slots em Multiclassing:**
>
> - Full Casters (Bard, Cleric, Druid, Sorcerer, Wizard): contam como 1 level
> - Half Casters (Paladin, Ranger): contam como 0.5 level (arredondado para baixo)
> - Warlock: separado (Pact Magic, não combina)
> - Fórmula: `CasterLevel = FullCasterLevels + floor(HalfCasterLevels / 2)`
>
> **📖 Ver também:** [Multiclassing (TDD)](../../03%20-%20TDD/dnd-rules/multiclassing.md)

</details>

---

## 🔮 Spellcasting (Básico)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✨ Sistema de Magias</b></summary>

> **Spell Save DC (Classe de Dificuldade):**
>
> ```
> SpellSaveDC = 8 + ProficiencyBonus + SpellcastingAbilityModifier
> ```
>
> **Spell Attack Modifier:**
>
> ```
> SpellAttackModifier = ProficiencyBonus + SpellcastingAbilityModifier
> ```
>
> **Spellcasting Ability por Classe:**
>
> - **Bard, Paladin, Sorcerer, Warlock:** Charisma (CHA)
> - **Cleric, Druid, Ranger:** Wisdom (WIS)
> - **Wizard:** Intelligence (INT)
>
> **Spell Slots:**
>
> - Full Casters: Tabela completa de spell slots (1-9)
> - Half Casters: Tabela limitada (1-5)
> - Warlock: Pact Magic (slots separados, recuperam em Short Rest)
>
> **Cantrips:**
>
> - Magias de nível 0, não gastam spell slots
> - Número conhecido varia por classe e nível
>
> **Spells Known vs Spells Prepared:**
>
> - **Known (Bard, Ranger, Sorcerer, Warlock):** Lista fixa, não pode mudar exceto em level up
> - **Prepared (Cleric, Druid, Paladin, Wizard):** Prepara spells da lista de classe após Long Rest
> - Número preparado = SpellcastingAbilityModifier + ClassLevel (mínimo 1)
>
> **📖 Ver também:** [Sistema de Spellcasting](spellcasting.md) - Documentação completa do GDD | [Spellcasting (TDD)](../../03%20-%20TDD/dnd-rules/spellcasting.md) - Documentação técnica

</details>

---

## 🎯 Features de Classes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔓 Features por Nível</b></summary>

> **Cada classe tem features específicas em cada nível:**
>
> - **Level 1:** Features iniciais (proficiencies, starting equipment, etc.)
> - **Level 2-3:** Features de classe base
> - **Level 3:** Subclass selection (Archetype)
> - **Level 4+:** Features conforme progressão da classe e subclass
>
> **Exemplos de Features:**
>
> - **Fighter:** Action Surge (nível 2), Second Wind (nível 1)
> - **Rogue:** Sneak Attack (nível 1), Cunning Action (nível 2)
> - **Wizard:** Arcane Recovery (nível 1), Spell Mastery (nível 18)
> - **Paladin:** Divine Smite (nível 2), Lay on Hands (nível 1)
>
> **Features de Raça:**
>
> - Cada raça tem features específicas (ex: Darkvision, Fey Ancestry)
> - Features de sub-raça adicionais
>
> **Features de Background:**
>
> - Skills proficiencies
> - Tool proficiencies
> - Languages
> - Feature especial (ex: Criminal Contact)
>
> **📖 Ver também:** [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json) | [ClassDataTable](../../../../Content/Data/DataTable/ClassDataTable%20copy.json)

</details>

---

## 🎲 Feats (Talentos)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⭐ Sistema de Feats</b></summary>

> **Quando Ganhar Feat:**
>
> - Opcional: Ao invés de ASI (+2 atributo ou +1/+1), pode escolher um Feat
> - Disponível nos níveis: 4, 8, 12, 16, 19
> - Alguns feats dão +1 em atributo (ex: Resilient, Observant)
>
> **Exemplos de Feats:**
>
> - **Great Weapon Master:** +10 dano, -5 no ataque
> - **Sharpshooter:** +10 dano em ranged, -5 no ataque
> - **Lucky:** 3 rerolls por long rest
> - **Resilient:** +1 atributo + proficiência em saving throw
>
> **📖 Ver também:** [FeatDataTable](../../../../Content/Data/DataTable/FeatDataTable.json)

</details>

---

## 📚 Ordem de Criação de Personagem

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Passos de Criação</b></summary>

> **Ordem Oficial D&D Beyond (para UI/Widget):**
>
> 1. **Choose a Race** → Seleciona raça (unlocks subrace options)
> 2. **Choose a Class** → Seleciona classe (unlocks subclass options)
> 3. **Determine Ability Scores** → Point Buy, Standard Array, ou Roll
> 4. **Describe Your Character** → Background, Personality, Alignment
> 5. **Choose Equipment** → Starting equipment da classe e background
> 6. **Come Together** → Revisão final
> 7. **Beyond 1st Level** → Leveling up e progressão
>
> **📖 Ver também:** [Character Creation (TDD)](../../03%20-%20TDD/dnd-rules/character-creation.md) - Ordem técnica e oficial

</details>

---

## 🔗 Referências e Documentação Técnica

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📚 Links Relacionados</b></summary>

> **Documentação Técnica (TDD):**
>
> - [Ability Scores](../../03%20-%20TDD/dnd-rules/ability-scores.md) - Cálculo de atributos
> - [Point Buy System](../../03%20-%20TDD/dnd-rules/point-buy.md) - Sistema de distribuição de pontos
> - [Raças e Sub-raças](../../03%20-%20TDD/dnd-rules/races.md) - Bônus raciais
> - [Character Creation](../../03%20-%20TDD/dnd-rules/character-creation.md) - Ordem de criação
> - [Level Up](../../03%20-%20TDD/dnd-rules/level-up.md) - Sistema de progressão
> - [Multiclassing](../../03%20-%20TDD/dnd-rules/multiclassing.md) - Regras de multiclassing
> - [Spellcasting](../../03%20-%20TDD/dnd-rules/spellcasting.md) - Sistema completo de magias
>
> **Data Tables:**
>
> - [AbilityScoreDataTable](../../../../Content/Data/DataTable/AbilityScoreDataTable.json)
> - [RaceDataTable](../../../../Content/Data/DataTable/RaceDataTable.json)
> - [ClassDataTable](../../../../Content/Data/DataTable/ClassDataTable%20copy.json)
> - [BackgroundDataTable](../../../../Content/Data/DataTable/BackgroundDataTable%20copy.json)
> - [FeatureDataTable](../../../../Content/Data/DataTable/FeatureDataTable.json)
> - [SkillDataTable](../../../../Content/Data/DataTable/SkillDataTable.json)
> - [ProficiencyDataTable](../../../../Content/Data/DataTable/ProficiencyDataTable.json)
> - [FeatDataTable](../../../../Content/Data/DataTable/FeatDataTable.json)
> - [SpellDataTable](../../../../Content/Data/DataTable/SpellDataTable%20copy.json)
>
> **Banco de Dados:**
>
> - [Banco de Mecânicas](../banco-dados/banco-mecanicas.md) - Status de implementação

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistemas de personagem baseados em D&D 5e |
| v1.1 | 2024-12-27 | Adicionado pseudocódigo para cálculo de atributos finais, level up e recalculo de stats derivados |

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima: Sistema de Combate](sistema-combate.md)
