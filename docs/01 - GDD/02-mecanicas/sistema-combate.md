# 2.3. Sistema de Combate

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Sistema de Combate</b></summary>

> Sistema de combate adaptado do D&D 5e (baseado em turnos) para tempo real, mantendo fidelidade às regras oficiais do Player's Handbook (PHB). Todas as mecânicas seguem as regras D&D 5e, adaptadas para gameplay em tempo real.

</details>

---

## 🔄 Adaptação de Turnos para Tempo Real

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⏱️ Conversão de Rounds para Tempo Real</b></summary>

> **Regra Base D&D 5e:**
>
> - 1 Round = 6 segundos (tempo de combate)
> - Cada personagem tem 1 Ação, 1 Movimento e 1 Reação por round
>
> **Adaptação para Tempo Real:**
>
> - **Cooldowns baseados em rounds:** Ações que normalmente levam 1 round têm cooldown de 6 segundos
> - **Ações simultâneas:** Todos os personagens agem simultaneamente (não em turnos)
> - **Reações:** Podem ser ativadas em resposta a eventos (ataques de oportunidade, etc.)
>
> **⚠️ Decisão: Ready Action (Consideração Futura)**
>
> > **Status:** Esta mecânica está sendo considerada para implementação futura, possivelmente alinhada com sistema de Surprise e emboscadas coordenadas no início do combate.
> >
> > - **📖 Ver mais detalhes:** [Ready Action - Ideias Futuras](ideias-futuras/ready-action-emboscada.md)
> > - **Nota:** Não será implementada no MVP, pode ser adicionada em atualização futura
> >
>___

</details>

---

## ⚔️ Ataque Básico (Attack Action)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Sistema de Ataques Básicos</b></summary>

> **Regra Oficial D&D 5e:**
>
> - Cada personagem pode fazer 1 ataque por ação (Action)
> - Classes marciais ganham "Extra Attack" em níveis específicos (Fighter nível 5, etc.)
> - **Extra Attack:** Permite fazer 2 ataques por ação (nível 5+)
>
> **✅ Decisão: Balanceamento de Velocidade de Combate**
>
> > **Implementação Decidida:**
> >
> > - **Ataque básico:** Cooldown de 6 segundos (mantém ritmo D&D de 1 round)
> > - **Níveis 1-4:** 1 ataque a cada 6 segundos
> > - **Níveis 5+ (Extra Attack):** 2 ataques dentro de 6 segundos (ataque 1 no segundo 0, ataque 2 no segundo 3-4)
> > - **Magias:** Cooldown baseado no nível (nível 1 = 6s, nível 2 = 7s, nível 3 = 8s)
> > - **Cantrips:** Sem cooldown (podem ser usados continuamente)
> > - **Justificativa:** Mantém fidelidade às regras D&D, ritmo balanceado
> >
>___

</details>

---

## ⚔️ Ações de Combate (Baseadas em D&D 5e)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎮 Ações Disponíveis</b></summary>

