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
> **❓ Decisão Criativa: Como implementar "Ready Action" em tempo real?**
>
> > **⚠️ CONSIDERAÇÃO FUTURA:** Esta mecânica está sendo considerada para implementação futura, possivelmente alinhada com sistema de Surprise e emboscadas coordenadas no início do combate.
> >
> > - **📖 Ver mais detalhes:** [Ready Action - Ideias Futuras](ideias-futuras/ready-action-emboscada.md)
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
> **❓ Decisão Criativa: Como balancear velocidade de combate e ataques por turno?**
>
> > **💡 Ideia Atual (Em Consideração):**
> >
> > - **Ataque básico:** Cooldown de 6 segundos (mantém ritmo D&D de 1 round)
> > - **Nível 5+ (Extra Attack):** Personagem pode fazer 2 ataques no mesmo "turno" (dentro de 6 segundos)
> > - **Bonus Action:** Equilibrar com bonus action para personagem fazer mais alguma coisa
> > - **Justificativa:** Balanceamento do jogo depende muito de ataques por turno, então manter 6 segundos garante fidelidade às regras D&D
> >
> > **Sugestões Alternativas:**
> >
> > - Ataques básicos: cooldown de 1-2 segundos (mais rápido que 6 segundos)
> > - Ações especiais: cooldown de 6 segundos (mantém ritmo D&D)
> > - Magias: cooldown baseado no nível da magia (nível 1 = 3s, nível 2 = 4s, etc.)
> > - **Teste:** Ajustar baseado em playtesting para encontrar ritmo ideal
>
> **Implementação Proposta:**
>
> - **Níveis 1-4:** 1 ataque a cada 6 segundos
> - **Níveis 5+ (com Extra Attack):** 2 ataques dentro de 6 segundos (ex: ataque 1 no segundo 0, ataque 2 no segundo 3)
> - **Bonus Action:** Pode ser usada para ações adicionais (segundo ataque com arma leve, habilidades de classe, etc.)
> - **❓ Decisão Criativa: Como distribuir os 2 ataques dentro dos 6 segundos?**
>
> > **Sugestão:**
> >
> > - **Opção 1:** Ataques rápidos (ataque 1 no segundo 0, ataque 2 no segundo 2-3)
> > - **Opção 2:** Ataques espaçados (ataque 1 no segundo 0, ataque 2 no segundo 4-5)
> > - **Opção 3:** Ataques simultâneos (ambos no mesmo momento, mas com animação dupla)
> > - **Recomendação:** Ataques espaçados (mais tático, permite ajuste de posicionamento)
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
> - **Adaptação:** Reduz chance de acerto de inimigos em X% (❓ definir valor: 25%? 50%?)
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
> - **❓ Decisão Criativa: Como mostrar visualmente que personagem está em Disengage?**
>
> > **Sugestão:**
> >
> > - Animação de recuo/retirada
> > - Efeito visual sutil (brilho leve)
> > - Indicador de status na UI
>
> **Help (Ajudar):**
>
> - Ajudar aliado (vantagem no próximo ataque)
> - **Efeito D&D 5e:** Aliado ganha vantagem no próximo ataque
> - **Adaptação:** Aliado ganha bônus de +X no próximo ataque (❓ definir valor: +2? +4?)
> - **Cooldown:** 6 segundos
> - **❓ Decisão Criativa: Help será usado em combate multiplayer ou apenas com NPCs?**
>
> > **Sugestão:**
> >
> > - Se multiplayer: manter Help (útil para cooperação)
> > - Se single-player: Help pode ser usado com companheiros (NPCs)
> > - **Alternativa:** Remover Help se não houver aliados controláveis
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
> - **Cooldown:** Baseado no nível da magia (❓ definir: nível 1 = 3s, nível 2 = 4s, etc.)
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
> **❓ Decisão Criativa: Como mostrar AC na UI?**
>
> > **Sugestão:**
> >
> > - Mostrar AC numérico na ficha de personagem
> > - Mostrar "chance de acerto" do inimigo (baseado em AC vs ataque do inimigo)
> > - Feedback visual quando ataque é bloqueado (diferente de esquiva)
> > - **Alternativa:** Mostrar apenas quando personagem é atacado (popup "AC 18 bloqueou!")
>
> **❓ Decisão Criativa: AC afeta visualmente o personagem?**
>
> > **Sugestão:**
> >
> > - AC alto = partículas de defesa quando atacado
> > - Escudo = animação de bloqueio automático
> > - Armadura pesada = som de metal batendo quando atacado
> > - **Alternativa:** Apenas feedback numérico (sem efeitos visuais)

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
> **❓ Decisão Criativa: Como mostrar críticos visualmente?**
>
> > **Sugestão:**
> >
> > - Efeito visual especial (flash, partículas)
> > - Som de crítico (som mais impactante)
> > - Texto "CRÍTICO!" flutuando
> > - Câmera shake leve
> > - **Alternativa:** Apenas número maior (sem efeitos especiais)
>
> **Resistências e Vulnerabilidades:**
>
> - **Resistência:** Dano reduzido pela metade (arredondado para baixo)
> - **Vulnerabilidade:** Dano dobrado
> - **Exemplo:** Criatura com resistência a fogo recebe 10 de dano de fogo → **5 de dano**
> - **Exemplo:** Criatura vulnerável a fogo recebe 10 de dano de fogo → **20 de dano**
>
> **❓ Decisão Criativa: Como mostrar resistências/vulnerabilidades na UI?**
>
> > **Sugestão:**
> >
> > - Mostrar ícone de resistência/vulnerabilidade na ficha de criatura
> > - Feedback visual quando dano é reduzido/aumentado
> > - Texto "RESISTENTE!" ou "VULNERÁVEL!" quando aplicado
> > - **Alternativa:** Apenas número menor/maior (sem feedback visual)

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
> **Natural 20 (Crítico):**
>
> - Sempre acerta (independente de AC)
> - Dano é crítico (dados dobrados)
>
> **Natural 1 (Falha Crítica):**
>
> - Sempre erra (independente de AC)
> - **❓ Decisão Criativa: Falha crítica tem efeito especial?**
>
> > **Sugestão:**
> >
> > - Animação de tropeço/erro
> > - Efeito visual de falha
> > - Som de erro
> > - **Alternativa:** Apenas erra (sem efeitos especiais)
>
> **Vantagem e Desvantagem:**
>
> - **Vantagem:** Rola 2d20, usa o maior valor
> - **Desvantagem:** Rola 2d20, usa o menor valor
> - **❓ Decisão Criativa: Como implementar vantagem/desvantagem em tempo real?**
>
> > **Sugestão:**
> >
> > - Sistema de "buff/debuff" que modifica chance de acerto
> > - Vantagem = +5 no ataque (equivalente estatístico)
> > - Desvantagem = -5 no ataque (equivalente estatístico)
> > - **Alternativa:** Rolar 2 vezes e usar melhor/pior (mais fiel, mas pode ser lento)
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
> **❓ Decisão Criativa: Como detectar cobertura automaticamente?**
>
> > **Sugestão:**
> >
> > - Sistema de raycast do atacante para o alvo
> > - Se raycast colidir com objeto: calcula porcentagem de cobertura
> > - **Half Cover:** 25-50% do corpo coberto
> > - **Three-Quarters Cover:** 50-75% do corpo coberto
> > - **Full Cover:** 75-100% do corpo coberto
> > - **Alternativa:** Cobertura manual (jogador se posiciona atrás de objetos)
>
> **❓ Decisão Criativa: Cobertura afeta visualmente?**
>
> > **Sugestão:**
> >
> > - Indicador visual quando personagem está em cobertura
> > - Efeito de "proteção" visual (aura leve)
> > - Feedback quando ataque é bloqueado por cobertura
> > - **Alternativa:** Apenas cálculo numérico (sem feedback visual)

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
> **❓ Decisão Criativa: Como implementar em tempo real?**
>
> > **Sugestão:**
> >
> > - Sistema de "threat zone" ao redor de inimigos
> > - Quando jogador sai da threat zone: inimigo ataca automaticamente
> > - Cooldown de 6 segundos entre ataques de oportunidade (1 por round)
> > - **Alternativa:** Ataque de oportunidade manual (jogador precisa ativar)
>
> **❓ Decisão Criativa: Como mostrar threat zone visualmente?**
>
> > **Sugestão:**
> >
> > - Círculo vermelho ao redor de inimigos (mostra alcance de ameaça)
> > - Indicador de "você está sendo ameaçado" na UI
> > - **Alternativa:** Sem indicador visual (jogador aprende por experiência)
>
> **❓ Decisão Criativa: Ataques de oportunidade são automáticos ou manuais?**
>
> > **Sugestão:**
> >
> > - **Automático:** Inimigo ataca automaticamente quando jogador sai do alcance
> > - **Manual:** Jogador pode escolher quando fazer ataque de oportunidade (mais controle)
> > - **Híbrido:** Automático para inimigos, manual para jogador
> > - **Recomendação:** Automático para inimigos (simula IA), manual para jogador (mais controle)

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
> **❓ Decisão Criativa: Como mostrar Death Saving Throws em tempo real?**
>
> > **Sugestão:**
> >
> > - UI mostra 3 slots de "Death Saves" (sucessos/falhas)
> > - Rolagem automática a cada 6 segundos
> > - Feedback visual para cada sucesso/falha
> > - Texto "ESTÁVEL" quando alcança 3 sucessos
> > - **Alternativa:** Sistema automático sem mostrar ao jogador (mais simples)
>
> **❓ Decisão Criativa: O que acontece quando personagem morre?**
>
> > **Sugestão:**
> >
> > - **Opção 1:** Respawn em checkpoint (perde progresso do combate)
> > - **Opção 2:** Morte permanente (hardcore mode)
> > - **Opção 3:** Sistema de ressurreição (magias, itens, NPCs)
> > - **Opção 4:** Game Over e recomeçar da última save
> > - **Recomendação:** Sistema de ressurreição (mais fiel a D&D) + opção de respawn para gameplay mais casual
>
> **Ressurreição:**
>
> - **Revivify (nível 3):** Ressuscita dentro de 1 minuto (usa componente de 300gp)
> - **Raise Dead (nível 5):** Ressuscita dentro de 10 dias (usa componente de 500gp)
> - **Resurrection (nível 7):** Ressuscita dentro de 100 anos (usa componente de 1000gp)
> - **True Resurrection (nível 9):** Ressuscita sem limite de tempo (usa componente de 25000gp)
>
> **❓ Decisão Criativa: Ressurreição será implementada?**
>
> > **Sugestão:**
> >
> > - Se multiplayer: implementar ressurreição (importante para cooperação)
> > - Se single-player: pode ser simplificado (respawn em checkpoint)
> > - **Recomendação:** Implementar pelo menos Revivify (nível 3) para gameplay fiel a D&D

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
> **❓ Decisão Criativa: Como mostrar Saving Throws em tempo real?**
>
> > **Sugestão:**
> >
> > - Rolagem automática quando efeito é aplicado
> > - Feedback visual (sucesso/falha)
> > - Texto "RESISTIU!" ou "FALHOU!" na UI
> > - **Alternativa:** Sistema automático sem mostrar ao jogador (mais simples)

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
> **❓ Decisão Criativa: Quais condições serão implementadas no MVP?**
>
> > **Sugestão (Prioridade Alta):**
> >
> > - **Poisoned:** Essencial para venenos e magias
> > - **Stunned:** Essencial para combate
> > - **Paralyzed:** Essencial para magias
> > - **Prone:** Essencial para combate corpo a corpo
> > - **Frightened:** Essencial para magias e habilidades
> >
> > **Sugestão (Prioridade Média):**
> >
> > - **Blinded:** Útil para magias
> > - **Grappled:** Útil para combate
> > - **Restrained:** Útil para magias
> >
> > **Sugestão (Prioridade Baixa):**
> >
> > - **Charmed:** Complexo (requer sistema de diálogo)
> > - **Invisible:** Complexo (requer sistema de stealth)
> > - **Petrified:** Raro (pode ser adicionado depois)
>
> **❓ Decisão Criativa: Como mostrar condições visualmente?**
>
> > **Sugestão:**
> >
> > - Ícone de condição na UI (ao lado do HP)
> > - Efeito visual no personagem (partículas, cor, animação)
> > - Tooltip explicando efeito da condição
> > - **Exemplos:**
> >   - **Poisoned:** Cor verde, partículas de veneno
> >   - **Stunned:** Estrelas girando, animação de atordoamento
> >   - **Paralyzed:** Cor azul, animação congelada
> >   - **Frightened:** Cor roxa, animação de medo
>
> **Duração de Condições:**
>
> - **Instantânea:** Remove no final do turno
> - **Concentração:** Remove quando concentração é quebrada
> - **Duração fixa:** Remove após X rounds/segundos
> - **Até remoção:** Remove com magia ou habilidade específica
>
> **❓ Decisão Criativa: Como gerenciar duração de condições em tempo real?**
>
> > **Sugestão:**
> >
> > - Timer visual na UI (mostra tempo restante)
> > - Sistema de "ticks" a cada 6 segundos (1 round)
> > - **Alternativa:** Duração baseada em tempo real (ex: 10 segundos = 10 segundos)

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
> **❓ Decisão Criativa: Todos os tipos de dano serão implementados?**
>
> > **Sugestão:**
> >
> > - **MVP:** Implementar tipos principais (Fire, Cold, Lightning, Poison, Physical)
> > - **Futuro:** Adicionar tipos restantes conforme necessário
> > - **Recomendação:** Implementar todos os tipos (fidelidade a D&D)
>
> **❓ Decisão Criativa: Como mostrar tipos de dano visualmente?**
>
> > **Sugestão:**
> >
> > - Cor do número de dano baseada no tipo
> >   - **Fire:** Vermelho
> >   - **Cold:** Azul
> >   - **Lightning:** Amarelo/Branco
> >   - **Poison:** Verde
> >   - **Physical:** Branco/Cinza
> > - Efeitos visuais (partículas) baseados no tipo
> > - Som baseado no tipo de dano

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
> **❓ Decisão Criativa: Iniciativa será usado em tempo real?**
>
> > **Sugestão:**
> >
> > - **Opção 1:** Remover iniciativa (não necessário em tempo real)
> > - **Opção 2:** Iniciativa afeta velocidade de ações (maior iniciativa = ações mais rápidas)
> > - **Opção 3:** Iniciativa afeta ordem de spawn/aparência em combate
> > - **Recomendação:** Remover iniciativa (não necessário em tempo real, simplifica sistema)
>
> **❓ Decisão Criativa: Como determinar quem age primeiro em tempo real?**
>
> > **Sugestão:**
> >
> > - Todos agem simultaneamente (padrão de tempo real)
> > - Velocidade de ações baseada em atributos (DEX afeta velocidade de ataque)
> > - **Alternativa:** Sistema de "action speed" baseado em DEX (maior DEX = ações mais rápidas)

