---
title: "Guia Algorítmico - Criação de Ficha"
category: technical
subcategory: guides
tags: [algorithmic, character-creation, design-patterns, dnd-5e]
last_updated: 2024-12-27
difficulty: advanced
related: [../getting-started.md, ../../../03 - TDD/dnd-rules/character-creation.md]
---

**Navegação:** [Home](../../../../README.md) > [Documentação](index.md) > [Técnico](../../technical/index.md) > [Guias](guides/index.md) > Guia Algorítmico

# Guia Algorítmico - Criação de Ficha D&D 5e

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Visão Geral</b></summary>

> Este documento define as **regras algorítmicas** necessárias para criação de personagens D&D 5e, usando **Design Patterns em C++** para garantir código eficiente, reutilizável e manutenível.
>

> **Fonte:** [D&D Beyond - Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)
>
> **⚠️ Importante:** Este documento segue a **ordem oficial do D&D Beyond** (Race → Class → Ability Scores → Describe → Equipment), que é usada no **Widget de criação de personagem** para o jogador final. Para a ordem técnica de processamento interno no Data Asset, veja [Character Creation Steps](../../../../03 - TDD/dnd-rules/character-creation.md).
>
> **Padrões Aplicados:**
>
> - **Builder Pattern**: Construção passo a passo do personagem
> - **Strategy Pattern**: Algoritmos intercambiáveis (Point Buy, Standard Array, Roll)
> - **Template Method Pattern**: Orquestração de passos fixos
> - **Factory Pattern**: Criação de objetos complexos
> - **Observer Pattern**: Notificações de mudanças de estado
> - **Chain of Responsibility**: Validação sequencial
>
</details>
---

## 🎯 Processo de Criação (Template Method Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Algoritmo Principal: CreateCharacter()</b></summary>

> **Padrão:** Template Method - define esqueleto do algoritmo, subclasses implementam passos
>

> ```pseudocode
> ALGORITMO CreateCharacter(CharacterBuilder builder) RETORNA Character
> INÍCIO
> // Template Method: ordem fixa de passos
> PASSO 1: ChooseRace(builder)
> PASSO 2: ChooseClass(builder)
> PASSO 3: DetermineAbilityScores(builder)
> PASSO 4: DescribeCharacter(builder)
> PASSO 5: ChooseEquipment(builder)
> PASSO 6: FinalizeCharacter(builder)
>
> RETORNA builder.Build()
> FIM
> ```
>
</details>
---

## 1️⃣ PASSO 1: Choose Race (Factory Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏭 Algoritmo: SelectRace()</b></summary>

> ```pseudocode
> ALGORITMO SelectRace(RaceFactory factory, RaceName raceName) RETORNA Race
> INÍCIO
> // Factory Pattern: cria objeto Race sem conhecer implementação
> Race race = factory.CreateRace(raceName)
>

> SE race == NULL ENTÃO
> RETORNA NULL
> FIM SE
>
> // Aplica traits raciais
> ApplyRacialTraits(race)
>
> // Aplica bônus de Ability Scores
> ApplyRacialAbilityBonuses(race)
>
> // Verifica subraces disponíveis
> SE race.HasSubraces() ENTÃO
> SubraceList subraces = GetAvailableSubraces(race)
> // Retorna lista para UI mostrar dropdown
> FIM SE
>
> RETORNA race
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: ApplyRacialAbilityBonuses()</b></summary>

> ```pseudocode
> ALGORITMO ApplyRacialAbilityBonuses(Race race, AbilityScores scores) RETORNA AbilityScores
> INÍCIO
> // Strategy Pattern: diferentes raças têm diferentes bônus
> RacialBonusStrategy strategy = race.GetBonusStrategy()
>

> PARA CADA bonus EM race.GetAbilityBonuses() FAÇA
> AbilityName ability = bonus.AbilityName
> BonusValue value = bonus.Value
>
> // Aplica bônus
> scores[ability] += value
>
> // Validação: máximo 30
> SE scores[ability] > MAX_ABILITY_SCORE ENTÃO
> scores[ability] = MAX_ABILITY_SCORE
> LogWarning("Ability score excedeu máximo, ajustado para 30")
> FIM SE
> FIM PARA
>
> RETORNA scores
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Algoritmo: HandleVariantHuman()</b></summary>

> ```pseudocode
> ALGORITMO HandleVariantHuman(CharacterBuilder builder) RETORNA VariantHumanChoices
> INÍCIO
> SE builder.GetRace().GetName() != "Variant Human" ENTÃO
> RETORNA NULL
> FIM SE
>

> // Variant Human: escolhas especiais
> VariantHumanChoices choices
>
> // 1. Ability Score Choices (2x +1)
> choices.AbilityScoreChoices = SelectAbilityScores(
> count: 2,
> bonus: +1,
> validAbilities: GetAllAbilityNames()
> )
>
> // Validação: máximo 2 escolhas
> SE choices.AbilityScoreChoices.Count() > VARIANT_HUMAN_ABILITY_SCORE_CHOICES ENTÃO
> LogError("Variant Human não pode ter mais de 2 ability score choices")
> choices.AbilityScoreChoices = TrimToMax(choices.AbilityScoreChoices, 2)
> FIM SE
>
> // 2. Feat Choice (1 feat)
> choices.SelectedFeat = SelectFeat(
> availableFeats: GetAvailableFeatsForVariantHuman(builder.GetAbilityScores())
> )
>
> // 3. Skill Choice (1 skill)
> choices.SelectedSkill = SelectSkill(
> availableSkills: GetAllSkills(),
> exclude: builder.GetClass().GetProficientSkills()
> )
>
> RETORNA choices
> FIM
> ```
>
> **Padrão:** Strategy Pattern - Variant Human tem estratégia diferente de Human normal
>
</details>
---

