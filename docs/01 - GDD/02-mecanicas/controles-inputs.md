# 2.5. Controles e Inputs

---

<details open>
<summary style="background-color: #e8e8e8; padding: 4px 8px; border-radius: 4px;"><b>⌨️ Controles e Inputs</b></summary>

> Mapeamento exato dos botões para todos os dispositivos suportados e feedback visual/sonoro. Cada ação segue o modelo Objeto-Ação-Reação para especificação precisa do comportamento do sistema.

</details>

---

## 📋 Tabela de Referência Rápida

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⌨️ PC - Teclado e Mouse</summary>

> | Ação | Tecla/Botão | Resposta do Sistema |
> |------|-------------|---------------------|
> | **Movimentar** | WASD | Move personagem na direção pressionada |
> | **Atacar** | Botão Esquerdo do Mouse | Executa ataque corpo a corpo ou à distância |
> | **Interagir** | E | Interage com objetos/NPCs dentro do raio |
> | **Usar Habilidade 1-4** | 1, 2, 3, 4 | Ativa habilidade correspondente da hotbar |
> | **Abrir Inventário** | I | Abre/fecha menu de inventário |
> | **Abrir Ficha** | C | Abre/fecha ficha de personagem |
> | **Abrir Mapa** | M | Abre/fecha mapa do mundo |
> | **Pausar** | ESC | Pausa o jogo e abre menu principal |

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📱 Mobile - Touch</summary>

> | Ação | Input | Resposta do Sistema |
> |------|-------|---------------------|
> | **Movimentar** | Analógico Virtual (esquerda) | Move personagem na direção do analógico |
> | **Atacar** | Botão de Ataque (direita) | Executa ataque corpo a corpo ou à distância |
> | **Interagir** | Botão de Interação | Interage com objetos/NPCs dentro do raio |
> | **Usar Habilidades** | Hotbar (inferior) | Toque na habilidade para ativar |
> | **Abrir Menus** | Botões de Menu | Abre/fecha menus (inventário, ficha, mapa) |

</details>

---

## 🎮 Controles Detalhados (Modelo Objeto-Ação-Reação)

### Movimentação

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🏃 Movimentar (WASD / Analógico Virtual)</summary>

> **Objeto:** Personagem do Jogador
>
> **Estados Possíveis:**
>
> - **Parado:** Personagem não está se movendo
> - **Andando:** Movimento normal
> - **Correndo:** Movimento rápido (se aplicável)
> - **Bloqueado:** Não pode se mover (em diálogo, menu, etc.)
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla W/A/S/D (ou combinação)
> - **Mobile:** Mover analógico virtual na direção desejada
>
> **Reação do Sistema:**
>
> - **Se não bloqueado:**
>   - Personagem acelera na direção pressionada (0 a velocidade máxima em 0.5s)
>   - Animação de movimento é ativada
>   - Som de passos toca (varia conforme terreno)
>   - Câmera segue personagem suavemente
>   - Velocidade aplicada conforme raça (pequena: 7.5 m/s, média: 9 m/s, grande: 12 m/s)
>
> - **Se bloqueado:**
>   - Nenhuma reação (personagem permanece parado)
>   - Feedback visual: cursor muda para indicar bloqueio (se aplicável)
>
> **Feedback Visual:**
>
> - Animação de movimento (walk/run cycle)
> - Partículas de poeira/grama ao pisar (se aplicável)
> - Indicador de direção (se aplicável)
>
> **Feedback Sonoro:**
>
> - Som de passos (varia conforme terreno: pedra, grama, água)
> - Volume ajustado conforme velocidade

</details>

### Combate

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⚔️ Atacar (Botão Esquerdo Mouse / Botão Ataque)</summary>

