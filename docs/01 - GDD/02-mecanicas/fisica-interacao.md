# 2.6. Física e Interação

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>🌍 Física e Interação</b></summary>

> Regras do mundo físico e como objetos interagem entre si.

</details>

---

## Regras do Mundo Físico

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌍 Parâmetros Físicos Base</summary>

> **Gravidade:**
>
> - **Valor:** 9.8 m/s² (padrão Unreal Engine)
> - **Aplicação:** Afeta todos os objetos e personagens
> - **Velocidade Máxima de Queda:** 50 m/s (limite para evitar bugs)
>
> **Atrito:**
>
> | Terreno | Multiplicador de Atrito | Efeito |
> |---------|------------------------|--------|
> | Normal (pedra, terra) | 1.0x | Velocidade normal |
> | Gelo | 0.3x | Desliza, difícil parar |
> | Água | 0.5x | Movimento reduzido |
> | Areia | 0.7x | Movimento ligeiramente reduzido |
> | Grama | 0.9x | Movimento quase normal |
>
> **Colisão:**
>
> - **Sistema:** Colisão padrão do Unreal Engine
> - **Tipos de Colisão:**
>   - **Sólido:** Bloqueia movimento (paredes, portas fechadas)
>   - **Atravessável:** Permite movimento (grama, fumaça)
>   - **Interagível:** Pode ser usado (portas, baús, alavancas)

</details>

### Velocidade e Movimento

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏃 Valores de Movimento</summary>

> **Velocidade Base (D&D 5e):**
>
> - **Raça Pequena (Halfling, Gnome):** 7.5 m/s (25 pés/round = 4.2 m/s, adaptado para tempo real)
> - **Raça Média (Humano, Elfo, Anão):** 9 m/s (30 pés/round = 5 m/s, adaptado)
> - **Raça Grande:** 12 m/s (40 pés/round = 6.7 m/s, adaptado)
>
> **Aceleração e Desaceleração:**
>
> - **Aceleração:** 0 a velocidade máxima em 0.5 segundos
> - **Desaceleração:** Velocidade máxima a 0 em 0.3 segundos
> - **Curva de Movimento:** Suave (não instantâneo)
>
> **Modificadores:**
>
> - **Armadura Pesada:** -10% velocidade
> - **Condição Exaustão:** -25% a -50% velocidade (dependendo do nível)
> - **Magia Haste:** +100% velocidade (dobra)

</details>

### Pulo e Queda

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🦘 Sistema de Pulo</summary>

> **Altura de Pulo:**
>
> - **Pulo Normal:** 1.5m (baseado em STR 10)
> - **Modificador:** +0.1m por ponto de STR acima de 10
> - **Pulo Máximo (STR 20):** 2.5m
> - **Pulo com Corrida:** +50% altura (requer 3m de corrida antes)
>
> **Dano de Queda (D&D 5e):**
>
> | Altura da Queda | Dano | Regra |
> |-----------------|------|-------|
> | 0-3m | 0 | Queda segura |
> | 3-6m | 1d6 | Primeiro 3m causam dano |
> | 6-9m | 2d6 | Cada 3m adicionais = +1d6 |
> | 9-12m | 3d6 | Máximo 20d6 (60m) |
> | 12m+ | 4d6+ | Dano máximo em 60m |
>
> **Exemplo:**
>
> - Queda de 10m = 3d6 de dano (primeiro 3m = 1d6, próximos 6m = +2d6)
> - Queda de 20m = 6d6 de dano
> - Queda de 60m+ = 20d6 de dano (máximo)

</details>

### Movimento Aéreo (Voo)

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🦅 Sistema de Voo em Top-Down 2D</summary>