## 2️⃣ PASSO 2: Choose Class (Factory Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏭 Algoritmo: SelectClass()</b></summary>

> ```pseudocode
> ALGORITMO SelectClass(ClassFactory factory, ClassName className) RETORNA Class
> INÍCIO
> // Factory Pattern: cria objeto Class
> Class class = factory.CreateClass(className)
>

> SE class == NULL ENTÃO
> RETORNA NULL
> FIM SE
>
> // Aplica features de nível 1
> ApplyLevel1Features(class)
>
> // Aplica proficiências
> ApplyClassProficiencies(class)
>
> // Calcula Hit Points iniciais
> CalculateStartingHitPoints(class)
>
> RETORNA class
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: ApplyClassProficiencies()</b></summary>

> ```pseudocode
> ALGORITMO ApplyClassProficiencies(Class class, Character character) RETORNA Proficiencies
> INÍCIO
> Proficiencies proficiencies
>

> // 1. Armor Proficiencies
> proficiencies.Armor = class.GetArmorProficiencies()
>
> // 2. Weapon Proficiencies
> proficiencies.Weapons = class.GetWeaponProficiencies()
>
> // 3. Tool Proficiencies
> proficiencies.Tools = class.GetToolProficiencies()
>
> // 4. Saving Throw Proficiencies (2 escolhidos pela classe)
> proficiencies.SavingThrows = class.GetSavingThrowProficiencies()
>
> // 5. Skill Proficiencies (2 escolhidos pelo jogador)
> skillChoices = SelectSkillsFromClassList(
> availableSkills: class.GetSkillProficiencies(),
> count: class.GetSkillProficiencyCount() // Geralmente 2
> )
> proficiencies.Skills = skillChoices
>
> RETORNA proficiencies
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❤️ Algoritmo: CalculateStartingHitPoints()</b></summary>

> ```pseudocode
> ALGORITMO CalculateStartingHitPoints(Class class, AbilityScores scores) RETORNA int32
> INÍCIO
> // HP inicial = Hit Die máximo + Constitution modifier
> HitDie hitDie = class.GetHitDie() // d6, d8, d10, d12
> int32 maxHitDie = hitDie.GetMaxValue() // 6, 8, 10, 12
>

> int32 constitutionModifier = CalculateAbilityModifier(
> score: scores[CONSTITUTION]
> )
>
> int32 startingHP = maxHitDie + constitutionModifier
>
> // Mínimo de 1 HP
> SE startingHP < MIN_HP ENTÃO
> startingHP = MIN_HP
> FIM SE
>
> RETORNA startingHP
> FIM
> ```
>
</details>
---

## 3️⃣ PASSO 3: Determine Ability Scores (Strategy Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Algoritmo: DetermineAbilityScores()</b></summary>

> ```pseudocode
> ALGORITMO DetermineAbilityScores(AbilityScoreStrategy strategy) RETORNA AbilityScores
> INÍCIO
> // Strategy Pattern: diferentes métodos de geração
> AbilityScores scores
>

> SE strategy == POINT_BUY ENTÃO
> scores = ApplyPointBuyStrategy()
> SENÃO SE strategy == STANDARD_ARRAY ENTÃO
> scores = ApplyStandardArrayStrategy()
> SENÃO SE strategy == ROLL_DICE ENTÃO
> scores = ApplyRollDiceStrategy()
> FIM SE
>
> // Aplica bônus raciais (já aplicado no Passo 1, mas valida)
> ValidateAbilityScores(scores)
>
> RETORNA scores
> FIM
> ```
>
> **Padrão:** Strategy Pattern - Point Buy, Standard Array e Roll são estratégias intercambiáveis
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💰 Algoritmo: ApplyPointBuyStrategy()</b></summary>

> ```pseudocode
> ALGORITMO ApplyPointBuyStrategy() RETORNA AbilityScores
> INÍCIO
> AbilityScores scores
> int32 availablePoints = MAX_POINT_BUY_POINTS // 27
>

> // Inicializa todos com BASE_ABILITY_SCORE (8)
> PARA CADA ability EM GetAllAbilityNames() FAÇA
> scores[ability] = BASE_ABILITY_SCORE
> FIM PARA
>
> // Tabela de custos (Data-Driven, vem de Data Table)
> CostTable costTable = LoadPointBuyCostTable()
>
> // Loop de alocação (jogador escolhe, sistema valida)
> ENQUANTO availablePoints > 0 FAÇA
> // Jogador escolhe ability e score desejado
> AbilityName selectedAbility = GetPlayerChoice()
> int32 desiredScore = GetPlayerDesiredScore()
>
> // Validação
> SE desiredScore < MIN_POINT_BUY_SCORE OU desiredScore > MAX_POINT_BUY_SCORE ENTÃO
> LogError("Score fora do range válido (8-15)")
> CONTINUE
> FIM SE
>
> // Calcula custo
> int32 currentScore = scores[selectedAbility]
> int32 cost = CalculatePointBuyCost(desiredScore, costTable)
> int32 pointsToSpend = cost - CalculatePointBuyCost(currentScore, costTable)
>
> // Valida pontos disponíveis
> SE pointsToSpend > availablePoints ENTÃO
> LogError("Pontos insuficientes")
> CONTINUE
> FIM SE
>
> // Aplica alocação
> scores[selectedAbility] = desiredScore
> availablePoints -= pointsToSpend
> FIM ENQUANTO
>
> // Validação final: deve gastar exatamente 27 pontos
> SE availablePoints != 0 ENTÃO
> LogWarning("Pontos não totalmente gastos")
> FIM SE
>
> RETORNA scores
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: CalculatePointBuyCost()</b></summary>

> ```pseudocode
> ALGORITMO CalculatePointBuyCost(int32 score, CostTable table) RETORNA int32
> INÍCIO
> // Tabela de custos D&D 5e (Data-Driven)
> // Score 8: 0 pontos
> // Score 9: 1 ponto
> // Score 10: 2 pontos
> // Score 11: 3 pontos
> // Score 12: 4 pontos
> // Score 13: 5 pontos
> // Score 14: 7 pontos
> // Score 15: 9 pontos
>