> **Objeto:** Arma Equipada / Personagem
>
> **Estados Possíveis:**
>
> - **Pronto:** Pode atacar (sem cooldown)
> - **Em Cooldown:** Ataque em recarga (não pode atacar)
> - **Sem Arma:** Não pode atacar corpo a corpo
> - **Sem Alvo:** Não há alvo válido no alcance
>
> **Ação do Jogador:**
>
> - **PC:** Clicar botão esquerdo do mouse
> - **Mobile:** Tocar botão de ataque
>
> **Reação do Sistema:**
>
> - **Se pronto e com alvo válido:**
>   - Verifica alcance da arma (corpo a corpo: 1.5m, distância: conforme arma)
>   - Verifica se há alvo no alcance (inimigo ou objeto atacável)
>   - Se há alvo:
>     - Toca som de ataque (varia conforme arma: espada, arco, etc.)
>     - Anima ataque (animação de swing/lançamento)
>     - Calcula dano baseado em arma + modificadores
>     - Aplica dano ao alvo
>     - Mostra número de dano flutuante acima do alvo
>     - Inicia cooldown do ataque (baseado em velocidade da arma)
>   - Se não há alvo:
>     - Toca som de "swing no ar" (mais leve)
>     - Anima ataque (sem impacto)
>     - Inicia cooldown normalmente
>
> - **Se em cooldown:**
>   - Nenhuma reação (ataque não é executado)
>   - Feedback visual: botão pisca ou mostra timer (se aplicável)
>
> - **Se sem arma:**
>   - Toca som de erro
>   - Mostra mensagem "Você precisa de uma arma" (se aplicável)
>
> **Feedback Visual:**
>
> - Animação de ataque (swing, lançamento, etc.)
> - Efeito de impacto no alvo (partículas, sangue, etc.)
> - Número de dano flutuante (cor varia: branco = normal, amarelo = crítico, vermelho = letal)
> - Trail da arma (se aplicável)
>
> **Feedback Sonoro:**
>
> - Som de ataque (varia conforme arma)
> - Som de impacto (varia conforme alvo: carne, metal, madeira)
> - Som de crítico (se aplicável)

</details>

### Interação

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🤝 Interagir (Tecla E / Botão Interação)</summary>

> **Objeto:** Objeto/NPC Interagível
>
> **Estados Possíveis:**
>
> - **Dentro do Raio:** Jogador está a 2m ou menos do objeto
> - **Fora do Raio:** Jogador está além de 2m
> - **Interagível:** Objeto pode ser usado
> - **Bloqueado:** Objeto não pode ser usado (condição não atendida)
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 'E'
> - **Mobile:** Tocar botão de interação
>
> **Reação do Sistema:**
>
> - **Se dentro do raio e interagível:**
>   - Verifica tipo de objeto (porta, baú, NPC, item, alavanca)
>   - Executa ação específica do objeto (ver `fisica-interacao.md` para detalhes)
>   - Toca som de interação (varia conforme tipo)
>   - Mostra feedback visual apropriado
>
> - **Se dentro do raio mas bloqueado:**
>   - Toca som de erro
>   - Mostra mensagem de bloqueio (ex: "Trancada", "Precisa chave", etc.)
>   - Highlight do objeto fica vermelho
>
> - **Se fora do raio:**
>   - Nenhuma reação (interação não é executada)
>
> **Feedback Visual:**
>
> - Highlight do objeto quando dentro do raio (verde = pode, amarelo = precisa condição, vermelho = bloqueado)
> - Prompt visual "Pressione E para [ação]" acima do objeto
> - Ícone de interação aparece
>
> **Feedback Sonoro:**
>
> - Som de interação (varia conforme tipo de objeto)
> - Som de erro (se bloqueado)

</details>

### Habilidades

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">✨ Usar Habilidade (Teclas 1-4 / Hotbar Touch)</summary>

> **Objeto:** Habilidade na Hotbar
>
> **Estados Possíveis:**
>
> - **Disponível:** Habilidade pode ser usada (sem cooldown, recursos suficientes)
> - **Em Cooldown:** Habilidade em recarga
> - **Sem Recursos:** Falta mana/energia/etc. para usar
> - **Sem Alvo:** Habilidade requer alvo mas não há alvo válido
> - **Slot Vazio:** Não há habilidade neste slot
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 1, 2, 3 ou 4
> - **Mobile:** Tocar habilidade na hotbar
>
> **Reação do Sistema:**
>
> - **Se disponível:**
>   - Verifica se habilidade requer alvo
>   - Se requer alvo: verifica se há alvo válido no alcance
>   - Se tudo OK:
>     - Consome recursos (mana, energia, etc.)
>     - Toca som característico da habilidade
>     - Anima habilidade (animação do personagem)
>     - Aplica efeito da habilidade (dano, cura, buff, etc.)
>     - Mostra efeito visual da habilidade
>     - Inicia cooldown da habilidade
>     - Atualiza UI (barra de recursos, cooldown visual)
>   - Se falta alvo:
>     - Toca som de erro
>     - Mostra mensagem "Selecione um alvo" (se aplicável)
>     - Habilidade não é executada
>
> - **Se em cooldown:**
>   - Nenhuma reação (habilidade não é executada)
>   - Feedback visual: ícone da habilidade mostra timer de cooldown
>
> - **Se sem recursos:**
>   - Toca som de erro
>   - Mostra mensagem "Recursos insuficientes" (se aplicável)
>   - Barra de recursos pisca (feedback visual)
>
> - **Se slot vazio:**
>   - Nenhuma reação (nada acontece)
>
> **Feedback Visual:**
>
> - Animação da habilidade (varia conforme tipo)
> - Efeito visual da habilidade (partículas, raios, etc.)
> - Indicador de cooldown (timer, overlay escuro no ícone)
> - Barra de recursos atualizada
>
> **Feedback Sonoro:**
>
> - Som característico da habilidade (varia conforme tipo)
> - Som de erro (se não pode usar)