</details>

---

## 🎮 Feedback Visual e Sonoro

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>👁️ Feedback do Combate</b></summary>

> **❓ Decisão Criativa: Quais feedbacks visuais serão implementados?**
>
> > **Sugestão (Essenciais):**
> >
> > - **Dano Flutuante:** Números de dano flutuando sobre alvos
> > - **Indicador de HP:** Barra de HP sobre inimigos
> > - **Feedback de Acerto:** Efeito visual quando ataque acerta
> > - **Feedback de Erro:** Efeito visual quando ataque erra
> > - **Feedback de Crítico:** Efeito especial para críticos
> >
> > **Sugestão (Importantes):**
> >
> > - **Indicador de Status:** Ícones de condições na UI
> > - **Feedback de Bloqueio:** Efeito quando ataque é bloqueado por AC
> > - **Feedback de Esquiva:** Efeito quando ataque é esquivado
> > - **Feedback de Resistência:** Efeito quando dano é reduzido
>
> **❓ Decisão Criativa: Quais feedbacks sonoros serão implementados?**
>
> > **Sugestão (Essenciais):**
> >
> > - **SFX de Ataque:** Som de impacto quando ataque acerta
> > - **SFX de Erro:** Som quando ataque erra
> > - **SFX de Crítico:** Som especial para críticos
> > - **SFX de Morte:** Som quando criatura morre
> >
> > **Sugestão (Importantes):**
> >
> > - **SFX de Bloqueio:** Som quando ataque é bloqueado
> > - **SFX de Esquiva:** Som quando ataque é esquivado
> > - **SFX de Condições:** Sons para condições (veneno, stun, etc.)