> SE table.Contains(score) ENTÃO
> RETORNA table.GetCost(score)
> SENÃO
> LogError("Score inválido para Point Buy")
> RETORNA 0
> FIM SE
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Algoritmo: ApplyStandardArrayStrategy()</b></summary>

> ```pseudocode
> ALGORITMO ApplyStandardArrayStrategy() RETORNA AbilityScores
> INÍCIO
> // Standard Array: valores fixos [15, 14, 13, 12, 10, 8]
> int32[] standardArray = [15, 14, 13, 12, 10, 8]
>

> // Jogador distribui valores fixos entre abilities
> AbilityScores scores
> AbilityName[] abilities = GetAllAbilityNames()
>
> PARA CADA i EM [0..standardArray.Length-1] FAÇA
> int32 value = standardArray[i]
> AbilityName ability = GetPlayerChoice(abilities) // Jogador escolhe
>
> scores[ability] = value
> RemoveFromArray(abilities, ability) // Remove para não repetir
> FIM PARA
>
> RETORNA scores
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔢 Algoritmo: CalculateAbilityModifier()</b></summary>

> ```pseudocode
> ALGORITMO CalculateAbilityModifier(int32 score) RETORNA int32
> INÍCIO
> // Fórmula: (Score - 10) / 2 (arredondado para baixo)
> int32 modifier = (score - ABILITY_MODIFIER_BASE) / ABILITY_MODIFIER_DIVISOR
>

> RETORNA modifier
> FIM
> ```
>
</details>
---

## 4️⃣ PASSO 4: Describe Character (Builder Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📝 Algoritmo: DescribeCharacter()</b></summary>

> ```pseudocode
> ALGORITMO DescribeCharacter(CharacterBuilder builder) RETORNA CharacterDescription
> INÍCIO
> CharacterDescription description
>

> // 1. Nome
> description.Name = GetPlayerInput("Nome do personagem")
>
> // 2. Alinhamento
> description.Alignment = SelectAlignment(
> options: GetAllAlignments() // Lawful Good, Chaotic Evil, etc.
> )
>
> // 3. Idade
> description.Age = GetPlayerInput("Idade")
>
> // 4. Altura
> description.Height = GetPlayerInput("Altura")
>
> // 5. Peso
> description.Weight = GetPlayerInput("Peso")
>
> // 6. Aparência física
> description.Appearance = GetPlayerInput("Descrição física")
>
> // 7. Personalidade
> description.Personality = GetPlayerInput("Traços de personalidade")
>
> // 8. Ideais
> description.Ideals = GetPlayerInput("Ideais")
>
> // 9. Vínculos
> description.Bonds = GetPlayerInput("Vínculos")
>
> // 10. Defeitos
> description.Flaws = GetPlayerInput("Defeitos")
>
> RETORNA description
> FIM
> ```
>
> **Padrão:** Builder Pattern - constrói objeto complexo passo a passo
>
</details>
---

## 5️⃣ PASSO 5: Choose Equipment (Chain of Responsibility)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎒 Algoritmo: ChooseEquipment()</b></summary>

> ```pseudocode
> ALGORITMO ChooseEquipment(Character character) RETORNA Equipment
> INÍCIO
> Equipment equipment
>

> // 1. Equipment da Classe (obrigatório)
> ClassStartingEquipment classEquipment = character.GetClass().GetStartingEquipment()
> equipment.Add(classEquipment)
>
> // 2. Equipment do Background (obrigatório)
> BackgroundStartingEquipment bgEquipment = character.GetBackground().GetStartingEquipment()
> equipment.Add(bgEquipment)
>
> // 3. Equipment opcional (se classe permite)
> SE character.GetClass().AllowsEquipmentChoice() ENTÃO
> EquipmentChoice choice = SelectEquipmentChoice(
> options: character.GetClass().GetEquipmentChoices()
> )
> equipment.Add(choice)
> FIM SE
>
> // 4. Trinket (opcional, gratuito)
> SE GetPlayerWantsTrinket() ENTÃO
> Trinket trinket = SelectTrinket(
> options: GetAllTrinkets()
> )
> equipment.Add(trinket)
> FIM SE
>
> // 5. Validação: Carrying Capacity
> ValidateCarryingCapacity(character, equipment)
>
> RETORNA equipment
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚖️ Algoritmo: ValidateCarryingCapacity()</b></summary>

> ```pseudocode
> ALGORITMO ValidateCarryingCapacity(Character character, Equipment equipment) RETORNA bool
> INÍCIO
> // Carrying Capacity = Strength Score × 15 (em libras)
> int32 strengthScore = character.GetAbilityScores()[STRENGTH]
> int32 maxWeight = strengthScore * 15
>

> int32 totalWeight = equipment.CalculateTotalWeight()
>
> SE totalWeight > maxWeight ENTÃO
> LogWarning("Equipamento excede capacidade de carga")
> LogInfo("Peso atual: " + totalWeight + " / Máximo: " + maxWeight)
> RETORNA false
> FIM SE
>
> RETORNA true
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Algoritmo: CalculateArmorClass()</b></summary>

> ```pseudocode
> ALGORITMO CalculateArmorClass(Character character) RETORNA int32
> INÍCIO
> int32 armorClass = 10 // Base
>