> **Attack (Ataque):**
>
> - Ataque corpo a corpo (melee) ou à distância (ranged)
> - Usa modificador de STR (melee) ou DEX (ranged)
> - Dano = dado da arma + modificador de atributo
> - **📖 Ver detalhes completos:** [Ataque Básico](#-ataque-básico-attack-action) (seção acima)
>
> **Dodge (Esquiva):**
>
> - Ação de defesa ativa
> - **Efeito D&D 5e:** Vantagem em Saving Throws, desvantagem em ataques recebidos
> - **Adaptação:** Reduz chance de acerto de inimigos em **30%** (equivalente a desvantagem estatística)
> - **Cooldown:** 6 segundos (1 round)
> - **✅ Decisão: Feedback Visual de Dodge**
>
> > **Implementação Decidida:**
> >
> > - **Dodge:** Animação de esquiva rápida (dash rápido) quando ativado
> > - **Defesa (posição defensiva):** Posição de defesa estática (postura defensiva) quando em modo defensivo
> > - Efeito visual (aura, partículas) para indicar estado ativo
> > - Indicador de status na UI
> > - Som de esquiva
>
> **Dash (Corrida):**
>
> - Ação de movimento duplo
> - **Efeito D&D 5e:** Velocidade de movimento dobrada por 1 round
> - **Adaptação:** Aumenta velocidade de movimento em 100% por 6 segundos
> - **Cooldown:** 6 segundos
>
> **Disengage (Desengajar):**
>
> - Sair de combate sem provocar ataques de oportunidade
> - **Efeito D&D 5e:** Não provoca Opportunity Attacks ao se mover
> - **Adaptação:** Remove "threat" de inimigos próximos por 6 segundos
> - **Cooldown:** 6 segundos
> - **✅ Decisão: Feedback Visual de Disengage**
>
> > **Implementação Decidida:**
> >
> > - **Animação:** Recuo rápido (backstep) quando ativado
> > - **Efeito Visual:** Brilho azul leve ao redor do personagem
> > - **Indicador de Status:** Ícone "Disengage" na UI (dura 6 segundos)
> > - **Feedback:** Personagem não provoca ataques de oportunidade durante efeito
>
> **Help (Ajudar):**
>
> - Ajudar aliado (vantagem no próximo ataque)
> - **Efeito D&D 5e:** Aliado ganha vantagem no próximo ataque
> - **Adaptação:** Aliado ganha bônus de **+4** no próximo ataque (equivalente a vantagem estatística)
> - **Cooldown:** 6 segundos
> - **✅ Decisão: Help em Single-Player e Multiplayer**
>
> > **Implementação Decidida:**
> >
> > - **Single-Player:** Help pode ser usado com companheiros NPCs (se houver sistema de companheiros)
> > - **Multiplayer:** Help funciona normalmente entre jogadores
> > - **Efeito:** Aliado ganha +4 no próximo ataque (equivalente a vantagem)
> > - **Cooldown:** 6 segundos (1 round)
>
> **Use Object (Usar Objeto):**
>
> - Interagir com objetos (portas, baús, itens)
> - **Efeito D&D 5e:** Usar item ou interagir com ambiente
> - **Adaptação:** Sistema de interação padrão do jogo
> - **Cooldown:** Instantâneo (sem cooldown)
>
> **Cast Spell (Conjurar Magia):**
>
> - Conjurar magia (usa spell slot)
> - **Efeito D&D 5e:** Conjura magia conforme regras de spellcasting
> - **Adaptação:** Sistema de spellcasting em tempo real
> - **Cooldown:** Baseado no nível da magia (nível 1 = 6s, nível 2 = 7s, nível 3 = 8s, etc.)
> - **📖 Ver também:** [Spellcasting](../03-ia-comportamento/spellcasting.md)

</details>

---

## 🛡️ Armor Class (AC) - Classe de Armadura

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Cálculo de AC</b></summary>

> **Regra Oficial D&D 5e:**
>
> **AC sem Armadura:**
>
> ```
> AC = 10 + DEX Modifier
> ```
>
> **AC com Armadura Leve (Light Armor):**
>
> ```
> AC = Armor Base AC + DEX Modifier (sem limite)
> ```
>
> **AC com Armadura Média (Medium Armor):**
>
> ```
> AC = Armor Base AC + DEX Modifier (máximo +2)
> ```
>
> **AC com Armadura Pesada (Heavy Armor):**
>
> ```
> AC = Armor Base AC (sem bônus de DEX)
> ```
>
> **AC com Escudo (Shield):**
>
> ```
> AC = AC Atual + 2
> ```
>
> **Tabela de AC Base por Armadura:**
>
> | Tipo de Armadura | AC Base | Limite DEX | Observações |
> |------------------|---------|------------|-------------|
> | **Sem Armadura** | 10 | - | + DEX modifier completo |
> | **Padded** | 11 | - | + DEX modifier completo |
> | **Leather** | 11 | - | + DEX modifier completo |
> | **Studded Leather** | 12 | - | + DEX modifier completo |
> | **Hide** | 12 | - | + DEX modifier (máx +2) |
> | **Chain Shirt** | 13 | - | + DEX modifier (máx +2) |
> | **Scale Mail** | 14 | - | + DEX modifier (máx +2) |
> | **Breastplate** | 14 | - | + DEX modifier (máx +2) |
> | **Half Plate** | 15 | - | + DEX modifier (máx +2) |
> | **Ring Mail** | 14 | - | Sem bônus de DEX |
> | **Chain Mail** | 16 | - | Sem bônus de DEX |
> | **Splint** | 17 | - | Sem bônus de DEX |
> | **Plate** | 18 | - | Sem bônus de DEX |
>
> **Exemplos de Cálculo:**
>
> - **Personagem sem armadura, DEX +3:** AC = 10 + 3 = **13**
> - **Personagem com Leather Armor (AC 11), DEX +3:** AC = 11 + 3 = **14**
> - **Personagem com Chain Mail (AC 16), DEX +3:** AC = **16** (sem bônus de DEX)
> - **Personagem com Scale Mail (AC 14), DEX +4, Escudo:** AC = 14 + 2 (DEX limitado) + 2 (escudo) = **18**
>
> **📖 Documentação Técnica:** Para implementação técnica, veja [TDD: Algoritmo de Cálculo de AC](../../02%20-%20TDD/04-regras-dnd/combate/ac-calculation-algorithm.md)
>
> **✅ Decisão: Feedback Visual de AC**
>
> > **Implementação Decidida:**
> >
> > - **UI:** AC numérico visível na ficha de personagem (ex: "AC: 18")
> > - **Feedback Visual:** Quando ataque é bloqueado por AC, mostra partículas de defesa (diferente de esquiva)
> > - **Som:** Som de metal batendo quando armadura bloqueia
> > - **Texto Flutuante:** "BLOQUEADO!" quando AC previne dano
>
> **✅ Decisão: Efeitos Visuais de AC**
>
> > **Implementação Decidida:**
> >
> > - **Armadura Pesada:** Som de metal batendo quando atacado
> > - **Escudo:** Animação de bloqueio automático quando ataque é bloqueado
> > - **AC Alto:** Partículas de defesa (aura leve) quando ataque é bloqueado
> > - **Feedback Diferencial:** Esquiva (movimento rápido) vs Bloqueio (partículas estáticas)

</details>

---

## 💥 Cálculo de Dano

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚔️ Fórmulas de Dano</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Dano de Ataque Melee (Corpo a Corpo):**
>
> ```
> Damage = Weapon Die Roll + STR Modifier
> ```
>
> **Dano de Ataque Ranged (À Distância):**
>
> ```
> Damage = Weapon Die Roll + DEX Modifier
> ```
>
> **Dano de Magia:**
>
> ```
> Damage = Spell Damage (conforme descrição da magia)
> ```
>
> **Exemplos:**
>
> - **Espada Longa (1d8), STR +3:** Dano = 1d8 + 3 (mínimo 4, máximo 11)
> - **Arco Curto (1d6), DEX +2:** Dano = 1d6 + 2 (mínimo 3, máximo 8)
> - **Fireball (nível 3):** 8d6 de dano de fogo (mínimo 8, máximo 48)
>
> **Críticos (Critical Hits):**
>
> - **Regra D&D 5e:** Natural 20 no d20 = crítico
> - **Efeito:** Todos os dados de dano são rolados novamente (dobrados)
> - **Fórmula:** `Critical Damage = (Weapon Die Roll × 2) + Modifier`
> - **Exemplo:** Espada Longa (1d8), STR +3, crítico = (1d8 × 2) + 3 = 2d8 + 3
>
> **✅ Decisão: Feedback Visual de Críticos**
>
> > **Implementação Decidida:**
> >
> > - **Efeito Visual:** Flash de luz branca/amarela, partículas especiais
> > - **Som:** Som de crítico mais impactante e alto
> > - **Texto Flutuante:** "CRÍTICO!" em fonte grande e destacada
> > - **Câmera Shake:** Leve shake (0.1s) para impacto
> > - **Animação:** Animação de impacto mais exagerada
>
> **Resistências e Vulnerabilidades:**
>
> - **Resistência:** Dano reduzido pela metade (arredondado para baixo)
> - **Vulnerabilidade:** Dano dobrado
> - **Exemplo:** Criatura com resistência a fogo recebe 10 de dano de fogo → **5 de dano**
> - **Exemplo:** Criatura vulnerável a fogo recebe 10 de dano de fogo → **20 de dano**
>
> **📖 Documentação Técnica:** Para implementação técnica, veja [TDD: Algoritmo de Cálculo de Dano](../../02%20-%20TDD/04-regras-dnd/combate/damage-calculation-algorithm.md)
>
> **✅ Decisão: Feedback Visual de Resistências/Vulnerabilidades**
>
> > **Implementação Decidida:**
> >
> > - **UI:** Ícone de resistência/vulnerabilidade na ficha de criatura (hover mostra tipo)
> > - **Feedback Visual:** Cor do número de dano muda (laranja = resistente, vermelho = vulnerável)
> > - **Texto Flutuante:** "RESISTENTE!" (laranja) ou "VULNERÁVEL!" (vermelho) quando aplicado
> > - **Partículas:** Efeito visual sutil baseado no tipo de dano

</details>

---

## 🎯 Ataques e Acertos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎲 Cálculo de Ataque</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Roll to Hit (Rolagem para Acertar):**
>
> ```
> Attack Roll = d20 + Proficiency Bonus (se proficiente) + Ability Modifier (STR ou DEX)
> ```
>
> **Comparação:**
>
> ```
> If Attack Roll >= Target AC: Hit (acertou)
> If Attack Roll < Target AC: Miss (errou)
> ```
>
> **📖 Documentação Técnica:** Para implementação técnica, veja [TDD: Algoritmo de Attack Roll](../../02%20-%20TDD/04-regras-dnd/combate/attack-roll-algorithm.md)
> ```
>
> **Natural 20 (Crítico):**
>
> - Sempre acerta (independente de AC)
> - Dano é crítico (dados dobrados)
>
> **Natural 1 (Falha Crítica):**
>
> - Sempre erra (independente de AC)
> - **✅ Decisão: Feedback Visual de Falha Crítica**
>
> > **Implementação Decidida:**
> >
> > - **Animação:** Animação de tropeço/erro breve
> > - **Efeito Visual:** Partículas de falha (cinza)
> > - **Som:** Som de erro/erro
> > - **Texto Flutuante:** "ERRO!" em fonte menor (não destaca tanto quanto crítico)
>
> **Vantagem e Desvantagem:**
>
> - **Vantagem:** Rola 2d20, usa o maior valor
> - **Desvantagem:** Rola 2d20, usa o menor valor
> - **✅ Decisão: Implementação de Vantagem/Desvantagem**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** Buff/debuff que modifica chance de acerto
> > - **Vantagem:** +5 no ataque (equivalente estatístico de vantagem)
> > - **Desvantagem:** -5 no ataque (equivalente estatístico de desvantagem)
> > - **Feedback Visual:** Ícone de vantagem (verde) ou desvantagem (vermelho) na UI
> > - **Justificativa:** Mais rápido que rolar 2 vezes, mantém fidelidade estatística
>
> **Spell Attack (Ataque de Magia):**
>
> ```
> Spell Attack Roll = d20 + Proficiency Bonus + Spellcasting Ability Modifier
> ```
>
> **Spell Save DC (Classe de Dificuldade):**
>
> ```
> Spell Save DC = 8 + Proficiency Bonus + Spellcasting Ability Modifier
> ```
>
> - Inimigo rola Saving Throw contra Spell Save DC
> - Se passar: efeito reduzido ou nenhum efeito
> - Se falhar: efeito completo

</details>

---

## 🛡️ Cobertura (Cover)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🏛️ Sistema de Cobertura</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Tipos de Cobertura:**
>
> - **Half Cover (Meia Cobertura):** +2 AC
> - **Three-Quarters Cover (Três Quartos de Cobertura):** +5 AC
> - **Full Cover (Cobertura Total):** Não pode ser atacado
>
> **✅ Decisão: Detecção Automática de Cobertura**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** Raycast do atacante para o alvo
> > - **Cálculo:** Se raycast colidir com objeto, calcula porcentagem de cobertura
> > - **Half Cover:** 25-50% do corpo coberto → +2 AC
> > - **Three-Quarters Cover:** 50-75% do corpo coberto → +5 AC
> > - **Full Cover:** 75-100% do corpo coberto → Não pode ser atacado
> > - **Feedback Visual:** Indicador "COBERTURA" na UI quando ativo
>
> **✅ Decisão: Feedback Visual de Cobertura**
>
> > **Implementação Decidida:**
> >
> > - **Indicador:** Ícone "COBERTURA" na UI quando personagem está protegido
> > - **Efeito Visual:** Aura leve (azul) ao redor do personagem quando em cobertura
> > - **Feedback:** Texto "BLOQUEADO POR COBERTURA!" quando ataque é bloqueado
> > - **Raycast Visual:** Linha de raycast mostra quando cobertura está ativa (opcional, modo debug)

</details>

---

## 📏 Alcance e Posicionamento

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Alcance de Ataques</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Alcance de Ataques Corpo a Corpo (Melee):**
>
> - **Armas de Uma Mão:** 1.5m (5 pés)
> - **Armas de Duas Mãos:** 1.5m (5 pés) - algumas armas têm alcance maior
> - **Armas com Alcance (Reach):** 3m (10 pés) - lanças, chicotes, etc.
>
> **Alcance de Ataques à Distância (Ranged):**
>
> - **Armas de Curto Alcance:** 6m (20 pés) - adagas, dardos
> - **Armas de Médio Alcance:** 30m (100 pés) - arcos, bestas
> - **Armas de Longo Alcance:** 60m (200 pés) - arcos longos, bestas pesadas
> - **Desvantagem:** Ataques à distância têm desvantagem se alvo está além do alcance normal (mas dentro do alcance longo)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🦅 Criaturas Voadoras e Alcance</summary>

> **Impacto do Voo no Combate:**
>
> **Ataques Corpo a Corpo vs. Criaturas Voadoras:**
>
> - **Regra:** Ataques corpo a corpo **não podem** atingir criaturas voadoras (a menos que o atacante também esteja voando)
> - **Exceção:** Algumas armas com alcance estendido (Reach) podem atingir criaturas voadoras baixas (altura < 3m)
> - **Feedback Visual:** Quando jogador tenta atacar criatura voadora com arma corpo a corpo, mostra mensagem "Fora de Alcance" (vermelho)
>
> **Ataques à Distância vs. Criaturas Voadoras:**
>
> - **Regra:** Ataques à distância funcionam normalmente contra criaturas voadoras
> - **Vantagem:** Criaturas voadoras geralmente não têm cobertura (estão no ar)
> - **Desvantagem:** Criaturas voadoras podem se mover rapidamente (dificulta acertar)
>
> **📖 Documentação Técnica:** Para implementação técnica, veja [TDD: Pseudocódigo de Combate](../../02%20-%20TDD/08-pseudocodigo/combate/combat-system.md)
>
> **📖 Ver detalhes completos:** [Física e Interação - Movimento Aéreo](fisica-interacao.md#movimento-aéreo-voo)

</details>

---

## ⚡ Ataques de Oportunidade (Opportunity Attacks)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🔄 Reações de Combate</b></summary>

> **Regra Oficial D&D 5e:**
>
> - Quando criatura sai do alcance de ataque corpo a corpo de inimigo, provoca Opportunity Attack
> - Inimigo pode fazer 1 ataque de oportunidade (reação)
> - **Disengage** remove oportunidade de ataque de oportunidade
>
> **✅ Decisão: Implementação de Ataques de Oportunidade**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** "Threat zone" (raio de 1.5m) ao redor de inimigos em combate corpo a corpo
> > - **Ativação:** Quando jogador sai da threat zone, inimigo ataca automaticamente
> > - **Cooldown:** 6 segundos entre ataques de oportunidade (1 por round)
> > - **Disengage:** Remove threat zone temporariamente (6 segundos)
> > - **Feedback Visual:** Círculo vermelho ao redor de inimigos mostra threat zone (opcional, pode ser desabilitado)
>
> **✅ Decisão: Feedback Visual de Threat Zone**
>
> > **Implementação Decidida:**
> >
> > - **Indicador Visual:** Círculo vermelho translúcido ao redor de inimigos (pode ser desabilitado nas opções)
> > - **UI:** Indicador "AMEAÇADO" na UI quando jogador está em threat zone
> > - **Feedback:** Pisca quando jogador está prestes a sair da threat zone
> > - **Opção:** Pode ser desabilitado para jogadores experientes
>
> **✅ Decisão: Automático vs Manual para Ataques de Oportunidade**
>
> > **Implementação Decidida:**
> >
> > - **Inimigos:** Automático (simula IA, ataca quando jogador sai do alcance)
> > - **Jogador:** Manual (jogador pode escolher quando fazer ataque de oportunidade)
> > - **UI:** Botão "Ataque de Oportunidade" aparece quando inimigo sai do alcance
> > - **Justificativa:** Inimigos agem automaticamente (IA), jogador tem controle tático

</details>

---

## 💀 Sistema de Morte e Death Saving Throws

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>☠️ Regras de Morte D&D 5e</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Quando HP chega a 0:**
>
> - Personagem fica **Inconsciente (Unconscious)**
> - Personagem fica **Incapacitado (Incapacitated)**
> - Personagem fica **Prone (Deitado)**
>
> **Death Saving Throws:**
>
> - A cada turno (6 segundos), personagem faz Death Saving Throw
> - **Sucesso (10 ou mais):** Conta como 1 sucesso
> - **Falha (9 ou menos):** Conta como 1 falha
> - **Natural 20:** Personagem recupera 1 HP (consciente)
> - **Natural 1:** Conta como 2 falhas
> - **3 Sucessos:** Personagem fica **Estável (Stable)** (não morre, mas continua inconsciente)
> - **3 Falhas:** Personagem **Morre (Dead)**
>
> **Dano enquanto está a 0 HP:**
>
> - **Dano de fonte crítica:** Conta como 1 falha automática
> - **Dano que reduz HP abaixo de 0:** Conta como 1 falha automática
> - **Dano massivo (reduz HP para -MaxHP):** Morte instantânea
>
> **✅ Decisão: Feedback Visual de Death Saving Throws**
>
> > **Implementação Decidida:**
> >
> > - **UI:** 3 slots de "Death Saves" visíveis na UI (sucessos = verde, falhas = vermelho)
> > - **Rolagem:** Automática a cada 6 segundos (1 round)
> > - **Feedback Visual:** Animação de dado rolando, resultado aparece nos slots
> > - **Texto:** "ESTÁVEL" quando alcança 3 sucessos, "MORTO" quando alcança 3 falhas
> > - **Som:** Som de tensão durante death saves
>
> **✅ Decisão: Sistema de Morte e Ressurreição**
>
> > **Implementação Decidida:**
> >
> > - **Modo Normal:** Sistema de ressurreição (magias Revivify, Raise Dead, etc.)
> > - **Modo Casual:** Opção de respawn em checkpoint (perde progresso do combate atual)
> > - **Ressurreição:** Clérigo pode usar Revivify (nível 3) dentro de 1 minuto
> > - **Game Over:** Se todos os personagens morrerem, Game Over e recomeçar da última save
> > - **Checkpoint:** Save automático antes de combates importantes
>
> **Ressurreição:**
>
> - **Revivify (nível 3):** Ressuscita dentro de 1 minuto (usa componente de 300gp)
> - **Raise Dead (nível 5):** Ressuscita dentro de 10 dias (usa componente de 500gp)
> - **Resurrection (nível 7):** Ressuscita dentro de 100 anos (usa componente de 1000gp)
> - **True Resurrection (nível 9):** Ressuscita sem limite de tempo (usa componente de 25000gp)
>
> **✅ Decisão: Sistema de Ressurreição**
>
> > **Implementação Decidida:**
> >
> > - **Revivify (nível 3):** Implementado (ressuscita dentro de 1 minuto, componente 300 GP)
> > - **Raise Dead (nível 5):** Implementado (ressuscita dentro de 10 dias, componente 500 GP)
> > - **Single-Player:** NPCs podem usar ressurreição se tiverem a magia
> > - **Multiplayer:** Jogadores podem usar ressurreição em aliados
> > - **Componentes:** Componentes mágicos podem ser comprados em Phandalin

</details>

---

## 🎲 Saving Throws (Testes de Resistência)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🛡️ Testes de Resistência</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Saving Throw:**
>
> ```
> Saving Throw = d20 + Proficiency Bonus (se proficiente) + Ability Modifier
> ```
>
> **Tipos de Saving Throws:**
>
> - **STR:** Resistir a empurrões, agarramentos
> - **DEX:** Esquivar de explosões, armadilhas
> - **CON:** Resistir a venenos, doenças, concentração
> - **INT:** Resistir a efeitos mentais (raros)
> - **WIS:** Resistir a encantamentos, medo
> - **CHA:** Resistir a banimento, possessão
>
> **Spell Save DC:**
>
> ```
> Spell Save DC = 8 + Proficiency Bonus + Spellcasting Ability Modifier
> ```
>
> - Inimigo rola Saving Throw contra Spell Save DC
> - **Sucesso:** Efeito reduzido ou nenhum efeito
> - **Falha:** Efeito completo
>
> **✅ Decisão: Feedback Visual de Saving Throws**
>
> > **Implementação Decidida:**
> >
> > - **Rolagem:** Automática quando efeito é aplicado
> > - **Feedback Visual:** Animação de dado rolando, resultado aparece
> > - **Texto Flutuante:** "RESISTIU!" (verde) ou "FALHOU!" (vermelho) na UI
> > - **UI:** Mostra DC do saving throw e resultado da rolagem
> > - **Som:** Som de sucesso (verde) ou falha (vermelho)

</details>

---

## 🎭 Condições (Conditions)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Estados de Condição</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Condições Principais:**
>
> - **Blinded (Cego):** Não pode ver, ataques têm desvantagem, ataques recebidos têm vantagem
> - **Charmed (Encantado):** Não pode atacar encantador, encantador tem vantagem em interações sociais
> - **Deafened (Surdo):** Não pode ouvir, falha em testes de percepção baseados em som
> - **Frightened (Assustado):** Desvantagem em testes e ataques enquanto vê fonte do medo
> - **Grappled (Agarrado):** Velocidade = 0, não pode se mover
> - **Incapacitated (Incapacitado):** Não pode realizar ações ou reações
> - **Invisible (Invisível):** Não pode ser visto, ataques têm vantagem, ataques recebidos têm desvantagem
> - **Paralyzed (Paralisado):** Incapacitado, não pode se mover, ataques recebidos têm vantagem, críticos automáticos
> - **Petrified (Petrificado):** Transformado em pedra, resistente a dano, incapacitado
> - **Poisoned (Envenenado):** Desvantagem em ataques e testes
> - **Prone (Deitado):** Deitado no chão, ataques corpo a corpo têm vantagem, ataques à distância têm desvantagem
> - **Restrained (Restrito):** Velocidade = 0, desvantagem em ataques, ataques recebidos têm vantagem
> - **Stunned (Atordoado):** Incapacitado, não pode se mover, ataques recebidos têm vantagem
> - **Unconscious (Inconsciente):** Incapacitado, deitado, não pode se mover ou falar, ataques recebidos têm vantagem, críticos automáticos
>
> **✅ Decisão: Condições para MVP**
>
> > **Implementação Decidida - Prioridade Alta (MVP):**
> >
> > - **Poisoned:** Implementado (desvantagem em ataques e testes)
> > - **Stunned:** Implementado (incapacitado, ataques recebidos têm vantagem)
> > - **Paralyzed:** Implementado (incapacitado, críticos automáticos)
> > - **Prone:** Implementado (deitado, ataques corpo a corpo têm vantagem, ranged têm desvantagem)
> > - **Frightened:** Implementado (desvantagem enquanto vê fonte do medo)
> >
> > **Prioridade Média (Pós-MVP):**
> >
> > - **Blinded, Grappled, Restrained:** Adicionar após MVP
> >
> > **Prioridade Baixa (Futuro):**
> >
> > - **Charmed, Invisible, Petrified:** Adicionar quando sistemas relacionados estiverem prontos
>
> **✅ Decisão: Feedback Visual de Condições**
>
> > **Implementação Decidida:**
> >
> > - **UI:** Ícone de condição na UI (ao lado do HP), tooltip ao passar mouse
> > - **Efeito Visual no Personagem:**
> >   - **Poisoned:** Cor verde, partículas de veneno
> >   - **Stunned:** Estrelas girando, animação de atordoamento
> >   - **Paralyzed:** Cor azul, animação congelada
> >   - **Frightened:** Cor roxa, animação de medo
> >   - **Prone:** Personagem deitado no chão
> > - **Timer:** Mostra duração restante da condição (se aplicável)
>
> **Duração de Condições:**
>
> - **Instantânea:** Remove no final do turno
> - **Concentração:** Remove quando concentração é quebrada
> - **Duração fixa:** Remove após X rounds/segundos
> - **Até remoção:** Remove com magia ou habilidade específica
>
> **✅ Decisão: Gerenciamento de Duração de Condições**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** Timer baseado em rounds (1 round = 6 segundos)
> > - **UI:** Timer visual na UI mostra rounds restantes (ex: "3 rounds")
> > - **Ticks:** Condição reduz 1 round a cada 6 segundos
> > - **Concentração:** Condições de concentração terminam quando concentração é quebrada
> > - **Instantânea:** Condições instantâneas terminam no final do round

</details>

---

## ⚔️ Tipos de Dano (Damage Types)

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>💥 Tipos de Dano D&D 5e</b></summary>

> **Tipos de Dano Oficiais:**
>
> - **Acid (Ácido)**
> - **Cold (Frio)**
> - **Fire (Fogo)**
> - **Force (Força)**
> - **Lightning (Raio)**
> - **Necrotic (Necrótico)**
> - **Poison (Veneno)**
> - **Psychic (Psíquico)**
> - **Radiant (Radiante)**
> - **Thunder (Trovão)**
> - **Bludgeoning (Contundente)** - Físico
> - **Piercing (Perfurante)** - Físico
> - **Slashing (Cortante)** - Físico
>
> **Resistências e Vulnerabilidades:**
>
> - Criaturas podem ter resistência ou vulnerabilidade a tipos específicos de dano
> - **Resistência:** Dano reduzido pela metade
> - **Vulnerabilidade:** Dano dobrado
> - **Imunidade:** Não recebe dano do tipo
>
> **✅ Decisão: Tipos de Dano para Implementação**
>
> > **Implementação Decidida:**
> >
> > - **MVP:** Implementar todos os tipos de dano D&D 5e (fidelidade completa)
> > - **Tipos:** Fire, Cold, Lightning, Poison, Acid, Necrotic, Radiant, Psychic, Thunder, Force, Physical (Bludgeoning, Piercing, Slashing)
> > - **Justificativa:** Fidelidade a D&D 5e requer todos os tipos
> > - **Resistências/Vulnerabilidades:** Implementadas para todos os tipos
>
> **✅ Decisão: Feedback Visual de Tipos de Dano**
>
> > **Implementação Decidida:**
> >
> > - **Cor do Número de Dano:**
> >   - **Fire:** Vermelho
> >   - **Cold:** Azul
> >   - **Lightning:** Amarelo/Branco
> >   - **Poison:** Verde
> >   - **Necrotic:** Roxo escuro
> >   - **Radiant:** Dourado
> >   - **Physical:** Branco/Cinza
> > - **Efeitos Visuais:** Partículas baseadas no tipo (fogo, gelo, raio, etc.)
> > - **Som:** Som específico para cada tipo de dano

</details>

---

## 🎯 Iniciativa e Ordem de Turnos

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⚡ Sistema de Iniciativa</b></summary>

> **Regra Oficial D&D 5e:**
>
> **Iniciativa:**
>
> ```
> Initiative = d20 + DEX Modifier
> ```
>
> - Ordem de turnos baseada em iniciativa (maior vai primeiro)
> - Em caso de empate, DEX maior vai primeiro
>
> **✅ Decisão: Sistema de Iniciativa em Tempo Real**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** Iniciativa removida (não necessário em tempo real)
> > - **Substituição:** Todos agem simultaneamente
> > - **Velocidade de Ações:** Baseada em DEX (maior DEX = cooldowns ligeiramente mais rápidos, opcional)
> > - **Justificativa:** Simplifica sistema, mantém gameplay fluido em tempo real
>
> **✅ Decisão: Ordem de Ações em Tempo Real**
>
> > **Implementação Decidida:**
> >
> > - **Sistema:** Todos agem simultaneamente (padrão de tempo real)
> > - **Velocidade Opcional:** DEX pode reduzir cooldowns em 5-10% (opcional, para balanceamento)
> > - **Justificativa:** Mantém gameplay fluido, sem necessidade de ordem de turnos

</details>

---

## 🎮 Feedback Visual e Sonoro

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👁️ Feedback do Combate</b></summary>

> **✅ Decisão: Feedback Visual Completo**
>
> > **Implementação Decidida - Essenciais:**
> >
> > - **Dano Flutuante:** Números de dano flutuando sobre alvos (cor baseada no tipo)
> > - **Indicador de HP:** Barra de HP sobre inimigos (vermelha quando baixo)
> > - **Feedback de Acerto:** Efeito visual de impacto quando ataque acerta
> > - **Feedback de Erro:** Efeito visual de erro quando ataque erra
> > - **Feedback de Crítico:** Efeito especial (flash, partículas, som)
> >
> > **Importantes:**
> >
> > - **Indicador de Status:** Ícones de condições na UI (ao lado do HP)
> > - **Feedback de Bloqueio:** Partículas de defesa quando bloqueado por AC
> > - **Feedback de Esquiva:** Animação de esquiva quando ataque é esquivado
> > - **Feedback de Resistência:** Cor laranja no número de dano quando resistente
>
> **✅ Decisão: Feedback Sonoro Completo**
>
> > **Implementação Decidida - Essenciais:**
> >
> > - **SFX de Ataque:** Som de impacto quando ataque acerta (varia por tipo de arma)
> > - **SFX de Erro:** Som de erro quando ataque erra
> > - **SFX de Crítico:** Som especial e impactante para críticos
> > - **SFX de Morte:** Som quando criatura morre
> >
> > **Importantes:**
> >
> > - **SFX de Bloqueio:** Som de metal batendo quando bloqueado por AC
> > - **SFX de Esquiva:** Som de movimento rápido quando esquivado
> > - **SFX de Condições:** Sons específicos para cada condição (veneno, stun, etc.)
> > - **SFX de Tipos de Dano:** Sons específicos para cada tipo (fogo, gelo, raio, etc.)

</details>

---

## 💡 Exemplos Práticos de Uso

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🎯 Cenários da Campanha Phandelver</b></summary>

> **Exemplo 1: Combate Inicial contra Goblins (Emboscada na Estrada)**
>
> **Situação:** Grupo é emboscado por 4 goblins enquanto escolta carroça para Phandalin.
>
> **Execução:**
>
> 1. **Iniciativa (adaptado):** Todos agem simultaneamente em tempo real
> 2. **Fighter (nível 1):** Move-se em direção ao goblin mais próximo (6m de movimento)
> 3. **Ataque:** Fighter ataca com espada longa (1d8+3 de dano, STR +3)
> 4. **Roll to Hit:** d20 + 2 (proficiency) + 3 (STR) = d20+5 vs AC 15 do goblin
> 5. **Resultado:** Rola 18, total 23 → **Acertou!**
> 6. **Dano:** 1d8+3 = 7 de dano → Goblin tem 7 HP, **morre**
>
> **Resultado:** Fighter elimina um goblin no primeiro ataque.
>
> **Exemplo 2: Combate contra Klarg (Boss Cragmaw Hideout)**
>
> **Situação:** Klarg (Bugbear, CR 1) está atacando grupo. Fighter nível 1 tenta atacar.
>
> **Execução:**
>
> 1. **Fighter:** Move-se para alcance corpo a corpo (1.5m)
> 2. **Ataque:** Espada longa (1d8+3)
> 3. **Roll to Hit:** d20+5 vs AC 16 de Klarg
> 4. **Resultado:** Rola 10, total 15 → **Errou!** (precisa de 16+)
> 5. **Klarg contra-ataca:** Clava (2d8+2 de dano)
> 6. **Roll to Hit:** d20+4 vs AC 16 do Fighter (Chain Mail)
> 7. **Resultado:** Rola 18, total 22 → **Acertou!**
> 8. **Dano:** 2d8+2 = 12 de dano → Fighter tem 12/12 HP, **cai para 0 HP**
> 9. **Death Saving Throws:** Fighter faz saving throw a cada 6 segundos
>
> **Resultado:** Fighter precisa de ajuda (cura ou estabilização) ou pode morrer.
>
> **Exemplo 3: Uso de Dodge em Combate**
>
> **Situação:** Clérigo está sendo atacado por 2 goblins. Usa Dodge para se defender.
>
> **Execução:**
>
> 1. **Clérigo:** Ativa ação **Dodge** (cooldown 6 segundos)
> 2. **Efeito Visual:** Animação de esquiva rápida (dash rápido)
> 3. **Efeito Mecânico:** Reduz chance de acerto de inimigos em 25% (desvantagem adaptada)
> 4. **Goblin 1 ataca:** Roll to Hit reduzido (d20+4 → equivalente a -5 = d20-1)
> 5. **Goblin 2 ataca:** Roll to Hit reduzido (mesma penalidade)
> 6. **Resultado:** Ambos os goblins têm maior chance de errar
>
> **Resultado:** Clérigo sobrevive ao ataque múltiplo, mas não pode atacar neste round.
>
> **Exemplo 4: Crítico em Combate**
>
> **Situação:** Rogue ataca goblin com adaga. Rola Natural 20 (crítico).
>
> **Execução:**
>
> 1. **Rogue:** Ataque com adaga (1d4+3, DEX +3)
> 2. **Roll to Hit:** Rola **Natural 20** → **Crítico automático!**
> 3. **Efeito Visual:** Flash de luz, partículas especiais, som de crítico
> 4. **Dano Crítico:** (1d4 × 2) + 3 = 2d4+3
> 5. **Rolagem:** 2d4 = 6, total **9 de dano**
> 6. **Goblin:** Tem 7 HP, recebe 9 de dano → **Morre instantaneamente**
>
> **Resultado:** Rogue elimina goblin com um ataque crítico espetacular.
>
> **Exemplo 5: Ataque de Oportunidade**
>
> **Situação:** Fighter está em combate corpo a corpo com goblin. Tenta recuar sem usar Disengage.
>
> **Execução:**
>
> 1. **Fighter:** Move-se para sair do alcance de ataque corpo a corpo (1.5m)
> 2. **Sistema detecta:** Fighter saiu da "threat zone" do goblin
> 3. **Goblin:** Ativa **Opportunity Attack** automaticamente (reação)
> 4. **Ataque:** Goblin ataca com adaga (1d4+2)
> 5. **Roll to Hit:** d20+4 vs AC 16 do Fighter
> 6. **Resultado:** Rola 15, total 19 → **Acertou!**
> 7. **Dano:** 1d4+2 = 5 de dano
> 8. **Fighter:** Recebe 5 de dano enquanto recua
>
> **Resultado:** Fighter sofre dano ao recuar sem usar Disengage. Deveria ter usado Disengage primeiro.
>
> **Exemplo 6: Resistência a Dano (Goblin vs Fire)**
>
> **Situação:** Wizard lança **Fire Bolt** (cantrip) em goblin. Goblin tem resistência a fogo (hipotético).
>
> **Execução:**
>
> 1. **Wizard:** Conjura **Fire Bolt** (1d10 de dano de fogo)
> 2. **Roll to Hit:** d20+5 vs AC 15 do goblin → **Acertou!**
> 3. **Dano:** 1d10 = 8 de dano de fogo
> 4. **Resistência:** Goblin tem resistência a fogo → Dano reduzido pela metade
> 5. **Dano Final:** 8 / 2 = **4 de dano** (arredondado para baixo)
> 6. **Feedback Visual:** Número de dano aparece em laranja (fogo), texto "RESISTENTE!" aparece
>
> **Resultado:** Goblin recebe menos dano devido à resistência, mas ainda sofre dano.
>
> **Exemplo 7: Cobertura em Combate**
>
> **Situação:** Rogue está atirando com arco curto em goblin. Goblin está atrás de uma rocha.
>
> **Execução:**
>
> 1. **Rogue:** Ataca com arco curto (1d6+3, DEX +3)
> 2. **Sistema detecta:** Raycast do Rogue para goblin colide com rocha
> 3. **Cálculo de Cobertura:** 50% do corpo do goblin está coberto → **Half Cover**
> 4. **Bônus de AC:** Goblin ganha +2 AC (de 15 para 17)
> 5. **Roll to Hit:** d20+5 vs AC 17 (com cobertura) → **Precisa de 12+**
> 6. **Resultado:** Rola 10, total 15 → **Errou!** (precisava de 17+)
> 7. **Feedback Visual:** Indicador mostra "COBERTURA" na UI, efeito de bloqueio visual
>
> **Resultado:** Goblin está protegido pela cobertura, dificultando acertá-lo.

</details>

---

## 📊 Resumo das Decisões Criativas Pendentes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>✅ Checklist de Decisões (Todas Resolvidas)</b></summary>

> **Adaptação de Turnos:**
>
> - [x] ~~Como implementar "Ready Action" em tempo real?~~ ⚠️ **Consideração Futura** - Ver [Ideias Futuras](ideias-futuras/ready-action-emboscada.md)
> - [x] Como balancear velocidade de combate (cooldowns)? ✅ **Decidido:** Ataques básicos 6s, magias baseado no nível, cantrips sem cooldown
>
> **Ações:**
>
> - [x] Como mostrar Dodge visualmente? ✅ **Decidido:** Esquiva rápida (dash) para Dodge, posição de defesa para defesa
> - [x] Como mostrar Disengage visualmente? ✅ **Decidido:** Recuo rápido, brilho azul, indicador na UI
> - [x] Help será usado em combate multiplayer ou apenas com NPCs? ✅ **Decidido:** Funciona em ambos, +4 no próximo ataque do aliado
>
> **AC e Dano:**
>
> - [x] Como mostrar AC na UI? ✅ **Decidido:** AC numérico na ficha, partículas quando bloqueado
> - [x] AC afeta visualmente o personagem? ✅ **Decidido:** Sim, som de metal, animação de bloqueio com escudo
> - [x] Como mostrar críticos visualmente? ✅ **Decidido:** Flash, partículas, som especial, texto "CRÍTICO!", camera shake
> - [x] Como mostrar resistências/vulnerabilidades na UI? ✅ **Decidido:** Ícone na ficha, cor do dano, texto flutuante
>
> **Ataques:**
>
> - [x] Falha crítica tem efeito especial? ✅ **Decidido:** Animação de tropeço, partículas cinza, som de erro, texto "ERRO!"
> - [x] Como implementar vantagem/desvantagem em tempo real? ✅ **Decidido:** +5/-5 no ataque (equivalente estatístico), ícone na UI
>
> **Cobertura:**
>
> - [x] Como detectar cobertura automaticamente? ✅ **Decidido:** Raycast automático, calcula porcentagem de cobertura
> - [x] Cobertura afeta visualmente? ✅ **Decidido:** Ícone "COBERTURA" na UI, aura azul, texto quando bloqueado
>
> **Ataques de Oportunidade:**
>
> - [x] Como implementar em tempo real? ✅ **Decidido:** Threat zone de 1.5m, ataque automático quando jogador sai
> - [x] Como mostrar threat zone visualmente? ✅ **Decidido:** Círculo vermelho translúcido (pode desabilitar), indicador "AMEAÇADO" na UI
> - [x] Ataques de oportunidade são automáticos ou manuais? ✅ **Decidido:** Automático para inimigos, manual para jogador
>
> **Morte:**
>
> - [x] Como mostrar Death Saving Throws em tempo real? ✅ **Decidido:** 3 slots na UI, rolagem automática a cada 6s, feedback visual
> - [x] O que acontece quando personagem morre? ✅ **Decidido:** Sistema de ressurreição (Revivify, Raise Dead) + opção de respawn em checkpoint
> - [x] Ressurreição será implementada? ✅ **Decidido:** Sim, Revivify (nível 3) e Raise Dead (nível 5) implementados
>
> **Saving Throws:**
>
> - [x] Como mostrar Saving Throws em tempo real? ✅ **Decidido:** Rolagem automática, animação de dado, texto "RESISTIU!" ou "FALHOU!"
>
> **Condições:**
>
> - [x] Quais condições serão implementadas no MVP? ✅ **Decidido:** Poisoned, Stunned, Paralyzed, Prone, Frightened (MVP)
> - [x] Como mostrar condições visualmente? ✅ **Decidido:** Ícone na UI, efeito visual no personagem, tooltip, timer
> - [x] Como gerenciar duração de condições em tempo real? ✅ **Decidido:** Timer baseado em rounds (6s por round), reduz 1 round a cada tick
>
> **Tipos de Dano:**
>
> - [x] Todos os tipos de dano serão implementados? ✅ **Decidido:** Sim, todos os tipos D&D 5e (fidelidade completa)
> - [x] Como mostrar tipos de dano visualmente? ✅ **Decidido:** Cor do número, partículas específicas, som específico
>
> **Iniciativa:**
>
> - [x] Iniciativa será usada em tempo real? ✅ **Decidido:** Não, removida (não necessário em tempo real)
> - [x] Como determinar quem age primeiro em tempo real? ✅ **Decidido:** Todos agem simultaneamente, DEX pode reduzir cooldowns opcionalmente
>
> **Feedback:**
>
> - [x] Quais feedbacks visuais serão implementados? ✅ **Decidido:** Dano flutuante, HP bar, acerto/erro/crítico, status, bloqueio/esquiva/resistência
> - [x] Quais feedbacks sonoros serão implementados? ✅ **Decidido:** Ataque, erro, crítico, morte, bloqueio, esquiva, condições, tipos de dano

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Sistemas de Personagem](sistemas-personagem.md)
> - [→ Próxima: Sistema de Equipamentos](equipamentos.md)
> - [📖 Sistema de Inventário](inventario.md)
> - [📖 Sistema de Rest](rest.md)
> - [📖 Sistema de Spellcasting](spellcasting.md) - Magias em combate
**📖 Documentação Técnica (TDD):**

Para implementação técnica, consulte:

- **[TDD: Pseudocódigo de Combate](../../02%20-%20TDD/08-pseudocodigo/combate/combat-system.md)** - Sistema completo de combate
- **[TDD: Algoritmos de Combate](../../02%20-%20TDD/04-regras-dnd/combate/index.md)** - Algoritmos técnicos (AC, Dano, Ataque)
- **[TDD: Data Tables - Combate](../../02%20-%20TDD/05-guias/data-tables/combate/spell-datatable.md)** - SpellDataTable, DamageTypeDataTable, ConditionDataTable
- **[TDD: API de Componentes](../../02%20-%20TDD/02-api/componentes/index.md)** - Componentes de combate

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Sistema de combate baseado em D&D 5e |
| v1.1 | 2024-12-27 | Adicionadas referências para documentação técnica (TDD) |
| v2.0 | 2024-12-27 | Expansão completa - Resolvidas todas as decisões criativas pendentes, adicionados exemplos práticos |

**Última atualização:** 2024-12-27