> **Criaturas Voadoras no Bestiário:**
>
> - **Green Dragon (Venomfang):** 24m voando (80 pés)
> - **Flameskull:** 12m voando (40 pés)
> - **Stirge:** 12m voando (40 pés)
>
> **Regra D&D 5e:**
>
> - Criaturas voadoras podem se mover pelo ar
> - Velocidade de voo é geralmente maior que velocidade terrestre
> - Criaturas voadoras podem cair se forem derrubadas (reduzidas a 0 HP ou efeitos especiais)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🎨 Representação Visual em Top-Down 2D</summary>

> **Objeto:** Criatura Voadora
>
> **Estado Inicial:** Voando (altura aérea)
>
> **Representação Visual:**
>
> 1. **Sombra no Chão:**
>    - Criatura projeta sombra no chão indicando posição horizontal
>    - Sombra se move independente de obstáculos terrestres
>    - Sombra indica que criatura está voando (não no chão)
>
> 2. **Sprite Elevado:**
>    - Sprite da criatura renderizado acima do chão (offset Y)
>    - Tamanho do sprite reduzido proporcionalmente à altura (quanto mais alto, menor)
>    - Sprite sempre visível acima de obstáculos terrestres
>
> 3. **Efeitos Visuais:**
>    - **Partículas de Asas:** Animação constante de batidas de asas
>    - **Aura/Brilho:** Efeito visual ao redor da criatura indicando estado voador
>    - **Animação de Voo:** Sprite animado com movimento de voo constante
>
> 4. **Indicador de Estado:**
>    - **Ícone de Voo:** Ícone de asas ou símbolo de voo na UI (ao selecionar criatura)
>    - **Tooltip:** "Voador" aparece ao passar mouse sobre criatura
>    - **Feedback Visual:** Criatura voadora tem outline ou brilho diferente

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌍 Mecânicas de Movimento Aéreo</summary>

> **Passagem sobre Obstáculos:**
>
> - **Objetos:** Criaturas voadoras podem voar sobre paredes, água, armadilhas e terreno difícil
> - **Colisão:** Não são bloqueadas por obstáculos terrestres
> - **Limites:** Apenas obstáculos aéreos (teto, estruturas altas) bloqueiam movimento
>
> **Velocidade de Voo:**
>
> - **Valor:** Baseado na velocidade de voo da criatura (D&D 5e)
> - **Exemplo:** Green Dragon = 24m/s voando, Stirge = 12m/s voando
> - **Modificadores:** Mesmos modificadores de velocidade terrestre (Haste, Exaustão, etc.)
>
> **Queda (Derrubar Criatura Voadora):**
>
> - **Condições para Queda:**
>   - Criatura reduzida a 0 HP
>   - Efeitos especiais que derrubam (magias, habilidades)
>   - Criatura perde capacidade de voo temporariamente
>
> - **Reação ao Cair:**
>   - Criatura cai no chão (posição da sombra)
>   - Aplica dano de queda (regras D&D 5e)
>   - Criatura perde capacidade de voo até recuperar HP ou efeito ser removido

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Impacto no Combate</summary>