> // Adiciona Dexterity modifier (se não usar armor pesada)
> Armor armor = character.GetEquipment().GetArmor()
>
> SE armor == NULL OU armor.GetType() == LIGHT OU armor.GetType() == MEDIUM ENTÃO
> int32 dexModifier = CalculateAbilityModifier(
> character.GetAbilityScores()[DEXTERITY]
> )
> armorClass += dexModifier
> FIM SE
>
> // Adiciona bônus de armor
> SE armor != NULL ENTÃO
> armorClass += armor.GetACBonus()
> FIM SE
>
> // Adiciona bônus de shield
> SE character.GetEquipment().HasShield() ENTÃO
> armorClass += 2 // Shield sempre +2
> FIM SE
>
> // Verifica se classe/spell fornece AC alternativo
> ACStrategy acStrategy = character.GetClass().GetACStrategy()
> SE acStrategy != NULL ENTÃO
> int32 alternativeAC = acStrategy.CalculateAC(character)
> // Usa o maior valor
> SE alternativeAC > armorClass ENTÃO
> armorClass = alternativeAC
> FIM SE
> FIM SE
>
> RETORNA armorClass
> FIM
> ```
>
> **Padrão:** Chain of Responsibility - validação sequencial de equipment
>
</details>
---

## 6️⃣ PASSO 6: Finalize Character (Builder Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Algoritmo: FinalizeCharacter()</b></summary>

> ```pseudocode
> ALGORITMO FinalizeCharacter(CharacterBuilder builder) RETORNA Character
> INÍCIO
> Character character = builder.Build()
>

> // 1. Calcula valores finais
> CalculateFinalAbilityScores(character)
> CalculateFinalProficiencies(character)
> CalculateFinalHitPoints(character)
> CalculateArmorClass(character)
> CalculateProficiencyBonus(character)
>
> // 2. Validação completa
> ValidationResult validation = ValidateCharacter(character)
> SE !validation.IsValid() ENTÃO
> LogErrors(validation.GetErrors())
> RETORNA NULL
> FIM SE
>
> // 3. Aplica features de nível 1
> ApplyLevel1Features(character)
>
> // 4. Calcula languages
> CalculateLanguages(character)
>
> // 5. Prepara para jogo
> PrepareForGameplay(character)
>
> RETORNA character
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: CalculateFinalAbilityScores()</b></summary>

> ```pseudocode
> ALGORITMO CalculateFinalAbilityScores(Character character) RETORNA AbilityScores
> INÍCIO
> // Fórmula: FinalScore = BaseScore + RacialBonus + PointBuyAllocation
> // (RacialBonus já aplicado no Passo 1, PointBuy no Passo 3)
>

> AbilityScores baseScores = character.GetBaseAbilityScores()
> AbilityScores racialBonuses = character.GetRace().GetAbilityBonuses()
> AbilityScores pointBuyAllocation = character.GetPointBuyAllocation()
>
> AbilityScores finalScores
>
> PARA CADA ability EM GetAllAbilityNames() FAÇA
> finalScores[ability] = baseScores[ability] +
> racialBonuses[ability] +
> pointBuyAllocation[ability]
>
> // Validação: máximo 30
> SE finalScores[ability] > MAX_ABILITY_SCORE ENTÃO
> finalScores[ability] = MAX_ABILITY_SCORE
> FIM SE
>
> // Validação: mínimo 1
> SE finalScores[ability] < MIN_ABILITY_SCORE ENTÃO
> finalScores[ability] = MIN_ABILITY_SCORE
> FIM SE
> FIM PARA
>
> character.SetFinalAbilityScores(finalScores)
>
> RETORNA finalScores
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⭐ Algoritmo: CalculateProficiencyBonus()</b></summary>

> ```pseudocode
> ALGORITMO CalculateProficiencyBonus(int32 level) RETORNA int32
> INÍCIO
> // Fórmula: 1 + ((Level - 1) / 4) (arredondado para baixo)
> // Níveis 1-4: +2
> // Níveis 5-8: +3
> // Níveis 9-12: +4
> // Níveis 13-16: +5
> // Níveis 17-20: +6
>

> int32 bonus = PROFICIENCY_BONUS_BASE + ((level - 1) / PROFICIENCY_BONUS_DIVISOR)
>
> RETORNA bonus
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🗣️ Algoritmo: CalculateLanguages()</b></summary>

> ```pseudocode
> ALGORITMO CalculateLanguages(Character character) RETORNA LanguageList
> INÍCIO
> LanguageList languages
>

> // 1. Languages da raça (obrigatórios)
> languages.AddAll(character.GetRace().GetLanguages())
>
> // 2. Languages do background (se houver)
> SE character.GetBackground().HasLanguages() ENTÃO
> languages.AddAll(character.GetBackground().GetLanguages())
> FIM SE
>
> // 3. Languages opcionais (se raça permite escolha)
> SE character.GetRace().AllowsLanguageChoice() ENTÃO
> int32 choicesCount = character.GetRace().GetLanguageChoicesCount()
> LanguageList availableLanguages = GetAvailableLanguages(
> exclude: languages
> )
>
> PARA i = 1 ATÉ choicesCount FAÇA
> Language choice = SelectLanguage(availableLanguages)
> languages.Add(choice)
> RemoveFromList(availableLanguages, choice)
> FIM PARA
> FIM SE
>
> // 4. Languages de features/feats (ex: Linguist feat)
> SE character.HasFeature("Linguist") ENTÃO
> PARA i = 1 ATÉ 3 FAÇA
> Language choice = SelectLanguage(GetAllLanguages())
> languages.Add(choice)
> FIM PARA
> FIM SE
>
> RETORNA languages
> FIM
> ```
>
</details>
---

