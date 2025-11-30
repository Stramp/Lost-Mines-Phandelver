# Preparação para GAS (Gameplay Ability System)

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Extraído de architecture.md |

---

## 🔮 Arquitetura GAS - Preparação e Padrões

**Visão Geral:** O projeto está preparado para migração futura para GAS, mantendo todos os princípios fundamentais (Data-Driven, Editor-Friendly, Modularidade) e incorporando os melhores padrões de runtime do GAS.

**Arquitetura Híbrida:**
- **Dados (C):** Atributos e lógica complexa de processamento
- **Lógica Visual (Blueprint):** Habilidades e fluxo de animações
- **Comunicação (Tags e Events):** Sistema desacoplado via ASC

**Princípio Central:** Nada é "hardcoded". Tudo se comunica via Tags, Events e Delegates, mantendo Editor-Friendly e Data-Driven.

---

## 📐 1. Localização do ASC (Ability System Component)

**Regra Fundamental:** Onde o ASC é criado depende do tipo de ator.

**Player (Jogador):**
- ✅ ASC criado no **PlayerState**
- **Motivo:** Em multiplayer, se o peão morre, o PlayerState persiste
- **Benefícios:**
  - Atributos (vida/mana) intactos após morte
  - Habilidades intactas
  - Estado do jogador preservado

**AI (Inimigos):**
- ✅ ASC criado no **próprio Character**
- **Motivo:** Inimigos não respawnam com persistência de dados
- **Benefícios:**
  - Morreu = destruiu (sem overhead desnecessário)
  - Não precisa persistir entre mortes

**Inicialização (`InitAbilityActorInfo`):**
- **Server:** No `PossessedBy`
- **Client:** No `OnRep_PlayerState`
- **Garante:** Replicação correta desde o início

---

## 💾 2. AttributeSet em C (Dados)

**Responsabilidade:** Definir atributos e lógica complexa de processamento.

**Padrão:**
- Herda de `UAttributeSet`
- Define atributos (`Health`, `MaxHealth`, `Stamina`, etc.)
- Usa macros `ATTRIBUTE_ACCESSORS` para gerar Getters/Setters automáticos

**Replicação:**
- Usa `DOREPLIFETIME_CONDITION_NOTIFY` para sincronizar atributos
- Sincroniza com UI do cliente automaticamente

**Meta-Atributos (Processamento de Dano):**
- Cria atributos "falsos" para processamento (ex: `IncomingDamage`)
- **Fluxo:**
  1. GameplayEffect aplica valor ao `IncomingDamage`
  2. `PostGameplayEffectExecute` captura esse valor
  3. Deduz da Vida real (`Health = Health - IncomingDamage`)
  4. Zera o `IncomingDamage` para próximo golpe

**Clamping:**
- Usa `PreAttributeChange` para garantir limites
- Vida nunca excede `MaxHealth` ou cai abaixo de `0`
- Antes mesmo da modificação ocorrer

**Migração do Projeto:**
```
CharacterDataComponent → GAS AttributeSet
- Health, MaxHealth → GAS Attributes
- FinalAbilityScores → GAS Attributes
- Lógica de cálculo → PostGameplayEffectExecute
```

---

## 🎨 3. Gameplay Abilities em Blueprint (Lógica Visual)

**Responsabilidade:** Controlar fluxo de habilidades e animações.

**Padrão Modular:**
- **Habilidade Base (C ou BP):** Contém lógica comum (tocar montages, aplicar dano)
- **Habilidades Filhas (BP):** Apenas definem parâmetros (Montage, Efeito)

**Fluxo de Ativação:**
1. `ActivateAbility`
2. Toca Animação (Montage)
3. Aplica efeito (força, dano, etc.)
4. `EndAbility`

**Input Binding:**
- Associa Input Action (Enhanced Input) a Gameplay Tag ou ID
- ASC ativa habilidade correspondente àquela tag

**Cancelamento:**
- Configura habilidade para ser cancelada automaticamente
- Se certas Tags (ex: `State.Dead`) estiverem presentes, cancela

**Gameplay Effects (GE):**
- **Duration:** Para recarga (Cooldown)
- **Instant:** Para custos (reduz Stamina imediatamente)
- **Infinite:** Para regeneração passiva (Regen Stamina)
- Vincula GEs nos campos `CostGameplayEffectClass` e `CooldownGameplayEffectClass`

**Migração do Projeto:**
```
Feature Components → GAS Abilities
- SpellcastingComponent → GA_Spellcasting (BP)
- SecondWindComponent → GA_SecondWind (BP)
- ActionSurgeComponent → GA_ActionSurge (BP)
```

---

## 📡 4. UI Reativa (Event-Driven)