> **Alcance de Ataques:**
>
> - **Ataques Corpo a Corpo:** Não podem atingir criaturas voadoras (a menos que atacante também voe)
> - **Ataques à Distância:** Funcionam normalmente (flechas, magias, etc.)
> - **Magias Especiais:** Algumas magias podem derrubar criaturas voadoras
>
> **Vantagens Táticas:**
>
> - **Posicionamento:** Criaturas voadoras podem se posicionar sobre inimigos
> - **Evasão:** Dificulta ataques corpo a corpo de inimigos terrestres
> - **Mobilidade:** Pode voar sobre terreno difícil sem penalidades
>
> **Desvantagens:**
>
> - **Exposição:** Criaturas voadoras são mais visíveis (não podem se esconder atrás de cobertura baixa)
> - **Vulnerabilidade:** Ataques à distância são mais eficazes (sem cobertura)
> - **Queda:** Se derrubadas, sofrem dano de queda adicional
>
> **📖 Ver detalhes completos:** [Sistema de Combate - Alcance e Posicionamento](sistema-combate.md#alcance-e-posicionamento)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💻 Pseudocódigo - Sistema de Voo</summary>

> **📖 Documentação Técnica:** Para implementação técnica, veja [TDD: Pseudocódigo de Combate](../../02%20-%20TDD/08-pseudocodigo/combate/combat-system.md)

</details>

## Interações entre Objetos

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔥 Sistema de Fogo</summary>

> **Fogo queima Madeira:**
>
> - **Tempo para Pegar Fogo:** 2 segundos de exposição contínua
> - **Duração:** Madeira queima por 10 segundos
> - **Dano:** 1d4 de dano de fogo por segundo para objetos/personagens em contato
> - **Propagação:** Fogo se espalha 1m por segundo em objetos de madeira adjacentes
> - **Extinção:** Água extingue fogo imediatamente em raio de 1m
>
> **Fogo em Outros Materiais:**
>
> - **Tecido:** Pega fogo em 1s, queima por 5s
> - **Papel:** Pega fogo em 0.5s, queima por 3s
> - **Pedra/Metal:** Não pega fogo (apenas aquece)
> - **Planta:** Pega fogo em 1s, queima por 8s, propaga rapidamente

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">❄️ Sistema de Gelo e Água</summary>

> **Gelo congela Água:**
>
> - **Tempo de Congelamento:** 3 segundos de exposição a magia de gelo
> - **Área Congelada:** Água vira gelo sólido (pode ser atravessada)
> - **Duração:** Gelo permanece por 1 minuto (ou até ser quebrado/aquecido)
> - **Quebra:** Gelo quebrado com 5 pontos de dano ou mais
>
> **Água apaga Fogo:**
>
> - **Extinção Imediata:** Água extingue fogo em raio de 1m instantaneamente
> - **Área Úmida:** Área molhada previne fogo por 10 segundos
> - **Chuva:** Extingue todos os fogos em área grande

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚡ Sistema de Eletricidade</summary>

> **Eletricidade conduz em Água:**
>
> - **Propagação:** Eletricidade se espalha em toda área com água em 0.5 segundos
> - **Raio de Efeito:** Área de água conectada (até 20m de raio)
> - **Dano:** Dano de eletricidade aplicado a todos na área molhada
> - **Isolamento:** Objetos secos não conduzem (madeira, couro, borracha)

</details>

## Sistema de Interação

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📏 Parâmetros Base</summary>

> **Raio de Interação:**
>
> - **Padrão:** 2 metros
> - **Modificadores:** Nenhum (fixo para todos os objetos)
> - **Visual:** Objeto destacado (highlight) quando dentro do raio
> - **Prompt:** Texto "Pressione E para [ação]" aparece acima do objeto
>
> **Feedback Visual:**
>
> - **Highlight:** Objeto brilha ou tem outline quando interagível
> - **Cor:** Verde (pode interagir), Amarelo (precisa condição), Vermelho (bloqueado)
> - **Ícone:** Ícone de interação aparece acima do objeto

</details>

### Tipos de Interação (Modelo Objeto-Ação-Reação)

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🚪 Portas</summary>

> **Objeto:** Porta
>
> **Estados Possíveis:**
>
> - **Fechada e Destrancada:** Pode ser aberta
> - **Fechada e Trancada:** Precisa chave ou lockpick
> - **Aberta:** Permite passagem
>
> **Ação do Jogador:**
>
> - Pressionar tecla 'E' dentro de 2m da porta
>
> **Reação do Sistema:**
>
> - **Se destrancada:**
>   - Toca som 'door_open.wav'
>   - Anima abertura da porta (1 segundo)
>   - Remove colisão, permite passagem
>   - Porta pode ser fechada novamente
>
> - **Se trancada:**
>   - Toca som 'door_locked.wav'
>   - Mostra mensagem "Trancada" (vermelho)
>   - Verifica se jogador tem chave no inventário
>   - Se tem chave: destranca e abre (mesmo processo de destrancada)
>   - Se não tem: mantém trancada
>
> - **Se aberta:**
>   - Pressionar 'E' fecha a porta
>   - Toca som 'door_close.wav'
>   - Restaura colisão

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📦 Baús</summary>

> **Objeto:** Baú
>
> **Estados Possíveis:**
>
> - **Fechado:** Contém loot
> - **Aberto:** Vazio (já foi coletado)
> - **Trancado:** Precisa chave ou lockpick
>
> **Ação do Jogador:**
>
> - Pressionar tecla 'E' dentro de 2m do baú
>
> **Reação do Sistema:**
>
> - **Se fechado e destrancado:**
>   - Toca som 'chest_open.wav'
>   - Anima abertura (1.5 segundos)
>   - Gera loot baseado na tabela de loot do baú
>   - Mostra interface de loot (itens disponíveis)
>   - Jogador pode coletar itens
>   - Baú fica aberto após coletar tudo
>
> - **Se trancado:**
>   - Mesmo processo de porta trancada
>   - Após destrancar, segue processo de baú destrancado
>
> - **Se aberto:**
>   - Mostra mensagem "Vazio" (cinza)
>   - Não permite interação

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👤 NPCs</summary>

> **Objeto:** NPC (Personagem Não-Jogável)
>
> **Estados Possíveis:**
>
> - **Disponível:** Pode conversar
> - **Ocupado:** Em diálogo com outro jogador (multiplayer)
> - **Hostil:** Em combate, não pode conversar
>
> **Ação do Jogador:**
>
> - Pressionar tecla 'E' dentro de 2m do NPC
>
> **Reação do Sistema:**
>
> - **Se disponível:**
>   - Pausa o jogo (ou overlay de diálogo)
>   - Abre interface de diálogo
>   - Mostra avatar do NPC
>   - Exibe opções de diálogo baseadas no estado da quest
>   - Toca som de voz do NPC (se disponível)
>
> - **Se ocupado:**
>   - Mostra mensagem "NPC está ocupado"
>   - Não abre diálogo
>
> - **Se hostil:**
>   - Não permite interação
>   - NPC ataca se jogador se aproximar

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💎 Itens no Chão</summary>

> **Objeto:** Item coletável
>
> **Estados Possíveis:**
>
> - **No chão:** Pode ser coletado
>   - Brilha ou pulsa para indicar que é coletável
>
> **Ação do Jogador:**
>
> - Pressionar tecla 'E' dentro de 2m do item
> - Ou passar por cima (coleta automática opcional)
>
> **Reação do Sistema:**
>
> - **Se inventário tem espaço:**
>   - Toca som 'item_pickup.wav'
>   - Item desaparece do chão
>   - Adiciona ao inventário
>   - Mostra notificação "Item coletado: [Nome]"
>
> - **Se inventário está cheio:**
>   - Toca som 'error.wav'
>   - Mostra mensagem "Inventário cheio" (vermelho)
>   - Item permanece no chão
>
> - **Se item é único e já possui:**
>   - Verifica se item pode ser empilhado
>   - Se sim: adiciona à pilha
>   - Se não: mostra mensagem "Você já possui este item"

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚙️ Alavancas e Botões</summary>

> **Objeto:** Alavanca/Botão/Mecanismo
>
> **Estados Possíveis:**
>
> - **Desativado:** Não está ativo
> - **Ativado:** Está ativo (pode ser desativado novamente se toggle)
> - **Bloqueado:** Não pode ser usado (precisa condição)
>
> **Ação do Jogador:**
>
> - Pressionar tecla 'E' dentro de 2m da alavanca
>
> **Reação do Sistema:**
>
> - **Se desativado:**
>   - Toca som 'lever_activate.wav'
>   - Anima movimento da alavanca (0.5 segundos)
>   - Ativa mecanismo conectado (porta abre, ponte levanta, etc.)
>   - Alavanca fica na posição ativada
>
> - **Se ativado (toggle):**
>   - Desativa mecanismo
>   - Alavanca volta à posição original
>
> - **Se bloqueado:**
>   - Toca som 'error.wav'
>   - Mostra mensagem "Bloqueado" ou condição necessária
>   - Não ativa

</details>

---

## Sistema de Peso e Empurrar

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">💪 Regras de Empurrar</summary>

> **Capacidade de Carga (D&D 5e):**
>
> - **Carga Normal:** STR × 15 kg (pode carregar)
> - **Carga Máxima:** STR × 30 kg (pode arrastar/empurrar)
> - **Exemplo:** STR 16 = 240 kg carga normal, 480 kg máxima
>
> **Empurrar Objetos:**
>
> | Peso do Objeto | STR Necessária | Velocidade de Empurrar |
> |----------------|----------------|------------------------|
> | < 50% carga normal | Qualquer | Velocidade normal |
> | 50-100% carga normal | STR 10+ | 50% velocidade |
> | 100-200% carga normal | STR 15+ | 25% velocidade |
> | > 200% carga normal | Impossível | Não pode empurrar |
>
> **Objetos Fixos vs. Móveis:**
>
> - **Móveis:** Caixas, barris, móveis (podem ser empurrados)
> - **Fixos:** Paredes, estátuas grandes, estruturas (não podem ser empurrados)
> - **Especiais:** Alguns objetos podem ser empurrados apenas em certas direções (portas, alavancas)
>
> **Empurrar em Combate:**
>
> - **Shove Action (D&D 5e):** Pode empurrar criatura 1.5m se STR maior
> - **Força:** Baseada em teste de Força (STR) vs. Força do alvo
> - **Resultado:** Alvo é empurrado 1.5m na direção escolhida

</details>

---

## Regras de Colisão Detalhadas

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔄 Tipos de Colisão</summary>

> **Objetos Sólidos:**
>
> - **Paredes:** Bloqueiam movimento completamente
> - **Portas Fechadas:** Bloqueiam até serem abertas
> - **Rochas Grandes:** Bloqueiam movimento
> - **Móveis:** Podem ser empurrados ou bloqueiam (depende do tamanho)
>
> **Objetos Atravessáveis:**
>
> - **Grama:** Permite movimento, reduz velocidade em 10%
> - **Fumaça:** Permite movimento, reduz visibilidade
> - **Água Rasa (< 1m):** Permite movimento, reduz velocidade em 50%
> - **Água Profunda (> 1m):** Requer natação ou bloqueia movimento
>
> **Objetos Interagíveis:**
>
> - **Portas:** Bloqueiam quando fechadas, permitem quando abertas
> - **Baús:** Bloqueiam movimento, mas podem ser abertos
> - **Alavancas:** Não bloqueiam movimento, apenas interagíveis

</details>

---

## Regras de Ambiente

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🌡️ Efeitos Ambientais</summary>

> **Iluminação:**
>
> - **Brilho:** Áreas iluminadas permitem visão normal
> - **Escuridão:** Reduz visibilidade (requer luz ou visão no escuro)
> - **Sombra:** Visibilidade reduzida em 50%
>
> **Temperatura:**
>
> - **Frio Extremo:** Causa 1d6 de dano de frio por minuto (sem proteção)
> - **Calor Extremo:** Causa 1d6 de dano de fogo por minuto (sem proteção)
> - **Proteção:** Roupas/armaduras adequadas previnem dano
>
> **Terreno Difícil:**
>
> - **Terreno Difícil (D&D 5e):** Custa 2m de movimento para cada 1m percorrido
> - **Exemplos:** Vegetação densa, escombros, gelo escorregadio
> - **Efeito:** Velocidade reduzida pela metade

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Regras físicas e interações baseadas em D&D 5e e Unreal Engine |
| v1.1 | 2024-12-27 | Atualizado - Referências corrigidas após expansão de mecânicas |

**Navegação:** [← Voltar ao Índice](index.md) | [→ Próxima Seção: IA e Comportamento](../03-ia-comportamento/index.md)