## 🔄 Validação (Chain of Responsibility Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Algoritmo: ValidateCharacter()</b></summary>

> ```pseudocode
> ALGORITMO ValidateCharacter(Character character) RETORNA ValidationResult
> INÍCIO
> ValidationResult result
>

> // Chain of Responsibility: validações sequenciais
> ValidatorChain chain = CreateValidatorChain()
>
> // 1. Valida Race
> result.Merge(chain.ValidateRace(character))
>
> // 2. Valida Class
> result.Merge(chain.ValidateClass(character))
>
> // 3. Valida Ability Scores
> result.Merge(chain.ValidateAbilityScores(character))
>
> // 4. Valida Background
> result.Merge(chain.ValidateBackground(character))
>
> // 5. Valida Equipment
> result.Merge(chain.ValidateEquipment(character))
>
> // 6. Valida Variant Human (se aplicável)
> SE character.GetRace().IsVariantHuman() ENTÃO
> result.Merge(chain.ValidateVariantHuman(character))
> FIM SE
>
> // 7. Valida Multiclass (se aplicável)
> SE character.IsMulticlass() ENTÃO
> result.Merge(chain.ValidateMulticlass(character))
> FIM SE
>
> RETORNA result
> FIM
> ```
>
> **Padrão:** Chain of Responsibility - validações sequenciais, cada validador pode processar ou passar adiante
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: ValidateAbilityScores()</b></summary>

> ```pseudocode
> ALGORITMO ValidateAbilityScores(Character character) RETORNA ValidationResult
> INÍCIO
> ValidationResult result
> AbilityScores scores = character.GetFinalAbilityScores()
>

> PARA CADA ability EM GetAllAbilityNames() FAÇA
> int32 score = scores[ability]
>
> // Validação: range válido (1-30)
> SE score < MIN_ABILITY_SCORE OU score > MAX_ABILITY_SCORE ENTÃO
> result.AddError("Ability score " + ability + " fora do range válido (1-30)")
> FIM SE
> FIM PARA
>
> RETORNA result
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👤 Algoritmo: ValidateVariantHuman()</b></summary>

> ```pseudocode
> ALGORITMO ValidateVariantHuman(Character character) RETORNA ValidationResult
> INÍCIO
> ValidationResult result
>

> SE !character.GetRace().IsVariantHuman() ENTÃO
> RETORNA result // Não é Variant Human, ignora
> FIM SE
>
> VariantHumanChoices choices = character.GetVariantHumanChoices()
>
> // 1. Valida Ability Score Choices (máximo 2)
> SE choices.AbilityScoreChoices.Count() > VARIANT_HUMAN_ABILITY_SCORE_CHOICES ENTÃO
> result.AddError("Variant Human não pode ter mais de 2 ability score choices")
> FIM SE
>
> // 2. Valida duplicatas
> SE HasDuplicates(choices.AbilityScoreChoices) ENTÃO
> result.AddError("Variant Human não pode ter ability scores duplicados")
> FIM SE
>
> // 3. Valida elementos inválidos
> TArray<int32> invalidIndices = FindInvalidAbilityScores(choices.AbilityScoreChoices)
> SE invalidIndices.Count() > 0 ENTÃO
> result.AddError("Variant Human tem ability scores inválidos")
> FIM SE
>
> // 4. Valida Feat
> SE choices.SelectedFeat != NULL ENTÃO
> SE !IsFeatAvailable(choices.SelectedFeat, character) ENTÃO
> result.AddError("Feat selecionado não está disponível")
> FIM SE
> FIM SE
>
> // 5. Valida Skill
> SE choices.SelectedSkill != NULL ENTÃO
> SE !IsSkillValid(choices.SelectedSkill) ENTÃO
> result.AddError("Skill selecionado não é válido")
> FIM SE
> FIM SE
>
> RETORNA result
> FIM
> ```
>
</details>
---

## 🎲 Multiclassing (Strategy Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Algoritmo: AddMulticlassLevel()</b></summary>

> ```pseudocode
> ALGORITMO AddMulticlassLevel(Character character, ClassName newClass) RETORNA bool
> INÍCIO
> // Validação: requisitos de multiclass
> SE !ValidateMulticlassRequirements(character, newClass) ENTÃO
> LogError("Requisitos de multiclass não atendidos")
> RETORNA false
> FIM SE
>

> // Adiciona nível na nova classe
> character.AddClassLevel(newClass, level: 1)
>
> // Aplica features de nível 1 da nova classe
> ApplyMulticlassLevel1Features(character, newClass)
>
> // Aplica proficiências de multiclass (limitadas)
> ApplyMulticlassProficiencies(character, newClass)
>
> // Recalcula valores derivados
> RecalculateDerivedValues(character)
>
> RETORNA true
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Algoritmo: ValidateMulticlassRequirements()</b></summary>