</details>

### Menus e Interface

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📦 Abrir Inventário (Tecla I / Botão Menu)</summary>

> **Objeto:** Menu de Inventário
>
> **Estados Possíveis:**
>
> - **Fechado:** Menu não está aberto
> - **Aberto:** Menu está aberto
> - **Bloqueado:** Não pode abrir (em combate, diálogo, etc.)
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 'I'
> - **Mobile:** Tocar botão de inventário
>
> **Reação do Sistema:**
>
> - **Se fechado e não bloqueado:**
>   - Pausa o jogo (ou mostra overlay)
>   - Abre interface de inventário
>   - Mostra itens do jogador organizados
>   - Toca som de abertura de menu
>   - Cursor muda para modo menu (se aplicável)
>
> - **Se aberto:**
>   - Fecha interface de inventário
>   - Retoma o jogo (ou remove overlay)
>   - Toca som de fechamento de menu
>
> - **Se bloqueado:**
>   - Toca som de erro
>   - Mostra mensagem "Não pode abrir inventário agora" (se aplicável)
>
> **Feedback Visual:**
>
> - Interface de inventário aparece/desaparece com animação
> - Itens organizados em grid ou lista
> - Highlight de item selecionado
>
> **Feedback Sonoro:**
>
> - Som de abertura/fechamento de menu
> - Som de erro (se bloqueado)

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📋 Abrir Ficha (Tecla C / Botão Menu)</summary>

> **Objeto:** Menu de Ficha de Personagem
>
> **Estados Possíveis:**
>
> - **Fechado:** Menu não está aberto
> - **Aberto:** Menu está aberto
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 'C'
> - **Mobile:** Tocar botão de ficha
>
> **Reação do Sistema:**
>
> - **Se fechado:**
>   - Pausa o jogo (ou mostra overlay)
>   - Abre interface de ficha de personagem
>   - Mostra atributos, habilidades, equipamentos, etc.
>   - Toca som de abertura de menu
>
> - **Se aberto:**
>   - Fecha interface de ficha
>   - Retoma o jogo
>   - Toca som de fechamento de menu
>
> **Feedback Visual:**
>
> - Interface de ficha aparece/desaparece com animação
> - Informações organizadas em abas (Atributos, Habilidades, Equipamentos, etc.)
>
> **Feedback Sonoro:**
>
> - Som de abertura/fechamento de menu

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🗺️ Abrir Mapa (Tecla M / Botão Menu)</summary>

> **Objeto:** Menu de Mapa
>
> **Estados Possíveis:**
>
> - **Fechado:** Mapa não está aberto
> - **Aberto:** Mapa está aberto
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 'M'
> - **Mobile:** Tocar botão de mapa
>
> **Reação do Sistema:**
>
> - **Se fechado:**
>   - Pausa o jogo (ou mostra overlay)
>   - Abre interface de mapa
>   - Mostra mapa do mundo com localização atual
>   - Mostra pontos de interesse descobertos
>   - Toca som de abertura de menu
>
> - **Se aberto:**
>   - Fecha interface de mapa
>   - Retoma o jogo
>   - Toca som de fechamento de menu
>
> **Feedback Visual:**
>
> - Interface de mapa aparece/desaparece com animação
> - Mapa mostra área explorada e não explorada
> - Marcadores para locais importantes
>
> **Feedback Sonoro:**
>
> - Som de abertura/fechamento de menu

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">⏸️ Pausar (Tecla ESC / Botão Menu)</summary>