</details>

---

## 📊 Resumo das Decisões Criativas Pendentes

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>❓ Checklist de Decisões</b></summary>

> **Adaptação de Turnos:**
>
> - [ ] ~~Como implementar "Ready Action" em tempo real?~~ ⚠️ **Consideração Futura** - Ver [Ideias Futuras](ideias-futuras/ready-action-emboscada.md)
> - [ ] Como balancear velocidade de combate (cooldowns)?
>
> **Ações:**
>
> - [x] Como mostrar Dodge visualmente? ✅ **Decidido:** Esquiva rápida (dash) para Dodge, posição de defesa para defesa
> - [ ] Como mostrar Disengage visualmente?
> - [ ] Help será usado em combate multiplayer ou apenas com NPCs?
>
> **AC e Dano:**
>
> - [ ] Como mostrar AC na UI?
> - [ ] AC afeta visualmente o personagem?
> - [ ] Como mostrar críticos visualmente?
> - [ ] Como mostrar resistências/vulnerabilidades na UI?
>
> **Ataques:**
>
> - [ ] Falha crítica tem efeito especial?
> - [ ] Como implementar vantagem/desvantagem em tempo real?
>
> **Cobertura:**
>
> - [ ] Como detectar cobertura automaticamente?
> - [ ] Cobertura afeta visualmente?
>
> **Ataques de Oportunidade:**
>
> - [ ] Como implementar em tempo real?
> - [ ] Como mostrar threat zone visualmente?
> - [ ] Ataques de oportunidade são automáticos ou manuais?
>
> **Morte:**
>
> - [ ] Como mostrar Death Saving Throws em tempo real?
> - [ ] O que acontece quando personagem morre?
> - [ ] Ressurreição será implementada?
>
> **Saving Throws:**
>
> - [ ] Como mostrar Saving Throws em tempo real?
>
> **Condições:**
>
> - [ ] Quais condições serão implementadas no MVP?
> - [ ] Como mostrar condições visualmente?
> - [ ] Como gerenciar duração de condições em tempo real?
>
> **Tipos de Dano:**
>
> - [ ] Todos os tipos de dano serão implementados?
> - [ ] Como mostrar tipos de dano visualmente?
>
> **Iniciativa:**
>
> - [ ] Iniciativa será usada em tempo real?
> - [ ] Como determinar quem age primeiro em tempo real?
>
> **Feedback:**
>
> - [ ] Quais feedbacks visuais serão implementados?
> - [ ] Quais feedbacks sonoros serão implementados?

</details>

---

## 🔗 Navegação

<details>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>📖 Links Relacionados</b></summary>

> - [← Voltar ao Índice](index.md)
> - [← Anterior: Sistemas de Personagem](sistemas-personagem.md)
> - [→ Próxima: Sistema de Equipamentos](equipamentos.md)
> - [📖 Regras D&D 5e (TDD)](../../03%20-%20TDD/dnd-rules/index.md)
> - [📊 Dashboard GDD](../dashboard-template.md)

</details>

---

**Última atualização:** 2024-12-27