> ```pseudocode
> ALGORITMO ValidateMulticlassRequirements(Character character, ClassName newClass) RETORNA bool
> INÍCIO
> // Requisitos de multiclass D&D 5e
> MulticlassRequirements requirements = GetMulticlassRequirements(newClass)
> AbilityScores scores = character.GetFinalAbilityScores()
>

> // Verifica cada requisito
> PARA CADA requirement EM requirements FAÇA
> AbilityName ability = requirement.AbilityName
> int32 minScore = requirement.MinScore
>
> SE scores[ability] < minScore ENTÃO
> LogError("Requisito não atendido: " + ability + " >= " + minScore)
> RETORNA false
> FIM SE
> FIM PARA
>
> RETORNA true
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📊 Algoritmo: CalculateTotalLevel()</b></summary>

> ```pseudocode
> ALGORITMO CalculateTotalLevel(Character character) RETORNA int32
> INÍCIO
> int32 totalLevel = 0
>

> PARA CADA classLevel EM character.GetClassLevels() FAÇA
> totalLevel += classLevel.Level
> FIM PARA
>
> // Validação: máximo 20
> SE totalLevel > MAX_LEVEL ENTÃO
> LogError("Nível total excede máximo (20)")
> totalLevel = MAX_LEVEL
> FIM SE
>
> RETORNA totalLevel
> FIM
> ```
>
> **Padrão:** Strategy Pattern - diferentes classes têm diferentes requisitos de multiclass
>
</details>
---

## 📊 Background (Factory Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏭 Algoritmo: SelectBackground()</b></summary>

> ```pseudocode
> ALGORITMO SelectBackground(BackgroundFactory factory, BackgroundName bgName) RETORNA Background
> INÍCIO
> // Factory Pattern: cria objeto Background
> Background background = factory.CreateBackground(bgName)
>

> SE background == NULL ENTÃO
> RETORNA NULL
> FIM SE
>
> // Aplica features do background
> ApplyBackgroundFeatures(background)
>
> // Aplica proficiências
> ApplyBackgroundProficiencies(background)
>
> // Aplica languages (se houver)
> SE background.HasLanguages() ENTÃO
> ApplyBackgroundLanguages(background)
> FIM SE
>
> // Aplica equipment inicial
> ApplyBackgroundEquipment(background)
>
> RETORNA background
> FIM
> ```
>
</details>
---

## 🔄 Level Up (Template Method Pattern)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⬆️ Algoritmo: LevelUp()</b></summary>

> ```pseudocode
> ALGORITMO LevelUp(Character character, ClassName classToLevel) RETORNA bool
> INÍCIO
> // Template Method: ordem fixa de operações
>

> // 1. Validação
> SE !ValidateLevelUp(character, classToLevel) ENTÃO
> RETORNA false
> FIM SE
>
> // 2. Incrementa nível
> int32 newLevel = character.IncrementClassLevel(classToLevel)
>
> // 3. Aplica features do nível
> ApplyLevelFeatures(character, classToLevel, newLevel)
>
> // 4. Calcula HP adicional
> CalculateAdditionalHitPoints(character, classToLevel, newLevel)
>
> // 5. Atualiza Proficiency Bonus
> UpdateProficiencyBonus(character)
>
> // 6. Verifica ASI/Feat (níveis 4, 8, 12, 16, 19)
> SE IsASILevel(newLevel) ENTÃO
> HandleASIOrFeat(character, classToLevel, newLevel)
> FIM SE
>
> // 7. Verifica Subclass (nível 3)
> SE newLevel == SUBCLASS_SELECTION_LEVEL ENTÃO
> HandleSubclassSelection(character, classToLevel)
> FIM SE
>
> RETORNA true
> FIM
> ```
>
> **Padrão:** Template Method - define ordem fixa, subclasses implementam detalhes
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❤️ Algoritmo: CalculateAdditionalHitPoints()</b></summary>

> ```pseudocode
> ALGORITMO CalculateAdditionalHitPoints(Character character, ClassName class, int32 newLevel) RETORNA int32
> INÍCIO
> // Opção 1: Rolar Hit Die
> // Opção 2: Usar valor fixo (média arredondada para cima)
>

> HitDie hitDie = class.GetHitDie()
> int32 constitutionModifier = CalculateAbilityModifier(
> character.GetFinalAbilityScores()[CONSTITUTION]
> )
>
> // Valor fixo (média)
> int32 averageHP = (hitDie.GetMaxValue() / HP_AVERAGE_DIVISOR) + 1 // Arredondado para cima
> int32 additionalHP = averageHP + constitutionModifier
>
> // Mínimo de 1 HP por nível
> SE additionalHP < 1 ENTÃO
> additionalHP = 1
> FIM SE
>
> // Aplica ao HP máximo
> character.IncreaseMaxHP(additionalHP)
> character.IncreaseCurrentHP(additionalHP) // Cura ao subir de nível
>
> RETORNA additionalHP
> FIM
> ```
>
</details>
<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⭐ Algoritmo: HandleASIOrFeat()</b></summary>

> ```pseudocode
> ALGORITMO HandleASIOrFeat(Character character, ClassName class, int32 level) RETORNA Choice
> INÍCIO
> // Níveis 4, 8, 12, 16, 19: ASI ou Feat
> Choice choice
>