> **Objeto:** Menu Principal / Sistema de Pausa
>
> **Estados Possíveis:**
>
> - **Jogando:** Jogo está rodando
> - **Pausado:** Jogo está pausado
> - **Em Menu:** Menu principal está aberto
>
> **Ação do Jogador:**
>
> - **PC:** Pressionar tecla 'ESC'
> - **Mobile:** Tocar botão de pausa
>
> **Reação do Sistema:**
>
> - **Se jogando:**
>   - Pausa o jogo completamente
>   - Abre menu principal (opções: Continuar, Configurações, Sair, etc.)
>   - Toca som de pausa
>   - Cursor muda para modo menu
>
> - **Se pausado:**
>   - Fecha menu principal
>   - Retoma o jogo
>   - Toca som de retomada
>
> - **Se em outro menu (inventário, ficha, etc.):**
>   - Fecha menu atual
>   - Se pressionar ESC novamente, abre menu principal
>
> **Feedback Visual:**
>
> - Menu principal aparece/desaparece com animação
> - Opções claras: Continuar, Configurações, Sair, etc.
>
> **Feedback Sonoro:**
>
> - Som de pausa/retomada

</details>

---

## 📱 Controles Mobile Específicos

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">📱 Analógico Virtual</summary>

> **Objeto:** Analógico Virtual de Movimento
>
> **Estados Possíveis:**
>
> - **Inativo:** Jogador não está tocando
> - **Ativo:** Jogador está arrastando o analógico
>
> **Ação do Jogador:**
>
> - Tocar e arrastar analógico virtual na tela
>
> **Reação do Sistema:**
>
> - **Se ativo:**
>   - Calcula direção baseada na posição do toque relativa ao centro
>   - Calcula intensidade baseada na distância do toque ao centro
>   - Move personagem na direção calculada
>   - Velocidade proporcional à intensidade (0 a 100%)
>   - Anima analógico virtual seguindo o dedo
>
> - **Se inativo:**
>   - Personagem para de se mover
>   - Analógico retorna ao centro
>
> **Feedback Visual:**
>
> - Analógico virtual visível na tela
> - Círculo externo (limite) e círculo interno (posição atual)
> - Animação suave ao mover
>
> **Feedback Sonoro:**
>
> - Nenhum (som de passos é do personagem, não do analógico)

</details>

---

## 🎨 Sistema de Feedback Unificado

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">👁️ Feedback Visual Geral</summary>

> **Cores Padrão:**
>
> - **Verde:** Ação permitida, sucesso
> - **Amarelo:** Ação requer condição, atenção necessária
> - **Vermelho:** Ação bloqueada, erro, perigo
> - **Azul:** Informação, neutro
> - **Branco:** Normal, padrão
>
> **Animações:**
>
> - Todas as ações têm animação correspondente
> - Animações são suaves e responsivas
> - Feedback imediato (sem delay perceptível)
>
> **Efeitos Visuais:**
>
> - Partículas para ações importantes
> - Highlight para objetos interagíveis
> - Números flutuantes para dano/recursos
> - Indicadores de cooldown claros

</details>

<details>
<summary style="background-color: #d8d8d8; padding: 3px 6px; border-radius: 3px;">🔊 Feedback Sonoro Geral</summary>

> **Categorias de Som:**
>
> - **Ações:** Som de ataque, movimento, interação
> - **UI:** Som de abertura/fechamento de menus
> - **Feedback:** Som de sucesso, erro, alerta
> - **Ambiente:** Som de passos, ambiente
>
> **Parâmetros:**
>
> - Volume ajustável por categoria
> - Pitch varia conforme contexto (ex: ataque crítico = pitch mais alto)
> - Spatial audio para sons 3D (se aplicável)

</details>

---

## 📝 Changelog

| Versão | Data | Alteração |
|--------|------|-----------|
| v1.0 | 2024-12-27 | Versão inicial - Mapeamento de controles PC e Mobile com modelo Objeto-Ação-Reação |
| v1.1 | 2024-12-27 | Atualizado - Referências corrigidas após expansão de mecânicas |

**Navegação:** [← Voltar ao Índice](index.md) | [← Anterior: Sistema de Inventário](inventario.md) | [→ Próxima: Física e Interação](fisica-interacao.md)