**Responsabilidade:** Atualizar UI sem usar Tick, via Delegates.

**Padrão:**
- ✅ UI **não verifica valores no Tick**
- ✅ UI se inscreve (Bind) em Delegates do ASC

**Atributos:**
- Usa `GetGameplayAttributeValueChangeDelegate` para ouvir mudanças
- Quando Vida/Mana muda, atualiza barra automaticamente
- **Desacoplado:** UI não conhece lógica de negócio

**Habilidades:**
- Escuta mudanças de Tags de Cooldown
- Usa `RegisterGameplayTagEvent`
- Desenha overlay escuro no ícone quando habilidade indisponível

**Benefícios:**
- Performance (sem Tick constante)
- Reatividade automática
- Desacoplamento completo

---

## 🔧 5. Gerenciamento de Habilidades (Handles)

**Responsabilidade:** Gerenciar concessão e remoção de habilidades sem vazamento de memória.

**Padrão:**
- Armazena `FGameplayAbilitySpecHandle` (identificadores) em `TArray`
- Ao conceder habilidade, salva o Handle
- Ao remover, usa Handle para `ClearAbility`

**Troca de Arma/Equipamento:**
1. Usa Handles para remover (`ClearAbility`) habilidades antigas
2. Antes de adicionar novas
3. Evita vazamento de memória ou habilidades duplicadas

---

## 📊 6. Data Assets Concedendo Habilidades (Data-Driven)

**Responsabilidade:** Usar Data Assets para conceder habilidades, mantendo Data-Driven.

**Padrão:**
- Cria DataAsset (ex: `UWeaponDataAsset`) com:
  - Mesh da arma
  - Animações associadas
  - **Crucialmente:** Lista de Habilidades (Classes) que a arma concede

**Equipamento:**
- Ao equipar, sistema lê DataAsset
- Chama `GiveAbility` no ASC para cada habilidade listada
- **Data-Driven:** Designers podem modificar habilidades sem código

---

## 🌐 7. Replication Modes (Multiplayer)

**Responsabilidade:** Configurar replicação adequada para Player e AI.

**Player:**
- ✅ Replication Mode: **Mixed**
- **Motivo:** Dono vê tudo (prediction), outros veem essencial
- **Benefícios:**
  - Responsividade para o dono
  - Eficiência de rede (outros não recebem tudo)

**AI:**
- ✅ Replication Mode: **Minimal**
- **Motivo:** Apenas servidor controla, clientes veem resultado visual
- **Benefícios:**
  - Economia de banda
  - Segurança (servidor autoritário)

**NetMulticast:**
- Para tocar sons/partículas que precisam aparecer para todos
- Lógica (dano) roda apenas no servidor (`HasAuthority`)

---

## 🔄 8. Migração do Projeto Atual

**Preparação Atual:**

- ✅ Dados em Components (fácil migrar para Attributes)
- ✅ Lógica em Components separados (fácil migrar para Abilities)
- ✅ Interfaces bem definidas (fácil refatorar)
- ✅ Replicação já configurada (GAS usa mesmo sistema)
- ✅ Data-Driven já implementado (Data Assets/Data Tables)
- ✅ Editor-Friendly já implementado (validação em tempo real)

**Migração Futura:**

```
CharacterDataComponent → GAS AttributeSet
- Health, MaxHealth → GAS Attributes
- FinalAbilityScores → GAS Attributes
- Lógica de cálculo → PostGameplayEffectExecute

Feature Components → GAS Abilities
- SpellcastingComponent → GA_Spellcasting (BP)
- SecondWindComponent → GA_SecondWind (BP)
- ActionSurgeComponent → GA_ActionSurge (BP)

CharacterSheetComponent → GAS Gameplay Effects
- Aplicação de regras → Gameplay Effects
- Bônus raciais → GE Duration/Infinite
- Features de classe → GE com Tags
```

---

## 📋 9. Checklist de Implementação GAS

**Antes de implementar GAS:**

- [ ] ASC criado no local correto (PlayerState para Player, Character para AI)
- [ ] AttributeSet em C com Meta-Atributos para dano
- [ ] Gameplay Abilities em Blueprint (modular: Base + Filhas)
- [ ] UI usando Delegates (sem Tick)
- [ ] Handles para gerenciar concessão/remoção de habilidades
- [ ] Data Assets concedendo habilidades (Data-Driven)
- [ ] Replication Modes configurados (Mixed para Player, Minimal para AI)
- [ ] Validação no editor mantida (Editor-Friendly)
- [ ] Data Tables para regras (Data-Driven)

---

**Navegação:** [← Data-Oriented Design](data-oriented-design.md) | [→ Regras de Implementação](regras-implementacao.md)

**Última atualização:** 2024-12-27