> // Jogador escolhe: ASI ou Feat
> ChoiceType type = GetPlayerChoice("ASI ou Feat?")
>
> SE type == ASI ENTÃO
> // Ability Score Improvement: +2 em um ou +1 em dois
> ASIChoice asiChoice = GetPlayerASIChoice()
>
> SE asiChoice.Type == SINGLE_ABILITY THEN
> // +2 em um ability
> character.IncreaseAbilityScore(asiChoice.Ability, 2)
> SENÃO SE asiChoice.Type == TWO_ABILITIES THEN
> // +1 em dois abilities
> character.IncreaseAbilityScore(asiChoice.Ability1, 1)
> character.IncreaseAbilityScore(asiChoice.Ability2, 1)
> FIM SE
>
> choice = asiChoice
> SENÃO SE type == FEAT THEN
> // Feat: escolhe um feat disponível
> FeatList availableFeats = GetAvailableFeats(character)
> Feat selectedFeat = GetPlayerFeatChoice(availableFeats)
>
> character.AddFeat(selectedFeat)
> ApplyFeatFeatures(character, selectedFeat)
>
> choice = selectedFeat
> FIM SE
>
> RETORNA choice
> FIM
> ```
>
</details>
---

## 🎯 Regras de Negócio (Business Rules)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📋 Regras Principais</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Regra 1: Ability Score Maximum</summary>
>

</details>
    > REGRA: Ability Score Maximum
    >     Ability Score máximo: 30
    >     Ability Score mínimo: 1
    >     Ability Score inicial (Point Buy): 8
    >     Ability Score máximo (Point Buy): 15
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💰 Regra 2: Point Buy System</summary>

    > ```pseudocode
    > REGRA: Point Buy System
    >     Pontos disponíveis: 27
    >     Tabela de custos:
    >         Score 8: 0 pontos
    >         Score 9: 1 ponto
    >         Score 10: 2 pontos
    >         Score 11: 3 pontos
    >         Score 12: 4 pontos
    >         Score 13: 5 pontos
    >         Score 14: 7 pontos
    >         Score 15: 9 pontos
    >     Deve gastar exatamente 27 pontos
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⭐ Regra 3: Proficiency Bonus</summary>

    > ```pseudocode
    > REGRA: Proficiency Bonus
    >     Fórmula: 1 + ((Level - 1) / 4) (arredondado para baixo)
    >     Níveis 1-4: +2
    >     Níveis 5-8: +3
    >     Níveis 9-12: +4
    >     Níveis 13-16: +5
    >     Níveis 17-20: +6
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔢 Regra 4: Ability Modifier</summary>

    > ```pseudocode
    > REGRA: Ability Modifier
    >     Fórmula: (Score - 10) / 2 (arredondado para baixo)
    >     Exemplos:
    >         Score 1: -5
    >         Score 8: -1
    >         Score 10: 0
    >         Score 12: +1
    >         Score 15: +2
    >         Score 20: +5
    >         Score 30: +10
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👤 Regra 5: Variant Human</summary>

    > ```pseudocode
    > REGRA: Variant Human
    >     Ability Score Choices: 2x +1 (máximo 2 escolhas)
    >     Feat Choice: 1 feat (nível 1)
    >     Skill Choice: 1 skill
    >     Validação: não pode ter mais de 2 ability score choices
    >     Validação: não pode ter duplicatas
    >     Validação: não pode ter elementos inválidos
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎲 Regra 6: Multiclassing</summary>

    > ```pseudocode
    > REGRA: Multiclassing
    >     Requisitos por classe:
    >         Barbarian: STR 13
    >         Bard: CHA 13
    >         Cleric: WIS 13
    >         Druid: WIS 13
    >         Fighter: STR 13 ou DEX 13
    >         Monk: DEX 13 e WIS 13
    >         Paladin: STR 13 e CHA 13
    >         Ranger: DEX 13 e WIS 13
    >         Rogue: DEX 13
    >         Sorcerer: CHA 13
    >         Warlock: CHA 13
    >         Wizard: INT 13
    >     Nível total máximo: 20
    >     Proficiências limitadas (apenas algumas da nova classe)
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⭐ Regra 7: ASI/Feat Levels</summary>

    > ```pseudocode
    > REGRA: ASI/Feat Levels
    >     Níveis que concedem ASI ou Feat: 4, 8, 12, 16, 19
    >     ASI: +2 em um ability OU +1 em dois abilities
    >     Feat: escolhe um feat disponível (alternativa ao ASI)
    >     Ability Score máximo mesmo com ASI: 20 (sem magic items)
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎯 Regra 8: Subclass Selection</summary>

    > ```pseudocode
    > REGRA: Subclass Selection
    >     Nível de seleção: 3
    >     Cada classe tem subclasses disponíveis
    >     Escolha é permanente (não pode mudar)
    >     Algumas classes não têm subclasses
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">❤️ Regra 9: Hit Points</summary>

    > ```pseudocode
    > REGRA: Hit Points
    >     HP inicial: Hit Die máximo + Constitution modifier
    >     HP por nível: Hit Die (rolado ou média) + Constitution modifier
    >     HP mínimo por nível: 1
    >     HP máximo: sem limite teórico (praticamente limitado por nível 20)
    > FIM REGRA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🛡️ Regra 10: Armor Class</summary>

    > ```pseudocode
    > REGRA: Armor Class
    >     Base: 10 + Dexterity modifier
    >     Com armor: Armor AC + Dexterity modifier (limitado por tipo de armor)
    >     Com shield: +2
    >     Algumas classes/spells fornecem AC alternativo
    >     Usa o maior valor disponível
    > FIM REGRA
    > ```

    </details>

    </details>

## 🏗️ Estrutura de Dados (Data Structures)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📦 Estruturas Principais</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👤 Character (Builder Pattern)</summary>
>

</details>
    > ESTRUTURA Character
    >     // Identificação
    >     Name: string
    >     Description: string
    >     Level: int32
    >
    >     // Race
    >     Race: Race
    >     Subrace: Subrace (opcional)
    >     VariantHumanChoices: VariantHumanChoices (se Variant Human)
    >
    >     // Class
    >     Classes: TMap<ClassName, ClassLevel> // Multiclass support
    >     TotalLevel: int32
    >
    >     // Ability Scores
    >     BaseAbilityScores: AbilityScores
    >     RacialBonuses: AbilityScores
    >     PointBuyAllocation: AbilityScores
    >     FinalAbilityScores: AbilityScores
    >
    >     // Proficiencies
    >     Proficiencies: Proficiencies
    >
    >     // Background
    >     Background: Background
    >
    >     // Equipment
    >     Equipment: Equipment
    >
    >     // Calculated Values
    >     HitPoints: HitPoints
    >     ArmorClass: int32
    >     ProficiencyBonus: int32
    >
    >     // Languages
    >     Languages: LanguageList
    >
    >     // Features
    >     Features: FeatureList
    >     Feats: FeatList
    > FIM ESTRUTURA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 AbilityScores</summary>

    > ```pseudocode
    > ESTRUTURA AbilityScores
    >     Strength: int32
    >     Dexterity: int32
    >     Constitution: int32
    >     Intelligence: int32
    >     Wisdom: int32
    >     Charisma: int32
    > FIM ESTRUTURA
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⭐ Proficiencies</summary>

    > ```pseudocode
    > ESTRUTURA Proficiencies
    >     Armor: TArray<ArmorType>
    >     Weapons: TArray<WeaponType>
    >     Tools: TArray<ToolType>
    >     SavingThrows: TArray<AbilityName>
    >     Skills: TArray<SkillName>
    > FIM ESTRUTURA
    > ```

    </details>

    </details>

## 🔍 Validações Críticas (Validation Rules)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Validações Principais</b></summary>

> <details>
> <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Validação 1: Ability Score Range</summary>
>

</details>
    > VALIDAÇÃO: AbilityScoreRange
    >     PARA CADA ability EM AbilityScores FAÇA
    >         SE ability < MIN_ABILITY_SCORE OU ability > MAX_ABILITY_SCORE ENTÃO
    >             ERRO: "Ability score fora do range válido (1-30)"
    >         FIM SE
    >     FIM PARA
    > FIM VALIDAÇÃO
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💰 Validação 2: Point Buy Total</summary>

    > ```pseudocode
    > VALIDAÇÃO: PointBuyTotal
    >     int32 totalSpent = CalculateTotalPointBuyCost(abilityScores)
    >     SE totalSpent != MAX_POINT_BUY_POINTS ENTÃO
    >         ERRO: "Point Buy deve gastar exatamente 27 pontos"
    >     FIM SE
    > FIM VALIDAÇÃO
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👤 Validação 3: Variant Human Choices</summary>

    > ```pseudocode
    > VALIDAÇÃO: VariantHumanChoices
    >     SE IsVariantHuman() ENTÃO
    >         SE AbilityScoreChoices.Count() > VARIANT_HUMAN_ABILITY_SCORE_CHOICES ENTÃO
    >             ERRO: "Variant Human não pode ter mais de 2 ability score choices"
    >         FIM SE
    >
    >         SE HasDuplicates(AbilityScoreChoices) ENTÃO
    >             ERRO: "Variant Human não pode ter duplicatas"
    >         FIM SE
    >
    >         SE HasInvalidElements(AbilityScoreChoices) ENTÃO
    >             ERRO: "Variant Human tem elementos inválidos"
    >         FIM SE
    >     FIM SE
    > FIM VALIDAÇÃO
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎲 Validação 4: Multiclass Requirements</summary>

    > ```pseudocode
    > VALIDAÇÃO: MulticlassRequirements
    >     PARA CADA class EM Classes FAÇA
    >         MulticlassRequirements req = GetRequirements(class)
    >         PARA CADA requirement EM req FAÇA
    >             SE FinalAbilityScores[requirement.Ability] < requirement.MinScore ENTÃO
    >                 ERRO: "Requisito de multiclass não atendido"
    >             FIM SE
    >         FIM PARA
    >     FIM PARA
    > FIM VALIDAÇÃO
    > ```

    </details>

    </details>
    <summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📊 Validação 5: Total Level</summary>

    > ```pseudocode
    > VALIDAÇÃO: TotalLevel
    >     int32 total = CalculateTotalLevel()
    >     SE total > MAX_LEVEL ENTÃO
    >         ERRO: "Nível total excede máximo (20)"
    >     FIM SE
    > FIM VALIDAÇÃO
    > ```

    </details>

    </details>

## 📚 Referências

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔗 Links e Documentação</b></summary>

> - [D&D Beyond - Step-By-Step Characters](https://www.dndbeyond.com/sources/dnd/basic-rules-2014/step-by-step-characters)
> - Design Patterns: Elements of Reusable Object-Oriented Software (Gang of Four)
> - Refactoring.Guru - Design Patterns in C++
> - **[Arquitetura Técnica](../architecture.md)** - Como o sistema funciona
> - **[API Reference](../api.md)** - Classes e funções disponíveis
> - **[Regras D&D 5e](../../03 - TDD/dnd-rules/)** - Regras implementadas
>

</details>

## 🎯 Notas de Implementação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💡 Princípios de Implementação</b></summary>

> 1. **Data-Driven**: Todas as regras devem vir de Data Tables, não hardcoded
> 2. **Modular**: Cada passo é um módulo independente
> 3. **Testável**: Cada algoritmo pode ser testado isoladamente
> 4. **Reutilizável**: Funções puras quando possível
> 5. **Validável**: Validação em cada etapa
> 6. **Observável**: Notificações de mudanças de estado (Observer Pattern)
>

</details>

**Última atualização:** 2024-12-26
**Versão:** 1.0
